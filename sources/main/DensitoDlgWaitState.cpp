// DensitoDlgWaitState.cpp: implementation of the CDensitoDlgWaitState class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CurveUnscan.h"
#include "UnscanView.h"
#include "DensitoDlgWaitState.h"
#include "DensitoDlgDrawState.h"
#include "DensitoDlgPickState.h"
#include "DensitometryDialog.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDensitoDlgWaitState::CDensitoDlgWaitState(CDensitometryDialog* pDlg)
:	CDensitoDlgAbstractState(pDlg)
{

	m_pDlg->UpdateData(TRUE);
	m_pDlg->m_bDrawSegment=FALSE;
	m_pDlg->m_bPickTop=FALSE;
	m_pDlg->m_bPickBottom=FALSE;
	m_pDlg->UpdateData(FALSE);

	m_pDlg->m_CursorShape=kDefaultCursor;

}

CDensitoDlgWaitState::~CDensitoDlgWaitState()
{

}

//////////////////////////////////////////////////////////////////////
// Methods
//////////////////////////////////////////////////////////////////////

void CDensitoDlgWaitState::CheckDrawButton()
{
	m_pDlg->UpdateData(TRUE);
	new CDensitoDlgDrawState(m_pDlg);
}

void CDensitoDlgWaitState::CheckPickColorButton(bool bIsTop)
{
	m_pDlg->UpdateData(TRUE);
	new CDensitoDlgPickState(m_pDlg,bIsTop);	
}

