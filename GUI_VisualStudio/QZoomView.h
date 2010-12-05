#pragma once

// =======================
// QZoomView
//
// QZoomView is a CScrollView with zooming facilities.
// Use like you would use a CScrollView.
//
// QZoomView has four modes of operation:
//	- ZoomViewOff		QZoomView behaves like a normal CScrollView;
//	- ZoomViewZoomIn	clicking with the mouse zooms in, dragging zooms to rectangle;
//	- ZoomViewZoomOut	clicking zooms out, dragging is identical to ZoomViewZoomIn;
//	- ZoomViewDrag		if big enough, dragging scrolls the document.
// Switch modes with SetZoomMode(), retrieve the mode with GetZoomMode().
//
// In any mode, the mouse wheel with the Ctrl key pressed zooms the window.
// In one of the zoom modes, pressing the space bar temporarely switches to
// ZoomViewDrag mode.
//
// In any mode (even in ZoomViewOff), the zoom factor can explicitly be set with the
// ZoomTo() method.
// The zoom factor is a float between 0.05 and 20.0. 1.0 is neutral (100%).
// The zoom factor can be retrieved with GetZoom().
//
// A range of preset zoom factors is defined. You can zoom stepwise through this range by
// the member functions ZoomIn() and ZoomOut(). Use ZoomToPreset() to directly zoom
// to a preset value.
// CanZoomIn() and CanZoomOut() return a BOOL indicating whether zoom is possible.
// Modify the preset table with the SetPresets() method.
//
// The ZoomToWindow() member function lets the document fill the window.
//
// Like CScrollView, QZoomView is an abstract base class. You must derive another
// class from it and at least override OnDraw().
//
// QZoomView has one overrideable member function, OnZoom(). You may use this in derived
// classes. It is called after zoom is processed, but before the window is invalidated.
// The default does nothing.
//
// The static member functions LoadCursor() enables you to set the cursors QZoomView displays.
// It can be called before any instance of QZoomView is created. In default mode,
// QZoomView always displays the standard cursor.
//===============================
// Version 1.1, October 8, 2003
// Version 1.0, August 29, 2003
// (c) Sjaak Priester, Amsterdam
// www.sjaakpriester.nl
//
// Freeware. Use at your own risk. Comments welcome.

#include "QTracker.h"

class QZoomView : public CScrollView
{
// Construction
protected:
	QZoomView();           // protected constructor used by dynamic creation
	virtual ~QZoomView();

public:
// Initializing
	void SetZoomSizes(SIZE sizeTotal, const SIZE& sizePage = sizeDefault, const SIZE& sizeLine = sizeDefault);

	BOOL SetPresets(const float * pPresets, int count);
	// Initialize the list of preset zoom factors. If not initialized, QZoomView
	// uses a default list.
	// The preset zoom factors must be a list of increasing positive values
	// between 0.05f and 20.0f.
	// Return: TRUE if succeeded; FALSE if error, list not changed.

	enum CursorType
	{
		CursorLoupe,
		CursorLoupePlus,
		CursorLoupeMinus,
		CursorGripOpen,
		CursorGripClosed
	};
	static BOOL LoadCursor(CursorType type, UINT nResourceID, HINSTANCE hInst = NULL);
	static BOOL LoadCursor(int type, UINT nResourceID, HINSTANCE hInst = NULL)
			{ return LoadCursor((CursorType) type, nResourceID, hInst) ; }
	// Load the cursors QZoomView shows. All instances of QZoomView share the same
	// cursors, so loading is only needed once.

// Operation
	enum ZoomViewMode
	{
		ZoomViewOff,
		ZoomViewZoomIn,
		ZoomViewZoomOut,
		ZoomViewDrag
	};

	ZoomViewMode SetZoomMode(ZoomViewMode newMode)
				{ ZoomViewMode temp(m_Mode); m_Mode = newMode; return temp; }
	// Set the mode. Returns previous mode.

