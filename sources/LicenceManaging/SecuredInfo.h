// SecuredInfo.h: interface for the CSecuredInfo class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SECUREDINFO_H__2D6EE0C5_8E46_4748_BAB9_2AD92562ADF7__INCLUDED_)
#define AFX_SECUREDINFO_H__2D6EE0C5_8E46_4748_BAB9_2AD92562ADF7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <fstream>
using namespace std;

class CSecuredInfo  
{
public:
	CSecuredInfo();
	CSecuredInfo(const char* fileName,
				 const char* filePath,
				 const char* regEntry,
				 const char* regPath);
	virtual ~CSecuredInfo();

public:
	CString GetSystemDirectory();
	bool IsInitialized();
	bool SetValue(const char * strSection,const char* strEntry, const char* strValue);
	CString GetValue(const char* strSection, const char* strEntry);

protected:
	bool SetValueToRegistry(const char *strSection, const char *strEntry, const char *strValue);
	bool SetValueToFile(const char *strSection, const char *strEntry, const char *strValue);
	bool IsFileWritable();
	CString GetValueFromRegistry(const char *strSection, const char *strEntry);
	CString GetValueFromFile(const char* strSection, const char *strEntry);
	bool IsRegKeyExists();
	bool IsFileExists();
	bool InitializeRegistry();
	bool InitializeFileNT();
	bool InitializeFileClassic();
	bool IsWinNT();
	bool InitializeFile();
	bool InitializeSupport();

	// attributes
protected:
	bool CreateFileSkeleton();
	virtual void WriteFileSkeleton(ofstream& stream)=0;
	CString m_strFilename;
	CString m_strFilePath;
	CString m_strRegistryEntryName;
	CString m_strRegistryPath;
	bool m_bUsefile;

};

#endif // !defined(AFX_SECUREDINFO_H__2D6EE0C5_8E46_4748_BAB9_2AD92562ADF7__INCLUDED_)
