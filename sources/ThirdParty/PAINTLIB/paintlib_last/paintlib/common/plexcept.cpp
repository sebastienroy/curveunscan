/*
/--------------------------------------------------------------------
|
|      $Id: plexcept.cpp,v 1.2 2001/10/06 22:37:08 uzadow Exp $
|      EXCEPT.CPP        Exception Class
|
|        Exception containing an error code and a string
|        describing the error in a user-friendly way.
|        The header file defines the error codes used.
|
|      Copyright (c) 1996-1998 Ulrich von Zadow
|
\--------------------------------------------------------------------
*/

#include "plstdpch.h"

#include "plexcept.h"
#include "plpaintlibdefs.h"

PLTextException::PLTextException
    ( int Code,
      const char * pszErr
    )
    : PLObject(),
      m_Code(Code),
      m_pszErr(NULL)
{
#ifdef _WINDOWS
  SetErrorMode (0);     // Restore normal error handling just in case
                        // file system error checking was disabled.
#endif

  m_pszErr = new char[strlen(pszErr)+1];
  strcpy (m_pszErr, pszErr);
}

PLTextException::PLTextException
    ( const PLTextException& ex
    )
    : PLObject(),
      m_Code( ex.m_Code ),
      m_pszErr( new char [strlen( ex.m_pszErr )+1] )

{
  strcpy (m_pszErr, (const char *)ex);
}

PLTextException::~PLTextException
    ()
{
  delete [] m_pszErr;
}

int PLTextException::GetCode
    ()
    const
{
  return m_Code;
}

PLTextException::operator const char *
    ()
    const
    // This operator allows the exception to be treated as a string
    // whenever needed.
{
  return m_pszErr;
}
/*
/--------------------------------------------------------------------
|
|      $Log: plexcept.cpp,v $
|      Revision 1.2  2001/10/06 22:37:08  uzadow
|      Linux compatibility.
|
|      Revision 1.1  2001/09/16 19:03:22  uzadow
|      Added global name prefix PL, changed most filenames.
|
|      Revision 1.6  2001/02/04 14:31:52  uzadow
|      Member initialization list cleanup (Erik Hoffmann).
|
|      Revision 1.5  2001/01/21 14:28:21  uzadow
|      Changed array cleanup from delete to delete[].
|
|      Revision 1.4  2000/01/16 20:43:13  anonymous
|      Removed MFC dependencies
|
|      Revision 1.3  1999/10/03 18:50:51  Ulrich von Zadow
|      Added automatic logging of changes.
|
|
--------------------------------------------------------------------
*/
