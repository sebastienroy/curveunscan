// DensitoDlgPickState.cpp: implementation of the CDensitoDlgPickState class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CurveUnscan.h"
#include "UnscanView.h"
#include "UnscanDoc.h"
#include "DensitoDlgPickState.h"
#include "DensitoDlgDrawState.h"
#include "DensitoDlgWaitState.h"
#include "DensitometryDialog.h"

#include <Dm/DensityCurve.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDensitoDlgPickState::CDensitoDlgPickState(CDensitometryDialog* pDlg, bool bIsTopColor)
:	CDensitoDlgAbstractState(pDlg),
	m_bIsTopColor(bIsTopColor)
{

	m_pDlg->UpdateData(TRUE);
	m_pDlg->m_bDrawSegment=FALSE;
	m_pDlg->m_bPickTop=bIsTopColor?TRUE:FALSE;
	m_pDlg->m_bPickBottom=bIsTopColor?FALSE:TRUE;
	m_pDlg->UpdateData(FALSE);

  	m_pDlg->m_CursorShape=kPickColorCursor;

}

CDensitoDlgPickState::~CDensitoDlgPickState()
{

}

//////////////////////////////////////////////////////////////////////
// Methods
//////////////////////////////////////////////////////////////////////

void CDensitoDlgPickState::CheckDrawButton()
{
	m_pDlg->UpdateData(TRUE);
	new CDensitoDlgDrawState(m_pDlg);
}

void CDensitoDlgPickState::CheckPickColorButton(bool bIsTop)
{
	m_pDlg->UpdateData(TRUE);

	if(bIsTop==m_bIsTopColor)	// pick canceled
	{
		if(m_pDlg->m_pCurve->IsPositionDefined())
		{
			new CDensitoDlgWaitState(m_pDlg);
		}
		else
		{
			new CDensitoDlgDrawState(m_pDlg);
		}
	}
	else	// other color to pick
	{
		new CDensitoDlgPickState(m_pDlg,bIsTop);	
	}
}

LONG CDensitoDlgPickState::EndPick(UINT wParam, LONG lParam)
{
	CUnscanView* pView=m_pDlg->GetView();
	CClientDC dc(pView);
	pView->OnPrepareDC(&dc);

	// Get Color
	CPoint* pPoint=(CPoint*)lParam;
	PLPixel32 color=pView->GetPixelColor(*pPoint);

	// Set color to buttons
	CColoredButton &rButton=(m_bIsTopColor)?m_pDlg->m_TopColorButton:m_pDlg->m_BottomColorButton;
	rButton.SetColor(color);
	if(m_bIsTopColor)
	{
		m_pDlg->m_ColorScaleButton.SetTopColor(color);
	}
	else
	{
		m_pDlg->m_ColorScaleButton.SetBottomColor(color);
	}

	m_pDlg->SetFocus();
	m_pDlg->UpdateOKButton();

	// Change state
	if(m_pDlg->m_pCurve->IsPositionDefined())
	{
		new CDensitoDlgWaitState(m_pDlg);
	}
	else
	{
		new CDensitoDlgDrawState(m_pDlg);
	}

	return 0;
}

