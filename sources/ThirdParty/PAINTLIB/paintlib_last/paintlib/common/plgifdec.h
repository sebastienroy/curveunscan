/*
/--------------------------------------------------------------------
|
|      $Id: plgifdec.h,v 1.2 2001/10/21 17:12:40 uzadow Exp $
|
|      Copyright (c) 1996-1998 Ulrich von Zadow
|
\--------------------------------------------------------------------
*/

#ifndef INCL_PLGIFDEC
#define INCL_PLGIFDEC

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "plpicdec.h"

class PLGIFDecoder : public PLPicDecoder  
{
public:
  void DoDecode (PLBmp * pBmp, PLDataSource * pDataSrc);
  PLGIFDecoder();
  virtual ~PLGIFDecoder();

};

#endif 

/*
/--------------------------------------------------------------------
|
|      $Log: plgifdec.h,v $
|      Revision 1.2  2001/10/21 17:12:40  uzadow
|      Added PSD decoder beta, removed BPPWanted from all decoders, added PLFilterPixel.
|
|      Revision 1.1  2001/09/16 19:03:22  uzadow
|      Added global name prefix PL, changed most filenames.
|
|      Revision 1.2  2000/12/18 22:42:52  uzadow
|      Replaced RGBAPIXEL with PLPixel32.
|
|      Revision 1.1  2000/12/08 13:41:23  uzadow
|      Added gif support by Michael Salzlechner.
|
|
\--------------------------------------------------------------------
*/
