// SaveCurveDialog.cpp : implementation file
//

#include "stdafx.h"
#include "CurveUnscan.h"
#include "UnscanDoc.h"
#include "SaveCurveDialog.h"
#include "PeriodDialog.h"
#include "DensitoPeriodDialog.h"
#include "SplinePeriodDialog.h"
#include "PreviewDialog.h"
#include "StringResultDumper.h"
#include "SeparatorDialog.h"

#include <Dm/Results.h>
#include <Dm/Curve.h>
#include <Dm/ContinuousResults.h>
#include <Dm/DiscreteResults.h>
#include <Dm/DensityResults.h>
#include <Dm/SplineResults.h>
#include <Dm/CoordSyst.h>
#include <Dm/BmpManager.h>

#include <HelpSystem/HelpFunctions.h>
#include <Utilities/UnscanException.h>
#include <SettingsManagement/SettingsManager.h>
#include <LicenceManaging/LicenceManager.h>

#include <list>
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSaveCurveDialog dialog


CSaveCurveDialog::CSaveCurveDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CSaveCurveDialog::IDD, pParent)
	{
	//{{AFX_DATA_INIT(CSaveCurveDialog)
	//}}AFX_DATA_INIT

	CSettingsManager *pSettings=CSettingsManager::GetInstance();
	m_cSeparator=(NULL==pSettings)?'\t':pSettings->GetExportColumnSeparator();
	}

CSaveCurveDialog::CSaveCurveDialog(CUnscanDoc *pDoc)
	: CDialog(CSaveCurveDialog::IDD,NULL)
	{
	m_pDoc=pDoc;

	CSettingsManager *pSettings=CSettingsManager::GetInstance();
	m_cSeparator=(NULL==pSettings)?'\t':pSettings->GetExportColumnSeparator();
	}

void CSaveCurveDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSaveCurveDialog)
	DDX_Control(pDX, IDC_TOSAVE_LIST, m_ToSaveLB);
	DDX_Control(pDX, IDC_AVAIL_LIST, m_AvailableLB);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSaveCurveDialog, CDialog)
	//{{AFX_MSG_MAP(CSaveCurveDialog)
	ON_BN_CLICKED(IDC_REMOVE_BUTTON, OnRemoveButton)
	ON_BN_CLICKED(IDC_ADD_BUTTON, OnAddButton)
	ON_LBN_SELCHANGE(IDC_TOSAVE_LIST, OnSelchangeTosaveList)
	ON_LBN_DBLCLK(IDC_TOSAVE_LIST, OnDblclkTosaveList)
	ON_LBN_SELCHANGE(IDC_AVAIL_LIST, OnSelchangeAvailList)
	ON_LBN_DBLCLK(IDC_AVAIL_LIST, OnDblclkAvailList)
	ON_NOTIFY(UDN_DELTAPOS, IDC_ORDER_SPIN, OnDeltaposOrderSpin)
	ON_BN_CLICKED(IDC_PREVIEW_BUTTON, OnPreviewButton)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_EXPORTFORMAT_BUTTON, OnExportformatButton)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSaveCurveDialog message handlers

void CSaveCurveDialog::OnRemoveButton() 
	{
	// TODO: Add your control notification handler code here
	int index=m_ToSaveLB.GetCurSel();
	if(index==LB_ERR)
		{
		return;
		}
	CResults* pResults=(CResults*)m_ToSaveLB.GetItemDataPtr(index);
	if((int)pResults==-1)
		{
		return;
		}
	CCurve* pCurve=pResults->GetCurve();
	int index2=m_AvailableLB.AddString(pCurve->GetName());
	if((index2==LB_ERR)||(index2==LB_ERRSPACE))
		{
		return;
		}
	m_AvailableLB.SetItemDataPtr(index2,pCurve);
	m_ToSaveLB.DeleteString(index);
	UpdateButtons();
	}

void CSaveCurveDialog::OnAddButton() 
	{
	// TODO: Add your control notification handler code here
	int index=m_AvailableLB.GetCurSel();
	if(index==LB_ERR)
		{
		return;
		}
	AddCurve(index);	
	UpdateButtons();
	}

void CSaveCurveDialog::OnSelchangeTosaveList() 
	{
	// TODO: Add your control notification handler code here
	UpdateButtons();
	}

