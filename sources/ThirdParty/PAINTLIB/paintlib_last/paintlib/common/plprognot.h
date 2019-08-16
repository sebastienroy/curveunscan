/*
/--------------------------------------------------------------------
|
|      $Id: plprognot.h,v 1.1 2001/09/16 19:03:22 uzadow Exp $
|
|      Copyright (c) 1996-1998 Ulrich von Zadow
|
\--------------------------------------------------------------------
*/

#ifndef INCL_PLPROGNOT
#define INCL_PLPROGNOT

//! Defines an interface for progress notifications.
class PLIProgressNotification
{
public:
  //! Called during decoding as progress gets made.
  virtual void OnProgress 
    ( double Part
    ) = 0;
};

#endif
/*
/--------------------------------------------------------------------
|
|      $Log: plprognot.h,v $
|      Revision 1.1  2001/09/16 19:03:22  uzadow
|      Added global name prefix PL, changed most filenames.
|
|
\--------------------------------------------------------------------
*/
