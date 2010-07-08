// CurveView.cpp : implementation of the CCurveView class
//

#include "stdafx.h"
#include "Curve.h"
#include "CurveDoc.h"
#include "CurveView.h"
//#include "SystemData.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCurveView

IMPLEMENT_DYNCREATE(CCurveView, CView)

BEGIN_MESSAGE_MAP(CCurveView, CView)
	//{{AFX_MSG_MAP(CCurveView)
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(ID_GRAPHIC_PROPERTY, OnGraphicProperty)
	ON_WM_LBUTTONDOWN()
	ON_WM_ERASEBKGND()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_LBUTTONUP()
	ON_COMMAND(ID_GRAPHIC_RESTORE, OnGraphicRestore)
	ON_COMMAND(ID_GRAPHIC_EXPEND, OnGraphicExpend)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCurveView construction/destruction

CCurveView::CCurveView()
{
///	m_pRtCurve = NULL;
	m_MemDC = NULL;
	m_MemBitmap = NULL;
	m_NewPoint.x = 0;
	m_NewPoint.y = 0;
	m_OldPoint.x = 0;
	m_OldPoint.y = 0;
    m_LARGEPoint.x = 0;
    m_LARGEPoint.y = 0;
	m_bLButtonDown = FALSE;
	m_bCtrlButton = FALSE;
}

CCurveView::~CCurveView()
{

}

BOOL CCurveView::PreCreateWindow(CREATESTRUCT& cs)
{
	if (!CView::PreCreateWindow(cs))
		return FALSE;
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CCurveView drawing

void CCurveView::OnDraw(CDC* pDC)
{
	CCurveDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if(m_MemDC == NULL)
	{
		m_MemDC = new CDC();
		m_MemDC->CreateCompatibleDC(pDC);
		OnPrepareDC(m_MemDC);
	}

	if(m_MemBitmap == NULL)
	{
		m_MemBitmap = new CBitmap();
		if(m_MemBitmap->CreateCompatibleBitmap(pDC,m_screenx,m_screeny))
		{
			m_MemDC->SelectObject(m_MemBitmap);
		}
		else return;
	}

	pDoc->m_pRtCurve->Draw(m_MemDC);
	if(m_bLButtonDown && m_bCtrlButton)
	{	
		CRect rect(m_OldPoint,m_NewPoint);
//		rect.NormalizeRect();
	//	int mode = m_MemDC->SetROP2(R2_NOT);
		CPen pen(PS_DOT,1,RGB(0,255,255));
///		m_MemDC->SelectObject(pen);
    	CPen  *pdrawOldPen = m_MemDC->SelectObject(&pen);
		m_MemDC->MoveTo(rect.left,rect.top);
		m_MemDC->LineTo(rect.right,rect.top);
		m_MemDC->LineTo(rect.right,rect.bottom);
		m_MemDC->LineTo(rect.left,rect.bottom);
		m_MemDC->LineTo(rect.left,rect.top);
    	m_MemDC->SelectObject(pdrawOldPen);
	//	m_MemDC->SetROP2(mode);
	}
	if(m_MemDC != pDC)
	{
		pDC->BitBlt(0,0,m_screenx,m_screeny,m_MemDC,0,0,SRCCOPY);
	}

}

/////////////////////////////////////////////////////////////////////////////
// CCurveView printing

BOOL CCurveView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CCurveView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}

void CCurveView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}

/////////////////////////////////////////////////////////////////////////////
// CCurveView diagnostics

#ifdef _DEBUG
void CCurveView::AssertValid() const
{
	CView::AssertValid();
}

void CCurveView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCurveDoc* CCurveView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCurveDoc)));
	return (CCurveDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCurveView message handlers

void CCurveView::OnInitialUpdate() 
{
	GetClientRect(m_ClientRect);
	m_screenx = m_ClientRect.Width();
	m_screeny = m_ClientRect.Height();
	CCurveDoc* pDoc = GetDocument();
///	pDoc->m_pRtCurve->m_bLock = TRUE;
	pDoc->m_pRtCurve->m_bHistory = TRUE;
	pDoc->m_pRtCurve->m_pointArray[0].x = 0;//rect.left;
	pDoc->m_pRtCurve->m_pointArray[0].y = 0;//rect.top;
	pDoc->m_pRtCurve->m_pointArray[1].x = m_screenx;//rect.right;
	pDoc->m_pRtCurve->m_pointArray[1].y = m_screeny;//rect.bottom;	
	CView::OnInitialUpdate();
}

void CCurveView::OnRButtonDown(UINT nFlags, CPoint point) 
{
	CPoint pt;
	CMenu menu;
	CMenu* pPopup;
	CWnd* pWndPopupOwner;
	int x = GetScrollPos(SB_HORZ);
	int y = GetScrollPos(SB_VERT);
	point.x += x;
	point.y += y;

	CMainFrame *pMainFrame = (CMainFrame *)AfxGetApp()->m_pMainWnd;

	pt.x = point.x - x;
	pt.y = point.y - y;
//    m_pRtCurve->m_nStandard=pt.x;
    m_LARGEPoint = point;

	ClientToScreen(&pt);
	VERIFY(menu.LoadMenu(IDR_GRAPHIC_PROPERTY));
	pPopup = menu.GetSubMenu(0);
	ASSERT(pPopup != NULL);
	pWndPopupOwner = GetTopLevelFrame();
	pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON,pt.x,pt.y,pWndPopupOwner);
	CView::OnRButtonDown(nFlags, point);
}

