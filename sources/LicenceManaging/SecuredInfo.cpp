// SecuredInfo.cpp: implementation of the CSecuredInfo class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "licencemanaging.h"
#include "SecuredInfo.h"
#include "AnyFileAccessor.h"
#include <io.h>

#include "Coder.h"

#include "../Utilities/Profile.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSecuredInfo::CSecuredInfo()
:	m_bUsefile(true)
{
}


CSecuredInfo::CSecuredInfo(const char* fileName,
				 const char* filePath,
				 const char* regEntry,
				 const char* regPath)
:	m_strFilename(fileName),
	m_strFilePath(filePath),
	m_strRegistryEntryName(regEntry),
	m_strRegistryPath(regPath),
	m_bUsefile(true)
{
	if(IsRegKeyExists())
	{
		m_bUsefile=false;
	}
}

CSecuredInfo::~CSecuredInfo()
{

}

CString CSecuredInfo::GetValue(const char *strSection, const char *strEntry)
{
	InitializeSupport();

	if(m_bUsefile)
	{
		return GetValueFromFile(strSection,strEntry);
	}
	else
	{
		return GetValueFromRegistry(strSection,strEntry);
	}
}

bool CSecuredInfo::SetValue(const char *strSection, const char *strEntry, const char *strValue)
{
	InitializeSupport();
	if(m_bUsefile)
	{
		return SetValueToFile(strSection,strEntry,strValue);
	}
	else
	{
		return SetValueToRegistry(strSection,strEntry,strValue);
	}

}

// return true if the support (file or registry) has already been used
bool CSecuredInfo::IsInitialized()
{
	if(m_bUsefile)
	{
		return IsFileExists();
	}
	else
	{
		return IsRegKeyExists();
	}
}

bool CSecuredInfo::InitializeSupport()
{
	if(m_bUsefile)
	{
		bool bFileExists=IsFileExists();
		if(bFileExists)
		{
			if(IsFileWritable())
			{
				return true;
			}
			else
			{
				m_bUsefile=false;
				return InitializeRegistry();
			}
		}
		else // file does not exist
		{
			if(InitializeFile())
			{
				return true;
			}
			else
			{
				m_bUsefile=false;
				return InitializeRegistry();
			}
		}
	}
	else
	{
		return InitializeRegistry();
	}
}

// create the file
bool CSecuredInfo::InitializeFile()
{
	CAnyFileAccessor::GetInstance()->AccessToSomeFiles();

	// check if win NT
	bool bIsNT=IsWinNT();
	bool created=false;
	bool initialized=false;
	if(bIsNT)
	{
		created=InitializeFileNT();
	}
	else
	{
		created=InitializeFileClassic();
	}
	if(created)
	{
		initialized=CreateFileSkeleton();
	}
	return initialized;
}

bool CSecuredInfo::IsWinNT()
{
	OSVERSIONINFO osVersion;
	osVersion.dwOSVersionInfoSize=sizeof(OSVERSIONINFO);
	GetVersionEx(&osVersion);
	bool isNT=(VER_PLATFORM_WIN32_NT==osVersion.dwPlatformId);
	return isNT;
}

bool CSecuredInfo::InitializeFileClassic()
{
	CString strFullName=m_strFilePath+CString("\\")+m_strFilename;
	HANDLE hFile=NULL;
	hFile=CreateFile(strFullName,
							GENERIC_READ|GENERIC_WRITE,
							0,
							NULL,
							CREATE_NEW,
							FILE_ATTRIBUTE_NORMAL,
							NULL);
	if(NULL==hFile)
	{
		return false;
	}
	else
	{
		CloseHandle(hFile);
		hFile=NULL;
		return true;
	}
}

bool CSecuredInfo::InitializeFileNT()
{
	typedef bool (*CreateFunc)(const char*);

	HINSTANCE hDll=NULL;
	hDll=LoadLibrary("NTSpecific.dll");
	if(NULL==hDll)
	{
		return false;
	}
	
	CreateFunc pfunc;
	pfunc=(CreateFunc)GetProcAddress(hDll,"CreateWritableFile");
	if(NULL==pfunc)
	{
		return false;
	}
	CString strFullName=m_strFilePath+CString("\\")+m_strFilename;
	bool result=pfunc(strFullName);

	FreeLibrary(hDll);
	return result;

}

bool CSecuredInfo::InitializeRegistry()
{
	CString strFullName=m_strRegistryPath+CString("\\")+m_strRegistryEntryName;
	
	HKEY hKey;	// key that will be created
	unsigned long createStatus=REG_OPENED_EXISTING_KEY;
	long result=RegCreateKeyEx(HKEY_CURRENT_USER,
								strFullName,
								0,
								NULL,
								REG_OPTION_NON_VOLATILE,
								KEY_ALL_ACCESS|KEY_QUERY_VALUE ,
								NULL,
								&hKey,
								&createStatus);
	if(ERROR_SUCCESS!=result)
	{
		return false;
	}
	RegCloseKey(hKey);
	return true;

}

bool CSecuredInfo::IsFileExists()
{
	CString strFullName=m_strFilePath+CString("\\")+m_strFilename;
	bool result=(0==_access(strFullName,0));
	return result;
}



