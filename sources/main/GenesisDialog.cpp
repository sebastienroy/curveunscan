// GenesisDialog.cpp : implementation file
//

#include "stdafx.h"
#include "CurveUnscan.h"
#include "GenesisDialog.h"
#include "UnscanView.h"
#include "UnscanDoc.h"
#include "Sequence.h"
#include "ContinuousAdvOptDlg.h"
#include "DashMaxDistDialog.h"

#include <Dm/ContinuousCurve.h>
#include <Dm/CurveElement.h>
#include <Dm/PartialCurve.h>
#include <Dm/Limit.h>
#include <Dm/LogicPoint.h>
#include <Dm/CoordSyst.h>
#include <Dm/BmpManager.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGenesisDialog dialog



CGenesisDialog::CGenesisDialog(UINT ID, CUnscanView *pView, CSequence *pSequence, CContinuousCurve *pCurve)
:	CConstructionDialog(ID,pView,pSequence),
	m_pOptDlg(NULL),
	m_pDashDistDialog(NULL)
{
	m_pCurve=pCurve;
	m_pCoord=pCurve->GetCoordSyst();
	m_Thickness=pCurve->GetTickness();
	m_CurveName=pCurve->GetName();
	m_Dashed=(pCurve->IsDashed())?0:1;
	m_nDashMaxDist=pCurve->GetDashMaxDist();
	m_Follow=(pCurve->GetTopFollow())?0:1;
	m_CheckThick=FALSE;
	m_CheckElement=TRUE;
	m_CursorShape=kDrawLineCursor;
}

void CGenesisDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGenesisDialog)
	DDX_Control(pDX, IDC_GENESIS_LIST, m_GenesisListBox);
	DDX_Text(pDX, IDC_EDIT_THICKNESS, m_Thickness);
	DDV_MinMaxInt(pDX, m_Thickness, 1, 32);
	DDX_Text(pDX, IDC_EDIT_CURVENAME, m_CurveName);
	DDX_Check(pDX, IDC_CHECK_THICK, m_CheckThick);
	DDX_Check(pDX, IDC_CHECK_ELEMENT, m_CheckElement);
	DDX_Radio(pDX, IDC_RADIO_TOP, m_Follow);
	DDX_Text(pDX, IDC_EDIT_DISTMAX, m_nDashMaxDist);
	DDV_MinMaxInt(pDX, m_nDashMaxDist, 0, 1000);
	DDX_Radio(pDX, IDC_RADIO_DASHED, m_Dashed);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CGenesisDialog, CDialog)
	//{{AFX_MSG_MAP(CGenesisDialog)
	ON_MESSAGE(WM_END_PICK,OnEndPick)
	ON_MESSAGE(WM_OPTDLG_CLOSED,OnOptDlgClosed)
	ON_MESSAGE(WM_APPLY_DASHDIST,OnApplyDashDist)
	ON_BN_CLICKED(IDC_PREVIOUS, OnPrevious)
	ON_BN_CLICKED(IDC_DELETE_ELEMENT, OnDelete)
	ON_LBN_SELCHANGE(IDC_GENESIS_LIST, OnSelchangeGenesisList)
	ON_BN_CLICKED(IDC_CHECK_THICK, OnCheckThick)
	ON_EN_CHANGE(IDC_EDIT_CURVENAME, OnChangeEditCurvename)
	ON_EN_CHANGE(IDC_EDIT_THICKNESS, OnChangeEditThickness)
	ON_BN_CLICKED(IDC_CHECK_ELEMENT, OnCheckElement)
	ON_BN_CLICKED(IDC_RADIO_TOP, OnRadioTop)
	ON_BN_CLICKED(IDC_RADIO_BOTTOM, OnRadioBottom)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_ADV_CONTINUOUS_BUTTON, OnAdvContinuousButton)
	ON_BN_CLICKED(IDC_BUTTON_DASHDIST, OnButtonDashdist)
	ON_MESSAGE(WM_DASHDISTDLG_CLOSED,OnDashDistDlgClosed)
	ON_BN_CLICKED(IDC_RADIO_DASHED, OnRadioDashed)
	ON_BN_CLICKED(IDC_RADIO_NOTDASHED, OnRadioNotdashed)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGenesisDialog message handlers

