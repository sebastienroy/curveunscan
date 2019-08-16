// CoordSyst.cpp: implementation of the CCoordSyst class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CoordSyst.h"
//#include "CurveUnscan.h"
#include "UnscanDoc.h"
//#include "Curve.h"
#include "Curve.h"


#include <Utilities/Tools.h>
#include <LicenceManaging/IntegrityCheck.h>
#include <LicenceManaging/Coder.h>
#include <md5/MD5Checksum.h>
#include <math.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

long CCoordSyst::m_NextIdentifierNumber=1;
CString CCoordSyst::m_strDataScrambling="";


IMPLEMENT_SERIAL(CCoordSyst,CObject,1)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCoordSyst::CCoordSyst() :m_pDoc(NULL)
	{
	ConstructorInclude();
	}

CCoordSyst::CCoordSyst(CUnscanDoc *pDoc) :m_pDoc(pDoc)
	{
	ConstructorInclude();
	}

CCoordSyst::CCoordSyst(CCoordSyst &other)
	{
	*this=other;
	}

void CCoordSyst::ConstructorInclude()
	{
	m_DefinedOrigin=FALSE;
//	m_bIsModified=FALSE;
	m_Selected=FALSE;
	m_XReverse=FALSE;
	m_XAxe.SetName(CString("X"));
	m_YAxe.SetName(CString("Y"));
	m_XAxe.SetCoordSyst(this);
	m_YAxe.SetCoordSyst(this);
	m_IdentifierNumber=m_NextIdentifierNumber;
	m_Color=(m_pDoc==NULL)?RGB(255,0,0):m_pDoc->GetColor(m_IdentifierNumber);
	}
	 
CCoordSyst::~CCoordSyst()
	{
	if (!m_CurveList.IsEmpty())	// vire les courbes existantes
		{
		POSITION pos=m_CurveList.GetHeadPosition();
		while(pos!=NULL)	
			{
			CCurve *pCurve=m_CurveList.GetNext(pos);
			delete pCurve;
			}
		m_CurveList.RemoveAll();
		}
	}

// Calcule le point d'intersection des axes x et y s'ils ont été définis.
// La condition axes non || est assuree par les boites de dialogue
// mais redondance dans la version Debug.
// Methode  de calcul :
//		axe x : pts d'equation (a1 b1) + k1(u1 v1)
//			y					 2  2     2  2  2
//		-> equation : Pt(axe x)==Pt(axe y)
// solution : k2=(1/delta)*( u1(b2-b1) + v1(a1-a2) )
//		avec delta=u2v1-u1v2
// Une fois l'origine calculee, le point des axes le plus proche de
//   l'origine est remplacé par ce dernier point
CPoint CCoordSyst::CalculateOrigin()
	{
	if( (m_XAxe.IsDefined()==FALSE)||(m_YAxe.IsDefined()==FALSE) )
		{
		return CPoint(0,0);
		}
	double delta;
	double k2;
	double a1,a2,b1,b2,u1,u2,v1,v2;
	double ox,oy;
	a1=(double)m_XAxe.m_From.x;
	a2=(double)m_YAxe.m_From.x; 
	b1=(double)m_XAxe.m_From.y;
	b2=(double)m_YAxe.m_From.y;
	u1=(double)(m_XAxe.m_To.x)-a1;
	u2=(double)(m_YAxe.m_To.x)-a2;
	v1=(double)(m_XAxe.m_To.y)-b1;
	v2=(double)(m_YAxe.m_To.y)-b2;
	delta=(u2*v1)-(u1*v2);

#ifdef _DEBUG  // verification delta non nul (axes ||)
	if(fabs(delta)<1.0e-5) 
		{
		AfxMessageBox("Calcul de l'origine :\n delta==0");
		delta=1;
		}
#endif // _DEBUG

	k2=(1.0/delta)*( u1*(b2-b1) + v1*(a1-a2) );
	ox=a2+k2*u2;
	oy=b2+k2*v2;
	m_Origin.x=(int)ox;
	m_Origin.y=(int)oy;
//	m_XAxe.SetOrigin(m_Origin);
//	m_YAxe.SetOrigin(m_Origin);
	m_DefinedOrigin=TRUE;
	return m_Origin;

	}

