//===============================
// QZoomView.cpp
//
// Version 1.1, October 8, 2003
// Buggy behaviour with MM_TEXT repaired.
// Erroneous assert when no cursors are set corrected.
// Spurious loupe cursor problem fixed.
//
// Version 1.0, August 29, 2003
// (c) Sjaak Priester, Amsterdam
// www.sjaakpriester.nl
//
// Freeware. Use at your own risk. Comments welcome.

#include "stdafx.h"
#include "QZoomView.h"
#include "QSelectTracker.h"
///#pragma comment(lib,"QTrackers.lib")

#define ZOOM_MIN	.05f
#define ZOOM_MAX	20.0f

#ifndef MM_NONE
#define MM_NONE	0
#endif

//===========================================
// QZoomView

// Preset zoom factors
float QZoomView::m_DefaultPresets[] =
{
	0.125f, 1.0f/6.0f, 0.25f, 1.0f/3.0f, 0.5f, 2.0f/3.0f, 1.0f,
	1.5f, 2.0f, 3.0f, 4.0f, 6.0f, 8.0f
};
#define INDEX_100PERCENT	6

HCURSOR QZoomView::m_Cursors[5] = { 0 };

IMPLEMENT_DYNAMIC(QZoomView, CScrollView)

BEGIN_MESSAGE_MAP(QZoomView, CScrollView)
	ON_WM_LBUTTONDOWN()
	ON_WM_SETCURSOR()
	ON_WM_KEYUP()
	ON_WM_KEYDOWN()
	ON_WM_MOUSEWHEEL()
END_MESSAGE_MAP()

QZoomView::QZoomView()
: m_PresetCount(0)
, m_Presets(0)
, m_Mode(ZoomViewOff)
, m_Zoom(1.0f)
, m_PresetIndex(INDEX_100PERCENT)
, m_WheelDelta(0)
, m_MessageBeep(MB_ICONHAND)
{
	SetPresets(m_DefaultPresets, sizeof(m_DefaultPresets)/sizeof(float));
}

QZoomView::~QZoomView()
{
	delete m_Presets;
}

// QZoomView initializing

BOOL QZoomView::SetPresets(const float * pPresets, int count)
{
	if (! pPresets || ! count) return FALSE;
	if (pPresets[0] < ZOOM_MIN) return FALSE;
	if (pPresets[count - 1] > ZOOM_MAX) return FALSE;

	for (int i = 1; i < count; i++)
		if (pPresets[i] <= pPresets[i - 1]) return FALSE;

	delete m_Presets;

	m_Presets = new float[count];
	if (m_Presets) ::CopyMemory(m_Presets, pPresets, count * sizeof(float));
	m_PresetCount = count;

	m_PresetIndex = -1;
	for ( i = 0; i < count; i++)
		if (pPresets[i] == 1.0f)
		{
			m_PresetIndex = i;
			break;
		}
	return TRUE;
}

float QZoomView::ZoomTo(float zoom)
{
#ifdef _DEBUG
	if (m_nMapMode == MM_NONE)
	{
		TRACE(_T("Error: must call SetScrollSizes() before calling ZoomTo.\n"));
		ASSERT(FALSE);
		return 1.0f;
	}
#endif //_DEBUG

	if (zoom < ZOOM_MIN) zoom = ZOOM_MIN;
	else if (zoom > ZOOM_MAX) zoom = ZOOM_MAX;

///	TRACE1(_T("Zoom factor = %f\n"), zoom);

	float prevZoom = m_Zoom;

	if (m_Zoom != zoom)
	{
		m_Zoom = zoom;

		CClientDC dc(this);
		OnPrepareDC(& dc);

		m_totalDev = m_totalLog;
		dc.LPtoDP(& m_totalDev);

		m_pageDev.cx = m_totalDev.cx / 10;
		m_pageDev.cy = m_totalDev.cy / 10;
		m_lineDev.cx = m_pageDev.cx / 10;
		m_lineDev.cy = m_pageDev.cy / 10;

		UpdateBars();
		OnZoom(zoom, prevZoom);
		Invalidate();
	}
	m_WheelDelta = 0;
	return prevZoom;
}

void QZoomView::ZoomToPreset(int index, const LPPOINT center /* = NULL */)
{
#ifdef _DEBUG
	if (m_nMapMode == MM_NONE)
	{
		TRACE(_T("Error: must call SetScrollSizes() before calling SetZoomIndex.\n"));
		ASSERT(FALSE);
		return;
	}
#endif //_DEBUG
	ASSERT(index >= 0);

	if (index >= m_PresetCount) return;

	CPoint pntCenter;
	if (center) pntCenter = * center;
	else
	{
		CClientDC dc(this);
		OnPrepareDC(& dc);

		CRect rcClient;
		GetClientRect(rcClient);
		pntCenter = rcClient.CenterPoint();
		dc.DPtoLP(& pntCenter);
	}

	m_PresetIndex = index;

	ZoomTo(m_Presets[index]);
	ScrollToCenter(pntCenter);
}

