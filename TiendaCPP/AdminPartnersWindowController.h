#include "WindowController.h"

#ifndef ADMIN_PARTNERS_WINDOW_CONTROLLER_H
#define ADMIN_PARTNERS_WINDOW_CONTROLLER_H
class AdminPartnersWindowController : WindowController
{
protected:
	AdminPartnersWindowController();
	static AdminPartnersWindowController* singleton_;

	virtual void InitializeWindowHandlersIfNeeded(HWND hDlg) override;
	virtual void HandleWindowCommand(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) override;
	virtual void HandlePaintCommand(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) override;

public:
	virtual ~AdminPartnersWindowController() override;
	//      * Singletons should not be cloneable.
	AdminPartnersWindowController(AdminPartnersWindowController& other) = delete;

	//      * Singletons should not be assignable.
	void operator=(const AdminPartnersWindowController&) = delete;

	static AdminPartnersWindowController* GetInstance();

	static bool PerformChecks(HWND hDlg);
	static bool PerformItemCheck(HWND hDlg, int dlgID);

	static void UpdateListBoxInfo(HWND hDlg);
	static void UpdateItemSelectionOnList(HWND hDlg);

	static INT_PTR CALLBACK HandleWindow(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
};
#endif