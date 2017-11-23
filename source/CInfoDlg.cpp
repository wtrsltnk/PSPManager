#include "CInfoDlg.h"

/////////////////////////////////////
// Constructors / Destructors      //
/////////////////////////////////////

CInfoDlg::CInfoDlg(HINSTANCE hInstance, HWND hWnd)
{
	//bewaar de instance en de parent window handle
	this->m_hWnd		= hWnd;
	this->m_hInstance	= hInstance;
}

CInfoDlg::~CInfoDlg()
{
}

/////////////////////////////////////
// Memberfuncties                  //
/////////////////////////////////////

BOOL CInfoDlg::DlgProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{

	switch(uMsg)
	{
		case WM_COMMAND:
			switch(LOWORD(wParam))
			{
  				case IDOK:
					EndDialog(hDlg, IDOK);
					return TRUE;
  				case IDCANCEL:
					EndDialog(hDlg, IDCANCEL);
					return TRUE;
			}
			break;
	}
	return FALSE;
}

void CInfoDlg::Show()
{
	//toon het dialoog venster MODAL
	int Nres = DialogBox(m_hInstance, MAKEINTRESOURCE(IDD_INFO), m_hWnd, (DLGPROC)DlgProc);
}
