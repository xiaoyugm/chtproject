// DrawChart.cpp: implementation of the CDrawChart class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "GUI_VisualStudio.h"
#include "DrawChart.h"
#include "drawdoc.h"
#include "drawview.h"
#include <mmsystem.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

extern SlaveStation             m_SlaveStation[65][25];
extern DisplayDraw    m_DisplayDraw[MAX_POINT_NUMBER];
IMPLEMENT_SERIAL(CDrawChart, CDrawObj, 0)
///////////////////////////////////////////////////////////////////////////////////////
CDrawChart::CDrawChart()
{
}

CDrawChart::~CDrawChart()
{
}

CDrawChart::CDrawChart(const CRect& position)
	: CDrawObj(position)
{
	ASSERT_VALID(this);
}

void CDrawChart::Init()
{
///	CyclesPerSec = 1000.0 / m_Graph.m_SpeedLevel[SpeedLevel];
    CyclesPerSec = 1;
	
	m_nStartTime = 0;								//开始时间
	MaxSeconds   = 3600;	
	mSec = 0;										//最大秒数

	nMinx = nMiny = 0;
	nMaxx = nMaxy = 100;
	CanTicks = TRUE;
	m_nTicks = 0;

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

	CString Line1Name,Line2Name,Line3Name,Line4Name;
	Line1Name.Format("点号:%d",m_nPoint1);
	Line2Name.Format("点号:%d",m_nPoint2);
	Line3Name.Format("点号:%d",m_nPoint3);
	Line4Name.Format("点号:%d",m_nPoint4);

	m_Graph.AddALine(m_clrLine1, 10, 20, Line1Name);
	m_Graph.AddALine(m_clrLine2, 30, 40, Line2Name);
	m_Graph.AddALine(m_clrLine3, 50, 60, Line3Name);
	m_Graph.AddALine(m_clrLine4, 70, 80, Line4Name);

	m_Graph.SetBackColor(m_ctlBackColor);

		for(int i=0; i< 4; i++)
		{
			unsigned short nPointNo ;
			if(i == 0)
        	   nPointNo = m_nPoint1 ;
			if(i == 1)
        	   nPointNo = m_nPoint2 ;
			if(i == 2)
        	   nPointNo = m_nPoint3 ;
			if(i == 3)
        	   nPointNo = m_nPoint4 ;

			double fScaleHigh,fScaleLow,fMax,fMin;
//    		if(m_SlaveStation[m_DisplayDraw[nPointNo].fds][m_DisplayDraw[nPointNo].chan].ptype == 0)
			{
				fScaleHigh = m_SlaveStation[m_DisplayDraw[nPointNo].fds][m_DisplayDraw[nPointNo].chan].m_RangeH;
				fScaleLow = 0;
				fMax = m_SlaveStation[m_DisplayDraw[nPointNo].fds][m_DisplayDraw[nPointNo].chan].Apbrk;
				fMin = m_SlaveStation[m_DisplayDraw[nPointNo].fds][m_DisplayDraw[nPointNo].chan].AlarmValueH;
			}
			m_Graph.m_LineArray[i].m_dScaleHigh = fScaleHigh;
			m_Graph.m_LineArray[i].m_dScaleLow = fScaleLow;
			m_Graph.m_LineArray[i].m_dMax = fMax;
			m_Graph.m_LineArray[i].m_dMin = fMin;
		}

}

