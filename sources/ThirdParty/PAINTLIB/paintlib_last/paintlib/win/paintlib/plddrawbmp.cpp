/*
/--------------------------------------------------------------------
|
|      $Id: plddrawbmp.cpp,v 1.1 2001/09/16 19:03:23 uzadow Exp $
|      Bitmap class using a directdraw surface.
|
|      Copyright (c) 1996-1998 Ulrich von Zadow
|
\--------------------------------------------------------------------
*/

#include "plstdpch.h"
#include "plddrawbmp.h"
#include "plexcept.h"
#include "plddhelper.h"

#include <stdio.h>

PLDDrawBmp::PLDDrawBmp
    ( IDirectDraw * pDDraw
    )
    : PLBmp(),
      m_pSurface (NULL),
      m_pDDSurfaceDesc (new DDSURFACEDESC),
      m_pDDraw(pDDraw)
    // Creates an empty bitmap.
{  
  internalCreate (0,0,32, false);
  PLASSERT_VALID(this);
}


PLDDrawBmp::~PLDDrawBmp
    ()
{
  // Free the memory.
  freeMembers();
  delete m_pDDSurfaceDesc;
}


#ifdef _DEBUG
void PLDDrawBmp::AssertValid
    () const
{
  // call inherited ASSERT_VALID first
  PLBmp::AssertValid();

  if (m_pSurface)
  {
    DDSURFACEDESC Desc;
    Desc.dwSize = sizeof(Desc); 
    m_pSurface->GetSurfaceDesc(&Desc);
    PLASSERT (int(Desc.dwHeight) == m_Height);
    PLASSERT (int(Desc.dwWidth) == m_Width);
  }
}
#endif


/////////////////////////////////////////////////////////////////////
// PLDDrawBmp information

long PLDDrawBmp::GetMemUsed
    ()
    // Returns the memory used by the object.
{
  PLASSERT_VALID (this);
  PLASSERT (m_pSurface);

  return GetBytesPerLine()*GetHeight();
}


long PLDDrawBmp::GetBytesPerLine
    ()
    // Returns number of bytes used per line.
{
  PLASSERT_VALID (this);
  PLASSERT (m_pSurface);

  switch (m_bpp)
  {
    case 32: 
      return GetWidth() * 4;
    default:
      PLASSERT (false);
      return 0;
  }
}

void PLDDrawBmp::Lock
    ( bool bReadable,
      bool bWriteable
    ) 
    // Locks the DirectDraw surface and fills the line array. GetLineArray() 
    // returns NULL if the surface isn't locked.
    // Always locks the whole surface.
{
  PLBmp::Lock(bReadable, bWriteable);

  PLASSERT_VALID (this);
  PLASSERT (m_pSurface);

  m_pDDSurfaceDesc->dwSize = sizeof(*m_pDDSurfaceDesc);
  DWORD dwFlags = 0;

  if (bReadable && !bWriteable)
    dwFlags |= DDLOCK_READONLY;
  if (!bReadable && bWriteable)
    dwFlags |= DDLOCK_WRITEONLY;
  HRESULT hr = m_pSurface->Lock(NULL, m_pDDSurfaceDesc, dwFlags, NULL);
  CheckForDDError (hr);
  initLineArray();
}

void PLDDrawBmp::Unlock
    () 
    // Unlocks the DirectDraw surface.
{
  PLBmp::Unlock();

  HRESULT hr = m_pSurface->Unlock (NULL);
  CheckForDDError (hr);
  delete[] m_pLineArray;
  initLineArray();
}

IDirectDrawSurface * PLDDrawBmp::GetSurface
  ()
  // Gets a pointer to the directdraw surface used.
{
  return m_pSurface;
}


/////////////////////////////////////////////////////////////////////
// Windows-specific interface

SIZE PLDDrawBmp::GetSize
    ()
    // Returns size in pixels
{
  SIZE sz;

  PLASSERT_VALID (this);

  sz.cx = GetWidth();
  sz.cy = GetHeight();

  return sz;
}




/////////////////////////////////////////////////////////////////////
// Protected callbacks

void PLDDrawBmp::internalCreate
    ( LONG Width,
      LONG Height,
      WORD BitsPerPixel,
      bool bAlphaChannel
    )
    // Create a new empty DIB. Bits are uninitialized.
    // Assumes that no memory is allocated before the call.
{
  PLASSERT (BitsPerPixel == 32);
  PLASSERT (!m_pSurface);

  if (Width != 0 || Height != 0)
  {
    DDSURFACEDESC Desc;
    ZeroMemory(&Desc,sizeof(Desc));
    Desc.dwSize = sizeof(Desc);
    Desc.dwWidth        = Width;
    Desc.dwHeight       = Height;
    Desc.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH | DDSD_PIXELFORMAT;
    Desc.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN | DDSCAPS_SYSTEMMEMORY;
    Desc.ddpfPixelFormat.dwSize  = sizeof(DDPIXELFORMAT);
    Desc.ddpfPixelFormat.dwFlags = DDPF_RGB; 
    Desc.ddpfPixelFormat.dwRGBBitCount = 32;
    Desc.ddpfPixelFormat.dwRBitMask = 0x000000FF;
    Desc.ddpfPixelFormat.dwGBitMask = 0x0000FF00;
    Desc.ddpfPixelFormat.dwBBitMask = 0x00FF0000;
    // DirectX ignores any alpha channel information.
    Desc.ddpfPixelFormat.dwRGBAlphaBitMask = 0x00000000;

    HRESULT hr = m_pDDraw->CreateSurface(&Desc, &m_pSurface, NULL);
    CheckForDDError (hr);   // ---> Replace this by exception.
  }

  // Set color table pointer & pointer to bits.
  initPointers ();

  initLocals (Width, Height, BitsPerPixel, bAlphaChannel);

  PLASSERT_VALID (this);
}


void PLDDrawBmp::freeMembers
    ()
{
  if (m_pSurface)
    m_pSurface->Release();
  m_pSurface = NULL;
}


void PLDDrawBmp::initLineArray
    ()
{
  if (IsLocked())
  {
    m_pLineArray = new BYTE * [m_Height];
    BYTE * pBits = (BYTE *)(m_pDDSurfaceDesc->lpSurface);
    int i;
    for (i = 0; i < GetHeight(); i++)
    {
      m_pLineArray[i] = pBits;
      pBits += m_pDDSurfaceDesc->lPitch;
    }
  }
  else
    m_pLineArray = NULL;
}


void PLDDrawBmp::initPointers
    ()
    // Set color table pointer
{
  m_pClrTab = NULL;
}

/*
/--------------------------------------------------------------------
|
|      $Log: plddrawbmp.cpp,v $
|      Revision 1.1  2001/09/16 19:03:23  uzadow
|      Added global name prefix PL, changed most filenames.
|
|      Revision 1.2  2001/02/04 14:31:52  uzadow
|      Member initialization list cleanup (Erik Hoffmann).
|
|      Revision 1.1  2000/08/13 12:11:43  Administrator
|      Added experimental DirectDraw-Support
|
|
\--------------------------------------------------------------------
*/
