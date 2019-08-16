# Microsoft Developer Studio Project File - Name="Dm" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=Dm - Win32 DebugCD
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Dm.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Dm.mak" CFG="Dm - Win32 DebugCD"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Dm - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "Dm - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "Dm - Win32 DebugCD" (based on "Win32 (x86) Static Library")
!MESSAGE "Dm - Win32 ReleaseCD" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/V130Spline/Dev/CURRENTVERSION/main", AWAAAAAA"
# PROP Scc_LocalPath "..\main"
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Dm - Win32 Release"

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
# ADD CPP /nologo /G5 /MD /W3 /GR /GX /O2 /Ob2 /I ".." /I "../main" /I "..\..\ThirdParty\PaintLib\paintlib_last\paintlib\common" /I "..\..\ThirdParty\PaintLib\paintlib_last\paintlib\win\paintlib" /I "../../ThirdParty" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "__MATH_H__" /U "__MWERKS__" /U "THINK_C" /U "VMS" /U "HAVE_UNISTD_H" /U "_AMIGA" /U "__TURBOC__" /Yu"stdafx.h" /FD /c
# ADD BASE RSC /l 0x40c /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x40c /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "Dm - Win32 Debug"

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
# ADD CPP /nologo /G5 /MDd /W3 /Gm /GR /GX /ZI /Od /I ".." /I "../main" /I "..\..\ThirdParty\PaintLib\paintlib_last\paintlib\common" /I "..\..\ThirdParty\PaintLib\paintlib_last\paintlib\win\paintlib" /I "../../ThirdParty" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "__MATH_H__" /D "AFX_RESOURCE_DLL" /U "__MWERKS__" /U "THINK_C" /U "VMS" /U "HAVE_UNISTD_H" /U "_AMIGA" /U "__TURBOC__" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE RSC /l 0x40c /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x40c /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "Dm - Win32 DebugCD"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Dm___Win32_DebugCD"
# PROP BASE Intermediate_Dir "Dm___Win32_DebugCD"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "DebugCD"
# PROP Intermediate_Dir "DebugCD/tmp"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /G5 /MDd /W3 /Gm /GR /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "__MATH_H__" /U "__MWERKS__" /U "THINK_C" /U "VMS" /U "HAVE_UNISTD_H" /U "_AMIGA" /U "__TURBOC__" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /G5 /MDd /W3 /Gm /GR /GX /ZI /Od /I ".." /I "../main" /I "..\..\ThirdParty\PaintLib\paintlib_last\paintlib\common" /I "..\..\ThirdParty\PaintLib\paintlib_last\paintlib\win\paintlib" /I "../../ThirdParty" /D "_AFXDLL" /D "__MATH_H__" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "CD_VERSION" /U "__MWERKS__" /U "THINK_C" /U "VMS" /U "HAVE_UNISTD_H" /U "_AMIGA" /U "__TURBOC__" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE RSC /l 0x40c /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x40c /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "Dm - Win32 ReleaseCD"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Dm___Win32_ReleaseCD"
# PROP BASE Intermediate_Dir "Dm___Win32_ReleaseCD"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "ReleaseCD"
# PROP Intermediate_Dir "ReleaseCD/tmp"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /G5 /MD /W3 /GR /GX /O2 /Ob2 /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "__MATH_H__" /U "__MWERKS__" /U "THINK_C" /U "VMS" /U "HAVE_UNISTD_H" /U "_AMIGA" /U "__TURBOC__" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /G5 /MD /W3 /GR /GX /O2 /Ob2 /I ".." /I "../main" /I "..\..\ThirdParty\PaintLib\paintlib_last\paintlib\common" /I "..\..\ThirdParty\PaintLib\paintlib_last\paintlib\win\paintlib" /I "../../ThirdParty" /D "_AFXDLL" /D "__MATH_H__" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "CD_VERSION" /U "__MWERKS__" /U "THINK_C" /U "VMS" /U "HAVE_UNISTD_H" /U "_AMIGA" /U "__TURBOC__" /Yu"stdafx.h" /FD /c
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

# Name "Dm - Win32 Release"
# Name "Dm - Win32 Debug"
# Name "Dm - Win32 DebugCD"
# Name "Dm - Win32 ReleaseCD"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\24BitsBmpReader.cpp
# End Source File
# Begin Source File

SOURCE=.\AbstractBmpReader.cpp
# End Source File
# Begin Source File

SOURCE=.\AbstractThicknessCorrector.cpp
# End Source File
# Begin Source File

SOURCE=.\Axe.cpp
# End Source File
# Begin Source File

SOURCE=.\BezierCurve.cpp
# End Source File
# Begin Source File

SOURCE=.\BezierNode.cpp
# End Source File
# Begin Source File

SOURCE=.\BezierQuickDraw.cpp
# End Source File
# Begin Source File

SOURCE=.\BezierSegment.cpp
# End Source File
# Begin Source File

SOURCE=.\BmpManager.cpp
# End Source File
# Begin Source File

SOURCE=.\Color256BmpReader.cpp
# End Source File
# Begin Source File

SOURCE=.\ColorScale.cpp
# End Source File
# Begin Source File

SOURCE=.\ContinuousCurve.cpp
# End Source File
# Begin Source File

