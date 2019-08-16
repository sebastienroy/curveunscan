/*
/--------------------------------------------------------------------
|
|      $Id: testpsddecoder.cpp,v 1.3 2002/01/27 18:20:18 uzadow Exp $
|
|      Copyright (c) 1996-2002 Ulrich von Zadow
|
\--------------------------------------------------------------------
*/

#include "testpsddecoder.h"
#include "pltester.h"

#include "plpsddec.h"
#include "planybmp.h"
#include "plpngenc.h"
#include <string>

using namespace std;

#ifdef WIN32
const std::string sTestFileDir ("..\\..\\..\\..\\testpic\\");
#else
const std::string sTestFileDir ("../../../testpic/");
#endif

PLTestPSDDecoder::PLTestPSDDecoder (PLTester * pTester)
    : m_pTester (pTester)
{
  
}

PLTestPSDDecoder::~PLTestPSDDecoder ()
{
}

void PLTestPSDDecoder::RunTests ()
{
  test (string ("rgb8.psd"));
  test (string ("rgb8alpha.psd"));
  test (string ("rgb24.psd"));
  test (string ("rgb24alpha.psd"));
  test (string ("rgb24alpha2.psd"));
  test (string ("rgb24layers.psd"));
}

void PLTestPSDDecoder::test (const string& sFName)
{
  PLPSDDecoder Decoder;
  PLAnyBmp Bmp;
  string sFilePos = sTestFileDir+sFName;
  Decoder.MakeBmpFromFile (sFilePos.c_str(), &Bmp);

  {
    PLPSDDecoder Decoder;
//    PLPNGEncoder Encoder;
    Decoder.OpenFile (sFilePos.c_str());
    int n = Decoder.GetNumLayers ();
    for (int i = 0; i<n; i++)
    {
      PLAnyBmp LayerBmp;
      Decoder.GetNextLayer (LayerBmp);
      PLPoint Pt = Decoder.GetLayerOffset ();
/*
      char sz[256];
      sprintf (sz, "c:\\test%i.png", i);
      Encoder.MakeFileFromBmp (sz, &LayerBmp);
*/
    }
    PLAnyBmp FlatBmp;
    Decoder.GetImage (FlatBmp);
    PLASSERT (FlatBmp == Bmp);
    Decoder.Close ();
  }
}

/*
/--------------------------------------------------------------------
|
|      $Log: testpsddecoder.cpp,v $
|      Revision 1.3  2002/01/27 18:20:18  uzadow
|      Updated copyright message; corrected pcx decoder bug.
|
|      Revision 1.2  2001/10/21 17:54:40  uzadow
|      Linux compatibility
|
|      Revision 1.1  2001/10/21 17:12:40  uzadow
|      Added PSD decoder beta, removed BPPWanted from all decoders, added PLFilterPixel.
|
|
\--------------------------------------------------------------------
*/

