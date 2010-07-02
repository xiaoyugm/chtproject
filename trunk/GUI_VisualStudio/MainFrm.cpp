// MainFrm.cpp : implementation of the CMainFrame class
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

#include "MainFrm.h"
#include "DynamicHelpView.h"

#include "FlatTabViewView.h"
#include "FlatTabViewDoc.h"
#include "ChildFrm.h"
#include "SettingHostDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)   
	ON_WM_CREATE()
	ON_COMMAND(ID_WINDOW_AUTOHIDEALL, OnWindowAutohideall)
	ON_COMMAND(ID_WINDOW_MORE, OnWindowMore)
	ON_WM_CLOSE()
	ON_COMMAND(ID_OnSimulation, OnSimulation)
	ON_COMMAND(ID_OnGenus, OnGenus)
	ON_COMMAND(ID_MANIPULATE, OnSoundPath)
	ON_UPDATE_COMMAND_UI(ID_MANIPULATE, OnUpdateOnSoundPath)
	ON_COMMAND(ID_D_D, OnDigital)
	ON_COMMAND(ID_A_D, OnAnalog)
	ON_COMMAND(ID_LOCALTION, OnLocation)
	ON_COMMAND(ID_BROWSERMOD, OnPBrowser)
	ON_COMMAND(ID_CONTROLTABLE, OnControlT)
	ON_COMMAND(ID_CONTROLS, OnControlS)
	ON_COMMAND(ID_CONTROLF, OnControlF)
//	ON_MESSAGE(WM_XTP_PRETRANSLATEMOUSEMSG, OnTabbarMouseMsg)  
//    ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_INFO, OnSelchangeTabInfo)
	//}}AFX_MSG_MAP
	ON_MESSAGE(XTPWM_DOCKINGPANE_NOTIFY, OnDockingPaneNotify)

	ON_COMMAND(ID_VIEW_FULLSCREEN, OnFullScreen)
	ON_UPDATE_COMMAND_UI(ID_VIEW_FULLSCREEN, OnUpdateFullScreen)

	ON_COMMAND_RANGE(ID_VIEW_SOLUTIONEXPLORER, ID_VIEW_TOOLBOX, OnShowView)
	ON_COMMAND_RANGE(ID_VIEW_CLASSVIEW, ID_HELP_DYNAMICHELP, OnShowViewOther)

	ON_COMMAND(ID_VIEW_OTHER, OnViewOther)
	ON_UPDATE_COMMAND_UI(ID_VIEW_OTHER, OnUpdateViewOther)
	ON_COMMAND_RANGE(ID_FILE_NEW_PROJECT + 1, 200, OnEmptyCommandRange)

//	ON_COMMAND(XTP_ID_CUSTOMIZE, OnCustomize)
//	ON_XTP_CREATECONTROL()

	ON_COMMAND_RANGE(ID_THEME_VC6, ID_THEME_VC9, OnTheme)
	ON_UPDATE_COMMAND_UI_RANGE(ID_THEME_VC6, ID_THEME_VC9, OnUpdateTheme)

#ifdef _XTP_INCLUDE_SKINFRAMEWORK
	ON_COMMAND_RANGE(ID_SKINFRAMEWORK_VISTABLUE, ID_SKINFRAMEWORK_SYSTEM, OnSkinFramework)
	ON_COMMAND_RANGE(ID_THEME_SKINFRAMEWORK, ID_THEME_SKINFRAMEWORK, OnEmptyCommandRange)
#endif

	ON_XTP_EXECUTE(ID_EDIT_STATE, OnEditState)
	ON_UPDATE_COMMAND_UI(ID_EDIT_STATE, OnUpdateEditState)

	ON_XTP_EXECUTE(ID_EDIT_PLATFORM, OnEditPlatform)
	ON_UPDATE_COMMAND_UI(ID_EDIT_PLATFORM, OnUpdateEditPlatform)
	ON_WM_ACTIVATE()

	ON_COMMAND(ID_HELP_FINDER, CXTPMDIFrameWnd::OnHelpFinder)
	ON_COMMAND(ID_HELP, CXTPMDIFrameWnd::OnHelp)
	ON_COMMAND(ID_CONTEXT_HELP, CXTPMDIFrameWnd::OnContextHelp)
	ON_COMMAND(ID_DEFAULT_HELP, CXTPMDIFrameWnd::OnHelpFinder)

END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
//    ID_MOUSCAPTION,
//	ID_MOUSPOINT,
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
//	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	m_nState = 1;
	m_nPlatform = 0;
	m_bFullScreen = FALSE;
	m_bSoundPath = TRUE;

	// get path of executable
	TCHAR szBuff[_MAX_PATH];
	VERIFY(::GetModuleFileName(AfxGetInstanceHandle(), szBuff, _MAX_PATH));

	LPTSTR lpszExt = _tcsrchr(szBuff, '.');
	lstrcpy(lpszExt, _T(".xml"));

	m_strIniFileName = szBuff;

	m_pFullScreenLayout = NULL;
	m_rcMainFrame.SetRectEmpty();

	m_nTheme = ID_THEME_VC9;

	m_nOtherView = ID_VIEW_CLASSVIEW;

#ifdef _XTP_INCLUDE_SKINFRAMEWORK
	XTPSkinManager()->GetResourceFile()->SetModuleHandle(AfxGetInstanceHandle());
#endif

//	m_pSampleFormView = NULL;
	m_ontime =0;

}

