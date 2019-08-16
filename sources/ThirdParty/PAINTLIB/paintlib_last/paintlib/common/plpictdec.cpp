/*
/--------------------------------------------------------------------
|
|      $Id: plpictdec.cpp,v 1.6 2001/10/21 17:12:40 uzadow Exp $
|      Macintosh pict Decoder Class
|
|      This class decodes macintosh PICT files with 1,2,4,8,16 and 32
|      bits per pixel as well as PICT/JPEG. If an alpha channel is
|      present in a 32-bit-PICT, it is decoded as well.
|      The PICT format is a general picture file format and can
|      contain a lot of other elements besides bitmaps. These elements
|      are ignored.
|
|      Copyright (c) 1996-1998 Ulrich von Zadow
|
\--------------------------------------------------------------------
*/

#include "plstdpch.h"
#include "config.h"
#include "plpictdec.h"
#ifdef PL_SUPPORT_JPEG
#include "pljpegdec.h"
#endif
#include "ploptable.h"
#include "plexcept.h"

#include <stdio.h>

PLPictDecoder::PLPictDecoder
    ( PLJPEGDecoder * pJPEGDecoder
    )
    : PLPicDecoder(),
      m_pJPEGDecoder (pJPEGDecoder),
      m_Resolution(0,0)
    // Creates a decoder
{
}


PLPictDecoder::~PLPictDecoder
    ()
{
}


void PLPictDecoder::DoDecode
    ( PLBmp * pBmp,
      PLDataSource * pDataSrc
    )
    // Called by MakeDIB to do the actual decoding.
{
  int Version;

  Trace (2, "Decoding mac pict.\n");

  // Skip empty 512 byte header.
  pDataSrc->Skip (512);

  // Read PICT header
  readHeader (pDataSrc, Version);

  interpretOpcodes (pBmp, pDataSrc, Version);
  pBmp->SetResolution (m_Resolution);
}

void PLPictDecoder::readHeader
    ( PLDataSource * pDataSrc,
      int& Version
    )
    // Decodes header and version information.
    // Performs checks to make sure the data is really a pict file.
{
  PLBYTE ch;
  PLWORD PicSize;  // Version 1 picture size. Ignored in version 2.
  char sz[256];
  MacRect Frame;

  PicSize = ReadMWord (pDataSrc);

  readRect (&Frame, pDataSrc);

  while ((ch = ReadByte(pDataSrc)) == 0);
  if (ch != 0x11)
                raiseError (PL_ERRWRONG_SIGNATURE,
                "Error decoding pict: Version number missing.");

  switch (ReadByte(pDataSrc))
  {
    case 1:
      Version = 1;
      break;
    case 2:
      if (ReadByte(pDataSrc) != 0xff)
        raiseError (PL_ERRWRONG_SIGNATURE,
                    "Illegal version number.");
      Version = 2;
      break;
    default:
      raiseError (PL_ERRWRONG_SIGNATURE,
                  "Illegal version number.");
  }

  sprintf (sz, "PICT version %d found.\n", Version);
  Trace (2, sz);
}


