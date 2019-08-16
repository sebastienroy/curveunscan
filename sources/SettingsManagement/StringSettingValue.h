// StringSettingValue.h: interface for the CStringSettingValue class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STRINGSETTINGVALUE_H__06A04FFC_BFFB_495A_A9AC_E1E369243289__INCLUDED_)
#define AFX_STRINGSETTINGVALUE_H__06A04FFC_BFFB_495A_A9AC_E1E369243289__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "AbstractSettingValue.h"

#define EmptyRegExp CString(".*")

class CStringSettingValue : public CAbstractSettingValue  
{
public:
	CStringSettingValue(const char *strSection,
						const char *strEntry,
						const char *strDefaultValue,
						const char *strPermittedValues);
	virtual ~CStringSettingValue();

public:
	CString GetDefaultValue() const;
	virtual void SetToDefault();
	bool SetValue(CString strValue);
	CString GetValue() const;
	bool IsValuePermitted(const CString &strValue) const;

protected:
	virtual void WriteValue() const;
	virtual void ReadValue();
	CString m_strCurrentValue;
	const CString m_strDefaultValue;
	const CString m_strPermittedValues;
};

#endif // !defined(AFX_STRINGSETTINGVALUE_H__06A04FFC_BFFB_495A_A9AC_E1E369243289__INCLUDED_)
