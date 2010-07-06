// DrawChart.cpp: implementation of the CDrawChart class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Draw.h"
#include "DrawChart.h"
#include "drawdoc.h"
#include "drawview.h"
#include "RealTimeDialog.h"
#include <mmsystem.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

extern "C"
void CALLBACK RealTimerProc(UINT id,UINT msg,DWORD dwUser,DWORD dw1,DWORD dw2)
{
	CDrawChart *	DrawChart = (CDrawChart *)dwUser;
	DrawChart->OnTimer();
}

IMPLEMENT_SERIAL(CDrawChart, CDrawObj, 0)
///////////////////////////////////////////////////////////////////////////////////////
CDrawChart::CDrawChart()
{
	
}

CDrawChart::~CDrawChart()
{
	if(nTimerIDChart)
		timeKillEvent(nTimerIDChart);
}


CDrawChart::CDrawChart(const CRect& position)
	: CDrawObj(position)
{
	ASSERT_VALID(this);

	SpeedLevel	 = 6;								//速度

	m_ctlBackColor = RGB(255,255,255);				//背景颜色
	nMinx = nMiny = 0;
	nMaxx = nMaxy = 100;
	CanTicks = TRUE;
	m_nTicks = 0;
	m_clrLine1 = RGB(255,   0,   0);
	m_clrLine2 = RGB(  0, 255,   0);
	m_clrLine3 = RGB(  0,   0, 255);
	m_clrLine4 = RGB(255,   0, 255);
	m_nTimeSpan	 = 60;								//时间范围	
	m_IsRealTime = TRUE;
	Init();
}

void CDrawChart::Init()
{
	CyclesPerSec = 1000.0 / m_Graph.m_SpeedLevel[SpeedLevel];
//	CyclesPerSec = 1;
	m_nStartTime = 0;								//开始时间
	MaxSeconds   = 120;	
	mSec = m_nStartTime;							//最大秒数

	m_Graph.SetXNumOfTicks(60);	

	if (!m_Graph.SetRange(nMinx, nMiny, nMaxx, nMaxy))
	{
		m_Graph.m_bSetingFailed = true;
		AfxMessageBox("Setting Range failed");
		return;
	}

	m_Graph.EnableMemoryDraw(TRUE);

	if (!m_Graph.InitialSetting(CyclesPerSec,  m_nStartTime, m_nTimeSpan, MaxSeconds, 6))
	{
		m_Graph.m_bSetingFailed = true;
		return;
	}
	m_Graph.m_bSetingFailed = false;

	m_bTimeOn = FALSE;
	m_nIsStartRealTime = FALSE;

	m_Graph.AddALine(m_clrLine1, 10, 20, "Line1");
	m_Graph.AddALine(m_clrLine2, 30, 40, "Line2");
	m_Graph.AddALine(m_clrLine3, 50, 60, "Line3");
	m_Graph.AddALine(m_clrLine4, 70, 80, "Line4");

//	m_Graph.AddALine(m_clrLine5, 50, 60, "Line5");
//	m_Graph.AddALine(m_clrLine6, 60, 70, "Line6");
//	m_Graph.AddALine(m_clrLine7, 70, 80, "Line7");
//	m_Graph.AddALine(m_clrLine8, 80, 90, "Line8");
}

void CDrawChart::Serialize(CArchive& ar)
{
	ASSERT_VALID(this);

	CDrawObj::Serialize(ar);
	if (ar.IsStoring())
	{
		ar << SpeedLevel;
		ar.Write(&m_ctlBackColor,sizeof(COLORREF));
		ar.Write(&m_clrLine1,    sizeof(COLORREF));
		ar.Write(&m_clrLine2,    sizeof(COLORREF));
		ar.Write(&m_clrLine3,    sizeof(COLORREF));
		ar.Write(&m_clrLine4,    sizeof(COLORREF));
		ar << nMinx;
		ar << nMiny;
		ar << nMaxx;
		ar << nMaxy;
		ar << m_nPoint1;
		ar << m_nPoint2;
		ar << m_nPoint3;
		ar << m_nPoint4;
		ar << m_nTimeSpan;
	}
	else
	{
		ar >> SpeedLevel;
		ar.Read(&m_ctlBackColor,sizeof(COLORREF));
		ar.Read(&m_clrLine1,    sizeof(COLORREF));
		ar.Read(&m_clrLine2,    sizeof(COLORREF));
		ar.Read(&m_clrLine3,    sizeof(COLORREF));
		ar.Read(&m_clrLine4,    sizeof(COLORREF));
		ar >> nMinx;
		ar >> nMiny;
		ar >> nMaxx;
		ar >> nMaxy;
		ar >> m_nPoint1;
		ar >> m_nPoint2;
		ar >> m_nPoint3;
		ar >> m_nPoint4;
		ar >> m_nTimeSpan;
		Init();
	}
}


