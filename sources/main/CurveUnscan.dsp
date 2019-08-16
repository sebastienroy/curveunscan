# Microsoft Developer Studio Project File - Name="CurveUnscan" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=CurveUnscan - Win32 DebugCD
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "CurveUnscan.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "CurveUnscan.mak" CFG="CurveUnscan - Win32 DebugCD"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "CurveUnscan - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "CurveUnscan - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "CurveUnscan - Win32 DebugCD" (based on "Win32 (x86) Application")
!MESSAGE "CurveUnscan - Win32 ReleaseCD" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/V130Spline/Dev/CURRENTVERSION/main", AWAAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "CurveUnscan - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release/tmp"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /G5 /MD /W3 /GR /GX /O2 /Ob2 /I "." /I ".." /I "../../ThirdParty" /I "..\..\ThirdParty\PaintLib\paintlib_last\paintlib\common" /I "..\..\ThirdParty\PaintLib\paintlib_last\paintlib\win\paintlib" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "__MATH_H__" /U "__MWERKS__" /U "THINK_C" /U "VMS" /U "HAVE_UNISTD_H" /U "_AMIGA" /U "__TURBOC__" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x40c /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL" /d "AFX_RESOURCE_DLL" /d "AFX_TARG_ENU"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 htmlhelp.lib paintlib.lib /nologo /subsystem:windows /machine:I386 /libpath:"..\..\ThirdParty\PaintLib\paintlib_last\lib\Release"
# SUBTRACT LINK32 /nodefaultlib
# Begin Special Build Tool
WkspDir=.
TargetPath=.\Release\CurveUnscan.exe
SOURCE="$(InputPath)"
PostBuild_Desc=Generating checksum file ...
PostBuild_Cmds="$(WkspDir)\..\ChecksumGen\release\ChecksumGen.exe" "$(WkspDir)\$(TargetPath)"
# End Special Build Tool

!ELSEIF  "$(CFG)" == "CurveUnscan - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug/tmp"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /G5 /MDd /W3 /Gm /GR /GX /ZI /Od /I "." /I ".." /I "../../ThirdParty" /I "..\..\ThirdParty\PaintLib\paintlib_last\paintlib\common" /I "..\..\ThirdParty\PaintLib\paintlib_last\paintlib\win\paintlib" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "__MATH_H__" /D "AFX_RESOURCE_DLL" /U "__MWERKS__" /U "THINK_C" /U "VMS" /U "HAVE_UNISTD_H" /U "_AMIGA" /U "__TURBOC__" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x40c /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL" /d "AFX_RESOURCE_DLL" /d "AFX_TARG_ENU"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 htmlhelp.lib paintlib.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept /libpath:"..\..\ThirdParty\PaintLib\paintlib_last\lib\Debug"
# Begin Special Build Tool
WkspDir=.
TargetPath=.\Debug\CurveUnscan.exe
SOURCE="$(InputPath)"
PostBuild_Desc=Generating checksum file ...
PostBuild_Cmds="$(WkspDir)\..\ChecksumGen\release\ChecksumGen.exe" "$(WkspDir)\$(TargetPath)"
# End Special Build Tool

!ELSEIF  "$(CFG)" == "CurveUnscan - Win32 DebugCD"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "CurveUnscan___Win32_DebugCD"
# PROP BASE Intermediate_Dir "CurveUnscan___Win32_DebugCD"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "DebugCD"
# PROP Intermediate_Dir "DebugCD/tmp"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /G5 /MDd /W3 /Gm /GR /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "__MATH_H__" /U "__MWERKS__" /U "THINK_C" /U "VMS" /U "HAVE_UNISTD_H" /U "_AMIGA" /U "__TURBOC__" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /G5 /MDd /W3 /Gm /GR /GX /ZI /Od /I "." /I ".." /I "../../ThirdParty" /I "..\..\ThirdParty\PaintLib\paintlib_last\paintlib\common" /I "..\..\ThirdParty\PaintLib\paintlib_last\paintlib\win\paintlib" /D "_AFXDLL" /D "__MATH_H__" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "CD_VERSION" /U "__MWERKS__" /U "THINK_C" /U "VMS" /U "HAVE_UNISTD_H" /U "_AMIGA" /U "__TURBOC__" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL" /d "AFX_RESOURCE_DLL" /d "AFX_TARG_ENU"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL" /d "AFX_RESOURCE_DLL" /d "AFX_TARG_ENU"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 htmlhelp.lib paintlib.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept /libpath:"..\ThirdParty\PaintLib\paintlib_last\lib\Debug"
# ADD LINK32 htmlhelp.lib paintlib.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept /libpath:"..\..\ThirdParty\PaintLib\paintlib_last\lib\Debug"
# Begin Special Build Tool
WkspDir=.
TargetPath=.\DebugCD\CurveUnscan.exe
SOURCE="$(InputPath)"
PostBuild_Desc=Generating checksum file ...
PostBuild_Cmds="$(WkspDir)\..\ChecksumGen\release\ChecksumGen.exe" "$(WkspDir)\$(TargetPath)"
# End Special Build Tool

