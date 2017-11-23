#include "CMainFrame.h"

/////////////////////////////////////
// Constructors / Destructors      //
/////////////////////////////////////

CMainFrame::CMainFrame()
{
	this->m_dwWindowStyle	 = WS_MAXIMIZE | WS_OVERLAPPED | WS_SYSMENU | WS_CAPTION | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_THICKFRAME;
	this->m_dwExWindowStyle	 = WS_EX_APPWINDOW;
	this->m_hbrWindowColor	 = (HBRUSH)COLOR_WINDOW;
	this->m_hIcon			 = LoadIcon(m_hInstance, MAKEINTRESOURCE(IDI_DUCK));
	this->m_hMenu = LoadMenu(m_hInstance, MAKEINTRESOURCE(IDR_MENU));
	this->m_strWindowTitle	 = "PSP Manager";
	m_pSuperManager = new CSuperManager();
	
	if ( isOpen() )
	{
		char szBuf[255]; 
		LoadString(m_hInstance, IDS_DUBBLEOPEN, szBuf, 255);
		MessageBox(NULL, szBuf, "PSP Manager", MB_OK|MB_ICONEXCLAMATION);
		exit(0);
	}
	else
	{
		//haal het aantal starts uit het register en zet die in de member functie
		getStarts();
	}
}


CMainFrame::~CMainFrame()
{
	setClose();
}

/////////////////////////////////////
// Memberfuncties                  //
/////////////////////////////////////

