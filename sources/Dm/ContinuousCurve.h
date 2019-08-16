// ContinuousCurve.h: interface for the CContinuousCurve class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CONTINUOUSCURVE_H__2725C5F5_F34E_4344_8172_7B7247679091__INCLUDED_)
#define AFX_CONTINUOUSCURVE_H__2725C5F5_F34E_4344_8172_7B7247679091__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Curve.h"
#include "plpixel32.h"
#include "AbstractThicknessCorrector.h"
#include <list>
using namespace std;

class CCurve;
class CCurveElement;
class CPartialCurve;
class CLimit;
class CSnailAlgorithm;
struct SContinuousCurveDefaultValues;


class CContinuousCurve : public CCurve  
{
public:
	//--- Construction/Destruction
	CContinuousCurve();
	CContinuousCurve(CContinuousCurve& otherCurve);
	CContinuousCurve(CCoordSyst* pCoord, const SContinuousCurveDefaultValues &defaultValues);
	virtual ~CContinuousCurve();

	//--- Methods
public:
	void SetThicknessCorrector(CAbstractThicknessCorrector* theCorrector);
	// Method used to the undo/redo feature of manual modification
	void SetPointList(const list<CPoint>* pointList);
	// Method used to the undo/redo feature of manual modification
	void GetPointList(list<CPoint>* pointList) const;
	CRect SetLine(CPoint ptA,CPoint ptB);
	CRect SetPoint(CPoint point);
	POSITION AddElement(CPartialCurve* pPartial);
	void Construct();
	BOOL RemoveElement(CCurveElement* pElement);
	inline CCurveElement* GetNextElement(POSITION& rPos) const;
	inline POSITION GetHeadElementPosition() const;
	BOOL FillFromElements();
	CContinuousCurve& operator =(const CContinuousCurve &otherCurve);
	BOOL Draw(CDC* pDC) const;
	virtual BOOL IsContinuousCurve() const;
protected:
	void RemoveAllElements();
	void SetMinMax(int nValue,int& nMin, int& nMax) const;
	void Initialize();
	void Initialize(const SContinuousCurveDefaultValues &defaultValues);

	//--- Accessors/Mutators
public:
	virtual CResults* GetResults();
	virtual CCurve* Clone() const;
	virtual void Serialize(CArchive &ar);
	CSnailAlgorithm* GetSnail();
	int SetDashMaxDist(int nDist);
	int GetDashMaxDist() const;
	bool SetDashed(bool bDashed);
	bool IsDashed() const;
	CRect EraseLine(CPoint ptA,CPoint ptB);
	CRect ErasePoint(const CPoint& point);
	void SetBlackLevel(PLPixel32 pixel);
	CAbstractThicknessCorrector* GetThicknessCorrector() const;
	PLPixel32 GetBlackLevel();
	inline BOOL SetTopFollow(BOOL value);
	inline BOOL GetTopFollow() const;
	virtual BOOL IsPresentOn(CPoint point) const;
	inline BOOL GetHandModification() const;
	inline BOOL SetHandModification(BOOL value=TRUE);
	inline int GetTickness() const;
	inline void SetThickness(int thick);
	inline CLimit* GetRightLimit() const;
	inline CLimit* GetLeftLimit() const;

	//--- Attributes
protected:
	mutable CSnailAlgorithm* m_pSnail;
	int m_nDashMaxDist;
	bool m_bDashed;
	CAbstractThicknessCorrector* m_pThicknessCorrector;
	PLPixel32 m_BlackLevel;
	BOOL m_TopFollow;
	BOOL m_HandModification;
	CTypedPtrList<CPtrList,CCurveElement*> m_pElementList;

protected:
DECLARE_SERIAL(CContinuousCurve)

};


CLimit* CContinuousCurve::GetLeftLimit() const
	{
#ifdef _DEBUG
	if(m_pElementList.GetCount()<2)
		{
		AfxMessageBox("Moins de 2 éléments dans la liste lors de l'accès à \n la limite gauche.");
		}
#endif // _DEBUG
	return (CLimit*)m_pElementList.GetHead();
	}

CLimit* CContinuousCurve::GetRightLimit() const
	{
#ifdef _DEBUG
	if(m_pElementList.GetCount()<2)
		{
		AfxMessageBox("Moins de 2 éléments dans la liste lors de l'accès à \n la limite droite.");
		}
#endif // _DEBUG
	return (CLimit*)m_pElementList.GetTail();
	}

BOOL CContinuousCurve::GetHandModification() const
	{
	return m_HandModification;
	}

void CContinuousCurve::SetThickness(int thick)
	{
	SetModifiedFlag(TRUE);
	m_pThicknessCorrector->SetThickness(thick);
	}

int CContinuousCurve::GetTickness() const
	{
	return m_pThicknessCorrector->GetThickness();
	}

BOOL CContinuousCurve::SetHandModification(BOOL value/*=TRUE*/)
	{
	BOOL oldValue=m_HandModification;
	m_HandModification=value;
	return oldValue;
	}

POSITION CContinuousCurve::GetHeadElementPosition() const
	{
	return m_pElementList.GetHeadPosition();
	}

CCurveElement* CContinuousCurve::GetNextElement(POSITION &rPos) const
	{
	return m_pElementList.GetNext(rPos);
	}

BOOL CContinuousCurve::GetTopFollow() const
	{
	return m_TopFollow;
	}

BOOL CContinuousCurve::SetTopFollow(BOOL value)
	{
	BOOL previous=m_TopFollow;
	m_TopFollow=value;
	SetModifiedFlag(TRUE);
	return previous;
	}




#endif // !defined(AFX_CONTINUOUSCURVE_H__2725C5F5_F34E_4344_8172_7B7247679091__INCLUDED_)
