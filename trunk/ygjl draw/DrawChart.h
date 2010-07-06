// DrawChart.h: interface for the CDrawChart class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DRAWCHART_H__0129F3CE_D69F_4194_BB21_AE438A8DAD58__INCLUDED_)
#define AFX_DRAWCHART_H__0129F3CE_D69F_4194_BB21_AE438A8DAD58__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DrawObj.h"
#include <mmsystem.h>

#include <RealTime.h>
#pragma comment(lib,"CurveT.lib")

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
	virtual int GetHandleCount();
	virtual CPoint GetHandle(int nHandle);
	virtual HCURSOR GetHandleCursor(int nHandle);
	virtual void MoveHandleTo(int nHandle, CPoint point, CDrawView* pView = NULL);
	virtual BOOL Intersects(const CRect& rect);
	virtual CDrawObj* Clone(CDrawDoc* pDoc);
	virtual void OnEditProperties();

	void OnTimer();						//时间消息
	BOOL StartRealTime();				//开始绘制实时曲线
	void Init();						//初始化

public:
	CRealTime	m_Graph;					//实时曲线类
	DWORD		m_nStartTime;				//开始时间
	UINT		m_nTimeSpan;				//时间跨步
	DWORD		MaxSeconds;					//最大秒数
	double		CyclesPerSec;		

	int			SpeedLevel;					//速度

	COLORREF	m_ctlBackColor;				//背景颜色
	int			nMinx,nMiny,nMaxx,nMaxy;	//取值范围
	COLORREF    m_clrLine1,					//线条颜色
				m_clrLine2,
				m_clrLine3,
				m_clrLine4;

	
	BOOL        m_IsRealTime;
	BOOL		m_bTimeOn;
	BOOL		m_nIsStartRealTime;
	BOOL		CanTicks;
	WORD		m_nTicks;
	DWORD		CurrentTime;
	DWORD		mSec;
	UINT		nTimerIDChart;
	UINT		m_nPoint1,m_nPoint2,m_nPoint3,m_nPoint4;
};

#endif // !defined(AFX_DRAWCHART_H__0129F3CE_D69F_4194_BB21_AE438A8DAD58__INCLUDED_)
