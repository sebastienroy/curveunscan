// CoordSyst.h: interface for the CCoordSyst class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_COORDSYST_H__AB02B004_454F_11D4_935E_0080C7A4F675__INCLUDED_)
#define AFX_COORDSYST_H__AB02B004_454F_11D4_935E_0080C7A4F675__INCLUDED_

#include <afxtempl.h>
#include "LogicPoint.h"	// Added by ClassView
#include "Axe.h"
#include "Curve.h"
class CUnscanDoc;

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CCoordSyst : public CObject  
{
	DECLARE_SERIAL(CCoordSyst)

public:
	static void setScramblingCode(CString strScambling);
	BOOL HasSomethingModified();
	void Serialize(CArchive& ar);
	BOOL IsDefined();
	void SetModified(BOOL flag=TRUE);
	static long IncrementIDNumber();
	static void ResetIdentifierNumber();
	CCoordSyst(CUnscanDoc* pDoc);
	inline int GetCurveCount() const;
	inline void SetDocument(CUnscanDoc* pDoc);
	inline BOOL XAxeIsReverse() const;
	BOOL RemoveCurve(CCurve* pCurve);
	inline void AddCurve(CCurve* pCurve);
	inline CCurve* GetNextCurve(POSITION& rPos) const;
	inline POSITION GetHeadCurvePosition() const;
	inline void SetSelected(BOOL flag=TRUE);
	inline BOOL IsSelected() const;
	BOOL IsPresentOn(CPoint point) const;
	CLogicPoint ToPhysicDouble(CLogicPoint logicPoint) const;
	CPoint ToPhysic(const CLogicPoint &logicPoint) const;
	BOOL CalculateConversionFactors();
	inline BOOL OriginIsDefined() const;
	inline CPoint GetOrigin() const;
	inline CUnscanDoc* GetDocument() const;
	CCoordSyst(CCoordSyst& other);
	inline CAxe* GetYAxe();
	inline CAxe* GetXAxe();
	BOOL Draw(CDC* pDC) const;
	CCoordSyst& operator =(const CCoordSyst &otherCoord);
	CLogicPoint ToLogic(CPoint physicalPoint);
	CPoint CalculateOrigin();
	CCoordSyst();
	virtual ~CCoordSyst();

protected:
	void ConstructorInclude();
	BOOL PresenceTest(CPoint testPoint, CPoint A, CPoint B, CPoint O) const;

	// attributes
protected:
	COLORREF m_Color;
	BOOL m_Selected;
	BOOL m_DefinedOrigin;
	CUnscanDoc* m_pDoc;
	long m_IdentifierNumber;
	static long m_NextIdentifierNumber;
	CAxe m_YAxe;
	CAxe m_XAxe;
	CTypedPtrList<CPtrList, CCurve*> m_CurveList;
	static CString m_strDataScrambling;
	CString m_strComputedScrambling;

	// derivated attributes
protected:
//	BOOL m_bIsModified;
	mutable BOOL m_XReverse;
	mutable CLogicPoint m_BmpOrigin;
	mutable CPoint m_Origin;
	mutable double m_PtoL11,m_PtoL12,m_PtoL21,m_PtoL22;	// matrice de passage physique->logique
	mutable double m_LtoP11,m_LtoP12,m_LtoP21,m_LtoP22;	// matrice de passage logique->physique


};

CAxe* CCoordSyst::GetXAxe()
	{
	return &m_XAxe;
	}

CAxe* CCoordSyst::GetYAxe()
	{
	return &m_YAxe;
	}

CUnscanDoc* CCoordSyst::GetDocument() const
	{
	return m_pDoc;
	}

CPoint CCoordSyst::GetOrigin() const
	{
	if(m_DefinedOrigin)
		{
		return m_Origin;
		}
	else
		{
		return CPoint(0,0);
		}
	}

BOOL CCoordSyst::OriginIsDefined() const
	{
	return m_DefinedOrigin;
	}

BOOL CCoordSyst::IsSelected() const
	{
	return m_Selected;
	}

void CCoordSyst::SetSelected(BOOL flag)
	{
	m_Selected=flag;
	}

POSITION CCoordSyst::GetHeadCurvePosition() const
	{
	return m_CurveList.GetHeadPosition();
	}

CCurve* CCoordSyst::GetNextCurve(POSITION &rPos) const
	{
	return m_CurveList.GetNext(rPos);
	}

void CCoordSyst::AddCurve(CCurve *pCurve)
	{
#ifdef _DEBUG
	if(pCurve==NULL)
		{
		AfxMessageBox("Attention ajout de courbe invalide dans le syst de coordonnées");
		return;
		}
#endif // _DEBUG
	m_CurveList.AddTail(pCurve);
	pCurve->SetCoordSyst(this);
	}

BOOL CCoordSyst::XAxeIsReverse() const
	{
	return m_XReverse;
	}

void CCoordSyst::SetDocument(CUnscanDoc *pDoc)
	{
	m_pDoc=pDoc;
	}

int CCoordSyst::GetCurveCount() const
	{
	return m_CurveList.GetCount();
	}

#endif // !defined(AFX_COORDSYST_H__AB02B004_454F_11D4_935E_0080C7A4F675__INCLUDED_)
