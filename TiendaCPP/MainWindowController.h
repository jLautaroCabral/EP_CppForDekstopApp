#pragma once

#include "framework.h"

#ifndef MAIN_WINDOW_CONTROLLER_H
#define MAIN_WINDOW_CONTROLLER_H

typedef	INT_PTR(*OnPressActionHandler)(HWND, UINT, WPARAM, LPARAM);

class MainWindowController
{
private:
	HINSTANCE* hInst = nullptr;                                // instancia actual
public:
	MainWindowController(HINSTANCE* inst);
	~MainWindowController();
	LRESULT CALLBACK HandleMainWindowProd(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};
#endif