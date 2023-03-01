#include "AdminBooksWindowController.h"
#include "resource.h"
#include "framework.h"
#include <stdio.h>
#include <string>
#include "DbContextLibrary.h"
#include "BookFactory.h"
#include "Utils.h"

AdminBooksWindowController::AdminBooksWindowController()
{
}
AdminBooksWindowController::~AdminBooksWindowController()
{
}
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
		/*
		hRbtnMangaCorta = GetDlgItem(hDlg, RBTN3_MANGA_CORTA);
		hRbtnMangaLarga = GetDlgItem(hDlg, RBTN3_MANGA_LARGA);
		hRbtnCuelloMao = GetDlgItem(hDlg, RBTN4_CUELLO_COMUN);
		hRbtnCuelloComun = GetDlgItem(hDlg, RBTN4_CUELLO_MAO);
		hRbtnPantalonComun = GetDlgItem(hDlg, RBTN5_COMUN);
		hRbtnPantalonChupin = GetDlgItem(hDlg, RBTN5_CHUPIN);

		hInpFPrice = GetDlgItem(hDlg, INPF_PRICE);
		hInpFQuantity = GetDlgItem(hDlg, INPF_QUANTITY);

		hLblQuotation = GetDlgItem(hDlg, LBL_QUOTATION);

		quotePrice = 10;
		quoteQuantity = 5;
		*/
		AdminBooksWindowController::GetInstance()->handlersInitialized = true;
	}
}

void AdminBooksWindowController::UpdateListBoxInfo(HWND hDlg)
{
	HWND hLbBooks = GetDlgItem(hDlg, LB_BOOKS);
	int itemCount = SendMessage(hLbBooks, LB_GETCOUNT, NULL, NULL);
	for (int i = 0; i < itemCount; i++)
	{
		int itemCount = SendMessage(hLbBooks, LB_DELETESTRING, HIWORD(i), NULL);
	}

	for (const Book* book : DbContextLibrary::GetInstance()->bookTable.GetAllItems())
	{
		// From strting to wchar_t
		std::string stringItemToAdd = "" + book->name + ",   " + book->autor;
		std::wstring wide_string = std::wstring(stringItemToAdd.begin(), stringItemToAdd.end());
		const wchar_t* result = wide_string.c_str();

		int itemPos = SendMessage(hLbBooks, LB_ADDSTRING, NULL, (LPARAM)result);

		// Set the array index of the player as item data.
		// This enables us to retrieve the item from the array
		// even after the items are sorted by the list box.
		SendMessage(hLbBooks, LB_SETITEMDATA, itemPos, (LPARAM)book->modelID);
	}
	// Set input focus to the list box.
	SetFocus(hLbBooks);
}


