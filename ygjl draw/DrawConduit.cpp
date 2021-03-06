// DrawConduit.cpp: implementation of the CDrawConduit class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Draw.h"
#include "DrawConduit.h"
#include "drawdoc.h"
#include "drawview.h"
#include "drawobj.h"
#include "ConduitSetDlg.h"
#include <mmsystem.h>
#include <math.h>

///#include "cntritem.h"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

IMPLEMENT_SERIAL(CDrawConduit, CDrawObj, 0)

CDrawConduit::CDrawConduit()
{
	m_points = NULL;
	m_nPoints = 0;
	m_nAllocPoints = 0;
}

CDrawConduit::CDrawConduit(const CRect& position)
	: CDrawObj(position)
{
	m_points = NULL;
	m_nPoints = 0;
	m_nAllocPoints = 0;
	m_ConduitStruct.nPoint = 0;
	m_ConduitStruct.clrBackColor = RGB(153,153,153);
	m_ConduitStruct.clrForwordColor = RGB(204,204,204);
	m_ConduitStruct.clrMoveColor = RGB(0,0,255);
	m_ConduitStruct.nLineWidth = 20;

	m_bIsShowMove = FALSE;
}

CDrawConduit::~CDrawConduit()
{
	if (m_points != NULL)
		delete[] m_points;
}

void CDrawConduit::Serialize( CArchive& ar )
{
	int i;
	CDrawObj::Serialize( ar );
	if( ar.IsStoring() )
	{
		ar << (WORD) m_nPoints;
		ar << (WORD) m_nAllocPoints;
		ar.Write(&m_ConduitStruct,sizeof(ConduitStruct));
		for (i = 0;i< m_nPoints; i++)
			ar << m_points[i];
	}
	else
	{
		WORD wTemp;
		ar >> wTemp; m_nPoints = wTemp;
		ar >> wTemp; m_nAllocPoints = wTemp;
		ar.Read(&m_ConduitStruct,sizeof(ConduitStruct));
		m_points = new CPoint[m_nAllocPoints];
		for (i = 0;i < m_nPoints; i++)
			ar >> m_points[i];
	}
}

void CDrawConduit::Draw(CDC* pDC)
{
	ASSERT_VALID(this);
	Graphics graphics (pDC->m_hDC);

	Color  clrLineColor,clrFillColor, clrDotColor;
	clrLineColor.SetFromCOLORREF(m_ConduitStruct.clrBackColor);
	clrFillColor.SetFromCOLORREF(m_ConduitStruct.clrForwordColor );
	clrDotColor.SetFromCOLORREF(m_ConduitStruct.clrMoveColor);

	Pen penLine(clrLineColor,m_ConduitStruct.nLineWidth);
//	penLine.SetWidth(m_ConduitStruct.nLineWidth);
	penLine.SetLineCap(LineCapRound , LineCapRound , DashCapRound);

	Pen Dotpen(clrDotColor,m_ConduitStruct.nLineWidth);
	Dotpen.SetWidth(m_ConduitStruct.nLineWidth - 5);
	Dotpen.SetLineCap(LineCapRound , LineCapRound , DashCapRound);	

	REAL dashValues[4] = {2, 1, 2, 1};
	Dotpen.SetDashPattern(dashValues, 4);	

	if(m_bIsShowMove)
		Dotpen.SetDashOffset(2);


	PointF *points = new PointF[m_nPoints+1];
	PointF *Fillpoints = new PointF[m_nPoints+1];

	for (int i=0;i<m_nPoints;i++)
	{
		Fillpoints[i].X = m_points[i].x;
		Fillpoints[i].Y = m_points[i].y;
	}


	for (i=0;i<m_nPoints;i++)
	{
		points[i].X = m_points[i].x;
		points[i].Y = m_points[i].y;
	}

	Fillpoints[0].X++;
	Fillpoints[0].Y++;
	points[0].X++;
	points[0].Y++;
	
//	m_nLineSize = 5;
	GraphicsPath Linepath;
	Linepath.StartFigure();
	for (i=0;i<m_nPoints-1;i++)
	{
		Linepath.AddLine(points[i],points[i+1]);
	}
	penLine.SetLineJoin(LineJoinBevel);
	Dotpen.SetLineJoin(LineJoinBevel);

	graphics.DrawPath(&penLine, &Linepath);
	graphics.DrawPath(&Dotpen, &Linepath);
	
	delete[] points;
	delete[] Fillpoints;

///	penLine.Dispose();
///		Dotpen.Dispose();

	graphics.ReleaseHDC(pDC->m_hDC);
}


