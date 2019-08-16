// SeparatorDialog.cpp : implementation file
//

#include "stdafx.h"
#include "CurveUnscan.h"
#include "SeparatorDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSeparatorDialog dialog


CSeparatorDialog::CSeparatorDialog(char cSeparator, CWnd* pParent /*=NULL*/)
	: CDialog(CSeparatorDialog::IDD, pParent),
	  m_cSeparator(cSeparator)
{
	//{{AFX_DATA_INIT(CSeparatorDialog)
	m_strOtherSeparator = _T("");
	m_nSeparatorRadio = -1;
	//}}AFX_DATA_INIT

	switch(m_cSeparator)
	{
	case '\t':
		m_nSeparatorRadio=0;
		break;
	case ';':
		m_nSeparatorRadio=1;
		break;
	case ',':
		m_nSeparatorRadio=2;
		break;
	case ' ':
		m_nSeparatorRadio=3;
		break;
	default:
		m_nSeparatorRadio=4;
		m_strOtherSeparator=CString(m_cSeparator);
	}
}


void CSeparatorDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSeparatorDialog)
	DDX_Text(pDX, IDC_EDIT_SEP_OTHER, m_strOtherSeparator);
	DDV_MaxChars(pDX, m_strOtherSeparator, 1);
	DDX_Radio(pDX, IDC_RADIO_SEP_TAB, m_nSeparatorRadio);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSeparatorDialog, CDialog)
	//{{AFX_MSG_MAP(CSeparatorDialog)
	ON_EN_CHANGE(IDC_EDIT_SEP_OTHER, OnChangeEditSepOther)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSeparatorDialog message handlers


char CSeparatorDialog::GetSeparator() const
{
	return m_cSeparator;
}

void CSeparatorDialog::OnOK() 
{
	// TODO: Add extra validation here

	if(!UpdateData(TRUE))	// check that not more than one character in edit ctrl
	{
		return;
	}
	switch(m_nSeparatorRadio)
	{
	case 0:
		m_cSeparator='\t';
		break;
	case 1:
		m_cSeparator=';';
		break;
	case 2:
		m_cSeparator=',';
		break;
	case 3:
		m_cSeparator=' ';
		break;
	case 4:
		if(m_strOtherSeparator.GetLength()<1)
		{
			AfxMessageBox(IDS_SEPARATOR_ISEMPTY,MB_OK|MB_ICONSTOP);
			CEdit *pEdit=static_cast<CEdit*>(GetDlgItem(IDC_EDIT_SEP_OTHER));
			pEdit->SetFocus();
			return;
		}
		m_cSeparator=m_strOtherSeparator[0];
		break;
	default:
		m_cSeparator='\t';
	}
	
	CDialog::OnOK();
}

void CSeparatorDialog::OnChangeEditSepOther() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_nSeparatorRadio=4;
	UpdateData(FALSE);
}
