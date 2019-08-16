// PeriodDialog.cpp : implementation file
//

#include "stdafx.h"
#include "CurveUnscan.h"
#include "PeriodDialog.h"

#include <Dm/ContinuousResults.h>
#include <Dm/Axe.h>
#include <Dm/Curve.h>
#include <Dm/CoordSyst.h>

#include <HelpSystem/HelpFunctions.h>

#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPeriodDialog dialog


CPeriodDialog::CPeriodDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CPeriodDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPeriodDialog)
	m_PeriodLegend = _T("");
	m_FrequencyLegend = _T("");
	m_FirstValueLegend = _T("");
	m_strNSavedPoints = _T("");
	//}}AFX_DATA_INIT
}

CPeriodDialog::CPeriodDialog(CContinuousResults *pResults)
	:CDialog(CPeriodDialog::IDD, NULL)
	{
	m_pResults=pResults;
	}

void CPeriodDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPeriodDialog)
	DDX_Control(pDX, IDC_EDIT_FIRSTSAVEDVALUE, m_FirstValueEdit);
	DDX_Control(pDX, IDC_EDIT_FREQUENCY, m_FrequencyEdit);
	DDX_Control(pDX, IDC_EDIT_PERIOD, m_PeriodEdit);
	DDX_Text(pDX, IDC_EDIT_LEGEND_PERIOD, m_PeriodLegend);
	DDX_Text(pDX, IDC_EDIT_LEGEND_FREQUENCY, m_FrequencyLegend);
	DDX_Text(pDX, IDC_EDIT_LEGEND_FIRSTVALUE, m_FirstValueLegend);
	DDX_Text(pDX, IDC_STATIC_NBOFSAVEDPOINTS, m_strNSavedPoints);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPeriodDialog, CDialog)
	//{{AFX_MSG_MAP(CPeriodDialog)
	ON_EN_CHANGE(IDC_EDIT_PERIOD, OnChangeEditPeriod)
	ON_EN_CHANGE(IDC_EDIT_FREQUENCY, OnChangeEditFrequency)
	ON_EN_CHANGE(IDC_EDIT_FIRSTSAVEDVALUE, OnChangeEditFirstvalue)
	ON_WM_HELPINFO()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPeriodDialog message handlers

void CPeriodDialog::OnChangeEditPeriod() 
	{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	if(GetFocus()!=&m_PeriodEdit)
		{
		return;
		}
	CButton* pOKButton=(CButton*)GetDlgItem(IDOK);
	if(m_PeriodEdit.IsEmpty())
		{
		pOKButton->EnableWindow(FALSE);
		m_FrequencyEdit.Erase();
		m_dPeriod=0.0;
		}
	else
		{
		pOKButton->EnableWindow(TRUE);
		m_dPeriod=m_PeriodEdit.GetValue();
		if(m_dPeriod!=0)
			{
			m_FrequencyEdit.SetValue(1/m_dPeriod);
			}
		else
			{
			m_FrequencyEdit.Erase();
			}
		}
	UpdateNbOfSavedPoints();
	}

void CPeriodDialog::OnChangeEditFrequency() 
	{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	if(GetFocus()!=&m_FrequencyEdit)
		{
		return;
		}
	CButton* pOKButton=(CButton*)GetDlgItem(IDOK);
	if(m_FrequencyEdit.IsEmpty())
		{
		m_PeriodEdit.Erase();
		pOKButton->EnableWindow(FALSE);
		m_dPeriod=0.0;
		}
	else
		{
		pOKButton->EnableWindow(TRUE);
		double freq=m_FrequencyEdit.GetValue();
		if(freq!=0)
			{
			m_dPeriod=1/freq;
			m_PeriodEdit.SetValue(m_dPeriod);
			}
		else
			{
			m_dPeriod=0.0;
			m_PeriodEdit.Erase();
			}
		}
	UpdateNbOfSavedPoints();
	}

void CPeriodDialog::OnOK() 
	{
	// TODO: Add extra validation here

	CAxe* pAxe=((m_pResults->GetCurve())->GetCoordSyst())->GetXAxe();
	bool isLogarithmic=pAxe->GetLogarithmic();

	//--- Check value
	double firstValue=m_FirstValueEdit.GetValue();
	if( (isLogarithmic)&&(firstValue<=0))
		{
		CString msg;
		msg.LoadString(IDS_LOG_VALUE_GREATER_THAN_ZERO);
		MessageBox(msg,"CurveUnscan",MB_OK|MB_ICONINFORMATION);
		HighlightEdit(IDC_EDIT_FIRSTSAVEDVALUE);
		return;
		}

	//--- Check period
//	double periodValue=m_PeriodEdit.GetValue();
	double periodValue=m_dPeriod;
	if(periodValue<=0)
		{
		CString msg;
		msg.LoadString(IDS_PERIOD_GREATER_THAN_ZERO);
		MessageBox(msg,"CurveUnscan",MB_OK|MB_ICONINFORMATION);
		HighlightEdit(IDC_EDIT_PERIOD);
		return;
		}

	//--- Ask confirmation in the case of big curves
	double lastValue=m_pResults->GetLastValue();
	double range;
	if(isLogarithmic)
		{
		double logFirst=log(fabs(firstValue));
		double logLast=log(fabs(lastValue));
		range=fabs(logLast-logFirst);
		}
	else
		{
		range=fabs(lastValue-firstValue);
		}
	double dLines=range/periodValue;
	if(dLines>1000000)
	{
		AfxMessageBox(IDS_NBLINESTOOBIG,MB_OK|MB_ICONSTOP);
		HighlightEdit(IDC_EDIT_FREQUENCY);
		return;
	}
	int nLines=(int)dLines;
	if(nLines>=1000)
		{
		CString txt;
		txt.LoadString(IDS_CURVE_CONTAINS_N_LINES);
		CString msg;
		msg.Format(txt,nLines);
		if(IDYES!=MessageBox(msg,"CurvUnscan",MB_YESNO|MB_ICONQUESTION))
			{
			HighlightEdit(IDC_EDIT_FREQUENCY);
			return;
			}
		}

	m_pResults->SetFirstValue(firstValue);
	m_pResults->SetPeriod(periodValue);
	CDialog::OnOK();
	}


