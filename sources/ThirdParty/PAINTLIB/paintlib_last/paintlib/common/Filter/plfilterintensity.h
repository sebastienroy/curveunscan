/*
/--------------------------------------------------------------------
|
|      $Id: plfilterintensity.h,v 1.3 2002/02/24 13:00:47 uzadow Exp $
|
|      Copyright (c) 1996-2002 Ulrich von Zadow
|
\--------------------------------------------------------------------
*/

#if !defined(INCL_PLFILTERINTENSITY)
#define INCL_PLFILTERINTENSITY

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "plfilter.h"
#include "plpaintlibdefs.h"

class PLBmp;

//! Changes the intensity of a 24 or 32 bpp bitmap. 
//! Applies the factor intensityFactor = 1.0 + csupp * pow((v-m_offset), m_exponent)
//! with csupp = intensity/pow(255.0, m_exponent);
//! on the v-Value of the image after a HSV transform.
//! The bitmap stays unchanged for intensity = 20, offset = 128, exponent = 1.
class PLFilterIntensity : public PLFilter  
{
public:
	PLFilterIntensity (double intensity, PLBYTE offset, double exponent);
	virtual ~PLFilterIntensity();
  virtual void Apply(PLBmp *pBmpSource, PLBmp* pBmpDest) const;

protected:
  double m_intensity;
  double m_offset;
  double m_exponent;
};
#endif

/*
/--------------------------------------------------------------------
|
|      $Log: plfilterintensity.h,v $
|      Revision 1.3  2002/02/24 13:00:47  uzadow
|      Documentation update; removed buggy PLFilterRotate.
|
|      Revision 1.2  2001/10/06 22:03:26  uzadow
|      Added PL prefix to basic data types.
|
|      Revision 1.1  2001/09/16 19:03:23  uzadow
|      Added global name prefix PL, changed most filenames.
|
|      Revision 1.2  2001/01/15 15:05:31  uzadow
|      Added PLBmp::ApplyFilter() and PLBmp::CreateFilteredCopy()
|
|      Revision 1.1  2000/11/06 23:20:22  uzadow
|      Added Contrast, Intensity and Lightness filters by
|      Thomas Hirschmann
|
|
\--------------------------------------------------------------------
*/
