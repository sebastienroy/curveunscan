/*
/--------------------------------------------------------------------
|
|      $Id: plfilterresizegaussian.cpp,v 1.4 2001/10/16 17:12:27 uzadow Exp $
|
|      Copyright (c) 1996-1998 Ulrich von Zadow
|
\--------------------------------------------------------------------
*/

#include "plstdpch.h"
#include "plfilterresizegaussian.h"
#include "pl2passscale.h"
#include "plbitmap.h"


PLFilterResizeGaussian::PLFilterResizeGaussian (int NewXSize, int NewYSize, double NewRadius)
  : PLFilterResize (NewXSize, NewYSize),
    m_NewRadius(NewRadius)
{
}

void PLFilterResizeGaussian::Apply(PLBmp * pBmpSource, PLBmp * pBmpDest) const
{
  PLASSERT(pBmpSource->GetBitsPerPixel()==32);

  // Create a new Bitmap 
  pBmpDest->Create(m_NewXSize,
                   m_NewYSize,
                   pBmpSource->GetBitsPerPixel(),
                   pBmpSource->HasAlpha(),
                   pBmpSource->GetResolution());
                     
  // Create a Filter Class from template
  PLGaussianContribDef f (m_NewRadius);
  C2PassScale <CDataRGBA_UBYTE> sS(f);
  sS.Scale ((CDataRGBA_UBYTE::_RowType *) pBmpSource->GetLineArray(), 
             pBmpSource->GetWidth(), 
             pBmpSource->GetHeight(), 
             (CDataRGBA_UBYTE::_RowType *) pBmpDest->GetLineArray(),
             pBmpDest->GetWidth(),
             pBmpDest->GetHeight());
}

/*
/--------------------------------------------------------------------
|
|      $Log: plfilterresizegaussian.cpp,v $
|      Revision 1.4  2001/10/16 17:12:27  uzadow
|      Added support for resolution information (Luca Piergentili)
|
|      Revision 1.3  2001/09/30 16:57:26  uzadow
|      Improved speed of 2passfilter.h, code readability changes.
|
|      Revision 1.2  2001/09/16 20:57:17  uzadow
|      Linux version name prefix changes
|
|      Revision 1.1  2001/09/16 19:03:23  uzadow
|      Added global name prefix PL, changed most filenames.
|
|      Revision 1.4  2001/01/15 15:05:31  uzadow
|      Added PLBmp::ApplyFilter() and PLBmp::CreateFilteredCopy()
|
|      Revision 1.3  2000/01/16 20:43:16  anonymous
|      Removed MFC dependencies
|
|      Revision 1.2  1999/12/08 16:31:40  Ulrich von Zadow
|      Unix compatibility
|
|      Revision 1.1  1999/10/21 16:05:18  Ulrich von Zadow
|      Moved filters to separate directory. Added Crop, Grayscale and
|      GetAlpha filters.
|
|      Revision 1.1  1999/10/19 21:29:45  Ulrich von Zadow
|      Added filters.
|
|
\--------------------------------------------------------------------
*/
