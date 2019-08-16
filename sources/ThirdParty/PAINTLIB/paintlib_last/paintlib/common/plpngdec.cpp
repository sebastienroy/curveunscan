/*
/--------------------------------------------------------------------
|
|      $Id: plpngdec.cpp,v 1.6 2001/10/21 17:12:40 uzadow Exp $
|      PNG Decoder Class
|
|      PNG file decoder. Uses LibPng to do the actual decoding.
|      PNG supports many pixel formats not supported by paintlib.
|      These pixel formats are converted to the nearest paintlib
|      equivalent. Images with less or more than 8 bits per channel
|      are converted to 8 bits per channel. Images with 16-bit
|      palettes or grayscale images with an alpha channel are
|      returned as full 32-bit RGBA bitmaps.
|
|      Copyright (c) 1996-1998 Ulrich von Zadow
|
\--------------------------------------------------------------------
*/

#include "plstdpch.h"
#include "plpngdec.h"
#include "plexcept.h"
#include "png.h"


PLPNGDecoder::PLPNGDecoder
    ()
    : PLPicDecoder()
    // Creates a decoder
{
}


PLPNGDecoder::~PLPNGDecoder
    ()
{
}



void my_read_data(png_structp png_ptr, png_bytep data, png_size_t length)
{
  // todo : check data erasing
  PLBYTE *ptr;
  PLDataSource* pSourceInfo=(PLDataSource*)png_get_io_ptr(png_ptr);

  ptr = pSourceInfo->ReadNBytes(length);
  memcpy(data,ptr,length);
}


void PLPNGDecoder::DoDecode
    ( PLBmp * pBmp,
      PLDataSource * pDataSrc
    )
{
  png_uint_32 width, height;
  int bit_depth, color_type, interlace_type;
  png_structp png_ptr = NULL;
  png_infop info_ptr;

  try
  {
    png_ptr = png_create_read_struct
                (PNG_LIBPNG_VER_STRING,
                 (void *)NULL,
                 user_error_fn,
                 user_warning_fn);
    PLASSERT (png_ptr);

    info_ptr = png_create_info_struct(png_ptr);
    PLASSERT (info_ptr);

    png_set_read_fn(png_ptr, (void*)pDataSrc, my_read_data);

    /* The call to png_read_info() gives us all of the information from the
     * PNG file before the first IDAT (image data chunk).  REQUIRED
     */
    png_read_info(png_ptr, info_ptr);

    png_get_IHDR(png_ptr, info_ptr, &width, &height, &bit_depth, &color_type,
                 &interlace_type, NULL, NULL);

    int DestBPP;
    bool bHasAlpha;
    switch (color_type)
    {
      case PNG_COLOR_TYPE_RGB:
        DestBPP = 32;
        bHasAlpha = false;
        break;
      case PNG_COLOR_TYPE_RGB_ALPHA:
        DestBPP = 32;
        bHasAlpha = true;
        break;
      case PNG_COLOR_TYPE_GRAY:
        DestBPP = 8;
        bHasAlpha = false;
        break;
      case PNG_COLOR_TYPE_GRAY_ALPHA:
        DestBPP = 32;
        png_set_gray_to_rgb(png_ptr);
        png_set_expand(png_ptr);
        bHasAlpha = true;
        break;
      case PNG_COLOR_TYPE_PALETTE:
        if (bit_depth != 16)
          DestBPP = 8;
        else
        { // 16-bit palette image
          png_set_expand(png_ptr);
          DestBPP = 32;
        }
        bHasAlpha = false;
        break;
    }

    if (DestBPP == 32)
    { // Make sure we use the correct byte order
// Jose Miguel Buenaposada 2000/06/30
#ifdef PL_PIXEL_BGRA_ORDER
      png_set_bgr (png_ptr);
#else
  #ifdef PL_PIXEL_RGBA_ORDER 
  #else
  #error Unsupported byte ordering!
  #endif
#endif
      
      if (!bHasAlpha)
#if (PL_RGBA_ALPHA == 3)
        png_set_filler(png_ptr, 0xff, PNG_FILLER_AFTER);
#else
        png_set_filler(png_ptr, 0xff, PNG_FILLER_BEFORE);
#endif
    }

    if (bHasAlpha)
      // Image has alpha channel
      pBmp->Create (width, height,
                    DestBPP, true);
    else
      // Image doesn't have alpha channel
      pBmp->Create (width, height,
                    DestBPP, false);

    if (color_type == PNG_COLOR_TYPE_GRAY)
    {
      int i;
      int NumColors = 1<<(bit_depth);
      for (i=0; i<NumColors; i++)
      {
        int CurColor = (i*255)/(NumColors-1);
        pBmp->SetPaletteEntry(i, CurColor, CurColor, CurColor, 0xFF);
      }
    }

    if (color_type == PNG_COLOR_TYPE_PALETTE)
    {
      png_color* ppng_color_tab=NULL;

      int   i;
      int   nbColor=0;

      png_get_PLTE(png_ptr,info_ptr,&ppng_color_tab,&nbColor);

      for (i=0; i<nbColor; i++)
      {
        pBmp->SetPaletteEntry(i,
                              (*(ppng_color_tab+i)).red,
                              (*(ppng_color_tab+i)).green,
                              (*(ppng_color_tab+i)).blue,
                              0xFF);
      }
    }

    if (bit_depth == 16)
      png_set_strip_16(png_ptr);
    if (bit_depth < 8)
      png_set_packing(png_ptr);

    pBmp->Lock(false, true);
    PLBYTE ** pLineArray = pBmp->GetLineArray();
    png_read_image(png_ptr, pLineArray);
    pBmp->Unlock();

    PLULONG XRes, YRes;
    int UnitType;
    png_get_pHYs (png_ptr, info_ptr, &XRes, &YRes,
                  &UnitType);
    if (UnitType == PNG_RESOLUTION_METER)
      pBmp->SetResolution (PLPoint (int (XRes/39.37f+0.5), int (YRes/39.37f+0.5)));
    else
      pBmp->SetResolution (PLPoint (0,0));

    /* read rest of file, and get additional chunks in info_ptr - REQUIRED */
    png_read_end(png_ptr, info_ptr);

    /* clean up after the read, and free any memory allocated - REQUIRED */
    png_destroy_read_struct(&png_ptr, &info_ptr, (png_infopp)NULL);
  }
  catch (PLTextException)
  {
    // Cleaning up in this catch seems to break Visual C++ memory management
    // completely in some cases, so we don't do it.
    // The result is a small memory leak whenever a png file can't be decoded.
    // if (png_ptr)
    //   png_destroy_read_struct(&png_ptr, &info_ptr, (png_infopp)NULL);
    throw;
  }
  catch(...)
  {
	  PLASSERT(false);
    // Cleaning up in this catch seems to break Visual C++ memory management
    // completely in some cases, so we don't do it.
	  // png_destroy_read_struct(&png_ptr, &info_ptr, (png_infopp)NULL);
	  throw;
  }
}

