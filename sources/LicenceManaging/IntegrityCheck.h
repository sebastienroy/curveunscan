// IntegrityCheck.h: interface for the CIntegrityCheck class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_INTEGRITYCHECK_H__B2BD7B41_5A18_42B2_B988_4516DFB6D930__INCLUDED_)
#define AFX_INTEGRITYCHECK_H__B2BD7B41_5A18_42B2_B988_4516DFB6D930__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CIntegrityCheck  
{
public:
	struct IntegrityParams
	{
		CString strFileToCheck;
		CString strCheckFile;
		CString strMD5CodedReadChecksum;
//		HANDLE hWnd;
	};

public:
	static CIntegrityCheck* Init(const char* filenameWithPath);

public:
	static void Clear();
	bool IsInstallOk();
	void LaunchCheck();
	static CIntegrityCheck* getInstance();
	CString getReadDataScrambler();
	CString getFileToCheck();


protected:
	void DisplayInstallPb();
	CIntegrityCheck(const char* filenameWithPath);
	virtual ~CIntegrityCheck();
	static UINT ThreadFunc(LPVOID pParam);

protected:
	static CIntegrityCheck* m_pInstance;
	CString m_strCheckFile;
	CString m_strFileToCheck;
	CString m_strReadChecksum;
	CString m_strReadDataScrambler;
	CWinThread *m_pThread;

};

#endif // !defined(AFX_INTEGRITYCHECK_H__B2BD7B41_5A18_42B2_B988_4516DFB6D930__INCLUDED_)
