// BmpManager.cpp: implementation of the CBmpManager class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CurveUnscan.h"
#include "BmpManager.h"

#include "MonochromaticBmpReader.h"
#include "Color256BmpReader.h"
#include "RealColorBmpReader.h"
#include "24BitsBmpReader.h"

// PaintLib includes
#include "plpixel32.h"
#include "WinBmpEx.h"
#include "planydec.h"
//#include "plmemsink.h"
//#include "plmemsrc.h"
#include "plbmpenc.h"
#include "plfilesink.h"

#include <Utilities/Tools.h>

#include "math.h"
#include "io.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

IMPLEMENT_SERIAL(CBmpManager,CObject,1)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

// protected constructor, used for serialization
CBmpManager::CBmpManager()
:	m_pDoc(NULL), 
	m_pBmp(NULL), 
	m_pReader(NULL)
{

}


CBmpManager::CBmpManager(CUnscanDoc *pDoc)
:m_pDoc(pDoc), m_pBmp(NULL), m_pReader(NULL)
	{

	}

CBmpManager::~CBmpManager()
	{
	delete m_pBmp;
	delete m_pReader;
	DeleteTempFile();
	}

//////////////////////////////////////////////////////////////////////
// Methods
//////////////////////////////////////////////////////////////////////

bool CBmpManager::OpenBitmap(CString strName)
{
	bool opened=false;
	delete m_pBmp;
	m_pBmp=NULL;
	DeleteTempFile();

	m_pBmp=new CWinBmpEx;

	PLAnyPicDecoder decoder;
	
	try
	{
		decoder.MakeBmpFromFile(strName,m_pBmp,0);
	}
	catch(...)
	{
		delete m_pBmp;
		m_pBmp=NULL;
		CString msg;
		msg.LoadString(IDS_FAIL_TO_OPEN_FILE);
		AfxMessageBox(msg,MB_OK|MB_ICONSTOP);
		return false;
	}

	if(Reset())
	{
		m_BitmapName=strName;
		MakeTempFileFromOriginalPicture(strName);
//		m_pDoc->SetModifiedFlag(TRUE);
		return true;
	}
	else
	{
		return false;
	}
}

// Initialise le BmpReader et les attributs dérivés à partir du bmp
// Return false if the bmp cannot be handled
bool CBmpManager::Reset()
{
	delete m_pReader;
	m_pReader=NULL;

	int depth=m_pBmp->GetBitsPerPixel();
	switch(depth)
		{
		case 1:
			m_pReader=new CMonochromaticBmpReader(m_pBmp);
			break;
		case 8:
			m_pReader=new CColor256BmpReader(m_pBmp);
			break;
		case 24:
			m_pReader=new C24BitsBmpReader(m_pBmp);
			break;
		case 32:
			m_pReader=new CRealColorBmpReader(m_pBmp);
			break;
		default:
			int nColors=1<<depth;
			CString strFormat;
			strFormat.LoadString(IDS_CANNOT_HANDLE_X_COLORS);
			CString msg;
			msg.Format(strFormat,nColors);
			AfxMessageBox(msg,MB_OK|MB_ICONSTOP);
			delete m_pBmp;
			m_pBmp=NULL;
			return false;
		}
	m_nWidth=m_pBmp->GetWidth();
	m_nHeight=m_pBmp->GetHeight();
	return true;
}


// Renvoie le point le plus proche à l'intérieur du bitmap.
// Renvoie CPoint(0,0) si pas de bmp ouvert.
CPoint CBmpManager::IntoBitmap(CPoint point)
	{
	if(NULL==m_pBmp)
		{
		return CPoint(0,0);
		}

	int width=m_pBmp->GetWidth();
	point.x=(point.x<0)?0:point.x;
	point.x=(point.x>=width)?width-1:point.x;

	int height=m_pBmp->GetHeight();
	point.y=(point.y<0)?0:point.y;
	point.y=(point.y>=height)?height-1:point.y;

	return point;
	}


