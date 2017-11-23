#include "CCManager.h"

CCManager::CCManager(HINSTANCE hInstance, HWND hParent)
{
	//bewaar de instance en parent window handle
	this->m_hInstance = hInstance;
	this->m_hWnd = hParent;

	//treeview object
	m_pTreeView = new CTreeView(hInstance, hParent, 0, 0, 100, 100);
	m_pTreeView->CreateTreeViewWindow();				//zet de treeview op het scherm

	//listview object
	m_pListView = new CListView(hInstance, hParent, 255, 0, 100, 100);
	m_pListView->CreateListViewWindow();				//zet de listview op het scherm

	//statusbalk object
	m_pStatusBar = new CStatusBar(hInstance, hParent);
	m_pStatusBar->CreateStatusBar();					//zet de statusbar op het scherm
	char szBuf[255];
	LoadString(m_hInstance, IDS_SB_TIMER, szBuf, 255);
	m_pStatusBar->setItemText(1, szBuf);

	//toolbalk object
	m_pToolBar = new CToolBar(hInstance, hParent);
	if ( m_pToolBar )
			m_pToolBar->CreateToolBar(10);				//zet de toolbar op het scherm
}

CCManager::~CCManager()
{
}

//resize de windows TreeView en Listview
void CCManager::Resize(WPARAM wParam, LPARAM lParam)
{
	//vraag de hoogte van de toolbalk
	int height = m_pToolBar->getHeight();

	//resize de controls mee met de window
	m_pToolBar->Resize(wParam, lParam);
	m_pStatusBar->Resize(wParam, lParam);
	m_pTreeView->setSize(0, height + 5, 300, HIWORD(lParam) - height - 24);
	m_pListView->setSize(300, height + 5, LOWORD(lParam) - 300, HIWORD(lParam) - height - 24);
}

//Zet de huidige tijd in de statusbar
void CCManager::setTime()
{
/*
	time( &ltime );										//haal de tijd op
	newtime = localtime( &ltime );						//bereken hier de locale tijd van
	m_pStatusBar->setItemText(2, asctime ( newtime ));	//zet dit als string in het tweede
														//vakje van de status balk
*/

	//nieuwe tijd functie met eigen datum klasse CDatum en tijd klasse CTijd
	string tad;
	tad += CDatum().toString();
	tad += " ";
	tad += CTijd().toString();
	m_pStatusBar->setItemText(2, tad);
}

//Zet het aantal starts in de statusbar
void CCManager::setStarts(int starts)
{
    stringstream strs;
	char szBuf[255];

	LoadString(m_hInstance, IDS_STARTS, szBuf, 255);
														//haal een string uit de string table
	strs << szBuf << starts << ends;					//maak een stringstream van de string
														//uit de string tabel en het aantal starts
	m_pStatusBar->setItemText(3, strs.str());			//zet deze stringstream in het derde
														//statusbar vakje
}

//set de timer in de statusbar
void CCManager::setTimer(char * time)
{
	m_pStatusBar->setItemText(1, time);
}

void CCManager::ToolTipProc(LPARAM lParam)
{
	//geef de parameters door naar de functie die de tooltips
	// afhandeld in de toolbar klasse
	m_pToolBar->ToolTipProc(lParam);
}

void CCManager::CControlProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, CSuperManager * sm)
{
	LPNMTVKEYDOWN info;
    stringstream strs;
	char szBuf[255], szDeadline[255], szStatus[255], szTotaaltijd[255], szNotitie[255];
	CProject * prj;
	CActiviteit * act;

	LoadString(m_hInstance, IDS_DEADLINE, szDeadline, 255);
	LoadString(m_hInstance, IDS_STATUS, szStatus, 255);
	LoadString(m_hInstance, IDS_TOTAALTIJD, szTotaaltijd, 255);
	LoadString(m_hInstance, IDS_NOTITIE, szNotitie, 255);
	
	switch (((LPNMHDR) lParam)->code)
	{
		case TVN_KEYDOWN :
			info = ((LPNMTVKEYDOWN)lParam);
			if (info->wVKey == 120)			//is F9 gedrukt
			{
				if (m_pTreeView->getSelectedActiviteit() != "") //is er een activiteit geselecteerd
				{
					act = sm->getActiviteit(m_pTreeView->getSelectedProject(), m_pTreeView->getSelectedActiviteit());
					LoadString(m_hInstance, IDS_ACTIEF + act->getStatus(), szBuf, 255);
					strs << act->getNaam() << "\n\n"
						<< szDeadline << ":\t\t" << act->getDeadLine().toString() 
						<< "\n"
						<< szStatus << ":\t\t" << szBuf 
						<< "\n"
						<< szTotaaltijd << ":\t" << act->getTotaalTijd().toString()
						<< "\n\n" << szNotitie << ":\n" << act->getNotitie() << ends;
                    MessageBox(m_hWnd, strs.str().c_str(), "PSP-Manager", 0);
				}
				else
				{
					if (m_pTreeView->getSelectedProject() != "") //is er een project geselecteerd
					{
						prj = sm->getProject(m_pTreeView->getSelectedProject());
						LoadString(m_hInstance, IDS_ACTIEF + prj->getStatus(), szBuf, 255);
						strs << prj->getNaam() << "\n\n" 
							<< szDeadline << ":\t\t" << prj->getDeadLine().toString() 
							<< "\n" 
							<< szStatus << ":\t\t" << szBuf
							<< "\n" 
							<< szTotaaltijd << ":\t" << prj->getTotaalTijd().toString()
							<< "\n\n" << szNotitie << ":\n" << prj->getNotitie() << ends;
                        MessageBox(m_hWnd, strs.str().c_str(), "PSP-Manager", 0);
					}
                }
			}
			if (info->wVKey == 116)		//F5 => refreshed de TreeView
				updateTreeView(sm);
			break;
		case TVN_SELCHANGED:
			if (m_pTreeView->TVProc(lParam))
			{
				//TreeView Project geselecteerd
			}
			else
			{
				//TreeView Activiteit geselecteerd
				m_pListView->updateListView(sm, m_pTreeView->getSelectedProject(), m_pTreeView->getSelectedActiviteit());
			}
			break;
		case LVN_ITEMCHANGED:
			//listview item geselecteerd
			m_pListView->LVProc(lParam);
			break;
	}
}

/*
HTREEITEM CCManager::TVAddProject(string naam)
{
	//voeg een project toe en krijg de handle van het item terug
	return m_pTreeView->AddProject(naam);
}

void CCManager::TVAddActiviteit(string naam, HTREEITEM hItem)
{
	//voeg een activiteit toe en geef de handle terug
	m_pTreeView->AddActiviteit(naam, hItem);
}
*/

void CCManager::updateListView(CSuperManager * sm)
{
	//vraag het geselecteerde project en activiteit op
	string project, activiteit;
	project = m_pTreeView->getSelectedProject();
	activiteit = m_pTreeView->getSelectedActiviteit();

	//ververs de Listview
	m_pListView->updateListView(sm, project, activiteit);
}


void CCManager::updateTreeView(CSuperManager * sm)
{
	//ververs de informatie in de Treeview
	m_pTreeView->UpdateTV(sm);
}

string CCManager::getSelectedProject()
{
	//vraag het geselecteerde project op
	return m_pTreeView->getSelectedProject();
}

string CCManager::getSelectedActiviteit()
{
	//vraag de geselcteerde activiteit op
	return m_pTreeView->getSelectedActiviteit();
}
