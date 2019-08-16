// RedrawPart.cpp: implementation of the CRedrawPart class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "RedrawPart.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CRedrawPart::CRedrawPart(const CPoint& pt1,
						 const CPoint& pt2,
						 bool bEraseBkg/*=true*/)
:	m_rect(pt1,pt2),
	m_bEraseBkg(bEraseBkg)						
{

}

CRedrawPart::~CRedrawPart()
{

}