CMainFrame::~CMainFrame()
{
	if (m_pFullScreenLayout)
	{
		delete m_pFullScreenLayout;
	}
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

//	XTThemeManager()->SetTheme(xtThemeOffice2003);

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	if (!InitCommandBars())
		return -1;

	CXTPPaintManager::SetTheme(xtpThemeOffice2003);  //xtpThemeVisualStudio2008

	CXTPCommandBars* pCommandBars = GetCommandBars();

	CXTPCommandBar* pMenuBar = pCommandBars->SetMenu(_T("Menu Bar"), IDR_MAINFRAME);
	pMenuBar->SetFlags(xtpFlagIgnoreSetMenuMessage | xtpFlagHideMDIButtons);  //main  IDR_MAINFRAME

/*	CXTPToolBar* pCommandBar = (CXTPToolBar*)pCommandBars->Add(_T("Standard"), xtpBarTop);
	if (!pCommandBar ||
		!pCommandBar->LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;
	}

/*	CXTPToolBar* pWebBar = (CXTPToolBar*)pCommandBars->Add(_T("Web"), xtpBarTop);
	if (!pWebBar ||
		!pWebBar->LoadToolBar(IDR_TOOLBAR_WEB))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;
	}*/

//	CXTPToolBar* pThemeBar = (CXTPToolBar*)pCommandBars->Add(_T("Theme"), xtpBarTop);
//	if (!pThemeBar ||
//		!pThemeBar->LoadToolBar(IDR_TOOLBAR_THEME))
	{
//		TRACE0("Failed to create toolbar\n");
//		return -1;
	}
/*	DockRightOf(pThemeBar, pWebBar);

	CXTPToolBar* pFullScreenBar = (CXTPToolBar*)pCommandBars->Add(_T("Full Screen"), xtpBarTop);
	if (!pFullScreenBar ||
		!pFullScreenBar->LoadToolBar(IDR_TOOLBAR_FULLSCREEN))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;
	}
	pFullScreenBar->SetVisible(FALSE);*/

	XTPPaintManager()->GetIconsInfo()->bUseDisabledIcons = TRUE;
//	XTPImageManager()->SetIcons(IDR_TOOLBAR_EXT);

	pCommandBars->GetCommandBarsOptions()->ShowKeyboardCues(xtpKeyboardCuesShowWindowsDefault);
	pCommandBars->GetToolTipContext()->SetStyle(xtpToolTipOffice);
	pCommandBars->GetShortcutManager()->SetAccelerators(IDR_MAINFRAME);

//	CreateToolBox();

	m_paneManager.InstallDockingPanes(this);
	m_paneManager.SetTheme(xtpPaneThemeVisualStudio2005);
	
	CXTPDockingPane* paneResourceView = m_paneManager.CreatePane(
		ID_VIEW_RESOURCEVIEW, CRect(0, 0, 100, 170), xtpPaneDockBottom);
/*	CXTPDockingPane* paneResourceView1 = m_paneManager.CreatePane(
		ID_VIEW_RESOURCEVIEW2, CRect(0, 0, 100, 135), xtpPaneDockBottom);
	CXTPDockingPane* paneResourceView2 = m_paneManager.CreatePane(
		ID_VIEW_RESOURCEVIEW3, CRect(0, 0, 100, 135), xtpPaneDockBottom);
	CXTPDockingPane* paneResourceView3 = m_paneManager.CreatePane(
		ID_VIEW_RESOURCEVIEW4, CRect(0, 0, 100, 135), xtpPaneDockBottom);
	CXTPDockingPane* paneResourceView4 = m_paneManager.CreatePane(
		ID_VIEW_RESOURCEVIEW5, CRect(0, 0, 100, 135), xtpPaneDockBottom);
	CXTPDockingPane* paneResourceView5 = m_paneManager.CreatePane(
		ID_VIEW_RESOURCEVIEW6, CRect(0, 0, 100, 135), xtpPaneDockBottom);*/
//	CXTPDockingPane* paneResourceView6 = m_paneManager.CreatePane(
//		ID_VIEW_RESOURCEVIEW7, CRect(0, 0, 100, 135), xtpPaneDockBottom);
//		ID_WINDOWS_OUTPUT, CRect(0, 0, 150, 120), xtpPaneDockBottom);
	
//	CXTPDockingPane* paneToolBox = m_paneManager.CreatePane(
//		ID_VIEW_TOOLBOX, CRect(0, 0, 200, 120), xtpPaneDockRight);
	
	CXTPDockingPane* paneClassView = m_paneManager.CreatePane(
		ID_VIEW_CLASSVIEW, CRect(0, 0, 230, 135), xtpPaneDockBottom);  //xtpPaneDockLeft
	
	CXTPDockingPane* paneSolutionExplorer = m_paneManager.CreatePane(
		ID_VIEW_SOLUTIONEXPLORER, CRect(0, 0, 230, 135), xtpPaneDockBottom);  //xtpPaneDockLeft
	
/*	CXTPDockingPane* paneResourceView = m_paneManager.CreatePane(
		ID_VIEW_RESOURCEVIEW, CRect(0, 0, 230, 140), xtpPaneDockLeft);

	CXTPDockingPane* paneHelpView =m_paneManager.CreatePane(
		ID_HELP_DYNAMICHELP, CRect(0, 0, 210, 140), xtpPaneDockBottom, paneToolBox);

	paneHelpView->Close();
*/
/*	m_paneManager.AttachPane(paneResourceView2, paneResourceView1);
	m_paneManager.AttachPane(paneResourceView3, paneResourceView2);
	m_paneManager.AttachPane(paneResourceView4, paneResourceView3);
	m_paneManager.AttachPane(paneResourceView5, paneResourceView4);
	m_paneManager.AttachPane(paneResourceView6, paneResourceView5);*/
	m_paneManager.AttachPane(paneClassView,paneResourceView );
	m_paneManager.AttachPane(paneSolutionExplorer,paneClassView);

	paneResourceView->Select();
	
//	m_paneManager.CreatePane(
//		ID_VIEW_PROPERTIESWINDOW, CRect(0, 0, 180, 140), xtpPaneDockBottom, paneClassView);

	m_paneManager.EnableKeyboardNavigate();
	

	//CXTPPropExchangeIniFile px(TRUE, 0, _T("Settings")); // To serialize to ini file
/*	CXTPPropExchangeXMLNode px(TRUE, 0, _T("Settings"));   // To serialize to XML file

	if (px.LoadFromFile(m_strIniFileName))
	{
		CXTPPropExchangeSection pxTaskPanel(px.GetSection(_T("TaskPanel")));
		m_wndTaskPanel.GetGroups()->DoPropExchange(&pxTaskPanel);

		CXTPPropExchangeSection pxNormalLayout(px.GetSection(_T("NormalLayout")));
		ExchangeLayout(&pxNormalLayout);

		m_pFullScreenLayout = DYNAMIC_DOWNCAST(CXTPPropExchangeXMLNode, px.GetSection(_T("FullScreenLayout")));
		ASSERT(m_pFullScreenLayout);
	}
	else
	{
		ResetToolboxItems();		
	}
*/
	CXTPImageManager* pImageManager = pCommandBars->GetImageManager();

	pImageManager->InternalAddRef();
	m_paneManager.SetImageManager(pImageManager);

	m_paneManager.SetAlphaDockingContext(TRUE);
	m_paneManager.SetShowDockingContextStickers(TRUE);
	m_paneManager.SetShowContentsWhileDragging(TRUE);
	m_paneManager.SetDefaultPaneOptions(xtpPaneNoCloseable |xtpPaneNoHoverShow
		| xtpPaneNoHideable |xtpPaneNoDockable |xtpPaneNoCaption
//		|xtpPaneDisabled |xtpPaneNoFloatable |xtpPaneNoFloatableByTabDoubleClick|xtpPaneNoFloatableByCaptionDoubleClick
		); //xtpPaneHasMenuButton  xtpPaneNoFloatable

	VERIFY(m_MTIClientWnd.Attach(this, TRUE));
//	m_MTIClientWnd.EnableToolTips();
	m_MTIClientWnd.SetFlags(xtpWorkspaceHideClose);   //child
	XTPImageManager()->SetIcons(IDR_DRAWTYPE);

	m_MTIClientWnd.GetPaintManager()->m_bShowIcons = FALSE;  //FALSE
//	m_MTIClientWnd.SetNewTabPosition(xtpWorkspaceNewTabLeftMost);
//	m_MTIClientWnd.SetFlags(xtpWorkspaceHideArrowsAlways | xtpWorkspaceShowActiveFiles);

	CXTPOffice2003Theme::LoadModernToolbarIcons(IDR_MAINFRAME);
//	CXTPOffice2003Theme::LoadModernToolbarIcons(IDR_BORDERS);

	m_wndStatusBar.GetPane(0)->SetBeginGroup(FALSE);
	AddLogo();
	m_wndStatusBar.SetRibbonDividerIndex(m_wndStatusBar.GetPaneCount() - 1);
	AddEdit();
//	AddProgress();
//	AddAnimation();
//	AddSwitchButtons();
//	AddZoomButton();
//	AddZoomSlider();
	m_wndStatusBar.EnableCustomization();
	
	// Load the previous state for command bars.
	LoadCommandBars(_T("CommandBars"));
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
//资源窗口->String Table->IDR_MAINFRAME中内容若为
//“MyDraw\n绘图\nMyDraw\n图像文件 (*.hss)\n.hss\nMyDrow.Document\nMyDrow Document”
//则标题为“绘图-MyDraw”  保存文件后缀名为.hss
//\nRSDraw\nRSDraw\nRSDraw 文件 (*.rsy)\n.rsy\nRsy.Object\nRsy Document
//隐藏部分文件扩展名
//在资源管理器中单击“工具→文件夹选项”，可以选择“隐藏已知文件类型的扩展名”将所有文件
//的扩展名隐藏起来。不过，如果你只想隐藏部分文件扩展名，那还要借助注册表编辑器：单击
//“开始→运行”，键入“Regedit”后回车，在注册表编辑器中展开 [HKEY_CLASSES_ROOT]分支，
//找到要隐藏的文件扩展名并展开，然后在右侧窗口中新建字符串值“NeverShowExt”，退出注册表
//编辑器重新启动计算机后，该类型文件的扩展名将会自动隐藏起来。

	//主窗口的标题
//    m_strTitle ="煤矿安全监测";
	if( !CMDIFrameWnd::PreCreateWindow(cs) )
		return FALSE;

//	cs.lpszClass = _T("XTPMainFrame");
//	CXTPDrawHelpers::RegisterWndClass(AfxGetInstanceHandle(), cs.lpszClass, 
//		CS_DBLCLKS, AfxGetApp()->LoadIcon(IDR_MAINFRAME));
	cs.style = WS_OVERLAPPED | WS_CAPTION | FWS_ADDTOTITLE
		| WS_THICKFRAME | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_MAXIMIZE ;

//	cs.style&=~(LONG)FWS_ADDTOTITLE;     //去掉标题栏前半部分和“—”
	// Helps to reduce screen flicker.
//	cs.lpszClass = AfxRegisterWndClass(0, NULL, NULL,
//		AfxGetApp()->LoadIcon(IDR_MAINFRAME));

	return TRUE;
}


LRESULT CMainFrame::OnTabbarMouseMsg(WPARAM wParam,LPARAM lParam)
{

	if (wParam != WM_RBUTTONDOWN)
		return FALSE;

	CPoint point = CPoint((DWORD)lParam);
	CXTPTabManagerItem* pItem =  m_MTIClientWnd.HitTest(point);

	if (pItem)
	{
		CWnd* pFrame = CWnd::FromHandle(pItem->GetHandle());
		MDIActivate(pFrame);

		m_MTIClientWnd.Refresh();

		CMenu menu;
		VERIFY(menu.LoadMenu(IDR_POPUP_TABS));
		CMenu* pPopup = menu.GetSubMenu(0);


		m_MTIClientWnd.WorkspaceToScreen(&point);

		CXTPCommandBars::TrackPopupMenu(pPopup, 0, point.x, point.y, this);

		m_MTIClientWnd.Refresh();

		return TRUE;
	}
	return FALSE;
}


/*
BOOL CMainFrame::ShowWindowEx(int nCmdShow)
{
	ASSERT_VALID(this);

	// Restore control bar postion.
	LoadBarState(_T("Control Bar State"));

	// Restore frame window size and position.
	m_wndPosition.LoadWindowPos(this);
	nCmdShow = m_wndPosition.showCmd;

	return ShowWindow(nCmdShow);
}
*/

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CMDIFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CMDIFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers


