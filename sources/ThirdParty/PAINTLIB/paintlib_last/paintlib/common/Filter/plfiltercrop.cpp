/*
/--------------------------------------------------------------------
|
|      $Id: plfiltercrop.cpp,v 1.5 2001/10/16 17:12:26 uzadow Exp $
|
|      Copyright (c) 1996-1998 Ulrich von Zadow
|
\--------------------------------------------------------------------
*/

#include "plstdpch.h"
#include "plfiltercrop.h"
#include "plbitmap.h"


PLFilterCrop::PLFilterCrop(int XMin, int YMin, int XMax, int YMax)
  : PLFilter(),
    m_XMin(XMin),
    m_XMax(XMax),
    m_YMin(YMin),
    m_YMax(YMax)
{
}

PLFilterCrop::~PLFilterCrop()
{

}

void PLFilterCrop::Apply(PLBmp * pBmpSource, PLBmp * pBmpDest) const
{
  PLASSERT (m_XMin >= 0);
  PLASSERT (m_XMax <= pBmpSource->GetWidth());
  PLASSERT (m_YMin >= 0);
  PLASSERT (m_YMax <= pBmpSource->GetHeight());
  PLASSERT (m_XMin < m_XMax);
  PLASSERT (m_YMin < m_YMax);
  // Only 8, 24 and 32 bpp supported for now.
  PLASSERT (pBmpSource->GetBitsPerPixel() == 8 ||
            pBmpSource->GetBitsPerPixel() == 24 ||
            pBmpSource->GetBitsPerPixel() == 32);

  pBmpDest->Create (m_XMax-m_XMin, m_YMax-m_YMin,
                    pBmpSource->GetBitsPerPixel(), pBmpSource->HasAlpha(),
                    pBmpSource->GetResolution());
  PLBYTE ** pSrcLineArray = pBmpSource->GetLineArray();
  PLBYTE ** pDstLineArray = pBmpDest->GetLineArray();

  int y;
  for (y = m_YMin; y < m_YMax; y++)
  {
    PLBYTE * pSrcLine = pSrcLineArray[y];
    PLBYTE * pDstLine = pDstLineArray[y-m_YMin];
    int BytesPerPixel = pBmpSource->GetBitsPerPixel()/8;
    memcpy (pDstLine, pSrcLine + m_XMin*BytesPerPixel, (m_XMax-m_XMin)*BytesPerPixel);
  }
  if (pBmpSource->GetBitsPerPixel() == 8)
  {
    pBmpDest->SetPalette(pBmpSource->GetPalette());
  }
}

/*
/--------------------------------------------------------------------
|
|      $Log: plfiltercrop.cpp,v $
|      Revision 1.5  2001/10/16 17:12:26  uzadow
|      Added support for resolution information (Luca Piergentili)
|
|      Revision 1.4  2001/10/06 22:37:08  uzadow
|      Linux compatibility.
|
|      Revision 1.3  2001/09/30 19:55:37  uzadow
|      Fixed bug for 8 bpp in PLFilterCrop.
|
|      Revision 1.2  2001/09/28 19:50:56  uzadow
|      Added some 24 bpp stuff & other minor features.
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
|      Revision 1.5  2000/09/26 10:47:26  Administrator
|      no message
|
|      Revision 1.4  2000/01/16 20:43:15  anonymous
|      Removed MFC dependencies
|
|      Revision 1.3  1999/12/08 16:31:40  Ulrich von Zadow
|      Unix compatibility
|
|      Revision 1.2  1999/10/21 18:48:03  Ulrich von Zadow
|      no message
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
