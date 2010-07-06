// DrawView.h : interface of the CDrawView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DRAWVIEW_H__3A21925E_D712_4CB0_9E9C_EAC494327AF0__INCLUDED_)
#define AFX_DRAWVIEW_H__3A21925E_D712_4CB0_9E9C_EAC494327AF0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DrawDoc.h"
#include "drawobj.h"

// Hints for UpdateAllViews/OnUpdate
#define HINT_UPDATE_WINDOW      0
#define HINT_UPDATE_DRAWOBJ     1
#define HINT_UPDATE_SELECTION   2
#define HINT_DELETE_SELECTION   3
#define HINT_UPDATE_OLE_ITEMS   4
#define HINT_UPDATE_ROUTE		5


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

	void SetPageSize(CSize size);
	CRect GetInitialPosition();
// Operations
public:
	void DocToClient(CRect& rect);
	void DocToClient(CPoint& point);
	void ClientToDoc(CPoint& point);
	void ClientToDoc(CRect& rect);
	void Select(CDrawObj* pObj, BOOL bAdd = FALSE);
	void SelectGroup(CDrawObj* pObj);
	void SelectUnit(CDrawObj* pObj);
	void SelectWithinRect(CRect rect, BOOL bAdd = FALSE);
	void Deselect(CDrawObj* pObj);
	void CloneSelection();
	void UpdateActiveItem();

	void InvalObj(CDrawObj* pObj);
	void InvalRouteObj(CDrawObj* pObj);
	void InvalMoveObj(CDrawObj* pObj);   //0413

	void Remove(CDrawObj* pObj);
	void PasteNative(COleDataObject& dataObject);
///	void PasteEmbedded(COleDataObject& dataObject, CPoint point );

	void DrawGrid(CDC* pDC);
	void SetGroupProperty(CString strName, double Height, double Width, CRect oldRect);
	void SetUnitProperty(CString strName, double Height, double Width, CRect oldRect);

public:
	CDrawObjList m_selection;
	BOOL m_bGrid;
	COLORREF m_gridColor;
	BOOL m_bActive; // is the view active?
	BOOL bLock;

	BOOL  m_bIsDraw;

	virtual BOOL IsSelected(const CObject* pDocItem) const;// Container support
// Implementation

protected:
	// added for drop-target functionality
	COleDropTarget m_dropTarget;        // for drop target functionality
	CPoint m_dragPoint;                 // current position
	CSize m_dragSize;                   // size of dragged object
	CSize m_dragOffset;                 // offset between pt and drag object corner
	DROPEFFECT m_prevDropEffect;
	BOOL m_bDragDataAcceptable;

	static CLIPFORMAT m_cfDraw; // custom clipboard format
	static CLIPFORMAT m_cfObjectDescriptor;

	BOOL GetObjectInfo(COleDataObject* pDataObject,
		CSize* pSize, CSize* pOffset);
	// end of drop-target additions
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDrawView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL);
	virtual DROPEFFECT OnDragEnter(COleDataObject* pDataObject, DWORD dwKeyState, CPoint point);
	virtual void OnDragLeave();
	virtual DROPEFFECT OnDragOver(COleDataObject* pDataObject, DWORD dwKeyState, CPoint point);
	virtual BOOL OnDrop(COleDataObject* pDataObject, DROPEFFECT dropEffect, CPoint point);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
	virtual BOOL OnScrollBy(CSize sizeScroll, BOOL bDoScroll = TRUE);
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

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CDrawView)
	afx_msg void OnCancelEdit();
	afx_msg void OnDestroy();
