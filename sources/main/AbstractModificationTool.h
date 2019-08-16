// AbstractModificationTool.h: interface for the CAbstractModificationTool class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ABSTRACTMODIFICATIONTOOL_H__2C373B22_4C41_11D5_935E_CBF475575E79__INCLUDED_)
#define AFX_ABSTRACTMODIFICATIONTOOL_H__2C373B22_4C41_11D5_935E_CBF475575E79__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CContinuousCurve;

class CAbstractModificationTool  
{
public:
	CAbstractModificationTool(CContinuousCurve* pCurve);
	virtual ~CAbstractModificationTool();

public:
	virtual CRect Apply(const CPoint& ptA,const CPoint& ptB)const =0;

protected:
	CContinuousCurve* m_pCurve;

};

#endif // !defined(AFX_ABSTRACTMODIFICATIONTOOL_H__2C373B22_4C41_11D5_935E_CBF475575E79__INCLUDED_)