CLogicPoint CCoordSyst::ToLogic(CPoint physicalPoint)
//	Calcul du point logic (suivant l'echelle choisie par l'utilisateur)
//		a partir d'un point physique (issus du bitmap)
	{
	
	CLogicPoint result;
	result.x=m_BmpOrigin.x;
	result.x+=m_PtoL11*(double)(physicalPoint.x);
	result.x+=m_PtoL12*(double)(physicalPoint.y);
	if(m_XAxe.GetLogarithmic())
		{
		result.x=exp(result.x);
		}
	result.y=m_BmpOrigin.y;
	result.y+=m_PtoL21*(double)(physicalPoint.x);
	// security : m_PtoL22 is scrambled with checksum
	double dPtoL22=m_PtoL22;
	void* pPtoL22=&dPtoL22;
	char* pCoef=(char*)pPtoL22;
	for(int i=0;i<8;i++)
	{
		if(m_strDataScrambling.IsEmpty())
		{
			m_strDataScrambling=CIntegrityCheck::getInstance()->getReadDataScrambler();
		}
		char& cCurrent=pCoef[i];
		cCurrent^=((LPCSTR)m_strDataScrambling)[i];
	}

	result.y+=dPtoL22*(double)(physicalPoint.y);
	if(m_YAxe.GetLogarithmic())
		{
		result.y=exp(result.y);
		}
	return result;
	}

CPoint CCoordSyst::ToPhysic(const CLogicPoint &logicPoint) const
// Calcul du point physique (du bitmap) correspondant à partir du point en 
// coordonnées logiques (échelle utilisateur).
	{
	CLogicPoint result=ToPhysicDouble(logicPoint);
	return CPoint(((int)result.x),((int)result.y));
	}

CLogicPoint CCoordSyst::ToPhysicDouble(CLogicPoint logicPoint) const
{
	CLogicPoint result;
	if(m_XAxe.GetLogarithmic())
		{
		logicPoint.x=log(logicPoint.x);
		}
	result.x=m_LtoP11*(logicPoint.x-m_BmpOrigin.x);
	result.x+=m_LtoP12*(logicPoint.y-m_BmpOrigin.y);
	if(m_YAxe.GetLogarithmic())
		{
		logicPoint.y=log(logicPoint.y);
		}
	result.y=m_LtoP21*(logicPoint.x-m_BmpOrigin.x);
	result.y+=m_LtoP22*(logicPoint.y-m_BmpOrigin.y);
	return result;
}

CCoordSyst& CCoordSyst::operator =(const CCoordSyst &otherCoord)
	{
	if(&otherCoord==this)
		{
		return *this;
		}
	m_IdentifierNumber=otherCoord.m_IdentifierNumber;
//	m_bIsModified=otherCoord.m_bIsModified;
	m_Color=otherCoord.m_Color;
	m_XAxe=otherCoord.m_XAxe;
	m_YAxe=otherCoord.m_YAxe;
	m_XAxe.SetCoordSyst(this);
	m_YAxe.SetCoordSyst(this);
	m_XReverse=otherCoord.m_XReverse;
	m_Origin=otherCoord.m_Origin;
	m_DefinedOrigin=otherCoord.m_DefinedOrigin;
	m_BmpOrigin=otherCoord.m_BmpOrigin;
	m_LtoP11=otherCoord.m_LtoP11;
	m_LtoP12=otherCoord.m_LtoP12;
	m_LtoP21=otherCoord.m_LtoP21;
	m_LtoP22=otherCoord.m_LtoP22;
	m_PtoL11=otherCoord.m_PtoL11;
	m_PtoL12=otherCoord.m_PtoL12;
	m_PtoL21=otherCoord.m_PtoL21;
	m_PtoL22=otherCoord.m_PtoL22;
	m_pDoc=otherCoord.m_pDoc;
	m_Selected=otherCoord.m_Selected;

	// vire les courbes existantes
	POSITION pos;
	if (!m_CurveList.IsEmpty())	
		{
		pos=m_CurveList.GetHeadPosition();
		while(pos!=NULL)
			{
			delete m_CurveList.GetNext(pos);
			}
		m_CurveList.RemoveAll();
		}

	// copie les courbes
	CCurve* pCurve;
	CCurve* pCurrent;
	if(!otherCoord.m_CurveList.IsEmpty())
		{
		pos=otherCoord.m_CurveList.GetHeadPosition();	
		while(pos!=NULL)
			{
			pCurrent=otherCoord.m_CurveList.GetNext(pos);
			pCurve=pCurrent->Clone();
			m_CurveList.AddTail(pCurve);
			pCurve->SetCoordSyst(this);
			}
		}

	return *this;
	}

