/*
/--------------------------------------------------------------------
|
|      $Id: plddrawbmp.h,v 1.1 2001/09/16 19:03:23 uzadow Exp $
|      Bitmap class using a directdraw surface.
|
|      Copyright (c) 1996-1998 Ulrich von Zadow
|
\--------------------------------------------------------------------
*/

#ifndef INCL_DDRAWBMP
#define INCL_DDRAWBMP

#include "plbitmap.h"

#include <ddraw.h>

//! 
class PLDDrawBmp : public PLBmp
{

DECLARE_DYNAMIC (PLDDrawBmp);

public:
  //! Creates an empty bitmap.
  PLDDrawBmp
    ( IDirectDraw * pDDraw
    );

  //! Destroys the bitmap.
  virtual ~PLDDrawBmp
    ();

#ifdef _DEBUG
  virtual void AssertValid
    () const;    // Tests internal object state
#endif

  // PLDDrawBmp information

  //! Returns the amount of memory used by the object.
  virtual long GetMemUsed
    ();

  //! Returns number of bytes used per line.
  long GetBytesPerLine
    ();

  //! Returns the size of the bitmap in pixels
  SIZE GetSize
    ();

  //! Draws the bitmap.
//  virtual void Blt
//    ();

  //! Locks the DirectDraw surface and fills the line array. GetLineArray() 
  //! returns NULL if the surface isn't locked.
  virtual void Lock
    ( bool bReadable,
      bool bWriteable
    );

  //! Unlocks the DirectDraw surface.
  virtual void Unlock
    ();
 
  //! Gets a pointer to the directdraw surface used.
  IDirectDrawSurface * GetSurface
    ();

protected:

  // Protected callbacks

  //! Create a new empty DIB. Bits are uninitialized.
  //! Assumes that no memory is allocated before the call.
  virtual void internalCreate
    ( LONG Width,
      LONG Height,
      WORD BitsPerPixel,
      bool bAlphaChannel
    );

  //! Deletes memory allocated by member variables.
  virtual void freeMembers
    ();

  //! Initializes internal table of line addresses.
  virtual void initLineArray
    ();

  // Set color table pointer & pointer to bits
  virtual void initPointers
    ();

private:

  // Member variables.
  IDirectDrawSurface * m_pSurface;
  DDSURFACEDESC * m_pDDSurfaceDesc;
  IDirectDraw * m_pDDraw;
};

#endif
/*
/--------------------------------------------------------------------
|
|      $Log: plddrawbmp.h,v $
|      Revision 1.1  2001/09/16 19:03:23  uzadow
|      Added global name prefix PL, changed most filenames.
|
|      Revision 1.1  2000/08/13 12:11:43  Administrator
|      Added experimental DirectDraw-Support
|
|
\--------------------------------------------------------------------
*/
