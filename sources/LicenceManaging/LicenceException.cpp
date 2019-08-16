// LicenceException.cpp: implementation of the CLicenceException class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "licencemanaging.h"
#include "LicenceException.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLicenceException::CLicenceException()
{

}

CLicenceException::~CLicenceException()
{

}

CLicenceException::CLicenceException(const char *msg, LicenceExceptionType type/*=kUnknownType*/)
:CUnscanException(msg), m_Type(type)
{

}

CLicenceException::LicenceExceptionType CLicenceException::GetType()
{
	return m_Type;
}
