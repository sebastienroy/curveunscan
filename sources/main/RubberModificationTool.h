// RubberModificationTool.h: interface for the CRubberModificationTool class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RUBBERMODIFICATIONTOOL_H__2C373B24_4C41_11D5_935E_CBF475575E79__INCLUDED_)
#define AFX_RUBBERMODIFICATIONTOOL_H__2C373B24_4C41_11D5_935E_CBF475575E79__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "AbstractModificationTool.h"

class CRubberModificationTool : public CAbstractModificationTool  
{
public:
	CRubberModificationTool(CContinuousCurve* pCurve);
	virtual ~CRubberModificationTool();

public:
	virtual CRect Apply(const CPoint &ptA, const CPoint &ptB) const;

};

#endif // !defined(AFX_RUBBERMODIFICATIONTOOL_H__2C373B24_4C41_11D5_935E_CBF475575E79__INCLUDED_)
