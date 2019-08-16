// SorryDlg.cpp : implementation file
//

#include "stdafx.h"
#include "licencemanaging.h"
#include "SorryDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSorryDlg dialog


CSorryDlg::CSorryDlg(CString strID, CWnd* pParent /*=NULL*/)
	: CDialog(CSorryDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSorryDlg)
	m_strProductID = _T("");
	//}}AFX_DATA_INIT
	m_strProductID="ProductID : ";
	m_strProductID+=strID;
}


void CSorryDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSorryDlg)
	DDX_Text(pDX, IDC_STATIC_PRODUCTID, m_strProductID);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSorryDlg, CDialog)
	//{{AFX_MSG_MAP(CSorryDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSorryDlg message handlers
