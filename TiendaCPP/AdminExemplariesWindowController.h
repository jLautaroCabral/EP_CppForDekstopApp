#include "WindowController.h"

#ifndef ADMIN_EXEMPLARIES_WINDOW_CONTROLLER_H
#define ADMIN_EXEMPLARIES_WINDOW_CONTROLLER_H
class AdminExemplariesWindowController : WindowController
{
protected:
	AdminExemplariesWindowController();
	static AdminExemplariesWindowController* singleton_;

	virtual void InitializeWindowHandlersIfNeeded(HWND hDlg) override;
	virtual void HandleWindowCommand(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) override;
	virtual void HandlePaintCommand(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) override;

public:
	virtual ~AdminExemplariesWindowController() override;
	//      * Singletons should not be cloneable.
	AdminExemplariesWindowController(AdminExemplariesWindowController& other) = delete;

	//      * Singletons should not be assignable.
	void operator=(const AdminExemplariesWindowController&) = delete;

	static AdminExemplariesWindowController* GetInstance();

	static bool PerformChecks(HWND hDlg);

	static bool PerformItemCheck(HWND hDlg, int dlgID);

	static void UpdateListBoxInfo(HWND hDlg);
	static void UpdateComboBoxesInfo(HWND hDlg);
	static void UpdateItemSelectionOnList(HWND hDlg);


	static INT_PTR CALLBACK HandleWindow(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
};
#endif