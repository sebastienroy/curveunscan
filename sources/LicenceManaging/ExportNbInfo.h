// ExportNbInfo.h: interface for the CExportNbInfo class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EXPORTNBINFO_H__635B585F_9A9C_4A4B_A66D_999EB9866C12__INCLUDED_)
#define AFX_EXPORTNBINFO_H__635B585F_9A9C_4A4B_A66D_999EB9866C12__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SecuredInfo.h"

class CExportNbInfo : public CSecuredInfo  
{
public:
	int DecreaseNbOfExportLeft();
	int GetNbOfExportLeft();
	CExportNbInfo();
	virtual ~CExportNbInfo();

protected:
	virtual void WriteFileSkeleton(ofstream& stream);
	void InitializeNb();
};

#endif // !defined(AFX_EXPORTNBINFO_H__635B585F_9A9C_4A4B_A66D_999EB9866C12__INCLUDED_)
