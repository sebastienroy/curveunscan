// DensitoPeriodDialog.cpp : implementation file
//

#include "stdafx.h"
#include "CurveUnscan.h"
#include "DensitoPeriodDialog.h"

#include <Dm/DensityCurve.h>
#include <Dm/DensityResults.h>
#include <Dm/CoordSyst.h>
#include <Dm/Axe.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDensitoPeriodDialog dialog


CDensitoPeriodDialog::CDensitoPeriodDialog(CDensityResults* pResults,
										   CWnd* pParent /*=NULL*/)
	: CDialog(CDensitoPeriodDialog::IDD, pParent),
	m_pResults(pResults),
	m_pBackupResults(static_cast<CDensityResults*>(pResults->Clone()))
{
	//{{AFX_DATA_INIT(CDensitoPeriodDialog)
	m_nDisplayedCoord = -1;
	m_strUnitX = _T("");
	m_strUnitY = _T("");
	m_strSavedNb = _T("");
	//}}AFX_DATA_INIT


	// Units
	CAxe *pXAxis=m_pResults->GetCurve()->GetCoordSyst()->GetXAxe();
	if(pXAxis->GetLogarithmic())
	{
		m_strUnitX.LoadString(IDS_DECADE_UNIT);
	}
	m_strUnitX+=pXAxis->GetName();

	CAxe *pYAxis=m_pResults->GetCurve()->GetCoordSyst()->GetYAxe();
	if(pYAxis->GetLogarithmic())
	{
		m_strUnitY.LoadString(IDS_DECADE_UNIT);
	}
	m_strUnitY+=pYAxis->GetName();

	// display
	m_nDisplayedCoord=(int)m_pResults->GetDisplayKind();

	// bounds
	m_pResults->GetXRange(m_dMinX,m_dMaxX);
	m_pResults->GetYRange(m_dMinY,m_dMaxY);


}


void CDensitoPeriodDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDensitoPeriodDialog)
	DDX_Control(pDX, IDC_EDIT_YMIN, m_MinYEdit);
	DDX_Control(pDX, IDC_EDIT_XMIN, m_MinXEdit);
	DDX_Control(pDX, IDC_EDIT_YMAX, m_MaxYEdit);
	DDX_Control(pDX, IDC_EDIT_XMAX, m_MaxXEdit);
	DDX_Control(pDX, IDC_EDIT_YFIRST, m_FirstYEdit);
	DDX_Control(pDX, IDC_EDIT_XFIRST, m_FirstXEdit);
	DDX_Control(pDX, IDC_EDIT_YPERIOD, m_PeriodYEdit);
	DDX_Control(pDX, IDC_EDIT_YFREQ, m_FreqYEdit);
	DDX_Control(pDX, IDC_EDIT_XPERIOD, m_PeriodXEdit);
	DDX_Control(pDX, IDC_EDIT_XFREQ, m_FreqXEdit);
	DDX_Radio(pDX, IDC_RADIO_DISP_X, m_nDisplayedCoord);
	DDX_Text(pDX, IDC_EDIT_XUNIT, m_strUnitX);
	DDX_Text(pDX, IDC_EDIT_YUNIT, m_strUnitY);
	DDX_Text(pDX, IDC_NB_SAVED_POINTS, m_strSavedNb);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDensitoPeriodDialog, CDialog)
	//{{AFX_MSG_MAP(CDensitoPeriodDialog)
	ON_BN_CLICKED(IDC_RADIO_DISP_X, OnRadioDispX)
	ON_BN_CLICKED(IDC_RADIO_DISP_Y, OnRadioDispY)
	ON_BN_CLICKED(IDC_RADIO_DISP_BOTH, OnRadioDispBoth)
	ON_EN_CHANGE(IDC_EDIT_XFIRST, OnChangeEditXfirst)
	ON_EN_CHANGE(IDC_EDIT_YFIRST, OnChangeEditYfirst)
	ON_EN_CHANGE(IDC_EDIT_XPERIOD, OnChangeEditXperiod)
	ON_EN_CHANGE(IDC_EDIT_YPERIOD, OnChangeEditYperiod)
	ON_EN_CHANGE(IDC_EDIT_XFREQ, OnChangeEditXfreq)
	ON_EN_CHANGE(IDC_EDIT_YFREQ, OnChangeEditYfreq)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDensitoPeriodDialog message handlers

