// KeyGenerator.cpp
//

#include "stdafx.h"

#include "KeyGenerator.h"
#include "ArgsParser.h"

#include <LicenceManaging/CoderV2.h>
#include <LicenceManaging/Coder.h>

#include "key_intf.h"

#include <strstream>
using namespace std;


// Constructor / Destructor

CKeyGenerator::CKeyGenerator(CArgsParser* parser, char* result1, char* result2)
:	m_pParser(parser),
	m_pResult1(result1),
	m_pResult2(result2),
	m_Language(liEnglish)
{
}

CKeyGenerator::~CKeyGenerator()
{
}

CKeyGenerator::generate()
{
	if(0==m_pParser->getSize())
	{
		strcpy(m_pResult1, "Could not parse args!");
		return ERC_BAD_INPUT;
	}


	// Read language
	CString strLanguage=m_pParser->getValue("LANGUAGE_ID");
	if(strLanguage.IsEmpty())
	{
		m_Language=liEnglish;
	}
	else
	{
		m_Language=atoi(strLanguage);
	}

	CString strName=m_pParser->getValue("REG_NAME");
	strName.TrimLeft();
	strName.TrimRight();
	if(strName.IsEmpty())
	{
		CString msg=(liFrench==m_Language)?"Le nom d'utilisateur ne doit pas etre vide":"The user name must not be empty !";
		strcpy(m_pResult1,msg);
		return ERC_BAD_INPUT;
	}
	if(strName.GetLength()>100)
	{
		CString msg=(liFrench==m_Language)?"Le nom d'utilisateur est limite a 100 caracteres":"The user name is limited to 100 characters !";
		strcpy(m_pResult1,msg);
		return ERC_BAD_INPUT;
	}

	CString strCompanyName=m_pParser->getValue("COMPANY");
	strCompanyName.TrimLeft();
	strCompanyName.TrimRight();
	if(strCompanyName.IsEmpty())
	{
		strCompanyName=(liFrench==m_Language)?"Particulier":"Private";
	}
	if(strCompanyName.GetLength()>100)
	{
		CString msg=(liFrench==m_Language)?"Le nom de l'entreprise est limite a 100 caracteres":"The company name is limited to 100 characters !";
		strcpy(m_pResult1,msg);
		return ERC_BAD_INPUT;
	}

	CString strSerialNb=m_pParser->getValue("ADDITIONAL1");
	strSerialNb.TrimLeft();
	strSerialNb.TrimRight();
	strSerialNb.MakeUpper();
	if(strSerialNb.IsEmpty())
	{
		CString msg=(liFrench==m_Language)?"Numero de serie vide, (champ additionel 1)...":"Empty serial number (field ADDITIONAL1)...";
		strcpy(m_pResult1,msg);
		return ERC_BAD_INPUT;
	}

	CCoder* pCoder;
	if( (strSerialNb=="V110PR23") || 
		(strSerialNb=="V120PR28") || 
		(strSerialNb=="V130PR31")    )
	{
		pCoder=CCoder::GetInstanceV1("SNI06POTDE");
	}
	else
	{
		pCoder=CCoder::GetInstanceV2("SNI06POTDE");
	}

	CString strLicenseKey=pCoder->getRegistrationNumber(strSerialNb,strName,strCompanyName);
	CCoder::Clear();
	if(strLicenseKey.IsEmpty())
	{
		CString msg=(liFrench==m_Language)?"Erreur dans la generation de cle de licence...":"Error during the licence key generation...";
		strcpy(m_pResult1,msg);
		return ERC_INTERNAL;
	}

	// Everything seams to be ok...
	ostrstream englMsg;
	englMsg << "Name : " << LPCTSTR(strName)
		<< "\r\nCompany name : " << LPCTSTR(strCompanyName) 
		<< "\r\nLicense key : " << LPCTSTR(strLicenseKey) << ends;
	ostrstream frenchMsg;
	frenchMsg << "Nom : " << LPCTSTR(strName) 
		<< "\r\nNom de l'entreprise : " << LPCTSTR(strCompanyName) 
		<< "\r\nClef de licence : " << LPCTSTR(strLicenseKey) << ends;

	// result1
	if(liFrench==m_Language)
	{
		strcpy(m_pResult1,frenchMsg.rdbuf()->str());
	}
	else
	{
		strcpy(m_pResult1,englMsg.rdbuf()->str());
	}
	// result2 (always english)
	strcpy(m_pResult2,englMsg.rdbuf()->str());


	return ERC_SUCCESS;
}