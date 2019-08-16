// DoubleSettingValue.h: interface for the CDoubleSettingValue class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DOUBLESETTINGVALUE_H__8E85683B_94B2_438F_9640_002A3546C4E8__INCLUDED_)
#define AFX_DOUBLESETTINGVALUE_H__8E85683B_94B2_438F_9640_002A3546C4E8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "AbstractSettingValue.h"

class CDoubleSettingValue : public CAbstractSettingValue  
{
public:
	CDoubleSettingValue(const char *strSection,
						const char *strEntry,
						double dDefaultValue);
	virtual ~CDoubleSettingValue();

public:
	double GetValue() const;
	double SetValue(double value);
	virtual void SetToDefault();

protected:
	void WriteValue() const;
	void ReadValue();
	double m_dCurrentValue;
	double m_dDefaultValue;
};

#endif // !defined(AFX_DOUBLESETTINGVALUE_H__8E85683B_94B2_438F_9640_002A3546C4E8__INCLUDED_)