BOOL CDensitoPeriodDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	// display choice
	CWnd *pDispXRadio=GetDlgItem(IDC_RADIO_DISP_X);
	CWnd *pDispYRadio=GetDlgItem(IDC_RADIO_DISP_Y);
	CWnd *pDispBothRadio=GetDlgItem(IDC_RADIO_DISP_BOTH);
	if(!m_pResults->IsXValid())
	{
		pDispXRadio->EnableWindow(false);
		pDispBothRadio->EnableWindow(false);
	}
	else if(!m_pResults->IsYValid())
	{
		pDispYRadio->EnableWindow(false);
		pDispBothRadio->EnableWindow(false);
	}

	DensitoDisplayKind displayKind=m_pResults->GetDisplayKind();

	// bounds
	m_MinXEdit.SetValue(m_dMinX);
	m_MaxXEdit.SetValue(m_dMaxX);
	m_MinYEdit.SetValue(m_dMinY);
	m_MaxYEdit.SetValue(m_dMaxY);


	UpdateAllValues();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CDensitoPeriodDialog::EnableX(BOOL bEnable)
{
	m_FirstXEdit.EnableWindow(bEnable);
	m_PeriodXEdit.EnableWindow(bEnable);
	m_FreqXEdit.EnableWindow(bEnable);
	if(FALSE==bEnable)
	{
		m_FirstXEdit.Erase();
		m_FreqXEdit.Erase();
		m_PeriodXEdit.Erase();
	}
}


void CDensitoPeriodDialog::EnableY(BOOL bEnable)
{
	m_FirstYEdit.EnableWindow(bEnable);
	m_PeriodYEdit.EnableWindow(bEnable);
	m_FreqYEdit.EnableWindow(bEnable);
	if(FALSE==bEnable)
	{
		m_FirstYEdit.Erase();
		m_FreqYEdit.Erase();
		m_PeriodYEdit.Erase();
	}

}

void CDensitoPeriodDialog::UpdateValues(CWnd *pCtrl/*=NULL*/)
{
	DensitoDisplayKind displayKind=m_pResults->GetDisplayKind();
	// fill values

	if(kYdisplay!=displayKind)
	{
		if(pCtrl!=&m_FirstXEdit) m_FirstXEdit.SetValue(m_pResults->GetFirstX());
		if(m_pResults->IsPeriodDefined())
		{
			double dPeriod=m_pResults->GetXPeriod();
			if(pCtrl!=&m_PeriodXEdit) m_PeriodXEdit.SetValue(dPeriod);
			if(pCtrl!=&m_FreqXEdit) m_FreqXEdit.SetValue(1.0/dPeriod);
		}
		else
		{
			if(pCtrl!=&m_PeriodXEdit) m_PeriodXEdit.Erase();
			if(pCtrl!=&m_FreqXEdit) m_FreqXEdit.Erase();
		}
	}

	if(kXdisplay!=displayKind)
	{
		if(pCtrl!=&m_FirstYEdit) m_FirstYEdit.SetValue(m_pResults->GetFirstY());
		if(m_pResults->IsPeriodDefined())
		{
			double dPeriod=m_pResults->GetYPeriod();
			if(pCtrl!=&m_PeriodYEdit) m_PeriodYEdit.SetValue(dPeriod);
			if(pCtrl!=&m_FreqYEdit) m_FreqYEdit.SetValue(1.0/dPeriod);
		}
		else
		{
			if(pCtrl!=&m_PeriodYEdit) m_PeriodYEdit.Erase();
			if(pCtrl!=&m_FreqYEdit) m_FreqYEdit.Erase();
		}
	}

	// Nb of saved points
	int nSaved=m_pResults->GetNbOfSavedPoints();
	CString strSaved;
	if(nSaved<0)
	{
		strSaved.LoadString(IDS_ERROR);
	}
	else
	{
		strSaved.Format("%d",nSaved);
	}
	CWnd *pSavedNbCtrl=GetDlgItem(IDC_NB_SAVED_POINTS);
	pSavedNbCtrl->SetWindowText(strSaved);

	// Ok button state
	CWnd* pOKButton=GetDlgItem(IDOK);
	pOKButton->EnableWindow(m_pResults->IsPeriodDefined());

}

void CDensitoPeriodDialog::UpdateAllValues(CWnd *pCtrl/*=NULL*/)
{
	DensitoDisplayKind displayKind=m_pResults->GetDisplayKind();

	// enable parts
	if(kXdisplay==displayKind)
	{
		EnableX(TRUE);
		EnableY(FALSE);
	}
	else if(kYdisplay==displayKind)
	{
		EnableX(FALSE);
		EnableY(TRUE);
	}
	else
	{
		EnableX(TRUE);
		EnableY(TRUE);
	}

	UpdateValues(pCtrl);
}

void CDensitoPeriodDialog::OnRadioDispX() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	m_pResults->SetDisplayKind((DensitoDisplayKind)m_nDisplayedCoord);	
	UpdateAllValues();

	UpdateData(FALSE);
}

void CDensitoPeriodDialog::OnRadioDispY() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	m_pResults->SetDisplayKind((DensitoDisplayKind)m_nDisplayedCoord);	
	UpdateAllValues();

	UpdateData(FALSE);
	
}

void CDensitoPeriodDialog::OnRadioDispBoth() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	m_pResults->SetDisplayKind((DensitoDisplayKind)m_nDisplayedCoord);	
	UpdateAllValues();

	UpdateData(FALSE);
	
}

