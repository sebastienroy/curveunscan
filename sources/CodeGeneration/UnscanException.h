// UnscanException.h: interface for the CUnscanException class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UNSCANEXCEPTION_H__68DE40C8_3713_11D5_935E_BAB3637C2579__INCLUDED_)
#define AFX_UNSCANEXCEPTION_H__68DE40C8_3713_11D5_935E_BAB3637C2579__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CUnscanException  
{
public:
	CString GetMessage();
	CUnscanException(const char* msg);
	CUnscanException();
	virtual ~CUnscanException();

protected:
	CString m_strMessage;
};

#endif // !defined(AFX_UNSCANEXCEPTION_H__68DE40C8_3713_11D5_935E_BAB3637C2579__INCLUDED_)
