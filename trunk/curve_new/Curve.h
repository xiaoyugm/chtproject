// Curve.h : main header file for the CURVE application
//

#if !defined(AFX_CURVE_H__95A0BCDF_A733_44E2_9A3B_C86096A3C285__INCLUDED_)
#define AFX_CURVE_H__95A0BCDF_A733_44E2_9A3B_C86096A3C285__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols
#include "MainFrm.h"
/////////////////////////////////////////////////////////////////////////////
// CCurveApp:
// See Curve.cpp for the implementation of this class
//
#define MAX_POINT_NUMBER     15000  //最大点数  1-15000
#define MAX_TRUNK_NUMBER     8      //最大干线数1-8
#define MAX_ADDR_NUMBER      128    //最大地址数0--127

// Anolog/SWitch channel 路 入出 位数 名称 
//becare: all num >=1    
//注：前带M表示多功能转接器支持
#define MS8IN_B38  	      1     //M0  
#define MS5OUT_B25  	  2     //M1
#define MA4IN             3     //M3
#define MP16IN            4     //M4
#define A1IN8BIT_CH4ICO  5      //CH4     
#define A1IN8BIT_A50     6
#define A8IN8BIT_MCA     7
#define A8IN8BIT_MC8     8
#define A1OUT8BIT_C35    9
#define P16IN            10     //pulse 16 channel
#define S8IN_B38  	     11     //M0
#define S8OUT_B48        12     //
#define S5OUT_B25  	     13     //M1
#define MULTICONV        14 
#define A4IN             15     //M3
#define S16IN           16


class CCurveApp : public CWinApp
{
public:
	CCurveApp();
	CSingleDocTemplate* pDocTemplate;         //0126

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCurveApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CCurveApp)
	afx_msg void OnAppAbout();
	afx_msg void OnFileNew();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CURVE_H__95A0BCDF_A733_44E2_9A3B_C86096A3C285__INCLUDED_)