void QZoomView::ZoomToRectangle(CRect logRect)
{
	CRect rcClient;
	GetClientRect(rcClient);

	// Compensate for scrollbars after zooming
	DWORD dwStyle = GetStyle();

	CSize szSB;
	GetScrollBarSizes(szSB);

	if(!(dwStyle & WS_VSCROLL))
		rcClient.right -= szSB.cx;
	if(!(dwStyle & WS_HSCROLL))
		rcClient.bottom -= szSB.cy;

	CRect devRect(logRect);

	// Original mapmode gives 100% zoom
	CClientDC dc(this);
	dc.SetMapMode(m_nMapMode);

	// Rect for 100% zoom in device coordinates:
	dc.LPtoDP(devRect);
	devRect.NormalizeRect();

	// We need to compare devRect.Width()/rcClient.right to devRect.Height()/rcClient.bottom.
	// Give them common denominators and compare just the numerators (assume all
	// numbers are positive):
	int nx = devRect.Width() * rcClient.bottom;
	int ny = devRect.Height() * rcClient.right;

	float zoom;
	if (nx < ny)
	{
		if (devRect.Width() < rcClient.right)
			rcClient.bottom += szSB.cy;
								// We probably don't need a horizontal scrollbar,
								// but we can't be sure.

		// -1 compensates for roundof errors
		zoom = (float)(rcClient.bottom - 1) /(float)devRect.Height();
	}
	else
	{
		if (devRect.Height() < rcClient.bottom)
			rcClient.right += szSB.cx;
		zoom = (float)(rcClient.right - 1) / (float)devRect.Width();
	}
	ZoomTo(zoom);
	m_PresetIndex = -1;
	ScrollToCenter(logRect.CenterPoint());
}

BOOL QZoomView::ZoomIn(const LPPOINT pPoint /* = NULL */)
{
	if (! m_Presets) return FALSE;

	int i;
	for ( i = 0; i < m_PresetCount; i++) if (m_Presets[i] > m_Zoom) break;
	if ( i < m_PresetCount)
	{
		ZoomToPreset(i, pPoint);
		return TRUE;
	}
	else
	{
		if (m_MessageBeep != NoBeep) MessageBeep(m_MessageBeep);
		return FALSE;
	}
}

BOOL QZoomView::ZoomOut(const LPPOINT pPoint /* = NULL */)
{
	if (! m_Presets) return FALSE;

	int i;
	for ( i = m_PresetCount; --i >= 0;) if (m_Presets[i] < m_Zoom) break;
	if ( i >= 0)
	{
		ZoomToPreset(i, pPoint);
		return TRUE;
	}
	else
	{
		if (m_MessageBeep != NoBeep) MessageBeep(m_MessageBeep);
		return FALSE;
	}
}

void QZoomView::ZoomToWindow(void)
{
	CRect rc(CPoint(0, 0), GetTotalSize());
	ZoomToRectangle(rc);
}

BOOL QZoomView::ScrollToCenter(CPoint logCenter)
{
	CClientDC dc(this);
	OnPrepareDC(& dc);
	dc.LPtoDP(& logCenter);

	CRect rcClient;
	GetClientRect(rcClient);

	return OnScrollBy(logCenter - rcClient.CenterPoint());
}

// Added in version 1.1
CRect QZoomView::VisibleRect(void)
{
	CRect rcDoc(0, 0, m_totalLog.cx, m_totalLog.cy);
	rcDoc.NormalizeRect();

	CRect rcClient;
	GetClientRect(rcClient);

	CClientDC dc(this);
	OnPrepareDC(& dc);
	dc.DPtoLP(rcClient);
	rcClient.NormalizeRect();

	rcClient &= rcDoc;
	return rcClient;
}

// QZoomView message handlers    OnLButtonDown

void QZoomView::DoLButtonDown(UINT nFlags, CPoint point)
{
	int mode = m_Mode;
	if (::GetKeyState(VK_SPACE) < 0) mode = ZoomViewDrag;

	if (mode == ZoomViewZoomIn || mode == ZoomViewZoomOut)
	{
		CClientDC dc(this);
		OnPrepareDC(& dc);
		dc.DPtoLP(& point);

		QSelectTracker tracker(this);
		tracker.m_CenterSize = 0;

		HCURSOR hOldCursor = 0;
		HCURSOR hNewCursor = m_Cursors[CursorLoupe];
		if (hNewCursor) hOldCursor = ::SetCursor(hNewCursor);
		
		int r = tracker.Track(& dc, nFlags, point);
///		TRACE1(_T("tracker returns %d\n"), r);

		if (hOldCursor) ::SetCursor(hOldCursor);

		if (r == QTracker::TrackNoMove)		// no mouse movement, zoom to point
		{
			if (::GetKeyState(VK_CONTROL) < 0) mode ^= 3;
			if (mode == ZoomViewZoomIn) ZoomIn(& point);
			else ZoomOut(& point);
		}
		else if (r > 0) ZoomToRectangle(tracker.GetRect());
	}
	else if (mode == ZoomViewDrag)
	{
		Dragger dragger(this);

		HCURSOR hOldCursor = 0;
		HCURSOR hNewCursor = m_Cursors[CursorGripClosed];
		if (hNewCursor) hOldCursor = ::SetCursor(hNewCursor);
		
		dragger.Track(point);

		if (hOldCursor) ::SetCursor(hOldCursor);
	}

	CScrollView::OnLButtonDown(nFlags, point);
}