void PLPNGDecoder::user_error_fn
    ( png_structp png_ptr,
      png_const_charp error_msg
    )
{
  raiseError (PL_ERRFORMAT_UNKNOWN, (char *)error_msg);
}

void PLPNGDecoder::user_warning_fn
    ( png_structp png_ptr,
      png_const_charp warning_msg
    )
{
  PLTRACE ((char *)warning_msg);
}

/*
/--------------------------------------------------------------------
|
|      $Log: plpngdec.cpp,v $
|      Revision 1.6  2001/10/21 17:12:40  uzadow
|      Added PSD decoder beta, removed BPPWanted from all decoders, added PLFilterPixel.
|
|      Revision 1.5  2001/10/16 18:00:19  uzadow
|      Linux compatibility
|
|      Revision 1.4  2001/10/16 17:12:26  uzadow
|      Added support for resolution information (Luca Piergentili)
|
|      Revision 1.3  2001/10/06 22:37:08  uzadow
|      Linux compatibility.
|
|      Revision 1.2  2001/09/28 19:50:56  uzadow
|      Added some 24 bpp stuff & other minor features.
|
|      Revision 1.1  2001/09/16 19:03:22  uzadow
|      Added global name prefix PL, changed most filenames.
|
|      Revision 1.11  2001/02/04 14:31:52  uzadow
|      Member initialization list cleanup (Erik Hoffmann).
|
|      Revision 1.10  2000/12/18 22:42:52  uzadow
|      Replaced RGBAPIXEL with PLPixel32.
|
|      Revision 1.9  2000/08/13 12:11:43  Administrator
|      Added experimental DirectDraw-Support
|
|      Revision 1.8  2000/07/11 17:11:01  Ulrich von Zadow
|      Added support for RGBA pixel ordering (Jose Miguel Buenaposada Biencinto).
|
|      Revision 1.7  2000/01/16 20:43:14  anonymous
|      Removed MFC dependencies
|
|      Revision 1.6  2000/01/04 18:35:23  Ulrich von Zadow
|      no message
|
|      Revision 1.5  1999/12/08 16:31:40  Ulrich von Zadow
|      Unix compatibility
|
|      Revision 1.4  1999/12/08 15:39:45  Ulrich von Zadow
|      Unix compatibility changes
|
|      Revision 1.3  1999/10/03 18:50:51  Ulrich von Zadow
|      Added automatic logging of changes.
|
|
--------------------------------------------------------------------
*/
