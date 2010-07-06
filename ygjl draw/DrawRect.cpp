/*****************************************************************************
绘制RECT图形的类
说明：包括矩形，圆角矩形，圆
*****************************************************************************/
#include "stdafx.h"
#include "Draw.h"

#include "drawdoc.h"
#include "drawview.h"
#include "drawobj.h"
#include "drawrect.h"
#include <mmsystem.h>
///#include "cntritem.h"
#include <math.h>

////////////////////////////////////////////////////////////////////////////
// CDrawRect

IMPLEMENT_SERIAL(CDrawRect, CDrawObj, 0)

CDrawRect::CDrawRect()
{
	
}

CDrawRect::CDrawRect(const CRect& position)
	: CDrawObj(position)
{
	ASSERT_VALID(this);

	m_nShape		= rectangle;
	m_roundness.x	= 16;
	m_roundness.y	= 16;
	bplus			= TRUE;
	bStart			= FALSE;
	m_nstartAngle	= 30;
	m_nsweepAngle	= -180;
	m_npie			= 0;
	m_npie45		= 45;
	m_nRoute		= 0; 
}

CDrawRect::~CDrawRect()
{

}

void CDrawRect::Serialize(CArchive& ar)
{
	ASSERT_VALID(this);

	CDrawObj::Serialize(ar);
	if (ar.IsStoring())
	{
		ar << (WORD) m_nShape;
		ar << m_roundness;
		ar << m_npie;
		ar << m_npie45;
		ar << m_nstartAngle;
		ar << m_nsweepAngle;
		ar << m_npie;
		ar << m_npie45;
		ar << m_nRoute;
		ar << (WORD)bplus;
///		ar << m_nDrawTrans;

	}
	else
	{
		WORD wTemp;
		ar >> wTemp; m_nShape = (Shape)wTemp;
		ar >> m_roundness;
		ar >> m_npie;
		ar >> m_npie45;
		ar >> m_nstartAngle;
		ar >> m_nsweepAngle;
		ar >> m_npie;
		ar >> m_npie45;
		ar >> m_nRoute;
		ar >> wTemp;		bplus = (BOOL)wTemp;
///		ar >> m_nDrawTrans;

	}
}

void CDrawRect::Remove()
{
	delete this;
}

void CDrawRect::Draw(CDC* pDC)
{
	ASSERT_VALID(this);

	CRect rect = m_position;
	rect.NormalizeRect();
	Rect GdiRect (rect.TopLeft().x,rect.TopLeft().y,rect.Size().cx,rect.Size().cy); 
	
	Normallize(GdiRect);				//坐标转换

		DrawFill(pDC,GdiRect);
}

