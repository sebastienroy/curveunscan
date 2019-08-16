// ContinuousCurveDefaultValues.h: 
//
//////////////////////////////////////////////////////////////////////


#if !defined(_CONTINUOUSCURVEDEFAULTVALUES_H_)
#define _CONTINUOUSCURVEDEFAULTVALUES_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SettingsDefs.h"

class PLPixel32;

struct SContinuousCurveDefaultValues
{
	ThicknessAlgoType m_nThicknessAlgo;
	int m_nSmartAlgoRange;
	PLPixel32 m_BlackColor;
	SideToFollowType m_nFollow;
	bool m_bDashed;	
	int m_nDashMaxDist;
};

#endif	/// !defined(_CONTINUOUSCURVEDEFAULTVALUES_H_)