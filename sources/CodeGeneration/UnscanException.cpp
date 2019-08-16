// UnscanException.cpp: implementation of the CUnscanException class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "UnscanException.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CUnscanException::CUnscanException()
{

}

CUnscanException::~CUnscanException()
{

}

CUnscanException::CUnscanException(const char *msg)
{
	m_strMessage=msg;
}

CString CUnscanException::GetMessage()
{
	return m_strMessage;
}
