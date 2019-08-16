/*
/--------------------------------------------------------------------
|
|      $Id: plfilterfill.cpp,v 1.1 2001/09/16 19:03:23 uzadow Exp $
|
\--------------------------------------------------------------------
*/

#include "plstdpch.h"
#include "plfilterfill.h"
#include "plfilterfillrect.h"
#include "plbitmap.h"

PLFilterFill::PLFilterFill(const PLPixel32& Color)
  : PLFilter(),
    m_Color (Color)
{
}

PLFilterFill::~PLFilterFill()
{
}

void PLFilterFill::ApplyInPlace(PLBmp * pBmp) const
{
  pBmp->ApplyFilter (PLFilterFillRect<PLPixel32> (PLPoint(0,0),
                                                PLPoint (pBmp->GetWidth(), pBmp->GetHeight()),
                                                m_Color));
}

/*
/--------------------------------------------------------------------
|
|      $Log: plfilterfill.cpp,v $
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