void CGenesisDialog::OnPrevious() 
	{
	// TODO: Add your control notification handler code here
	CConstructionDialog::OnPrevious();
	}

void CGenesisDialog::OnDelete() 
// virer l'élément sélectionné, reconstruire la courbe et la ListBox
	{
	// TODO: Add your control notification handler code here
	if(!ActionConfirmed())
		{
		return;
		}

	int index=m_GenesisListBox.GetCurSel();
	if(index==LB_ERR)
		{
		return;
		CString msg;
		msg.LoadString(IDS_NO_POINT_SELECTED);
		MessageBox(msg,"CurveUnscan",MB_OK|MB_ICONINFORMATION);
		}
	CCurveElement* pElement=(CCurveElement*)m_GenesisListBox.GetItemDataPtr(index);

/*#ifdef _DEBUG
	CString str;
	str.Format("Remove Partial :\nindex=%d\npointeur=%d.",index,pElement);
	MessageBox(str);
#endif // _DEBUG*/

	m_pCurve->RemoveElement(pElement);
	delete pElement;
	m_GenesisListBox.DeleteString(index);
	UpdateDeleteButton();
	UpdateOKButton();
	m_pCurve->Construct();
	CWnd* pWnd=GetParent();
	pWnd->InvalidateRgn(NULL);
	pWnd->PostMessage(WM_PAINT);
	}

void CGenesisDialog::OnSelchangeGenesisList() 
// Mettre à jour le bouton "Delete"
	{
	// TODO: Add your control notification handler code here
	UpdateDeleteButton();
	}

BOOL CGenesisDialog::UpdateDeleteButton()
// Met à jour le bouton "Delete"
	{
	CButton* pButton=(CButton*)GetDlgItem(IDC_DELETE_ELEMENT);
	BOOL select=((m_GenesisListBox.GetCurSel())==LB_ERR)?FALSE:TRUE;
	pButton->EnableWindow(select);
	return select;
	}

void CGenesisDialog::AddPartial(CPartialCurve *pPartial)
// Rajoute une courbe partielle à la ListBox
	{
	CPoint point=pPartial->GetPosition();
	CLogicPoint lpoint=m_pCoord->ToLogic(point);
	CString strX;
	CString strY;
	CString strLB;
	strX.Format("%g",lpoint.x);	
	for(int length=strX.GetLength();length<14;length++)
		{
		strX+=CString("  ");
		}
	strY.Format("%g",lpoint.y);
	strLB=strX+strY;
	int index=m_GenesisListBox.AddString(strLB);
	m_GenesisListBox.SetItemDataPtr(index,pPartial);
/*#ifdef _DEBUG
	CString str;
	str.Format("AddPartial :\nindex=%d\npointeur=%d.",index,pPartial);
	MessageBox(str);
#endif // _DEBUG*/
	}

void CGenesisDialog::FillListBox()
// Remplit la listBox en fonction des courbes partielles déjà existantes.
	{
	m_GenesisListBox.ResetContent();
	m_PosArray.RemoveAll();

	POSITION pos=m_pCurve->GetHeadElementPosition();
	CCurveElement* pElement;
	while(pos!=NULL)
		{
		pElement=m_pCurve->GetNextElement(pos);
		if(pElement->IsPartialCurve())
			{
			AddPartial((CPartialCurve*)pElement);
			}
		}
	}

