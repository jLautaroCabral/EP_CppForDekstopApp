#include "WindowController.h"

#ifndef LOANS_HISTORY_WINDOW_CONTROLLER_H
#define LOANS_HISTORY_WINDOW_CONTROLLER_H
class LoanHistoryWindowController : WindowController
{
protected:
	LoanHistoryWindowController();
	static LoanHistoryWindowController* singleton_;

	virtual void InitializeWindowHandlersIfNeeded(HWND hDlg) override;
	virtual void HandleWindowCommand(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) override;
	virtual void HandlePaintCommand(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) override;

public:
	virtual ~LoanHistoryWindowController() override;
	//      * Singletons should not be cloneable.
	LoanHistoryWindowController(LoanHistoryWindowController& other) = delete;

	//      * Singletons should not be assignable.
	void operator=(const LoanHistoryWindowController&) = delete;

	static LoanHistoryWindowController* GetInstance();

	static bool PerformChecks(HWND hDlg);

	static bool PerformItemCheck(HWND hDlg, int dlgID);

	static void UpdateListBoxInfo(HWND hDlg);

	static void UpdateItemInfoOfLoanSelectedOnList(HWND hDlg);

	static INT_PTR CALLBACK HandleWindow(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
};
#endif