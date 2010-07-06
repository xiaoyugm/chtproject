// TabTreeCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "Draw.h"
#include "TabTreeCtrl.h"
#include "drawview.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTabTreeCtrl

CTabTreeCtrl::CTabTreeCtrl()
{
}

CTabTreeCtrl::~CTabTreeCtrl()
{
}

BEGIN_MESSAGE_MAP(CTabTreeCtrl, CXTTreeCtrl)
	//{{AFX_MSG_MAP(CTabTreeCtrl)
	ON_WM_CREATE()
	ON_WM_LBUTTONDBLCLK()
	ON_NOTIFY_REFLECT(NM_DBLCLK, OnDblclk)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTabTreeCtrl message handlers

BOOL CTabTreeCtrl::PreCreateWindow(CREATESTRUCT& cs) 
{
	if ( !CXTTreeCtrl::PreCreateWindow( cs ) )
		return FALSE;

	// Set the style for the tree control.
	cs.style |= TVS_HASBUTTONS|TVS_HASLINES|TVS_LINESATROOT|TVS_EDITLABELS;

	// If non-xp mode, add a client edge border to the tree.
	if (!xtAfxData.bXPMode)
	{
		cs.dwExStyle |= WS_EX_CLIENTEDGE;
	}

	// TODO: Add your specialized code here and/or call the base class
	return TRUE;
}

int CTabTreeCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CXTTreeCtrl::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// Create the image list used by the tree control.
	if ( !m_imageList.Create( 16, 16, ILC_COLOR24 | ILC_MASK, 1, 1 ) )
	{
		TRACE0("Failed to create image list.\n");
		return -1;
	}

	// load the tree images bitmap and add it to the image list.
	m_bitmap.LoadBitmap( IDB_IMGLIST_VIEW );
	m_imageList.Add( &m_bitmap, RGB( 0x00,0xff,0x00 ) );

	// Set the image list for the tree control.
	SetImageList( &m_imageList, TVSIL_NORMAL );

	// Add the parent item
	htItem = InsertItem( _T( "项目导航" ) );
	SetItemState( htItem, TVIS_BOLD, TVIS_BOLD );

	htViewItem = InsertItem(_T("窗口"),1,1,htItem);

	Expand( htItem, TVE_EXPAND );
	
	return 0;
}

void CTabTreeCtrl::InsertViewName(CString strName, CDrawView *pView)
{
	HTREEITEM viewItem = InsertItem(strName,1,1,htViewItem);
	Expand( htViewItem, TVE_EXPAND );
	SelectItem(viewItem);
	m_map.SetAt(strName,pView);
	Invalidate();
}

void CTabTreeCtrl::DeleteViewName(CString strName)
{
	HTREEITEM delhtm = GetChildItem(htViewItem);
	while(delhtm != NULL)
	{
		CString temp = GetItemText(delhtm);
		if(temp == strName)
		{
			DeleteItem(delhtm);
			m_map.RemoveKey(strName);
			return;
		}
		delhtm = GetNextSiblingItem(delhtm);
	}
}

BOOL CTabTreeCtrl::IsSameName(CString strName)
{
	HTREEITEM htm = FindItem(strName);
	if(htm != NULL)
		return TRUE;
	else
		return FALSE;
}

void CTabTreeCtrl::OnDblclk(NMHDR* pNMHDR, LRESULT* pResult) 
{
	HTREEITEM htm = GetSelectedItem();
	CString temp= GetItemText(htm);

	CDrawView *pView;
	if(m_map.Lookup(temp,pView))
	{
		if(pView != NULL)
			pView->GetParentFrame()->ActivateFrame();
	}
	*pResult = 0;
}
