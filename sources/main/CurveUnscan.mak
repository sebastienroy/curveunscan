# Microsoft Developer Studio Generated NMAKE File, Based on CurveUnscan.dsp
!IF "$(CFG)" == ""
CFG=CurveUnscan - Win32 Debug
!MESSAGE No configuration specified. Defaulting to CurveUnscan - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "CurveUnscan - Win32 Release" && "$(CFG)" != "CurveUnscan - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "CurveUnscan.mak" CFG="CurveUnscan - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "CurveUnscan - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "CurveUnscan - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "CurveUnscan - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release/tmp
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : ".\HelpFiles\French\CurveUnscan.chm" ".\HelpFiles\CurveUnscan.hm" "$(OUTDIR)\CurveUnscan.exe"

!ELSE 

ALL : "paintlib - Win32 Release" "Utilities - Win32 Release" "LicenceManaging - Win32 Release" "HelpSystem - Win32 Release" ".\HelpFiles\French\CurveUnscan.chm" ".\HelpFiles\CurveUnscan.hm" "$(OUTDIR)\CurveUnscan.exe"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"HelpSystem - Win32 ReleaseCLEAN" "LicenceManaging - Win32 ReleaseCLEAN" "Utilities - Win32 ReleaseCLEAN" "paintlib - Win32 ReleaseCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\AbstractBmpReader.obj"
	-@erase "$(INTDIR)\AbstractModificationTool.obj"
	-@erase "$(INTDIR)\AbstractResultDumper.obj"
	-@erase "$(INTDIR)\AbstractThicknessCorrector.obj"
	-@erase "$(INTDIR)\Axe.obj"
	-@erase "$(INTDIR)\AxeAbstractState.obj"
	-@erase "$(INTDIR)\AxeDialog.obj"
	-@erase "$(INTDIR)\AxeDrawingState.obj"
	-@erase "$(INTDIR)\AxePointPickingState.obj"
	-@erase "$(INTDIR)\AxeWaitState.obj"
	-@erase "$(INTDIR)\BmpManager.obj"
	-@erase "$(INTDIR)\Color256BmpReader.obj"
	-@erase "$(INTDIR)\CompleteSequence.obj"
	-@erase "$(INTDIR)\ConstructionDialog.obj"
	-@erase "$(INTDIR)\ContinuousAdvOptDlg.obj"
	-@erase "$(INTDIR)\ContinuousCurve.obj"
	-@erase "$(INTDIR)\ContinuousResults.obj"
	-@erase "$(INTDIR)\ContinuousSequence.obj"
	-@erase "$(INTDIR)\CoordSequence.obj"
	-@erase "$(INTDIR)\CoordSyst.obj"
	-@erase "$(INTDIR)\Curve.obj"
	-@erase "$(INTDIR)\CurveElement.obj"
	-@erase "$(INTDIR)\CurveKindDialog.obj"
	-@erase "$(INTDIR)\CurveUnscan.obj"
	-@erase "$(INTDIR)\CurveUnscan.pch"
	-@erase "$(INTDIR)\CurveUnscan.res"
	-@erase "$(INTDIR)\DiscreteCurve.obj"
	-@erase "$(INTDIR)\DiscreteDialog.obj"
	-@erase "$(INTDIR)\DiscreteResults.obj"
	-@erase "$(INTDIR)\DiscreteSequence.obj"
	-@erase "$(INTDIR)\FileResultDumper.obj"
	-@erase "$(INTDIR)\FlatThicknessCorrector.obj"
	-@erase "$(INTDIR)\GenesisDialog.obj"
	-@erase "$(INTDIR)\HandModificationDialog.obj"
	-@erase "$(INTDIR)\Limit.obj"
	-@erase "$(INTDIR)\LimitDialog.obj"
	-@erase "$(INTDIR)\LogicPoint.obj"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\MonochromaticBmpReader.obj"
	-@erase "$(INTDIR)\PartialCurve.obj"
	-@erase "$(INTDIR)\PenModificationTool.obj"
	-@erase "$(INTDIR)\PeriodDialog.obj"
	-@erase "$(INTDIR)\PreviewDialog.obj"
	-@erase "$(INTDIR)\RealColorBmpReader.obj"
	-@erase "$(INTDIR)\Results.obj"
	-@erase "$(INTDIR)\RubberModificationTool.obj"
	-@erase "$(INTDIR)\SaveCurveDialog.obj"
	-@erase "$(INTDIR)\ScalePoint.obj"
	-@erase "$(INTDIR)\Sequence.obj"
	-@erase "$(INTDIR)\SmartThicknessCorrector.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StringResultDumper.obj"
	-@erase "$(INTDIR)\Tools.obj"
	-@erase "$(INTDIR)\UnscanDoc.obj"
	-@erase "$(INTDIR)\UnscanView.obj"
	-@erase "$(INTDIR)\ValueEdit.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\WinBmpEx.obj"
	-@erase "$(INTDIR)\ZoomCombo.obj"
	-@erase "$(INTDIR)\ZoomDialog.obj"
	-@erase "$(OUTDIR)\CurveUnscan.exe"
	-@erase "HelpFiles\CurveUnscan.hm"
	-@erase "HelpFiles\French\CurveUnscan.chm"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GR /GX /O2 /Ob2 /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "__MATH_H__" /U "__MWERKS__" /U "THINK_C" /U "VMS" /U "HAVE_UNISTD_H" /U "_AMIGA" /U "__TURBOC__" /Fp"$(INTDIR)\CurveUnscan.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\CurveUnscan.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\CurveUnscan.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=htmlhelp.lib libjpeg.lib libpng.lib libtiff.lib libungif.lib /nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\CurveUnscan.pdb" /machine:I386 /out:"$(OUTDIR)\CurveUnscan.exe" 
