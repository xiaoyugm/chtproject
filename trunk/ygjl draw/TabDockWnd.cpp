// TabDockWnd.cpp : implementation file
//

#include "stdafx.h"
#include "Draw.h"
#include "TabDockWnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTabDockWnd

CTabDockWnd::CTabDockWnd()
{
}

CTabDockWnd::~CTabDockWnd()
{
}

BEGIN_MESSAGE_MAP(CTabDockWnd, CXTTabCtrlBar)
	//{{AFX_MSG_MAP(CTabDockWnd)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTabDockWnd message handlers

int CTabDockWnd::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CXTTabCtrlBar::OnCreate(lpCreateStruct) == -1)
		return -1;
	
    // create the tree control.
    if (!m_wndTreeCtrl.Create( WS_VISIBLE | TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS | TVS_SHOWSELALWAYS,
        CRect(0,0,0,0), this, 0xFF ))
    {
        TRACE0( "Unable to create tree control.\n" );
        return -1;
    }
	
	// add the tree control to the tab docking bar.
	AddControl( _T( "µ¼º½Æ÷" ), &m_wndTreeCtrl, 0 );

	// Create the image list used with the tab control bar.
	if (!m_imageList.Create(IDB_IMGLIST_TAB, 16, 1, RGB(0x00,0xff,0x00)))
	{
		TRACE0("Failed to create image list.\n");
		return -1;
	}

	// Associate the image list with the tab control bar.
	SetTabImageList(&m_imageList);

	return 0;
}
