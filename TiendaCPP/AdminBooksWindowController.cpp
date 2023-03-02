#include "AdminBooksWindowController.h"
#include "resource.h"
#include "framework.h"
#include <stdio.h>
#include <string>
#include "DbContextLibrary.h"
#include "BookFactory.h"
#include "Utils.h"
#include "UtilsUI.h"

AdminBooksWindowController::AdminBooksWindowController() {}
AdminBooksWindowController::~AdminBooksWindowController() {}
AdminBooksWindowController* AdminBooksWindowController::singleton_ = nullptr;

AdminBooksWindowController* AdminBooksWindowController::GetInstance()
{
	/**
	 * This is a safer way to create an instance. instance = new Singleton is
	 * dangeruous in case two instance threads wants to access at the same time
	 */
	if (singleton_ == nullptr) {
		singleton_ = new AdminBooksWindowController();
	}
	return singleton_;
}

void AdminBooksWindowController::InitializeWindowHandlersIfNeeded(HWND hDlg)
{
	if (!AdminBooksWindowController::GetInstance()->handlersInitialized)
	{
		AdminBooksWindowController::GetInstance()->handlersInitialized = true;
	}
}

void AdminBooksWindowController::UpdateListBoxInfo(HWND hDlg)
{
	HWND hLbBooks = GetDlgItem(hDlg, LB_BOOKS);

	/*
	// First delete all previous elements
	int itemCount = SendMessage(hLbBooks, LB_GETCOUNT, NULL, NULL);
	for (int i = 0; i < itemCount; i++)
	{
		//int itemCount = SendMessage(hLbBooks, LB_DELETESTRING, HIWORD(i), NULL);
	}
	*/
	SendMessage(hLbBooks, LB_RESETCONTENT, NULL, NULL);

	// Then fill the list box
	for (const Book* book : DbContextLibrary::GetInstance()->bookTable.GetAllItems())
	{
		// From strting to wchar_t
		std::string stringItemToAdd = "" + book->name + ",   " + book->autor;
		int itemPos = SendMessage(hLbBooks, LB_ADDSTRING, NULL,
			(LPARAM)Utils::StringToConstWchar_TPointer(stringItemToAdd));

		// Set the array index of the player as item data.
		// This enables us to retrieve the item from the array
		// even after the items are sorted by the list box.
		SendMessage(hLbBooks, LB_SETITEMDATA, itemPos, (LPARAM)book->modelID);
	}
	// Set input focus to the list box.
	SetFocus(hLbBooks);
}


void AdminBooksWindowController::UpdateItemSelectionOnList(HWND hDlg)
{
	HWND hwndList = GetDlgItem(hDlg, LB_BOOKS);
	// Get selected index.
	int selectedItem = (int)SendMessage(hwndList, LB_GETCURSEL, NULL, NULL);
	// Get item data.
	int modelIdOfSelectedItem = (int)SendMessage(hwndList, LB_GETITEMDATA, selectedItem, NULL);
	// Get book from DbContext
	Book* bookSelected = DbContextLibrary::GetInstance()->bookTable.GetElementByID(modelIdOfSelectedItem);

	// Fill labels
	SetDlgItemText(hDlg, LBL_BOOKINFO_NAME, Utils::StringToConstWchar_TPointer(bookSelected->name));
	SetDlgItemText(hDlg, LBL_BOOKINFO_AUTHOR, Utils::StringToConstWchar_TPointer(bookSelected->autor));
	SetDlgItemText(hDlg, LBL_BOOKINFO_ISBNCODE, Utils::StringToConstWchar_TPointer(bookSelected->ISBNcode));
	SetDlgItemText(hDlg, LBL_BOOKINFO_EXEMPLARIESAMOUNT, Utils::StringToConstWchar_TPointer(std::to_string(std::size(bookSelected->exemplaries))));
}


void AdminBooksWindowController::HandleWindowCommand(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	AdminBooksWindowController::GetInstance()->InitializeWindowHandlersIfNeeded(hDlg);

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
			}
		}
	}
}

void AdminBooksWindowController::HandlePaintCommand(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
}

INT_PTR AdminBooksWindowController::HandleWindow(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		UpdateListBoxInfo(hDlg);
		return (INT_PTR)TRUE;
	case WM_COMMAND:
		AdminBooksWindowController::GetInstance()->HandleWindowCommand(hDlg, message, wParam, lParam);
		break;
	case WM_PAINT:
		AdminBooksWindowController::GetInstance()->HandlePaintCommand(hDlg, message, wParam, lParam);
		break;
	}
	return (INT_PTR)FALSE;
}

bool AdminBooksWindowController::PerformChecks(HWND hDlg)
{
	
	int dlgItemsIDsToCheck[] =
	{
		INPF_BOOK_NAME,
		INPF_ADDBOOK_AUTHORNAME,
		INPF_ADDBOOK_ISBNCODE
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

bool AdminBooksWindowController::PerformItemCheck(HWND hDlg, int dlgID)
{
	bool thereIsAError = false;
	int iTextLength;
	HWND hInpf;

	switch (dlgID)
	{
		case INPF_BOOK_NAME:
		{
			hInpf = GetDlgItem(hDlg, INPF_BOOK_NAME);
			iTextLength = GetWindowTextLength(hInpf);
			if (iTextLength == 0)
			{
				thereIsAError = true;
				MessageBox(NULL, L"Es necesario ingresar una cantidad de prendas a cotizar en el campo 'Nombre del libro'", L"Error", MB_ICONERROR);
			}
		}
		case INPF_ADDBOOK_AUTHORNAME:
		{
			hInpf = GetDlgItem(hDlg, INPF_ADDBOOK_AUTHORNAME);
			iTextLength = GetWindowTextLength(hInpf);
			if (iTextLength == 0)
			{
				thereIsAError = true;
				MessageBox(NULL, L"Es necesario ingresar una cantidad de prendas a cotizar en el campo 'Nombre del autor del libro'", L"Error", MB_ICONERROR);
			}
		}
		case INPF_ADDBOOK_ISBNCODE:
		{
			hInpf = GetDlgItem(hDlg, INPF_ADDBOOK_ISBNCODE);
			iTextLength = GetWindowTextLength(hInpf);
			if (iTextLength == 0)
			{
				thereIsAError = true;
				MessageBox(NULL, L"Es necesario ingresar una cantidad de prendas a cotizar en el campo 'Codigo ISBN'", L"Error", MB_ICONERROR);
			}
		}
	}
	return thereIsAError;
}


