//��ͼ��������
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
	DashStyle		m_LineStyle;				//�������
	COLORREF		m_clrFillColor;				//�����ɫ
	COLORREF		m_clrLineColor;				//������ɫ
	BOOL			m_bNoFill;					//�Ƿ����
	UINT			m_nLineSize;				//�����ߴ�

	//CFillPatternDlg
	COLORREF		m_clrBackColor;				//������ɫ

	BOOL			m_bIsGroup;					//�Ƿ�������
	BOOL			m_bIsUnit;					//�Ƿ����ڵ�Ԫ
	BOOL			m_bLock;					//�Ƿ�����

	CString			m_strGroupName;				//������
	CString			m_strUnitName;				//��Ԫ����
	UINT			m_nRoute;					//��ת�Ƕ�

	double			m_ID;

	UINT			m_nPointNo;					//�������

	ActionStruct	m_ActionStruct;				//�����ṹ
};

// special 'list' class for this application (requires afxtempl.h)
typedef CTypedPtrList<CObList, CDrawObj*> CDrawObjList;

/////////////////////////////////////////////////////////////////////////////////////////

#endif // __DRAWOBJ_H__
