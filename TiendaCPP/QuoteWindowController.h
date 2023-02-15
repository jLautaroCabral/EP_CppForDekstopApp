#pragma once
#include "framework.h"
#include "WindowController.h"

#ifndef QUOTE_WINDOW_CONTROLLER_H
#define QUOTE_WINDOW_CONTROLLER_H

class QuoteWindowController :  WindowController
{
protected:
	QuoteWindowController();
	static QuoteWindowController* singleton_;

	RECT rect;

	HWND hChkManga;
	HWND hChkCuello;
	HWND hChkChupin;

	HWND hRbtnCamisa;
	HWND hRbtnPantalon;

	HWND hRbtnStandar;
	HWND hRbtnPremium;

	HWND hInpFPrice;
	HWND hInpFQuantity;

	HWND hBtnQuitation;
	HWND hLblQuotation;

	int quotePrice;
	int quoteQuantity;
	int quoteFinalPrice;

	virtual void InitializeWindowHandlersIfNeeded(HWND hDlg) override;
	virtual void HandleWindowCommand(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) override;
	virtual void HandlePaintCommand(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) override;
public:
	virtual ~QuoteWindowController() override;
	//      * Singletons should not be cloneable.
	QuoteWindowController(QuoteWindowController& other) = delete;

	//      * Singletons should not be assignable.
	void operator=(const QuoteWindowController&) = delete;

	static QuoteWindowController* GetInstance();
	
	static INT_PTR CALLBACK HandleWindow(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
};

#endif