void PLPictDecoder::interpretOpcodes
    ( PLBmp * pBmp,
      PLDataSource * pDataSrc,
      int& Version
    )
    // This is the main decoder loop. The functions reads opcodes,
    // skips some, and hands the rest to opcode-specific functions.
    // It stops decoding after the first opcode containing bitmapped
    // data.
{
  PLWORD   Opcode;
  char   sz[256];

  bool   bDone = false;

  while (!bDone)
  {
    Opcode = readOpcode(Version, pDataSrc);

    if (Opcode == 0xFF || Opcode == 0xFFFF)
    {
      bDone = true;
      Trace (2, "Opcode: End of pict.\n");
      raiseError (PL_ERRFORMAT_NOT_SUPPORTED,
                  "PICT contained only vector data!\n");
    }
    else if (Opcode < 0xa2)
    {
      if (!strcmp(optable[Opcode].name, "reserved"))
        sprintf (sz, "Opcode: reserved=0x%x\n", Opcode);
      else
        sprintf (sz, "Opcode: %s\n", optable[Opcode].name);
      Trace (2, sz);

      switch (Opcode)
      {
        case 0x01: // Clip
          clip (pDataSrc);
          break;
        case 0x12:
        case 0x13:
        case 0x14:
          pixPat (pDataSrc);
          break;
        case 0x70:
        case 0x71:
        case 0x72:
        case 0x73:
        case 0x74:
        case 0x75:
        case 0x76:
        case 0x77:
          skipPolyOrRegion (pDataSrc);
          break;
        case 0x90:
        case 0x98:
          bitsRect (pDataSrc, pBmp);
          bDone = true;
          break;
        case 0x91:
        case 0x99:
          bitsRegion (pDataSrc, pBmp);
          bDone = true;
          break;
        case 0x9a:
          opcode9a (pDataSrc, pBmp);
          bDone = true;
          break;
        case 0xa1:
          longComment (pDataSrc);
          break;
        default:
          // No function => skip to next Opcode
          if (optable[Opcode].len == WORD_LEN)
            pDataSrc->Skip(ReadMWord(pDataSrc));
           else
            pDataSrc->Skip(optable[Opcode].len);
      }
    }
    else if (Opcode == 0xc00)
    {
      Trace (2, "Opcode: Header.\n");
      headerOp (pDataSrc, pBmp);
    }
    else if (Opcode == 0x8200)
    {
      Trace (2, "Opcode: JPEG.\n");
      jpegOp (pDataSrc, pBmp);
      bDone = true;
    }
    else if (Opcode >= 0xa2 && Opcode <= 0xaf)
    {
      sprintf (sz, "Opcode: reserved 0x%x.\n", Opcode);
      Trace (2, sz);
      pDataSrc->Skip(ReadMWord(pDataSrc));
    }
    else if ((Opcode >= 0xb0 && Opcode <= 0xcf) ||
             (Opcode >= 0x8000 && Opcode <= 0x80ff))
    {
      // just a reserved Opcode, no data
      sprintf (sz, "Opcode: reserved 0x%x.\n", Opcode);
      Trace (2, sz);
    }
    else if ((Opcode >= 0xd0 && Opcode <= 0xfe) ||
             (Opcode >= 8100 && Opcode <= 0xffff))
    {
      sprintf (sz, "Opcode: reserved 0x%x.\n", Opcode);
      Trace (2, sz);
      pDataSrc->Skip(ReadMLong(pDataSrc));
    }
    else if (Opcode >= 0x100 && Opcode <= 0x7fff)
    {
      sprintf (sz, "Opcode: reserved 0x%x.\n", Opcode);
      Trace (2, sz);
      pDataSrc->Skip((Opcode >> 7) & 255);
    }
    else
    {
      char sz[256];
      sprintf (sz, "Can't handle Opcode %x.\n", Opcode);
      raiseError (PL_ERRFORMAT_UNKNOWN, sz);
    }
  }
}


PLWORD PLPictDecoder::readOpcode
    ( int Version,
      PLDataSource * pDataSrc
    )
    // moves to an even byte position in the file and returns the
    // opcode found.
{
  if (Version == 2)
    pDataSrc->AlignToWord();

  if (Version == 1)
    return ReadByte (pDataSrc);
   else
    return ReadMWord (pDataSrc);
}


/////////////////////////////////////////////////////////////////////
// Opcode functions

void PLPictDecoder::clip
    ( PLDataSource * pDataSrc
    )
    // skips clipping rectangle or region.
{
  MacRect ClipRect;

  PLWORD len = ReadMWord(pDataSrc);

  if (len == 0x000a)
    { /* null rgn */
      readRect(&ClipRect, pDataSrc);
    }
   else
    pDataSrc->Skip(len - 2);
}

void PLPictDecoder::pixPat
    ( PLDataSource * pDataSrc
    )
    // skips pattern definition.
{
  PLWORD       PatType;
  PLWORD       rowBytes;
  MacpixMap  p;
  PLWORD       NumColors;

  PatType = ReadMWord(pDataSrc);

  switch (PatType)
    {
      case 2:
        pDataSrc->Skip(8);
        pDataSrc->Skip(5);
        break;
      case 1:
        {
          pDataSrc->Skip(8);
          rowBytes = ReadMWord(pDataSrc);
          readRect(&p.Bounds, pDataSrc);
          readPixmap(&p, pDataSrc);

          PLPixel32 CT[256];
          readColourTable(&NumColors, pDataSrc, CT);
          skipBits(&p.Bounds, rowBytes, p.pixelSize, pDataSrc);
        }
        break;
      default:
        raiseError (PL_ERRFORMAT_UNKNOWN,
                    "Unknown pattern type in pixPat.");
    }
}

void PLPictDecoder::skipPolyOrRegion
    ( PLDataSource * pDataSrc
    )
{
  Trace (3, "Skipping polygon or region.\n");
  pDataSrc->Skip (ReadMWord (pDataSrc) - 2);
}

void PLPictDecoder::bitsRect
    ( PLDataSource * pDataSrc,
      PLBmp * pBmp
    )
    // Bitmap/pixmap data clipped by a rectangle.
{
  PLWORD rowBytes;

  rowBytes = ReadMWord(pDataSrc);    // Bytes per row in source when
                                     // uncompressed.
  if (rowBytes & 0x8000)
    doPixmap(rowBytes, false, pBmp, pDataSrc);
   else
    doBitmap(rowBytes, false, pBmp, pDataSrc);
}