CXTPTaskPanelGroup* CMainFrame::CreateToolboxGroup(UINT nID)
{
	CXTPTaskPanelGroup* pFolder = m_wndTaskPanel.AddGroup(nID);

	CXTPTaskPanelGroupItem* pPointer = pFolder->AddLinkItem(ID_TOOLBOXITEM_POINTER, 0);
	pPointer->SetItemSelected(TRUE);
	pPointer->AllowDrag(FALSE);
	pPointer->AllowDrop(FALSE);

	return pFolder;
}

void CMainFrame::ResetToolboxItems()
{
	m_wndTaskPanel.GetGroups()->Clear(FALSE);

	CXTPTaskPanelGroup* pFolderPropertyPanes = CreateToolboxGroup(ID_TOOLBOXFOLDER_PROPERTYPANES);

	CXTPTaskPanelGroup* pFolderData = CreateToolboxGroup(ID_TOOLBOXFOLDER_DATA);
	pFolderData->AddLinkItem(ID_TOOLBOXITEM_DATASET                 ,26);
	pFolderData->AddLinkItem(ID_TOOLBOXITEM_OLEDBDATAADAPTER        ,27);
	pFolderData->AddLinkItem(ID_TOOLBOXITEM_OLEDBCONNECTION         ,28);
	pFolderData->AddLinkItem(ID_TOOLBOXITEM_OLEDBCOMMAND            ,29);
	pFolderData->AddLinkItem(ID_TOOLBOXITEM_SQLDATAADAPTER          ,30);
	pFolderData->AddLinkItem(ID_TOOLBOXITEM_SQLCONNECTION           ,31);
	pFolderData->AddLinkItem(ID_TOOLBOXITEM_SQLCOMMAND              ,32);
	pFolderData->AddLinkItem(ID_TOOLBOXITEM_DATAVIEW                ,33);

	CXTPTaskPanelGroup* pFolderComponents = CreateToolboxGroup(ID_TOOLBOXFOLDER_COMPONENTS);
	pFolderComponents->AddLinkItem(ID_TOOLBOXITEM_FILESYSTEMWATCHER     ,34);
	pFolderComponents->AddLinkItem(ID_TOOLBOXITEM_EVENTLOG              ,35);
	pFolderComponents->AddLinkItem(ID_TOOLBOXITEM_DIRECTORYENTRY        ,36);
	pFolderComponents->AddLinkItem(ID_TOOLBOXITEM_DIRECTORYSEARCHER     ,37);
	pFolderComponents->AddLinkItem(ID_TOOLBOXITEM_MESSAGEQUEUE          ,38);
	pFolderComponents->AddLinkItem(ID_TOOLBOXITEM_PERFORMANCECOUNTER    ,39);
	pFolderComponents->AddLinkItem(ID_TOOLBOXITEM_PROCESS               ,40);
	pFolderComponents->AddLinkItem(ID_TOOLBOXITEM_SERVICECONTROLLER     ,41);
	pFolderComponents->AddLinkItem(ID_TOOLBOXITEM_TIMER                 ,42);


	CXTPTaskPanelGroup* pFolderWindowsForms = CreateToolboxGroup(ID_TOOLBOXFOLDER_WINDOWSFORMS);
	pFolderWindowsForms->AddLinkItem(ID_TOOLBOXITEM_BUTTON,             1);
	pFolderWindowsForms->AddLinkItem(ID_TOOLBOXITEM_CHECK_BOX,              2);
	pFolderWindowsForms->AddLinkItem(ID_TOOLBOXITEM_EDIT_CONTROL,           3);
	pFolderWindowsForms->AddLinkItem(ID_TOOLBOXITEM_COMBO_BOX,              4);
	pFolderWindowsForms->AddLinkItem(ID_TOOLBOXITEM_LIST_BOX,               5);
	pFolderWindowsForms->AddLinkItem(ID_TOOLBOXITEM_GROUP_BOX,              6);
	pFolderWindowsForms->AddLinkItem(ID_TOOLBOXITEM_RADIO_BUTTON,           7);
	pFolderWindowsForms->AddLinkItem(ID_TOOLBOXITEM_STATIC_TEXT,            8);
	pFolderWindowsForms->AddLinkItem(ID_TOOLBOXITEM_PICTURE_CONTROL,        9);
	pFolderWindowsForms->AddLinkItem(ID_TOOLBOXITEM_HORIZONTAL_SCROLL_BAR,  10);
	pFolderWindowsForms->AddLinkItem(ID_TOOLBOXITEM_VERTICAL_SCROLL_BAR,    11);
	pFolderWindowsForms->AddLinkItem(ID_TOOLBOXITEM_SLIDER_CONTROL,     12);
	pFolderWindowsForms->AddLinkItem(ID_TOOLBOXITEM_SPIN_CONTROL,           13);
	pFolderWindowsForms->AddLinkItem(ID_TOOLBOXITEM_PROGRESS_CONTROL,       14);
	pFolderWindowsForms->AddLinkItem(ID_TOOLBOXITEM_HOT_KEY,                15);
	pFolderWindowsForms->AddLinkItem(ID_TOOLBOXITEM_LIST_CONTROL,           16);
	pFolderWindowsForms->AddLinkItem(ID_TOOLBOXITEM_TREE_CONTROL,           17);
	pFolderWindowsForms->AddLinkItem(ID_TOOLBOXITEM_TAB_CONTROL,            18);
	pFolderWindowsForms->AddLinkItem(ID_TOOLBOXITEM_ANIMATION_CONTROL,      19);
	pFolderWindowsForms->AddLinkItem(ID_TOOLBOXITEM_RICH_EDIT_CONTROL,      20);
	pFolderWindowsForms->AddLinkItem(ID_TOOLBOXITEM_DATE_TIME_PICKER,       21);
	pFolderWindowsForms->AddLinkItem(ID_TOOLBOXITEM_MONTH_CALENDAR_CONTROL,22);
	pFolderWindowsForms->AddLinkItem(ID_TOOLBOXITEM_IP_ADDRESS_CONTROL, 23);
	pFolderWindowsForms->AddLinkItem(ID_TOOLBOXITEM_EXTENDED_COMBO_BOX, 24);
	pFolderWindowsForms->AddLinkItem(ID_TOOLBOXITEM_CUSTOM_CONTROL,     25);

	CreateToolboxGroup(ID_TOOLBOXFOLDER_CLIPBOARDRING);
	CreateToolboxGroup(ID_TOOLBOXFOLDER_GENERAL);

	pFolderPropertyPanes->SetExpanded(TRUE);

}

CWnd* CMainFrame::CreateToolBox()
{
	if (!m_wndTaskPanel.GetSafeHwnd())
	{
		if (!m_wndTaskPanel.Create(WS_CHILD|WS_VISIBLE|WS_CLIPSIBLINGS|WS_CLIPCHILDREN, CRect(0, 0, 0, 0), this, 0))
			return FALSE;
		
		m_wndTaskPanel.SetOwner(this);
		
		m_wndTaskPanel.GetImageManager()->SetIcons(IDB_TOOLBOXICONS, 0, 0, CSize(16, 16));
		m_wndTaskPanel.SetBehaviour(xtpTaskPanelBehaviourExplorer);
		m_wndTaskPanel.SetTheme(xtpTaskPanelThemeToolboxWhidbey);
		m_wndTaskPanel.SetHotTrackStyle(xtpTaskPanelHighlightItem);
		m_wndTaskPanel.SetSelectItemOnFocus(TRUE);
		m_wndTaskPanel.SetSingleSelection();
		m_wndTaskPanel.AllowDrag(TRUE);		
	}
	
	return &m_wndTaskPanel;
}