!ELSEIF  "$(CFG)" == "CurveUnscan - Win32 ReleaseCD"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "CurveUnscan___Win32_ReleaseCD"
# PROP BASE Intermediate_Dir "CurveUnscan___Win32_ReleaseCD"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "ReleaseCD"
# PROP Intermediate_Dir "ReleaseCD/tmp"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /G5 /MD /W3 /GR /GX /O2 /Ob2 /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "__MATH_H__" /U "__MWERKS__" /U "THINK_C" /U "VMS" /U "HAVE_UNISTD_H" /U "_AMIGA" /U "__TURBOC__" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /G5 /MD /W3 /GR /GX /O2 /Ob2 /I "." /I ".." /I "../../ThirdParty" /I "..\..\ThirdParty\PaintLib\paintlib_last\paintlib\common" /I "..\..\ThirdParty\PaintLib\paintlib_last\paintlib\win\paintlib" /D "_AFXDLL" /D "__MATH_H__" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "CD_VERSION" /U "__MWERKS__" /U "THINK_C" /U "VMS" /U "HAVE_UNISTD_H" /U "_AMIGA" /U "__TURBOC__" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL" /d "AFX_RESOURCE_DLL" /d "AFX_TARG_ENU"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL" /d "AFX_RESOURCE_DLL" /d "AFX_TARG_ENU"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 htmlhelp.lib paintlib.lib /nologo /subsystem:windows /machine:I386 /libpath:"..\ThirdParty\PaintLib\paintlib_last\lib\Release"
# SUBTRACT BASE LINK32 /nodefaultlib
# ADD LINK32 htmlhelp.lib paintlib.lib /nologo /subsystem:windows /machine:I386 /libpath:"..\..\ThirdParty\PaintLib\paintlib_last\lib\Release"
# SUBTRACT LINK32 /nodefaultlib
# Begin Special Build Tool
WkspDir=.
TargetPath=.\ReleaseCD\CurveUnscan.exe
SOURCE="$(InputPath)"
PostBuild_Desc=Generating checksum file ...
PostBuild_Cmds="$(WkspDir)\..\ChecksumGen\release\ChecksumGen.exe" "$(WkspDir)\$(TargetPath)"
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "CurveUnscan - Win32 Release"
# Name "CurveUnscan - Win32 Debug"
# Name "CurveUnscan - Win32 DebugCD"
# Name "CurveUnscan - Win32 ReleaseCD"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\AbstractModificationTool.cpp
# End Source File
# Begin Source File

SOURCE=.\AbstractResultDumper.cpp
# End Source File
# Begin Source File

SOURCE=.\AxeAbstractState.cpp
# End Source File
# Begin Source File

SOURCE=.\AxeDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\AxeDrawingState.cpp
# End Source File
# Begin Source File

SOURCE=.\AxePointPickingState.cpp
# End Source File
# Begin Source File

SOURCE=.\AxeWaitState.cpp
# End Source File
# Begin Source File

SOURCE=.\CompleteSequence.cpp
# End Source File
# Begin Source File

SOURCE=.\ConstructionDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\ContinuousAdvOptDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ContinuousSequence.cpp
# End Source File
# Begin Source File

SOURCE=.\CoordSequence.cpp
# End Source File
# Begin Source File

SOURCE=.\CurveKindDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\CurveUnscan.cpp
# End Source File
# Begin Source File

SOURCE=.\CurveUnscan.rc
# ADD BASE RSC /l 0x40c
# ADD RSC /l 0x40c /i ".."
# End Source File
# Begin Source File

SOURCE=.\DashMaxDistDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\DensitoDlgAbstractState.cpp
# End Source File
# Begin Source File

SOURCE=.\DensitoDlgDrawState.cpp
# End Source File
# Begin Source File

SOURCE=.\DensitoDlgPickState.cpp
# End Source File
# Begin Source File

SOURCE=.\DensitoDlgWaitState.cpp
# End Source File
# Begin Source File

SOURCE=.\DensitometryDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\DensitoPeriodDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\DensitoPreviewWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\DensitoSequence.cpp
# End Source File
# Begin Source File

