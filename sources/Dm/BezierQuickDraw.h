// BezierQuickDraw.h: interface for the CBezierQuickDraw class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BEZIERQUICKDRAW_H__9B65D52E_1C2D_4D27_B575_4CFFB25CFE22__INCLUDED_)
#define AFX_BEZIERQUICKDRAW_H__9B65D52E_1C2D_4D27_B575_4CFFB25CFE22__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BezierNode.h"

class CBezierQuickDraw  
{
public:
	CBezierQuickDraw(CBezierNode* pNode);
	virtual ~CBezierQuickDraw();

public:
	void Draw(CDC *pDC);

protected:
	void Redraw(CDC* pDC);

protected:
	void UpdateData();
	CBezierNode* m_pNode;
	CBezierNode* m_pDrawnNode;

	CBezierNode::Data m_FrontData;
	CBezierNode::Data m_BackData;
	CBezierNode::Data m_CurrentData;

	CPoint* m_PtArray;
	int m_nPtArrayCount;

	bool m_bDrawFront;
	bool m_bDrawBack;
	bool m_bAlreadyDrawn;

};

#endif // !defined(AFX_BEZIERQUICKDRAW_H__9B65D52E_1C2D_4D27_B575_4CFFB25CFE22__INCLUDED_)
