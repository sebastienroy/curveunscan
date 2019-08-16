// AxeWaitState.cpp: implementation of the CAxeWaitState class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CurveUnscan.h"
#include "AxeWaitState.h"
#include "AxeDrawingState.h"
#include "AxePointPickingState.h"
#include "AxeDialog.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CAxeWaitState::CAxeWaitState(CAxeDialog* theDialog)
:CAxeAbstractState(theDialog)
{
	m_pDialog->m_bCheckAxe=FALSE;
	m_pDialog->m_bCheckPt1=FALSE;
	m_pDialog->m_bCheckPt2=FALSE;
	m_pDialog->UpdateData(FALSE);

	m_pDialog->m_CursorShape=kDefaultCursor;

	UpdateStateLine();
}

CAxeWaitState::~CAxeWaitState()
{

}

void CAxeWaitState::CheckAxeButton()
{
	new CAxeDrawingState(m_pDialog);
}

void CAxeWaitState::CheckPointButton(int nButton)
{
	new CAxePointPickingState(m_pDialog,nButton);
}

void CAxeWaitState::UpdateStateLine()
{
	CString msg; //="wait state";

	int nFocused=m_pDialog->GetFocusedEditNb();
	if( (1==nFocused)&&(m_pDialog->IsValueEditEmpty(1)) )
		{
		msg.Format(IDS_AXE_ENTER_VALUE,1);
		}
	else if( (2==nFocused)&&(m_pDialog->IsValueEditEmpty(2)) )
		{
		msg.Format(IDS_AXE_ENTER_VALUE,2);
		}
	else if(!m_pDialog->IsPositionDefined(1))
		{
		msg.Format(IDS_AXE_DEFINE_POINT,1);
		}
	else if(!m_pDialog->IsPositionDefined(2))
		{
		msg.Format(IDS_AXE_DEFINE_POINT,2);
		}
	else if(m_pDialog->IsValueEditEmpty(1))
		{
		msg.Format(IDS_AXE_ENTER_VALUE,1);
		}
	else if(m_pDialog->IsValueEditEmpty(2))
		{
		msg.Format(IDS_AXE_ENTER_VALUE,2);
		}
	else
		{
		msg.LoadString(IDS_AXE_READY);
		}

	CWnd* pStatus=m_pDialog->GetDlgItem(IDC_STATIC_STATUS);
	pStatus->SetWindowText(msg);
	pStatus->RedrawWindow();
}
