/*
/--------------------------------------------------------------------
|
|      $Id: plfilterflip.cpp,v 1.3 2002/02/24 13:00:46 uzadow Exp $
|
|      Copyright (c) 1996-2002 Ulrich von Zadow
|      Original code by Richard Hollis
|
\--------------------------------------------------------------------
*/

#include "plstdpch.h"
#include "plbitmap.h"
#include "plfilterflip.h"
#include "plpoint.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

PLFilterFlip::PLFilterFlip() : PLFilter()
{}


PLFilterFlip::~PLFilterFlip()
{}


void PLFilterFlip::Apply(PLBmp * pBmpSource, PLBmp * pBmpDest) const
{
  PLASSERT (pBmpSource->GetBitsPerPixel() == 32);
  int nWidth = pBmpSource->GetWidth();
  int nHeight= pBmpSource->GetHeight();

  int x,y;

  //ROTATE the bitmap
  pBmpDest->Create (nWidth, nHeight, pBmpSource->GetBitsPerPixel(), 
                    pBmpSource->HasAlpha(), pBmpSource->GetResolution());
  PLPixel32 pix;

  for (y = 0; y<nHeight; y++)
  {
    for (x = 0; x<nWidth; x++)
    {
      pix = pBmpSource->GetPixel(x,y);
      pBmpDest->SetPixel(x,(nHeight- y)-1,pix);
    }
  }

  PLPixel32 * pPalette = pBmpSource->GetPalette();
  if ((pBmpSource->GetBitsPerPixel()<16) && (pPalette))
    pBmpDest->SetPalette(pPalette);
}

/*
/--------------------------------------------------------------------
|
|      $Log: plfilterflip.cpp,v $
|      Revision 1.3  2002/02/24 13:00:46  uzadow
|      Documentation update; removed buggy PLFilterRotate.
|
|      Revision 1.2  2001/10/16 17:12:26  uzadow
|      Added support for resolution information (Luca Piergentili)
|
|      Revision 1.1  2001/09/16 19:03:23  uzadow
|      Added global name prefix PL, changed most filenames.
|
|      Revision 1.3  2001/02/04 14:31:52  uzadow
|      Member initialization list cleanup (Erik Hoffmann).
|
|      Revision 1.2  2001/01/15 15:05:31  uzadow
|      Added PLBmp::ApplyFilter() and PLBmp::CreateFilteredCopy()
|
|      Revision 1.1  2001/01/13 20:06:16  uzadow
|      Added Flip and Mirror filters.
|
|
|
\--------------------------------------------------------------------
*/
