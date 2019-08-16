// UnscanDoc.h : interface of the CUnscanDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_UNSCANDOC_H__96163FDE_1FE2_4EFB_B4F3_64B36248C34B__INCLUDED_)
#define AFX_UNSCANDOC_H__96163FDE_1FE2_4EFB_B4F3_64B36248C34B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <afxtempl.h>
#include "DrawParameters.h"
class CBmpManager;
class CCoordSyst;
class CCurve;

class CUnscanDoc : public CDocument
{
protected: // create from serialization only
	CUnscanDoc();
	DECLARE_DYNCREATE(CUnscanDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUnscanDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual void DeleteContents();
	virtual BOOL CanCloseFrame(CFrameWnd* pFrame);
	protected:
	virtual BOOL SaveModified();
	//}}AFX_VIRTUAL

// Implementation
public:
	BOOL AskToSave();
	void SetScannedImage(HANDLE hBitmap, int nBitsPerPixel);
	BOOL UpdateModifiedState();
	bool IsCurveBuilt();
	BOOL SaveCurves();
	void Draw(CRect* rect=NULL);
	void Draw(CDC* pDC,CRect* rect=NULL);
	CString GetBitmapName();
	BOOL GetModified();
	COLORREF GetColor(int nIndex);
	BOOL InitialOpenBitmap();
	CCoordSyst* GetNextCoordSyst(POSITION& rPos);
	POSITION GetHeadCoordSystPosition();
	CBmpManager* GetBmpManager();
	CCurve* GetSelectedCurve();
	CCoordSyst* GetSelectedCoordSyst();
	void UnselectAll();
	DrawParameters GetUnselParam();
	DrawParameters GetSelParam();
	BOOL SelectOn(CPoint point);
	CTypedPtrList<CPtrList, CCoordSyst*> m_CoordSystList;
	BOOL DeleteCoordSyst(CCoordSyst* systeme);
	void AddCoordSyst(CCoordSyst* systeme);
	virtual ~CUnscanDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CUnscanDoc)
	afx_msg void OnFileOpenbitmap();
	afx_msg BOOL OnFileSavecurves();
	afx_msg void OnUpdateFileSavecurves(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFileOpenbitmap(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFileSaveAs(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFileOpen(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
protected:
	CArray<COLORREF,COLORREF> m_ColorArray;
	CBmpManager* m_pBmpManager;
	DrawParameters m_UnselectedParameters;
	DrawParameters m_SelectedParameters;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_UNSCANDOC_H__96163FDE_1FE2_4EFB_B4F3_64B36248C34B__INCLUDED_)
