#include "WindowController.h"

#ifndef ADMIN_LOANS_WINDOW_CONTROLLER_H
#define ADMIN_LOANS_WINDOW_CONTROLLER_H
class AdminLoansWindowController : WindowController
{
protected:
	AdminLoansWindowController();
	static AdminLoansWindowController* singleton_;

	virtual void InitializeWindowHandlersIfNeeded(HWND hDlg) override;
	virtual void HandleWindowCommand(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) override;
	virtual void HandlePaintCommand(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) override;

public:
	virtual ~AdminLoansWindowController() override;
	//      * Singletons should not be cloneable.
	AdminLoansWindowController(AdminLoansWindowController& other) = delete;

	//      * Singletons should not be assignable.
	void operator=(const AdminLoansWindowController&) = delete;

	static AdminLoansWindowController* GetInstance();

	static bool PerformChecks(HWND hDlg);

	static bool PerformItemCheck(HWND hDlg, int dlgID);

	static void UpdateListBoxInfo(HWND hDlg);

	static void UpdatePartnerComboBox(HWND hDlg);
	static void UpdateBookComboBox(HWND hDlg);
	static void UpdateExemplaryComboBox(HWND hDlg);

	static void UpdateItemInfoOfLoanSelectedOnList(HWND hDlg);
	static void UpdateItemInfoOfPartnerSelectedOnComboBox(HWND hDlg);


	static INT_PTR CALLBACK HandleWindow(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
};
#endif