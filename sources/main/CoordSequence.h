// CoordSequence.h: interface for the CCoordSequence class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_COORDSEQUENCE_H__0144DD84_4F2D_11D4_935E_0080C7A4F675__INCLUDED_)
#define AFX_COORDSEQUENCE_H__0144DD84_4F2D_11D4_935E_0080C7A4F675__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Sequence.h"
class CUnscanView;
class CUnscanDoc;
class CCoordSyst;

class CCoordSequence : public CSequence  
{
public:
	virtual void CancelSequence(CDialog* pDialogue);
	virtual BOOL Begin();
	CCoordSequence(CUnscanView *pView, CUnscanDoc *pDoc, CCoordSyst *pCoord=NULL);
	CCoordSequence();
	virtual ~CCoordSequence();

protected:
	virtual void EndStep();
};

#endif // !defined(AFX_COORDSEQUENCE_H__0144DD84_4F2D_11D4_935E_0080C7A4F675__INCLUDED_)
