#if !defined(AFX_EXPORTPROPAGE_H__A6E0004A_47EF_4BAF_B7B6_A3B77E90CC91__INCLUDED_)
#define AFX_EXPORTPROPAGE_H__A6E0004A_47EF_4BAF_B7B6_A3B77E90CC91__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ExportProPage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CExportProPage dialog

class CExportProPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CExportProPage)

// Construction
public:
	CExportProPage();
	~CExportProPage();

public:
	void SetSeparator(char cSeparator);
	char GetSeparator() const;

// Dialog Data
	//{{AFX_DATA(CExportProPage)
	enum { IDD = IDD_PROPPAGE_EXPORT };
	int		m_nSepRadio;
	CString	m_strOtherSeparator;
	CString	m_strExtension;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CExportProPage)
	public:
	virtual BOOL OnKillActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	char m_cSeparator;
	// Generated message map functions
	//{{AFX_MSG(CExportProPage)
	afx_msg void OnChangeEditSettSepOther();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EXPORTPROPAGE_H__A6E0004A_47EF_4BAF_B7B6_A3B77E90CC91__INCLUDED_)
