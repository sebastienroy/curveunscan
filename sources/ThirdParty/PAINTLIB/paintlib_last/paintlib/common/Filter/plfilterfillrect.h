/*
/--------------------------------------------------------------------
|
|      $Id: plfilterfillrect.h,v 1.4 2002/02/10 22:53:26 uzadow Exp $
|
\--------------------------------------------------------------------
*/

#if !defined(INCL_PLFILTERFILLRECT)
#define INCL_PLFILTERFILLRECT

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "plfilter.h"
#include "../plpoint.h"

class PLBmp;

// Fills a rectangle in a Bitmap with a color
template<class PixelC> class PLFilterFillRect: public PLFilter
{
public:
    PLFilterFillRect (PLPoint min, PLPoint max, const PixelC& Color);
    virtual ~PLFilterFillRect();
    virtual void ApplyInPlace(PLBmp *pBmp) const;

private:
    PixelC m_Color;
    PLPoint m_min;
    PLPoint m_max;
};

template<class PixelC>
PLFilterFillRect<PixelC>::PLFilterFillRect
    (PLPoint min, PLPoint max, const PixelC& Color)
{
  m_min = min;
  m_max = max;
  m_Color = Color;
}

template<class PixelC>
PLFilterFillRect<PixelC>::~PLFilterFillRect ()
{

}

template<class PixelC>
void PLFilterFillRect<PixelC>::ApplyInPlace (PLBmp *pBmp) const
{
  PixelC** ppLines = (PixelC**)(pBmp->GetLineArray());
  for (int y=m_min.y; y<m_max.y; ++y)
  {
    PixelC* pLine = ppLines[y];
    for (int x=m_min.x; x<m_max.x; ++x)
      pLine[x] = m_Color;
  }
}

#endif

/*
/--------------------------------------------------------------------
|
|      $Log: plfilterfillrect.h,v $
|      Revision 1.4  2002/02/10 22:53:26  uzadow
|      Fixed cdoc problems.
|
|      Revision 1.3  2001/10/21 17:12:40  uzadow
|      Added PSD decoder beta, removed BPPWanted from all decoders, added PLFilterPixel.
|
|      Revision 1.2  2001/09/28 19:50:56  uzadow
|      Added some 24 bpp stuff & other minor features.
|
|      Revision 1.1  2001/09/16 19:03:23  uzadow
|      Added global name prefix PL, changed most filenames.
|
|      Revision 1.1  2001/09/13 20:48:42  uzadow
|      Added fill filters.
|
|      Revision 1.1  2001/09/13 10:39:31  uzadow
|      Added FilterFillRect
|
|
\--------------------------------------------------------------------
*/
