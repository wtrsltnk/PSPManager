#include "CActiviteitDlg.h"

bool CActiviteitDlg::s_isedit;
CActiviteit CActiviteitDlg::s_act;
string CActiviteitDlg::s_prj;
act_message CActiviteitDlg::s_sendAct;

/////////////////////////////////////
// Constructors / Destructors      //
/////////////////////////////////////

CActiviteitDlg::CActiviteitDlg(HINSTANCE hInstance, HWND hWnd)
{
	//bewaar de instance en de parent window handle
	this->m_hOwner		= hWnd;
	this->m_hInstance	= hInstance;
}

CActiviteitDlg::~CActiviteitDlg()
{
}

/////////////////////////////////////
// Memberfuncties                  //
/////////////////////////////////////

BOOL CActiviteitDlg::DlgProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	string strNaam;
	CDatum deadline;
	switch(uMsg)
	{
		case WM_COMMAND:
			switch(LOWORD(wParam))
			{
  				case IDOK:
				char szNaam[255], szNotitie[1024], szDeadline[255];
				int iStatus;

				//controleer of het om bewerken of toevoegen van een activiteit gaat
				if(s_isedit)
					strNaam = s_act.getNaam();
				else
				{
					GetDlgItemText(hDlg, IDC_NAAM, szNaam, 255);
					strNaam = szNaam;
				}

				//vraag de inhoud van de text vakken op
				GetDlgItemText(hDlg, IDC_NOTITIE, szNotitie, 1024);
				GetDlgItemText(hDlg, IDC_DEADLINE, szDeadline, 255);
				deadline = CDatum(szDeadline);
				iStatus = SendMessage(GetDlgItem(hDlg, IDC_STATUS), CB_GETCURSEL, 0, 0);
				if (iStatus == CB_ERR)
					iStatus = 0;

				//zet alle informatie van het dialoog in een object
				s_act.setActiviteit(CProjectActiviteit(strNaam, iStatus, deadline, szNotitie));
				
				//stuur een message naar maiframe om het project ver vernieuwen of
				//toe te voegen
				s_sendAct.activiteit = &s_act;
				s_sendAct.project = &s_prj;
				SendMessage(GetWindow(hDlg, GW_OWNER), WM_SETACT, (WPARAM)&s_sendAct, s_isedit);
				EndDialog(hDlg, IDOK);

				//Als er cancel geklikt wordt niets doen
  				case IDCANCEL:
					EndDialog(hDlg, IDCANCEL);
					return TRUE;
			}
			break;
	}
	return FALSE;
}

void CActiviteitDlg::Show(CActiviteit *temp, string project, bool isedit)
{
	this->project = project;
	//toon het dialoog venster MODALLESS
	m_hActiviteit = CreateDialog(m_hInstance, MAKEINTRESOURCE(IDD_ACTIVITEIT), m_hOwner, (DLGPROC)DlgProc);
	ShowWindow(m_hActiviteit, SW_SHOWNORMAL);

	//initialiseer het scherm en toon de data uit het project
	initDlg();
	showData(temp, project);
	s_isedit = isedit;
}

void CActiviteitDlg::initDlg()
{
	//vul de lijst met status
	SendMessage(GetDlgItem(m_hActiviteit, IDC_STATUS), CB_INSERTSTRING, 0, LPARAM("Actief"));
	SendMessage(GetDlgItem(m_hActiviteit, IDC_STATUS), CB_INSERTSTRING, 1, LPARAM("Beëindigd"));
	SendMessage(GetDlgItem(m_hActiviteit, IDC_STATUS), CB_INSERTSTRING, 2, LPARAM("Geblokkeerd"));
}

void CActiviteitDlg::showData(CActiviteit *temp, string project)
{
	//vul de project in
    SetDlgItemText(m_hActiviteit, IDC_PROJECT, const_cast<const char *>(project.c_str()));
	//vul de naam in
    SetDlgItemText(m_hActiviteit, IDC_NAAM, const_cast<const char *>(temp->getNaam().c_str()));
	//vul de notitie
    SetDlgItemText(m_hActiviteit, IDC_NOTITIE, const_cast<const char *>(temp->getNotitie().c_str()));
	//zet de status
	SendMessage(GetDlgItem(m_hActiviteit, IDC_STATUS), CB_SETCURSEL, temp->getStatus(), 0);
	//vul de deadine
    SetDlgItemText(m_hActiviteit, IDC_DEADLINE, const_cast<const char *>(temp->getDeadLine().toString().c_str()));
	//vul de totaal tijd
    SetDlgItemText(m_hActiviteit, IDC_TOTAALTIJD, const_cast<const char *>(temp->getTotaalTijd().toString().c_str()));
	s_act = *temp;
	s_prj = project;
}