void CMainFrame::ShowDockingPanePopupMenu(CXTPDockingPane* pPopupPane, CPoint pt, LPRECT lprcExclude)
{
	CMenu menu;
	VERIFY(menu.LoadMenu(IDR_POPUP_PANES));
	CMenu* pPopup = menu.GetSubMenu(0);
	
	
	if (pPopupPane->IsHidden())
	{
		pPopup->CheckMenuItem(ID_POPUP_AUTOHIDE, MF_BYCOMMAND|MF_CHECKED);
		pPopup->EnableMenuItem(ID_POPUP_FLOATING, MF_BYCOMMAND|MF_DISABLED);
		pPopup->EnableMenuItem(ID_POPUP_DOCKABLE, MF_BYCOMMAND|MF_DISABLED);
	}
	else if (pPopupPane->GetOptions() & xtpPaneNoDockable)
	{
		pPopup->CheckMenuItem(ID_POPUP_FLOATING, MF_BYCOMMAND|MF_CHECKED);
	}
	else
	{
		pPopup->CheckMenuItem(ID_POPUP_DOCKABLE, MF_BYCOMMAND|MF_CHECKED);
	}

	TPMPARAMS tpm;
	tpm.cbSize = sizeof(TPMPARAMS);
	tpm.rcExclude = lprcExclude ? *lprcExclude : CRect(0, 0, 0, 0);

	int nCommand = GetCommandBars()->TrackPopupMenuEx(pPopup, TPM_RIGHTBUTTON|TPM_NONOTIFY|TPM_RETURNCMD, pt.x, pt.y, NULL, &tpm);
	
	switch (nCommand)
	{
	case ID_POPUP_HIDE:
		pPopupPane->Close();
		break;		
		
	case ID_POPUP_AUTOHIDE:
		m_paneManager.ToggleAutoHide(pPopupPane);
		break;

	case ID_POPUP_DOCKABLE:
		if (pPopupPane->GetOptions() & xtpPaneNoDockable)
		{
			pPopupPane->SetOptions(pPopupPane->GetOptions() & ~xtpPaneNoDockable);
		}
		break;

	case ID_POPUP_FLOATING:
		if ((pPopupPane->GetOptions() & xtpPaneNoDockable) == 0)
		{
			if (!pPopupPane->IsFloating())
				m_paneManager.ToggleDocking(pPopupPane);
			
			pPopupPane->SetOptions(pPopupPane->GetOptions() | xtpPaneNoDockable);
		}

		break;
	}
}
	
LRESULT CMainFrame::OnDockingPaneNotify(WPARAM wParam, LPARAM lParam)
{
	if (wParam == XTP_DPN_SHOWWINDOW)
	{
		CXTPDockingPane* pPane = (CXTPDockingPane*)lParam;

		if (!pPane->IsValid())
		{
			switch (pPane->GetID())
			{
//				case ID_VIEW_TOOLBOX:					
//					pPane->Attach(CreateToolBox());
//					break;

				case ID_VIEW_CLASSVIEW:
					if (!m_wndClassView.GetSafeHwnd())
					{
						m_wndClassView.Create(_T("STATIC"), NULL, WS_CHILD|WS_VISIBLE|WS_CLIPCHILDREN|WS_CLIPSIBLINGS, CXTPEmptyRect(), this, 0);
					}
					pPane->Attach(&m_wndClassView);
					break;

				case ID_VIEW_RESOURCEVIEW:
					if (!m_wndResourceView.GetSafeHwnd())
					{
						m_wndResourceView.Create(_T("STATIC"), NULL, WS_CHILD|WS_VISIBLE|WS_CLIPCHILDREN|WS_CLIPSIBLINGS, CXTPEmptyRect(), this, 0);
					}
					pPane->Attach(&m_wndResourceView);
					break;
/*				case ID_VIEW_RESOURCEVIEW2:
					if (!m_wndResourceView1.GetSafeHwnd())
					{
						m_wndResourceView1.Create(_T("STATIC"), NULL, WS_CHILD|WS_VISIBLE|WS_CLIPCHILDREN|WS_CLIPSIBLINGS, CXTPEmptyRect(), this, 0);
					}
					pPane->Attach(&m_wndResourceView1);
					break;
				case ID_VIEW_RESOURCEVIEW3:
					if (!m_wndResourceView2.GetSafeHwnd())
					{
						m_wndResourceView2.Create(_T("STATIC"), NULL, WS_CHILD|WS_VISIBLE|WS_CLIPCHILDREN|WS_CLIPSIBLINGS, CXTPEmptyRect(), this, 0);
					}
					pPane->Attach(&m_wndResourceView2);
					break;
				case ID_VIEW_RESOURCEVIEW4:
					if (!m_wndResourceView3.GetSafeHwnd())
					{
						m_wndResourceView3.Create(_T("STATIC"), NULL, WS_CHILD|WS_VISIBLE|WS_CLIPCHILDREN|WS_CLIPSIBLINGS, CXTPEmptyRect(), this, 0);
					}
					pPane->Attach(&m_wndResourceView3);
					break;
				case ID_VIEW_RESOURCEVIEW5:
					if (!m_wndResourceView4.GetSafeHwnd())
					{
						m_wndResourceView4.Create(_T("STATIC"), NULL, WS_CHILD|WS_VISIBLE|WS_CLIPCHILDREN|WS_CLIPSIBLINGS, CXTPEmptyRect(), this, 0);
					}
					pPane->Attach(&m_wndResourceView4);
					break;
				case ID_VIEW_RESOURCEVIEW6:
					if (!m_wndResourceView5.GetSafeHwnd())
					{
						m_wndResourceView5.Create(_T("STATIC"), NULL, WS_CHILD|WS_VISIBLE|WS_CLIPCHILDREN|WS_CLIPSIBLINGS, CXTPEmptyRect(), this, 0);
					}
					pPane->Attach(&m_wndResourceView5);
					break;
				case ID_VIEW_RESOURCEVIEW7:
					CWnd* pView = pPane->AttachView(this, RUNTIME_CLASS(CSampleFormView));
//					if (!m_wndResourceView6->GetSafeHwnd())
					{
//						m_wndResourceView6->Create(_T("STATIC"), NULL, WS_CHILD|WS_VISIBLE|WS_CLIPCHILDREN|WS_CLIPSIBLINGS, CXTPEmptyRect(), this, 0);
					}
//					pPane->Attach(m_wndResourceView6);
					break;*/

				case ID_VIEW_SOLUTIONEXPLORER:
//					CWnd* pView = pPane->AttachView(this, RUNTIME_CLASS(CSampleFormView));
					if (!m_wndSolutionExplorer.GetSafeHwnd())
					{
						m_wndSolutionExplorer.Create(_T("STATIC"), NULL, WS_CHILD|WS_VISIBLE|WS_CLIPCHILDREN|WS_CLIPSIBLINGS, CXTPEmptyRect(), this, 0);
					}
					pPane->Attach(&m_wndSolutionExplorer);
					break;

/*				case ID_VIEW_PROPERTIESWINDOW:   
					if (!m_wndProperties.GetSafeHwnd())
					{
						m_wndProperties.Create(_T("STATIC"), NULL, WS_CHILD|WS_VISIBLE|WS_CLIPCHILDREN|WS_CLIPSIBLINGS, CXTPEmptyRect(), this, 0);
					}
					pPane->Attach(&m_wndProperties);
					break;

				case ID_WINDOWS_OUTPUT:
					if (!m_wndOutput.GetSafeHwnd())
					{
						m_wndOutput.Create(WS_HSCROLL|ES_AUTOHSCROLL|ES_MULTILINE|WS_VISIBLE, CXTPEmptyRect(), this, 0);
					}
					pPane->Attach(&m_wndOutput);
					break;

				case ID_HELP_DYNAMICHELP:
					{
						// attach the dynamic help view to the pane.
						CWnd* pView = pPane->AttachView(this, RUNTIME_CLASS(CDynamicHelpView));
						pView;
						break;
					}*/
	
			}
		}
		return 1;
	}

/*	if (wParam == XTP_DPN_CONTEXTMENU)
	{
		XTP_DOCKINGPANE_CLICK* pClick = (XTP_DOCKINGPANE_CLICK*)lParam;

		CXTPDockingPane* pPopupPane = pClick->pPane;
		if (!pPopupPane) 
			return FALSE;

		ShowDockingPanePopupMenu(pPopupPane, pClick->pt, pClick->rcExclude);

		return TRUE;
	}*/
	
	return 0;
}

void CMainFrame::OnShowView(UINT nID)
{
	m_paneManager.ShowPane(nID);
}

void CMainFrame::OnShowViewOther(UINT nID)
{
	m_nOtherView = nID;
	m_paneManager.ShowPane(nID);
}

void CMainFrame::OnViewOther()
{
	m_paneManager.ShowPane(m_nOtherView);
}

void CMainFrame::OnUpdateViewOther(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(TRUE);
	CXTPControl* pControl = CXTPControl::FromUI(pCmdUI);

	if (pControl && pControl->GetIconId() != m_nOtherView)
	{
		pControl->SetIconId(m_nOtherView);
		
		CString strPrompt;
		strPrompt.LoadString(m_nOtherView);
		pControl->SetPrompt(strPrompt);
	}
}

void CMainFrame::OnEmptyCommandRange(UINT)
{

}

void CMainFrame::OnWindowAutohideall()
{
	CXTPDockingPaneInfoList& lstPanes = m_paneManager.GetPaneList();
	POSITION pos = lstPanes.GetHeadPosition();
	while (pos)
	{
		CXTPDockingPane* pPane = lstPanes.GetNext(pos);
		if (!pPane->IsClosed() && !pPane->IsHidden())
			m_paneManager.HidePane(pPane);
	}
}

void CMainFrame::OnWindowMore()
{
	CXTWindowList dlg(this);
	dlg.DoModal();
}


