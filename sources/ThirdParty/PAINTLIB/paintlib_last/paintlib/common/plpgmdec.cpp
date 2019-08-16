/*
/--------------------------------------------------------------------
|
|      $Id: plpgmdec.cpp,v 1.4 2001/10/21 17:12:40 uzadow Exp $
|      portable graymap Decoder Class
|
|      Original author: Jose Miguel Buenaposada Biencinto.
|
|      Copyright (c) 1996-1998 Ulrich von Zadow
|
\--------------------------------------------------------------------
*/

#include "plstdpch.h"
#include "plpgmdec.h"
#include "plexcept.h"

PLPGMDecoder::PLPGMDecoder
    ()
    : PLPicDecoder(),
      m_LastByte(0),
      m_UseLastByte(false)
    // Creates a decoder
{
}

PLPGMDecoder::~PLPGMDecoder
    ()
{
}

void PLPGMDecoder::DoDecode
    ( PLBmp * pBmp,
      PLDataSource * pDataSrc
    )
{
  PGMHEADER PgmHead;
  Trace (2, "Decoding PGM.\n");

  readPgmHeader(&PgmHead, pDataSrc);

  // Image doesn't have alpha channel
  pBmp->Create (PgmHead.ImageWidth, PgmHead.ImageHeight,
                8, false);

  readImage (&PgmHead, pBmp, pDataSrc);
}


void PLPGMDecoder::readPgmHeader
    ( PGMHEADER * pPgmHead,       // Pointer to PGM header structure
      PLDataSource * pDataSrc
    )
{
  int current = 0;
  bool HeaderComplete = false;

  // Read type
  m_LastByte = ReadByte (pDataSrc);
  if (m_LastByte!=0x50) // ASCII P
      raiseError (PL_ERRFORMAT_UNKNOWN,
                  "PGM decoder: Is not the correct identifier P5 or P2.");

  m_LastByte = ReadByte (pDataSrc);
  if (m_LastByte==0x32) // ASCII 2
	  pPgmHead->ImageType = PGM_P2;
  else if (m_LastByte==0x35) // ASCII 5
	  pPgmHead->ImageType = PGM_P5;
  else
      raiseError (PL_ERRFORMAT_UNKNOWN,
                  "PGM decoder: Is not the correct identifier P5 or P2.");

  m_LastByte = ReadByte (pDataSrc);

  // Search for the with, height and Max gray value
  while (current<3)
  {
    if (m_LastByte==0x23) // # Starts a comment
		skipComment(pDataSrc);
	else if ((m_LastByte>=0x30)&&(m_LastByte<=0x39)) // A digit
		switch (current)
		{
		case 0: // looking for the width
		  {
		  pPgmHead->ImageWidth = readASCIIDecimal(pDataSrc);
		  current++;
		  }
		  break;
		case 1: // looking for the height
		  {
		  pPgmHead->ImageHeight = readASCIIDecimal(pDataSrc);
		  current++;
		  }
		  break;
		case 2: // looking for the max gray value
		  {
		  pPgmHead->MaxGrayValue  = readASCIIDecimal(pDataSrc);
          if ((pPgmHead->MaxGrayValue>255)||(pPgmHead->MaxGrayValue<=0))
	        pPgmHead->MaxGrayValue=255;
		  current++;
		  }
		  break;
		default:
          continue;
		}
	else
      skipPgmASCIISeparators(pDataSrc);
  }
}

PLBYTE *PLPGMDecoder::readASCIILine(PLDataSource *pDataSrc)
{
  int i = 0;
  bool HaveLine = false;
  PLBYTE byte;
  PLBYTE* pLine   = new PLBYTE[PGM_MAXLINESIZE]; // Line should not be larger than 70 bytes

  do
  {
	  if (i==80)
		  raiseError (PL_ERRFORMAT_UNKNOWN,
	                 "PGM decoder: File Line to long.");

	  byte    =ReadByte(pDataSrc);
	  pLine[i]=byte;
	  if ((byte==0x0D)|| // Carriege Return
	      (byte==0x0A))  // Line Feed
	  {
		  HaveLine=true;
		  pLine[i]=0x00;
	  }
	  i++;
  }
  while (!HaveLine);

  return pLine;
}


int PLPGMDecoder::readASCIIDecimal(PLDataSource * pDataSrc)
{
  int Value    = 0;
  int digit;

  while ((m_LastByte>=0x30)&&(m_LastByte<=0x39)) // Is ASCII digit
  {
	digit      = m_LastByte - 0x30;
	Value      = Value*10+digit;
	m_LastByte = ReadByte(pDataSrc);
  }

  return Value;
}