BOOL CCoordSyst::Draw(CDC *pDC) const
	{
/*	DrawParameters drawParam;
	if(m_Selected)
		{
		drawParam=m_pDoc->GetSelParam();
		}
	else
		{
		drawParam=m_pDoc->GetUnselParam();
		}*/
	CPen pen(PS_SOLID,(m_Selected)?2:1,m_Color);
	CPen* oldPen=pDC->SelectObject(&pen);
	pDC->SetTextColor(m_Color);
	m_XAxe.Draw(pDC);
	m_YAxe.Draw(pDC);
	if(!m_CurveList.IsEmpty())
		{
		POSITION pos=m_CurveList.GetHeadPosition();
		while(pos!=NULL)
			{
			CCurve* pCurve=m_CurveList.GetNext(pos);
			pCurve->Draw(pDC);
			}
		}
	pDC->SelectObject(oldPen);
	return TRUE;
	}

// Etablit les constantes de conversion entre les coordonnees physiques (bmp)
// et les coordonnées logiques définies par l'utilisateur.
// Fonction appelée par la boite de dialogue CScaleDialog au moment de sa fermeture
//  (au sein de la fonction UpdateObjects() )
BOOL CCoordSyst::CalculateConversionFactors()
	{
	if( (!m_XAxe.ScaleDefined())||(!m_YAxe.ScaleDefined()) )
		{
		return FALSE;
		}
	/////////////////////////////////////////////////////////
	// calcul des coordonnées logiques de l'origine des axes.
	CLogicPoint LOrigin;
	double k1,k2;	// AO = k.AB
					// A : ScalePoint 1 de l'axe
					// B : ScalePoint 2 de l'axe
					// O : Origine des axes
					// Indices : 1->Axe X ; 2->Axe Y
	CPoint A1,B1,A2,B2;
	CLogicPoint AB1,AO1,AB2,AO2;	// vecteurs correspondants
	double scalAOAB1,scalAOAB2;
	double normeAB1,normeAB2;
	// Détermination de k1
	A1=(m_XAxe.GetScalePoint(1))->GetAxePosition();
	B1=(m_XAxe.GetScalePoint(2))->GetAxePosition();
	AB1.x=(double)(B1.x-A1.x);
	AB1.y=(double)(B1.y-A1.y);
	AO1.x=(double)(m_Origin.x-A1.x);
	AO1.y=(double)(m_Origin.y-A1.y);
	normeAB1=AB1.x*AB1.x+AB1.y*AB1.y;
	scalAOAB1=AO1.x*AB1.x+AO1.y*AB1.y;
	k1=scalAOAB1/normeAB1;
	// Détermination de k2
	A2=(m_YAxe.GetScalePoint(1))->GetAxePosition();
	B2=(m_YAxe.GetScalePoint(2))->GetAxePosition();
	AB2.x=(double)(B2.x-A2.x);
	AB2.y=(double)(B2.y-A2.y);
	AO2.x=(double)(m_Origin.x-A2.x);
	AO2.y=(double)(m_Origin.y-A2.y);
	normeAB2=AB2.x*AB2.x+AB2.y*AB2.y;
	scalAOAB2=AO2.x*AB2.x+AO2.y*AB2.y;
	k2=scalAOAB2/normeAB2;
	// calcul des coordonees logiques de l'origine des axes
	double val;
	double lA1,lA2,lB1,lB2;		// valeur logiques des points de l'échelle
	double lAB1,lAB2;
	val=(m_XAxe.GetScalePoint(1))->GetValue();
	lA1=(m_XAxe.GetLogarithmic())?log(val):val;
	val=(m_XAxe.GetScalePoint(2))->GetValue();
	lB1=(m_XAxe.GetLogarithmic())?log(val):val;
	lAB1=lB1-lA1;
	val=(m_YAxe.GetScalePoint(1))->GetValue();
	lA2=(m_YAxe.GetLogarithmic())?log(val):val;
	val=(m_YAxe.GetScalePoint(2))->GetValue();
	lB2=(m_YAxe.GetLogarithmic())?log(val):val;
	lAB2=lB2-lA2;
	LOrigin.x=lA1+k1*lAB1;
	LOrigin.y=lA2+k2*lAB2;
	////////////////////////////////////////////
	// Determination des matrices de passage
	double delta;
	m_LtoP11=AB1.x/lAB1;
	m_LtoP12=AB2.x/lAB2;
	m_LtoP21=AB1.y/lAB1;
	m_LtoP22=AB2.y/lAB2;
	delta=AB1.x*AB2.y-AB1.y*AB2.x;
	m_PtoL11=AB2.y*lAB1/delta;
	m_PtoL12=(-1.0)*AB2.x*lAB1/delta;
	m_PtoL21=(-1.0)*AB1.y*lAB2/delta;
	m_PtoL22=AB1.x*lAB2/delta;
	////////////////////////////////////////////////////////////////
	// Détermination des coordonnées logiques de l'origine du bitmap
	m_BmpOrigin.x=LOrigin.x-(m_PtoL11*(double)m_Origin.x+m_PtoL12*(double)m_Origin.y);
	m_BmpOrigin.y=LOrigin.y-(m_PtoL21*(double)m_Origin.x+m_PtoL22*(double)m_Origin.y);
	m_XReverse=(m_PtoL11<0)?TRUE:FALSE;

	// security : m_PtoL22 is scrambled with checksum
	if(m_strComputedScrambling.IsEmpty())
	{
		CString strScramblingCode=CCoder::GetInstance()->GetDataScramblingValue(CIntegrityCheck::getInstance()->getFileToCheck());
		m_strComputedScrambling=CMD5Checksum::GetMD5((BYTE*)(LPCSTR)strScramblingCode,strScramblingCode.GetLength());
	}
	void* pPtoL22=&m_PtoL22;
	char* pCoef=(char*)pPtoL22;
	for(int i=0;i<8;i++)
	{
		char& cCurrent=pCoef[i];
		cCurrent^=((LPCSTR)m_strComputedScrambling)[i];
	}
	

	return TRUE;
	}


