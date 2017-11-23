#ifndef CACTIVITEITDLG_H
#define CACTIVITEITDLG_H

#define WM_SETACT		WM_USER+5002

#include <windows.h>
#include "..\Resource\resource.h"
#include "..\bc\Project.h"
#include "..\bc\Activiteit.h"
#include "..\bc\Datum.h"
#include "..\bc\Tijdverschil.h"
#include <strstream>


typedef struct _act_message 
{ 
    CActiviteit * activiteit;
	string * project;
} act_message;


class CActiviteitDlg
{
private:
	HWND				m_hOwner;
	HWND				m_hActiviteit;
	HINSTANCE			m_hInstance;
	static CActiviteit	s_act;
	static string		s_prj;
	static bool			s_isedit;
	static act_message	s_sendAct;
	string				project;
public:
	CActiviteitDlg(HINSTANCE, HWND);
	~CActiviteitDlg();
	void Show(CActiviteit *, string, bool);
	static BOOL DlgProc(HWND, UINT, WPARAM, LPARAM);
	void showData(CActiviteit *, string);
	void initDlg();
};

#endif
