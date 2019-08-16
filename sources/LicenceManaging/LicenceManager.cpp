// LicenceManager.cpp: implementation of the CLicenceManager class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "LicenceManager.h"
#include "LicenceManagingResources.h"
#include "../Utilities/UnscanException.h"
#include "../Utilities/VersionInfo.h"
#include "../Utilities/Tools.h"
#include "LicenceException.h"
#include "Coder.h"
#include "WelcomeDialog.h"
#include "LicenceDlg.h"
#include "SorryDlg.h"
#include "FirstUseInfo.h"
#include "ExportNbInfo.h"
#include "../main/resource.h"
#include "AnyFileAccessor.h"
#include "StringInterface.h"

#include <md5/md5checksum.h>

#include <assert.h>
using namespace std;

//////////////////////////////////////////////////////////////////////
// static members
//////////////////////////////////////////////////////////////////////

CLicenceManager* CLicenceManager::m_Instance=NULL;

CString CLicenceManager::m_ProductID=SERIAL;		// definition into LicenceManagingResources file
CString CLicenceManager::m_strMyCompany=MYCOMPANY;
CString CLicenceManager::m_strThisVersion=THISVERSION;

#if defined(CD_VERSION)
bool CLicenceManager::m_bIsCDVersion(true);
#else
bool CLicenceManager::m_bIsCDVersion(false);
#endif



//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLicenceManager::CLicenceManager()
:	m_pExportNbInfo(NULL),
	m_pFirstUseInfo(NULL),
	m_bRegistered(false),
	m_nDays(-1),
	m_hPeriodKey(NULL),
	m_hInfoKey(NULL)
{
}

CLicenceManager::~CLicenceManager()
{
	CloseKeys();
	delete m_pExportNbInfo;
	delete m_pFirstUseInfo;
}

CLicenceManager& CLicenceManager::GetInstance()
{
	if(NULL==m_Instance)
		{
		m_Instance=new CLicenceManager;
		}
	return *m_Instance;
}

RegistrationStateEnum CLicenceManager::CheckLicence()
{

	RegistrationStateEnum state=GetRegistrationState();

	RegistrationStateEnum stateCopy=state;

#if defined(CD_VERSION)
	if(kRegistered != stateCopy)
	{
		AskLicenceKey();	// (return true if the licence is the good one)
		state=GetRegistrationState();
	}
#else
	if( kUnderEvaluation==stateCopy )
	{
		ShowWelcomeDlg();
		state=GetRegistrationState();
	}
	else if( kInstallPb==stateCopy)
	{
		UINT iD=GET_STRING_ID(kInstallNotCorrect);
		AfxMessageBox(iD,MB_OK|MB_ICONSTOP);
	}
	else if( kNoRight==stateCopy )
	{
		ShowSorryDlg();
		state=GetRegistrationState();
	}
#endif

	return state;
}

// Open the registry key where are located licence data.
// If the key doesn't already exists, create it and return true, otherwise, return false
// Throws, if fail to open the key 
bool CLicenceManager::OpenPeriodKey(HKEY &hKey)
{
	HKEY baseKey=SECURITYROOTKEY;
	unsigned long createStatus=REG_OPENED_EXISTING_KEY;
	LONG result;
	CString strPeriodKeyPath=STRPERIODKEYPATH;

	result=RegOpenKeyEx(baseKey,
						strPeriodKeyPath,
						0,
						KEY_READ,
						&hKey);
	if(ERROR_SUCCESS!=result)	// key doesn't exist? So create it
		{
		result=RegCreateKeyEx(baseKey,
							strPeriodKeyPath,
							0,
							NULL,
							REG_OPTION_NON_VOLATILE,
							KEY_ALL_ACCESS|KEY_QUERY_VALUE ,
							NULL,
							&hKey,
							&createStatus);
		if(ERROR_SUCCESS!=result)
			{
			CString msg;
			msg.LoadString(GET_STRING_ID(kCannotWritePeriod));
			throw CLicenceException(msg,CLicenceException::kCannotWritePeriod);
			}

		// write entry
		CCoder *pCoder=CCoder::GetInstance();
		CString strDate=pCoder->GetEncodedTimeStamp();
		bool written=WriteRegistryString(hKey,DATE_ENTRY,strDate);
		if(!written)
			{
			CString msg;
			msg.LoadString(GET_STRING_ID(kCannotWritePeriod));
			throw CLicenceException(msg,CLicenceException::kCannotWritePeriod);
			}
		}


	return (REG_CREATED_NEW_KEY==createStatus);
}


CString CLicenceManager::GetRegistryString(HKEY hKey, CString strValueName)
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

bool CLicenceManager::WriteRegistryString(HKEY hKey, const CString strEntry, const CString strValue)
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

CString CLicenceManager::GetProductID()
{
	return m_ProductID;
}

