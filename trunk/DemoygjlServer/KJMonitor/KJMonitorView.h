// KJ86MonitorView.h : interface of the CKJ86MonitorView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_KJMONITORVIEW_H__4B4FC3F8_61E5_433C_82E0_2031F3671DA7__INCLUDED_)
#define AFX_KJMONITORVIEW_H__4B4FC3F8_61E5_433C_82E0_2031F3671DA7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CKJMonitorView : public CView
{
protected: // create from serialization only
	CKJMonitorView();
	DECLARE_DYNCREATE(CKJMonitorView)

// Attributes
public:
	CKJMonitorDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CKJ86MonitorView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CKJMonitorView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CKJ86MonitorView)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in KJ86MonitorView.cpp
inline CKJMonitorDoc* CKJMonitorView::GetDocument()
   { return (CKJMonitorDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_KJ86MONITORVIEW_H__4B4FC3F8_61E5_433C_82E0_2031F3671DA7__INCLUDED_)
