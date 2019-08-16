/*
/--------------------------------------------------------------------
|
|      $Id: plmemsink.h,v 1.3 2002/02/24 13:00:22 uzadow Exp $
|
|      Copyright (c) 1996-2002 Ulrich von Zadow
|
\--------------------------------------------------------------------
*/

#ifndef INCL_PLMEMSINK
#define INCL_PLMEMSINK

#include "pldatasink.h"
#include "plpaintlibdefs.h"

//! This is a class which takes a memory region as a destination of picture data.
class PLMemSink : public PLDataSink
{

public:
  //!
  PLMemSink
    ();

  //!
  virtual ~PLMemSink
    ();

  //!
  virtual int Open
    ( const char * pszFName,
      int MaxFileSize
    );

  //!
  virtual void Close
    ();

	virtual PLBYTE* GetBytes();

private:
  PLBYTE * m_pDataBuf;
};

#endif

/*
/--------------------------------------------------------------------
|
|      $Log: plmemsink.h,v $
|      Revision 1.3  2002/02/24 13:00:22  uzadow
|      Documentation update; removed buggy PLFilterRotate.
|
|      Revision 1.2  2001/10/06 22:03:26  uzadow
|      Added PL prefix to basic data types.
|
|      Revision 1.1  2001/09/16 19:03:22  uzadow
|      Added global name prefix PL, changed most filenames.
|
|      Revision 1.2  2001/02/04 14:31:52  uzadow
|      Member initialization list cleanup (Erik Hoffmann).
|
|      Revision 1.1  2000/10/12 21:57:26  uzadow
|      no message
|
|
|
\--------------------------------------------------------------------
*/
