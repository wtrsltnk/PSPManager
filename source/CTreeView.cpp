#include "CTreeView.h"

/////////////////////////////////////
// Constructors / Destructors      //
/////////////////////////////////////

CTreeView::CTreeView(	HINSTANCE hInstance, 
				HWND hParent, 
				int x, int y, int nWidth, int nHeight)
{
	//bewaar de instance en de parent window handle
	m_hInstance=hInstance;
	m_hParent=hParent;

	//bewaar de positie en grootte van de treeview
	//die opgegeven is in de contructor parameters
	m_x=x;
	m_y=y;
	m_nWidth=nWidth;
	m_nHeight=nHeight;
}


CTreeView::~CTreeView()
{
}

/////////////////////////////////////
// Memberfuncties                  //
/////////////////////////////////////

bool CTreeView::TVProc(LPARAM lParam)
{
	return TreeView_GetParent(m_hTreeView, TreeView_GetSelection(m_hTreeView)) == TVGN_ROOT;
}

void CTreeView::CreateTreeViewWindow()
{
	//maak en vul een imagelist
	HIMAGELIST imgList = ImageList_Create(15, 15, ILC_COLORDDB, 4, 0);
	ImageList_Add(imgList, LoadBitmap(m_hInstance, MAKEINTRESOURCE(IDB_NODES) ), NULL);

	//maak een treeview control
	m_hTreeView = CreateWindowEx(WS_EX_STATICEDGE, WC_TREEVIEW, "", 
		WS_VISIBLE|WS_CHILD|TVS_LINESATROOT|TVS_HASLINES|TVS_HASBUTTONS|TVS_SHOWSELALWAYS,
		m_x, m_y, m_nWidth, m_nHeight, m_hParent, NULL, m_hInstance, NULL);

	//voeg de imagelist toe aan de treeview control
	TreeView_SetImageList (m_hTreeView, imgList, TVSIL_NORMAL);
}

HTREEITEM CTreeView::AddNewItem(string str, HTREEITEM hParent, int status)
{
	TV_INSERTSTRUCT tvins;
	TV_ITEM tvi;

	//vul het treeview item sructure met text
	tvi.mask = TVIF_TEXT|TVIF_IMAGE|TVIF_SELECTEDIMAGE;
	tvi.pszText = const_cast<char *> (str.c_str());
	tvi.iImage = 0 + (status * 2);
	tvi.iSelectedImage = (status == 3)?6:(1 + (status * 2));

	//vul het insert structure met parent handle, treeview item
	tvins.hParent = hParent;
	tvins.hInsertAfter = TVI_LAST;
	tvins.item = tvi;

	//geef een handle terug van het nieuw aangemaakte treeview item
	return TreeView_InsertItem(m_hTreeView, &tvins);
}

void CTreeView::setSize(int x, int y, int nWidth, int nHeight)
{
	//verschuif de window naar nieuwe locatie en resize deze
	MoveWindow(m_hTreeView, x, y, nWidth, nHeight, true);
}

HTREEITEM CTreeView::AddProject(string naam, bool isActief)
{
	TV_INSERTSTRUCT tvins;
	TV_ITEM tvi;

	//vul het treeview item sructure met text
	tvi.mask = TVIF_TEXT|TVIF_IMAGE|TVIF_SELECTEDIMAGE;
	tvi.pszText = const_cast<char *> (naam.c_str());
	tvi.iImage = 0;
	tvi.iSelectedImage = 1;

	//vul het insert structure met parent handle, treeview item
	tvins.hParent = TVGN_ROOT;
	tvins.hInsertAfter = TVI_LAST;
	tvins.item = tvi;

	//geef een handle terug van het nieuw aangemaakte treeview item
	return TreeView_InsertItem(m_hTreeView, &tvins);
}

void CTreeView::AddActiviteit(string naam, HTREEITEM hParent)
{
	TV_INSERTSTRUCT tvins;
	TV_ITEM tvi;

	//vul het treeview item sructure met text
	tvi.mask = TVIF_TEXT|TVIF_IMAGE|TVIF_SELECTEDIMAGE;
	tvi.pszText = const_cast<char *> (naam.c_str());
	tvi.iImage = 2;
	tvi.iSelectedImage = 3;

	tvins.hParent = hParent;
	tvins.hInsertAfter = TVI_LAST;
	tvins.item = tvi;

	TreeView_InsertItem(m_hTreeView, &tvins);
}

