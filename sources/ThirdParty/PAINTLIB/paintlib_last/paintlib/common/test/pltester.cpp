/*
/--------------------------------------------------------------------
|
|      $Id: pltester.cpp,v 1.33 2002/03/06 23:11:15 uzadow Exp $
|
|      Copyright (c) 1996-2002 Ulrich von Zadow
|
\--------------------------------------------------------------------
*/

#include "pltester.h"

#include <iostream>
#include <string>
#include <fstream>

#include "plpaintlibdefs.h"
#include "planybmp.h"
#include "planydec.h"
#include "plbmpenc.h"
#include "plbmpdec.h"
#include "pljpegenc.h"
#include "pljpegdec.h"
#include "pltiffenc.h"
#include "pltiffencex.h"
#include "pltiffdec.h"
#include "plpngenc.h"
#include "plpngdec.h"
#include "plfilesink.h"
#include "plpixel32.h"
#include "plpixel24.h"
#include "plpixel8.h"
#include "plpoint.h"
#include "plrect.h"
#include "plmemsink.h"

#include "Filter/plfilter.h"
#include "Filter/plfiltercontrast.h"
#include "Filter/plfiltercrop.h"
#include "Filter/plfilterintensity.h"
#include "Filter/plfilterlightness.h"
#include "Filter/plfilterquantize.h"
#include "Filter/plfilterresizebilinear.h"
#include "Filter/plfilterresizegaussian.h"
#include "Filter/plfilterflip.h"
#include "Filter/plfiltermirror.h"
#include "Filter/plfilterfillrect.h"
#include "Filter/plfilterfill.h"

#include "config.h"

#include "testfilterresizebilinear.h"
#include "testpsddecoder.h"

#include <typeinfo>

#ifdef _WINDOWS
#include "../../win/test/resource.h"
#endif

//#define PL_TESTIMAGES_AVAILABLE

PLTester::PLTester ()
{
  m_bOk = true;
}

PLTester::~PLTester ()
{
}

bool PLTester::Ok ()
{
  return m_bOk;
}

void PLTester::RunTests ()
{
  setUp();
  try
  {

    PLTRACE ("Testing Bmp classes...\n");
    PLTRACE ("  Testing 32 bpp PLAnyBmp...\n");
    testPLBmp (m_AnyBmp32);

    PLTRACE ("  Testing 8 bpp PLAnyBmp...\n");
    testPLBmp (m_AnyBmp8);

#ifdef _WINDOWS
    PLTRACE ("  Testing 32 bpp PLDIBSection...\n");
    testPLBmp (m_DIBSect32);
    testPLWinBmp (m_DIBSect32);
    testDIBSect (m_DIBSect32);
    setUp();
    PLTRACE ("  Testing 8 bpp PLDIBSection...\n");
    testPLBmp (m_DIBSect8);
    testPLWinBmp (m_DIBSect8);
    testDIBSect (m_DIBSect32);
    setUp();
    PLTRACE ("  Testing load from resource...\n");
    testLoadRes ();
#endif

    PLTRACE ("  Testing pixel classes...\n");
    testPixels ();

    PLTRACE ("  Testing PLPoint...\n");
    testPoint ();
    PLTRACE ("  Testing PLRect...\n");
    testRect ();

#ifdef PL_SUPPORT_BMP
    PLTRACE ("Testing Bmp Codec...\n");
    testCodec (PLBmpEncoder(), PLBmpDecoder());
#else
    PLTRACE ("Skipping Bmp Codec check - support not compiled into library.\n");
#endif
#ifdef PL_SUPPORT_TIFF
    PLTRACE ("Testing TIFF Codec...\n");
    testCodec (PLTIFFEncoder(), PLTIFFDecoder());
    PLTRACE ("Testing TIFF Codec with compression...\n");
    PLTRACE ("  Testing 32 bpp PLAnyBmp....\n");
    testCTIFFEx (m_AnyBmp32);
    PLTRACE ("  Testing 8 bpp PLAnyBmp....\n");
    testCTIFFEx (m_AnyBmp8);
#else
    PLTRACE ("Skipping TIFF Codec check - support not compiled into library.\n");
#endif
#ifdef PL_SUPPORT_PNG
    PLTRACE ("Testing PNG Codec...\n");
    testCodec (PLPNGEncoder(), PLPNGDecoder());
#else
    PLTRACE ("Skipping PNG Codec check - support not compiled into library.\n");
#endif
#ifdef PL_TESTIMAGES_AVAILABLE
    PLTRACE ("Testing PSD decoder...\n");
    PLTestPSDDecoder PSDTester(this);
    PSDTester.RunTests();
#else
    PLTRACE ("Skipping PSD decoder check - test images not available.\n");
#endif

    PLTRACE ("Testing Filters...\n");
    testFilters();

    // TODO:
    // - JPEG Codec test.
    // - Move decoder tests from testdec.
    // - Codec tests using CMemSource and PLMemSink.
    // - DirectDraw bmp tests.

  }
  catch (PLTextException e)
  {
    PLTRACE ("\npaintlibtest: %s\n", (const char*)e);
    exit (1);
  }
  tearDown();
}

