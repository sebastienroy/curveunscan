/*
/--------------------------------------------------------------------
|
|      $Id: StdAfx.h,v 1.4 2000/01/17 23:38:08 Ulrich von Zadow Exp $
|
|      Copyright (c) 1996-1998 Ulrich von Zadow
|
\--------------------------------------------------------------------
*/

// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows 95 Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

/*
/--------------------------------------------------------------------
|
|      $Log: StdAfx.h,v $
|      Revision 1.4  2000/01/17 23:38:08  Ulrich von Zadow
|      MFC removal aftermath.
|
|      Revision 1.3  2000/01/16 20:43:19  anonymous
|      Removed MFC dependencies
|
|
\--------------------------------------------------------------------
*/
