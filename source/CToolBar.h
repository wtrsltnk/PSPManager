#ifndef CTOOLBAR_H
#define CTOOLBAR_H

#include <windows.h>
#include <commctrl.h>
#include "..\Resource\resource.h"
#include <tchar.h>
#include <strstream>
using namespace std;

class CToolBar
{
private:
	HWND m_hToolBar, m_hParent;
	HINSTANCE m_hInstance;
	TBBUTTON tbb[10];
	TBADDBITMAP tbab;
public:
	CToolBar(HINSTANCE, HWND);
	~CToolBar();
	void ToolTipProc(LPARAM);
	void CreateToolBar(int);
	void Resize(WPARAM, LPARAM);
	int getHeight();
};
#endif