void PLTester::Test (bool b)
{
  if (!b)
  {
    PLTRACE ("           ---->> failed\n");
    m_bOk = false;
  }
// Comment in to stop when an assertion fails
// PLASSERT (b);
}

void PLTester::testPLBmp (PLBmp& Bmp)
{
  {
    PLTRACE ("    Testing copy constructors...\n");
#ifdef _WINDOWS
    PLWinBmp WinBmp (Bmp);
    Test (Bmp == WinBmp);

    PLDIBSection DIBSect (Bmp);
    Test (Bmp == DIBSect);

#endif
    PLAnyBmp AnyBmp (Bmp);
    Test (Bmp == AnyBmp);
  }

  // Assignment operators
  {
    PLTRACE ("    Testing assignment operators...\n");
#ifdef _WINDOWS
    PLWinBmp WinBmp;
    PLDIBSection DIBSect;
    WinBmp = Bmp;
    Test (Bmp == WinBmp);
    DIBSect = Bmp;
    Test (Bmp == DIBSect);
#endif
    PLAnyBmp AnyBmp;
    AnyBmp = Bmp;
    Test (Bmp == AnyBmp);

    PLTRACE ("      Testing for duplicated members...\n");
    PLAnyBmp * pBmp2 = new PLAnyBmp(Bmp);
    PLAnyBmp * pBmp3 = new PLAnyBmp();
    *pBmp3 = *pBmp2;
    delete pBmp3;
    delete pBmp2;
  }

  // Misc. tests
  {
    if (Bmp.GetBitsPerPixel() == 8)
    {
      PLTRACE ("    Testing FindNearestColor()...\n");
      PLPixel32 Pix = Bmp.GetPalette()[0];
      PLBYTE index = Bmp.FindNearestColor (Pix);
      Test (index == 0);
    }
  }

  // CreateCopy tests
  {
    if (Bmp.GetBitsPerPixel() == 32)
    {
      PLTRACE ("    Testing CreateCopy()...\n");
      PLAnyBmp AnyBmp24;
      PLAnyBmp AnyBmp32;
      AnyBmp24.CreateCopy (Bmp, 24);
      AnyBmp32.CreateCopy (AnyBmp24, 32);
      Test (AnyBmp32 == Bmp);
    }
  }
}

#ifdef _WINDOWS
void PLTester::testPLWinBmp (PLWinBmp& Bmp)
{
  // Test clipboard
  PLTRACE ("    Testing clipboard support....\n");
  Bmp.ToClipboard();

  PLWinBmp DestBmp;
  DestBmp.FromClipboard();
  PLTRACE ("        expected to fail...\n");
//  Test (Bmp == DestBmp);
}

void PLTester::testLoadRes ()
{
  // Load from resource
  PLWinBmp ResBmp;
  ResBmp.CreateRes (NULL, IDB_TEST);
  // We can't make sure the data is loaded correctly because CreateRes
  // outputs a 24 bpp bitmap :-(.
}

void PLTester::testDIBSect (PLDIBSection& Bmp)
{
  // Get the handle and create a PLWinBmp from it again.
  PLTRACE ("    Testing GetHandle()...\n");
  HBITMAP hBmp = Bmp.GetHandle ();
  PLWinBmp TestBmp;
  TestBmp.CreateFromHBitmap (hBmp);
  TestBmp.SetResolution(PLPoint(72,72));  // Resolution isn't preserved.
  Test (TestBmp == Bmp);

  // Test if Detach() works.
  PLTRACE ("    Testing Detach()...\n");
  hBmp = Bmp.GetHandle();
  BITMAPINFOHEADER * pBMI = Bmp.GetBMI();
  Bmp.Detach();
  DeleteObject (hBmp);
  free (pBMI);
  PLASSERT_VALID (&Bmp);
}
#endif

