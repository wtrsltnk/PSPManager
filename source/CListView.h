#ifndef CLISTVIEW_H
#define CLISTVIEW_H

#include <string>
#include <windows.h>
#include <commctrl.h>
#include "..\Resource\resource.h"
#include "..\bc\SuperManager.h"

using namespace std;

class CListView
{
private:
	HWND			m_hListView, m_hParent;
	int				m_x, m_y, m_nWidth , m_nHeight;
	HINSTANCE		m_hInstance;
public:
	CListView(HINSTANCE, HWND,int, int, int ,int);
	~CListView();
	void LVProc(LPARAM);
	void CreateListViewWindow();
	void SetHeaderColomn(string, int, int);
	void InsertRow(string, int);
	void SetItemText(int,int,string);
	void setSize(int, int, int ,int);
	void updateListView(CSuperManager *, string, string);
	void clearListView();
};
#endif
