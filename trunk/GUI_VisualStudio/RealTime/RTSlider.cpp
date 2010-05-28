// RTSlider.cpp : implementation file
//

#include "stdafx.h"
///#include "Draw.h"
#include "RTSlider.h"

///#include "drawdoc.h"
///#include "drawview.h"
#include "..\\DrawChart.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRTSlider

CRTSlider::CRTSlider()
{
	m_sType	   = TICK;
	m_nCurPos  = 0;
}

CRTSlider::~CRTSlider()
{
}


BEGIN_MESSAGE_MAP(CRTSlider, CSliderCtrl)
	//{{AFX_MSG_MAP(CRTSlider)
	ON_WM_LBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRTSlider message handlers

void CRTSlider::OnLButtonUp(UINT nFlags, CPoint point) 
{
	m_nCurPos = GetPos();
	if (m_sType == TICK)
	{
		CDrawChart* pWnd = (CDrawChart*)GetParent();
		ASSERT_VALID(pWnd);
		if (pWnd->m_Graph.m_nTick == m_nCurPos)
		{
			CSliderCtrl::OnLButtonUp(nFlags, point);
			return;
		}
		else
		{
			pWnd->m_Graph.m_nTick = m_nCurPos;
//			pWnd->RefreshGraph();
		}
	}
/*	else if (m_sType == PAGE)
	{
		CRTForm* pForm = (CRTForm*)GetParent();
		ASSERT_VALID(pForm);
		CRTDemoView* pWnd = (CRTDemoView*)pForm->GetRTDemoView();
		if (pWnd->m_Graph.m_nPage == m_nCurPos)
		{
			CSliderCtrl::OnLButtonUp(nFlags, point);
			return;
		}
		else if (m_nCurPos == GetRangeMax())
			pWnd->m_Graph.m_bAutoScrollX = TRUE;
		else
			pWnd->m_Graph.m_bAutoScrollX = FALSE;

		pWnd->m_Graph.m_nPage = m_nCurPos;
		pWnd->m_Graph.Reset();
		pWnd->RefreshGraph();
	}
	*/
	CSliderCtrl::OnLButtonUp(nFlags, point);
}