//画标准填充
void CDrawRect::DrawFill(CDC *pDC,Rect rc)
{
	CRect rect = m_position;
	CRect pierect = rect;
	pierect.NormalizeRect();
	pierect.bottom += pierect.Height();

	Rect GdiPieRect (pierect.TopLeft().x,pierect.TopLeft().y,pierect.Size().cx,pierect.Size().cy); 
	
	Rect GdiRect = rc;

	Color  clrFillColor,clrLineColor;
	clrLineColor.SetFromCOLORREF(m_clrLineColor );
	clrFillColor.SetFromCOLORREF(m_clrFillColor );

	Graphics graphics(pDC->m_hDC);

	if(m_nRoute != 0)
	{
		CRect rcRoute = m_position;
		rcRoute.NormalizeRect();
		PointF ptF;
		ptF.X = rcRoute.CenterPoint().x;
		ptF.Y = rcRoute.CenterPoint().y;
		Matrix transformMatrix;
		transformMatrix.RotateAt(m_nRoute,ptF);
		CString lee;
		lee.Format("%d,%d",ptF.X,ptF.Y);

		graphics.SetTransform(&transformMatrix);

	}

	//solid brush
	SolidBrush solidBrush(clrFillColor); 
	//pen
	Pen pen(clrLineColor,m_nLineSize);
	pen.SetDashStyle(m_LineStyle);

	switch (m_nShape)
	{
	case rectangle:					//矩形
		if(m_bNoFill)
		{
			graphics.DrawRectangle(&pen,GdiRect);
		}
		else
		{
			graphics.FillRectangle(&solidBrush,GdiRect);
			graphics.DrawRectangle(&pen,GdiRect);
		}
		break;
	case roundRectangle:			//园角矩形
		{
			int X1 = GdiRect.X;
			int X2 = GdiRect.X+GdiRect.Width;
			int Y1 = GdiRect.Y;
			int Y2 = GdiRect.Y+GdiRect.Height;
			int W =  m_roundness.x/2;
			int H =  m_roundness.y/2;
			
			if (2*W >= GdiRect.Width)
				W = GdiRect.Width/2;
			
			if (2*H >= GdiRect.Height)
				H = GdiRect.Height/2;
			
			GraphicsPath roundRectPath;
			roundRectPath.AddArc(X1,Y1,2*W,2*H,180,90);
			roundRectPath.AddArc(X2-2*W,Y1,2*W,2*H,270,90);
			roundRectPath.AddArc(X2-2*W,Y2-2*H,2*W,2*H,0,90);
			roundRectPath.AddArc(X1,Y2-2*H,2*W,2*H,90,90);
			roundRectPath.CloseFigure();
			if(m_bNoFill)
			{
				graphics.DrawPath(&pen,&roundRectPath);
			}
			else
			{
				graphics.FillPath(&solidBrush,&roundRectPath);
				graphics.DrawPath(&pen,&roundRectPath);
			}
		}
		break;
	case ellipse:						//圆形
		if(m_bNoFill)
		{
			graphics.DrawEllipse(&pen,GdiRect);
		}
		else
		{
			graphics.FillEllipse(&solidBrush,GdiRect);
			graphics.DrawEllipse(&pen,GdiRect);
		}
		break;
	case line:							//线
	case arrow:
		{
			if (rect.top > rect.bottom)
			{
				rect.top -= m_nLineSize / 2;
				rect.bottom += (m_nLineSize + 1) / 2;
			}
			else
			{
				rect.top += (m_nLineSize + 1) / 2;
				rect.bottom -= m_nLineSize / 2;
			}
			
			if (rect.left > rect.right)
			{
				rect.left -= m_nLineSize / 2;
				rect.right += (m_nLineSize + 1) / 2;
			}
			else
			{
				rect.left += (m_nLineSize + 1) / 2;
				rect.right -= m_nLineSize / 2;
			}

			graphics.DrawLine(&pen,rect.TopLeft().x, rect.TopLeft().y,rect.BottomRight().x,rect.BottomRight().y);
		}
		break;

	case beeline:						//直线
		{
			int x = abs(rect.left - rect.right);
			int y = abs(rect.top - rect.bottom);
			if(x > y)
			{
				m_position.bottom = rect.top + m_nLineSize;
				graphics.DrawLine(&pen,rect.TopLeft().x, rect.TopLeft().y,rect.BottomRight().x,rect.TopLeft().y);
	
			}
			else
			{
				m_position.right = m_position.left + m_nLineSize;
				graphics.DrawLine(&pen,rect.TopLeft().x, rect.TopLeft().y,rect.TopLeft().x,rect.BottomRight().y );

			}
		}
		break;
	case pie:							//饼
		{
			REAL startAngle = m_npie;
			REAL sweepAngle = -180.0f;
			
			//		Rect PieRect (rect.TopLeft().x,rect.TopLeft().y,rect.Size().cx*2,rect.Size().cy); 
			if(m_bNoFill)
			{
//				graphics.DrawPie(&pen, GdiPieRect, startAngle, sweepAngle);
				graphics.DrawPie(&pen, GdiRect, startAngle, sweepAngle);
			}
			else
			{
//				graphics.FillPie(&solidBrush, GdiPieRect, startAngle, sweepAngle);
//				graphics.DrawPie(&pen, GdiPieRect, startAngle, sweepAngle);
				graphics.FillPie(&solidBrush, GdiRect, startAngle, sweepAngle);
				graphics.DrawPie(&pen, GdiRect, startAngle, sweepAngle);
			}
		}
		break;
	case pie45:							//45度饼
		{
			REAL startAngle = m_npie45;
			REAL sweepAngle = -180.0f;
			
			//		Rect PieRect (rect.TopLeft().x,rect.TopLeft().y,rect.Size().cx*2,rect.Size().cy); 
			if(m_bNoFill)
			{
				graphics.DrawPie(&pen, GdiRect, startAngle, sweepAngle);
			}
			else
			{
				graphics.FillPie(&solidBrush, GdiRect, startAngle, sweepAngle);
				graphics.DrawPie(&pen, GdiRect, startAngle, sweepAngle);
			}
		}
		break;							//切
	case qie:
		{
			//		Rect PieRect (rect.TopLeft().x,rect.TopLeft().y,rect.Size().cx*2,rect.Size().cy); 
			if(m_bNoFill)
			{
				graphics.DrawPie(&pen, GdiRect, m_nstartAngle, m_nsweepAngle);
			}
			else
			{
				graphics.FillPie(&solidBrush, GdiRect, m_nstartAngle, m_nsweepAngle);
				graphics.DrawPie(&pen, GdiRect, m_nstartAngle, m_nsweepAngle);
			}
		}
	case group:
		break;
	case warning:
		{

		}
	}
	graphics.ReleaseHDC(pDC->m_hDC);
}

