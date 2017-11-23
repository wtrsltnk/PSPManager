# Microsoft Developer Studio Project File - Name="PSP_manager" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=PSP_manager - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "PSP_manager.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "PSP_manager.mak" CFG="PSP_manager - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "PSP_manager - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "PSP_manager - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "PSP_manager - Win32 Release"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x413 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x413 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib /nologo /subsystem:windows /machine:I386 /out:"exe/PSP_manager.exe"

!ELSEIF  "$(CFG)" == "PSP_manager - Win32 Debug"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /FR /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x413 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x413 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib source\help\htmlhelp.lib /nologo /subsystem:windows /debug /machine:I386 /out:"exe/PSP_manager.exe" /pdbtype:sept

!ENDIF 

# Begin Target

# Name "PSP_manager - Win32 Release"
# Name "PSP_manager - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "GUI_CPP"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\source\CActiviteitDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\source\CCManager.cpp
# End Source File
# Begin Source File

SOURCE=.\source\CDlgManager.cpp
# End Source File
# Begin Source File

SOURCE=.\source\CInfoDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\source\CListView.cpp
# End Source File
# Begin Source File

SOURCE=.\source\CMainFrame.cpp
# End Source File
# Begin Source File

SOURCE=.\source\CProjectDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\source\CRegistry.cpp
# End Source File
# Begin Source File

SOURCE=.\source\CSplashDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\source\CStatusBar.cpp
# End Source File
# Begin Source File

SOURCE=.\source\CToolBar.cpp
# End Source File
# Begin Source File

SOURCE=.\source\CTreeView.cpp
# End Source File
# Begin Source File

SOURCE=.\source\CWin.cpp
# End Source File
# Begin Source File

SOURCE=.\source\WinMain.cpp
# End Source File
# End Group
# Begin Group "BC_CPP"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\bc\Activiteit.cpp
# End Source File
# Begin Source File

SOURCE=.\bc\Datum.cpp
# End Source File
# Begin Source File

SOURCE=.\bc\Project.cpp
# End Source File
# Begin Source File

SOURCE=.\bc\ProjectActiviteit.cpp
# End Source File
# Begin Source File

SOURCE=.\bc\ProjectManager.cpp
# End Source File
# Begin Source File

SOURCE=.\bc\SuperManager.cpp
# End Source File
# Begin Source File

SOURCE=.\bc\Tijd.cpp
# End Source File
# Begin Source File

SOURCE=.\bc\TijdRegistratie.cpp
# End Source File
# Begin Source File

SOURCE=.\bc\Tijdsverschil.cpp
# End Source File
# Begin Source File

SOURCE=.\bc\XMLManager.cpp
# End Source File
# End Group
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Group "GUI_H"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\source\CActiviteitDlg.h
# End Source File
# Begin Source File

SOURCE=.\source\CCManager.h
# End Source File
# Begin Source File

SOURCE=.\source\CDlgManager.h
# End Source File
# Begin Source File

SOURCE=.\source\CInfoDlg.h
# End Source File
# Begin Source File

SOURCE=.\source\CListView.h
# End Source File
# Begin Source File

SOURCE=.\source\CMainFrame.h
# End Source File
# Begin Source File

SOURCE=.\source\CProjectDlg.h
# End Source File
# Begin Source File

SOURCE=.\source\CRegistry.h
# End Source File
# Begin Source File

SOURCE=.\source\CSplashDlg.h
# End Source File
# Begin Source File

SOURCE=.\source\CStatusBar.h
# End Source File
# Begin Source File

SOURCE=.\source\CToolBar.h
# End Source File
# Begin Source File

SOURCE=.\source\CTreeView.h
# End Source File
# Begin Source File

SOURCE=.\source\CWin.h
# End Source File
# Begin Source File

SOURCE=.\resource\resource.h
# End Source File
# End Group
# Begin Group "BC_H"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\bc\Activiteit.h
# End Source File
# Begin Source File

SOURCE=.\bc\Datum.h
# End Source File
# Begin Source File

SOURCE=.\bc\main.h
# End Source File
# Begin Source File

SOURCE=.\bc\Project.h
# End Source File
# Begin Source File

SOURCE=.\bc\ProjectActiviteit.h
# End Source File
# Begin Source File

SOURCE=.\bc\ProjectManager.h
# End Source File
# Begin Source File

SOURCE=.\bc\SuperManager.h
# End Source File
# Begin Source File

SOURCE=.\bc\Tijd.h
# End Source File
# Begin Source File

SOURCE=.\bc\TijdRegistratie.h
# End Source File
# Begin Source File

SOURCE=.\bc\Tijdverschil.h
# End Source File
# Begin Source File

SOURCE=.\bc\XMLManager.h
# End Source File
# End Group
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\resource\duck.ico
# End Source File
# Begin Source File

SOURCE=.\resource\info_duck.bmp
# End Source File
# Begin Source File

SOURCE=.\resource\PSP_project.rc
# End Source File
# Begin Source File

SOURCE=.\resource\splash.bmp
# End Source File
# Begin Source File

SOURCE=.\resource\toolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\resource\tv_nodes.bmp
# End Source File
# End Group
# End Target
# End Project
