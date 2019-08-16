// ZoomCombo.cpp : implementation file
//

#include "stdafx.h"
#include "CurveUnscan.h"
#include "ZoomCombo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CZoomCombo

CZoomCombo::CZoomCombo()
{
}

CZoomCombo::~CZoomCombo()
{
}


BEGIN_MESSAGE_MAP(CZoomCombo, CComboBox)
	//{{AFX_MSG_MAP(CZoomCombo)
	ON_WM_CHAR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CZoomCombo message handlers



void CZoomCombo::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
	{
	// TODO: Add your message handler code here and/or call default
	if( (nChar>='0')&&(nChar<='9') )
		{
		CComboBox::OnChar(nChar, nRepCnt, nFlags);
		}
	if(nChar=='\n')
		{
		GetParent()->SendMessage(WM_ZOOM_CHANGES);
		}	
	}


