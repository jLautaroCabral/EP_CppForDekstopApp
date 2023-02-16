#include <string>
#include <iostream>
#include <chrono>

#include "QuoteWindowController.h"
#include "resource.h"
#include "framework.h"
#include "Pants.h"
#include "Shirt.h"
#include "Utils.h"
#include "MainWindowController.h"
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

QuoteWindowController* QuoteWindowController::singleton_ = nullptr;
int QuoteWindowController::nextIDForQuotation = 0;

QuoteWindowController::QuoteWindowController() {}

QuoteWindowController::~QuoteWindowController() {}

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
		break;
	}
	case BTN_QUOTE:
	{
		if (PerformChecks(hDlg)) // Comprobación de campos antes de hacer la cotización
		{
			Quotation* quotation = new Quotation();
			string message = "";
			// Aqui viene la cotizacion
			if (IsDlgButtonChecked(hDlg, RBTN2_PANT) == BST_CHECKED)
			{
				singleton_->garmetToQuote = new Pants();
				Pants* garmentPants = dynamic_cast<Pants*>(singleton_->garmetToQuote);

				garmentPants->garmentType = Garment::Pants;

				garmentPants->pantType =
					IsDlgButtonChecked(hDlg, RBTN5_COMUN) == BST_CHECKED ? Pants::Comun : Pants::Chupin;
			}
			else if (IsDlgButtonChecked(hDlg, RBTN2_SHIRT) == BST_CHECKED)
			{
				singleton_->garmetToQuote = new Shirt();
				Shirt* garmentShirt = dynamic_cast<Shirt*>(singleton_->garmetToQuote);

				garmentShirt->garmentType = Garment::Shirt;

				garmentShirt->qualityType =
					IsDlgButtonChecked(hDlg, RBTN_STANDAR) == BST_CHECKED ? Garment::Standar : Garment::Premium;
				
				garmentShirt->mangaType =
					IsDlgButtonChecked(hDlg, RBTN3_MANGA_CORTA) == BST_CHECKED ? Shirt::MangaCorta : Shirt::MangaLarga;

				garmentShirt->cuelloType =
					IsDlgButtonChecked(hDlg, RBTN4_CUELLO_COMUN) == BST_CHECKED ? Shirt::CuelloComun : Shirt::CuelloMao;
			}

			iTextLength = GetWindowTextLength(hInpFPrice);
			GetWindowTextW(hInpFPrice, priceStr, iTextLength + 1);
			quotePrice = _wtoi(priceStr);
			iTextLength = GetWindowTextLength(hInpFQuantity);
			GetWindowTextW(hInpFQuantity, priceStr, iTextLength + 1);
			quoteQuantity = _wtoi(priceStr);

			quotation->unitaryPrice = quotePrice;
			quotation->garmentQuantity = quoteQuantity;

			auto currentTime = std::chrono::system_clock::now();
			quotation->quotationDate = chrono::system_clock::to_time_t(currentTime);
			quotation->sellerID = MainWindowController::GetInstance()->store->currentSeller->sellerID;
			quotation->quotationID = nextIDForQuotation;
			nextIDForQuotation++;
			BuildQuotation(*quotation, *(singleton_->garmetToQuote), message);
			RegisterQuotation(quotation);

			SetDlgItemText(hDlg, LBL_QUOTATION_RESUME, (wstring(message.begin(), message.end())).c_str());
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

void QuoteWindowController::RegisterQuotation(Quotation* quotation)
{
	MainWindowController::GetInstance()->store->quotationHistory.push_front(quotation);
}

void QuoteWindowController::BuildQuotation(Quotation& quotation, Garment& garment, std::string& quotationText)
{
	string descountString;
	size_t pos;
	string descountStringTruncated;

	int originalPrice = quotation.unitaryPrice * quotation.garmentQuantity;
	quotationText = "";

	float priceWithDiscoutns = originalPrice;
	quotationText = "Precio base: $ " + std::to_string(originalPrice) + "\n";

	if (garment.garmentType == Garment::Shirt)
	{
		Shirt garmentShirt = dynamic_cast<Shirt&>(garment);

		if (garmentShirt.mangaType == Shirt::MangaCorta)
		{
			descountString = to_string(originalPrice * 0.10f);
			pos = descountString.find(".");
			descountStringTruncated = descountString.substr(0, pos + 3);

			quotationText += "Descuento por remera tipo Manga Corta: - $" + descountStringTruncated + "\n";
			priceWithDiscoutns -= originalPrice * 0.10f;
		}

		if (garmentShirt.cuelloType == Shirt::CuelloMao)
		{
			descountString = to_string(originalPrice * 0.3f);
			pos = descountString.find(".");
			descountStringTruncated = descountString.substr(0, pos + 3);

			quotationText += "Aumento por remera tipo Cuello Mao: + $" + descountStringTruncated + "\n";
			priceWithDiscoutns += originalPrice * 0.03f;
		}
	}
	else
	{
		Pants garmentPants = dynamic_cast<Pants&>(garment);
		
		if (garmentPants.pantType == Pants::Chupin)
		{
			descountString = to_string(originalPrice * 0.12f);
			pos = descountString.find(".");
			descountStringTruncated = descountString.substr(0, pos + 3);

			quotationText += "Descuento por pantalon tipo Chupin: - $" + descountStringTruncated + "\n";
			priceWithDiscoutns -= originalPrice * 0.12f;
		}
	}

	if (garment.qualityType == Garment::Premium)
	{
		descountString = to_string(priceWithDiscoutns * 0.30f);
		pos = descountString.find(".");
		descountStringTruncated = descountString.substr(0, pos + 3);
		quotationText += "\n";
		quotationText += "Aumento por prenda tipo Premium: + $" + descountStringTruncated + "\n";
		priceWithDiscoutns += priceWithDiscoutns * 0.30f;
	}

	string priceWithDiscoutnsTructated;
	pos = to_string(priceWithDiscoutns).find(".");
	priceWithDiscoutnsTructated = to_string(priceWithDiscoutns).substr(0, pos + 3);
	quotationText += "\n";
	quotationText += "RESULTADO FINAL DE COTIZACION: $ " + priceWithDiscoutnsTructated;

	quotation.sellerID = "Vendedor de ejemplo";
	quotation.quotationResult = priceWithDiscoutns;
}

void QuoteWindowController::HandlePaintCommand(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
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
}