// position must be in logical coordinates
void CDrawConduit::MoveTo(const CRect& position, CDrawView* pView)
{
	ASSERT_VALID(this);
	if (position == m_position)
		return;

	if (pView == NULL)
		Invalidate();
	else
		pView->InvalObj(this);

	for (int i = 0; i < m_nPoints; i += 1)
	{
		m_points[i].x += position.left - m_position.left;
		m_points[i].y += position.top - m_position.top;
	}

	m_position = position;

	if (pView == NULL)
		Invalidate();
	else
		pView->InvalObj(this);
	m_pDocument->SetModifiedFlag();
}

int CDrawConduit::GetHandleCount()
{
	if(m_bIsGroup)
		return 0;
	return m_nPoints;
}

CPoint CDrawConduit::GetHandle(int nHandle)
{
	ASSERT_VALID(this);

	ASSERT(nHandle >= 1 && nHandle <= m_nPoints);
	return m_points[nHandle - 1];
}

HCURSOR CDrawConduit::GetHandleCursor(int )
{
	return AfxGetApp()->LoadStandardCursor(IDC_ARROW);
}

// point is in logical coordinates
void CDrawConduit::MoveHandleTo(int nHandle, CPoint point, CDrawView* pView)
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
BOOL CDrawConduit::Intersects(const CRect& rect)
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

CDrawObj* CDrawConduit::Clone(CDrawDoc* pDoc)
{
	ASSERT_VALID(this);

	CDrawConduit* pClone = new CDrawConduit(m_position);
	pClone->m_LineStyle			= m_LineStyle;				//线条风格
	pClone->m_clrFillColor		= m_clrFillColor;			//填充颜色
	pClone->m_clrLineColor		= m_clrLineColor;			//线条颜色
	pClone->m_bNoFill			= m_bNoFill;				//是否填充
	pClone->m_nLineSize			= m_nLineSize;				//线条尺寸
///	pClone->m_clrBackColor		= m_clrBackColor;			//结束颜色

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
void CDrawConduit::AddPoint(const CPoint& point, CDrawView* pView)
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

BOOL CDrawConduit::RecalcBounds(CDrawView* pView)
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
	m_position.top -= m_ConduitStruct.nLineWidth ;
	m_position.left -= m_ConduitStruct.nLineWidth ;
	m_position.bottom += m_ConduitStruct.nLineWidth ;
	m_position.right += m_ConduitStruct.nLineWidth ;

	if (pView == NULL)
		Invalidate();
	else
		pView->InvalObj(this);

	return TRUE;
}

void CDrawConduit::OnEditProperties()
{
	CConduitSetDlg dlg;

	dlg.m_clrConduitColor	= m_ConduitStruct.clrBackColor;
	dlg.m_clrDotColor		= m_ConduitStruct.clrMoveColor;
	dlg.m_nWidth			= m_ConduitStruct.nLineWidth;
	dlg.m_nPointNo			= m_ConduitStruct.nPoint;
	if(dlg.DoModal() != IDOK)
		return;
	m_ConduitStruct.clrBackColor = dlg.m_clrConduitColor;
	m_ConduitStruct.clrMoveColor  = dlg.m_clrDotColor;
	m_ConduitStruct.nLineWidth  = dlg.m_nWidth;
	m_ConduitStruct.nPoint		= dlg.m_nPointNo;
	Invalidate();
	m_pDocument->SetModifiedFlag();
}

BOOL CDrawConduit::StartAction()
{
	m_bIsShowMove = !m_bIsShowMove;
	Invalidate();
	return TRUE;
}