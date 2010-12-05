
#include "stdafx.h"
#include "GUI_VisualStudio.h"
#include "drawdoc.h"
#include "drawview.h"
#include "drawobj.h"
#include "drawtool.h"
#include "drawrect.h"
#include "drawpoly.h"
#include "drawbutton.h"
#include "DrawConduit.h"
#include "DrawCar.h"
#include "DrawRotary.h"
///#include "DrawHistory.h"
/////////////////////////////////////////////////////////////////////////////
// CDrawTool implementation

CPtrList CDrawTool::c_tools;

static CSelectTool	selectTool;
static CZoomTool	zoomTool;
static CRectTool	lineTool(line);
static CRectTool	arrowTool(arrow);
static CRectTool	rectTool(rect);
static CRectTool	rectNoFillTool(rectNoFill);
static CRectTool	roundRectTool(roundRect);
static CRectTool	roundRectNoFillTool(roundRectNoFill);
static CRectTool	ellipseTool(ellipse);
static CRectTool	ellipseNoFillTool(ellipseNoFill);
static CPolyTool	polyTool(poly);
static CPolyTool	polyNoFillTool(polyNoFill);
//static CConduitTool conduitTool(conduit);
//static CCurveTool	curveTool;
static CRectTool	pieTool(pie);
static CRectTool	pie45Tool(pie45);
static CRectTool	imageTool(image);
static CRectTool	beelineTool(beeline);

static CButtonTool	buttonTool(button);
static CButtonTool	textTool(text);
static CButtonTool	pictureTool(picture);
static CRectTool	GroupTool(group);
static CRectTool	WarnTool(warning);
static CRectTool	qieTool(qie);
/*
static CChartTool	chartTool(chart);
static CChartTool	HchartTool(Hchart);

static CWarnTool	warnTool(warn);
static CCarTool		CarTool(car);
static CRotaryTool	RotaryTool(rotary);*/

CPoint CDrawTool::c_down;
UINT CDrawTool::c_nDownFlags;
CPoint CDrawTool::c_last;
DrawShape CDrawTool::c_drawShape = selection;

CDrawTool::CDrawTool(DrawShape drawShape)
{
	m_drawShape = drawShape;
	c_tools.AddTail(this);
}

CDrawTool* CDrawTool::FindTool(DrawShape drawShape)
{
	POSITION pos = c_tools.GetHeadPosition();
	while (pos != NULL)
	{
		CDrawTool* pTool = (CDrawTool*)c_tools.GetNext(pos);
		if (pTool->m_drawShape == drawShape)
			return pTool;
	}

	return NULL;
}

void CDrawTool::OnLButtonDown(CDrawView* pView, UINT nFlags, const CPoint& point)
{
	// deactivate any in-place active item on this view!
	COleClientItem* pActiveItem = pView->GetDocument()->GetInPlaceActiveItem(pView);
	if (pActiveItem != NULL)
	{
		pActiveItem->Close();
		ASSERT(pView->GetDocument()->GetInPlaceActiveItem(pView) == NULL);
	}

	pView->SetCapture();
	c_nDownFlags = nFlags;
	c_down = point;
	c_last = point;
}

void CDrawTool::OnLButtonDblClk(CDrawView* /*pView*/, UINT /*nFlags*/, const CPoint& /*point*/)
{
}

void CDrawTool::OnLButtonUp(CDrawView* /*pView*/, UINT /*nFlags*/, const CPoint& point)
{
	ReleaseCapture();

	if (point == c_down)
		c_drawShape = selection;
}

void CDrawTool::OnMouseMove(CDrawView* /*pView*/, UINT /*nFlags*/, const CPoint& point)
{
	c_last = point;
	SetCursor(AfxGetApp()->LoadStandardCursor(IDC_ARROW));
}

void CDrawTool::OnEditProperties(CDrawView* /*pView*/)
{
}

void CDrawTool::OnCancel()
{
	c_drawShape = selection;
}

////////////////////////////////////////////////////////////////////////////
// CResizeTool

enum SelectMode
{
	NONE,
	netSelect,
	move,
	size
};

SelectMode selectMode = NONE;
int nDragHandle;

CPoint lastPoint;

CSelectTool::CSelectTool()
	: CDrawTool(selection)
{
}