void UpdateList(HWND hDlg)
{

}
void AdminBooksWindowController::HandleWindowCommand(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	AdminBooksWindowController::GetInstance()->InitializeWindowHandlersIfNeeded(hDlg);

	int lWord = LOWORD(wParam);
	int hWord = HIWORD(wParam);
	int iTextLength;
	int a;
	//std::wstring strFinal;
	wchar_t str[100];
	LPWSTR priceStr(str);

	// TODO: UPGRADE THIS PLS
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
						wchar_t inputStr[100];
						int inputStrLength;

						HWND hInpfBookName = GetDlgItem(hDlg, INPF_BOOK_NAME);
						HWND hInpfBookAuthor = GetDlgItem(hDlg, INPF_ADDBOOK_AUTHORNAME);
						HWND hInpfBookISBNCode = GetDlgItem(hDlg, INPF_ADDBOOK_ISBNCODE);
						HWND hLbBooks = GetDlgItem(hDlg, LB_BOOKS);

						std::string bookName;
						std::string bookAuthorName;
						std::string bookISBNCode;
						
						inputStrLength = GetWindowTextLength(hInpfBookName);
						GetWindowText(hInpfBookName, inputStr, inputStrLength + 1);
						bookName = *Utils::WCharToString_TPointer(inputStr);

						inputStrLength = GetWindowTextLength(hInpfBookAuthor);
						GetWindowText(hInpfBookAuthor, inputStr, inputStrLength + 1);
						bookAuthorName = *Utils::WCharToString_TPointer(inputStr);

						inputStrLength = GetWindowTextLength(hInpfBookISBNCode);
						GetWindowText(hInpfBookISBNCode, inputStr, inputStrLength + 1);
						bookISBNCode = *Utils::WCharToString_TPointer(inputStr);

						Book* newBook = BookFactory::CreateBook(bookName, bookAuthorName, bookISBNCode);
						DbContextLibrary::GetInstance()->bookTable.Add(newBook);

						DbContextLibrary::GetInstance()->PrintBooksDebugInfo();

						UpdateListBoxInfo(hDlg);
					}
					break;
				}
				case LB_BOOKS:
				{
					if (HIWORD(wParam) == LBN_SELCHANGE)
					{
						HWND hwndList = GetDlgItem(hDlg, LB_BOOKS);

						// Get selected index.
						int selectedItem = (int)SendMessage(hwndList, LB_GETCURSEL, 0, 0);
						// Get item data.
						int modelIdOfSelectedItem = (int)SendMessage(hwndList, LB_GETITEMDATA, selectedItem, 0);
						// Get book from DbContext
						Book* bookSelected = DbContextLibrary::GetInstance()->bookTable.GetElementByID(modelIdOfSelectedItem);

						// Fill labels
						SetDlgItemText(hDlg, LBL_BOOKINFO_NAME, Utils::StringToConstWchar_TPointer(bookSelected->name));
						SetDlgItemText(hDlg, LBL_BOOKINFO_AUTHOR, Utils::StringToConstWchar_TPointer(bookSelected->autor));
						SetDlgItemText(hDlg, LBL_BOOKINFO_ISBNCODE, Utils::StringToConstWchar_TPointer(bookSelected->ISBNcode));
						SetDlgItemText(hDlg, LBL_BOOKINFO_EXEMPLARIESAMOUNT, Utils::StringToConstWchar_TPointer(std::to_string(std::size(bookSelected->exemplaries))));
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
	/*
	int dlgItemsIDsToCheck[] =
	{
		RBTN_STANDAR,
		RBTN_PREMIUM,
		RBTN2_SHIRT,
		RBTN2_PANT,
		RBTN3_MANGA_CORTA,
		RBTN3_MANGA_LARGA,
		RBTN4_CUELLO_COMUN,
		RBTN4_CUELLO_MAO,
		RBTN5_COMUN,
		RBTN5_CHUPIN,
		INPF_PRICE,
		INPF_QUANTITY,
		INPF_PRICE
	};

	for (int const& id : dlgItemsIDsToCheck)
	{
		if (PerformItemCheck(hDlg, id)) return false;
	}
	*/
	return true;
}

bool AdminBooksWindowController::PerformItemCheck(HWND hDlg, int dlgID)
{
	/*
	bool thereIsAError = false;
	int iTextLength;
	LPWSTR stringInTheField;
	wchar_t str[100];
	switch (dlgID)
	{
	case RBTN_STANDAR:
	case RBTN_PREMIUM:
	{
		if (IsDlgButtonChecked(hDlg, RBTN_STANDAR) == BST_UNCHECKED && IsDlgButtonChecked(hDlg, RBTN_PREMIUM) == BST_UNCHECKED)
		{
			thereIsAError = true;
			MessageBox(NULL, L"Es necesario seleccionar un tipo de calidad (Standar o Premium)", L"Error", MB_ICONERROR);
		}
		break;
	}
	case RBTN2_PANT:
	case RBTN2_SHIRT:
	{
		if (IsDlgButtonChecked(hDlg, RBTN2_PANT) == BST_UNCHECKED && IsDlgButtonChecked(hDlg, RBTN2_SHIRT) == BST_UNCHECKED)
		{
			thereIsAError = true;
			MessageBox(NULL, L"Es necesario seleccionar un tipo de prenda (Camisa o Pantalón)", L"Error", MB_ICONERROR);
		}
		break;
	}
	case RBTN3_MANGA_LARGA:
	case RBTN3_MANGA_CORTA:
	{
		if (IsDlgButtonChecked(hDlg, RBTN2_SHIRT) == BST_CHECKED &&
			IsDlgButtonChecked(hDlg, RBTN3_MANGA_CORTA) == BST_UNCHECKED &&
			IsDlgButtonChecked(hDlg, RBTN3_MANGA_LARGA) == BST_UNCHECKED)
		{
			thereIsAError = true;
			MessageBox(NULL, L"Es necesario seleccionar un tipo de manga (Manga corta o Manga larga)", L"Error", MB_ICONERROR);
		}
		break;
	}
	case RBTN4_CUELLO_COMUN:
	case RBTN4_CUELLO_MAO:
	{
		if (IsDlgButtonChecked(hDlg, RBTN2_SHIRT) == BST_CHECKED &&
			IsDlgButtonChecked(hDlg, RBTN4_CUELLO_COMUN) == BST_UNCHECKED &&
			IsDlgButtonChecked(hDlg, RBTN4_CUELLO_MAO) == BST_UNCHECKED)
		{
			thereIsAError = true;
			MessageBox(NULL, L"Es necesario seleccionar un tipo de cuello (Cuello común o Cuello Mao)", L"Error", MB_ICONERROR);
		}
		break;
	}
	case RBTN5_COMUN:
	case RBTN5_CHUPIN:
	{
		if (IsDlgButtonChecked(hDlg, RBTN2_PANT) == BST_CHECKED &&
			IsDlgButtonChecked(hDlg, RBTN5_COMUN) == BST_UNCHECKED &&
			IsDlgButtonChecked(hDlg, RBTN5_CHUPIN) == BST_UNCHECKED)
		{
			thereIsAError = true;
			MessageBox(NULL, L"Es necesario seleccionar un tipo de pantalon (Común o Chupín)", L"Error", MB_ICONERROR);
		}
		break;
	}
	case INPF_QUANTITY:
	{
		iTextLength = GetWindowTextLength(hInpFQuantity);
		if (iTextLength == 0)
		{
			thereIsAError = true;
			MessageBox(NULL, L"Es necesario ingresar una cantidad de prendas a cotizar en el campo 'Cantidad'", L"Error", MB_ICONERROR);
		}
		else
		{
			GetWindowTextW(hInpFQuantity, str, iTextLength + 1);

			wstring ws(str);
			string stdStr(ws.begin(), ws.end());
			if (!Utils::isNumber(stdStr))
			{
				thereIsAError = true;
				MessageBox(NULL, L"Es necesario ingresar un número válido en el campo 'Cantidad'", L"Error", MB_ICONERROR);
			}
		}
		break;
	}
	case INPF_PRICE:
	{
		iTextLength = GetWindowTextLength(hInpFPrice);
		if (iTextLength == 0)
		{
			thereIsAError = true;
			MessageBox(NULL, L"Es necesario ingresar un precio unitario a la prenda a cotizar en el campo 'Precio'", L"Error", MB_ICONERROR);
		}
		else
		{
			GetWindowTextW(hInpFPrice, str, iTextLength + 1);

			wstring ws(str);
			string stdStr(ws.begin(), ws.end());
			if (!Utils::isNumber(stdStr))
			{
				thereIsAError = true;
				MessageBox(NULL, L"Es necesario ingresar un número válido en el campo 'Precio'", L"Error", MB_ICONERROR);
			}
		}
		break;
	}
	default:
		break;
	}
	return thereIsAError;
	*/
	return false;
}


