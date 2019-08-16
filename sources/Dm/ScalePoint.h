// ScalePoint.h: interface for the CScalePoint class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SCALEPOINT_H__FDDC4660_4842_11D4_935E_0080C7A4F675__INCLUDED_)
#define AFX_SCALEPOINT_H__FDDC4660_4842_11D4_935E_0080C7A4F675__INCLUDED_


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <list>
using namespace std;
#include "RedrawPart.h"

class CAxe;

class CScalePoint : public CObject  
{
DECLARE_SERIAL(CScalePoint)

public:
	inline void SetOwner(CAxe *pAxe) { m_pAxe = pAxe; }
	virtual void Serialize(CArchive& ar);
	void SetAxe(CAxe* pAxe);
	CPoint GetAxePosition();
	BOOL EraseValue();
	void Actualize();
	CScalePoint(CScalePoint& other);
	CScalePoint& operator =(const CScalePoint &other);
	double GetValue();
	BOOL IsDefined();
	BOOL PositionIsDefined();
	SetValue(double valeur);
	BOOL ValueIsDefined();
	BOOL SetPosition(CPoint point,list<CRedrawPart>* redrawList=NULL);
	BOOL Draw(CDC* pDC) const;
	CScalePoint();
	virtual ~CScalePoint();

protected:
	bool GetTickLine(CPoint& pt1, CPoint& pt2) const;
	static const double m_piSur2;
	static const double m_tickLength;

	CAxe* m_pAxe;
	BOOL m_DefinedPosition;
	BOOL DrawLegend(CDC* pDC) const;
	BOOL DrawThick(CDC* pDC) const;
	mutable CPoint m_AxePosition;
	BOOL m_DefinedValue;
	double m_Value;
	CPoint m_Position;
};

#endif // !defined(AFX_SCALEPOINT_H__FDDC4660_4842_11D4_935E_0080C7A4F675__INCLUDED_)
