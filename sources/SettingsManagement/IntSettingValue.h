// IntSettingValue.h: interface for the CIntSettingValue class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_INTSETTINGVALUE_H__2831B9F2_8763_4B68_9247_28B720E10151__INCLUDED_)
#define AFX_INTSETTINGVALUE_H__2831B9F2_8763_4B68_9247_28B720E10151__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "AbstractSettingValue.h"

class CIntSettingValue : public CAbstractSettingValue  
{
public:
	CIntSettingValue(	const char *strSection,
						const char *strEntry,
						int nDefaultValue,
						int nMin,
						int nMax);
	virtual ~CIntSettingValue();

public:
	int GetDefaultValue() const;
	virtual void SetToDefault();
	bool SetValue(int nValue);
	int GetValue() const;
	virtual bool IsValuePermitted(int nValue) const;

protected:
	virtual void ReadValue();
	virtual void WriteValue() const;

protected:
	int m_nMaxValue;
	int m_nMinValue;
	int m_nDefaultValue;
	int m_nCurrentValue;
};

#endif // !defined(AFX_INTSETTINGVALUE_H__2831B9F2_8763_4B68_9247_28B720E10151__INCLUDED_)
