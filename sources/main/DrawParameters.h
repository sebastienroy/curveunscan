////////////////////////////////////////////////////////////////
// Draw Parameters.h

#ifndef DRAWPARAMETERS_H
#define DRAWPARAMETERS_H


typedef struct DRAWPARAMETERS
	{
	COLORREF AxeColor;//=RGB(255,0,0);
	int AxeThickness;//=1;
	int ThickLength;//=5;
	int LegendFont;//=OEM_CHARSET;
	CSize LegendSize;//=CSize(0,0);
	COLORREF LegendColor;//=RGB(255,0,0);
	int CurveThickness;//=1;
	COLORREF CurveColor;//=RGB(255,0,0);
	int PointSize;//=5;
	}DrawParameters;



#endif // defined DRAWPARAMETERS_H