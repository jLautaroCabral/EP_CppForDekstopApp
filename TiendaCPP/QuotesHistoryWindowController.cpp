#include <list>

#include "QuotesHistoryWindowController.h"
#include "resource.h"
#include "Quotation.h"
#include "MainWindowController.h"
#include <ctime>
#pragma _CTR_SECURE_NO_WARNINGS
using namespace std;

QuotesHistoryWindowController::~QuotesHistoryWindowController() {}


QuotesHistoryWindowController* QuotesHistoryWindowController::GetInstance()
{
	/**
	 * This is a safer way to create an instance. instance = new Singleton is
	 * dangeruous in case two instance threads wants to access at the same time
	 */
	if (singleton_ == nullptr) {
		singleton_ = new QuotesHistoryWindowController();
	}
	return singleton_;
}

QuotesHistoryWindowController* QuotesHistoryWindowController::singleton_ = nullptr;


QuotesHistoryWindowController::QuotesHistoryWindowController()
{
}

void QuotesHistoryWindowController::InitializeWindowHandlersIfNeeded(HWND hDlg)
{
}

void QuotesHistoryWindowController::HandleWindowCommand(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
	{
		EndDialog(hDlg, LOWORD(wParam));
	}
}

void QuotesHistoryWindowController::HandlePaintCommand(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	HWND hComboHistory = GetDlgItem(hDlg, LBC_DESCRIPTION);

	list<Quotation*> quotations = MainWindowController::GetInstance()->store->quotationHistory;
	string historyMesssage = "Realiza cotizaciones para ver el historial";
	for (Quotation* const& quotation : quotations)
	{
		historyMesssage += "\n";
		historyMesssage += "-------------------------------------\n";
		historyMesssage += "NUMERO DE IDENTIFICACION: " + to_string(quotation->quotationID) + "\n";
		historyMesssage += "Codigo del vendedor: " + quotation->sellerID + "\n";
		historyMesssage += "Prenda cotizada: " + quotation->garmentPtr->garmentName + "\n";
		historyMesssage += "Precio unitario: " + to_string(quotation->unitaryPrice) + "\n";
		historyMesssage += "Cantidad de prendas cotizadas: " + to_string(quotation->garmentQuantity) + "\n";
		historyMesssage += "Precio final: " + to_string(quotation->quotationResult) + "\n";
		historyMesssage += "-------------------------------------\n";
	}
	SetDlgItemText(hDlg, LBL_HISTORY_TEXT, (wstring(historyMesssage.begin(), historyMesssage.end())).c_str());
}

INT_PTR QuotesHistoryWindowController::HandleWindow(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;
	case WM_PAINT:
		QuotesHistoryWindowController::GetInstance()->HandlePaintCommand(hDlg, message, wParam, lParam);
		break;
	case WM_COMMAND:
		QuotesHistoryWindowController::GetInstance()->HandleWindowCommand(hDlg, message, wParam, lParam);
		break;
	}

	return (INT_PTR)FALSE;
}