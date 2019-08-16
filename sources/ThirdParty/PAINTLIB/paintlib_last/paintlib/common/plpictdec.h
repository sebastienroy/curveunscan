/*
/--------------------------------------------------------------------
|
|      $Id: plpictdec.h,v 1.5 2001/10/21 17:12:40 uzadow Exp $
|
|      Copyright (c) 1996-1998 Ulrich von Zadow
|
\--------------------------------------------------------------------
*/

#ifndef INCL_PLPICTDEC
#define INCL_PLPICTDEC

#ifndef INCL_PLPICDEC
#include "plpicdec.h"
#endif

#include "qdraw.h"

class PLJPEGDecoder;

//! This class decodes macintosh PICT files with 1,2,4,8,16 and 32
//! bits per pixel as well as PICT/JPEG. If an alpha channel is
//! present in a 32-bit-PICT, it is decoded as well.
//! The PICT format is a general picture file format and can
//! contain a lot of other elements besides bitmaps. These elements
//! are ignored.
class PLPictDecoder : public PLPicDecoder
{


public:
  //! Creates a decoder. A JPEG decoder is needed to decode PICT
  //! files containing JPEGs.
  PLPictDecoder
    ( PLJPEGDecoder * pJPEGDecoder
    );

  //! Destroys a decoder.
  virtual ~PLPictDecoder
    ();

protected:
  //! Does the actual decoding after a data source has been set up.
  virtual void DoDecode
    ( PLBmp * pBmp,
      PLDataSource * pDataSrc
    );

private:
  // Decodes header and version information.
  // Sets m_Version.
  // Performs checks to make sure the data is really a pict file.
  void readHeader
    ( PLDataSource * pDataSrc,
      int& Version
    );

  // This is the main decoder loop. The functions reads opcodes,
  // skips some of them, and hands the rest to opcode-specific
  // functions. It stops decoding after the first opcode containing
  // bitmapped data.
  void interpretOpcodes
    ( PLBmp * pBmp,
      PLDataSource * pDataSrc,
      int& Version
    );

  // Moves to an even byte position in the file and returns the
  // opcode found there.
  PLWORD readOpcode
    ( int Version,
      PLDataSource * pDataSrc
    );

  // Opcode functions

  // Skips clipping rectangle or region opcode.
  void clip
    ( PLDataSource * pDataSrc
    );

  // Skips pattern definition opcode.
  // Untested!!
  void pixPat
    ( PLDataSource * pDataSrc
    );

  // Skips polygon/region opcodes.
  // Untested!!
  void skipPolyOrRegion
    ( PLDataSource * pDataSrc
    );

  // Opcode: Bitmap/pixmap data clipped by a rectangle.
  void bitsRect
    ( PLDataSource * pDataSrc,
      PLBmp * pBmp
    );

  // Opcode: Bitmap/pixmap data clipped by a region.
  void bitsRegion
    ( PLDataSource * pDataSrc,
      PLBmp * pBmp
    );

  // DirectBitsRect opcode.
  void opcode9a
    ( PLDataSource * pDataSrc,
      PLBmp * pBmp
    );

  // Long comment opcode. Skipped.
  void longComment
    ( PLDataSource * pDataSrc
    );

  // Header opcode. Contains resolution information.
  void headerOp 
    ( PLDataSource * pDataSrc,
      PLBmp * pBmp
    );

  // JPEG opcode. Invoke the JPEG decoder for this PICT.
  void jpegOp
    ( PLDataSource * pDataSrc,
      PLBmp * pBmp
    );

  // Bitmap & Pixmap functions.

  // Allocates the output bitmap.
  void createOutputBmp
    ( MacpixMap PixMap,
      PLBmp * pBmp
    );

  // Decode version 1 bitmap: 1 bpp.
  void doBitmap
    ( int rowBytes,
      bool bIsRegion,
      PLBmp * pBmp,
      PLDataSource * pDataSrc
    );

