/////////////////////////////////////////////////
// SetfirstUse.cpp

#include "stdafx.h"

#include "SetFirstUse.h"

#include "../LicenceManaging/LicenceManagingResources.h"
#include "../LicenceManaging/Coder.h"
#include "../Utilities/UnscanException.h"

LONG APIENTRY 
SetFirstUse(HWND hwnd, LPLONG lpIValue, LPSTR lpszValue)
{
	long result;
	try
		{
		result=createDateKey();
		}
	catch(...)
		{
		result=-1;
		}

	return result;
}


int createDateKey()
{
	CString strFullDir=STRPERIODKEYPATH;
	HKEY hKey;	// key that will be created

	HKEY baseKey=SECURITYROOTKEY;
	unsigned long createStatus=REG_OPENED_EXISTING_KEY;
	long result;


	result=RegCreateKeyEx(baseKey,
						strFullDir,
						0,
						NULL,
						REG_OPTION_NON_VOLATILE,
						KEY_ALL_ACCESS|KEY_QUERY_VALUE ,
						NULL,
						&hKey,
						&createStatus);
	if(ERROR_SUCCESS!=result)
		{
		throw CUnscanException("Cannot created entry");
		}

	CString strValue=GetRegistryString(hKey, DATE_ENTRY);

	if(""==strValue)	// key doesn't exist
		{
		// write entry
		CString strDate=CCoder::GetInstance()->GetEncodedTimeStamp();
		bool written=WriteRegistryString(hKey,DATE_ENTRY,strDate);
		if(!written)
			{
			throw CUnscanException("Cannot write entry");
			}
		}

	return result;

}

bool WriteRegistryString(HKEY hKey, const CString strEntry, const CString strValue)
{
	LONG result;
	bool written;
	const BYTE* formatedValue=(const unsigned char *)(LPCSTR)strValue;
	result=RegSetValueEx(hKey,
						strEntry,
						0,
						REG_SZ,
						/*(const unsigned char *)*/formatedValue,
						strValue.GetLength()+1);
	written=(ERROR_SUCCESS==result);
	return written;
}

CString GetRegistryString(HKEY hKey, CString strValueName)
{
	bool found=false;
	CString strResult;

	LONG result=ERROR_SUCCESS;
	for(int index=0;(ERROR_SUCCESS==result)&&!found;index++)
		{
		char valueName[1024];
		unsigned long sizeName=1024;
		DWORD valueType;
		unsigned char data[1024];
		unsigned long sizeData=1024;
		result=RegEnumValue(hKey,index,valueName,&sizeName,0,&valueType,data,&sizeData);
		if( (ERROR_SUCCESS==result)&&(CString(valueName)==strValueName)&&(REG_SZ==valueType) )
			{
			strResult=CString(data);
			found=true;
			}
		}
	return strResult;
}


