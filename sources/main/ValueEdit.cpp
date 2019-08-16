// ValueEdit.cpp : implementation file
//

#include "stdafx.h"
#include "CurveUnscan.h"
#include "ValueEdit.h"
#include <stdlib.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CValueEdit

CValueEdit::CValueEdit()
{
}

CValueEdit::~CValueEdit()
{
}


BEGIN_MESSAGE_MAP(CValueEdit, CEdit)
	//{{AFX_MSG_MAP(CValueEdit)
	ON_WM_CHAR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CValueEdit message handlers

double CValueEdit::GetValue() const
	{
	CString str;
	double value;
	GetWindowText(str);
	char *buff;
	char *buffEnd;
	buff=str.GetBuffer(64);
	value=strtod(buff,&buffEnd);
	str.ReleaseBuffer();
	return value;
	}

void CValueEdit::SetValue(double value)
	{
	CString str;
	str.Format("%g",value);
	SetWindowText(str);
	}

void CValueEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	switch(nChar)
		{
		case '-':
		case '+':
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
		case '.':
		case 'e':
		case 'E':
		case 8 :  // Back space
		case 127 : // Delete
			CEdit::OnChar(nChar, nRepCnt, nFlags);
		default: ;
		}
}

BOOL CValueEdit::IsEmpty() const
	{
	CString str;
	GetWindowText(str);
	int length=str.GetLength();
	if (length==0)
		{
		return TRUE;
		}
	else
		{
		return FALSE;
		}
	}

double CValueEdit::Erase()
	{
	double oldValue=GetValue();
	SetWindowText("");
	return oldValue;
	}