void CSelectTool::OnLButtonDown(CDrawView* pView, UINT nFlags, const CPoint& point)
{
	CPoint local = point;
	pView->ClientToDoc(local);

	CDrawObj* pObj;
	selectMode = NONE;

	// Check for resizing (only allowed on single selections)
	if (pView->m_selection.GetCount() == 1)
	{
		pObj = pView->m_selection.GetHead();
		nDragHandle = pObj->HitTest(local, pView, TRUE);
		if (nDragHandle != 0)
			selectMode = size;
	}

	// See if the click was on an object, select and start move if so
	if (selectMode == NONE)
	{
		pObj = pView->GetDocument()->ObjectAt(local);

		if (pObj != NULL)
		{
			selectMode = move;

/*			if(pObj->m_strGroupName.GetLength()>0 )			//选择组
				pView->SelectGroup(pObj);
			else
			{
				if(pObj->m_strUnitName.GetLength()>0)
					pView->SelectUnit(pObj);
				else
				{
					
					if (!pView->IsSelected(pObj))
						pView->Select(pObj, (nFlags & MK_SHIFT) != 0);
					
					// Ctrl+Click clones the selection...
					if ((nFlags & MK_CONTROL) != 0)
						pView->CloneSelection();
				}
			}*/
		


		}
	}


	// Click on background, start a net-selection
	if (selectMode == NONE)
	{
//		if ((nFlags & MK_SHIFT) == 0)
//			pView->Select(NULL);

		selectMode = netSelect;

		CClientDC dc(pView);
		CRect rect(point.x, point.y, point.x, point.y);
		rect.NormalizeRect();
		dc.DrawFocusRect(rect);
	}

	lastPoint = local;
	CDrawTool::OnLButtonDown(pView, nFlags, point);
}

void CSelectTool::OnLButtonDblClk(CDrawView* pView, UINT nFlags, const CPoint& point)
{
	if ((nFlags & MK_SHIFT) != 0)
	{
		// Shift+DblClk deselects object...
		CPoint local = point;
		pView->ClientToDoc(local);
		CDrawObj* pObj = pView->GetDocument()->ObjectAt(local);
//		if (pObj != NULL)
//			pView->Deselect(pObj);
	}
	else
	{
		//双击鼠标左键调用属性对话框
		// "Normal" DblClk opens properties, or OLE server...
		if (pView->m_selection.GetCount() == 1 ||
			(pView->m_selection.GetCount() > 0 && 
			(pView->m_selection.GetHead()->m_strGroupName.GetLength() > 0||
			pView->m_selection.GetHead()->m_strUnitName .GetLength() > 0)))
			pView->m_selection.GetHead()->OnOpen(pView);
	}

	CDrawTool::OnLButtonDblClk(pView, nFlags, point);
}

void CSelectTool::OnEditProperties(CDrawView* pView)
{
	if (pView->m_selection.GetCount() == 1 ||
		pView->m_selection.GetHead()->m_strGroupName.GetLength() > 0)
		pView->m_selection.GetHead()->OnEditProperties();
}

void CSelectTool::OnLButtonUp(CDrawView* pView, UINT nFlags, const CPoint& point)
{
	if (pView->GetCapture() == pView)
	{
		if (selectMode == netSelect)
		{
			CClientDC dc(pView);
			CRect rect(c_down.x, c_down.y, c_last.x, c_last.y);
			rect.NormalizeRect();
			dc.DrawFocusRect(rect);

//			pView->SelectWithinRect(rect, TRUE);
		}
		else if (selectMode != NONE)
		{
			pView->GetDocument()->UpdateAllViews(pView);
		}
	}
	if(pView->m_selection.GetCount() >0)
	{
		POSITION pos = pView->m_selection.GetHeadPosition();
		while(pos != NULL)
		{
			CDrawObj * pObj = pView->m_selection.GetNext(pos);
			if(pObj->IsKindOf(RUNTIME_CLASS(CDrawCar)))
			{
				CDrawCar*  pCar = (CDrawCar*)pObj;
//				pCar->AddCarRect(pObj->m_position);
				pView->GetDocument()->UpdateAllViews(NULL);
			}
		}		
	}

	CDrawTool::OnLButtonUp(pView, nFlags, point);
}

