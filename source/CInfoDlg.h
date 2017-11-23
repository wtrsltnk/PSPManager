#ifndef CINFODLG_H
#define CINFODLG_H

#include <windows.h>
#include "..\Resource\resource.h"
#include <strstream>

class CInfoDlg
{
private:
	HWND		m_hWnd;
	HINSTANCE	m_hInstance;
public:
	CInfoDlg(HINSTANCE, HWND);
	~CInfoDlg();
	void Show();
	static BOOL DlgProc(HWND, UINT, WPARAM, LPARAM);
};

#endif
