# Microsoft Developer Studio Project File - Name="CrvResFr" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=CrvResFr - Win32 DebugCD
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "CrvResFr.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "CrvResFr.mak" CFG="CrvResFr - Win32 DebugCD"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "CrvResFr - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "CrvResFr - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "CrvResFr - Win32 DebugCD" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "CrvResFr - Win32 ReleaseCD" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/V130Spline/Dev/CURRENTVERSION/main", AWAAAAAA"
# PROP Scc_LocalPath "..\main"
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "CrvResFr - Win32 Release"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release/tmp"
# PROP Ignore_Export_Lib 1
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /G5 /MD /W3 /GX /O2 /I ".." /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_MBCS" /D "_USRDLL" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x40c /d "NDEBUG"
# ADD RSC /l 0x40c /d "NDEBUG" /d "AFX_RESOURCE_DLL" /d "AFX_TARG_FRA"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 /nologo /subsystem:windows /dll /machine:I386 /noentry
# SUBTRACT LINK32 /pdb:none
# Begin Special Build Tool
TargetDir=.\Release
TargetName=CrvResFr
SOURCE="$(InputPath)"
PostBuild_Desc=Copying dll...
PostBuild_Cmds=copy $(TargetDir)\$(TargetName).dll ..\main\$(TargetDir)\$(TargetName).dll
# End Special Build Tool

!ELSEIF  "$(CFG)" == "CrvResFr - Win32 Debug"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug/tmp"
# PROP Ignore_Export_Lib 1
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /G5 /MDd /W3 /Gm /GR /GX /ZI /Od /I ".." /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_MBCS" /D "_USRDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x40c /d "_DEBUG"
# ADD RSC /l 0x40c /d "_DEBUG" /d "AFX_RESOURCE_DLL" /d "AFX_TARG_FRA"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept /noentry
# SUBTRACT LINK32 /pdb:none
# Begin Special Build Tool
TargetDir=.\Debug
TargetName=CrvResFr
SOURCE="$(InputPath)"
PostBuild_Desc=Copying dll...
PostBuild_Cmds=echo copy $(TargetDir)\$(TargetName).dll ..\main\$(TargetDir)\$(TargetName).dll	copy $(TargetDir)\$(TargetName).dll ..\main\$(TargetDir)\$(TargetName).dll
# End Special Build Tool

!ELSEIF  "$(CFG)" == "CrvResFr - Win32 DebugCD"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "CrvResFr___Win32_DebugCD"
# PROP BASE Intermediate_Dir "CrvResFr___Win32_DebugCD"
# PROP BASE Ignore_Export_Lib 1
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "DebugCD"
# PROP Intermediate_Dir "DebugCD/tmp"
# PROP Ignore_Export_Lib 1
# PROP Target_Dir ""
# ADD BASE CPP /nologo /G5 /MDd /W3 /Gm /GR /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_MBCS" /D "_USRDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /G5 /MDd /W3 /Gm /GR /GX /ZI /Od /I ".." /D "_WINDLL" /D "_USRDLL" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "CD_VERSION" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x40c /d "_DEBUG" /d "AFX_RESOURCE_DLL" /d "AFX_TARG_FRA"
# ADD RSC /l 0x40c /d "_DEBUG" /d "AFX_RESOURCE_DLL" /d "AFX_TARG_FRA"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept /noentry
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept /noentry
# SUBTRACT LINK32 /pdb:none
# Begin Special Build Tool
TargetDir=.\DebugCD
TargetName=CrvResFr
SOURCE="$(InputPath)"
PostBuild_Desc=Copying dll...
PostBuild_Cmds=copy $(TargetDir)\$(TargetName).dll ..\main\$(TargetDir)\$(TargetName).dll
# End Special Build Tool

