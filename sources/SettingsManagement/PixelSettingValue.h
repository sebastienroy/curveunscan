// PixelSettingValue.h: interface for the CPixelSettingValue class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PIXELSETTINGVALUE_H__B8371C16_3CA6_46B7_8277_E1C2BF1E79D6__INCLUDED_)
#define AFX_PIXELSETTINGVALUE_H__B8371C16_3CA6_46B7_8277_E1C2BF1E79D6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "IntSettingValue.h"

#include "plpixel32.h"

class CPixelSettingValue : public CIntSettingValue  
{
public:
	CPixelSettingValue(const char *strSection,
					   const char *strEntry,
					   const PLPixel32 &defaultPixel);
	virtual ~CPixelSettingValue();

public:
	PLPixel32 GetPixelDefaultValue() const;
	void SetPixelValue(const PLPixel32 &pixel);
	PLPixel32 GetPixelValue() const;

};

#endif // !defined(AFX_PIXELSETTINGVALUE_H__B8371C16_3CA6_46B7_8277_E1C2BF1E79D6__INCLUDED_)
