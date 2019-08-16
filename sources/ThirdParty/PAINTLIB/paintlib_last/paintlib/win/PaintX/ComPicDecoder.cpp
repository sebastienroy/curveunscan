/*
/--------------------------------------------------------------------
|
|      $Id: ComPicDecoder.cpp,v 1.3 2000/01/10 23:53:00 Ulrich von Zadow Exp $
|
|      Copyright (c) 1996-1998 Ulrich von Zadow
|
\--------------------------------------------------------------------
*/

#include "stdafx.h"
#include "PaintX.h"
#include "ComPicDecoder.h"
#include "filesrc.h"
#include "winbmp.h"

/////////////////////////////////////////////////////////////////////////////
// CComPicDecoder

CComPicDecoder::CComPicDecoder()
    :m_AnyPicDecoder()
{}



STDMETHODIMP CComPicDecoder::CreatePictureFromFile(
  /*[in]*/ BSTR bstrFilename,
  /*[in]*/ int intBPPWanted,
  /*[out, RetVal]*/ IUnknown** ppUnk)
{
  AFX_MANAGE_STATE(AfxGetStaticModuleState())

  // TODO: Add your implementation code here
  HRESULT hResult= S_OK;
  CWinBmp m_WinBmp;
  CFileSource m_FileSource;

  TRACE("Loading CWinBMP");
  // Load a CWinBMP
  m_FileSource.Open(CString(bstrFilename));
  m_AnyPicDecoder.MakeBmp(&m_FileSource,&m_WinBmp, intBPPWanted);
  m_FileSource.Close();

  TRACE("Saving the CWinBMP in a global mem");
  // Now save the CWinBMP to GMem-Stream
  LPSTREAM lpStream=NULL;
  hResult = SaveBmpToGMemStream(&m_WinBmp, &lpStream);

  ASSERT(hResult==0);

  // Now create a new picture with this Stream
  TRACE("Loading the CWinBMP from a stream.");
  hResult = OleLoadPicture(lpStream,0,FALSE, IID_IPictureDisp, (void**)ppUnk);

  // Clean up after ourselves
  TRACE("cleaning up");
  if (lpStream)
  {
    lpStream->Release();
    lpStream = NULL;
  }
  return hResult;
}

void CComPicDecoder::raiseError (int Code, char * pszErr)
// This function is needed by callbacks outside of any object,
// so it's public and static. It should not be called from
// outside of the library.
{
  char sz[256];
  TRACE ("Decoder error: %s\n", pszErr);
  sprintf (sz, "Decoder error: %s\n", pszErr);
  throw (CTextException (Code, sz));
}

HRESULT CComPicDecoder::SaveBmpToGMemStream(CWinBmp *pWinBmp, LPSTREAM * lppStream)
{
  int BPP = pWinBmp->GetBitsPerPixel();

  BITMAPFILEHEADER BFH;
  BFH.bfType = *((WORD*)"BM");
  BFH.bfReserved1 = 0;
  BFH.bfReserved2 = 0;
  if (BPP == 8)
    BFH.bfOffBits = sizeof (BITMAPFILEHEADER)+
                    sizeof (BITMAPINFOHEADER)+
                    256*4;
  else
    BFH.bfOffBits = sizeof (BITMAPFILEHEADER)+
                    sizeof (BITMAPINFOHEADER);

  BFH.bfSize = BFH.bfOffBits;
  int m_Height = pWinBmp->GetHeight();
  int m_Width = pWinBmp->GetWidth();

  if (BPP == 8)
    BFH.bfSize += pWinBmp->GetBytesPerLine()*m_Height;
  else
    BFH.bfSize += (((m_Width * 3) + 3) & ~3)*m_Height;

  // Allocate Global Memory
  HGLOBAL hgBitMap = GlobalAlloc(GMEM_MOVEABLE, BFH.bfSize);
  if (!hgBitMap)
    raiseError(E_OUTOFMEMORY,"Global Alloc failed!");

  // Make a GMEM-based IStream
  if (CreateStreamOnHGlobal(hgBitMap,TRUE, lppStream) != S_OK)
    raiseError(E_OUTOFMEMORY,"Create Stream failed!");

  // Write Bitmap-Formatted data in the Stream.
  ULONG BytesWritten;

  (*lppStream)->Write (&BFH, sizeof (BITMAPFILEHEADER), &BytesWritten );

  BYTE ** m_pLineArray = pWinBmp->GetLineArray();

  BYTE * pCurLine = m_pLineArray[0];

  if (pWinBmp->GetBitsPerPixel() == 8)
  {
    (*lppStream)->Write (pWinBmp->GetBMI(), sizeof (BITMAPINFOHEADER), &BytesWritten );
    (*lppStream)->Write (pWinBmp->GetPalette(), 256*4, &BytesWritten );
    (*lppStream)->Write (pCurLine, pWinBmp->GetBytesPerLine()*m_Height, &BytesWritten );
  }
  else
  {
    BITMAPINFOHEADER FileBMI = *(pWinBmp->GetBMI());
    FileBMI.biBitCount = 24;
    (*lppStream)->Write (&FileBMI, sizeof (BITMAPINFOHEADER), &BytesWritten);

    int x,y;
    int LinePadding = 4-((m_Width*3)&3);
    if (LinePadding == 4)
      LinePadding = 0;

    for (y=m_Height-1; y>=0; y--)
    {
      pCurLine = m_pLineArray[y];
      for (x=0; x<m_Width; x++)
      {
        (*lppStream)->Write(pCurLine+x*4, 3, &BytesWritten);
      }
      (*lppStream)->Write(" ", LinePadding, &BytesWritten);
    }
  }

  LARGE_INTEGER li_NULL;
  li_NULL.LowPart = 0;
  li_NULL.HighPart = 0;

  HRESULT hResult = (*lppStream)->Seek(li_NULL,STREAM_SEEK_SET,NULL);

  return hResult;
}

/*
/--------------------------------------------------------------------
|
|      $Log: ComPicDecoder.cpp,v $
|      Revision 1.3  2000/01/10 23:53:00  Ulrich von Zadow
|      Changed formatting & removed tabs.
|
|
--------------------------------------------------------------------
*/
