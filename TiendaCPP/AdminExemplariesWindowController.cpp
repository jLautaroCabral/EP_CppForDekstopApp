#include "AdminExemplariesWindowController.h"
#include "resource.h"
#include "framework.h"
#include <stdio.h>
#include <string>
#include "DbContextLibrary.h"
#include "BookFactory.h"
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
		case BTN_ADD_BOOK:
		{
			if (hWord == BN_CLICKED)
			{
				HWND hLbBooks = GetDlgItem(hDlg, LB_BOOKS);

				std::string bookName;
				std::string bookAuthorName;
				std::string bookISBNCode;

				if (!UtilsUI::TryGetStringFromInputField(hDlg, INPF_BOOK_NAME, "Nombre del libro", bookName)) break;
				if (!UtilsUI::TryGetStringFromInputField(hDlg, INPF_ADDBOOK_AUTHORNAME, "Nombre del autor del libro", bookAuthorName)) break;
				if (!UtilsUI::TryGetStringFromInputField(hDlg, INPF_ADDBOOK_ISBNCODE, "Codigo ISNB", bookISBNCode)) break;

				if (!PerformChecks(hDlg)) break;

				Book* newBook = BookFactory::CreateBook(bookName, bookAuthorName, bookISBNCode);
				DbContextLibrary::GetInstance()->bookTable.Add(newBook);

				UpdateListBoxInfo(hDlg);
			}
		}
		case BTN_REMOVE_BOOK:
		{
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
    return false;
}

bool AdminExemplariesWindowController::PerformItemCheck(HWND hDlg, int dlgID)
{
    return false;
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

	/*
	// First delete all previous elements
	int itemCount = SendMessage(hLbBooks, LB_GETCOUNT, NULL, NULL);
	for (int i = 0; i < itemCount; i++)
	{
		int itemCount = SendMessage(hLbBooks, LB_DELETESTRING, HIWORD(i), NULL);
	}
	*/

	// Then fill the list box
	for (const Book* book : DbContextLibrary::GetInstance()->bookTable.GetAllItems())
	{
		// From strting to wchar_t
		std::string stringItemToAdd = "" + book->name + ",   " + book->autor;
		const wchar_t* result = Utils::StringToConstWchar_TPointer(stringItemToAdd);

		//int itemPos = SendMessage(hLbBooks, LB_ADDSTRING, NULL, (LPARAM)result);
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