BOOL QZoomView::DoMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	if (nFlags & MK_CONTROL)
	{
		m_WheelDelta += zDelta;
		if (m_WheelDelta >= 120) ZoomOut();
		else if (m_WheelDelta <= -120) ZoomIn();
		return TRUE;
	}

	return CScrollView::OnMouseWheel(nFlags, zDelta, pt);
}

BOOL QZoomView::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	if (nHitTest != HTCLIENT || m_Mode == ZoomViewOff)
		return CScrollView::OnSetCursor(pWnd, nHitTest, message);

	SetCursor();
	return TRUE;
}

void QZoomView::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == VK_CONTROL || nChar == VK_SPACE) SetCursor();
	CScrollView::OnKeyUp(nChar, nRepCnt, nFlags);
}

void QZoomView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == VK_CONTROL || nChar == VK_SPACE) SetCursor();
	CScrollView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void QZoomView::SetCursor(void)
{
	int mode = m_Mode;
	if (::GetKeyState(VK_SPACE) < 0) mode = ZoomViewDrag;
	if ((mode == ZoomViewZoomIn || mode == ZoomViewZoomOut)
		&& ::GetKeyState(VK_CONTROL) < 0) mode ^= 3;

	int iCursor(-1);
	switch (mode)
	{
	case ZoomViewZoomIn:
		iCursor = CursorLoupePlus;
		break;
	case ZoomViewZoomOut:
		iCursor = CursorLoupeMinus;
		break;
	case ZoomViewDrag:
		iCursor = CursorGripOpen;
		break;
	default:
		ASSERT(mode == ZoomViewOff);	// No other mode allowed
		break;
	}

	HCURSOR h = NULL;
	if (iCursor >= 0) h = m_Cursors[iCursor];
	if (h) ::SetCursor(h);
}

/*---------------------------------------------------------------------------
   FUNCTION: SetZoomSizes
   PURPOSE : Set up the CZoomView class with the logical page size, and 
   			 scrolling page/line units.  
   			 This replaces CScrollView::SetScrollSizes.
---------------------------------------------------------------------------*/
void QZoomView::SetZoomSizes (
	SIZE sizeTotal,
	const SIZE& sizePage, // in logical units
	const SIZE& sizeLine) // in logical units
{
	// Set up the defaults
	ASSERT(sizeTotal.cx >= 0 && sizeTotal.cy >= 0);
	m_nMapMode    = MM_ANISOTROPIC; // Need for arbitrary scaling
	m_totalLog    = sizeTotal;
	// Setup default Viewport extent to be conversion of Window extent
	// into device units.
	//BLOCK for DC
	{
		CClientDC dc(NULL);
		dc.SetMapMode(m_nMapMode);

		// total size
		m_totalDev = m_totalLog;
		dc.LPtoDP((LPPOINT)&m_totalDev);

		m_origVPSize=CSize(dc.GetDeviceCaps(LOGPIXELSX),
			dc.GetDeviceCaps(LOGPIXELSY));

		m_viewportSize=m_origVPSize;
	} // Release DC here
	
	// Save the origional Viewport Extent
	m_origTotalDev = m_totalDev;
	// Save the origional scrollbar info - for CalcBars
	m_origPageDev = sizePage;
	m_origLineDev = sizeLine;
	// Fugure out scroll bar info
	CalcBars();
	// Notify the class that the zoom scale was set
///	NotifyZoom();
} // SetZoomSizes

