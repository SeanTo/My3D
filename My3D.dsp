# Microsoft Developer Studio Project File - Name="My3D" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=My3D - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "My3D.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "My3D.mak" CFG="My3D - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "My3D - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "My3D - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=xicl6.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "My3D - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=xilink6.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "My3D - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# SUBTRACT CPP /WX
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=xilink6.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "My3D - Win32 Release"
# Name "My3D - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\AutoBase.cpp
# End Source File
# Begin Source File

SOURCE=.\Common.cpp
# End Source File
# Begin Source File

SOURCE=.\Cond1.cpp
# End Source File
# Begin Source File

SOURCE=.\Cond2.cpp
# End Source File
# Begin Source File

SOURCE=.\Cond3.cpp
# End Source File
# Begin Source File

SOURCE=.\Cond4.cpp
# End Source File
# Begin Source File

SOURCE=.\Cond5.cpp
# End Source File
# Begin Source File

SOURCE=.\Cond6.cpp
# End Source File
# Begin Source File

SOURCE=.\DataAnalyse.cpp
# End Source File
# Begin Source File

SOURCE=.\DataChart.cpp
# End Source File
# Begin Source File

SOURCE=.\DataDistribute.cpp
# End Source File
# Begin Source File

SOURCE=.\DataInput.cpp
# End Source File
# Begin Source File

SOURCE=.\DonateInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\History.cpp
# End Source File
# Begin Source File

SOURCE=.\Intersection.cpp
# End Source File
# Begin Source File

SOURCE=.\My3D.cpp
# End Source File
# Begin Source File

SOURCE=.\My3D.rc
# End Source File
# Begin Source File

SOURCE=.\My3DDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Number.cpp
# End Source File
# Begin Source File

SOURCE=.\PageG1.cpp
# End Source File
# Begin Source File

SOURCE=.\PageG3.cpp
# End Source File
# Begin Source File

SOURCE=.\PageG6.cpp
# End Source File
# Begin Source File

SOURCE=.\PageSelNum.cpp
# End Source File
# Begin Source File

SOURCE=.\PageUseBase.cpp
# End Source File
# Begin Source File

SOURCE=.\SaveOption.cpp
# End Source File
# Begin Source File

SOURCE=.\Stat1.cpp
# End Source File
# Begin Source File

SOURCE=.\Stat2.cpp
# End Source File
# Begin Source File

SOURCE=.\Stat3.cpp
# End Source File
# Begin Source File

SOURCE=.\Stat4.cpp
# End Source File
# Begin Source File

SOURCE=.\Stat5.cpp
# End Source File
# Begin Source File

SOURCE=.\Stat6.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\WinHistory.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\AutoBase.h
# End Source File
# Begin Source File

SOURCE=.\Common.h
# End Source File
# Begin Source File

SOURCE=.\Cond1.h
# End Source File
# Begin Source File

SOURCE=.\Cond2.h
# End Source File
# Begin Source File

SOURCE=.\Cond3.h
# End Source File
# Begin Source File

SOURCE=.\Cond4.h
# End Source File
# Begin Source File

SOURCE=.\Cond5.h
# End Source File
# Begin Source File

SOURCE=.\Cond6.h
# End Source File
# Begin Source File

SOURCE=.\DataAnalyse.h
# End Source File
# Begin Source File

SOURCE=.\DataChart.h
# End Source File
# Begin Source File

SOURCE=.\DataDistribute.h
# End Source File
# Begin Source File

SOURCE=.\DataInput.h
# End Source File
# Begin Source File

SOURCE=.\DonateInfo.h
# End Source File
# Begin Source File

SOURCE=.\History.h
# End Source File
# Begin Source File

SOURCE=.\Intersection.h
# End Source File
# Begin Source File

SOURCE=.\My3D.h
# End Source File
# Begin Source File

SOURCE=.\My3DDlg.h
# End Source File
# Begin Source File

SOURCE=.\Number.h
# End Source File
# Begin Source File

SOURCE=.\PageG1.h
# End Source File
# Begin Source File

SOURCE=.\PageG3.h
# End Source File
# Begin Source File

SOURCE=.\PageG6.h
# End Source File
# Begin Source File

SOURCE=.\PageSelNum.h
# End Source File
# Begin Source File

SOURCE=.\PageUseBase.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\SaveOption.h
# End Source File
# Begin Source File

SOURCE=.\Stat1.h
# End Source File
# Begin Source File

SOURCE=.\Stat2.h
# End Source File
# Begin Source File

SOURCE=.\Stat3.h
# End Source File
# Begin Source File

SOURCE=.\Stat4.h
# End Source File
# Begin Source File

SOURCE=.\Stat5.h
# End Source File
# Begin Source File

SOURCE=.\Stat6.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\WinHistory.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\My3D.ico
# End Source File
# Begin Source File

SOURCE=.\res\My3D.rc2
# End Source File
# End Group
# Begin Group "Share"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\Share\EMFC.cpp
# End Source File
# Begin Source File

SOURCE=..\Share\EMFC.h
# End Source File
# Begin Source File

SOURCE=..\Share\HyperLink.cpp
# End Source File
# Begin Source File

SOURCE=..\Share\HyperLink.h
# End Source File
# Begin Source File

SOURCE=..\Share\IniFile.cpp
# End Source File
# Begin Source File

SOURCE=..\Share\IniFile.h
# End Source File
# Begin Source File

SOURCE=..\Share\ListCtrlEx.cpp
# End Source File
# Begin Source File

SOURCE=..\Share\ListCtrlEx.h
# End Source File
# Begin Source File

SOURCE=..\Share\MyDT.cpp
# End Source File
# Begin Source File

SOURCE=..\Share\MyDT.h
# End Source File
# Begin Source File

SOURCE=..\Share\SortListCtrl.cpp
# End Source File
# Begin Source File

SOURCE=..\Share\SortListCtrl.h
# End Source File
# Begin Source File

SOURCE=..\Share\TabSheet.cpp
# End Source File
# Begin Source File

SOURCE=..\Share\TabSheet.h
# End Source File
# Begin Source File

SOURCE=..\Share\TXT.cpp
# End Source File
# Begin Source File

SOURCE=..\Share\TXT.h
# End Source File
# Begin Source File

SOURCE=..\Share\wnd.cpp
# End Source File
# Begin Source File

SOURCE=..\Share\wnd.h
# End Source File
# End Group
# Begin Group "Help"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Help\Help.chm
# End Source File
# Begin Source File

SOURCE=.\Help\WhatsNew.txt
# End Source File
# End Group
# Begin Source File

SOURCE=.\ChangeLog.txt
# End Source File
# Begin Source File

SOURCE=.\Upload\LiveUpdate.ini.txt
# End Source File
# End Target
# End Project
