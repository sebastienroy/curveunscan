// UnscanDoc.cpp : implementation of the CUnscanDoc class
//

#include "stdafx.h"
#include "CurveUnscan.h"

#include "UnscanDoc.h"
#include "UnscanView.h"
#include "SavePromptDlg.h"
#include "SaveCurveDialog.h"
#include "FileResultDumper.h"
#include "Mainfrm.h"

#include <Dm/BmpManager.h>
#include <Dm/CoordSyst.h>
#include <Dm/Curve.h>
#include <Dm/Results.h>

#include <Utilities/UnscanException.h>
#include <Utilities/tools.h>
#include <SettingsManagement/SettingsManager.h>
#include <LicenceManaging/LicenceManager.h>

#include <list>
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUnscanDoc

IMPLEMENT_DYNCREATE(CUnscanDoc, CDocument)

BEGIN_MESSAGE_MAP(CUnscanDoc, CDocument)
	//{{AFX_MSG_MAP(CUnscanDoc)
	ON_COMMAND(ID_FILE_OPENBITMAP, OnFileOpenbitmap)
	ON_COMMAND(ID_FILE_SAVECURVES, OnFileSavecurves)
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVECURVES, OnUpdateFileSavecurves)
	ON_UPDATE_COMMAND_UI(ID_FILE_OPENBITMAP, OnUpdateFileOpenbitmap)
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE_AS, OnUpdateFileSaveAs)
	ON_UPDATE_COMMAND_UI(ID_FILE_OPEN, OnUpdateFileOpen)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUnscanDoc construction/destruction

CUnscanDoc::CUnscanDoc()
	{
	// TODO: add one-time construction code here

	// définition des paramètres de dessin pour les objets sélectionnés 
	// et les objets non sélectionnés
	// à terme, ces paramètres vont être accessibles via option\parameters

	m_pBmpManager=new CBmpManager(this);

	m_SelectedParameters.AxeThickness=2;
	m_SelectedParameters.PointSize=10;
	m_SelectedParameters.CurveThickness=2;

	m_UnselectedParameters.AxeThickness=1;
	m_UnselectedParameters.PointSize=5;
	m_UnselectedParameters.CurveThickness=1;

	m_ColorArray.Add(RGB(150,100,170));
	m_ColorArray.Add(RGB(255,0,0));
	m_ColorArray.Add(RGB(0,255,0));
	m_ColorArray.Add(RGB(0,0,255));
	m_ColorArray.Add(RGB(128,0,128));
	m_ColorArray.Add(RGB(0,128,128));
	m_ColorArray.Add(RGB(128,128,0));
	m_ColorArray.Add(RGB(200,120,50));
	m_ColorArray.Add(RGB(50,120,50));
	m_ColorArray.Add(RGB(100,170,150));
	m_ColorArray.FreeExtra();
	}

CUnscanDoc::~CUnscanDoc()
	{
	DeleteContents();
	delete m_pBmpManager;
	}

BOOL CUnscanDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	// Ouverture d'un bitmap au démarrage

	DeleteContents();
	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CUnscanDoc serialization

void CUnscanDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
		m_pBmpManager->Serialize(ar);

		int nCoordSystNb=m_CoordSystList.GetCount();
		ar << nCoordSystNb;
		POSITION pos=m_CoordSystList.GetHeadPosition();
		CCoordSyst *pCoord;
		while(NULL!=pos)
		{
			pCoord=m_CoordSystList.GetNext(pos);
			ar << pCoord;
		}

		// update modified flag
		pos=m_CoordSystList.GetHeadPosition();
		while(NULL!=pos)
		{
			pCoord=m_CoordSystList.GetNext(pos);
			pCoord->SetModified(FALSE);
		}

	}
	else
	{
		// TODO: add loading code here
		m_pBmpManager->Serialize(ar);
		m_pBmpManager->SetOwner(this);

		int nCoordSystNb;
		ar >> nCoordSystNb;
		for(int nCounter=0;nCounter<nCoordSystNb;nCounter++)
		{
			CCoordSyst *pCoordSyst=NULL;
			ar >> pCoordSyst;
			pCoordSyst->SetDocument(this);
			m_CoordSystList.AddTail(pCoordSyst);
		}

	}
}

/////////////////////////////////////////////////////////////////////////////
// CUnscanDoc diagnostics

#ifdef _DEBUG
void CUnscanDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CUnscanDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CUnscanDoc commands