void PLTester::testPixels ()
{
  // 32 bpp
  PLPixel32 px1(0,1,2,3);
  PLPixel32 px2;
  px2.Set (0,1,2,3);

  Test (px1 == px2);

  Test (px1.GetR() == 0);
  Test (px1.GetG() == 1);
  Test (px1.GetB() == 2);
  Test (px1.GetA() == 3);

  px2.SetR (4);
  px2.SetG (5);
  px2.SetB (6);
  px2.SetA (7);
  Test (px1 != px2);

  px1 = px2;
  Test (px1 == px2);

  Test (px1.BoxDist (px2) == 0);

  PLPixel32 px3;
  px3 = PLPixel32::Blend(256, PLPixel32(255,255,255,0), PLPixel32(0,0,0,0));
  Test (px3 == PLPixel32 (255,255,255,0));
  px3 = PLPixel32::Blend(0, PLPixel32(255,255,255,0), PLPixel32(0,0,0,0));
  Test (px3 == PLPixel32 (0,0,0,0));
  px3 = PLPixel32::Blend(128, PLPixel32(255,0,0,0), PLPixel32(0,255,0,0));
  Test (px3 == PLPixel32 (127,127,0,0));

  // 24 bpp
  Test (sizeof (PLPixel24) == 3);
  PLPixel24 pxs[4];
  Test (sizeof (pxs) == 12);

  PLPixel24 px241 (0,1,2);
  PLPixel24 px242;
  px242.Set (0,1,2);
  Test (px241 == px242);
  Test (px241.GetR() == 0);
  Test (px241.GetG() == 1);
  Test (px241.GetB() == 2);

  px242.SetR (4);
  px242.SetG (5);
  px242.SetB (6);
  Test (px241 != px242);

  px241 = px242;
  Test (px241 == px242);

  Test (px241.BoxDist (px242) == 0);

  px1.Set (8,9,10,11);
  px241 = px1;
  Test (px241 == PLPixel24 (8,9,10));

  // 8 bpp
  PLPixel8 px81 (128);
  PLASSERT (px81 == PLPixel8(128));
  PLASSERT (px81.Get() == 128);

  PLPixel8 px82 (129);
  PLASSERT (px81 != px82);

  PLASSERT (px81.BoxDist(px82) == 1);
  px82.Set (128);
  PLASSERT (px81 == px82);
}

void PLTester::testPoint ()
{
  PLPoint pt1 (1,1);
  PLPoint pt2;
  pt2.x = 1;
  pt2.y = 1;
  PLASSERT (pt1 == pt2);
  pt2.x = 2;
  PLASSERT (pt1 != pt2);

  pt1 += PLPoint (1,0);
  PLASSERT (pt1 == pt2);

  pt1 -= PLPoint (1,0);
  PLASSERT (pt1 == PLPoint (1,1));

  pt2 = -pt1;
  PLASSERT (pt2 == PLPoint (-1, -1));

  PLASSERT (pt1+pt2 == PLPoint (0,0));
  PLASSERT (pt1-pt2 == PLPoint (2,2));

  PLASSERT (PLPoint (2,2)/2 == PLPoint (1,1));
}

void PLTester::testRect ()
{
  PLRect Rect (1,1,5,6);
  PLASSERT (Rect == PLRect (1,1,5,6));

  PLASSERT (Rect.Width() == 4);
  PLASSERT (Rect.Height() == 5);

  PLASSERT (Rect == PLRect (PLPoint (1,1), PLPoint (5,6)));

}