void CSelectTool::OnMouseMove(CDrawView* pView, UINT nFlags, const CPoint& point)
{
	if (pView->GetCapture() != pView)
	{
		if (c_drawShape == selection && pView->m_selection.GetCount() == 1)
		{
			CDrawObj* pObj = pView->m_selection.GetHead();
			CPoint local = point;
			pView->ClientToDoc(local);
			int nHandle = pObj->HitTest(local, pView, TRUE);
			if (nHandle != 0)
			{
				SetCursor(pObj->GetHandleCursor(nHandle));
				return; // bypass CDrawTool
			}
		}
		if (c_drawShape == selection)
			CDrawTool::OnMouseMove(pView, nFlags, point);
		return;
	}

	if (selectMode == netSelect)
	{
		CClientDC dc(pView);
		CRect rect(c_down.x, c_down.y, c_last.x, c_last.y);
		rect.NormalizeRect();
		dc.DrawFocusRect(rect);
		rect.SetRect(c_down.x, c_down.y, point.x, point.y);
		rect.NormalizeRect();
		dc.DrawFocusRect(rect);

		CDrawTool::OnMouseMove(pView, nFlags, point);
		return;
	}

	CPoint local = point;
	pView->ClientToDoc(local);
	CPoint delta = (CPoint)(local - lastPoint);

	POSITION pos = pView->m_selection.GetHeadPosition();
	while (pos != NULL)
	{
		CDrawObj* pObj = pView->m_selection.GetNext(pos);
		CRect position = pObj->m_position;

		if (selectMode == move)
		{
			position += delta;
			pObj->MoveTo(position, pView);
		}
		else if (nDragHandle != 0)
		{
			pObj->MoveHandleTo(nDragHandle, local, pView);
		}
	}

	lastPoint = local;

	if (selectMode == size && c_drawShape == selection)
	{
		c_last = point;
		SetCursor(pView->m_selection.GetHead()->GetHandleCursor(nDragHandle));
		return; // bypass CDrawTool
	}

	c_last = point;

	if (c_drawShape == selection)
		CDrawTool::OnMouseMove(pView, nFlags, point);
}
////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////
// CZoomTool 

CZoomTool::CZoomTool(): CDrawTool(zoom)
{
}

void CZoomTool::OnLButtonDown(CDrawView* pView, UINT nFlags, const CPoint& point)
{
	ASSERT(pView);
//	pView->DoLButtonDown(nFlags,point);
}

void CZoomTool::OnLButtonDblClk(CDrawView* /*pView*/, UINT /*nFlags*/, const CPoint& /*point*/)
{
}

void CZoomTool::OnLButtonUp(CDrawView* /*pView*/, UINT /*nFlags*/, const CPoint& /*point*/)
{
///	ASSERT(pView);
///	pView->DoLButtonUp(nFlags,point);
}

void CZoomTool::OnMouseMove(CDrawView* pView, UINT nFlags, const CPoint& point)
{
	ASSERT(pView);
/*	if (pView->GetZoomMode()==QZoomView::ZoomViewZoomOut)
		SetCursor(AfxGetApp()->LoadCursor(IDC_LOUPEMINUS));
	else if(pView->GetZoomMode()==QZoomView::ZoomViewZoomIn)
		SetCursor(AfxGetApp()->LoadCursor(IDC_LOUPEPLUS));
	else if(pView->GetZoomMode()==QZoomView::ZoomViewDrag)
		SetCursor(AfxGetApp()->LoadCursor(IDC_GRIPOPEN));*/

    selectTool.OnMouseMove(pView, nFlags, point);
}

void CZoomTool::OnMouseWheel(CDrawView* pView, UINT nFlags, short zDelta, CPoint& point)
{
	ASSERT(pView);
	pView->DoMouseWheel(nFlags, zDelta, point);
}

// CRectTool (does rectangles, round-rectangles, and ellipses)

CRectTool::CRectTool(DrawShape drawShape)
	: CDrawTool(drawShape)
{
}