!ELSEIF  "$(CFG)" == "CrvResFr - Win32 ReleaseCD"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "CrvResFr___Win32_ReleaseCD"
# PROP BASE Intermediate_Dir "CrvResFr___Win32_ReleaseCD"
# PROP BASE Ignore_Export_Lib 1
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "ReleaseCD"
# PROP Intermediate_Dir "ReleaseCD/tmp"
# PROP Ignore_Export_Lib 1
# PROP Target_Dir ""
# ADD BASE CPP /nologo /G5 /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_MBCS" /D "_USRDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /G5 /MD /W3 /GX /O2 /I ".." /D "NDEBUG" /D "_WINDLL" /D "_USRDLL" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "CD_VERSION" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x40c /d "NDEBUG" /d "AFX_RESOURCE_DLL" /d "AFX_TARG_FRA"
# ADD RSC /l 0x40c /d "NDEBUG" /d "AFX_RESOURCE_DLL" /d "AFX_TARG_FRA"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386 /noentry
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 /nologo /subsystem:windows /dll /machine:I386 /noentry
# SUBTRACT LINK32 /pdb:none
# Begin Special Build Tool
TargetDir=.\ReleaseCD
TargetName=CrvResFr
SOURCE="$(InputPath)"
PostBuild_Desc=Copying dll...
PostBuild_Cmds=copy $(TargetDir)\$(TargetName).dll ..\main\$(TargetDir)\$(TargetName).dll
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "CrvResFr - Win32 Release"
# Name "CrvResFr - Win32 Debug"
# Name "CrvResFr - Win32 DebugCD"
# Name "CrvResFr - Win32 ReleaseCD"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\main\CurveUnscan.rc
# ADD BASE RSC /l 0x40c /i "\Documents and Settings\MARGUIN\Mes documents\Sebastien\Curveunscan\V130Spline\Dev\CURRENTVERSION\main" /i "\CurveUnscan\V130Spline\Dev\CURRENTVERSION\main" /i "\CurveUnscan\Dev\CurrentVersion\main"
# ADD RSC /l 0x40c /i "\Documents and Settings\MARGUIN\Mes documents\Sebastien\Curveunscan\V130Spline\Dev\CURRENTVERSION\main" /i "\CurveUnscan\V130Spline\Dev\CURRENTVERSION\main" /i "\CurveUnscan\Dev\CurrentVersion\main" /i ".."
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\resource.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=..\arrow.cur
# End Source File
# Begin Source File

SOURCE=..\main\arrow.cur
# End Source File
# Begin Source File

SOURCE=..\main\res\bitmap1.bmp
# End Source File
# Begin Source File

SOURCE=..\main\res\bitmap_p.bmp
# End Source File
# Begin Source File

SOURCE=..\res\bitmap_p.bmp
# End Source File
# Begin Source File

SOURCE=..\main\res\bitmap_r.bmp
# End Source File
# Begin Source File

SOURCE=..\res\bitmap_r.bmp
# End Source File
# Begin Source File

SOURCE=..\main\res\bmp00001.bmp
# End Source File
# Begin Source File

SOURCE=..\res\bmp00001.bmp
# End Source File
# Begin Source File

SOURCE=..\main\res\bmp00002.bmp
# End Source File
# Begin Source File

SOURCE=..\res\bmp00002.bmp
# End Source File
# Begin Source File

SOURCE=..\main\res\bmp00003.bmp
# End Source File
# Begin Source File

SOURCE=..\res\bmp00003.bmp
# End Source File
# Begin Source File

SOURCE=..\main\res\bmp00004.bmp
# End Source File
# Begin Source File

SOURCE=..\res\bmp00004.bmp
# End Source File
# Begin Source File

SOURCE=..\main\res\bmp00005.bmp
# End Source File
# Begin Source File

SOURCE=..\res\bmp00005.bmp
# End Source File
# Begin Source File

SOURCE=..\main\res\bmp00006.bmp
# End Source File
# Begin Source File

SOURCE=..\res\bmp00006.bmp
# End Source File
# Begin Source File

SOURCE=..\main\res\continuo.bmp
# End Source File
# Begin Source File

SOURCE=..\res\continuo.bmp
# End Source File
# Begin Source File

SOURCE=..\main\res\cur00001.cur
# End Source File
# Begin Source File

SOURCE=..\res\cur00001.cur
# End Source File
# Begin Source File

