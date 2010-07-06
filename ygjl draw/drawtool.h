// drawtool.h - interface for CDrawTool and derivatives
//
// This is a part of the Microsoft Foundation Classes C++ library.
// Copyright (c) Microsoft Corporation.  All rights reserved.
//
// This source code is only intended as a supplement to the
// Microsoft Foundation Classes Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding the
// Microsoft Foundation Classes product.


#ifndef __DRAWTOOL_H__
#define __DRAWTOOL_H__

#include "drawobj.h"
#include "drawrect.h"
#include "drawpoly.h"
#include "drawbutton.h"
#include "DrawChart.h"
#include "DrawWarn.h"
#include "DrawConduit.h"
#include "DrawCar.h"
#include "DrawRotary.h"
///#include "DrawHistory.h"

class CDrawView;

enum DrawShape
{
	selection,
	line,
	rect,
	rectNoFill,
	roundRect,
	roundRectNoFill,
	ellipse,
	ellipseNoFill,
	poly,
	polyNoFill,
	text,
	picture,
	hemicycle,
	hemicycleNoFill,
	button,
	image,
	arrow,
	curve,
	pie,
	pie45,
	conduit,						//¹ÜµÀ
	group,
	unit,
	warning,
	beeline,
	qie,
	chart,
	Hchart,
	warn,
	car,
	rotary,							//×ªÂÖ
	history

};

class CDrawTool
{
// Constructors
public:
	CDrawTool(DrawShape nDrawShape);

// Overridables
	virtual void OnLButtonDown(CDrawView* pView, UINT nFlags, const CPoint& point);
	virtual void OnLButtonDblClk(CDrawView* pView, UINT nFlags, const CPoint& point);
	virtual void OnLButtonUp(CDrawView* pView, UINT nFlags, const CPoint& point);
	virtual void OnMouseMove(CDrawView* pView, UINT nFlags, const CPoint& point);
	virtual void OnEditProperties(CDrawView* pView);
	virtual void OnCancel();

// Attributes
	DrawShape m_drawShape;

	static CDrawTool* FindTool(DrawShape drawShape);
	static CPtrList c_tools;
	static CPoint c_down;
	static UINT c_nDownFlags;
	static CPoint c_last;
	static DrawShape c_drawShape;
};

class CSelectTool : public CDrawTool
{
// Constructors
public:
	CSelectTool();

// Implementation
	virtual void OnLButtonDown(CDrawView* pView, UINT nFlags, const CPoint& point);
	virtual void OnLButtonDblClk(CDrawView* pView, UINT nFlags, const CPoint& point);
	virtual void OnLButtonUp(CDrawView* pView, UINT nFlags, const CPoint& point);
	virtual void OnMouseMove(CDrawView* pView, UINT nFlags, const CPoint& point);
	virtual void OnEditProperties(CDrawView* pView);
};

class CRectTool : public CDrawTool
{
// Constructors
public:
	CRectTool(DrawShape drawShape);
	CDrawRect* pObj;
// Implementation
	virtual void OnLButtonDown(CDrawView* pView, UINT nFlags, const CPoint& point);
	virtual void OnLButtonDblClk(CDrawView* pView, UINT nFlags, const CPoint& point);
	virtual void OnLButtonUp(CDrawView* pView, UINT nFlags, const CPoint& point);
	virtual void OnMouseMove(CDrawView* pView, UINT nFlags, const CPoint& point);
};

class CPolyTool : public CDrawTool
{
// Constructors
public:
	CPolyTool(DrawShape drawShape);

// Implementation
	virtual void OnLButtonDown(CDrawView* pView, UINT nFlags, const CPoint& point);
	virtual void OnLButtonDblClk(CDrawView* pView, UINT nFlags, const CPoint& point);
	virtual void OnLButtonUp(CDrawView* pView, UINT nFlags, const CPoint& point);
	virtual void OnMouseMove(CDrawView* pView, UINT nFlags, const CPoint& point);
	virtual void OnCancel();

	CDrawPoly* m_pDrawObj;
};

