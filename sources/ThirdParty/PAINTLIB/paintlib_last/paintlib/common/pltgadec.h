/*
/--------------------------------------------------------------------
|
|      $Id: pltgadec.h,v 1.3 2001/10/21 17:12:40 uzadow Exp $
|
|      Copyright (c) 1996-1998 Ulrich von Zadow
|
\--------------------------------------------------------------------
*/

#ifndef INCL_PLTGADEC
#define INCL_PLTGADEC

#ifndef INCL_PLPICDEC
#include "plpicdec.h"
#endif

#ifndef INCL_PLTGA
#include "pltga.h"
#endif

//! Targa file decoder. Decodes 8, 15, 16, 24 and 32 bpp
//! targa files (compressed and uncompressed) and returns an 8 or 32
//! bpp CBitmap. Preserves the alpha channel.
class PLTGADecoder : public PLPicDecoder
{


public:
  //! Creates a decoder
  PLTGADecoder
    ();

  //! Destroys a decoder
  virtual ~PLTGADecoder
    ();

protected:
  //! Main decoder routine. Reads the header, Creates the bitmap,
  //! reads the palette, and reads the image data.
  virtual void DoDecode
    ( PLBmp * pBmp,
      PLDataSource * pDataSrc
    );

private:

  // Fills TGAHEADER structure with the information in the file.
  void readTgaHeader
    ( TGAHEADER * pTgaHead,       // Pointer to TGA header structure
      PLDataSource * pDataSrc
    );

  // Reads the TGA palette and creates a windows palette.
  void readPalette
    ( int StartIndex,           // Index of first palette entry.
      int Length,               // Number of palette entries stored.
      int EntrySize,            // Size of palette entries in bits.
      PLBmp * pBmp,
      PLDataSource * pDataSrc
    );


  // Determines compression type and calls readData.
  void readImage
    ( TGAHEADER * pTgaHead,       // Pointer to TGA header structure
      PLBmp * pBmp,
      PLDataSource * pDataSrc
    );

  // Reads image data line-by-line.
  void readData
    ( TGAHEADER * pTgaHead,       // Pointer to TGA header structure
      bool bCompressed,
      PLBmp * pBmp,
      PLDataSource * pDataSrc
    );

  // Decodes one line of uncompressed image data.
  void expandUncompressedLine
    ( PLBYTE * pDest,
      int Width,
      bool bReversed,
      int bpp,
      PLDataSource * pDataSrc
    );

  // Decodes one line of compressed image data.
  void expandCompressedLine
    ( PLBYTE * pDest,
      int Width,
      bool bReversed,
      int bpp,
      PLDataSource * pDataSrc
    );

  // Reads one image pixel and returns it in RGBA format.
  PLPixel32 readPixel32
    ( int bpp,
      PLDataSource * pDataSrc
    );

  // Reads one image pixel and returns it in 8-bit format.
  PLBYTE readPixel8
    ( int bpp,
      PLDataSource * pDataSrc
    );
};

#endif
/*
/--------------------------------------------------------------------
|
|      $Log: pltgadec.h,v $
|      Revision 1.3  2001/10/21 17:12:40  uzadow
|      Added PSD decoder beta, removed BPPWanted from all decoders, added PLFilterPixel.
|
|      Revision 1.2  2001/10/06 22:37:08  uzadow
|      Linux compatibility.
|
|      Revision 1.1  2001/09/16 19:03:22  uzadow
|      Added global name prefix PL, changed most filenames.
|
|
\--------------------------------------------------------------------
*/
