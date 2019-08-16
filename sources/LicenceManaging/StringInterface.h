// StringInterface.h: interface for the CStringInterface class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STRINGINTERFACE_H__E6A6ADA7_6C11_4442_B3E1_744454713B01__INCLUDED_)
#define AFX_STRINGINTERFACE_H__E6A6ADA7_6C11_4442_B3E1_744454713B01__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <map>
using namespace std;

class CStringInterface  
{
public:
	// enum used to use string indirectly : 
	//	their use location cannot be easily be found by desassembling the code
	typedef enum
	{
		kNameFieldEmpty,
		kLicenceKeyEmpty,
		kNoKeyCDVersion,
		kInstallNotCorrect,
		kUnknownError,
		kCannotWritePeriod,
		kAdministratorRights,
		kCannotWriteLicense,
		kLicenseKeyNotValid,
		kNbOfExportLeft,
		kNoExportLeft,
		kProductId,
		kPostFixId1,
		kPostFixId2,
		kPostFixId3,
		kPostFixIdN,
		kWelcomeFormat
	} LicenseStringEnum;

public:
	UINT GetStringID(LicenseStringEnum nEnum);
	static void Clear();
	static CStringInterface* GetInstance();

protected:
	CStringInterface();
	virtual ~CStringInterface();

protected:
	void FillMap();
	static CStringInterface* m_pInstance;
	map<int , UINT> m_StringMap;

};

#define GET_STRING_ID(id) CStringInterface::GetInstance()->GetStringID(CStringInterface::id)

#endif // !defined(AFX_STRINGINTERFACE_H__E6A6ADA7_6C11_4442_B3E1_744454713B01__INCLUDED_)