LRESULT CMainFrame::MsgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	CProject  * tmpprj;
	CActiviteit  * tmpact;
	string * prjNaam;
	switch ( uMsg )
	{
	case WM_SETPRJ:
		tmpprj = ((CProject*)wParam);
		if ( (lParam == 0) )
			if (m_pSuperManager->getProject(tmpprj->getNaam()) != NULL)
				MessageBox(m_hWnd, "Dit project bestaat al!", "PSP Manager", MB_OK);
			else
				m_pSuperManager->addProject(*tmpprj);
		else
			m_pSuperManager->setProject((CProjectActiviteit)*tmpprj);
			
		//m_pCCManager->updateListView(m_pSuperManager);
		m_pCCManager->updateTreeView(m_pSuperManager);
		break;
	case WM_SETACT:
		tmpact = ((act_message*)wParam)->activiteit;
		prjNaam = ((act_message*)wParam)->project;
		if ( lParam == 0 )
			if (m_pSuperManager->getActiviteit(*prjNaam, tmpact->getNaam()) != NULL)
				MessageBox(m_hWnd, "Deze activiteit bestaat al!", "PSP Manager", MB_OK);
			else
				m_pSuperManager->addActiviteit(*prjNaam, *tmpact);
		else
			m_pSuperManager->setActiviteit(*prjNaam, (CProjectActiviteit)*tmpact);
			
		//m_pCCManager->updateListView(m_pSuperManager);
		m_pCCManager->updateTreeView(m_pSuperManager);
		break;
	case WM_COMMAND:
		//stuur alle menu messages door naar deze functies
		menuProc(hWnd, wParam);			
		break;

	case WM_CREATE:
	
		change = false;


		//dialog manager object
		m_pDlgManager = new CDlgManager(m_hInstance, m_hWnd);
		//SHOW splash screen
		m_pDlgManager->showSplashDlg();

		//Het Systray menuutje initialiseren
		hSystray = CreatePopupMenu();
		AppendMenu(hSystray,MF_STRING ,ID_MSHOW,"Show");
		AppendMenu(hSystray,MF_STRING ,ID_MHIDE,"Hide");
		AppendMenu(hSystray,MF_SEPARATOR,0,0);
		AppendMenu(hSystray,MF_STRING,ID_MINFO,"Info");
		AppendMenu(hSystray,MF_STRING,ID_MDUCK,"Mascotte");

		//systray icoontje initialiseren
		note.cbSize = sizeof(NOTIFYICONDATA);
		note.hIcon = LoadIcon(m_hInstance,MAKEINTRESOURCE(IDI_DUCK));
		note.hWnd = hWnd;
		note.uCallbackMessage = WM_SHELLNOTIFY;
		lstrcpy(note.szTip, "PSP-Manager");
		note.uID = IDI_TRAY;
		note.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
		//toon notify icon
		Shell_NotifyIcon(NIM_ADD,&note);

		///Manager voor de controls aanmaken
		m_pCCManager = new CCManager(m_hInstance, hWnd);

		//set timer en starts in statusbar
		//m_pCCManager->setTimer(0);
		m_pCCManager->setTime();
		m_pCCManager->setStarts(aantalStarts);

		//test gegevens in de controls zetten
		//m_pCCManager->setControlsText();
		
		//Set de timer
		SetTimer(hWnd, ID_TIME, 1000, NULL);
		break;

	case WM_SIZE:
		if(wParam == SIZE_MINIMIZED)
			{
			//als het scherm geminimaliseerd is
				//verberg hoofd venster
				ShowWindow(hWnd,SW_HIDE);
			}
		m_pCCManager->Resize(wParam, lParam);//*/
		break;
	case WM_SHELLNOTIFY:
		{
			if(lParam == WM_RBUTTONDOWN)
			{
				//als de rechter muis knop is in gedrukt, 
				//toon het menuutje
				POINT pt;
				GetCursorPos(&pt);
				SetForegroundWindow(hWnd);
				TrackPopupMenu(hSystray,TPM_RIGHTALIGN,pt.x,pt.y,NULL,hWnd,NULL);
				PostMessage(hWnd,WM_NULL,0,0);	              
			}
			else if(lParam == WM_LBUTTONDBLCLK)
			{
				ShowWindow(m_hWnd,SW_SHOW);
				ShowWindow(m_hWnd,SW_RESTORE);		              
			}
		}			
		break;
	case WM_NOTIFY:
		switch (((LPNMHDR) lParam)->code)
		{
		case TTN_NEEDTEXT:
			//stuur alle requests voor een tooltip text
			//door naar de functie in de toolbar klasse
			m_pCCManager->ToolTipProc(lParam);
			break;
		case TVN_SELCHANGED:
		case LVN_ITEMCHANGED:
		case TVN_KEYDOWN:
			m_pCCManager->CControlProc(hWnd, uMsg, 0, lParam, m_pSuperManager);
			break;
		}
		break;
	case WM_TIMER:
		//zet de huidige tijd in de status balk
		switch (wParam)
		{
		case ID_TIME:
			m_pCCManager->setTime();
			break;
		case ID_COUNT_TIMER:
			//MessageBox(NULL, "Timer", "", MB_OK);
			tr.setStopTijd(CTijd());
			tr.setStopDatum(CDatum());
			strstream str;
			str << "Werktijd: "<< tr.getTotaalTijd().toString() << ends;
			m_pCCManager->setTimer(str.str());
			delete str.str();
			SetTimer(m_hWnd, ID_COUNT_TIMER, 1000, NULL);
			break;
		}
		break;
	case WM_DESTROY:
		//haal het systray icoontje weg
		Shell_NotifyIcon(NIM_DELETE,&note);
		//setClose();
		break;
	}
	return CWin::MsgProc(hWnd, uMsg, wParam, lParam);
}

void CMainFrame::getStarts()
{
	//buffer voor loadstring
	char szBuf[255];

	//vraag het aantal starts op uit de registery klasse
	aantalStarts = m_Registry.getStarts();

	//controleer of het de eerste keer is, of dat er een error op getrede is
	if (aantalStarts == 1)		//eerste keer dat het programma gestart wordt
	{
		//laad een string uit de string tabel
		LoadString(m_hInstance, IDS_REG_NEW, szBuf, 255);
		//geef een message box
		MessageBox(m_hWnd, szBuf, "PSP Manager", MB_OK);
	}
	else if (aantalStarts < 1)	//error, register sleutel kon nietgemaakt of geleze worden
	{
		//laad een string uit de string tabel
		LoadString(m_hInstance, IDS_REG_FAIL, szBuf, 255);
		//geef een message box
		MessageBox(m_hWnd, szBuf, "PSP Manager", MB_OK);
	}
}

bool CMainFrame::isOpen()
{
	return m_Registry.isOpen();
}

void CMainFrame::setClose()
{
	m_Registry.setClose();
}

CProject CMainFrame::getNewProject()
{
    CProject p;
	//vul de atributen van het Project object
    p.setNaam("Nieuw Project");
    p.setNotitie("Geen Notities");
    p.setStatus(0);

	//return  het gevulde project
    return p;
}

