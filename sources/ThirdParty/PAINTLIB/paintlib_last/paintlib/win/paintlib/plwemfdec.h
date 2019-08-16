/*
/--------------------------------------------------------------------
|
|      $Id: plwemfdec.h,v 1.2 2001/10/21 17:12:40 uzadow Exp $
|
|      Copyright (c) 1996-1998 Ulrich von Zadow
|
--------------------------------------------------------------------
*/

#ifndef INCL_WEMFDEC_H
#define INCL_WEMFDEC_H

#ifndef INCL_PICDEC
#include "plpicdec.h"
#endif

// This only makes sense for Windows
#ifdef _WINDOWS

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


//! Decoder for 16-Bit Windows Metafiles (*.wmf) and 16-Bit Adobe 
//! Placeable Metafiles (*,wmf) and 32-Bit Enhanced Windows 
//! Metafiles (*.emf) for Windows 95, Windows 98 and Windows NT 
//! >= 3.1.
//!
//! Comments by the author, Mario Westphal:<BR>
//!   <I>It can handle at least the 500 tested images I've got
//!   from various free and commercial clipart sources. If
//!   you find a WMF/EMF file it cannot handle, attach it to
//!   an email and send it to mw@mwlabs.de. I'll see what I
//!   can do. But, please, test it with another program
//!   before you send itin to see if it is really a valid 
//!   metafile.</I>
class PLWEMFDecoder : public PLPicDecoder  
{
public:
  //!
	PLWEMFDecoder();

  //!
	virtual ~PLWEMFDecoder();

protected:
	//!
  virtual void DoDecode(PLBmp * pBmp, PLDataSource* pDataSrc);

#ifdef _DEBUG
  virtual void AssertValid() const;
#endif
};

#endif // _WINDOWS

#endif // INCL_WEMFDEC_H
/*
/--------------------------------------------------------------------
|
|      $Log: plwemfdec.h,v $
|      Revision 1.2  2001/10/21 17:12:40  uzadow
|      Added PSD decoder beta, removed BPPWanted from all decoders, added PLFilterPixel.
|
|      Revision 1.1  2001/09/16 19:03:23  uzadow
|      Added global name prefix PL, changed most filenames.
|
|      Revision 1.5  2000/12/18 22:42:53  uzadow
|      Replaced RGBAPIXEL with PLPixel32.
|
|      Revision 1.4  2000/01/16 20:43:18  anonymous
|      Removed MFC dependencies
|
|      Revision 1.3  1999/12/02 17:07:35  Ulrich von Zadow
|      Changes by bdelmee.
|
|
\--------------------------------------------------------------------
*/
