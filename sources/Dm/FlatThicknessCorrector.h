// FlatThicknessCorrector.h: interface for the CFlatThicknessCorrector class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FLATTHICKNESSCORRECTOR_H__568B11A3_3C81_11D5_935E_BA3BA588DF78__INCLUDED_)
#define AFX_FLATTHICKNESSCORRECTOR_H__568B11A3_3C81_11D5_935E_BA3BA588DF78__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "AbstractThicknessCorrector.h"

class CContinuousCurve;

class CFlatThicknessCorrector : public CAbstractThicknessCorrector  
{
DECLARE_SERIAL(CFlatThicknessCorrector)

public:
	CFlatThicknessCorrector(CContinuousCurve* pCurve);
	virtual ~CFlatThicknessCorrector();

public:
	virtual void Serialize(CArchive &ar);
	virtual CAbstractThicknessCorrector* Clone(CContinuousCurve* pCurve);
	virtual void CompensateThickness(CList<CPoint,CPoint>& pointList, bool bTopFollow);

protected:
	CFlatThicknessCorrector();
};

#endif // !defined(AFX_FLATTHICKNESSCORRECTOR_H__568B11A3_3C81_11D5_935E_BA3BA588DF78__INCLUDED_)
