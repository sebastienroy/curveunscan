// Unif.h: interface for the CUnif class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UNIF_H__F07F86ED_E9F0_4947_B897_08D40A5FEA7A__INCLUDED_)
#define AFX_UNIF_H__F07F86ED_E9F0_4947_B897_08D40A5FEA7A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// in order to avoid compilation error with valarray template
#undef min
#undef max

#include <valarray>
using namespace std;

// Generateur de nombres pseudo aléatoires

class CUnif  
{
public:
	CUnif();
	virtual ~CUnif();

public:
	static int GetMaxInt();
	double GetDouble();
	int GetInt();
	void Reset();

protected:
	valarray<int> m_ValVect;
	int m_index1;
	int m_index2;
	static const int m_nMaxVal;
	static const int m_nMaxIndex;
	static const int m_nMiddleIndex;
	

};

#endif // !defined(AFX_UNIF_H__F07F86ED_E9F0_4947_B897_08D40A5FEA7A__INCLUDED_)
