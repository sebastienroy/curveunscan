# Microsoft Developer Studio Generated NMAKE File, Based on LicenceManaging.dsp
!IF "$(CFG)" == ""
CFG=LicenceManaging - Win32 Debug
!MESSAGE No configuration specified. Defaulting to LicenceManaging - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "LicenceManaging - Win32 Release" && "$(CFG)" != "LicenceManaging - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "LicenceManaging.mak" CFG="LicenceManaging - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "LicenceManaging - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "LicenceManaging - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "LicenceManaging - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release/tmp
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\LicenceManaging.lib"


CLEAN :
	-@erase "$(INTDIR)\Coder.obj"
	-@erase "$(INTDIR)\FileConfirm.obj"
	-@erase "$(INTDIR)\LicenceDlg.obj"
	-@erase "$(INTDIR)\LicenceException.obj"
	-@erase "$(INTDIR)\LicenceManager.obj"
	-@erase "$(INTDIR)\LicenceManaging.pch"
	-@erase "$(INTDIR)\LicenceManaging.res"
	-@erase "$(INTDIR)\SorryDlg.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\WelcomeDialog.obj"
	-@erase "$(OUTDIR)\LicenceManaging.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GR /GX /O2 /Ob2 /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "__MATH_H__" /U "__MWERKS__" /U "THINK_C" /U "VMS" /U "HAVE_UNISTD_H" /U "_AMIGA" /U "__TURBOC__" /Fp"$(INTDIR)\LicenceManaging.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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

RSC=rc.exe
RSC_PROJ=/l 0x40c /fo"$(INTDIR)\LicenceManaging.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\LicenceManaging.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"$(OUTDIR)\LicenceManaging.lib" 
LIB32_OBJS= \
	"$(INTDIR)\Coder.obj" \
	"$(INTDIR)\FileConfirm.obj" \
	"$(INTDIR)\LicenceDlg.obj" \
	"$(INTDIR)\LicenceException.obj" \
	"$(INTDIR)\LicenceManager.obj" \
	"$(INTDIR)\SorryDlg.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\WelcomeDialog.obj" \
	"$(INTDIR)\LicenceManaging.res"

"$(OUTDIR)\LicenceManaging.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ELSEIF  "$(CFG)" == "LicenceManaging - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug/tmp
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\LicenceManaging.lib"


CLEAN :
	-@erase "$(INTDIR)\Coder.obj"
	-@erase "$(INTDIR)\FileConfirm.obj"
	-@erase "$(INTDIR)\LicenceDlg.obj"
	-@erase "$(INTDIR)\LicenceException.obj"
	-@erase "$(INTDIR)\LicenceManager.obj"
	-@erase "$(INTDIR)\LicenceManaging.pch"
	-@erase "$(INTDIR)\LicenceManaging.res"
	-@erase "$(INTDIR)\SorryDlg.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\WelcomeDialog.obj"
	-@erase "$(OUTDIR)\LicenceManaging.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GR /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "__MATH_H__" /U "__MWERKS__" /U "THINK_C" /U "VMS" /U "HAVE_UNISTD_H" /U "_AMIGA" /U "__TURBOC__" /Fp"$(INTDIR)\LicenceManaging.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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

RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\LicenceManaging.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\LicenceManaging.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"$(OUTDIR)\LicenceManaging.lib" 
LIB32_OBJS= \
	"$(INTDIR)\Coder.obj" \
	"$(INTDIR)\FileConfirm.obj" \
	"$(INTDIR)\LicenceDlg.obj" \
	"$(INTDIR)\LicenceException.obj" \
	"$(INTDIR)\LicenceManager.obj" \
	"$(INTDIR)\SorryDlg.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\WelcomeDialog.obj" \
	"$(INTDIR)\LicenceManaging.res"

"$(OUTDIR)\LicenceManaging.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("LicenceManaging.dep")
!INCLUDE "LicenceManaging.dep"
!ELSE 
!MESSAGE Warning: cannot find "LicenceManaging.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "LicenceManaging - Win32 Release" || "$(CFG)" == "LicenceManaging - Win32 Debug"
SOURCE=.\Coder.cpp

"$(INTDIR)\Coder.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\LicenceManaging.pch"


SOURCE=.\FileConfirm.cpp

"$(INTDIR)\FileConfirm.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\LicenceManaging.pch"


SOURCE=.\LicenceDlg.cpp

"$(INTDIR)\LicenceDlg.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\LicenceManaging.pch"


SOURCE=.\LicenceException.cpp

"$(INTDIR)\LicenceException.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\LicenceManaging.pch"


SOURCE=.\LicenceManager.cpp

"$(INTDIR)\LicenceManager.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\LicenceManaging.pch"


SOURCE=.\LicenceManaging.rc

!IF  "$(CFG)" == "LicenceManaging - Win32 Release"


"$(INTDIR)\LicenceManaging.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) /l 0x40c /fo"$(INTDIR)\LicenceManaging.res" /d "NDEBUG" /d "_AFXDLL" $(SOURCE)


!ELSEIF  "$(CFG)" == "LicenceManaging - Win32 Debug"


"$(INTDIR)\LicenceManaging.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) /l 0x409 /fo"$(INTDIR)\LicenceManaging.res" /d "_DEBUG" /d "_AFXDLL" $(SOURCE)


!ENDIF 

SOURCE=.\SorryDlg.cpp

"$(INTDIR)\SorryDlg.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\LicenceManaging.pch"


SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "LicenceManaging - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GR /GX /O2 /Ob2 /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "__MATH_H__" /U "__MWERKS__" /U "THINK_C" /U "VMS" /U "HAVE_UNISTD_H" /U "_AMIGA" /U "__TURBOC__" /Fp"$(INTDIR)\LicenceManaging.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\LicenceManaging.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "LicenceManaging - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GR /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "__MATH_H__" /U "__MWERKS__" /U "THINK_C" /U "VMS" /U "HAVE_UNISTD_H" /U "_AMIGA" /U "__TURBOC__" /Fp"$(INTDIR)\LicenceManaging.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\LicenceManaging.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\WelcomeDialog.cpp

"$(INTDIR)\WelcomeDialog.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\LicenceManaging.pch"



!ENDIF 

