#if !defined(AFX_PROMPTPROPAGE_H__15CFA84E_94B1_42D4_86B5_060CFC4DDF08__INCLUDED_)
#define AFX_PROMPTPROPAGE_H__15CFA84E_94B1_42D4_86B5_060CFC4DDF08__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PromptProPage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPromptProPage dialog

class CPromptProPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CPromptProPage)

// Construction
public:
	CPromptProPage();
	~CPromptProPage();

// Dialog Data
	//{{AFX_DATA(CPromptProPage)
	enum { IDD = IDD_PROPPAGE_PROMPT };
	int		m_nPromptExport;
	int		m_nHowToStart;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPromptProPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPromptProPage)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROMPTPROPAGE_H__15CFA84E_94B1_42D4_86B5_060CFC4DDF08__INCLUDED_)
