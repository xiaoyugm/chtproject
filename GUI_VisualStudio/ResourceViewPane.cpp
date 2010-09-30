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

extern ADMainDis             m_ADMainDis[MAX_FDS][MAX_CHAN];          //调用显示
extern SerialF               m_DCHlist[MAX_FDS][MAX_CHAN][65];        //D状态改变
extern SerialF               m_DFlist[MAX_FDS][MAX_CHAN][65];     //D馈电列表
extern SerialF               m_DABlist[MAX_FDS][MAX_CHAN][65];    //D报警\断电列表
extern ADCbreakE             m_CFeed[MAX_FDS][9][65];
extern ADCbreakE             m_ADCbreakE[MAX_FDS][MAX_CHAN][65];
extern SerialF               m_Flist[MAX_FDS][MAX_CHAN][65];
extern SerialF               m_Blist[MAX_FDS][MAX_CHAN][65];
extern SlaveStation             m_SlaveStation[MAX_FDS][MAX_CHAN];
extern SerialF               m_Warnlist[MAX_FDS][MAX_CHAN];
/////////////////////////////////////////////////////////////////////////////
// CResourceViewPane

CResourceViewPane::CResourceViewPane()
{
	m_ontime=0;
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
	130,
	130,
	130,
//	60,
//	160,
	450
};
static CString arColLabels[] = {
	_T("安装地点/名称"),
	_T("监测值"),
	_T("报警时刻"),
	_T("断电时刻"),
	_T("复电时刻"),
//	_T("馈电状态"),
//	_T("馈电状态/时刻"),
	_T("安全措施/时刻")
};

static int bColWidths[] = {
	160,
	50,
	130,
	300,
	160,
//	60,
//	160,
//	360
};
static CString bColLabels[] = {
	_T("安装地点/名称"),
	_T("监测值"),
//	_T("报警时刻"),
	_T("断电时刻"),
	_T("断电区域"),
//	_T("复电时刻"),
//	_T("馈电状态"),
	_T("馈电状态/时刻"),
//	_T("安全措施/时刻")
};

static int fColWidths[] = {
	160,
//	50,
	130,
	130,
	300,
//	60,
//	160,
	160
};
static CString fColLabels[] = {
	_T("安装地点/名称"),
//	_T("监测值"),
//	_T("报警时刻"),
	_T("断电时刻"),
	_T("复电时刻"),
	_T("断电区域"),
//	_T("馈电状态"),
	_T("馈电状态/时刻"),
//	_T("安全措施")
};

static int dabColWidths[] = {
	160,
	100,
	130,
	130,
	160,
//	60,
	160,
	300
};
static CString dabColLabels[] = {
	_T("安装地点/名称"),
	_T("状态"),
	_T("报警时刻"),
	_T("断电时刻"),
//	_T("复电时刻"),
	_T("断电区域"),
//	_T("馈电状态"),
	_T("馈电状态/时刻"),
	_T("安全措施/时刻")
};

static int dfColWidths[] = {
	160,
	100,
//	130,
	130,
	160,
//	60,
	160
//	300
};
static CString dfColLabels[] = {
	_T("安装地点/名称"),
	_T("状态"),
//	_T("报警时刻"),
	_T("断电时刻"),
//	_T("复电时刻"),
	_T("断电区域"),
//	_T("馈电状态"),
	_T("馈电状态/时刻")
//	_T("安全措施")
};

//开关量状态变动显示
static int dchColWidths[] = {
	160,
	100,
//	130,
	130,
	160,
//	60,
	160
//	300
};
static CString dchColLabels[] = {
	_T("安装地点/名称"),
	_T("状态"),
//	_T("报警时刻"),
	_T("变动时刻"),
//	_T("复电时刻"),
	_T("断电区域"),
//	_T("馈电状态"),
	_T("馈电状态/时刻")
//	_T("安全措施")
};

/*
设备故障记录
static CString arColLabels[] = {
	_T("安装地点/名称"),
	_T("故障状态"),
	_T("故障时间"),
	_T("安全措施及处理时刻")
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
	if (!m_listCtrl.Create( dwStyle, CRect(3,0,1022,165), this, 0xff ))
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


BOOL CResourceViewPane::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	if( !CWnd::PreCreateWindow(cs) )
		return FALSE;

	cs.style |= WS_CLIPCHILDREN;
	
	cs.style = WS_CHILD | WS_VISIBLE //| WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU
		| FWS_ADDTOTITLE | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX 
    ;

//	cs.style   &=~   (LONG)   FWS_PREFIXTITLE;
//	cs.style &= ~WS_MAXIMIZEBOX;
//	cs.style &= ~WS_THICKFRAME;
//   cs.style   &=~WS_VSCROLL;     FWS_ADDTOTITLE

/*
cs.style = WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX;// | WS_THICKFRAME;
cs.style &= ~WS_BORDER;
cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
int iWinBorderX = GetSystemMetrics(SM_CXBORDER);
int iWinBorderY = GetSystemMetrics(SM_CYBORDER);
int iCaptionY = GetSystemMetrics(SM_CYCAPTION);
int iMenuY = GetSystemMetrics(SM_CYMENU);
int iStausY = GetSystemMetrics(SM_CYMENU);
cs.cx = 510 + iWinBorderX ;
cs.cy = 530 + iWinBorderY + iCaptionY + iStausY + iMenuY;*/

	return TRUE;
}



