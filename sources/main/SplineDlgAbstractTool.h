// SplineDlgAbstractTool.h: interface for the CSplineDlgAbstractTool class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SPLINEDLGABSTRACTTOOL_H__0DE5786F_373A_45AC_B7CF_A40ADAD3CA4B__INCLUDED_)
#define AFX_SPLINEDLGABSTRACTTOOL_H__0DE5786F_373A_45AC_B7CF_A40ADAD3CA4B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CSplineDialog;
class CSplineCurve;

class CSplineDlgAbstractTool  
{
public:
	typedef enum
	{
		kAddBack,
		kAddFront,
		kAddMiddle,
		kRemove,
		kModify
	}
	ToolKind;

public:
	CSplineDlgAbstractTool(CSplineDialog* pDialog, CSplineCurve* pCurve);
	virtual ~CSplineDlgAbstractTool();

public:
	virtual CString getToolComment();
	virtual ToolKind GetKind() =0;
	virtual void EndPick(const CPoint &pt, bool bModif1, bool bModif2);
	virtual void MovePick(const CPoint &pt, bool bModif1, bool bModif2);
	virtual void StartPick(const CPoint& pt, bool bModif1, bool bModif2);

protected:
	CSplineDialog* m_pDialog;
	CSplineCurve* m_pCurve;

};

#endif // !defined(AFX_SPLINEDLGABSTRACTTOOL_H__0DE5786F_373A_45AC_B7CF_A40ADAD3CA4B__INCLUDED_)
