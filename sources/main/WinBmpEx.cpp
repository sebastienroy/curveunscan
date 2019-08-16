// WinBmpEx.cpp: implementation of the CWinBmpEx class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CurveUnscan.h"
#include "WinBmpEx.h"

#include "plexcept.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CWinBmpEx::CWinBmpEx()
{

}

CWinBmpEx::~CWinBmpEx()
{

}

void CWinBmpEx::DrawRect(HDC hDC,const CRect &rect, DWORD rop)
{

int width;
int height;
int sourceY;
if(rect.Height()>GetHeight())
	{
	height=GetHeight();
	sourceY=0;
	}
else
	{
	height=rect.Height();
	sourceY=GetHeight()-rect.bottom;
	}

if(rect.Width()>GetWidth())
	{
	width=GetWidth();
	}
else
	{
	width=rect.Width();
	}



  ::StretchDIBits(hDC,
                  rect.left,                        // Destination x
                  rect.top,                        // Destination y
                  width,               // Destination width
                  height,              // Destination height
                  rect.left,                        // Source x
                  sourceY,                        // Source y
                  width,               // Source width
                  height,              // Source height
                  m_pBits,                  // Pointer to bits
                  (BITMAPINFO *) m_pBMI,    // BITMAPINFO
                  DIB_RGB_COLORS,           // Options
                  rop);                     // Raster operator code

	
}

// This is the overloaded method of PaintLib one
// Paintlib doesn't copy the bits...
void CWinBmpEx::internalCreate(BITMAPINFOHEADER *pBMI)
{
#ifdef MAX_BITMAP_SIZE
	if (GetMemNeeded (pBMI->biWidth, pBMI->biHeight, pBMI->biBitCount)
      > MAX_BITMAP_SIZE)
	  throw PLTextException(PL_ERRDIB_TOO_LARGE, "Bitmap size too large.\n");
#endif

  int MemNeeded = sizeof (BITMAPINFOHEADER);
  if (pBMI->biBitCount < 16)
  { // Color table exists
    MemNeeded += (1 << pBMI->biBitCount)*sizeof (RGBQUAD);
  }

  m_pBMI = (BITMAPINFOHEADER *) malloc (MemNeeded);

  memcpy (m_pBMI, pBMI, MemNeeded);

  // Create DIB section in shared memory
  m_hBitmap = CreateDIBSection (NULL, (BITMAPINFO *)m_pBMI,
                                DIB_RGB_COLORS, (void **)&m_pBits, 0, 0l);

  // SR: the paintlib method doesn't copy the bits
  BYTE* source=(BYTE*)pBMI;
  source+=MemNeeded;
  memcpy (m_pBits, source, pBMI->biSizeImage);


  if (!m_hBitmap)
    throw (PLTextException (PL_ERRNO_MEMORY, "Out of memory creating bitmap."));

  // Set color table pointer & pointer to bits.
  initPointers ();

  initLocals (m_pBMI->biWidth, m_pBMI->biHeight,
              m_pBMI->biBitCount, false);

  PLASSERT_VALID (this);
}
