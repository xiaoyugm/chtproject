/***********************************************************************************
说明:绘制曲线，多边形的类

***********************************************************************************/
#include "stdafx.h"
#include "Draw.h"
#include "drawpoly.h"
#include "drawdoc.h"
#include "drawview.h"
#include "drawobj.h"
#include <mmsystem.h>

///#include "cntritem.h"

extern "C"
void CALLBACK PolyTimeProc(UINT id,UINT msg,DWORD dwUser,DWORD dw1,DWORD dw2)
{
	CDrawPoly *	DrawPoly = (CDrawPoly *)dwUser;

//	DrawPoly->m_nRoute+=30;
//	DrawPoly->ActionActive();
}
////////////////////////////////////////////////////////////////////////////
// CDrawPoly

IMPLEMENT_SERIAL(CDrawPoly, CDrawObj, 0)

CDrawPoly::CDrawPoly()
{
	m_points = NULL;
	m_nPoints = 0;
	m_nAllocPoints = 0;
}

CDrawPoly::CDrawPoly(const CRect& position)
	: CDrawObj(position)
{
	m_points = NULL;
	m_nPoints = 0;
	m_nAllocPoints = 0;
	m_bIsActive = FALSE;
	m_nRoutePoly = 0;
}

CDrawPoly::~CDrawPoly()
{
	if (m_points != NULL)
		delete[] m_points;
	if(nTimerID)
		timeKillEvent(nTimerID);
}

void CDrawPoly::Serialize( CArchive& ar )
{
	int i;
	CDrawObj::Serialize( ar );
	if( ar.IsStoring() )
	{
		ar << (WORD) m_nPoints;
		ar << (WORD) m_nAllocPoints;
		for (i = 0;i< m_nPoints; i++)
			ar << m_points[i];
		ar << (WORD)m_nShape;
		ar << (WORD)m_bIsActive;
		ar << m_nRoutePoly;

	}
	else
	{
		WORD wTemp;
		ar >> wTemp; m_nPoints = wTemp;
		ar >> wTemp; m_nAllocPoints = wTemp;
		m_points = new CPoint[m_nAllocPoints];
		for (i = 0;i < m_nPoints; i++)
			ar >> m_points[i];
		ar >> wTemp;		m_nShape = (Shape)wTemp;
		ar >> wTemp;		m_bIsActive = (BOOL)wTemp;
		ar >> m_nRoutePoly;
	}
}

void CDrawPoly::Draw(CDC* pDC)
{
	ASSERT_VALID(this);
	Graphics graphics (pDC->m_hDC);

	CRect rect = m_position;
	Rect GdiRect (rect.TopLeft().x,rect.TopLeft().y,rect.Size().cx,rect.Size().cy); 
	Normallize(GdiRect); 

		DrawFill(pDC,GdiRect);

	if(!m_bIsActive)
		m_bIsActive = StartAction();
	graphics.ReleaseHDC(pDC->m_hDC);
}

void CDrawPoly::DrawFill(CDC *pDC,Rect rc)
{
	CRect rect = m_position;
	Rect GdiRect = rc;

	Color  clrLineColor,clrFillColor;
	clrLineColor.SetFromCOLORREF(m_clrLineColor);
	clrFillColor.SetFromCOLORREF(m_clrFillColor );

	Graphics graphics(pDC->m_hDC);

	if(m_nRoutePoly != 0)
	{
		CRect rcRoute = m_position;
		rcRoute.NormalizeRect();
		PointF ptF;
		ptF.X = rcRoute.CenterPoint().x;
		ptF.Y = rcRoute.CenterPoint().y;
		Matrix transformMatrix;
		transformMatrix.RotateAt(m_nRoutePoly,ptF);
		CString lee;
		lee.Format("%d,%d",ptF.X,ptF.Y);

		graphics.SetTransform(&transformMatrix);
	}

	//solid brush
	SolidBrush solidBrush(clrFillColor); 
	//pen
	Pen pen(clrLineColor,m_nLineSize);
	pen.SetDashStyle(m_LineStyle);

	PointF *points = new PointF[m_nPoints+1];

	for (int i=0;i<m_nPoints;i++)
	{
		points[i].X = m_points[i].x;
		points[i].Y = m_points[i].y;
	}

	points[0].X++;
	points[0].Y++;

	switch(m_nShape)
	{
	case poly:
		{
//			points[i].X = m_points[0].x;
//			points[i].Y = m_points[0].y;
			if(m_bNoFill)
			{
				graphics.DrawPolygon(&pen,points,m_nPoints);
			}
			else
			{
				graphics.FillPolygon(&solidBrush,points,m_nPoints,FillModeWinding);
				graphics.DrawPolygon(&pen,points,m_nPoints);
			}
		}
		break;
	case curve:
		{

			graphics.DrawCurve(&pen,points,m_nPoints);

		}
		break;
	case conduit:
		{
			m_nLineSize = 10;
			GraphicsPath Linepath;
			Linepath.StartFigure();
			for (int i=0;i<m_nPoints-1;i++)
			{
				Linepath.AddLine(points[i],points[i+1]);
			}
			pen.SetLineJoin(LineJoinBevel);
			graphics.DrawPath(&pen, &Linepath);
		}
		break;
	}
	delete[] points;
	graphics.ReleaseHDC(pDC->m_hDC);
}

// position must be in logical coordinates
void CDrawPoly::MoveTo(const CRect& position, CDrawView* pView)
{
	ASSERT_VALID(this);
	if (position == m_position)
		return;

	if (pView == NULL)
		Invalidate();
	else
		pView->InvalRouteObj(this);

	for (int i = 0; i < m_nPoints; i += 1)
	{
		m_points[i].x += position.left - m_position.left;
		m_points[i].y += position.top - m_position.top;
	}

	m_position = position;

	if (pView == NULL)
		Invalidate();
	else
		pView->InvalRouteObj(this);
	m_pDocument->SetModifiedFlag();
}

