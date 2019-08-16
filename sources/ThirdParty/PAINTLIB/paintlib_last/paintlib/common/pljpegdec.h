/*
/--------------------------------------------------------------------
|
|      $Id: pljpegdec.h,v 1.2 2001/10/21 17:12:40 uzadow Exp $
|
|      Copyright (c) 1996-1998 Ulrich von Zadow
|
\--------------------------------------------------------------------
*/

#ifndef INCL_PLJPEGDEC
#define INCL_PLJPEGDEC

#ifndef INCL_PLPICDEC
#include "plpicdec.h"
#endif

#include <stdio.h>

extern "C"
{
#include "jpeglib.h"
}

//! JPEG file decoder. Uses the independent JPEG group's library
//! to do the actual conversion.
class PLJPEGDecoder : public PLPicDecoder
{


public:
  //! Creates a decoder
  PLJPEGDecoder
    ();

  //! Destroys a decoder
  ~PLJPEGDecoder
    ();

/* I used this function to test the IJPEG rouines without a custom
   data source. If something goes wrong, it may still be useful to
   isolate bugs.
  PLBmp * MakeBmpFromFile
    ( char * pszFName
    );
*/

  //! true (the default) selects fast but sloppy decoding.
  void SetFast
    ( bool bFast
    );

  // Jo Hagelberg 15.4.99
  // this must be static as it's passed to extern C
  //! callback for jpeglib's progress notification
  static void JNotification
    (j_common_ptr cinfo
    );

protected:
  //! Sets up the jpeg library data source and error handler and
  //! calls the jpeg decoder.
  void DoDecode
    ( PLBmp * pBmp,
      PLDataSource * pDataSrc
    );

private:
  // Assumes IJPEG decoder is already set up.
  void decodeGray
    ( PLBmp * pBmp,
      int w,
      int h
    );

  // Assumes IJPEG decoder is already set up.
  void decodeRGB
    ( PLBmp * pBmp,
      int w,
      int h
    );

  jpeg_decompress_struct cinfo;  // IJPEG decoder state.
  jpeg_error_mgr         jerr;   // Custom error manager.

  bool  m_bFast;  // true selects fast but sloppy decoding.
};

#endif
/*
/--------------------------------------------------------------------
|
|      $Log: pljpegdec.h,v $
|      Revision 1.2  2001/10/21 17:12:40  uzadow
|      Added PSD decoder beta, removed BPPWanted from all decoders, added PLFilterPixel.
|
|      Revision 1.1  2001/09/16 19:03:22  uzadow
|      Added global name prefix PL, changed most filenames.
|
|      Revision 1.8  2001/09/15 21:02:44  uzadow
|      Cleaned up stdpch.h and config.h to make them internal headers.
|
|      Revision 1.7  2000/12/18 22:42:52  uzadow
|      Replaced RGBAPIXEL with PLPixel32.
|
|      Revision 1.6  2000/01/16 20:43:13  anonymous
|      Removed MFC dependencies
|
|      Revision 1.5  1999/12/08 15:39:45  Ulrich von Zadow
|      Unix compatibility changes
|
|      Revision 1.4  1999/11/27 18:45:48  Ulrich von Zadow
|      Added/Updated doc comments.
|
|
\--------------------------------------------------------------------
*/
