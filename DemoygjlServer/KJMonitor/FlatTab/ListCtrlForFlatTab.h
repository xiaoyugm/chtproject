// ListCtrlForFlatTab.h : header file
//
// This file is a part of the Xtreme Toolkit for MFC.
// ©1998-2003 Codejock Software, All Rights Reserved.
//
// This source code can only be used under the terms and conditions
// outlined in the accompanying license agreement.
//
// support@codejock.com
// http://www.codejock.com
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LISTCTRLFORFLATTAB_H__065C7848_BDB9_4599_A81B_81F15E9A23E6__INCLUDED_)
#define AFX_LISTCTRLFORFLATTAB_H__065C7848_BDB9_4599_A81B_81F15E9A23E6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CListCtrlForFlatTab window

class CListCtrlForFlatTab : public CListCtrl
{
// Construction
public:
	CListCtrlForFlatTab();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CListCtrlForFlatTab)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CListCtrlForFlatTab();

	// Generated message map functions
protected:
	//{{AFX_MSG(CListCtrlForFlatTab)
	afx_msg void OnWindowPosChanged(WINDOWPOS FAR* lpwndpos);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LISTCTRLFORFLATTAB_H__065C7848_BDB9_4599_A81B_81F15E9A23E6__INCLUDED_)
