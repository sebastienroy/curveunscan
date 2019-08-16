/*
/--------------------------------------------------------------------
|
|      $Id: plppmdec.cpp,v 1.3 2001/10/21 17:12:40 uzadow Exp $
|
|      Copyright (c) 2001 Ulrich von Zadow
|
|      Portable Pixmap Decoder Class
|
|      Decodes PPM files, either P3 (ASCII data) or P6 (raw data).
|		   Always decodes to 32 bpp, no alpha channel.
|
|      Originally by Todd Harris - Mar 2001
|      adadapted from pgm.h originally by
|			 Jose Miguel Buenaposada Biencinto. Mar 2000.
|
\--------------------------------------------------------------------
*/

#include "plstdpch.h"
#include "plppmdec.h"
#include "plexcept.h"

PLPPMDecoder::PLPPMDecoder
()
// Creates a decoder
{
}

PLPPMDecoder::~PLPPMDecoder
()
{
}

void PLPPMDecoder::DoDecode
    ( PLBmp * pBmp,
      PLDataSource * pDataSrc
    )
{
	PPMHEADER PpmHead;
	Trace (2, "Decoding PPM.\n");
	
	readPpmHeader(&PpmHead, pDataSrc);

	// Image doesn't have alpha channel
	pBmp->Create (PpmHead.ImageWidth, PpmHead.ImageHeight,
		            32, false);
	
	readImage (&PpmHead, pBmp, pDataSrc);
}


void PLPPMDecoder::readPpmHeader
    ( PPMHEADER * pPpmHead,       // Pointer to PPM header structure
      PLDataSource * pDataSrc
    )
{
	int current = 0;
	bool HeaderComplete = false;
	
	// Read type
	m_LastByte = ReadByte (pDataSrc);
	if (m_LastByte!=0x50) // ASCII P
		raiseError (PL_ERRFORMAT_UNKNOWN,
		"PPM decoder: Is not the correct identifier P3 or P6.");
	
	m_LastByte = ReadByte (pDataSrc);
	if (m_LastByte==0x33) // ASCII 3
		pPpmHead->ImageType = PPM_P3;
	else if (m_LastByte==0x36) // ASCII 6
		pPpmHead->ImageType = PPM_P6;
	else
		raiseError (PL_ERRFORMAT_UNKNOWN,
		"PPM decoder: Is not the correct identifier P3 or P6.");
	
	m_LastByte = ReadByte (pDataSrc);
	
	// Search for the with, height and Max sample value
	while (current<3)
	{
		if (m_LastByte==0x23) // # Starts a comment
			skipComment(pDataSrc);
		else if ((m_LastByte>=0x30)&&(m_LastByte<=0x39)) // A digit
  		switch (current)
		  {
		    case 0: // looking for the width
			    {
				    pPpmHead->ImageWidth = readASCIIDecimal(pDataSrc);
				    current++;
			    }
			    break;
		    case 1: // looking for the height
			    {
				    pPpmHead->ImageHeight = readASCIIDecimal(pDataSrc);
				    current++;
			    }
			    break;
		    case 2: // looking for the sample value (max = 255)
			    {
				    pPpmHead->MaxSampleValue  = readASCIIDecimal(pDataSrc);
				    if ((pPpmHead->MaxSampleValue>255)||(pPpmHead->MaxSampleValue<=0))
					    pPpmHead->MaxSampleValue=255;
				    current++;
			    }
			    break;
		    default:
			    continue;
		  }
		else
			skipPpmASCIISeparators(pDataSrc);
	}
}