void PLPictDecoder::bitsRegion
    ( PLDataSource * pDataSrc,
      PLBmp * pBmp
    )
    // Bitmap/pixmap data clipped by a region.
{
  PLWORD rowBytes;

  rowBytes = ReadMWord(pDataSrc);    // Bytes per row in source when
                                     // uncompressed.
  if (rowBytes & 0x8000)
    doPixmap(rowBytes, true, pBmp, pDataSrc);
   else
    doBitmap(rowBytes, true, pBmp, pDataSrc);
}

void PLPictDecoder::opcode9a
    ( PLDataSource * pDataSrc,
      PLBmp * pBmp
    )
    // DirectBitsRect.
{
  MacpixMap PixMap;

  pDataSrc->Skip(4);           // Skip fake len and fake EOF.
  ReadMWord(pDataSrc);         // bogus row bytes.

  // Read in the PixMap fields.
  readRect(&PixMap.Bounds, pDataSrc);
  readPixmap (&PixMap, pDataSrc);

  // Ignore source & destination rectangle as well as transfer mode.
  MacRect TempRect;
  readRect (&TempRect, pDataSrc);
  readRect (&TempRect, pDataSrc);
  PLWORD mode = ReadMWord(pDataSrc);

  // Create empty DIB
  createOutputBmp (PixMap, pBmp);
  pBmp->Lock(false, true);

  // Do the actual unpacking.
  switch (PixMap.pixelSize)
  {
    case 32:
      unpack32bits (&PixMap.Bounds, 0, PixMap.cmpCount, pBmp, pDataSrc);
      break;
    case 8:
      unpack8bits (&PixMap.Bounds, 0, pBmp, pDataSrc);
      break;
    default:
      unpackbits (&PixMap.Bounds, 0, PixMap.pixelSize, pBmp, pDataSrc);
  }
  pBmp->Unlock();
}

void PLPictDecoder::longComment
    ( PLDataSource * pDataSrc
    )
{
  PLWORD type;
  PLWORD len;

  type = ReadMWord(pDataSrc);
  len = ReadMWord(pDataSrc);
  if (len > 0)
    pDataSrc->Skip (len);
}

void PLPictDecoder::headerOp 
    ( PLDataSource * pDataSrc,
      PLBmp * pBmp
    )
{
  int Version = ReadMWord (pDataSrc);
  m_Resolution.x = ReadMLong(pDataSrc);
  m_Resolution.y = ReadMLong(pDataSrc);
  MacRect Dummy;
  readRect (&Dummy, pDataSrc);
  ReadMWord (pDataSrc);
}

void PLPictDecoder::jpegOp
    ( PLDataSource * pDataSrc,
      PLBmp * pBmp
    )
    // Invoke the JPEG decoder for this PICT.
{
  long OpLen = ReadMLong(pDataSrc);
  bool bFound = false;
  int i = 0;

  // skip to JPEG header.
  while (!bFound && i < OpLen)
  {
    PLBYTE * pData = pDataSrc->GetBufferPtr (3);
    if (pData[0] == 0xFF && pData[1] == 0xD8 && pData[2] == 0xFF)
      bFound = true;
    else
    {
      ReadByte(pDataSrc);
      i++;
    }
  }
  if (bFound)
    // Pass the data to the JPEG decoder.
    if (m_pJPEGDecoder)
#ifdef PL_SUPPORT_JPEG
      m_pJPEGDecoder->MakeBmp (pDataSrc, pBmp);
#else
      raiseError (PL_ERRFORMAT_NOT_SUPPORTED,
                  "Library not compiled for PICT/JPEG.");
#endif
     else
      raiseError (PL_ERRFORMAT_NOT_SUPPORTED,
                  "Library not compiled for PICT/JPEG.");
   else
    raiseError (PL_ERRFORMAT_NOT_SUPPORTED,
                "PICT file contains unrecognized quicktime data.\n");
}

/////////////////////////////////////////////////////////////////////
// Bitmap & Pixmap functions

void PLPictDecoder::createOutputBmp
    ( MacpixMap PixMap,
      PLBmp * pBmp
    )
{
  int DestBPP;
  if (PixMap.pixelSize > 8)
    DestBPP = 32;
  else
    DestBPP = 8;

  bool bAlpha = false;
  // Create empty DIB
  if (DestBPP == 32 && PixMap.cmpCount == 4)
    bAlpha = true;
  pBmp->Create (PixMap.Bounds.right - PixMap.Bounds.left,
                PixMap.Bounds.bottom - PixMap.Bounds.top,
                DestBPP, bAlpha);
}