void CDrawPoly::Invalidate()
{
	ASSERT_VALID(this);
	if(m_nRoutePoly == 0)
		m_pDocument->UpdateAllViews(NULL, HINT_UPDATE_DRAWOBJ, this);
	else
		m_pDocument->UpdateAllViews(NULL, HINT_UPDATE_ROUTE, this);
}

int CDrawPoly::GetHandleCount()
{
	if(m_bIsGroup)
		return 0;
	return m_nPoints;
}

CPoint CDrawPoly::GetHandle(int nHandle)
{
	ASSERT_VALID(this);

	ASSERT(nHandle >= 1 && nHandle <= m_nPoints);
	return m_points[nHandle - 1];
}

HCURSOR CDrawPoly::GetHandleCursor(int )
{
	return AfxGetApp()->LoadStandardCursor(IDC_ARROW);
}

// point is in logical coordinates
void CDrawPoly::MoveHandleTo(int nHandle, CPoint point, CDrawView* pView)
{
	ASSERT_VALID(this);
	ASSERT(nHandle >= 1 && nHandle <= m_nPoints);
	if (m_points[nHandle - 1] == point)
		return;

	m_points[nHandle - 1] = point;
	RecalcBounds(pView);

	if (pView == NULL)
		Invalidate();
	else
		pView->InvalObj(this);
	m_pDocument->SetModifiedFlag();
}

// rect must be in logical coordinates
BOOL CDrawPoly::Intersects(const CRect& rect)
{
	ASSERT_VALID(this);
	switch(m_nShape)
	{
	case poly:	
		{
			CRgn rgn;
			rgn.CreatePolygonRgn(m_points, m_nPoints, ALTERNATE);
			return rgn.RectInRegion(rect);
		}
		break;
	case curve:
		{
			CRgn rgn;
			rgn.CreatePolygonRgn(m_points, m_nPoints, ALTERNATE);
			return rgn.RectInRegion(rect);
		}
		break;
	case conduit:
		{
			CRgn rgn;
			rgn.CreatePolygonRgn(m_points, m_nPoints, ALTERNATE);
			return rgn.RectInRegion(rect);
		}
		break;
	}
	return FALSE;
}

CDrawObj* CDrawPoly::Clone(CDrawDoc* pDoc)
{
	ASSERT_VALID(this);

	CDrawPoly* pClone = new CDrawPoly(m_position);
	pClone->m_LineStyle			= m_LineStyle;				//线条风格
	pClone->m_clrFillColor		= m_clrFillColor;			//填充颜色
	pClone->m_clrLineColor		= m_clrLineColor;			//线条颜色
	pClone->m_bNoFill			= m_bNoFill;				//是否填充
	pClone->m_nLineSize			= m_nLineSize;				//线条尺寸
///	pClone->m_clrBackColor		= m_clrBackColor;			//结束颜色
	pClone->m_nShape			= m_nShape;

	pClone->m_points = new CPoint[m_nAllocPoints];
	memcpy(pClone->m_points, m_points, sizeof(CPoint) * m_nPoints);
	pClone->m_nAllocPoints = m_nAllocPoints;
	pClone->m_nPoints = m_nPoints;

	ASSERT_VALID(pClone);

	if (pDoc != NULL)
		pDoc->Add(pClone);

	ASSERT_VALID(pClone);
	return pClone;
}

// point is in logical coordinates
void CDrawPoly::AddPoint(const CPoint& point, CDrawView* pView)
{
	ASSERT_VALID(this);
	if (m_nPoints == m_nAllocPoints)
	{
		CPoint* newPoints = new CPoint[m_nAllocPoints + 10];
		if (m_points != NULL)
		{
			memcpy(newPoints, m_points, sizeof(CPoint) * m_nAllocPoints);
			delete[] m_points;
		}
		m_points = newPoints;
		m_nAllocPoints += 10;
	}


	if (m_nPoints == 0 || m_points[m_nPoints - 1] != point)
	{
		m_points[m_nPoints++] = point;
		if (!RecalcBounds(pView))
		{
			if (pView == NULL)
				Invalidate();
			else
				pView->InvalObj(this);
		}
		m_pDocument->SetModifiedFlag();
	}

}

BOOL CDrawPoly::RecalcBounds(CDrawView* pView)
{
	ASSERT_VALID(this);

	if (m_nPoints == 0)
		return FALSE;

	CRect bounds(m_points[0], CSize(0, 0));

	for (int i = 1; i < m_nPoints; ++i)
	{
		if (m_points[i].x < bounds.left)
			bounds.left = m_points[i].x;
		if (m_points[i].x > bounds.right)
			bounds.right = m_points[i].x;
		if (m_points[i].y < bounds.top)
			bounds.top = m_points[i].y;
		if (m_points[i].y > bounds.bottom)
			bounds.bottom = m_points[i].y;
	}

	if (bounds == m_position)
		return FALSE;

	if (pView == NULL)
		Invalidate();
	else
		pView->InvalObj(this);

	m_position = bounds;

	if (pView == NULL)
		Invalidate();
	else
		pView->InvalObj(this);

	return TRUE;
}

BOOL CDrawPoly::StartAction()
{
	nTimerID = timeSetEvent(200,1000,PolyTimeProc,(DWORD)this,false ? TIME_ONESHOT : TIME_PERIODIC);
	if (nTimerID)
	{
		return TRUE;
	}
	return FALSE;
}