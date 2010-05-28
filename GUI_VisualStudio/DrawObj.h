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
	DashStyle   m_LineStyle;				//�������
	COLORREF	m_clrFillColor;				//�����ɫ
	COLORREF	m_clrLineColor;				//������ɫ
	BOOL		m_bNoFill;					//�Ƿ����
	UINT		m_nLineSize;				//�����ߴ�

	//CFillPatternDlg
	COLORREF	m_clrBackColor;				//������ɫ

	BOOL			m_bIsGroup;					//�Ƿ�������
	BOOL			m_bIsUnit;					//�Ƿ����ڵ�Ԫ
	BOOL			m_bLock;					//�Ƿ�����

	CString			m_strGroupName;				//������
	CString			m_strUnitName;				//��Ԫ����
	UINT			m_nRoute;					//��ת�Ƕ�

	double      m_ID;
	UINT		m_nPointNo;					//�������
	COLORREF	m_TempFillColor;
	COLORREF	m_TempLineColor;

	ActionStruct	m_ActionStruct;
	double			m_nPercentFill;			//���ٷֱ�
	REFERENCEPOINT	m_RefPoint;				//�ο���
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