void PLPictDecoder::doBitmap
    ( int rowBytes,
      bool bIsRegion,
      PLBmp * pBmp,
      PLDataSource * pDataSrc
    )
    // Decode version 1 bitmap: 1 bpp.
{
  MacRect Bounds;
  MacRect SrcRect;
  MacRect DstRect;
  PLWORD    mode;
  PLWORD    width;        // Width in pixels
  PLWORD    height;       // Height in pixels

  Trace (2, "Reading version 1 bitmap.\n");

  readRect(&Bounds, pDataSrc);
  dumpRect ("  Bounds", &Bounds);
  readRect(&SrcRect, pDataSrc);
  readRect(&DstRect, pDataSrc);

  width = Bounds.right - Bounds.left;
  height = Bounds.bottom - Bounds.top;

  // Create empty DIB without resolution info.
  pBmp->Create (width, height, 8, false);

  mode = ReadMWord(pDataSrc);

  if (bIsRegion)
    skipPolyOrRegion (pDataSrc);

  pBmp->Lock(false, true);
  pBmp->SetPaletteEntry (0, 0, 0, 0, 255);
  pBmp->SetPaletteEntry (1, 255, 255, 255, 255);
  unpackbits (&Bounds, rowBytes, 1, pBmp, pDataSrc);

  pBmp->Unlock();
}

void PLPictDecoder::doPixmap
    ( int rowBytes,
      bool bIsRegion,
      PLBmp * pBmp,
      PLDataSource * pDataSrc
    )
    // Decode version 2 pixmap
{
  MacpixMap   PixMap;
  PLWORD      NumColors;    // Palette size.

  readRect(&PixMap.Bounds, pDataSrc);
  readPixmap(&PixMap, pDataSrc);

  createOutputBmp (PixMap, pBmp);

  // Read mac colour table into windows palette.
  PLPixel32 Pal[256];
  readColourTable (&NumColors, pDataSrc, Pal);
  if (pBmp->GetBitsPerPixel() == 8)
    pBmp->SetPalette (Pal);

  // Ignore source & destination rectangle as well as transfer mode.
  MacRect TempRect;
  readRect (&TempRect, pDataSrc);
  readRect (&TempRect, pDataSrc);
  PLWORD mode = ReadMWord(pDataSrc);

  if (bIsRegion)
    skipPolyOrRegion (pDataSrc);

  pBmp->Lock(false, true);
  switch (PixMap.pixelSize)
  {
    case 32:
      unpack32bits (&PixMap.Bounds, rowBytes, PixMap.cmpCount, pBmp, pDataSrc);
      break;
    case 8:
      unpack8bits (&PixMap.Bounds, rowBytes, pBmp, pDataSrc);
      break;
    default:
      unpackbits (&PixMap.Bounds, rowBytes, PixMap.pixelSize,
                  pBmp, pDataSrc);
  }
  pBmp->Unlock();
}

void PLPictDecoder::unpack32bits
    ( MacRect* pBounds,
      PLWORD rowBytes,
      int NumBitPlanes,    // 3 if RGB, 4 if RGBA
      PLBmp * pBmp,
      PLDataSource * pDataSrc
    )
    // This routine decompresses BitsRects with a packType of 4 (and
    // 32 bits per pixel). In this format, each line is separated
    // into 8-bit-bitplanes and then compressed via RLE. To decode,
    // the routine decompresses each line & then juggles the bytes
    // around to get pixel-oriented data.
{
  int    i,j;
  PLWORD   BytesPerRow;        // bytes per row when uncompressed.
  PLPixel32 * pDestLine;

  PLBYTE * pLinebuf;           // Temporary buffer for line data. In
                             // this buffer, pixels are uncompressed
                             // but still plane-oriented.
  PLPixel32 ** pLineArray = pBmp->GetLineArray32();


  int Height = pBounds->bottom - pBounds->top;
  int Width = pBounds->right - pBounds->left;

  BytesPerRow = Width*NumBitPlanes;

  if (rowBytes == 0)
    rowBytes = Width*4;

  // Allocate temporary line buffer.
  pLinebuf = new PLBYTE [BytesPerRow];

  try
  {
    for (i = 0; i < Height; i++)
    { // for each line do...
      int linelen;            // length of source line in bytes.
      if (rowBytes > 250)
        linelen = ReadMWord(pDataSrc);
       else
        linelen = ReadByte(pDataSrc);

      PLBYTE * pBuf = unpackPictRow (pLinebuf, pDataSrc, Width, rowBytes, linelen);

      // Convert plane-oriented data into pixel-oriented data &
      // copy into destination bitmap.
      pDestLine = pLineArray[i];

      if (NumBitPlanes == 3)
        for (j = 0; j < Width; j++)
        { // For each pixel in line...
          pDestLine->SetB (*(pBuf+Width*2));     // Blue
          pDestLine->SetG (*(pBuf+Width));       // Green
          pDestLine->SetR (*pBuf);             // Red
          pDestLine->SetA (0xFF);        
          pDestLine++;
          pBuf++;
        }
      else
        for (j = 0; j < Width; j++)
        { // For each pixel in line...
          pDestLine->SetB (*(pBuf+Width*3));     // Blue
          pDestLine->SetG (*(pBuf+Width*2));     // Green
          pDestLine->SetR (*(pBuf+Width));       // Red
          pDestLine->SetA (*pBuf);        
          pDestLine++;
          pBuf++;
        }
    }
  }
  catch (PLTextException)
  {
    delete [] pLinebuf;
    throw;
  }
  catch(...)
  {
    delete [] pLinebuf;
    throw;
  }
  delete [] pLinebuf;
}


