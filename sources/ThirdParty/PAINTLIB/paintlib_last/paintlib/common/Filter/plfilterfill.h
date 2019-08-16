/*
/--------------------------------------------------------------------
|
|      $Id: plfilterfill.h,v 1.4 2002/02/24 13:00:46 uzadow Exp $
|
\--------------------------------------------------------------------
*/

#if !defined(INCL_PLFILTERFILL)
#define INCL_PLFILTERFILL

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "plfilter.h"
#include "../plpixel32.h"

class PLBmp;

//! Fills a 32 bpp Bitmap completely with a color.
class PLFilterFill : public PLFilter
{
public:
  PLFilterFill (const PLPixel32& Color);
  virtual ~PLFilterFill();
  virtual void ApplyInPlace(PLBmp *pBmp) const;

private:
    PLPixel32 m_Color;
};
#endif

/*
/--------------------------------------------------------------------
|
|      $Log: plfilterfill.h,v $
|      Revision 1.4  2002/02/24 13:00:46  uzadow
|      Documentation update; removed buggy PLFilterRotate.
|
|      Revision 1.3  2002/02/11 16:45:37  uzadow
|      Fixed bug decoding 16 bit per channel tiffs.
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
|      Revision 1.2  2001/09/13 10:39:31  uzadow
|      Added FilterFillRect
|
|      Revision 1.1  2001/09/06 14:20:13  uzadow
|      Moved FilterFill to paintlib
|
|      Revision 1.1.2.1  2001/09/04 11:20:40  uzadow
|      Initial version: test works, no main program yet.
|
|
\--------------------------------------------------------------------
*/
