/*
/--------------------------------------------------------------------
|
|      $Id: plfilesrc.h,v 1.3 2001/10/06 22:37:08 uzadow Exp $
|
|      Copyright (c) 1996-1998 Ulrich von Zadow
|
\--------------------------------------------------------------------
*/

#ifndef INCL_PLFILESRC
#define INCL_PLFILESRC

#ifndef INCL_PLDATASRC
#include "pldatasrc.h"
#endif

#ifdef _WINDOWS
#define PL_FILE_MAPPING
#endif

#include <stdio.h>

class PLIProgressNotification;

//! This is a class which takes a file as a source of picture data.
class PLFileSource : public PLDataSource
{

public:
  //!
  PLFileSource
    ( PLIProgressNotification * pNotification = NULL
    );

  //!
  virtual ~PLFileSource
    ();

  //!
  virtual int Open
    ( const char * pszFName
    );

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

  virtual PLBYTE * ReadEverything
    ();

private:
#ifdef PL_FILE_MAPPING
  HANDLE m_hf;    // File handle.
  HANDLE m_hm;    // Handle to file-mapping object.

#else
  bool bytesAvailable
    ( int n
    );

  void fillBuffer
    ( int n = 4096
    );

  FILE * m_pFile;
  PLBYTE * m_pBuffer;

  PLBYTE * m_pReadPos;
  int m_BytesReadFromFile;
#endif
  PLBYTE * m_pStartData;
  PLBYTE * m_pCurPos;
};

#endif
/*
/--------------------------------------------------------------------
|
|      $Log: plfilesrc.h,v $
|      Revision 1.3  2001/10/06 22:37:08  uzadow
|      Linux compatibility.
|
|      Revision 1.2  2001/09/16 20:57:17  uzadow
|      Linux version name prefix changes
|
|      Revision 1.1  2001/09/16 19:03:22  uzadow
|      Added global name prefix PL, changed most filenames.
|
|      Revision 1.4  2001/09/13 20:46:45  uzadow
|      Removed 4096-byte limit for fillBuffer that was causing PLPNGEncoder
|      to fail under Linux.
|
|
\--------------------------------------------------------------------
*/