void PLPictDecoder::unpack8bits
    ( MacRect* pBounds,
      PLWORD rowBytes,
      PLBmp * pBmp,
      PLDataSource * pDataSrc
    )
    // Decompression routine for 8 bpp. rowBytes is the number of
    // bytes each source row would take if it were uncompressed.
    // This _isn't_ equal to the number of pixels in the row - it
    // seems apple pads the data to a word boundary and then
    // compresses it. Of course, we have to decompress the excess
    // data and then throw it away.
{
  int     i;
  PLBYTE ** pLineArray = pBmp->GetLineArray();

  int Height = pBounds->bottom - pBounds->top;
  int Width = pBounds->right - pBounds->left;

  // High bit of rowBytes is flag.
  rowBytes &= 0x7fff;

  if (rowBytes == 0)
    rowBytes = Width;

  PLBYTE * pLineBuf = new PLBYTE [rowBytes];

  try
  {
    for (i = 0; i < Height; i++)
    {
      int linelen;            // length of source line in bytes.
      if (rowBytes > 250)
        linelen = ReadMWord(pDataSrc);
       else
        linelen = ReadByte(pDataSrc);
      PLBYTE * pRawLine = unpackPictRow (pLineBuf, pDataSrc, Width, rowBytes, linelen);
      memcpy (pLineArray[i], pRawLine, Width);
    }
  }
  catch (PLTextException)
  {
    delete [] pLineBuf;
    throw;
  }
  delete [] pLineBuf;
}


void PLPictDecoder::unpackbits
    ( MacRect* pBounds,
      PLWORD rowBytes,
      int pixelSize,         // Source bits per pixel.
      PLBmp * pBmp,
      PLDataSource * pDataSrc
    )
    // Decompression routine for everything but 8 & 32 bpp. This
    // routine is slower than the two routines above since it has to
    // deal with a lot of special cases :-(.
    // It's also a bit chaotic because of these special cases...
    // unpack8bits is basically a dumber version of unpackbits.
{
  PLBYTE * pSrcLine;           // Pointer to source line in file.
  int    i,j,k;
  PLWORD   pixwidth;           // bytes per row when uncompressed.
  int    linelen;            // length of source line in bytes.
  int    pkpixsize;
  PLBYTE * pDestLine;
  PLBYTE   FlagCounter;
  int    len;
  int    PixelPerRLEUnit;
  PLBYTE * pLineBuf;
  PLBYTE * pBuf;
  PLBYTE ** pLineArray = pBmp->GetLineArray();

  int Height = pBounds->bottom - pBounds->top;
  int Width = pBounds->right - pBounds->left;

  // High bit of rowBytes is flag.
  if (pixelSize <= 8)
    rowBytes &= 0x7fff;

  pixwidth = Width;
  pkpixsize = 1;          // RLE unit: one byte for everything...
  if (pixelSize == 16)    // ...except 16 bpp.
  {
    pkpixsize = 2;
    pixwidth *= 2;
  }

  if (rowBytes == 0)
    rowBytes = pixwidth;

  try
  {
    // I allocate the temporary line buffer here. I allocate too
    // much memory to compensate for sloppy (& hence fast)
    // decompression.
    switch (pixelSize)
    {
      case 1:
        PixelPerRLEUnit = 8;
        pLineBuf = new PLBYTE [(rowBytes+1) * 32];
        break;
      case 2:
        PixelPerRLEUnit = 4;
        pLineBuf = new PLBYTE [(rowBytes+1) * 16];
        break;
      case 4:
        PixelPerRLEUnit = 2;
        pLineBuf = new PLBYTE [(rowBytes+1) * 8];
        break;
      case 8:
        PixelPerRLEUnit = 1;
        pLineBuf = new PLBYTE [rowBytes * 4];
        break;
      case 16:
        PixelPerRLEUnit = 1;
        pLineBuf = new PLBYTE [rowBytes * 2 + 4];
        break;
      default:
        char sz[256];
        sprintf (sz,
                 "Illegal bpp value in unpackbits: %d\n",
                 pixelSize);
        raiseError (PL_ERRFORMAT_UNKNOWN, sz);
    }

    if (rowBytes < 8)
    { // ah-ha!  The bits aren't actually packed.  This will be easy.
      for (i = 0; i < Height; i++)
      {
        pDestLine = pLineArray[i];
        pSrcLine = pDataSrc->ReadNBytes (rowBytes);
        if (pixelSize == 16)
          expandBuf(pDestLine, pSrcLine, Width, pixelSize);
        else
          expandBuf8(pDestLine, pSrcLine, Width, pixelSize);
      }
    }
    else
    {
      for (i = 0; i < Height; i++)
      { // For each line do...
        if (rowBytes > 250)
          linelen = ReadMWord(pDataSrc);
         else
          linelen = ReadByte(pDataSrc);

        pSrcLine = pDataSrc->ReadNBytes(linelen);
        pBuf = pLineBuf;

        // Unpack RLE. The data is packed bytewise - except for
        // 16 bpp data, which is packed per pixel :-(.
        for (j = 0; j < linelen; )
        {
          FlagCounter = pSrcLine[j];
          if (FlagCounter & 0x80)
          {
            if (FlagCounter == 0x80)
              // Special case: repeat value of 0.
              // Apple sais ignore.
              j++;
            else
            { // Packed data.
              len = ((FlagCounter ^ 255) & 255) + 2;

              // This is slow for some formats...
              if (pixelSize == 16)
              {
                expandBuf (pBuf, pSrcLine+j+1, 1, pixelSize);
                for (k = 1; k < len; k++)
                { // Repeat the pixel len times.
                  memcpy (pBuf+(k*4*PixelPerRLEUnit), pBuf,
                          4*PixelPerRLEUnit);
                }
                pBuf += len*4*PixelPerRLEUnit;
              }
              else
              {
                expandBuf8 (pBuf, pSrcLine+j+1, 1, pixelSize);
                for (k = 1; k < len; k++)
                { // Repeat the expanded byte len times.
                  memcpy (pBuf+(k*PixelPerRLEUnit), pBuf,
                          PixelPerRLEUnit);
                }
                pBuf += len*PixelPerRLEUnit;
              }
              j += 1 + pkpixsize;
            }
          }
          else
          { // Unpacked data
            len = (FlagCounter & 255) + 1;
            if (pixelSize == 16)
            {
              expandBuf (pBuf, pSrcLine+j+1, len, pixelSize);
              pBuf += len*4*PixelPerRLEUnit;
            }
            else
            {
              expandBuf8 (pBuf, pSrcLine+j+1, len, pixelSize);
              pBuf += len*PixelPerRLEUnit;
            }
            j += len * pkpixsize + 1;
          }
        }
        pDestLine = pLineArray[i];
        if (pixelSize == 16)
          memcpy (pDestLine, pLineBuf, 4*Width);
        else
          memcpy (pDestLine, pLineBuf, Width);
      }
    }
  }
  catch (PLTextException)
  {
    delete [] pLineBuf;
    throw;
  }

  delete [] pLineBuf;
}