  // Decode version 2 pixmap.
  void doPixmap
    ( int rowBytes,
      bool bIsRegion,
      PLBmp * pBmp,
      PLDataSource * pDataSrc
    );

  // This routine decompresses BitsRects with a packType of 4 (and
  // 32 bits per pixel). In this format, each line is separated
  // into 8-bit-bitplanes and then compressed via RLE. To decode,
  // the routine decompresses each line & then juggles the bytes
  // around to get pixel-oriented data.
  void unpack32bits
    ( MacRect* pBounds,
      PLWORD rowBytes,
      int NumBitPlanes,    // 3 if RGB, 4 if RGBA
      PLBmp * pBmp,
      PLDataSource * pDataSrc
    );

  // Decompression routine for 8 bpp. rowBytes is the number of
  // bytes each source row would take if it were uncompressed.
  // This _isn't_ equal to the number of pixels in the row - apple
  // pads the data to a word boundary and then compresses it. Of
  // course, we have to decompress the excess data and then throw it
  // away.
  void unpack8bits
    ( MacRect* pBounds,
      PLWORD rowBytes,
      PLBmp * pBmp,
      PLDataSource * pDataSrc
    );

  // Decompression routine for everything but 32 bpp. This routine
  // is slower than the two routines above since it has to deal
  // with a lot of special cases.
  void unpackbits
    ( MacRect* pBounds,
      PLWORD rowBytes,
      int pixelSize,         // Source bits per pixel.
      PLBmp * pBmp,
      PLDataSource * pDataSrc
    );

  // Skips unneeded packbits.
  void skipBits
    ( MacRect* pBounds,
      PLWORD rowBytes,
      int pixelSize,         // Source bits per pixel.
      PLDataSource * pDataSrc
    );

  // Expands one RLE unit to 32-bit pixel data.
  void expandBuf
    ( PLBYTE * pDestBuf,
      PLBYTE * pSrcBuf,
      int Width,       // Width in bytes for 8 bpp or less.
                       // Width in pixels for 16 bpp.
      int bpp          // bits per pixel
    );

  // Expands Width units to 8-bit pixel data.
  // Max. 8 bpp source format.
  void expandBuf8
    ( PLBYTE * pDestBuf,
      PLBYTE * pSrcBuf,
      int Width,       // Width in bytes.
      int bpp          // bits per pixel.
    );

  void readPixmap
    ( MacpixMap * pPixMap,
      PLDataSource * pDataSrc
    );

  // Reads a mac colour table into a windows palette.
  void readColourTable
    ( PLWORD * pNumColors,
      PLDataSource * pDataSrc,
      PLPixel32 * pPal
    );

  void readRect
    ( MacRect * pr,
      PLDataSource * pDataSrc
    );

  void dumpRect
    ( char * psz,
      MacRect * pr
    );

  void tracePixMapHeader
    ( int Level,
      MacpixMap * pPixMap
    );


  PLJPEGDecoder * m_pJPEGDecoder; // Used if a pict file contains a JPEG.
  PLPoint m_Resolution;

};

#endif
/*
/--------------------------------------------------------------------
|
|      $Log: plpictdec.h,v $
|      Revision 1.5  2001/10/21 17:12:40  uzadow
|      Added PSD decoder beta, removed BPPWanted from all decoders, added PLFilterPixel.
|
|      Revision 1.4  2001/10/16 17:12:26  uzadow
|      Added support for resolution information (Luca Piergentili)
|
|      Revision 1.3  2001/10/06 22:03:26  uzadow
|      Added PL prefix to basic data types.
|
|      Revision 1.2  2001/10/03 13:58:21  uzadow
|      Removed references to config.h
|
|      Revision 1.1  2001/09/16 19:03:22  uzadow
|      Added global name prefix PL, changed most filenames.
|
|
\--------------------------------------------------------------------
*/