SOURCE=.\DiscreteDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\DiscreteSequence.cpp
# End Source File
# Begin Source File

SOURCE=.\FileResultDumper.cpp
# End Source File
# Begin Source File

SOURCE=.\GenesisDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\HandModificationDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\LimitDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\PenModificationTool.cpp
# End Source File
# Begin Source File

SOURCE=.\PeriodDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\PreviewDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\RubberModificationTool.cpp
# End Source File
# Begin Source File

SOURCE=.\SaveCurveDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\SavePromptDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ScannerManager.cpp
# End Source File
# Begin Source File

SOURCE=.\SeparatorDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\Sequence.cpp
# End Source File
# Begin Source File

SOURCE=.\SplineDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\SplineDlgAbstractTool.cpp
# End Source File
# Begin Source File

SOURCE=.\SplineDlgAddBackTool.cpp
# End Source File
# Begin Source File

SOURCE=.\SplineDlgAddFrontTool.cpp
# End Source File
# Begin Source File

SOURCE=.\SplineDlgAddMiddleTool.cpp
# End Source File
# Begin Source File

SOURCE=.\SplineDlgModifyTool.cpp
# End Source File
# Begin Source File

SOURCE=.\SplineDlgRemoveTool.cpp
# End Source File
# Begin Source File

SOURCE=.\SplinePeriodDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\SplineSequence.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\StringResultDumper.cpp
# End Source File
# Begin Source File

SOURCE=.\UnscanDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\UnscanView.cpp
# End Source File
# Begin Source File

SOURCE=.\ValueEdit.cpp
# End Source File
# Begin Source File

SOURCE=.\WinBmpEx.cpp
# End Source File
# Begin Source File

SOURCE=.\ZoomCombo.cpp
# End Source File
# Begin Source File

SOURCE=.\ZoomDialog.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\AbstractModificationTool.h
# End Source File
# Begin Source File

SOURCE=.\AbstractResultDumper.h
# End Source File
# Begin Source File

SOURCE=.\AxeAbstractState.h
# End Source File
# Begin Source File

SOURCE=.\AxeDialog.h
# End Source File
# Begin Source File

SOURCE=.\AxeDrawingState.h
# End Source File
# Begin Source File

SOURCE=.\AxePointPickingState.h
# End Source File
# Begin Source File

SOURCE=.\AxeWaitState.h
# End Source File
# Begin Source File

SOURCE=.\CompleteSequence.h
# End Source File
# Begin Source File

SOURCE=.\ConstructionDialog.h
# End Source File
# Begin Source File

SOURCE=.\ContinuousAdvOptDlg.h
# End Source File
# Begin Source File

SOURCE=.\ContinuousSequence.h
# End Source File
# Begin Source File

SOURCE=.\CoordSequence.h
# End Source File
# Begin Source File

SOURCE=.\CurveKindDialog.h
# End Source File
# Begin Source File

SOURCE=.\CurveUnscan.h
# End Source File
# Begin Source File

SOURCE=.\DashMaxDistDialog.h
# End Source File
# Begin Source File

SOURCE=.\DensitoDlgAbstractState.h
# End Source File
# Begin Source File

SOURCE=.\DensitoDlgDrawState.h
# End Source File
# Begin Source File

SOURCE=.\DensitoDlgPickState.h
# End Source File
# Begin Source File

SOURCE=.\DensitoDlgWaitState.h
# End Source File
# Begin Source File

SOURCE=.\DensitometryDialog.h
# End Source File
# Begin Source File

SOURCE=.\DensitoPeriodDialog.h
# End Source File
# Begin Source File

SOURCE=.\DensitoPreviewWnd.h
# End Source File
# Begin Source File

SOURCE=.\DensitoSequence.h
# End Source File
# Begin Source File

SOURCE=.\DiscreteDialog.h
# End Source File
# Begin Source File

SOURCE=.\DiscreteSequence.h
# End Source File
# Begin Source File

SOURCE=.\DrawParameters.h
# End Source File
# Begin Source File

SOURCE=.\enums.h
# End Source File
# Begin Source File

SOURCE=.\FileResultDumper.h
# End Source File
# Begin Source File

SOURCE=.\GenesisDialog.h
# End Source File
# Begin Source File

SOURCE=.\HandModificationDialog.h
# End Source File
# Begin Source File

SOURCE=.\LimitDialog.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\PenModificationTool.h
# End Source File
# Begin Source File

SOURCE=.\PeriodDialog.h
# End Source File
# Begin Source File

SOURCE=.\PreviewDialog.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h

!IF  "$(CFG)" == "CurveUnscan - Win32 Release"