void CSaveCurveDialog::OnDblclkTosaveList() 
{
	// TODO: Add your control notification handler code here
	int index=m_ToSaveLB.GetCurSel();
	if(index==LB_ERR)
	{
		return;
	}
	CResults* pResults=(CResults*)m_ToSaveLB.GetItemDataPtr(index);
	if((int)pResults==-1)
	{
		return;
	}
	CContinuousResults *pContResults=dynamic_cast<CContinuousResults*>(pResults);
	CDensityResults *pDensResults=dynamic_cast<CDensityResults*>(pResults);
	CSplineResults *pSplineResults=dynamic_cast<CSplineResults*>(pResults);
	if(NULL!=pContResults)
	{
		CPeriodDialog periodDialog((CContinuousResults*)pResults);
		if( (periodDialog.DoModal())==IDOK)
		{
			BeginWaitCursor();
			pResults->Construct();
			EndWaitCursor();
		}
	}
	else if(NULL!=pDensResults)
	{
		CDensitoPeriodDialog periodDialog(pDensResults);
		if(periodDialog.DoModal()==IDOK)
		{
			BeginWaitCursor();
			pResults->Construct();
			EndWaitCursor();
		}		
	}
	else if(NULL!=pSplineResults)
	{
		CSplinePeriodDialog periodDialog(pSplineResults);
		if(periodDialog.DoModal()==IDOK)
		{
			BeginWaitCursor();
			pResults->Construct();
			EndWaitCursor();
		}		
	}

}

void CSaveCurveDialog::OnSelchangeAvailList() 
	{
	// TODO: Add your control notification handler code here
	UpdateButtons();
	}

void CSaveCurveDialog::OnDblclkAvailList() 
	{
	// TODO: Add your control notification handler code here
	int index=m_AvailableLB.GetCurSel();
	if(index==LB_ERR)
		{
		return;
		}
	AddCurve(index);
	UpdateButtons();
	}


BOOL CSaveCurveDialog::OnInitDialog() 
	{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CCoordSyst* pCoord;
	CCurve* pCurve;
	int nIndex;
	POSITION coordPos=m_pDoc->GetHeadCoordSystPosition();
	POSITION curvePos;
	while(coordPos!=NULL)
		{
		pCoord=m_pDoc->GetNextCoordSyst(coordPos);
		curvePos=pCoord->GetHeadCurvePosition();
		while(curvePos!=NULL)
			{
			pCurve=pCoord->GetNextCurve(curvePos);
			nIndex=m_AvailableLB.AddString(pCurve->GetName());
			m_AvailableLB.SetItemDataPtr(nIndex,pCurve);
			}
		}
	CButton* pAddButton=(CButton*)GetDlgItem(IDC_ADD_BUTTON);
	pAddButton->EnableWindow(FALSE);
	CButton* pRemoveButton=(CButton*)GetDlgItem(IDC_REMOVE_BUTTON);
	pRemoveButton->EnableWindow(FALSE);
	CButton* pPreviewButton=(CButton*)GetDlgItem(IDC_PREVIEW_BUTTON);
	pPreviewButton->EnableWindow(FALSE);
//	m_Spin.SetRange(0,31);
	UpdateButtons();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
	}

BOOL CSaveCurveDialog::UpdateButtons()
	{
	BOOL result=FALSE;
	if((m_ToSaveLB.GetCount())>0)
		{
		result=TRUE;
		}
	CButton* pOKButton=(CButton*)GetDlgItem(IDOK);
	CButton* pPreviewButton=(CButton*)GetDlgItem(IDC_PREVIEW_BUTTON);
	pOKButton->EnableWindow(result);
	pPreviewButton->EnableWindow(result);
//	return result;

	CButton* pAddButton=(CButton*)GetDlgItem(IDC_ADD_BUTTON);
	BOOL enableAdd=TRUE;
	if((m_AvailableLB.GetCurSel())==LB_ERR)
		{
		enableAdd=FALSE;
		}
	pAddButton->EnableWindow(enableAdd);

	CButton* pRemoveButton=(CButton*)GetDlgItem(IDC_REMOVE_BUTTON);
	BOOL enableRemove=TRUE;
	if((m_ToSaveLB.GetCurSel())==LB_ERR)
		{
		enableRemove=FALSE;
		}
	pRemoveButton->EnableWindow(enableRemove);	

	return TRUE;
	}

void CSaveCurveDialog::AddCurve(int nIndex)
// Ajoute une courbe à la liste de celles qu'il faut enregistrer
{
	CCurve* pCurve=(CCurve*)m_AvailableLB.GetItemDataPtr(nIndex);
	CResults* pResults=pCurve->GetResults();

	CContinuousResults *pContinuousResults=dynamic_cast<CContinuousResults*>(pResults);
	CDiscreteResults *pDiscreteResults=dynamic_cast<CDiscreteResults*>(pResults);
	CDensityResults *pDensityResults=dynamic_cast<CDensityResults*>(pResults);
	CSplineResults *pSplineResults=dynamic_cast<CSplineResults*>(pResults);


	if(NULL!=pContinuousResults)
	{
		
		CPeriodDialog periodDialog(pContinuousResults);
		if(periodDialog.DoModal()!=IDOK)
		{
			return;
		}		
	}
	else if(NULL!=pDiscreteResults)
	{
		// nothing to do;
	}
	else if(NULL!=pDensityResults)
	{
		CDensitoPeriodDialog periodDialog(pDensityResults);
		if(periodDialog.DoModal()!=IDOK)
		{
			return;
		}		
	}
	else if(NULL!=pSplineResults)
	{
		CSplinePeriodDialog splineDlg(pSplineResults);
		if(splineDlg.DoModal()!=IDOK)
		{
			return;
		}		
	}
	else
	{
#if defined(_DEBUG)
		MessageBox("Error : Unexpected result type!");
#endif
	}

	BeginWaitCursor();
	pResults->Construct();
	int index=m_ToSaveLB.AddString(pCurve->GetName());
	m_ToSaveLB.SetItemDataPtr(index,pResults);
	m_AvailableLB.DeleteString(nIndex);
	UpdateButtons();
	EndWaitCursor();
}

