/*
/--------------------------------------------------------------------
|
|      $Id: plpixel32.h,v 1.5 2001/10/21 17:12:40 uzadow Exp $
|
|      Copyright (c) 1996-1998 Ulrich von Zadow
|
\--------------------------------------------------------------------
*/

#ifndef INCL_PLPIXEL32
#define INCL_PLPIXEL32

#include "plpixeldefs.h"
#include "plpaintlibdefs.h"

//! 32 bit pixel class. A pixel in this class contains 8 bits each of
//! red, green, blue and alpha. The order of the color components is
//! OS-dependent and defined in config.h. This class is meant to be
//! fast, so all methods are inlined.
class PLPixel32
{
  public:
    //!
    PLPixel32 ();
    //!
    PLPixel32 (PLBYTE r, PLBYTE g, PLBYTE b, PLBYTE a);
    //!
    PLPixel32 (PLBYTE r, PLBYTE g, PLBYTE b);
    //!
    void Set (PLBYTE r, PLBYTE g, PLBYTE b, PLBYTE a);
    //!
    void Set (PLBYTE r, PLBYTE g, PLBYTE b);
    //!
    void SetR (PLBYTE r);
    //!
    void SetG (PLBYTE g);
    //!
    void SetB (PLBYTE b);
    //!
    void SetA (PLBYTE a);
    //!
    PLBYTE GetR () const;
    //!
    PLBYTE GetG () const;
    //!
    PLBYTE GetB () const;
    //!
    PLBYTE GetA () const;

    //!
    bool operator ==(const PLPixel32 Pix) const;

    //!
    bool operator !=(const PLPixel32 Pix) const;

    //! Simple and fast 'distance' between two pixels. Just adds the
    //! distances between the color components and treats colors
    //! equally.
    int BoxDist (const PLPixel32 Pix) const;

    //! Returns a weighed average between two pixels. Factor must be 
    //! between 0 and 256. Factor=256 means Pix1 is the result, Factor=0 
    //! means Pix2 is the result.
    static PLPixel32 Blend (int Factor, const PLPixel32 Pix1, 
                            const PLPixel32 Pix2);

  private:
    PLBYTE m_Data[4];
};

inline PLPixel32::PLPixel32()
{
}


inline PLPixel32::PLPixel32(PLBYTE r, PLBYTE g, PLBYTE b, PLBYTE a)
{
  Set (r, g, b, a);
}


inline PLPixel32::PLPixel32(PLBYTE r, PLBYTE g, PLBYTE b)
{
  Set (r, g, b, 255);
}


inline void PLPixel32::Set(PLBYTE r, PLBYTE g, PLBYTE b, PLBYTE a)
{
  m_Data[PL_RGBA_RED] = r;
  m_Data[PL_RGBA_GREEN] = g;
  m_Data[PL_RGBA_BLUE] = b;
  m_Data[PL_RGBA_ALPHA] = a;
}

//!
inline void PLPixel32::Set (PLBYTE r, PLBYTE g, PLBYTE b)
{
  m_Data[PL_RGBA_RED] = r;
  m_Data[PL_RGBA_GREEN] = g;
  m_Data[PL_RGBA_BLUE] = b;
}

inline void PLPixel32::SetR(PLBYTE r)
{
  m_Data[PL_RGBA_RED] = r;
}


inline void PLPixel32::SetG(PLBYTE g)
{
  m_Data[PL_RGBA_GREEN] = g;
}


inline void PLPixel32::SetB(PLBYTE b)
{
  m_Data[PL_RGBA_BLUE] = b;
}


inline void PLPixel32::SetA(PLBYTE a)
{
  m_Data[PL_RGBA_ALPHA] = a;
}


inline PLBYTE PLPixel32::GetR() const
{
  return m_Data[PL_RGBA_RED];
}


inline PLBYTE PLPixel32::GetG() const
{
  return m_Data[PL_RGBA_GREEN];
}


inline PLBYTE PLPixel32::GetB() const
{
  return m_Data[PL_RGBA_BLUE];
}


inline PLBYTE PLPixel32::GetA() const
{
  return m_Data[PL_RGBA_ALPHA];
}

inline int PLPixel32::BoxDist (const PLPixel32 Pix) const
{
  return (abs ((int)GetR()-Pix.GetR()) +
          abs ((int)GetG()-Pix.GetG()) +
          abs ((int)GetB()-Pix.GetB()));
}

inline PLPixel32 PLPixel32::Blend (int Factor, const PLPixel32 Pix1, const PLPixel32 Pix2)
{
  PLASSERT (Factor >= 0 && Factor <= 256);

  return PLPixel32 ((Pix1.GetR()*Factor+Pix2.GetR()*(256-Factor))>>8,
                    (Pix1.GetG()*Factor+Pix2.GetG()*(256-Factor))>>8,
                    (Pix1.GetB()*Factor+Pix2.GetB()*(256-Factor))>>8,
                    Pix1.GetA());
}

inline bool PLPixel32::operator ==(const PLPixel32 Pix) const
{
  return (*(const PLLONG *)this == *(const PLLONG*)&Pix);
}

inline bool PLPixel32::operator !=(const PLPixel32 Pix) const
{
  return (!(*this == Pix));
}


#endif

/*
/--------------------------------------------------------------------
|
|      $Log: plpixel32.h,v $
|      Revision 1.5  2001/10/21 17:12:40  uzadow
|      Added PSD decoder beta, removed BPPWanted from all decoders, added PLFilterPixel.
|
|      Revision 1.4  2001/10/06 22:03:26  uzadow
|      Added PL prefix to basic data types.
|
|      Revision 1.3  2001/09/28 19:50:56  uzadow
|      Added some 24 bpp stuff & other minor features.
|
|      Revision 1.2  2001/09/24 14:13:18  uzadow
|      Added Blend, improved const-correctness.
|
|      Revision 1.1  2001/09/16 19:03:22  uzadow
|      Added global name prefix PL, changed most filenames.
|
|      Revision 1.3  2001/09/15 14:30:20  uzadow
|      Fixed PLPixel32 initialization bug.
|
|      Revision 1.2  2001/09/13 20:45:35  uzadow
|      Added 8-bpp pixel class.
|
|      Revision 1.1  2000/12/18 22:42:52  uzadow
|      Replaced RGBAPIXEL with PLPixel32.
|
|
\--------------------------------------------------------------------
*/
