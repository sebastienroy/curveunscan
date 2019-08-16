// AxePointPickingState.cpp: implementation of the CAxePointPickingState class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CurveUnscan.h"
#include "UnscanDoc.h"
#include "AxePointPickingState.h"
#include "AxeDrawingState.h"
#include "AxeWaitState.h"

#include <Utilities/Tools.h>

#include <Dm/Axe.h>
#include <Dm/ScalePoint.h>
#include <Dm/RedrawPart.h>

#include "AxeDialog.h"
#include "Sequence.h"
#include "ValueEdit.h"

#include <list>
using namespace std;


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CAxePointPickingState::CAxePointPickingState(CAxeDialog* theDialog,int nPointNumber)
:CAxeAbstractState(theDialog),
m_nPointNumber(nPointNumber)
{
	int nOtherOtherPoint=(1==nPointNumber)?2:1;
	m_pScalePoint=m_pDialog->m_pAxe->GetScalePoint(nPointNumber);
	m_pOtherScalePoint=m_pDialog->m_pAxe->GetScalePoint(nOtherOtherPoint);

	m_pDialog->m_bCheckAxe=FALSE;
	m_pDialog->m_bCheckPt1=(1==nPointNumber);
	m_pDialog->m_bCheckPt2=(2==nPointNumber);
	m_pDialog->UpdateData(FALSE);

	m_pDialog->m_CursorShape=kDrawLineCursor;

	UpdateStateLine();
}

CAxePointPickingState::~CAxePointPickingState()
{

}

LONG CAxePointPickingState::EndPick(UINT wParam, LONG lParam)
{
	CPoint point=*((CPoint*)lParam);

	// Check consistency
	bool bValid=true;
	if(m_pOtherScalePoint->PositionIsDefined())
		{
		CAxe* pAxe=m_pDialog->m_pAxe;
		CPoint ptA=pAxe->GetFrom();
		CPoint ptB=pAxe->GetTo();
		CPoint ptProj=CTools::GetProjection(ptA,ptB,point);
		if(ptProj==m_pOtherScalePoint->GetAxePosition())
			{
			bValid=false;
			CString msg;
			msg.LoadString(IDS_SCALE_POINT_DIFFERENT);
			m_pDialog->MessageBox(msg,"CurveUnscan",MB_OK|MB_ICONINFORMATION);
			}
		}

	if(!bValid)
		{
		return -1;
		}

	// Set point
	list<CRedrawPart> redrawList;
	m_pScalePoint->SetPosition(point,&redrawList);
	CUnscanDoc* pDoc=m_pDialog->m_pSequence->GetDocument();
	pDoc->UpdateAllViews(NULL,0);

	// set focus on the related ValueEdit and update
	CValueEdit* pEdit=(1==m_nPointNumber)?&(m_pDialog->m_ValueEditPt1):&(m_pDialog->m_ValueEditPt2);
	pEdit->SetFocus();
	pEdit->SetSel(0,-1);

	// Update Dialog OK button
	m_pDialog->UpdateOKButton();

	// Change state

	if(!m_pOtherScalePoint->PositionIsDefined())
		{
		int nOtherPt=(1==m_nPointNumber)?2:1;
		m_pDialog->EnablePoint(nOtherPt,TRUE);
		new CAxePointPickingState(m_pDialog,nOtherPt);
		}
	else
		{
		new CAxeWaitState(m_pDialog);
		}
	return 0;
}

void CAxePointPickingState::CheckAxeButton()
{
	new CAxeDrawingState(m_pDialog);
}

void CAxePointPickingState::CheckPointButton(int nButton)
{
	if(nButton==m_nPointNumber)
		{
		new CAxeWaitState(m_pDialog);
		}
	else
		{
		new CAxePointPickingState(m_pDialog,nButton);
		}
}

void CAxePointPickingState::UpdateStateLine()
{
	int nOther=(1==m_nPointNumber)?2:1;
	CString msg; //="Point picking";

	if(m_pScalePoint->PositionIsDefined())	// point already defined, the user knows what to do
		{
		msg.Format(IDS_AXE_PICK_POINT,m_nPointNumber);
		}
	else if( (m_pDialog->GetFocusedEditNb()==nOther)	// other value not defined
				&& (m_pDialog->IsValueEditEmpty(nOther)) )
		{
		msg.Format(IDS_AXE_ENTER_VALUE_AND_POSITION,nOther,m_nPointNumber);
		}
	else if( (m_pDialog->GetFocusedEditNb()==m_nPointNumber)	// this value not defined
				&& (m_pDialog->IsValueEditEmpty(m_nPointNumber)) )
		{
		msg.Format(IDS_AXE_DEFINE_SCALEPOINT,m_nPointNumber);
		}
	else
		{
		msg.Format(IDS_AXE_PICK_POINT,m_nPointNumber);
		}
	
	CWnd* pStatus=m_pDialog->GetDlgItem(IDC_STATIC_STATUS);
	pStatus->SetWindowText(msg);
	pStatus->RedrawWindow();
}