# Begin Custom Build - Making HTML include file...
TargetName=CurveUnscan
InputPath=.\Resource.h

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

!ELSEIF  "$(CFG)" == "CurveUnscan - Win32 Debug"

# Begin Custom Build - Making HTML include file...
TargetName=CurveUnscan
InputPath=.\Resource.h

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

!ELSEIF  "$(CFG)" == "CurveUnscan - Win32 DebugCD"

# Begin Custom Build - Making HTML include file...
TargetName=CurveUnscan
InputPath=.\Resource.h

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

!ELSEIF  "$(CFG)" == "CurveUnscan - Win32 ReleaseCD"

# Begin Custom Build - Making HTML include file...
TargetName=CurveUnscan
InputPath=.\Resource.h

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

SOURCE=.\RubberModificationTool.h
# End Source File
# Begin Source File

SOURCE=.\SaveCurveDialog.h
# End Source File
# Begin Source File

SOURCE=.\SavePromptDlg.h
# End Source File
# Begin Source File

SOURCE=.\ScannerManager.h
# End Source File
# Begin Source File

SOURCE=.\SeparatorDialog.h
# End Source File
# Begin Source File

SOURCE=.\Sequence.h
# End Source File
# Begin Source File

SOURCE=.\SplineDialog.h
# End Source File
# Begin Source File

SOURCE=.\SplineDlgAbstractTool.h
# End Source File
# Begin Source File

SOURCE=.\SplineDlgAddBackTool.h
# End Source File
# Begin Source File

SOURCE=.\SplineDlgAddFrontTool.h
# End Source File
# Begin Source File

SOURCE=.\SplineDlgAddMiddleTool.h
# End Source File
# Begin Source File

SOURCE=.\SplineDlgModifyTool.h
# End Source File
# Begin Source File

SOURCE=.\SplineDlgRemoveTool.h
# End Source File
# Begin Source File

SOURCE=.\SplinePeriodDialog.h
# End Source File
# Begin Source File

SOURCE=.\SplineSequence.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\StringResultDumper.h
# End Source File
# Begin Source File

SOURCE=.\UnscanDoc.h
# End Source File
# Begin Source File

SOURCE=.\UnscanView.h
# End Source File
# Begin Source File

SOURCE=.\ValueEdit.h
# End Source File
# Begin Source File

SOURCE=.\WinBmpEx.h
# End Source File
# Begin Source File

SOURCE=.\ZoomCombo.h
# End Source File
# Begin Source File

SOURCE=.\ZoomDialog.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\bitmap_p.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap_r.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00001.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00002.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00003.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00004.bmp
# End Source File
# Begin Source File

SOURCE=.\res\continuo.bmp
# End Source File
# Begin Source File

SOURCE=.\res\CurveUnscan.ico
# End Source File
# Begin Source File

SOURCE=.\res\CurveUnscan.rc2
# End Source File
# Begin Source File

SOURCE=.\res\discret.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ico00001.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00002.ico
# End Source File
# Begin Source File

SOURCE=.\res\idr_main.ico
# End Source File
# Begin Source File

SOURCE=.\res\idr_unsc.ico
# End Source File
# Begin Source File

SOURCE=.\res\mainfram.bmp
# End Source File
# Begin Source File

SOURCE=.\res\redo.bmp
# End Source File
# Begin Source File

SOURCE=.\res\redoicon.ico
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\undo.bmp
# End Source File
# Begin Source File

SOURCE=.\res\undoicon.ico
# End Source File
# Begin Source File

SOURCE=.\res\UnscanDoc.ico
# End Source File
# End Group
# Begin Source File

SOURCE=..\HelpFiles\French\CurveUnscan.hhp

!IF  "$(CFG)" == "CurveUnscan - Win32 Release"

USERDEP__CURVE="resource.h"	"..\Helpfiles\$(TargetName).hm"	"..\Helpfiles\SettingsManagement.hm"	
# Begin Custom Build - Making HTML help file...
OutDir=.\Release
TargetName=CurveUnscan
InputPath=..\HelpFiles\French\CurveUnscan.hhp
InputName=CurveUnscan

"..\HelpFiles\French\$(InputName).chm" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	hhc.exe ..\HelpFiles\French\$(InputName).hhp 
	echo. 
	copy ..\HelpFiles\French\$(InputName).chm $(OutDir)\$(InputName).chm 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "CurveUnscan - Win32 Debug"

USERDEP__CURVE="resource.h"	"..\Helpfiles\$(TargetName).hm"	"..\Helpfiles\SettingsManagement.hm"	
# Begin Custom Build - Making HTML help file...
OutDir=.\Debug
TargetName=CurveUnscan
InputPath=..\HelpFiles\French\CurveUnscan.hhp
InputName=CurveUnscan

