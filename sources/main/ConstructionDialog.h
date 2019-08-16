#if !defined(AFX_CONSTRUCTIONDIALOG_H__BBF58280_4B6B_11D4_935E_0080C7A4F675__INCLUDED_)
#define AFX_CONSTRUCTIONDIALOG_H__BBF58280_4B6B_11D4_935E_0080C7A4F675__INCLUDED_


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Resource.h"
#include "enums.h"

class CUnscanView;
class CUnscanDoc;
class CSequence;
class CCurve;
// ConstructionDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CConstructionDialog dialog

class CConstructionDialog : public CDialog
{
// Construction
public:
	CConstructionDialog(UINT ID, CUnscanView *pParent, CSequence *pSequence);
	CConstructionDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CConstructionDialog)
	enum { IDD = IDD_COMMON_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CConstructionDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
public:
	void SetCursorShape(CursorShape shape);
	CursorShape GetCursorShape() const;
	CUnscanDoc* GetDocument();
	CUnscanView* GetView();
	BOOL UpdateOKButton();
	void SetLastDialog(BOOL flag=TRUE);
	void NoPrevious(BOOL flag=TRUE);

protected:
	virtual BOOL DataValidation()=0;
	virtual BOOL OKState();
	virtual void UpdateObjects();
	bool CheckCurveNameUnicity(CCurve* pCurve, CString strName);

	// attributes
protected:
	CursorShape m_CursorShape;
	CSequence* m_pSequence;


	// Generated message map functions
	//{{AFX_MSG(CConstructionDialog)
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnPrevious();
	virtual BOOL OnInitDialog();
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONSTRUCTIONDIALOG_H__BBF58280_4B6B_11D4_935E_0080C7A4F675__INCLUDED_)
