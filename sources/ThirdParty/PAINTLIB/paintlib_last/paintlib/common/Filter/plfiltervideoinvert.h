/*
/--------------------------------------------------------------------
|
|      $Id: plfiltervideoinvert.h,v 1.1 2001/09/16 19:03:23 uzadow Exp $
|
|      Copyright (c) 1996-1998 Ulrich von Zadow
|
\--------------------------------------------------------------------
*/

#if !defined(AFX_VIDEOINVERTFILTER_H__5AB120C1_CEB0_11D3_AD70_444553540000__INCLUDED_)
#define AFX_VIDEOINVERTFILTER_H__5AB120C1_CEB0_11D3_AD70_444553540000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "plfilter.h"

//!
class PLFilterVideoInvert : public PLFilter  
{
public:
	//!
  PLFilterVideoInvert();

	//!
  virtual ~PLFilterVideoInvert();

  //!
	void Apply(PLBmp * pBmpSource, PLBmp * pBmpDest) const;
};

#endif // !defined(AFX_VIDEOINVERTFILTER_H__5AB120C1_CEB0_11D3_AD70_444553540000__INCLUDED_)

/*
/--------------------------------------------------------------------
|
|      $Log: plfiltervideoinvert.h,v $
|      Revision 1.1  2001/09/16 19:03:23  uzadow
|      Added global name prefix PL, changed most filenames.
|
|      Revision 1.2  2001/01/15 15:05:31  uzadow
|      Added PLBmp::ApplyFilter() and PLBmp::CreateFilteredCopy()
|
|      Revision 1.1  2000/03/31 12:20:06  Ulrich von Zadow
|      Video invert filter (beta)
|
|
|
\--------------------------------------------------------------------
*/
