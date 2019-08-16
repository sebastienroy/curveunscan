/*
/--------------------------------------------------------------------
|
|      $Id: plppmdec.h,v 1.2 2001/10/21 17:12:40 uzadow Exp $
|
|      Copyright (c) 2001 Ulrich von Zadow
|
|      Portable Pixmap Decoder Class
|
|      Originally by Todd Harris - Mar 2001
|      adadapted from pgm.h originally by
|			 Jose Miguel Buenaposada Biencinto. Mar 2000.
|
\--------------------------------------------------------------------
*/

#ifndef INCL_PLPPMDEC
#define INCL_PLPPMDEC

#ifndef INCL_PLPICDEC
#include "plpicdec.h"
#endif

#ifndef INCL_PLPPM
#include "plppm.h"
#endif

//! Portable Pixmap file decoder. Delivers a 24 bit true color image.
class PLPPMDecoder : public PLPicDecoder
{

public:
  //! Creates a decoder
  PLPPMDecoder
    ();

  //! Destroys a decoder
  virtual ~PLPPMDecoder
    ();

protected:
  //! Main decoder routine. Reads the header, Creates the bitmap,
  //! reads the palette, and reads the image data.
  virtual void DoDecode
    ( PLBmp * pBmp,
      PLDataSource * pDataSrc
    );

private:

  void readPpmHeader (PPMHEADER *pPpmHead,
	                    PLDataSource * pDataSrc);

  int  readASCIIDecimal(PLDataSource * pDataSrc);

  void skipComment(PLDataSource * pDataSrc);

  void skipPpmASCIISeparators(PLDataSource * pDataSrc);

  PLBYTE *readASCIILine(PLDataSource *pDataSrc);

  void readImage (PPMHEADER * pPpmHead,
                  PLBmp * pBmp,
                  PLDataSource * pDataSrc);

  void readData(PPMHEADER * pPpmHead,
                PLBmp * pBmp,
                PLDataSource * pDataSrc);

  void expandASCIILine
    ( PLPixel32 * pDest,
      int MaxGrayValue,
      int Width,
      PLDataSource * pDataSrc
    );

  void expandByteLine
    ( PLPixel32 * pDest,
	    int MaxGrayValue,
	    int Width,
      PLDataSource * pDataSrc
    );


  PLPixel32 PLPPMDecoder::readASCIIPixel32
    ( int MaxGrayValue,
      PLDataSource * pDataSrc
    );

  PLBYTE m_LastByte;
  bool m_UseLastByte;
};

#endif

/*
/--------------------------------------------------------------------
|
|      $Log: plppmdec.h,v $
|      Revision 1.2  2001/10/21 17:12:40  uzadow
|      Added PSD decoder beta, removed BPPWanted from all decoders, added PLFilterPixel.
|
|      Revision 1.1  2001/10/16 17:51:32  uzadow
|      Added ppm support (Todd Harris)
|
|
\--------------------------------------------------------------------
*/