	ZoomViewMode GetZoomMode() const	{ return m_Mode; }
	// Get the current mode.

// Attributes

	float GetZoom() const				{ return m_Zoom; }
	// Get the current zoom factor.

	int GetPresetZoom() const			{ return m_PresetIndex; }
	// Get the current preset zoom. If -1, current zoom factor is not in the preset list.

	int GetPresetCount() const			{ return m_PresetCount; }
	// Get the number of available presets.

	CRect VisibleRect(void);
	// Get the visible rectangle in logical coordinates (added in v. 1.1).

// Methods

	float ZoomTo(float zoom);
	// Set the zoom factor. Returns previous zoom factor.
	// zoom may be any value between 0.05 and 20.0.

	void ZoomToPreset(int i, const LPPOINT pPoint = NULL);
	// Set the zoom factor to the i'th preset value.
	// If pPoint is not NULL, scrolls to pPoint (logical coordinates).

	void ZoomToRectangle(CRect rect);
	// Zoom to let rect conveniently fill the window. Logical coordinates.

	BOOL ZoomIn(const LPPOINT pPoint = NULL);
	BOOL CanZoomIn() const	{ return m_Presets && m_Zoom < m_Presets[m_PresetCount - 1]; }
	// Zoom In one step, if possible.
	// If pPoint is not NULL, scrolls to pPoint (logical coordinates).
	// Return: TRUE if zoomed, FALSE if end of range.

	BOOL ZoomOut(const LPPOINT pPoint = NULL);
	BOOL CanZoomOut() const	{ return m_Presets && m_Zoom > m_Presets[0]; }
	// Zoom Out one step, if possible.
	// If pPoint is not NULL, scrolls to pPoint (logical coordinates).
	// Return: TRUE if zoomed, FALSE if end of range.

	void ZoomToWindow(void);
	// Zoom to let the document conveniently fill the window.

	BOOL ScrollToCenter(CPoint point);
	// If possible, scroll point (logical coordinates) to the center of the window.
	// Return: TRUE if scrolled, FALSE if not.

	enum { NoBeep = 0xffff };
	UINT m_MessageBeep;
	// Set this value to the type of MessageBeep that QZoomView sounds to indicate the end
	// of zoom range. NoBeep to disable. Default is MB_ICONHAND.

	 void DoLButtonDown(UINT nFlags, CPoint point);
	 BOOL DoMouseWheel(UINT nFlags, short zDelta, CPoint pt);

protected:
// Overrideables
	virtual void OnZoom(float Zoom, float PreviousZoom);
	// Called when zoom factor is changed, before window is redrawn. Default does nothing.

// Implementation

	// Overrides
	virtual void OnDraw(CDC* pDC) = 0;
	virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL);

	// Message handlers
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);

	void SetCursor(void);

	float m_Zoom;
	int m_PresetIndex;
	ZoomViewMode m_Mode;
	int m_PresetCount;
	float *m_Presets;
	int m_WheelDelta;
	float     m_zoomScale;

	static float m_DefaultPresets[];
	static HCURSOR m_Cursors[5];

private:
	// Internally called functions
	void      CalcBars(void);
	CSize     m_origTotalDev;           // Origional total size in device units
	CSize     m_origPageDev;            // Origional per page scroll size in device units
	CSize     m_origLineDev;            // Origional per line scroll size in device units
	CSize	  m_origVPSize;				// Origional view portsize;
	CSize     m_viewportSize;

	DECLARE_DYNAMIC(QZoomView)
	DECLARE_MESSAGE_MAP()

// Diagnostics
#ifdef _DEBUG
public:
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Small helper class, based on my versatile QTracker class for tracking operations.
	class Dragger : public QTracker
	{
	public:
		Dragger(CView * pView) : QTracker(pView)		{ }
		int Track(CPoint point)		{ return QTracker::Track(NULL, 0, point, FALSE); }
	protected:
		virtual int OnMouseMessage(UINT msg, UINT nFlags, CPoint point);
	};
};