int CMainFrame::OnCreateControl(LPCREATECONTROLSTRUCT lpCreateControl)
{
	if (lpCreateControl->bToolBar)
	{
		CXTPToolBar* pToolBar = DYNAMIC_DOWNCAST(CXTPToolBar, lpCreateControl->pCommandBar);
		if (!pToolBar)
			return FALSE;

		if (lpCreateControl->nID == ID_VIEW_OTHER && pToolBar->GetBarID() == IDR_MAINFRAME)
		{
			lpCreateControl->controlType = xtpControlSplitButtonPopup;
			return TRUE;
		}
		if (lpCreateControl->nID == ID_VIEW_FULLSCREEN)
		{
//			lpCreateControl->buttonStyle = xtpButtonIconAndCaption;
			return TRUE;
		}

		if (lpCreateControl->nID == ID_THEME_SKINFRAMEWORK)
		{
			lpCreateControl->controlType = xtpControlPopup;
			return TRUE;
		}

		if (lpCreateControl->nID == ID_FILE_NEW_PROJECT && pToolBar->GetBarID() == IDR_MAINFRAME)
		{
			lpCreateControl->controlType = xtpControlSplitButtonPopup;
			return TRUE;
		}
		if (lpCreateControl->nID == ID_PROJECT_ADDNEWITEM && pToolBar->GetBarID() == IDR_MAINFRAME)
		{
			lpCreateControl->controlType = xtpControlSplitButtonPopup;
			return TRUE;
		}

		if (lpCreateControl->nID == ID_EDIT_FIND_EX && pToolBar->GetBarID() == IDR_MAINFRAME)
		{
			CXTPControlComboBox* pComboFind = (CXTPControlComboBox*)CXTPControlComboBox::CreateObject();
			pComboFind->SetDropDownListStyle();

			pComboFind->AddString(_T("Line1"));
			pComboFind->AddString(_T("Line2"));
			pComboFind->AddString(_T("Line3"));

			pComboFind->SetWidth(180);
			pComboFind->SetCaption(_T("Find"));
			pComboFind->SetStyle(xtpComboLabel);

			lpCreateControl->pControl = pComboFind;
			return TRUE;
		}

		if (lpCreateControl->nID == ID_EDIT_STATE && pToolBar->GetBarID() == IDR_MAINFRAME)
		{
			CXTPControlComboBox* pComboState = (CXTPControlComboBox*)CXTPControlComboBox::CreateObject();
			pComboState->AddString(_T("Debug"));
			pComboState->AddString(_T("Release"));
			pComboState->AddString(_T("Configuration Manager"));
			pComboState->SetDropDownWidth(150);
			lpCreateControl->pControl = pComboState;
			return TRUE;
		}

		if (lpCreateControl->nID == ID_EDIT_PLATFORM && pToolBar->GetBarID() == IDR_MAINFRAME)
		{
			CXTPControlComboBox* pComboState = (CXTPControlComboBox*)CXTPControlComboBox::CreateObject();
			pComboState->AddString(_T("Win32"));
			pComboState->AddString(_T("Configuration Manager"));
			pComboState->SetDropDownWidth(150);
			lpCreateControl->pControl = pComboState;
			return TRUE;
		}


		if (lpCreateControl->nID == ID_GOTO_URL && pToolBar->GetBarID() == IDR_TOOLBAR_WEB)
		{
			CXTPControlComboBox* pComboUrl = (CXTPControlComboBox*)CXTPControlComboBox::CreateObject();
			pComboUrl->AddString(_T("http://www.codejock.com"));
			pComboUrl->AddString(_T("ms-help://MS.VSCC/vsccCommon/html/vsccCommon_Start_Page.htm"));
			pComboUrl->SetWidth(200);
			pComboUrl->SetDropDownWidth(300);
			pComboUrl->SetDropDownListStyle();
			pComboUrl->SetFlags(xtpFlagManualUpdate);
			pComboUrl->SetEditText(_T("http://www.codejock.com"));
			pComboUrl->EnableShellAutoComplete();

			lpCreateControl->pControl = pComboUrl;
			return TRUE;
		}


	}
	return FALSE;

}

void CMainFrame::OnCustomize()
{
	CXTPCustomizeSheet cs(GetCommandBars());

	CXTPCustomizeKeyboardPage pageKeyboard(&cs);
	cs.AddPage(&pageKeyboard);
	pageKeyboard.AddCategories(IDR_MAINFRAME, TRUE);

	CXTPCustomizeOptionsPage pageOptions(&cs);
	cs.AddPage(&pageOptions);

	CXTPCustomizeCommandsPage* pCommands = cs.GetCommandsPage();
	pCommands->AddCategories(IDR_MAINFRAME, TRUE);

	pCommands->InsertAllCommandsCategory();
	pCommands->InsertBuiltInMenus(IDR_MAINFRAME);
	pCommands->InsertNewMenuCategory();

	cs.DoModal();
}

void CMainFrame::OnEditState(NMHDR* pNMHDR, LRESULT* pResult)
{
	NMXTPCONTROL* tagNMCONTROL = (NMXTPCONTROL*)pNMHDR;

	CXTPControlComboBox* pControl = (CXTPControlComboBox*)tagNMCONTROL->pControl;
	if (pControl->GetType() == xtpControlComboBox)
	{
		int nState = pControl->GetCurSel();
		if (nState != 2)
		{
			m_nState = nState;
		}
		else
		{
			MessageBox(_T("Configuration Manager"));
			pControl->SetCurSel(m_nState);
		}
		*pResult = TRUE; // Handled
	}
}

void CMainFrame::OnUpdateEditState(CCmdUI* pCmdUI)
{
	CXTPCommandBar* pToolBar = (CXTPToolBar*)pCmdUI->m_pOther;
	if (pToolBar && !XTPMouseManager()->IsTrackedLock())
	{
		CXTPControlComboBox* pStateCombo = (CXTPControlComboBox*)pToolBar->GetControls()->GetAt(pCmdUI->m_nIndex);

		if (pStateCombo->GetType() == xtpControlComboBox)
		{
			pStateCombo->SetCurSel(m_nState);
		}
	}

	pCmdUI->Enable(TRUE);
}

void CMainFrame::OnEditPlatform(NMHDR* pNMHDR, LRESULT* pResult)
{
	NMXTPCONTROL* tagNMCONTROL = (NMXTPCONTROL*)pNMHDR;

	CXTPControlComboBox* pControl = (CXTPControlComboBox*)tagNMCONTROL->pControl;
	if (pControl->GetType() == xtpControlComboBox)
	{
		int nState = pControl->GetCurSel();
		if (nState != 1)
		{
			m_nPlatform = nState;
		}
		else
		{
			MessageBox(_T("Configuration Manager"));
			pControl->SetCurSel(m_nPlatform);
		}
		*pResult = TRUE; // Handled
	}
}

void CMainFrame::OnUpdateEditPlatform(CCmdUI* pCmdUI)
{
	CXTPCommandBar* pToolBar = (CXTPToolBar*)pCmdUI->m_pOther;
	if (pToolBar && !XTPMouseManager()->IsTrackedLock())
	{
		CXTPControlComboBox* pStateCombo = (CXTPControlComboBox*)pToolBar->GetControls()->GetAt(pCmdUI->m_nIndex);

		if (pStateCombo->GetType() == xtpControlComboBox)
		{
			pStateCombo->SetCurSel(m_nPlatform);
		}
	}

	pCmdUI->Enable(TRUE);
}

void CMainFrame::OnClose()
{
	//CXTPPropExchangeIniFile px(FALSE, 0, _T("Settings"));    // To serialize to ini file
	CXTPPropExchangeXMLNode px(FALSE, 0, _T("Settings"));      // To serialize to XML file

	if (px.OnBeforeExchange()) 
	{
		CXTPPropExchangeSection pxTaskPanel(px.GetSection(_T("TaskPanel")));
		m_wndTaskPanel.GetGroups()->DoPropExchange(&pxTaskPanel);

		// Reset Full Screen Mode
		if (m_bFullScreen)
		{
			OnFullScreen();
		}

		CXTPPropExchangeSection pxNormalLayout(px.GetSection(_T("NormalLayout")));
		ExchangeLayout(&pxNormalLayout);
	
		px.PutSection(m_pFullScreenLayout);

		px.SaveToFile(m_strIniFileName);
	}

	CMDIFrameWnd::OnClose();
}


void CMainFrame::OnSetPreviewMode(BOOL bPreview, CPrintPreviewState* pState)
{

// Toggle CommandBars
	GetCommandBars()->OnSetPreviewMode(bPreview);
// Toggle Tab Client
	m_MTIClientWnd.ShowWorkspace(!bPreview);

// Toggle Docking Panes.
	m_paneManager.OnSetPreviewMode(bPreview);


	CMDIFrameWnd::OnSetPreviewMode(bPreview, pState);
}

void CMainFrame::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized)
{
	static HWND hFocus = 0;

	if (nState == WA_INACTIVE)
	{
		hFocus = m_paneManager.GetActivePane() != NULL ? ::GetFocus() : NULL;
	}
	
	CMDIFrameWnd::OnActivate(nState, pWndOther, bMinimized);

	if (nState != WA_INACTIVE && hFocus)
	{
		::SetFocus(hFocus);		
		hFocus = NULL;		
	}
}