// Initialise la boîte de dialogue : définit les légendes, la valeur initiale de
//  m_FirstValue (limite la plus faible si pas déjà défini) et de la fréquence si 
//  déjà définie.
BOOL CPeriodDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CAxe* pAxe=((m_pResults->GetCurve())->GetCoordSyst())->GetXAxe();
	CString strUnit=pAxe->GetName();
	m_FirstValueLegend="( "+strUnit+" )";
	if(pAxe->GetLogarithmic())
		{
		CString strDecade;
		strDecade.LoadString(IDS_DECADE_UNIT);
		strUnit=strDecade+strUnit+CString(" )");
		}
	else
		{
		strUnit+=CString(" )");
		}
	m_PeriodLegend=CString("( ")+strUnit;
	m_FrequencyLegend=CString("( 1 / ")+strUnit;

	m_FirstValueEdit.SetValue(m_pResults->GetFirstValue());
	if(m_pResults->PeriodIsDefined())
		{
		m_dPeriod=m_pResults->GetPeriod();
		
		m_PeriodEdit.SetValue(m_dPeriod);
		m_FrequencyEdit.SetValue(1.0/m_dPeriod);
		}
	else
		{
		m_dPeriod=0;
		}
	if(m_PeriodEdit.IsEmpty())
		{
		CButton* pOKButton=(CButton*)GetDlgItem(IDOK);
		pOKButton->EnableWindow(FALSE);
		}
	UpdateData(FALSE);

	UpdateNbOfSavedPoints();

	m_FirstValueEdit.SetFocus();
	m_FirstValueEdit.SetSel(0,-1);
	
	return FALSE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CPeriodDialog::OnChangeEditFirstvalue() 
	{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	CButton* pOKButton=(CButton*)GetDlgItem(IDOK);
	if(m_FirstValueEdit.IsEmpty())
		{
		pOKButton->EnableWindow(FALSE);
		}
	else
		{
		pOKButton->EnableWindow(TRUE);
		}
	UpdateNbOfSavedPoints();
	}

BOOL CPeriodDialog::OnHelpInfo(HELPINFO* pHelpInfo) 
{
	// TODO: Add your message handler code here and/or call default
	CHelpFunctions::DisplayCtrlPopup(FromHandle((HWND)pHelpInfo->hItemHandle),
									pHelpInfo->MousePos,
									pHelpInfo->iCtrlId);
	return TRUE;
	
}

// Used after data validation problems
void CPeriodDialog::HighlightEdit(int nID)
{
	CEdit* pEdit=static_cast<CEdit*>(GetDlgItem(nID));
	pEdit->SetSel(0,-1);
	pEdit->SetFocus();
}

void CPeriodDialog::UpdateNbOfSavedPoints()
{
	int nLines=GetLinesNb();
	CString strNumber;
	if(nLines>=0)
	{
		strNumber.Format("%d",nLines);
	}
	else
	{
		strNumber.LoadString(IDS_ERROR);
	}
	CWnd *pLinesNbWnd=GetDlgItem(IDC_STATIC_NBOFSAVEDPOINTS);
	pLinesNbWnd->SetWindowText(strNumber);
}

int CPeriodDialog::GetLinesNb() const
{
	// check value presence
	if( (m_FirstValueEdit.IsEmpty())
		||(m_FrequencyEdit.IsEmpty())
		||(m_PeriodEdit.IsEmpty()) )
	{
		return 0;
	}

	// check value validity
	double dFirstValue=m_FirstValueEdit.GetValue();
	CAxe* pAxe=((m_pResults->GetCurve())->GetCoordSyst())->GetXAxe();
	bool isLogarithmic=pAxe->GetLogarithmic();

	if( (isLogarithmic)&&(dFirstValue<=0))
	{
		return 0;
	}
	if(m_dPeriod<=0)
	{
		return 0;
	}

	// everything is ok, compute value
	double lastValue=m_pResults->GetLastValue();
	double range;
	if(isLogarithmic)
		{
		double logFirst=log10(fabs(dFirstValue));
		double logLast=log10(fabs(lastValue));
		range=fabs(logLast-logFirst);
		}
	else
		{
		range=fabs(lastValue-dFirstValue);
		}
	double dLines=(range/m_dPeriod);
	int nLines=(dLines<1000000)?(int)dLines:-1;
	return nLines+1;
}
