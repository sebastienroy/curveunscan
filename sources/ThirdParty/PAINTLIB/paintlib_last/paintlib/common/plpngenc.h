/*
/--------------------------------------------------------------------
|
|      $Id: plpngenc.h,v 1.3 2002/02/24 13:00:38 uzadow Exp $
|
|      Copyright (c) 1996-2002 Ulrich von Zadow
|
\--------------------------------------------------------------------
*/

#ifndef INCL_PLPNGENC
#define INCL_PLPNGENC

#ifndef INCL_PLPICENC
#include "plpicenc.h"
#endif

//! PNG file encoder. Uses LIBPNG to do the actual conversion.
class PLPNGEncoder : public PLPicEncoder
{

public:
  //! Creates an encoder
  PLPNGEncoder
    ();

  //! Destroys a encoder
  virtual ~PLPNGEncoder
    ();

  PLDataSink * GetDataSink
    ();

protected:

  //! Sets up LIBPNG environment and calls LIBPNG to encode an image.
  virtual void DoEncode
    ( PLBmp* pBmp,
      PLDataSink* pDataSnk
    );

private:
	PLBmp * m_pBmp;
	PLDataSink* m_pDataSnk;

};


#endif  // INCL_PLPNGENC
/*
/--------------------------------------------------------------------
|
|      $Log: plpngenc.h,v $
|      Revision 1.3  2002/02/24 13:00:38  uzadow
|      Documentation update; removed buggy PLFilterRotate.
|
|      Revision 1.2  2001/10/06 20:44:45  uzadow
|      Linux compatibility
|
|      Revision 1.1  2001/09/16 19:03:22  uzadow
|      Added global name prefix PL, changed most filenames.
|
|      Revision 1.3  2000/01/16 20:43:14  anonymous
|      Removed MFC dependencies
|
|      Revision 1.2  2000/01/08 15:53:12  Ulrich von Zadow
|      Moved several functions to the cpp file so applications don't
|      need the png directory in the include path.
|
|      Revision 1.1  2000/01/04 22:06:17  Ulrich von Zadow
|      Initial version by Neville Richards.
|
|
\--------------------------------------------------------------------
*/