void PLPictDecoder::skipBits
    ( MacRect* pBounds,
      PLWORD rowBytes,
      int pixelSize,         // Source bits per pixel.
      PLDataSource * pDataSrc
    )
    // skips unneeded packbits.
{
  int    i;
  PLWORD   pixwidth;           // bytes per row when uncompressed.
  int    linelen;            // length of source line in bytes.

  int Height = pBounds->bottom - pBounds->top;
  int Width = pBounds->right - pBounds->left;

  // High bit of rowBytes is flag.
  if (pixelSize <= 8)
    rowBytes &= 0x7fff;

  pixwidth = Width;

  if (pixelSize == 16)
    pixwidth *= 2;

  if (rowBytes == 0)
    rowBytes = pixwidth;

  if (rowBytes < 8)
  {
    pDataSrc->Skip (rowBytes*Height);
  }
  else
  {
    for (i = 0; i < Height; i++)
    {
      if (rowBytes > 250)
        linelen = ReadMWord(pDataSrc);
       else
        linelen = ReadByte(pDataSrc);
      pDataSrc->Skip (linelen);
    }
  }
}


void PLPictDecoder::expandBuf
    ( PLBYTE * pDestBuf,
      PLBYTE * pSrcBuf,
      int Width,       // Width in bytes for 8 bpp or less.
                       // Width in pixels for 16 bpp.
      int bpp          // bits per pixel
    )
    // Expands Width units to 32-bit pixel data.
{
  PLBYTE * pSrc;
  PLBYTE * pDest;
  int i;

  pSrc = pSrcBuf;
  pDest = pDestBuf;

  switch (bpp)
  {
    case 16:
      for (i=0; i<Width; i++)
      {
        PLWORD Src = pSrcBuf[1]+(pSrcBuf[0]<<8);
        *(pDestBuf+PL_RGBA_BLUE) = ((Src) & 31)*8;          // Blue
        *(pDestBuf+PL_RGBA_GREEN) = ((Src >> 5) & 31)*8;    // Green
        *(pDestBuf+PL_RGBA_RED) = ((Src  >> 10) & 31)*8;    // Red
        *(pDestBuf+PL_RGBA_ALPHA) = 0xFF;                   // Alpha
        pSrcBuf += 2;
        pDestBuf += 4;
      }
      break;
    default:
      raiseError (PL_ERRFORMAT_UNKNOWN,
                  "Bad bits per pixel in expandBuf.");
  }
  return;
}


