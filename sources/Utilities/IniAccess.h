// IniAccess.h: interface for the IniAccess class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_INIACCESS_H__A33403A7_FD7B_4F9D_9C56_88F7F23BCD45__INCLUDED_)
#define AFX_INIACCESS_H__A33403A7_FD7B_4F9D_9C56_88F7F23BCD45__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <list>
using namespace std;

class IniAccess  
{
public:
	static void GetEntries(const char *strSection, list<CString> &outEntriesList, const char *strFilename);
	static void GetSections(list<CString> &outSectionList, const char *strFilename);
	static void WriteInt(const char *strSection, const char * strEntry, int nValue, const char* strFilename);
	static void WriteString(const char* strSection, const char* strEntry, const char *strValue, const char *strFilename);
	static int GetInt(const char* strSection, const char *strEntry, int nDefault, const char *strFilename);
	static CString GetString(const char* strSection, const char *strEntry, const char* strDefault, const char* strFilename);
	IniAccess();
	virtual ~IniAccess();

};

#endif // !defined(AFX_INIACCESS_H__A33403A7_FD7B_4F9D_9C56_88F7F23BCD45__INCLUDED_)
