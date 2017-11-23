#ifndef CSPLASHDLG_H
#define CSPLASHDLG_H

#include <windows.h>
#include "..\Resource\resource.h"
#include <strstream>

class CSplashDlg
{
private:
	HWND		m_hSplash;
	HWND		m_hParent;
	HINSTANCE	m_hInstance;
public:
	CSplashDlg(HINSTANCE, HWND);
	~CSplashDlg();
	void Show();
	static BOOL DlgProc(HWND, UINT, WPARAM, LPARAM);
};

#endif