void PLTester::testCodec (const PLPicEncoder& Encoder, const PLPicDecoder& Decoder)
{
  PLTRACE ("  Testing 32 bpp PLAnyBmp....\n");
  testCodecBmp (m_AnyBmp32, Encoder, Decoder, "test");
  if (typeid(Encoder) == typeid (PLPNGEncoder))
  {
    PLTRACE ("  Testing 24 bpp PLAnyBmp....\n");
    testCodecBmp (m_AnyBmp24, Encoder, Decoder, "test");
  }

  PLTRACE ("  Testing 8 bpp PLAnyBmp....\n");
  testCodecBmp (m_AnyBmp8, Encoder, Decoder, "test");
#ifdef _WINDOWS
  PLTRACE ("  Testing 32 bpp PLDIBSection....\n");
  testCodecBmp (m_DIBSect32, Encoder, Decoder, "test");
  PLTRACE ("  Testing 8 bpp PLDIBSection....\n");
  testCodecBmp (m_DIBSect8, Encoder, Decoder, "test");
#endif
}

void PLTester::testCodecBmp (PLBmp& Bmp, const PLPicEncoder& Encoder,
                              const PLPicDecoder& Decoder, char * pszFName)
{
  // Test writing to file.
  PLAnyBmp NewBmp;
  // paintlib isn't const-correct yet :-(.
  const_cast<PLPicEncoder&>(Encoder).MakeFileFromBmp (pszFName, &Bmp);
  const_cast<PLPicDecoder&>(Decoder).MakeBmpFromFile (pszFName, &NewBmp);
  ::remove (pszFName);  // Delete file again.
  if (Bmp.GetBitsPerPixel() == 24)
  {
    PLAnyBmp TempBmp;
    TempBmp.CreateCopy (Bmp, 32);
    Bmp = TempBmp;
  }
  Test (Bmp == NewBmp);

  // Test writing to memory.
  int Size = Bmp.GetWidth()*Bmp.GetHeight()*4+2000;
  PLMemSink MemSink;
  MemSink.Open (pszFName, Size);
  const_cast<PLPicEncoder&>(Encoder).SaveBmp (&Bmp, &MemSink);
  const_cast<PLPicDecoder&>(Decoder).MakeBmpFromMemory (
      MemSink.GetBytes(), Size, &Bmp);
  MemSink.Close();
  if (Bmp.GetBitsPerPixel() == 24)
  {
    PLAnyBmp TempBmp;
    TempBmp.CreateCopy (Bmp, 32);
    Bmp = TempBmp;
  }
  Test (Bmp == NewBmp);
}

void PLTester::testCTIFFEx (PLBmp& Bmp)
{
  const char szFName[] = "test";
  PLAnyBmp NewBmp;
  PLTIFFEncoderEx Encoder;
  PLFileSink Sink;
  Sink.Open (szFName, Bmp.GetMemUsed() + 4096);
  Encoder.Associate (&Sink );
  // mandatory 'base_line' tags
  Encoder.SetBaseTags( &Bmp );
  // one strip = the whole image (no strip, no tile)
  Encoder.SetField( TIFFTAG_ROWSPERSTRIP, Bmp.GetHeight());
  Encoder.SetField( TIFFTAG_DOCUMENTNAME, szFName);
  Encoder.SetField (TIFFTAG_COMPRESSION, COMPRESSION_PACKBITS);
  Encoder.SaveBmp (&Bmp, &Sink);
  // only really needed if you encode several bitmaps
  Encoder.Dissociate ();
  Sink.Close();

  PLTIFFDecoder Decoder;
  Decoder.MakeBmpFromFile (szFName, &NewBmp);
  ::remove (szFName);  // Delete file again.
  Test (Bmp == NewBmp);
}


