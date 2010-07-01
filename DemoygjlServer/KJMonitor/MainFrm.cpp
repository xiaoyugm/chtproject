// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "KJMonitor.h"

#include "MainFrm.h"
#include "KJMonitorDoc.h"
//#include "CommStatusFM.h"
#include "KJMonitorView.h"
#include "TabDoc.h"
#include "TabView.h"
#include "UserPasswdDlg.h"

#include "PointEditSwitchIn.h"
#include "PointEditAnologIn.h"
#include "WarnCauseEditDlg.h"
#include "ViewDeleteAddr.h"

//#include "ComfirmDlg.h"
#include "CommParaDlg.h"

#include "SetPortVsTrunkDlg.h"  //set trunk vs serial port

#include "BitCmdCtrlDlg.h"
#include "CtrlCmdDlg.h"
#include "Sequence\\shixuDlg.h"        // 
#include "AnologOutDlg.h"
#include "LoginDlg.h"
#include "IcoControl.h"

#include "TrunkAdd.h"



#include "Others\\Splash.h"
#include "Sequence\\dialogspumonitor.h"   //  add
#include "Sequence\\dialogR.h"
#include "Sequence\\DialogFeg.h"
#include "Sequence\\dialogtime.h"

#include <afxdb.h>               //  add
#include "Sequence\\SpuInform.h"            //  add
#include  "Sequence\\Spudetailed_me.h"     //  add
//#include "Sequence.h"

//添加的代码
#include "SyncDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame
//  add    全局变量定义
extern Cdialogspumonitor dlg_spumonitor;
extern CShixuDlg dlgshixu; 
extern BOOL StartSequence;


IMPLEMENT_DYNCREATE(CMainFrame, CXTFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CXTFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_COMMAND(ID_MEPOINT_SWITCHINPUT, OnMepointSwitchinput)
	ON_COMMAND(ID_MEPOINT_ANALOGINPUT, OnMepointAnaloginput)
	ON_COMMAND(ID_SYS_USERPASSWORD, OnSysUserpassword)
	ON_COMMAND(ID_MEPOINT_ALARMREASON, OnMepointAlarmreason)
	ON_COMMAND(ID_MEPOINT_LOADPARADATA, OnMepointLoadparadata)
	ON_COMMAND(ID_MENU_COMM_EDITPARAMENTS, OnMenuCommEditparaments)
	ON_COMMAND(ID_SYS_TRUNKVSPORT, OnSysTrunkvsport)
	ON_COMMAND(ID_MENU_SYS_STARTSCAN, OnMenuSysStartscan)
	ON_COMMAND(ID_MENU_SYS_STOPSCAN, OnMenuSysStopscan)
	ON_COMMAND(ID_MENU_BITCMD, OnMenuBitcmd)
	ON_COMMAND(ID_MEPOINT_CTRL_SWITCHOUTPUT, OnMepointCtrlSwitchoutput)
	ON_COMMAND(ID_MENU_TABLE_ANALOG, OnMenuTableAnalog)
	ON_COMMAND(ID_APP_EXIT, OnAppExit)
	ON_COMMAND(ID_MEPOINT_CTRL_ANALOGOUTPUT, OnMepointCtrlAnalogoutput)
	ON_COMMAND(ID_MEPOINT_CTRL_GASINSPECT, OnMepointCtrlGasinspect)
	ON_COMMAND(ID_MENU_SQUENCE_COMMONREG, OnMenuSquenceCommonreg)
	ON_COMMAND(ID_MENU_SQUENCE_START, OnMenuSquenceStart)
	ON_COMMAND(ID_MENU_SQUENCE_END, OnMenuSquenceEnd)
	ON_COMMAND(ID_MENU_SQUENCE_EDIT, OnMenuSquenceEdit)
	ON_COMMAND(ID_MENU_SQUENCE_MONITOR, OnMenuSquenceMonitor)
	ON_COMMAND(ID_MENU_SQUENCE_TRIG_POINTEDIT, OnMenuSquenceTrigPointedit)
	ON_COMMAND(ID_MENU_SQUENCE_TIME, OnMenuSquenceTime)
	ON_WM_TIMER()
	ON_COMMAND(ID_SYNC_SYNC, OnSyncSync)
	ON_UPDATE_COMMAND_UI(ID_MENU_SYS_STARTSCAN, OnUpdateMenuSysStartscan)
	ON_UPDATE_COMMAND_UI(ID_MENU_SYS_STOPSCAN, OnUpdateMenuSysStopscan)
	ON_UPDATE_COMMAND_UI(ID_MENU_SQUENCE_START, OnUpdateMenuSquenceStart)
	ON_UPDATE_COMMAND_UI(ID_MENU_SQUENCE_END, OnUpdateMenuSquenceEnd)
	//}}AFX_MSG_MAP
	ON_MESSAGE(XTWM_OUTBAR_NOTIFY, OnOutbarNotify)
	ON_COMMAND(ID_HELP_FINDER, CXTFrameWnd::OnHelpFinder)
	ON_COMMAND(ID_HELP, CXTFrameWnd::OnHelp)
	ON_COMMAND(ID_CONTEXT_HELP, CXTFrameWnd::OnContextHelp)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
//	ID_INDICATOR_CAPS,
//	ID_INDICATOR_NUM,
//	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	m_bDestroy = false;
	

	// TODO: add member initialization code here
	m_bCloseAllSerialPort=FALSE;
	m_bStartStopScan=FALSE;
//	m_xpara1=0;			//9/14

}

