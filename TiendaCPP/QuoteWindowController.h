#pragma once
#include "framework.h"
#include "WindowController.h"
#include "Garment.h"
#include "Quotation.h"

#ifndef QUOTE_WINDOW_CONTROLLER_H
#define QUOTE_WINDOW_CONTROLLER_H

class QuoteWindowController : WindowController
{
protected:
	QuoteWindowController();
	static QuoteWindowController* singleton_;
	static int nextIDForQuotation;
	RECT rect;

	HWND hRbtnMangaCorta;
	HWND hRbtnMangaLarga;
	HWND hRbtnCuelloComun;
	HWND hRbtnCuelloMao;

	HWND hRbtnPantalonComun;
	HWND hRbtnPantalonChupin;

	HWND hRbtnStandar;
	HWND hRbtnPremium;

	HWND hInpFPrice;
	HWND hInpFQuantity;

	HWND hBtnQuitation;
	HWND hLblQuotation;

	Garment* garmetToQuote;

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

	bool PerformChecks(HWND hDlg);

	bool PerformItemCheck(HWND hDlg, int dlgID);

	void BuildQuotation(Quotation& quotation, Garment& garment, std::string& quotationText);

	void RegisterQuotation(Quotation* quotation);

	static QuoteWindowController* GetInstance();
	
	static INT_PTR CALLBACK HandleWindow(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
};

#endif