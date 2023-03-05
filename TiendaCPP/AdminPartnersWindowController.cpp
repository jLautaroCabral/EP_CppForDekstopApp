#include "AdminPartnersWindowController.h"
#include "resource.h"
#include "framework.h"
#include <stdio.h>
#include <string>
#include "DbContextLibrary.h"
#include "PartnerFactory.h"
#include "Partner.h"
#include "PartnerVIP.h"
#include "Utils.h"
#include "UtilsUI.h"

AdminPartnersWindowController::AdminPartnersWindowController() {}
AdminPartnersWindowController::~AdminPartnersWindowController() {}
AdminPartnersWindowController* AdminPartnersWindowController::singleton_ = nullptr;

AdminPartnersWindowController* AdminPartnersWindowController::GetInstance()
{
	/**
	 * This is a safer way to create an instance. instance = new Singleton is
	 * dangeruous in case two instance threads wants to access at the same time
	 */
	if (singleton_ == nullptr) {
		singleton_ = new AdminPartnersWindowController();
	}
	return singleton_;
}

void AdminPartnersWindowController::InitializeWindowHandlersIfNeeded(HWND hDlg)
{
	if (!AdminPartnersWindowController::GetInstance()->handlersInitialized)
	{
		AdminPartnersWindowController::GetInstance()->handlersInitialized = true;
	}

	UpdateListBoxInfo(hDlg);
}

void AdminPartnersWindowController::HandleWindowCommand(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
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
		case BTN_ADDPARTNER_ADD:
		{
			if (hWord == BN_CLICKED)
			{
				if (!PerformChecks(hDlg)) break;

				HWND hLbPartners = GetDlgItem(hDlg, LB_PARTNERS);

				std::string partnerName;
				std::string partnerLastName;

				if (!UtilsUI::TryGetStringFromInputField(hDlg, INPF_ADDPARTNER_PARTNERNAME, "Nombre", partnerName)) break;
				if (!UtilsUI::TryGetStringFromInputField(hDlg, INPF_ADDPARTNER_PARTNERLASTNAME, "Apellido", partnerLastName)) break;
				//if (!UtilsUI::TryGetStringFromInputField(hDlg, INPF_ADDBOOK_ISBNCODE, "Codigo ISNB", bookISBNCode)) break;

				Partner* newPartner = nullptr;

				if (IsDlgButtonChecked(hDlg, RBTN_PARTNERTYPE_COMMON) == BST_CHECKED)
				{
					newPartner = PartnerFactory::CreatePartner(partnerName, partnerLastName);
				}
				else
				{
					newPartner = PartnerFactory::CreatePartnerVIP(partnerName, partnerLastName);
				}

				DbContextLibrary::GetInstance()->partnerTable.Add(newPartner);
				UpdateListBoxInfo(hDlg);
			}
		}
		case BTN_PARTNERINFO_REMOVE:
		{
			if (hWord == BN_CLICKED)
			{
				// TODO: Update models to support remove
				/*
				HWND hwndList = GetDlgItem(hDlg, LB_BOOKS);
				// Get selected index.
				int selectedItem = (int)SendMessage(hwndList, LB_GETCURSEL, NULL, NULL);
				// Get item data.
				int modelIdOfSelectedItem = (int)SendMessage(hwndList, LB_GETITEMDATA, selectedItem, NULL);

				DbContextLibrary::GetInstance()->bookTable.Remove(modelIdOfSelectedItem);
				UpdateListBoxInfo(hDlg);
				SendMessage(hwndList, LB_SETCURSEL, (WPARAM)0, NULL);
				UpdateItemSelectionOnList(hDlg);
				*/
			}
		}
		case LB_PARTNERS:
		{
			if (HIWORD(wParam) == LBN_SELCHANGE)
			{
				UpdateItemSelectionOnList(hDlg);
			}
		}
		}
	}
	}
}

void AdminPartnersWindowController::HandlePaintCommand(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
}

