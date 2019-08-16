//////////////////////////////////////////////////////////////////////
// IsKeyOk.cpp

#include "stdafx.h"

#include "IsKeyOk.h"

#include "../LicenceManaging/LicenceManagingResources.h"
#include "../LicenceManaging/Coder.h"
#include "../Utilities/UnscanException.h"

#include <md5/md5checksum.h>

LONG APIENTRY HelloSeb(LPSTR lpCompany, LPSTR lpFirstName, LPSTR lpLastName, LPSTR lpKey)
{
	CString strSerial(SERIAL);
	CString strKey=CString(lpKey);
	strKey=CCoder::GetInstance()->Strip(strKey);
	CString strMD5CodedKey=CMD5Checksum::GetMD5((BYTE*)(LPCSTR)strKey);
//	CCoder coder;
	// in order to introduce confusion for hackers
	// lpCompany=name
	// lpLastName=company name
	// lpKey= key
	bool bResult=CCoder::GetInstance()->isRegistrationCodeCorrect(strSerial,lpCompany,lpLastName,lpKey);
//	bool bResult=coder.isRegistrationCodeCorrect(strSerial,lpCompany,lpLastName,lpKey);
	if(bResult)
	{
		return 0;
	}
	else
	{
		return -1;
	}
}