// Cherche le point suivant de la courbe
// modifie le point passé en paramètre et renvoie TRUE si trouvé
// renvoie FALSE si fin de la courbe
BOOL CBmpManager::FindNext(CPoint &rPoint,const PLPixel32& blackLevel, BOOL toLeft, BOOL top) const
	{
	int side=(top)?-1:+1;
	int direction=(toLeft)?-1:+1;
	CPoint point=rPoint;
	point.x+=direction;
	if( (point.x<0)||(point.x>m_nWidth) )
		{
		return FALSE;
		}
	if(PixelIsBlack(point,blackLevel)) // Si le pixel a coté est noir
		{
		while( (PixelIsBlack(point,blackLevel))&&(point.y>0)&&(point.y<m_nHeight) )
			{
			point.y+=side;
			}
		point.y-=side;
		rPoint=point;
		return TRUE;
		}
	else					// S'il est blanc
		{
		BOOL found=FindBlackPixel(0,point,blackLevel,direction,side);
		if(found)
			{
			rPoint=point;
			}
		return found;
		}
	}

// algorithme récursif
// Trouve le point noir le plus proche dans la direction et du coté spécifié.
// On s'autorise deux retours en arrière (courbe "poreuse").
// renvoie TRUE si un point a été trouvé ; le point passé en paramètre est modifié.
// renvoie FALSE si fin de la courbe.
BOOL CBmpManager::FindBlackPixel(int nRecur, CPoint &rPoint,const PLPixel32& blackLevel, int direction, int side) const
	{
	if(nRecur>4)
		{
		return FALSE;
		}
	CPoint point=rPoint;
	CPoint sidePoint;
	BOOL found;
	while(!PixelIsBlack(point,blackLevel))
		{
		sidePoint=point;
		sidePoint.x-=direction;
		if( (sidePoint.x<0)||(sidePoint.x>m_nWidth) )// vérification dans bmp
			{
			return FALSE;
			}
		if(!PixelIsBlack(sidePoint,blackLevel)) 
			{
			found=FindBlackPixel(nRecur+1,sidePoint,blackLevel,direction,side);
			if(!found)
				{
				return FALSE;
				}
			else
				{
				point=sidePoint;
				point.x+=direction;
				}
			}
		else
			{
			point.y-=side;
			if( (point.y<0)||(point.y>m_nHeight) )
				{
				return FALSE;
				}
			}
		}
	rPoint=point;
	return TRUE;
	}

BOOL CBmpManager::Draw(CDC *pDC)
	{
	if(NULL==m_pBmp)
		{
		return FALSE;
		}
	m_pBmp->Draw(pDC->m_hDC,0,0);
	return TRUE;

	}

// renvoie TRUE si une courbe se trouve sous le point passé en paramètre
// modifie le point pour le situer sur le bord de la courbe
BOOL CBmpManager::FindCurve(CPoint &point,const PLPixel32& blackLevel, BOOL top) const
{
	BOOL result=FALSE;
	if(PixelIsBlack(point,blackLevel))
		{
		result=TRUE;
		int increment=(top)?-1:1;
		while(PixelIsBlack(CPoint(point.x,increment+point.y),blackLevel) )
			{
			point.y+=increment;
			}
		if( (point.y<0)||(point.y>=m_nHeight) )
			{
			point.y-=increment;
			return TRUE;
			}
		}
	return result;
}

bool CBmpManager::IsBmpOpened() const
{
	return (NULL!=m_pBmp);
}

CSize CBmpManager::GetBmpSize()
{
	CSize size(0,0);
	if(NULL!=m_pBmp)
		{
		size.cx=m_pBmp->GetWidth();
		size.cy=m_pBmp->GetHeight();
		}
	return size;

}

PLPixel32 CBmpManager::GetPointColor(CPoint point)
{
	if(NULL==m_pBmp)
		{
		return PLPixel32(255,255,255,0);
		}
	if( (point.x<0)||(point.x>=m_nWidth)||(point.y<0)||(point.y>=m_nHeight) )
		{
		return PLPixel32(255,255,255,0);
		}
	return m_pReader->GetPixel(point);
}