LINK32_OBJS= \
	"$(INTDIR)\AbstractBmpReader.obj" \
	"$(INTDIR)\AbstractModificationTool.obj" \
	"$(INTDIR)\AbstractResultDumper.obj" \
	"$(INTDIR)\AbstractThicknessCorrector.obj" \
	"$(INTDIR)\Axe.obj" \
	"$(INTDIR)\AxeAbstractState.obj" \
	"$(INTDIR)\AxeDialog.obj" \
	"$(INTDIR)\AxeDrawingState.obj" \
	"$(INTDIR)\AxePointPickingState.obj" \
	"$(INTDIR)\AxeWaitState.obj" \
	"$(INTDIR)\BmpManager.obj" \
	"$(INTDIR)\Color256BmpReader.obj" \
	"$(INTDIR)\CompleteSequence.obj" \
	"$(INTDIR)\ConstructionDialog.obj" \
	"$(INTDIR)\ContinuousAdvOptDlg.obj" \
	"$(INTDIR)\ContinuousCurve.obj" \
	"$(INTDIR)\ContinuousResults.obj" \
	"$(INTDIR)\ContinuousSequence.obj" \
	"$(INTDIR)\CoordSequence.obj" \
	"$(INTDIR)\CoordSyst.obj" \
	"$(INTDIR)\Curve.obj" \
	"$(INTDIR)\CurveElement.obj" \
	"$(INTDIR)\CurveKindDialog.obj" \
	"$(INTDIR)\CurveUnscan.obj" \
	"$(INTDIR)\DiscreteCurve.obj" \
	"$(INTDIR)\DiscreteDialog.obj" \
	"$(INTDIR)\DiscreteResults.obj" \
	"$(INTDIR)\DiscreteSequence.obj" \
	"$(INTDIR)\FileResultDumper.obj" \
	"$(INTDIR)\FlatThicknessCorrector.obj" \
	"$(INTDIR)\GenesisDialog.obj" \
	"$(INTDIR)\HandModificationDialog.obj" \
	"$(INTDIR)\Limit.obj" \
	"$(INTDIR)\LimitDialog.obj" \
	"$(INTDIR)\LogicPoint.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\MonochromaticBmpReader.obj" \
	"$(INTDIR)\PartialCurve.obj" \
	"$(INTDIR)\PenModificationTool.obj" \
	"$(INTDIR)\PeriodDialog.obj" \
	"$(INTDIR)\PreviewDialog.obj" \
	"$(INTDIR)\RealColorBmpReader.obj" \
	"$(INTDIR)\Results.obj" \
	"$(INTDIR)\RubberModificationTool.obj" \
	"$(INTDIR)\SaveCurveDialog.obj" \
	"$(INTDIR)\ScalePoint.obj" \
	"$(INTDIR)\Sequence.obj" \
	"$(INTDIR)\SmartThicknessCorrector.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\StringResultDumper.obj" \
	"$(INTDIR)\Tools.obj" \
	"$(INTDIR)\UnscanDoc.obj" \
	"$(INTDIR)\UnscanView.obj" \
	"$(INTDIR)\ValueEdit.obj" \
	"$(INTDIR)\WinBmpEx.obj" \
	"$(INTDIR)\ZoomCombo.obj" \
	"$(INTDIR)\ZoomDialog.obj" \
	"$(INTDIR)\CurveUnscan.res" \
	".\HelpSystem\Release\HelpSystem.lib" \
	".\LicenceManaging\Release\LicenceManaging.lib" \
	".\Utilities\Release\Utilities.lib" \
	"..\..\..\Programmation\ExternalLibs\paintlib\lib\Release\paintlib.lib"

