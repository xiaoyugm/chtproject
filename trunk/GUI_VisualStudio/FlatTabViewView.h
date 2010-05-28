// FlatTabViewView.h : interface of the CFlatTabViewView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_FLATTABVIEWVIEW_H__7573940C_6FB8_4142_A9F2_3693D044224E__INCLUDED_)
#define AFX_FLATTABVIEWVIEW_H__7573940C_6FB8_4142_A9F2_3693D044224E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//#include "ListCtrlForFlatTab.h"
//#include "EditCtrlForFlatTab.h"
//#include "TreeCtrlForFlatTab.h"
#define IDC_FLAT_TABCTRL                1001
#define IDC_SHEET7                      1009

class CFlatTabViewDoc;
class CXTFlatTabCtrl;
class CSampleFormView;
class CFlatTabViewView : public CView
{
protected: // create from serialization only
	CFlatTabViewView();
	DECLARE_DYNCREATE(CFlatTabViewView)

// Attributes
public:
	CFlatTabViewDoc* GetDocument();

// Operations
public:

	BOOL	m_FTS_XT_BOTTOM;
	BOOL	m_FTS_XT_HASARROWS;
	BOOL	m_FTS_XT_HASHOMEEND;
	BOOL	m_FTS_XT_HSCROLL;

    int   m_dwTabStyle;
    CRect m_rcTabs;

	CXTFlatTabCtrl*			m_pFlatTabCtrl;
    CSampleFormView*		m_pSheet;

	// use the flicker free template class, this will create the objects
	// making them flicker free!
//    CXTNoFlickerWnd <CListCtrlForFlatTab> m_sheet1;
//    CXTNoFlickerWnd <CEditCtrlForFlatTab> m_sheet2;
//    CXTNoFlickerWnd <CTreeCtrlForFlatTab> m_sheet3;
//    CXTNoFlickerWnd <CListBox>            m_sheet4;
//    CXTNoFlickerWnd <CListBox>            m_sheet5;
//    CXTNoFlickerWnd <CListBox>            m_sheet6;

    void CreateTabs();
    int CreateViews();
	void UpdateTabsStyle();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFlatTabViewView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CFlatTabViewView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CFlatTabViewView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

    void UpdateActiveView();

//	friend class CFlatTabPropDlg;
};

#ifndef _DEBUG  // debug version in FlatTabViewView.cpp
inline CFlatTabViewDoc* CFlatTabViewView::GetDocument()
   { return (CFlatTabViewDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FLATTABVIEWVIEW_H__7573940C_6FB8_4142_A9F2_3693D044224E__INCLUDED_)
