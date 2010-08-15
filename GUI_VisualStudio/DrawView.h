// DrawView.h : interface of the CDrawView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DRAWVIEW_H__3A21925E_D712_4CB0_9E9C_EAC494327AF0__INCLUDED_)
#define AFX_DRAWVIEW_H__3A21925E_D712_4CB0_9E9C_EAC494327AF0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DrawDoc.h"
#include <String2DataType.h>
#include "MQClient.h"

// Hints for UpdateAllViews/OnUpdate
#define HINT_UPDATE_WINDOW      0
#define HINT_UPDATE_DRAWOBJ     1
#define HINT_UPDATE_SELECTION   2
#define HINT_DELETE_SELECTION   3
#define HINT_UPDATE_OLE_ITEMS   4
#define HINT_UPDATE_ROUTE		5
#define HINT_UPDATE_SIZE		6
#define HINT_UPDATE_MOVE		7
#define HINT_UPDATE_CAR  		8

class CDrawObj;
///class CDrawItem;

class CDrawView : public CScrollView
{
protected: // create from serialization only
	CDrawView();
	DECLARE_DYNCREATE(CDrawView)

// Attributes
public:
	CDrawDoc* GetDocument();
	// m_pSelection holds the selection to the current CDrawItem.
	// For many applications, such a member variable isn't adequate to
	//  represent a selection, such as a multiple selection or a selection
	//  of objects that are not CDrawItem objects.  This selection
	//  mechanism is provided just to help you get started.

	// TODO: replace this selection mechanism with one appropriate to your app.
///	CDrawItem* m_pSelection;
	BOOL  m_bIsDraw;

	CString2DataType m_Str2Data;
///    void   ConnectDB();
    CMQClient socketClient;

	void SetPageSize(CSize size);
	CRect GetInitialPosition();
// Operations
public:
	void DocToClient(CRect& rect);
	void DocToClient(CPoint& point);
	void ClientToDoc(CPoint& point);
	void ClientToDoc(CRect& rect);
///	void Select(CDrawObj* pObj, BOOL bAdd = FALSE);
///	void SelectGroup(CDrawObj* pObj);
///	void SelectWithinRect(CRect rect, BOOL bAdd = FALSE);
///	void Deselect(CDrawObj* pObj);
///	void CloneSelection();
	void UpdateActiveItem();
	void InvalObj(CDrawObj* pObj);
	void InvalRouteObj(CDrawObj* pObj);
	void InvalSizeObj(CDrawObj* pObj);
	void InvalMoveObj(CDrawObj* pObj);
	void InvalCarObj(CDrawObj* pObj);
	void Remove(CDrawObj* pObj);
///	void PasteNative(COleDataObject& dataObject);
///	void PasteEmbedded(COleDataObject& dataObject, CPoint point );

///	void DrawGrid(CDC* pDC);
///	void DrawHistoryLine();

public:
	BOOL m_bGrid;
	BOOL m_bDragDataAcceptable;

	CDrawObjList m_selection;
	COLORREF m_gridColor;
	BOOL m_bActive; // is the view active?

///	CDrawItem* pItemWarn;
	BOOL UpdataWarningExcel();
///	BOOL InitWarningExcel();

	POSITION	m_ViewPos ;
	UINT        CountView;
	UINT    	m_Second;


	virtual BOOL IsSelected(const CObject* pDocItem) const;// Container support
// Implementation

protected:
	// added for drop-target functionality
	COleDropTarget m_dropTarget;        // for drop target functionality
	CPoint m_dragPoint;                 // current position
	CSize m_dragSize;                   // size of dragged object
	CSize m_dragOffset;                 // offset between pt and drag object corner
	DROPEFFECT m_prevDropEffect;

	static CLIPFORMAT m_cfDraw; // custom clipboard format
	static CLIPFORMAT m_cfObjectDescriptor;

///    UINT Count ;
///	BOOL GetObjectInfo(COleDataObject* pDataObject,
///		CSize* pSize, CSize* pOffset);
	// end of drop-target additions
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDrawView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
//	virtual BOOL OnScrollBy(CSize sizeScroll, BOOL bDoScroll = TRUE);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDrawView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

public:
	afx_msg void OnTimeView();

// Generated message map functions
protected:
	//{{AFX_MSG(CDrawView)
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDblClk(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in DrawView.cpp
inline CDrawDoc* CDrawView::GetDocument()
   { return (CDrawDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DRAWVIEW_H__3A21925E_D712_4CB0_9E9C_EAC494327AF0__INCLUDED_)
