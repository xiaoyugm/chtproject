#if !defined(AFX_TABTREECTRL_H__926195AF_55DF_495B_B5A9_CE508814A7FD__INCLUDED_)
#define AFX_TABTREECTRL_H__926195AF_55DF_495B_B5A9_CE508814A7FD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TabTreeCtrl.h : header file
//
#include "drawview.h"
/////////////////////////////////////////////////////////////////////////////
// CTabTreeCtrl window

class CTabTreeCtrl : public CXTTreeCtrl
{
// Construction
public:
	CTabTreeCtrl();

// Attributes
protected:
	CImageList	m_imageList;
	CBitmap     m_bitmap;
	HTREEITEM htItem;
	HTREEITEM htViewItem;

// Operations
public:

	void InsertViewName(CString strName, CDrawView *pView);
	void DeleteViewName(CString strName);
	BOOL IsSameName(CString strName);
	CTypedPtrMap<CMapStringToOb,CString,CDrawView *> m_map;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTabTreeCtrl)
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL
// Implementation
public:
	virtual ~CTabTreeCtrl();

	// Generated message map functions
protected:
	//{{AFX_MSG(CTabTreeCtrl)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDblclk(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TABTREECTRL_H__926195AF_55DF_495B_B5A9_CE508814A7FD__INCLUDED_)
