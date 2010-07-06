//绘图函数基类
//
//
#ifndef __DRAWOBJ_H__
#define __DRAWOBJ_H__

#include "Enum.h"

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

	virtual int		GetHandleCount();
	virtual CPoint	GetHandle(int nHandle);
	CRect			GetHandleRect(int nHandleID, CDrawView* pView);
	virtual HCURSOR GetHandleCursor(int nHandle);
	virtual void	SetLineColor(COLORREF color);
	virtual void	SetFillColor(COLORREF color);
	virtual void	SetFillStyle(HatchStyle FillStyle, COLORREF fkColor, COLORREF bkColor);

// Operations
	enum TrackerState { normal, selected, active };  //0413
	virtual void	Draw(CDC* pDC);
	virtual void	DrawTracker(CDC* pDC, TrackerState state);
	virtual void	MoveTo(const CRect& positon, CDrawView* pView = NULL);
	virtual int		HitTest(CPoint point, CDrawView* pView, BOOL bSelected);
	virtual BOOL	Intersects(const CRect& rect);
	virtual void	MoveHandleTo(int nHandle, CPoint point, CDrawView* pView = NULL);
	virtual void	OnOpen(CDrawView* pView);
	virtual void	OnEditProperties();
	virtual CDrawObj* Clone(CDrawDoc* pDoc = NULL);
	virtual void	Remove();
	void			Invalidate();
	BOOL			Intersects(CRect rect, POINT, POINT);
	BOOL			PointOnLine(CPoint , POINT, POINT);
///	void    AddCarRect(CRect rc);

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
	DashStyle		m_LineStyle;				//线条风格
	COLORREF		m_clrFillColor;				//填充颜色
	COLORREF		m_clrLineColor;				//线条颜色
	BOOL			m_bNoFill;					//是否填充
	UINT			m_nLineSize;				//线条尺寸

	//CFillPatternDlg
	COLORREF		m_clrBackColor;				//结束颜色

	BOOL			m_bIsGroup;					//是否属于组
	BOOL			m_bIsUnit;					//是否属于单元
	BOOL			m_bLock;					//是否锁定

	CString			m_strGroupName;				//组名称
	CString			m_strUnitName;				//单元名称
	UINT			m_nRoute;					//旋转角度

	double			m_ID;

	UINT			m_nPointNo;					//动作点号

	ActionStruct	m_ActionStruct;				//动作结构
};

// special 'list' class for this application (requires afxtempl.h)
typedef CTypedPtrList<CObList, CDrawObj*> CDrawObjList;

/////////////////////////////////////////////////////////////////////////////////////////

#endif // __DRAWOBJ_H__