bool CLicenceManager::IsRegistered()
{
	RegistrationStateEnum state=kNoRight;

	try
	{
		//--- Check licence key if any
		CString strLicenceKey=GetRegistryString(GetInfoKey(),"Key");
		strLicenceKey=CCoder::GetInstance()->Strip(strLicenceKey);
		CString strName=GetRegistryString(GetInfoKey(),"Name");
		CString strMd5CodedKey=CMD5Checksum::GetMD5((BYTE*)(LPCSTR)strLicenceKey,strLicenceKey.GetLength());
		CString strCompanyName=GetRegistryString(GetInfoKey(),"CompanyName");
		if((!strLicenceKey.IsEmpty())&&(CCoder::GetInstance()->isRegistrationCodeCorrect(m_ProductID,strName,strCompanyName,strMd5CodedKey) ) )
		{
			state=kRegistered;
			m_strName=strName;
			m_strCompanyName=strCompanyName;
		}
	}
	catch(CLicenceException)
	{
		return false;
	}
	catch(...)
	{
		return false;
	}
	return (kRegistered==state);
}

bool CLicenceManager::IsIntoEvaluationPeriod()
{
	bool result=(m_nDays>0)&&(m_nDays<31);
	return result;
}

CString CLicenceManager::GetName()
{
	return m_strName;
}

CString CLicenceManager::GetCompanyName()
{
	return m_strCompanyName;
}

bool CLicenceManager::AskLicenceKey() throw(CLicenceException)
{
	CLicenceDlg dlg;
	if(IDOK==dlg.DoModal())
		{
		CString strKey=dlg.m_strLicence;
		CString strName=dlg.m_strName;
		strKey=CCoder::GetInstance()->Strip(strKey);
		CString strMD5CodedKey=CMD5Checksum::GetMD5((BYTE*)(LPCSTR)strKey,strKey.GetLength());
		CString strCompName=dlg.m_strCompanyName;
		if(CCoder::GetInstance()->isRegistrationCodeCorrect(m_ProductID,strName,strCompName,strMD5CodedKey))
			{
			m_bRegistered=true;
			bool bOk=true;
			bOk&=WriteRegistryString(GetInfoKey(),"Name",strName);
			bOk&=WriteRegistryString(GetInfoKey(),"CompanyName",strCompName);
			bOk&=WriteRegistryString(GetInfoKey(),"Key",strKey);
			if(!bOk)
				{
				AfxMessageBox(GET_STRING_ID(kAdministratorRights),MB_OK|MB_ICONSTOP);
				return false;
				//CString msg;
				//msg.LoadString(IDS_CANNOT_WRITE_LICENCE);
				//throw CLicenceException(msg,kCannotWriteLicence);
				}
			m_strName=strName;
			m_strCompanyName=strCompName;
			return true;
			}
		else
			{
			CString msg;
			msg.LoadString(GET_STRING_ID(kLicenseKeyNotValid));
			AfxMessageBox(msg,MB_OK|MB_ICONEXCLAMATION);
			}
		}
	return false;
}

void CLicenceManager::ShowWelcomeDlg()
{
	// welcome evaluating
	if(m_nDays>TEST_PERIOD_DAYS_NB)
	{
		exit(-1);
	}
	CWelcomeDialog dlg(m_nDays,GetProductID(),GetInitialExportNb(),GetNbOfExportLeft());
	bool showWelcome=true;
	while(showWelcome)
		{
		if(IDOK==dlg.DoModal())
			{
			showWelcome=!AskLicenceKey();	// (return true if the licence is the good one)
			}
		else
			{
			showWelcome=false;
			}
		}

}

void CLicenceManager::ShowSorryDlg()
{
	try
		{
		CSorryDlg dlg(GetProductID());
		bool showWelcome=true;
		while(showWelcome)
			{
			if(IDOK==dlg.DoModal())
				{
				showWelcome=!AskLicenceKey();	// (return true if the licence is the good one)
				}
			else
				{
				showWelcome=false;
				}
			}
		}
	catch(CLicenceException& err)
		{
		AfxMessageBox(err.GetMessage(),MB_OK|MB_ICONSTOP);
		}
}

HKEY CLicenceManager::GetPeriodKey()
{
	if(NULL==m_hPeriodKey)
		{
		OpenPeriodKey(m_hPeriodKey);
		}
	return m_hPeriodKey;
}

HKEY CLicenceManager::GetInfoKey()
{
	if(NULL==m_hInfoKey)
		{
		HKEY baseKey=HKEY_LOCAL_MACHINE;
		unsigned long createStatus;
		LONG result;
		CString path;
		path.Format("Software\\%s\\CurveUnscan\\%s",m_strMyCompany,m_strThisVersion);
		
		result=RegCreateKeyEx(baseKey,
							path,
							0,
							NULL,
							REG_OPTION_NON_VOLATILE,
							KEY_ALL_ACCESS|KEY_QUERY_VALUE ,
							NULL,
							&m_hInfoKey,
							&createStatus);
		if(ERROR_SUCCESS!=result)	// cannot have read-write access, so 
			{						//		try to get read-only access
			result=RegOpenKeyEx(baseKey,
								path,
								0,
								KEY_READ,
								&m_hInfoKey);
			}
		}
	return m_hInfoKey;

}

