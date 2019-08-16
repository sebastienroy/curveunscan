/*
/--------------------------------------------------------------------
|
|      $Id: plfiltergrayscale.cpp,v 1.3 2001/10/16 17:12:26 uzadow Exp $
|
|      Copyright (c) 1996-1998 Ulrich von Zadow
|
\--------------------------------------------------------------------
*/

#include "plstdpch.h"
#include "plfiltergrayscale.h"
#include "plbitmap.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

PLFilterGrayscale::PLFilterGrayscale() : PLFilter()
{
}

PLFilterGrayscale::~PLFilterGrayscale()
{

}

void PLFilterGrayscale::Apply(PLBmp * pBmpSource, PLBmp * pBmpDest) const
{
  // Only works for 32 bpp bitmaps at the moment.
  PLASSERT (pBmpSource->GetBitsPerPixel() == 32);

  pBmpDest->Create (pBmpSource->GetWidth(), pBmpSource->GetHeight(), 8,
                    false, pBmpSource->GetResolution());
  PLBYTE ** pSrcLines = pBmpSource->GetLineArray();
  PLBYTE ** pDstLines = pBmpDest->GetLineArray();

  for (int y = 0; y<pBmpDest->GetHeight(); ++y)
  { // For each line
    PLBYTE * pSrcPixel = pSrcLines[y];
    PLBYTE * pDstPixel = pDstLines[y];

    for (int x = 0; x < pBmpDest->GetWidth(); ++x)
    { // For each pixel
      // For the coefficients used, see http://www.inforamp.net/~poynton/
      // We could approximate this for more speed by using
      // Y = (54 * R + 183 * G + 19 * B)/256 like libpng does.
      *pDstPixel = PLBYTE (pSrcPixel[PL_RGBA_RED]*0.212671+
                         pSrcPixel[PL_RGBA_GREEN]*0.715160+
                         pSrcPixel[PL_RGBA_BLUE]*0.072169);
      pSrcPixel += sizeof(PLPixel32);
      ++pDstPixel;
    }
  }
}

/*
/--------------------------------------------------------------------
|
|      $Log: plfiltergrayscale.cpp,v $
|      Revision 1.3  2001/10/16 17:12:26  uzadow
|      Added support for resolution information (Luca Piergentili)
|
|      Revision 1.2  2001/10/06 22:37:08  uzadow
|      Linux compatibility.
|
|      Revision 1.1  2001/09/16 19:03:23  uzadow
|      Added global name prefix PL, changed most filenames.
|
|      Revision 1.7  2001/02/04 14:31:52  uzadow
|      Member initialization list cleanup (Erik Hoffmann).
|
|      Revision 1.6  2001/01/15 15:05:31  uzadow
|      Added PLBmp::ApplyFilter() and PLBmp::CreateFilteredCopy()
|
|      Revision 1.5  2000/12/18 22:42:53  uzadow
|      Replaced RGBAPIXEL with PLPixel32.
|
|      Revision 1.4  2000/09/26 10:47:41  Administrator
|      Added comment
|
|      Revision 1.3  2000/01/16 20:43:15  anonymous
|      Removed MFC dependencies
|
|      Revision 1.2  1999/12/08 16:31:40  Ulrich von Zadow
|      Unix compatibility
|
|      Revision 1.1  1999/10/21 16:05:17  Ulrich von Zadow
|      Moved filters to separate directory. Added Crop, Grayscale and
|      GetAlpha filters.
|
|      Revision 1.1  1999/10/19 21:29:44  Ulrich von Zadow
|      Added filters.
|
|
\--------------------------------------------------------------------
*/
