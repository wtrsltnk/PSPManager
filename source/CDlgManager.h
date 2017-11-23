#ifndef CDLGMANAGER_H
#define CDLGMANAGER_H

#include <windows.h>
#include "CInfoDlg.h"
#include "CProjectDlg.h"
#include "CActiviteitDlg.h"
#include "CSplashDlg.h"
#include "..\bc\Project.h"
#include <strstream>
using namespace std;

class CDlgManager
{
private:
	HWND m_hOwner;
	HINSTANCE m_hInstance;
	CInfoDlg * m_pInfoDlg;
	CProjectDlg * m_pProjectDlg;
	CActiviteitDlg * m_pActiviteitDlg;
	CSplashDlg * m_pSplashDlg;
	OPENFILENAME open;

public:
	CDlgManager(HINSTANCE, HWND);
	~CDlgManager();
	void showInfoDlg();
	void showProjectDlg(CProject *, bool);
	void showActiviteitDlg(CActiviteit *, string, bool);
	void showSplashDlg();
	string showOpen();
	string showSave();
	string showImport();
	string showExport();
};
#endif
