/*
/--------------------------------------------------------------------
|
|      $Id: pldatasink.h,v 1.4 2002/02/24 13:00:20 uzadow Exp $
|
|      Copyright (c) 1996-2002 Ulrich von Zadow
|
\--------------------------------------------------------------------
*/
// not quite ready for prime-time; bdelmee; 2/99

#ifndef INCL_PLDATASNK
#define INCL_PLDATASNK

#include "plexcept.h"
#include "plpaintlibdefs.h"

#include <stdio.h>

//! This is a base class for a destination of picture data.
//! It defines methods to open, write to, close data sinks.
//!
//! Restriction: actually writes to a memory buffer that needs
//! to be foreseen large enough by user (descendant class)
class PLDataSink : public PLObject
{
  // I'd like to get rid of this, but now it is needed so the encoders
  // can maintain the actually useful length of the buffer
  friend class PLTIFFEncoder;
  friend class PLTIFFEncoderEx;

public:
  //!
  void Open
    ( const char* pszName,
      PLBYTE*   pData,
      size_t  MaxDataSize
    );

  //!
  virtual void Close
    ();

  //!
  char* GetName
    ();

  //!
  PLBYTE* GetBufferPtr
    ();

  //!
  size_t GetDataSize
    ();

  //!
  size_t GetMaxDataSize
    ();

  //!
  size_t WriteNBytes
    ( size_t   n,
	  PLBYTE* pData
    );

  void WriteByte
    ( PLBYTE Data
    );

  //!
  void Skip
    ( size_t n );

  //! Test to see if we didn't go past the "end of the file"
  void CheckEOF
    ();

protected:
  PLBYTE* m_pStartData;
  int   m_nCurPos;   // this SHOULD be an unsigned int (size_t), but TIFFLib wants an int

  //!
  PLDataSink
    ();

  //!
  virtual ~PLDataSink
   ();

private:
  char*  m_pszName;    // Name of the data source for diagnostic purposes
  size_t m_nMaxFileSize;
};


inline PLBYTE * PLDataSink::GetBufferPtr
    ()
{
	return m_pStartData + m_nCurPos;
}

inline size_t PLDataSink::GetMaxDataSize
    ()
{
  return  m_nMaxFileSize;
}

inline size_t PLDataSink::GetDataSize
    ()
{
  // return currently used buffer size
  return m_nCurPos;
}

inline void PLDataSink::CheckEOF
    ()
{
  //if (GetFileSize() > GetMaxFileSize())
  if (m_nCurPos > (int)m_nMaxFileSize)
  {
    throw PLTextException (PL_ERREND_OF_FILE,
          "Buffer overflow while encoding.\n");
  }
}

inline void PLDataSink::Skip
    ( size_t n )
{
	// maybe we should fill the gap with nulls
  m_nCurPos += n;
  CheckEOF ();
}

#endif	// INCL_PLDATASNK
/*
/--------------------------------------------------------------------
|
|      $Log: pldatasink.h,v $
|      Revision 1.4  2002/02/24 13:00:20  uzadow
|      Documentation update; removed buggy PLFilterRotate.
|
|      Revision 1.3  2001/10/06 22:03:26  uzadow
|      Added PL prefix to basic data types.
|
|      Revision 1.2  2001/10/06 20:44:45  uzadow
|      Linux compatibility
|
|      Revision 1.1  2001/09/16 19:03:22  uzadow
|      Added global name prefix PL, changed most filenames.
|
|      Revision 1.5  2000/01/16 20:43:13  anonymous
|      Removed MFC dependencies
|
|      Revision 1.4  2000/01/08 15:56:12  Ulrich von Zadow
|      Made sure change logging works in every file.
|
|
\--------------------------------------------------------------------
*/
