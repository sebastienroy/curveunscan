// BmpManager.h: interface for the CBmpManager class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BMPMANAGER_H__0844A5E0_62E0_11D4_935E_0080C7A4F675__INCLUDED_)
#define AFX_BMPMANAGER_H__0844A5E0_62E0_11D4_935E_0080C7A4F675__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "plpixel32.h"
#include "AbstractBmpReader.h"

class CUnscanDoc;
class CWinBmpEx;


class CBmpManager : public CObject  
{
DECLARE_SERIAL(CBmpManager)

public:
	CBmpManager(CUnscanDoc* pDoc);
	virtual ~CBmpManager();
protected:
	CBmpManager();

public:
	PLPixel32 GetPixelColor(const CPoint& point) const;
	bool MakeBmpFromHandle(HANDLE hBmp,int nBitsPerPixel);
	virtual void Serialize(CArchive &ar);
	CPoint FindNextDash(const CPoint& inPoint,const PLPixel32& blackLevel, BOOL toLeft, int nMaxDist) const;
	void Draw(CDC* pDC,const CRect& rect);
	PLPixel32 GetPointColor(CPoint point);
	CSize GetBmpSize();
	bool IsBmpOpened() const;
	BOOL FindCurve(CPoint& point,const PLPixel32& blackLevel, BOOL top) const;
	CString GetName() const;
	BOOL Draw(CDC* pDC);
	CUnscanDoc* GetDocument() const;
	inline void SetOwner(CUnscanDoc *pDoc) { m_pDoc=pDoc; }
	BOOL FindNext(CPoint& rPoint,const PLPixel32& blackLevel,BOOL toLeft=TRUE,BOOL top=TRUE) const;
	BOOL PixelIsBlack(CPoint& point,const PLPixel32& blackLevel) const;
	CPoint IntoBitmap(CPoint point);
	bool OpenBitmap(CString strName);

protected:
	bool Reset();
	bool IsIntoBitmap(const CPoint& point) const;
	BOOL FindBlackPixel(int nRecur,CPoint& rPoint,const PLPixel32& blackLevel,int direction,int side) const;

	// Attributes
protected:
	void MakeTempFileFromMemory();
//	BOOL m_bModified;
//	bool WriteBmpToArchive(CArchive &ar);
	void MakeTempFileFromOriginalPicture(const CString &strFileName);
	bool ReadArchiveToTempFile(CArchive &ar);
	bool WriteTempFileToArchive(CArchive &ar);
	CString MakeTempFilename();
	void DeleteTempFile();
	CUnscanDoc* m_pDoc;
	CString m_BitmapName;
	CWinBmpEx* m_pBmp;
	mutable CAbstractBmpReader* m_pReader;
	mutable int m_nWidth;
	mutable int m_nHeight;
	mutable CString m_strTempFileName;
};


inline CUnscanDoc* CBmpManager::GetDocument() const
	{
	return m_pDoc;
	}

inline CString CBmpManager::GetName() const
	{
	return (NULL==m_pBmp)?CString(""):m_BitmapName;

	}

inline 	BOOL CBmpManager::PixelIsBlack(CPoint& point,const PLPixel32& blackLevel) const
	{
	return m_pReader->PixelIsBlack(point, blackLevel);
	}


#endif // !defined(AFX_BMPMANAGER_H__0844A5E0_62E0_11D4_935E_0080C7A4F675__INCLUDED_)
