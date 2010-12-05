#pragma once

// ==============
// QSelectTracker
//
// This class maintains a CRect m_Rect, which can be sized by the mouse.
// The rectangle starts with zero size at the starting point of Track().
//
// If Shift is pressed, the rectangle is a square, and dragging is
// restricted to horizontal, vertical and diagonals.
// 
// If Alt is pressed, resizing occurs with respect to the center. The center is not moved.
//
// If the space bar is pressed, the rectangle is dragged.
//===============================
// Version 1.0, August 29, 2003
// (c) Sjaak Priester, Amsterdam
// www.sjaakpriester.nl
//
// Freeware. Use at your own risk. Comments welcome.

#include "QTracker.h"

class QSelectTracker :
	public QTracker
{
public:
// Construction
	QSelectTracker(CWnd * pWnd);
	virtual ~QSelectTracker();

// Methods
	CRect GetRect() const				{ return m_Rect; }
	void GetRect(LPRECT pRect) const	{ ((CRect *) pRect)->CopyRect(m_Rect); }
	// Get the resulting rectangle.

	void SetTrackPen(CPen * pPen);
	// Set the pen used for drawing the track rectangle
	// If pPen == NULL: set the default (dotted black, 1 pixel)
	// QRectTracker deletes the pen if no longer needed.

	int m_CenterSize;
	// The size of the midpoint drawn by tracking, in logical coordinates.
	// If zero, no midpoint is drawn. Default is 4.

	COLORREF m_colorCenter;
	// The color of the midpoint. Default is black.

protected:
// Overrides
	virtual int OnBeginTrack(UINT nFlags, CPoint point);
	virtual int OnEndTrack(int trackResult);
	virtual int OnMouseMessage(UINT msg, UINT nFlags, CPoint point);
	virtual void OnUpdate(CDC * pDC, UINT nMode);

// Implementation
	void DrawCenter(CDC * pDC);
	CPoint RestrictPoint(CPoint point, CPoint pntBase, BOOL bDiagonalOnly);

	CRect m_Rect;			// the current rectangle
	CPen *m_pTrackPen;
};

