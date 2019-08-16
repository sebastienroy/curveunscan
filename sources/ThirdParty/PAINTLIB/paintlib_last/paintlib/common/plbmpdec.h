/*
/--------------------------------------------------------------------
|
|      $Id: plbmpdec.h,v 1.5 2001/10/21 17:12:39 uzadow Exp $
|
|      Copyright (c) 1996-1998 Ulrich von Zadow
|
\--------------------------------------------------------------------
*/

#ifndef INCL_PLBMPDEC
#define INCL_PLBMPDEC

#ifndef INCL_PLPICDEC
#include "plpicdec.h"
#endif

#ifndef INCL_PLWINDEFS
#include "plwindefs.h"
#endif

//! Windows bitmap file decoder. Decodes bitmap files (compressed and
//! uncompressed) of all bit depths. Returns an 8
//! or 32 bpp bitmap.
class PLBmpDecoder : public PLPicDecoder
{

public:
  //! Creates a decoder
  PLBmpDecoder
    ();

  //! Destroys a decoder
  virtual ~PLBmpDecoder
    ();

protected:
  //! Does the actual decoding of bitmap data.
  virtual void DoDecode
    ( PLBmp * pBmp,
      PLDataSource * pDataSrc
    );

private:

  // Decodes the bitmap file & info headers
  WINBITMAPINFOHEADER * getInfoHeader
    ( PLDataSource * pDataSrc,
      PLPixel32* Pal
    );

  // Decodes a 2-color bitmap. Ignores the palette & just uses
  // black & white as 'colors'
  void decode1bpp
    ( PLDataSource * pDataSrc,
      PLBmp * pBmp
    );

  // Decodes an uncompressed 16-color-bitmap.
  void decode4bpp
    ( PLDataSource * pDataSrc,
      PLBmp * pBmp
    );

  // Decodes an uncompressed 256-color-bitmap.
  void decode8bpp
    ( PLDataSource * pDataSrc,
      PLBmp * pBmp
    );

  // Decodes a compressed 16-color-bitmap.
  void decodeRLE4
    ( PLDataSource * pDataSrc,
      PLBmp * pBmp
    );

  // Decodes a compressed 256-color-bitmap.
  void decodeRLE8
    ( PLDataSource * pDataSrc,
      PLBmp * pBmp
    );

  void decodeHiColor
    ( PLDataSource * pDataSrc,
      PLBmp * pBmp,
      WINBITMAPINFOHEADER * pBMI
    );

  // Decodes true-color bitmap
  void decodeTrueColor
    ( PLDataSource * pDataSrc,
      PLBmp * pBmp,
      int SrcBPP
    );

  void decode15bppLine
    ( PLDataSource * pDataSrc,
      PLBmp * pBmp,
      PLBYTE * pDest
    );

  void decode16bppLine
    ( PLDataSource * pDataSrc,
      PLBmp * pBmp,
      PLBYTE * pDest
    );

  void decode24bppLine
    ( PLDataSource * pDataSrc,
      PLBmp * pBmp,
      PLBYTE * pDest
    );

  void decode32bppLine
    ( PLDataSource * pDataSrc,
      PLBmp * pBmp,
      PLBYTE * pDest
    );


  // Decodes two 4-bit pixels using a palette & puts them in pDest
  // and pDest+4.
  void decode2Nibbles
    ( PLBYTE * pDest,
      PLBYTE SrcByte
    );

  // Makes a private copy of the palette in the file and sets the
  // alpha channel. Returns the number of colors read.
  int readPalette
    ( WINBITMAPINFOHEADER * pBMI,     // Pointer to bitmapinfoheader in file.
      PLDataSource * pDataSrc,
      PLPixel32 * pPal,
      int RGBSize
    );

};

#endif
/*
/--------------------------------------------------------------------
|
|      $Log: plbmpdec.h,v $
|      Revision 1.5  2001/10/21 17:12:39  uzadow
|      Added PSD decoder beta, removed BPPWanted from all decoders, added PLFilterPixel.
|
|      Revision 1.4  2001/10/06 22:37:08  uzadow
|      Linux compatibility.
|
|      Revision 1.3  2001/10/06 20:44:45  uzadow
|      Linux compatibility
|
|      Revision 1.2  2001/10/05 21:15:09  uzadow
|      Improved support for OS/2 bitmap decoding.
|
|      Revision 1.1  2001/09/16 19:03:22  uzadow
|      Added global name prefix PL, changed most filenames.
|
|
\--------------------------------------------------------------------
*/