void CCurveView::OnGraphicProperty() 
{
	CCurveProp	curveProp;
	CCurveDoc* pDoc = GetDocument();
	curveProp.m_pCurveProp = pDoc->m_pRtCurve->m_curveProp;
	curveProp.m_colorBg = pDoc->m_pRtCurve->m_colorBrush;
	curveProp.m_sCheckGrid = pDoc->m_pRtCurve->m_sCheckGrid ;
    curveProp.m_sPoint = pDoc->m_pRtCurve->m_curveProp[0].point ;
			curveProp.m_sStartHour = pDoc->m_pRtCurve->m_sStartHour ;
			curveProp.m_sEndHour = pDoc->m_pRtCurve->m_sEndHour ;
			curveProp.m_startMin = pDoc->m_pRtCurve->m_sStartMin ;
			curveProp.m_endMin = pDoc->m_pRtCurve->m_sEndMin ;
	if(curveProp.DoModal() == IDOK)
	{
		pDoc->m_pRtCurve->m_colorBrush = curveProp.m_colorBg;
		pDoc->m_pRtCurve->m_sCheckGrid = curveProp.m_sCheckGrid;
		if(pDoc->m_pRtCurve->m_bHistory)
		{
			pDoc->m_pRtCurve->m_strStartDate.Format("%d-%d-%d",curveProp.m_startDate.GetYear(),curveProp.m_startDate.GetMonth(),curveProp.m_startDate.GetDay());
			pDoc->m_pRtCurve->m_strEndDate.Format("%d-%d-%d",curveProp.m_endDate.GetYear(),curveProp.m_endDate.GetMonth(),curveProp.m_endDate.GetDay());
			pDoc->m_pRtCurve->m_sStartHour = curveProp.m_sStartHour;
			pDoc->m_pRtCurve->m_sEndHour = curveProp.m_sEndHour;
			pDoc->m_pRtCurve->m_sStartMin = curveProp.m_startMin;
			pDoc->m_pRtCurve->m_sEndMin = curveProp.m_endMin;
			pDoc->m_pRtCurve->InsertHistoryData();
			InvalidateRect(pDoc->m_pRtCurve->GetRect());
		}
	}
}

void CCurveView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CCurveDoc* pDoc = GetDocument();
	if((nFlags & MK_CONTROL) == 0)
	{
		if(pDoc->m_pRtCurve->m_nTime > 0)
		{	
			pDoc->m_pRtCurve->ShowValue(point);
			Invalidate();
		}
	}
	else 
    	m_bLButtonDown = TRUE;
	m_OldPoint = point;
	m_NewPoint = point;
	SetCapture();
	CView::OnLButtonDown(nFlags, point);
}

BOOL CCurveView::OnEraseBkgnd(CDC* pDC) 
{
	return true;
}

void CCurveView::OnMouseMove(UINT nFlags, CPoint point) 
{
	CCurveDoc* pDoc = GetDocument();
	if((nFlags & MK_LBUTTON) == 0)
		return;
	if((nFlags & MK_CONTROL) == 0)
	{
		m_bCtrlButton = FALSE;
		if(pDoc->m_pRtCurve->m_nTime > 0)
			pDoc->m_pRtCurve->ShowValue(point);
	}
	else m_bCtrlButton = TRUE;
	m_NewPoint = point;
	Invalidate();
	CView::OnMouseMove(nFlags, point);
}

void CCurveView::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	CCurveDoc* pDoc = GetDocument();
	pDoc->m_pRtCurve->GetCurrentPoint(point);	
	CView::OnLButtonDblClk(nFlags, point);
}

void CCurveView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	CCurveDoc* pDoc = GetDocument();
	m_bLButtonDown = FALSE;
	m_bCtrlButton = FALSE;
	ReleaseCapture();
	CRect rect(m_OldPoint,m_NewPoint);
//	rect.NormalizeRect();
	if(pDoc->m_pRtCurve->m_rect.PtInRect(m_OldPoint) || pDoc->m_pRtCurve->m_rect.PtInRect(m_NewPoint) )
	{
		if((rect.Width() > 0) && (rect.Height() > 0))
		{
			if((nFlags & MK_CONTROL) != 0)
			{
                pDoc->m_pRtCurve->m_oldPoint = m_OldPoint ;
                pDoc->m_pRtCurve->m_newPoint = m_NewPoint ;
				pDoc->m_pRtCurve->ZoomIn(rect);
			}
		}
	}
	Invalidate();
	CView::OnLButtonUp(nFlags, point);
}

void CCurveView::OnGraphicRestore() 
{
	CCurveDoc* pDoc = GetDocument();
	if(pDoc->m_pRtCurve->m_nZoom > 0)
	{	
		pDoc->m_pRtCurve->Restore();
		Invalidate();
	}
}

void CCurveView::OnGraphicExpend() 
{	
	CCurveDoc* pDoc = GetDocument();
	pDoc->m_pRtCurve->Expend(m_LARGEPoint);
//	pDoc->m_pRtCurve->Expend();
	Invalidate();	
}
