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
		hChkManga = GetDlgItem(hDlg, CHK_MANGA);
		hChkCuello = GetDlgItem(hDlg, CHK_CUELLO);
		hChkChupin = GetDlgItem(hDlg, CHK_CHUPIN);

		hRbtnCamisa = GetDlgItem(hDlg, CHK_MANGA);
		hRbtnPantalon = GetDlgItem(hDlg, CHK_MANGA);

		hRbtnStandar = GetDlgItem(hDlg, CHK_MANGA);
		hRbtnPremium = GetDlgItem(hDlg, CHK_MANGA);

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
	bool withoutErrors = true;
	PerformItemCheck(hDlg, RBTN2_PANT, withoutErrors);
	PerformItemCheck(hDlg, RBTN_STANDAR, withoutErrors);
	PerformItemCheck(hDlg, INPF_PRICE, withoutErrors);
	PerformItemCheck(hDlg, INPF_QUANTITY, withoutErrors);
	return withoutErrors;
}

void QuoteWindowController::PerformItemCheck(HWND hDlg, int dlgID, bool& withoutErrors)
{
	int iTextLength;
	LPWSTR stringInTheField;
	wchar_t str[100];
	switch (dlgID)
	{
	case RBTN2_PANT:
	case RBTN2_SHIRT:
	{
		if (IsDlgButtonChecked(hDlg, RBTN2_PANT) == BST_UNCHECKED && IsDlgButtonChecked(hDlg, RBTN2_SHIRT) == BST_UNCHECKED)
		{
			withoutErrors = false;
			MessageBox(NULL, L"Es necesario seleccionar un tipo de prenda (Camisa o Pantal�n)", L"Error", MB_ICONERROR);
		}
		break;
	}
	case RBTN_STANDAR:
	case RBTN_PREMIUM:
	{
		if (IsDlgButtonChecked(hDlg, RBTN_STANDAR) == BST_UNCHECKED && IsDlgButtonChecked(hDlg, RBTN_PREMIUM) == BST_UNCHECKED)
		{
			withoutErrors = false;
			MessageBox(NULL, L"Es necesario seleccionar un tipo de calidad (Standar o Premium)", L"Error", MB_ICONERROR);
		}
		break;
	}
	case INPF_QUANTITY:
	{
		iTextLength = GetWindowTextLength(hInpFQuantity);
		if (iTextLength == 0)
		{
			withoutErrors = false;
			MessageBox(NULL, L"Es necesario ingresar una cantidad de prendas a cotizar en el campo 'Cantidad'", L"Error", MB_ICONERROR);
		}
		else
		{
			GetWindowTextW(hInpFQuantity, str, iTextLength + 1);

			wstring ws(str);
			string stdStr(ws.begin(), ws.end());
			if (!Utils::isNumber(stdStr))
			{
				withoutErrors = false;
				MessageBox(NULL, L"Es necesario ingresar un n�mero v�lido en el campo 'Cantidad'", L"Error", MB_ICONERROR);
			}
		}
		break;
	}
	case INPF_PRICE:
	{		
		if (GetWindowTextLength(hInpFPrice) == 0)
		{
			withoutErrors = false;
			MessageBox(NULL, L"Es necesario ingresar un precio unitario a la prenda en el campo 'Precio'", L"Error", MB_ICONERROR);
		}
		break;
	}
	default:
		break;
	}
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
		EnableWindow(hChkManga, TRUE);
		EnableWindow(hChkCuello, TRUE);
		EnableWindow(hChkChupin, FALSE);
		CheckDlgButton(hDlg, CHK_CHUPIN, BST_UNCHECKED);
		break;

	case RBTN2_PANT:
		EnableWindow(hChkManga, FALSE);
		EnableWindow(hChkCuello, FALSE);
		EnableWindow(hChkChupin, TRUE);
		CheckDlgButton(hDlg, CHK_MANGA, BST_UNCHECKED);
		CheckDlgButton(hDlg, CHK_CUELLO, BST_UNCHECKED);
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
