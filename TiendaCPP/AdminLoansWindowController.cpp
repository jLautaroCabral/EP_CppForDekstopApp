#include <stdio.h>
#include <string>
#include <ctime>
#include <cstring>
#include <cassert>
#include <iostream>
#include "AdminLoansWindowController.h"
#include "AdminExemplariesWindowController.h"
#include "resource.h"
#include "framework.h"
#include "DbContextLibrary.h"
#include "BookFactory.h"
#include "LoanFactory.h"
#include "ExemplaryFactory.h"
#include "Utils.h"
#include "UtilsUI.h"


AdminLoansWindowController::AdminLoansWindowController() {}
AdminLoansWindowController::~AdminLoansWindowController() {}
AdminLoansWindowController* AdminLoansWindowController::singleton_ = nullptr;

AdminLoansWindowController* AdminLoansWindowController::GetInstance()
{
	/**
	 * This is a safer way to create an instance. instance = new Singleton is
	 * dangeruous in case two instance threads wants to access at the same time
	 */
	if (singleton_ == nullptr) {
		singleton_ = new AdminLoansWindowController();
	}
	return singleton_;
}


void AdminLoansWindowController::InitializeWindowHandlersIfNeeded(HWND hDlg)
{
	if (!AdminLoansWindowController::GetInstance()->handlersInitialized)
	{
		AdminLoansWindowController::GetInstance()->handlersInitialized = true;
	}

	UpdatePartnerComboBox(hDlg);
	UpdateBookComboBox(hDlg);
	UpdateExemplaryComboBox(hDlg);
	UpdateListBoxInfo(hDlg);
	UpdateItemInfoOfPartnerSelectedOnComboBox(hDlg);
}

void AdminLoansWindowController::HandleWindowCommand(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
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
		case BTN_ADDLOAN_ADD:
		{
			if (hWord == BN_CLICKED)
			{
				if(!PerformChecks(hDlg)) return;

				HWND hCbSelectPartnerAddLoan = GetDlgItem(hDlg, CB_ADDLOAN_PARTNER);
				HWND hCbSelectExemplaryAddLoan = GetDlgItem(hDlg, CB_ADDLOAN_EXEMPLARY);
				HWND hwndList = GetDlgItem(hDlg, LB_LOANS);

				Partner* selectedPartner;
				Exemplary* selectedExemplary;

				int selectedItem = 0;
				int modelIdOfSelectedItem = 0;

				// Get partner
				selectedItem = (int)SendMessage(hCbSelectPartnerAddLoan, CB_GETCURSEL, NULL, NULL);
				modelIdOfSelectedItem = (int)SendMessage(hCbSelectPartnerAddLoan, CB_GETITEMDATA, selectedItem, NULL);
				selectedPartner = DbContextLibrary::GetInstance()->partnerTable.GetElementByID(modelIdOfSelectedItem);
				
				// Get exemplary
				selectedItem = (int)SendMessage(hCbSelectExemplaryAddLoan, CB_GETCURSEL, NULL, NULL);
				modelIdOfSelectedItem = (int)SendMessage(hCbSelectExemplaryAddLoan, CB_GETITEMDATA, selectedItem, NULL);
				selectedExemplary = DbContextLibrary::GetInstance()->exemplaryTable.GetElementByID(modelIdOfSelectedItem);

				Book* bookOfExemplary = DbContextLibrary::GetInstance()->bookTable.GetElementByID(selectedExemplary->bookID);

				selectedExemplary = bookOfExemplary->LoanExemplary(selectedExemplary);
				selectedPartner->LoanExemplary(selectedExemplary);

				DbContextLibrary::GetInstance()->loanTable.Add(LoanFactory::CreateLoan(selectedPartner, selectedExemplary, LoanType::Withdrawal));
				DbContextLibrary::GetInstance()->loanHistoryTable.Add(LoanFactory::CreateLoan(selectedPartner, selectedExemplary, LoanType::Withdrawal));
				
				UpdateListBoxInfo(hDlg);
				UpdateExemplaryComboBox(hDlg);
			}
			break;
		}
		case BTN_LOANINFO_REMOVE:
		{
			if (hWord == BN_CLICKED)
			{
				HWND hwndList = GetDlgItem(hDlg, LB_LOANS);
				Loan* loanReturn;

				int selectedItem = 0;
				int modelIdOfSelectedItem = 0;

				// Get loan
				selectedItem = (int)SendMessage(hwndList, LB_GETCURSEL, NULL, NULL);
				modelIdOfSelectedItem = (int)SendMessage(hwndList, LB_GETITEMDATA, selectedItem, NULL);
				loanReturn = DbContextLibrary::GetInstance()->loanTable.GetElementByID(modelIdOfSelectedItem);

				Partner* selectedPartner = loanReturn->partner;
				Exemplary* selectedExemplary = loanReturn->exemplary;

				Book* bookOfExemplary = DbContextLibrary::GetInstance()->bookTable.GetElementByID(selectedExemplary->bookID);

				selectedExemplary = selectedPartner->ReturnExemplary(selectedExemplary);
				bookOfExemplary->RegisterReturnOfExemplary(selectedExemplary);

				DbContextLibrary::GetInstance()->loanTable.Remove(loanReturn->modelID);
				DbContextLibrary::GetInstance()->loanHistoryTable.Add(LoanFactory::CreateLoan(selectedPartner, selectedExemplary, LoanType::Return));

				UpdateListBoxInfo(hDlg);
				UpdateExemplaryComboBox(hDlg);
				SendMessage(hwndList, LB_SETCURSEL, (WPARAM)0, NULL);
				UpdateItemInfoOfLoanSelectedOnList(hDlg);
			}
			break;
		}
		case LB_LOANS:
		{
			if (HIWORD(wParam) == LBN_SELCHANGE)
			{
				UpdateItemInfoOfLoanSelectedOnList(hDlg);
			}
		}
		case CB_ADDLOAN_BOOK:
		{
			if (hWord == CBN_SELENDOK)
			{
				//UpdateItemSelectionOnList(hDlg);
				UpdateExemplaryComboBox(hDlg);
			}
		}
		case CB_ADDLOAN_PARTNER:
		{
			if (hWord == CBN_SELENDOK)
			{
				UpdateItemInfoOfPartnerSelectedOnComboBox(hDlg);
			}
		}
		}
	}
	}
}