void CSaveCurveDialog::OnDeltaposOrderSpin(NMHDR* pNMHDR, LRESULT* pResult) 
	{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here
	
	int updown=pNMUpDown->iDelta;
	*pResult = 0;		// C'est quoi ça?
	int initIndex=m_ToSaveLB.GetCurSel();
	if(initIndex==LB_ERR)
		{
		return;
		}
	int min=0;
	int max=m_ToSaveLB.GetCount()-1;
	if( ((initIndex+updown)<min)||((initIndex+updown)>max) )
		{
		return;
		}
	CResults* pResults=(CResults*)m_ToSaveLB.GetItemDataPtr(initIndex);
	if((int)pResults==-1)
		{
		return;
		}
	m_ToSaveLB.DeleteString(initIndex);
	CString str=pResults->GetCurve()->GetName();
	int newIndex=m_ToSaveLB.InsertString(initIndex+updown,str);
	m_ToSaveLB.SetItemDataPtr(newIndex,pResults);
	m_ToSaveLB.SetFocus();
	m_ToSaveLB.SetCurSel(newIndex);
	}

void CSaveCurveDialog::OnCancel() 
	{
	// TODO: Add extra cleanup here
	CDialog::OnCancel();
	}

void CSaveCurveDialog::OnOK() 
	{
	// TODO: Add extra validation here

	//--- check rights
	RegistrationStateEnum registrState=kNoRight;
	CLicenceManager &licenceManager=CLicenceManager::GetInstance();
	if( !licenceManager.HaveRightToExport() )
	{
		return;
	}
	registrState=licenceManager.GetRegistrationState();
	if((kNoRight==registrState)||(kInstallPb==registrState))
	{
		return;
	}
	//complement test
	if((kRegistered!=registrState)&&(kUnderEvaluation!=registrState))
	{
		return;
	}
	
	//--- Do the job
	ConstructResultList();
	CDialog::OnOK();
	}

CString* CSaveCurveDialog::GetStrBuffer()
	{
	return &m_StrBuffer;
	}

void CSaveCurveDialog::ConstructResultList()
	{
	m_pResultsList.clear();
	for(int counter=0;counter<m_ToSaveLB.GetCount();counter++)
		{
		CResults* pResults=(CResults*)m_ToSaveLB.GetItemDataPtr(counter);
		if((int)pResults!=-1)
			{
			m_pResultsList.push_back(pResults);
			}
		}
	}




void CSaveCurveDialog::OnPreviewButton() 
// Construit le tampon de façon adéquate pour la prévisualisation.
// Affiche le dialogue de prévisualisation.
	{
	// TODO: Add your control notification handler code here
	ConstructResultList();
	CPreviewDialog dlg;
	try
		{
		BeginWaitCursor();
		CStringResultDumper dumper(&m_pResultsList,dlg.m_PreviewString,10,14);
		dumper.Dump();
		EndWaitCursor();
		dlg.DoModal();
		}
	catch(CUnscanException& err)
		{
		EndWaitCursor();
		CString msg=err.GetMessage();
		MessageBox(msg,"CurveUnscan",MB_OK|MB_ICONSTOP);
		}
	catch(...)
		{
		EndWaitCursor();
		CString msg="Error when trying to build the preview.";
		MessageBox(msg,"CurveUnscan",MB_OK|MB_ICONSTOP);
		}
	}

BOOL CSaveCurveDialog::OnHelpInfo(HELPINFO* pHelpInfo) 
{
	// TODO: Add your message handler code here and/or call default
	
	CHelpFunctions::DisplayCtrlPopup(FromHandle((HWND)pHelpInfo->hItemHandle),
									pHelpInfo->MousePos,
									pHelpInfo->iCtrlId);
	return TRUE;
}

list<CResults*>* CSaveCurveDialog::GetResultsList()
{
	return &m_pResultsList;
}

void CSaveCurveDialog::OnExportformatButton() 
{
	// TODO: Add your control notification handler code here
	CSeparatorDialog dlg(m_cSeparator);
	if(IDOK==dlg.DoModal())
	{
		m_cSeparator=dlg.GetSeparator();
	}
}

char CSaveCurveDialog::GetSeparator() const
{
	return m_cSeparator;
}
