/*
/--------------------------------------------------------------------
|
|      $Id: plpngdec.h,v 1.2 2001/10/21 17:12:40 uzadow Exp $
|
|      Copyright (c) 1996-1998 Ulrich von Zadow
|
--------------------------------------------------------------------
*/

#ifndef INCL_PLPNGDEC
#define INCL_PLPNGDEC

#ifndef INCL_PLPICDEC
#include "plpicdec.h"
#endif

#ifndef INCL_PLPNG
#include "png.h"
#endif



//! PNG file decoder. Uses LibPng to do the actual decoding.
//! PNG supports many pixel formats not supported by paintlib. These
//! pixel formats are converted to the nearest paintlib equivalent.
//! Images with less or more than 8 bits per channel are converted to 
//! 8 bits per channel. Images with 16-bit palettes or grayscale 
//! images with an alpha channel are returned as full 32-bit RGBA 
//! bitmaps.
class PLPNGDecoder : public PLPicDecoder
{


public:
  //! Creates a decoder
  PLPNGDecoder
    ();

  //! Destroys a decoder
  virtual ~PLPNGDecoder
    ();

protected:
  //! Main decoder routine. Reads the header, creates the bitmap,
  //! reads the palette, and reads the image data.
  virtual void DoDecode
    ( PLBmp * pBmp,
      PLDataSource * pDataSrc
    );

private:

  static void PLPNGDecoder::user_error_fn
    ( png_structp png_ptr,
      png_const_charp error_msg
    );

  static void PLPNGDecoder::user_warning_fn
    ( png_structp png_ptr,
      png_const_charp warning_msg
    );
};

#endif
/*
/--------------------------------------------------------------------
|
|      $Log: plpngdec.h,v $
|      Revision 1.2  2001/10/21 17:12:40  uzadow
|      Added PSD decoder beta, removed BPPWanted from all decoders, added PLFilterPixel.
|
|      Revision 1.1  2001/09/16 19:03:22  uzadow
|      Added global name prefix PL, changed most filenames.
|
|      Revision 1.5  2000/12/18 22:42:52  uzadow
|      Replaced RGBAPIXEL with PLPixel32.
|
|      Revision 1.4  2000/01/16 20:43:14  anonymous
|      Removed MFC dependencies
|
|      Revision 1.3  1999/12/08 15:39:45  Ulrich von Zadow
|      Unix compatibility changes
|
|
--------------------------------------------------------------------
*/