SOURCE=.\ContinuousResults.cpp
# End Source File
# Begin Source File

SOURCE=.\CoordSyst.cpp
# End Source File
# Begin Source File

SOURCE=.\Curve.cpp
# End Source File
# Begin Source File

SOURCE=.\CurveElement.cpp
# End Source File
# Begin Source File

SOURCE=.\DashedSnail.cpp
# End Source File
# Begin Source File

SOURCE=.\DensityCurve.cpp
# End Source File
# Begin Source File

SOURCE=.\DensityResults.cpp
# End Source File
# Begin Source File

SOURCE=.\DensityResultsProcessor.cpp
# End Source File
# Begin Source File

SOURCE=.\DiscreteCurve.cpp
# End Source File
# Begin Source File

SOURCE=.\DiscreteResults.cpp
# End Source File
# Begin Source File

SOURCE=.\FlatThicknessCorrector.cpp
# End Source File
# Begin Source File

SOURCE=.\Limit.cpp
# End Source File
# Begin Source File

SOURCE=.\LogicPoint.cpp
# End Source File
# Begin Source File

SOURCE=.\MonochromaticBmpReader.cpp
# End Source File
# Begin Source File

SOURCE=.\PartialCurve.cpp
# End Source File
# Begin Source File

SOURCE=.\RealColorBmpReader.cpp
# End Source File
# Begin Source File

SOURCE=.\RedrawPart.cpp
# End Source File
# Begin Source File

SOURCE=.\Results.cpp
# End Source File
# Begin Source File

SOURCE=.\ScalePoint.cpp
# End Source File
# Begin Source File

SOURCE=.\SimpleSnail.cpp
# End Source File
# Begin Source File

SOURCE=.\SmartThicknessCorrector.cpp
# End Source File
# Begin Source File

SOURCE=.\SnailAlgorithm.cpp
# End Source File
# Begin Source File

SOURCE=.\SplineCurve.cpp
# End Source File
# Begin Source File

SOURCE=.\SplineNode.cpp
# End Source File
# Begin Source File

SOURCE=.\SplineResults.cpp
# End Source File
# Begin Source File

SOURCE=.\SplineSegment.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\24BitsBmpReader.h
# End Source File
# Begin Source File

SOURCE=.\AbstractBmpReader.h
# End Source File
# Begin Source File

SOURCE=.\AbstractThicknessCorrector.h
# End Source File
# Begin Source File

SOURCE=.\Axe.h
# End Source File
# Begin Source File

SOURCE=.\BezierCurve.h
# End Source File
# Begin Source File

SOURCE=.\BezierNode.h
# End Source File
# Begin Source File

SOURCE=.\BezierQuickDraw.h
# End Source File
# Begin Source File

SOURCE=.\BezierSegment.h
# End Source File
# Begin Source File

SOURCE=.\BmpManager.h
# End Source File
# Begin Source File

SOURCE=.\Color256BmpReader.h
# End Source File
# Begin Source File

SOURCE=.\ColorScale.h
# End Source File
# Begin Source File

SOURCE=.\ContinuousCurve.h
# End Source File
# Begin Source File

SOURCE=.\ContinuousResults.h
# End Source File
# Begin Source File

SOURCE=.\CoordSyst.h
# End Source File
# Begin Source File

SOURCE=.\Curve.h
# End Source File
# Begin Source File

SOURCE=.\CurveElement.h
# End Source File
# Begin Source File

SOURCE=.\DashedSnail.h
# End Source File
# Begin Source File

SOURCE=.\DensityCurve.h
# End Source File
# Begin Source File

SOURCE=.\DensityResults.h
# End Source File
# Begin Source File

SOURCE=.\DensityResultsProcessor.h
# End Source File
# Begin Source File

SOURCE=.\DiscreteCurve.h
# End Source File
# Begin Source File

SOURCE=.\DiscreteResults.h
# End Source File
# Begin Source File

SOURCE=.\FlatThicknessCorrector.h
# End Source File
# Begin Source File

SOURCE=.\Limit.h
# End Source File
# Begin Source File

SOURCE=.\LogicPoint.h
# End Source File
# Begin Source File

SOURCE=.\MonochromaticBmpReader.h
# End Source File
# Begin Source File

SOURCE=.\PartialCurve.h
# End Source File
# Begin Source File

SOURCE=.\RealColorBmpReader.h
# End Source File
# Begin Source File

SOURCE=.\RedrawPart.h
# End Source File
# Begin Source File

SOURCE=.\Results.h
# End Source File
# Begin Source File

SOURCE=.\ScalePoint.h
# End Source File
# Begin Source File

SOURCE=.\SimpleSnail.h
# End Source File
# Begin Source File

SOURCE=.\SmartThicknessCorrector.h
# End Source File
# Begin Source File

SOURCE=.\SnailAlgorithm.h
# End Source File
# Begin Source File

SOURCE=.\SplineCurve.h
# End Source File
# Begin Source File

SOURCE=.\SplineNode.h
# End Source File
# Begin Source File

SOURCE=.\SplineResults.h
# End Source File
# Begin Source File

SOURCE=.\SplineSegment.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\Readme.txt
# End Source File
# End Target
# End Project