void CRectTool::OnLButtonDown(CDrawView* pView, UINT nFlags, const CPoint& point)
{
	CDrawTool::OnLButtonDown(pView, nFlags, point);

	CPoint local = point;
	pView->ClientToDoc(local);

	pObj = new CDrawRect(CRect(local, CSize(0, 0)));
	switch (m_drawShape)
	{
	default:
		ASSERT(FALSE); // unsuported shape!

	case rect:
		pObj->m_nShape = CDrawRect::rectangle;
		break;

	case rectNoFill:
		pObj->m_bNoFill = TRUE;
		pObj->m_nShape = CDrawRect::rectangle;
		break;

	case roundRect:
		pObj->m_nShape = CDrawRect::roundRectangle;
		break;

	case roundRectNoFill:
		pObj->m_bNoFill = TRUE;
		pObj->m_nShape = CDrawRect::roundRectangle;
		break;

	case ellipse:
		pObj->m_nShape = CDrawRect::ellipse;
		break;

	case ellipseNoFill:
		pObj->m_bNoFill = TRUE;
		pObj->m_nShape = CDrawRect::ellipse;
		break;

	case line:
		pObj->m_nShape = CDrawRect::line;
		break;

	case beeline:
		pObj->m_nShape = CDrawRect::beeline;
		break;

	case arrow:
		pObj->m_nShape = CDrawRect::arrow;
		break;
		
	case pie:
		pObj->m_nShape = CDrawRect::pie;
		break;

	case pie45:
		pObj->m_nShape = CDrawRect::pie45;
		break;
	case group:
		pObj->m_nShape = CDrawRect::group;
		break;

	case warning:
		pObj->m_nShape = CDrawRect::warning;
		break;

	case qie:
		pObj->m_nShape = CDrawRect::qie;
		break;


	}
	pView->GetDocument()->Add(pObj);
//	pView->Select(pObj);

	selectMode = size;
	nDragHandle = 1;
	lastPoint = local;
}

void CRectTool::OnLButtonDblClk(CDrawView* pView, UINT nFlags, const CPoint& point)
{
	CDrawTool::OnLButtonDblClk(pView, nFlags, point);
}

void CRectTool::OnLButtonUp(CDrawView* pView, UINT nFlags, const CPoint& point)
{
	if (point == c_down)
	{
		// Don't create empty objects...
		CDrawObj *pObj = pView->m_selection.GetTail();
		pView->GetDocument()->Remove(pObj);
		pObj->Remove();
		selectTool.OnLButtonDown(pView, nFlags, point); // try a select!
	}
	selectTool.OnLButtonUp(pView, nFlags, point);
}

void CRectTool::OnMouseMove(CDrawView* pView, UINT nFlags, const CPoint& point)
{
	SetCursor(AfxGetApp()->LoadStandardCursor(IDC_CROSS));
	selectTool.OnMouseMove(pView, nFlags, point);
}

////////////////////////////////////////////////////////////////////////////
// CPolyTool

CPolyTool::CPolyTool(DrawShape drawShape)
	: CDrawTool(drawShape)
{
	m_pDrawObj = NULL;
}

void CPolyTool::OnLButtonDown(CDrawView* pView, UINT nFlags, const CPoint& point)
{
	CDrawTool::OnLButtonDown(pView, nFlags, point);

	CPoint local = point;
	pView->ClientToDoc(local);

	if (m_pDrawObj == NULL)
	{
		pView->SetCapture();

		m_pDrawObj = new CDrawPoly(CRect(local, CSize(0, 0)));
		

	
		switch(m_drawShape)
		{
		case poly:
			m_pDrawObj->m_bNoFill = FALSE;
			m_pDrawObj->m_nShape = CDrawPoly::poly;
			break;
		case polyNoFill:
			m_pDrawObj->m_bNoFill = TRUE;
			m_pDrawObj->m_nShape = CDrawPoly::poly;
			break;
		case curve:
			m_pDrawObj->m_nShape = CDrawPoly::curve;
			break;
		case conduit:
			m_pDrawObj->m_nShape = CDrawPoly::conduit;
			break;
		}

		pView->GetDocument()->Add(m_pDrawObj);
//		pView->Select(m_pDrawObj);
//		m_pDrawObj->AddPoint(local, pView);

	}
	else if (local == m_pDrawObj->m_points[0])
	{
		// Stop when the first point is repeated...
		ReleaseCapture();
		m_pDrawObj->m_nPoints -= 1;
		if (m_pDrawObj->m_nPoints < 2)
		{
			m_pDrawObj->Remove();
		}
		else
		{
			pView->InvalObj(m_pDrawObj);
		}
		m_pDrawObj = NULL;
		c_drawShape = selection;
		return;
	}

	local.x += 1; // adjacent points can't be the same!
//	m_pDrawObj->AddPoint(local, pView);
	pView->m_bIsDraw = TRUE;

	selectMode = size;
	nDragHandle = m_pDrawObj->GetHandleCount();
	lastPoint = local;

}

void CPolyTool::OnLButtonUp(CDrawView* /*pView*/, UINT /*nFlags*/, const CPoint& /*point*/)
{
	// Don't release capture yet!
}

