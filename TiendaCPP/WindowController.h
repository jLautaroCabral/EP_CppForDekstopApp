#pragma once
#include "framework.h"

#ifndef WINDOW_CONTROLLER_H
#define WINDOW_CONTROLLER_H

class WindowController
{
protected:
	bool handlersInitialized;
	virtual void InitializeWindowHandlersIfNeeded(HWND hDlg) = 0;
	virtual void HandlePaintCommand(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) = 0;
	virtual void HandleWindowCommand(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) = 0;
public:
	virtual ~WindowController() = 0;
};
#endif