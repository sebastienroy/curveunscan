// Coder.h: interface for the CCoder class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CODER_H__68DE40C9_3713_11D5_935E_BAB3637C2579__INCLUDED_)
#define AFX_CODER_H__68DE40C9_3713_11D5_935E_BAB3637C2579__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <list>
#include <vector>
using namespace std;

class CCoder  
{
	// singleton method
protected:
	CCoder();
	CCoder(CString strCodeKey);
	virtual ~CCoder();
	static CCoder* m_pInstance;

public:
	static void Clear();
	static CCoder* GetInstance();
	static CCoder* GetInstanceV1(CString strCodeKey);
	static CCoder* GetInstanceV2(CString strCodeKey);
	

public:
	CString GetDataScramblingValue(const char *filename);
	CString GetCheckSumValue(const char* filename);
	CString Strip(const CString& string) const;
	virtual CString GetMd5CodedRegistrationNumber();
	CString getDecodedString(const CString &inString) const;
	CString getCodedString(const CString &inString) const;
	CString getCodeKey() const { return  m_strCodeKey; }
	bool isRegistrationCodeCorrect(CString strSerial, CString strName, CString strCompany,CString strCode);
	virtual CString getRegistrationNumber(CString strSerial,CString strName,CString strCompany);
	void getFirstNumbers(vector<int>& firstNumberVector,int nNumbers) const;
	CString getCodedString(const CString& inString, const CString& inKey) const;
	CString getDecodedString(const CString& inString, const CString& inKey) const;
	char getCharFromValue(int value) const;
	int getCharValue(char inChar) const;
	CTime GetDecodedTime(CString strTime); 
	CString DecodeString(const CString& inString);
	CString EncodeString(const CString& inString);
	CString GetEncodedTimeStamp();

protected:
	char GetCodeChar(int index);
	char GetDecodedChar(char aChar, char codeChar) const;
	char GetEncodedChar(char aChar,char codeChar) const;
	CString m_strCodeKey;
//	mutable CString m_strCurrentKey;
	mutable CString m_strCurrentName;
	mutable CString m_strCurrentCompany;
	mutable CString m_strCurrentSerial;
};

#endif // !defined(AFX_CODER_H__68DE40C9_3713_11D5_935E_BAB3637C2579__INCLUDED_)