void CPolyTool::OnMouseMove(CDrawView* pView, UINT nFlags, const CPoint& point)
{
	if (m_pDrawObj != NULL && (nFlags & MK_LBUTTON) != 0)
	{
		CPoint local = point;
		pView->ClientToDoc(local);
//		m_pDrawObj->AddPoint(local);
		nDragHandle = m_pDrawObj->GetHandleCount();
		lastPoint = local;
		c_last = point;
		SetCursor(AfxGetApp()->LoadCursor(IDC_PENCIL));
	}
	else
	{
		SetCursor(AfxGetApp()->LoadStandardCursor(IDC_CROSS));
		selectTool.OnMouseMove(pView, nFlags, point);
	}

}

void CPolyTool::OnLButtonDblClk(CDrawView* pView, UINT , const CPoint& )
{

	ReleaseCapture();

	int nPoints = m_pDrawObj->m_nPoints;
	if (nPoints > 2 &&
		(m_pDrawObj->m_points[nPoints - 1] == m_pDrawObj->m_points[nPoints - 2] ||
		m_pDrawObj->m_points[nPoints - 1].x - 1 == m_pDrawObj->m_points[nPoints - 2].x &&
		m_pDrawObj->m_points[nPoints - 1].y == m_pDrawObj->m_points[nPoints - 2].y))

	{
		// Nuke the last point if it's the same as the next to last...
		m_pDrawObj->m_nPoints -= 1;
		pView->InvalObj(m_pDrawObj);
	}

	m_pDrawObj = NULL;
	c_drawShape = selection;
	pView->m_bIsDraw = FALSE;
}

void CPolyTool::OnCancel()
{
	CDrawTool::OnCancel();
//	pView->m_bIsDraw = FALSE;
	m_pDrawObj = NULL;
}

////////////////////////////////////////////////////////////////////////////////////////
CCurveTool::CCurveTool()
	: CDrawTool(curve)
{
	m_pDrawObj = NULL;
}

void CCurveTool::OnLButtonDown(CDrawView* pView, UINT nFlags, const CPoint& point)
{
	CDrawTool::OnLButtonDown(pView, nFlags, point);

	CPoint local = point;
	pView->ClientToDoc(local);

	if (m_pDrawObj == NULL)
	{
		pView->SetCapture();

		m_pDrawObj = new CDrawPoly(CRect(local, CSize(0, 0)));
		m_pDrawObj->m_nShape = CDrawPoly::curve;

		pView->GetDocument()->Add(m_pDrawObj);
//		pView->Select(m_pDrawObj);
//		m_pDrawObj->AddPoint(local, pView);
	}
	else if (local == m_pDrawObj->m_points[0])
	{
		// Stop when the first point is repeated...
		ReleaseCapture();
		m_pDrawObj->m_nPoints -= 1;
		if (m_pDrawObj->m_nPoints < 2)
		{
			ASSERT(0);
			m_pDrawObj->Remove();
		}
		else
		{
			pView->InvalObj(m_pDrawObj);
		}
		m_pDrawObj = NULL;
		c_drawShape = selection;
		return;
	}

	local.x += 1; // adjacent points can't be the same!
//	m_pDrawObj->AddPoint(local, pView);

	selectMode = size;
	nDragHandle = m_pDrawObj->GetHandleCount();
	lastPoint = local;
}

void CCurveTool::OnLButtonUp(CDrawView* /*pView*/, UINT /*nFlags*/, const CPoint& /*point*/)
{
	// Don't release capture yet!
}

void CCurveTool::OnMouseMove(CDrawView* pView, UINT nFlags, const CPoint& point)
{
	if (m_pDrawObj != NULL && (nFlags & MK_LBUTTON) != 0)
	{
		CPoint local = point;
		pView->ClientToDoc(local);
//		m_pDrawObj->AddPoint(local);
		nDragHandle = m_pDrawObj->GetHandleCount();
		lastPoint = local;
		c_last = point;
		SetCursor(AfxGetApp()->LoadCursor(IDC_PENCIL));
	}
	else
	{
		SetCursor(AfxGetApp()->LoadStandardCursor(IDC_CROSS));
		selectTool.OnMouseMove(pView, nFlags, point);
	}
}

void CCurveTool::OnLButtonDblClk(CDrawView* pView, UINT , const CPoint& )
{
	ReleaseCapture();

	int nPoints = m_pDrawObj->m_nPoints;
	if (nPoints > 2 &&
		(m_pDrawObj->m_points[nPoints - 1] == m_pDrawObj->m_points[nPoints - 2] ||
		m_pDrawObj->m_points[nPoints - 1].x - 1 == m_pDrawObj->m_points[nPoints - 2].x &&
		m_pDrawObj->m_points[nPoints - 1].y == m_pDrawObj->m_points[nPoints - 2].y))

	{
		// Nuke the last point if it's the same as the next to last...
		m_pDrawObj->m_nPoints -= 1;
		pView->InvalObj(m_pDrawObj);
	}

	m_pDrawObj = NULL;
	c_drawShape = selection;
//	pView->lastAction->Finish();

}