"$(OUTDIR)\CurveUnscan.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "CurveUnscan - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug/tmp
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : ".\HelpFiles\French\CurveUnscan.chm" "$(OUTDIR)\CurveUnscan.exe"

!ELSE 

ALL : "paintlib - Win32 Debug" "Utilities - Win32 Debug" "LicenceManaging - Win32 Debug" "HelpSystem - Win32 Debug" ".\HelpFiles\French\CurveUnscan.chm" "$(OUTDIR)\CurveUnscan.exe"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"HelpSystem - Win32 DebugCLEAN" "LicenceManaging - Win32 DebugCLEAN" "Utilities - Win32 DebugCLEAN" "paintlib - Win32 DebugCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\AbstractBmpReader.obj"
	-@erase "$(INTDIR)\AbstractModificationTool.obj"
	-@erase "$(INTDIR)\AbstractResultDumper.obj"
	-@erase "$(INTDIR)\AbstractThicknessCorrector.obj"
	-@erase "$(INTDIR)\Axe.obj"
	-@erase "$(INTDIR)\AxeAbstractState.obj"
	-@erase "$(INTDIR)\AxeDialog.obj"
	-@erase "$(INTDIR)\AxeDrawingState.obj"
	-@erase "$(INTDIR)\AxePointPickingState.obj"
	-@erase "$(INTDIR)\AxeWaitState.obj"
	-@erase "$(INTDIR)\BmpManager.obj"
	-@erase "$(INTDIR)\Color256BmpReader.obj"
	-@erase "$(INTDIR)\CompleteSequence.obj"
	-@erase "$(INTDIR)\ConstructionDialog.obj"
	-@erase "$(INTDIR)\ContinuousAdvOptDlg.obj"
	-@erase "$(INTDIR)\ContinuousCurve.obj"
	-@erase "$(INTDIR)\ContinuousResults.obj"
	-@erase "$(INTDIR)\ContinuousSequence.obj"
	-@erase "$(INTDIR)\CoordSequence.obj"
	-@erase "$(INTDIR)\CoordSyst.obj"
	-@erase "$(INTDIR)\Curve.obj"
	-@erase "$(INTDIR)\CurveElement.obj"
	-@erase "$(INTDIR)\CurveKindDialog.obj"
	-@erase "$(INTDIR)\CurveUnscan.obj"
	-@erase "$(INTDIR)\CurveUnscan.pch"
	-@erase "$(INTDIR)\CurveUnscan.res"
	-@erase "$(INTDIR)\DiscreteCurve.obj"
	-@erase "$(INTDIR)\DiscreteDialog.obj"
	-@erase "$(INTDIR)\DiscreteResults.obj"
	-@erase "$(INTDIR)\DiscreteSequence.obj"
	-@erase "$(INTDIR)\FileResultDumper.obj"
	-@erase "$(INTDIR)\FlatThicknessCorrector.obj"
	-@erase "$(INTDIR)\GenesisDialog.obj"
	-@erase "$(INTDIR)\HandModificationDialog.obj"
	-@erase "$(INTDIR)\Limit.obj"
	-@erase "$(INTDIR)\LimitDialog.obj"
	-@erase "$(INTDIR)\LogicPoint.obj"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\MonochromaticBmpReader.obj"
	-@erase "$(INTDIR)\PartialCurve.obj"
	-@erase "$(INTDIR)\PenModificationTool.obj"
	-@erase "$(INTDIR)\PeriodDialog.obj"
	-@erase "$(INTDIR)\PreviewDialog.obj"
	-@erase "$(INTDIR)\RealColorBmpReader.obj"
	-@erase "$(INTDIR)\Results.obj"
	-@erase "$(INTDIR)\RubberModificationTool.obj"
	-@erase "$(INTDIR)\SaveCurveDialog.obj"
	-@erase "$(INTDIR)\ScalePoint.obj"
	-@erase "$(INTDIR)\Sequence.obj"
	-@erase "$(INTDIR)\SmartThicknessCorrector.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StringResultDumper.obj"
	-@erase "$(INTDIR)\Tools.obj"
	-@erase "$(INTDIR)\UnscanDoc.obj"
	-@erase "$(INTDIR)\UnscanView.obj"
	-@erase "$(INTDIR)\ValueEdit.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\WinBmpEx.obj"
	-@erase "$(INTDIR)\ZoomCombo.obj"
	-@erase "$(INTDIR)\ZoomDialog.obj"
	-@erase "$(OUTDIR)\CurveUnscan.exe"
	-@erase "$(OUTDIR)\CurveUnscan.ilk"
	-@erase "$(OUTDIR)\CurveUnscan.pdb"
	-@erase "HelpFiles\French\CurveUnscan.chm"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GR /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "__MATH_H__" /U "__MWERKS__" /U "THINK_C" /U "VMS" /U "HAVE_UNISTD_H" /U "_AMIGA" /U "__TURBOC__" /Fp"$(INTDIR)\CurveUnscan.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\CurveUnscan.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\CurveUnscan.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=htmlhelp.lib libjpeg.lib libpng.lib libtiff.lib libungif.lib /nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\CurveUnscan.pdb" /debug /machine:I386 /out:"$(OUTDIR)\CurveUnscan.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\AbstractBmpReader.obj" \
	"$(INTDIR)\AbstractModificationTool.obj" \
	"$(INTDIR)\AbstractResultDumper.obj" \
	"$(INTDIR)\AbstractThicknessCorrector.obj" \
	"$(INTDIR)\Axe.obj" \
	"$(INTDIR)\AxeAbstractState.obj" \
	"$(INTDIR)\AxeDialog.obj" \
	"$(INTDIR)\AxeDrawingState.obj" \
	"$(INTDIR)\AxePointPickingState.obj" \
	"$(INTDIR)\AxeWaitState.obj" \
	"$(INTDIR)\BmpManager.obj" \
	"$(INTDIR)\Color256BmpReader.obj" \
	"$(INTDIR)\CompleteSequence.obj" \
	"$(INTDIR)\ConstructionDialog.obj" \
	"$(INTDIR)\ContinuousAdvOptDlg.obj" \
	"$(INTDIR)\ContinuousCurve.obj" \
	"$(INTDIR)\ContinuousResults.obj" \
	"$(INTDIR)\ContinuousSequence.obj" \
	"$(INTDIR)\CoordSequence.obj" \
	"$(INTDIR)\CoordSyst.obj" \
	"$(INTDIR)\Curve.obj" \
	"$(INTDIR)\CurveElement.obj" \
	"$(INTDIR)\CurveKindDialog.obj" \
	"$(INTDIR)\CurveUnscan.obj" \
	"$(INTDIR)\DiscreteCurve.obj" \
	"$(INTDIR)\DiscreteDialog.obj" \
	"$(INTDIR)\DiscreteResults.obj" \
	"$(INTDIR)\DiscreteSequence.obj" \
	"$(INTDIR)\FileResultDumper.obj" \
	"$(INTDIR)\FlatThicknessCorrector.obj" \
	"$(INTDIR)\GenesisDialog.obj" \
	"$(INTDIR)\HandModificationDialog.obj" \
	"$(INTDIR)\Limit.obj" \
	"$(INTDIR)\LimitDialog.obj" \
	"$(INTDIR)\LogicPoint.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\MonochromaticBmpReader.obj" \
	"$(INTDIR)\PartialCurve.obj" \
	"$(INTDIR)\PenModificationTool.obj" \
	"$(INTDIR)\PeriodDialog.obj" \
	"$(INTDIR)\PreviewDialog.obj" \
	"$(INTDIR)\RealColorBmpReader.obj" \
	"$(INTDIR)\Results.obj" \
	"$(INTDIR)\RubberModificationTool.obj" \
	"$(INTDIR)\SaveCurveDialog.obj" \
	"$(INTDIR)\ScalePoint.obj" \
	"$(INTDIR)\Sequence.obj" \
	"$(INTDIR)\SmartThicknessCorrector.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\StringResultDumper.obj" \
	"$(INTDIR)\Tools.obj" \
	"$(INTDIR)\UnscanDoc.obj" \
	"$(INTDIR)\UnscanView.obj" \
	"$(INTDIR)\ValueEdit.obj" \
	"$(INTDIR)\WinBmpEx.obj" \
	"$(INTDIR)\ZoomCombo.obj" \
	"$(INTDIR)\ZoomDialog.obj" \
	"$(INTDIR)\CurveUnscan.res" \
	".\HelpSystem\Debug\HelpSystem.lib" \
	".\LicenceManaging\Debug\LicenceManaging.lib" \
	".\Utilities\Debug\Utilities.lib" \
	"..\..\..\Programmation\ExternalLibs\paintlib\lib\Debug\paintlib.lib"