void CDrawChart::Draw(CDC* pDC)
{
	ASSERT_VALID(this);
	CRect rect = m_position;
	rect.NormalizeRect();
	CRect rc = CRect(rect.left,rect.bottom,rect.right,rect.top);
	
	m_Graph.m_LineArray[0].SetLineColor(m_clrLine1);
	m_Graph.m_LineArray[1].SetLineColor(m_clrLine2);
	m_Graph.m_LineArray[2].SetLineColor(m_clrLine3);
	m_Graph.m_LineArray[3].SetLineColor(m_clrLine4);
	int n = m_Graph.m_LineArray.GetSize();
	CString str[4];
	if(m_nPoint1 > 0 || m_nPoint2 > 0 || m_nPoint3 > 0 || m_nPoint4 > 0)
	{
		str[0].Format("点号:%d",m_nPoint1);
		str[1].Format("点号:%d",m_nPoint2);
		str[2].Format("点号:%d",m_nPoint3);
		str[3].Format("点号:%d",m_nPoint4);
		
		for(int i=0; i< 4; i++)
		{
			m_Graph.m_LineArray[i].m_sName = str[i];
		}
	}

	m_Graph.SetBackColor(m_ctlBackColor);
	
		m_Graph.RecalcRects(rect);
	m_Graph.BeginDraw(pDC->m_hDC);
	if(rect.Width()>30 && rect.Height()>30)
	{

		m_Graph.RecalcRects(rect);
			m_Graph.XAxisTitle("时间");
			m_Graph.Title("实时曲线");

		m_Graph.Axes();
		m_Graph.Grid();
		m_Graph.EnableLegend(true);
		
		m_Graph.DrawRealTimeLines();	
	}
	m_Graph.EndDraw(pDC->m_hDC );
	
//	if(!m_bTimeOn)
//	{
//		if(!m_nIsStartRealTime)
//			m_nIsStartRealTime = StartRealTime();
//
//	}

}



int CDrawChart::GetHandleCount()
{
	ASSERT_VALID(this);
	return CDrawObj::GetHandleCount();
}

// returns center of handle in logical coordinates
CPoint CDrawChart::GetHandle(int nHandle)
{
	ASSERT_VALID(this);

	return CDrawObj::GetHandle(nHandle);
}

HCURSOR CDrawChart::GetHandleCursor(int nHandle)
{
	ASSERT_VALID(this);

	return CDrawObj::GetHandleCursor(nHandle);
}

// point is in logical coordinates
void CDrawChart::MoveHandleTo(int nHandle, CPoint point, CDrawView* pView)
{
	ASSERT_VALID(this);
	CDrawObj::MoveHandleTo(nHandle, point, pView);
}

// rect must be in logical coordinates
BOOL CDrawChart::Intersects(const CRect& rect)
{
	ASSERT_VALID(this);
	CRect rectT = rect;
	rectT.NormalizeRect();

	CRect fixed = m_position;
	fixed.NormalizeRect();
	if ((rectT & fixed).IsRectEmpty())
		return FALSE;
	return TRUE;

}

