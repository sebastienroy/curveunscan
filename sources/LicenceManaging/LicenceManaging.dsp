# Microsoft Developer Studio Project File - Name="LicenceManaging" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=LicenceManaging - Win32 DebugCD
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "LicenceManaging.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "LicenceManaging.mak" CFG="LicenceManaging - Win32 DebugCD"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "LicenceManaging - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "LicenceManaging - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "LicenceManaging - Win32 DebugCD" (based on "Win32 (x86) Static Library")
!MESSAGE "LicenceManaging - Win32 ReleaseCD" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/V130Spline/Dev/CURRENTVERSION/main", AWAAAAAA"
# PROP Scc_LocalPath "..\main"
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "LicenceManaging - Win32 Release"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release/tmp"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /G5 /MD /W3 /GR /GX /O2 /Ob2 /I ".." /I "../../ThirdParty" /I "..\..\ThirdParty\PaintLib\paintlib_last\paintlib\common" /I "..\..\ThirdParty\PaintLib\paintlib_last\paintlib\win\paintlib" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "__MATH_H__" /U "__MWERKS__" /U "THINK_C" /U "VMS" /U "HAVE_UNISTD_H" /U "_AMIGA" /U "__TURBOC__" /Yu"stdafx.h" /FD /c
# ADD BASE RSC /l 0x40c /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x40c /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "LicenceManaging - Win32 Debug"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug/tmp"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /G5 /MDd /W3 /Gm /GR /GX /ZI /Od /I "..\..\ThirdParty\PaintLib\paintlib_last\paintlib\common" /I "..\..\ThirdParty\PaintLib\paintlib_last\paintlib\win\paintlib" /I ".." /I "../../ThirdParty" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "__MATH_H__" /D "AFX_RESOURCE_DLL" /U "__MWERKS__" /U "THINK_C" /U "VMS" /U "HAVE_UNISTD_H" /U "_AMIGA" /U "__TURBOC__" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE RSC /l 0x40c /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "LicenceManaging - Win32 DebugCD"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "LicenceManaging___Win32_DebugCD"
# PROP BASE Intermediate_Dir "LicenceManaging___Win32_DebugCD"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "DebugCD"
# PROP Intermediate_Dir "DebugCD/tmp"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /G5 /MDd /W3 /Gm /GR /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "__MATH_H__" /U "__MWERKS__" /U "THINK_C" /U "VMS" /U "HAVE_UNISTD_H" /U "_AMIGA" /U "__TURBOC__" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /G5 /MDd /W3 /Gm /GR /GX /ZI /Od /I ".." /I "../../ThirdParty" /I "..\..\ThirdParty\PaintLib\paintlib_last\paintlib\common" /I "..\..\ThirdParty\PaintLib\paintlib_last\paintlib\win\paintlib" /D "_AFXDLL" /D "__MATH_H__" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "CD_VERSION" /U "__MWERKS__" /U "THINK_C" /U "VMS" /U "HAVE_UNISTD_H" /U "_AMIGA" /U "__TURBOC__" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "LicenceManaging - Win32 ReleaseCD"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "LicenceManaging___Win32_ReleaseCD"
# PROP BASE Intermediate_Dir "LicenceManaging___Win32_ReleaseCD"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "ReleaseCD"
# PROP Intermediate_Dir "ReleaseCD/tmp"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /G5 /MD /W3 /GR /GX /O2 /Ob2 /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "__MATH_H__" /U "__MWERKS__" /U "THINK_C" /U "VMS" /U "HAVE_UNISTD_H" /U "_AMIGA" /U "__TURBOC__" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /G5 /MD /W3 /GR /GX /O2 /Ob2 /I ".." /I "../../ThirdParty" /I "..\..\ThirdParty\PaintLib\paintlib_last\paintlib\common" /I "..\..\ThirdParty\PaintLib\paintlib_last\paintlib\win\paintlib" /D "_AFXDLL" /D "__MATH_H__" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "CD_VERSION" /U "__MWERKS__" /U "THINK_C" /U "VMS" /U "HAVE_UNISTD_H" /U "_AMIGA" /U "__TURBOC__" /Yu"stdafx.h" /FD /c
# ADD BASE RSC /l 0x40c /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x40c /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ENDIF 

# Begin Target

# Name "LicenceManaging - Win32 Release"
# Name "LicenceManaging - Win32 Debug"
# Name "LicenceManaging - Win32 DebugCD"
# Name "LicenceManaging - Win32 ReleaseCD"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\AnyFileAccessor.cpp
# End Source File
# Begin Source File

SOURCE=.\Coder.cpp
# End Source File
# Begin Source File

SOURCE=.\CoderV2.cpp
# End Source File
# Begin Source File

SOURCE=.\Crc32Dynamic.cpp
# End Source File
# Begin Source File

SOURCE=.\ExportNbInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\FirstUseInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\IntegrityCheck.cpp
# End Source File
# Begin Source File

SOURCE=.\LicenceDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\LicenceException.cpp
# End Source File
# Begin Source File

SOURCE=.\LicenceManager.cpp
# End Source File
# Begin Source File

SOURCE=.\LicenceManaging.rc

!IF  "$(CFG)" == "LicenceManaging - Win32 Release"

!ELSEIF  "$(CFG)" == "LicenceManaging - Win32 Debug"

# ADD BASE RSC /l 0x40c
# ADD RSC /l 0x409

!ELSEIF  "$(CFG)" == "LicenceManaging - Win32 DebugCD"

# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409

!ELSEIF  "$(CFG)" == "LicenceManaging - Win32 ReleaseCD"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\SecuredInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\SorryDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\StringInterface.cpp
# End Source File
# Begin Source File

SOURCE=.\WelcomeDialog.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\AnyFileAccessor.h
# End Source File
# Begin Source File

SOURCE=.\Coder.h
# End Source File
# Begin Source File

SOURCE=.\CoderV2.h
# End Source File
# Begin Source File

SOURCE=.\Crc32Dynamic.h
# End Source File
# Begin Source File

SOURCE=.\ExportNbInfo.h
# End Source File
# Begin Source File

SOURCE=.\FirstUseInfo.h
# End Source File
# Begin Source File

SOURCE=.\IntegrityCheck.h
# End Source File
# Begin Source File

SOURCE=.\LicenceDlg.h
# End Source File
# Begin Source File

SOURCE=.\LicenceException.h
# End Source File
# Begin Source File

SOURCE=.\LicenceManager.h
# End Source File
# Begin Source File

SOURCE=.\LicenceManaging.h
# End Source File
# Begin Source File

SOURCE=.\LicenceManagingResources.h
# End Source File
# Begin Source File

SOURCE=.\resource.h
# End Source File
# Begin Source File

SOURCE=.\SecuredInfo.h
# End Source File
# Begin Source File

SOURCE=.\SorryDlg.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\StringInterface.h
# End Source File
# Begin Source File

SOURCE=.\WelcomeDialog.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\res\ico00001.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon_uns.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon_unsus.ico
# End Source File
# Begin Source File

SOURCE=.\Readme.txt
# End Source File
# End Target
# End Project