void CMainFrame::ExchangeLayout(CXTPPropExchange* pPX, BOOL bSerializeControls /*= TRUE*/)
{
	XTP_COMMANDBARS_PROPEXCHANGE_PARAM param; param.bSerializeControls = bSerializeControls; 

	CXTPPropExchangeSection pxCommandBars(pPX->GetSection(_T("CommandBars")));
	GetCommandBars()->DoPropExchange(&pxCommandBars, &param);

	CXTPPropExchangeSection secShortcuts(pPX->GetSection(_T("Shortcuts")));
	GetCommandBars()->GetShortcutManager()->DoPropExchange(&secShortcuts);

	CXTPPropExchangeSection secOptions(pPX->GetSection(_T("Options")));	
	GetCommandBars()->GetCommandBarsOptions()->DoPropExchange(&secOptions, TRUE);

	CXTPPropExchangeSection pxDockingPane(pPX->GetSection(_T("DockingPane")));	
	m_paneManager.DoPropExchange(&pxDockingPane);
}

void CMainFrame::OnFullScreen()
{
	m_bFullScreen ^= 1;

	CXTPPropExchangeXMLNode px(FALSE, 0, _T("Settings"));
	CXTPPropExchangeXMLNode* pxLayoutSave = DYNAMIC_DOWNCAST(CXTPPropExchangeXMLNode, px.GetSection(_T("FullScreenLayout")));
	ASSERT(pxLayoutSave);

	// Save current layout
	if (pxLayoutSave != 0)
	{	
		ExchangeLayout(pxLayoutSave, FALSE);
	}

	// If Full screen layout exists
	if (m_pFullScreenLayout && m_pFullScreenLayout->IsSectionExists(_T("CommandBars")))
	{
		// Set it
		m_pFullScreenLayout->SetLoading(TRUE);
		ExchangeLayout(m_pFullScreenLayout, FALSE);
	}
	// Else create new fullscreen layout. Hide all toolbars and DockingPanes.
	else
	{		
//		for (int i = 0; i < GetCommandBars()->GetCount(); i++)
		{
//			CXTPToolBar* pToolBar = GetCommandBars()->GetAt(i);
//			pToolBar->SetVisible((pToolBar->GetType() == xtpBarTypeMenuBar) || (pToolBar->GetBarID() == IDR_TOOLBAR_FULLSCREEN));
		}
//		m_paneManager.CloseAll();
	}
	
	// Save old layout
	if (m_pFullScreenLayout)
	{
		delete m_pFullScreenLayout;
	}
	m_pFullScreenLayout = pxLayoutSave;


/*	if (m_bFullScreen)
	{
		GetWindowRect(&m_rcMainFrame);

		ModifyStyle(WS_CAPTION|WS_THICKFRAME, 0);
		
		// Now resize the main window
		CRect rcScreen = XTPMultiMonitor()->GetScreenArea(this);
		
		int cxBorder = ::GetSystemMetrics(SM_CXBORDER);
		int cyBorder = ::GetSystemMetrics(SM_CYBORDER);

		SetWindowPos(NULL, rcScreen.left - cxBorder, rcScreen.top - cyBorder, 
			rcScreen.Width() + cxBorder * 2, rcScreen.Height() + cyBorder * 2, SWP_NOZORDER);

		m_wndStatusBar.ShowWindow(SW_HIDE);

	} 
	else
	{
		ModifyStyle(0, WS_CAPTION|WS_THICKFRAME);
		MoveWindow(&m_rcMainFrame);
		m_wndStatusBar.ShowWindow(SW_SHOW);
	}*/
	RecalcLayout(TRUE);
}

void CMainFrame::OnUpdateFullScreen(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_bFullScreen);

}

class CVisualStudio6Theme : public CXTPDefaultTheme
{
	CSize DrawCommandBarGripper(CDC* pDC, CXTPCommandBar* pBar, BOOL bDraw)
	{
		if (pBar->IsDialogBar() || pBar->GetPosition() == xtpBarFloating)
			return CXTPDefaultTheme::DrawCommandBarGripper(pDC, pBar, bDraw);
		
		CRect rc;
		pBar->GetClientRect(&rc);
		
		if (pBar->GetPosition() == xtpBarRight || pBar->GetPosition() == xtpBarLeft)
		{
			if (pDC && bDraw)
			{
				Draw3dRect(pDC, CRect(3, 3, rc.right - 3, 6), COLOR_BTNHILIGHT, COLOR_3DSHADOW);
				Draw3dRect(pDC, CRect(3, 7, rc.right - 3, 10), COLOR_BTNHILIGHT, COLOR_3DSHADOW);
			}
			return CSize(0, 10);
		}
		else if (pBar->GetPosition() == xtpBarTop || pBar->GetPosition() == xtpBarBottom)
		{
			if (pDC && bDraw)
			{
				Draw3dRect(pDC, CRect(3, 3, 6, rc.bottom - 3), COLOR_BTNHILIGHT, COLOR_3DSHADOW);
				Draw3dRect(pDC, CRect(7, 3, 10, rc.bottom - 3), COLOR_BTNHILIGHT, COLOR_3DSHADOW);
			}
			return CSize(10, 0);
		}
		return 0;
	}
};

void CMainFrame::OnSkinFramework(UINT nID)
{
#ifdef _XTP_INCLUDE_SKINFRAMEWORK
	switch (nID)
	{
	case ID_SKINFRAMEWORK_VISTABLUE:
		XTPSkinManager()->LoadSkin(NULL, _T("NORMALBLUE.INI"));
		break;

	case ID_SKINFRAMEWORK_VISTABLACK:
		XTPSkinManager()->LoadSkin(NULL, _T("NORMALBLACK.INI"));
		break;

	default:
		XTPSkinManager()->LoadSkin(NULL);
		break;
	}
#endif
}

void CMainFrame::OnTheme(UINT nID)
{
	m_nTheme = nID;

	switch (nID)
	{
	case ID_THEME_VC6:
		XTPPaintManager()->SetCustomTheme(new CVisualStudio6Theme);
		m_paneManager.SetTheme(xtpPaneThemeGrippered);
		m_wndTaskPanel.SetTheme(xtpTaskPanelThemeToolbox);
		m_wndProperties.m_wndPropertyGrid.SetTheme(xtpGridThemeDefault);
		break;

	case ID_THEME_VC7:
		XTPPaintManager()->SetTheme(xtpThemeOfficeXP);
		m_paneManager.SetTheme(xtpPaneThemeVisualStudio2003);
		m_wndTaskPanel.SetTheme(xtpTaskPanelThemeToolbox);
		m_wndProperties.m_wndPropertyGrid.SetTheme(xtpGridThemeOfficeXP);
		break;

	case ID_THEME_VC8:
		XTPPaintManager()->SetTheme(xtpThemeWhidbey);
		m_paneManager.SetTheme(xtpPaneThemeVisualStudio2005);
		m_wndTaskPanel.SetTheme(xtpTaskPanelThemeToolboxWhidbey);
		m_wndProperties.m_wndPropertyGrid.SetTheme(xtpGridThemeWhidbey);
		break;

	case ID_THEME_VC9:
		XTPPaintManager()->SetTheme(xtpThemeVisualStudio2008);
		m_paneManager.SetTheme(xtpPaneThemeVisualStudio2005);
		m_wndTaskPanel.SetTheme(xtpTaskPanelThemeToolboxWhidbey);
		m_wndProperties.m_wndPropertyGrid.SetTheme(xtpGridThemeWhidbey);
		break;
	}

	GetCommandBars()->RedrawCommandBars();
}

void CMainFrame::OnUpdateTheme(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(pCmdUI->m_nID == m_nTheme ? TRUE : FALSE);
}

void CMainFrame::OnDigital() 
{
	CSettingHostDlg dlg;
	dlg.m_strtable =  _T("digitaltype");
	dlg.DoModal() ;
}

void CMainFrame::OnAnalog() 
{
	CSettingHostDlg dlg;
	dlg.m_strtable =  _T("analogtype");
	dlg.DoModal() ;
//	if(dlg.DoModal() != IDOK)
//		return FALSE;
}

void CMainFrame::OnLocation() 
{
	CSettingHostDlg dlg;
	dlg.m_strtable =  _T("fixlocation");
	dlg.DoModal() ;
}

void CMainFrame::OnPBrowser() 
{
	CSettingHostDlg dlg;
	dlg.m_strtable =  _T("pointdescription");
	dlg.DoModal();
}

void CMainFrame::OnControlT() 
{
	CSettingHostDlg dlg;
	dlg.m_strtable =  _T("control");
	dlg.DoModal();
}

void CMainFrame::OnControlS() 
{
	CSettingHostDlg dlg;
	dlg.m_strtable =  _T("specialcontrol");
	dlg.DoModal();
}

void CMainFrame::OnControlF() 
{
	CSettingHostDlg dlg;
	dlg.m_strtable =  _T("specialcontrol");
	dlg.m_bADD = true;
	dlg.DoModal();
}