BOOL CCoordSyst::IsPresentOn(CPoint point) const
// Renvoir TRUE si les axes du système de coordonnée passent par
// le point donné en paramètre
	{
	CPoint O=m_Origin;
	CPoint A=m_XAxe.GetFrom();
	CPoint B=m_XAxe.GetTo();
	BOOL flagX=PresenceTest(point,A,B,O);
	A=m_YAxe.GetFrom();
	B=m_YAxe.GetTo();
	BOOL flagY=PresenceTest(point,A,B,O);

	return (flagX||flagY);
	}

BOOL CCoordSyst::PresenceTest(CPoint testPoint, CPoint A, CPoint B, CPoint O) const
// teste la présence du point testPoint sur le segment contenant les points A, B et O.
	{
	double k=CTools::GetNormalizedScalar(A,B,O);	// détermination droite
	if(k<0)
		{
		A=O;
		}
	if(k>1)
		{
		B=O;
		}
	k=CTools::GetNormalizedScalar(A,B,testPoint);
	if( (k<0)||(k>1.0) )
		{
		return FALSE;
		}
	CPoint projection=CTools::GetProjection(A,B,testPoint);
	double diffX=projection.x-testPoint.x;
	if( (diffX>2)||(diffX<-2) )
		{
		return FALSE;
		}
	double diffY=projection.y-testPoint.y;
	if( (diffY>2)||(diffY<-2) )
		{
		return FALSE;
		}
	return TRUE;
	}