PLBYTE *PLPPMDecoder::readASCIILine(PLDataSource *pDataSrc)
{
	int i = 0;
	bool HaveLine = false;
	PLBYTE byte;
	PLBYTE* pLine = new PLBYTE[PPM_MAXLINESIZE]; // Line should not be larger than 70 bytes
	
	do
	{
		if (i==80)
			raiseError (PL_ERRFORMAT_UNKNOWN,
			            "PPM decoder: File Line to long.");
		
		byte = ReadByte(pDataSrc);
		pLine[i] = byte;
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


int PLPPMDecoder::readASCIIDecimal(PLDataSource * pDataSrc)
{
	int Value    = 0;
	int digit;
	
	while ((m_LastByte>=0x30)&&(m_LastByte<=0x39)) // Is ASCII digit
	{
		digit = m_LastByte - 0x30;
		Value = Value*10+digit;
		m_LastByte = ReadByte(pDataSrc);
	}
	
	return Value;
}

void PLPPMDecoder::skipComment(PLDataSource * pDataSrc)
{
	while ((m_LastByte!=0x0D)&& // Carriege Return
	       (m_LastByte!=0x0A))  // New Line
	{
		m_LastByte = ReadByte(pDataSrc);
	}
}

void PLPPMDecoder::skipPpmASCIISeparators(PLDataSource * pDataSrc)
{
	while ((m_LastByte==0x20)|| // Space
		(m_LastByte==0x0D)|| // Carriege Return
		(m_LastByte==0x0A))  // New Line
	{
		m_LastByte = ReadByte(pDataSrc);
	}
}

void PLPPMDecoder::readImage
    ( PPMHEADER * pPpmHead,       // Pointer to PPM header structure
      PLBmp * pBmp,
      PLDataSource * pDataSrc
    )
{
	switch (pPpmHead->ImageType)
	{
    case PPM_P6:
    case PPM_P3:
	  	readData (pPpmHead, pBmp, pDataSrc);
		  break;
    default:
		  raiseError (PL_ERRFORMAT_UNKNOWN, "Unknown PPM image type.");
	}
}

void PLPPMDecoder::readData
    ( PPMHEADER * pPpmHead,       // Pointer to PPM header structure
      PLBmp * pBmp,
      PLDataSource * pDataSrc
    )
{
	int Width  = pPpmHead->ImageWidth;
	int Height = pPpmHead->ImageHeight;
	
	PLPixel32 * pDest;
	PLPixel32 ** pLineArray = pBmp->GetLineArray32();
	
	int y;
	
	if (pPpmHead->ImageType == PPM_P3)
	{
		skipPpmASCIISeparators(pDataSrc);
		m_UseLastByte = true;
	}
	
	for (y=0; y < Height; y++)
	{
		pDest = pLineArray[y];
		if (pPpmHead->ImageType==PPM_P6) // P6
			expandByteLine (pDest, pPpmHead->MaxSampleValue, Width, pDataSrc);
		else // P3
			expandASCIILine (pDest, pPpmHead->MaxSampleValue, Width, pDataSrc);
	}
}

void PLPPMDecoder::expandASCIILine
    ( PLPixel32 * pDest,
      int MaxSampleValue,
      int Width,
      PLDataSource * pDataSrc
    )
{
	int x;
	
	for (x=0; x<Width; x++)
	{
		*pDest = readASCIIPixel32 (MaxSampleValue, pDataSrc);
		pDest ++;
	}
}

void PLPPMDecoder::expandByteLine
    ( PLPixel32 * pDest,
      int MaxSampleValue,
      int Width,
      PLDataSource * pDataSrc
    )
{
	int x;
	PLBYTE *pLine;
	PLBYTE r,g,b;
	int bWidth = Width * 3;
	
	pLine = pDataSrc->ReadNBytes(bWidth);
	if (pLine==NULL)
		return;

	for (x=0; x<bWidth; x+=3)
	{
		if (MaxSampleValue != 255)
		{
			r = ((int)pLine[x] * 255) / MaxSampleValue;
			g = ((int)pLine[x+1] * 255) / MaxSampleValue;
			b = ((int)pLine[x+2] * 255) / MaxSampleValue;
			pDest->Set(r, g, b, 255);
		}
		else
			pDest->Set(pLine[x], pLine[x+1], pLine[x+2], 0);
		pDest ++;
	}
}


PLPixel32 PLPPMDecoder::readASCIIPixel32
    ( int MaxSampleValue,
      PLDataSource * pDataSrc
    )
{
	PLPixel32 Dest;
	PLBYTE r, g, b;

	skipPpmASCIISeparators(pDataSrc);
	r = readASCIIDecimal(pDataSrc);

	skipPpmASCIISeparators(pDataSrc);
	g = readASCIIDecimal(pDataSrc);

	skipPpmASCIISeparators(pDataSrc);
	b = readASCIIDecimal(pDataSrc);

	if (MaxSampleValue != 255)
	{
		r = (r * 255) / MaxSampleValue;
		g = (g * 255) / MaxSampleValue;
		b = (b * 255) / MaxSampleValue;
	}

	Dest.Set(r, g, b, 0);

	return Dest;
}


/*
/--------------------------------------------------------------------
|
|      $Log: plppmdec.cpp,v $
|      Revision 1.3  2001/10/21 17:12:40  uzadow
|      Added PSD decoder beta, removed BPPWanted from all decoders, added PLFilterPixel.
|
|      Revision 1.2  2001/10/16 18:00:19  uzadow
|      Linux compatibility
|
|      Revision 1.1  2001/10/16 17:51:32  uzadow
|      Added ppm support (Todd Harris)
|
|
\--------------------------------------------------------------------
*/