CProject* CMainFrame::getSelProject()
{
	//vraag het geselecteerde project op
    return m_pSuperManager->getProject(m_pCCManager->getSelectedProject());;
}

CActiviteit* CMainFrame::getSelActiviteit()
{
	//vraag de geselecteerde activiteit op
    return m_pSuperManager->getActiviteit(m_pCCManager->getSelectedProject(), m_pCCManager->getSelectedActiviteit());
}

CActiviteit CMainFrame::getNewActiviteit()
{
    CActiviteit a;
	//vul de atributen van het Activiteit object
    a.setNaam("Nieuwe Activiteit");
    a.setNotitie("Geen Notities");
    a.setStatus(0);

	//return  het gevulde project
    return a;
}


//////////////////////
///Bestand functies///
//////////////////////
void CMainFrame::NieuwFile()
{
	//supermanager leegmaken
	if (m_pSuperManager != NULL)
		delete m_pSuperManager;
	m_pSuperManager = new CSuperManager();
	
	//treeview leegmaken
	m_pCCManager->updateTreeView(m_pSuperManager);
	
	//listview leegmaken
	m_pCCManager->updateListView(m_pSuperManager);

}

void CMainFrame::OpenFile()
{
	//Xmlfile inlezen
	string filename = m_pDlgManager->showOpen();
	if (filename != "")
	{
		this->NieuwFile();
		m_pSuperManager->readXML(filename);
	}
	//supermanager in treeview zetten
	m_pCCManager->updateTreeView(m_pSuperManager);
}

void CMainFrame::OpslaanFile()
{
	string filename;
	//supermanager op slaan in xml
	if (m_pSuperManager->getXMLPath() != "")
		m_pSuperManager->saveXML();
	else
		filename = m_pDlgManager->showSave();
		if (filename != "")
			m_pSuperManager->saveXML(filename);
}

void CMainFrame::OpslaanAlsFile()
{
	//ShowSaveDialog()
	//OpslaanFile(nieuw_bestandsnaam)
	string filename = m_pDlgManager->showSave();
	if (filename != "")
		m_pSuperManager->saveXML(filename);
}

bool CMainFrame::OpslaanQuestion()
{
	if (change)
	{
		int result;
		string filename;
		char szBuf[255];
		LoadString(m_hInstance, IDS_SAVE_QUESTION, szBuf, 255);
		if (m_pSuperManager->getXMLPath() != "")
		{
			result = MessageBox(m_hWnd, szBuf, "PSP Manager", MB_YESNOCANCEL|MB_ICONQUESTION|MB_DEFBUTTON1);
			switch (result)
			{
			case IDYES:
				m_pSuperManager->saveXML();
			case IDNO:
				//stop de timer
				SendMessage(m_hWnd, WM_COMMAND, (WPARAM)LOWORD(ID_TIMER_STOP), 0);
				return true;
			case IDCANCEL:
				return false;
			}
		}
		else
		{
			result = MessageBox(m_hWnd, szBuf, "PSP Manager", MB_YESNOCANCEL|MB_ICONQUESTION|MB_DEFBUTTON1);
			switch (result)
			{
			case IDYES:
				filename = m_pDlgManager->showSave();
				if (filename != "")
					m_pSuperManager->saveXML(filename);
			case IDNO:
				//stop de timer
				SendMessage(m_hWnd, WM_COMMAND, (WPARAM)LOWORD(ID_TIMER_STOP), 0);
				return true;
			case IDCANCEL:
				return false;
			}
		}
	}
	return true;
}

void CMainFrame::ImportFile()
{
	string filename = m_pDlgManager->showImport();
	if (filename != "")
	{
		m_pSuperManager->importXML(filename);
		m_pCCManager->updateTreeView(m_pSuperManager);
	}
}

void CMainFrame::ExportFile()
{
	string filename = m_pDlgManager->showExport();
	if (filename != "")
		m_pSuperManager->exportXML(filename);
}
///////////////////////////
///Eind Bestand functies///
///////////////////////////

