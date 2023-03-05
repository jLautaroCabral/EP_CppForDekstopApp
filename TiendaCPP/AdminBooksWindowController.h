#include "WindowController.h"

#ifndef ADMIN_BOOKS_WINDOW_CONTROLLER_H
#define ADMIN_BOOKS_WINDOW_CONTROLLER_H
class AdminBooksWindowController : WindowController
{
protected:
	AdminBooksWindowController();
	static AdminBooksWindowController* singleton_;

	virtual void InitializeWindowHandlersIfNeeded(HWND hDlg) override;
	virtual void HandleWindowCommand(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) override;
	virtual void HandlePaintCommand(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) override;

public:
	virtual ~AdminBooksWindowController() override;
	//      * Singletons should not be cloneable.
	AdminBooksWindowController(AdminBooksWindowController& other) = delete;

	//      * Singletons should not be assignable.
	void operator=(const AdminBooksWindowController&) = delete;

	static AdminBooksWindowController* GetInstance();

	static bool PerformChecks(HWND hDlg);

	static bool PerformItemCheck(HWND hDlg, int dlgID);

	static void UpdateListBoxInfo(HWND hDlg);
	static void UpdateItemSelectionOnList(HWND hDlg);
	

	static INT_PTR CALLBACK HandleWindow(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
};
#endif