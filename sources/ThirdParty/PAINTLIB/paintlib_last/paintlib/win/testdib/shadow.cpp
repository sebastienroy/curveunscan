/*
/--------------------------------------------------------------------
|
|      $Id: shadow.cpp,v 1.5 2001/09/16 19:03:23 uzadow Exp $
|      Shadow Graphic item class
|
|      A shadowed region on a canvas. The item is basically a
|      partially transparent region. Transparency is defined by an
|      alpha DIB and a global transparency value. Most of the code
|      was just copied from CDIBGrItem & changed a bit.
|
|      Copyright (c) 1996-1998 Ulrich von Zadow
|
\--------------------------------------------------------------------
*/

#include "stdafx.h"
#include "shadow.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC (CShadowItem, CGrItem);


CShadowItem::CShadowItem
    ( int x,             // Position on the canvas
      int y,
      int w,             // Width
      int h,             // Height
      int z,             // Position in z-Order
      BYTE Opacity,      // Opacity of the object. 255 is completely
                         // opaque, 0 is completely transparent.
      PLPixel32 * pColor, // Shadow color.
      PLBmp * pAlphaBmp   // Alpha channel (must be 8 bpp). Can be NULL.
    )
  : CGrItem (x, y, w, h, z, Opacity)
{
  m_Color = *pColor;
  m_pAlphaBmp = pAlphaBmp;
  if (m_pAlphaBmp)
    m_pLineArray = m_pAlphaBmp->GetLineArray();
   else
    m_pLineArray = NULL;
}


CShadowItem::~CShadowItem
    ()
{
}


void CShadowItem::Draw
    ( PLBmp * pCanvas,
      CRect * pUpdateRect
    )
    // Responsible for drawing the object on the canvas.
{
//  ASSERT_VALID (pCanvas);
  ASSERT (pCanvas->GetBitsPerPixel() == 32);

  // Perform clipping.
  CRect ClipRect (pUpdateRect);
  clip (pCanvas, &ClipRect);

  // Draw
  if (m_pAlphaBmp)
  {
    if (m_w == m_pAlphaBmp->GetWidth() &&
        m_h == m_pAlphaBmp->GetHeight())
      drawClippedNoScale (pCanvas, &ClipRect);
     else
      drawClipped (pCanvas, &ClipRect);
  }
  else
    drawClippedNoScale (pCanvas, &ClipRect);

  // If this fails, the procedure destroyed something.
//  ASSERT_VALID (pCanvas);
}


void CShadowItem::drawClippedNoScale
    ( PLBmp * pCanvas,
      CRect * pRect
    )
    // Draws the object. pRect must have been clipped already.
    // Assumes that no scaling is nessesary.
{
  BYTE * pDest;
  BYTE * pAlpha;
  BYTE ** pDestLineArray = pCanvas->GetLineArray();

  // Set up loop invariants.
  int SrcXOfs = (pRect->left-m_x);

  for (int sy = pRect->top; sy<pRect->bottom; sy++)
  { // For each line
    pDest = pDestLineArray[sy] +  pRect->left*4;
    if (m_pAlphaBmp)
    {
      pAlpha = m_pLineArray[sy-m_y] + SrcXOfs;

      drawAlphaLine (pDest, pAlpha, pRect);
    }
    else
      drawFadeLine (pDest, pRect);
  }
}


inline void CShadowItem::drawAlphaLine
    ( BYTE * pDest,
      BYTE * pAlpha,
      CRect * pRect
    )
{
  int alpha;
  int negalpha;
  BYTE * pColor = (BYTE *)(&m_Color);  // Well...

  for (int sx = pRect->left; sx<pRect->right; sx++)
  { // For each pixel
    alpha = ((*pAlpha) * m_Opacity)>>8;
    negalpha = 255-alpha;
    pDest[PL_RGBA_RED] = (pDest[PL_RGBA_RED]*negalpha +
                       *(pColor+PL_RGBA_RED)*alpha)>>8;
    pDest[PL_RGBA_GREEN] = (pDest[PL_RGBA_GREEN]*negalpha +
                         *(pColor+PL_RGBA_GREEN)*alpha)>>8;
    pDest[PL_RGBA_BLUE] = (pDest[PL_RGBA_BLUE]*negalpha +
                        *(pColor+PL_RGBA_BLUE)*alpha)>>8;

    pDest += 4;
    pAlpha++;
  }
}