class CCurveTool : public CDrawTool
{
// Constructors
public:
	CCurveTool();

// Implementation
	virtual void OnLButtonDown(CDrawView* pView, UINT nFlags, const CPoint& point);
	virtual void OnLButtonDblClk(CDrawView* pView, UINT nFlags, const CPoint& point);
	virtual void OnLButtonUp(CDrawView* pView, UINT nFlags, const CPoint& point);
	virtual void OnMouseMove(CDrawView* pView, UINT nFlags, const CPoint& point);
	virtual void OnCancel();

	CDrawPoly* m_pDrawObj;
};
////////////////////////////////////////////////////////////////////////////
class CButtonTool : public CDrawTool
{
// Constructors
public:
	CButtonTool(DrawShape drawShape);

// Implementation
	virtual void OnLButtonDown(CDrawView* pView, UINT nFlags, const CPoint& point);
	virtual void OnLButtonDblClk(CDrawView* pView, UINT nFlags, const CPoint& point);
	virtual void OnLButtonUp(CDrawView* pView, UINT nFlags, const CPoint& point);
	virtual void OnMouseMove(CDrawView* pView, UINT nFlags, const CPoint& point);

	CDrawButton* m_pDrawObj;
};

class CChartTool : public CDrawTool
{
// Constructors
public:
	CChartTool(DrawShape drawShape);

// Implementation
	virtual void OnLButtonDown(CDrawView* pView, UINT nFlags, const CPoint& point);
	virtual void OnLButtonDblClk(CDrawView* pView, UINT nFlags, const CPoint& point);
	virtual void OnLButtonUp(CDrawView* pView, UINT nFlags, const CPoint& point);
	virtual void OnMouseMove(CDrawView* pView, UINT nFlags, const CPoint& point);

	CDrawChart* m_pDrawObj;
};
///////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////
class CWarnTool : public CDrawTool
{
// Constructors
public:
	CWarnTool(DrawShape drawShape);

// Implementation
	virtual void OnLButtonDown(CDrawView* pView, UINT nFlags, const CPoint& point);
	virtual void OnLButtonDblClk(CDrawView* pView, UINT nFlags, const CPoint& point);
	virtual void OnLButtonUp(CDrawView* pView, UINT nFlags, const CPoint& point);
	virtual void OnMouseMove(CDrawView* pView, UINT nFlags, const CPoint& point);

	CDrawWarn* m_pDrawObj;
};

class CConduitTool : public CDrawTool
{
// Constructors
public:
	CConduitTool(DrawShape drawShape);

// Implementation
	virtual void OnLButtonDown(CDrawView* pView, UINT nFlags, const CPoint& point);
	virtual void OnLButtonDblClk(CDrawView* pView, UINT nFlags, const CPoint& point);
	virtual void OnLButtonUp(CDrawView* pView, UINT nFlags, const CPoint& point);
	virtual void OnMouseMove(CDrawView* pView, UINT nFlags, const CPoint& point);
	virtual void OnCancel();

	CDrawConduit* m_pDrawObj;
};

class CCarTool : public CDrawTool
{
// Constructors
public:
	CCarTool(DrawShape drawShape);

// Implementation
	virtual void OnLButtonDown(CDrawView* pView, UINT nFlags, const CPoint& point);
	virtual void OnLButtonDblClk(CDrawView* pView, UINT nFlags, const CPoint& point);
	virtual void OnLButtonUp(CDrawView* pView, UINT nFlags, const CPoint& point);
	virtual void OnMouseMove(CDrawView* pView, UINT nFlags, const CPoint& point);

	CDrawCar* pCar;
};

class CRotaryTool : public CDrawTool
{
// Constructors
public:
	CRotaryTool(DrawShape drawShape);

// Implementation
	virtual void OnLButtonDown(CDrawView* pView, UINT nFlags, const CPoint& point);
	virtual void OnLButtonDblClk(CDrawView* pView, UINT nFlags, const CPoint& point);
	virtual void OnLButtonUp(CDrawView* pView, UINT nFlags, const CPoint& point);
	virtual void OnMouseMove(CDrawView* pView, UINT nFlags, const CPoint& point);

	CDrawRotary* pRotary;
};

#endif // __DRAWTOOL_H__
