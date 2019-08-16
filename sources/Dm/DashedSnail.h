// DashedSnail.h: interface for the CDashedSnail class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DASHEDSNAIL_H__94226C93_57D7_4B43_BE63_973565D1959B__INCLUDED_)
#define AFX_DASHEDSNAIL_H__94226C93_57D7_4B43_BE63_973565D1959B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SnailAlgorithm.h"

#include <deque>
using namespace std;

class CDashedSnail : public CSnailAlgorithm  
{
protected:
	friend class CContinuousCurve;
	CDashedSnail(CBmpManager* pBmpManager,
					const PLPixel32& blackLevel,
					bool bTopFollow,
					int nMaxDashDist);
public:
	virtual bool FindNext(CPoint& point);
	virtual bool Initialize(CPoint& ptInitial, bool bToLeft);
	virtual ~CDashedSnail();

protected:
	void ApplyReverse();
	bool IsReachingPoint(const CPoint& point) const;
	int m_nMaxReverse;
	void ReverseClimb();
	void FillLine(const CPoint& ptFinal,deque<CPoint>& buffer);
	void FillBuffer();
	bool m_bIsStopped;
	deque<CPoint> m_DirectBuffer;
	deque<CPoint> m_ReverseBuffer;
	int m_nBufferSizeMax;
	int m_nMaxDashDist;
};

#endif // !defined(AFX_DASHEDSNAIL_H__94226C93_57D7_4B43_BE63_973565D1959B__INCLUDED_)