"$(OUTDIR)\CurveUnscan.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("CurveUnscan.dep")
!INCLUDE "CurveUnscan.dep"
!ELSE 
!MESSAGE Warning: cannot find "CurveUnscan.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "CurveUnscan - Win32 Release" || "$(CFG)" == "CurveUnscan - Win32 Debug"
SOURCE=.\AbstractBmpReader.cpp

"$(INTDIR)\AbstractBmpReader.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CurveUnscan.pch"


SOURCE=.\AbstractModificationTool.cpp

"$(INTDIR)\AbstractModificationTool.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CurveUnscan.pch"


SOURCE=.\AbstractResultDumper.cpp

"$(INTDIR)\AbstractResultDumper.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CurveUnscan.pch"


SOURCE=.\AbstractThicknessCorrector.cpp

"$(INTDIR)\AbstractThicknessCorrector.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CurveUnscan.pch"


SOURCE=.\Axe.cpp

"$(INTDIR)\Axe.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CurveUnscan.pch"


SOURCE=.\AxeAbstractState.cpp

"$(INTDIR)\AxeAbstractState.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CurveUnscan.pch"


SOURCE=.\AxeDialog.cpp

"$(INTDIR)\AxeDialog.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CurveUnscan.pch"


SOURCE=.\AxeDrawingState.cpp