int CDrawRect::GetHandleCount()
{
	ASSERT_VALID(this);
	if(m_bIsGroup)
		return 0;
	if (m_nShape == line || m_nShape == arrow || m_nShape == beeline)
		return 2;
	if (m_nShape == roundRectangle)
		return 9;
	if (m_nShape == qie)
		return 10;

	return CDrawObj::GetHandleCount();
}

// returns center of handle in logical coordinates
CPoint CDrawRect::GetHandle(int nHandle)
{
	ASSERT_VALID(this);

	if ((m_nShape == line || m_nShape == arrow ||  m_nShape == beeline) && nHandle == 2)
		nHandle = 5;
	else 
	{
		if (m_nShape == roundRectangle && nHandle == 9)			//园角举行
		{
			CRect rect = m_position;
			rect.NormalizeRect();
			CPoint point = rect.BottomRight();				
			point.x -= m_roundness.x / 2;
			point.y -= m_roundness.y / 2;
			return point;
		}
		if (m_nShape == qie && nHandle > 8)					//切
		{
			CRect rect = m_position;
			rect.NormalizeRect();
			CPoint point = rect.CenterPoint();
			if (nHandle == 9)
			{
//				int i = min(rect.Width()/2, rect.Height()/2);
//				point.x -= (i-10);
//				point.y -= (i-10)*sin(m_nstartAngle);
			}
			if (nHandle == 10)
			{
				point.x += 20;
				point.y += abs(20 * sin(m_nstartAngle));

			}
			return point;
		}
	}

	return CDrawObj::GetHandle(nHandle);
}

HCURSOR CDrawRect::GetHandleCursor(int nHandle)
{
	ASSERT_VALID(this);

	if ((m_nShape == line || m_nShape == arrow ||  m_nShape == beeline)&& nHandle == 2)
		nHandle = 5;
	else 
	{
		if (m_nShape == roundRectangle && nHandle == 9)
			return AfxGetApp()->LoadStandardCursor(IDC_SIZEALL);
		if (m_nShape == qie && nHandle > 8)					//切
			return AfxGetApp()->LoadStandardCursor(IDC_SIZEALL);
	}
	return CDrawObj::GetHandleCursor(nHandle);
}

// point is in logical coordinates
void CDrawRect::MoveHandleTo(int nHandle, CPoint point, CDrawView* pView)
{
	ASSERT_VALID(this);

	if ((m_nShape == line || m_nShape == arrow ||  m_nShape == beeline) && nHandle == 2)
		nHandle = 5;
	else 
	{
/*		if (m_nShape == roundRectangle && nHandle == 9)
		{
			CRect rect = m_position;
			rect.NormalizeRect();
			if (point.x > rect.right - 1)
				point.x = rect.right - 1;
			else if (point.x < rect.left + rect.Width() / 2)
				point.x = rect.left + rect.Width() / 2;
			if (point.y > rect.bottom - 1)
				point.y = rect.bottom - 1;
			else if (point.y < rect.top + rect.Height() / 2)
				point.y = rect.top + rect.Height() / 2;
///			m_roundness.x = 2 * (rect.right - point.x);
///			m_roundness.y = 2 * (rect.bottom - point.y);
			m_pDocument->SetModifiedFlag();
			if (pView == NULL)
				Invalidate();
			else
				pView->InvalObj(this);
			return;
		}*/
		if (m_nShape == qie && nHandle > 8)	
		{
			CRect rect = m_position;
			rect.NormalizeRect();
			return;
		}
	}

	CDrawObj::MoveHandleTo(nHandle, point, pView);
}

