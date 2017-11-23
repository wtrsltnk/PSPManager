#ifndef CTREEVIEW_H
#define CTREEVIEW_H

#include <windows.h>
#include "..\Resource\resource.h"
#include <commctrl.h>
#include <string>
#include "..\BC\supermanager.h"

using namespace std;

class CTreeView
{
private:
	HWND m_hTreeView, m_hParent;
	int m_x, m_y, m_nWidth , m_nHeight;
	HINSTANCE m_hInstance;
public:
	CTreeView(HINSTANCE, HWND,int,int,int,int);
	~CTreeView();
	void UpdateTV(CSuperManager*);
	bool TVProc(LPARAM);
	void CreateTreeViewWindow();
	HTREEITEM AddNewItem(string, HTREEITEM, int);
	void setSize(int, int, int, int);
	HTREEITEM AddProject(string, bool);
	void AddActiviteit(string, HTREEITEM);
	string getSelectedActiviteit();
	string getSelectedProject();
//	void setSelection(string, string);
	HWND getHandle();
};
#endif