void CCurveTool::OnCancel()
{
	CDrawTool::OnCancel();

	m_pDrawObj = NULL;
}

////////////////////////////////////////////////////////////////////////////
// CRectTool (does rectangles, round-rectangles, and ellipses)

CButtonTool::CButtonTool(DrawShape drawShape)
	: CDrawTool(drawShape)
{
}

void CButtonTool::OnLButtonDown(CDrawView* pView, UINT nFlags, const CPoint& point)
{
	CDrawTool::OnLButtonDown(pView, nFlags, point);

	CPoint local = point;
	pView->ClientToDoc(local);

	m_pDrawObj = new CDrawButton(CRect(local, CSize(0, 0)));

	switch (m_drawShape)
	{
	case button:
		m_pDrawObj->m_nShape = CDrawButton::button;
		break;
	case text:
		m_pDrawObj->m_nShape = CDrawButton::text;
		break;
	case picture:
		m_pDrawObj->m_nShape = CDrawButton::picture;
		break;
	default:
		break;
	}

	pView->GetDocument()->Add(m_pDrawObj);
//	pView->Select(m_pDrawObj);

	selectMode = size;
	nDragHandle = 1;
	lastPoint = local;
}

void CButtonTool::OnLButtonDblClk(CDrawView* pView, UINT nFlags, const CPoint& point)
{
	CDrawTool::OnLButtonDblClk(pView, nFlags, point);
}

void CButtonTool::OnLButtonUp(CDrawView* pView, UINT nFlags, const CPoint& point)
{
	if (point == c_down)
	{
		// Don't create empty objects...
		CDrawObj *pObj = pView->m_selection.GetTail();
		pView->GetDocument()->Remove(pObj);
		pObj->Remove();
		selectTool.OnLButtonDown(pView, nFlags, point); // try a select!
	}
	
	selectTool.OnLButtonUp(pView, nFlags, point);
}

void CButtonTool::OnMouseMove(CDrawView* pView, UINT nFlags, const CPoint& point)
{
	SetCursor(AfxGetApp()->LoadStandardCursor(IDC_CROSS));
///	if(m_pDrawObj)          //0415
///	{
///		CRect rect = m_pDrawObj->m_position;
//		if(rect.PtInRect(point))
//			m_pDrawObj->SetState(CDrawButton::MOVE);
///	}
	selectTool.OnMouseMove(pView, nFlags, point);
}


////////////////////////////////////////////////////////////////////////////
// CRectTool (does rectangles, round-rectangles, and ellipses)

CChartTool::CChartTool(DrawShape drawShape)
	: CDrawTool(drawShape)
{
}

void CChartTool::OnLButtonDown(CDrawView* pView, UINT nFlags, const CPoint& point)
{
	CDrawTool::OnLButtonDown(pView, nFlags, point);

	CPoint local = point;
	pView->ClientToDoc(local);

	m_pDrawObj = new CDrawChart(CRect(local, CSize(0, 0)));
	
	switch (m_drawShape)
	{
	case chart:
//		m_pDrawObj->m_IsRealTime = TRUE;
		break;
	case Hchart:
//		m_pDrawObj->m_IsRealTime = FALSE;
	default:
		break;
	}
	pView->GetDocument()->Add(m_pDrawObj);
//	pView->Select(m_pDrawObj);

	selectMode = size;
	nDragHandle = 1;
	lastPoint = local;
}

void CChartTool::OnLButtonDblClk(CDrawView* pView, UINT nFlags, const CPoint& point)
{
	CDrawTool::OnLButtonDblClk(pView, nFlags, point);
}

void CChartTool::OnLButtonUp(CDrawView* pView, UINT nFlags, const CPoint& point)
{
	if (point == c_down)
	{
		// Don't create empty objects...
		CDrawObj *pObj = pView->m_selection.GetTail();
		pView->GetDocument()->Remove(pObj);
		pObj->Remove();
		selectTool.OnLButtonDown(pView, nFlags, point); // try a select!
		m_pDrawObj = NULL;
	}
	if (m_pDrawObj!= NULL)
	{
//		m_pDrawObj->m_bReDraw = TRUE;
//		m_pDrawObj->Invalidate();
	}
	selectTool.OnLButtonUp(pView, nFlags, point);
}