void CDensitoPeriodDialog::OnChangeEditXfirst() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	if(GetFocus()!=&m_FirstXEdit)
	{
		return;
	}

	if(!m_FirstXEdit.IsEmpty())
	{
		m_pResults->SetFirstX(m_FirstXEdit.GetValue());
	}

	UpdateAllValues(&m_FirstXEdit);

//	UpdateData(FALSE);
}

void CDensitoPeriodDialog::OnChangeEditYfirst() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	if(GetFocus()!=&m_FirstYEdit)
	{
		return;
	}

	if(!m_FirstYEdit.IsEmpty())
	{
		m_pResults->SetFirstY(m_FirstYEdit.GetValue());
	}

	UpdateAllValues(&m_FirstYEdit);

//	UpdateData(FALSE);	
}

void CDensitoPeriodDialog::OnChangeEditXperiod() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	
	if(GetFocus()!=&m_PeriodXEdit)
	{
		return;
	}

	if( (m_PeriodXEdit.IsEmpty()) || (0==m_PeriodXEdit.GetValue()) )
	{
		m_pResults->UndefPeriod();
	}
	else
	{
		m_pResults->SetXPeriod(m_PeriodXEdit.GetValue());
	}

	UpdateAllValues(&m_PeriodXEdit);

}

void CDensitoPeriodDialog::OnChangeEditYperiod() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	
	if(GetFocus()!=&m_PeriodYEdit)
	{
		return;
	}

	if( (m_PeriodYEdit.IsEmpty()) || (0==m_PeriodYEdit.GetValue()) )
	{
		m_pResults->UndefPeriod();
	}
	else
	{
		m_pResults->SetYPeriod(m_PeriodYEdit.GetValue());
	}

	UpdateAllValues(&m_PeriodYEdit);

}

void CDensitoPeriodDialog::OnChangeEditXfreq() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	if(GetFocus()!=&m_FreqXEdit)
	{
		return;
	}

	if( (m_FreqXEdit.IsEmpty()) || (0==m_FreqXEdit.GetValue()) )
	{
		m_pResults->UndefPeriod();
	}
	else
	{
		m_pResults->SetXPeriod(1.0/m_FreqXEdit.GetValue());
	}

	UpdateAllValues(&m_FreqXEdit);
	
}

void CDensitoPeriodDialog::OnChangeEditYfreq() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	if(GetFocus()!=&m_FreqYEdit)
	{
		return;
	}

	if( (m_FreqYEdit.IsEmpty()) || (0==m_FreqYEdit.GetValue()) )
	{
		m_pResults->UndefPeriod();
	}
	else
	{
		m_pResults->SetYPeriod(1.0/m_FreqYEdit.GetValue());
	}

	UpdateAllValues(&m_FreqYEdit);	
}

void CDensitoPeriodDialog::OnOK() 
{
	// TODO: Add extra validation here

	// Check range
	if( (kYdisplay!=m_pResults->GetDisplayKind())
		&&(m_pResults->IsXPeriodUsed()))
	{
		if( (m_FirstXEdit.GetValue()<m_MinXEdit.GetValue())
			||(m_FirstXEdit.GetValue()>m_MaxXEdit.GetValue()) )
		{
			CString msg;
			msg.LoadString(IDS_VALUE_OUTSIDE_RANGE);
			MessageBox(msg,"CurveUnscan",MB_OK|MB_ICONINFORMATION);
			m_FirstXEdit.SetFocus();
			m_FirstXEdit.SetSel(0,-1);
			return;
		}
	}
	else
	{
		if( (m_FirstYEdit.GetValue()<m_MinYEdit.GetValue())
			||(m_FirstYEdit.GetValue()>m_MaxYEdit.GetValue()) )
		{
			CString msg;
			msg.LoadString(IDS_VALUE_OUTSIDE_RANGE);
			MessageBox(msg,"CurveUnscan",MB_OK|MB_ICONINFORMATION);
			m_FirstYEdit.SetFocus();
			m_FirstYEdit.SetSel(0,-1);
			return;
		}
	}

	// check nb of saved values
	if( m_pResults->GetNbOfSavedPoints()<0)
	{
		CString msg;
		msg.LoadString(IDS_NBLINESTOOBIG);
		MessageBox(msg,"CurveUnscan",MB_OK|MB_ICONINFORMATION);
		if( (kYdisplay!=m_pResults->GetDisplayKind())
			&&(m_pResults->IsXPeriodUsed()))
		{
			m_PeriodXEdit.SetFocus();
			m_PeriodXEdit.SetSel(0,-1);
		}
		else
		{
			m_PeriodYEdit.SetFocus();
			m_PeriodYEdit.SetSel(0,-1);
		}
		return;
	}
	
	delete m_pBackupResults;
	m_pBackupResults=NULL;

	CDialog::OnOK();
}

void CDensitoPeriodDialog::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CCurve *pCurve=m_pResults->GetCurve();
	pCurve->SetResults(m_pBackupResults);

	CDialog::OnCancel();
}