void CDrawChart::Serialize(CArchive& ar)
{
	ASSERT_VALID(this);

	CDrawObj::Serialize(ar);
	if (ar.IsStoring())
	{
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

	int n = m_Graph.m_LineArray.GetSize();
	CString str[4];

	if(m_nPoint1 > 0 || m_nPoint2 > 0 || m_nPoint3 > 0 || m_nPoint4 > 0)
	{
		int nn_point ;
	    CString strv[4];
		for(int i=0; i< 4; i++)
		{
			if(i == 0)
				nn_point = m_nPoint1;
			else if(i == 1)
				nn_point = m_nPoint2;
			else if(i == 2)
				nn_point = m_nPoint3;
			else if(i == 3)
				nn_point = m_nPoint4;
//    		if(m_SlaveStation[m_DisplayDraw[nn_point].fds][m_DisplayDraw[nn_point].chan].ptype == 0)
		    	strv[i].Format("%.2f %s",m_SlaveStation[m_DisplayDraw[nn_point].fds][m_DisplayDraw[nn_point].chan].AValue,m_SlaveStation[m_DisplayDraw[nn_point].fds][m_DisplayDraw[nn_point].chan].m_Unit);
//	    	else
//	    		strv[i].Format("%d %s",m_SlaveStation[m_DisplayDraw[nn_point].fds][m_DisplayDraw[nn_point].chan].CValue,m_SlaveStation[m_DisplayDraw[nn_point].fds][m_DisplayDraw[nn_point].chan].m_Unit);
			str[i].Format("%d : ",nn_point);
		}
		
		for( i=0; i< 4; i++)
		{
			m_Graph.m_LineArray[i].m_sName = str[i] +strv[i];
		}
	}
	
	if(!m_Graph.m_bSetingFailed)
	{
		m_Graph.BeginDraw(pDC->m_hDC);
    	OnTimer();
		if(rect.Width()>30 && rect.Height()>30)
		{
			m_Graph.RecalcRects(rect);

				m_Graph.Title("实时曲线" );
    			m_Graph.YAxisTitle("百分比");

				m_Graph.XAxisTitle("时间" );
			m_Graph.Axes();
			m_Graph.Grid();

			m_Graph.EnableLegend();
		}
		m_Graph.DrawRealTimeLines();	
		m_Graph.EndDraw(pDC->m_hDC);
	}
}
/*
int CDrawChart::GetHandleCount()
{
	ASSERT_VALID(this);
	return CDrawObj::GetHandleCount();
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
*/
void CDrawChart::StartAction()
{
	Invalidate();
}
/*
void CDrawChart::Invalidate()
{
	ASSERT_VALID(this);
	m_pDocument->UpdateAllViews(NULL, HINT_UPDATE_DRAWOBJ, this);
}
*/
void CDrawChart::OnTimer()
{
		int n = m_Graph.m_LineArray.GetSize();
		for(int i=0; i<n; i++)
		{
			unsigned short nPointNo ;
			if(i == 0)
        	   nPointNo = m_nPoint1 ;
			if(i == 1)
        	   nPointNo = m_nPoint2 ;
			if(i == 2)
        	   nPointNo = m_nPoint3 ;
			if(i == 3)
        	   nPointNo = m_nPoint4 ;

			unsigned char fvalue = m_SlaveStation[m_DisplayDraw[nPointNo].fds][m_DisplayDraw[nPointNo].chan].pnValue;
//   			m_Graph.AddYValue(i, m_CPointInfo[nPointNo].pnValue * 100 );
			//占值域百分比*100
   			m_Graph.AddYValue(i, fvalue );
		}

		m_Graph.UpdateTimeRange(mSec);
///		mSec += (UINT)(0.5 + 1515);
		mSec += (UINT)(0.5 + 1000 / CyclesPerSec);
		
///		m_Graph.GetCursorTimeAndIndex(CurrentTime);	
		m_Graph.SetPrintTime(mSec - m_nStartTime, m_Graph.MaxTime); // Sim time : max time

    	n = m_Graph.GetCursorTimeAndIndex(CurrentTime);

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

}

/*
CDrawObj* CDrawChart::Clone(CDrawDoc* pDoc)
{
	ASSERT_VALID(this);

	CDrawChart* pClone = new CDrawChart(m_position);

	if (pDoc != NULL)
		pDoc->Add(pClone);

	ASSERT_VALID(pClone);
	return this;
}

void CDrawChart::OnEditProperties()			//编辑属性
{
}
*/