void CDrawChart::OnTimer()
{
		int n = m_Graph.m_LineArray.GetSize();
		for(int i=0; i<n; i++)
		{
			int m_dY = m_Graph.m_LineArray[i].m_dScaleLow + 
				(m_Graph.m_LineArray[i].m_dScaleHigh - 
				m_Graph.m_LineArray[i].m_dScaleLow);
			m_Graph.AddYValue(i, m_dY);
		}
		
		m_Graph.UpdateTimeRange(mSec);
		mSec += (UINT)(0.5 + 1000 / CyclesPerSec);
		
		m_Graph.GetCursorTimeAndIndex(CurrentTime);	
		m_Graph.SetPrintTime(mSec - m_nStartTime, m_Graph.MaxTime); // Sim time : max time
		m_Graph.SetPrintTime(CurrentTime - m_nStartTime, m_Graph.CursorTime); // cursor time
		
		
		if (CanTicks && m_Graph.m_nTimes / (m_nTimeSpan + 1) > m_nTicks && 
			MaxSeconds >= m_Graph.m_nTimes + 1)
		{
			m_nTicks = m_Graph.m_nTimes / m_nTimeSpan;
			if (m_nTicks >= m_Graph.m_nMaxPages) 
				CanTicks = FALSE;
			else
			{
				m_Graph.m_nPage = m_nTicks + 1;
			}
		}
		
		if (m_Graph.m_nTick < m_Graph.m_nSTicks)
		{
			m_Graph.m_nTick ++;
		}

//	Invalidate();
}

BOOL CDrawChart::StartRealTime()
{
	nTimerIDChart = timeSetEvent(200,1000,RealTimerProc,(DWORD)this,false ? TIME_ONESHOT : TIME_PERIODIC);
	if (nTimerIDChart)
	{
		return TRUE;
	}
	return FALSE;
}

CDrawObj* CDrawChart::Clone(CDrawDoc* pDoc)
{
	ASSERT_VALID(this);

	CDrawChart* pClone = new CDrawChart(m_position);
	pClone->m_nStartTime = m_nStartTime;
	pClone->SpeedLevel = SpeedLevel;
	pClone->CyclesPerSec = CyclesPerSec;
	pClone->m_nStartTime = m_nStartTime;
	pClone->m_nTimeSpan = m_nTimeSpan;
	pClone->MaxSeconds = MaxSeconds;
	pClone->m_ctlBackColor = m_ctlBackColor;
	pClone->m_clrLine1 = m_clrLine1;
	pClone->m_clrLine2 = m_clrLine2;
	pClone->m_clrLine3 = m_clrLine3;
	pClone->m_clrLine4 = m_clrLine4;
//	pClone->m_clrLine5 = m_clrLine5;
//	pClone->m_clrLine6 = m_clrLine6;
//	pClone->m_clrLine7 = m_clrLine7;
//	pClone->m_clrLine8 = m_clrLine8;

	pClone->nMinx = nMinx;
	pClone->nMiny = nMiny;
	pClone->nMaxx = nMaxx;
	pClone->nMaxy = nMaxy;
	pClone->m_nTimeSpan = m_nTimeSpan;
	

	if (pDoc != NULL)
		pDoc->Add(pClone);

	ASSERT_VALID(pClone);
	return this;
}

void CDrawChart::OnEditProperties()			//编辑属性
{
	CRealTimeDialog dlg;
	dlg.m_clrBackColor = m_ctlBackColor;
	dlg.m_clrLine1 = m_clrLine1;
	dlg.m_clrLine2 = m_clrLine2;
	dlg.m_clrLine3 = m_clrLine3;
	dlg.m_clrLine4 = m_clrLine4;
	dlg.m_nXMax = nMaxx;
	dlg.m_nXMin = nMinx;
	dlg.m_nYMax = nMaxy;
	dlg.m_nYMin = nMiny;
	dlg.m_nTimeSpan = m_nTimeSpan;

	dlg.m_nPoint1 = m_nPoint1;
	dlg.m_nPoint2 = m_nPoint2;
	dlg.m_nPoint3 = m_nPoint3;
	dlg.m_nPoint4 = m_nPoint4;

	if(dlg.DoModal() != IDOK)
		return;

	m_ctlBackColor = dlg.m_clrBackColor;
	m_clrLine1 = dlg.m_clrLine1;
	m_clrLine2 = dlg.m_clrLine2;
	m_clrLine3 = dlg.m_clrLine3;
	m_clrLine4 = dlg.m_clrLine4;

	m_nPoint1 = dlg.m_nPoint1;
	m_nPoint2 = dlg.m_nPoint2;
	m_nPoint3 = dlg.m_nPoint3;
	m_nPoint4 = dlg.m_nPoint4;



	nMaxx = dlg.m_nXMax ;
	nMinx = dlg.m_nXMin ;
	nMaxy = dlg.m_nYMax ;
	nMiny = dlg.m_nYMin ;
	m_nTimeSpan = dlg.m_nTimeSpan;

	m_pDocument->SetModifiedFlag();
	Invalidate();
}