void CChartTool::OnMouseMove(CDrawView* pView, UINT nFlags, const CPoint& point)
{
	SetCursor(AfxGetApp()->LoadStandardCursor(IDC_CROSS));
	selectTool.OnMouseMove(pView, nFlags, point);
}

///////////////////////////////////////////////////////////////////////////
// CRectTool (does rectangles, round-rectangles, and ellipses)

CWarnTool::CWarnTool(DrawShape drawShape)
	: CDrawTool(drawShape)
{
}

void CWarnTool::OnLButtonDown(CDrawView* pView, UINT nFlags, const CPoint& point)
{
	CDrawTool::OnLButtonDown(pView, nFlags, point);

	CPoint local = point;
	pView->ClientToDoc(local);

	m_pDrawObj = new CDrawWarn(CRect(local, CSize(0, 0)));


	pView->GetDocument()->Add(m_pDrawObj);
//	pView->Select(m_pDrawObj);

	selectMode = size;
	nDragHandle = 1;
	lastPoint = local;
}

void CWarnTool::OnLButtonDblClk(CDrawView* pView, UINT nFlags, const CPoint& point)
{
	CDrawTool::OnLButtonDblClk(pView, nFlags, point);
}

void CWarnTool::OnLButtonUp(CDrawView* pView, UINT nFlags, const CPoint& point)
{
	if (point == c_down)
	{
		// Don't create empty objects...
		CDrawObj *pObj = pView->m_selection.GetTail();
		pView->GetDocument()->Remove(pObj);
		pObj->Remove();
		selectTool.OnLButtonDown(pView, nFlags, point); // try a select!
	}
	selectTool.OnLButtonUp(pView, nFlags, point);
}

void CWarnTool::OnMouseMove(CDrawView* pView, UINT nFlags, const CPoint& point)
{
	SetCursor(AfxGetApp()->LoadStandardCursor(IDC_CROSS));
	selectTool.OnMouseMove(pView, nFlags, point);
}

////////////////////////////////////////////////////////////////////////////
// CPolyTool

CConduitTool::CConduitTool(DrawShape drawShape)
	: CDrawTool(drawShape)
{
	m_pDrawObj = NULL;
}

void CConduitTool::OnLButtonDown(CDrawView* pView, UINT nFlags, const CPoint& point)
{
	CDrawTool::OnLButtonDown(pView, nFlags, point);

	CPoint local = point;
	pView->ClientToDoc(local);

	if (m_pDrawObj == NULL)
	{
		pView->SetCapture();

		m_pDrawObj = new CDrawConduit(CRect(local, CSize(0, 0)));
		
//		m_pDrawObj->m_nShape = CDrawConduit::conduit;
		pView->GetDocument()->Add(m_pDrawObj);
//		pView->Select(m_pDrawObj);
//		m_pDrawObj->AddPoint(local, pView);

	}
	else if (local == m_pDrawObj->m_points[0])
	{
		// Stop when the first point is repeated...
		ReleaseCapture();
		m_pDrawObj->m_nPoints -= 1;
		if (m_pDrawObj->m_nPoints < 2)
		{
			m_pDrawObj->Remove();
		}
		else
		{
			pView->InvalObj(m_pDrawObj);
		}
		m_pDrawObj = NULL;
		c_drawShape = selection;
		return;
	}

	local.x += 1; // adjacent points can't be the same!
//	m_pDrawObj->AddPoint(local, pView);
	pView->m_bIsDraw = TRUE;

	selectMode = size;
	nDragHandle = m_pDrawObj->GetHandleCount();
	lastPoint = local;

}

void CConduitTool::OnLButtonUp(CDrawView* /*pView*/, UINT /*nFlags*/, const CPoint& /*point*/)
{
	// Don't release capture yet!
}

void CConduitTool::OnMouseMove(CDrawView* pView, UINT nFlags, const CPoint& point)
{
	if (m_pDrawObj != NULL && (nFlags & MK_LBUTTON) != 0)
	{
		CPoint local = point;
		pView->ClientToDoc(local);
//		m_pDrawObj->AddPoint(local);
		nDragHandle = m_pDrawObj->GetHandleCount();
		lastPoint = local;
		c_last = point;
		SetCursor(AfxGetApp()->LoadCursor(IDC_PENCIL));
	}
	else
	{
		SetCursor(AfxGetApp()->LoadStandardCursor(IDC_CROSS));
		selectTool.OnMouseMove(pView, nFlags, point);
	}

}

