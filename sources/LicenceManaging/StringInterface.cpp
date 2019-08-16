// StringInterface.cpp: implementation of the CStringInterface class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "licencemanaging.h"
#include "StringInterface.h"

#include "..\main\resource.h"

#include <assert.h>
using namespace std;

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CStringInterface* CStringInterface::m_pInstance=NULL;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CStringInterface::CStringInterface()
{
	FillMap();
}

CStringInterface::~CStringInterface()
{

}

CStringInterface* CStringInterface::GetInstance()
{
	if(NULL==m_pInstance)
	{
		m_pInstance=new CStringInterface;
	}
	return m_pInstance;
}

void CStringInterface::Clear()
{
	delete m_pInstance;
	m_pInstance=NULL;
}

void CStringInterface::FillMap()
{
	m_StringMap.insert(pair<int , UINT>(kNameFieldEmpty,IDS_NAME_FIELD_EMPTY));
	m_StringMap.insert(pair<int , UINT>(kLicenceKeyEmpty,IDS_LICENCE_KEY_EMPTY));
	m_StringMap.insert(pair<int , UINT>(kNoKeyCDVersion,IDS_NOKEY_CDVERSION));
	m_StringMap.insert(pair<int , UINT>(kInstallNotCorrect,IDS_INSTALL_NOT_CORRECT));
	m_StringMap.insert(pair<int , UINT>(kUnknownError,IDS_UNKNOWN_ERROR));
	m_StringMap.insert(pair<int , UINT>(kCannotWritePeriod,IDS_CANNOT_WRITE_PERIOD));
	m_StringMap.insert(pair<int , UINT>(kAdministratorRights,IDS_ADMINISTRATOR_RIGHTS));
	m_StringMap.insert(pair<int , UINT>(kCannotWriteLicense,IDS_CANNOT_WRITE_LICENCE));
	m_StringMap.insert(pair<int , UINT>(kLicenseKeyNotValid,IDS_LICENCE_KEY_NOT_VALID));
	m_StringMap.insert(pair<int , UINT>(kNbOfExportLeft,IDS_NB_OF_EXPORT_LEFT));
	m_StringMap.insert(pair<int , UINT>(kNoExportLeft,IDS_NO_EXPORT_LEFT));
	m_StringMap.insert(pair<int , UINT>(kProductId,IDS_PRODUCTID));
	m_StringMap.insert(pair<int , UINT>(kPostFixId1,IDS_POSTFIX1));
	m_StringMap.insert(pair<int , UINT>(kPostFixId2,IDS_POSTFIX2));
	m_StringMap.insert(pair<int , UINT>(kPostFixId3,IDS_POSTFIX3));
	m_StringMap.insert(pair<int , UINT>(kPostFixIdN,IDS_POSTFIX_NTH));
	m_StringMap.insert(pair<int , UINT>(kWelcomeFormat,IDS_WELCOME_FORMAT));
}

UINT CStringInterface::GetStringID(LicenseStringEnum nEnum)
{
	UINT nResult=0;
	map<int, UINT>::iterator iter=m_StringMap.find(nEnum);
	if(m_StringMap.end()!=iter)
	{
		pair<int, UINT> paire=*iter;
		nResult=paire.second;
	}
	else
	{
		assert(false);
	}
	return nResult;
}

