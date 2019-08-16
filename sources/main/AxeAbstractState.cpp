// AxeAbstractState.cpp: implementation of the CAxeAbstractState class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CurveUnscan.h"
#include "AxeAbstractState.h"

#include "UnscanDoc.h"
#include "AxeDialog.h"
#include "ValueEdit.h"

#include <Dm/CoordSyst.h>
#include <Dm/Axe.h>
#include <Dm/ScalePoint.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#include "AxeDialog.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CAxeAbstractState::CAxeAbstractState(CAxeDialog* theDialog)
:m_pDialog(theDialog)
{
	delete m_pDialog->m_pState;
	m_pDialog->m_pState=this;
}

CAxeAbstractState::~CAxeAbstractState()
{

}

LONG CAxeAbstractState::StartPick(UINT wParam, LONG lParam)
{
	return 0;
}

LONG CAxeAbstractState::MovePick(UINT wParam, LONG lParam)
{
	return 0;
}

LONG CAxeAbstractState::EndPick(UINT wParam, LONG lParam)
{
	return 0;
}

void CAxeAbstractState::PointValueEdited(int nControl)
{
	CValueEdit& editCtrl=(1==nControl)?m_pDialog->m_ValueEditPt1:m_pDialog->m_ValueEditPt2;
	CScalePoint* pScalePt=m_pDialog->m_pAxe->GetScalePoint(nControl);

	if(editCtrl.IsEmpty())
		{
		pScalePt->EraseValue();
		}
	else
		{
		pScalePt->SetValue(editCtrl.GetValue());
		}

	UpdateStateLine();
	m_pDialog->UpdateData(FALSE);
	m_pDialog->UpdateOKButton();
	CUnscanDoc* pDoc=m_pDialog->m_pAxe->GetCoordSyst()->GetDocument();
	pDoc->UpdateAllViews(NULL);

}

LONG CAxeAbstractState::ScrollOff(UINT wParam, LONG lParam)
{
	return 0;
}

void CAxeAbstractState::UpdateStateLine()
{
}
