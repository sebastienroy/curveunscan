/*
/--------------------------------------------------------------------
|
|      $Id: plfilterintensity.cpp,v 1.4 2001/10/16 17:12:26 uzadow Exp $
|
|      Copyright (c) 1996-1998 Ulrich von Zadow
|
\--------------------------------------------------------------------
*/

#include "plstdpch.h"
#include "plfilterintensity.h"
#include "plbitmap.h"
#include "plpaintlibdefs.h"

#include  <math.h>

PLFilterIntensity::PLFilterIntensity(double intensity, PLBYTE offset, double exponent)
  : PLFilter(),
    m_intensity(intensity),
    m_offset(offset),
    m_exponent(exponent)
{

}

PLFilterIntensity::~PLFilterIntensity()
{

}

void PLFilterIntensity::Apply(PLBmp * pBmpSource, PLBmp * pBmpDest) const 
{
  double h, s, v;
  double intensityFactor;
  int total = 0;
  register int inc;
  extern void fp_rgb_to_hsv(double* r, double* g, double *b);
  extern void fp_hsv_to_rgb(double* r, double* g, double *b);

  // double intensity = 4.0 * m_intensity - 200.0;
  double intensity = m_intensity-20;
  intensity /= 4.0;
  PLASSERT (pBmpSource->GetBitsPerPixel() >= 24);

  pBmpDest->Create (pBmpSource->GetWidth(), 
                    pBmpSource->GetHeight(),
                    pBmpSource->GetBitsPerPixel(),
                    pBmpSource->HasAlpha(),
                    pBmpSource->GetResolution());

  PLBYTE ** pSrcLines = pBmpSource->GetLineArray();
  PLBYTE ** pDstLines = pBmpDest->GetLineArray();

  register int destWidth = pBmpDest->GetWidth();

  if(pBmpSource->GetBitsPerPixel() == 24)
   inc = 3;

  if(pBmpSource->GetBitsPerPixel() == 32)
   inc = sizeof(PLPixel32);

  double csupp = intensity/pow(255.0, m_exponent);

  for (int y = 0; y < pBmpDest->GetHeight(); ++y)
  { // For each line
    PLBYTE * pSrcPixel = pSrcLines[y];
    PLBYTE * pDstPixel = pDstLines[y];

    for (register int x = 0; x < destWidth; ++x)
    {
       // Transform rgb->hsv
       h =(double) pSrcPixel[PL_RGBA_RED];
       s =(double) pSrcPixel[PL_RGBA_GREEN];
       v =(double) pSrcPixel[PL_RGBA_BLUE];

       fp_rgb_to_hsv(&h, &s, &v);

       // Modify the intensity
       if (v >= m_offset)
        intensityFactor = 1.0 + csupp * pow((v-m_offset), m_exponent);
       else
        intensityFactor = 1.0;

       v *= intensityFactor;

       // Transform back to rgb.
       fp_hsv_to_rgb(&h, &s, &v);

       pDstPixel[PL_RGBA_RED]   = (PLBYTE) h;
       pDstPixel[PL_RGBA_GREEN] = (PLBYTE) s;
       pDstPixel[PL_RGBA_BLUE]  = (PLBYTE) v;

       if(h >= 255.0)
         pDstPixel[PL_RGBA_RED]   = (PLBYTE) 255;
       if(s >= 255.0)
         pDstPixel[PL_RGBA_GREEN] = (PLBYTE) 255;
       if(v >= 255.0)
         pDstPixel[PL_RGBA_BLUE]  = (PLBYTE) 255;
       if(h <= 0.0)
         pDstPixel[PL_RGBA_RED]   = (PLBYTE) 0;
       if(s <= 0.0)
         pDstPixel[PL_RGBA_GREEN] = (PLBYTE) 0;
       if(v <= 0.0)
         pDstPixel[PL_RGBA_BLUE]  = (PLBYTE) 0;

       pSrcPixel += inc;
       pDstPixel += inc;
    }
  }
}

/*
/--------------------------------------------------------------------
|
|      $Log: plfilterintensity.cpp,v $
|      Revision 1.4  2001/10/16 17:12:26  uzadow
|      Added support for resolution information (Luca Piergentili)
|
|      Revision 1.3  2001/10/06 22:03:26  uzadow
|      Added PL prefix to basic data types.
|
|      Revision 1.2  2001/10/06 15:32:22  uzadow
|      Removed types LPBYTE, DWORD, UCHAR, VOID and INT from the code.
|
|      Revision 1.1  2001/09/16 19:03:23  uzadow
|      Added global name prefix PL, changed most filenames.
|
|      Revision 1.5  2001/09/15 21:02:44  uzadow
|      Cleaned up stdpch.h and config.h to make them internal headers.
|
|      Revision 1.4  2001/02/04 14:31:52  uzadow
|      Member initialization list cleanup (Erik Hoffmann).
|
|      Revision 1.3  2001/01/15 15:05:31  uzadow
|      Added PLBmp::ApplyFilter() and PLBmp::CreateFilteredCopy()
|
|      Revision 1.2  2000/12/18 22:42:53  uzadow
|      Replaced RGBAPIXEL with PLPixel32.
|
|      Revision 1.1  2000/11/06 23:20:22  uzadow
|      Added Contrast, Intensity and Lightness filters by
|      Thomas Hirschmann
|
|
\--------------------------------------------------------------------
*/