CMainFrame::~CMainFrame()
{

}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CXTFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

    // Enable/Disable XP GUI Mode
    xtAfxData.bXPMode = TRUE;

    // Enable/Disable Menu Shadows
    xtAfxData.bMenuShadows = TRUE;

	if (!m_wndMenuBar.CreateEx(this,  NULL
//	if (!m_wndMenuBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		  ) ||
//		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndMenuBar.LoadMenuBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create menubar\n");
		return -1;      // fail to create
	}
/*	
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}
*/
	// Create the output bar.
	if (!m_wndOutputBar.Create(this, IDW_OUTPUTBAR, _T("WARNING!!!"),
		CSize(150, 118), CBRS_TOP))//CBRS_BOTTOM))
	{
		TRACE0("Failed to create output dock window\n");
		return -1;		// fail to create
	}

/*	int dwNewStyle = 0;
		dwNewStyle |= FTS_XT_HASHOMEEND;
      dwNewStyle |= FTS_XT_HASARROWS;*/
	// Create the workspace bar.
	//if( !m_wndWrkspBar.Create(this, IDW_WORKSPBAR, _T("WARNING"),
		//CSize(200, 150), CBRS_LEFT ,CBRS_BOTTOM))
	if( !m_wndWrkspBar.Create(this, IDW_WORKSPBAR,_T("STATUS"),
		CSize(910, 400), CBRS_RIGHT ,OBS_XT_DEFAULT ))
	//		if( !m_wndWrkspBar.Create(this, NULL, NULL,
	//	CSize(600, 150), CBRS_RIGHT))  ,CBRS_XT_BUTTONS | CBRS_XT_GRIPPER   OBS_XT_DEFAULT

	{
		TRACE0("Failed to create workspace dock window\n");
		return -1;		// fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	AddFxStaticText();
	AddLogoPane();

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndMenuBar.EnableDockingEx(CBRS_ALIGN_ANY, CBRS_XT_ALL_FLAT);
//	m_wndToolBar.EnableDockingEx(CBRS_ALIGN_ANY, CBRS_XT_ALL_FLAT);
	m_wndOutputBar.EnableDockingEx(CBRS_ALIGN_ANY, CBRS_XT_ALL_FLAT|CBRS_XT_GRIPPER_GRAD);
	m_wndWrkspBar.EnableDockingEx(CBRS_ALIGN_ANY, CBRS_XT_ALL_FLAT|CBRS_XT_GRIPPER_GRAD);
	EnableDockingEx(CBRS_ALIGN_ANY , CBRS_XT_ALL_FLAT );
	DockControlBar(&m_wndMenuBar);
//	DockControlBar(&m_wndToolBar);
	DockControlBar(&m_wndOutputBar);
	DockControlBar(&m_wndWrkspBar);

	// Initialize the tab control bar.
	InitTabCtrlBar();

	// TODO: Remove this line if you don't want cool menus.
	InstallCoolMenus(IDR_MAINFRAME);

	// CG: The following line was added by the Splash Screen component.
	CSplashWnd::ShowSplashScreen(this);

	return 0;
}

BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT /*lpcs*/,
	CCreateContext* pContext)
{
	// Create the splitter window with two columns
	if (!m_wndSplitter1.CreateStatic(this, 1, 2))
	{
		TRACE0("Failed to create splitter window\n");
		return FALSE;
	}

	if (!m_wndSplitter1.CreateView(0, 1, RUNTIME_CLASS(CKJMonitorView),
		CSize(0, 0), pContext))
	{
		TRACE0("Failed to create CKJMonitorView\n"); 
		return FALSE;
	}

	// Create the Outlook bar, this will be inserted
	// into row 0, col 0.
	if (!InitializeOutlookBar())
		return FALSE;

	return TRUE;
}

