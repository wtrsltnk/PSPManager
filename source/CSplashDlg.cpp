#include "CSplashDlg.h"

/////////////////////////////////////
// Constructors / Destructors      //
/////////////////////////////////////

CSplashDlg::CSplashDlg(HINSTANCE hInstance, HWND hWnd)
{
	//bewaar de instance en de parent window handle
	this->m_hParent		= hWnd;
	this->m_hInstance	= hInstance;
}

CSplashDlg::~CSplashDlg()
{
}

/////////////////////////////////////
// Memberfuncties                  //
/////////////////////////////////////

BOOL CSplashDlg::DlgProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uMsg)
	{
	case WM_TIMER:
	case WM_LBUTTONDOWN:
	case WM_RBUTTONDOWN:
		EndDialog(hDlg, IDOK);
		break;
	}
	return FALSE;
}

void CSplashDlg::Show()
{
	//toon het dialoog venster
	m_hSplash = CreateDialog(m_hInstance, MAKEINTRESOURCE(IDD_SPLASH), m_hParent, (DLGPROC)DlgProc);
	ShowWindow(m_hSplash, SW_SHOWNORMAL);
	SetTimer(m_hSplash, ID_COUNT_TIMER, 2000, NULL);
}