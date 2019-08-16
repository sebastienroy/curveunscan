/*
/--------------------------------------------------------------------
|
|      $Id: plmemsrc.h,v 1.3 2001/10/16 17:12:26 uzadow Exp $
|
|      Copyright (c) 1996-1998 Ulrich von Zadow
|
\--------------------------------------------------------------------
*/

#ifndef INCL_PLMEMSRC
#define INCL_PLMEMSRC

#ifndef INCL_PLDATASRC
#include "pldatasrc.h"
#endif

//! This is a class which takes a memory pointer as a source of
//! picture data.
class PLMemSource : public PLDataSource
{
public:
  //!
  PLMemSource
    ();

  //!
  virtual ~PLMemSource
    ();

  //!
  virtual int Open( unsigned char *pek, int size);

  //!
  virtual void Close
    ();

  virtual PLBYTE * ReadNBytes
    ( int n
    );

  //! Read but don't advance file pointer.
  virtual PLBYTE * GetBufferPtr
    ( int MinBytesInBuffer
    );

  //! This is a legacy routine that interferes with progress notifications.
  //! Don't call it!
  virtual PLBYTE * ReadEverything
    ();

private:
  PLBYTE * m_pCurPos;
};

#endif
/*
/--------------------------------------------------------------------
|
|      $Log: plmemsrc.h,v $
|      Revision 1.3  2001/10/16 17:12:26  uzadow
|      Added support for resolution information (Luca Piergentili)
|
|      Revision 1.2  2001/10/06 22:37:08  uzadow
|      Linux compatibility.
|
|      Revision 1.1  2001/09/16 19:03:22  uzadow
|      Added global name prefix PL, changed most filenames.
|
|      Revision 1.1  2000/03/17 10:51:38  Ulrich von Zadow
|      no message
|
|
|
\--------------------------------------------------------------------
*/
