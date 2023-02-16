#include <string>
#include <iostream>

#include "QuoteWindowController.h"
#include "resource.h"
#include "framework.h"
#include "Pants.h"
#include "Shirt.h"
#include "Utils.h"
using namespace std;

QuoteWindowController* QuoteWindowController::GetInstance()
{
	/**
	 * This is a safer way to create an instance. instance = new Singleton is
	 * dangeruous in case two instance threads wants to access at the same time
	 */
	if (singleton_ == nullptr) {
		singleton_ = new QuoteWindowController();
	}
	return singleton_;
}

QuoteWindowController* QuoteWindowController::singleton_ = nullptr;;

QuoteWindowController::QuoteWindowController()
{

}

QuoteWindowController::~QuoteWindowController() { }

void QuoteWindowController::InitializeWindowHandlersIfNeeded(HWND hDlg)
{
	if (!QuoteWindowController::GetInstance()->handlersInitialized)
	{
		hRbtnMangaCorta = GetDlgItem(hDlg, RBTN3_MANGA_CORTA);
		hRbtnMangaLarga = GetDlgItem(hDlg, RBTN3_MANGA_LARGA);
		hRbtnCuelloMao = GetDlgItem(hDlg, RBTN4_CUELLO_COMUN);
		hRbtnCuelloComun = GetDlgItem(hDlg, RBTN4_CUELLO_MAO);
		hRbtnPantalonComun = GetDlgItem(hDlg, RBTN5_COMUN);
		hRbtnPantalonChupin = GetDlgItem(hDlg, RBTN5_CHUPIN);

		//hRbtnCamisa = GetDlgItem(hDlg, CHK_MANGA);
		//hRbtnPantalon = GetDlgItem(hDlg, CHK_MANGA);

		//hRbtnStandar = GetDlgItem(hDlg, CHK_MANGA);
		//hRbtnPremium = GetDlgItem(hDlg, CHK_MANGA);

		hInpFPrice = GetDlgItem(hDlg, INPF_PRICE);
		hInpFQuantity = GetDlgItem(hDlg, INPF_QUANTITY);

		hLblQuotation = GetDlgItem(hDlg, LBL_QUOTATION);

		quotePrice = 10;
		quoteQuantity = 5;

		QuoteWindowController::GetInstance()->handlersInitialized = true;
	}
}


INT_PTR QuoteWindowController::HandleWindow(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId;
	int wmCode;
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;
	case WM_COMMAND:
		QuoteWindowController::GetInstance()->HandleWindowCommand(hDlg, message, wParam, lParam);
		break;
	case WM_PAINT:
		QuoteWindowController::GetInstance()->HandlePaintCommand(hDlg, message, wParam, lParam);
		break;
	}
	return (INT_PTR)FALSE;
}

bool QuoteWindowController::PerformChecks(HWND hDlg)
{
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
	return true;
}

bool QuoteWindowController::PerformItemCheck(HWND hDlg, int dlgID)
{
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
			MessageBox(NULL, L"Es necesario seleccionar un tipo de prenda (Camisa o Pantal�n)", L"Error", MB_ICONERROR);
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
			MessageBox(NULL, L"Es necesario seleccionar un tipo de cuello (Cuello com�n o Cuello Mao)", L"Error", MB_ICONERROR);
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
			MessageBox(NULL, L"Es necesario seleccionar un tipo de pantalon (Com�n o Chup�n)", L"Error", MB_ICONERROR);
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
				MessageBox(NULL, L"Es necesario ingresar un n�mero v�lido en el campo 'Cantidad'", L"Error", MB_ICONERROR);
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
				MessageBox(NULL, L"Es necesario ingresar un n�mero v�lido en el campo 'Precio'", L"Error", MB_ICONERROR);
			}
		}
		break;
	}
	default:
		break;
	}
	return thereIsAError;
}

bool ConvertWideStringToInt(wchar_t* wStr, int& nInt);