static UINT arIcons[] =
{
	IDI_ICON_ANOLOGIN,     // f00      n0 
	IDI_ICON_ANOLOGOUT,    // f01   f34   n1 
	IDI_ICON_SWITCHPOINTEDIT,// f02     n2 
	IDI_ICON_SWITCHPOINTOUTEDIT, //f03  f32 n3
	IDI_ICON_REGINCTRLEDIT,    //f04    n4
	IDI_ICON_WARNEDIT,        //f05     n5
	IDI_ICON_SAVEDBFILE,      //f06     n6
	IDI_ICON_LOADDBFILE,      //f07     n7
	IDI_ICON_CUSTOM1,  //f10        n8       ＊＊＊
	IDI_ICON_COMPARAEDIT,     //f11   f31    n9
	IDI_ICON_COMMONITOR,      //f12      n10
	IDI_ICON_COMSTARTTIME,    //f13      n11
	IDI_ICON_TABLE1,        // f20  F10    n12   
	IDI_ICON_TABLE2,
	IDI_ICON_TABLE3,
	IDI_ICON_TABLE4,
	IDI_ICON_TABLE5,
	IDI_ICON_TABLE6,
	IDI_ICON_TABLE7,
	IDI_ICON_TABLE8,
	IDI_ICON_TABLE9,
	IDI_ICON_TABLE10,       //f29            n21
	IDI_ICON_GASMONITOR,    //f33            n22
	IDI_ICON_PRINTER,       //f41,f42,f43    n23
	IDI_ICON_CHANGEDATETIME, //f44           n24
	IDI_ICON_INITDB,         //f45           n25
	IDI_ICON_LOGIN,     //f46          n26        ＊＊＊＊＊＊＊
	IDI_ICON_CANCEL,              //f47          n27＊＊＊＊＊＊＊
	IDI_ICON_START,   //****     28
	IDI_ICON_STOP,     //29
	IDI_ICON_STOP1,     //30
	IDI_ICON_SEARCH ,    //31
	IDI_ICON_EXCEL       //32


};

