/***********************************************************************************
说明:绘制曲线，多边形的类

***********************************************************************************/
#ifndef __DRAWPOLY_H__
#define __DRAWPOLY_H__


class CDrawView;
class CDrawDoc;
class CDrawPoly;
/////////////////////////////////////////////////////////////////////////////

class CDrawPoly : public CDrawObj
{
protected:
	DECLARE_SERIAL(CDrawPoly);
	CDrawPoly();

public:
	CDrawPoly(const CRect& position);

// Operations
///	void AddPoint(const CPoint& point, CDrawView* pView = NULL);
///	BOOL RecalcBounds(CDrawView* pView = NULL);

// Implementation
public:
	virtual ~CDrawPoly();
	virtual void Serialize(CArchive& ar);
	virtual void Draw(CDC* pDC);
///	virtual void MoveTo(const CRect& position, CDrawView* pView = NULL);
///	virtual int GetHandleCount();
///	virtual CPoint GetHandle(int nHandle);
///	virtual HCURSOR GetHandleCursor(int nHandle);
///	virtual void MoveHandleTo(int nHandle, CPoint point, CDrawView* pView = NULL);
///	virtual BOOL Intersects(const CRect& rect);
///	virtual CDrawObj* Clone(CDrawDoc* pDoc);
///	virtual void Invalidate();

	void DrawFill(CDC* pDc,Rect rc);
///	BOOL StartAction();
///	CPoint  GetLeftPoint();

public:
	int m_nPoints;
	int m_nAllocPoints;
	CPoint* m_points;
	CPoint* m_ActionPoints;
///	CDrawPoly* m_pDrawObj;
	enum Shape{poly,curve,conduit};
	Shape m_nShape;
///	CArray<POINT, POINT> m_CurvePoints;

///	UINT nTimerIDPoly;
	BOOL m_bIsActive;
	UINT m_nRoutePoly;
///	friend class CPolyTool;
};
#endif