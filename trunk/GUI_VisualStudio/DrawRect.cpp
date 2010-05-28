/*****************************************************************************
绘制RECT图形的类
说明：包括矩形，圆角矩形，圆

*****************************************************************************/
#include "stdafx.h"
#include "GUI_VisualStudio.h"
#include "drawrect.h"

///#include "drawdoc.h"
///#include "drawview.h"
///#include "drawobj.h"
///#include <mmsystem.h>
///#include "cntritem.h"
///#include <math.h>

extern "C"
void CALLBACK internalTimerProc(UINT id,UINT msg,DWORD dwUser,DWORD dw1,DWORD dw2)
{
///	CDrawRect *	DrawRect = (CDrawRect *)dwUser;

//	AfxMessageBox("KJ86");
///	DrawRect->ActionActive();
//	Sleep(10);
}
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

	m_nShape = rectangle;
	m_roundness.x = 16;
	m_roundness.y = 16;
	bplus = TRUE;
	bStart = FALSE;
	m_nstartAngle = 30;
	m_nsweepAngle = -180;
	m_npie	= 0;
	m_npie45 = 45;
	m_nRoute = 0; 
	bIsStartAction = FALSE;
}

CDrawRect::~CDrawRect()
{
///	if(nTimerIDRect)
///		timeKillEvent(nTimerIDRect);
}

void CDrawRect::Serialize(CArchive& ar)
{
	ASSERT_VALID(this);

	CDrawObj::Serialize(ar);
	if (ar.IsStoring())
	{
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
		bStart = FALSE;
///		ar >> m_nPercentFill;
		m_nMove = 0;

/*		if(m_bIsCar)
		{
			CRect rect = m_RectPath.GetAt(0);
			m_position = rect;
			m_rectAction = m_position;
		}*/
	}
}
/*
void CDrawRect::Remove()
{
	delete this;
}
*/
void CDrawRect::Draw(CDC* pDC)
{
	ASSERT_VALID(this);
	
	CRect rect = m_position;
	CRect rcPercent = m_position;
	rect.NormalizeRect();
	rcPercent.NormalizeRect();
	Rect GdiRect (rect.TopLeft().x,rect.TopLeft().y,rect.Size().cx,rect.Size().cy); 
	Rect GdiPercentRect;
	switch(m_RefPoint)
	{
	case TOP:
		{
		GdiPercentRect = Rect(rcPercent.TopLeft().x,
						rcPercent.TopLeft().y  ,
						rcPercent.Size().cx,
						rcPercent.Size().cy * m_nPercentFill /100); 
		}
		break;
	case BOTTOM:
		GdiPercentRect = Rect(rcPercent.TopLeft().x,
						rcPercent.TopLeft().y+(rcPercent.Size().cy - rcPercent.Size().cy * m_nPercentFill /100 ),
						rcPercent.Size().cx,
						rcPercent.Size().cy * m_nPercentFill  /100); 
		break;
	case LEFT:
		GdiPercentRect = Rect(rcPercent.TopLeft().x,
						rcPercent.TopLeft().y,
						rcPercent.Size().cx * m_nPercentFill  /100,
						rcPercent.Size().cy ); 
		break;
	case RIGHT:
		GdiPercentRect = Rect(rcPercent.TopLeft().x+(rcPercent.Size().cx - rcPercent.Size().cx * m_nPercentFill /100 ),
						rcPercent.TopLeft().y,
						rcPercent.Size().cx* m_nPercentFill /100 ,
						rcPercent.Size().cy ); 
		break;
	default:
		break;
	}
	
	Normallize(GdiRect);				//坐标转换

		DrawFill(pDC,GdiRect,GdiPercentRect);

}

void CDrawRect::DrawFill(CDC *pDC,Rect rc,Rect rcPercent)
{
	CRect rect = m_position;
	Rect GdiRect = rc ;

	Color  clrFillColor,clrLineColor;
	clrLineColor.SetFromCOLORREF(m_clrLineColor );
	clrFillColor.SetFromCOLORREF(m_clrFillColor );

	Graphics graphics(pDC->m_hDC);
	graphics.SetSmoothingMode (SmoothingModeHighSpeed);

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
			if(m_RefPoint != NULL)
	     		graphics.FillRectangle(&solidBrush,rcPercent);
			else
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
		break;
	case pie45:							//45度饼
		{
			REAL startAngle = m_npie45;
			REAL sweepAngle = -180.0f;
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
	}
	graphics.ReleaseHDC(pDC->m_hDC);
}

