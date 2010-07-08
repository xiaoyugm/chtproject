// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__8A7FF552_6860_4D5B_86EA_DB6F25DB05A2__INCLUDED_)
#define AFX_MAINFRM_H__8A7FF552_6860_4D5B_86EA_DB6F25DB05A2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SqlDirect.h"
#include "SystemData.h"

#include "CurveDoc.h"

class CMainFrame : public CXTFrameWnd
{
	
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:
	CTypedPtrList<CObList,CCurveDoc *> m_docList;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

public:  // control bar embedded members
	CXTStatusBar     m_wndStatusBar;
//	CXTToolBar       m_wndToolBar;
	CSQLDirect		m_sql;		//Êý¾Ý¿â
	CMap <__int64,__int64,StructPoint,StructPoint>	m_PointMap;///modified by xizheng	
	void LoadPointInfo();
// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnFileLoad();
	afx_msg void OnMenuEditReport();
	afx_msg void OnGraphicProperty();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__8A7FF552_6860_4D5B_86EA_DB6F25DB05A2__INCLUDED_)
