// LicenceException.h: interface for the CLicenceException class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LICENCEEXCEPTION_H__5C691A80_CCB0_11D5_935E_C3D7509D4479__INCLUDED_)
#define AFX_LICENCEEXCEPTION_H__5C691A80_CCB0_11D5_935E_C3D7509D4479__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../Utilities/UnscanException.h"


class CLicenceException : public CUnscanException  
{
public:
typedef enum
	{
	kUnknownType,
	kCannotWritePeriod,
	kCannotWriteLicence,
	kOpenKey
	}
	LicenceExceptionType;

public:
	CLicenceException(const char* msg,LicenceExceptionType=kUnknownType);
	CLicenceException();
	virtual ~CLicenceException();

public:
	LicenceExceptionType GetType();

protected:
	LicenceExceptionType m_Type;

};

#endif // !defined(AFX_LICENCEEXCEPTION_H__5C691A80_CCB0_11D5_935E_C3D7509D4479__INCLUDED_)
