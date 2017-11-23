#include "CProjectDlg.h"
CProject CProjectDlg::s_prj;
bool	 CProjectDlg::s_isedit;

/////////////////////////////////////
// Constructors / Destructors      //
/////////////////////////////////////

CProjectDlg::CProjectDlg(HINSTANCE hInstance, HWND hWnd)
{
	//bewaar de instance en de parent window handle
	this->m_hOwner		= hWnd;
	this->m_hInstance	= hInstance;
}

CProjectDlg::~CProjectDlg()
{
}

/////////////////////////////////////
// Memberfuncties                  //
/////////////////////////////////////

BOOL CProjectDlg::DlgProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	CDatum deadline;
	string strNaam;

	switch(uMsg)
	{
	case WM_INITDIALOG:
		//zet alles uit temp op het scherm
		
		//MessageBox(NULL, "CREATED", "TEST", MB_OK);
		break;
	case WM_COMMAND:
		switch(LOWORD(wParam))
		{
  			case IDOK:
				//vul tempPrj met de waarden van het dialoog
				char szNaam[255], szNotitie[1024], szDeadline[255];
				int iStatus;
				if(s_isedit)
					strNaam = s_prj.getNaam();
				else
				{
					GetDlgItemText(hDlg, IDC_NAAM, szNaam, 255);
					strNaam = szNaam;
				}
				GetDlgItemText(hDlg, IDC_NOTITIE, szNotitie, 1024);
				GetDlgItemText(hDlg, IDC_DEADLINE, szDeadline, 255);
				deadline = CDatum(szDeadline);
				iStatus = SendMessage(GetDlgItem(hDlg, IDC_STATUS), CB_GETCURSEL, 0, 0);

				if (iStatus == CB_ERR)
					iStatus = 0;
				s_prj.setProject(CProjectActiviteit(strNaam, iStatus, deadline, szNotitie));
				SendMessage(GetWindow(hDlg, GW_OWNER), WM_SETPRJ, (WPARAM)&s_prj, s_isedit);
				EndDialog(hDlg, IDOK);
				return TRUE;
  			case IDCANCEL:
				//maak de tempPrj leeg
				EndDialog(hDlg, IDCANCEL);
				return TRUE;
		}
		break;
	}
	return FALSE;
}

void CProjectDlg::Show(CProject *temp, bool isedit)
{
	//toon het dialoog venster
	m_hProject = CreateDialog(m_hInstance, MAKEINTRESOURCE(IDD_PROJECT), m_hOwner, (DLGPROC)DlgProc);
	ShowWindow(m_hProject, SW_SHOWNORMAL);

	initDlg();
	showData(temp);
	s_isedit = isedit;
}

void CProjectDlg::initDlg()
{
	//vul de lijst met status
	SendMessage(GetDlgItem(m_hProject, IDC_STATUS), CB_INSERTSTRING, 0, LPARAM("Actief"));
	SendMessage(GetDlgItem(m_hProject, IDC_STATUS), CB_INSERTSTRING, 1, LPARAM("Beëindigd"));
	SendMessage(GetDlgItem(m_hProject, IDC_STATUS), CB_INSERTSTRING, 2, LPARAM("Geblokkeerd"));
}

void CProjectDlg::showData(CProject *temp)
{
	SetDlgItemText(m_hProject, IDC_NAAM, const_cast<char *>(temp->getNaam().c_str()));
	SetDlgItemText(m_hProject, IDC_NOTITIE, const_cast<char *>(temp->getNotitie().c_str()));
	SendMessage(GetDlgItem(m_hProject, IDC_STATUS), CB_SETCURSEL, temp->getStatus(), 0);
	SetDlgItemText(m_hProject, IDC_DEADLINE, const_cast<char *>(temp->getDeadLine().toString()));
	SetDlgItemText(m_hProject, IDC_TOTAALTIJD, const_cast<char *>(temp->getTotaalTijd().toString()));
	s_prj = *temp;
}
