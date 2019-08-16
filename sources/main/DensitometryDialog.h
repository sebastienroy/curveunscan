#if !defined(AFX_DENSITOMETRYDIALOG_H__82C16C8F_AEDF_433A_96F1_C01E5A79B8B4__INCLUDED_)
#define AFX_DENSITOMETRYDIALOG_H__82C16C8F_AEDF_433A_96F1_C01E5A79B8B4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DensitometryDialog.h : header file
//

#include "ConstructionDialog.h"
#include "Utilities/ColoredButton.h"
#include "Utilities/ColorScaleButton.h"
#include "ValueEdit.h"


class CDensityCurve;
class CDensitoDlgAbstractState;
class CDensitoPreviewWnd;
class CColorScale;

/////////////////////////////////////////////////////////////////////////////
// CDensitometryDialog dialog

class CDensitometryDialog : public CConstructionDialog
{
	// state classes
friend class CDensitoDlgAbstractState;
friend class CDensitoDlgDrawState;
friend class CDensitoDlgPickState;
friend class CDensitoDlgWaitState;

// Construction
public:
//	CDensitometryDialog(CWnd* pParent = NULL);   // standard constructor
	CDensitometryDialog(UINT ID,CUnscanView *pParent, 
						CSequence *pSequence, 
						CDensityCurve *pCurve);


// Dialog Data
	//{{AFX_DATA(CDensitometryDialog)
	enum { IDD = IDD_DENSITO_DIALOG };
	CColorScaleButton	m_ColorScaleButton;
	CColoredButton	m_BottomColorButton;
	CColoredButton	m_TopColorButton;
	CValueEdit	m_BottomValueEdit;
	CValueEdit	m_TopValueEdit;
	BOOL	m_bPickBottom;
	BOOL	m_bPickTop;
	BOOL	m_bDrawSegment;
	CString	m_strCurveName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDensitometryDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:
	LONG OnPreviewClosed(UINT wParam, LONG lParam);
	LONG OnScrollOff(UINT wParam, LONG lParam);
	LONG OnScrollOn(UINT wParam, LONG lParam);
	LONG OnMovePick(UINT wParam, LONG lParam);
	LONG OnStartPick(UINT wParam, LONG lParam);
	LONG OnEndPick(UINT wParam, LONG lParam);
	bool CheckScaleValidity();
	virtual BOOL DataValidation();

protected:
	CDensitoPreviewWnd* m_pPreviewWnd;
	virtual void UpdateObjects();
	void UpdateButtons();
	virtual BOOL OKState();
	CPoint m_ptTo;
	CPoint m_ptFrom;
	CDensitoDlgAbstractState* m_pState;
	CColorScale *m_pColorScale;
	CDensityCurve* m_pCurve;

	// Generated message map functions
	//{{AFX_MSG(CDensitometryDialog)
	afx_msg void OnTopColorButton();
	afx_msg void OnBottomColorButton();
	afx_msg void OnCheckDrawsegmentDensito();
	afx_msg void OnCheckPickBottomColor();
	afx_msg void OnCheckPickTopColor();
	afx_msg void OnDefaultColorScaleButton();
	virtual BOOL OnInitDialog();
	afx_msg void OnClose();
	afx_msg void OnPrevious();
	afx_msg void OnDensitopreviewButton();
	afx_msg void OnChangeEditBottomColorValue();
	afx_msg void OnChangeEditTopColorValue();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DENSITOMETRYDIALOG_H__82C16C8F_AEDF_433A_96F1_C01E5A79B8B4__INCLUDED_)
