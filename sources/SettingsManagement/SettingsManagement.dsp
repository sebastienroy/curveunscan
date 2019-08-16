# Microsoft Developer Studio Project File - Name="SettingsManagement" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=SettingsManagement - Win32 DebugCD
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "SettingsManagement.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "SettingsManagement.mak" CFG="SettingsManagement - Win32 DebugCD"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "SettingsManagement - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "SettingsManagement - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "SettingsManagement - Win32 DebugCD" (based on "Win32 (x86) Static Library")
!MESSAGE "SettingsManagement - Win32 ReleaseCD" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/V130Spline/Dev/CURRENTVERSION/main", AWAAAAAA"
# PROP Scc_LocalPath "..\main"
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "SettingsManagement - Win32 Release"

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
# ADD CPP /nologo /G5 /MD /W3 /GR /GX /O2 /Ob2 /I ".." /I "../main" /I "..\..\ThirdParty\PaintLib\paintlib_last\paintlib\common" /I "..\..\ThirdParty\PaintLib\paintlib_last\paintlib\win\paintlib" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "__MATH_H__" /U "__MWERKS__" /U "THINK_C" /U "VMS" /U "HAVE_UNISTD_H" /U "_AMIGA" /U "__TURBOC__" /Yu"stdafx.h" /FD /c
# ADD BASE RSC /l 0x40c /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x40c /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "SettingsManagement - Win32 Debug"

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
# ADD CPP /nologo /G5 /MDd /W3 /Gm /GR /GX /ZI /Od /I ".." /I "../main" /I "..\..\ThirdParty\PaintLib\paintlib_last\paintlib\common" /I "..\..\ThirdParty\PaintLib\paintlib_last\paintlib\win\paintlib" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "__MATH_H__" /D "AFX_RESOURCE_DLL" /U "__MWERKS__" /U "THINK_C" /U "VMS" /U "HAVE_UNISTD_H" /U "_AMIGA" /U "__TURBOC__" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE RSC /l 0x40c /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x40c /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "SettingsManagement - Win32 DebugCD"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "SettingsManagement___Win32_DebugCD"
# PROP BASE Intermediate_Dir "SettingsManagement___Win32_DebugCD"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "DebugCD"
# PROP Intermediate_Dir "DebugCD/tmp"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /G5 /MDd /W3 /Gm /GR /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "__MATH_H__" /U "__MWERKS__" /U "THINK_C" /U "VMS" /U "HAVE_UNISTD_H" /U "_AMIGA" /U "__TURBOC__" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /G5 /MDd /W3 /Gm /GR /GX /ZI /Od /I ".." /I "../main" /I "..\..\ThirdParty\PaintLib\paintlib_last\paintlib\common" /I "..\..\ThirdParty\PaintLib\paintlib_last\paintlib\win\paintlib" /D "_AFXDLL" /D "__MATH_H__" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "CD_VERSION" /U "__MWERKS__" /U "THINK_C" /U "VMS" /U "HAVE_UNISTD_H" /U "_AMIGA" /U "__TURBOC__" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE RSC /l 0x40c /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x40c /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "SettingsManagement - Win32 ReleaseCD"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "SettingsManagement___Win32_ReleaseCD"
# PROP BASE Intermediate_Dir "SettingsManagement___Win32_ReleaseCD"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "ReleaseCD"
# PROP Intermediate_Dir "ReleaseCD/tmp"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /G5 /MD /W3 /GR /GX /O2 /Ob2 /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "__MATH_H__" /U "__MWERKS__" /U "THINK_C" /U "VMS" /U "HAVE_UNISTD_H" /U "_AMIGA" /U "__TURBOC__" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /G5 /MD /W3 /GR /GX /O2 /Ob2 /I ".." /I "../main" /I "..\..\ThirdParty\PaintLib\paintlib_last\paintlib\common" /I "..\..\ThirdParty\PaintLib\paintlib_last\paintlib\win\paintlib" /D "_AFXDLL" /D "__MATH_H__" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "CD_VERSION" /U "__MWERKS__" /U "THINK_C" /U "VMS" /U "HAVE_UNISTD_H" /U "_AMIGA" /U "__TURBOC__" /Yu"stdafx.h" /FD /c
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

# Name "SettingsManagement - Win32 Release"
# Name "SettingsManagement - Win32 Debug"
# Name "SettingsManagement - Win32 DebugCD"
# Name "SettingsManagement - Win32 ReleaseCD"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\AbstractSettingValue.cpp
# End Source File
# Begin Source File

SOURCE=.\CurveProPage.cpp
# End Source File
# Begin Source File

SOURCE=.\DensitoProPage.cpp
# End Source File
# Begin Source File

SOURCE=.\DoubleSettingValue.cpp
# End Source File
# Begin Source File

SOURCE=.\ExportProPage.cpp
# End Source File
# Begin Source File

SOURCE=.\IntSettingValue.cpp
# End Source File
# Begin Source File

SOURCE=.\LanguageProPage.cpp
# End Source File
# Begin Source File

SOURCE=.\PixelSettingValue.cpp
# End Source File
# Begin Source File

SOURCE=.\PromptProPage.cpp
# End Source File
# Begin Source File

SOURCE=.\SettingsManagement.rc
# End Source File
# Begin Source File

SOURCE=.\SettingsManager.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\StringSettingValue.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\AbstractSettingValue.h
# End Source File
# Begin Source File

SOURCE=.\ContinuousCurveDefaultValues.h
# End Source File
# Begin Source File