bool CSecuredInfo::IsRegKeyExists()
{
	CString strFullName=m_strRegistryPath+CString("\\")+m_strRegistryEntryName;
	HKEY hKey;	// key that will be created
	long result=RegOpenKeyEx(HKEY_CURRENT_USER,
							strFullName,
							0,
							KEY_ALL_ACCESS,
							&hKey);
	if(ERROR_SUCCESS!=result)
	{
		return false;
	}
	RegCloseKey(hKey);
	return true;
}

CString CSecuredInfo::GetValueFromFile(const char *strSection, const char *strEntry)
{
	CAnyFileAccessor::GetInstance()->AccessToSomeFiles();

	CString filename=m_strFilePath+CString("\\")+m_strFilename;
	
	CString strResult;
	char buffer[256];
//	GetProfileString(strSection,strEntry,"",buffer,256,"");
	int nRead=GetPrivateProfileString(strSection,strEntry,"",buffer,256,filename);
	if(0==nRead)
	{
		return CString("");
	}
	CCoder *pCoder=CCoder::GetInstance();
	try
	{
		strResult=pCoder->getDecodedString(CString(buffer));
	}
	catch(...)
	{
		CAnyFileAccessor::GetInstance()->AccessToSomeFiles();
		return CString("");
	}

	CAnyFileAccessor::GetInstance()->AccessToSomeFiles();

	return strResult;
}

CString CSecuredInfo::GetValueFromRegistry(const char *strSection, const char *strEntry)
{
	// open key
	CString strKeyPath=m_strRegistryPath
						+CString("\\")
						+m_strRegistryEntryName
						+CString("\\")
						+CString(strSection);
	HKEY hKey;	// key that will be created
	long result=RegOpenKeyEx(HKEY_CURRENT_USER,
							strKeyPath,
							0,
							KEY_ALL_ACCESS,
							&hKey);
	if(ERROR_SUCCESS!=result)
	{
		return CString("");;
	}
	
	DWORD dataType=REG_SZ;
	char buffer[2048];
	DWORD size=2048;
	// get the value
	result=RegQueryValueEx(hKey,
							strEntry,
							NULL,
							&dataType,
							(unsigned char *)buffer,
							&size);
	if((ERROR_SUCCESS!=result)
		|| (REG_SZ!=dataType))
	{
		RegCloseKey(hKey);
		return CString("");
	}
	RegCloseKey(hKey);

	// translate
	CString strRead(buffer);
	CString strResult;
	try
	{
		strResult=CCoder::GetInstance()->getDecodedString(strRead);
	}
	catch(...)
	{
		strResult=CString("");
	}
	return strResult;	
}

bool CSecuredInfo::IsFileWritable()
{
	CString strFullName=m_strFilePath+CString("\\")+m_strFilename;
	bool result=(0==_access(strFullName,02));
	return result;	
}

bool CSecuredInfo::SetValueToFile(const char *strSection, const char *strEntry, const char *strValue)
{
	CAnyFileAccessor::GetInstance()->AccessToSomeFiles();
	
	CString filename=m_strFilePath+CString("\\")+m_strFilename;
	CString strCodedValue=CCoder::GetInstance()->getCodedString(strValue);
//	bool result=WriteProfileString(strSection,strEntry,strCodedValue,filename);
	bool result=WritePrivateProfileString(strSection,strEntry,strCodedValue,filename);

	CAnyFileAccessor::GetInstance()->AccessToSomeFiles();

	return result;
}

bool CSecuredInfo::SetValueToRegistry(const char *strSection, const char *strEntry, const char *strValue)
{
	CString strCodedValue=CCoder::GetInstance()->getCodedString(strValue);

	// open key
	CString strKeyPath=m_strRegistryPath
						+CString("\\")
						+m_strRegistryEntryName
						+CString("\\")
						+CString(strSection);
	HKEY hKey;	// key that will be created
/*	long result=RegOpenKeyEx(HKEY_CURRENT_USER,
							strKeyPath,
							0,
							0,
							&hKey);
							*/
	unsigned long createStatus=REG_OPENED_EXISTING_KEY;
	long result=RegCreateKeyEx(HKEY_CURRENT_USER,
								strKeyPath,
								0,
								NULL,
								REG_OPTION_NON_VOLATILE,
								KEY_ALL_ACCESS|KEY_QUERY_VALUE ,
								NULL,
								&hKey,
								&createStatus);
	if(ERROR_SUCCESS!=result)
	{
		return false;
	}

	bool written;
	result=RegSetValueEx(hKey,
						strEntry,
						0,
						REG_SZ,
						(const unsigned char*)(const char*)strCodedValue,
						strCodedValue.GetLength()+1);
	written=(ERROR_SUCCESS==result);
	RegCloseKey(hKey);
	return written;
	
}

CString CSecuredInfo::GetSystemDirectory()
{
	char buffer[256];
	::GetSystemDirectory(buffer,256);
	return buffer;
}

void CSecuredInfo::WriteFileSkeleton(ofstream &stream)
{

}

bool CSecuredInfo::CreateFileSkeleton()
{
	CString strFullName=m_strFilePath+CString("\\")+m_strFilename;
	ofstream file;
	file.open(strFullName);
	if(!file.is_open())
	{
		return false;
	}
	WriteFileSkeleton(file);
	return true;
}
