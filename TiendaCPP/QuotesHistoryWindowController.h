#pragma once

#include "framework.h"

#ifndef QUOTES_HISTORY_WINDOW_CONTROLLER_H
#define QUOTES_HISTORY_WINDOW_CONTROLLER_H

class QuotesHistoryWindowController
{
public:
	static INT_PTR CALLBACK HandleWindow(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
};
#endif