void PLPictDecoder::expandBuf8
    ( PLBYTE * pDestBuf,
      PLBYTE * pSrcBuf,
      int Width,       // Width in bytes.
      int bpp          // bits per pixel.
    )
    // Expands Width units to 8-bit pixel data.
    // Max. 8 bpp source format.
{
  PLBYTE * pSrc;
  PLBYTE * pDest;
  int i;

  pSrc = pSrcBuf;
  pDest = pDestBuf;

  switch (bpp)
  {
    case 8:
      memcpy (pDestBuf, pSrcBuf, Width);
      break;
    case 4:
      for (i=0; i<Width; i++)
      {
        *pDest = (*pSrc >> 4) & 15;
        *(pDest+1) = (*pSrc & 15);
        pSrc++;
        pDest += 2;
      }
      if (Width & 1) // Odd Width?
      {
        *pDest = (*pSrc >> 4) & 15;
        pDest++;
      }
      break;
    case 2:
      for (i=0; i<Width; i++)
      {
        *pDest = (*pSrc >> 6) & 3;
        *(pDest+1) = (*pSrc >> 4) & 3;
        *(pDest+2) = (*pSrc >> 2) & 3;
        *(pDest+3) = (*pSrc & 3);
        pSrc++;
        pDest += 4;
      }
      if (Width & 3)  // Check for leftover pixels
        for (i=6; i>8-(Width & 3)*2; i-=2)
        {
          *pDest = (*pSrc >> i) & 3;
          pDest++;
        }
      break;
    case 1:
      for (i=0; i<Width; i++)
      {
        *pDest = (*pSrc >> 7) & 1;
        *(pDest+1) = (*pSrc >> 6) & 1;
        *(pDest+2) = (*pSrc >> 5) & 1;
        *(pDest+3) = (*pSrc >> 4) & 1;
        *(pDest+4) = (*pSrc >> 3) & 1;
        *(pDest+5) = (*pSrc >> 2) & 1;
        *(pDest+6) = (*pSrc >> 1) & 1;
        *(pDest+7) = (*pSrc  & 1);
        pSrc++;
        pDest += 8;
      }
      if (Width & 7)  // Check for leftover pixels
        for (i=7; i>(8-Width & 7); i--)
        {
          *pDest = (*pSrc >> i) & 1;
          pDest++;
        }
      break;
    default:
      raiseError (PL_ERRFORMAT_UNKNOWN,
                  "Bad bits per pixel in expandBuf8.");
  }
  return;
}


/////////////////////////////////////////////////////////////////////
// Auxillary functions

void PLPictDecoder::readPixmap
    ( MacpixMap * pPixMap,
      PLDataSource * pDataSrc
    )
{
  pPixMap->version = ReadMWord(pDataSrc);
  pPixMap->packType = ReadMWord(pDataSrc);
  pPixMap->packSize = ReadMLong(pDataSrc);
  pPixMap->hRes = ReadMLong(pDataSrc);
  pPixMap->vRes = ReadMLong(pDataSrc);
  pPixMap->pixelType = ReadMWord(pDataSrc);
  pPixMap->pixelSize = ReadMWord(pDataSrc);
  pPixMap->cmpCount = ReadMWord(pDataSrc);
  pPixMap->cmpSize = ReadMWord(pDataSrc);
  pPixMap->planeBytes = ReadMLong(pDataSrc);
  pPixMap->pmTable = ReadMLong(pDataSrc);
  pPixMap->pmReserved = ReadMLong(pDataSrc);

  tracePixMapHeader (2, pPixMap);
}

void PLPictDecoder::readColourTable
    ( PLWORD * pNumColors,
      PLDataSource * pDataSrc,
      PLPixel32 * pPal
    )
    // Reads a mac colour table into a bitmap palette.
{
  PLLONG        ctSeed;
  PLWORD        ctFlags;
  PLWORD        val;
  int         i;

  Trace (3, "Getting color table info.\n");

  ctSeed = ReadMLong(pDataSrc);
  ctFlags = ReadMWord(pDataSrc);
  *pNumColors = ReadMWord(pDataSrc)+1;

  char sz[256];
  sprintf (sz, "Palette Size:  %d\n", *pNumColors);
  Trace (2, sz);
  Trace (3, "Reading Palette.\n");

  for (i = 0; i < *pNumColors; i++)
  {
    val = ReadMWord(pDataSrc);
    if (ctFlags & 0x8000)
      // The indicies in a device colour table are bogus and
      // usually == 0, so I assume we allocate up the list of
      // colours in order.
      val = i;
    if (val >= *pNumColors)
    {
      raiseError (PL_ERRFORMAT_UNKNOWN,
                  "pixel value greater than colour table size.");
    }
    // Mac colour tables contain 16-bit values for R, G, and B...
    pPal[val].SetR ((PLBYTE) (((PLWORD) (ReadMWord(pDataSrc)) >> 8) & 0xFF));
    pPal[val].SetG ((PLBYTE) (((PLWORD) (ReadMWord(pDataSrc)) >> 8) & 0xFF));
    pPal[val].SetB ((PLBYTE) (((PLWORD) (ReadMWord(pDataSrc)) >> 8) & 0xFF));
  }

}