SOURCE=.\CurveProPage.h
# End Source File
# Begin Source File

SOURCE=.\DensitoPropage.h
# End Source File
# Begin Source File

SOURCE=.\DoubleSettingValue.h
# End Source File
# Begin Source File

SOURCE=.\ExportProPage.h
# End Source File
# Begin Source File

SOURCE=.\IntSettingValue.h
# End Source File
# Begin Source File

SOURCE=.\LanguageProPage.h
# End Source File
# Begin Source File

SOURCE=.\PixelSettingValue.h
# End Source File
# Begin Source File

SOURCE=.\PromptProPage.h
# End Source File
# Begin Source File

SOURCE=.\resource.h

!IF  "$(CFG)" == "SettingsManagement - Win32 Release"

# Begin Custom Build - Making HTML include file...
TargetName=SettingsManagement
InputPath=.\resource.h

"..\HelpFiles\$(TargetName).hm" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	del ..\Helpfiles\$(TargetName).hm 
	makehm ID_,IDH_,0x10000  resource.h >>"..\HelpFiles\$(TargetName).hm" 
	makehm IDM_,IDH_,0x10000 resource.h >>"..\HelpFiles\$(TargetName).hm" 
	makehm IDP_,IDH_,0x30000 resource.h >>"..\HelpFiles\$(TargetName).hm" 
	makehm IDR_,IDH_,0x20000 resource.h >>"..\HelpFiles\$(TargetName).hm" 
	makehm IDD_,IDH_,0x20000 resource.h >>"..\HelpFiles\$(TargetName).hm" 
	makehm IDW_,IDH_,0x50000 resource.h >>"..\HelpFiles\$(TargetName).hm" 
	echo.  >>"..\HelpFiles\$(TargetName).hm" 
	MakeIDH "..\HelpFiles\$(TargetName).hm" 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "SettingsManagement - Win32 Debug"

# Begin Custom Build - Making HTML include file...
TargetName=SettingsManagement
InputPath=.\resource.h

"..\HelpFiles\$(TargetName).hm" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	del ..\Helpfiles\$(TargetName).hm 
	makehm ID_,IDH_,0x10000  resource.h >>"..\HelpFiles\$(TargetName).hm" 
	makehm IDM_,IDH_,0x10000 resource.h >>"..\HelpFiles\$(TargetName).hm" 
	makehm IDP_,IDH_,0x30000 resource.h >>"..\HelpFiles\$(TargetName).hm" 
	makehm IDR_,IDH_,0x20000 resource.h >>"..\HelpFiles\$(TargetName).hm" 
	makehm IDD_,IDH_,0x20000 resource.h >>"..\HelpFiles\$(TargetName).hm" 
	makehm IDW_,IDH_,0x50000 resource.h >>"..\HelpFiles\$(TargetName).hm" 
	echo.  >>"..\HelpFiles\$(TargetName).hm" 
	MakeIDH "..\HelpFiles\$(TargetName).hm" 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "SettingsManagement - Win32 DebugCD"

# Begin Custom Build - Making HTML include file...
TargetName=SettingsManagement
InputPath=.\resource.h

"..\HelpFiles\$(TargetName).hm" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	del ..\Helpfiles\$(TargetName).hm 
	makehm ID_,IDH_,0x10000  resource.h >>"..\HelpFiles\$(TargetName).hm" 
	makehm IDM_,IDH_,0x10000 resource.h >>"..\HelpFiles\$(TargetName).hm" 
	makehm IDP_,IDH_,0x30000 resource.h >>"..\HelpFiles\$(TargetName).hm" 
	makehm IDR_,IDH_,0x20000 resource.h >>"..\HelpFiles\$(TargetName).hm" 
	makehm IDD_,IDH_,0x20000 resource.h >>"..\HelpFiles\$(TargetName).hm" 
	makehm IDW_,IDH_,0x50000 resource.h >>"..\HelpFiles\$(TargetName).hm" 
	echo.  >>"..\HelpFiles\$(TargetName).hm" 
	MakeIDH "..\HelpFiles\$(TargetName).hm" 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "SettingsManagement - Win32 ReleaseCD"

# Begin Custom Build - Making HTML include file...
TargetName=SettingsManagement
InputPath=.\resource.h

"..\HelpFiles\$(TargetName).hm" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	del ..\Helpfiles\$(TargetName).hm 
	makehm ID_,IDH_,0x10000  resource.h >>"..\HelpFiles\$(TargetName).hm" 
	makehm IDM_,IDH_,0x10000 resource.h >>"..\HelpFiles\$(TargetName).hm" 
	makehm IDP_,IDH_,0x30000 resource.h >>"..\HelpFiles\$(TargetName).hm" 
	makehm IDR_,IDH_,0x20000 resource.h >>"..\HelpFiles\$(TargetName).hm" 
	makehm IDD_,IDH_,0x20000 resource.h >>"..\HelpFiles\$(TargetName).hm" 
	makehm IDW_,IDH_,0x50000 resource.h >>"..\HelpFiles\$(TargetName).hm" 
	echo.  >>"..\HelpFiles\$(TargetName).hm" 
	MakeIDH "..\HelpFiles\$(TargetName).hm" 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\SettingsDefs.h
# End Source File
# Begin Source File

SOURCE=.\SettingsManagement.h
# End Source File
# Begin Source File

SOURCE=.\SettingsManager.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\StringSettingValue.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\Readme.txt
# End Source File
# End Target
# End Project