void PLPGMDecoder::skipComment(PLDataSource * pDataSrc)
{
	while ((m_LastByte!=0x0D)&& // Carriege Return
	       (m_LastByte!=0x0A))  // New Line
	{
	  m_LastByte     = ReadByte(pDataSrc);
	}
}
void PLPGMDecoder::skipPgmASCIISeparators(PLDataSource * pDataSrc)
{
	while ((m_LastByte==0x20)|| // Space
	     (m_LastByte==0x0D)|| // Carriege Return
//	     (m_LastByte<=0x10)|| // Tab
	     (m_LastByte==0x0A))  // New Line
	{
	  m_LastByte     = ReadByte(pDataSrc);
	}
}

void PLPGMDecoder::readImage
    ( PGMHEADER * pPgmHead,       // Pointer to PGM header structure
      PLBmp * pBmp,
      PLDataSource * pDataSrc
    )
{
  switch (pPgmHead->ImageType)
  {
    case PGM_P5:
    case PGM_P2:
      readData(pPgmHead, pBmp, pDataSrc);
	  break;
    default:
      raiseError (PL_ERRFORMAT_UNKNOWN, "Unknown PGM image type.");
  }
}

void PLPGMDecoder::readData
    ( PGMHEADER * pPgmHead,       // Pointer to PGM header structure
      PLBmp * pBmp,
      PLDataSource * pDataSrc
    )
{
  int Width  = pPgmHead->ImageWidth;
  int Height = pPgmHead->ImageHeight;

  PLBYTE * pDest;
  PLBYTE ** pLineArray = pBmp->GetLineArray();

  int y;

  if (pPgmHead->ImageType == PGM_P2)
  {
    skipPgmASCIISeparators(pDataSrc);
    m_UseLastByte = true;
  }

  for (y=0; y < Height; y++)
  {
    pDest = pLineArray[y];
	  if (pPgmHead->ImageType==PGM_P5) // P5
      expandByteLine (pDest, pPgmHead->MaxGrayValue,Width,  pDataSrc);
	  else // P2
      expandASCIILine (pDest, pPgmHead->MaxGrayValue,Width, pDataSrc);
  }
}

void PLPGMDecoder::expandASCIILine
    ( PLBYTE * pDest,
      int MaxGrayValue,
      int Width,
      PLDataSource * pDataSrc
    )
{
  int x;

  for (x=0; x<Width; x++)
  {
    *pDest = readASCIIPixel8 (MaxGrayValue, pDataSrc);
    pDest ++;
  }
}

void PLPGMDecoder::expandByteLine
    ( PLBYTE * pDest,
      int MaxGrayValue,
      int Width,
      PLDataSource * pDataSrc
    )
{
  int x;
  PLBYTE *pLine;

  pLine = pDataSrc->ReadNBytes(Width);
  if (pLine==NULL)
	  return;

  for (x=0; x<Width; x++)
  {
    *pDest = (PLBYTE)(((int)pLine[x]*255)/MaxGrayValue);
    pDest ++;
  }
}

PLBYTE PLPGMDecoder::readASCIIPixel8
    ( int MaxGrayValue,
      PLDataSource * pDataSrc
    )
{
  PLBYTE Dest;
  int Value;

  skipPgmASCIISeparators(pDataSrc);
  m_UseLastByte = true;
  Value    = readASCIIDecimal(pDataSrc);
  Dest     = (PLBYTE)((Value*255)/MaxGrayValue);

  return Dest;
}


/*
/--------------------------------------------------------------------
|
|      $Log: plpgmdec.cpp,v $
|      Revision 1.4  2001/10/21 17:12:40  uzadow
|      Added PSD decoder beta, removed BPPWanted from all decoders, added PLFilterPixel.
|
|      Revision 1.3  2001/10/16 17:12:26  uzadow
|      Added support for resolution information (Luca Piergentili)
|
|      Revision 1.2  2001/10/06 22:37:08  uzadow
|      Linux compatibility.
|
|      Revision 1.1  2001/09/16 19:03:22  uzadow
|      Added global name prefix PL, changed most filenames.
|
|      Revision 1.5  2001/02/04 14:31:52  uzadow
|      Member initialization list cleanup (Erik Hoffmann).
|
|      Revision 1.4  2000/12/18 22:42:52  uzadow
|      Replaced RGBAPIXEL with PLPixel32.
|
|      Revision 1.3  2000/05/27 16:34:05  Ulrich von Zadow
|      Linux compatibility changes
|
|      Revision 1.2  2000/05/23 10:19:11  Ulrich von Zadow
|      Minor unix compatibility changes.
|
|      Revision 1.1  2000/03/16 13:56:37  Ulrich von Zadow
|      Added pgm decoder by Jose Miguel Buenaposada Biencinto
|
|
\--------------------------------------------------------------------
*/
