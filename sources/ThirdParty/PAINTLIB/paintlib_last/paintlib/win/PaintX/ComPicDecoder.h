/*
/--------------------------------------------------------------------
|
|      $Id: ComPicDecoder.h,v 1.3 2000/01/10 23:53:00 Ulrich von Zadow Exp $
|
|      Copyright (c) 1996-1998 Ulrich von Zadow
|
\--------------------------------------------------------------------
*/

#ifndef __COMPICDECODER_H_
#define __COMPICDECODER_H_

#include "resource.h"       // main symbols
#include "anydec.h"
#include "winbmp.h"

/////////////////////////////////////////////////////////////////////////////
// CComPicDecoder
class ATL_NO_VTABLE CComPicDecoder :
      public CComObjectRootEx<CComSingleThreadModel>,
      public CComCoClass<CComPicDecoder, &CLSID_PicDecoder>,
      public IDispatchImpl<IPicDecoder, &IID_IPicDecoder, &LIBID_PAINTXLib>
{
public:
  CComPicDecoder();
  STDMETHOD(CreatePictureFromFile)(/*[in]*/ BSTR bstrFilename,
      /*[in]*/ int intBPPWanted,
      /*[out, retval]*/ IUnknown ** ppUnk);
  void raiseError
  ( int Code,
    char * pszErr
  );
  HRESULT SaveBmpToGMemStream(CWinBmp* WinBmp, LPSTREAM * lpStream);


  DECLARE_REGISTRY_RESOURCEID(IDR_COMPICDECODER)

  BEGIN_COM_MAP(CComPicDecoder)
  COM_INTERFACE_ENTRY(IPicDecoder)
  COM_INTERFACE_ENTRY(IDispatch)
  END_COM_MAP()

  // IPicDecoder
protected:
  CAnyPicDecoder m_AnyPicDecoder;
};

#endif //__COMPICDECODER_H_
/*
/--------------------------------------------------------------------
|
|      $Log: ComPicDecoder.h,v $
|      Revision 1.3  2000/01/10 23:53:00  Ulrich von Zadow
|      Changed formatting & removed tabs.
|
|
--------------------------------------------------------------------
*/
