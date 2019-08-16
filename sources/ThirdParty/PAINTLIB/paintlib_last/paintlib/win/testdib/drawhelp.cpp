/*
/--------------------------------------------------------------------
|
|      $Id: drawhelp.cpp,v 1.3 2001/09/16 19:03:23 uzadow Exp $
|
|      Copyright (c) 1996-1998 Ulrich von Zadow
|
--------------------------------------------------------------------
*/

#include "stdafx.h"

#include "drawhelp.h"
#include "dibgrit.h"


void DrawOnBmp
    ( PLBmp * pDestBmp,
      CRect * pDestRect,
      PLBmp * pSrPLBmp,
      BYTE Opacity
    )
{
  CDIBGrItem DIBItem (pDestRect->left, pDestRect->top,
                      pDestRect->Width(), pDestRect->Height(),
                      0, Opacity, pSrPLBmp);

  DIBItem.Draw (pDestBmp, pDestRect);
}
/*
/--------------------------------------------------------------------
|
|      $Log: drawhelp.cpp,v $
|      Revision 1.3  2001/09/16 19:03:23  uzadow
|      Added global name prefix PL, changed most filenames.
|
|
--------------------------------------------------------------------
*/
