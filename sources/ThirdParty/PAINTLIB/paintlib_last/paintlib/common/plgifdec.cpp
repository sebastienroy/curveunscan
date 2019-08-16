/*
/--------------------------------------------------------------------
|
|      $Id: plgifdec.cpp,v 1.3 2001/10/21 17:12:39 uzadow Exp $
|
|      TODO: Error handling.
|
|      Copyright (c) 1996-1998 Ulrich von Zadow
|      Initial version by Michael Salzlechner
|
\-------------------------------------------------------------------
*/

#include "plstdpch.h"

#include "plgifdec.h"
#include "planybmp.h"

extern "C" 
{
#define DOEXTERNGIF

// Workaround for namespace clash. This has been fixed in newer versions
// of libungif.
#ifdef _WINDOWS
#undef DrawText
#endif
#include "gif_lib.h"
}

#include <stdio.h>

static int
    InterlacedOffset[] = { 0, 4, 2, 1 }, /* The way Interlaced image should. */
    InterlacedJumps[] = { 8, 8, 4, 2 };    /* be read - offsets and jumps... */

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

PLGIFDecoder::PLGIFDecoder()
  : PLPicDecoder()
{
//	SetFileExtensions("*.gif");
//	SetFileDescription("GIF File");
}

PLGIFDecoder::~PLGIFDecoder()
{

}

int GIF_Read_Data(GifFileType* pGifFile,GifByteType* pByteType,int length)
{
  PLBYTE *ptr;
  PLDataSource* pSourceInfo=(PLDataSource*)pGifFile->UserData;

  ptr = pSourceInfo->ReadNBytes(length);
  memcpy(pByteType,ptr,length);

  return length;
}

void PLGIFDecoder::DoDecode(PLBmp *pBmp, PLDataSource *pDataSrc)
{
  GifFileType *GifFile;
  GifRecordType RecordType;
  GifByteType *Extension;
  ColorMapObject *ColorMap = NULL;

	int CurLine = 0;
	int i, Row, Col, Width, Height, Count, j, ExtCode;

	GifFile = DGifOpen( (void*)pDataSrc, GIF_Read_Data);

	pBmp->Create (GifFile->SWidth, GifFile->SHeight , 8, false);

	PLBYTE ** pLineArray = pBmp->GetLineArray();

	CurLine = 0;
	while (CurLine < GifFile->SHeight)
	{
		pLineArray[CurLine][0] = GifFile->SBackGroundColor;
	    CurLine++;
	}

    /* Scan the content of the GIF file and load the image(s) in: */
  do
  {
    if (DGifGetRecordType(GifFile, &RecordType) == GIF_ERROR)
    {
	    PrintGifError();
      PLASSERT (false);
	  }

    switch (RecordType)
    {
	    case IMAGE_DESC_RECORD_TYPE:
		    if (DGifGetImageDesc(GifFile) == GIF_ERROR)
        {
		      PrintGifError();
          PLASSERT (false);
        }
        Row = GifFile->Image.Top; /* Image Position relative to Screen. */
        Col = GifFile->Image.Left;
        Width = GifFile->Image.Width;
        Height = GifFile->Image.Height;
        if (GifFile->Image.Left + GifFile->Image.Width > GifFile->SWidth ||
	          GifFile->Image.Top + GifFile->Image.Height > GifFile->SHeight)
        {
          fprintf(stderr, "Image %d is not confined to screen dimension, aborted.\n");
          PLASSERT (false);
        }
        if (GifFile->Image.Interlace)
        {
		      /* Need to perform 4 passes on the images: */
		      for (Count = i = 0; i < 4; i++)
	          for (j = Row + InterlacedOffset[i]; j < Row + Height;
				         j += InterlacedJumps[i])
            {
			        GifQprintf("\b\b\b\b%-4d", Count++);
			        if (DGifGetLine(GifFile, &pLineArray[j][Col], Width) == GIF_ERROR)
              {
		            PrintGifError();
                PLASSERT (false);
			        }
            }
        }
        else
        {
		      for (i = 0; i < Height; i++)
          {
			      GifQprintf("\b\b\b\b%-4d", i);
			      if (DGifGetLine(GifFile, &pLineArray[Row++][Col], Width) == GIF_ERROR)
            {
			        PrintGifError();
              PLASSERT (false);
      			}
		      }
		    }
		    break;
	    case EXTENSION_RECORD_TYPE:
		    /* Skip any extension blocks in file: */
		    if (DGifGetExtension(GifFile, &ExtCode, &Extension) == GIF_ERROR)
        {
		      PrintGifError();
          PLASSERT (false);
		    }
		    while (Extension != NULL)
        {
		      if (DGifGetExtensionNext(GifFile, &Extension) == GIF_ERROR)
          {
			      PrintGifError();
            PLASSERT (false);
 		      }
		    }
		    break;
	    case TERMINATE_RECORD_TYPE:
		    break;
	    default:		    /* Should be trapped by DGifGetRecordType. */
		    break;
	  }
  } while (RecordType != TERMINATE_RECORD_TYPE);

  ColorMap = (GifFile->Image.ColorMap ? GifFile->Image.ColorMap :
	            GifFile->SColorMap);

	PLBYTE* pb = (PLBYTE*)ColorMap->Colors;
	for (i = 0; i < ColorMap->ColorCount; i++)
	{
		pBmp->SetPaletteEntry(i, pb[0], pb[1], pb[2], 255);
		pb += 3;
	}

	DGifCloseFile(GifFile);
}

/*
/--------------------------------------------------------------------
|
|      $Log: plgifdec.cpp,v $
|      Revision 1.3  2001/10/21 17:12:39  uzadow
|      Added PSD decoder beta, removed BPPWanted from all decoders, added PLFilterPixel.
|
|      Revision 1.2  2001/10/06 22:37:08  uzadow
|      Linux compatibility.
|
|      Revision 1.1  2001/09/16 19:03:22  uzadow
|      Added global name prefix PL, changed most filenames.
|
|      Revision 1.6  2001/09/15 21:02:44  uzadow
|      Cleaned up stdpch.h and config.h to make them internal headers.
|
|      Revision 1.5  2001/02/04 14:31:52  uzadow
|      Member initialization list cleanup (Erik Hoffmann).
|
|      Revision 1.4  2001/01/15 12:09:34  uzadow
|      Fixed crash decoding some gif files.
|
|      Revision 1.3  2000/12/18 22:42:52  uzadow
|      Replaced RGBAPIXEL with PLPixel32.
|
|      Revision 1.2  2000/12/17 20:45:57  uzadow
|      Fixed build problem with libungif.
|
|      Revision 1.1  2000/12/08 13:41:23  uzadow
|      Added gif support by Michael Salzlechner.
|
|
\--------------------------------------------------------------------
*/
