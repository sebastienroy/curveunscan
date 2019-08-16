/*
/--------------------------------------------------------------------
|
|      $Id: plpcxdec.h,v 1.3 2001/10/21 17:12:40 uzadow Exp $
|
|      Copyright (c) 1996-1998 Ulrich von Zadow
|
\--------------------------------------------------------------------
*/

#ifndef INCL_PLPCXDEC
#define INCL_PLPCXDEC

#ifndef INCL_PLPICDEC
#include "plpicdec.h"
#endif


//! PCX file decoder. Decodes 8, 15, 16, 24 and 32 bpp
//! PCX files (compressed and uncompressed) and returns an 8 or 32
//! bpp CBitmap. Preserves the alpha channel.
class PLPCXDecoder : public PLPicDecoder
{

public:
  //! Creates a decoder
  PLPCXDecoder();

  //! Destroys a decoder
  virtual ~PLPCXDecoder ();

protected:
  //! Main decoder routine. Reads the header, Creates the bitmap,
  //! reads the palette, and reads the image data.
  virtual void DoDecode (PLBmp * pBmp, PLDataSource * pDataSrc);

private:
  void PCX_PlanesToPixels(PLBYTE *pixels, PLBYTE *bitplanes,
                          short bytesperline, short planes, short bitsperpixel);
  void PCX_UnpackPixels(PLBYTE *pixels, PLBYTE *bitplanes,
                        short bytesperline, short planes, short bitsperpixel);
};

#endif

/*
/--------------------------------------------------------------------
|
|      $Log: plpcxdec.h,v $
|      Revision 1.3  2001/10/21 17:12:40  uzadow
|      Added PSD decoder beta, removed BPPWanted from all decoders, added PLFilterPixel.
|
|      Revision 1.2  2001/10/06 22:37:08  uzadow
|      Linux compatibility.
|
|      Revision 1.1  2001/09/16 19:03:22  uzadow
|      Added global name prefix PL, changed most filenames.
|
|      Revision 1.8  2000/12/18 22:42:52  uzadow
|      Replaced RGBAPIXEL with PLPixel32.
|
|      Revision 1.7  2000/01/16 20:43:13  anonymous
|      Removed MFC dependencies
|
|      Revision 1.6  2000/01/10 23:52:59  Ulrich von Zadow
|      Changed formatting & removed tabs.
|
|      Revision 1.5  1999/12/15 21:16:30  Ulrich von Zadow
|      Removed references to gif in pcx decoder.
|
|      Revision 1.4  1999/12/10 01:27:26  Ulrich von Zadow
|      Added assignment operator and copy constructor to
|      bitmap classes.
|
|      Revision 1.3  1999/12/08 15:39:45  Ulrich von Zadow
|      Unix compatibility changes
|
|      Revision 1.2  1999/11/27 18:45:48  Ulrich von Zadow
|      Added/Updated doc comments.
|
\--------------------------------------------------------------------
*/
