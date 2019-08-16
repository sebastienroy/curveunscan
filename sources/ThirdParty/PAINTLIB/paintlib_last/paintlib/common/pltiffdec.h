/*
/--------------------------------------------------------------------
|
|      $Id: pltiffdec.h,v 1.3 2001/10/21 17:12:40 uzadow Exp $
|
|      Copyright (c) 1996-1998 Ulrich von Zadow
|
\--------------------------------------------------------------------
*/

#ifndef INCL_PLTIFFDEC
#define INCL_PLTIFFDEC

#ifndef INCL_PLPICDEC
#include "plpicdec.h"
#endif

#ifndef INCL_PLPOINT
#include "plpoint.h"
#endif

extern "C"
{
#include "tiff.h"
#include "tiffio.h"
}

//! TIFF file decoder. Uses LIBTIFF to do the actual conversion.
//! Supports 1, 8 and 24 bits per pixel as output formats.
class PLTIFFDecoder : public PLPicDecoder
{

friend class _tiff_helper;
friend class PLTIFFEncoder;

public:
  //! Creates a decoder
  PLTIFFDecoder
    ();

  //! Destroys a decoder
  virtual ~PLTIFFDecoder
    ();
/*
  PLBmp * MakeBmpFromFile
    ( char * pszFName
    );
*/
protected:
  //! Sets up LIBTIFF environment and calls LIBTIFF to decode an
  //! image.
  virtual void DoDecode
    ( PLBmp * pBmp,
      PLDataSource * pDataSrc
    );

  virtual void DoTiffDecode
    ( PLBmp * pBmp,
      PLDataSource * pDataSrc,
      TIFF* tiff
    );

private:
	// these 2 helpers dedicated to hi/low bit-depths respectively
	void doHiColor
    ( TIFF * tif,
      PLBmp * pBmp,
      uint16 SamplePerPixel
    );

	void doLoColor
    ( TIFF * tif,
      PLBmp * pBmp
    );

  const PLPoint getResolution (TIFF* tif);

  // Callback from the TIFF library.
  // Should be accessed only by the TIFF decoder and libtiff.
  static void Win32WarningHandler
    ( const char* module,
      const char* fmt,
      va_list ap
    );

  // Callback from the TIFF library.
  // Should be accessed only by the TIFF decoder and libtiff.
  static void Win32ErrorHandler
    ( const char* module,
      const char* fmt,
      va_list ap
    );

private:
  // Temporary storage for an error message. 
  // Used in the callbacks, so it's static.
  static char m_szLastErr[256];
};


#endif
/*
/--------------------------------------------------------------------
|
|      $Log: pltiffdec.h,v $
|      Revision 1.3  2001/10/21 17:12:40  uzadow
|      Added PSD decoder beta, removed BPPWanted from all decoders, added PLFilterPixel.
|
|      Revision 1.2  2001/10/17 13:19:47  uzadow
|      Added support for photoshop tiff alpha channels.
|
|      Revision 1.1  2001/09/16 19:03:22  uzadow
|      Added global name prefix PL, changed most filenames.
|
|      Revision 1.7  2000/12/18 22:42:52  uzadow
|      Replaced RGBAPIXEL with PLPixel32.
|
|      Revision 1.6  2000/01/16 20:43:15  anonymous
|      Removed MFC dependencies
|
|      Revision 1.5  2000/01/08 15:56:12  Ulrich von Zadow
|      Made sure change logging works in every file.
|
|      Revision 1.4  1999/10/03 18:50:52  Ulrich von Zadow
|      Added automatic logging of changes.
|
|
--------------------------------------------------------------------
*/
