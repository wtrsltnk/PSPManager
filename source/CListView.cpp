#include "CListView.h"

/////////////////////////////////////
// Constructors / Destructors      //
/////////////////////////////////////

CListView::CListView(HINSTANCE hInstance, 
					 HWND hParent,
					 int x, int y , 
					 int nWidth ,int nHeigth)
{
	//bewaar de instance en de parent window handle
	m_hParent = hParent;
	m_hInstance = hInstance;
	
	//bewaar de positie en grootte van de listview
	//die opgegeven is in de contructor parameters
	m_x=x;
	m_y=y;
	m_nWidth=nWidth;
	m_nHeight=nHeigth;
}

CListView::~CListView()
{
}

/////////////////////////////////////
// Memberfuncties                  //
/////////////////////////////////////

void CListView::LVProc(LPARAM lParam)
{
	//MessageBox(NULL, "ListView","Bestand", MB_OK);
}

void CListView::SetHeaderColomn(string str, int cx, int iColNo)
{

	LV_COLUMN lvc;

	//vul een column structure
	lvc.mask = LVCF_SUBITEM|LVCF_TEXT|LVCF_WIDTH|LVCF_FMT;
	lvc.fmt = LVCFMT_LEFT ;
	lvc.cchTextMax = 300;
	lvc.cx = cx;
	lvc.pszText = const_cast<char *>(str.c_str());
	lvc.iSubItem = iColNo - 1;

	//voeg de column toe aan de listview
	ListView_InsertColumn(m_hListView, iColNo, &lvc);
}

void CListView::InsertRow(string str, int iRowNo)
{
	LV_ITEM lvi;

	//vul de listview item structure
	lvi.mask = LVIF_TEXT|LVIF_IMAGE|LVIF_STATE;
	lvi.state = 0;
	lvi.stateMask = -1;
	lvi.iItem = (iRowNo);
	lvi.iSubItem = 0;
	lvi.pszText = const_cast<char *>(str.c_str());

	//voeg deze toe aan de listview
	//er wordt een nieuwe rij gemaakt
	ListView_InsertItem(m_hListView, &lvi);
}

void CListView::SetItemText(int i,int iSubItem,string s)
{
	//verander of voeg text toe aan een rij
	//nieuw sub item wordt aangemaakt
	ListView_SetItemText(m_hListView, i, iSubItem, const_cast<char *>(s.c_str()) );
}

void CListView::CreateListViewWindow()
{
	char szBuf[255];

	//maak ene listview window
	 m_hListView = CreateWindowEx(WS_EX_STATICEDGE, WC_LISTVIEW, "",
		WS_VISIBLE|WS_CHILD|LVS_REPORT|LVS_SHOWSELALWAYS, 
		m_x, m_y, m_nWidth, m_nHeight, m_hParent, NULL, m_hInstance, NULL);
 
	//voeg extra style egenschappen toe
	ListView_SetExtendedListViewStyleEx(m_hListView,LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT|LVS_EX_FLATSB , 
		LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT|LVS_EX_FLATSB );
 
	//voeg een header window toe
	HWND hHeader = CreateWindow(WC_HEADER,"", HDS_HORZ|HDS_BUTTONS, m_x, m_y, m_nWidth, m_nHeight, 
		m_hListView, NULL, m_hInstance, NULL);

	//Start datum
	LoadString(m_hInstance, IDS_LV_STARTDATUM, szBuf, 255);		//laad de string uit ST
	SetHeaderColomn( szBuf, 93, 1);							//maak de column aan
	
	//Start tijd kolom
	LoadString(m_hInstance, IDS_LV_STARTTIJD, szBuf, 255);		//laad de string uit ST
	SetHeaderColomn( szBuf, 90, 2);							//maak de column aan
	
	//Stop datum
	LoadString(m_hInstance, IDS_LV_STOPDATUM, szBuf, 255);		//laad de string uit ST
	SetHeaderColomn( szBuf, 90, 3);							//maak de column aan

	//Stop tijd kolom
	LoadString(m_hInstance, IDS_LV_STOPTIJD, szBuf, 255);		//laad de string uit ST
	SetHeaderColomn( szBuf, 90, 4);							//maak de column aan

	//Totaal tijd kolom
	LoadString(m_hInstance, IDS_LV_TOTAALTIJD, szBuf, 255);		//laad de string uit ST
	SetHeaderColomn( szBuf, 90, 5);							//maak de column aan
}


void CListView::setSize(int x, int y, int nWidth, int nHeight)
{
	//verschuif de window naar nieuwe locatie en resize deze
	MoveWindow(m_hListView, x, y, nWidth, nHeight, true);
}


//HdeB: Functie om listview te update en de activiteiten te tonen.
void CListView::updateListView(CSuperManager * sm, string project, string activiteit)
{
	CActiviteit * ac;
	CProject prj;
	vector <CTijdRegistratie> tr;

	//HdeB: Maak de listview leeg
	clearListView();
	
	//HdeB: Vraag het activiteit op en plaats het in de listview
	ac = sm->getActiviteit(project, activiteit);
	if (ac != NULL)
	{
		tr = ac->getTijdRegistraties();
		for(int i=0; i < tr.size(); i++)
		{
			InsertRow(tr[i].getStartDatum().toString(), i);
			SetItemText(i, 1, tr[i].getStartTijd().toString());
			SetItemText(i, 2, tr[i].getStopDatum().toString());
			SetItemText(i, 3, tr[i].getStopTijd().toString());
			SetItemText(i, 4, tr[i].getTotaalTijd().toString());
		}
	}
}


//HdeB: Functie die de listview items verwijderd
void CListView::clearListView()
{
	ListView_DeleteAllItems(m_hListView);
}
