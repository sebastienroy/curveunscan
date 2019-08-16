/*
/--------------------------------------------------------------------
|
|      $Id: plfilesink.h,v 1.2 2001/10/06 22:37:08 uzadow Exp $
|
|      Copyright (c) 1996-1998 Ulrich von Zadow
|
\--------------------------------------------------------------------
*/
// not quite ready for prime-time; bdelmee; 2/99

#ifndef INCL_PLFILESNK
#define INCL_PLFILESNK

#ifndef INCL_PLDATASNK
#include "pldatasink.h"
#endif

#include <stdio.h>

//! This is a class which takes a file as a destination of picture data.
//!
//! Restriction: needs to allocate a buffer large enough to hold a complete
//! image file. But we don't know its size before it's actually encoded, so
//! we have to be generous or "accidents will happen"
//! A better implementation would rely on memory-mapped files or implement
//! dynamic buffering.
class PLFileSink : public PLDataSink
{

public:
  //!
  PLFileSink
    ();

  //!
  virtual ~PLFileSink
    ();

  //!
  virtual int Open
    ( const char * pszFName,
      int MaxFileSize
    );

  //!
  virtual void Close
    ();

private:
  FILE * m_pFile;
  PLBYTE * m_pDataBuf;
};

#endif

/*
/--------------------------------------------------------------------
|
|      $Log: plfilesink.h,v $
|      Revision 1.2  2001/10/06 22:37:08  uzadow
|      Linux compatibility.
|
|      Revision 1.1  2001/09/16 19:03:22  uzadow
|      Added global name prefix PL, changed most filenames.
|
|      Revision 1.5  2001/09/15 21:02:44  uzadow
|      Cleaned up stdpch.h and config.h to make them internal headers.
|
|      Revision 1.4  2000/01/16 20:43:13  anonymous
|      Removed MFC dependencies
|
|      Revision 1.3  2000/01/08 15:56:12  Ulrich von Zadow
|      Made sure change logging works in every file.
|
|
\--------------------------------------------------------------------
*/
