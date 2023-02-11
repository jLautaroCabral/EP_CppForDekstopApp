// TiendaCPP.cpp : Define el punto de entrada de la aplicación.
//

#include "framework.h"
#include "TiendaCPP.h"

#define MAX_LOADSTRING 100

// Variables globales:
HINSTANCE hInst;                                // instancia actual
WCHAR szTitle[MAX_LOADSTRING];                  // Texto de la barra de título
WCHAR szWindowClass[MAX_LOADSTRING];            // nombre de clase de la ventana principal

// Declaraciones de funciones adelantadas incluidas en este módulo de código:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	//return MessageBox(NULL, L"hello, world", L"caption", 0);

    UNREFERENCED_PARAMETER(hPrevInstance); //
    UNREFERENCED_PARAMETER(lpCmdLine); //

    // TODO: Colocar código aquí.

    // Inicializar cadenas globales
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING); //
    LoadStringW(hInstance, IDC_TIENDACPP, szWindowClass, MAX_LOADSTRING); //
    MyRegisterClass(hInstance);

    // Realizar la inicialización de la aplicación:
    if (!InitInstance (hInstance, nCmdShow)) //
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_TIENDACPP));

    MSG msg;

    // Bucle principal de mensajes:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  FUNCIÓN: MyRegisterClass()
//
//  PROPÓSITO: Registra la clase de ventana.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_TIENDACPP));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOWFRAME +1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_TIENDACPP);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}


static struct {
	const wchar_t* txt;    // pointer to text to display on button face
	int      iCount;       // count of number of times button clicked
	HWND     hwnd;         // button window handle which identifies the button
} myButtons[] = {
	{L"Points up", 0, 0},
	{L"Points dwn", 0, 0},
	{L"Level up", 0, 0},
	{L"Level dwn", 0, 0}
};

TCHAR greeting[] = _T("Hello, Windows desktop!");

//
//   FUNCIÓN: InitInstance(HINSTANCE, int)
//
//   PROPÓSITO: Guarda el identificador de instancia y crea la ventana principal
//
//   COMENTARIOS:
//
//        En esta función, se guarda el identificador de instancia en una variable común y
//        se crea y muestra la ventana principal del programa.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Almacenar identificador de instancia en una variable global

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   // create the displayed window along with the buttons.
  // the buttons are in a single row at the top of the window.

   POINT myPoint = { 10, 10 };  // x, y

   for (auto& a : myButtons) {
	   a.hwnd = CreateWindow(
		   L"BUTTON",  // Predefined class; Unicode assumed 
		   a.txt,      // Button text 
		   WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
		   myPoint.x,  // x position 
		   myPoint.y,  // y position 
		   100,        // Button width
		   50,         // Button height
		   hWnd,       // Parent window
		   NULL,       // No menu.
		   (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
		   NULL);      // Pointer not needed.

	   myPoint.x += 100 + 20;    // button width plus a separation distance
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

// process a button click event and return an indication
// whether the button handle matches one we are managing (1)
// or not managing (0).
int buttonClick(HWND hWnd, HWND hButton)
{
	// look through the list of buttons to see if the window handle
	// of the button event matches one of our buttons.
	for (auto& a : myButtons) {
		if (a.hwnd == hButton) {
			// this is one of our buttons so we increment button click count.
			// then invalidate the window area and update to trigger WM_PAINT message.
			a.iCount++;
			InvalidateRect(hWnd, NULL, TRUE);
			UpdateWindow(hWnd);
			return 1;    // indicate we processed this event.
		}
	}
	return 0;    // indicate we did not process this event
}


//
//  FUNCIÓN: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PROPÓSITO: Procesa mensajes de la ventana principal.
//
//  WM_COMMAND  - procesar el menú de aplicaciones
//  WM_PAINT    - Pintar la ventana principal
//  WM_DESTROY  - publicar un mensaje de salida y volver
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
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
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX_NEW), hWnd, About);
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
					if (buttonClick(hWnd, (HWND)lParam))
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

			TextOut(hdc, 100, 100, greeting, _tcslen(greeting));

			//Logical units are device dependent pixels, so this will create a handle to a logical font that is 48 pixels in height.
			//The width, when set to 0, will cause the font mapper to choose the closest matching value.
			//The font face name will be Impact.
			hFont1 = CreateFont(48, 0, 0, 0, FW_DONTCARE, FALSE, TRUE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
				CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Impact"));
			hFontOriginal = (HFONT)SelectObject(hdc, hFont1);

			//Sets the coordinates for the rectangle in which the text is to be formatted.
			SetRect(&rect, 100, 100, 700, 200);
			SetTextColor(hdc, RGB(255, 0, 0));
			DrawText(hdc, TEXT("Drawing Text with Impact"), -1, &rect, DT_NOCLIP);

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

			SelectObject(hdc, hFontOriginal);
			DeleteObject(hFont1);
			DeleteObject(hFont2);
			DeleteObject(hFont3);

//			DialogBox(hInst, MAKEINTRESOURCE(IDD_OLE_PROPPAGE_LARGE), hWnd, About);


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
		//DialogBox(hInst, MAKEINTRESOURCE(IDD_OLE_PROPPAGE_LARGE), hWnd, About);
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Controlador de mensajes del cuadro Acerca de.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}