void QuoteWindowController::HandleWindowCommand(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	QuoteWindowController::GetInstance()->InitializeWindowHandlersIfNeeded(hDlg);

	int lWord = LOWORD(wParam);
	int hWord = HIWORD(wParam);
	int iTextLength;
	int a;
	std::wstring strFinal;
	wchar_t str[100];
	LPWSTR priceStr(str);
	
	switch (lWord)
	{
	case RBTN2_SHIRT:
		EnableWindow(hRbtnMangaCorta, TRUE);
		EnableWindow(hRbtnMangaLarga , TRUE);
		EnableWindow(hRbtnCuelloMao, TRUE);
		EnableWindow(hRbtnCuelloComun, TRUE);
		EnableWindow(hRbtnPantalonComun, FALSE);
		EnableWindow(hRbtnPantalonChupin, FALSE);
		CheckDlgButton(hDlg, RBTN5_COMUN, BST_UNCHECKED);
		CheckDlgButton(hDlg, RBTN5_CHUPIN, BST_UNCHECKED);
		break;

	case RBTN2_PANT:
		EnableWindow(hRbtnMangaCorta, FALSE);
		EnableWindow(hRbtnMangaLarga, FALSE);
		EnableWindow(hRbtnCuelloMao, FALSE);
		EnableWindow(hRbtnCuelloComun, FALSE);
		EnableWindow(hRbtnPantalonComun, TRUE);
		EnableWindow(hRbtnPantalonChupin, TRUE);
		CheckDlgButton(hDlg, RBTN3_MANGA_CORTA, BST_UNCHECKED);
		CheckDlgButton(hDlg, RBTN3_MANGA_LARGA, BST_UNCHECKED);
		CheckDlgButton(hDlg, RBTN4_CUELLO_COMUN, BST_UNCHECKED);
		CheckDlgButton(hDlg, RBTN4_CUELLO_MAO, BST_UNCHECKED);
		break;

	case INPF_QUANTITY:
	case INPF_PRICE:
	{
		iTextLength = GetWindowTextLength(hInpFPrice);
		GetWindowTextW(hInpFPrice, priceStr, iTextLength + 1);
		quotePrice = _wtoi(priceStr);

		iTextLength = GetWindowTextLength(hInpFQuantity);
		GetWindowTextW(hInpFQuantity, priceStr, iTextLength + 1);
		quoteQuantity = _wtoi(priceStr);

		quoteFinalPrice = quoteQuantity * quotePrice;

		strFinal = L"$  ";
		strFinal += std::to_wstring(quoteFinalPrice) + L"\n precio final";

		SetDlgItemText(hDlg, LBL_QUOTATION, strFinal.c_str());
		//a = UpdateWindow(hDlg);
		break;
	}
	case BTN_QUOTE:
	{
		if (PerformChecks(hDlg))
		{
			// Aqui viene la cotizacion
			if (IsDlgButtonChecked(hDlg, RBTN2_PANT) == BST_CHECKED)
			{
				singleton_->garmetToQuote = new Pants();
				MessageBox(NULL, L"Hola", L"PANTALONES", MB_OK);
			}
			else if (IsDlgButtonChecked(hDlg, RBTN2_SHIRT) == BST_CHECKED)
			{
				singleton_->garmetToQuote = new Shirt();
				MessageBox(NULL, L"Hola", L"CAMISA", MB_OK);
			}
			else
			{
				MessageBox(NULL, L"Hola", L"Seleccione un tipo de prenda", MB_OK);
			}
		}
		
		break;
	}
	default:
		break;
	}

	

	if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
	{
		EndDialog(hDlg, LOWORD(wParam));
	}
}

bool ConvertWideStringToInt (wchar_t* wStr, int& nInt)
{
	if (wscanf_s(wStr, _T("%d"), &nInt) == 1)
		return (true);
	return (false);
}


void QuoteWindowController::HandlePaintCommand(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	
	HFONT hFontOriginal, hFont1;
	HDC hdc = BeginPaint(hDlg, &ps);
	
	/*
	
	hFont1 = CreateFont(25, 0, 0, 0, FW_DONTCARE, FALSE, TRUE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
		CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Impact"));
	hFontOriginal = (HFONT)SelectObject(hdc, hFont1);

	
	quoteFinalPrice = quoteQuantity * quotePrice;

	std::wstring str = L"$  ";
	str += std::to_wstring(quoteFinalPrice);

	//Sets the coordinates for the rectangle in which the text is to be formatted.
	SetRect(&QuoteWindowController::GetInstance()->rect, 250, 280, 750, 200);
	SetTextColor(hdc, RGB(0, 0, 0));
	DrawText(hdc, str.c_str(), -1, &QuoteWindowController::GetInstance()->rect, DT_NOCLIP);

	SelectObject(hdc, hFontOriginal);
	DeleteObject(hFont1);
	*/
	EndPaint(hDlg, &ps);
}
