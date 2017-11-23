#include "CStatusBar.h"


/////////////////////////////////////
// Constructors / Destructors      //
/////////////////////////////////////

CStatusBar::CStatusBar(HINSTANCE hInstance, HWND hWnd)
{
	//bewaar de instance en de parent window handle
	m_hInstance = hInstance;
	m_hParent = hWnd;
}

CStatusBar::~CStatusBar()
{
}

/////////////////////////////////////
// Memberfuncties                  //
/////////////////////////////////////

void CStatusBar::CreateStatusBar()
{
	const int noParts = 3;
	int parts[noParts];
	
	//maak drie statusbar vakjes aan
	parts[0] = 400;
	parts[1] = parts[0] + 150;
	parts[2] = -1;
	
	//creeer de statusbar window
	m_hStatusBar = CreateStatusWindow(WS_CHILD | WS_VISIBLE, "", m_hParent, 1);

	//voeg de aangemaakte vakjes toe
	SendMessage(m_hStatusBar, SB_SETPARTS, noParts, (LPARAM)parts);
	SendMessage(m_hStatusBar, SB_SETMINHEIGHT, 16, 0);
}

void CStatusBar::Resize(WPARAM wParam, LPARAM lParam)
{
	//stuur message om de statusbar te resizen en te verplaaten
	SendMessage(m_hStatusBar, WM_SIZE, wParam, lParam);
}

void CStatusBar::setItemText(int index, string strText)
{
	//set de text in een van de statusbar vakjes
	SendMessage(m_hStatusBar, SB_SETTEXT, (WPARAM) index-1|0, (LPARAM)strText.c_str());
}
