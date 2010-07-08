#include "stdafx.h"
#include "Graphic.h"

IMPLEMENT_DYNAMIC(CGraphic,CObject)

CGraphic::CGraphic()
{
	m_nPenWidth = 1;
//	m_colorPen = RGB(0,0,0);
	m_bSelect = FALSE;
///	m_bFill	= FALSE;
///	m_nLineStyle = 0;
///	m_bLock = FALSE;
///	m_nUnion = 0;
///	m_timespan = 0;///modified by xizheng
///	m_RoundWidth = 15;///modified by xizheng
///	m_RoundHeight = 15;///modified by xizheng
///	m_FillStyle = -1;///modified by xizheng
///	memset(&m_ptdata,0,sizeof(POINTDATA));
}

CGraphic::~CGraphic()
{

}

void CGraphic::Serialize(CArchive &ar)
{
///	m_pointArray.Serialize(ar);
	if(ar.IsStoring())
	{
        ar << m_nPenWidth;
///	    ar << m_colorPen;
///	    ar << m_colorBrush;
///		ar << m_nLineStyle;
///		ar << m_bFill;
		ar << m_bSelect;
///		ar << m_nShapeMode;
///		ar << m_nNo;
///		ar << m_bLock;
///		ar << m_nUnion;
///		ar << m_FillStyle;
///		ar.Write(&m_ptdata,sizeof(POINTDATA));
	}
	else
	{
		ar >> m_nPenWidth;
///		ar >> m_colorPen;
///		ar >> m_colorBrush;
///		ar >> m_nLineStyle;
///		ar >> m_bFill;
		ar >> m_bSelect;
///		ar >> m_nShapeMode;
///		ar >> m_nNo;
///		ar >> m_bLock;
///		ar >> m_nUnion;
///		ar >> m_FillStyle;
///		ar.Read(&m_ptdata,sizeof(POINTDATA));
	}
}

UINT CGraphic::ChangeCursor(CPoint &point)
{
	CRect rect;
	rect.top = min(m_pointArray[0].y,m_pointArray[1].y);
	rect.bottom = max(m_pointArray[0].y,m_pointArray[1].y);
	rect.left = min(m_pointArray[0].x,m_pointArray[1].x);
	rect.right = max(m_pointArray[0].x,m_pointArray[1].x);
	CRgn rgn;
	rgn.CreateRectRgn(rect.left-RADIUS,rect.top+RADIUS,rect.left+RADIUS,rect.top-RADIUS);
	if(rgn.PtInRegion(point))
	{
		rgn.DeleteObject();
		return 1;
	}
	else rgn.DeleteObject();///modified by xizheng
	rgn.CreateRectRgn(rect.right-RADIUS,rect.bottom+RADIUS,rect.right+RADIUS,rect.bottom-RADIUS);
	if(rgn.PtInRegion(point))
	{
		rgn.DeleteObject();
		return 1;
	}
	else rgn.DeleteObject();///modified by xizheng
	rgn.CreateRectRgn(rect.left-RADIUS,rect.bottom+RADIUS,rect.left+RADIUS,rect.bottom-RADIUS);
	if(rgn.PtInRegion(point))
	{
		rgn.DeleteObject();
		return 2;
	}
	else rgn.DeleteObject();///modified by xizheng
    rgn.CreateRectRgn(rect.right-RADIUS,rect.top+RADIUS,rect.right+RADIUS,rect.top-RADIUS);
	if(rgn.PtInRegion(point))
	{
		rgn.DeleteObject();
		return 2;
	}
	else rgn.DeleteObject();///modified by xizheng
	return 0;
}