void CConduitTool::OnLButtonDblClk(CDrawView* pView, UINT , const CPoint& )
{

	ReleaseCapture();

	int nPoints = m_pDrawObj->m_nPoints;
	if (nPoints > 2 &&
		(m_pDrawObj->m_points[nPoints - 1] == m_pDrawObj->m_points[nPoints - 2] ||
		m_pDrawObj->m_points[nPoints - 1].x - 1 == m_pDrawObj->m_points[nPoints - 2].x &&
		m_pDrawObj->m_points[nPoints - 1].y == m_pDrawObj->m_points[nPoints - 2].y))

	{
		// Nuke the last point if it's the same as the next to last...
		m_pDrawObj->m_nPoints -= 1;
		pView->InvalObj(m_pDrawObj);
	}

	m_pDrawObj = NULL;
	c_drawShape = selection;
	pView->m_bIsDraw = FALSE;
}

void CConduitTool::OnCancel()
{
	CDrawTool::OnCancel();
//	pView->m_bIsDraw = FALSE;
	m_pDrawObj = NULL;
}

///////////////////////////////////////////////////////////////////////////////////////
CCarTool::CCarTool(DrawShape drawShape)
	: CDrawTool(drawShape)
{
}

void CCarTool::OnLButtonDown(CDrawView* pView, UINT nFlags, const CPoint& point)
{
	CDrawTool::OnLButtonDown(pView, nFlags, point);

	CPoint local = point;
	pView->ClientToDoc(local);

	pCar = new CDrawCar(CRect(local, CSize(0, 0)));

	pView->GetDocument()->Add(pCar);
//	pView->Select(pCar);

	selectMode = size;
	nDragHandle = 1;
	lastPoint = local;
}

void CCarTool::OnLButtonDblClk(CDrawView* pView, UINT nFlags, const CPoint& point)
{
	CDrawTool::OnLButtonDblClk(pView, nFlags, point);
}

void CCarTool::OnLButtonUp(CDrawView* pView, UINT nFlags, const CPoint& point)
{
	if (point == c_down)
	{
		// Don't create empty objects...
		CDrawObj *pObj = pView->m_selection.GetTail();
		pView->GetDocument()->Remove(pObj);
		pObj->Remove();
		selectTool.OnLButtonDown(pView, nFlags, point); // try a select!
	}
	selectTool.OnLButtonUp(pView, nFlags, point);
}

void CCarTool::OnMouseMove(CDrawView* pView, UINT nFlags, const CPoint& point)
{
	SetCursor(AfxGetApp()->LoadStandardCursor(IDC_CROSS));
	selectTool.OnMouseMove(pView, nFlags, point);
}

///////////////////////////////////////////////////////////////////////////////////////
CRotaryTool::CRotaryTool(DrawShape drawShape)
	: CDrawTool(drawShape)
{
}

void CRotaryTool::OnLButtonDown(CDrawView* pView, UINT nFlags, const CPoint& point)
{
	CDrawTool::OnLButtonDown(pView, nFlags, point);

	CPoint local = point;
	pView->ClientToDoc(local);

	pRotary = new CDrawRotary(CRect(local, CSize(0, 0)));

	pView->GetDocument()->Add(pRotary);
//	pView->Select(pRotary);

	selectMode = size;
	nDragHandle = 1;
	lastPoint = local;
}

void CRotaryTool::OnLButtonDblClk(CDrawView* pView, UINT nFlags, const CPoint& point)
{
	CDrawTool::OnLButtonDblClk(pView, nFlags, point);
}

void CRotaryTool::OnLButtonUp(CDrawView* pView, UINT nFlags, const CPoint& point)
{
	if (point == c_down)
	{
		// Don't create empty objects...
		CDrawObj *pObj = pView->m_selection.GetTail();
		pView->GetDocument()->Remove(pObj);
		pObj->Remove();
		selectTool.OnLButtonDown(pView, nFlags, point); // try a select!
	}
	selectTool.OnLButtonUp(pView, nFlags, point);
}

void CRotaryTool::OnMouseMove(CDrawView* pView, UINT nFlags, const CPoint& point)
{
	SetCursor(AfxGetApp()->LoadStandardCursor(IDC_CROSS));
	selectTool.OnMouseMove(pView, nFlags, point);
}

