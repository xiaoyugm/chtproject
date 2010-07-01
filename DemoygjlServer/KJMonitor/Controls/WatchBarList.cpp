// WatchBarList.cpp : implementation file
//

#include "stdafx.h"
#include "WatchBarList.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWatchBarList

CWatchBarList::CWatchBarList()
{
}

CWatchBarList::~CWatchBarList()
{
}


BEGIN_MESSAGE_MAP(CWatchBarList, CListCtrl)
	//{{AFX_MSG_MAP(CWatchBarList)
	ON_WM_WINDOWPOSCHANGED()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWatchBarList message handlers

void CWatchBarList::OnWindowPosChanged(WINDOWPOS FAR* lpwndpos) 
{
	CListCtrl::OnWindowPosChanged(lpwndpos);
	
    ShowScrollBar(SB_HORZ, FALSE);
    ModifyStyle(WS_HSCROLL, 0, SWP_DRAWFRAME);
}
