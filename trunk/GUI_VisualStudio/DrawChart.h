// DrawChart.h: interface for the CDrawChart class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DRAWCHART_H__0129F3CE_D69F_4194_BB21_AE438A8DAD58__INCLUDED_)
#define AFX_DRAWCHART_H__0129F3CE_D69F_4194_BB21_AE438A8DAD58__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

///#include <RealTime.h>
#include "RealTime//RealTime.h"
#include "DrawObj.h"
#include <mmsystem.h>
///#pragma comment(lib,"CurveT.lib")

class CDrawView;
class CDrawDoc;

class CDrawChart : public CDrawObj  
{
public:
	DECLARE_SERIAL(CDrawChart);
	CDrawChart();
	virtual ~CDrawChart();

public:
	CDrawChart(const CRect& position);
public:
	virtual void Serialize(CArchive& ar);
	virtual void Draw(CDC* pDC);
///	virtual int GetHandleCount();
///	virtual CPoint GetHandle(int nHandle);
///	virtual HCURSOR GetHandleCursor(int nHandle);
///	virtual void MoveHandleTo(int nHandle, CPoint point, CDrawView* pView = NULL);
///	virtual BOOL Intersects(const CRect& rect);
///	virtual CDrawObj* Clone(CDrawDoc* pDoc);
///	virtual void OnEditProperties();
///	virtual void Invalidate();
	void    StartAction();

	void OnTimer();
	void Init();

public:
	CRealTime  m_Graph;

	DWORD  m_nStartTime;
	UINT   m_nTimeSpan;
	DWORD  MaxSeconds;
	double CyclesPerSec;

	int		SpeedLevel;
	unsigned char fvalue;

	COLORREF	m_ctlBackColor;
	int    nMinx,nMiny,nMaxx,nMaxy;
	COLORREF    m_clrLine1,
				m_clrLine2,
				m_clrLine3,
				m_clrLine4;

	BOOL    CanTicks;
	WORD    m_nTicks;
	DWORD	CurrentTime;
	DWORD	mSec;
	UINT    m_nPoint1,m_nPoint2,m_nPoint3,m_nPoint4;

};

#endif // !defined(AFX_DRAWCHART_H__0129F3CE_D69F_4194_BB21_AE438A8DAD58__INCLUDED_)