/*
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
		if (m_nShape == roundRectangle && nHandle == 9)
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
			m_roundness.x = 2 * (rect.right - point.x);
			m_roundness.y = 2 * (rect.bottom - point.y);
			m_pDocument->SetModifiedFlag();
			if (pView == NULL)
				Invalidate();
			else
				pView->InvalObj(this);
			return;
		}
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

void CDrawRect::ActionActive()
{

	if(bIsStartAction)
	{
		if(m_strAction == "出现")
		{

			m_nDrawTrans = 255;
			Invalidate();
			bIsStartAction = FALSE;
		}

		if(m_strAction == "渐入")
		{
			if(m_nDrawTrans < 255)
			{
				if(m_strSpeed == "慢速")
					m_nDrawTrans += 20;
				if(m_strSpeed == "中速")
					m_nDrawTrans += 40;
				if(m_strSpeed == "快速")
					m_nDrawTrans += 80;
			}
			else
			{
				m_nDrawTrans = 255;
			}
			Invalidate();
		}

		if(m_strAction == "消失")
		{

			m_nDrawTrans = 0;
			Invalidate();
			bIsStartAction = FALSE;
		}

		if(m_strAction == "闪烁")
		{
			if(m_nDrawTrans < 255)
				m_nDrawTrans += 100;
			else
				m_nDrawTrans -= 100;
			Invalidate();
		}

		if(m_strAction == "渐出")
		{
			if(m_nDrawTrans > 0)
			{
				if(m_strSpeed == "慢速")
					m_nDrawTrans -= 20;
				if(m_strSpeed == "中速")
					m_nDrawTrans -= 40;
				if(m_strSpeed == "快速")
					m_nDrawTrans -= 80;
			}
			else
			{
				m_nDrawTrans = 0;
			}
			Invalidate();
		}

		if(m_strAction == "旋转")
		{
			if(m_strSpeed == "慢速")
				m_nRoute += 10;
			if(m_strSpeed == "中速")
				m_nRoute += 20;
			if(m_strSpeed == "快速")
				m_nRoute += 30;
			Invalidate();
		}
	}
}

void CDrawRect::StartAction()
{
///	nTimerIDRect = timeSetEvent(200,500,internalTimerProc,(DWORD)this,false ? TIME_ONESHOT : TIME_PERIODIC);
	if (nTimerIDRect)
	{
		return TRUE;
	}
	return FALSE;
}

void CDrawRect::DrawCarMove()
{
	int nSize = m_nPointCount;
	CRect rect = m_rectAction;

	if(nSize < 1)
	{
		return;
	}

	if(m_nCarPaths >= nSize-1)
	{
		m_nActionRoute = 0;
		m_ActionStruct.stcRotary.ReferencePoint = CENTER;
		m_position = m_RectPath.GetAt(nSize-1);
		return;
	}
	
	CPoint  ptStart, ptEnd;
	CRect   EndRect;
	ptStart = m_RectPath.GetAt(m_nCarPaths).CenterPoint();
	EndRect = m_RectPath.GetAt(m_nCarPaths+1);
	if(m_nCarPaths < nSize-1)
		ptEnd = m_RectPath.GetAt(m_nCarPaths+1).CenterPoint();
	else
		ptEnd = ptStart;	
	
	double nXlen = abs(ptStart.x - ptEnd.x);
	double nYlen = abs(ptStart.y - ptEnd.y);
	double nMoveLen = sqrt(nXlen*nXlen + nYlen*nYlen);
//	double nAngle = (atan(nXlen/nYlen))*180/3.14159265;
	int xMove,yMove;

	if(nXlen == nMoveLen && nYlen == 0)				//直线
	{
		m_nActionRoute = 0;
		m_ActionStruct.stcRotary.ReferencePoint = CENTER;
		xMove = m_nMoveStep * m_CarStruct.nSpeed;
		CPoint ptCenter = ptStart;
		if(ptEnd.x > ptStart.x)
			ptCenter.x += abs(xMove);
		else
			ptCenter.x -= abs(xMove);
		m_position.left = ptCenter.x - rect.Width()/2;
		m_position.top = ptCenter.y-rect.Height()/2;
		m_position.right = ptCenter.x + rect.Width()/2;
		m_position.bottom = ptCenter.y+rect.Height()/2;
		m_nMoveStep++;
		if(xMove >= nMoveLen-m_CarStruct.nSpeed)
		{
			m_position = EndRect;
			m_nMoveStep = 0;
			m_nCarPaths++;
		}
	}

	if(nYlen == nMoveLen && nXlen == 0)				//斜线
	{
		m_nActionRoute = 0;
		m_ActionStruct.stcRotary.ReferencePoint = CENTER;
		yMove = m_nMoveStep * m_CarStruct.nSpeed;
		CPoint ptCenter = ptStart;
		if(ptEnd.y > ptStart.y)
			ptCenter.y += abs(yMove);
		else
			ptCenter.y -= abs(yMove);
		m_position.left = ptCenter.x - rect.Width()/2;
		m_position.top = ptCenter.y-rect.Height()/2;
		m_position.right = ptCenter.x + rect.Width()/2;
		m_position.bottom = ptCenter.y+rect.Height()/2;
		m_nMoveStep++;
		if(yMove >= nMoveLen-m_CarStruct.nSpeed)
		{
			m_position = EndRect;
			m_nMoveStep = 0;
			m_nCarPaths++;

		}
	}

	if(nXlen != 0 && nYlen != 0)
	{
		double nAngle = (nXlen/nMoveLen)/0.5;
		nAngle = nAngle*30;
		m_nActionRoute = nAngle;
		m_ActionStruct.stcRotary.ReferencePoint = CENTER;

		double x = sin(m_nActionRoute);
		double y = cos(m_nActionRoute);

		double MoveX = (m_nMoveStep * m_CarStruct.nSpeed) * x;
		double MoveY= (m_nMoveStep * m_CarStruct.nSpeed) * y;
		double len = sqrt((MoveX)*(MoveX) + (MoveY)*(MoveY));
		if(len < nMoveLen)
		{
			CPoint ptCenter = ptStart;
			if(ptEnd.x > ptStart.x)
				ptCenter.x += abs(MoveX);
			else
				ptCenter.x -= abs(MoveX);
			if(ptEnd.y > ptStart.y)
				ptCenter.y += abs(MoveY);
			else
				ptCenter.y -= abs(MoveY);
			m_position.left = ptCenter.x - rect.Width()/2;
			m_position.top = ptCenter.y-rect.Height()/2;
			m_position.right = ptCenter.x + rect.Width()/2;
			m_position.bottom = ptCenter.y+rect.Height()/2;
			
			m_nMoveStep++;
		}
		else
		{
			m_nMoveStep = 0;
			m_nCarPaths++;
		}
	}

}
*/



