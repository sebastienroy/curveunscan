/*
/--------------------------------------------------------------------
|
|      $Id: testfilterresizebilinear.cpp,v 1.4 2002/01/27 18:20:18 uzadow Exp $
|
|      Copyright (c) 1996-2002 Ulrich von Zadow
|
\--------------------------------------------------------------------
*/

#include "testfilterresizebilinear.h"
#include "pltester.h"

#include <iostream>
#include <string>
#include <fstream>

#include "plpaintlibdefs.h"
#include "planybmp.h"
#include "plpixel32.h"

#include "Filter/plfilterresizebilinear.h"

PLTestFilterResizeBilinear::PLTestFilterResizeBilinear (PLTester * pTester)
    : m_pTester (pTester)
{
  
}

PLTestFilterResizeBilinear::~PLTestFilterResizeBilinear ()
{
}

void PLTestFilterResizeBilinear::RunTests ()
{
  PLAnyBmp AnyBmp32;
  createBmp (AnyBmp32);

  PLTRACE ("  Testing bilinear resize...\n");
  PLAnyBmp DestBmp1;
  PLAnyBmp DestBmp2;
  DestBmp1.CreateFilteredCopy (AnyBmp32, PLFilterResizeBilinear (4,4));
  DestBmp2.CreateFilteredCopy (DestBmp1, PLFilterResizeBilinear (8,8));
  m_pTester->Test (AnyBmp32.AlmostEqual (DestBmp2, 1));
/*
  DestBmp1.CreateFilteredCopy (AnyBmp32, PLFilterResizeBilinear (2,2));
  DestBmp2.CreateFilteredCopy (DestBmp1, PLFilterResizeBilinear (8,8));
  m_pTester->Test (AnyBmp32.AlmostEqual (DestBmp2, 5));
*/
  DestBmp1.CreateFilteredCopy (AnyBmp32, PLFilterResizeBilinear (16,16));
  DestBmp2.CreateFilteredCopy (DestBmp1, PLFilterResizeBilinear (8,8));
  m_pTester->Test (AnyBmp32.AlmostEqual (DestBmp2, 1));
}

void PLTestFilterResizeBilinear::createBmp(PLBmp& Bmp)
{
  Bmp.Create (8, 8, 32, false);

  int x,y;
  for (y=0; y<4; y++)
    for (x=0; x<4; x++)
      Bmp.SetPixel (x,y, PLPixel32 (255,0,0,0));

  for (y=0; y<4; y++)
    for (x=4; x<8; x++)
      Bmp.SetPixel (x,y, PLPixel32 (0,255,0,0));

  for (y=4; y<8; y++)
    for (x=0; x<4; x++)
      Bmp.SetPixel (x,y, PLPixel32 (0,0,255,0));

  for (y=4; y<8; y++)
    for (x=4; x<8; x++)
      Bmp.SetPixel (x,y, PLPixel32 (255,255,255,0));
}

/*
/--------------------------------------------------------------------
|
|      $Log: testfilterresizebilinear.cpp,v $
|      Revision 1.4  2002/01/27 18:20:18  uzadow
|      Updated copyright message; corrected pcx decoder bug.
|
|      Revision 1.3  2001/10/06 15:32:22  uzadow
|      Removed types LPBYTE, DWORD, UCHAR, VOID and INT from the code.
|
|      Revision 1.2  2001/10/05 21:15:09  uzadow
|      Improved support for OS/2 bitmap decoding.
|
|      Revision 1.1  2001/10/03 14:00:29  uzadow
|      Much improved quality in FilterResizeBilinear.
|
|
\--------------------------------------------------------------------
*/