"..\HelpFiles\French\$(InputName).chm" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	hhc.exe ..\HelpFiles\French\$(InputName).hhp 
	echo. 
	copy ..\HelpFiles\French\$(InputName).chm $(OutDir)\$(InputName).chm 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "CurveUnscan - Win32 DebugCD"

USERDEP__CURVE="resource.h"	"..\Helpfiles\$(TargetName).hm"	"..\Helpfiles\SettingsManagement.hm"	
# Begin Custom Build - Making HTML help file...
OutDir=.\DebugCD
TargetName=CurveUnscan
InputPath=..\HelpFiles\French\CurveUnscan.hhp
InputName=CurveUnscan

"..\HelpFiles\French\$(InputName).chm" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	hhc.exe ..\HelpFiles\French\$(InputName).hhp 
	echo. 
	copy ..\HelpFiles\French\$(InputName).chm $(OutDir)\$(InputName).chm 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "CurveUnscan - Win32 ReleaseCD"

USERDEP__CURVE="resource.h"	"..\Helpfiles\$(TargetName).hm"	"..\Helpfiles\SettingsManagement.hm"	
# Begin Custom Build - Making HTML help file...
OutDir=.\ReleaseCD
TargetName=CurveUnscan
InputPath=..\HelpFiles\French\CurveUnscan.hhp
InputName=CurveUnscan

"..\HelpFiles\French\$(InputName).chm" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	hhc.exe ..\HelpFiles\French\$(InputName).hhp 
	echo. 
	copy ..\HelpFiles\French\$(InputName).chm $(OutDir)\$(InputName).chm 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\HelpFiles\English\CurveUnscanUs.hhp

!IF  "$(CFG)" == "CurveUnscan - Win32 Release"

USERDEP__CURVEU="resource.h"	"..\Helpfiles\$(TargetName).hm"	"..\Helpfiles\SettingsManagement.hm"	
# Begin Custom Build - Making HTML help file...
OutDir=.\Release
TargetName=CurveUnscan
InputPath=..\HelpFiles\English\CurveUnscanUs.hhp
InputName=CurveUnscanUs

"..\HelpFiles\English\$(InputName).chm" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	hhc.exe ..\HelpFiles\English\$(InputName).hhp 
	echo. 
	copy ..\HelpFiles\English\$(InputName).chm $(OutDir)\$(InputName).chm 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "CurveUnscan - Win32 Debug"

USERDEP__CURVEU="resource.h"	"..\Helpfiles\$(TargetName).hm"	"..\Helpfiles\SettingsManagement.hm"	
# Begin Custom Build - Making HTML help file...
OutDir=.\Debug
TargetName=CurveUnscan
InputPath=..\HelpFiles\English\CurveUnscanUs.hhp
InputName=CurveUnscanUs

"..\HelpFiles\English\$(InputName).chm" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	hhc.exe ..\HelpFiles\English\$(InputName).hhp 
	echo. 
	copy ..\HelpFiles\English\$(InputName).chm $(OutDir)\$(InputName).chm 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "CurveUnscan - Win32 DebugCD"

USERDEP__CURVEU="resource.h"	"..\Helpfiles\$(TargetName).hm"	"..\Helpfiles\SettingsManagement.hm"	
# Begin Custom Build - Making HTML help file...
OutDir=.\DebugCD
TargetName=CurveUnscan
InputPath=..\HelpFiles\English\CurveUnscanUs.hhp
InputName=CurveUnscanUs

"..\HelpFiles\English\$(InputName).chm" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	hhc.exe ..\HelpFiles\English\$(InputName).hhp 
	echo. 
	copy ..\HelpFiles\English\$(InputName).chm $(OutDir)\$(InputName).chm 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "CurveUnscan - Win32 ReleaseCD"

USERDEP__CURVEU="resource.h"	"..\Helpfiles\$(TargetName).hm"	"..\Helpfiles\SettingsManagement.hm"	
# Begin Custom Build - Making HTML help file...
OutDir=.\ReleaseCD
TargetName=CurveUnscan
InputPath=..\HelpFiles\English\CurveUnscanUs.hhp
InputName=CurveUnscanUs

"..\HelpFiles\English\$(InputName).chm" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	hhc.exe ..\HelpFiles\English\$(InputName).hhp 
	echo. 
	copy ..\HelpFiles\English\$(InputName).chm $(OutDir)\$(InputName).chm 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# Begin Source File

SOURCE=.\WhatIsNew.txt
# End Source File
# End Target
# End Project