"$(INTDIR)\AxeDrawingState.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CurveUnscan.pch"


SOURCE=.\AxePointPickingState.cpp

"$(INTDIR)\AxePointPickingState.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CurveUnscan.pch"


SOURCE=.\AxeWaitState.cpp

"$(INTDIR)\AxeWaitState.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CurveUnscan.pch"


SOURCE=.\BmpManager.cpp

"$(INTDIR)\BmpManager.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CurveUnscan.pch"


SOURCE=.\Color256BmpReader.cpp

"$(INTDIR)\Color256BmpReader.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CurveUnscan.pch"


SOURCE=.\CompleteSequence.cpp

"$(INTDIR)\CompleteSequence.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CurveUnscan.pch"


SOURCE=.\ConstructionDialog.cpp

"$(INTDIR)\ConstructionDialog.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CurveUnscan.pch"


SOURCE=.\ContinuousAdvOptDlg.cpp

"$(INTDIR)\ContinuousAdvOptDlg.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CurveUnscan.pch"


SOURCE=.\ContinuousCurve.cpp

"$(INTDIR)\ContinuousCurve.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CurveUnscan.pch"


SOURCE=.\ContinuousResults.cpp

"$(INTDIR)\ContinuousResults.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CurveUnscan.pch"


SOURCE=.\ContinuousSequence.cpp

"$(INTDIR)\ContinuousSequence.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CurveUnscan.pch"


SOURCE=.\CoordSequence.cpp

"$(INTDIR)\CoordSequence.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CurveUnscan.pch"


SOURCE=.\CoordSyst.cpp

"$(INTDIR)\CoordSyst.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CurveUnscan.pch"


SOURCE=.\Curve.cpp

"$(INTDIR)\Curve.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CurveUnscan.pch"


SOURCE=.\CurveElement.cpp

"$(INTDIR)\CurveElement.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CurveUnscan.pch"


SOURCE=.\CurveKindDialog.cpp

"$(INTDIR)\CurveKindDialog.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CurveUnscan.pch"


SOURCE=.\CurveUnscan.cpp

"$(INTDIR)\CurveUnscan.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CurveUnscan.pch"


SOURCE=.\CurveUnscan.rc

"$(INTDIR)\CurveUnscan.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\DiscreteCurve.cpp

"$(INTDIR)\DiscreteCurve.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CurveUnscan.pch"


SOURCE=.\DiscreteDialog.cpp

"$(INTDIR)\DiscreteDialog.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CurveUnscan.pch"


