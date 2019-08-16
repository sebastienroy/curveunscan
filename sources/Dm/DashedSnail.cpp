// DashedSnail.cpp: implementation of the CDashedSnail class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "CurveUnscan.h"
#include "DashedSnail.h"
#include "BmpManager.h"

#include <deque>
using namespace std;

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDashedSnail::CDashedSnail(CBmpManager* pBmpManager,
								const PLPixel32& blackLevel,
								bool bTopFollow,
								int nMaxDashDist)
:	CSnailAlgorithm(pBmpManager,blackLevel,bTopFollow),
	m_nMaxDashDist(nMaxDashDist),
	m_nBufferSizeMax(nMaxDashDist),
	m_bIsStopped(false),
	m_nMaxReverse(nMaxDashDist/2)
{

}

CDashedSnail::~CDashedSnail()
{

}

bool CDashedSnail::Initialize(CPoint &ptInitial, bool bToLeft)
{
	m_DirectBuffer.clear();
	m_ReverseBuffer.clear();
	m_bToLeft=bToLeft;
	m_bIsInitialized=m_pBmpManager->FindCurve(ptInitial,m_BlackLevel,m_bTopFollow);
	m_bIsStopped=!m_bIsInitialized;
	// push the first value to initialize the algo
	m_DirectBuffer.push_front(ptInitial);
	FillBuffer();
	// remove the first (it is already given by this method)
	m_DirectBuffer.pop_front();

	return m_bIsInitialized;
}

bool CDashedSnail::FindNext(CPoint &point)
{
	bool result=false;
	if(m_DirectBuffer.size()>0)
	{
		result=true;
		point=m_DirectBuffer.front();
		m_DirectBuffer.pop_front();
		FillBuffer();
	}
	return result;
}

// Fill the buffer used to find the good way.
void CDashedSnail::FillBuffer()
{
	while( (!m_bIsStopped)&&(m_DirectBuffer.size()<=m_nBufferSizeMax) )
	{
		CPoint ptCurrent=m_DirectBuffer.back();
		bool found=m_pBmpManager->FindNext(ptCurrent,m_BlackLevel,m_bToLeft,m_bTopFollow);
		
		if(found)	// a point is near the last one
		{
			m_DirectBuffer.push_back(ptCurrent);
		}
		else		// end of dash, try to find the next
		{
			CPoint ptFinal=m_pBmpManager->FindNextDash(ptCurrent,m_BlackLevel,m_bToLeft,m_nMaxDashDist);
			if(ptFinal==ptCurrent)	// no more dashes, stop
			{
				m_bIsStopped=true;
			}
			else					// an other dash has been found
			{
				m_pBmpManager->FindCurve(ptFinal,m_BlackLevel,m_bTopFollow);
				FillLine(ptFinal,m_DirectBuffer);

				// the dash follow is best when descending than when climbing
				bool isUp=(ptFinal.y<ptCurrent.y);
				bool isAscending=(isUp&&m_bTopFollow)||( (!isUp)&&(!m_bTopFollow) );
				if(isAscending)
				{
					ReverseClimb();
				}
			}
		}
	}
}

// Fill the buffer by a line from its last point to ptFinal
void CDashedSnail::FillLine(const CPoint& ptFinal, deque<CPoint> &buffer)
{
	CPoint ptInitial=buffer.back();
	CPoint ptCurrent=ptInitial;
	int increment=(ptFinal.x>ptInitial.x)?+1:-1;

	int deltaX=ptFinal.x-ptInitial.x;
	int deltaY=ptFinal.y-ptInitial.y;
	double rate=((double)deltaY)/((double)deltaX);

	while(ptCurrent.x!=ptFinal.x)
	{
		(ptCurrent.x)+=increment;
		double dx=double(ptCurrent.x-ptInitial.x);
		ptCurrent.y=ptInitial.y+(int)( dx*rate );
		buffer.push_back(ptCurrent);
	}
}

void CDashedSnail::ReverseClimb()
{
	m_ReverseBuffer.clear();
	m_ReverseBuffer.push_back(m_DirectBuffer.back());
	CPoint ptCurrent;
	int nDist=0;
	bool reverseStopped=false;

	while( (nDist<m_nMaxReverse)&&(!reverseStopped) )
	{
		nDist++;
		ptCurrent=m_ReverseBuffer.back();
		bool isEndDash=!m_pBmpManager->FindNext(ptCurrent,m_BlackLevel,!m_bToLeft,m_bTopFollow);
		if(isEndDash)// end of the current dash, try to find the previous
		{
			CPoint ptFinal=m_pBmpManager->FindNextDash(ptCurrent,m_BlackLevel,!m_bToLeft,m_nMaxDashDist);
			if(ptFinal!=ptCurrent)
			{
				// Is it descending?
				bool isDown=(ptFinal.y>ptCurrent.y);
				bool isDescending=((isDown)&&(m_bTopFollow))||((!isDown)&&(!m_bTopFollow));

				if( isDescending && (IsReachingPoint(ptFinal)) )
				{
					FillLine(ptFinal,m_ReverseBuffer);
					ApplyReverse();
				}
			}
			reverseStopped=true;
		}
		else	// creep, not already end of current dash 
		{
			m_ReverseBuffer.push_back(ptCurrent);
		}
	}
}

bool CDashedSnail::IsReachingPoint(const CPoint &point) const
{
	CPoint lastPoint=m_DirectBuffer.back();
	int nDist=abs(point.x-lastPoint.x);
	int nDirectSize=m_DirectBuffer.size();

	// look for distance
	bool tooFar=(nDist>m_nMaxReverse)||(nDist>nDirectSize);
	if(tooFar)
	{
		return false;
	}
	// look if contained in the direct buffer
	const CPoint directPoint=m_DirectBuffer[nDirectSize-1-nDist];
	bool isTheSame=(point==directPoint);
	return isTheSame;
}

void CDashedSnail::ApplyReverse()
{
	int nReverseSize=m_ReverseBuffer.size();
	for(int nCounter=0;nCounter<nReverseSize;nCounter++)
	{
		m_DirectBuffer.pop_back();
	}
	deque<CPoint>::reverse_iterator iter;
	for(iter=m_ReverseBuffer.rbegin();iter!=m_ReverseBuffer.rend();iter++)
	{
		m_DirectBuffer.push_back(*iter);
	}
}
