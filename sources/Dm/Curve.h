// Curve.h: interface for the CCurve class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CURVE_H__1C7507B0_181D_49F7_AA1A_35FC02BDA92A__INCLUDED_)
#define AFX_CURVE_H__1C7507B0_181D_49F7_AA1A_35FC02BDA92A__INCLUDED_

#include <afxtempl.h>


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CCoordSyst;
class CResults;

class CCurve : public CObject  
{

public:
	virtual CCurve* Clone() const =0;
	virtual void Serialize(CArchive& ar) =0;
	virtual CResults* GetResults()=0;
	void SetResults(CResults* pResults);
	POSITION FindPoint(CPoint point);
	BOOL SetModifiedFlag(BOOL flag=TRUE);
	BOOL GetModifiedFlag();
	static long IncrementIDNumber();
	long GetIdentifierNumber();
	void SetCoordSyst(CCoordSyst* pCoord);
	int GetPointCount();
	CPoint GetPrevPoint(POSITION& rPos);
	POSITION GetTailPointPosition();
	CCurve(CCoordSyst* pCoord);
	static long ResetIdentifierNumber();
	void SetSelected(BOOL flag=TRUE);
	BOOL IsSelected();
	virtual BOOL IsPresentOn(CPoint point) const =0;
	void SortStraight();
	CPoint GetNextPoint(POSITION& rPos);
	POSITION GetHeadPointPosition();
	CCoordSyst* GetCoordSyst();
	virtual BOOL IsContinuousCurve() const;
	virtual BOOL IsDiscreteCurve() const;
	CCurve(CCurve& otherCurve);
	void SetName(CString name);
	CString GetName();
	CCurve& operator =(const CCurve &otherCurve);
	virtual BOOL Draw(CDC* pDC) const=0;
	CCurve();
	virtual ~CCurve();
protected:
	CResults* m_pResults;
	BOOL m_ModifiedFlag;
	COLORREF m_Color;
	void Initialize();
	BOOL m_Selected;
	CCoordSyst* m_pCoordSyst;
	CString m_CurveName;
	long m_IdentifierNumber;
	static long m_NextIdentifierNumber;
	CList<CPoint, CPoint> m_PointList;

protected:
//	DECLARE_SERIAL(CCurve)

};

#endif // !defined(AFX_CURVE_H__1C7507B0_181D_49F7_AA1A_35FC02BDA92A__INCLUDED_)