void CBmpManager::Draw(CDC *pDC,const CRect& rect)
{
	if(NULL==m_pBmp)
		{
		return;
		}
	
//	int width=m_pBmp->GetWidth();
//	int height=m_pBmp->GetHeight();
//	m_pBmp->DrawExtract(pDC->m_hDC,(POINT)(rect.TopLeft()),(RECT)rect);	
	m_pBmp->DrawRect(pDC->m_hDC,rect);
	
//	m_pBmp->Draw(pDC->m_hDC,0,0);

//	m_pBmp->DrawExtract(pDC->m_hDC,(POINT)(CPoint(100,100)),(RECT)(CRect(100,100,200,200)));	


}

CPoint CBmpManager::FindNextDash(const CPoint &inPoint, const PLPixel32 &blackLevel, BOOL toLeft, int nMaxDist) const
{
	bool found=false;
	int direction=(toLeft)?-1:+1;
	CPoint ptResult=inPoint;
	static double pi=acos(-1.0);

	CPoint ptTop=inPoint;
	ptTop.x-=direction;
	FindNext(ptTop,blackLevel,toLeft,true);	// FindNext is used instead of FindCurve in order to allow recurse porosity

	CPoint ptBottom=inPoint;
	ptBottom.x-=direction;
	FindNext(ptBottom,blackLevel,toLeft,false); // FindNext is used instead of FindCurve in order to allow recurse porosity


	for(int rayon=1;(!found)&&(rayon<nMaxDist);rayon++)
	{
		// determination du pas angulaire
		double dAlpha=atan(1.0/(double)rayon);
		int N=(int)(pi/dAlpha);	// nombre de pas pour faire un demi cercle
		dAlpha=pi/N;	// pour tomber sur un multiple

		int dx;
		int dy;
		double alpha;
		double fRayon=(double)rayon;


		// check du premier quart de cercle

		int X=ptTop.x+direction;
		int Y=ptTop.y;
		for(int nCounter=0;(!found)&&(nCounter<=(N/2));nCounter++)
		{
			
			alpha=dAlpha*(double)nCounter;
			dx=direction*(CTools::Round(fRayon*sin(alpha)) );
			dy=CTools::Round((-1)*fRayon*cos(alpha));	// -1 : on commence en haut

			CPoint ptCurrent(X+dx,Y+dy);
			if( (IsIntoBitmap(ptCurrent)) && (PixelIsBlack(ptCurrent,blackLevel)) )
			{
				found=true;
				ptResult=ptCurrent;
			}
		}

		// check du chemin entre top et bottom

		for(int nCounter2=ptTop.y;(!found)&&(nCounter2<=ptBottom.y);nCounter2++)
		{
			dx=direction*rayon;
			CPoint ptCurrent(X+dx,nCounter2);
			if( (IsIntoBitmap(ptCurrent)) && (PixelIsBlack(ptCurrent,blackLevel)) )
			{
				found=true;
				ptResult=ptCurrent;
			}
		}

		// check du premier quart de cercle

		X=ptBottom.x+direction;
		Y=ptBottom.y;
		for(int nCounter3=0;(!found)&&(nCounter3<=(N/2));nCounter3++)
		{
			
			alpha=dAlpha*(double)nCounter3;
			dx=direction*(CTools::Round(fRayon*cos(alpha)) );	
			dy=CTools::Round(fRayon*sin(alpha)) ;

			CPoint ptCurrent(X+dx,Y+dy);
			if( (IsIntoBitmap(ptCurrent)) && (PixelIsBlack(ptCurrent,blackLevel)) )
			{
				found=true;
				ptResult=ptCurrent;
			}
		}

	}
	return ptResult;
}

bool CBmpManager::IsIntoBitmap(const CPoint &point) const
{
	return (	(NULL!=m_pBmp)
				&& (point.x>=0)
				&& (point.y>=0)
				&& (point.x<m_pBmp->GetWidth())
				&& (point.y<m_pBmp->GetHeight())
			);
}

