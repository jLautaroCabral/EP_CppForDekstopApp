#include "framework.h"

#ifndef SETTINGS_WINDOW_CONTROLLER_H
#define SETTINGS_WINDOW_CONTROLLER_H

class SettingsWindowController
{
public:
	static INT_PTR CALLBACK HandleWindow(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
};
#endif