#ifndef CMAINFRAME_H
#define CMAINFRAME_H

#define WM_SETPRJ		WM_USER+5001
#define WM_SETACT		WM_USER+5002
#define WM_SHELLNOTIFY	WM_USER+5000
#define IDI_TRAY	42
#define ID_MSHOW	421
#define ID_MHIDE	422
#define ID_MINFO	423
#define ID_MDUCK	424

#include "CWin.h"
#include "CCManager.h"
#include "CDlgManager.h"
#include "CRegistry.h"
#include "..\bc\Supermanager.h"
#include "..\Resource\resource.h"
//#include "help\htmlhelp.h"

using namespace std;

class CMainFrame : public CWin
{
private:
	HWND				hStatusBar;
	HWND				hToolBar;
	CDlgManager			* m_pDlgManager;
	CCManager			* m_pCCManager;
	CSuperManager		* m_pSuperManager;
	CRegistry			m_Registry;	
	CProject			prj;
	CActiviteit			act;
	CTijdRegistratie	tr;
	string				cp, ca;

	int aantalStarts;
	bool change;

	//systray menu en icon
	HMENU hSystray;
	NOTIFYICONDATA note;

public:
	CMainFrame();
	~CMainFrame();
	void menuProc(HWND, WPARAM);
	LRESULT MsgProc(HWND, UINT, WPARAM, LPARAM);
	void getStarts();
	bool isOpen();
	void setClose();
	CProject getNewProject();
    CProject* getSelProject();
	CActiviteit getNewActiviteit();
    CActiviteit* getSelActiviteit();
	void NieuwFile();
	void OpenFile();
	void OpslaanFile();
	void OpslaanAlsFile();
	bool OpslaanQuestion();
	void ImportFile();
	void ExportFile();

};

#endif
