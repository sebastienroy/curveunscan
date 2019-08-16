// SettingsDefs.h
//
//////////////////////////////////////////////////////////////////////


#if !defined(_SETTINGSDEFS_H_)
#define _SETTINGSDEFS_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

typedef enum
{
	kEnglish=0,
	kFrench=1
}
LanguageType;

typedef enum
{
	kSmartAlgo=0,
	kFlatAlgo=1
}
ThicknessAlgoType;

typedef enum
{
	kTopFollow=0,
	kBottomFollow=1
}
SideToFollowType;

typedef enum
{
	kOpenBitmap=0,
	kScanning=1,
	kNothing=2
}
StartingJobType;


#endif	// !defined(_SETTINGSDEFS_H_)