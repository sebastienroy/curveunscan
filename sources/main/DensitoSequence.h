// DensitoSequence.h: interface for the CDensitoSequence class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DENSITOSEQUENCE_H__E684D642_831D_46B3_AF0B_FDF1550FBB48__INCLUDED_)
#define AFX_DENSITOSEQUENCE_H__E684D642_831D_46B3_AF0B_FDF1550FBB48__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Sequence.h"

class CUnscanView;
class CUnscanDoc;
class CCoordSyst;
class CDensityCurve;

class CDensitoSequence : public CSequence  
{
public:
	CDensitoSequence(CUnscanView *pView,
					CUnscanDoc *pDoc,
					CCoordSyst *pCoord,
					CDensityCurve *pCurve=NULL);
	CDensitoSequence();
	virtual ~CDensitoSequence();

public:
	virtual void CancelSequence(CDialog *pDialogue);
	virtual BOOL Begin();

protected:
	virtual void EndStep();
};

#endif // !defined(AFX_DENSITOSEQUENCE_H__E684D642_831D_46B3_AF0B_FDF1550FBB48__INCLUDED_)
