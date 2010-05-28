// ResourceViewPane.cpp : implementation file
//
// This file is a part of the XTREME TOOLKIT PRO MFC class library.
// (c)1998-2009 Codejock Software, All Rights Reserved.
//
// THIS SOURCE FILE IS THE PROPERTY OF CODEJOCK SOFTWARE AND IS NOT TO BE
// RE-DISTRIBUTED BY ANY MEANS WHATSOEVER WITHOUT THE EXPRESSED WRITTEN
// CONSENT OF CODEJOCK SOFTWARE.
//
// THIS SOURCE CODE CAN ONLY BE USED UNDER THE TERMS AND CONDITIONS OUTLINED
// IN THE XTREME TOOLKIT PRO LICENSE AGREEMENT. CODEJOCK SOFTWARE GRANTS TO
// YOU (ONE SOFTWARE DEVELOPER) THE LIMITED RIGHT TO USE THIS SOFTWARE ON A
// SINGLE COMPUTER.
//
// CONTACT INFORMATION:
// support@codejock.com
// http://www.codejock.com
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "GUI_VisualStudio.h"
#include "ResourceViewPane.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CStrWarn m_CStrWarn[MAX_ROW];
/////////////////////////////////////////////////////////////////////////////
// CResourceViewPane

CResourceViewPane::CResourceViewPane()
{
}

CResourceViewPane::~CResourceViewPane()
{
}


BEGIN_MESSAGE_MAP(CResourceViewPane, CWnd)
	//{{AFX_MSG_MAP(CResourceViewPane)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_NCHITTEST()
	//}}AFX_MSG_MAP
	ON_WM_SETFOCUS()
END_MESSAGE_MAP()

static int arColWidths[] = {
	160,
	50,
	100,
	120,
	120,
	120,
	360
};

static CString arColLabels[] = {
	_T("安装地点/名称"),
	_T("监测值"),
	_T("报警时刻"),
	_T("断电时刻"),
	_T("复电时刻"),
	_T("馈电状态及时刻"),
	_T("安全措施")
};
/*
设备故障记录
static CString arColLabels[] = {
	_T("安装地点/名称"),
	_T("故障状态"),
	_T("故障时间"),
	_T("安全措施及处理时刻")
};

开关量状态变动显示
static CString arColLabels[] = {
	_T("安装地点/名称"),
	_T("断电/报警时刻"),
	_T("设备状态"),
	_T("设备状态时刻"),
	_T("断电时刻"),
	_T("报警时刻"),
	_T("断电区域"),
	_T("馈电状态及时刻")
};
模拟量调用显示
static CString arColLabels[] = {
	_T("安装地点/名称"),
	_T("监测值"),
	_T("单位"),
	_T("报警门限"),
	_T("断电门限"),
	_T("复电门限"),
	_T("最后一次统计的最大值")
	_T("平均值"),
	_T("最后一次报警时刻"),
	_T("最后一次解除报警时刻"),
	_T("最后一次断电时刻"),
	_T("最后一次复电时刻")
};
开关量调用显示
static CString arColLabels[] = {
	_T("安装地点/名称"),
	_T("设备状态/时刻"),
	_T("断电/报警状态"),
	_T("断电/报警及时刻"),
	_T("断电区域"),
	_T("安全措施及处理时刻")
};
*/

//设备状态   
/////////////////////////////////////////////////////////////////////////////
// CResourceViewPane message handlers

int CResourceViewPane::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

//	SetWindowLong(m_hWnd, GWL_STYLE, GetWindowLong(m_hWnd, GWL_STYLE) & ~WS_THICKFRAME);

	// Define the default style for the output list controls.
	DWORD dwStyle = LVS_REPORT | LVS_NOSORTHEADER | LVS_SHOWSELALWAYS |
		WS_CHILD | WS_VSCROLL | WS_TABSTOP|WS_VISIBLE;

	// Create the list control.
	if (!m_listCtrl.Create( dwStyle, CRect(3,0,1022,200), this, 0xff ))
	{
		TRACE0( "Failed to create list control.\n" );
		return FALSE;
	}

	// initialize the list control.
	InitListControl();

/*	if (m_wndResourceView.GetSafeHwnd() == 0)
	{
		if (!m_wndResourceView.Create( WS_VISIBLE | TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS | TVS_SHOWSELALWAYS,
			CRect(0,0,0,0), this, 0xFF ))
		{
			TRACE0( "Unable to create tree control.\n" );
			return 0;
		}
		m_wndResourceView.ModifyStyleEx(0, WS_EX_STATICEDGE);

		// load the tree images bitmap and add it to the image list.
		if (!CreateImageList(m_ilResourceView, IDB_RESTREE))
			return 0;

		// Set the image list for the tree control.
		m_wndResourceView.SetImageList( &m_ilResourceView, TVSIL_NORMAL );

		// add the parent item
		HTREEITEM htItem = m_wndResourceView.InsertItem(_T("XtremeDemo resources"), 0, 1);
		m_wndResourceView.SetItemState(htItem, TVIS_BOLD, TVIS_BOLD);

		HTREEITEM hti = m_wndResourceView.InsertItem(_T("Accelerator"), 0, 1, htItem);
		m_wndResourceView.InsertItem(_T("IDR_MAINFRAME"), 2, 2, hti);
		m_wndResourceView.Expand(hti, TVE_EXPAND);

		hti = m_wndResourceView.InsertItem(_T("Dialog"), 0, 1, htItem);
		m_wndResourceView.InsertItem(_T("IDD_ABOUTBOX"), 3, 3, hti);
		m_wndResourceView.Expand(hti, TVE_EXPAND);

		hti = m_wndResourceView.InsertItem(_T("Icon"), 0, 1, htItem);
		m_wndResourceView.InsertItem(_T("IDR_MAINFRAME"), 4, 4, hti);
		m_wndResourceView.InsertItem(_T("IDR_XTREMETYPE"), 4, 4, hti);
		m_wndResourceView.Expand(hti, TVE_EXPAND);

		hti = m_wndResourceView.InsertItem(_T("Menu"), 0, 1, htItem);
		m_wndResourceView.InsertItem(_T("IDR_MAINFRAME"), 5, 5, hti);
		m_wndResourceView.InsertItem(_T("IDR_XTREMETYPE"), 5, 5, hti);

		hti = m_wndResourceView.InsertItem(_T("String Table"), 0, 1, htItem);
		m_wndResourceView.InsertItem(_T("String Table"), 6, 6, hti);

		hti = m_wndResourceView.InsertItem(_T("Toolbar"), 0, 1, htItem);
		m_wndResourceView.InsertItem(_T("IDR_MAINFRAME"), 7, 7, hti);

		hti = m_wndResourceView.InsertItem(_T("Version"), 0, 1, htItem);
		m_wndResourceView.InsertItem(_T("VS_VERSION_INFO"), 8, 8, hti);

		m_wndResourceView.Expand (htItem, TVE_EXPAND);
	}*/

	return 0;
}

