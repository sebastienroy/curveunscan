/*
/--------------------------------------------------------------------
|
|      $Id: pljpegdec.cpp,v 1.4 2001/10/21 17:12:40 uzadow Exp $
|      JPEG Decoder Class
|
|      JPEG file decoder. Uses the independent JPEG group's library
|      to do the actual conversion.
|
|      Copyright (c) 1996-1998 Ulrich von Zadow
|
\--------------------------------------------------------------------
*/

#include "plstdpch.h"
#include "pljpegdec.h"

#include "plexcept.h"

#include "jmemsrc.h"

// This is for RGB_RED, RGB_GREEN, RGB_BLUE, RGB_PIXELSIZE
#define JPEG_INTERNALS
#include <jmorecfg.h>


/////////////////////////////////////////////////////////////////////
// Error handling.

METHODDEF(void)
error_exit (j_common_ptr pcinfo)
// This procedure is called by the IJPEG library when an error
// occurs.
{
  /* Create the message string */
  char sz[256];
  (pcinfo->err->format_message) (pcinfo, sz);
  strcat (sz, "\n");

  PLPicDecoder::raiseError (PL_ERRFORMAT_NOT_SUPPORTED, sz);
}

/////////////////////////////////////////////////////////////////////
// Class functions

PLJPEGDecoder::PLJPEGDecoder
    ()
    : PLPicDecoder(),
      m_bFast(true)
    // Creates a decoder
{
  cinfo.err = jpeg_std_error (&jerr);
  jerr.error_exit = error_exit;  // Register custom error manager.

  jpeg_create_decompress (&cinfo);
}


PLJPEGDecoder::~PLJPEGDecoder
    ()
{
  jpeg_destroy_decompress (&cinfo);
}

void PLJPEGDecoder::SetFast
    ( bool bFast
    )
    // true (the default) selects fast but sloppy decoding.
{
  m_bFast = bFast;
}


void PLJPEGDecoder::DoDecode
    ( PLBmp * pBmp,
      PLDataSource * pDataSrc
    )
{
  try
  {
  // Jo Hagelberg 15.4.99: added progress notification callback
    JMETHOD( void, notify, (j_common_ptr));
    notify = JNotification;

    // Initialize custom data source.
    // Jo Hagelberg 15.4.99: added pDataSrc and notify
    jpeg_mem_src (&cinfo, pDataSrc->ReadEverything(),
                  pDataSrc->GetFileSize(), (void*)pDataSrc, notify);

    jpeg_read_header (&cinfo, true);

    if (m_bFast)
    {
      cinfo.do_fancy_upsampling = false;
    }

    // Choose floating point DCT method.
    cinfo.dct_method = JDCT_FLOAT;

    int w = cinfo.image_width;
    int h = cinfo.image_height;

    jpeg_start_decompress (&cinfo);

    if (cinfo.out_color_space == JCS_GRAYSCALE)
      decodeGray (pBmp, w, h);
    else
      decodeRGB (pBmp, w, h);
    jpeg_finish_decompress (&cinfo);

	  PLPoint DPI;

	  DPI.x = cinfo.X_density;
	  if(DPI.x <= 1)
		  DPI.x = 72;

	  DPI.y = cinfo.Y_density;
	  if(DPI.y <= 1)
		  DPI.y = 72;
	  pBmp->SetResolution (DPI);
  }
  catch (PLTextException)
  {
    jpeg_abort_decompress(&cinfo);
    throw;
  }


}

void PLJPEGDecoder::decodeRGB
    ( PLBmp * pBmp,
      int w,
      int h
    )
    // Assumes IJPEG decoder is already set up.
{
  int CurLine = 0;
  PLBYTE * pBuf;
  JSAMPARRAY ppBuf = &pBuf;

  pBmp->Create (w, h, 32, false);
#if ((PL_RGBA_RED!=RGB_RED)||(PL_RGBA_GREEN!=RGB_GREEN)||(PL_RGBA_BLUE!=RGB_BLUE)||(4!=RGB_PIXELSIZE))
  pBuf = new PLBYTE[w*sizeof (PLPixel32)];
#endif

  pBmp->Lock(false, true);
  PLPixel32 ** pLineArray = pBmp->GetLineArray32();

  int readed = 0;
  while (CurLine < h)
  {
    // Correct pixel ordering if libjpeg is configured differently
    // than paintlib.
#if ((PL_RGBA_RED!=RGB_RED)||(PL_RGBA_GREEN!=RGB_GREEN)||(PL_RGBA_BLUE!=RGB_BLUE)||(4!=RGB_PIXELSIZE))
    jpeg_read_scanlines (&cinfo, ppBuf, 1);
    int i;
    for (i=0;i<w;i++)
    {
      PLBYTE * pSrcPixel = pBuf+i*RGB_PIXELSIZE;
      PLPixel32 * pDestPixel = pLineArray[CurLine]+i;
      pDestPixel->SetR (pSrcPixel[RGB_RED]);
      pDestPixel->SetG (pSrcPixel[RGB_GREEN]);
      pDestPixel->SetB (pSrcPixel[RGB_BLUE]);
    }
    CurLine++;
#else
    readed = jpeg_read_scanlines (&cinfo,&pLineArray[CurLine],32);
    CurLine+=min(readed,(h-CurLine));
    if(readed==0)
      break;
#endif
  }
  pBmp->Unlock();
  if(pBuf)
  {
    delete[] pBuf;
  }
}

