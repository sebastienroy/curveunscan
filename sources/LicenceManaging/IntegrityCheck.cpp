// IntegrityCheck.cpp: implementation of the CIntegrityCheck class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "licencemanaging.h"
#include "IntegrityCheck.h"

#include "LicenceManagingResources.h"
//#include "Crc32Dynamic.h"
#include "Coder.h"
#include "StringInterface.h"

#include "../Utilities/RegularExpressions.h"
#include <md5/MD5Checksum.h>

#include <fstream>
using namespace std;

#include <io.h>


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CIntegrityCheck* CIntegrityCheck::m_pInstance=NULL;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CIntegrityCheck::CIntegrityCheck(const char* filenameWithPath)
:	m_pThread(NULL),
	m_strFileToCheck(filenameWithPath)
{
	CString strChkFile(filenameWithPath);
	RegSearchReplaceOnce(strChkFile,"\\.([^\\.]+)$", "");
	strChkFile+=CString(".")+CString(CHECKSUM_FILENAME_EXT);
	m_strCheckFile=strChkFile;
	CString strRead1;
	CString strRead2;
	try
	{
		char buffer[256];
		ifstream checkFile;
		checkFile.open(m_strCheckFile);
		checkFile >> buffer;
		strRead1=CString(buffer);
		checkFile >> buffer;
		strRead2=CString(buffer);
	}
	catch(...)
	{
		strRead1=strRead2="";
	}
	m_strReadChecksum=CMD5Checksum::GetMD5((BYTE*)(LPCSTR)strRead1,strRead1.GetLength());
	m_strReadDataScrambler=CMD5Checksum::GetMD5((BYTE*)(LPCSTR)strRead2,strRead2.GetLength());
}

CIntegrityCheck::~CIntegrityCheck()
{
}

UINT CIntegrityCheck::ThreadFunc(LPVOID pParam)
{
	IntegrityParams *integParams=(IntegrityParams *)pParam;
	CString strFileToCheck=integParams->strFileToCheck;
	CString strCheckFile=integParams->strCheckFile;
	CString strMD5CodedRead=integParams->strMD5CodedReadChecksum;
	delete integParams;

#if !defined(_DEBUG)
	int nMili=3*30*1000;
#else
	int nMili=5*1000;	// only 5 seconds in debug mode
#endif // !defined(_DEBUG)

	::Sleep(nMili);

	CString strTemp=CCoder::GetInstance()->GetCheckSumValue(strFileToCheck);
	CString strMD5CodedChecksum=CMD5Checksum::GetMD5((BYTE*)(LPCSTR)strTemp,strTemp.GetLength());

	if(strMD5CodedChecksum!=strMD5CodedRead)
	{
#if defined(_DEBUG)
		AfxMessageBox("Checksum failed!");
#endif // defined(_DEBUG)
		exit(-1);
	}

	return 0;
}

void CIntegrityCheck::LaunchCheck()
{

	// launch the checking thread
	IntegrityParams *pParams=new IntegrityParams;
	pParams->strFileToCheck=m_strFileToCheck;
	pParams->strCheckFile=m_strCheckFile;
	pParams->strMD5CodedReadChecksum=m_strReadChecksum;

	m_pThread=AfxBeginThread(ThreadFunc,pParams);
}


void CIntegrityCheck::DisplayInstallPb()
{
	CString msg;
	msg.LoadString(GET_STRING_ID(kInstallNotCorrect));
	AfxMessageBox(msg);
}

bool CIntegrityCheck::IsInstallOk()
{
	// first check the file existence
	if( (0!=_access(m_strFileToCheck,04))
		|| (0!=_access(m_strCheckFile,04)) )
	{
		DisplayInstallPb();
		return false;
	}

	return true;
}

CIntegrityCheck* CIntegrityCheck::Init(const char* filenameWithPath)
{
	if(NULL==m_pInstance)
	{
		m_pInstance=new CIntegrityCheck(filenameWithPath);
	}
	return m_pInstance;
}

void CIntegrityCheck::Clear()
{
	delete m_pInstance;
	m_pInstance=NULL;
}

CIntegrityCheck* CIntegrityCheck::getInstance()
{
	return m_pInstance;
}

CString CIntegrityCheck::getReadDataScrambler()
{
	return m_strReadDataScrambler;
}

CString CIntegrityCheck::getFileToCheck()
{
	return m_strFileToCheck; 
}