void CTreeView::UpdateTV(CSuperManager * sm)
{
	string cp, ca;

	cp = getSelectedProject();
	ca = getSelectedActiviteit();
	// Vullen van de TreeView met Projecten en Activiteiten

	//MessageBox(NULL, cp.c_str(), ca.c_str(), MB_OK);

	SendMessage(m_hTreeView, TVM_DELETEITEM, 0, (LPARAM) TVI_ROOT);
	
	HTREEITEM hTreeItemProject, hTreeItemActiviteit;
	
	vector <CProject> project = sm->getProjecten();
	vector <CActiviteit> activiteit;

	for(int i=0; i< project.size(); i++)
	{
		hTreeItemProject = AddNewItem(project[i].getNaam(), TVGN_ROOT, (CDatum() < project[i].getDeadLine())?3:project[i].getStatus());
	
		activiteit = project[i].getActiviteiten();

		for(int j=0; j< activiteit.size(); j++)
		{
			hTreeItemActiviteit = AddNewItem(activiteit[j].getNaam(), hTreeItemProject, (CDatum() < activiteit[j].getDeadLine())?3:activiteit[j].getStatus());
		}
	}

	//hier de bewaarde geselecteerde items weer terug zetten.
//	setSelection(cp, ca);
}
/*
void CTreeView::setSelection(string prj, string act)
{
	TVITEM item;
	item.mask = TVIF_TEXT | TVIF_HANDLE;

	if (act != "")
	{
		item.pszText = const_cast <char*> (act.c_str());
		TreeView_GetItem(m_hTreeView, &item);
		TreeView_Select(m_hTreeView, item.hItem, TVGN_CARET);
	}
	else if (prj != "")
	{
	}
}
//*/
string CTreeView::getSelectedProject()
{
	
	HTREEITEM hItem = (HTREEITEM)SendMessage(m_hTreeView, TVM_GETNEXTITEM, TVGN_CARET, (LPARAM)&hItem);
		
	//Kijken of het gaat om een geslecteerd project of activiteit
	if(TreeView_GetParent(m_hTreeView, TreeView_GetSelection(m_hTreeView)) == TVGN_ROOT)
	{
				
		TVITEM item;
		char text[255];
		item.hItem=hItem;
		item.cchTextMax=255;
		item.pszText=text;
		item.mask = TVIF_TEXT;

		if(SendMessage(m_hTreeView, TVM_GETITEM, 0, (LPARAM)&item))
			return text;
		return "";
	}
	
	// als het geselecteerde een activiteit is -> uitzoeken welk bijbehorend project
	HTREEITEM hParent = TreeView_GetParent(m_hTreeView, TreeView_GetSelection(m_hTreeView));

	TVITEM item1;
	char text[255];
	item1.hItem=hParent;
	item1.cchTextMax=255;
	item1.pszText=text;
	item1.mask = TVIF_TEXT;

	if(SendMessage(m_hTreeView, TVM_GETITEM, 0, (LPARAM)&item1))
		return text;
	return "";
	
}

string CTreeView::getSelectedActiviteit()
{

	HTREEITEM hItem = (HTREEITEM)SendMessage(m_hTreeView, TVM_GETNEXTITEM, TVGN_CARET, (LPARAM)&hItem);
		
	
	if(TreeView_GetParent(m_hTreeView, TreeView_GetSelection(m_hTreeView)) != TVGN_ROOT)
	{
			
	
	// als TVGN_ROOT = PROJECT
	// als != TVGNROOT = ACTITITEIT

	TVITEM item;
	char text[255];
	item.hItem=hItem;
	item.cchTextMax=255;
	item.pszText=text;
	item.mask = TVIF_TEXT;

	if(SendMessage(m_hTreeView, TVM_GETITEM, 0, (LPARAM)&item))
		return text;
	return "";
	}

	return "";
}

HWND CTreeView::getHandle()
{
	return m_hTreeView;
}