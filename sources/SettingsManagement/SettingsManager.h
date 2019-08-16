// SettingsManager.h: interface for the CSettingsManager class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SETTINGSMANAGER_H__9B089CF6_361D_4351_BFFB_1A6C828FFDB7__INCLUDED_)
#define AFX_SETTINGSMANAGER_H__9B089CF6_361D_4351_BFFB_1A6C828FFDB7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "IntSettingValue.h"
#include "StringSettingValue.h"
#include "PixelSettingValue.h"
#include "DoubleSettingValue.h"
#include "Settingsdefs.h"
#include "ContinuousCurveDefaultValues.h"	// Added by ClassView

class CColorScale;

class CSettingsManager  
{


protected:
	CSettingsManager();	// Singleton design pattern
	virtual ~CSettingsManager();
public:
	static CSettingsManager* GetInstance();
	static void DeleteInstance();

public:
	void SetColorScale(const CColorScale &scale);
	CColorScale GetColorScale() const;
	CString GetExportFilenameExtension() const;
	char GetExportColumnSeparator() const;
	bool MustPromptForExport();
	StartingJobType GetStartingJob();
	LanguageType GetCurrentLanguage();
	SContinuousCurveDefaultValues GetContinuousCurveDefaultValues() const;
	PLPixel32 GetDefaultBlackLevel() const;
	CString GetResourceDllName() const;
	void ShowOptions();

protected:
	void SetToDefault();
	static CSettingsManager* m_pInstance;

	CStringSettingValue m_Version;
	CIntSettingValue m_Language;
	CIntSettingValue m_ThicknessAlgo;
	CIntSettingValue m_ThicknessRange;
	CPixelSettingValue m_BlackLevel;
	CIntSettingValue m_SideFollow;
	CIntSettingValue  m_Dashed;
	CIntSettingValue m_DashMaxDist;
	CIntSettingValue m_StartingJob;
	CIntSettingValue m_ExportPrompt;
	CIntSettingValue m_SeparatorChar;
	CStringSettingValue m_ExportExtension;

	CPixelSettingValue m_DensityTopColor;
	CPixelSettingValue m_DensityBottomColor;
	CDoubleSettingValue m_DensityTopValue;
	CDoubleSettingValue m_DensityBottomValue;
};

#endif // !defined(AFX_SETTINGSMANAGER_H__9B089CF6_361D_4351_BFFB_1A6C828FFDB7__INCLUDED_)