void CUnscanDoc::OnFileOpenbitmap() 
{
	// TODO: Add your command handler code here
	BOOL ok=AskToSave();
	if(!ok)
	{
		return;
	}
	BOOL opened=FALSE;
	CString graphicFilterName;
	graphicFilterName.LoadString(IDS_GRAPHICFILTERNAME);
	CString filter=graphicFilterName;
	filter+="|*.bmp; *.jpg; *.jpe; *.tif; *.gif; *.pic; *.pcx; *.png|";
	graphicFilterName.LoadString(IDS_GRAPHICFILTERNAME_ALL);
	filter+=graphicFilterName;
	filter+=" (*.*)|*.*||";
	CFileDialog dlg(TRUE,"","",OFN_FILEMUSTEXIST,filter,NULL);
	if(dlg.DoModal()==IDOK)
	{
		DeleteContents();
		CString filename=dlg.GetPathName();
		BeginWaitCursor();
        opened=m_pBmpManager->OpenBitmap(filename);
		if(opened)
		{
			SetTitle(dlg.GetFileTitle());
		}
		else
		{
			SetTitle("");
		}
		EndWaitCursor();
	}

	POSITION pos=GetFirstViewPosition();
	CUnscanView* pView=static_cast<CUnscanView*>(GetNextView(pos));
	if(NULL!=pView)
	{
		pView->OnInitialUpdate();
	}
	// launch identification
	if(opened)
	{
		pView->StartInitialSequence();
	}
}

BOOL CUnscanDoc::InitialOpenBitmap()
	{
	OnFileOpenbitmap();
	return TRUE;
	}

void CUnscanDoc::OnUpdateFileOpenbitmap(CCmdUI* pCmdUI) 
	{
	// TODO: Add your command update UI handler code here
	POSITION pos=GetFirstViewPosition();
	CUnscanView* pView=(CUnscanView*)GetNextView(pos);
	CMainFrame* pMainFrame=static_cast<CMainFrame*>(pView->GetParent());
	bool bScannerActive=pMainFrame->IsScannerActive();
	bool bDialogOn=pView->IsDialogOn();

	pCmdUI->Enable((!bDialogOn)&&(!bScannerActive));
	}

void CUnscanDoc::AddCoordSyst(CCoordSyst *systeme)
	{
	m_CoordSystList.AddTail(systeme);
	systeme->SetDocument(this);
	}

BOOL CUnscanDoc::DeleteCoordSyst(CCoordSyst *systeme)
	{
	POSITION pos;
	pos=m_CoordSystList.Find(systeme);
	if(pos==NULL)
		{
		return FALSE;
		}
	delete m_CoordSystList.GetAt(pos);
	m_CoordSystList.RemoveAt(pos);
	return TRUE;
	}

void CUnscanDoc::DeleteContents() 
	{
	// TODO: Add your specialized code here and/or call the base class
	
	CDocument::DeleteContents();
	delete m_pBmpManager;
	m_pBmpManager=new CBmpManager(this);
	if(!m_CoordSystList.IsEmpty())
		{
		POSITION pos=m_CoordSystList.GetHeadPosition();
		while(pos!=NULL)
			{
			CCoordSyst* pCoord = m_CoordSystList.GetNext(pos);
			delete pCoord;
			}
		}
	m_CoordSystList.RemoveAll();
	CCurve::ResetIdentifierNumber();
	CCoordSyst::ResetIdentifierNumber();

	CString strTitle;
	strTitle.LoadString(IDS_UNTITLED);
	SetTitle(strTitle);

	SetModifiedFlag(FALSE);
	}

// Déselectionne l'ensemble des objets
// sélectionne le cas échéant l'objet présent au point passé en paramètre
BOOL CUnscanDoc::SelectOn(CPoint point)
	{
	UnselectAll();
	BOOL select=FALSE;
	POSITION posCoord=m_CoordSystList.GetHeadPosition();
	POSITION posCurve;
	CCoordSyst* pCoord;
	CCurve* pCurve;
	// Sélectionner ce qu'il faut
	while( (posCoord!=NULL)&&(select==FALSE) ) 
		{
		pCoord=m_CoordSystList.GetNext(posCoord);
		if(pCoord->IsPresentOn(point))
			{
			pCoord->SetSelected();
			select=TRUE;
			}
		posCurve=pCoord->GetHeadCurvePosition();
		while( (posCurve!=NULL)&&(select==FALSE) )
			{
			pCurve=pCoord->GetNextCurve(posCurve);
			if(pCurve->IsPresentOn(point))
				{
				pCurve->SetSelected();
				select=TRUE;
				}
			}
		}
	return select;
	}

	// Tout déselectionner
