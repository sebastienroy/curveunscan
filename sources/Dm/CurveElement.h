// CurveElement.h: interface for the CCurveElement class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CURVEELEMENT_H__7AAEEBE0_6240_11D4_935E_0080C7A4F675__INCLUDED_)
#define AFX_CURVEELEMENT_H__7AAEEBE0_6240_11D4_935E_0080C7A4F675__INCLUDED_

#include "UnscanDoc.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CContinuousCurve;

	typedef enum 
	{
		kUndefined,	// default value, used when unasked
		kOutside,	// used for a point which is outside the element definition
		kUp,		// used by partial curves, when a point of the partial curve has the same x
		kDown,		// idem
		kOn			// partial curve : when a point is the same ; limits : when into the limit
	} RelativePosition;


class CCurveElement : public CObject  
{

public:
	virtual void Serialize(CArchive &ar);
	virtual RelativePosition GetRelativePosition(const CPoint& point) const =0 ;
	CCurveElement& operator =(const CCurveElement &otherElement);
	virtual BOOL RemovePart(CPoint point, BOOL toLeft=TRUE);
	virtual BOOL IsPartialCurve();
	virtual BOOL IsLimit();
	void SetCurve(CContinuousCurve* pCurve);
	void SetRightElement(CCurveElement* pElement);
	void SetLeftElement(CCurveElement* pElement);
	CCurveElement* GetLeftElement();
	CCurveElement* GetRightElement();
	virtual BOOL HaveIncluded(CPoint point);
	CCurveElement(CContinuousCurve* pCurve);
	CContinuousCurve* GetCurve();
	CCurveElement();
	virtual ~CCurveElement();

protected:
	void Initialize();
	CCurveElement* m_pRightElement;
	CCurveElement* m_pLeftElement;
	CContinuousCurve* m_pCurve;
};

#endif // !defined(AFX_CURVEELEMENT_H__7AAEEBE0_6240_11D4_935E_0080C7A4F675__INCLUDED_)