// rect must be in logical coordinates
BOOL CDrawRect::Intersects(const CRect& rect)
{
	ASSERT_VALID(this);

	CRect rectT = rect;
	rectT.NormalizeRect();

	CRect fixed = m_position;
	fixed.NormalizeRect();
	if ((rectT & fixed).IsRectEmpty())
		return FALSE;

	CRgn rgn;
	switch (m_nShape)
	{
	case rectangle:
		return TRUE;

	case roundRectangle:
		rgn.CreateRoundRectRgn(fixed.left, fixed.top, fixed.right, fixed.bottom,
			m_roundness.x, m_roundness.y);
		break;

	case ellipse:
		rgn.CreateEllipticRgnIndirect(fixed);
		break;

	case pie:
		return TRUE;				//需更改
		break;

	case pie45:
		return TRUE;

	case line:
	case arrow:
	case beeline:
		{
			int w = (m_nLineSize + 10) / 2;
			//if (m_nShape==arrow) w+=m_rArrowSize;
			//int y = (m_logpen.lopnWidth.y + 5) / 2;   document says lopenWidth.y is not used;
			double l=sqrt((double)(fixed.top-fixed.bottom)*(fixed.top-fixed.bottom)+(fixed.left-fixed.right)*(fixed.left-fixed.right));
			double dx=w*(fixed.top-fixed.bottom)/l;
			double dy=w*(fixed.left-fixed.right)/l;
			int x=-(int)dx;
			int y=-(int)dy;
			
			int change=1;
			if (fixed.bottom!=m_position.bottom) change*=-1;
			if (fixed.left!=m_position.left) change*=-1;
			
			POINT points[4];
			points[0].x = m_position.left;
			points[0].y = m_position.top;
			points[1].x = m_position.left;
			points[1].y = m_position.top;
			points[2].x = m_position.right;
			points[2].y = m_position.bottom;
			points[3].x = m_position.right;
			points[3].y = m_position.bottom;

			if ((fixed.left-fixed.right)<=0)
			{
				points[0].x -= x;
				points[1].x += x;
				points[2].x += x;
				points[3].x -= x;
			}
			else
			{
				points[0].x += x;
				points[1].x -= x;
				points[2].x -= x;
				points[3].x += x;
			}

			if ((fixed.top - fixed.bottom)*change>=0)
			{
				points[0].y -= y;
				points[1].y += y;
				points[2].y += y;
				points[3].y -= y;
			}
			else
			{
				points[0].y += y;
				points[1].y -= y;
				points[2].y -= y;
				points[3].y += y;
			}
			rgn.CreatePolygonRgn(points, 4, WINDING);
		}
		break;
	default:
		return TRUE;
	}
	return rgn.RectInRegion(rectT);
}

CDrawObj* CDrawRect::Clone(CDrawDoc* pDoc)
{
	ASSERT_VALID(this);

	CDrawRect* pClone = new CDrawRect(m_position);

	pClone->m_LineStyle			= m_LineStyle;				//线条风格
	pClone->m_clrFillColor		= m_clrFillColor;			//填充颜色
	pClone->m_clrLineColor		= m_clrLineColor;			//线条颜色
	pClone->m_bNoFill			= m_bNoFill;				//是否填充
	pClone->m_nLineSize			= m_nLineSize;				//线条尺寸
///	pClone->m_clrBackColor		= m_clrBackColor;			//结束颜色

	pClone->m_nShape			= m_nShape;
	pClone->m_roundness			= m_roundness;
	pClone->m_nsweepAngle       = m_nsweepAngle;
	pClone->m_nstartAngle       = m_nstartAngle;
	pClone->m_npie				= m_npie;
	pClone->m_npie45			= m_npie45;
	pClone->bStart				= bStart;

	ASSERT_VALID(pClone);

	if (pDoc != NULL)
		pDoc->Add(pClone);

	ASSERT_VALID(pClone);
	return pClone;
}

void CDrawRect::Invalidate()
{
	ASSERT_VALID(this);
	if(m_nRoute == 0)
		m_pDocument->UpdateAllViews(NULL, HINT_UPDATE_DRAWOBJ, this);
	else
		m_pDocument->UpdateAllViews(NULL, HINT_UPDATE_ROUTE, this);
		
}