///	afx_msg void OnSetFocus(CWnd* pOldWnd);
///	afx_msg void OnSize(UINT nType, int cx, int cy);
///	afx_msg void OnCancelEditCntr();
///	afx_msg void OnCancelEditSrvr();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnObjectLineColor();
	afx_msg void OnObjectFillColor();
	afx_msg void OnObjectMoveForward();
	afx_msg void OnObjectMoveBack();
	afx_msg void OnUpdateSingleSelect(CCmdUI* pCmdUI);
	afx_msg void OnEditSelectAll();
	afx_msg void OnEditClear();
	afx_msg void OnEditCopy();
	afx_msg void OnEditCut();
	afx_msg void OnEditPaste();
	afx_msg void OnUpdateEditCopy(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditCut(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditPaste(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditSelectAll(CCmdUI* pCmdUI);
	afx_msg void OnUpdateAnySelect(CCmdUI* pCmdUI);
	afx_msg void OnViewGrid();
	afx_msg void OnUpdateViewGrid(CCmdUI* pCmdUI);
///	afx_msg void OnViewShowobjects();
///	afx_msg void OnUpdateViewShowobjects(CCmdUI* pCmdUI);
	afx_msg void OnDrawSelect();
	afx_msg void OnDrawRoundRect();
	afx_msg void OnDrawRect();
	afx_msg void OnDrawLine();
	afx_msg void OnDrawEllipse();
	afx_msg void OnUpdateDrawEllipse(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDrawLine(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDrawRect(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDrawRoundRect(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDrawSelect(CCmdUI* pCmdUI);
	afx_msg void OnDrawPolygon();
	afx_msg void OnUpdateDrawPolygon(CCmdUI* pCmdUI);
	afx_msg void OnToolboxrectangle();
	afx_msg void OnUpdateToolboxrectangle(CCmdUI* pCmdUI);
	afx_msg void OnToolboxoval();
	afx_msg void OnUpdateToolboxoval(CCmdUI* pCmdUI);
	afx_msg void OnToolboxpolygon();
	afx_msg void OnUpdateToolboxpolygon(CCmdUI* pCmdUI);
	afx_msg void OnToolboxbitmap();
	afx_msg void OnToolboxbutton();
	afx_msg void OnUpdateToolboxbutton(CCmdUI* pCmdUI);
	afx_msg void OnToolboxtext();
	afx_msg void OnUpdateToolboxtext(CCmdUI* pCmdUI);
	afx_msg void OnToolboxwarn();
	afx_msg void OnToolboxRoundrectNofill();
	afx_msg void OnUpdateToolboxRoundrectNofill(CCmdUI* pCmdUI);
	afx_msg void OnToolboxArrow();
	afx_msg void OnUpdateToolboxArrow(CCmdUI* pCmdUI);
	afx_msg void OnDrawCurve();
	afx_msg void OnUpdateDrawCurve(CCmdUI* pCmdUI);
	afx_msg void OnToolboxchord();
	afx_msg void OnUpdateToolboxchord(CCmdUI* pCmdUI);
	afx_msg void OnToolboxpie();
	afx_msg void OnUpdateToolboxpie(CCmdUI* pCmdUI);
	afx_msg void OnToolboxConduit();
	afx_msg void OnUpdateToolboxConduit(CCmdUI* pCmdUI);
	afx_msg void OnUnitSave();
	afx_msg void OnUpdateUnitSave(CCmdUI* pCmdUI);
	afx_msg void OnObjectLoadsub();
	afx_msg void OnFormattingBold();
	afx_msg void OnFormattingItalic();
	afx_msg void OnFormattingUnderline();
	afx_msg void OnToolboxreport();
	afx_msg void OnUpdateToolboxreport(CCmdUI* pCmdUI);
	afx_msg void OnToolboxBeeline();
	afx_msg void OnUpdateToolboxBeeline(CCmdUI* pCmdUI);
	afx_msg void OnToolboxQie();
	afx_msg void OnUpdateToolboxQie(CCmdUI* pCmdUI);
	afx_msg void OnPupupLock();
	afx_msg void OnUpdatePupupLock(CCmdUI* pCmdUI);
	afx_msg void OnToolboxTimeCurve();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPopupAction();
	afx_msg void OnUpdatePopupAction(CCmdUI* pCmdUI);
	afx_msg void OnToolboxstroke();
	afx_msg void OnInsertCar();
	afx_msg void OnInsertRotary();
	afx_msg void OnUpdateToolboxbitmap(CCmdUI* pCmdUI);
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