SOURCE=..\main\res\CurveUnscan.ico
# End Source File
# Begin Source File

SOURCE=..\res\CurveUnscan.ico
# End Source File
# Begin Source File

SOURCE=..\main\res\densito.bmp
# End Source File
# Begin Source File

SOURCE=..\res\densito.bmp
# End Source File
# Begin Source File

SOURCE=..\main\res\discret.bmp
# End Source File
# Begin Source File

SOURCE=..\res\discret.bmp
# End Source File
# Begin Source File

SOURCE=..\main\res\dropper_.ico
# End Source File
# Begin Source File

SOURCE=..\res\dropper_.ico
# End Source File
# Begin Source File

SOURCE=..\main\res\dropperUs.ico
# End Source File
# Begin Source File

SOURCE=..\res\dropperUs.ico
# End Source File
# Begin Source File

SOURCE=..\main\res\ico00001.ico
# End Source File
# Begin Source File

SOURCE=..\res\ico00001.ico
# End Source File
# Begin Source File

SOURCE=..\main\res\ico00002.ico
# End Source File
# Begin Source File

SOURCE=..\res\ico00002.ico
# End Source File
# Begin Source File

SOURCE=..\main\res\idr_main.ico
# End Source File
# Begin Source File

SOURCE=..\res\idr_main.ico
# End Source File
# Begin Source File

SOURCE=..\main\res\idr_unsc.ico
# End Source File
# Begin Source File

SOURCE=..\res\idr_unsc.ico
# End Source File
# Begin Source File

SOURCE=..\main\res\mainfram.bmp
# End Source File
# Begin Source File

SOURCE=..\res\mainfram.bmp
# End Source File
# Begin Source File

SOURCE=..\main\res\manualdr.cur
# End Source File
# Begin Source File

SOURCE=..\res\manualdr.cur
# End Source File
# Begin Source File

SOURCE=..\main\res\manualdrFr.cur
# End Source File
# Begin Source File

SOURCE=..\res\manualdrFr.cur
# End Source File
# Begin Source File

SOURCE=..\main\res\pick_col.cur
# End Source File
# Begin Source File

SOURCE=..\res\pick_col.cur
# End Source File
# Begin Source File

SOURCE=..\main\res\redoicon.ico
# End Source File
# Begin Source File

SOURCE=..\res\redoicon.ico
# End Source File
# Begin Source File

SOURCE=..\main\res\rubber_c.cur
# End Source File
# Begin Source File

SOURCE=..\res\rubber_c.cur
# End Source File
# Begin Source File

SOURCE=..\main\res\spline.bmp
# End Source File
# Begin Source File

SOURCE=..\main\res\spline_add_back.ico
# End Source File
# Begin Source File

SOURCE=..\main\res\spline_add_back_us.ico
# End Source File
# Begin Source File

SOURCE=..\main\res\spline_add_front.ico
# End Source File
# Begin Source File

SOURCE=..\main\res\spline_add_front_us.ico
# End Source File
# Begin Source File

SOURCE=..\main\res\spline_add_middle.ico
# End Source File
# Begin Source File

SOURCE=..\main\res\spline_add_middle_us.ico
# End Source File
# Begin Source File

SOURCE=..\main\res\spline_modify.ico
# End Source File
# Begin Source File

SOURCE=..\main\res\spline_modify_us.ico
# End Source File
# Begin Source File

SOURCE=..\main\res\spline_remove.ico
# End Source File
# Begin Source File

SOURCE=..\main\res\spline_remove_us.ico
# End Source File
# Begin Source File

SOURCE=..\main\res\splineUs.bmp
# End Source File
# Begin Source File

SOURCE=..\res\Toolbar.bmp
# End Source File
# Begin Source File

SOURCE=..\main\res\undoicon.ico
# End Source File
# Begin Source File

SOURCE=..\res\undoicon.ico
# End Source File
# Begin Source File

SOURCE=..\main\res\UnscanDoc.ico
# End Source File
# Begin Source File

SOURCE=..\res\UnscanDoc.ico
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
