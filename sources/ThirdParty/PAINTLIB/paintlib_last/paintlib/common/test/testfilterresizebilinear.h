/*
/--------------------------------------------------------------------
|
|      $Id: testfilterresizebilinear.h,v 1.3 2001/10/21 17:08:41 uzadow Exp $
|
|      Copyright (c) 1996-1998 Ulrich von Zadow
|
\--------------------------------------------------------------------
*/

#ifndef INCL_PLTESTFILTERRESIZEBILINEAR
#define INCL_PLTESTFILTERRESIZEBILINEAR

class PLTester;
class PLBmp;

class PLTestFilterResizeBilinear
{

public:
  PLTestFilterResizeBilinear (PLTester * pTester);

  virtual ~PLTestFilterResizeBilinear();

  void RunTests ();

private:
  void createBmp(PLBmp& Bmp);
  PLTester * m_pTester;
};

#endif
/*
/--------------------------------------------------------------------
|
|      $Log: testfilterresizebilinear.h,v $
|      Revision 1.3  2001/10/21 17:08:41  uzadow
|      no message
|
|      Revision 1.2  2001/10/06 20:44:45  uzadow
|      Linux compatibility
|
|      Revision 1.1  2001/10/03 14:00:29  uzadow
|      Much improved quality in FilterResizeBilinear.
|
|
\--------------------------------------------------------------------
*/