void CLicenceManager::CloseKeys()
{
	if(NULL!=m_hInfoKey)
		{
		RegCloseKey(m_hInfoKey);
		m_hInfoKey=NULL;
		}
	if(NULL!=m_hPeriodKey)
		{
		RegCloseKey(m_hPeriodKey);
		m_hPeriodKey=NULL;
		}
}

void CLicenceManager::Destroy()
{
	delete m_Instance;
	m_Instance=NULL;
	// destroy too the other singletons
	CAnyFileAccessor::Clear();
	CCoder::Clear();
}

// Method called by the about box
bool CLicenceManager::Register()
{
	return AskLicenceKey();
}


void CLicenceManager::FillVersionInfo(SVersionInfo &version)
{
	version.m_nMajorVersion=MAJORVERSION_NB;
	version.m_nMinorVersion=MINORVERSION_NB;
	version.m_strManufacturer=CString(MYCOMPANY);
	version.m_strAppName=CString(SOFTWARENAME);
	version.m_strInfo=CString(THISVERSION);
	version.m_strInfo+=CString(" ");
	version.m_strInfo+=CString(SERIAL);
}

int CLicenceManager::GetNbOfExportLeft() 
{
	if(NULL==m_pExportNbInfo)
	{
		m_pExportNbInfo=new CExportNbInfo;
	}
	return m_pExportNbInfo->GetNbOfExportLeft();
}

void CLicenceManager::DecreaseNbOfExportLeft() 
{
	if(!IsRegistered())
	{
		if(NULL==m_pExportNbInfo)
		{
			m_pExportNbInfo=new CExportNbInfo;
		}	
		int nLeft=m_pExportNbInfo->DecreaseNbOfExportLeft();
		CString strFormat;
		strFormat.LoadString(GET_STRING_ID(kNbOfExportLeft));
		CString msg;
		msg.Format(strFormat,nLeft);
		AfxMessageBox(msg,MB_OK|MB_ICONINFORMATION);
	}

}

int CLicenceManager::GetInitialExportNb() const
{
	return INITIAL_EXPORT_NB;
}

bool CLicenceManager::HaveRightToExport() 
{
	if(IsRegistered())
	{
		return true;
	}
	else
	{
		int nLeft=GetNbOfExportLeft();
		if(nLeft<=0)
		{
			AfxMessageBox(GET_STRING_ID(kNoExportLeft),MB_OK);
			return false;
		}
		else
		{
			return true;
		}
	}
}

CString CLicenceManager::GetVersion() const
{
	return CString(THISVERSION);
}


RegistrationStateEnum CLicenceManager::GetRegistrationState()
{
	RegistrationStateEnum state=kNoRight;

	try
	{
		//--- Check licence key if any
		CString strName=GetRegistryString(GetInfoKey(),"Name");
		CString strCompanyName=GetRegistryString(GetInfoKey(),"CompanyName");
		CString strLicenceKey=GetRegistryString(GetInfoKey(),"Key");
		strLicenceKey=CCoder::GetInstance()->Strip(strLicenceKey);
		CString strMd5CodedKey=CMD5Checksum::GetMD5((BYTE*)(LPCSTR)strLicenceKey,strLicenceKey.GetLength());
		if((!strLicenceKey.IsEmpty())&&(CCoder::GetInstance()->isRegistrationCodeCorrect(m_ProductID,strName,strCompanyName,strMd5CodedKey) ) )
		{
			state=kRegistered;
			m_strName=strName;
			m_strCompanyName=strCompanyName;
		}
	}
	catch(CLicenceException)
	{
		// do nothing, no need now
	}
	catch(...)
	{
		// do nothing, no need now
	}

#if !defined(CD_VERSION)

	if(kRegistered!=state)		//--- no licence key, so check time
	{
		try
		{
			int nDays=100;
			m_nDays=48;		// Why? Why not?
			CString strTime=GetRegistryString(GetPeriodKey(),DATE_ENTRY);
			if(""==strTime)
			{
				throw CLicenceException("No date entry");
			}
			try
			{
				if(NULL==m_pFirstUseInfo)
				{
					m_pFirstUseInfo=new CFirstUseInfo;
				}
				if(!m_pFirstUseInfo->ConfirmDate(strTime))	// uses a file to perform further tests
				{
					throw CLicenceException("");
				}
				CTime initialTime=CCoder::GetInstance()->GetDecodedTime(strTime); // throws if format not correct
				CTime currentTime=CTime::GetCurrentTime();
				CTimeSpan ts=currentTime-initialTime;
				nDays=ts.GetDays()+1;	
				m_nDays=nDays;
			}
			catch(...)
			{
				nDays=100;
			}
			// now a difficult task : compare the nb of days without be visible from a hacker
			if((nDays>0)&&(nDays<TEST_PERIOD_DAYS_NB))
			{
				state=kUnderEvaluation;
			}
		}
		catch(...)
		{
			state=kInstallPb;
		}
	}
#endif // !defined(CD_VERSION)

	CloseKeys();
	return state;	

}

CString CLicenceManager::GetStrBuildNb() const
{
	return BUILD_NB;
}