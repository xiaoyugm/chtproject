#if !defined(AFX_TREECTRLFORFLATTAB_H__A4187D9D_6A07_468C_9B37_8600D5FD07C4__INCLUDED_)
#define AFX_TREECTRLFORFLATTAB_H__A4187D9D_6A07_468C_9B37_8600D5FD07C4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TreeCtrlForFlatTab.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTreeCtrlForFlatTab window

class CTreeCtrlForFlatTab : public CTreeCtrl
{
// Construction
public:
	CTreeCtrlForFlatTab();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTreeCtrlForFlatTab)
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CTreeCtrlForFlatTab();

	// Generated message map functions
protected:
	//{{AFX_MSG(CTreeCtrlForFlatTab)
	afx_msg void OnWindowPosChanged(WINDOWPOS FAR* lpwndpos);
	afx_msg void OnItemexpanded(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG

	void CommonInit();

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TREECTRLFORFLATTAB_H__A4187D9D_6A07_468C_9B37_8600D5FD07C4__INCLUDED_)
