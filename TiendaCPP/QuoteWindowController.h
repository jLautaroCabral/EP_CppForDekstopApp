#pragma once
#include "framework.h"

#ifndef QUOTE_WINDOW_CONTROLLER_H
#define QUOTE_WINDOW_CONTROLLER_H

class QuoteWindowController
{
public:
	static INT_PTR CALLBACK HandleWindow(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
};

#endif