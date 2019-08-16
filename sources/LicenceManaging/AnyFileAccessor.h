// AnyFileAccessor.h: interface for the CAnyFileAccessor class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ANYFILEACCESSOR_H__2A6D517B_49B2_4819_8C29_9592FD36C7B3__INCLUDED_)
#define AFX_ANYFILEACCESSOR_H__2A6D517B_49B2_4819_8C29_9592FD36C7B3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <list>
using namespace std;

class CAnyFileAccessor  
{
protected:
	CAnyFileAccessor(const char *rootDir);
	virtual ~CAnyFileAccessor();

public:
	static void Clear();
	void AccessToSomeFiles();
	static CAnyFileAccessor* GetInstance();
	

protected:
	void ReadFile(const char *filename);
	CString m_strRootdir;
	list<CString> m_SubDirList;
	static CAnyFileAccessor *m_pInstance;

};

#endif // !defined(AFX_ANYFILEACCESSOR_H__2A6D517B_49B2_4819_8C29_9592FD36C7B3__INCLUDED_)
