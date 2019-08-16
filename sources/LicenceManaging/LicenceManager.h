// LicenceManager.h: interface for the CLicenceManager class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LICENCEMANAGER_H__6802A486_3668_11D5_935E_F409C9E7C178__INCLUDED_)
#define AFX_LICENCEMANAGER_H__6802A486_3668_11D5_935E_F409C9E7C178__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#pragma warning(disable : 4290)	// exception specification warning

#include "StringInterface.h"

class CCoder;
class CLicenceException;
struct SVersionInfo;
class CExportNbInfo;
class CFirstUseInfo;




// registration state
typedef enum
	{
		kRegistered=19,	// using an other default value than 0 is best
		kUnderEvaluation,
		kNoRight,
		kInstallPb
	} RegistrationStateEnum;




// singleton
class CLicenceManager  
{


protected:
	CLicenceManager();
public:
	virtual ~CLicenceManager();
public:
	RegistrationStateEnum GetRegistrationState();
	RegistrationStateEnum CheckLicence();
	CString GetVersion() const;
	bool HaveRightToExport();
	int GetInitialExportNb() const;
	void DecreaseNbOfExportLeft();
	int GetNbOfExportLeft();
	static void FillVersionInfo(SVersionInfo &version);
	bool Register();
	static void Destroy();
	CString GetCompanyName();
	CString GetName();
	bool IsIntoEvaluationPeriod();
	bool IsRegistered();
	CString GetProductID();
	static CLicenceManager& GetInstance();
	CString GetStrBuildNb() const;

protected:
	void CloseKeys();
	HKEY GetInfoKey();
	HKEY GetPeriodKey();
	void ShowSorryDlg();
	void ShowWelcomeDlg();
	bool AskLicenceKey() throw(CLicenceException);
	CString m_strCompanyName;
	CString m_strName;
	int m_nDays;
	bool m_bRegistered;
	bool WriteRegistryString(HKEY hKey,const CString strEntry,const CString strValue);
	CString GetRegistryString(HKEY hKey, CString strValueName);
//	CCoder* m_pCoder;
	bool OpenPeriodKey(HKEY& hKey);
	HKEY m_hInfoKey;		// stores the owner info : name, comp. name, key.
	HKEY m_hPeriodKey;		// stores, in coded form, the date of the first use
	static CString m_strThisVersion;
	static CString m_strMyCompany;
	static CString m_ProductID;
	static CLicenceManager* m_Instance;
	static bool m_bIsCDVersion;
	CExportNbInfo *m_pExportNbInfo;
	CFirstUseInfo *m_pFirstUseInfo;


};

#endif // !defined(AFX_LICENCEMANAGER_H__6802A486_3668_11D5_935E_F409C9E7C178__INCLUDED_)