SOURCE=.\DiscreteResults.cpp

"$(INTDIR)\DiscreteResults.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CurveUnscan.pch"


SOURCE=.\DiscreteSequence.cpp

"$(INTDIR)\DiscreteSequence.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CurveUnscan.pch"


SOURCE=.\FileResultDumper.cpp

"$(INTDIR)\FileResultDumper.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CurveUnscan.pch"


SOURCE=.\FlatThicknessCorrector.cpp

"$(INTDIR)\FlatThicknessCorrector.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CurveUnscan.pch"


SOURCE=.\GenesisDialog.cpp

"$(INTDIR)\GenesisDialog.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CurveUnscan.pch"


SOURCE=.\HandModificationDialog.cpp

"$(INTDIR)\HandModificationDialog.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CurveUnscan.pch"


SOURCE=.\Limit.cpp

"$(INTDIR)\Limit.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CurveUnscan.pch"


SOURCE=.\LimitDialog.cpp

"$(INTDIR)\LimitDialog.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CurveUnscan.pch"


SOURCE=.\LogicPoint.cpp

"$(INTDIR)\LogicPoint.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CurveUnscan.pch"


SOURCE=.\MainFrm.cpp

"$(INTDIR)\MainFrm.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CurveUnscan.pch"


SOURCE=.\MonochromaticBmpReader.cpp

"$(INTDIR)\MonochromaticBmpReader.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CurveUnscan.pch"


SOURCE=.\PartialCurve.cpp

"$(INTDIR)\PartialCurve.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CurveUnscan.pch"


SOURCE=.\PenModificationTool.cpp

"$(INTDIR)\PenModificationTool.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CurveUnscan.pch"


SOURCE=.\PeriodDialog.cpp

"$(INTDIR)\PeriodDialog.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CurveUnscan.pch"


SOURCE=.\PreviewDialog.cpp

"$(INTDIR)\PreviewDialog.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CurveUnscan.pch"


SOURCE=.\RealColorBmpReader.cpp

"$(INTDIR)\RealColorBmpReader.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CurveUnscan.pch"


SOURCE=.\Results.cpp

"$(INTDIR)\Results.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CurveUnscan.pch"


SOURCE=.\RubberModificationTool.cpp

"$(INTDIR)\RubberModificationTool.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CurveUnscan.pch"


SOURCE=.\SaveCurveDialog.cpp

"$(INTDIR)\SaveCurveDialog.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CurveUnscan.pch"


SOURCE=.\ScalePoint.cpp

"$(INTDIR)\ScalePoint.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CurveUnscan.pch"


SOURCE=.\Sequence.cpp

"$(INTDIR)\Sequence.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CurveUnscan.pch"


SOURCE=.\SmartThicknessCorrector.cpp

"$(INTDIR)\SmartThicknessCorrector.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CurveUnscan.pch"


SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "CurveUnscan - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GR /GX /O2 /Ob2 /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "__MATH_H__" /U "__MWERKS__" /U "THINK_C" /U "VMS" /U "HAVE_UNISTD_H" /U "_AMIGA" /U "__TURBOC__" /Fp"$(INTDIR)\CurveUnscan.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\CurveUnscan.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "CurveUnscan - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GR /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "__MATH_H__" /U "__MWERKS__" /U "THINK_C" /U "VMS" /U "HAVE_UNISTD_H" /U "_AMIGA" /U "__TURBOC__" /Fp"$(INTDIR)\CurveUnscan.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\CurveUnscan.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\StringResultDumper.cpp

"$(INTDIR)\StringResultDumper.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CurveUnscan.pch"


SOURCE=.\Tools.cpp

"$(INTDIR)\Tools.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CurveUnscan.pch"


SOURCE=.\UnscanDoc.cpp

"$(INTDIR)\UnscanDoc.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CurveUnscan.pch"


SOURCE=.\UnscanView.cpp

"$(INTDIR)\UnscanView.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CurveUnscan.pch"


SOURCE=.\ValueEdit.cpp

"$(INTDIR)\ValueEdit.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CurveUnscan.pch"


SOURCE=.\WinBmpEx.cpp

"$(INTDIR)\WinBmpEx.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CurveUnscan.pch"


SOURCE=.\ZoomCombo.cpp

"$(INTDIR)\ZoomCombo.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CurveUnscan.pch"


SOURCE=.\ZoomDialog.cpp

"$(INTDIR)\ZoomDialog.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CurveUnscan.pch"


