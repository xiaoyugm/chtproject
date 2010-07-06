#if !defined(AFX_TABDOCKWND_H__DCF0AC13_476E_4353_B5C2_6D22016DBB1A__INCLUDED_)
#define AFX_TABDOCKWND_H__DCF0AC13_476E_4353_B5C2_6D22016DBB1A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TabDockWnd.h : header file
//

#include "TabTreeCtrl.h"

/////////////////////////////////////////////////////////////////////////////
// CTabDockWnd window

class CTabDockWnd : public CXTTabCtrlBar
{
// Construction
public:
	CTabDockWnd();

// Attributes
public:
	CTabTreeCtrl m_wndTreeCtrl;
	CImageList   m_imageList;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTabDockWnd)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CTabDockWnd();

	// Generated message map functions
protected:
	//{{AFX_MSG(CTabDockWnd)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TABDOCKWND_H__DCF0AC13_476E_4353_B5C2_6D22016DBB1A__INCLUDED_)
