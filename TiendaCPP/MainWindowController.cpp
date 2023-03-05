#include "MainWindowController.h"
#include "framework.h"
#include "resource.h"
#include "QuoteWindowController.h"
#include "QuotesHistoryWindowController.h"
#include "SettingsWindowController.h"
#include "AdminBooksWindowController.h"
#include "AdminExemplariesWindowController.h"
#include "AdminPartnersWindowController.h"
#include "AdminLoansWindowController.h"
#include "LoanHistoryWindowController.h"
#include "Store.h"
#include "Shirt.h"
#include "Pants.h"
#include "Garment.h"

TCHAR greeting[] = _T("Software para biblioteca, proyecto estudiantil");
TCHAR storeName[] = _T("Tienda: Nombre De Tienda De Ejemplo");
TCHAR userName[] = _T("Vendedor: Nombre De Vendedor De Ejemplo");

// Declaraciones de funciones adelantadas incluidas en este módulo de código:
void CreateButtons(HWND);

MainWindowController::MainWindowController() {}

MainWindowController::~MainWindowController() {}

MainWindowController* MainWindowController::singleton_ = nullptr;

MainWindowController* MainWindowController::GetInstance()
{
	/**
	 * This is a safer way to create an instance. instance = new Singleton is
	 * dangeruous in case two instance threads wants to access at the same time
	 */
	if (singleton_ == nullptr) {
		singleton_ = new MainWindowController();
	}
	return singleton_;
}


void MainWindowController::Initialize(HINSTANCE* inst, HWND* hwnd)
{
	hInst = inst;
	hWnd = hwnd;

	CreateButtons(*hWnd);
}


// process a button click event and return an indication
// whether the button handle matches one we are managing (1)
// or not managing (0).
int MainWindowController::HandleButtonClick(HWND hWnd, HWND hButton)
{
	// look through the list of buttons to see if the window handle
	// of the button event matches one of our buttons.
	for (auto& button : windowButtonsInfo) {
		if (button.hWnd == hButton) {
			// this is one of our buttons so we increment button click count.
			// then invalidate the window area and update to trigger WM_PAINT message.
			button.iCount++;
			button.OnPressAction();
			InvalidateRect(hWnd, NULL, TRUE);
			UpdateWindow(hWnd);
			return 1;    // indicate we processed this event.
		}
	}

	return 0;    // indicate we did not process this event
}

// create the displayed window along with the buttons.
// the buttons are in a single row at the top of the window.
void MainWindowController::CreateButtons(HWND hWnd)
{
	windowButtonsInfo[0] = { L"Administrar libros", 0, 0, MAKEINTRESOURCE(IDD_ADMIN_BOOKS), hInst, AdminBooksWindowController::HandleWindow };
	windowButtonsInfo[1] = { L"Administrar ejemplares", 0, 0, MAKEINTRESOURCE(IDD_ADMIN_EXEMPLARIES), hInst, AdminExemplariesWindowController::HandleWindow };
	windowButtonsInfo[2] = { L"Administrar socios", 0, 0, MAKEINTRESOURCE(IDD_ADMIN_PARTNERS), hInst, AdminPartnersWindowController::HandleWindow };
	windowButtonsInfo[3] = { L"Administrar prestámos", 0, 0, MAKEINTRESOURCE(IDD_ADMIN_LOANS), hInst, AdminLoansWindowController::HandleWindow };
	windowButtonsInfo[4] = { L"Consultar historial de prestamos y devoluciones", 0, 0, MAKEINTRESOURCE(IDD_LOANSHISTORY), hInst, LoanHistoryWindowController::HandleWindow };

	POINT myPoint = { 100, 300 };  // x, y

	for (auto& button : windowButtonsInfo) {
		button.hWnd = CreateWindow(
			L"BUTTON",  // Predefined class; Unicode assumed 
			button.txt,      // Button text 
			WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
			myPoint.x,  // x position 
			myPoint.y,  // y position 
			420,        // Button width
			50,         // Button height
			hWnd,       // Parent window
			NULL,       // No menu.
			(HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
			NULL);      // Pointer not needed.

		myPoint.y += 50 + 20;    // button width plus a separation distance
	}
}


//  FUNCIÓN: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PROPÓSITO: Procesa mensajes de la ventana principal.
//
//  WM_COMMAND  - procesar el menú de aplicaciones
//  WM_PAINT    - Pintar la ventana principal
//  WM_DESTROY  - publicar un mensaje de salida y volver
LRESULT MainWindowController::HandleMainWindowProd(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		int wmCode = HIWORD(wParam);
		// Analizar las selecciones de menú:
		switch (wmId)
		{
		case IDM_ABOUT:
			//DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX_NEW), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			// not a menu event so see if it is a button click or not.
			if (wmCode == BN_CLICKED) {
				// if we are managing this button then we skip
				// the DefWindowProc() otherwise it is called.
				//DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX_NEW), hWnd, About);
				if (HandleButtonClick(hWnd, (HWND)lParam))
					break;
			}
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		RECT rect;
		HFONT hFontOriginal, hFont1, hFont2, hFont3;
		HDC hdc = BeginPaint(hWnd, &ps);

		//Logical units are device dependent pixels, so this will create a handle to a logical font that is 48 pixels in height.
		//The width, when set to 0, will cause the font mapper to choose the closest matching value.
		//The font face name will be Impact.
		hFont1 = CreateFont(48, 0, 0, 0, FW_DONTCARE, FALSE, TRUE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
			CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Impact"));
		hFontOriginal = (HFONT)SelectObject(hdc, hFont1);

		//Sets the coordinates for the rectangle in which the text is to be formatted.
		SetRect(&rect, 100, 50, 700, 200);
		SetTextColor(hdc, RGB(0, 0, 0));
		DrawText(hdc, TEXT("¡Bienvenidos a LibreriaCPP!"), -1, &rect, DT_NOCLIP);

		SelectObject(hdc, hFontOriginal);
		TextOut(hdc, 100, 105, greeting, _tcslen(greeting));

		TextOut(hdc, 100, 130, storeName, _tcslen(storeName));
		TextOut(hdc, 100, 150, userName, _tcslen(userName));

		SelectObject(hdc, hFontOriginal);
		DeleteObject(hFont1);

		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}