void CUnscanDoc::UnselectAll()
	{
	BOOL select=FALSE;
	POSITION posCoord=m_CoordSystList.GetHeadPosition();
	POSITION posCurve;
	CCoordSyst* pCoord;
	CCurve* pCurve;
	while(posCoord!=NULL)
		{
		pCoord=m_CoordSystList.GetNext(posCoord);
		pCoord->SetSelected(FALSE);
		posCurve=pCoord->GetHeadCurvePosition();
		while(posCurve!=NULL)
			{
			pCurve=pCoord->GetNextCurve(posCurve);
			pCurve->SetSelected(FALSE);
			}
		}
	}

DrawParameters CUnscanDoc::GetSelParam()
	{
	return m_SelectedParameters;
	}

DrawParameters CUnscanDoc::GetUnselParam()
	{
	return m_UnselectedParameters;
	}


CCoordSyst* CUnscanDoc::GetSelectedCoordSyst()
	{
	POSITION pos=m_CoordSystList.GetHeadPosition();
	CCoordSyst* pCoord;
	while(pos!=NULL)
		{
		pCoord=m_CoordSystList.GetNext(pos);
		if(pCoord->IsSelected())
			{
			return pCoord;
			}
		}
	return NULL;
	}

CCurve* CUnscanDoc::GetSelectedCurve()
	{
	POSITION posCoord=m_CoordSystList.GetHeadPosition();
	POSITION posCurve;
	CCoordSyst* pCoord;
	CCurve* pCurve;
	while(posCoord!=NULL)
		{
		pCoord=m_CoordSystList.GetNext(posCoord);
		posCurve=pCoord->GetHeadCurvePosition();
		while(posCurve!=NULL)
			{
			pCurve=pCoord->GetNextCurve(posCurve);
			if(pCurve->IsSelected())
				{
				return pCurve;
				}
			}
		}
	return NULL;
	}

CBmpManager* CUnscanDoc::GetBmpManager()
	{
	return m_pBmpManager;
	}

BOOL CUnscanDoc::OnFileSavecurves() 
	{
	// TODO: Add your command handler code here
	CSaveCurveDialog saveDialog(this);
	if(saveDialog.DoModal()!=IDOK)
		{
		return FALSE;
		}


	CSettingsManager *pSettings=CSettingsManager::GetInstance();

	CString strExtension=(NULL==pSettings)?"xls":pSettings->GetExportFilenameExtension();

	CString strFilter=CTools::GetFileFiltersFromExtension(strExtension);

	CFileDialog dlg(FALSE,strExtension,CTools::GetNameFromPath(GetTitle()),
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,strFilter);
	if(dlg.DoModal()==IDOK)
		{
		CString filename=dlg.GetPathName();
		list<CResults*>* pResultsList=saveDialog.GetResultsList();
		try
			{
			BeginWaitCursor();
			//--- Save results
			char cSeparator=saveDialog.GetSeparator();
			CFileResultDumper dumper(pResultsList,filename,cSeparator);
			dumper.Dump();

			//--- Mark curves as saved
			list<CResults*>::iterator iter;
			for(iter=pResultsList->begin();iter!=pResultsList->end();iter++)
				{
				CResults* pResults=*iter;
				CCurve* pCurve=pResults->GetCurve();
				pCurve->SetModifiedFlag(FALSE);
				}

			// decrease the number of export left (if not licenced)
			CLicenceManager &licenceManager=CLicenceManager::GetInstance();
			if(NULL!=&licenceManager)
			{
				licenceManager.DecreaseNbOfExportLeft();
			}

			EndWaitCursor();
			}
		catch (CUnscanException& err)
			{
			EndWaitCursor();
			CString msg=err.GetMessage();
			AfxMessageBox(msg,MB_OK|MB_ICONSTOP);
			}
		catch (...)
			{
			EndWaitCursor();
			CString msg="Error while accessing to the file.";
			AfxMessageBox(msg,MB_OK|MB_ICONSTOP);
			}
		}		
	return FALSE;
	}