// Gère le bouton thickness et la construction de la courbe
// Rajoute un élément de courbe au point spécifié après vérification validité :
// Le point choisi est noir, 
// il est dans les limites choisies, 
// la courbe ne passe pas déjà par là.
void CGenesisDialog::OnEndPick(UINT wParam, LONG lParam)
	{
	if(NULL!=m_pOptDlg)
		{
		m_pOptDlg->SendMessage(WM_END_PICK,wParam,lParam);
		return;
		}

	if(!ActionConfirmed())
		{
		return;
		}
	CPoint* point=(CPoint*)lParam;
	CBmpManager* pManager=(m_pCoord->GetDocument())->GetBmpManager();
	PLPixel32 blackLevel=m_pCurve->GetBlackLevel();
	if(m_CheckThick)	// c'est le bouton thickness qui est enfoncé
		{
		if( !(pManager->PixelIsBlack(*point,blackLevel)) )
			{
			CString msg;
			msg.LoadString(IDS_NO_CURVE_HERE);
			MessageBox(msg,"CurveUnscan",MB_OK|MB_ICONINFORMATION);
			return;
			}
		CPoint topPoint=*point;
		CPoint bottomPoint=*point;
		BOOL oK1=pManager->FindCurve(topPoint,blackLevel,TRUE);
		BOOL oK2=pManager->FindCurve(bottomPoint,blackLevel,FALSE);
		if(!(oK1&&oK2))
			{
			return;
			}
		int thick=bottomPoint.y-topPoint.y;
		if(thick>32)
			{
			thick=32;
			}
		if(thick<1)
			{
			thick=1;
			}
		m_CheckThick=FALSE;
		m_CursorShape=kDefaultCursor;
		m_Thickness=thick;
		UpdateData(FALSE);
		m_pCurve->SetThickness(thick);
		m_pCurve->FillFromElements();
		CWnd* pWnd=GetParent();
		pWnd->InvalidateRgn(NULL);
		pWnd->PostMessage(WM_PAINT);
		return;
		}
	else if(m_CheckElement)	// C'est le bouton "Pick curve" qui est enfoncé
		{
		if( !(pManager->PixelIsBlack(*point,blackLevel)) )
			{
			CString msg;
			msg.LoadString(IDS_NO_CURVE_HERE);
			MessageBox(msg,"CurveUnscan",MB_OK|MB_ICONINFORMATION);
			return;
			}
		CLimit* pLeftLimit=m_pCurve->GetLeftLimit();
		CLimit* pRightLimit=m_pCurve->GetRightLimit();
		if( (pLeftLimit->HaveIncluded(*point))||(pRightLimit->HaveIncluded(*point)) )
			{
			CString msg;
			msg.LoadString(IDS_OUT_OF_LIMITS);
			MessageBox(msg,"CurveUnscan",MB_OK|MB_ICONINFORMATION);
			return;
			}
		CPoint borderPt=*point;
		pManager->FindCurve(borderPt,blackLevel,m_pCurve->GetTopFollow());
		POSITION pos=m_pCurve->GetHeadElementPosition();
		CCurveElement* pCurveElement;
		while(pos!=NULL)	
			{
			pCurveElement=m_pCurve->GetNextElement(pos);
			if(pCurveElement->HaveIncluded(borderPt))
				{
				CString msg;
				msg.LoadString(IDS_CURVE_ALREADY_EXISTS);
				MessageBox(msg,"CurveUnscan",MB_OK|MB_ICONINFORMATION);
				return;	
				}
			}
		BeginWaitCursor();
		CPartialCurve* pNewPartial=new CPartialCurve(m_pCurve);
		pNewPartial->SetPosition(*point);
		m_pCurve->AddElement(pNewPartial);	
		m_pCurve->Construct();
		m_pCurve->FillFromElements();
		m_GenesisListBox.ResetContent();
		FillListBox();
		CWnd* pWnd=GetParent();
		pWnd->InvalidateRgn(NULL);
		pWnd->PostMessage(WM_PAINT);
//		m_CheckElement=FALSE;
		UpdateData(FALSE);
		UpdateOKButton();
		EndWaitCursor();
		}
	}

