/*
/--------------------------------------------------------------------
|
|      $Id: pldibsect.h,v 1.1 2001/09/16 19:03:23 uzadow Exp $
|
|      Copyright (c) 1996-1998 Ulrich von Zadow
|
\--------------------------------------------------------------------
*/

#ifndef INCL_DIBSECT
#define INCL_DIBSECT

#ifndef INCL_WINBMP
#include "plwinbmp.h"
#endif

//! This is a windows DIBSection wrapped in a PLBmp-derived class.
//! It can be used just like a PLWinBmp can be used. In addition,
//! PLDIBSection can give access to the bitmap as a GDI bitmap handle.
//! This bitmap handle can be selected into a device context. All
//! normal GDI drawing functions can be used to write on the bitmap
//! in this way.
//!
//! Internally, PLDIBSections are stored with header and bits in two
//! separate buffers.
class PLDIBSection : public PLWinBmp
{

public:
  //! Creates an empty bitmap.
  PLDIBSection
    ();

  //! Destroys the bitmap.
  virtual ~PLDIBSection
    ();

  //! Copy constructor
  PLDIBSection
    ( const PLBmp &Orig
    );

  //! Copy constructor
  PLDIBSection
    ( const PLDIBSection &Orig
    );

  //! Assignment operator.
  PLDIBSection &operator=
    ( PLBmp const &Orig
    );

  //! Assignment operator.
  PLDIBSection &operator=
    ( PLDIBSection const &Orig
    );

#ifdef _DEBUG
  virtual void AssertValid
    () const;    // Tests internal object state
#endif

  //! Calling this function causes the windows DIBSection to be detached
  //! from the PLDIBSection object. The bitmap data are not deleted in
  //! this function. This means that the bitmap handle and
  //! the bitmap memory (bits and BMI) must be deleted by some other object.
  //! The PLDIBSection object is in the same state as after a constructor
  //! call after this function is called.
  virtual void Detach
    ();

  // PLDIBSection output

  //! Draws the bitmap on the given device context using
  //! BitBlt.
  virtual void Draw
    ( HDC hDC,
      int x,
      int y,
      DWORD rop = SRCCOPY
    );

  //! Draws a portion of the bitmap on the given device context
  virtual BOOL DrawExtract
    ( HDC hDC,
      POINT pntDest,
      RECT rcSrc
    );

  // PLDIBSection member access

  //! Returns a GDI handle to the bitmap. This handle can be selected
  //! into a DC and used in normal GDI operations.
  //! Under Windows NT, GDI operations can be queued. This means that
  //! a program running under NT must call GdiFlush() before the
  //! DIBSection can be used again after GetHandle() has been called.
  //! See the documentation for GdiFlush() for details.
  HBITMAP GetHandle
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

  // Creates a PLDIBSection from an existing bitmap pointer.
  // Assumes that no memory is allocated before the call.
  virtual void internalCreate
    ( BITMAPINFOHEADER* pBMI
    );

  //! Deletes memory allocated by member variables.
  virtual void freeMembers
    ();

  //! Creates a copy of the current bitmap in a global memory block
  //! and returns a handle to this block.
  virtual HANDLE createCopyHandle
    ();

  //! Set color table pointer & pointer to bits based on m_pBMI.
  virtual void initPointers
    ();


protected:
  // Local functions

  // Member variables.
  HBITMAP  m_hBitmap;

  bool     m_bOwnsBitmap;
};

// Note that _both_ these copy constructors are needed. If only the 
// second one is there, the compiler generates a default copy 
// constructor anyway :-(.
inline PLDIBSection::PLDIBSection
    ( const PLDIBSection &Orig
    )
{
  // Delete everything the base class allocated.
  free(m_pBMI);
  m_pBMI = NULL;

  delete [] m_pLineArray;
  m_pLineArray = NULL;

  internalCopy (Orig);
}

inline PLDIBSection::PLDIBSection
    ( const PLBmp &Orig
    )
{
  // Delete everything the base class allocated.
  free(m_pBMI);
  m_pBMI = NULL;

  delete [] m_pLineArray;
  m_pLineArray = NULL;

  internalCopy (Orig);
}


inline PLDIBSection & PLDIBSection::operator=
    ( PLBmp const &Orig
    )
{
  PLBmp::operator=(Orig);
  return *this;
}

inline PLDIBSection & PLDIBSection::operator=
    ( PLDIBSection const &Orig
    )
{
  PLBmp::operator=(Orig);
  return *this;
}


#endif
/*
/--------------------------------------------------------------------
|
|      $Log: pldibsect.h,v $
|      Revision 1.1  2001/09/16 19:03:23  uzadow
|      Added global name prefix PL, changed most filenames.
|
|      Revision 1.12  2001/01/21 14:28:22  uzadow
|      Changed array cleanup from delete to delete[].
|
|      Revision 1.11  2000/12/09 12:16:26  uzadow
|      Fixed several memory leaks.
|
|      Revision 1.10  2000/11/02 21:28:47  uzadow
|      Fixed copy constructors.
|
|      Revision 1.9  2000/07/19 12:23:15  Ulrich von Zadow
|      Changed HANDLE to HBITMAP.
|
|      Revision 1.8  2000/07/07 13:20:03  Ulrich von Zadow
|      Comments
|
|      Revision 1.7  2000/01/17 23:37:12  Ulrich von Zadow
|      Corrected bug in assignment operator.
|
|      Revision 1.6  2000/01/16 20:43:17  anonymous
|      Removed MFC dependencies
|
|
\--------------------------------------------------------------------
*/
