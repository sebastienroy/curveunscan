#if !defined(AFX_LANGUAGEPROPAGE_H__6457FD2D_1D97_4C91_8C05_47AA1516BFF5__INCLUDED_)
#define AFX_LANGUAGEPROPAGE_H__6457FD2D_1D97_4C91_8C05_47AA1516BFF5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LanguageProPage.h : header file
//

#include "resource.h"

#include <list>
using namespace std;

/////////////////////////////////////////////////////////////////////////////
// CLanguageProPage dialog

class CLanguageProPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CLanguageProPage)

// Construction
public:
	CLanguageProPage();
	CLanguageProPage(int nDefault,const list<CString> &languageList);
	~CLanguageProPage();

public:
	int GetSelectedLanguage() const;

// Dialog Data
	//{{AFX_DATA(CLanguageProPage)
	enum { IDD = IDD_PROPPAGE_LANGUAGE };
	CComboBox	m_LanguageCombo;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CLanguageProPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	list<CString> m_languageList;
	int m_nSelectedLanguage;
	int m_nInitialLanguage;
	// Generated message map functions
	//{{AFX_MSG(CLanguageProPage)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LANGUAGEPROPAGE_H__6457FD2D_1D97_4C91_8C05_47AA1516BFF5__INCLUDED_)
