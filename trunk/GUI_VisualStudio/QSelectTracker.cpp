///////////////////////////////////////////////////////////
// QSelectTracker
//===============================
// Version 1.0, August 29, 2003
// (c) Sjaak Priester, Amsterdam
// www.sjaakpriester.nl
//
// Freeware. Use at your own risk. Comments welcome.

#include "StdAfx.h"
#include "QSelectTracker.h"

//#include "STDLIB.H"
//#include <stdio.h>
//#include <afx.h>
#include <stdlib.h>
//#pragma comment(lib,"msvert.lib")


QSelectTracker::QSelectTracker(CWnd * pWnd)
: QTracker(pWnd)
, m_pTrackPen(0)
, m_CenterSize(4)
, m_colorCenter(RGB(0, 0, 0))
{
	SetTrackPen(0);
}

QSelectTracker::~QSelectTracker()
{
	delete m_pTrackPen;
}

int QSelectTracker::OnBeginTrack(UINT nFlags, CPoint point)
{
	m_Rect.SetRectEmpty();
	m_Rect.OffsetRect(point);
	return QTracker::OnBeginTrack(nFlags, point);
}

int QSelectTracker::OnEndTrack(int trackResult)
{
	if (trackResult <= 0) m_Rect.SetRectEmpty();

	return trackResult;
}

int QSelectTracker::OnMouseMessage(UINT msg, UINT nFlags, CPoint point)
{
	// If spacebar is pressed, move the rectangle
	if (::GetAsyncKeyState(VK_SPACE) < 0)
	{
		if (nFlags & MK_SHIFT)
		{
			point = RestrictPoint(point, m_StartPoint, FALSE);
			m_Point = point;
		}

		CSize sz = point - m_PreviousPoint;
		m_Rect.OffsetRect(sz);
	}
	else
	{
		if (nFlags & MK_SHIFT)
		{
			point = RestrictPoint(point, m_Rect.CenterPoint(), TRUE);
			m_Point = point;
		}
		
		if (::GetAsyncKeyState(VK_MENU) < 0)	// Alt pressed
		{
			CPoint pCenter = m_Rect.CenterPoint();
			CSize sz = point - pCenter;
			m_Rect.TopLeft() = pCenter - sz;
		}

		m_Rect.BottomRight() = point;
	}
	return QTracker::OnMouseMessage(msg, nFlags, point);
}

void QSelectTracker::OnUpdate(CDC * pDC, UINT /*nMode*/)
{
	ASSERT_VALID(pDC);
	ASSERT_VALID(m_pTrackPen);

	CPen * pOldPen = (CPen *) pDC->SelectObject(m_pTrackPen);
	pDC->Rectangle(& m_Rect);
	if (pOldPen) pDC->SelectObject(pOldPen);
	DrawCenter(pDC);
}

void QSelectTracker::DrawCenter(CDC * pDC)
{
	int d = 2 * m_CenterSize;

	if (m_CenterSize
		&& abs(m_Rect.Width()) > d
		&& abs(m_Rect.Height()) > d)
	{
		CPoint pCenter = m_Rect.CenterPoint();

		CPen pen(PS_SOLID, 0, m_colorCenter);

		CPen * pOldPen = (CPen *) pDC->SelectObject(& pen);

		pDC->MoveTo(pCenter.x - m_CenterSize, pCenter.y);
		pDC->LineTo(pCenter.x + m_CenterSize, pCenter.y);
		pDC->MoveTo(pCenter.x, pCenter.y - m_CenterSize);
		pDC->LineTo(pCenter.x, pCenter.y + m_CenterSize);

		if (pOldPen) pDC->SelectObject(pOldPen);
	}
}

// Set the pen of the track rectangle; if 0, use default (1 pixel dotted black).
void QSelectTracker::SetTrackPen(CPen * pPen)
{


	delete m_pTrackPen;
	if (pPen) m_pTrackPen = pPen;
	else
	{
		unsigned int _winmajor;/// = _osver & 0x00FF ;
		if ( _winmajor > 4)
		{
			LOGBRUSH lb;
			lb.lbColor = RGB(0, 0, 0);
			lb.lbHatch = 0;
			lb.lbStyle = BS_SOLID;

			m_pTrackPen = new CPen(PS_COSMETIC | PS_ALTERNATE, 1, & lb);
		}
		else m_pTrackPen = new CPen(PS_SOLID, 0, RGB(192, 192, 192));
					// PS_ALTERNATE not supported on W98
	}
}

// Restrict point to horizontal, vertical or diagonal with respect to pntBase
CPoint QSelectTracker::RestrictPoint(CPoint point, CPoint pntBase, BOOL bDiagonalOnly)
{
	// distance
	CSize d = point - pntBase;
	int cxAbs = abs(d.cx);
	int cyAbs = abs(d.cy);

	BOOL bHandled = FALSE;

	if (! bDiagonalOnly)
	{
		if (cxAbs > 2 * cyAbs)			// 0 degrees
		{
			point.y = pntBase.y;
			bHandled = TRUE;
		}
		else if (cyAbs > 2 * cxAbs)		// 90 degrees
		{
			point.x = pntBase.x;
			bHandled = TRUE;
		}
	}
	
	if (! bHandled)					// 45 degrees
	{
		if (cxAbs > cyAbs)
			point.x = pntBase.x + ((d.cx < 0) ? -cyAbs : cyAbs);
		else point.y = pntBase.y + ((d.cy < 0) ? -cxAbs : cxAbs);
	}
	return point;
}
