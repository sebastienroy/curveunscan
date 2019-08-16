// DensitoDlgAbstractState.cpp: implementation of the CDensitoDlgAbstractState class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CurveUnscan.h"
#include "DensitoDlgAbstractState.h"
#include "DensitometryDialog.h"
#include "UnscanView.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDensitoDlgAbstractState::CDensitoDlgAbstractState(CDensitometryDialog* pDlg)
:	m_pDlg(pDlg)
{
	delete m_pDlg->m_pState;
	m_pDlg->m_pState=this;
}

CDensitoDlgAbstractState::~CDensitoDlgAbstractState()
{
  
}

//////////////////////////////////////////////////////////////////////
// Methods
//////////////////////////////////////////////////////////////////////


LONG CDensitoDlgAbstractState::StartPick(UINT wParam, LONG lParam)
{
	return 0;
}

LONG CDensitoDlgAbstractState::MovePick(UINT wParam, LONG lParam)
{
	return 0;
}

LONG CDensitoDlgAbstractState::EndPick(UINT wParam, LONG lParam)
{
	return 0;
}

LONG CDensitoDlgAbstractState::ScrollOff(UINT wParam, LONG lParam)
{
	return 0;
}



void CDensitoDlgAbstractState::CheckDrawButton()
{

}

void CDensitoDlgAbstractState::CheckPickColorButton(bool bIsTop)
{

}