inline void CShadowItem::drawFadeLine
    ( BYTE * pDest,
      CRect * pRect
    )
    // Draws one line. No scaling. Assumes alpha channel doesn't
    // exist.
{
  int negalpha;
  BYTE * pColor = (BYTE *)(&m_Color);  // Well...
  BYTE Color[4];
  Color[PL_RGBA_BLUE] = *(pColor+PL_RGBA_BLUE)*m_Opacity>>8;
  Color[PL_RGBA_GREEN] = *(pColor+PL_RGBA_GREEN)*m_Opacity>>8;
  Color[PL_RGBA_RED] = *(pColor+PL_RGBA_RED)*m_Opacity>>8;
  negalpha = 255-m_Opacity;

  for (int sx = pRect->left; sx<pRect->right; sx++)
  { // For each pixel
    pDest[PL_RGBA_BLUE] = (pDest[PL_RGBA_BLUE]*negalpha>>8)+Color[PL_RGBA_BLUE];
    pDest[PL_RGBA_GREEN] = (pDest[PL_RGBA_GREEN]*negalpha>>8)+Color[PL_RGBA_GREEN];
    pDest[PL_RGBA_RED] = (pDest[PL_RGBA_RED]*negalpha>>8)+Color[PL_RGBA_RED];

    pDest += 4;
  }
}


void CShadowItem::drawClipped
    ( PLBmp * pCanvas,
      CRect * pRect
    )
    // Draws the object. pRect must have been clipped already.
{
  BYTE * pDest;
  BYTE * pAlpha = NULL;
  int SrcLineNum;
  BYTE ** pDestLineArray = pCanvas->GetLineArray();

  double YScale = (double)(m_pAlphaBmp->GetHeight())/m_h;

  for (int sy = pRect->top; sy<pRect->bottom; sy++)
  { // For each line
    pDest = pDestLineArray[sy] + pRect->left*4;
    SrcLineNum = (int)((sy-m_y)*YScale);
    pAlpha = m_pLineArray [SrcLineNum];
    drawScaleLine (pDest, pAlpha, pRect);
  }
}


inline void CShadowItem::drawScaleLine
    ( BYTE * pDest,
      BYTE * pAlpha,
      CRect * pRect
    )
{
  int alpha;
  int negalpha;
  int SrcOfs;
  double XScale = (double)(m_pAlphaBmp->GetWidth())/m_w;
  int xs = (int)(XScale*65536);
  BYTE * pColor = (BYTE *)(&m_Color);  // Well...

  for (int sx = pRect->left-m_x; sx<pRect->right-m_x; sx++)
  { // For each pixel
    SrcOfs = (sx*xs)>>16;
    if (pAlpha)
      alpha = ((*(pAlpha+SrcOfs)) * m_Opacity)>>8;
     else
      alpha = m_Opacity;
    negalpha = 255-alpha;
    pDest[PL_RGBA_BLUE] = (pDest[PL_RGBA_BLUE]*negalpha +
                       pColor[PL_RGBA_BLUE]*alpha)>>8;
    pDest[PL_RGBA_GREEN] = (pDest[PL_RGBA_GREEN]*negalpha +
                        pColor[PL_RGBA_GREEN]*alpha)>>8;
    pDest[PL_RGBA_RED] = (pDest[PL_RGBA_RED]*negalpha +
                      pColor[PL_RGBA_RED]*alpha)>>8;
    pDest += 4;
  }
}


/*
/--------------------------------------------------------------------
|
|      $Log: shadow.cpp,v $
|      Revision 1.5  2001/09/16 19:03:23  uzadow
|      Added global name prefix PL, changed most filenames.
|
|
--------------------------------------------------------------------
*/
