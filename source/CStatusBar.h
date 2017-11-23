#ifndef CSTATUSBAR_H
#define CSTATUSBAR_H

#include <windows.h>
#include "..\Resource\resource.h"
#include <string>
#include <commctrl.h>
using namespace std;

class CStatusBar
{
private:
	HWND m_hStatusBar, m_hParent;
	HINSTANCE m_hInstance;
public:
	CStatusBar(HINSTANCE, HWND);
	~CStatusBar();
	void CreateStatusBar();
	void setItemText(int, string);
	void Resize(WPARAM, LPARAM);
};
#endif