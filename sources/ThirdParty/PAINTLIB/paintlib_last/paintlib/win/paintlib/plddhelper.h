/*
/--------------------------------------------------------------------
|
|      $Id: plddhelper.h,v 1.1 2001/09/16 19:03:23 uzadow Exp $
|
|      Copyright (c) 1996-1998 Ulrich von Zadow
|
\--------------------------------------------------------------------
*/

char * GetDDErrorText
    (HRESULT hr
    );

void CheckForDDError 
    ( HRESULT hr
    );

/*
/--------------------------------------------------------------------
|
|      $Log: plddhelper.h,v $
|      Revision 1.1  2001/09/16 19:03:23  uzadow
|      Added global name prefix PL, changed most filenames.
|
|      Revision 1.1  2000/08/13 12:11:43  Administrator
|      Added experimental DirectDraw-Support
|
|
\--------------------------------------------------------------------
*/
