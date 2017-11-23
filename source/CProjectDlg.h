#ifndef CPROJECTDLG_H
#define CPROJECTDLG_H

#include <windows.h>
#include "..\Resource\resource.h"
#include "..\bc\Project.h"

#define WM_SETPRJ WM_USER+5001

class CProjectDlg
{
private:
	HWND		m_hOwner;
	HWND		m_hProject;
	HINSTANCE	m_hInstance;
	static CProject s_prj;
	static bool s_isedit;
public:
	CProjectDlg(HINSTANCE, HWND);
	~CProjectDlg();
	void Show(CProject *, bool);
	static BOOL DlgProc(HWND, UINT, WPARAM, LPARAM);
	void showData(CProject *);
	void initDlg();
};

#endif
