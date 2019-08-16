// PenModificationTool.h: interface for the CPenModificationTool class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PENMODIFICATIONTOOL_H__2C373B23_4C41_11D5_935E_CBF475575E79__INCLUDED_)
#define AFX_PENMODIFICATIONTOOL_H__2C373B23_4C41_11D5_935E_CBF475575E79__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "AbstractModificationTool.h"

class CPenModificationTool : public CAbstractModificationTool  
{
public:
	CPenModificationTool(CContinuousCurve* pCurve);
	virtual ~CPenModificationTool();

public:
	virtual CRect Apply(const CPoint& ptA,const CPoint& ptB) const;

};

#endif // !defined(AFX_PENMODIFICATIONTOOL_H__2C373B23_4C41_11D5_935E_CBF475575E79__INCLUDED_)