BOOL CMainFrame::InitializeOutlookBar()
{
	// Create the outbar control, set the id to the first row/col.
	if (!m_wndOutlookBar.Create(WS_CHILD|WS_VISIBLE, CRect(0,0,0,0),
		&m_wndSplitter1, m_wndSplitter1.IdFromRowCol(0, 0), OBS_XT_DEFAULT))
	{
		TRACE0("Failed to create outlook bar.");
		return FALSE;
	}
    
	// Tell the control to send message to this window (the mainframe) 
	// and not to its real parent (the splitter)
	m_wndOutlookBar.SetOwner(this);

	// Create the imagelists for the Outlook bar.
	m_ilSmallIcons.Create (16, 16, ILC_MASK | ILC_COLOR16, 2, 1);
	m_ilLargeIcons.Create (32, 32, ILC_MASK | ILC_COLOR16, 2, 1);

	// Add icons to the large and small image lists.
	for (int i = 0; i < _countof(arIcons); ++i)
	{
		HICON hIcon = AfxGetApp()->LoadIcon(arIcons[i]);
		ASSERT (hIcon != NULL);

		m_ilSmallIcons.Add (hIcon);
		m_ilLargeIcons.Add (hIcon);
	}

	//change background and text color
	m_wndOutlookBar.SetBackColor(RGB(0x33,0x66,0xff));
	m_wndOutlookBar.SetTextColor(RGB(0xff,0xff,0xff));


	// Set the large and small icons for the Outlook bar.
	m_wndOutlookBar.SetImageList(&m_ilLargeIcons, OBS_XT_LARGEICON);
	m_wndOutlookBar.SetImageList(&m_ilSmallIcons, OBS_XT_SMALLICON);

	// Add the fifth 系统功能 folder.
	m_wndOutlookBar.AddFolder(_T("◆ 系统功能"), NULL);
	m_wndOutlookBar.InsertItem(0, 0, _T("开始扫描"), 28, 0);
	m_wndOutlookBar.InsertItem(0, 1, _T("查看点号地址"), 31, 0);
	//m_wndOutlookBar.InsertItem(0, 2, _T("停止扫描/关串口"), 30, 0);
	//m_wndOutlookBar.InsertItem(0, 3, _T("暂停扫描"), 23, 0);
	m_wndOutlookBar.InsertItem(0, 2, _T("干线与串口设置"), 8, 0);
	//m_wndOutlookBar.InsertItem(0, 5, _T("初始化数据链接"), 25, 0);
	m_wndOutlookBar.InsertItem(0, 3, _T("用户管理"), 26, 0);
	m_wndOutlookBar.InsertItem(0, 4, _T("退出系统"), 27, 0);


	// Add the first folder测点编辑 to the outlook bar. Input values are folder text
	// and lParam value.
	m_wndOutlookBar.AddFolder(_T("◆ 点编辑"), NULL);

	// Insert the shortcut items into the folder we just added. Input values are
	// folder index, shortcut index, shortcut text, icon index and lParam value.
	m_wndOutlookBar.InsertItem(1, 0, _T("模拟量编辑"), 0, 0);
//	m_wndOutlookBar.InsertItem(0, 1, _T("模拟量输出点号"), 1, 0);
	m_wndOutlookBar.InsertItem(1, 1, _T("开关量输入"), 2, 0);
//	m_wndOutlookBar.InsertItem(0, 3, _T("开关量输出点号"), 3, 0);
//	m_wndOutlookBar.InsertItem(0, 4, _T("区域控制编辑器"), 4, 0);
	m_wndOutlookBar.InsertItem(1, 2, _T("报警原因编辑器"), 5, 0);
	m_wndOutlookBar.InsertItem(1, 3, _T("保存系统参数表"), 6, 0);
	m_wndOutlookBar.InsertItem(1, 4, _T("装入系统参数表"), 7, 0);


	// Add the second 通信编辑 folder.
	m_wndOutlookBar.AddFolder(_T("◆ 通信编辑"), NULL);
	m_wndOutlookBar.InsertItem(2, 0, _T("转接器汇总表"), 12, 0);
	m_wndOutlookBar.InsertItem(2, 1, _T("编辑通信参数"), 8, 0);

	// Add the second 序列编辑 folder.
	m_wndOutlookBar.AddFolder(_T("◆ 序列编辑"), NULL);
	m_wndOutlookBar.InsertItem(3, 2, _T("序列状况监视"), 9, 0);
	m_wndOutlookBar.InsertItem(3, 3, _T("编辑序列控制"), 10, 0);
	m_wndOutlookBar.InsertItem(3, 4, _T("编辑触发时间"), 11, 0);



	// Add the third 查看报表 folder.
	m_wndOutlookBar.AddFolder(_T("◆ 查看报表"), NULL);
	m_wndOutlookBar.InsertItem(4, 0, _T("测点信息报表"), 32, 0);
	m_wndOutlookBar.InsertItem(4, 1, _T("报警点报表"), 32, 0);
	m_wndOutlookBar.InsertItem(4, 2, _T("时序报表"), 32, 0);

	// Add the forth 测点控制 folder.
	m_wndOutlookBar.AddFolder(_T("◆ 测点控制"), NULL);
	m_wndOutlookBar.InsertItem(5, 0, _T("位命令"), 9, 0);
	m_wndOutlookBar.InsertItem(5, 1, _T("开关量输出"), 3, 0);
	m_wndOutlookBar.InsertItem(5, 2, _T("模拟量输出"), 22, 0);
	m_wndOutlookBar.InsertItem(5, 3, _T("ICO控制"), 1, 0);


	// Select the first folder.
	m_unOutlookbarFolderNo = 0;
	m_wndOutlookBar.SetSelFolder(m_unOutlookbarFolderNo);
	//m_wndOutlookBar.SetSmallIconView(TRUE,-1);

	// Sizing for splitter
	CRect r;
	GetClientRect(&r);
	m_wndSplitter1.SetColumnInfo( 0, r.Width()/7, 0 );
	m_wndSplitter1.SetColumnInfo( 1, r.Width()/5, 0 );
	m_wndSplitter1.SetSplitterStyle(XT_SPLIT_NOFULLDRAG);

	return TRUE;
}