void PLTester::testFilters ()
{
  PLTRACE ("  Testing contrast...\n");
  testFilterWithBmp (PLFilterContrast (1, 128), m_AnyBmp32);

  PLTRACE ("  Testing crop...\n");
  PLTRACE ("    32 bpp...\n");
  testFilterWithBmp (PLFilterCrop (0,0,5,5), m_AnyBmp32);
  PLTRACE ("    8 bpp...\n");
  testFilterWithBmp (PLFilterCrop (0,0,5,5), m_AnyBmp8);

  PLTRACE ("  Testing intensity...\n");
  testFilterWithBmp (PLFilterIntensity (20, 128, 1), m_AnyBmp32);

  PLTRACE ("  Testing lightness...\n");
  testFilterWithBmp (PLFilterLightness (0), m_AnyBmp32);

  PLTRACE ("  Testing quantization...\n");
  PLTRACE ("    Testing median cut...\n");
  testQuant (PLDTHPAL_MEDIAN, PLDTH_NONE);
  PLTRACE ("    Testing popularity sort...\n");
  testQuant (PLDTHPAL_POPULARITY, PLDTH_NONE);
  PLTRACE ("    Testing default palette...\n");
  testQuant (PLDTHPAL_DEFAULT, PLDTH_NONE);
  PLTRACE ("    Testing user-defined palette...\n");
  testQuant (PLDTHPAL_USERDEFINED, PLDTH_NONE);
  PLTRACE ("    Testing ordered dithering...\n");
  testQuant (PLDTHPAL_MEDIAN, PLDTH_ORDERED);
  PLTRACE ("    Testing floyd-steinberg dithering...\n");
  testQuant (PLDTHPAL_MEDIAN, PLDTH_FS);

  {
    PLTestFilterResizeBilinear ResizeTester(this);
    ResizeTester.RunTests();
  }

  PLTRACE ("  Testing gauss filter...\n");
  testFilterWithBmp (PLFilterResizeGaussian (5,5,0.2), m_AnyBmp32);

  PLTRACE ("  Testing flip...\n");
  testDoubleFilter (PLFilterFlip());

  PLTRACE ("  Testing mirror...\n");
  testDoubleFilter (PLFilterMirror());

  PLTRACE ("  Testing fillrect...\n");
  testFillRect ();

  PLTRACE ("  Testing fill...\n");
  testFill ();
}

void PLTester::testFilterWithBmp (const PLFilter& Filter, PLBmp& SrcBmp)
{
  PLAnyBmp DestBmp;
  DestBmp.CreateFilteredCopy (SrcBmp, Filter);
  Test (almostEqual (SrcBmp, DestBmp, 4));

  DestBmp = SrcBmp;
  DestBmp.ApplyFilter (Filter);
  Test (almostEqual (SrcBmp, DestBmp, 8));
}

void PLTester::testDoubleFilter (const PLFilter& Filter)
{
  PLAnyBmp DestBmp1;
  PLAnyBmp DestBmp2;
  const_cast<PLFilter&>(Filter).Apply (&m_AnyBmp32, &DestBmp1);
  const_cast<PLFilter&>(Filter).Apply (&DestBmp1, &DestBmp2);
  Test (almostEqual (m_AnyBmp32, DestBmp2, 4));
}


void PLTester::testQuant (int DthPal, int Dth)
{
  PLAnyBmp DestBmp8;
  PLAnyBmp DestBmp32;
  PLFilterQuantize Q (DthPal, Dth);
  if (DthPal == PLDTHPAL_USERDEFINED)
    Q.SetUserPalette(PLFilterQuantize::GetDefaultPalette ());
  Q.Apply(&m_AnyBmp32, &DestBmp8);
  DestBmp32.CreateCopy (DestBmp8, 32);
  Test (almostEqual (m_AnyBmp32, DestBmp32, 4));
}

void PLTester::testFillRect ()
{
  PLAnyBmp Bmp8;
  Bmp8.Create (4, 4, 8, 0);
  Bmp8.ApplyFilter (PLFilterFillRect<PLPixel8> (PLPoint (0, 0), PLPoint (4, 4), PLPixel8(0)));
  Bmp8.ApplyFilter (PLFilterFillRect<PLPixel8> (PLPoint (1, 1), PLPoint (3, 3), PLPixel8(255)));
  PLPixel8 ** ppLines = (PLPixel8**)Bmp8.GetLineArray();
  for (int i=0; i<4; ++i)
  {
    PLASSERT (ppLines[0][i] == 0);
    PLASSERT (ppLines[3][i] == 0);
    PLASSERT (ppLines[i][0] == 0);
    PLASSERT (ppLines[i][3] == 0);
  }
  PLASSERT (ppLines[1][1] == 255);
  PLASSERT (ppLines[1][2] == 255);
  PLASSERT (ppLines[2][1] == 255);
  PLASSERT (ppLines[2][2] == 255);

  PLFilterFillRect<PLPixel32> Filter32(PLPoint (0, 0), PLPoint (15, 15), PLPixel32(0,0,0,0));
}

