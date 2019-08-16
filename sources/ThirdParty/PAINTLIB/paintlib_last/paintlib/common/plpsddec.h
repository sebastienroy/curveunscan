/*
/--------------------------------------------------------------------
|
|      $Id: plpsddec.h,v 1.1 2001/10/21 17:12:40 uzadow Exp $
|
|      Copyright (c) 1996-1998 Ulrich von Zadow
|
\--------------------------------------------------------------------
*/

#ifndef INCL_PLPSDDEC
#define INCL_PLPSDDEC

#ifndef INCL_PLPICDEC
#include "plpicdec.h"
#endif

#include <vector>

class PLDataSource;
class PLPoint;

struct PLPSDHeader
{
  char     Signature[4];
  PLWORD   Version;
  PLBYTE   Reserved[6];
  PLWORD   Channels;
  int      Rows;
  int      Columns;
  PLWORD   BPP;
  PLWORD   Mode;
};

struct PLPSDLayerInfo;

//! Photoshop file decoder. Besides having the MakeBmpFromFile interface
//! that the other decoders have, the photoshop decoder loads the layers
//! of the image into separate bitmaps so they can be manipulated separately:
//! <pre>
//!   vector<PLAnyBmp> Bmp;
//!   PLAnyBmp BaseBmp);
//!   Decoder->OpenFile ("face.psd");
//!   int NumLayers = Decoder->GetNumLayers();
//!   for (int i=0; i<NumLayers; i++)
//!   {
//!     GetNextLayer (Bmp[i]);
//!     LayerOffset = GetLayerOffset();
//!   }
//!   GetImage (&BaseBmp);
//!   Close();
class PLPSDDecoder : public PLPicDecoder
{
public:
  //! Creates a decoder
  PLPSDDecoder
    ();

  //! Destroys a decoder
  virtual ~PLPSDDecoder
    ();

  //! Returns number of layers in the image.
  int GetNumLayers
    ();

  //! Fills the bitmap with the layer data.
  void GetNextLayer
    ( PLBmp& Bmp
    );

  //! Returns the origin of the layer data in the image.
  PLPoint GetLayerOffset
    ();

  //! Fills the bitmap with the main image. This image is a flattened 
  //! version of the layers.
  void GetImage
    ( PLBmp& Bmp
    );

protected:
  //! Main decoder routine. Reads the header, Creates the bitmap,
  //! reads the palette, and reads the image data.
  virtual void DoDecode
    ( PLBmp * pBmp,
      PLDataSource * pDataSrc
    );

private:
  void readHeader
    ( PLDataSource * pDataSrc,
      PLPSDHeader * pPSDHeader
    );

  void readColorModeData 
    ( PLDataSource * pDataSrc
    );

  void createBmp 
    ( PLBmp *pBmp, 
      int Mode,
      int Height,
      int Width,
      int Channels,
      const PLPoint& Resolution
    );

  void readImageResData 
    ( PLDataSource * pDataSrc,
      PLPoint& Resolution
    );

  void readLayerHeader 
    ( PLDataSource * pDataSrc
    );

  void skipLayerData
    ( PLDataSource * pDataSrc
    );

  void skipMaskData
    ( PLDataSource * pDataSrc
    );

  void readLayer 
    ( PLDataSource * pDataSrc, 
      PLBmp& Bmp,
      int Mode
    );

  void readImageData
    ( PLDataSource * pDataSrc,
      PLBmp * pBmp,
      int Mode,
      int Height,
      int Width,
      int Channels 
    );

  void traceCompressionMethod
    ( PLWORD CompressionMethod
    );

  void readRLEImage 
    ( PLDataSource * pDataSrc,
      PLBmp * pBmp,
      int Mode,
      int Height,
      int Width,
      int Channels 
    );

  void readRLEChannel 
    ( PLDataSource * pDataSrc,
      PLBmp * pBmp,
      int Mode,
      int Height,
      int Width,
      int ChannelNum,
      int * pRowLengths 
    );

  void cleanup
    ();

  PLPSDHeader m_PSDHeader;
  PLPoint m_Resolution;
  PLPixel32 m_pPal[256];
  PLBYTE * m_pMiscDataStart;
  int m_MiscDataSize;
  int m_NumLayers;
  int m_LayersRead;
  std::vector<PLPSDLayerInfo *> m_pLayerInfo;
};

#endif

/*
/--------------------------------------------------------------------
|
|      $Log: plpsddec.h,v $
|      Revision 1.1  2001/10/21 17:12:40  uzadow
|      Added PSD decoder beta, removed BPPWanted from all decoders, added PLFilterPixel.
|
|
\--------------------------------------------------------------------
*/