LRESULT CMainFrame::OnOutbarNotify(WPARAM wParam, LPARAM lParam)
{
	int nBarAction = (int)wParam;

	// Cast the lParam to a XT_OUTBAR_INFO* struct pointer.
	XT_OUTBAR_INFO* pOBInfo = (XT_OUTBAR_INFO*)lParam;
	ASSERT(pOBInfo);

	CViewDeleteAddr dlgViewDeleteAddr;
	
	switch (nBarAction)
	{
	case OBN_XT_ITEMCLICK:
		{
			switch(m_unOutlookbarFolderNo)
			{
			case 0:
				{
					switch(pOBInfo->nIndex)
					{
					case 0:
						SetStartStopScan();
						break;
					case 1:
						dlgViewDeleteAddr.DoModal();
						break;
					//case 2:
						//m_bCloseAllSerialPort = TRUE;
						//StopScan();
						//break;
					case 2:
						OnSysTrunkvsport();
						break;
					case 3:
						OnSysUserpassword();
						break;
					case 4:
						OnAppExit();
						//PostQuitMessage(0);
						break;
					case 6:
						
						break;
					case 7:
						break;
					case 8:
						break;
					case 9:
						break;
					default:
						break;
					}
					break;
				}
			case 1:
				{
					switch(pOBInfo->nIndex)
					{
					case 0:
						PointEditAnologIn();
						break;
					case 1:
						OnMepointSwitchinput();
						break;
					case 2:
						WarnCauseEdit();
						break;
					case 3:
						break;
					case 4:
						break;
					case 5:
						break;
					case 6:
						break;
					case 7:
						break;
					case 8:
						break;
					case 9:
						break;
					default:
						break;
					}
					break;
				}
			case 2:
				{
					switch(pOBInfo->nIndex)
					{
					case 0:
						OnMepointLoadparadata();
				
						break;
					case 1:
						OnMenuCommEditparaments();
						break;
					case 2:
					//	m_wndWrkspBar.SetActiveView(2);
						break;
					case 3:
						break;
					case 4:
						break;
					case 5:
						break;
					case 6:
						break;
					case 7:
						break;
					case 8:
						break;
					case 9:
						break;
					default:
						break;
					}
					break;
				}
			case 3:
				{
					switch(pOBInfo->nIndex)
					{
					case 0:
						m_wndWrkspBar.DeleteView(2,TRUE);
						break;
					case 1:
						m_wndWrkspBar.AddView(_T("报表2"), RUNTIME_CLASS(CTabView), new CTabDoc);
						break;
					case 2:
						break;
					case 3:
						break;
					case 4:
						break;
					case 5:
						break;
					case 6:
						break;
					case 7:
						break;
					case 8:
						break;
					case 9:
						break;
					default:
						break;
					}
					break;
				}
			case 4:
				{
					switch(pOBInfo->nIndex)
					{
					case 0:
						OnMenuTableAnalog() ;
						break;
					case 1:
						break;
					case 2:
						break;
					case 3:
						break;
					case 4:
						break;
					case 5:
						break;
					case 6:
						break;
					case 7:
						break;
					case 8:
						break;
					case 9:
						break;
					default:
						break;
					}
					break;
				}
			case 5:
				{
					switch(pOBInfo->nIndex)
					{
					case 0:
						OnMenuBitcmd();
						break;
					case 1:
						break;
					case 2:
						break;
					case 3:
						break;
					case 4:
						break;
					case 5:
						break;
					case 6:
						break;
					case 7:
						break;
					case 8:
						break;
					case 9:
						break;
					default:
						break;
					}
					break;
				}

			default:
				break;
			}
		break;
		}

	case OBN_XT_FOLDERCHANGE:
		m_unOutlookbarFolderNo = pOBInfo->nIndex;
		break;
		
	case OBN_XT_ONLABELENDEDIT:
		TRACE2( "Item edited: %d, New name: %s.\n", pOBInfo->nIndex, pOBInfo->lpszText);
		break;

	case OBN_XT_ONGROUPENDEDIT:
		TRACE2( "Folder edited: %d, New name: %s.\n", pOBInfo->nIndex, pOBInfo->lpszText);
		break;
		
	case OBN_XT_DRAGITEM:
		TRACE3( "Dragging From: %d, To: %d, Name: %s.\n", pOBInfo->nDragFrom, pOBInfo->nDragTo, pOBInfo->lpszText);
		break;

	case OBN_XT_ITEMHOVER:
		TRACE2( "Hovering Item: %d, Name: %s.\n", pOBInfo->nIndex, pOBInfo->lpszText);
		break;
		
	case OBN_XT_DELETEITEM:
		
		if (!m_bDestroy && AfxMessageBox(_T("Are you sure you want to remove this folder shortcut?"),
			MB_ICONWARNING|MB_YESNO) == IDNO)
		{
			// The user selected No, return FALSE to abort the action.
			return FALSE;
		}
		TRACE2( "Item deleted: %d, Name: %s.\n", pOBInfo->nIndex, pOBInfo->lpszText);
		break;
		
	case OBN_XT_DELETEFOLDER:
		if (!m_bDestroy && AfxMessageBox(_T("Are you sure you want to remove the specified folder?"),
			MB_ICONWARNING|MB_YESNO) == IDNO)
		{
			// The user selected No, return FALSE to abort the action.
			return FALSE;
		}
		TRACE2( "Folder deleted: %d, Name: %s.\n", pOBInfo->nIndex, pOBInfo->lpszText);
		break;
	}

	return TRUE;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	//cs.style = WS_CAPTION| WS_VISIBLE |  WS_CLIPSIBLINGS | WS_OVERLAPPED ;
	//cs.dwExStyle = WS_EX_LEFT | WS_EX_LTRREADING | WS_EX_RIGHTSCROLLBAR |
              //WS_EX_WINDOWEDGE | WS_EX_CONTROLPARENT | WS_EX_APPWINDOW ;

	if( !CXTFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	// Helps to reduce screen flicker.
	cs.lpszClass = AfxRegisterWndClass(0, NULL, NULL,
		AfxGetApp()->LoadIcon(IDR_MAINFRAME));

	return TRUE;
}




/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CXTFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CXTFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

void CMainFrame::InitTabCtrlBar()
{
	// TODO: Add your own view and documents to the workspace window.
	//m_pCommStatusFM = (CCommStatusFM*)m_wndWrkspBar.AddView(_T("主屏"), RUNTIME_CLASS(CCommStatusFM));//, new CTabDoc);

	m_wndWrkspBar.AddView(_T("干线、地址监测"), RUNTIME_CLASS(CCommStatusFM));//, new CTabDoc);
	m_wndWrkspBar.AddView(_T("点监测") , RUNTIME_CLASS(CFMMonitorPoint));//, new CTabDoc);
	m_wndWrkspBar.AddView(_T("干线、地址状态"), RUNTIME_CLASS(CTrunkAdd));//, new CTabDoc);
	m_wndWrkspBar.AddView(_T("报表"), RUNTIME_CLASS(CTabView));//, new CTabDoc);
	//添加报警窗口   
///	m_wndWarningBar.AddView(_T("报警信息：点号、说明、报警原因、时间(红色报警/绿色正常)"), RUNTIME_CLASS(CWarningWin));

	// Create the image list used with the tab control bar.
	if (!m_imageList.Create(IDB_IMGLIST_TAB, 16, 1, RGB(0,255,0)))
	{
		TRACE0("Failed to create image list.\n");
		return;
	}

	// Associate the image list with the tab control bar.
	m_wndWrkspBar.SetTabImageList(&m_imageList);
	m_wndWrkspBar.SetActiveView(0);

	// Draw an edge around the control.
///	m_wndWrkspBar.ModifyStyleEx(NULL, WS_EX_STATICEDGE);;

/*	if (!m_imageList1.Create(IDB_IMGLIST_VIEW, 16, 1, RGB(0xff,0xff,0xff)))
	{
		TRACE0("Failed to create image list.\n");
		return;
	}
*/
///	m_wndWarningBar.SetTabImageList(&m_imageList1);
///	m_wndWarningBar.SetActiveView(0);
}


void CMainFrame::OnDestroy() 
{
	m_bDestroy = true;
	CXTFrameWnd::OnDestroy();
}

void CMainFrame::PointEditAnologIn()
{
	CPointEditAnologIn dlg;
	dlg.DoModal();
}

void CMainFrame::PointEditSwitchIn()
{
	CPointEditSwitchIn dlg;
	dlg.DoModal();
}

void CMainFrame::OnMepointSwitchinput() 
{
	// TODO: Add your command handler code here
	PointEditSwitchIn();
}

void CMainFrame::OnMepointAnaloginput() 
{
	// TODO: Add your command handler code here
	PointEditAnologIn();
}

void CMainFrame::OnSysUserpassword() 
{
	// TODO: Add your command handler code here
	CUserPasswdDlg dlgup;
	dlgup.DoModal();
}

void CMainFrame::WarnCauseEdit()
{
	CWarnCauseEditDlg dlg;
	dlg.DoModal();
}

void CMainFrame::OnMepointAlarmreason() 
{
	// TODO: Add your command handler code here
	WarnCauseEdit();
}

void CMainFrame::OnMepointLoadparadata() 
{
	// TODO: Add your command handler code here
	//并选择是否加载数据参数表
//	CComfirmDlg  firmdlg;
	//if(
//		firmdlg.DoModal();//==IDOK
}

void CMainFrame::OnMenuCommEditparaments() 
{
	// TODO: Add your command handler code here
	CCommParaDlg commparadlg;
	commparadlg.DoModal();
}

void CMainFrame::AddFxStaticText()
{
	if (!m_wndStaticCtrl.CreateEx(WS_EX_STATICEDGE| ES_READONLY, _T("static"), _T("        报警信息：点号、说明、报警原因、时间(红色(高)报警/橙色(低)报警/绿色正常)"),
		WS_CHILD|WS_VISIBLE, CRect(0,0,0,0), &m_wndStatusBar, 0))
	{
		TRACE0("Failed to create edit control.\n");
		return;
	}


	m_wndStaticCtrl.SetFont(&xtAfxData.font);
	
	// add the indicator to the status bar.          static
	m_wndStatusBar.AddIndicator(ID_INDICATOR_FXTEXT, 0);
	
	// Initialize the pane info and add the control.  560
	int nIndex = m_wndStatusBar.CommandToIndex(ID_INDICATOR_FXTEXT);
	ASSERT (nIndex != -1);
	
	m_wndStatusBar.SetPaneWidth(nIndex, 580);
	m_wndStatusBar.SetPaneStyle(nIndex, m_wndStatusBar.GetPaneStyle(nIndex) | SBPS_NOBORDERS);
	m_wndStatusBar.AddControl(&m_wndStaticCtrl, ID_INDICATOR_FXTEXT, FALSE);

}

void CMainFrame::AddLogoPane()
{
	if (!m_wndLogoPane.Create(_T("润蓝科技"), &m_wndStatusBar))
	{
		TRACE0("Failed to create logo control.\n");
		return;
	}


	int nWidth = m_wndLogoPane.GetTextSize().cx;
	
	// this will adjust the vertical position of the logo text.
//	m_wndLogoPane.SetOffset(1);

	// add the indicator to the status bar.
	m_wndStatusBar.AddIndicator(ID_INDICATOR_LOGO, 0);
	
	// Initialize the pane info and add the control.
	int nIndex = m_wndStatusBar.CommandToIndex(ID_INDICATOR_LOGO);
	ASSERT (nIndex != -1);
	
	m_wndStatusBar.SetPaneWidth(nIndex, nWidth);
	m_wndStatusBar.SetPaneStyle(nIndex, m_wndStatusBar.GetPaneStyle(nIndex) | SBPS_POPOUT);
	m_wndStatusBar.AddControl(&m_wndLogoPane, ID_INDICATOR_LOGO, FALSE);

}

void CMainFrame::OnSysTrunkvsport() 
{
	// TODO: Add your command handler code here
	//干线与串口号对应关系设置
	CSetPortVsTrunkDlg setporttrunkdlg;
	setporttrunkdlg.DoModal();
}


void CMainFrame::StartScan()
{
	m_pCommStatusFM->m_bStartScan=TRUE;
	m_pCommStatusFM->StartScan();
}

void CMainFrame::StopScan()
{
	//m_pCommStatusFM->m_bStartScan=TRUE;
	m_pCommStatusFM->StopScan();
	if(m_bCloseAllSerialPort)
	{
		m_pCommStatusFM->CloseAllSerailPort();
		m_bCloseAllSerialPort=FALSE;
	}
}

void CMainFrame::OnMenuSysStartscan() 
{
	// TODO: Add your command handler code here
	SetStartStopScan();

   
	
}

void CMainFrame::OnMenuSysStopscan() 
{
	// TODO: Add your command handler code here
	//StopScan();
	SetStartStopScan();

}

void CMainFrame::SetStartStopScan()
{
	m_bStartStopScan=!m_bStartStopScan;
	if(m_bStartStopScan)
	{
		m_pCommStatusFM->m_bStartScan=TRUE;
		if(!m_pCommStatusFM->StartScan())
		{
			m_bStartStopScan=!m_bStartStopScan;
			return;
		}
		//StartScan();
		m_wndOutlookBar.SetSelFolder( 0 );
		m_wndOutlookBar.SetItemImage(0,30 );
		m_wndOutlookBar.SetItemText(0,"停止扫描" );
	}
	else
	{
		StopScan();
		m_wndOutlookBar.SetSelFolder( 0 );
		m_wndOutlookBar.SetItemImage(0,28 );
		m_wndOutlookBar.SetItemText(0,"开始扫描" );
	}
}

void CMainFrame::OnMenuBitcmd() 
{
	// TODO: Add your command handler code here
	CBitCmdCtrlDlg BitCmdCtrlDlg;
	BitCmdCtrlDlg.DoModal();
}

void CMainFrame::OnMepointCtrlSwitchoutput() 
{
	// TODO: Add your command handler code here
//	CCtrlCmdDlg* pCtrlCmdDlg;
//	pCtrlCmdDlg=new CCtrlCmdDlg;
//	pCtrlCmdDlg->DoModal();
//	delete pCtrlCmdDlg;
	CCtrlCmdDlg  pCtrlCmdDlg;
	pCtrlCmdDlg.DoModal();
}

void CMainFrame::OnMenuTableAnalog() 
{
	// TODO: Add your command handler code here
	CViewDeleteAddr dlgViewDeleteAddr;
	dlgViewDeleteAddr.DoModal();
}

void CMainFrame::OnAppExit() 
{
	// TODO: Add your command handler code here
	//modified   2003/8/15
	CLoginDlg dlg;
	dlg.m_bLogInOut=1;
	if(dlg.DoModal()==IDCANCEL)
		return;
	
	PostQuitMessage(0);

}

LRESULT CMainFrame::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	// TODO: Add your specialized code here and/or call the base class
	switch(message)
	{
	case WM_SYSCOMMAND:

      switch(wParam )
      {
      case SC_MAXIMIZE:
      break;
      case SC_MINIMIZE:
      break;
      case SC_CLOSE:
		  
		  OnAppExit();
		  return 0;
      break;
      };
		break;
	}
	

	return CXTFrameWnd::DefWindowProc(message, wParam, lParam);
}

