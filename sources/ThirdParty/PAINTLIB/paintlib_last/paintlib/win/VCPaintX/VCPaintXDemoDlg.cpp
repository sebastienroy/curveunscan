// VCPaintXDemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "VCPaintXDemo.h"
#include "VCPaintXDemoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVCPaintXDemoDlg dialog

CVCPaintXDemoDlg::CVCPaintXDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CVCPaintXDemoDlg::IDD, pParent),
    MyPictureDecoder(__uuidof(PAINTXLib::PictureDecoder))

{
	//{{AFX_DATA_INIT(CVCPaintXDemoDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CVCPaintXDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CVCPaintXDemoDlg)
	DDX_Control(pDX, IDC_IMAGE1, m_Image);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CVCPaintXDemoDlg, CDialog)
	//{{AFX_MSG_MAP(CVCPaintXDemoDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDCANCEL, OnClose)
	ON_BN_CLICKED(ID_FILE_OPEN, OnFileOpen)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVCPaintXDemoDlg message handlers

BOOL CVCPaintXDemoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(false);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, true);			// Set big icon
	SetIcon(m_hIcon, false);		// Set small icon
	
	// TODO: Add extra initialization here
  m_Image.SetPicture( (IPictureDispPtr) MyPictureDecoder->LoadResPicture(IDR_LOGO) );
	
	return true;  // return true  unless you set the focus to a control
}

void CVCPaintXDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CVCPaintXDemoDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CVCPaintXDemoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CVCPaintXDemoDlg::OnClose() 
{
	// TODO: Add your control notification handler code here
    CDialog::EndDialog(0);	
}

void CVCPaintXDemoDlg::OnFileOpen() 
{
  CFileDialog dlg(true); // open dialog
  if (dlg.DoModal()==IDOK )
    LoadPictureTest(dlg.GetPathName ());
}

void CVCPaintXDemoDlg::LoadPictureTest ( CString strFilename )
{
  // for (int i; i < 1000; i++) // stress test

  try
  {
    m_Image.SetPicture( (IPictureDispPtr) MyPictureDecoder->LoadPicture((_bstr_t)strFilename) );
    m_Image.RedrawWindow ();
  } 
  catch (_com_error comerr) 
  { 
    HandleErrors(comerr); 
  }; 
};

void CVCPaintXDemoDlg::LoadResPictureTest ( int iResourceID )
{
  try
  {
    m_Image.SetPicture( (IPictureDispPtr) MyPictureDecoder->LoadResPicture(iResourceID) );
    m_Image.RedrawWindow ();
  } 
  catch (_com_error comerr) 
  { 
    HandleErrors(comerr); 
  }; 
};

void CVCPaintXDemoDlg::HandleErrors(_com_error comerr) 
{ 
    HRESULT hr = comerr.Error(); 
    char szDec[16];
    char szHex[16];

    itoa(hr, szHex, 16); 
    itoa(hr, szDec, 10); 
    CString tempString = "PaintX COM Error returned HRESULT:0x"; 
    tempString += szHex;
    tempString += "("; 
    tempString += szDec; 
    tempString += "): "; 
    
	tempString += "Severity:0x";
    itoa(HRESULT_SEVERITY(hr), szHex, 16);
    itoa(HRESULT_SEVERITY(hr), szDec, 10);
    tempString += szHex;
    tempString += "("; 
    tempString += szDec; 
    tempString += "), "; 
    
	tempString += "Facility:0x";
    itoa(HRESULT_FACILITY(hr), szHex, 16);
    itoa(HRESULT_FACILITY(hr), szDec, 10);
    tempString += szHex;
    tempString += "("; 
    tempString += szDec;
    tempString += "), "; 
    if (HRESULT_FACILITY(hr)==FACILITY_ITF)
	{
      // 3rd Party Errors: show the source and the description
	  tempString += "Source:";
	  tempString += comerr.Source();
	  tempString += ", Description:";
	  tempString += comerr.Description();
	}
	else
	{
      // MS Errors: show the ErrorMessage
	  tempString += "ErrorMessage:";
      tempString += comerr.ErrorMessage();
	}
    
	tempString += ", Code:0x";
    itoa(HRESULT_CODE(hr), szHex, 16);
    itoa(HRESULT_CODE(hr), szDec, 10);
    tempString += szHex;
    tempString += "("; 
    tempString += szDec; 
    tempString += ")\n"; 
    
    TRACE(tempString);
};    
