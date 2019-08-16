// Unif.cpp: implementation of the CUnif class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "utilities.h"
#include "Unif.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


//////////////////////////////////////////////////////////////////////
// Static members
//////////////////////////////////////////////////////////////////////

const int CUnif::m_nMaxVal=1073741824;
const int CUnif::m_nMaxIndex=54;
const int CUnif::m_nMiddleIndex=30;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CUnif::CUnif()
{
	Reset();
}

CUnif::~CUnif()
{

}

void CUnif::Reset()
{
	static int t[]={980629335,889272121,422278310,1042669295, 531256381,
		335028099, 47160432, 788808135, 660624592, 793263632, 998900570, 
		470796980,327436767, 287473989, 119515078, 575143087, 922274831, 
		21914605, 923291707, 753782759, 254480986, 816423843, 931542684, 
		993691006,343157264, 272972469, 733687879, 468941742, 444207473,
		896089285,629371118, 892845902, 163581912, 861580190,  85601059, 
		899226806,438711780, 921057966, 794646776, 417139730, 343610085, 
		737162282,1024718389, 65196680, 954338580, 642449958, 240238978,
		722544540,281483031,1024570269, 602730138, 915220349, 651571385, 
		405259519,145115737};

	m_ValVect=valarray<int>(t,55);
	m_index1=m_nMaxIndex;
	m_index2=m_nMiddleIndex;

}

int CUnif::GetInt()
{
	m_index1=(m_nMaxIndex==m_index1)?0:m_index1+1;
	m_index2=(m_nMaxIndex==m_index2)?0:m_index2+1;

	int nVal=m_ValVect[m_index2]-m_ValVect[m_index1];
	if(nVal<0)
	{
		nVal+=m_nMaxVal;
	}
	m_ValVect[m_index1]=nVal;
	return nVal;
}

double CUnif::GetDouble()
{
	static double dMax=1/(double)m_nMaxVal;
	return dMax*(double)GetInt();
}

int CUnif::GetMaxInt()
{
	return m_nMaxVal;
}
