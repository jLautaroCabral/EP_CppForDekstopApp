#pragma once
#include "framework.h"
#include "WindowController.h"

#ifndef QUOTES_HISTORY_WINDOW_CONTROLLER_H
#define QUOTES_HISTORY_WINDOW_CONTROLLER_H

class QuotesHistoryWindowController : WindowController
{
protected:
	QuotesHistoryWindowController();
	static QuotesHistoryWindowController* singleton_;
	virtual void InitializeWindowHandlersIfNeeded(HWND hDlg) override;
	virtual void HandleWindowCommand(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) override;
	virtual void HandlePaintCommand(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) override;

public:
	virtual ~QuotesHistoryWindowController() override;
	//      * Singletons should not be cloneable.
	QuotesHistoryWindowController(QuotesHistoryWindowController& other) = delete;
	//      * Singletons should not be assignable.
	void operator=(const QuotesHistoryWindowController&) = delete;

	static QuotesHistoryWindowController* GetInstance();
	static INT_PTR CALLBACK HandleWindow(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
};
#endif