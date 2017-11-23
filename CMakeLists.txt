cmake_minimum_required(VERSION 3.1)

project(psp-manager)

add_executable(psp-manager
    bc/Activiteit.cpp
    bc/Activiteit.h
    bc/Datum.cpp
    bc/Datum.h
#    bc/main.cpp
#    bc/main.h
    bc/Project.cpp
    bc/Project.h
    bc/ProjectActiviteit.cpp
    bc/ProjectActiviteit.h
    bc/ProjectManager.cpp
    bc/ProjectManager.h
    bc/SuperManager.cpp
    bc/SuperManager.h
    bc/Tijd.cpp
    bc/Tijd.h
    bc/TijdRegistratie.cpp
    bc/TijdRegistratie.h
    bc/Tijdsverschil.cpp
    bc/Tijdverschil.h
    bc/XMLManager.cpp
    bc/XMLManager.h
    resource/PSP_project.rc
    source/CActiviteitDlg.cpp
    source/CActiviteitDlg.h
    source/CCManager.cpp
    source/CCManager.h
    source/CDlgManager.cpp
    source/CDlgManager.h
    source/CInfoDlg.cpp
    source/CInfoDlg.h
    source/CListView.cpp
    source/CListView.h
    source/CMainFrame.cpp
    source/CMainFrame.h
    source/CProjectDlg.cpp
    source/CProjectDlg.h
    source/CRegistry.cpp
    source/CRegistry.h
    source/CSplashDlg.cpp
    source/CSplashDlg.h
    source/CStatusBar.cpp
    source/CStatusBar.h
    source/CToolBar.cpp
    source/CToolBar.h
    source/CTreeView.cpp
    source/CTreeView.h
    source/CWin.cpp
    source/CWin.h
    source/WinMain.cpp
    )

target_compile_features(psp-manager
    PRIVATE cxx_auto_type
    PRIVATE cxx_nullptr
    PRIVATE cxx_range_for
    )

target_link_libraries(psp-manager
    comctl32
#    htmlhelp
    )
