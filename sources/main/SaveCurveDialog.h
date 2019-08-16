#if !defined(AFX_SAVECURVEDIALOG_H__A801C2C5_6943_11D4_935E_0080C7A4F675__INCLUDED_)
#define AFX_SAVECURVEDIALOG_H__A801C2C5_6943_11D4_935E_0080C7A4F675__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <afxtempl.h>
#include <list>
using namespace std;

class CUnscanDoc;
class CResults;
class CCurve;

// SaveCurveDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSaveCurveDialog dialog

class CSaveCurveDialog : public CDialog
{
// Construction
public:
	char GetSeparator() const;
	list<CResults*>* GetResultsList();
	CTypedPtrList<CPtrList,CCurve*> m_pSavedCurveList;
	CString* GetStrBuffer();
	CSaveCurveDialog(CUnscanDoc* pDoc);
	CSaveCurveDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSaveCurveDialog)
	enum { IDD = IDD_SAVE_DIALOG };
	CListBox	m_ToSaveLB;
	CListBox	m_AvailableLB;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSaveCurveDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	char m_cSeparator;
	void ConstructResultList();
	CString m_StrBuffer;
	list<CResults*> m_pResultsList;
	void AddCurve(int nIndex);
	BOOL UpdateButtons();
	CUnscanDoc* m_pDoc;

	// Generated message map functions
	//{{AFX_MSG(CSaveCurveDialog)
	afx_msg void OnRemoveButton();
	afx_msg void OnAddButton();
	afx_msg void OnSelchangeTosaveList();
	afx_msg void OnDblclkTosaveList();
	afx_msg void OnSelchangeAvailList();
	afx_msg void OnDblclkAvailList();
	virtual BOOL OnInitDialog();
	afx_msg void OnDeltaposOrderSpin(NMHDR* pNMHDR, LRESULT* pResult);
	virtual void OnCancel();
	virtual void OnOK();
	afx_msg void OnPreviewButton();
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	afx_msg void OnExportformatButton();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SAVECURVEDIALOG_H__A801C2C5_6943_11D4_935E_0080C7A4F675__INCLUDED_)