//Activer la commande si courbe présente et pas de dialogue actif
void CUnscanDoc::OnUpdateFileSavecurves(CCmdUI* pCmdUI) 
	{
	// TODO: Add your command update UI handler code here
	BOOL present=FALSE;
	BOOL noDialog=FALSE;

	POSITION posView=GetFirstViewPosition();
	CUnscanView* pView=(CUnscanView*)GetNextView(posView);
	noDialog=!(pView->IsDialogOn());
	POSITION posCoord=m_CoordSystList.GetHeadPosition();
	CCoordSyst* pCoord;
	while(posCoord!=NULL)
		{
		pCoord=m_CoordSystList.GetNext(posCoord);
		if((pCoord->GetCurveCount())>0)
			{
			present=TRUE;
			break;
			}
		}
	pCmdUI->Enable(present&&noDialog);
	}

POSITION CUnscanDoc::GetHeadCoordSystPosition()
	{
	return m_CoordSystList.GetHeadPosition();
	}

CCoordSyst* CUnscanDoc::GetNextCoordSyst(POSITION &rPos)
	{
	return m_CoordSystList.GetNext(rPos);
	}


COLORREF CUnscanDoc::GetColor(int nIndex)
	{
	int size=m_ColorArray.GetSize();
	int n=nIndex%size;
	return m_ColorArray[n];
	}

BOOL CUnscanDoc::CanCloseFrame(CFrameWnd* pFrame) 
	{
	// TODO: Add your specialized code here and/or call the base class

	return SaveModified();

/*
	CString str;
	str.LoadString(IDS_CURVES_NOT_SAVED_EXIT);

	BOOL result=AskToSave(str);
	return result;
*/
	}

BOOL CUnscanDoc::GetModified()
	{
	BOOL modified=FALSE;
	POSITION coordPos=m_CoordSystList.GetHeadPosition();
	CCoordSyst* pCoord;
	POSITION curvePos;
	CCurve* pCurve;
	while( (coordPos!=NULL)&&(!modified) )
		{
		pCoord=m_CoordSystList.GetNext(coordPos);
		curvePos=pCoord->GetHeadCurvePosition();
		while( (curvePos!=NULL)&&(!modified) )
			{
			pCurve=pCoord->GetNextCurve(curvePos);
			if(pCurve->GetModifiedFlag())
				{
				modified=TRUE;
				}
			}
		}
	return modified;
	}

BOOL CUnscanDoc::AskToSave()
{
	return SaveModified();
/*	BOOL result=TRUE;
	if(GetModified())
		{
		BOOL succeded=FALSE;
		while(!succeded)
			{
			int answer=AfxMessageBox(msg,MB_YESNOCANCEL|MB_ICONEXCLAMATION);
			if(answer==IDCANCEL)
				{
				result=FALSE;
				succeded=TRUE;
				}
			else if(answer==IDNO)
				{
				result=TRUE;
				succeded=TRUE;	
				}
			else if(answer==IDYES)
				{
				result=succeded=OnFileSavecurves();
				}
			}
		}
	return result;
*/
}

CString CUnscanDoc::GetBitmapName()
{
	return m_pBmpManager->GetName();
}

void CUnscanDoc::Draw(CDC *pDC, CRect* pRect/*=NULL*/)
{
	//--- Get a correct drawing rectangle
	CRect drawingRect;
	if(NULL==pRect)
		{
		POSITION pos=GetFirstViewPosition();
		CUnscanView* pView=static_cast<CUnscanView*>(GetNextView(pos));
		pView->GetClientRect(&drawingRect);
		}
	else
		{
		drawingRect=*pRect;
		}

	drawingRect.bottom++;	// the last bottom and right line is not drawn
	drawingRect.right++;

	m_pBmpManager->Draw(pDC,drawingRect);

	POSITION pos=m_CoordSystList.GetHeadPosition();
	CCoordSyst* pCoord;
	while(pos!=NULL)
		{
		pCoord=m_CoordSystList.GetNext(pos);
		pCoord->Draw(pDC);
		}
}

void CUnscanDoc::Draw(CRect* pRect/*=NULL*/)
{
	POSITION pos=GetFirstViewPosition();
	CUnscanView* pView=static_cast<CUnscanView*>(GetNextView(pos));
	CDC* pDC=pView->GetDC();
	if(NULL==pDC)
		{
		return;
		}

	pView->OnPrepareDC(pDC);
	if(NULL==pRect)
		{
		CRect clientRect;
		pView->GetClientRect(&clientRect);
		Draw(pDC,&clientRect);
		}
	else
		{
		Draw(pDC,pRect);
		}
	pView->ReleaseDC(pDC);	// style is OWNDC so no need to release the DC

}

BOOL CUnscanDoc::SaveCurves()
{
	return OnFileSavecurves();
}

