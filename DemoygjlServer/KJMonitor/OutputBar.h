// OutputBar.h : header file
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_OUTPUTBAR_H__4B3132B9_56BC_408F_87A4_2FECB995E22E__INCLUDED_)
#define AFX_OUTPUTBAR_H__4B3132B9_56BC_408F_87A4_2FECB995E22E__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// COutputBar dock window class

#include "FlatTab\\ColorListBox.h"
#include "FlatTab\\OutputBarEdit.h"
#include "FlatTab\\ListCtrlForFlatTab.h"
#include "FlatTab\\EditCtrlForFlatTab.h"
#include "FlatTab\\TreeCtrlForFlatTab.h"

class COutputBar : public CXTDockWindow
{
	DECLARE_DYNAMIC(COutputBar)

// Construction / destruction
public:
	COutputBar();
	virtual ~COutputBar();

// Attributes
protected:

	CXTFlatTabCtrl	m_flatTabCtrl;
//	CXTListBox		m_sheet1;
//	CXTListBox		m_sheet2;
	CColorListBox		m_sheet1;
	CColorListBox		m_sheet2;
    CXTNoFlickerWnd <CListCtrlForFlatTab> m_sheet3;
    CXTNoFlickerWnd <CEditCtrlForFlatTab> m_sheet4;
    CXTNoFlickerWnd <CTreeCtrlForFlatTab> m_sheet5;
	CFont          m_sheetFont;
	UINT           m_NowCount ;
	UINT           m_HistoryCount ;

// Operations
public:
	BOOL CreateTabOutputWnd(COutputBarEdit& wndOutput, UINT nID);
	void AddDispWarnItem(int nWarnNormal, CString strItemText);
	int GetFlag(int nIndex);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COutputBar)
	//}}AFX_VIRTUAL

protected:
	//{{AFX_MSG(COutputBar)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OUTPUTBAR_H__4B3132B9_56BC_408F_87A4_2FECB995E22E__INCLUDED_)
