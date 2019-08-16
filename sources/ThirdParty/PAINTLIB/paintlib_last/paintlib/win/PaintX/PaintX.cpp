/*
/--------------------------------------------------------------------
|
|      $Id: PaintX.cpp,v 1.6 2001/09/16 19:03:23 uzadow Exp $
|
|      Copyright (c) 1996-1998 Ulrich von Zadow
|
\--------------------------------------------------------------------
*/

// Note: Proxy/Stub Information
//    To build a separate proxy/stub DLL,
//    run nmake -f PaintXps.mk in the project directory.

#include "stdafx.h"
#include "resource.h"
#include "initguid.h"
#include "PaintX.h"

#include "PaintX_i.c"
#include "PictureDecoder.h"


CComModule _Module;

BEGIN_OBJECT_MAP(ObjectMap)
OBJECT_ENTRY(CLSID_PictureDecoder, CPictureDecoder)
END_OBJECT_MAP()

/////////////////////////////////////////////////////////////////////////////
// DLL Entry Point

extern "C"
bool WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID /*lpReserved*/)
{
    if (dwReason == DLL_PROCESS_ATTACH)
    {
        _Module.Init(ObjectMap, hInstance, &LIBID_PAINTXLib);
        DisableThreadLibraryCalls(hInstance);
    }
    else if (dwReason == DLL_PROCESS_DETACH)
        _Module.Term();
    return true;    // ok
}

/////////////////////////////////////////////////////////////////////////////
// Used to determine whether the DLL can be unloaded by OLE

STDAPI DllCanUnloadNow(void)
{
    return (_Module.GetLockCount()==0) ? S_OK : S_FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// Returns a class factory to create an object of the requested type

STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv)
{
    return _Module.GetClassObject(rclsid, riid, ppv);
}

/////////////////////////////////////////////////////////////////////////////
// DllRegisterServer - Adds entries to the system registry

STDAPI DllRegisterServer(void)
{
    // registers object, typelib and all interfaces in typelib
    return _Module.RegisterServer(true);
}

/////////////////////////////////////////////////////////////////////////////
// DllUnregisterServer - Removes entries from the system registry

STDAPI DllUnregisterServer(void)
{
    return _Module.UnregisterServer(true);
}

/*
/--------------------------------------------------------------------
|
|      $Log: PaintX.cpp,v $
|      Revision 1.6  2001/09/16 19:03:23  uzadow
|      Added global name prefix PL, changed most filenames.
|
|      Revision 1.5  2000/09/01 14:13:49  Administrator
|      Removed MFC from paintX, added MSCV paintX sample.
|
|      Revision 1.4  2000/01/10 23:53:00  Ulrich von Zadow
|      Changed formatting & removed tabs.
|
|
--------------------------------------------------------------------
*/