SOURCE=.\Resource.h

!IF  "$(CFG)" == "CurveUnscan - Win32 Release"

TargetName=CurveUnscan
InputPath=.\Resource.h

".\HelpFiles\CurveUnscan.hm" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	del Helpfiles\$(TargetName).hm 
	makehm ID_,IDH_,0x10000  resource.h >>"HelpFiles\$(TargetName).hm" 
	makehm IDM_,IDH_,0x10000 resource.h >>"HelpFiles\$(TargetName).hm" 
	makehm IDP_,IDH_,0x30000 resource.h >>"HelpFiles\$(TargetName).hm" 
	makehm IDR_,IDH_,0x20000 resource.h >>"HelpFiles\$(TargetName).hm" 
	makehm IDD_,IDH_,0x20000 resource.h >>"HelpFiles\$(TargetName).hm" 
	makehm IDW_,IDH_,0x50000 resource.h >>"HelpFiles\$(TargetName).hm" 
	echo.  >>"HelpFiles\$(TargetName).hm" 
	MakeIDH "HelpFiles\$(TargetName).hm" 
<< 
	

!ELSEIF  "$(CFG)" == "CurveUnscan - Win32 Debug"

TargetName=CurveUnscan
InputPath=.\Resource.h

".\HelpFiles\CurveUnscan.hm" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	del Helpfiles\$(TargetName).hm 
	makehm ID_,IDH_,0x10000  resource.h >>"HelpFiles\$(TargetName).hm" 
	makehm IDM_,IDH_,0x10000 resource.h >>"HelpFiles\$(TargetName).hm" 
	makehm IDP_,IDH_,0x30000 resource.h >>"HelpFiles\$(TargetName).hm" 
	makehm IDR_,IDH_,0x20000 resource.h >>"HelpFiles\$(TargetName).hm" 
	makehm IDD_,IDH_,0x20000 resource.h >>"HelpFiles\$(TargetName).hm" 
	makehm IDW_,IDH_,0x50000 resource.h >>"HelpFiles\$(TargetName).hm" 
	echo.  >>"HelpFiles\$(TargetName).hm" 
	MakeIDH "HelpFiles\$(TargetName).hm" 
<< 
	

!ENDIF 

!IF  "$(CFG)" == "CurveUnscan - Win32 Release"

"HelpSystem - Win32 Release" : 
   cd ".\HelpSystem"
   $(MAKE) /$(MAKEFLAGS) /F ".\HelpSystem.mak" CFG="HelpSystem - Win32 Release" 
   cd ".."

"HelpSystem - Win32 ReleaseCLEAN" : 
   cd ".\HelpSystem"
   $(MAKE) /$(MAKEFLAGS) /F ".\HelpSystem.mak" CFG="HelpSystem - Win32 Release" RECURSE=1 CLEAN 
   cd ".."

!ELSEIF  "$(CFG)" == "CurveUnscan - Win32 Debug"

"HelpSystem - Win32 Debug" : 
   cd ".\HelpSystem"
   $(MAKE) /$(MAKEFLAGS) /F ".\HelpSystem.mak" CFG="HelpSystem - Win32 Debug" 
   cd ".."

"HelpSystem - Win32 DebugCLEAN" : 
   cd ".\HelpSystem"
   $(MAKE) /$(MAKEFLAGS) /F ".\HelpSystem.mak" CFG="HelpSystem - Win32 Debug" RECURSE=1 CLEAN 
   cd ".."

!ENDIF 

!IF  "$(CFG)" == "CurveUnscan - Win32 Release"

"LicenceManaging - Win32 Release" : 
   cd ".\LicenceManaging"
   $(MAKE) /$(MAKEFLAGS) /F ".\LicenceManaging.mak" CFG="LicenceManaging - Win32 Release" 
   cd ".."

"LicenceManaging - Win32 ReleaseCLEAN" : 
   cd ".\LicenceManaging"
   $(MAKE) /$(MAKEFLAGS) /F ".\LicenceManaging.mak" CFG="LicenceManaging - Win32 Release" RECURSE=1 CLEAN 
   cd ".."

!ELSEIF  "$(CFG)" == "CurveUnscan - Win32 Debug"

"LicenceManaging - Win32 Debug" : 
   cd ".\LicenceManaging"
   $(MAKE) /$(MAKEFLAGS) /F ".\LicenceManaging.mak" CFG="LicenceManaging - Win32 Debug" 
   cd ".."

