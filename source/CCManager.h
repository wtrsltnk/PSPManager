#ifndef CCMANAGER_H
#define CCMANAGER_H

#include <windows.h>
#include "CListView.h"
#include "CTreeView.h"
#include "CStatusBar.h"
#include "CToolBar.h"
#include <time.h>
using namespace std;

class CCManager
{
private:
	HWND m_hWnd;
	HINSTANCE m_hInstance;
	CTreeView * m_pTreeView;
	CListView * m_pListView;
	CStatusBar * m_pStatusBar;
	CToolBar * m_pToolBar;
	struct tm *newtime;
//	CTime *newtime;
//	CDate *newdate;
	long ltime;
public:
	CCManager(HINSTANCE, HWND);
	~CCManager();
	void ToolTipProc(LPARAM);
	void CControlProc(HWND, UINT, WPARAM, LPARAM, CSuperManager *);
	void Resize(WPARAM, LPARAM);
	void setTime();
	void setStarts(int);
	void setTimer(char *);
//	HTREEITEM TVAddProject(string);
//	void TVAddActiviteit(string, HTREEITEM);
	void updateListView(CSuperManager *);
	void updateTreeView(CSuperManager *);
	string getSelectedProject();
	string getSelectedActiviteit();

	//test functie, kan verwijderd worden als de bussniss class toegevoegd wordt
	//void setControlsText();
};
#endif
