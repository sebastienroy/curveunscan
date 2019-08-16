/*
/--------------------------------------------------------------------
|
|      $Id: maindlg.h,v 1.4 2001/09/16 19:03:23 uzadow Exp $
|
|      Copyright (c) 1996-1998 Ulrich von Zadow
|
--------------------------------------------------------------------
*/

#include "plwinbmp.h"
#include "mtdibwnd.h"
#include "plpicdec.h"
#include "grarray.h"

#ifdef TEST_DDRAW
#include <ddraw.h>
#endif

class CDibtestDlg : public CDialog
{
// Construction
public:
  CDibtestDlg
    ( char * pszDirName
    );

  ~CDibtestDlg
    ();

  void DoWork
    ();

// Dialog Data
  //{{AFX_DATA(CDibtestDlg)
  enum { IDD = IDD_DIBTEST_DIALOG };
          // NOTE: the ClassWizard will add data members here
  //}}AFX_DATA

  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CDibtestDlg)
  protected:
  virtual void DoDataExchange(CDataExchange* pDX);        // DDX/DDV support
  //}}AFX_VIRTUAL

// Implementation
protected:
  HICON m_hIcon;

  // Generated message map functions
  //{{AFX_MSG(CDibtestDlg)
  virtual BOOL OnInitDialog();
  afx_msg void OnPaint();
  afx_msg HCURSOR OnQueryDragIcon();
  afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
  //}}AFX_MSG
  DECLARE_MESSAGE_MAP()

private:
  void loadDir
    ( PLPicDecoder * pDecoder,
      CGrItemArray * pDIBArray,
      const char * pszDirName
    );
    // Tries to load all files in a directory and its
    // subdirectories.

  void loadFile
    ( PLPicDecoder * pDecoder,
      CGrItemArray * pDIBArray,
      const char * pszFName
    );
    // Tries to load a file. Does error checking.

  void loadRes
    ( PLPicDecoder * pDecoder,
      CGrItemArray * pDIBArray,
      int ResourceID
    );
    // Tries to load a resource. Does error checking.

  void createBkGrnd
    ( PLPicDecoder * pDecoder
    );

  void setAlphaChannel
    ( CGrItemArray * pDIBArray
    );

  void update
    ( CGrItemArray * pDIBArray,
      CRect * pOldRect,
      CRect * pNewRect
    );

  void testResource
    ();

  PLWinBmp * m_pBmp;
  PLWinBmp * m_pBigBmp;

  CMTDIBWnd * m_pDIBWnd;

  CString m_sDirName;

  int m_x;
  int m_y;

  CRITICAL_SECTION m_Critical;

#ifdef TEST_DDRAW
  IDirectDraw * m_pDDraw;
#endif
};
/*
/--------------------------------------------------------------------
|
|      $Log: maindlg.h,v $
|      Revision 1.4  2001/09/16 19:03:23  uzadow
|      Added global name prefix PL, changed most filenames.
|
|      Revision 1.3  2000/08/13 12:11:44  Administrator
|      Added experimental DirectDraw-Support
|
|
--------------------------------------------------------------------
*/