bool CUnscanDoc::IsCurveBuilt()
{
	bool bCurveExists=false;
	POSITION pos=m_CoordSystList.GetHeadPosition();
	while( (NULL!=pos)&&(false==bCurveExists) )
		{
		CCoordSyst* pCoord=m_CoordSystList.GetNext(pos);
		POSITION posCurve=pCoord->GetHeadCurvePosition();
		if(NULL!=posCurve)
			{
			bCurveExists=true;
			}
		}
	return bCurveExists;
}

// check if document modified
BOOL CUnscanDoc::UpdateModifiedState()
{
	BOOL bModified=FALSE;

	POSITION pos=m_CoordSystList.GetHeadPosition();
	while((FALSE==bModified)&&(NULL!=pos))
	{
		CCoordSyst *pCoord=m_CoordSystList.GetNext(pos);
		bModified=pCoord->HasSomethingModified();
	}

	SetModifiedFlag(bModified);
/*	CString strTitle=GetTitle();
	if( (!strTitle.IsEmpty() )
		&& (strTitle[strTitle.GetLength()-1]!='*') )
	{
		strTitle+='*';
	}
	SetTitle(strTitle);*/
	return bModified;
}


void CUnscanDoc::OnUpdateFileSaveAs(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here

	// is window opened?
	POSITION pos=GetFirstViewPosition();
	CUnscanView* pView=static_cast<CUnscanView*>(GetNextView(pos));
	bool bWindowOpened=pView->IsDialogOn();

	// is there something to save? (an opened bitmap should be enough)
	bool bSomethingToSave=m_pBmpManager->IsBmpOpened();

	bool bCanSave=bSomethingToSave&&(!bWindowOpened);
	pCmdUI->Enable(bCanSave);
}

void CUnscanDoc::OnUpdateFileOpen(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here

	// is window opened?
	POSITION pos=GetFirstViewPosition();
	CUnscanView* pView=static_cast<CUnscanView*>(GetNextView(pos));
	CMainFrame* pMainFrame=static_cast<CMainFrame*>(pView->GetParent());
	bool bScannerActive=pMainFrame->IsScannerActive();
	bool bWindowOpened=pView->IsDialogOn();
	
	pCmdUI->Enable( (!bWindowOpened)&&(!bScannerActive) );
}

void CUnscanDoc::SetScannedImage(HANDLE hBitmap, int nBitsPerPixel)
{
	BeginWaitCursor();
	m_pBmpManager->MakeBmpFromHandle(hBitmap,nBitsPerPixel);
	
	CString strTitle;
	strTitle.LoadString(IDS_UNTITLED);
	SetTitle(strTitle);
	SetPathName(strTitle);

	POSITION pos=GetFirstViewPosition();
	CView* pView=GetNextView(pos);
	if(NULL!=pView)
		{
		pView->OnInitialUpdate();
		}
	EndWaitCursor();
}

BOOL CUnscanDoc::SaveModified() 
{
	// TODO: Add your specialized code here and/or call the base class
	

//---- Original code

//	return CDocument::SaveModified();

	if (!IsModified())
		return TRUE;        // ok to continue

	// get name/title of document
	CString name;
	if (m_strPathName.IsEmpty())
	{
		// get name based on caption
		name = m_strTitle;
		if (name.IsEmpty())
		{
			VERIFY(name.LoadString(AFX_IDS_UNTITLED));
		}
	}
	else
	{
		// get name based on file title of path name
		name = CTools::GetNameFromPath(m_strPathName);
	}
	if( (!name.IsEmpty())&&('*'==name[name.GetLength()-1]))
	{
		name=name.Left(name.GetLength()-1);
	}

	CString strPrompt;
	AfxFormatString1(strPrompt, AFX_IDP_ASK_TO_SAVE, name);

	CSavePromptDlg dlg(strPrompt);

	switch (dlg.DoModal())
	{
	case IDCANCEL:
		return FALSE;       // don't continue

	case IDYES:
		// If so, either Save or Update, as appropriate
		if(0==dlg.m_nSaveKind)	// export data
		{
			if(!OnFileSavecurves())
			{
				return FALSE;       // don't continue
			}
		}
		else					//save document
		{
			if (!DoFileSave())
			{
				return FALSE;       // don't continue
			}
		}
		break;

	case IDNO:
		// If not saving changes, revert the document
		break;

	default:
		ASSERT(FALSE);
		break;
	}
	return TRUE;    // keep going*/
}
