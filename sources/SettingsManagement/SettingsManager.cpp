// SettingsManager.cpp: implementation of the CSettingsManager class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SettingsManager.h"
#include "LanguageProPage.h"
#include "CurveProPage.h"
#include "DensitoProPage.h"
#include "PromptProPage.h"
#include "ExportProPage.h"

#include <Dm/ColorScale.h>

#include "resource.h"

#include <list>
using namespace std;

#define EmptyRegExp CString(".*")

#define CURRENT_VERSION "V120"

//////////////////////////////////////////////////////////////////////
// Static member initialization
//////////////////////////////////////////////////////////////////////

CSettingsManager* CSettingsManager::m_pInstance=NULL;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSettingsManager::CSettingsManager()
:	m_Version("General","Version",CURRENT_VERSION,EmptyRegExp),
	m_Language("General","Language",kEnglish,kEnglish,kFrench),
	m_ThicknessAlgo("Curve","Algo",kSmartAlgo,kSmartAlgo,kFlatAlgo),
	m_ThicknessRange("Curve","SmartAlgoRange",2,1,32),
	m_BlackLevel("Curve","BlackLevel",PLPixel32(70,70,70)),
	m_SideFollow("Curve","SideFollow",kTopFollow,kTopFollow,kBottomFollow),
	m_Dashed("Curve","Dashed",0,0,1),
	m_DashMaxDist("Curve","DashMaxDist",20,1,1000),
	m_StartingJob("Prompt","StartingJob",kOpenBitmap,kOpenBitmap,kNothing),
	m_ExportPrompt("Prompt","ExportPrompt",1,0,1),
	m_SeparatorChar("Export","Separator",'\t',0,255),
	m_ExportExtension("Export","Extension","xls","^[a-zA-Z0-9][a-zA-Z0-9]?[a-zA-Z0-9]?$"),
	m_DensityTopColor("Density","TopColor",PLPixel32(0,0,0)),
	m_DensityBottomColor("Density","BottomColor",PLPixel32(255,255,255)),
	m_DensityTopValue("Density","TopValue",100),
	m_DensityBottomValue("Density","BottomValue",0)
{
	if(CString(CURRENT_VERSION)!=m_Version.GetValue())
	{
		SetToDefault();
	}
}

CSettingsManager::~CSettingsManager()
{

}

//////////////////////////////////////////////////////////////////////
// Methods
//////////////////////////////////////////////////////////////////////



CSettingsManager* CSettingsManager::GetInstance()
{
	if(NULL==m_pInstance)
	{
		m_pInstance=new CSettingsManager();
	}
	return m_pInstance;
}

void CSettingsManager::DeleteInstance()
{
	delete m_pInstance;
	m_pInstance=NULL;
}

void CSettingsManager::SetToDefault()
{
	m_Version.SetToDefault();
	m_Language.SetToDefault();
	m_ThicknessAlgo.SetToDefault();
	m_ThicknessRange.SetToDefault();
	m_BlackLevel.SetToDefault();
	m_SideFollow.SetToDefault();
	m_Dashed.SetToDefault();
	m_StartingJob.SetToDefault();
	m_ExportPrompt.SetToDefault();
	m_SeparatorChar.SetToDefault();
	m_ExportExtension.SetToDefault();

	m_DensityTopColor.SetToDefault();
	m_DensityBottomColor.SetToDefault();
	m_DensityTopValue.SetToDefault();
	m_DensityBottomValue.SetToDefault();

}

