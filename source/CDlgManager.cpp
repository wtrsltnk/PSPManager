#include "CDlgManager.h"

CDlgManager::CDlgManager(HINSTANCE hInstance, HWND hWnd)
{
	//bewaar parent window handle en instance
	this->m_hOwner		= hWnd;
	this->m_hInstance	= hInstance;

	//initialiseer de dialog klassen objecten
	m_pInfoDlg = new CInfoDlg(hInstance, hWnd);
	m_pProjectDlg = new CProjectDlg(hInstance, hWnd);
	m_pActiviteitDlg = new CActiviteitDlg(hInstance, hWnd);
	m_pSplashDlg = new CSplashDlg(hInstance, hWnd);
}

CDlgManager::~CDlgManager()
{
}

void CDlgManager::showInfoDlg()
{
	m_pInfoDlg->Show();										//toon info dialoog
}

void CDlgManager::showProjectDlg(CProject *temp, bool isedit)
{
	m_pProjectDlg->Show(temp, isedit);								//toon project dialoog
}

void CDlgManager::showActiviteitDlg(CActiviteit *temp, string project, bool isedit)
{
	m_pActiviteitDlg->Show(temp, project, isedit);				//toon activiteit dialoog
}

void CDlgManager::showSplashDlg()
{
	m_pSplashDlg->Show();									//toon activiteit dialoog
}



//Save en Open Dialogs.
//voor het openen, saven, importeren en exporteren van  bestanden
string CDlgManager::showOpen()
{
	OPENFILENAME ofn = {0};
	char szFile[MAX_PATH+1] =	{0};
	static char *szFilter   =	"XML Files\0*.xml\0";
	
	//specificeer de dialog box zo volledig mogelijk
	ofn.Flags             = OFN_HIDEREADONLY;
	ofn.hwndOwner         = m_hOwner;
	ofn.lpstrCustomFilter = 0;
	ofn.lpstrFile         = szFile;
	ofn.lpstrFileTitle    = 0;
	ofn.lpstrFilter       = szFilter;
	ofn.lpstrInitialDir   = 0;
	ofn.lpstrTitle        = "PSP Manager - Open...";
	ofn.lStructSize       = sizeof( OPENFILENAME );
	ofn.nMaxFile          = MAX_PATH;

	//open de dialoog
	if( GetOpenFileName( &ofn ) != 0 )
		return ofn.lpstrFile;
	
	//als het openen van de dialoog niet gelukt is, geeft een lege string terug
	return "";
}

string CDlgManager::showSave()
{
	OPENFILENAME ofn = {0};
	char szFile[MAX_PATH+1] =	{0};
	static char *szFilter   =	"XML Files\0*.xml\0";
	static char *szDefExt   =	"xml";
	
	//specificeer de dialog box zo volledig mogelijk
	ofn.Flags             = OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT;
	ofn.hwndOwner         = m_hOwner;
	ofn.lpstrCustomFilter = 0;
	ofn.lpstrFile         = szFile;
	ofn.lpstrFileTitle    = 0;
	ofn.lpstrFilter       = szFilter;
	ofn.lpstrDefExt		  = szDefExt;
	ofn.lpstrInitialDir   = 0;
	ofn.lpstrTitle        = "PSP Manager - Save...";
	ofn.lStructSize       = sizeof( OPENFILENAME );
	ofn.nMaxFile          = MAX_PATH;


	//open de dialoog
	if( GetSaveFileName( &ofn ) != 0 )
		return ofn.lpstrFile;

	//als het openen van de dialoog niet gelukt is, geeft een lege string terug
	return "";
}

string CDlgManager::showImport()
{
	OPENFILENAME ofn = {0};
	char szFile[MAX_PATH+1] =	{0};
	static char *szFilter   =	"XML Files\0*.xml\0";

	
	//specificeer de dialog box zo volledig mogelijk
	ofn.Flags             = OFN_HIDEREADONLY;
	ofn.hwndOwner         = m_hOwner;
	ofn.lpstrCustomFilter = 0;
	ofn.lpstrFile         = szFile;
	ofn.lpstrFileTitle    = 0;
	ofn.lpstrFilter       = szFilter;
	ofn.lpstrInitialDir   = 0;
	ofn.lpstrTitle        = "PSP Manager - Import...";
	ofn.lStructSize       = sizeof( OPENFILENAME );
	ofn.nMaxFile          = MAX_PATH;


	//open de dialoog
	if( GetOpenFileName( &ofn ) != 0 )
		return ofn.lpstrFile;

	//als het openen van de dialoog niet gelukt is, geeft een lege string terug
	return "";
}

string CDlgManager::showExport()
{
	OPENFILENAME ofn = {0};
	char szFile[MAX_PATH+1] =	{0};
	static char *szFilter   =	"XML Files\0*.xml\0";
	static char *szDefExt   =	"xml"; //toegevoegd om extendsie xml toe  te voegen
	
	//specificeer de dialog box zo volledig mogelijk
	ofn.Flags             = OFN_HIDEREADONLY;
	ofn.hwndOwner         = m_hOwner;
	ofn.lpstrCustomFilter = 0;
	ofn.lpstrFile         = szFile;
	ofn.lpstrFileTitle    = 0;
	ofn.lpstrFilter       = szFilter;
	ofn.lpstrDefExt		  = szDefExt; //toegevoegd om extendsie xml toe  te voegen
	ofn.lpstrInitialDir   = 0;
	ofn.lpstrTitle        = "PSP Manager - Export...";
	ofn.lStructSize       = sizeof( OPENFILENAME );
	ofn.nMaxFile          = MAX_PATH;

	//open de dialoog
	if( GetSaveFileName( &ofn ) != 0 )
		return ofn.lpstrFile;

	//als het openen van de dialoog niet gelukt is, geeft een lege string terug
	return "";
}