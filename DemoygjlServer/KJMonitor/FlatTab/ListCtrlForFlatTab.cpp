// ListCtrlForFlatTab.cpp : implementation file
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
#include "ListCtrlForFlatTab.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CListCtrlForFlatTab

CListCtrlForFlatTab::CListCtrlForFlatTab()
{
}

CListCtrlForFlatTab::~CListCtrlForFlatTab()
{
}


BEGIN_MESSAGE_MAP(CListCtrlForFlatTab, CListCtrl)
	//{{AFX_MSG_MAP(CListCtrlForFlatTab)
	ON_WM_WINDOWPOSCHANGED()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CListCtrlForFlatTab message handlers

void CListCtrlForFlatTab::OnWindowPosChanged(WINDOWPOS FAR* lpwndpos) 
{
	CListCtrl::OnWindowPosChanged(lpwndpos);
	
    ShowScrollBar(SB_HORZ, FALSE);
    ModifyStyle(WS_HSCROLL, 0, SWP_DRAWFRAME);
}
