/*
/--------------------------------------------------------------------
|
|      $Id: pltiffdecex.h,v 1.2 2001/10/21 17:12:40 uzadow Exp $
|
|      Copyright (c) 1996-1998 Ulrich von Zadow
|
\--------------------------------------------------------------------
*/

#ifndef INCL_PLTIFFDECEX
#define INCL_PLTIFFDECEX

#include "pltiffdec.h"

//! Modest interface to get access to tagged fields
//! This should move to CTiffDecoder but I dare not re-introduce 
//! data members in the reworked thread-safe base decoder
class PLTIFFDecoderEx : public PLTIFFDecoder
{

public:
  PLTIFFDecoderEx();
  ~PLTIFFDecoderEx();
  bool Associate( PLDataSource * pDataSrc );
  void Dissociate();
  int GetField( int tag_id, ... );
  //! this is this first argument to most libtiff's routines
  //! use at your own risk; you've been warned!
  TIFF* GetTIFFHandle()	{ return m_TiffToken; }
 	
protected:
  virtual void DoDecode
    ( PLBmp * pBmp,
      PLDataSource * pDataSrc
    );

private:
  TIFF* m_TiffToken;
};

#endif
/*
/--------------------------------------------------------------------
|
|      $Log: pltiffdecex.h,v $
|      Revision 1.2  2001/10/21 17:12:40  uzadow
|      Added PSD decoder beta, removed BPPWanted from all decoders, added PLFilterPixel.
|
|      Revision 1.1  2001/09/16 19:03:22  uzadow
|      Added global name prefix PL, changed most filenames.
|
|      Revision 1.4  2000/12/18 22:42:52  uzadow
|      Replaced RGBAPIXEL with PLPixel32.
|
|      Revision 1.3  2000/01/16 20:43:15  anonymous
|      Removed MFC dependencies
|
|      Revision 1.2  2000/01/09 22:24:10  Ulrich von Zadow
|      Corrected tiff callback bug.
|
|      Revision 1.1  1999/10/19 21:30:42  Ulrich von Zadow
|      B. Delmee - Initial revision
|
|
--------------------------------------------------------------------
*/