LRESULT CResourceViewPane::OnNcHitTest(CPoint point)
{
	if (CWnd::OnNcHitTest(point) == HTRIGHT || CWnd::OnNcHitTest(point) == HTLEFT 
		|| CWnd::OnNcHitTest(point) == HTTOP || CWnd::OnNcHitTest(point) == HTBOTTOM)
	return HTCLIENT;
	return CWnd::OnNcHitTest(point);
}

/*
BOOL CResourceViewPane::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	if( !CWnd::PreCreateWindow(cs) )
		return FALSE;

//	cs.style |= WS_CLIPCHILDREN;
	
//	cs.style = WS_CHILD | WS_VISIBLE //| WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU
//		| FWS_ADDTOTITLE | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX 
//    ;

//	cs.style   &=~   (LONG)   FWS_PREFIXTITLE;
//	cs.style &= ~WS_MAXIMIZEBOX;
//	cs.style &= ~WS_THICKFRAME;
//   cs.style   &=~WS_VSCROLL;     FWS_ADDTOTITLE


cs.style = WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX;// | WS_THICKFRAME;
cs.style &= ~WS_BORDER;
cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
int iWinBorderX = GetSystemMetrics(SM_CXBORDER);
int iWinBorderY = GetSystemMetrics(SM_CYBORDER);
int iCaptionY = GetSystemMetrics(SM_CYCAPTION);
int iMenuY = GetSystemMetrics(SM_CYMENU);
int iStausY = GetSystemMetrics(SM_CYMENU);
cs.cx = 510 + iWinBorderX ;
cs.cy = 530 + iWinBorderY + iCaptionY + iStausY + iMenuY;

	return TRUE;
}
*/


void CResourceViewPane::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);

//	if (m_wndResourceView.GetSafeHwnd())
	{
//		m_wndResourceView.MoveWindow(0, 0, 200, 200);
	}
//		m_wndSolutionView.MoveWindow(0, nTop, cx, cy - nTop);
	m_listCtrl.MoveWindow(0, 0, cx, 170);
}

void CResourceViewPane::OnSetFocus(CWnd* /*pOldWnd*/)
{
//	m_wndResourceView.SetFocus();
	InitLC();
	m_listCtrl.SetFocus();
}

void CResourceViewPane::InitListControl()
{
	// Insert the columns.
	m_listCtrl.BuildColumns(_countof(arColWidths), arColWidths, arColLabels);

	// Subclass the flat header control.
	m_listCtrl.SubclassHeader();

	// lock the first two colums from sizing operations.
	CXTFlatHeaderCtrl* pHeaderCtrl = m_listCtrl.GetFlatHeaderCtrl( );
	if ( pHeaderCtrl != NULL )
	{
//		pHeaderCtrl->FreezeColumn(0);
//		pHeaderCtrl->FreezeColumn(1);
//		pHeaderCtrl->FreezeColumn(2);
		// enable autosizing for columns.
		pHeaderCtrl->EnableAutoSize();

//		pHeaderCtrl->SetBitmap(2, IDB_HEADER, HDF_STRING);
	}

	ListView_SetExtendedListViewStyle(
		m_listCtrl.m_hWnd, LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT );

	m_listCtrl.EnableUserSortColor(true);
	m_listCtrl.EnableUserListColor(true);
	m_listCtrl.EnableUserRowColor(true);

    for(int i=0;i<MAX_ROW;i++)
	{
    	m_listCtrl.InsertItem(i, NULL, 0);
    	m_listCtrl.SetItemText(i, 3, _T(""));
        m_listCtrl.SetRowColor(i, RGB(255,0,0), RGB(255,255,255));
	}
}

void CResourceViewPane::InitLC()
{
	for(int i =0; i<MAX_ROW; i++)
	{
		m_listCtrl.SetItemText(i, 0,  m_CStrWarn[i+1].strPoint);
		m_listCtrl.SetItemText(i, 1,  m_CStrWarn[i+1].strDate);
		m_listCtrl.SetItemText(i, 2,  m_CStrWarn[i+1].strText);
		m_listCtrl.SetItemText(i, 3,  m_CStrWarn[i+1].strWarn);
		m_listCtrl.SetItemText(i, 4,  m_CStrWarn[i+1].strTime);
	}
	PostMessage(WM_VSCROLL,SB_LINEDOWN,0);
}
