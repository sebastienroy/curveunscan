// SplinePeriodDialog.cpp : implementation file
//

#include "stdafx.h"
#include "CurveUnscan.h"
#include "SplinePeriodDialog.h"

#include <Dm/SplineResults.h>
#include <Dm/SplineCurve.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSplinePeriodDialog dialog


CSplinePeriodDialog::CSplinePeriodDialog(CSplineResults* pResults, CWnd* pParent /*=NULL*/)
	: CDialog(CSplinePeriodDialog::IDD, pParent),
	m_pResults(pResults)
{
	//{{AFX_DATA_INIT(CSplinePeriodDialog)
	m_SavedPointsNb = m_pResults->GetPointsPerSegmentNb();
	m_strTotalNb = _T("");
	//}}AFX_DATA_INIT

}


void CSplinePeriodDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSplinePeriodDialog)
	DDX_Text(pDX, IDC_SPLINE_SAVED_POINTS_NB_EDIT, m_SavedPointsNb);
	DDV_MinMaxInt(pDX, m_SavedPointsNb, 1, 1000);
	DDX_Text(pDX, IDC_NB_SAVED_POINTS, m_strTotalNb);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSplinePeriodDialog, CDialog)
	//{{AFX_MSG_MAP(CSplinePeriodDialog)
	ON_EN_CHANGE(IDC_SPLINE_SAVED_POINTS_NB_EDIT, OnChangeSplineSavedPointsNbEdit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSplinePeriodDialog message handlers

void CSplinePeriodDialog::OnOK() 
{
	// TODO: Add extra validation here
	if(UpdateData(TRUE))
	{
		m_pResults->SetPointsPerSegmentNb(m_SavedPointsNb);
	}
	
	CDialog::OnOK();
}

void CSplinePeriodDialog::OnChangeSplineSavedPointsNbEdit() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	UpdateTotalNb();
}

void CSplinePeriodDialog::UpdateTotalNb()
{
	int nbTotal=0;
	CString strTmp;
	CWnd *pEdit=GetDlgItem(IDC_SPLINE_SAVED_POINTS_NB_EDIT);
	pEdit->GetWindowText(strTmp);
	int nb=atoi(strTmp);
	if( (nb>=0) && (nb<1000) )
	{
		CSplineCurve *pCurve=static_cast<CSplineCurve*>(m_pResults->GetCurve());
		nbTotal=nb*(pCurve->GetNodeCount()-1)+1;
	}
	else
	{
		nbTotal=0;
	}
	m_strTotalNb.Format("%d",nbTotal);
	CWnd *pStatic=GetDlgItem(IDC_NB_SAVED_POINTS);
	pStatic->SetWindowText(m_strTotalNb);
}

BOOL CSplinePeriodDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	UpdateTotalNb();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
