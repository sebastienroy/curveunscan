// ExportNbInfo.cpp: implementation of the CExportNbInfo class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "licencemanaging.h"
#include "ExportNbInfo.h"

#include "LicenceManagingResources.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CExportNbInfo::CExportNbInfo()
{
	m_strFilename=EXPORT_NB_FILENAME;
	m_strFilePath=GetSystemDirectory();
	m_strRegistryPath=EXPORT_NB_REGPATH;
	m_strRegistryEntryName=EXPORT_NB_REGKEYNAME;

	if(IsRegKeyExists())
	{
		m_bUsefile=false;
	}
}

CExportNbInfo::~CExportNbInfo()
{

}

int CExportNbInfo::GetNbOfExportLeft()
{
	InitializeNb();
	CString strValue=GetValue(EXPORT_NB_SECTION,EXPORT_NB_ENTRY);
	int result=atoi(strValue);
	return result;
}

int CExportNbInfo::DecreaseNbOfExportLeft()
{
	InitializeNb();
	CString strValue=GetValue(EXPORT_NB_SECTION,EXPORT_NB_ENTRY);
	int nb=atoi(strValue);
	nb--;
	char buffer[256];
	sprintf(buffer,"%d",nb);
	SetValue(EXPORT_NB_SECTION,EXPORT_NB_ENTRY,buffer);
	return nb;	
}

void CExportNbInfo::InitializeNb()
{
	if(!IsInitialized())
	{
		char buffer[256];
		int nValue=INITIAL_EXPORT_NB;
		sprintf(buffer,"%d",nValue);
		SetValue(EXPORT_NB_SECTION,EXPORT_NB_ENTRY,buffer);
	}

}

void CExportNbInfo::WriteFileSkeleton(ofstream &file)
{
	file << "[" << EXPORT_NB_SECTION << "]" << endl;
	file << EXPORT_NB_ENTRY << "=" << endl;
}
