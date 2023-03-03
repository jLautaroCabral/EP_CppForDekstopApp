#include "AdminExemplariesWindowController.h"
#include "resource.h"
#include "framework.h"
#include <stdio.h>
#include <string>
#include "DbContextLibrary.h"
#include "BookFactory.h"
#include "ExemplaryFactory.h"
#include "Utils.h"
#include "UtilsUI.h"

AdminExemplariesWindowController::AdminExemplariesWindowController() {}
AdminExemplariesWindowController::~AdminExemplariesWindowController() {}
AdminExemplariesWindowController* AdminExemplariesWindowController::singleton_ = nullptr;

AdminExemplariesWindowController* AdminExemplariesWindowController::GetInstance()
{
	/**
	 * This is a safer way to create an instance. instance = new Singleton is
	 * dangeruous in case two instance threads wants to access at the same time
	 */
	if (singleton_ == nullptr) {
		singleton_ = new AdminExemplariesWindowController();
	}
	return singleton_;
}


void AdminExemplariesWindowController::InitializeWindowHandlersIfNeeded(HWND hDlg)
{
	if (!AdminExemplariesWindowController::GetInstance()->handlersInitialized)
	{
		AdminExemplariesWindowController::GetInstance()->handlersInitialized = true;
	}

	UpdateComboBoxesInfo(hDlg);
	UpdateListBoxInfo(hDlg);
}

void AdminExemplariesWindowController::HandleWindowCommand(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	int lWord = LOWORD(wParam);
	int hWord = HIWORD(wParam);

	switch (message)
	{
	case WM_COMMAND:
	{
		switch (lWord)
		{
		case IDOK:
		case IDCANCEL:
		{
			EndDialog(hDlg, LOWORD(wParam));
			break;
		}
		case BTN_ADDEXEMPLARY_ADD:
		{
			if (hWord == BN_CLICKED)
			{
				if (!PerformChecks(hDlg)) break;

				HWND hCbSelectedBookListExemplaries = GetDlgItem(hDlg, CB_LISTEXEMPLARIES_SELECTEDBOOK);
				HWND hCbSelectedBookAddExemplary = GetDlgItem(hDlg, CB_ADDEXEMPLARY_SELECTEDBOOK);

				std::string exemplaryEditionNum;
				std::string exemplaryUbication;
				int exemplaryBookId;

				if (!UtilsUI::TryGetStringFromInputField(hDlg, INPF_ADDEXEMPLARY_EDITION, "Numero de edicion", exemplaryEditionNum)) break;
				if (!UtilsUI::TryGetStringFromInputField(hDlg, INPF_ADDEXEMPLARY_UBICATION, "Ubicacion en la biblioteca", exemplaryUbication)) break;

				// Get selected index.
				int selectedItem = (int)SendMessage(hCbSelectedBookAddExemplary, CB_GETCURSEL, NULL, NULL);
				// Get item data.
				int modelIdOfSelectedItem = (int)SendMessage(hCbSelectedBookAddExemplary, CB_GETITEMDATA, selectedItem, NULL);				

				Exemplary* newExemplary = ExemplaryFactory::CreateExemplary(stoi(exemplaryEditionNum), exemplaryUbication, modelIdOfSelectedItem);
				DbContextLibrary::GetInstance()->bookTable.GetElementByID(modelIdOfSelectedItem)->exemplaries.push_back(newExemplary);

				SendMessage(hCbSelectedBookListExemplaries, CB_SETCURSEL, (WPARAM)selectedItem, NULL);
				UpdateListBoxInfo(hDlg);
			}
		}
		case BTN_LISTEXEMPLARIES_REMOVE:
		{
			// TODO: REMOVE, UPDATE MODELS
			/*
			if (hWord == BN_CLICKED)
			{
				HWND hwndList = GetDlgItem(hDlg, LB_BOOKS);
				// Get selected index.
				int selectedItem = (int)SendMessage(hwndList, LB_GETCURSEL, NULL, NULL);
				// Get item data.
				int modelIdOfSelectedItem = (int)SendMessage(hwndList, LB_GETITEMDATA, selectedItem, NULL);

				DbContextLibrary::GetInstance()->bookTable.Remove(modelIdOfSelectedItem);
				UpdateListBoxInfo(hDlg);
				SendMessage(hwndList, LB_SETCURSEL, (WPARAM)0, NULL);
				UpdateItemSelectionOnList(hDlg);
			}
			*/
		}
		case LB_BOOKS:
		{
			if (HIWORD(wParam) == LBN_SELCHANGE)
			{
				UpdateItemSelectionOnList(hDlg);
			}
		}
		case CB_LISTEXEMPLARIES_SELECTEDBOOK:
		{
			if (hWord == CBN_SELENDOK)
			{
				//UpdateItemSelectionOnList(hDlg);
				UpdateListBoxInfo(hDlg);
			}
		}
		}
	}
	}
}

void AdminExemplariesWindowController::HandlePaintCommand(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
}


bool AdminExemplariesWindowController::PerformChecks(HWND hDlg)
{
	int dlgItemsIDsToCheck[] =
	{
		INPF_ADDEXEMPLARY_EDITION,
		INPF_ADDEXEMPLARY_UBICATION
	};

	for (int const& id : dlgItemsIDsToCheck)
	{
		if (PerformItemCheck(hDlg, id))
		{
			return false; // There is something wrong
		}
	}

	return true; // All good
}

