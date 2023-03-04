#include "LoanHistoryWindowController.h"

#include <stdio.h>
#include <string>
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
#include <ctime>
#include <cstring>
#include <cassert>
#include <iostream>


LoanHistoryWindowController::LoanHistoryWindowController() {}
LoanHistoryWindowController::~LoanHistoryWindowController() {}
LoanHistoryWindowController* LoanHistoryWindowController::singleton_ = nullptr;

LoanHistoryWindowController* LoanHistoryWindowController::GetInstance()
{
	/**
	 * This is a safer way to create an instance. instance = new Singleton is
	 * dangeruous in case two instance threads wants to access at the same time
	 */
	if (singleton_ == nullptr) {
		singleton_ = new LoanHistoryWindowController();
	}
	return singleton_;
}

void LoanHistoryWindowController::InitializeWindowHandlersIfNeeded(HWND hDlg)
{
	if (!LoanHistoryWindowController::GetInstance()->handlersInitialized)
	{
		LoanHistoryWindowController::GetInstance()->handlersInitialized = true;
	}
	UpdateListBoxInfo(hDlg);
}

void LoanHistoryWindowController::HandleWindowCommand(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
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
		case LB_LOANSHISTORY:
		{
			if (HIWORD(wParam) == LBN_SELCHANGE)
			{
				UpdateItemInfoOfLoanSelectedOnList(hDlg);
			}
		}
		}
	}
	}
}

void LoanHistoryWindowController::HandlePaintCommand(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
}


bool LoanHistoryWindowController::PerformChecks(HWND hDlg)
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

bool LoanHistoryWindowController::PerformItemCheck(HWND hDlg, int dlgID)
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
	}
	}
	return thereIsAError;
}

void LoanHistoryWindowController::UpdateListBoxInfo(HWND hDlg)
{

	HWND hLbListLoans = GetDlgItem(hDlg, LB_LOANSHISTORY);
	SendMessage(hLbListLoans, LB_RESETCONTENT, NULL, NULL);

	// Then fill the list box
	for (const Loan* loan : DbContextLibrary::GetInstance()->loanTable.GetAllItems())
	{
		// From strting to wchar_t
		std::string stringItemToAdd =
			"Fecha:  " + *Utils::WCharToString_TPointer(Utils::Time_tToWChar_tPointer(loan->loanDate)) +
			",    Tipo:  " + (loan->type == LoanType::Withdrawal ? "Prestamo" : "Devolución") +
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

void LoanHistoryWindowController::UpdateItemInfoOfLoanSelectedOnList(HWND hDlg)
{
	HWND hwndList = GetDlgItem(hDlg, LB_LOANSHISTORY);
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
	SetDlgItemText(hDlg, LBL_LOANHISTORYINFO_BOOKNAME, Utils::StringToConstWchar_TPointer(bookOfLoanSelected->name));
	SetDlgItemText(hDlg, LBL_LOANHISTORYINFO_BOOKAUTHOR, Utils::StringToConstWchar_TPointer(bookOfLoanSelected->autor));
	SetDlgItemText(hDlg, LBL_LOANHISTORYINFO_BOOKISBN, Utils::StringToConstWchar_TPointer(bookOfLoanSelected->ISBNcode));

	SetDlgItemText(hDlg, LBL_LOANHISTORYINFO_EXEMPLARYEDITION, Utils::StringToConstWchar_TPointer(std::to_string(exemplaryOfLoanSelected->editionNumber)));
	SetDlgItemText(hDlg, LBL_LOANHISTORYINFO_EXEMPLARYUBICATION, Utils::StringToConstWchar_TPointer(exemplaryOfLoanSelected->libraryUbication));

	SetDlgItemText(hDlg, LBL_LOANHISTORYINFO_PARTNERNAME, Utils::StringToConstWchar_TPointer(partnerOfLoanSelected->name));
	SetDlgItemText(hDlg, LBL_LOANHISTORYINFO_PARTNERLASTNAME, Utils::StringToConstWchar_TPointer(partnerOfLoanSelected->lastName));
	SetDlgItemText(hDlg, LBL_LOANHISTORYINFO_PARTNERID, Utils::StringToConstWchar_TPointer(partnerOfLoanSelected->idNumber));

	SetDlgItemText(hDlg, LBL_LOANHISTORYINFO_DATE, Utils::Time_tToWChar_tPointer(loanSelected->loanDate));
	SetDlgItemText(hDlg, LBL_LOANHISTORYINFO_TYPE, (loanSelected->type == LoanType::Withdrawal ? L"Prestamo" : L"Devolución"));
}

INT_PTR LoanHistoryWindowController::HandleWindow(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		LoanHistoryWindowController::GetInstance()->InitializeWindowHandlersIfNeeded(hDlg);
		//UpdateListBoxInfo(hDlg);
		return (INT_PTR)TRUE;
	case WM_COMMAND:
		LoanHistoryWindowController::GetInstance()->HandleWindowCommand(hDlg, message, wParam, lParam);
		break;
	case WM_PAINT:
		LoanHistoryWindowController::GetInstance()->HandlePaintCommand(hDlg, message, wParam, lParam);
		break;
	}
	return (INT_PTR)FALSE;
}