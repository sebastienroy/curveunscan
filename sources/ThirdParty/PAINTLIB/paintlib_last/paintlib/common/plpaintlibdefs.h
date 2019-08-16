/*
/--------------------------------------------------------------------
|
|      $Id: plpaintlibdefs.h,v 1.4 2002/02/24 13:00:22 uzadow Exp $
|
|      Copyright (c) 1996-2002 Ulrich von Zadow
|
\--------------------------------------------------------------------
*/

//! Contains common datatype definitions.
//!

#ifndef INCL_PLPAINTLIBDEFS
#define INCL_PLPAINTLIBDEFS

#include "pldebug.h"

typedef unsigned char       PLBYTE;
typedef unsigned int        PLUINT;
typedef unsigned short      PLWORD;         // This is 16 bit.
typedef long                PLLONG;         // This is 32 bit.
typedef unsigned long       PLULONG;

#ifndef _WINDOWS
#include <stdarg.h>

// max & min definitions
#include <algorithm> // STL

#ifndef NULL
#define NULL    0
#endif

#endif //#ifndef _WINDOWS


#endif
/*
/--------------------------------------------------------------------
|
|      $Log: plpaintlibdefs.h,v $
|      Revision 1.4  2002/02/24 13:00:22  uzadow
|      Documentation update; removed buggy PLFilterRotate.
|
|      Revision 1.3  2001/10/06 22:03:26  uzadow
|      Added PL prefix to basic data types.
|
|      Revision 1.2  2001/10/06 15:32:22  uzadow
|      Removed types LPBYTE, DWORD, UCHAR, VOID and INT from the code.
|
|      Revision 1.1  2001/09/16 19:03:22  uzadow
|      Added global name prefix PL, changed most filenames.
|
|      Revision 1.3  2001/09/15 21:02:44  uzadow
|      Cleaned up stdpch.h and config.h to make them internal headers.
|
|      Revision 1.2  2000/11/09 22:23:36  uzadow
|      no message
|
|      Revision 1.1  2000/11/07 15:33:44  jmbuena
|      Windows type defines for non windows systems
|
|
\--------------------------------------------------------------------
*/
