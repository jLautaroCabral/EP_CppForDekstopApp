#include "QuotesHistoryWindowController.h"

INT_PTR QuotesHistoryWindowController::HandleWindow(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:

		//int wmId = LOWORD(wParam);
		//int wmCode = HIWORD(wParam);

		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	case WM_PAINT:
		PAINTSTRUCT ps;
		RECT rect;
		HFONT hFontOriginal, hFont1, hFont2, hFont3;
		HDC hdc = BeginPaint(hDlg, &ps);
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

		EndPaint(hDlg, &ps);
		break;
	}


	return (INT_PTR)FALSE;
}