void  CGraphic::ModifyShape(CPoint &pointOrigin,CPoint &point)
{
   CRect rect;
  if((pointOrigin.x == point.x) && (pointOrigin.y == point.y))
  {   
	rect.top = min(m_pointArray[0].y,m_pointArray[1].y);
	rect.bottom = max(m_pointArray[0].y,m_pointArray[1].y);
	rect.left = min(m_pointArray[0].x,m_pointArray[1].x);
	rect.right = max(m_pointArray[0].x,m_pointArray[1].x);
	CRgn rgn;
	rgn.CreateRectRgn(rect.left-RADIUS,rect.top+RADIUS,rect.left+RADIUS,rect.top-RADIUS);
	if(rgn.PtInRegion(point))
	{
		m_pointArray[0].x = rect.right;
		m_pointArray[0].y = rect.bottom;
		m_pointArray[1].x = rect.left;
		m_pointArray[1].y = rect.top;
		return;
	}	
	rgn.CreateRectRgn(rect.right-RADIUS,rect.bottom+RADIUS,rect.right+RADIUS,rect.bottom-RADIUS);
	if(rgn.PtInRegion(point))
	{	
		m_pointArray[0].x = rect.left;
		m_pointArray[0].y = rect.top;
		m_pointArray[1].x = rect.right;
		m_pointArray[1].y = rect.bottom;
		return;
	}
	rgn.CreateRectRgn(rect.left-RADIUS,rect.bottom+RADIUS,rect.left+RADIUS,rect.bottom-RADIUS);
	if(rgn.PtInRegion(point))
	{
		m_pointArray[0].x = rect.right;
		m_pointArray[0].y = rect.top;
		m_pointArray[1].x = rect.left;
		m_pointArray[1].y = rect.bottom;
		return;
	}
    rgn.CreateRectRgn(rect.right-RADIUS,rect.top+RADIUS,rect.right+RADIUS,rect.top-RADIUS);
	if(rgn.PtInRegion(point))
	{
		m_pointArray[0].x = rect.left;
		m_pointArray[0].y = rect.bottom;
		m_pointArray[1].x = rect.right;
		m_pointArray[1].y = rect.top;
		return;
	}
  }
  else
      m_pointArray[1] = point;
}

CGraphic* CGraphic::CreateSameOne()
{
	return this;
}

CRect CGraphic::GetRect()
{
	CRect rect(0,0,0,0);
	if(m_pointArray.GetSize() < 2)
	   return rect;
	rect.left = min(m_pointArray[0].x,m_pointArray[1].x) - 5 - m_nPenWidth;
	rect.right = max(m_pointArray[0].x,m_pointArray[1].x) + 5+ m_nPenWidth;
	rect.top = min(m_pointArray[0].y,m_pointArray[1].y) - 5 - m_nPenWidth;
	rect.bottom = max(m_pointArray[0].y,m_pointArray[1].y) + 5 + m_nPenWidth;
	return rect;

}

CRect CGraphic::GetRealRect()
{
	CRect rect(0,0,0,0);
	if(m_pointArray.GetSize() < 2)
	   return rect;
	rect.left = min(m_pointArray[0].x,m_pointArray[1].x) ;
	rect.right = max(m_pointArray[0].x,m_pointArray[1].x) ;
	rect.top = min(m_pointArray[0].y,m_pointArray[1].y);
	rect.bottom = max(m_pointArray[0].y,m_pointArray[1].y);
	return rect;
}

void CGraphic::DrawSelect(CDC *pDC)
{
	CPen pen(PS_SOLID,SELECTLINE,m_colorPen);
	CPen *oldpen = pDC->SelectObject(&pen);
	int oldmode = pDC->SetROP2(R2_NOT);
	pDC->Rectangle(m_pointArray[0].x-3,m_pointArray[0].y+3,m_pointArray[0].x+3,m_pointArray[0].y-3);
	pDC->Rectangle(m_pointArray[1].x-3,m_pointArray[0].y+3,m_pointArray[1].x+3,m_pointArray[0].y-3);
	pDC->Rectangle(m_pointArray[0].x-3,m_pointArray[1].y+3,m_pointArray[0].x+3,m_pointArray[1].y-3);
	pDC->Rectangle(m_pointArray[1].x-3,m_pointArray[1].y+3,m_pointArray[1].x+3,m_pointArray[1].y-3);
	pDC->SetROP2(oldmode);
	pDC->SelectObject(oldpen);
}

void CGraphic::DragGraphic(int x,int y)
{
	int size = m_pointArray.GetSize();
	for(int i=0; i<size; i++)
	{
		m_pointArray[i].x += x;
		m_pointArray[i].y += y;
	}
}

CGraphic *CGraphic::Select(CPoint &pointx,CPoint &pointy,BOOL flag)
{
	if((pointx.x == pointy.x) && (pointx.y == pointy.y))
	{
		CRgn rgn;
		rgn.CreateRectRgn(m_pointArray[0].x,m_pointArray[0].y,m_pointArray[1].x,m_pointArray[1].y);
		if(rgn.PtInRegion(pointx))
		{
			m_bSelect = TRUE;
			return this;
		}
	}
	else
	{
		CRgn rgn;
		rgn.CreateRectRgn(pointx.x,pointx.y,pointy.x,pointy.y);
		if(rgn.PtInRegion(m_pointArray[0].x,m_pointArray[0].y) && rgn.PtInRegion(m_pointArray[1].x,m_pointArray[1].y))
		{
			m_bSelect = TRUE;
			return this;
		}
	}
	if(flag == false)
		m_bSelect = FALSE;
	return NULL;
}
