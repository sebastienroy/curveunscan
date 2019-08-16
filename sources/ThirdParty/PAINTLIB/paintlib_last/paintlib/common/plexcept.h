/*
/--------------------------------------------------------------------
|
|      $Id: plexcept.h,v 1.2 2002/03/03 16:29:55 uzadow Exp $
|
|      Copyright (c) 1996-2002 Ulrich von Zadow
|
\--------------------------------------------------------------------
*/

#ifndef INCL_PLEXCEPT
#define INCL_PLEXCEPT


// Error codes
#define PL_ERROK              0            // No error
#define PL_ERRWRONG_SIGNATURE 1            // Expected file signature
                                           // not found.
#define PL_ERRFORMAT_UNKNOWN  2            // Sanity check failed.

#define PL_ERRPATH_NOT_FOUND  3            // <--
#define PL_ERRFILE_NOT_FOUND  4            // <-- Problems with the file
#define PL_ERRACCESS_DENIED   5            // <-- system.

#define PL_ERRFORMAT_NOT_SUPPORTED 6       // Known but unsupported
                                           // format.
#define PL_ERRINTERNAL        7            // Internal error of some sort.
#define PL_ERRUNKNOWN_FILE_TYPE    8       // Couldn't recognize the
                                           // file type.
#define PL_ERRDIB_TOO_LARGE   9            // Maximum size for 1 bmp was
                                           // exceeded.
#define PL_ERRNO_MEMORY      10            // Out of memory.
#define PL_ERREND_OF_FILE    11            // End of file reached before
                                           // end of image.

//! An object of this class is thrown by other classes when an error
//! occurs. It contains an error code and a string describing the
//! error. The error code is meant to be used internally in the
//! program; the descriptive string can be output to the user. Error
//! codes and strings do not correspond 1:1. The strings are more
//! precise.
class PLTextException : public PLObject
{

public:
  //! Creates an exception.
  PLTextException
    ( int Code,
      const char * pszErr
    );

  //! Copy constructor.
  PLTextException
    ( const PLTextException& ex
    );

  //! Destroys an exception
  virtual ~PLTextException
    ();

  //! Returns the code of the error that caused the exception. Valid
  //! error codes are:
  //!
  //! PL_ERRWRONG_SIGNATURE (1): Expected file signature not found.
  //!
  //! PL_ERRFORMAT_UNKNOWN (2): Unexpected data encountered. This
  //! probably indicates a corrupt file or an unknown file
  //! sub-format.
  //!
  //! PL_ERRPATH_NOT_FOUND (3), PL_ERRFILE_NOT_FOUND (4),
  //! PL_ERRACCESS_DENIED (5): Problems with the file system.
  //!
  //! PL_ERRFORMAT_NOT_PL_SUPPORTED (6): Known but unsupported format.
  //!
  //! PL_ERRINTERNAL (7): Kaputt. Tell me about it.
  //!
  //! PL_ERRUNKNOWN_FILE_TYPE (8): Couldn't recognize the file type.
  //!
  //! PL_ERRDIB_TOO_LARGE (9): Maximum size for 1 bmp was exceeded.
  //! (See MAX_BITMAP_SIZE above for an explanation).
  //!
  //! PL_ERRNO_MEMORY (10): Out of memory.
  //!
  //! PL_ERREND_OF_FILE (11): End of file reached before end of image.
  virtual int GetCode
    ()
    const;


  //! This operator allows the exception to be treated as a string
  //! whenever needed. The string contains the error message.
  virtual operator const char *
    ()
    const;

private:
  int     m_Code;
  char *  m_pszErr;
};

#endif
/*
/--------------------------------------------------------------------
|
|      $Log: plexcept.h,v $
|      Revision 1.2  2002/03/03 16:29:55  uzadow
|      Re-added BPPWanted.
|
|      Revision 1.1  2001/09/16 19:03:22  uzadow
|      Added global name prefix PL, changed most filenames.
|
|      Revision 1.4  2000/01/17 23:38:07  Ulrich von Zadow
|      MFC removal aftermath.
|
|
\--------------------------------------------------------------------
*/