void CMainFrame::OnSimulation() 
{
//	m_ontime = 0;
	CDocManager* pManager = AfxGetApp()->m_pDocManager ;
	if(pManager == NULL)
	{
		return ;
	}

	POSITION posTemplate = pManager->GetFirstDocTemplatePosition() ;
	while(posTemplate != NULL)
	{
		CDocTemplate* pTemplate = pManager->GetNextDocTemplate(posTemplate) ;
		POSITION posDoc = pTemplate->GetFirstDocPosition() ;
		while(posDoc != NULL)
		{
			CDrawDoc* pThisOne = (CDrawDoc *)pTemplate->GetNextDoc(posDoc) ;
			if(pThisOne->IsKindOf(RUNTIME_CLASS(CDrawDoc)))
			{
				POSITION posView = pThisOne->GetFirstViewPosition() ;
				while(posView != NULL)
				{
					CView * pView = pThisOne->GetNextView(posView) ;
					if(pView->IsKindOf(RUNTIME_CLASS(CDrawView)))
					{
						pView->GetParentFrame()->ActivateFrame() ;
					}
				}
			}
		}
	}
}

void CMainFrame::OnGenus() 
{
//	CDrawApp* pApp = (CDrawApp *)AfxGetApp() ;
//	pApp->pNewDocTemplate->OpenDocumentFile(NULL) ;

//	m_ontime = 1;

	CDocManager* pManager = AfxGetApp()->m_pDocManager ;
	if(pManager == NULL)
	{
		return ;
	}

	POSITION posTemplate = pManager->GetFirstDocTemplatePosition() ;
	while(posTemplate != NULL)
	{
		CDocTemplate* pTemplate = pManager->GetNextDocTemplate(posTemplate) ;
		POSITION posDoc = pTemplate->GetFirstDocPosition() ;
		while(posDoc != NULL)
		{
			CFlatTabViewDoc* pThisOne = (CFlatTabViewDoc *)pTemplate->GetNextDoc(posDoc) ;
			if(pThisOne->IsKindOf(RUNTIME_CLASS(CFlatTabViewDoc)))
			{
				POSITION posView = pThisOne->GetFirstViewPosition() ;
				while(posView != NULL)
				{
					CView * pView = pThisOne->GetNextView(posView) ;
					if(pView->IsKindOf(RUNTIME_CLASS(CSampleFormView)))
					{
						pView->GetParentFrame()->ActivateFrame() ;
					}
				}
			}
		}
	}
}

void CMainFrame::OnManipulate() 
{
//	m_pSampleFormView->SetInfo(_T(" %d年%d月%d日 %d时:%d分：%d秒"));
}

void CMainFrame::Msg(int iItem, CString str1,CString str2,CString str3,CString str4,CString str5)
{
//	m_wndResourceView.SetLC(iItem, str1,str2, str3, str4, str5);

/*	if(m_ontime == 30)
		m_ontime = 0;
	m_ontime++;
		m_wndResourceView.m_listCtrl.SetItemText(m_ontime, 0, str1);
		m_wndResourceView.m_listCtrl.SetItemText(m_ontime, 1,  str2);
		m_wndResourceView.m_listCtrl.SetItemText(m_ontime, 2,  str3);
		m_wndResourceView.m_listCtrl.SetItemText(m_ontime, 3,  str4);
		m_wndResourceView.m_listCtrl.SetItemText(m_ontime, 4, str5);

/*	CListBox * plistInfo = (CListBox*)m_wndBar.GetDlgItem(IDC_LIST_INFO);
	SYSTEMTIME tm;
	GetLocalTime(&tm);
	CString time;
	time.Format(_T(" %d年%d月%d日 %d时:%d分：%d秒"), tm.wYear,tm.wMonth,tm.wDay,tm.wHour, tm.wMinute,tm.wSecond);
	plistInfo->AddString(time+"        "+str);
	int numList=plistInfo->GetCount()-1;
	plistInfo->SetTopIndex(numList);
	plistInfo->SetCurSel(numList);
*/
	//水平滚动
/*	int max_width=0;
	CSize sz;
	CClientDC dc(this);
	for(int i=0;i<plistInfo->GetCount();i++)
	{
		plistInfo->GetText(i,str);
		sz=dc.GetTextExtent(str);
		if(max_width<sz.cx)
			max_width=sz.cx;
	}
	plistInfo->SendMessage(LB_SETHORIZONTALEXTENT,max_width,0);
*/
//	CMainFrame* pFWnd=(CMainFrame*)AfxGetMainWnd();
//	pFWnd->m_TaskListBar=this;	
//	m_TaskListBar->SetWarnInfo();

}

void CMainFrame::OnSelchangeTabInfo(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here

/*	CTabCtrl * ptab=(CTabCtrl *)m_wndBar.GetDlgItem(IDC_TAB_INFO);
	CListBox * plistHistory = (CListBox*)m_wndBar.GetDlgItem(IDC_LIST_HISTORY);
	CListBox * plistInfo = (CListBox*)m_wndBar.GetDlgItem(IDC_LIST_INFO);
	int currenttab=ptab->GetCurSel();	
//	UINT currentWin=((CMainFrame*)AfxGetMainWnd())->m_currentwin;
	if(currenttab==0)
	{	
		plistInfo->ShowWindow(SW_SHOW);;
		plistHistory->ShowWindow(SW_HIDE);
	}
	else
	{
		plistHistory->ShowWindow(SW_SHOW);
		plistInfo->ShowWindow(SW_HIDE);
	}

	plistHistory->ResetContent();
	plistHistory->AddString("当前没有历史当前没有历史纪录当前没有历史纪录当前没有历史纪录当前没有历史纪录当前没有历史纪录当前没有历史纪录当前没有历史纪录当前没有历史纪录当前没有历史纪录当前没有历史纪录纪录");
	plistHistory->AddString("当前没有历史纪录");
	plistHistory->AddString("当前没有历史纪录");
	plistHistory->AddString("当前没有历史纪录");
	plistHistory->AddString("当前没有历史纪录");
	plistHistory->AddString("当前没有历史纪录");
	plistHistory->AddString("当前没有历史纪录");
	plistHistory->AddString("当前没有历史纪录");
	plistHistory->AddString("当前没有历史纪录");
	//程序中没有添加历史纪录
//	plistInfo->ResetContent();
*/


//	*pResult = 0;
}


void CMainFrame::MsgDel()
{
//	CListBox * plistInfo = (CListBox*)m_wndBar.GetDlgItem(IDC_LIST_INFO);
//	int numList=plistInfo->GetCount()-1;
//	plistInfo->DeleteString(numList);
}


void CMainFrame::AddAnimation()
{
	if (!m_wndAnimCtrl.Create(WS_CHILD|WS_VISIBLE|ACS_CENTER,
		CRect(0,0,0,0), &m_wndStatusBar, 0))
	{
		TRACE0("Failed to create avi control.\n");
		return;
	}

	m_wndAnimCtrl.Open(IDR_HEARTBEAT);

	// add the indicator to the status bar.
	CXTPStatusBarPane* pPane = m_wndStatusBar.AddIndicator(ID_INDICATOR_ANIM);

	// Initialize the pane info and add the control.
	int nIndex = m_wndStatusBar.CommandToIndex(ID_INDICATOR_ANIM);
	ASSERT (nIndex != -1);

	m_wndStatusBar.SetPaneWidth(nIndex, 14);
	m_wndStatusBar.SetPaneStyle(nIndex, m_wndStatusBar.GetPaneStyle(nIndex) | SBPS_POPOUT);
	m_wndStatusBar.AddControl(&m_wndAnimCtrl, ID_INDICATOR_ANIM, FALSE);

//	pPane->SetCustomizationVisible(FALSE);
}

void CMainFrame::AddZoomButton()
{
	CXTPStatusBarPane* pPane = m_wndStatusBar.AddIndicator(ID_INDICATOR_ZOOM);
	pPane->SetText(_T("100%"));
	pPane->SetWidth(pPane->GetBestFit());
	pPane->SetButton();
	pPane->SetTextAlignment(DT_CENTER);
	pPane->SetTooltip(_T("Zoom level. Click to open the Zoom dialog box."));
	pPane->SetBeginGroup(FALSE);

	pPane->SetCaption(_T("&Zoom"));

}

void CMainFrame::AddZoomSlider()
{
	CXTPStatusBarSliderPane* pZoomPane = (CXTPStatusBarSliderPane*)m_wndStatusBar.AddIndicator(new CXTPStatusBarSliderPane(), ID_INDICATOR_ZOOMSLIDER);
	pZoomPane->SetWidth(130);
	
	pZoomPane->SetPos(100);
	pZoomPane->SetRange(0, 200);
	pZoomPane->SetStyle(SBPS_NOBORDERS);

	pZoomPane->SetBeginGroup(FALSE);

	pZoomPane->SetCaption(_T("&Zoom Slider"));
	pZoomPane->SetTooltip(_T("Zoom"));

}

