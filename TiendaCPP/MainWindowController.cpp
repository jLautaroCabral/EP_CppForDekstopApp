#include "MainWindowController.h"
#include "framework.h"
#include "resource.h"
#include "QuoteWindowController.h"
#include "QuotesHistoryWindowController.h"
#include "SettingsWindowController.h"
#include "TiendaCPP.h"

static struct {
	const wchar_t* txt;    // pointer to text to display on button face
	int      iCount;       // count of number of times button clicked
	HWND     hWnd;         // button window handle which identifies the button
	//void (*onPressAction)();
	LPCWSTR ResourceID;
	OnPressActionHandler onPressActionHandler;
	void OnPressAction()
	{
		OpenDialogBox();
	}
private:
	void OpenDialogBox()
	{
		//DialogBox(hInst, ResourceID, hWnd, onPressActionHandler);
	}
} myButtons[] = {
	{L"Realizar cotizacion", 0, 0, MAKEINTRESOURCE(IDD_COTIZACIONBOX), QuoteWindowController::HandleWindow},
	{L"Historial de cotizaciones", 0, 0, MAKEINTRESOURCE(IDD_HISTORYBOX), QuotesHistoryWindowController::HandleWindow},
	{L"Configurar vendedor", 0, 0, MAKEINTRESOURCE(IDD_SETTINGSBOX), SettingsWindowController::HandleWindow},
	//{L"Level dwn", 0, 0}
};

TCHAR greeting[] = _T("Software para venta de ropa, proyecto estudiantil");
TCHAR storeName[] = _T("Tienda: Nike");
TCHAR userName[] = _T("Vendedor: Rebeca");

// process a button click event and return an indication
// whether the button handle matches one we are managing (1)
// or not managing (0).
int HandleButtonClick(HWND hWnd, HWND hButton)
{
	// look through the list of buttons to see if the window handle
	// of the button event matches one of our buttons.
	for (auto& a : myButtons) {
		if (a.hWnd == hButton) {
			// this is one of our buttons so we increment button click count.
			// then invalidate the window area and update to trigger WM_PAINT message.
			a.iCount++;
			a.OnPressAction();
			InvalidateRect(hWnd, NULL, TRUE);
			UpdateWindow(hWnd);
			return 1;    // indicate we processed this event.
		}
	}

	return 0;    // indicate we did not process this event
}


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
			//DialogBox(hInst, MAKEINTRESOURCE(IDD_OLE_PROPPAGE_LARGE), hWnd, About);
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
		// TODO: Agregar cualquier código de dibujo que use hDC aquí...

		//Logical units are device dependent pixels, so this will create a handle to a logical font that is 48 pixels in height.
		//The width, when set to 0, will cause the font mapper to choose the closest matching value.
		//The font face name will be Impact.
		hFont1 = CreateFont(48, 0, 0, 0, FW_DONTCARE, FALSE, TRUE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
			CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Impact"));
		hFontOriginal = (HFONT)SelectObject(hdc, hFont1);

		//Sets the coordinates for the rectangle in which the text is to be formatted.
		SetRect(&rect, 100, 50, 700, 200);
		SetTextColor(hdc, RGB(0, 0, 0));
		DrawText(hdc, TEXT("Bienvenidos a TiendaCPP"), -1, &rect, DT_NOCLIP);

		SelectObject(hdc, hFontOriginal);
		TextOut(hdc, 100, 105, greeting, _tcslen(greeting));

		TextOut(hdc, 100, 130, storeName, _tcslen(storeName));
		TextOut(hdc, 100, 150, userName, _tcslen(userName));

		/*ANOTHER TEXT SAMPLES


		//Logical units are device dependent pixels, so this will create a handle to a logical font that is 36 pixels in height.
		//The width, when set to 20, will cause the font mapper to choose a font which, in this case, is stretched.
		//The font face name will be Times New Roman.  This time nEscapement is at -300 tenths of a degree (-30 degrees)
		hFont2 = CreateFont(36, 20, -300, 0, FW_DONTCARE, FALSE, TRUE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
			CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Times New Roman"));
		SelectObject(hdc, hFont2);

		//Sets the coordinates for the rectangle in which the text is to be formatted.
		SetRect(&rect, 100, 200, 900, 800);
		SetTextColor(hdc, RGB(0, 128, 0));
		DrawText(hdc, TEXT("Drawing Text with Times New Roman"), -1, &rect, DT_NOCLIP);

		//Logical units are device dependent pixels, so this will create a handle to a logical font that is 36 pixels in height.
		//The width, when set to 10, will cause the font mapper to choose a font which, in this case, is compressed.
		//The font face name will be Arial. This time nEscapement is at 250 tenths of a degree (25 degrees)
		hFont3 = CreateFont(36, 10, 250, 0, FW_DONTCARE, FALSE, TRUE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
			CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, VARIABLE_PITCH, TEXT("Arial"));
		SelectObject(hdc, hFont3);

		//Sets the coordinates for the rectangle in which the text is to be formatted.
		SetRect(&rect, 500, 200, 1400, 600);
		SetTextColor(hdc, RGB(0, 0, 255));
		DrawText(hdc, TEXT("Drawing Text with Arial"), -1, &rect, DT_NOCLIP);

		*/


		SelectObject(hdc, hFontOriginal);
		DeleteObject(hFont1);
		//DeleteObject(hFont2);
		//DeleteObject(hFont3);

		//DialogBox(hInst, MAKEINTRESOURCE(IDD_OLE_PROPPAGE_LARGE), hWnd, About);


		wchar_t myText[2][64];
		// following swprintf_s() works because template
		// generates the proper call with the additional buffer
		// size argument.
		swprintf_s(myText[0], L"Points: %d", myButtons[0].iCount - myButtons[1].iCount);
		swprintf_s(myText[1], L"Level: %d", myButtons[2].iCount - myButtons[3].iCount);

		// get the text metrics of the font we are using to draw the text so
		// that we can find out how tall the letters are and can adjust the
		// distance for each line of text properly.
		TEXTMETRIC myTextMetric = { 0 };
		GetTextMetrics(hdc, &myTextMetric);

		// we will use a POINT struct for maintaining the point at which
		// the text output will start. x coordinate is horizontal position
		// and y coordinate is the vertical position.
		POINT myPoint = { 10, 150 };  // x, y
		int   myMargin = 5;

		// iterate over the list of strings we are displaying and
		// display each one on a separate line.
		for (auto& a : myText) {
			TextOut(hdc, myPoint.x, myPoint.y, a, wcslen(a));
			myPoint.y += myTextMetric.tmHeight + myMargin;
		}

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

// create the displayed window along with the buttons.
// the buttons are in a single row at the top of the window.
void CreateButtons(HWND hWnd)
{
	POINT myPoint = { 100, 300 };  // x, y

	for (auto& a : myButtons) {
		a.hWnd = CreateWindow(
			L"BUTTON",  // Predefined class; Unicode assumed 
			a.txt,      // Button text 
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