void CSettingsManager::ShowOptions()
{
	// language
	list<CString> langList;
	CString strLanguage;
	strLanguage.LoadString(IDS_ENGLISHLABEL);
	langList.push_back(strLanguage);
	strLanguage.LoadString(IDS_FRENCHLABEL);
	langList.push_back(strLanguage);
	CLanguageProPage languagePage(m_Language.GetValue(),langList);

	// Curve
	CCurveProPage curvePage;
	curvePage.m_nThicknessAlgo=m_ThicknessAlgo.GetValue();
	curvePage.m_nSmartAlgoRange=m_ThicknessRange.GetValue();
	curvePage.m_BlackColor=m_BlackLevel.GetPixelValue();
	curvePage.m_nFollow=m_SideFollow.GetValue();
	curvePage.m_nDashed=(0==m_Dashed.GetValue())?1:0;	// Yes is 0
	curvePage.m_nDashMaxDist=m_DashMaxDist.GetValue();

	curvePage.m_nDefaultThicknessAlgo=m_ThicknessAlgo.GetDefaultValue();
	curvePage.m_nDefaultSmartAlgoRange=m_ThicknessRange.GetDefaultValue();
	curvePage.m_DefaultBlackColor=m_BlackLevel.GetPixelDefaultValue();
	curvePage.m_nDefaultFollow=m_SideFollow.GetDefaultValue();
	curvePage.m_nDefaultDashed=(0==m_Dashed.GetDefaultValue())?1:0;	// Yes is 0
	curvePage.m_nDefaultDashMaxDist=m_DashMaxDist.GetDefaultValue();

	// Densitometry
	CDensitoProPage densitoPage;
	densitoPage.SetColorScale(GetColorScale());

	// Prompt
	CPromptProPage promptPage;
	promptPage.m_nHowToStart=m_StartingJob.GetValue();
	promptPage.m_nPromptExport=m_ExportPrompt.GetValue();

	// Export
	CExportProPage exportPage;
	exportPage.SetSeparator((char)m_SeparatorChar.GetValue());
	exportPage.m_strExtension=m_ExportExtension.GetValue();

	// Property sheet
	CPropertySheet propsheet("Options");
	propsheet.AddPage(&languagePage);
	propsheet.AddPage(&curvePage);
	propsheet.AddPage(&densitoPage);
	propsheet.AddPage(&promptPage);
	propsheet.AddPage(&exportPage);

	if(IDOK==propsheet.DoModal())
	{
		// language
		m_Language.SetValue(languagePage.GetSelectedLanguage());

		// Curve
		m_ThicknessAlgo.SetValue(curvePage.m_nThicknessAlgo);
		m_ThicknessRange.SetValue(curvePage.m_nSmartAlgoRange);
		m_BlackLevel.SetPixelValue(curvePage.m_BlackColor);
		m_SideFollow.SetValue(curvePage.m_nFollow);
		m_Dashed.SetValue((0==curvePage.m_nDashed)?1:0);
		m_DashMaxDist.SetValue(curvePage.m_nDashMaxDist);

		// densitometry
		SetColorScale(densitoPage.GetColorScale());

		// Prompt
		m_StartingJob.SetValue(promptPage.m_nHowToStart);
		m_ExportPrompt.SetValue(promptPage.m_nPromptExport);

		// Export
		m_SeparatorChar.SetValue((int)exportPage.GetSeparator());
		m_ExportExtension.SetValue(exportPage.m_strExtension);
	}
}
 
CString CSettingsManager::GetResourceDllName() const
{
	CString strName;
	LanguageType nLanguage=(LanguageType)m_Language.GetValue();
	switch(nLanguage)
	{
	case kEnglish:
		strName="CrvResUs.dll";
		break;
	case kFrench:
		strName="CrvResFr.dll";
		break;
	default:
		strName="CrvResUs.dll";
	}
	return strName;
}

SContinuousCurveDefaultValues CSettingsManager::GetContinuousCurveDefaultValues() const
{
	SContinuousCurveDefaultValues defaultValues;

	defaultValues.m_nThicknessAlgo=(ThicknessAlgoType)m_ThicknessAlgo.GetValue();
	defaultValues.m_nSmartAlgoRange=m_ThicknessRange.GetValue();
	defaultValues.m_nFollow=(SideToFollowType)m_SideFollow.GetValue();
	defaultValues.m_BlackColor=m_BlackLevel.GetPixelValue();
	defaultValues.m_bDashed=(0==m_Dashed.GetValue())?false:true;
	defaultValues.m_nDashMaxDist=m_DashMaxDist.GetValue();

	return defaultValues;
}

LanguageType CSettingsManager::GetCurrentLanguage()
{
	return (LanguageType)m_Language.GetValue();
}

StartingJobType CSettingsManager::GetStartingJob()
{
	return (StartingJobType)m_StartingJob.GetValue();
}

bool CSettingsManager::MustPromptForExport()
{
	return (0!=m_ExportPrompt.GetValue());
}

char CSettingsManager::GetExportColumnSeparator() const
{
	return m_SeparatorChar.GetValue();
}

CString CSettingsManager::GetExportFilenameExtension() const
{
	return m_ExportExtension.GetValue();
}

CColorScale CSettingsManager::GetColorScale() const
{
	PLPixel32 topColor=m_DensityTopColor.GetPixelValue();
	PLPixel32 bottomColor=m_DensityBottomColor.GetPixelValue();
	double topValue=m_DensityTopValue.GetValue();
	double bottomValue=m_DensityBottomValue.GetValue();

	return CColorScale(topColor,bottomColor,topValue,bottomValue);
}

void CSettingsManager::SetColorScale(const CColorScale &scale)
{
	m_DensityTopColor.SetPixelValue(scale.GetTopColor());
	m_DensityBottomColor.SetPixelValue(scale.GetBottomColor());
	m_DensityTopValue.SetValue(scale.GetTopValue());
	m_DensityBottomValue.SetValue(scale.GetBottomValue());
}
