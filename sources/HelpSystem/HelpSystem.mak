# Microsoft Developer Studio Generated NMAKE File, Based on HelpSystem.dsp
!IF "$(CFG)" == ""
CFG=HelpSystem - Win32 Debug
!MESSAGE No configuration specified. Defaulting to HelpSystem - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "HelpSystem - Win32 Release" && "$(CFG)" != "HelpSystem - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "HelpSystem.mak" CFG="HelpSystem - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "HelpSystem - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "HelpSystem - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "HelpSystem - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release/tmp
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\HelpSystem.lib"


CLEAN :
	-@erase "$(INTDIR)\HelpFunctions.obj"
	-@erase "$(INTDIR)\HelpSystem.pch"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\HelpSystem.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GR /GX /O2 /Ob2 /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "__MATH_H__" /U "__MWERKS__" /U "THINK_C" /U "VMS" /U "HAVE_UNISTD_H" /U "_AMIGA" /U "__TURBOC__" /Fp"$(INTDIR)\HelpSystem.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\HelpSystem.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"$(OUTDIR)\HelpSystem.lib" 
LIB32_OBJS= \
	"$(INTDIR)\HelpFunctions.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\HelpSystem.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ELSEIF  "$(CFG)" == "HelpSystem - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug/tmp
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\HelpSystem.lib"


CLEAN :
	-@erase "$(INTDIR)\HelpFunctions.obj"
	-@erase "$(INTDIR)\HelpSystem.pch"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\HelpSystem.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GR /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "__MATH_H__" /U "__MWERKS__" /U "THINK_C" /U "VMS" /U "HAVE_UNISTD_H" /U "_AMIGA" /U "__TURBOC__" /Fp"$(INTDIR)\HelpSystem.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\HelpSystem.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"$(OUTDIR)\HelpSystem.lib" 
LIB32_OBJS= \
	"$(INTDIR)\HelpFunctions.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\HelpSystem.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("HelpSystem.dep")
!INCLUDE "HelpSystem.dep"
!ELSE 
!MESSAGE Warning: cannot find "HelpSystem.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "HelpSystem - Win32 Release" || "$(CFG)" == "HelpSystem - Win32 Debug"
SOURCE=.\HelpFunctions.cpp

"$(INTDIR)\HelpFunctions.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\HelpSystem.pch"


SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "HelpSystem - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GR /GX /O2 /Ob2 /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "__MATH_H__" /U "__MWERKS__" /U "THINK_C" /U "VMS" /U "HAVE_UNISTD_H" /U "_AMIGA" /U "__TURBOC__" /Fp"$(INTDIR)\HelpSystem.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\HelpSystem.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "HelpSystem - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GR /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "__MATH_H__" /U "__MWERKS__" /U "THINK_C" /U "VMS" /U "HAVE_UNISTD_H" /U "_AMIGA" /U "__TURBOC__" /Fp"$(INTDIR)\HelpSystem.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\HelpSystem.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 


!ENDIF 