/*---------------------------------------------------------------------------
   FUNCTION: CalcBars
   PURPOSE : Update the scrollbars - uses logical units
				 Call when the Viewport changes size.
---------------------------------------------------------------------------*/
void QZoomView::CalcBars (void)
{
	{	// BLOCK for DC
		CClientDC dc(NULL);
		dc.SetMapMode(m_nMapMode);

		// Calculate new device units for scrollbar
		// Start with origional logical units from SetScrollPos
		m_pageDev = m_origPageDev;
		dc.LPtoDP((LPPOINT)&m_pageDev);
		m_lineDev = m_origLineDev;
		dc.LPtoDP((LPPOINT)&m_lineDev);
	} // Free DC

	// Make sure of the range
	if (m_pageDev.cy < 0)  m_pageDev.cy = -m_pageDev.cy;
	if (m_lineDev.cy < 0)  m_lineDev.cy = -m_lineDev.cy;

	// If none specified - use one tenth
	ASSERT(m_totalDev.cx >= 0 && m_totalDev.cy >= 0);
	if (m_pageDev.cx == 0) m_pageDev.cx = m_totalDev.cx / 10;
	if (m_pageDev.cy == 0) m_pageDev.cy = m_totalDev.cy / 10;
	if (m_lineDev.cx == 0) m_lineDev.cx = m_pageDev.cx  / 10;
	if (m_lineDev.cy == 0) m_lineDev.cy = m_pageDev.cy  / 10;

	// Now update the scrollbars
	if (m_hWnd != NULL) {
		UpdateBars();
		Invalidate(TRUE); // Zoom scale changed, redraw all
	}
} // CalcBars   

void QZoomView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo)
{
	CScrollView::OnPrepareDC(pDC, pInfo);

	if (!pDC->IsPrinting())
	{
		ASSERT(m_Zoom > 0.0f);

		int denom(1000);
		int num((int)(m_Zoom * (float)denom));

		// Added in version 1.1
		if (pDC->GetMapMode() == MM_TEXT)
		{
			// MM_TEXT has WindowExt and ViewportExt of (1 x 1),    
			// so ScaleViewportExt doesn't work properly.
			// We compensate by scaling both the WindowExt and ViewportExt.
			// (Thanks to Almut Branner)        MM_ANISOTROPIC
			pDC->SetMapMode(MM_ANISOTROPIC);
			pDC->ScaleWindowExt(denom, 1, denom, 1);
			num *= denom;
		}
		else pDC->SetMapMode(MM_ANISOTROPIC);


	pDC->SetWindowExt(96,-96);   // in logical coordinates     100,-100
		pDC->SetViewportExt(m_viewportSize); // in device  coordinates

		
		
		
		pDC->ScaleViewportExt(num, denom, num, denom);

		CRect rect;
		GetClientRect(&rect);

		CPoint pntVO = pDC->GetViewportOrg();

		// Center in window if small enough
		if (m_totalDev.cx < rect.Width())
			pntVO.x = (rect.Width() - m_totalDev.cx) / 2;
		if (m_totalDev.cy < rect.Height())
			pntVO.y = (rect.Height() - m_totalDev.cy) / 2;
		pDC->SetViewportOrg(pntVO);


		
		CPoint ptOrg;
		ptOrg.x=m_totalLog.cx/2;
		ptOrg.y=m_totalLog.cy/2;
		pDC->OffsetWindowOrg(-ptOrg.x, ptOrg.y);
	}
    else {
		// Special case for printing
	 	CSize  printSize;
		printSize.cx = pDC->GetDeviceCaps(LOGPIXELSX);
		printSize.cy = pDC->GetDeviceCaps(LOGPIXELSY);
		// Maintain the origional ratio, setup origin shift
		//PersistRatio(m_totalLog, printSize, ptVpOrg);
		// Zoom completely out
		pDC->SetViewportExt(printSize); 
		pDC->SetWindowOrg(-m_totalLog.cx/2, m_totalLog.cy/2);  
	}	
}

// Overrideable
// Called when zoom factor is changed, before window is redrawn. Default does nothing.
void QZoomView::OnZoom(float /*Zoom*/, float /*PreviousZoom*/)
{
}

/* static */
BOOL QZoomView::LoadCursor(CursorType type, UINT nResourceID, HINSTANCE hInst /* = NULL */)
{
	ASSERT(type >= 0 && type < 5);

	HCURSOR h(0);
	if (nResourceID)
	{
		if (hInst) h = ::LoadCursor(hInst, MAKEINTRESOURCE(nResourceID));
		else h = ::AfxGetApp()->LoadCursor(nResourceID);
	}

	m_Cursors[type] = h;

	return h != 0;
}

// QZoomView diagnostics

#ifdef _DEBUG
void QZoomView::AssertValid() const
{
	CScrollView::AssertValid();
}

void QZoomView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
	dc << _T("Zoom factor = ") << m_Zoom << _T("\n");
}
#endif //_DEBUG

// ==========================
// QZoomView::Dragger

int QZoomView::Dragger::OnMouseMessage(UINT msg, UINT nFlags, CPoint point)
{
	ASSERT_KINDOF(CView, m_pWnd);

	CSize szScroll = m_PreviousPoint - point;
	((CView *) m_pWnd)->OnScrollBy(szScroll);

	return QTracker::OnMouseMessage(msg, nFlags, point);
}