void PLJPEGDecoder::decodeGray
    ( PLBmp * pBmp,
      int w,
      int h
    )
    // Assumes IJPEG decoder is already set up.
{
  PLBYTE * pDst;
  int CurLine = 0;
  PLBYTE * pBuf = new PLBYTE [w];
  try
  {
    JSAMPARRAY ppBuf = &pBuf;

    pBmp->Create (w, h, 8, false);

    pBmp->Lock(false, true);
    PLBYTE ** pLineArray = pBmp->GetLineArray();

    while (CurLine < h)
    {
      ppBuf = &pDst;
      *ppBuf = pLineArray[CurLine];
      jpeg_read_scanlines (&cinfo, ppBuf, 1);

      CurLine++;
    }
    pBmp->Unlock();
  }
  catch(...)
  {
    delete [] pBuf;
    throw;
  }
  delete [] pBuf;
}


/*
 * Jo Hagelberg 15.4.99
 * progress notification callback
 * since this is a static function we need pDataSrc from cinfo->client_data
 * progress is calculated (0...1) and PaintLib's Notification called
 */

void PLJPEGDecoder::JNotification (j_common_ptr cinfo)
{
  double       part;
  PLDataSource *pDataSrc;

  /* calculated according to jpeg lib manual
   * note: this may not be precice when using buffered image mode
   * todo: think hard of alternatives 4 this case ... :-)
   */
  part = ( (double)cinfo->progress->completed_passes +
           ((double)cinfo->progress->pass_counter/cinfo->progress->pass_limit) ) /
         (double)cinfo->progress->total_passes;

  // call Notification in PLDataSource
  pDataSrc = (PLDataSource*) cinfo->client_data;
  if (pDataSrc)
  {
    pDataSrc->OProgressNotification( part);
  }

}

/*
/--------------------------------------------------------------------
|
|      $Log: pljpegdec.cpp,v $
|      Revision 1.4  2001/10/21 17:12:40  uzadow
|      Added PSD decoder beta, removed BPPWanted from all decoders, added PLFilterPixel.
|
|      Revision 1.3  2001/10/16 17:12:26  uzadow
|      Added support for resolution information (Luca Piergentili)
|
|      Revision 1.2  2001/10/06 22:37:08  uzadow
|      Linux compatibility.
|
|      Revision 1.1  2001/09/16 19:03:22  uzadow
|      Added global name prefix PL, changed most filenames.
|
|      Revision 1.19  2001/09/15 17:12:40  uzadow
|      Added jpeg codec optimizations by Petr Kures.
|
|      Revision 1.18  2001/02/04 14:31:52  uzadow
|      Member initialization list cleanup (Erik Hoffmann).
|
|      Revision 1.17  2001/01/21 14:28:21  uzadow
|      Changed array cleanup from delete to delete[].
|
|      Revision 1.16  2000/12/18 22:42:52  uzadow
|      Replaced RGBAPIXEL with PLPixel32.
|
|      Revision 1.15  2000/11/10 10:40:53  jmbuena
|      Fixed jpeg decoder bug on GNU/Linux
|
|      Revision 1.5  2000/11/08 13:36:32  jmbuena
|      Changes due to paintlib changes
|
|      Revision 1.14  2000/10/30 14:32:51  uzadow
|      Removed dependency on jinclude.h
|
|      Revision 1.13  2000/10/27 11:58:25  jmbuena
|      paintlib-config added, libjpeg and so on taked from the system ones, copied libs internal headers onto paintlib
|
|      Revision 1.12  2000/10/26 21:06:17  uzadow
|      Removed dependency on jpegint.h
|
|      Revision 1.11  2000/10/24 23:00:09  uzadow
|      Added byte order conversion.
|
|      Revision 1.10  2000/08/13 12:11:43  Administrator
|      Added experimental DirectDraw-Support
|
|      Revision 1.9  2000/01/16 20:43:13  anonymous
|      Removed MFC dependencies
|
|      Revision 1.8  1999/12/14 12:30:13  Ulrich von Zadow
|      Corrected copy constructor and assignment operator.
|
|      Revision 1.7  1999/12/08 16:31:40  Ulrich von Zadow
|      Unix compatibility
|
|      Revision 1.6  1999/12/08 15:39:45  Ulrich von Zadow
|      Unix compatibility changes
|
|      Revision 1.5  1999/10/19 21:25:16  Ulrich von Zadow
|      no message
|
|      Revision 1.4  1999/10/03 18:50:51  Ulrich von Zadow
|      Added automatic logging of changes.
|
|
\--------------------------------------------------------------------
*/
