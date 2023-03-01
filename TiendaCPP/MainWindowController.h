#pragma once

#include "framework.h"
#include "Store.h"

#ifndef MAIN_WINDOW_CONTROLLER_H
#define MAIN_WINDOW_CONTROLLER_H

typedef	INT_PTR(*OnPressActionHandler)(HWND, UINT, WPARAM, LPARAM);

class MainWindowController
{
private:
	static MainWindowController* singleton_;

	struct ButtonInfo
	{
		const wchar_t* txt;		// pointer to text to display on button face
		int iCount;				// count of number of times button clicked
		HWND hWnd;				// button window handle which identifies the button

		LPCWSTR ResourceID;		//
		HINSTANCE* hInstance;	//

		OnPressActionHandler onPressActionHandler;		// OnPressActionHandle is a own typedef
		void OnPressAction() { DialogBox(*hInstance, ResourceID, hWnd, onPressActionHandler); }
	};

	HINSTANCE* hInst = nullptr;
	HWND* hWnd = nullptr;
	ButtonInfo windowButtonsInfo[4] = { nullptr };

	int HandleButtonClick(HWND hWnd, HWND hButton);
	void CreateButtons(HWND hWnd);

public:
	Store* store;
	MainWindowController();
	~MainWindowController();
	void Initialize(HINSTANCE* inst, HWND* hwnd);

	static MainWindowController* GetInstance();

	LRESULT CALLBACK HandleMainWindowProd(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};
#endif