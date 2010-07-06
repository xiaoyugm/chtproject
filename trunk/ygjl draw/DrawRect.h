/*****************************************************************************
绘制RECT图形的类
说明：包括矩形，圆角矩形，圆，
*****************************************************************************/

#ifndef __DRAWRECT_H__
#define __DRAWRECT_H__

#include "Enum.h"

class CDrawView;
class CDrawDoc;

////////////////////////////////////////////////////////////////////////
// specialized draw objects

class CDrawRect : public CDrawObj
{
protected:
	DECLARE_SERIAL(CDrawRect);
	CDrawRect();
	~CDrawRect();

public:
	CDrawRect(const CRect& position);

// Implementation
public:
	virtual void Serialize(CArchive& ar);
	virtual void Draw(CDC* pDC);
	virtual int GetHandleCount();
	virtual CPoint GetHandle(int nHandle);
	virtual HCURSOR GetHandleCursor(int nHandle);
	virtual void MoveHandleTo(int nHandle, CPoint point, CDrawView* pView = NULL);
	virtual BOOL Intersects(const CRect& rect);
	virtual CDrawObj* Clone(CDrawDoc* pDoc);
	virtual void Remove();
	virtual void Invalidate();

	void DrawFill(CDC* pDc,Rect rc);


	UINT	ActionRes;
	UINT	ActionId;
	BOOL	bStart;
	BOOL	bplus;
//protected:
	enum Shape { rectangle, 
				 rectNoFill, 
				 roundRectangle, 
				 roundrectNoFill, 
				 ellipse ,
				 ellipseNoFill, 
				 line,
				 arrow,
				 pie,
				 pie45,
				 button,
				 group,
				 unit,
				 warning,
				 beeline,
				 qie
				};
	Shape m_nShape;
	CPoint m_roundness; // for roundRect corners
///	int m_nDrawTrans;

	int  m_nstartAngle;
	int  m_nsweepAngle;
	int  m_npie, m_npie45;
	int  m_nRoute;
	friend class CRectTool;
};

#endif