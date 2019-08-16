/*
/--------------------------------------------------------------------
|
|      $Id: pltrace.cpp,v 1.1 2001/09/16 19:03:22 uzadow Exp $
|
|      Copyright (c) 1996-1998 Ulrich von Zadow
|
\--------------------------------------------------------------------
*/
#include "plstdpch.h"

#ifdef _DEBUG

#include <stdarg.h>
#include <stdio.h>

void PLTrace(const char * pszFormat, ...)
{
  va_list args;
  va_start(args, pszFormat);

  int nBuf;
  char szBuffer[4096];

  nBuf = vsprintf(szBuffer, pszFormat, args);
  PLASSERT(nBuf < 4096);

#ifndef _WINDOWS
  fprintf (stderr, szBuffer);
#else
  ::OutputDebugString (szBuffer);
#endif //_WINDOWS

  va_end(args);
}

#endif //_DEBUG

/*
/--------------------------------------------------------------------
|
|      $Log: pltrace.cpp,v $
|      Revision 1.1  2001/09/16 19:03:22  uzadow
|      Added global name prefix PL, changed most filenames.
|
|      Revision 1.6  2001/09/15 21:02:44  uzadow
|      Cleaned up stdpch.h and config.h to make them internal headers.
|
|      Revision 1.5  2000/01/16 20:43:15  anonymous
|      Removed MFC dependencies
|
|      Revision 1.4  2000/01/10 23:53:00  Ulrich von Zadow
|      Changed formatting & removed tabs.
|
|      Revision 1.3  1999/10/03 18:50:52  Ulrich von Zadow
|      Added automatic logging of changes.
|
|
\--------------------------------------------------------------------
*/
