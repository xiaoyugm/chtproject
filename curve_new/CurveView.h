// CurveView.h : interface of the CCurveView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CURVEVIEW_H__A2833FCC_77ED_4C2E_B838_D9FE8B3706AE__INCLUDED_)
#define AFX_CURVEVIEW_H__A2833FCC_77ED_4C2E_B838_D9FE8B3706AE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
///#include "CurveProp.h"
//#include "RtCurve.h"
class CCurveView : public CView
{
protected: // create from serialization only
	CCurveView();
	DECLARE_DYNCREATE(CCurveView)

// Attributes
public:
	CCurveDoc* GetDocument();
///	CRtCurve *m_pRtCurve;
	CDC         *m_MemDC;///modified by xizheng
	CBitmap		*m_MemBitmap;///modified by xizheng
	short		m_screenx;
	short		m_screeny;
	CRect		m_ClientRect;
	CPoint      m_OldPoint;
	CPoint		m_NewPoint;
	CPoint		m_LARGEPoint;

private:
	BOOL		m_bLButtonDown;
	BOOL		m_bCtrlButton;


// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCurveView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CCurveView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CCurveView)
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnGraphicProperty();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnGraphicRestore();
	afx_msg void OnGraphicExpend();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in CurveView.cpp
inline CCurveDoc* CCurveView::GetDocument()
   { return (CCurveDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CURVEVIEW_H__A2833FCC_77ED_4C2E_B838_D9FE8B3706AE__INCLUDED_)