void CGenesisDialog::OnCheckThick() 
	{
	// TODO: Add your control notification handler code here
	m_CheckThick=!m_CheckThick;
	m_CursorShape=(m_CheckThick)?kDrawLineCursor:kDefaultCursor;
	m_CheckElement=FALSE;
	UpdateData(FALSE);
	}

void CGenesisDialog::OnCheckElement() 
	{
	// TODO: Add your control notification handler code here
	m_CheckElement=!m_CheckElement;
	m_CursorShape=(m_CheckElement)?kDrawLineCursor:kDefaultCursor;
	m_CheckThick=FALSE;
	UpdateData(FALSE);
	}

void CGenesisDialog::OnChangeEditCurvename() 
// Mettre le bouton OK à jour
	{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	UpdateOKButton();
	}

BOOL CGenesisDialog::OKState()
// TRUE si ListBox et CurveName non vides
	{
	UpdateData(TRUE);
	BOOL flag=TRUE;
	if(m_GenesisListBox.GetCount()==0)
		{
		flag=FALSE;
		}
	if(m_CurveName.GetLength()==0)
		{
		flag=FALSE;
		}
	return flag;
	}

// Nothing to validate -> always TRUE
BOOL CGenesisDialog::DataValidation()
	{
	// Check that no other curve has the same name
	UpdateData(TRUE);

	return CheckCurveNameUnicity(m_pCurve,m_CurveName);

	}

// Met à jour le nom de la courbe
void CGenesisDialog::UpdateObjects()
	{
	UpdateData(TRUE);
	if(m_CurveName!=m_pCurve->GetName())
		{
		m_pCurve->SetName(m_CurveName);
		}
	}

// modifier la courbe en conséquence
void CGenesisDialog::OnChangeEditThickness() 
	{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	CEdit* pThickEdit=(CEdit*)GetDlgItem(IDC_EDIT_THICKNESS);
	if(GetFocus()==pThickEdit)
		{
		if(!ActionConfirmed())
			{
			UpdateData(FALSE);
			return;
			}
		UpdateData(TRUE);
		m_pCurve->SetThickness(m_Thickness);
		m_pCurve->Construct();
//		m_pCurve->FillFromElements();
		CWnd* pWnd=GetParent();
		pWnd->InvalidateRgn(NULL);
		pWnd->PostMessage(WM_PAINT);
		}
	}


BOOL CGenesisDialog::OnInitDialog() 
	{
	CConstructionDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN_THICKNESS))->SetRange(1,32);
	FillListBox();
	UpdateDeleteButton();
	CButton* pDistButton=static_cast<CButton*>(GetDlgItem(IDC_BUTTON_DASHDIST));
	pDistButton->EnableWindow(m_pCurve->IsDashed());
	CEdit* pEdit=static_cast<CEdit*>(GetDlgItem(IDC_EDIT_DISTMAX));
	pEdit->EnableWindow(m_pCurve->IsDashed());

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
	}

void CGenesisDialog::OnRadioTop() 
	{
	if(!ActionConfirmed())
		{
		UpdateData(FALSE);
		return;
		}
	UpdateData(TRUE);
	BOOL value=(m_Follow==0)?TRUE:FALSE;
	m_pCurve->SetTopFollow(value);
	m_pCurve->Construct();
	m_GenesisListBox.ResetContent();
	FillListBox();
	CWnd* pWnd=GetParent();
	pWnd->InvalidateRgn(NULL);
	pWnd->PostMessage(WM_PAINT);
	}

void CGenesisDialog::OnRadioBottom() 
	{
	if(!ActionConfirmed())
		{
		UpdateData(FALSE);
		return;
		}
	UpdateData(TRUE);
	BOOL value=(m_Follow==0)?TRUE:FALSE;
	m_pCurve->SetTopFollow(value);
	m_pCurve->Construct();
	m_GenesisListBox.ResetContent();
	FillListBox();
	CWnd* pWnd=GetParent();
	pWnd->InvalidateRgn(NULL);
	pWnd->PostMessage(WM_PAINT);
	}

