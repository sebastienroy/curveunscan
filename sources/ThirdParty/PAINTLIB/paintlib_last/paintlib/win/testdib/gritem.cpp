/*
/--------------------------------------------------------------------
|
|      $Id: gritem.cpp,v 1.5 2002/02/24 13:00:57 uzadow Exp $
|      Graphic item class
|
|      Abstract base class for an item on a canvas.
|
|      Copyright (c) 1996-2002 Ulrich von Zadow
|
\--------------------------------------------------------------------
*/

#include "stdafx.h"
#include "gritem.h"
#include "plbitmap.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC (CGrItem, CObject);


CGrItem::CGrItem
    ( int x,            // Position on the canvas
      int y,
      int w,            // Width
      int h,            // Height
      int z,            // Position in z-Order
      BYTE Opacity      // Opacity of the object. 255 is completely
                        // opaque, 0 is completely transparent.
    )
{
  m_x = x;
  m_y = y;
  m_w = w;
  m_h = h;
  m_z = z;
  m_Opacity = Opacity;
}


CGrItem::~CGrItem
    ()
{
}


void CGrItem::GetRect
    ( CRect * pRect
    )
    // Returns dimensions as a rectangle.
{
  *pRect = CRect (CPoint (m_x, m_y), CSize (m_w, m_h));
}


void CGrItem::clip
    ( PLBmp * pDestBmp,
      CRect * pUpdRect
    )
    // Clips pUpdRect to the item and the canvas.
{
  CRect TempRect;
  CRect ItemRect (CPoint (m_x, m_y), CSize (m_w, m_h));
  CRect CanvasRect (CPoint (0,0),
                    CSize (pDestBmp->GetWidth()-1,
                           pDestBmp->GetHeight()-1));

  TempRect.IntersectRect (pUpdRect, &ItemRect);

  pUpdRect->IntersectRect (&TempRect, &CanvasRect);
}
/*
/--------------------------------------------------------------------
|
|      $Log: gritem.cpp,v $
|      Revision 1.5  2002/02/24 13:00:57  uzadow
|      Documentation update; removed buggy PLFilterRotate.
|
|      Revision 1.4  2001/09/16 19:03:23  uzadow
|      Added global name prefix PL, changed most filenames.
|
|      Revision 1.3  2000/01/16 20:43:19  anonymous
|      Removed MFC dependencies
|
|
\--------------------------------------------------------------------
*/
