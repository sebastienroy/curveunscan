/*
/--------------------------------------------------------------------
|
|      $Id: plrect.h,v 1.2 2001/09/28 19:50:56 uzadow Exp $
|
|      Copyright (c) 1996-1998 Ulrich von Zadow
|
\--------------------------------------------------------------------
*/

#ifndef INCL_PLRECT
#define INCL_PLRECT

#include "plpoint.h"

//!
class PLRect
{
public:
  PLPoint tl;
  PLPoint br;

  //!
  PLRect
  ();

  //!
  PLRect
  ( int left,
    int top,
    int right,
    int bottom
  );

  //!
  PLRect
  ( const PLPoint& TL,
    const PLPoint& BR
  );

  //!
  bool operator ==
  ( const PLRect & rect
  ) const;

  //!
  bool operator !=
  ( const PLRect & rect
  ) const;

  //!
  int Width 
  () const;

  //!
  int Height
  () const;

};

inline PLRect::PLRect
()
{}

inline PLRect::PLRect
  ( const PLPoint& TL,
    const PLPoint& BR
  ): tl(TL), br(BR)
{}

inline PLRect::PLRect
  ( int left,
    int top,
    int right,
    int bottom
  ) : tl(left, top), 
      br (right, bottom)
{}

inline bool PLRect::operator ==
( const PLRect & rect
) const
{
  return (tl == rect.tl && br == rect.br);
}

inline bool PLRect::operator !=
( const PLRect & rect
) const
{
  return !(rect==*this);
}

inline int PLRect::Width 
() const
{
  return br.x-tl.x;
}

inline int PLRect::Height
() const
{
  return br.y-tl.y;
}

#endif

/*
/--------------------------------------------------------------------
|
|      $Log: plrect.h,v $
|      Revision 1.2  2001/09/28 19:50:56  uzadow
|      Added some 24 bpp stuff & other minor features.
|
|      Revision 1.1  2001/09/24 14:24:52  uzadow
|      Added PLRect.
|
|      Revision 1.4  2001/09/16 19:03:22  uzadow
|      Added global name prefix PL, changed most filenames.
|
|      Revision 1.3  2000/11/21 20:20:36  uzadow
|      Changed bool to bool.
|
|      Revision 1.2  2000/01/10 23:52:59  Ulrich von Zadow
|      Changed formatting & removed tabs.
|
|      Revision 1.1  1999/12/09 16:35:58  Ulrich von Zadow
|      Added PLRect.
|
|
\--------------------------------------------------------------------
*/