BOOL CGenesisDialog::OnHelpInfo(HELPINFO* pHelpInfo) 
{
	// TODO: Add your message handler code here and/or call default
	
	return CConstructionDialog::OnHelpInfo(pHelpInfo);
}

bool CGenesisDialog::ActionConfirmed()
{
	bool result=true;
	if(m_pCurve->GetHandModification())
		{
		CString caption("CurveUnscan");
		CString text;
		text.LoadString(IDS_HAND_MODIFICATION_LOST);
		int reponse=MessageBox(text,caption,MB_YESNO);
		if(reponse!=IDYES)
			{
			result=false;
			}
		}
	return result;
}

void CGenesisDialog::OnAdvContinuousButton() 
{
	// TODO: Add your control notification handler code here
//	CContinuousAdvOptDlg dlg(m_pCurve);
//	dlg.DoModal();
	EnableWindow(FALSE);
	m_pOptDlg=new CContinuousAdvOptDlg(m_pCurve,this);
	m_pOptDlg->Create(IDD_CONTINUOUSOPTION_DIALOG);
}

void CGenesisDialog::OnOptDlgClosed(UINT wParam, LONG lParam)
{
	// set the good cursor
	m_CursorShape=(m_CheckThick|m_CheckElement)?kDrawLineCursor:kDefaultCursor;

	m_pOptDlg=NULL;
	EnableWindow(TRUE);
	UpdateData();
	SetFocus();


}

void CGenesisDialog::OnButtonDashdist() 
{
	// TODO: Add your control notification handler code here
	if(!ActionConfirmed())
		{
		UpdateData(FALSE);
		return;
		}
	EnableWindow(FALSE);
	m_pDashDistDialog=new CDashMaxDistDialog(this,m_nDashMaxDist);
	m_pDashDistDialog->Create(IDD_DASHDIST_DIALOG);	
}

void CGenesisDialog::OnApplyDashDist(UINT wParam, LONG lParam)
{
	BeginWaitCursor();
	m_nDashMaxDist=(int)wParam;
	m_pCurve->SetDashMaxDist(m_nDashMaxDist);
	m_pCurve->Construct();
	CUnscanDoc* pDoc=m_pSequence->GetDocument();
	pDoc->UpdateAllViews(NULL);
	UpdateData(FALSE);
	EndWaitCursor();
}

void CGenesisDialog::OnDashDistDlgClosed(UINT wParam, LONG lParam)
{
	m_pDashDistDialog=NULL;
	EnableWindow(TRUE);
	SetFocus();
}

void CGenesisDialog::OnRadioDashed() 
{
	// TODO: Add your control notification handler code here
	UpdateDashed();
}

void CGenesisDialog::OnRadioNotdashed() 
{
	// TODO: Add your control notification handler code here
	UpdateDashed();	
}

void CGenesisDialog::UpdateDashed()
{
	if(!ActionConfirmed())
		{
		UpdateData(FALSE);
		return;
		}
	BeginWaitCursor();
	UpdateData(TRUE);
	bool isDashed=(0==m_Dashed);
	bool oldValue=m_pCurve->SetDashed(isDashed);
	if(oldValue!=isDashed)
	{
		m_pCurve->Construct();
		CUnscanDoc* pDoc=m_pSequence->GetDocument();
		pDoc->UpdateAllViews(NULL);
	}
	CButton* pButton=static_cast<CButton*>(GetDlgItem(IDC_BUTTON_DASHDIST));
	pButton->EnableWindow(isDashed);
	CEdit* pEdit=static_cast<CEdit*>(GetDlgItem(IDC_EDIT_DISTMAX));
	pEdit->EnableWindow(isDashed);
	EndWaitCursor();
}