void CMainFrame::menuProc(HWND hWnd, WPARAM wParam)
{
	string filename;
	strstream str;
	char szText[255];
	LoadString(m_hInstance, IDS_CLOSE, szText, 255);



	switch ( LOWORD(wParam) )
	{
	//BESTAND MENU
	case ID_BESTAND_NIEUW:
		if (this->OpslaanQuestion())
		{
			this->change = false;
			this->NieuwFile();
		}
		break;
	case ID_BESTAND_OPENEN:
		if (this->OpslaanQuestion())
		{
			this->change = false;
			this->OpenFile();
		}
		break;
	case ID_BESTAND_SLUITEN:
		if (this->OpslaanQuestion())
		{
			this->change = false;
			this->NieuwFile();
		}
		break;
	case ID_BESTAND_IMPORTEREN:
		this->ImportFile();
		break;
	case ID_BESTAND_EXPORTEREN:
		this->ExportFile();
		break;
	case ID_BESTAND_OPSLAAN:
		this->OpslaanFile();
		this->change = false;
		break;
	case ID_BESTAND_OPSLAANALS:
		this->OpslaanAlsFile();
		this->change = false;
		break;
	case ID_BESTAND_AFSLUITEN:
		if (this->OpslaanQuestion())
		{
			Shell_NotifyIcon(NIM_DELETE,&note);
			SendMessage(hWnd, WM_DESTROY, 0, 0);
		}
		break;





	//BEWERKEN MENU
	case ID_PROJECT_NEW:
		this->change = true;
        this->prj = getNewProject();
        m_pDlgManager->showProjectDlg(&this->prj, false);
		break;
	case ID_PROJECT_REMOVE:
		this->change = true;
		if (m_pCCManager->getSelectedProject() != "")	//is een project geselecteerd?
		{
			LoadString(m_hInstance, IDS_ZEKER, szText, 255);
			if (MessageBox(m_hWnd, szText, "PSP Manager", MB_YESNO|MB_ICONQUESTION|MB_DEFBUTTON2) == IDYES)
				m_pSuperManager->removeProject(m_pCCManager->getSelectedProject());
			m_pCCManager->updateTreeView(m_pSuperManager);
			m_pCCManager->updateListView(m_pSuperManager);
		}
		else
		{
			LoadString(m_hInstance, IDS_SEL_PROJECT, szText, 255);
			MessageBox(m_hWnd, szText, "PSP Manager", MB_OK|MB_ICONINFORMATION);
		}
		break;
	case ID_PROJECT_EDIT:
		this->change = true;
		if (m_pCCManager->getSelectedProject() != "")		//is een project geselecteerd?
        {
            m_pDlgManager->showProjectDlg(getSelProject(), true);
        }
		else
		{
			LoadString(m_hInstance, IDS_SEL_PROJECT, szText, 255);
			MessageBox(m_hWnd, szText, "PSP Manager", MB_OK|MB_ICONINFORMATION);
		}
		break;
	case ID_ACTIVITEIT_NEW:
		this->change = true;
		if (m_pCCManager->getSelectedProject() != "")		//is een project geselecteerd?
        {
            if((m_pSuperManager->getProject(m_pCCManager->getSelectedProject())->getStatus() == 0)
                    && !(CDatum() < m_pSuperManager->getProject(m_pCCManager->getSelectedProject())->getDeadLine()))
            {
                this->act = getNewActiviteit();
                m_pDlgManager->showActiviteitDlg(&this->act, m_pCCManager->getSelectedProject(), false);
            }
			else
			{	
				LoadString(m_hInstance, IDS_ACT_BLOCKED, szText, 255);
				MessageBox(hWnd, szText, "PSP-Manager", MB_OK|MB_ICONINFORMATION);
			}
        }
		else
		{
			LoadString(m_hInstance, IDS_SEL_PROJECT, szText, 255);
			MessageBox(m_hWnd, szText, "PSP Manager", MB_OK|MB_ICONINFORMATION);
		}
		break;
	case ID_ACTIVITEIT_REMOVE:
		this->change = true;
		if (m_pCCManager->getSelectedActiviteit() != "")	//is een activiteit geselecteerd?
		{
			LoadString(m_hInstance, IDS_ZEKER, szText, 255);
			if(MessageBox(m_hWnd, szText, "PSP Manager", MB_YESNO|MB_ICONQUESTION|MB_DEFBUTTON2) == IDYES)
				m_pSuperManager->removeActiviteit(m_pCCManager->getSelectedProject(), m_pCCManager->getSelectedActiviteit());
			m_pCCManager->updateTreeView(m_pSuperManager);
			m_pCCManager->updateListView(m_pSuperManager);
		}
		else
		{
			LoadString(m_hInstance, IDS_SEL_ACTIVITEIT, szText, 255);
			MessageBox(m_hWnd, szText, "PSP Manager", MB_OK|MB_ICONINFORMATION);
		}
		break;
	case ID_ACTIVITEIT_EDIT:
		this->change = true;
		if (m_pCCManager->getSelectedActiviteit() != "")	//is een activiteit geselecteerd?
        {
            m_pDlgManager->showActiviteitDlg(getSelActiviteit(), m_pCCManager->getSelectedProject(), true);
        }
		else
		{
			LoadString(m_hInstance, IDS_SEL_ACTIVITEIT, szText, 255);
			MessageBox(m_hWnd, szText, "PSP Manager", MB_OK|MB_ICONINFORMATION);
		}
		break;
	
	//KOPPELING MENU
	case ID_KOPPELING_MANAGEMENTINFO:
		//MessageBox(m_hWnd, "Management info","Koppeling", MB_OK|MB_ICONINFORMATION);

		break;
		
	//TIMER MENU
	case ID_TIMER_START:
		this->change = true;
		if (stricmp(ca.c_str(), "") == 0)	//loopt er een timer?
		{
			cp = m_pCCManager->getSelectedProject();
			ca = m_pCCManager->getSelectedActiviteit();
			if (stricmp(ca.c_str(), "") != 0)
			{
				if ( (m_pSuperManager->getProject(cp)->getActiviteit(ca)->getStatus() == 0) && (m_pSuperManager->getProject(cp)->getStatus() == 0) && !(CDatum() < m_pSuperManager->getProject(cp)->getDeadLine()) && !(CDatum() < m_pSuperManager->getActiviteit(cp, ca)->getDeadLine()))
				{
					tr = CTijdRegistratie();
					LoadString(m_hInstance, IDS_TIMER_STARTED, szText, 255);
					str << szText << cp << " / " << ca << ends;
					m_pCCManager->setTimer(str.str());
					delete str.str();
					SetTimer(m_hWnd, ID_COUNT_TIMER, 1000, NULL);
				}
				else
				{
					LoadString(m_hInstance, IDS_TIMER_BLOCKED, szText, 255);
					MessageBox(hWnd, szText, "PSP Manager", MB_OK|MB_ICONINFORMATION);
					cp = "";
					ca = "";
				}
			}
			else
			{
				LoadString(m_hInstance, IDS_SEL_ACTIVITEIT, szText, 255);
				MessageBox(hWnd, szText, "PSP Manager", MB_OK|MB_ICONINFORMATION);
				cp = "";
				ca = "";
			}
		}
		else
		{
			LoadString(m_hInstance, IDS_TIMER_ON, szText, 255);
			MessageBox(hWnd, szText, "PSP Manager", MB_OK|MB_ICONINFORMATION);
		}
		break;
	case ID_TIMER_STOP:
		this->change = true;
		tr.setStopTijd(CTijd());
		tr.setStopDatum(CDatum());
		m_pSuperManager->addTijdRegistratie(cp, ca, tr);
		m_pCCManager->updateListView(m_pSuperManager);
		cp = "";
		ca = "";
		KillTimer(m_hWnd, ID_COUNT_TIMER);
		break;

	
	//HELP MENU
	case ID_HELP_INHOUDSOPGAVE:
		//MessageBox(m_hWnd, "Inhoudsopgave","Help", MB_OK);
//		HtmlHelp(NULL, "PSP_Help.chm", HH_DISPLAY_TOPIC, 0);
		break;
	case ID_HELP_INFO:
		//MessageBox(m_hWnd, "Info","Help", MB_OK);
		m_pDlgManager->showInfoDlg();
		break;

	//SYSTRAY MENU
	case ID_MINFO:
		m_pDlgManager->showInfoDlg();
		break;
	case ID_MSHOW:
		ShowWindow(m_hWnd,SW_SHOW);
		ShowWindow(m_hWnd,SW_RESTORE);
		break;
	case ID_MHIDE:
		ShowWindow(m_hWnd,SW_HIDE);
		break;
	case ID_MDUCK:
		m_pDlgManager->showSplashDlg();
		break;
	}
}