void AdminLoansWindowController::HandlePaintCommand(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
}


bool AdminLoansWindowController::PerformChecks(HWND hDlg)
{
	int dlgItemsIDsToCheck[] =
	{
		CB_ADDLOAN_PARTNER
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

bool AdminLoansWindowController::PerformItemCheck(HWND hDlg, int dlgID)
{
	bool thereIsAError = false;
	int iTextLength;
	HWND hComboBx;

	switch (dlgID)
	{
		case CB_ADDLOAN_PARTNER:
		{
			hComboBx = GetDlgItem(hDlg, CB_ADDLOAN_PARTNER);

			Partner* selectedPartner;

			int selectedItem = 0;
			int modelIdOfSelectedItem = 0;

			// Get partner
			selectedItem = (int)SendMessage(hComboBx, CB_GETCURSEL, NULL, NULL);
			modelIdOfSelectedItem = (int)SendMessage(hComboBx, CB_GETITEMDATA, selectedItem, NULL);
			selectedPartner = DbContextLibrary::GetInstance()->partnerTable.GetElementByID(modelIdOfSelectedItem);

			if (!selectedPartner->CanApplyForALoan())
			{
				thereIsAError = true;
				MessageBox(NULL, L"Este socio ha llegado a su cantidad máxima de prestamos activos'", L"Error", MB_ICONERROR);
			}
		}
	}
	return thereIsAError;
}

void AdminLoansWindowController::UpdateListBoxInfo(HWND hDlg)
{
	
	HWND hLbListLoans = GetDlgItem(hDlg, LB_LOANS);
	SendMessage(hLbListLoans, LB_RESETCONTENT, NULL, NULL);

	// Then fill the list box
	for (const Loan* loan : DbContextLibrary::GetInstance()->loanTable.GetAllItems())
	{
		// From strting to wchar_t
		std::string stringItemToAdd =
			"Fecha:  " + *Utils::WCharToString_TPointer(Utils::Time_tToWChar_tPointer(loan->loanDate)) +
			",    Socio:  " + loan->partner->name + " " + loan->partner->lastName +
			",    Libro:  " + DbContextLibrary::GetInstance()->bookTable.GetElementByID(loan->exemplary->bookID)->name +
			",    Edicion:  " + std::to_string(loan->exemplary->editionNumber);

		int itemPos = SendMessage(hLbListLoans, LB_ADDSTRING, NULL,
			(LPARAM)Utils::StringToConstWchar_TPointer(stringItemToAdd));

		// Set the array index of the player as item data.
		// This enables us to retrieve the item from the array
		// even after the items are sorted by the list box.
		SendMessage(hLbListLoans, LB_SETITEMDATA, itemPos, (LPARAM)loan->modelID);
	}
	
}

void AdminLoansWindowController::UpdatePartnerComboBox(HWND hDlg)
{
	HWND hCbSelectPartnerAddLoan = GetDlgItem(hDlg, CB_ADDLOAN_PARTNER);

	//SendMessage(hCbSelectedBookAddExemplary, CB_RESETCONTENT, NULL, NULL);
	SendMessage(hCbSelectPartnerAddLoan, CB_RESETCONTENT, NULL, NULL);

	// Then fill the list box
	for (const Partner* partner : DbContextLibrary::GetInstance()->partnerTable.GetAllItems())
	{
		// From strting to wchar_t
		std::string stringItemToAdd = "" + partner->name + ",   " + partner->lastName;
		const wchar_t* result = Utils::StringToConstWchar_TPointer(stringItemToAdd);
		int itemPosListExemplaries = SendMessage(hCbSelectPartnerAddLoan, CB_ADDSTRING, NULL, (LPARAM)result);

		// Set the array index of the player as item data.
		// This enables us to retrieve the item from the array
		// even after the items are sorted by the combo box.
		SendMessage(hCbSelectPartnerAddLoan, CB_SETITEMDATA, itemPosListExemplaries, (LPARAM)partner->modelID);
	}
	SendMessage(hCbSelectPartnerAddLoan, CB_SETCURSEL, (WPARAM)0, NULL);
}

void AdminLoansWindowController::UpdateBookComboBox(HWND hDlg)
{
	HWND hCbSelectBookAddLoan = GetDlgItem(hDlg, CB_ADDLOAN_BOOK);

	//SendMessage(hCbSelectedBookAddExemplary, CB_RESETCONTENT, NULL, NULL);
	SendMessage(hCbSelectBookAddLoan, CB_RESETCONTENT, NULL, NULL);

	// Then fill the list box
	for (const Book* book : DbContextLibrary::GetInstance()->bookTable.GetAllItems())
	{
		// From strting to wchar_t
		std::string stringItemToAdd = "" + book->name + ",   " + book->autor;
		const wchar_t* result = Utils::StringToConstWchar_TPointer(stringItemToAdd);
		int itemPosListExemplaries = SendMessage(hCbSelectBookAddLoan, CB_ADDSTRING, NULL, (LPARAM)result);

		// Set the array index of the player as item data.
		// This enables us to retrieve the item from the array
		// even after the items are sorted by the combo box.
		SendMessage(hCbSelectBookAddLoan, CB_SETITEMDATA, itemPosListExemplaries, (LPARAM)book->modelID);
	}
	SendMessage(hCbSelectBookAddLoan, CB_SETCURSEL, (WPARAM)0, NULL);
}

void AdminLoansWindowController::UpdateExemplaryComboBox(HWND hDlg)
{
	HWND hCbSelectBookAddLoan = GetDlgItem(hDlg, CB_ADDLOAN_BOOK);
	HWND hCbSelectExemplaryAddLoan = GetDlgItem(hDlg, CB_ADDLOAN_EXEMPLARY);

	SendMessage(hCbSelectExemplaryAddLoan, CB_RESETCONTENT, NULL, NULL);

	// Get selected index.
	int selectedItem = (int)SendMessage(hCbSelectBookAddLoan, CB_GETCURSEL, NULL, NULL);
	// Get item data.
	int modelIdOfSelectedItem = (int)SendMessage(hCbSelectBookAddLoan, CB_GETITEMDATA, selectedItem, NULL);

	const Book* book = DbContextLibrary::GetInstance()->bookTable.GetElementByID(modelIdOfSelectedItem);

	if (book->exemplaries.empty())
	{
		SendMessage(hCbSelectExemplaryAddLoan, CB_ADDSTRING, NULL,
			(LPARAM)L"Actualmente no existen ejemplares de este libro...");
	}
	else
	{
		// Then fill the list box
		for (const Exemplary* exemplary : book->exemplaries)
		{
			// From strting to wchar_t
			std::string stringItemToAdd =
				"Edition number:  " + std::to_string(exemplary->editionNumber) +
				",   Ubication:  " + exemplary->libraryUbication;

			int itemPos = SendMessage(hCbSelectExemplaryAddLoan, CB_ADDSTRING, NULL,
				(LPARAM)Utils::StringToConstWchar_TPointer(stringItemToAdd));

			// Set the array index of the player as item data.
			// This enables us to retrieve the item from the array
			// even after the items are sorted by the list box.
			SendMessage(hCbSelectExemplaryAddLoan, CB_SETITEMDATA, itemPos, (LPARAM)exemplary->modelID);
		}
	}
	SendMessage(hCbSelectExemplaryAddLoan, CB_SETCURSEL, (WPARAM)0, NULL);
}

void AdminLoansWindowController::UpdateItemInfoOfLoanSelectedOnList(HWND hDlg)
{
	HWND hwndList = GetDlgItem(hDlg, LB_LOANS);
	// Get selected index.
	int selectedItem = (int)SendMessage(hwndList, LB_GETCURSEL, NULL, NULL);
	// Get item data.
	int modelIdOfSelectedItem = (int)SendMessage(hwndList, LB_GETITEMDATA, selectedItem, NULL);
	// Get data from DbContext
	Loan* loanSelected = DbContextLibrary::GetInstance()->loanTable.GetElementByID(modelIdOfSelectedItem);
	Exemplary* exemplaryOfLoanSelected = loanSelected->exemplary;
	Book* bookOfLoanSelected = DbContextLibrary::GetInstance()->bookTable.GetElementByID(exemplaryOfLoanSelected->bookID);
	Partner* partnerOfLoanSelected = loanSelected->partner;

	// Fill labels
	SetDlgItemText(hDlg, LBL_LOANINFO_BOOKNAME, Utils::StringToConstWchar_TPointer(bookOfLoanSelected->name));
	SetDlgItemText(hDlg, LBL_LOANINFO_BOOKAUTHOR, Utils::StringToConstWchar_TPointer(bookOfLoanSelected->autor));
	SetDlgItemText(hDlg, LBL_LOANINFO_BOOKISBN, Utils::StringToConstWchar_TPointer(bookOfLoanSelected->ISBNcode));

	SetDlgItemText(hDlg, LBL_LOANINFO_EXEMPLARYEDITION, Utils::StringToConstWchar_TPointer(std::to_string(exemplaryOfLoanSelected->editionNumber)));
	SetDlgItemText(hDlg, LBL_LOANINFO_EXEMPLARYUBICATION, Utils::StringToConstWchar_TPointer(exemplaryOfLoanSelected->libraryUbication));

	SetDlgItemText(hDlg, LBL_LOANINFO_PARTNERNAME, Utils::StringToConstWchar_TPointer(partnerOfLoanSelected->name));
	SetDlgItemText(hDlg, LBL_LOANINFO_PARTNERLASTNAME, Utils::StringToConstWchar_TPointer(partnerOfLoanSelected->lastName));
	SetDlgItemText(hDlg, LBL_LOANINFO_PARTNERID, Utils::StringToConstWchar_TPointer(partnerOfLoanSelected->idNumber));

	SetDlgItemText(hDlg, LBL_LOANINFO_DATE, Utils::Time_tToWChar_tPointer(loanSelected->loanDate));
}

void AdminLoansWindowController::UpdateItemInfoOfPartnerSelectedOnComboBox(HWND hDlg)
{
	HWND hCbSelectPartnerAddLoan = GetDlgItem(hDlg, CB_ADDLOAN_PARTNER);

	// Get selected index.
	int selectedItem = (int)SendMessage(hCbSelectPartnerAddLoan, CB_GETCURSEL, NULL, NULL);
	// Get item data.
	int modelIdOfSelectedItem = (int)SendMessage(hCbSelectPartnerAddLoan, CB_GETITEMDATA, selectedItem, NULL);

	Partner* partner = DbContextLibrary::GetInstance()->partnerTable.GetElementByID(modelIdOfSelectedItem);

	// Fill labels
	SetDlgItemText(hDlg, LBL_ADDLOAN_PARTNERTYPE, Partner::IsPartnerVIP(partner) ? L"VIP" : L"Común");
	SetDlgItemText(hDlg, LBL_ADDLOAN_PARTNERLOANAMOUNT, Utils::StringToConstWchar_TPointer(std::to_string(std::size(partner->loanedExemplaries))));
	SetDlgItemText(hDlg, LBL_ADDLOAN_PARTNERLOANMAXAMOUNT, Utils::StringToConstWchar_TPointer(std::to_string(partner->maxWithdrawalAmount)));
}

INT_PTR AdminLoansWindowController::HandleWindow(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		AdminLoansWindowController::GetInstance()->InitializeWindowHandlersIfNeeded(hDlg);
		//UpdateListBoxInfo(hDlg);
		return (INT_PTR)TRUE;
	case WM_COMMAND:
		AdminLoansWindowController::GetInstance()->HandleWindowCommand(hDlg, message, wParam, lParam);
		break;
	case WM_PAINT:
		AdminLoansWindowController::GetInstance()->HandlePaintCommand(hDlg, message, wParam, lParam);
		break;
	}
	return (INT_PTR)FALSE;
}