void CMainFrame::OnMepointCtrlAnalogoutput() 
{
	// TODO: Add your command handler code here
	CAnologOutDlg  AnologOutDlg;
	AnologOutDlg.DoModal();
	
}

void CMainFrame::OnMepointCtrlGasinspect() 
{
	// TODO: Add your command handler code here
	CIcoControl  IcoControl;
	IcoControl.DoModal();
	
}

void CMainFrame::OnMenuSquenceCommonreg() 
{
	// TODO: Add your command handler code here
	CdialogR dlg;
  
	dlg.DoModal();
}

void CMainFrame::OnMenuSquenceStart() 
{
	// TODO: Add your command handler code here
	CKJMonitorApp* pApp=(CKJMonitorApp* )AfxGetApp();
///    if(!StartSequence)
///       	pApp->pMPT->InitSequence();
 //	this->Enable(FALSE);

}

void CMainFrame::OnMenuSquenceEnd() 
{
	// TODO: Add your command handler code here
	CKJMonitorApp* pApp=(CKJMonitorApp* )AfxGetApp();
    if(StartSequence)
         pApp->pMPT->EndSequence();

//    EnableMenuItem(hMenu,ID_MENU_SQUENCE_END,MFS_GRAYED|MF_BYCOMMAND);
}

void CMainFrame::OnMenuSquenceEdit() 
{
	// TODO: Add your command handler code here
             dlgshixu.DoModal();
}