void CBmpManager::Serialize(CArchive &ar)
{
	CObject::Serialize(ar);

	if( ar.IsStoring() )
	{
		ar << m_BitmapName;

		if(m_strTempFileName.IsEmpty())
		{
			MakeTempFileFromMemory();
		}
		WriteTempFileToArchive(ar);


	}
	else
	{
		ar >> m_BitmapName;

		delete m_pBmp;
		m_pBmp=NULL;
		delete m_pReader;
		m_pReader=NULL;
		DeleteTempFile();

		bool bIsOk=ReadArchiveToTempFile(ar);
		if(bIsOk)
		{
			m_pBmp=new CWinBmpEx;
			PLAnyPicDecoder decoder;
	
			try
			{
				decoder.MakeBmpFromFile(m_strTempFileName,m_pBmp,0);
			}
			catch(...)
			{
				CArchiveException *pErr=new CArchiveException(CArchiveException::generic);
				THROW(pErr);
			}
			if(!Reset())
			{
				CArchiveException *pErr=new CArchiveException(CArchiveException::generic);
				THROW(pErr);
			}
		}
		else
		{
			CArchiveException *pErr=new CArchiveException(CArchiveException::generic);
			THROW(pErr);
		}

/*		long nBmpSize;
		ar >> nBmpSize;
		if(0!=nBmpSize)
		{
			m_pBmp=new CWinBmpEx;
			BYTE* pMemBuffer=new BYTE[nBmpSize];
			for(int counter=0;counter<nBmpSize;counter++)
			{
				ar >> *(pMemBuffer+counter);
			}

			PLAnyPicDecoder decoder;
			try
			{
				decoder.MakeBmpFromMemory(pMemBuffer,nBmpSize,m_pBmp,0);
				if(!Reset())
				{
					delete m_pBmp;
					m_pBmp=NULL;
				}
			}
			catch(...)
			{
				// pb
			}
			delete []pMemBuffer;
		}
*/
	}
}

void CBmpManager::DeleteTempFile()
{
	if(!m_strTempFileName.IsEmpty())
	{
		remove(m_strTempFileName);
		m_strTempFileName="";
	}
}



CString CBmpManager::MakeTempFilename()
{
	CString strTempPath=getenv("TEMP");

	// The following commented code cannot run under Windows 95 and Windows NT
//	char strLongName[256];
//	GetLongPathName(strTempPath,strLongName,256);
//	strTempPath=strLongName;

	if(strTempPath.IsEmpty())
	{
		return CString("");
	}
	if(strTempPath[strTempPath.GetLength()-1]!='\\')
	{
		strTempPath+='\\';
	}

	char strTemplate[]="crvnscnXXXXXX";
	CString strTempName=_mktemp(strTemplate);
	if(strTempName.IsEmpty())
	{
		return CString("");
	}
	CString strFullName=strTempPath+strTempName;

	return strFullName;
}

bool CBmpManager::WriteTempFileToArchive(CArchive &ar)
{
	ASSERT(!m_strTempFileName.IsEmpty());

	CFile tempFile(m_strTempFileName,CFile::modeRead);

	DWORD nByteRemaining=tempFile.GetLength();
	ar << nByteRemaining;

	const UINT nBufferSize=0x10000;	// 64 Ko
	BYTE* pBuffer=new BYTE[nBufferSize];
	while(nByteRemaining)
	{
		UINT nByteRead=tempFile.Read(pBuffer,nBufferSize);
		ar.Write(pBuffer,nByteRead);
		nByteRemaining-=nByteRead;
	}
	delete []pBuffer;

	tempFile.Close();

	return true;
}

