/*
/--------------------------------------------------------------------
|
|      $Id: testpaintlib.cpp,v 1.6 2002/02/24 13:00:50 uzadow Exp $
|
|      Test suite for paintlib.
|
|
|      Copyright (c) 1996-2002 Ulrich von Zadow
|
\--------------------------------------------------------------------
*/

#ifdef _WINDOWS
#include <windows.h>
#else
#include "plpaintlibdefs.h"
#endif

#include "pltester.h"

void main(int nargs, char** args)
{
  PLTester* pTester;
  pTester = new PLTester();
  pTester->RunTests();
  bool bOK = pTester->Ok();
  delete pTester;

  if (bOK)
    exit (0);
  else
    exit (1);
}

/*
/--------------------------------------------------------------------
|
|      $Log: testpaintlib.cpp,v $
|      Revision 1.6  2002/02/24 13:00:50  uzadow
|      Documentation update; removed buggy PLFilterRotate.
|
|      Revision 1.5  2001/10/06 20:44:45  uzadow
|      Linux compatibility
|
|      Revision 1.4  2001/09/16 20:57:17  uzadow
|      Linux version name prefix changes
|
|      Revision 1.3  2001/01/15 15:05:31  uzadow
|      Added CBmp::ApplyFilter() and CBmp::CreateFilteredCopy()
|
|      Revision 1.2  2000/12/09 12:16:26  uzadow
|      Fixed several memory leaks.
|
|      Revision 1.1  2000/11/21 20:29:39  uzadow
|      Added test project.
|
|
|
\--------------------------------------------------------------------
*/
