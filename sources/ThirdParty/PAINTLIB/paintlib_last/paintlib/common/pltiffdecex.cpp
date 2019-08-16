/*
|
|      $Id: pltiffdecex.cpp,v 1.2 2001/10/21 17:12:40 uzadow Exp $
|      TIFF Decoder Class
|
|      Copyright (c) 1996-1998 Ulrich von Zadow
|
\--------------------------------------------------------------------
*/

#include "plstdpch.h"
#include "pltiffdec.h"
#include "pltiffdecex.h"
#include "plexcept.h"

extern "C"
{
#include "tif_msrc.h"
}


/////////////////////////////////////////////////////////////////////
// slightly more capable decoder...

PLTIFFDecoderEx::PLTIFFDecoderEx() 
  : PLTIFFDecoder(),
    m_TiffToken(0)
{}



PLTIFFDecoderEx::~PLTIFFDecoderEx()
{
  Dissociate();
}


bool PLTIFFDecoderEx::Associate( PLDataSource* pDataSrc )
{
  m_TiffToken = TIFFOpenMem (pDataSrc->ReadEverything(),
                             pDataSrc->GetFileSize(),
                             NULL);
  return m_TiffToken != 0;
}


void PLTIFFDecoderEx::Dissociate()
{
  if ( m_TiffToken )
  {
    TIFFClose( m_TiffToken );
    m_TiffToken = 0;
  }
}


void PLTIFFDecoderEx::DoDecode (PLBmp * pBmp,
                               PLDataSource * pDataSrc)
{
  PLASSERT( m_TiffToken );

  // call base version on associated data source
  PLTIFFDecoder::DoTiffDecode(
    pBmp,
    pDataSrc,
    m_TiffToken
  );
}

// It'd be nicer to define a bunch of type-safe functions like:
//    uint32  PLTIFFDecoderEx::GetImageLength();
//    CString PLTIFFDecoderEx::GetImageDescription();
int PLTIFFDecoderEx::GetField( int tag_id, ... )
{
  va_list marker;
  int retv;

  va_start( marker, tag_id );     /* Initialize variable arguments. */
  retv = TIFFVGetFieldDefaulted( m_TiffToken, (ttag_t) tag_id, marker );
  va_end( marker );              /* Reset variable arguments.      */

  return retv;
}

/*
/--------------------------------------------------------------------
|
|      $Log: pltiffdecex.cpp,v $
|      Revision 1.2  2001/10/21 17:12:40  uzadow
|      Added PSD decoder beta, removed BPPWanted from all decoders, added PLFilterPixel.
|
|      Revision 1.1  2001/09/16 19:03:22  uzadow
|      Added global name prefix PL, changed most filenames.
|
|      Revision 1.6  2001/02/04 14:31:52  uzadow
|      Member initialization list cleanup (Erik Hoffmann).
|
|      Revision 1.5  2000/12/18 22:42:52  uzadow
|      Replaced RGBAPIXEL with PLPixel32.
|
|      Revision 1.4  2000/01/16 20:43:15  anonymous
|      Removed MFC dependencies
|
|      Revision 1.3  2000/01/10 23:53:00  Ulrich von Zadow
|      Changed formatting & removed tabs.
|
|      Revision 1.2  2000/01/09 22:24:10  Ulrich von Zadow
|      Corrected tiff callback bug.
|
|      Revision 1.1  1999/10/19 21:30:42  Ulrich von Zadow
|      B. Delmee - Initial revision
|
|
\--------------------------------------------------------------------
*/
