// TreeCtrlForFlatTab.cpp : implementation file
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

#include "stdafx.h"
#include "TreeCtrlForFlatTab.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTreeCtrlForFlatTab

CTreeCtrlForFlatTab::CTreeCtrlForFlatTab()
{
}

CTreeCtrlForFlatTab::~CTreeCtrlForFlatTab()
{
}


BEGIN_MESSAGE_MAP(CTreeCtrlForFlatTab, CTreeCtrl)
	//{{AFX_MSG_MAP(CTreeCtrlForFlatTab)
	ON_WM_WINDOWPOSCHANGED()
	ON_NOTIFY_REFLECT(TVN_ITEMEXPANDED, OnItemexpanded)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTreeCtrlForFlatTab message handlers

void CTreeCtrlForFlatTab::OnWindowPosChanged(WINDOWPOS FAR* lpwndpos) 
{
	// for the tree control, we'll call ShowScrollBar(SB_HORZ, FALSE) both
	// before and after CTreeCtrl::OnWindowPosChanged() - this seems to 
	// reduce flicker much more
	ShowScrollBar(SB_HORZ, FALSE);
	CTreeCtrl::OnWindowPosChanged(lpwndpos);
	ShowScrollBar(SB_HORZ, FALSE);
	ModifyStyle(WS_HSCROLL, 0, SWP_DRAWFRAME);
}

void CTreeCtrlForFlatTab::OnItemexpanded(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	
	// since the newly expanded / collapsed item could affect the horz.
	// scroll bar, we'll force a resync here
	((CXTFlatTabCtrl *)GetParent())->SyncScrollBar();

	*pResult = 0;
}

void CTreeCtrlForFlatTab::PreSubclassWindow() 
{
	CTreeCtrl::PreSubclassWindow();
	CommonInit();
}

int CTreeCtrlForFlatTab::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CTreeCtrl::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	CommonInit();
	
	return 0;
}

void CTreeCtrlForFlatTab::CommonInit()
{
	// make tooltips "top-most" so they don't get obscured by the flat tab
	// when floating in a dock bar
	CToolTipCtrl *pTTCtrl = 
#if _MSC_VER >= 1200  // VC6
		GetToolTips();
#else
		(CToolTipCtrl*)CWnd::FromHandle((HWND)::SendMessage(m_hWnd, TVM_GETTOOLTIPS, 0, 0L));
#endif

	if (pTTCtrl->GetSafeHwnd())
	{
		pTTCtrl->SetWindowPos(&CWnd::wndTopMost, 0, 0, 0, 0, 
			SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
	}
}
