// CodeGenerationDlg.h : header file
//

#if !defined(AFX_CODEGENERATIONDLG_H__041728E7_38F4_11D5_935E_C0FE45E14079__INCLUDED_)
#define AFX_CODEGENERATIONDLG_H__041728E7_38F4_11D5_935E_C0FE45E14079__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include <set>
using namespace std;

/////////////////////////////////////////////////////////////////////////////
// CCodeGenerationDlg dialog

class CCoder;

class CCodeGenerationDlg : public CDialog
{
// Construction
public:
	CCodeGenerationDlg(CString strCodeKey, CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CCodeGenerationDlg)
	enum { IDD = IDD_CODEGENERATION_DIALOG };
	CComboBox	m_Version_ComboBox;
	CString	m_String;
	CString	m_StrCompany;
	CString	m_StrName;
	CString	m_StrRegistration;
	CString	m_strChecksum;
	CString	m_strFilename;
	CString	m_strExtension;
	int		m_nLanguage;
	CString	m_strLicenceText;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCodeGenerationDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:
	CCoder* GetCoderInstance();

protected:
	void fillLicenceText();
	void ShowUsage();
	void FillDefaultComboBox();
	void FillComboBox();
	CString m_strCodeKey;
	HICON m_hIcon;
	set<CString> m_V1Serials;
	set<CString> m_V2Serials;
	

	// Generated message map functions
	//{{AFX_MSG(CCodeGenerationDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnDecode();
	afx_msg void OnEncode();
	afx_msg void OnButtonCheckRegistration();
	afx_msg void OnButtonGetRegistration();
	afx_msg void OnButtonChoosefile();
	afx_msg void OnButtonGenerate();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CODEGENERATIONDLG_H__041728E7_38F4_11D5_935E_C0FE45E14079__INCLUDED_)
