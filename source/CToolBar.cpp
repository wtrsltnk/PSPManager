#include "CToolBar.h"


/////////////////////////////////////
// Constructors / Destructors      //
/////////////////////////////////////

CToolBar::CToolBar(HINSTANCE hInstance, HWND hWnd)
{
	//bewaar de instance en de parent window handle
	m_hInstance = hInstance;
	m_hParent = hWnd;
}

CToolBar::~CToolBar()
{
}

/////////////////////////////////////
// Memberfuncties                  //
/////////////////////////////////////

void CToolBar::CreateToolBar(int iNumBut)
{
	int iWidth, iHeight;
	const int bufSz = 23;
	char szBuf[bufSz]; 

	//zet de hoogte en breedte van de plaatjes vast
	iWidth = 24;
	iHeight = 24;
 
	//maak de toolbar windo aan
	m_hToolBar = CreateToolbarEx(m_hParent, WS_CHILD|WS_VISIBLE|TBSTYLE_FLAT|TBSTYLE_LIST|TBSTYLE_TOOLTIPS,	1002, iNumBut, 
		m_hInstance, IDB_TOOLBAR , NULL, 0, iWidth, iHeight, iWidth, iHeight, sizeof(TBBUTTON));
	
	//stuur een message om de statusbar automatisch te laten resizen
	SendMessage(m_hToolBar, TB_AUTOSIZE, 0, 0);

	for (int i = 0; i < iNumBut; i++)								//voor iedere toolbar knop
	{
		//laad een string uit de String Table
		LoadString(m_hInstance, IDS_PRJ_NIEUW + i, szBuf, bufSz); 

		//zet de eigenschappen van de toolbar knoppen
		tbb[i].fsState = TBSTATE_ENABLED;
		tbb[i].fsStyle = TBSTYLE_GROUP;
		tbb[i].idCommand = ID_PROJECT_NEW + i;
		tbb[i].dwData = 0L;
		tbb[i].iString = SendMessage(m_hToolBar, TB_ADDSTRING, 0, (LPARAM) (LPSTR) szBuf);;
	}
	
	//zet de unieke eigenschappen van de toolbar knoppen
	tbb[0].iBitmap = 0;
	tbb[1].iBitmap = 1;
	tbb[2].iBitmap = 2;
	//------------------------------------
	tbb[3].fsStyle = TBSTYLE_SEP;
	//------------------------------------
	tbb[4].iBitmap = 0;
	tbb[5].iBitmap = 1;
	tbb[6].iBitmap = 2;
	//------------------------------------
	tbb[7].fsStyle = TBSTYLE_SEP;
	//------------------------------------
	tbb[8].iBitmap = 3;
	tbb[9].iBitmap = 4;
	

	//stuur een message om de knoppen aan de toolbar toe te vpegen
	SendMessage(m_hToolBar, TB_ADDBUTTONS, (WPARAM)(UINT) iNumBut, (LPARAM)(LPTBBUTTON) tbb);
}

void CToolBar::Resize(WPARAM wParam, LPARAM lParam)
{
	//stuur message om de toolbar te resizen en te verplaaten
	SendMessage(m_hToolBar, WM_SIZE, wParam, lParam);
}

int CToolBar::getHeight()
{
	//vraag de hoogte van de toolbar op
	return HIWORD(SendMessage(m_hToolBar, TB_GETBUTTONSIZE, 0, 0));
}

//zet de tooltip texten
void CToolBar::ToolTipProc(LPARAM lParam)
{
	LPTOOLTIPTEXT lptttext;         //tooltip structure
	lptttext = (LPTOOLTIPTEXT) lParam;    //fill the structure with values
          																	//already in the lparam
	lptttext->hinst = m_hInstance;//set the value of mamber hinst in
          													   //the structure to hinstance_main.
	switch(lptttext->hdr.idFrom)    //switch for the id the called this
	{
	case ID_PROJECT_NEW:
		LoadString(m_hInstance, TT_PRJ_NIEUW, lptttext->lpszText, 32);
		break;
	case ID_PROJECT_REMOVE:
		LoadString(m_hInstance, TT_PRJ_VERWIJDEREN, lptttext->lpszText, 32);
		break;
	case ID_PROJECT_EDIT:
		LoadString(m_hInstance, TT_PRJ_BEWERKEN, lptttext->lpszText, 32);
		break;
	case ID_ACTIVITEIT_NEW:
		LoadString(m_hInstance, TT_ACT_NIEUW, lptttext->lpszText, 32);
		break;
	case ID_ACTIVITEIT_REMOVE:
		LoadString(m_hInstance, TT_ACT_VERWIJDEREN, lptttext->lpszText, 32);
		break;
	case ID_ACTIVITEIT_EDIT:
		LoadString(m_hInstance, TT_ACT_BEWERKEN, lptttext->lpszText, 32);
		break;
	case ID_TIMER_START:
		LoadString(m_hInstance, TT_TIMER_START, lptttext->lpszText, 32);
		break;
	case ID_TIMER_STOP:
		LoadString(m_hInstance, TT_TIMER_STOP, lptttext->lpszText, 32);
		break;
	}
}