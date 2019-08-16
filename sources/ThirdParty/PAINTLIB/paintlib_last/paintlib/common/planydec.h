/*
/--------------------------------------------------------------------
|
|      $Id: planydec.h,v 1.6 2002/03/06 22:46:54 uzadow Exp $
|
|      Copyright (c) 1996-2002 Ulrich von Zadow
|
\--------------------------------------------------------------------
*/

#ifndef INCL_PLANYDEC
#define INCL_PLANYDEC

#ifndef INCL_PLPICDEC
#include "plpicdec.h"
#endif

class CBitmap;

class PLPictDecoder;
class PLTGADecoder;
class PLTIFFDecoder;
class PLJPEGDecoder;
class PLPNGDecoder;
class PLWEMFDecoder;
class PLPCXDecoder;
class PLPGMDecoder;
class PLGIFDecoder;
class PLBmpDecoder;
class PLPPMDecoder;
class PLPSDDecoder;

#define PL_FT_UNKNOWN 0
#define PL_FT_WINBMP  1
#define PL_FT_MACPICT 2
#define PL_FT_TARGA   3
#define PL_FT_TIFF    4
#define PL_FT_JPEG    5
#define PL_FT_PNG     6
#define PL_FT_EPSTIFF 7
#define PL_FT_WMF     8
#define PL_FT_EMF     9
#define PL_FT_PCX    10
#define PL_FT_PGM    11
#define PL_FT_GIF    12
#define PL_FT_PPM    13
#define PL_FT_PSD    14

//! Class which decodes pictures with any known format. It
//! auto-detects the format to use and delegates the work to one of
//! the other decoder classes.
//!
//! The interface to PLAnyPicDecoder is the same as PLPicDecoder.
class PLAnyPicDecoder : public PLPicDecoder
{

public:
  //! Creates a decoder.
  PLAnyPicDecoder
    ();

  //! Destroys the decoder.
  ~PLAnyPicDecoder
    ();

  //! Decodes a picture in a block of memory.
  virtual void MakeBmp
    ( PLDataSource * pDataSrc,
      PLBmp * pBmp,
      int BPPWanted = 0
    );

  //! Called after decoding. Returns the actual file type loaded.
  int GetFileFormat ();


private:
  // Check for file-format-specific data & return the file type if
  // something fits.
  int getFileType
    ( PLBYTE * pData,
      int DataLen
    );

  long epsLongVal
    ( unsigned char *p
    );

  ///////////////////////////////////////////////////////////////////
  // Member variables.
  int m_Type;

  PLBmpDecoder  * m_pBmpDec;
  PLPictDecoder * m_pPictDec;
  PLTGADecoder  * m_pTGADec;
  PLTIFFDecoder * m_pTIFFDec;
  PLJPEGDecoder * m_pJPEGDec;
  PLPNGDecoder  * m_pPNGDec;
  PLWEMFDecoder * m_pWEMFDec;
  PLPCXDecoder  * m_pPCXDec;
  PLPGMDecoder  * m_pPGMDec;
  PLGIFDecoder  * m_pGIFDec;
  PLPPMDecoder  * m_pPPMDec;
  PLPSDDecoder  * m_pPSDDec;
};

#endif

/*
/--------------------------------------------------------------------
|
|      $Log: planydec.h,v $
|      Revision 1.6  2002/03/06 22:46:54  uzadow
|      Fixed major PLAnyDec bug
|
|      Revision 1.5  2001/10/21 17:12:39  uzadow
|      Added PSD decoder beta, removed BPPWanted from all decoders, added PLFilterPixel.
|
|      Revision 1.4  2001/10/16 17:51:32  uzadow
|      Added ppm support (Todd Harris)
|
|      Revision 1.3  2001/10/06 22:37:08  uzadow
|      Linux compatibility.
|
|      Revision 1.2  2001/10/03 13:58:21  uzadow
|      Removed references to config.h
|
|      Revision 1.1  2001/09/16 19:03:22  uzadow
|      Added global name prefix PL, changed most filenames.
|
|      Revision 1.12  2001/09/15 21:02:44  uzadow
|      Cleaned up stdpch.h and config.h to make them internal headers.
|
|      Revision 1.11  2001/01/14 13:36:15  uzadow
|      Added PLAnyPicDecoder::GetFileFormat()
|
|      Revision 1.10  2000/12/08 12:32:00  uzadow
|      Added gif decoder by Michael Salzlechner.
|
|      Revision 1.9  2000/03/31 11:53:29  Ulrich von Zadow
|      Added quantization support.
|
|      Revision 1.8  2000/03/16 13:56:37  Ulrich von Zadow
|      Added pgm decoder by Jose Miguel Buenaposada Biencinto
|
|      Revision 1.7  2000/01/16 20:43:12  anonymous
|      Removed MFC dependencies
|
|      Revision 1.6  1999/12/08 15:39:45  Ulrich von Zadow
|      Unix compatibility changes
|
|
\--------------------------------------------------------------------
*/
