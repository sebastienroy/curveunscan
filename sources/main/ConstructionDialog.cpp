// ConstructionDialog.cpp : implementation file
//

#include "stdafx.h"
#include "ConstructionDialog.h"
#include "CurveUnscan.h"
#include "UnscanView.h"
#include "UnscanDoc.h"
#include "Sequence.h"

#include <Dm/CoordSyst.h>
#include <Dm/Curve.h>

#include "HelpSystem/HelpFunctions.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CConstructionDialog dialog


CConstructionDialog::CConstructionDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CConstructionDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CConstructionDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CConstructionDialog::CConstructionDialog(UINT ID, CUnscanView *pParent, CSequence *pSequence)
	: CDialog(ID, (CWnd*)pParent)
// Met en place les liens et le dialogTemplate
{
	m_pSequence=pSequence;
	pParent->SetActiveDialog(this);
	m_CursorShape=kDefaultCursor;
}

void CConstructionDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CConstructionDialog)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CConstructionDialog, CDialog)
	//{{AFX_MSG_MAP(CConstructionDialog)
	ON_BN_CLICKED(IDC_PREVIOUS, OnPrevious)
	ON_WM_HELPINFO()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConstructionDialog message handlers

void CConstructionDialog::OnOK() 
// Met à jour les données non "temps réel", appelle la fonction "NextStep()"
// de la séquence et détruit le dialogue.
{
	// TODO: Add extra validation here
	UpdateData(TRUE);
	if(DataValidation())
		{
		UpdateObjects();
		CRect rect;
		GetWindowRect(&rect);
		m_pSequence->SetActWndPosition(rect.TopLeft());
		ShowWindow(SW_HIDE);
		m_pSequence->NextStep(1);
		DestroyWindow();
		}
}

void CConstructionDialog::OnCancel() 
// appelle la fonction CancelSequence() de la séquence et détruit le dialogue
	{
	// TODO: Add extra cleanup here
	m_pSequence->CancelSequence(this);
	DestroyWindow();	
	}

void CConstructionDialog::OnPrevious() 
	{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	UpdateObjects();
	CRect rect;
	GetWindowRect(&rect);
	m_pSequence->SetActWndPosition(rect.TopLeft());
	ShowWindow(SW_HIDE);
	m_pSequence->NextStep(-1);
	DestroyWindow();
	}

void CConstructionDialog::PostNcDestroy() 
	{
	// TODO: Add your specialized code here and/or call the base class
	delete this;
	}


BOOL CConstructionDialog::UpdateOKButton()
// Active ou désactive le bouton "OK" suivant la valeur 
//  renvoyée par la fonction "OKState
	{
	BOOL state=OKState();
	CButton* buttonOK=(CButton*)GetDlgItem(IDOK);
	buttonOK->EnableWindow(state);
	return state;
	}

BOOL CConstructionDialog::OKState()
//  Virtual function. Return TRUE if the OK button can be activated
//	   (All needed values are defined
//      The determination of that must be redefined in the derived classes
	{
	return FALSE;
	}

BOOL CConstructionDialog::DataValidation()
// Verify if data are consistant. returns TRUE if yes.
//  The derived classes must explain via MessageBox()s what is not OK
	{
//	MessageBox("Appel de la fonction DataValidation de base.");
	return TRUE;
	}

void CConstructionDialog::UpdateObjects()
//  Non real-time data transfert between Dialog and objects
//   Virtual function. Must be redefined in derived classes
	{
#ifdef _DEBUG
	MessageBox("Erreur : appel de la fonction UpdateObjects()\nde la classe de base");
#endif // _DEBUG
	}

void CConstructionDialog::NoPrevious(BOOL flag)
// Desactive (TRUE) ou reactive (FALSE) le bouton PREVIOUS du dialogue
	{
	CButton* pPrevious=(CButton*)GetDlgItem(IDC_PREVIOUS);
	if ((flag)&&(pPrevious!=NULL))
		{
		pPrevious->EnableWindow(FALSE);
		pPrevious->DestroyWindow();
		}
	else if (pPrevious!=NULL)
		{
		pPrevious->EnableWindow(TRUE);
		}
	}

void CConstructionDialog::SetLastDialog(BOOL flag)
// Change le bouton Next en Ok (TRUE) et inversement (FALSE)
	{
	CString strCaption;
	if (flag)
		{
		strCaption.LoadString(IDS_FINISHBUTTON);
		}
	else
		{
		strCaption.LoadString(IDS_NEXTBUTTON);
		}
	SetDlgItemText(IDOK,strCaption);
	}

BOOL CConstructionDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CPoint position=m_pSequence->GetPrevWndPosition();
	CRect rect;
	GetWindowRect(&rect);
	MoveWindow(position.x,position.y,rect.Width(),rect.Height());
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CConstructionDialog::OnHelpInfo(HELPINFO* pHelpInfo) 
{
	// TODO: Add your message handler code here and/or call default
	CHelpFunctions::DisplayCtrlPopup(FromHandle((HWND)pHelpInfo->hItemHandle),
									pHelpInfo->MousePos,
									pHelpInfo->iCtrlId);
	return TRUE;
}


CUnscanView* CConstructionDialog::GetView()
{
	return m_pSequence->GetView();
}

CUnscanDoc* CConstructionDialog::GetDocument()
{
	return m_pSequence->GetDocument();
}

CursorShape CConstructionDialog::GetCursorShape() const
{
	return m_CursorShape;
}

void CConstructionDialog::SetCursorShape(CursorShape shape)
{
	m_CursorShape=shape;
}

bool CConstructionDialog::CheckCurveNameUnicity(CCurve* pCurve, CString strName)
{
	CUnscanDoc* pDoc=m_pSequence->GetDocument();
	CCoordSyst* pCoord;
	CCurve* pCurrentCurve;

	POSITION coordPos=pDoc->GetHeadCoordSystPosition();
	POSITION curvePos;
	while(coordPos!=NULL)
	{
		pCoord=pDoc->GetNextCoordSyst(coordPos);
		curvePos=pCoord->GetHeadCurvePosition();
		while(curvePos!=NULL)
		{
			pCurrentCurve=pCoord->GetNextCurve(curvePos);
			if( (pCurrentCurve!=pCurve) && (pCurrentCurve->GetName()==strName) )
			{
				CString msg;
				msg.LoadString(IDS_NAME_ALREADY_EXISTS);
				int result=MessageBox(msg,"CurveUnscan",MB_YESNO|MB_ICONEXCLAMATION);
				if(IDNO==result)
				{
					return false;
				}
				else
				{
					return true;
				}
			}
		}
	}
	
	return true;
}