void CMainFrame::AddSwitchButtons()
{
	static UINT switches[] =
	{
		ID_INDICATOR_PRINT,
		ID_INDICATOR_FULLSCREEN,
		ID_INDICATOR_WEB,
		ID_INDICATOR_OUTLINE,
		ID_INDICATOR_DRAFT,
	};

	CXTPStatusBarSwitchPane* pSwitchPane = (CXTPStatusBarSwitchPane*)m_wndStatusBar.AddIndicator(new CXTPStatusBarSwitchPane(), ID_INDICATOR_VIEW);
	pSwitchPane->SetSwitches(switches, sizeof(switches)/sizeof(UINT));
	pSwitchPane->SetChecked(ID_INDICATOR_PRINT);

	for (int i = 0; i < sizeof(switches)/sizeof(UINT); i++)
	{
		m_wndStatusBar.GetImageManager()->SetIcon(switches[i], switches[i]);
	}

	pSwitchPane->BestFit();

	m_wndStatusBar.UpdateAllPanes(TRUE, FALSE);

	m_strMessage.LoadString(ID_INDICATOR_PRINT);

}

void CMainFrame::AddEdit()
{
	// Create the edit control and add it to the status bar
/*	if (!m_wndEditCtrl.CreateEx(WS_EX_STATICEDGE, _T("edit"), _T("Hello World"),
		WS_CHILD|WS_VISIBLE, CRect(0,0,0,0), &m_wndStatusBar, 0))
	{
		TRACE0("Failed to create edit control.\n");
		return;
	}

	m_wndEditCtrl.SetFont(m_wndStatusBar.GetFont());
*/
	CTime time;
	time=CTime::GetCurrentTime();//得到当前时间     ID_INDICATOR_CLOCK
	CString s=time.Format("%Y-%m-%d %H:%M:%S");//转换时间格式

	// add the indicator to the status bar.   ID_INDICATOR_EDIT
	CXTPStatusBarPane* pPane = m_wndStatusBar.AddIndicator(ID_INDICATOR_EDIT,2);

	// Initialize the pane info and add the control.
	int nIndex = m_wndStatusBar.CommandToIndex(ID_INDICATOR_EDIT);
	ASSERT (nIndex != -1);

	m_wndStatusBar.SetPaneWidth(nIndex, 120);
	m_wndStatusBar.SetPaneStyle(nIndex, m_wndStatusBar.GetPaneStyle(nIndex) | SBPS_NOBORDERS);
//	m_wndStatusBar.AddControl(&m_wndEditCtrl, ID_INDICATOR_EDIT, FALSE);
	m_wndStatusBar.SetPaneText(m_wndStatusBar.CommandToIndex(ID_INDICATOR_EDIT),s); //显示时钟

//	pPane->SetCustomizationVisible(TRUE);
}

void CMainFrame::AddLogo()
{
#if 0 // Obsolete 

	if (!m_wndLogoPane.Create(_T("Bodhi Software"), &m_wndStatusBar))
	{
		TRACE0("Failed to create logo control.\n");
		return;
	}

	int nWidth = m_wndLogoPane.GetTextSize().cx;

	// add the indicator to the status bar.
	m_wndStatusBar.AddIndicator(ID_INDICATOR_LOGO, 0);

	// Initialize the pane info and add the control.
	int nIndex = m_wndStatusBar.CommandToIndex(ID_INDICATOR_LOGO);
	ASSERT (nIndex != -1);

	m_wndStatusBar.SetPaneWidth(nIndex, nWidth);
	m_wndStatusBar.SetPaneStyle(nIndex, m_wndStatusBar.GetPaneStyle(nIndex) | SBPS_POPOUT);
	m_wndStatusBar.AddControl(&m_wndLogoPane, ID_INDICATOR_LOGO, FALSE);
#else
	CXTPStatusBarPane* pPane = m_wndStatusBar.AddIndicator(ID_INDICATOR_LOGO, 0);
	
#ifndef _XTP_INCLUDE_MARKUP
	pPane->SetText(_T("Bodhi Software"));
	pPane->SetTextColor(0x915f36);
	CXTPPaintManager::CNonClientMetrics ncm;
	ncm.lfMenuFont.lfWeight = FW_BOLD;
	pPane->SetTextFont(&ncm.lfMenuFont);
#else
	m_wndStatusBar.EnableMarkup(TRUE);
	pPane->SetText(_T("<TextBlock VerticalAlignment='Center'><Bold><Run Foreground='#365f91'>Bodhi</Run> <Run Foreground='Black'>Software</Run></Bold></TextBlock>"));
#endif

	pPane->SetCaption(_T("Application Logo"));

	pPane->SetStyle(pPane->GetStyle() | SBPS_POPOUT);

#endif
}

void CMainFrame::AddProgress()
{
	// Create the edit control and add it to the status bar
	if (!m_wndProgCtrl.Create(WS_CHILD|WS_VISIBLE|PBS_SMOOTH,
		CRect(0,0,0,0), &m_wndStatusBar, 0))
	{
		TRACE0("Failed to create edit control.\n");
		return;
	}

	// add the indicator to the status bar.
	CXTPStatusBarPane* pPane = m_wndStatusBar.AddIndicator(ID_INDICATOR_PROG);

	// Initialize the pane info and add the control.
	int nIndex = m_wndStatusBar.CommandToIndex(ID_INDICATOR_PROG);
	ASSERT (nIndex != -1);

	pPane->SetCaption(pPane->GetText());
	pPane->SetText(_T(""));

	m_wndStatusBar.SetPaneWidth(nIndex, 150);
	m_wndStatusBar.SetPaneStyle(nIndex, m_wndStatusBar.GetPaneStyle(nIndex) | SBPS_NOBORDERS);
	m_wndStatusBar.AddControl(&m_wndProgCtrl, ID_INDICATOR_PROG, FALSE);

	// initialize progress control.
	m_wndProgCtrl.SetRange (0, 5000);
	m_wndProgCtrl.SetPos (0);
	m_wndProgCtrl.SetStep (1);

	pPane->SetCustomizationVisible(FALSE);
}


void CMainFrame::TestProgress()
{
	m_wndProgCtrl.SetPos (0);

	int i;
	for (i = 0; i <= 5000; i++)
	{
		m_wndProgCtrl.StepIt();
	}
}

void CMainFrame::OnSoundPath()
{
	m_bSoundPath ^= 1;

	CXTPPropExchangeXMLNode px(FALSE, 0, _T("Settings"));
	CXTPPropExchangeXMLNode* pxLayoutSave = DYNAMIC_DOWNCAST(CXTPPropExchangeXMLNode, px.GetSection(_T("FullScreenLayout")));
	ASSERT(pxLayoutSave);

	// Save current layout
	if (pxLayoutSave != 0)
	{	
		ExchangeLayout(pxLayoutSave, FALSE);
	}

	// If Full screen layout exists
	if (m_pFullScreenLayout && m_pFullScreenLayout->IsSectionExists(_T("CommandBars")))
	{
		// Set it
		m_pFullScreenLayout->SetLoading(TRUE);
		ExchangeLayout(m_pFullScreenLayout, FALSE);
	}
	// Else create new fullscreen layout. Hide all toolbars and DockingPanes.
	else
	{		
//		for (int i = 0; i < GetCommandBars()->GetCount(); i++)
		{
//			CXTPToolBar* pToolBar = GetCommandBars()->GetAt(i);
//			pToolBar->SetVisible((pToolBar->GetType() == xtpBarTypeMenuBar) || (pToolBar->GetBarID() == IDR_TOOLBAR_FULLSCREEN));
		}
//		m_paneManager.CloseAll();
	}
	
	// Save old layout
	if (m_pFullScreenLayout)
	{
		delete m_pFullScreenLayout;
	}
	m_pFullScreenLayout = pxLayoutSave;


/*	if (m_bFullScreen)
	{
		GetWindowRect(&m_rcMainFrame);

		ModifyStyle(WS_CAPTION|WS_THICKFRAME, 0);
		
		// Now resize the main window
		CRect rcScreen = XTPMultiMonitor()->GetScreenArea(this);
		
		int cxBorder = ::GetSystemMetrics(SM_CXBORDER);
		int cyBorder = ::GetSystemMetrics(SM_CYBORDER);

		SetWindowPos(NULL, rcScreen.left - cxBorder, rcScreen.top - cyBorder, 
			rcScreen.Width() + cxBorder * 2, rcScreen.Height() + cyBorder * 2, SWP_NOZORDER);

		m_wndStatusBar.ShowWindow(SW_HIDE);

	} 
	else
	{
		ModifyStyle(0, WS_CAPTION|WS_THICKFRAME);
		MoveWindow(&m_rcMainFrame);
		m_wndStatusBar.ShowWindow(SW_SHOW);
	}*/
	RecalcLayout(TRUE);
}

void CMainFrame::OnUpdateOnSoundPath(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_bSoundPath);

}
