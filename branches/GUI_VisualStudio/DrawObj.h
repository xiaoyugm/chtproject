// drawobj.h - interface for CDrawObj and derivatives
//
// This is a part of the Microsoft Foundation Classes C++ library.
// Copyright (c) Microsoft Corporation.  All rights reserved.
//
// This source code is only intended as a supplement to the
// Microsoft Foundation Classes Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding the
// Microsoft Foundation Classes product.


#ifndef __DRAWOBJ_H__
#define __DRAWOBJ_H__


class CDrawView;
class CDrawDoc;

extern void Normallize(Rect &rect);
extern void Normallize(RectF &rect);

/////////////////////////////////////////////////////////////////////////////
// CDrawObj - base class for all 'drawable objects'

class CDrawObj : public CObject
{
protected:
	DECLARE_SERIAL(CDrawObj);
	CDrawObj();

// Constructors
public:
	CDrawObj(const CRect& position);

// Attributes
	CRect m_position;
	CDrawDoc* m_pDocument;

	virtual int GetHandleCount();
	virtual CPoint GetHandle(int nHandle);
	CRect GetHandleRect(int nHandleID, CDrawView* pView);
	virtual HCURSOR GetHandleCursor(int nHandle);
	virtual void SetLineColor(COLORREF color);
	virtual void SetFillColor(COLORREF color);
	virtual void SetFillStyle(HatchStyle FillStyle, COLORREF fkColor, COLORREF bkColor);

// Operations
	virtual void Draw(CDC* pDC);
	enum TrackerState { normal, selected, active };
	virtual void DrawTracker(CDC* pDC, TrackerState state);
	virtual void MoveTo(const CRect& positon, CDrawView* pView = NULL);
	virtual int HitTest(CPoint point, CDrawView* pView, BOOL bSelected);
	virtual BOOL Intersects(const CRect& rect);
	virtual void MoveHandleTo(int nHandle, CPoint point, CDrawView* pView = NULL);
	virtual void OnOpen(CDrawView* pView);
	virtual void OnEditProperties();
	virtual CDrawObj* Clone(CDrawDoc* pDoc = NULL);
	virtual void Remove();
	void Invalidate();
	void Invalidate(CRect rect);
	void Invalidate(CPoint pt);
	void Init();
	BOOL	Intersects(CRect rect, POINT, POINT);
	BOOL	PointOnLine(CPoint , POINT, POINT);

// Implementation
public:
	virtual ~CDrawObj();
	virtual void Serialize(CArchive& ar);
#ifdef _DEBUG
	void AssertValid();
#endif

	// implementation data
//protected:
public:
	//CLineProperty
	DashStyle   m_LineStyle;				//线条风格
	COLORREF	m_clrFillColor;				//填充颜色
	COLORREF	m_clrLineColor;				//线条颜色
	BOOL		m_bNoFill;					//是否填充
	UINT		m_nLineSize;				//线条尺寸

	//CFillPatternDlg
	COLORREF	m_clrBackColor;				//结束颜色

	BOOL			m_bIsGroup;					//是否属于组
	BOOL			m_bIsUnit;					//是否属于单元
	BOOL			m_bLock;					//是否锁定

	CString			m_strGroupName;				//组名称
	CString			m_strUnitName;				//单元名称
	UINT			m_nRoute;					//旋转角度

	double      m_ID;
	UINT		m_nPointNo;					//动作点号
	COLORREF	m_TempFillColor;
	COLORREF	m_TempLineColor;

	ActionStruct	m_ActionStruct;
	double			m_nPercentFill;			//填充百分比
	REFERENCEPOINT	m_RefPoint;				//参考点
	int			m_nMove;
	
	UINT		nTimerID;
	BOOL		bIsStartRay;
	BOOL		bIsTranPlus;
	CRect		m_rectAction;
	BOOL		m_bIsAction;
///	UINT		m_nActionRoute;
	int		m_nActionRoute;
	BOOL		m_bIsSwitch;

};

// special 'list' class for this application (requires afxtempl.h)
typedef CTypedPtrList<CObList, CDrawObj*> CDrawObjList;

/////////////////////////////////////////////////////////////////////////////////////////
/*
class CDrawItem;    // COleClientItem derived class

class CDrawOleObj : public CDrawObj
{
protected:
	DECLARE_SERIAL(CDrawOleObj);
	CDrawOleObj();

public:
	CDrawOleObj(const CRect& position);

// Implementation
public:
	virtual void Serialize(CArchive& ar);
	virtual void Draw(CDC* pDC);
///	virtual CDrawObj* Clone(CDrawDoc* pDoc);
///	virtual void OnOpen(CDrawView* pView);
///	virtual void MoveTo(const CRect& positon, CDrawView* pView = NULL);
///	virtual void OnEditProperties();
///	virtual void Remove();
	virtual ~CDrawOleObj();

	static BOOL c_bShowItems;


	CDrawItem* m_pClientItem;
	CSize m_extent; // current extent is tracked separate from scaled position
};
*/
#endif // __DRAWOBJ_H__