void CMainFrame::OnMenuSquenceMonitor() 
{
	// TODO: Add your command handler code here
	  dlg_spumonitor.DoModal();	
}

void CMainFrame::OnMenuSquenceTrigPointedit() 
{
	// TODO: Add your command handler code here
		CDialogFeg  dlg;
	dlg.DoModal();
}

void CMainFrame::OnMenuSquenceTime() 
{
	// TODO: Add your command handler code here
    Cdialogtime dlg;
    dlg.DoModal();	
}

//以下是添加的代码
void CMainFrame::OnTimer(UINT nIDEvent) 
{
	theApp.Checked();
	CXTFrameWnd::OnTimer(nIDEvent);
}

void CMainFrame::StartTimer(int nTime)
{
	SetTimer(1,nTime,0);
}

void CMainFrame::StopTimer()
{
	KillTimer(1);
}

//调用同步对话框
void CMainFrame::OnSyncSync() 
{
	if(bIsClient)
	{
		CSyncDlg DlgSync;
		DlgSync.DoModal();
	}
	else
		AfxMessageBox("本机是主机不需要同步!");
}

void CMainFrame::OnUpdateMenuSysStartscan(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if(m_bStartStopScan==FALSE)
        pCmdUI->Enable(TRUE);
	else
        pCmdUI->Enable(FALSE);
	
}

void CMainFrame::OnUpdateMenuSysStopscan(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if(m_bStartStopScan==FALSE)
        pCmdUI->Enable(FALSE);
	else
        pCmdUI->Enable(TRUE);
	
}

void CMainFrame::OnUpdateMenuSquenceStart(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if(StartSequence==FALSE)
        pCmdUI->Enable(TRUE);
	else
        pCmdUI->Enable(FALSE);
	
}

void CMainFrame::OnUpdateMenuSquenceEnd(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if(StartSequence==FALSE)
        pCmdUI->Enable(FALSE);
	else
        pCmdUI->Enable(TRUE);
	
}