bool CBmpManager::ReadArchiveToTempFile(CArchive &ar)
{
	m_strTempFileName=MakeTempFilename();
	CFile tempFile(m_strTempFileName,CFile::modeCreate|CFile::modeWrite);
	CString strPath=tempFile.GetFilePath();

	DWORD nByteRemaining;
	ar >> nByteRemaining;

	if(0==nByteRemaining)
	{
		CArchiveException *pErr=new CArchiveException(CArchiveException::generic);
		THROW(pErr);
		return false;
	}

	const UINT nBufferSize=0x10000;	// 64 Ko
	BYTE* pBuffer=new BYTE[nBufferSize];
	while(nByteRemaining)
	{
		UINT nByteRead=(nByteRemaining>nBufferSize)?nBufferSize:nByteRemaining;
		ar.Read(pBuffer,nByteRead);
		tempFile.Write(pBuffer,nByteRead);

		nByteRemaining-=nByteRead;
	}
	delete []pBuffer;

	return true;
}

void CBmpManager::MakeTempFileFromOriginalPicture(const CString &strFileName)
{
	m_strTempFileName=MakeTempFilename();
	CopyFile(strFileName,m_strTempFileName,FALSE);
}
/*
bool CBmpManager::WriteBmpToArchive(CArchive &ar)
{
	if( (NULL==m_pBmp)||(0==m_pBmp->GetMemUsed()) )
	{
		ar << (DWORD)0;
		return false;
	}
	else	
	{
		long nBmpSize=0;
		nBmpSize=m_pBmp->GetMemUsed();
		// get byte array
		PLMemSink memSink;
		memSink.Open("myBuffer",nBmpSize+1024);	// will it be enough?
		PLBmpEncoder encoder;	
		
		try
		{
			encoder.SaveBmp(m_pBmp,&memSink);
		}
		catch(...)
		{
			// TODO : throw an exception
			CArchiveException *pErr=new CArchiveException(CArchiveException::generic);
			THROW(pErr);
		}
		DWORD nSavedSize=memSink.GetDataSize();
		// write
		ar << nSavedSize;
		ar.Write(memSink.GetBytes(),nSavedSize);
		return true;
	}
}
*/

bool CBmpManager::MakeBmpFromHandle(HANDLE hBmp, int nBitsPerPixel)
{
	delete m_pBmp;
	m_pBmp=NULL;
	DeleteTempFile();

	UCHAR *lpVoid = (UCHAR *)GlobalLock(hBmp);
	LPBITMAPINFOHEADER pHead=(LPBITMAPINFOHEADER)lpVoid;;

	m_pBmp=new CWinBmpEx;
	try
	{
		m_pBmp->CreateFromHDIBBitmap((BITMAPINFOHEADER*) pHead);
		GlobalUnlock(lpVoid);

		// paintlib doesn't handle correctly 24 bits
		int nBits=m_pBmp->GetBitsPerPixel();
		if(24==nBits)
		{
			CWinBmpEx *pBmpTemp=new CWinBmpEx;
			pBmpTemp->CreateCopy(*m_pBmp,32);
			delete m_pBmp;
			m_pBmp=pBmpTemp;
		}
	}
	catch(...)
	{
		DWORD err=::GetLastError();
		delete m_pBmp;
		m_pBmp=NULL;
		GlobalUnlock(lpVoid);
		return false;
	}
	if(Reset())
	{
		CString strTitle;
		strTitle.LoadString(IDS_SCANNED_GRAPHIC);
		m_BitmapName=strTitle;
		MakeTempFileFromMemory();
		return true;
	}
	else
	{
		return false;
	}

}

void CBmpManager::MakeTempFileFromMemory()
{
	m_strTempFileName=MakeTempFilename();

	PLFileSink fileSink;
	fileSink.Open(m_strTempFileName,m_pBmp->GetMemUsed());

	PLBmpEncoder encoder;
	encoder.SaveBmp(m_pBmp,&fileSink);

	fileSink.Close();

}

PLPixel32 CBmpManager::GetPixelColor(const CPoint &point) const
{
	if( (!IsBmpOpened())
		||(point.x<0)
		||(point.y<0)
		||(point.x>=m_nWidth)
		||(point.y>=m_nHeight) )
	{
		return PLPixel32(255,255,255);
	}
	return m_pReader->GetPixel(point);
}
