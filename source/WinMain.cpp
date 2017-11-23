// WinClass.cpp : Defines the entry point for the application.
//
#include "CMainFrame.h"

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
/*
	CDatum cd = CDatum();
	signed int t1 = cd.getTotaaldagen();
	CDatum cd2 = CDatum("01-06-2003");
	signed int t2 = cd2.getTotaaldagen();

	return 0;
*/
	//mk:@MSITStore:E:\NEW\MSDN\techart.chm::/html/offaut.htm

	CMainFrame app;

	if (!app.Create())
		return 0;
	
	return app.Run();

	
	return 0;
}