void CResourceViewPane::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);

//	if (m_wndResourceView.GetSafeHwnd())
	{
//		m_wndResourceView.MoveWindow(0, 0, 200, 200);
	}
//		m_wndSolutionView.MoveWindow(0, nTop, cx, cy - nTop);
//	m_listCtrl.MoveWindow(0, 0, cx, 170);
}

void CResourceViewPane::OnSetFocus(CWnd* /*pOldWnd*/)
{
//	m_wndResourceView.SetFocus();
//	InitLC();
//	m_listCtrl.SetFocus();
}

void CResourceViewPane::InitListControl()
{
	// Insert the columns.
	if(theApp.m_resnum == 1)
       	m_listCtrl.BuildColumns(_countof(arColWidths), arColWidths, arColLabels);
	else if(theApp.m_resnum == 2)
       	m_listCtrl.BuildColumns(_countof(bColWidths), bColWidths, bColLabels);
	else if(theApp.m_resnum == 3)
       	m_listCtrl.BuildColumns(_countof(fColWidths), fColWidths, fColLabels);
	else if(theApp.m_resnum == 4)
       	m_listCtrl.BuildColumns(_countof(dabColWidths), dabColWidths, dabColLabels);
	else if(theApp.m_resnum == 5)
       	m_listCtrl.BuildColumns(_countof(dfColWidths), dfColWidths, dfColLabels);
	else if(theApp.m_resnum == 6)
       	m_listCtrl.BuildColumns(_countof(dchColWidths), dchColWidths, dchColLabels);
	// Subclass the flat header control.
	m_listCtrl.SubclassHeader();

	// lock the first two colums from sizing operations.
//	CXTFlatHeaderCtrl* pHeaderCtrl = m_listCtrl.GetFlatHeaderCtrl( );
//	if ( pHeaderCtrl != NULL )
	{
//		pHeaderCtrl->FreezeColumn(0);
//		pHeaderCtrl->FreezeColumn(1);
//		pHeaderCtrl->FreezeColumn(2);
		// enable autosizing for columns.
//		pHeaderCtrl->EnableAutoSize();
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

void CResourceViewPane::InitLC(unsigned char  afds, unsigned char  achan)
{
    CMainFrame* pFWnd=(CMainFrame*)AfxGetMainWnd();
//	pFWnd->OnDisAAR();
    pFWnd->paneResourceView->Select();

	CString strtemp,strtemp1,strtemp2,strtempB,strtempS,strtempN;
	int m_listnum = m_Warnlist[afds][achan].SFSd;
	unsigned char	ufData1 = m_SlaveStation[afds][achan].Channel_state;
	strtemp2 = theApp.socketClient.strstatus(ufData1);
				  COleDateTime oleDateTime=m_ADMainDis[afds][achan].ATime ;
	strtemp = oleDateTime.Format(_T("%Y-%m-%d %H:%M:%S")); 
	oleDateTime=m_ADMainDis[afds][achan].BTime ;
	strtempB = oleDateTime.Format(_T("%Y-%m-%d %H:%M:%S")); 
	if(oleDateTime.GetYear() == 1900)
		strtempB ="";
	oleDateTime=m_ADMainDis[afds][achan].NTime ;
	strtempN = oleDateTime.Format(_T("%Y-%m-%d %H:%M:%S")); 
	if(oleDateTime.GetYear() == 1900)
		strtempN ="";
	  oleDateTime=m_SlaveStation[afds][achan].ValueTime;
	strtempS = oleDateTime.Format(_T("%Y-%m-%d %H:%M:%S")); 

	int	ufData6 = m_SlaveStation[afds][achan].ptype;
	if(ufData6 == 2)
        strtemp1.Format("%d",m_SlaveStation[afds][achan].CValue);
	else
    	strtemp1.Format(_T("%.2f"), m_SlaveStation[afds][achan].AValue);
	if(m_listnum == 500)
	{
		m_listnum = m_Warnlist[afds][achan].SFSd = theApp.idis;
		m_listCtrl.SetItemText(m_listnum, 0,  m_SlaveStation[afds][achan].WatchName);
		if(ufData1 == 0x10)
		{
      		m_listCtrl.SetItemText(m_listnum, 1,  strtemp1);
    		m_listCtrl.SetItemText(m_listnum, 2,  strtemp);
    		m_listCtrl.SetItemText(m_listnum, 3,  strtempB);
    		m_listCtrl.SetItemText(m_listnum, 4,  strtempN);
		}
		theApp.idis++;
	}
	else
	{
		m_listCtrl.SetItemText(m_listnum, 0,  m_SlaveStation[afds][achan].WatchName);

		if(ufData1 == 0x10)
		{
      		m_listCtrl.SetItemText(m_listnum, 1,  strtemp1);
    		m_listCtrl.SetItemText(m_listnum, 2,  strtemp);
    		m_listCtrl.SetItemText(m_listnum, 3,  strtempB);
    		m_listCtrl.SetItemText(m_listnum, 4,  strtempN);
		}
		if(theApp.m_resnum == 10)
		{
    		m_listCtrl.SetItemText(m_listnum, 5,  m_SlaveStation[afds][achan].strSafe+"|"+strtempS);
	    	theApp.m_resnum = 0;
		}
	}
    //Highlight the first item
//    LV_ITEM lvi;
//		lvi.mask = LVIF_TEXT;
//		lvi.iItem = m_listnum;
//		lvi.iSubItem = 0;
//	  lvi.stateMask = LVIS_SELECTED | LVIS_FOCUSED;
//	  lvi.state = LVIS_SELECTED | LVIS_FOCUSED;
//		lvi.pszText = "";
//		lvi.pszText = (LPSTR)(LPCTSTR)m_SlaveStation[afds][achan].WatchName;
//		lvi.iImage = 0;
//		lvi.iIndent = 0;
//		lvi.cchTextMax = 50;

//	  for(int i =0; i<theApp.idis+1; i++)
	  {
//		  if(i == m_listnum)
//        	    m_listCtrl.SetItemState(m_listnum,LVIS_SELECTED,LVIS_SELECTED);
//             m_listCtrl.SetItemState(lvi.iItem, &lvi);
//		  else
		  {
//    	    m_listCtrl.SetItemState(i,NULL,NULL);
		  }
	  }

//	PostMessage(WM_VSCROLL,SB_LINEDOWN,0);
}

void CResourceViewPane::InitLB(unsigned char  afds, unsigned char  achan)
{
    CMainFrame* pFWnd=(CMainFrame*)AfxGetMainWnd();
    pFWnd->paneResourceView2->Select();
    	int m_listnum = m_Blist[afds][achan][0].SFSd;
    	CString strtemp,strtemp1,strtemp2,strfeed,strtempB;
     	unsigned char	ufData1 = m_SlaveStation[afds][achan].Channel_state;
      	strtemp2 = theApp.socketClient.strstatus(ufData1);
				  COleDateTime oleDateTime=m_SlaveStation[afds][achan].ValueTime;
       	strtemp = oleDateTime.Format(_T("%Y-%m-%d %H:%M:%S")); 
				  oleDateTime=m_ADMainDis[afds][achan].BTime;
       	strtempB = oleDateTime.Format(_T("%Y-%m-%d %H:%M:%S")); 
    	int	ufData6 = m_SlaveStation[afds][achan].ptype;
	if(ufData6 == 2)
        strtemp1.Format("%d",m_SlaveStation[afds][achan].CValue);
	else
		strtemp1.Format(_T("%.2f"), m_SlaveStation[afds][achan].AValue);
	if(m_listnum == 500)
	{
		int x=0;
		for(int i= 0 ;i<64 ; i++)
		{
		int y=0;
		     int cfds = m_ADCbreakE[afds][achan][i].bFSd;
			 int cchan = m_ADCbreakE[afds][achan][i].bchanel;
			 if(cfds == 0)
				 break;
     		m_listnum = m_Blist[afds][achan][x].SFSd = theApp.bidis;
      		m_listCtrl.SetItemText(m_listnum, 0,  m_SlaveStation[afds][achan].WatchName);
    		if((ufData1 == 0x40)|| (ufData1 == 0x50)|| (ufData1 == 0x60) ||(ufData1 == 0x70)|| (ufData1 == 0x80))
				strtemp1 = theApp.socketClient.strstatus(ufData1);
			{
//      	    	m_listCtrl.SetItemText(m_listnum, 1, strtemp2 );
//           		m_listCtrl.SetItemText(m_listnum, 2,  strtemp);
			}
//	    	else if((ufData1 == 0x20)|| (ufData1 == 0x60))
			{
         		m_listCtrl.SetItemText(m_listnum, 1,  strtemp1);
           		m_listCtrl.SetItemText(m_listnum, 2,  strtempB);
			}
			//断电关联馈电
			for(int j= 0 ;j<64 ; j++)
			{
    		     int ffds = m_CFeed[cfds][cchan][j].bFSd;
	       		 int fchan = m_CFeed[cfds][cchan][j].bchanel;
				 if(ffds == 0)
	 				 break;

        	 	 m_listnum = m_Blist[afds][achan][x].SFSd = theApp.bidis;
         		m_listCtrl.SetItemText(m_listnum, 0,  m_SlaveStation[afds][achan].WatchName);
         		m_listCtrl.SetItemText(m_listnum, 1,  strtemp1);
           		m_listCtrl.SetItemText(m_listnum, 2,  strtempB);
        		m_listCtrl.SetItemText(m_listnum, 3,  m_SlaveStation[ffds][fchan].WatchName);
				 y++;
				 m_Blist[afds][achan][x].cfds =cfds;
				 m_Blist[afds][achan][x].cchan = cchan;
				 m_Blist[afds][achan][x].ffds = ffds;
				 m_Blist[afds][achan][x].fchan =fchan;

//				  COleDateTime oleDT=m_SlaveStation[ffds][fchan].ValueTime;
//                 strfeed = oleDT.Format(_T("%Y-%m-%d %H:%M:%S")); 
				 strfeed = m_SlaveStation[ffds][fchan].FeedState+"|"+strtemp;
            		m_listCtrl.SetItemText(m_listnum, 4,  strfeed);
        		theApp.bidis++;
				x++;
			}
			if(y == 0)
			{
              	theApp.bidis++;
				x++;
			}
		}
	}
	else
	{
		for(int i= 0 ;i<64 ; i++)
		{
     		m_listnum = m_Blist[afds][achan][i].SFSd ;
			 if(m_listnum == 500)
				 break;
      		m_listCtrl.SetItemText(m_listnum, 0,  m_SlaveStation[afds][achan].WatchName);
    		if((ufData1 == 0x40)|| (ufData1 == 0x50) ||(ufData1 == 0x70)|| (ufData1 == 0x80)||(ufData1 == 0x90)|| (ufData1 == 0xa0))
				strtemp1 = theApp.socketClient.strstatus(ufData1);
			{
//      	    	m_listCtrl.SetItemText(m_listnum, 1, strtemp2 );
//           		m_listCtrl.SetItemText(m_listnum, 2,  strtemp);
			}
//	    	else if((ufData1 == 0x20)|| (ufData1 == 0x60))
			{
         		m_listCtrl.SetItemText(m_listnum, 1,  strtemp1);
           		m_listCtrl.SetItemText(m_listnum, 2,  strtempB);
			}
//		     int cfds = m_Blist[afds][achan][i].cfds;
//			 int cchan = m_Blist[afds][achan][i].cchan;
//			 if(cfds != 0)

			int ffds = m_Blist[afds][achan][i].ffds;
	       		 int fchan = m_Blist[afds][achan][i].fchan;
				 if(ffds != 0)
				 {
         		m_listCtrl.SetItemText(m_listnum, 3, m_SlaveStation[ffds][fchan].WatchName);
//    				  COleDateTime oleDT=m_SlaveStation[ffds][fchan].ValueTime;
//                      strfeed = oleDT.Format(_T("%Y-%m-%d %H:%M:%S")); 
			       	  strfeed = m_SlaveStation[ffds][fchan].FeedState+"|"+strtemp;
            		  m_listCtrl.SetItemText(m_listnum, 4,  strfeed);
				 }
		}
	}
}

void CResourceViewPane::InitLF(unsigned char  afds, unsigned char  achan)
{
    CMainFrame* pFWnd=(CMainFrame*)AfxGetMainWnd();
    pFWnd->paneResourceView3->Select();

	int m_listnum = m_Flist[afds][achan][0].SFSd;
    	CString strtemp,strtemp1,strtemp2,strfeed,strtempB,strtempN;
     	unsigned char	ufData1 = m_SlaveStation[afds][achan].Channel_state;
      	strtemp2 = theApp.socketClient.strstatus(ufData1);
				  COleDateTime oleDateTime=m_ADMainDis[afds][achan].BTime;
       	strtempB = oleDateTime.Format(_T("%Y-%m-%d %H:%M:%S")); 
	if(oleDateTime.GetYear() == 1900)
		strtempB ="";
	   oleDateTime=m_SlaveStation[afds][achan].ValueTime;
       	strtemp = oleDateTime.Format(_T("%Y-%m-%d %H:%M:%S")); 
	oleDateTime=m_ADMainDis[afds][achan].NTime ;
	strtempN = oleDateTime.Format(_T("%Y-%m-%d %H:%M:%S")); 
	if(oleDateTime.GetYear() == 1900)
		strtempN ="";
    	int	ufData6 = m_SlaveStation[afds][achan].ptype;
	if(ufData6 == 2)
        strtemp1.Format("%d",m_SlaveStation[afds][achan].CValue);
	else
		strtemp1.Format(_T("%.2f"), m_SlaveStation[afds][achan].AValue);
	if(m_listnum == 500)
	{
		int x=0;
		for(int i= 0 ;i<64 ; i++)
		{
		int y=0;
		     int cfds = m_ADCbreakE[afds][achan][i].bFSd;
			 int cchan = m_ADCbreakE[afds][achan][i].bchanel;
			 if(cfds == 0)
				 break;
     		m_listnum = m_Flist[afds][achan][x].SFSd = theApp.fidis;
      		m_listCtrl.SetItemText(m_listnum, 0,  m_SlaveStation[afds][achan].WatchName);
//    		if((ufData1 == 0x40)|| (ufData1 == 0x50) ||(ufData1 == 0x70))
//      	    	m_listCtrl.SetItemText(m_listnum, 1, strtemp );
//	    	else if((ufData1 == 0x20)|| (ufData1 == 0x60))
           		m_listCtrl.SetItemText(m_listnum, 1,  strtempB);
//	    	else if(ufData1 == 0x00)
    	    	m_listCtrl.SetItemText(m_listnum, 2,  strtempN);
			for(int j= 0 ;j<64 ; j++)
			{
    		     int ffds = m_CFeed[cfds][cchan][j].bFSd;
	       		 int fchan = m_CFeed[cfds][cchan][j].bchanel;
				 if(ffds == 0)
	 				 break;

        		m_listCtrl.SetItemText(m_listnum, 3,  m_SlaveStation[ffds][fchan].WatchName);
				 y++;
        	 	 m_listnum = m_Flist[afds][achan][x].SFSd = theApp.fidis;
				 m_Flist[afds][achan][x].cfds =cfds;
				 m_Flist[afds][achan][x].cchan = cchan;
				 m_Flist[afds][achan][x].ffds = ffds;
				 m_Flist[afds][achan][x].fchan =fchan;

//				  COleDateTime oleDT=m_SlaveStation[ffds][fchan].ValueTime;
//                 strfeed = oleDT.Format(_T("%Y-%m-%d %H:%M:%S")); 
				 strfeed = m_SlaveStation[ffds][fchan].FeedState+"|"+strtemp;
            		m_listCtrl.SetItemText(m_listnum, 4,  strfeed);
        		theApp.fidis++;
				x++;
			}
			if(y == 0)
			{
              	theApp.fidis++;
				x++;
			}
		}
	}
	else
	{
		for(int i= 0 ;i<64 ; i++)
		{
     		m_listnum = m_Flist[afds][achan][i].SFSd ;
			 if(m_listnum == 500)
				 break;
      		m_listCtrl.SetItemText(m_listnum, 0,  m_SlaveStation[afds][achan].WatchName);
//    		if((ufData1 == 0x40)|| (ufData1 == 0x50) ||(ufData1 == 0x70))
//      	    	m_listCtrl.SetItemText(m_listnum, 1, strtemp );
//	    	else if((ufData1 == 0x20)|| (ufData1 == 0x60))
           		m_listCtrl.SetItemText(m_listnum, 1,  strtempB);
//	    	else if(ufData1 == 0x00)
    	    	m_listCtrl.SetItemText(m_listnum, 2,  strtempN);
//		     int cfds = m_Blist[afds][achan][i].cfds;
//			 int cchan = m_Blist[afds][achan][i].cchan;
//			 if(cfds != 0)

			int ffds = m_Flist[afds][achan][i].ffds;
	       		 int fchan = m_Flist[afds][achan][i].fchan;
				 if(ffds != 0)
				 {
         		m_listCtrl.SetItemText(m_listnum, 3, m_SlaveStation[ffds][fchan].WatchName);
//    				  COleDateTime oleDT=m_SlaveStation[ffds][fchan].ValueTime;
//                      strfeed = oleDT.Format(_T("%Y-%m-%d %H:%M:%S")); 
			       	  strfeed = m_SlaveStation[ffds][fchan].FeedState+"|"+strtemp;
            		  m_listCtrl.SetItemText(m_listnum, 4,  strfeed);
				 }
		}
	}
}

void CResourceViewPane::InitLDAB(unsigned char  afds, unsigned char  achan)
{
    CMainFrame* pFWnd=(CMainFrame*)AfxGetMainWnd();
    pFWnd->paneResourceView4->Select();
    	int m_listnum = m_DABlist[afds][achan][0].SFSd;
    	CString strtemp,strtemp1,strtemp2,strfeed,strtempB,strtempN,strtempA;
     	unsigned char	ufData1 = m_SlaveStation[afds][achan].Channel_state;
      	strtemp2 = theApp.socketClient.strstatus(ufData1);
				  COleDateTime oleDateTime=m_SlaveStation[afds][achan].ValueTime;
       	strtemp = oleDateTime.Format(_T("%Y-%m-%d %H:%M:%S")); 
				  oleDateTime=m_ADMainDis[afds][achan].BTime;
       	strtempB = oleDateTime.Format(_T("%Y-%m-%d %H:%M:%S")); 
	if(oleDateTime.GetYear() == 1900)
		strtempB ="";
	oleDateTime=m_ADMainDis[afds][achan].NTime ;
	strtempN = oleDateTime.Format(_T("%Y-%m-%d %H:%M:%S")); 
	if(oleDateTime.GetYear() == 1900)
		strtempN ="";
				  oleDateTime=m_ADMainDis[afds][achan].ATime;
       	strtempA = oleDateTime.Format(_T("%Y-%m-%d %H:%M:%S")); 
	if(oleDateTime.GetYear() == 1900)
		strtempA ="";

//    	int	ufData6 = m_SlaveStation[afds][achan].ptype;
		int dvalue= m_SlaveStation[afds][achan].CValue;
		if(dvalue == 0)
    		strtemp1 =  m_SlaveStation[afds][achan].ZeroState;
		else if(dvalue == 1)
    		strtemp1 =  m_SlaveStation[afds][achan].OneState;
		else if(dvalue == 2)
    		strtemp1 =  m_SlaveStation[afds][achan].TwoState;
	if(m_listnum == 500)
	{
		int x=0;
		for(int i= 0 ;i<64 ; i++)
		{
     		m_listnum = m_DABlist[afds][achan][x].SFSd = theApp.dabidis;
      		m_listCtrl.SetItemText(m_listnum, 0,  m_SlaveStation[afds][achan].WatchName);
				if((ufData1 == 0x70) ||(ufData1 == 0x80))
         	        strtemp1= strtemp2 ;

				m_listCtrl.SetItemText(m_listnum, 1, strtemp1 );
      	    	m_listCtrl.SetItemText(m_listnum, 2, strtempA );
      	    	m_listCtrl.SetItemText(m_listnum, 3, strtempB );
    		int y=0;
		     int cfds = m_ADCbreakE[afds][achan][i].bFSd;
			 int cchan = m_ADCbreakE[afds][achan][i].bchanel;
			 if(cfds == 0)
			 {
              	theApp.dabidis++;
				 break;
			 }

			for(int j= 0 ;j<64 ; j++)
			{
    		     int ffds = m_CFeed[cfds][cchan][j].bFSd;
	       		 int fchan = m_CFeed[cfds][cchan][j].bchanel;
				 if(ffds == 0)
	 				 break;

        		m_listCtrl.SetItemText(m_listnum, 4,  m_SlaveStation[ffds][fchan].WatchName);
				 y++;
        	 	 m_listnum = m_DABlist[afds][achan][x].SFSd = theApp.dabidis;
				 m_DABlist[afds][achan][x].cfds =cfds;
				 m_DABlist[afds][achan][x].cchan = cchan;
				 m_DABlist[afds][achan][x].ffds = ffds;
				 m_DABlist[afds][achan][x].fchan =fchan;

//				  COleDateTime oleDT=m_SlaveStation[ffds][fchan].ValueTime;
//                 strfeed = oleDT.Format(_T("%Y-%m-%d %H:%M:%S")); 
				 strfeed = m_SlaveStation[ffds][fchan].FeedState+"|"+strtemp;
            		m_listCtrl.SetItemText(m_listnum, 5,  strfeed);
        		theApp.dabidis++;
				x++;
			}
			if(y == 0)
			{
              	theApp.dabidis++;
				x++;
			}
		}
	}
	else
	{
		for(int i= 0 ;i<64 ; i++)
		{
     		m_listnum = m_DABlist[afds][achan][i].SFSd ;
			 if(m_listnum == 500)
				 break;
      		m_listCtrl.SetItemText(m_listnum, 0,  m_SlaveStation[afds][achan].WatchName);
				if((ufData1 == 0x70) ||(ufData1 == 0x80))
         	        strtemp1= strtemp2 ;
       	    	m_listCtrl.SetItemText(m_listnum, 1, strtemp1 );
      	    	m_listCtrl.SetItemText(m_listnum, 2, strtempA );
      	    	m_listCtrl.SetItemText(m_listnum, 3, strtempB );
//		     int cfds = m_Blist[afds][achan][i].cfds;
//			 int cchan = m_Blist[afds][achan][i].cchan;
//			 if(cfds != 0)

			int ffds = m_DABlist[afds][achan][i].ffds;
	       		 int fchan = m_DABlist[afds][achan][i].fchan;
				 if(ffds != 0)
				 {
             		m_listCtrl.SetItemText(m_listnum, 4, m_SlaveStation[ffds][fchan].WatchName);
//    				  COleDateTime oleDT=m_SlaveStation[ffds][fchan].ValueTime;
//                      strfeed = oleDT.Format(_T("%Y-%m-%d %H:%M:%S")); 
			       	  strfeed = m_SlaveStation[ffds][fchan].FeedState+"|"+strtemp;
            		  m_listCtrl.SetItemText(m_listnum, 5,  strfeed);
				 }
	    	if((theApp.m_resnum == 10)&&(i== 0))
			{
    	    	m_listCtrl.SetItemText(m_listnum, 6,  m_SlaveStation[afds][achan].strSafe+"|"+strtemp);
	        	theApp.m_resnum = 0;
			}
		}
	}
}

void CResourceViewPane::InitLDF(unsigned char  afds, unsigned char  achan)
{
    CMainFrame* pFWnd=(CMainFrame*)AfxGetMainWnd();
    pFWnd->paneResourceView5->Select();
    	int m_listnum = m_DFlist[afds][achan][0].SFSd;
    	CString strtemp,strtemp1,strtemp2,strfeed,strtempB;
     	unsigned char	ufData1 = m_SlaveStation[afds][achan].Channel_state;
      	strtemp2 = theApp.socketClient.strstatus(ufData1);
				  COleDateTime oleDateTime=m_SlaveStation[afds][achan].ValueTime;
       	strtemp = oleDateTime.Format(_T("%Y-%m-%d %H:%M:%S")); 
				  oleDateTime=m_ADMainDis[afds][achan].BTime;
       	strtempB = oleDateTime.Format(_T("%Y-%m-%d %H:%M:%S")); 

		int dvalue= m_SlaveStation[afds][achan].CValue;
		if(dvalue == 0)
    		strtemp1 =  m_SlaveStation[afds][achan].ZeroState;
		else if(dvalue == 1)
    		strtemp1 =  m_SlaveStation[afds][achan].OneState;
		else if(dvalue == 2)
    		strtemp1 =  m_SlaveStation[afds][achan].TwoState;
	if(m_listnum == 500)
	{
		int x=0;
		for(int i= 0 ;i<64 ; i++)
		{
    		int y=0;
		     int cfds = m_ADCbreakE[afds][achan][i].bFSd;
			 int cchan = m_ADCbreakE[afds][achan][i].bchanel;
			 if(cfds == 0)
				 break;
     		m_listnum = m_DFlist[afds][achan][x].SFSd = theApp.dfidis;
			for(int j= 0 ;j<64 ; j++)
			{
    		     int ffds = m_CFeed[cfds][cchan][j].bFSd;
	       		 int fchan = m_CFeed[cfds][cchan][j].bchanel;
				 if(ffds == 0)
	 				 break;

           		m_listCtrl.SetItemText(m_listnum, 0,  m_SlaveStation[afds][achan].WatchName);
				if((ufData1 == 0x70) ||(ufData1 == 0x80))
         	        strtemp1= strtemp2 ;
   	        	m_listCtrl.SetItemText(m_listnum, 1, strtemp1 );
      	        	m_listCtrl.SetItemText(m_listnum, 2, strtempB );
        		m_listCtrl.SetItemText(m_listnum, 3,  m_SlaveStation[ffds][fchan].WatchName);
				 y++;
        	 	 m_listnum = m_DFlist[afds][achan][x].SFSd = theApp.dfidis;
				 m_DFlist[afds][achan][x].cfds =cfds;
				 m_DFlist[afds][achan][x].cchan = cchan;
				 m_DFlist[afds][achan][x].ffds = ffds;
				 m_DFlist[afds][achan][x].fchan =fchan;

//				  COleDateTime oleDT=m_SlaveStation[ffds][fchan].ValueTime;
//                 strfeed = oleDT.Format(_T("%Y-%m-%d %H:%M:%S")); 
				 strfeed = m_SlaveStation[ffds][fchan].FeedState+"|"+strtemp;
            		m_listCtrl.SetItemText(m_listnum, 4,  strfeed);
        		theApp.dfidis++;
				x++;
			}
			if(y == 0)
			{
              	theApp.dfidis++;
				x++;
			}
		}
	}
	else
	{
		for(int i= 0 ;i<64 ; i++)
		{
     		m_listnum = m_DFlist[afds][achan][i].SFSd ;
			 if(m_listnum == 500)
				 break;
			int ffds = m_DFlist[afds][achan][i].ffds;
	       		 int fchan = m_DFlist[afds][achan][i].fchan;
				 if(ffds != 0)
				 {
               		m_listCtrl.SetItemText(m_listnum, 0,  m_SlaveStation[afds][achan].WatchName);
            		if((ufData1 == 0x70)||(ufData1 == 0x80))
         	             strtemp1= strtemp2 ;
   	              	m_listCtrl.SetItemText(m_listnum, 1, strtemp1 );
              	    	m_listCtrl.SetItemText(m_listnum, 2, strtempB );

              		m_listCtrl.SetItemText(m_listnum, 3, m_SlaveStation[ffds][fchan].WatchName);
//    				  COleDateTime oleDT=m_SlaveStation[ffds][fchan].ValueTime;
//                      strfeed = oleDT.Format(_T("%Y-%m-%d %H:%M:%S")); 
			       	  strfeed = m_SlaveStation[ffds][fchan].FeedState+"|"+strtemp;
            		  m_listCtrl.SetItemText(m_listnum, 4,  strfeed);
				 }
		}
	}
}

void CResourceViewPane::InitLDCH(unsigned char  afds, unsigned char  achan)
{
    CMainFrame* pFWnd=(CMainFrame*)AfxGetMainWnd();
    pFWnd->paneResourceView6->Select();
    	int m_listnum = m_DCHlist[afds][achan][0].SFSd; //列表位置id
    	CString strtemp,strtemp1,strtemp2,strfeed;
     	unsigned char	ufData1 = m_SlaveStation[afds][achan].Channel_state;
      	strtemp2 = theApp.socketClient.strstatus(ufData1);
				  COleDateTime oleDateTime=m_SlaveStation[afds][achan].ValueTime;
       	strtemp = oleDateTime.Format(_T("%Y-%m-%d %H:%M:%S")); 
		int dvalue= m_SlaveStation[afds][achan].CValue;
		if(dvalue == 0)
    		strtemp1 =  m_SlaveStation[afds][achan].ZeroState;
		else if(dvalue == 1)
    		strtemp1 =  m_SlaveStation[afds][achan].OneState;
		else if(dvalue == 2)
    		strtemp1 =  m_SlaveStation[afds][achan].TwoState;
	if(m_listnum == 500)
	{
		int x=0;
		for(int i= 0 ;i<64 ; i++)
		{
			//m_listnum  点号
     		m_listnum = m_DCHlist[afds][achan][x].SFSd = theApp.dchidis;
           		m_listCtrl.SetItemText(m_listnum, 0,  m_SlaveStation[afds][achan].WatchName);
				if((ufData1 == 0x70) ||(ufData1 == 0x80))
         	        m_listCtrl.SetItemText(m_listnum, 1, strtemp2 );
				else
         	        m_listCtrl.SetItemText(m_listnum, 1, strtemp1 );
      	        m_listCtrl.SetItemText(m_listnum, 2, strtemp );
    		int y=0;
		     int cfds = m_ADCbreakE[afds][achan][i].bFSd;
			 int cchan = m_ADCbreakE[afds][achan][i].bchanel;
			 if(cfds == 0)
			 {
              	theApp.dchidis++;
				 break;
			 }
    			for(int j= 0 ;j<64 ; j++)
				{
    		     int ffds = m_CFeed[cfds][cchan][j].bFSd;
	       		 int fchan = m_CFeed[cfds][cchan][j].bchanel;
				 if(ffds == 0)
	 				 break;
        		m_listCtrl.SetItemText(m_listnum, 3,  m_SlaveStation[ffds][fchan].WatchName);
				 y++;
        	 	 m_listnum = m_DCHlist[afds][achan][x].SFSd = theApp.dchidis;
				 m_DCHlist[afds][achan][x].cfds =cfds;
				 m_DCHlist[afds][achan][x].cchan = cchan;
				 m_DCHlist[afds][achan][x].ffds = ffds;
				 m_DCHlist[afds][achan][x].fchan =fchan;

//				  COleDateTime oleDT=m_SlaveStation[ffds][fchan].ValueTime;
//                 strfeed = oleDT.Format(_T("%Y-%m-%d %H:%M:%S")); 
				 strfeed = m_SlaveStation[ffds][fchan].FeedState+"|"+strtemp;
            		m_listCtrl.SetItemText(m_listnum, 4,  strfeed);
        		theApp.dchidis++;
				x++;
				}
			if(y == 0)
			{
              	theApp.dchidis++;
				x++;
			}
		}
	}
	else
	{
		for(int i= 0 ;i<64 ; i++)
		{
     		m_listnum = m_DCHlist[afds][achan][i].SFSd ;
			 if(m_listnum == 500)
				 break;
			int ffds = m_DCHlist[afds][achan][i].ffds;
	       		 int fchan = m_DCHlist[afds][achan][i].fchan;
//				 if(ffds != 0)
				 {
               		m_listCtrl.SetItemText(m_listnum, 0,  m_SlaveStation[afds][achan].WatchName);
				if((ufData1 == 0x70) ||(ufData1 == 0x80))
         	        m_listCtrl.SetItemText(m_listnum, 1, strtemp2 );
				else
      	            m_listCtrl.SetItemText(m_listnum, 1, strtemp1 );
              	    m_listCtrl.SetItemText(m_listnum, 2, strtemp );
				if(ffds == 0)
	    			 break;
              		m_listCtrl.SetItemText(m_listnum, 3, m_SlaveStation[ffds][fchan].WatchName);
//    				  COleDateTime oleDT=m_SlaveStation[ffds][fchan].ValueTime;
//                      strfeed = oleDT.Format(_T("%Y-%m-%d %H:%M:%S")); 
			       	  strfeed = m_SlaveStation[ffds][fchan].FeedState+"|"+strtemp;
            		  m_listCtrl.SetItemText(m_listnum, 4,  strfeed);
				 }
		}
	}
}
