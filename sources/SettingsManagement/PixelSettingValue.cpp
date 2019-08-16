// PixelSettingValue.cpp: implementation of the CPixelSettingValue class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "PixelSettingValue.h"

#include "../Utilities/PLUtils.h"

#include "plpixel32.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPixelSettingValue::CPixelSettingValue(const char *strSection,
									   const char *strEntry,
									   const PLPixel32 &defaultPixel)
:	CIntSettingValue(strSection,strEntry,(PLPixel32ToInt(defaultPixel)),0x00000000,0x00FFFFFF)
{

}

CPixelSettingValue::~CPixelSettingValue()
{

}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

PLPixel32 CPixelSettingValue::GetPixelValue() const
{
	return IntToPLPixel32(m_nCurrentValue);
}

void CPixelSettingValue::SetPixelValue(const PLPixel32 &pixel)
{
	SetValue(PLPixel32ToInt(pixel));
}

PLPixel32 CPixelSettingValue::GetPixelDefaultValue() const
{
	return IntToPLPixel32(m_nDefaultValue);
}
