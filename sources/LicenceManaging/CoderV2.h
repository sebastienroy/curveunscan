// CoderV2.h: interface for the CCoderV2 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CODERV2_H__CEEB062B_0EEA_4BD2_B7D4_003205660E32__INCLUDED_)
#define AFX_CODERV2_H__CEEB062B_0EEA_4BD2_B7D4_003205660E32__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Coder.h"

class CCoderV2 : public CCoder  
{
protected:
	CCoderV2();
	CCoderV2(CString strCodeKey);
	virtual ~CCoderV2();


public:
	virtual CString getRegistrationNumber(CString strSerial,CString strName,CString strCompany);
	virtual CString GetMd5CodedRegistrationNumber();


	friend class CCoder;
};

#endif // !defined(AFX_CODERV2_H__CEEB062B_0EEA_4BD2_B7D4_003205660E32__INCLUDED_)