void PLTester::testFill ()
{
  PLAnyBmp Bmp;
  Bmp.Create (5, 5, 32, true);
  PLPixel32 color(1,2,3,4);
  Bmp.ApplyFilter (PLFilterFill (color));
  PLBYTE ** ppLines = Bmp.GetLineArray();
  for (int y=0; y<5; y++)
    for (int x=0; x<5; x++)
    {
      PLPixel32 * pPix = (PLPixel32*)&(ppLines[y][x*4]);
      PLASSERT (*pPix == color);
    }
}

void PLTester::setUpBmp (PLBmp& Bmp, int BPP)
{
  Bmp.Create(5, 5, BPP, false);
  Bmp.SetResolution (PLPoint (72, 72));
  PLBYTE ** ppLines = Bmp.GetLineArray();
  int y,x;
  for (y=0; y<5; y++)
    for (x=0; x<5; x++)
    {
      switch (BPP)
      {
        case 8:
          if (y<2)
            ppLines[y][x] = 255;
          else if (y<3)
            ppLines[y][x] = 128;
          else
            ppLines[y][x] = 0;
          break;
        case 24:
          {
            PLPixel24 * pPix;
            pPix = (PLPixel24*)&(ppLines[y][x*3]);
            if (y == 0)
              pPix->Set(255,255,255);
            else if (y == 1)
              pPix->Set(255,255,0);
            else if (y == 2 || y == 3)
              pPix->Set(255,0,0);
            else if (y == 4)
              pPix->Set(0,0,0);
          }
          break;
        case 32:
          {
            PLPixel32 * pPix;
            pPix = (PLPixel32*)&(ppLines[y][x*4]);
            if (y == 0)
              pPix->Set(255,255,255,0);
            else if (y == 1)
              pPix->Set(255,255,0,0);
            else if (y == 2 || y == 3)
              pPix->Set(255,0,0,0);
            else if (y == 4)
              pPix->Set(0,0,0,0);
          }
          break;
        default:
          PLASSERT (false);
      }
    }

  if (BPP == 8)
  {
    for (int i=0; i< 256; ++i)
    {
      Bmp.SetPaletteEntry (i, i,i,0,255);
    }
  }

}

void PLTester::setUp ()
{
  setUpBmp (m_AnyBmp32, 32);
  setUpBmp (m_AnyBmp24, 24);
  setUpBmp (m_AnyBmp8, 8);
#ifdef _WINDOWS
  setUpBmp (m_DIBSect32, 32);
  setUpBmp (m_DIBSect8, 8);
//  setUpBmp (m_DDBmp32, 32);
//  setUpBmp (m_DDBmp8, 8);
#endif
}

void PLTester::tearDown ()
{
}

void PLTester::dumpBmp (PLBmp& bmp)
{
  PLTRACE ("  Size: %ix%i\n", bmp.GetWidth(), bmp.GetHeight());
  PLTRACE ("  Pixel data: \n");

  PLBYTE ** ppLines = bmp.GetLineArray();
  int y,x;
  for (y=0; y<bmp.GetHeight(); y++)
  {
    PLTRACE ("    ");
    for (x=0; x<bmp.GetWidth(); x++)
    {
      PLPixel32 pix;
      switch (bmp.GetBitsPerPixel())
      {
        case 8:
          PLTRACE ("%i, ", ppLines[y][x]);
          break;
        case 32:
          pix = *((PLPixel32*)&(ppLines [y][x*4]));
          PLTRACE ("(%i,%i,%i,%i) ", pix.GetR(), pix.GetG(), pix.GetB (), pix.GetA ());
          break;
        default:
          PLASSERT (false);
      }
    }
    PLTRACE ("\n");
  }
  if (bmp.GetBitsPerPixel() <= 8)
  {
    PLTRACE ("    Palette:");
    PLTRACE ("      ");
    PLPixel32 * pPal = bmp.GetPalette();
    int i;
    for (i=0; i<2; i++)
      PLTRACE ("(%i,%i,%i,%i) ", pPal[i].GetR(), pPal[i].GetG(), pPal[i].GetB (), pPal[i].GetA ());
    PLTRACE ("... ");
    for (i=254; i<256; i++)
      PLTRACE ("(%i,%i,%i,%i) ", pPal[i].GetR(), pPal[i].GetG(), pPal[i].GetB (), pPal[i].GetA ());

  }
  PLTRACE ("\n");
}

