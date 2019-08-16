#if !defined(AFX_VALUEEDIT_H__3C85DC40_5FD7_11D4_935E_0080C7A4F675__INCLUDED_)
#define AFX_VALUEEDIT_H__3C85DC40_5FD7_11D4_935E_0080C7A4F675__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ValueEdit.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CValueEdit window

class CValueEdit : public CEdit
{
// Construction
public:
	CValueEdit();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CValueEdit)
	//}}AFX_VIRTUAL

// Implementation
public:
	double Erase();
	BOOL IsEmpty() const;
	void SetValue(double value);
	double GetValue() const;
	virtual ~CValueEdit();

	// Generated message map functions
protected:
	//{{AFX_MSG(CValueEdit)
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VALUEEDIT_H__3C85DC40_5FD7_11D4_935E_0080C7A4F675__INCLUDED_)
