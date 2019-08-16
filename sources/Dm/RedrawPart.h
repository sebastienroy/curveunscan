// RedrawPart.h: interface for the CRedrawPart class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_REDRAWPART_H__DB8E1C42_D697_4EBB_9B2B_183439FED84E__INCLUDED_)
#define AFX_REDRAWPART_H__DB8E1C42_D697_4EBB_9B2B_183439FED84E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// this class is used to define the areas that must be redrawn

class CRedrawPart  
{
	// constructor destructor
public:
	CRedrawPart(const CPoint& pt1,
				const CPoint& pt2,
				bool bEraseBkg=true);
	virtual ~CRedrawPart();

	// accessors  mutators
public:
	CRect& getRect() { return m_rect; }
	bool isEraseBkg() { return m_bEraseBkg; }

protected:
	CRect m_rect;
	bool m_bEraseBkg;


};

#endif // !defined(AFX_REDRAWPART_H__DB8E1C42_D697_4EBB_9B2B_183439FED84E__INCLUDED_)