void PLPictDecoder::readRect
    ( MacRect * pr,
      PLDataSource * pDataSrc
    )
{
  pr->top = ReadMWord(pDataSrc);
  pr->left = ReadMWord(pDataSrc);
  pr->bottom = ReadMWord(pDataSrc);
  pr->right = ReadMWord(pDataSrc);
}


void PLPictDecoder::dumpRect
    ( char * psz,
      MacRect * pr
    )
{
  char sz[256];
  sprintf (sz, "%s (%d,%d) (%d,%d).\n",
           psz, pr->left, pr->top, pr->right, pr->bottom);
  Trace (2, sz);
}


void PLPictDecoder::tracePixMapHeader
    ( int Level,
      MacpixMap * pPixMap
    )
{
  char sz[256];
  Trace (Level, "PixMap header info:\n");
  dumpRect ("  Bounds:", &(pPixMap->Bounds));

  sprintf (sz, "  version: 0x%x\n", pPixMap->version);
  Trace (Level, sz);
  sprintf (sz, "  packType: %d\n", pPixMap->packType);
  Trace (Level, sz);
  sprintf (sz, "  packSize: %ld\n", pPixMap->packSize);
  Trace (Level, sz);
  sprintf (sz, "  pixelSize: %d\n", pPixMap->pixelSize);
  Trace (Level, sz);
  sprintf (sz, "  cmpCount: %d\n", pPixMap->cmpCount);
  Trace (Level, sz);
  sprintf (sz, "  cmpSize: %d.\n", pPixMap->cmpSize);
  Trace (Level, sz);
  sprintf (sz, "  planeBytes: %ld.\n", pPixMap->planeBytes);
  Trace (Level, sz);
}

/*
/--------------------------------------------------------------------
|
|      $Log: plpictdec.cpp,v $
|      Revision 1.6  2001/10/21 17:12:40  uzadow
|      Added PSD decoder beta, removed BPPWanted from all decoders, added PLFilterPixel.
|
|      Revision 1.5  2001/10/16 17:12:26  uzadow
|      Added support for resolution information (Luca Piergentili)
|
|      Revision 1.4  2001/10/06 22:03:26  uzadow
|      Added PL prefix to basic data types.
|
|      Revision 1.3  2001/10/06 15:32:22  uzadow
|      Removed types LPBYTE, DWORD, UCHAR, VOID and INT from the code.
|
|      Revision 1.2  2001/09/16 20:57:17  uzadow
|      Linux version name prefix changes
|
|      Revision 1.1  2001/09/16 19:03:22  uzadow
|      Added global name prefix PL, changed most filenames.
|
|      Revision 1.12  2001/02/04 14:31:52  uzadow
|      Member initialization list cleanup (Erik Hoffmann).
|
|      Revision 1.11  2001/01/21 14:28:21  uzadow
|      Changed array cleanup from delete to delete[].
|
|      Revision 1.10  2000/12/18 22:42:52  uzadow
|      Replaced RGBAPIXEL with PLPixel32.
|
|      Revision 1.9  2000/10/24 23:01:42  uzadow
|      Fixed bug in ver.1 bitmap decoder
|
|      Revision 1.8  2000/08/13 12:11:43  Administrator
|      Added experimental DirectDraw-Support
|
|      Revision 1.7  2000/05/27 16:28:28  Ulrich von Zadow
|      Really fixed bug decoding pixmaps with < 8 bpp.
|
|      Revision 1.6  2000/03/15 17:23:20  Ulrich von Zadow
|      Fixed bug decoding pixmaps with < 8 bpp.
|
|      Revision 1.5  2000/01/16 20:43:14  anonymous
|      Removed MFC dependencies
|
|      Revision 1.4  1999/11/22 15:00:27  Ulrich von Zadow
|      Fixed bug decoding small 24 bpp pict files.
|
|      Revision 1.3  1999/10/03 18:50:51  Ulrich von Zadow
|      Added automatic logging of changes.
|
|
\--------------------------------------------------------------------
*/