BOOL CCoordSyst::RemoveCurve(CCurve *pCurve)
	{
	POSITION pos;
	pos=m_CurveList.Find(pCurve);
	if(pos==NULL)
		{
		return FALSE;
		}
	delete m_CurveList.GetAt(pos);
	m_CurveList.RemoveAt(pos);
	return TRUE;
	}

long CCoordSyst::IncrementIDNumber()
	{
	m_NextIdentifierNumber++;
	return m_NextIdentifierNumber;
	}

void CCoordSyst::ResetIdentifierNumber()
	{
	m_NextIdentifierNumber=1;
	}

void CCoordSyst::SetModified(BOOL flag)
{
//	m_bIsModified=flag;

	POSITION pos=m_CurveList.GetHeadPosition();
	while(NULL!=pos)
		{
		CCurve* pCurve=m_CurveList.GetNext(pos);
		pCurve->SetModifiedFlag(flag);
		}
	CalculateConversionFactors();
}

BOOL CCoordSyst::IsDefined()
{
	return ( (m_XAxe.ScaleDefined())&&(m_YAxe.ScaleDefined())  );
}

void CCoordSyst::Serialize(CArchive &ar)
{
	CObject::Serialize(ar);

	if(ar.IsStoring())
	{
		ar << m_IdentifierNumber;
		ar << m_NextIdentifierNumber;
		ar << m_Color;
		ar << m_Selected;

		m_XAxe.Serialize(ar);
		m_YAxe.Serialize(ar);

		int nCurveNb=m_CurveList.GetCount();
		ar << nCurveNb;
		POSITION pos=m_CurveList.GetHeadPosition();
		while(NULL!=pos)
		{
			CCurve* pCurve=m_CurveList.GetNext(pos);
			ar << pCurve;
		}
	}
	else
	{
		ar >> m_IdentifierNumber;
		ar >> m_NextIdentifierNumber;
		ar >> m_Color;
		ar >> m_Selected;

		m_XAxe.Serialize(ar);
		m_YAxe.Serialize(ar);

		m_XAxe.Actualize();
		m_YAxe.Actualize();

		CalculateOrigin();
		CalculateConversionFactors();

		int nCurveNb;
		ar >> nCurveNb;
		for(int nCounter=0;nCounter<nCurveNb;nCounter++)
		{
			CObject* pObj=NULL;
			ar >> pObj;
			CCurve *pCurve=dynamic_cast<CCurve*>(pObj);
			if(NULL!=pCurve)
			{
				m_CurveList.AddTail(pCurve);
				pCurve->SetCoordSyst(this);
			}
		}
	}
}

BOOL CCoordSyst::HasSomethingModified()
{
	BOOL bModified=FALSE;

	POSITION pos=m_CurveList.GetHeadPosition();
	while( (FALSE==bModified)&&(NULL!=pos) )
		{
		CCurve* pCurve=m_CurveList.GetNext(pos);
		bModified=pCurve->GetModifiedFlag();
		}
	
	return bModified;
}

void CCoordSyst::setScramblingCode(CString strScambling)
{
	m_strDataScrambling=strScambling;
}