bool PLTester::almostEqual (PLBmp& bmp1, PLBmp& bmp2, int epsilon)
{
  return bmp1.AlmostEqual (bmp2, epsilon);
}


/*
/--------------------------------------------------------------------
|
|      $Log: pltester.cpp,v $
|      Revision 1.33  2002/03/06 23:11:15  uzadow
|      Fixed major PLAnyDec bug
|
|      Revision 1.32  2002/03/06 22:46:55  uzadow
|      Fixed major PLAnyDec bug
|
|      Revision 1.31  2002/03/03 16:29:56  uzadow
|      Re-added BPPWanted.
|
|      Revision 1.30  2002/03/03 11:59:43  uzadow
|      Updated to work with cygwin.
|
|      Revision 1.29  2002/02/24 13:24:17  uzadow
|      no message
|
|      Revision 1.28  2002/02/24 13:00:49  uzadow
|      Documentation update; removed buggy PLFilterRotate.
|
|      Revision 1.27  2002/01/27 18:20:18  uzadow
|      Updated copyright message; corrected pcx decoder bug.
|
|      Revision 1.26  2001/10/21 17:12:40  uzadow
|      Added PSD decoder beta, removed BPPWanted from all decoders, added PLFilterPixel.
|
|      Revision 1.25  2001/10/16 17:12:27  uzadow
|      Added support for resolution information (Luca Piergentili)
|
|      Revision 1.24  2001/10/06 22:03:26  uzadow
|      Added PL prefix to basic data types.
|
|      Revision 1.23  2001/10/06 20:44:45  uzadow
|      Linux compatibility
|
|      Revision 1.22  2001/10/06 15:32:22  uzadow
|      Removed types LPBYTE, DWORD, UCHAR, VOID and INT from the code.
|
|      Revision 1.21  2001/10/03 14:00:29  uzadow
|      Much improved quality in FilterResizeBilinear.
|
|      Revision 1.20  2001/09/30 19:55:37  uzadow
|      Fixed bug for 8 bpp in PLFilterCrop.
|
|      Revision 1.19  2001/09/28 19:50:56  uzadow
|      Added some 24 bpp stuff & other minor features.
|
|      Revision 1.18  2001/09/24 14:19:19  uzadow
|      Added PLPoint & PLRect tests.
|
|      Revision 1.17  2001/09/16 19:03:23  uzadow
|      Added global name prefix PL, changed most filenames.
|
|      Revision 1.16  2001/09/15 20:39:57  uzadow
|      Added Quantization to user-defined palette (Andreas Köpf)
|
|      Revision 1.15  2001/09/15 14:30:20  uzadow
|      Fixed PLPixel32 initialization bug.
|
|      Revision 1.14  2001/09/13 20:49:31  uzadow
|      Added fill filters.
|
|      Revision 1.13  2001/02/04 14:07:26  uzadow
|      Changed max. filename length.
|
|      Revision 1.12  2001/01/15 15:05:31  uzadow
|      Added PLBmp::ApplyFilter() and PLBmp::CreateFilteredCopy()
|
|      Revision 1.11  2001/01/13 20:06:16  uzadow
|      Added Flip and Mirror filters.
|
|      Revision 1.10  2001/01/13 00:28:03  uzadow
|      no message
|
|      Revision 1.9  2001/01/12 23:06:11  uzadow
|      Additional bmp assignment test.
|
|      Revision 1.8  2000/12/18 22:42:53  uzadow
|      Replaced RGBAPIXEL with PLPixel32.
|
|      Revision 1.7  2000/12/09 12:16:26  uzadow
|      Fixed several memory leaks.
|
|      Revision 1.6  2000/12/05 00:12:18  uzadow
|      *** empty log message ***
|
|      Revision 1.5  2000/12/04 23:59:02  uzadow
|      Added filter tests.
|
|      Revision 1.4  2000/12/03 21:15:43  uzadow
|      Fixed png handling in configure; test/ adapted to linux
|
|      Revision 1.3  2000/12/02 19:42:29  uzadow
|      Added PLTIFFEncoderEx test.
|
|      Revision 1.2  2000/11/21 23:28:53  uzadow
|      Moved PLBmp tests from testdec to test.
|
|      Revision 1.1  2000/11/21 20:29:39  uzadow
|      Added test project.
|
|
\--------------------------------------------------------------------
*/
