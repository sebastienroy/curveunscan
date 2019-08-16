// AbstractThicknessCorrector.h: interface for the CAbstractThicknessCorrector class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ABSTRACTTHICKNESSCORRECTOR_H__568B11A2_3C81_11D5_935E_BA3BA588DF78__INCLUDED_)
#define AFX_ABSTRACTTHICKNESSCORRECTOR_H__568B11A2_3C81_11D5_935E_BA3BA588DF78__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <afxtempl.h>

class CContinuousCurve;

class CAbstractThicknessCorrector  : public CObject
{
public:
	CAbstractThicknessCorrector(CContinuousCurve* pCurve);
	virtual ~CAbstractThicknessCorrector();

public:
	virtual void Serialize(CArchive &ar);
	virtual CAbstractThicknessCorrector* Clone(CContinuousCurve* pCurve)=0;
	virtual void CompensateThickness(CList<CPoint,CPoint>& pointList, bool bTopFollow)=0;
	void SetOwner(CContinuousCurve* pCurve);
	int GetThickness() const;
	void SetThickness(int thickness);

protected:
	CContinuousCurve* m_pCurve;
	int m_nThickness;

};

inline int CAbstractThicknessCorrector::GetThickness() const { return m_nThickness; }
inline void CAbstractThicknessCorrector::SetOwner(CContinuousCurve *pCurve) { m_pCurve=pCurve; }

#endif // !defined(AFX_ABSTRACTTHICKNESSCORRECTOR_H__568B11A2_3C81_11D5_935E_BA3BA588DF78__INCLUDED_)