"LicenceManaging - Win32 DebugCLEAN" : 
   cd ".\LicenceManaging"
   $(MAKE) /$(MAKEFLAGS) /F ".\LicenceManaging.mak" CFG="LicenceManaging - Win32 Debug" RECURSE=1 CLEAN 
   cd ".."

!ENDIF 

!IF  "$(CFG)" == "CurveUnscan - Win32 Release"

"Utilities - Win32 Release" : 
   cd ".\Utilities"
   $(MAKE) /$(MAKEFLAGS) /F ".\Utilities.mak" CFG="Utilities - Win32 Release" 
   cd ".."

"Utilities - Win32 ReleaseCLEAN" : 
   cd ".\Utilities"
   $(MAKE) /$(MAKEFLAGS) /F ".\Utilities.mak" CFG="Utilities - Win32 Release" RECURSE=1 CLEAN 
   cd ".."

!ELSEIF  "$(CFG)" == "CurveUnscan - Win32 Debug"

"Utilities - Win32 Debug" : 
   cd ".\Utilities"
   $(MAKE) /$(MAKEFLAGS) /F ".\Utilities.mak" CFG="Utilities - Win32 Debug" 
   cd ".."

"Utilities - Win32 DebugCLEAN" : 
   cd ".\Utilities"
   $(MAKE) /$(MAKEFLAGS) /F ".\Utilities.mak" CFG="Utilities - Win32 Debug" RECURSE=1 CLEAN 
   cd ".."

!ENDIF 

!IF  "$(CFG)" == "CurveUnscan - Win32 Release"

"paintlib - Win32 Release" : 
   cd "\Mes documents\Programmation\ExternalLibs\paintlib\paintlib\win\paintlib"
   $(MAKE) /$(MAKEFLAGS) /F ".\paintlib.mak" CFG="paintlib - Win32 Release" 
   cd "..\..\..\..\..\..\CurveUnscan\Dev\CurrentVersion"

"paintlib - Win32 ReleaseCLEAN" : 
   cd "\Mes documents\Programmation\ExternalLibs\paintlib\paintlib\win\paintlib"
   $(MAKE) /$(MAKEFLAGS) /F ".\paintlib.mak" CFG="paintlib - Win32 Release" RECURSE=1 CLEAN 
   cd "..\..\..\..\..\..\CurveUnscan\Dev\CurrentVersion"

!ELSEIF  "$(CFG)" == "CurveUnscan - Win32 Debug"

"paintlib - Win32 Debug" : 
   cd "\Mes documents\Programmation\ExternalLibs\paintlib\paintlib\win\paintlib"
   $(MAKE) /$(MAKEFLAGS) /F ".\paintlib.mak" CFG="paintlib - Win32 Debug" 
   cd "..\..\..\..\..\..\CurveUnscan\Dev\CurrentVersion"

"paintlib - Win32 DebugCLEAN" : 
   cd "\Mes documents\Programmation\ExternalLibs\paintlib\paintlib\win\paintlib"
   $(MAKE) /$(MAKEFLAGS) /F ".\paintlib.mak" CFG="paintlib - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\..\..\..\..\..\CurveUnscan\Dev\CurrentVersion"

!ENDIF 

SOURCE=.\HelpFiles\French\CurveUnscan.hhp

!IF  "$(CFG)" == "CurveUnscan - Win32 Release"

OutDir=.\Release
InputPath=.\HelpFiles\French\CurveUnscan.hhp
InputName=CurveUnscan

".\HelpFiles\French\CurveUnscan.chm" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	hhc.exe HelpFiles\French\$(InputName).hhp 
	echo. 
	copy HelpFiles\French\$(InputName).chm $(OutDir)\$(InputName).chm 
<< 
	

!ELSEIF  "$(CFG)" == "CurveUnscan - Win32 Debug"

OutDir=.\Debug
InputPath=.\HelpFiles\French\CurveUnscan.hhp
InputName=CurveUnscan
USERDEP__CURVE="HelpFiles\$(InputName).hm"	

".\HelpFiles\French\CurveUnscan.chm" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)" $(USERDEP__CURVE)
	<<tempfile.bat 
	@echo off 
	hhc.exe HelpFiles\French\$(InputName).hhp 
	echo. 
	copy HelpFiles\French\$(InputName).chm $(OutDir)\$(InputName).chm 
<< 
	

!ENDIF 


!ENDIF 