bool AdminExemplariesWindowController::PerformItemCheck(HWND hDlg, int dlgID)
{
	bool thereIsAError = false;
	int iTextLength;
	HWND hInpf;

	switch (dlgID)
	{
		case INPF_ADDEXEMPLARY_EDITION:
		{
			hInpf = GetDlgItem(hDlg, INPF_ADDEXEMPLARY_EDITION);
			iTextLength = GetWindowTextLength(hInpf);
			if (iTextLength == 0)
			{
				thereIsAError = true;
				MessageBox(NULL, L"Es necesario ingresar un valor en el campo 'Numero de edicion'", L"Error", MB_ICONERROR);
			}

			wchar_t str[100];
			GetWindowTextW(hInpf, str, iTextLength + 1);
			if (!Utils::IsNumber(*Utils::WCharToString_TPointer(str)))
			{
				thereIsAError = true;
				MessageBox(NULL, L"Es necesario ingresar un número válido en el campo 'Numero de edicion'", L"Error", MB_ICONERROR);
			}
		}
		case INPF_ADDEXEMPLARY_UBICATION:
		{
			hInpf = GetDlgItem(hDlg, INPF_ADDEXEMPLARY_UBICATION);
			iTextLength = GetWindowTextLength(hInpf);
			if (iTextLength == 0)
			{
				thereIsAError = true;
				MessageBox(NULL, L"Es necesario ingresar una ubicacion en el campo 'Ubicacion en la biblioteca'", L"Error", MB_ICONERROR);
			}
		}
	}
	return thereIsAError;
}

void AdminExemplariesWindowController::UpdateListBoxInfo(HWND hDlg)
{
	HWND hLbListExemplaries = GetDlgItem(hDlg, LB_LISTEXEMPLARIES_EXEMPLARIES);
	HWND hCbSelectedBookListExemplaries = GetDlgItem(hDlg, CB_LISTEXEMPLARIES_SELECTEDBOOK);
	SendMessage(hLbListExemplaries, LB_RESETCONTENT, NULL, NULL);

	// Get selected index.
	int selectedItem = (int)SendMessage(hCbSelectedBookListExemplaries, CB_GETCURSEL, NULL, NULL);
	// Get item data.
	int modelIdOfSelectedItem = (int)SendMessage(hCbSelectedBookListExemplaries, CB_GETITEMDATA, selectedItem, NULL);

	const Book* book = DbContextLibrary::GetInstance()->bookTable.GetElementByID(modelIdOfSelectedItem);
	
	// Then fill the list box
	for (const Exemplary* exemplary : book->exemplaries)
	{
		// From strting to wchar_t
		std::string stringItemToAdd =
			"Edition number:  " + std::to_string(exemplary->editionNumber) +
			",   Ubication:  " + exemplary->libraryUbication;

		int itemPos = SendMessage(hLbListExemplaries, LB_ADDSTRING, NULL,
			(LPARAM)Utils::StringToConstWchar_TPointer(stringItemToAdd));

		// Set the array index of the player as item data.
		// This enables us to retrieve the item from the array
		// even after the items are sorted by the list box.
		SendMessage(hLbListExemplaries, LB_SETITEMDATA, itemPos, (LPARAM)book->modelID);
	}
}

void AdminExemplariesWindowController::UpdateComboBoxesInfo(HWND hDlg)
{
	HWND hCbSelectedBookAddExemplary = GetDlgItem(hDlg, CB_ADDEXEMPLARY_SELECTEDBOOK);
	HWND hCbSelectedBookListExemplaries = GetDlgItem(hDlg, CB_LISTEXEMPLARIES_SELECTEDBOOK);

	SendMessage(hCbSelectedBookAddExemplary, CB_RESETCONTENT, NULL, NULL);
	SendMessage(hCbSelectedBookListExemplaries, CB_RESETCONTENT, NULL, NULL);

	// Then fill the list box
	for (const Book* book : DbContextLibrary::GetInstance()->bookTable.GetAllItems())
	{
		// From strting to wchar_t
		std::string stringItemToAdd = "" + book->name + ",   " + book->autor;
		const wchar_t* result = Utils::StringToConstWchar_TPointer(stringItemToAdd);

		int itemPosAddExemplary = SendMessage(hCbSelectedBookAddExemplary, CB_ADDSTRING, NULL, (LPARAM)result);
		int itemPosListExemplaries = SendMessage(hCbSelectedBookListExemplaries, CB_ADDSTRING, NULL, (LPARAM)result);

		// Set the array index of the player as item data.
		// This enables us to retrieve the item from the array
		// even after the items are sorted by the combo box.
		SendMessage(hCbSelectedBookAddExemplary, CB_SETITEMDATA, itemPosAddExemplary, (LPARAM)book->modelID);
		SendMessage(hCbSelectedBookListExemplaries, CB_SETITEMDATA, itemPosListExemplaries, (LPARAM)book->modelID);
	}

	SendMessage(hCbSelectedBookAddExemplary, CB_SETCURSEL, (WPARAM)0, NULL);
	SendMessage(hCbSelectedBookListExemplaries, CB_SETCURSEL, (WPARAM)0, NULL);
}

void AdminExemplariesWindowController::UpdateItemSelectionOnList(HWND hDlg)
{
}

INT_PTR AdminExemplariesWindowController::HandleWindow(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		AdminExemplariesWindowController::GetInstance()->InitializeWindowHandlersIfNeeded(hDlg);
		//UpdateListBoxInfo(hDlg);
		return (INT_PTR)TRUE;
	case WM_COMMAND:
		AdminExemplariesWindowController::GetInstance()->HandleWindowCommand(hDlg, message, wParam, lParam);
		break;
	case WM_PAINT:
		AdminExemplariesWindowController::GetInstance()->HandlePaintCommand(hDlg, message, wParam, lParam);
		break;
	}
	return (INT_PTR)FALSE;
}