bool AdminPartnersWindowController::PerformChecks(HWND hDlg)
{
	int dlgItemsIDsToCheck[] =
	{
		INPF_ADDPARTNER_PARTNERNAME,
		INPF_ADDPARTNER_PARTNERLASTNAME,
		RBTN_PARTNERTYPE_COMMON,
		RBTN_PARTNERTYPE_VIP
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

bool AdminPartnersWindowController::PerformItemCheck(HWND hDlg, int dlgID)
{
	bool thereIsAError = false;
	int iTextLength;
	HWND hInpf;

	switch (dlgID)
	{
	case INPF_ADDPARTNER_PARTNERNAME:
	{
		hInpf = GetDlgItem(hDlg, INPF_ADDPARTNER_PARTNERNAME);
		iTextLength = GetWindowTextLength(hInpf);
		if (iTextLength == 0)
		{
			thereIsAError = true;
			MessageBox(NULL, L"Es necesario ingresar un valor en el campo 'Nombre'", L"Error", MB_ICONERROR);
		}
	}
	case INPF_ADDPARTNER_PARTNERLASTNAME:
	{
		hInpf = GetDlgItem(hDlg, INPF_ADDPARTNER_PARTNERLASTNAME);
		iTextLength = GetWindowTextLength(hInpf);
		if (iTextLength == 0)
		{
			thereIsAError = true;
			MessageBox(NULL, L"Es necesario ingresar un valor en el campo 'Apellido'", L"Error", MB_ICONERROR);
		}
	}
	case RBTN_PARTNERTYPE_COMMON:
	case RBTN_PARTNERTYPE_VIP:
	{
		if (IsDlgButtonChecked(hDlg, RBTN_PARTNERTYPE_COMMON) == BST_UNCHECKED &&
			IsDlgButtonChecked(hDlg, RBTN_PARTNERTYPE_VIP) == BST_UNCHECKED)
		{
			thereIsAError = true;
			MessageBox(NULL, L"Es necesario seleccionar un tipo de socio (Socio común o Socio VIP)", L"Error", MB_ICONERROR);
		}
		break;
	}
	}
	return thereIsAError;
}

void AdminPartnersWindowController::UpdateListBoxInfo(HWND hDlg)
{
	HWND hLbPartners = GetDlgItem(hDlg, LB_PARTNERS);
	SendMessage(hLbPartners, LB_RESETCONTENT, NULL, NULL);

	// Then fill the list box
	for (const Partner* book : DbContextLibrary::GetInstance()->partnerTable.GetAllItems())
	{
		// From strting to wchar_t
		std::string stringItemToAdd = "" + book->name + ",   " + book->lastName;
		int itemPos = SendMessage(hLbPartners, LB_ADDSTRING, NULL,
			(LPARAM)Utils::StringToConstWchar_TPointer(stringItemToAdd));

		// Set the array index of the player as item data.
		// This enables us to retrieve the item from the array
		// even after the items are sorted by the list box.
		SendMessage(hLbPartners, LB_SETITEMDATA, itemPos, (LPARAM)book->modelID);
	}
	// Set input focus to the list box.
	SetFocus(hLbPartners);
}

void AdminPartnersWindowController::UpdateItemSelectionOnList(HWND hDlg)
{
	HWND hwndList = GetDlgItem(hDlg, LB_PARTNERS);
	// Get selected index.
	int selectedItem = (int)SendMessage(hwndList, LB_GETCURSEL, NULL, NULL);
	// Get item data.
	int modelIdOfSelectedItem = (int)SendMessage(hwndList, LB_GETITEMDATA, selectedItem, NULL);
	// Get partner from DbContext
	Partner* partnerSelected = DbContextLibrary::GetInstance()->partnerTable.GetElementByID(modelIdOfSelectedItem);

	// Fill labels
	SetDlgItemText(hDlg, LBL_PARTNERINFO_NAME, Utils::StringToConstWchar_TPointer(partnerSelected->name));
	SetDlgItemText(hDlg, LBL_PARTNERINFO_LASTNAME, Utils::StringToConstWchar_TPointer(partnerSelected->lastName));
	SetDlgItemText(hDlg, LBL_PARTNERINFO_PARTNERID, Utils::StringToConstWchar_TPointer(partnerSelected->idNumber));
	
	if (Partner::IsPartnerVIP(partnerSelected))
	{
		SetDlgItemText(hDlg, LBL_PARTNERINFO_PARTNERTYPE, L"VIP");
	}
	else
	{
		SetDlgItemText(hDlg, LBL_PARTNERINFO_PARTNERTYPE, L"Común");
	}

	SetDlgItemText(hDlg, LBL_PARTNERINFO_AMOUNT, Utils::StringToConstWchar_TPointer(std::to_string(std::size(partnerSelected->loanedExemplaries))));
	//SetDlgItemText(hDlg, LBL_PARTNERINFO_AMOUNT, Utils::StringToConstWchar_TPointer(std::to_string(std::size(partnerSelected->exemplaries))));
}

INT_PTR AdminPartnersWindowController::HandleWindow(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		AdminPartnersWindowController::GetInstance()->InitializeWindowHandlersIfNeeded(hDlg);
		return (INT_PTR)TRUE;
	case WM_COMMAND:
		AdminPartnersWindowController::GetInstance()->HandleWindowCommand(hDlg, message, wParam, lParam);
		break;
	case WM_PAINT:
		AdminPartnersWindowController::GetInstance()->HandlePaintCommand(hDlg, message, wParam, lParam);
		break;
	}
	return (INT_PTR)FALSE;
}
