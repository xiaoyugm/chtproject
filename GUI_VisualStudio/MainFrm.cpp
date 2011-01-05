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
#include "LoginDlg.h"
#include "ColorSetDlg.h"
#include "AdjustDlg.h"
#include "DASafeMehod.h"
#include "MadeCertView.h"
#include "ClassTime.h"
#include "FormDraw.h"
#include "DCH5m.h"

//#include "DynamicMenu.h"
//#include <CommonTools.h>
#include  <winable.h> 

//#include  <tlhelp32.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#ifdef ATLASSERT
// for ATL
#define THREADASSERT ATLASSERT
#elif defined ASSERT
// for MfC
#define THREADASSERT ASSERT
#endif	// defined ATLASSERT

#ifndef THREADASSERT
#define THREADASSERT
#endif

#ifndef _ATL_MIN_CRT
#define THREADPOOL_USE_CRT
#endif

LONG CThreadObject::s_lNext = 0;
LONG CThreadObject::s_lCount = 0;

CThreadObject::CThreadObject(HWND hWnd, int nRuns) : m_hWndNotify(hWnd), m_nRuns(nRuns)
{
	m_n = InterlockedIncrement(&s_lNext);
	InterlockedIncrement(&s_lCount);
	if (::IsWindow(m_hWndNotify))
		PostMessage(m_hWndNotify, WMX_OBJECT_ADDED, NULL, (LPARAM)m_n);
}

void CThreadObject::Run(CThreadPoolThreadCallback &pool)
{
	if (::IsWindow(m_hWndNotify))
		PostMessage(m_hWndNotify, WMX_OBJECT_START, (WPARAM)GetCurrentThreadId(), (LPARAM)m_n);
//	Sleep(1000);
//	for (int n = 0; n < m_nRuns; n++)
	{
		if (!pool.CanContinue())
			return;
		if(m_nRuns ==1)
        	theApp.InitRTData(); //读取当天数据
		else if(m_nRuns ==2)
		{
        	CMainFrame* pFWnd=(CMainFrame*)AfxGetMainWnd();
			pFWnd->m_pDCH5m->DCH5mInitList();
		}
		else if(m_nRuns ==3)//清空报表
		{
//        	CMainFrame* pFWnd=(CMainFrame*)AfxGetMainWnd();
//			pFWnd->OnOpenR();
		}
		else if(m_nRuns ==4)//查询报表
		{
        	CMainFrame* pFWnd=(CMainFrame*)AfxGetMainWnd();
			pFWnd->OnOpenR();
		}
		else if(m_nRuns ==5)//查询报表
		{
        	CMainFrame* pFWnd=(CMainFrame*)AfxGetMainWnd();
			pFWnd->m_MadeCert->OnTAuto();
		}
//		if (::IsWindow(m_hWndNotify))
//			PostMessage(m_hWndNotify, WMX_OBJECT_PROGRESS, (WPARAM)MAKELONG(n,m_nRuns), (LPARAM)m_n);
//		Sleep(500);
	}
//	if (::IsWindow(m_hWndNotify))
//		PostMessage(m_hWndNotify, WMX_OBJECT_DONE, NULL, (LPARAM)m_n);
}

void CThreadObject::Done()
{
	InterlockedDecrement(&s_lCount);
	if (::IsWindow(m_hWndNotify))
		PostMessage(m_hWndNotify, WMX_OBJECT_REMOVED, NULL, (LPARAM)m_n);
	delete this;
}

/*
#define ID_COMMAND_0                    2000
#define ID_COMMAND_1                    2001
#define ID_COMMAND_2                    2002
#define ID_COMMAND_3                    2003
#define ID_COMMAND_4                    2004
#define ID_COMMAND_5                    2005
#define ID_COMMAND_6                    2006
#define ID_COMMAND_7                    2007
#define ID_COMMAND_8                    2008
#define ID_COMMAND_9                    2009
#define ID_COMMAND_10                    2010
#define ID_COMMAND_11                    2011
#define ID_COMMAND_12                    2012
#define ID_COMMAND_13                    2013
#define ID_COMMAND_14                    2014
#define ID_COMMAND_15                    2015
#define ID_COMMAND_16                    2016
#define ID_COMMAND_17                    2017
#define ID_COMMAND_18                    2018
#define ID_COMMAND_19                    2019
#define ID_COMMAND_20                    2020
#define ID_COMMAND_21                    2021
#define ID_COMMAND_22                    2022
#define ID_COMMAND_23                    2023
#define ID_COMMAND_24                    2024
#define ID_COMMAND_25                    2025
#define ID_COMMAND_26                    2026
#define ID_COMMAND_27                    2027
#define ID_COMMAND_28                    2028
#define ID_COMMAND_29                    2029
*/

CString strRTData1[6000];
CString strRTData2[6000];
extern SerialF               m_SerialF[MAX_FDS];
extern BYTE     m_ndkSend[MAX_FDS][44];//44BUFFER_SIZE
extern SlaveStation             m_SlaveStation[MAX_FDS][MAX_CHAN];
/////////////////////////////////////////////////////////////////////////////
// CMainFrame
static UINT RTDATAThread(void*);

enum
{
	UIREFRESH = 100,
	CALRTDATA = 200,
	ABFREFRESH = 300
};

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)   
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_COMMAND(ID_WINDOW_AUTOHIDEALL, OnWindowAutohideall)
	ON_COMMAND(ID_WINDOW_MORE, OnWindowMore)
	ON_WM_CLOSE()
	ON_COMMAND_RANGE(2000,2050,OnFileMenuItems)
//	ON_WM_LBUTTONDOWN()	// OnLButtonDown(UINT nFlags, CPoint point)
	ON_COMMAND(ID_OnSimulation, OnSimulation)
//	ON_COMMAND(ID_OnGenus, OnGenus)

	ON_COMMAND(ID_MANIPULATE, OnSoundPath)
	ON_UPDATE_COMMAND_UI(ID_MANIPULATE, OnUpdateOnSoundPath)

	ON_COMMAND(ID_FORMS, OnFORMS)

	ON_COMMAND(ID_D_D, OnDigital)
	ON_COMMAND(ID_A_D, OnAnalog)
	ON_COMMAND(ID_LOCALTION, OnLocation)
	ON_COMMAND(ID_BROWSERMOD, OnPBrowser)
	ON_COMMAND(ID_CONTROLTABLE, OnControlT)
	ON_COMMAND(ID_CONTROLS, OnFeedE)
	ON_COMMAND(ID_CONTROLF, OnColorS)
	ON_COMMAND(ID_VERIFY_TIMER, OnVerifyT)
	ON_COMMAND(ID_MANUAL_CONTROL, OnManualC)
	ON_COMMAND(ID_FDS_CONFIG, OnFDSC)
	ON_COMMAND(ID_TEST_COMMUNICATION, OnTESTC)
	ON_COMMAND(ID_WINDGAS_ATRESIA, OnWINDGASA)
	ON_COMMAND(ID_FAILURE_ATRESIA, OnFAILUREA)
	ON_COMMAND(ID_FDS_CONFIGop, OnFDSconfig)
	ON_COMMAND(ID_DLGAM, OnSafeMethod)
	ON_COMMAND(ID_SAFEMETHOD, OnSafeMethod)
	ON_COMMAND(ID_LOGIN, OnLOGIN)
	ON_COMMAND(ID_LOGOUT, OnLOGOUT)
	ON_COMMAND(ID_CLASSTIME, OnCLASSTIME)
	ON_COMMAND(ID_FANSA, OnFansA)
	ON_COMMAND(ID_FORMPROP, OnFORMPROP)
	ON_COMMAND(ID_SAVEFD, OnSAVEFD) //save files

	ON_COMMAND(ID_ADJUST_DIS, OnAdjustdis)
	ON_COMMAND(ID_ALARMS, OnALARMS)
	ON_COMMAND(ID_BREAKES, OnBREAKES)
	ON_COMMAND(ID_FEEDES, OnFEEDES)
	ON_COMMAND(ID_SELECTS, OnSELECTS)

	ON_COMMAND(ID_SELECT_DISA, OnSDisA)
	ON_COMMAND(ID_SELECT_DISD, OnSDisD)

	ON_COMMAND(ID_DIS_AAR, OnDisAAR)
	ON_COMMAND(ID_DIS_ABR, OnDisABR)
	ON_COMMAND(ID_DIS_AFER, OnDisAFER)
	ON_COMMAND(ID_DIS_DABR, OnDisDABR)
	ON_COMMAND(ID_DIS_DFER, OnDisDFER)

	ON_COMMAND(ID_DRIVERE, OnDRIVERE)
	ON_COMMAND(ID_DIS_DSC, OnDisDSC)
	ON_COMMAND(ID_OPTXT, OnOPTXT)
	ON_COMMAND(ID_WORKTXT, OnWORKTXT)
	ON_COMMAND(ID_OnGenus, OnDebugInfo)
	ON_COMMAND(ID_DEMO_TEST, OnTest)
	ON_COMMAND(ID_DEMO_TEST1, OnTest1)

		//记录查询显示
	ON_COMMAND(ID_REC_AAD, OnRECAAD)
	ON_COMMAND(ID_REC_ABD, OnRECABD)
	ON_COMMAND(ID_REC_AFED, OnRECAFED)
	ON_COMMAND(ID_REC_ASR, OnRECASR)
	ON_COMMAND(ID_REC_DABD, OnRECDABD)
	ON_COMMAND(ID_REC_DABB, OnRECDABB)
	ON_COMMAND(ID_REC_DSCD, OnRECDSCD)
	ON_COMMAND(ID_REC_DFED, OnRECDFED)
	ON_COMMAND(ID_REC_DRIVERE, OnRECDRIVERE)
		//日(班)报表
	ON_COMMAND(ID_EXCEL_A, OnEXCELA)
	ON_COMMAND(ID_EXCEL_AA, OnEXCELAA)
	ON_COMMAND(ID_EXCEL_AB, OnEXCELAB)
	ON_COMMAND(ID_EXCEL_AFE, OnEXCELAFE)
	ON_COMMAND(ID_EXCEL_ASR, OnEXCELASR)
	ON_COMMAND(ID_EXCEL_DA, OnEXCELDA)
	ON_COMMAND(ID_EXCEL_DAB, OnEXCELDAB)
	ON_COMMAND(ID_EXCEL_DSCD, OnEXCELDSCD)
	ON_COMMAND(ID_EXCEL_DFE, OnEXCELDFE)
	ON_COMMAND(ID_EXCEL_DRIVERE, OnEXCELDRIVERE)

//	ON_COMMAND(ID_DRAW_PAERATION, OnWAERATION)
	ON_COMMAND(ID_DRAW_PGAS, OnWGAS)
	ON_COMMAND(ID_DRAW_SYSTEM, Sqlite3define)
	ON_COMMAND(ID_DRTDATA, Sqlite3init)

	ON_COMMAND(ID_DRAW_STATE, OnCDS)
	ON_COMMAND(ID_DRAW_COLUMNIATION, OnCDC)
	ON_COMMAND(ID_DRAW_CS, OnCASelect)
	ON_COMMAND(ID_DRAW_CA, OnCAALARM)
	ON_COMMAND(ID_DRAW_CB, OnCABREAK)
	ON_COMMAND(ID_DRAW_CFE, OnCAFEED)
	ON_COMMAND(ID_ECURVE, OnCurveADP)
	ON_COMMAND(ID_EDRAW, OnEDRAW) //模拟图编辑

	ON_COMMAND(ID_MADE_MADE, OnMadeMade)

	ON_UPDATE_COMMAND_UI(ID_FANSA, OnUpdateDis)
	ON_UPDATE_COMMAND_UI(ID_D_D, OnUpdateDis)
	ON_UPDATE_COMMAND_UI(ID_A_D, OnUpdateDis)
	ON_UPDATE_COMMAND_UI(ID_LOCALTION, OnUpdateDis)
	ON_UPDATE_COMMAND_UI(ID_BROWSERMOD, OnUpdateDis)
	ON_UPDATE_COMMAND_UI(ID_CONTROLTABLE, OnUpdateDis)
	ON_UPDATE_COMMAND_UI(ID_CONTROLS, OnUpdateDis)
	ON_UPDATE_COMMAND_UI(ID_CONTROLF, OnUpdateDis)
	ON_UPDATE_COMMAND_UI(ID_VERIFY_TIMER, OnUpdateDis)
	ON_UPDATE_COMMAND_UI(ID_MANUAL_CONTROL, OnUpdateDis)
	ON_UPDATE_COMMAND_UI(ID_FDS_CONFIG, OnUpdateDis)
	ON_UPDATE_COMMAND_UI(ID_TEST_COMMUNICATION, OnUpdateDis)
	ON_UPDATE_COMMAND_UI(ID_WINDGAS_ATRESIA, OnUpdateDis)
	ON_UPDATE_COMMAND_UI(ID_FAILURE_ATRESIA, OnUpdateDis)
	ON_UPDATE_COMMAND_UI(ID_FDS_CONFIG, OnUpdateDis)
	ON_UPDATE_COMMAND_UI(ID_LOGIN, OnUpdateLog)
	ON_UPDATE_COMMAND_UI(ID_LOGOUT, OnUpdateDis)
	ON_UPDATE_COMMAND_UI(ID_CLASSTIME, OnUpdateDis)
	ON_UPDATE_COMMAND_UI(ID_FDS_CONFIGop, OnUpdateDis)
	ON_UPDATE_COMMAND_UI(ID_DLGAM, OnUpdateDis)
	ON_UPDATE_COMMAND_UI(ID_SAFEMETHOD, OnUpdateDis)
//	ON_MESSAGE(WM_XTP_PRETRANSLATEMOUSEMSG, OnTabbarMouseMsg)  
//    ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_INFO, OnSelchangeTabInfo)
	ON_COMMAND(IDI_STOP, OnSoundStop)
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

	ON_MESSAGE(WM_RTDATA_THREAD_MESSAGE, OnThreadMessage)
//	ON_MESSAGE(WM_RTDATA_THREAD_MESSAGE, On1000ThreadMessage)

		ON_MESSAGE(WMX_OBJECT_ADDED, OnObjectAdded)
		ON_MESSAGE(WMX_OBJECT_START, OnObjectStart)
		ON_MESSAGE(WMX_OBJECT_PROGRESS, OnObjectProgress)
		ON_MESSAGE(WMX_OBJECT_DONE, OnObjectDone)
		ON_MESSAGE(WMX_OBJECT_REMOVED, OnObjectRemoved)

END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
//    ID_MOUSCAPTION,
//	ID_MOUSPOINT,
//	ID_INDICATOR_CAPS,
//	ID_INDICATOR_NUM,
//	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
//:m_pMenuCommandSet(NULL)
{
	m_nState = 1;
	m_nPlatform = 0;
	m_bFullScreen = FALSE;
	m_bSoundPath = TRUE;
	m_m300 =0;
	n_m60 =1;
	m_bIsDraw =  TRUE;
	n_timer60=0;
	n_derr60=0;

	// get path of executable
	TCHAR szBuff[_MAX_PATH];
	VERIFY(::GetModuleFileName(AfxGetInstanceHandle(), szBuff, _MAX_PATH));

	LPTSTR lpszExt = _tcsrchr(szBuff, '.');
	lstrcpy(lpszExt, _T(".xml"));

	m_strIniFileName = szBuff;

	m_pFullScreenLayout = NULL;
	m_rcMainFrame.SetRectEmpty();

	m_nTheme = ID_THEME_VC9;
//	m_nOtherView = ID_VIEW_CLASSVIEW;

//	m_pMade=NULL;
//	m_pMenu=NULL;
//	m_pMenuCommandSet=	new MenuCommandSet();

#ifdef _XTP_INCLUDE_SKINFRAMEWORK
	XTPSkinManager()->GetResourceFile()->SetModuleHandle(AfxGetInstanceHandle());
#endif

	m_MadeCert = NULL;
	m_pSampleFormView = NULL;
	m_pDCH5m = NULL;
//	m_ontime =0;
	m_nPaneID =1;
	m_RepeatFlag = FALSE;
	m_ViewPos = NULL;
	s_ViewPos = NULL;
	m_pSetTimeDlg  = NULL;

	m_nTimerID = 0;
	m_pTimerThread = NULL;
	m_ThreadParam.nTime = 0;
	m_ThreadParam.hTimerEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	m_ThreadParam.hExitEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	for(int i=0; i<6000 ;i++)
	{
		strRTData1[i]="";
		strRTData2[i]="";
	}
}

CMainFrame::~CMainFrame()
{
//	delete m_pMenuCommandSet;
//    delete m_pMenu;
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
//	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
//		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
//		!m_wndToolBar.LoadToolBar(IDR_TOOLBARY))

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	if (!InitCommandBars())
		return -1;
	CXTPPaintManager::SetTheme(xtpThemeVisualStudio2008);  //xtpThemeVisualStudio2008
	pCommandBars = GetCommandBars();

	CXTPMenuBar* pMenuBar ;//= pCommandBars->SetMenu(_T("Menu Bar"), IDR_MAINFRAME);
//	CXTPCommandBar* pMenuBar;
	CString strmes = theApp.strargc.Mid(0,2);
	if(strmes == "On")
    	pMenuBar = pCommandBars->SetMenu(_T("Menu Bar"), IDR_MREPORT);
	else
    	pMenuBar = pCommandBars->SetMenu(_T("Menu Bar"), IDR_MAINFRAME);
//	pMenuBar->SetFlags(xtpFlagIgnoreSetMenuMessage | xtpFlagHideMDIButtons);  //main  IDR_MAINFRAME
	pMenuBar->SetFlags(xtpFlagAddMDISysPopup);

	CXTPToolBar* pCommandBart = (CXTPToolBar*)pCommandBars->Add(_T("工具栏"), xtpBarTop);
	if (!pCommandBart ||
		!pCommandBart->LoadToolBar(IDR_TOOLBARY))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;
	}
	if(strmes == "On")
    	pCommandBart->SetVisible(FALSE);//
	else
    	pCommandBart->SetVisible(TRUE);//FALSE

	/*	CXTPToolBar* pWebBar = (CXTPToolBar*)pCommandBars->Add(_T("Web"), xtpBarTop);Standard
	if (!pWebBar ||
		!pWebBar->LoadToolBar(IDR_TOOLBAR_WEB))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;
	}

	CXTPToolBar* pThemeBar = (CXTPToolBar*)pCommandBars->Add(_T("Theme"), xtpBarTop);
	if (!pThemeBar ||
		!pThemeBar->LoadToolBar(IDR_TOOLBAR_THEME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;
	}
	DockRightOf(pThemeBar, pWebBar);

	CXTPToolBar* pFullScreenBar = (CXTPToolBar*)pCommandBars->Add(_T("工具栏"), xtpBarTop);
//	CXTPToolBar* pFullScreenBar = (CXTPToolBar*)pCommandBars->Add(_T("Full Screen"), xtpBarTop);
	if (!pFullScreenBar ||
		!pFullScreenBar->LoadToolBar(IDR_TOOLBARY))
//		!pFullScreenBar->LoadToolBar(IDR_TOOLBAR_FULLSCREEN))
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
	m_paneManager.SetTheme(xtpPaneThemeVisualStudio2005);  //xtpPaneThemeVisualStudio2005
	
	if(strmes == "On")
	{
	}
	else
	{
			 paneResourceView = m_paneManager.CreatePane(
				ID_VIEW_RESOURCEVIEW, CRect(0, 0, 100, 170), xtpPaneDockBottom);
			 paneResourceView2 = m_paneManager.CreatePane(
				ID_VIEW_RESOURCEVIEW2, CRect(0, 0, 100, 170), xtpPaneDockBottom);
			 paneResourceView3 = m_paneManager.CreatePane(
				ID_VIEW_RESOURCEVIEW3, CRect(0, 0, 100, 170), xtpPaneDockBottom);
			 paneResourceView4 = m_paneManager.CreatePane(
				ID_VIEW_RESOURCEVIEW4, CRect(0, 0, 100, 170), xtpPaneDockBottom);
			 paneResourceView5 = m_paneManager.CreatePane(
				ID_VIEW_RESOURCEVIEW5, CRect(0, 0, 100, 170), xtpPaneDockBottom);
//			 paneResourceView6 = m_paneManager.CreatePane(
//				ID_VIEW_RESOURCEVIEW6, CRect(0, 0, 100, 170), xtpPaneDockBottom);
		
			m_paneManager.AttachPane(paneResourceView2,paneResourceView );
			m_paneManager.AttachPane(paneResourceView3,paneResourceView2);
			m_paneManager.AttachPane(paneResourceView4,paneResourceView3 );
			m_paneManager.AttachPane(paneResourceView5,paneResourceView4);
//			m_paneManager.AttachPane(paneResourceView6,paneResourceView5 );
//			m_paneManager.AttachPane(paneResourceView3,paneResourceView2);
					if (!m_wndResourceView3.GetSafeHwnd())
					{
						m_wndResourceView3.m_numabf = 3;
						m_wndResourceView3.Create(_T("STATIC"), NULL, WS_CHILD|WS_VISIBLE|WS_CLIPCHILDREN|WS_CLIPSIBLINGS, CXTPEmptyRect(), this, 0);
					}
					paneResourceView3->Attach(&m_wndResourceView3);
					if (!m_wndResourceView2.GetSafeHwnd())
					{
						m_wndResourceView2.m_numabf = 2;
						m_wndResourceView2.Create(_T("STATIC"), NULL, WS_CHILD|WS_VISIBLE|WS_CLIPCHILDREN|WS_CLIPSIBLINGS, CXTPEmptyRect(), this, 0);
					}
					paneResourceView2->Attach(&m_wndResourceView2);
					if (!m_wndResourceView.GetSafeHwnd())
					{
						m_wndResourceView.m_numabf = 1;
						m_wndResourceView.Create(_T("STATIC"), NULL, WS_CHILD|WS_VISIBLE|WS_CLIPCHILDREN|WS_CLIPSIBLINGS, CXTPEmptyRect(), this, 0);
					}
					paneResourceView->Attach(&m_wndResourceView);

					if (!m_wndResourceView4.GetSafeHwnd())
					{
						m_wndResourceView4.m_numabf = 4;
						m_wndResourceView4.Create(_T("STATIC"), NULL, WS_CHILD|WS_VISIBLE|WS_CLIPCHILDREN|WS_CLIPSIBLINGS, CXTPEmptyRect(), this, 0);
					}
					paneResourceView4->Attach(&m_wndResourceView4);
					if (!m_wndResourceView5.GetSafeHwnd())
					{
						m_wndResourceView5.m_numabf = 5;
						m_wndResourceView5.Create(_T("STATIC"), NULL, WS_CHILD|WS_VISIBLE|WS_CLIPCHILDREN|WS_CLIPSIBLINGS, CXTPEmptyRect(), this, 0);
					}
					paneResourceView5->Attach(&m_wndResourceView5);
//					if (!m_wndResourceView6.GetSafeHwnd())
//					{
//						m_wndResourceView6.Create(_T("STATIC"), NULL, WS_CHILD|WS_VISIBLE|WS_CLIPCHILDREN|WS_CLIPSIBLINGS, CXTPEmptyRect(), this, 0);
//					}
//					paneResourceView6->Attach(&m_wndResourceView6);
//			paneResourceView->Select();
	}
/*
	m_paneManager.CreatePane(
		ID_WINDOWS_OUTPUT, CRect(0, 0, 150, 120), xtpPaneDockBottom);
	CXTPDockingPane* paneToolBox = m_paneManager.CreatePane(
		ID_VIEW_TOOLBOX, CRect(0, 0, 200, 120), xtpPaneDockRight);
	CXTPDockingPane* paneClassView = m_paneManager.CreatePane(
		ID_VIEW_CLASSVIEW, CRect(0, 0, 230, 140), xtpPaneDockLeft);
	CXTPDockingPane* paneSolutionExplorer = m_paneManager.CreatePane(
		ID_VIEW_SOLUTIONEXPLORER, CRect(0, 0, 230, 140), xtpPaneDockLeft);
//	CXTPDockingPane* paneResourceView = m_paneManager.CreatePane(
//		ID_VIEW_RESOURCEVIEW, CRect(0, 0, 230, 140), xtpPaneDockLeft);
	CXTPDockingPane* paneHelpView =m_paneManager.CreatePane(
		ID_HELP_DYNAMICHELP, CRect(0, 0, 210, 140), xtpPaneDockBottom, paneToolBox);
	paneHelpView->Close();
	m_paneManager.AttachPane(paneClassView, paneSolutionExplorer);
//	m_paneManager.AttachPane(paneResourceView, paneClassView);
	paneClassView->Select();

	m_paneManager.CreatePane(
		ID_VIEW_PROPERTIESWINDOW, CRect(0, 0, 180, 140), xtpPaneDockBottom, paneClassView);
*/
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
	}*/

	CXTPImageManager* pImageManager = pCommandBars->GetImageManager();
//m_wndResourceView图标显示控制
//	pImageManager->InternalAddRef();
//	m_paneManager.SetImageManager(pImageManager);

	m_paneManager.SetAlphaDockingContext(TRUE);
//	m_paneManager.UseSplitterTracker(FALSE);
	m_paneManager.SetShowDockingContextStickers(TRUE);
	m_paneManager.SetShowContentsWhileDragging(TRUE);
//	m_paneManager.SetDefaultPaneOptions(xtpPaneHasMenuButton);
	m_paneManager.SetDefaultPaneOptions(xtpPaneNoHoverShow | xtpPaneNoCloseable//|xtpPaneHasMenuButton
//		| xtpPaneNoHideable //|xtpPaneNoDockable //|xtpPaneNoCaption  //停靠按钮
		|xtpPaneNoFloatableByTabDoubleClick|xtpPaneNoFloatableByCaptionDoubleClick
		); //xtpPaneHasMenuButton  xtpPaneNoFloatable |xtpPaneDisabled |xtpPaneNoFloatable 
//	m_paneManager.HidePane(201);
	m_paneManager.EnableSideDocking(FALSE);

	VERIFY(m_MTIClientWnd.Attach(this, TRUE));
	m_MTIClientWnd.EnableToolTips();
	if(strmes == "On")
    	m_MTIClientWnd.SetFlags(xtpWorkspaceHideClose |xtpWorkspaceHideArrowsAlways);   //child  关闭按钮
//	XTPImageManager()->SetIcons(IDR_DRAWTYPE);

	m_MTIClientWnd.GetPaintManager()->m_bShowIcons = FALSE;  //FALSE
//	if(strmes == "On")
//	m_MTIClientWnd.SetNewTabPosition(xtpWorkspaceNewTabLeftMost);
//    	m_MTIClientWnd.SetFlags(xtpWorkspaceHideArrowsAlways | xtpWorkspaceShowActiveFiles);

	CXTPOffice2003Theme::LoadModernToolbarIcons(IDR_MAINFRAME);
//	CXTPOffice2003Theme::LoadModernToolbarIcons(IDR_BORDERS);

	if(strmes != "On")
	{
    	m_wndStatusBar.GetPane(0)->SetBeginGroup(FALSE);
    	AddLogo();
	m_wndStatusBar.SetRibbonDividerIndex(m_wndStatusBar.GetPaneCount() - 1);
//	AddSwitchButtons();
	AddProgress();
	AddEdit();
	AddUser();
	AddMessage("");
//	AddAnimation();
//	AddZoomButton();
//	AddZoomSlider();
    	m_wndStatusBar.EnableCustomization();
	}
	// Load the previous state for command bars.
	LoadCommandBars(_T("CommandBars"));


#ifdef _DEBUG
#else
	OnTopWindow();
#endif //_DEBUG

	if(strmes == "On")
	{
		OnMadeMade();
	}
	else 
	{
	// create the pool with 2 initial threads and a maximum of 10 threads
    	HRESULT hr = m_ThreadPool.Init(2, 10);
    	ATLASSERT(S_OK == hr);
    	if (FAILED(hr))
		{
	    	MessageBox(_T("Initializing thread pool failed"), _T("RTThreadPool"), MB_OK|MB_ICONERROR);
    		return -1;
		}
    	m_ThreadPool.Add(new CThreadObject(*this, 1));

//		OnDisasysmenu();
//    	OnDisableMinbox();
//		OnDisableMaxbox();
//		OnDisableClose();
	}
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
//\n煤矿安全监控 文件 (*.rsy)\n.rsy\nRsy.Object\nRsy Document
//	\n\n\n\n.rsf\nRSF.Object\nRSF Document
//	\nUntitled\nUntitled\n\n\nGUIVisualStudio.Document\nText Document
	//主窗口的标题
//    m_strTitle ="煤矿安全监测";
	if( !CMDIFrameWnd::PreCreateWindow(cs) )
		return FALSE;

//	cs.lpszClass = _T("XTPMainFrame");
//	CXTPDrawHelpers::RegisterWndClass(AfxGetInstanceHandle(), cs.lpszClass, 
//		CS_DBLCLKS, AfxGetApp()->LoadIcon(IDR_MAINFRAME));
	cs.style = WS_OVERLAPPED | WS_CAPTION | FWS_ADDTOTITLE
		| WS_THICKFRAME | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX;
//		| WS_THICKFRAME | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_MAXIMIZE ;
//去除最大化、最小化按钮 去掉系统菜单
	// disable the maxmini box 最大化按钮变灰
//	cs.style&=~WS_MAXIMIZEBOX;     //
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
				case ID_VIEW_TOOLBOX:					
					pPane->Attach(CreateToolBox());
					break;

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
				case ID_VIEW_RESOURCEVIEW2:
					if (!m_wndResourceView2.GetSafeHwnd())
					{
						m_wndResourceView2.Create(_T("STATIC"), NULL, WS_CHILD|WS_VISIBLE|WS_CLIPCHILDREN|WS_CLIPSIBLINGS, CXTPEmptyRect(), this, 0);
					}
					pPane->Attach(&m_wndResourceView2);
					break;
				case ID_VIEW_RESOURCEVIEW3:
					if (!m_wndResourceView3.GetSafeHwnd())
					{
						m_wndResourceView3.Create(_T("STATIC"), NULL, WS_CHILD|WS_VISIBLE|WS_CLIPCHILDREN|WS_CLIPSIBLINGS, CXTPEmptyRect(), this, 0);
					}
					pPane->Attach(&m_wndResourceView3);
					break;

				case ID_VIEW_SOLUTIONEXPLORER:
//					CWnd* pView = pPane->AttachView(this, RUNTIME_CLASS(CSampleFormView));
					if (!m_wndSolutionExplorer.GetSafeHwnd())
					{
						m_wndSolutionExplorer.Create(_T("STATIC"), NULL, WS_CHILD|WS_VISIBLE|WS_CLIPCHILDREN|WS_CLIPSIBLINGS, CXTPEmptyRect(), this, 0);
					}
					pPane->Attach(&m_wndSolutionExplorer);
					break;

				case ID_VIEW_PROPERTIESWINDOW:   
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
					}
	
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

/*		if (lpCreateControl->nID == ID_FILE_NEW_PROJECT && pToolBar->GetBarID() == IDR_MAINFRAME)
		{
			lpCreateControl->controlType = xtpControlSplitButtonPopup;
			return TRUE;
		}
/*		if (lpCreateControl->nID == ID_PROJECT_ADDNEWITEM && pToolBar->GetBarID() == IDR_MAINFRAME)
		{
			lpCreateControl->controlType = xtpControlSplitButtonPopup;
			return TRUE;
		}

/*		if (lpCreateControl->nID == ID_EDIT_FIND_EX && pToolBar->GetBarID() == IDR_MAINFRAME)
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

/*		if (lpCreateControl->nID == ID_EDIT_STATE && pToolBar->GetBarID() == IDR_MAINFRAME)
		{
			CXTPControlComboBox* pComboState = (CXTPControlComboBox*)CXTPControlComboBox::CreateObject();
			pComboState->AddString(_T("Debug"));
			pComboState->AddString(_T("Release"));
			pComboState->AddString(_T("Configuration Manager"));
			pComboState->SetDropDownWidth(150);
			lpCreateControl->pControl = pComboState;
			return TRUE;
		}

/*		if (lpCreateControl->nID == ID_EDIT_PLATFORM && pToolBar->GetBarID() == IDR_MAINFRAME)
		{
			CXTPControlComboBox* pComboState = (CXTPControlComboBox*)CXTPControlComboBox::CreateObject();
			pComboState->AddString(_T("Win32"));
			pComboState->AddString(_T("Configuration Manager"));
			pComboState->SetDropDownWidth(150);
			lpCreateControl->pControl = pComboState;
			return TRUE;
		}*/


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
//        KillTimer(UIREFRESH);
//        KillTimer(CALRTDATA);
  CString szMsg;
         szMsg= "你确定要退出吗？";

#ifdef _DEBUG
#else
		 theApp.m_bLogIn = FALSE;
			CLoginDlg dlglogin;
			dlglogin.m_strdism = "login";
			dlglogin.m_strUser = theApp.curuser;
			if(dlglogin.DoModal()==IDOK) 
			{
//				if(theApp.curuser == "")
//    				m_bLogIn=false;
//				else
//    				m_bLogIn=true;
			}
			else
			{
         		 theApp.m_bLogIn = TRUE;
				return ;
			}

           MessageBeep(MB_ICONEXCLAMATION);
           int Reply = AfxMessageBox(szMsg, MB_YESNO);
           if ( Reply != IDYES )
		   {
//             	SetTimer(UIREFRESH,1000,NULL);
//             	SetTimer(CALRTDATA,20,NULL);
        		return;
		   }
#endif //_DEBUG


//	CXTPPropExchangeIniFile px(FALSE, 0, _T("Settings"));    // To serialize to ini file
/*	CXTPPropExchangeXMLNode px(FALSE, 0, _T("Settings"));      // To serialize to XML file

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
	}*/

//	CommonTools CT;
    	m_ThreadPool.Close();//结束线程池pool
    	//结束定时线程
    	if (m_pTimerThread != NULL)
		{
		//设置退出事件
    		SetEvent(m_ThreadParam.hExitEvent);
		//等待定时线程结束
    		::WaitForSingleObject(m_pTimerThread->m_hThread, INFINITE);
    		delete m_pTimerThread;
    		m_pTimerThread = NULL;
		}	
    	CloseHandle(m_ThreadParam.hTimerEvent);
       	CloseHandle(m_ThreadParam.hExitEvent);

		if(theApp.socketClient.IsConnected())
         	theApp.socketClient.Close();
		if(theApp.sFC.IsConnected())
         	theApp.sFC.Close();

#ifdef _DEBUG
//    	theApp.SocketServer.StopServer();
//    	theApp.sMSb.StopServer();
		if(n_CPort == 999 || n_CPort == 888 || n_CPort ==111)
     		if(theApp.sCb.IsConnected())
 		    	theApp.sCb.Close();
#else
		if(n_CPort == 999 || n_CPort == 888 || n_CPort ==111)
		{
     		if(theApp.sCb.IsConnected())
		    	theApp.sCb.Close();
		}
    	theApp.SocketServer.StopServer();
//    	theApp.sMSb.StopServer();
//		C_Ts.KillProcess("RSDRAW-YSDB.EXE");
#endif //_DEBUG

//		m_wndResourceView.m_listCtrl.DestroyWindow();
//	      m_wndResourceView2.m_listCtrl.DestroyWindow();
//	      m_wndResourceView3.m_listCtrl.DestroyWindow();
//	      m_wndResourceView4.m_listCtrl.DestroyWindow();
//	      m_wndResourceView5.m_listCtrl.DestroyWindow();
//	      m_wndResourceView6.m_listCtrl.DestroyWindow();
//	 paneResourceView6->Close();
	 paneResourceView5->Close();
	 paneResourceView4->Close();
	 paneResourceView3->Close();
	 paneResourceView2->Close();
	 paneResourceView->Close();

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
//		XTPPaintManager()->SetCustomTheme(new CVisualStudio6Theme);
//		m_paneManager.SetTheme(xtpPaneThemeGrippered);
//		m_wndTaskPanel.SetTheme(xtpTaskPanelThemeToolbox);
//		m_wndProperties.m_wndPropertyGrid.SetTheme(xtpGridThemeDefault);
		XTPPaintManager()->SetTheme(xtpThemeVisualStudio2008);
		m_paneManager.SetTheme(xtpPaneThemeVisualStudio2008);
		m_wndTaskPanel.SetTheme(xtpTaskPanelThemeOffice2003Plain);
		m_wndProperties.m_wndPropertyGrid.SetTheme(xtpGridThemeOffice2007);
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

void CMainFrame::OnFeedE() 
{
	CSettingHostDlg dlg;
	dlg.m_strtable =  _T("feedelectricity");
	dlg.DoModal();
}

void CMainFrame::OnFORMS() 
{
	CFormDraw dlg;
	dlg.m_dorf=1;
	dlg.DoModal();
}

void CMainFrame::OnColorS() 
{
	CColorSetDlg dlg;
	dlg.DoModal();
}

////////////通讯命令//////////////////////////////////////
void CMainFrame::OnVerifyT() 
{
	CSetTimeDlg dlg;
	dlg.chcommand =  0x54;
	dlg.DoModal();
}

void CMainFrame::OnManualC() 
{
	CSetTimeDlg dlg;
	dlg.chcommand =  0x4B;
	dlg.DoModal();
}

void CMainFrame::OnFDSC() 
{
	CSetTimeDlg dlg;
	dlg.chcommand =  0x43;
	dlg.DoModal();
}

void CMainFrame::OnTESTC() 
{
	CSetTimeDlg dlg;
	dlg.chcommand =  0x47;
	dlg.DoModal();
}

void CMainFrame::OnWINDGASA() 
{
	CSetTimeDlg dlg;
	dlg.chcommand =  0x46;
	dlg.m_nSecond =  6;
	dlg.DoModal();
}

void CMainFrame::OnFAILUREA() 
{
	CSetTimeDlg dlg;
	dlg.chcommand =  0x5A;
	dlg.m_nSecond =  MAX_FDS-1;
	dlg.DoModal();
}

void CMainFrame::OnFDSconfig() 
{
	CSetTimeDlg dlg;
	dlg.chcommand =  0x41;
	dlg.m_nSecond =  MAX_FDS-1;
	dlg.DoModal();
}

void CMainFrame::OnFORMPROP() 
{
	CSetTimeDlg dlg;
	dlg.chcommand =  0xf1;
//	dlg.m_nSecond =  64;
	dlg.DoModal();
}

void CMainFrame::OnFansA() 
{
	CSetTimeDlg dlg;
	dlg.chcommand =  0xf0;
//	dlg.m_nSecond =  64;
	dlg.DoModal();
}

/////列表显示/////////////通讯命令///////

void CMainFrame::OnSDisA()    //模拟量调用
{
	CLoginDlg dlg;
	dlg.m_strdism = "OnSDisA";
	dlg.DoModal();
}
void CMainFrame::OnSDisD()       //开关量调用
{
	CLoginDlg dlg;
	dlg.m_strdism = "OnSDisD";
	dlg.DoModal();
}

void CMainFrame::OnDisAAR()  //模拟量报警
{
//	dlg.m_strdism = "OnDisAAR";ToggleDocking   
//    if(!paneResourceView->IsSelected())
	{
//		paneResourceView->SetFocus();
//		m_paneManager.ClosePane(201);
        	paneResourceView->Select();
	}
}
void CMainFrame::OnDisABR()   //模拟量断电
{
//		paneResourceView2->SetFocus();
	 BOOL m_select = paneResourceView3->IsSelected();
//     if(!paneResourceView2->IsSelected()&& !m_select)
	 {
//		m_paneManager.ClosePane(207);
       	paneResourceView2->Select();
	 }
}
void CMainFrame::OnDisAFER() //模拟量馈电异常
{
//		BOOL m_select = paneResourceView3->IsSelected();
//     if(!m_select)
	 {
//		m_paneManager.ClosePane(208);
		paneResourceView3->SetFocus();
        	paneResourceView3->Select();
	 }
}
void CMainFrame::OnDisDABR()   //开关量报警与断电
{
//		m_paneManager.ClosePane(209);
//     if(!paneResourceView4->IsSelected())
        	paneResourceView4->Select();
}
void CMainFrame::OnDisDFER() //开关量馈电异常
{
//		m_paneManager.ClosePane(210);
//     if(!paneResourceView5->IsSelected())
         	paneResourceView5->Select();
}
void CMainFrame::OnDisDSC() //开关量状态变动
{
	CDCH5m dlg;
	dlg.n_select =1;
	dlg.DoModal();
//		m_paneManager.ClosePane(211);
//     if(!paneResourceView6->IsSelected())
//        	paneResourceView6->Select();
}
void CMainFrame::OnOPTXT() //操作日志
{
	CDCH5m dlg;
	dlg.n_select =2;
	dlg.DoModal();
}
void CMainFrame::OnWORKTXT() //中心站运行日志
{
	CDCH5m dlg;
	dlg.n_select =3;
	dlg.DoModal();
}

void CMainFrame::OnDRIVERE()    //设备故障
{
	CLoginDlg dlg;
	dlg.m_strdism = "OnDRIVERE";
	dlg.DoModal();
}

////列表显示///记录查询显示///////////////
void CMainFrame::OnRECAAD()  //模拟量报警记录
{
	theApp.strargc = "OnRECAAD";
	OnMadeMade();
//	C_Ts.CreateP(gstrTimeOut +"\\RSDRAW-YRun.EXE", "OnRECAAD",5,0x00000001);
}
void CMainFrame::OnRECABD()  //模拟量断电记录
{
	theApp.strargc = "OnRECABD";
	OnMadeMade();
//	C_Ts.CreateP(gstrTimeOut +"\\RSDRAW-YRun.EXE", "OnRECABD",5,0x00000001);
}
void CMainFrame::OnRECAFED() //模拟量馈电异常记录
{
	theApp.strargc = "OnRECAFED";
	OnMadeMade();
//	C_Ts.CreateP(gstrTimeOut +"\\RSDRAW-YRun.EXE", "OnRECAFED",5,0x00000001);
}
void CMainFrame::OnRECASR() //模拟量统计值记录
{
	theApp.strargc = "OnRECASR";
	OnMadeMade();
//	C_Ts.CreateP(gstrTimeOut +"\\RSDRAW-YRun.EXE", "OnRECASR",5,0x00000001);
}
void CMainFrame::OnRECDABD() //开关量报警记录
{
	theApp.strargc = "OnRECDABD";
	OnMadeMade();
//	C_Ts.CreateP(gstrTimeOut +"\\RSDRAW-YRun.EXE", "OnRECDABD",5,0x00000001);
}
void CMainFrame::OnRECDABB() //开关量断电记录
{
	theApp.strargc = "OnRECDABB";
	OnMadeMade();
//	C_Ts.CreateP(gstrTimeOut +"\\RSDRAW-YRun.EXE", "OnRECDABB",5,0x00000001);
}
void CMainFrame::OnRECDSCD() //开关量状态变动记录
{
	theApp.strargc = "OnRECDSCD";
	OnMadeMade();
//	C_Ts.CreateP(gstrTimeOut +"\\RSDRAW-YRun.EXE", "OnRECDSCD",5,0x00000001);
}
void CMainFrame::OnRECDFED() //开关量馈电异常记录
{
	theApp.strargc = "OnRECDFED";
	OnMadeMade();
//	C_Ts.CreateP(gstrTimeOut +"\\RSDRAW-YRun.EXE", "OnRECDFED",5,0x00000001);
}
void CMainFrame::OnRECDRIVERE() //设备故障记录
{
	theApp.strargc = "OnRECDRIVERE";
	OnMadeMade();
//	C_Ts.CreateP(gstrTimeOut +"\\RSDRAW-YRun.EXE", "OnRECDRIVERE",5,0x00000001);
}
///////记录查询显示/////打印////////////
void CMainFrame::OnEXCELA()  //模拟量记录
{
	theApp.strargc = "OnEXCELA";
	OnMadeMade();
//	C_Ts.CreateP(gstrTimeOut +"\\RSDRAW-YRun.EXE", "OnEXCELA",5,0x00000001);
}
void CMainFrame::OnEXCELAA()  //模拟量报警记录
{
	theApp.strargc = "OnEXCELAA";
	OnMadeMade();
//	C_Ts.CreateP(gstrTimeOut +"\\RSDRAW-YRun.EXE", "OnEXCELAA",5,0x00000001);
}
void CMainFrame::OnEXCELAB()  //模拟量断电记录
{
	theApp.strargc = "OnEXCELAB";
	OnMadeMade();
//	C_Ts.CreateP(gstrTimeOut +"\\RSDRAW-YRun.EXE", "OnEXCELAB",5,0x00000001);
}
void CMainFrame::OnEXCELAFE() //模拟量馈电异常记录
{
	theApp.strargc = "OnEXCELAFE";
	OnMadeMade();
//	C_Ts.CreateP(gstrTimeOut +"\\RSDRAW-YRun.EXE", "OnEXCELAFE",5,0x00000001);
}
void CMainFrame::OnEXCELASR() //模拟量统计值记录
{
	theApp.strargc = "OnEXCELASR";
	OnMadeMade();
//	C_Ts.CreateP(gstrTimeOut +"\\RSDRAW-YRun.EXE", "OnEXCELASR",5,0x00000001);
}
void CMainFrame::OnEXCELDA() //开关量报警记录
{
	theApp.strargc = "OnEXCELDA";
	OnMadeMade();
//	C_Ts.CreateP(gstrTimeOut +"\\RSDRAW-YRun.EXE", "OnEXCELDA",5,0x00000001);
}
void CMainFrame::OnEXCELDAB() //开关量断电记录
{
	theApp.strargc = "OnEXCELDAB";
	OnMadeMade();
//	C_Ts.CreateP(gstrTimeOut +"\\RSDRAW-YRun.EXE", "OnEXCELDAB",5,0x00000001);
}
void CMainFrame::OnEXCELDSCD() //开关量状态变动记录
{
	theApp.strargc = "OnEXCELDSCD";
	OnMadeMade();
//	C_Ts.CreateP(gstrTimeOut +"\\RSDRAW-YRun.EXE", "OnEXCELDSCD",5,0x00000001);
}
void CMainFrame::OnEXCELDFE() //开关量馈电异常记录
{
	theApp.strargc = "OnEXCELDFE";
	OnMadeMade();
//	C_Ts.CreateP(gstrTimeOut +"\\RSDRAW-YRun.EXE", "OnEXCELDFE",5,0x00000001);
}
void CMainFrame::OnEXCELDRIVERE() //设备故障记录
{
	theApp.strargc = "OnEXCELDRIVERE";
	OnMadeMade();
//	C_Ts.CreateP(gstrTimeOut +"\\RSDRAW-YRun.EXE", "OnEXCELDRIVERE",5,0x00000001);
}
///////打印/////分类查询//////////

void CMainFrame::OnALARMS() 
{
	theApp.strargc = "OnALARMS";
	OnMadeMade();
//	C_Ts.CreateP(gstrTimeOut +"\\RSDRAW-YRun.EXE", "OnALARMS",5,0x00000001);
}

void CMainFrame::OnBREAKES() 
{
	theApp.strargc = "OnBREAKES";
	OnMadeMade();
//	C_Ts.CreateP(gstrTimeOut +"\\RSDRAW-YRun.EXE", "OnBREAKES",5,0x00000001);
}

void CMainFrame::OnFEEDES() 
{
	theApp.strargc = "OnFEEDES";
	OnMadeMade();
//	C_Ts.CreateP(gstrTimeOut +"\\RSDRAW-YRun.EXE", "OnFEEDES",5,0x00000001);
}

void CMainFrame::OnSELECTS() 
{
	theApp.strargc = "OnSELECTS";
	OnMadeMade();
//	C_Ts.CreateP(gstrTimeOut +"\\RSDRAW-YRun.EXE", "OnSELECTS",5,0x00000001);
}
///////////////////////分类查询/////////////////////////////
///////////////////////模拟图显示/////////////////////////////
//申明只适用于ON_COMMAND消息的函数申明
//void CMainFrame::OnWAERATION(WPARAM wParam, LPARAM lParam) 
void CMainFrame::OnFileMenuItems(UINT nID)
{
//switch(wParam)
//{
//case IDC_STATIC_OUT1:
//代码1
//break;
	OnMView(nID-2000,1);
}

void CMainFrame::OnWGAS() 
{
	OnMView(0,1);
}

void CMainFrame::OnWSYSTEM() 
{
//	CMenu* pMenu1 = AfxGetMainWnd()->GetMenu();
//sysmenu = pFrame->GetSystemMenu(FALSE);
//	CXTPCommandBars* pCommandBars = GetCommandBars();
	if (!pCommandBars)
		return;

//	BOOL bCustomizeMode = pCommandBars->IsCustomizeMode();
//	pCommandBars->SetCustomizeMode(FALSE);
//	CDialogMenuGrabber ds(m_pFrame);
//	if (ds.DoModal() == IDOK)
	{
//		if (ds.m_wndMenuBar.GetControls()->GetCount() > 0)
		{

//			pMenuBar->GetControls()->RemoveAll();
//			pMenuBar->GetControls()->Copy(ds.m_wndMenuBar.GetControls());
		}
	}

//	pCommandBars->SetCustomizeMode(bCustomizeMode);
			CXTPMenuBar* pMenuBar = pCommandBars->GetMenuBar();
			if (!pMenuBar)
				return;
//			pMenuBar->SetFlags(xtpFlagAddMDISysPopup);
	for(int i=12; i>6 ;i--)   //总的菜单项0-12
			pMenuBar->GetControls()->Remove(i);
//			pMenuBar->GetControls()->RemoveAll();
//			pMenuBar->GetControls()->Copy(pMenuBar->GetControl(1));
//			pMenuBar->LoadMenuBar(IDC_POPLISTCONTROL);
	//Add(CXTPControl* pControl, int nId, LPCTSTR lpszParameter = NULL, int nBefore = -1, BOOL bTemporary = FALSE);
//			pMenuBar->GetControls()->Add(pMenuBar->,2,"ffff",1,TRUE);
    //再添加新的
	CMenu menu;
		VERIFY(menu.LoadMenu(IDR_MAINFRAME));
//		menu.AppendMenu(MF_STRING, 2000, "xxx");
		CMenu* pPopup = menu.GetSubMenu(7);
        pPopup->RemoveMenu(0,MF_BYPOSITION);
        pPopup->RemoveMenu(0,MF_BYPOSITION);
	CString strrsy = theApp.m_strms[18].strl + strMetrics+ "rsy\\";
    for( i =0; i < 100 ;i++)
	{
		CString strclm = theApp.m_RTDM.m_strdf[theApp.m_RTDM.Initfbl(strMetrics)][i].strl;
		strclm.Replace(strrsy,"");
		int n_ish = strclm.Find("\\");
		if(n_ish>0)
			break;
		if(strclm == "")
			break;
		int m_ishave = strclm.GetLength();
		strclm = strclm.Mid(0 ,m_ishave-4);
        pPopup->AppendMenu(MF_STRING, i+2000, strclm);
	}
//    pPopup->AppendMenu(MF_SEPARATOR);
//	pPopup->DeleteMenu(11,MF_BYPOSITION);
//	kkkk=pPopup->GetMenuItemCount();
#ifdef _DEBUG
	for( i=7; i<13 ;i++)
       pMenuBar->GetControls()->AddMenuItem(&menu,i);
//       pCommandBars->GetMenuBar()->LoadMenu(&menu , TRUE); ;
#else
	for( i=7; i<12 ;i++)
       pMenuBar->GetControls()->AddMenuItem(&menu,i);
//       pCommandBars->GetMenuBar()->LoadMenu(&menu , TRUE); ;
#endif //_DEBUG
//	pPopup->DestroyMenu();
//	menu.DestroyMenu();
//	pMenuBar->Invalidate(FALSE);
//	pMenuBar->RefreshMenu();
//   CMenu   *pMenu   =   new   CMenu();
//  HMENU   hMenu   =   pSysMenu->Detach();  
//  pMenu->Attach(hMenu);  
//  SetMenu(NULL);   
//  SetMenu(pMenu);   
//  m_pMenu = AddSubMenu(pMenuBar->GetFrameSite(), 0, 0, "Dynamic Menu",NULL); 
//	CMenu* pMenu= _GetDynaPopupMenu1();
//	m_pMenu = CMenu::FromHandle( m_wndMenuBar.GetHMenu() );
//	CMenu* pSubMenu = m_pMenu->GetSubMenu(2);
    OnTheme(ID_THEME_VC6);
	CXTPPaintManager::SetTheme(xtpThemeVisualStudio2008);  //xtpThemeVisualStudio2008

//    AfxGetMainWnd()->DrawMenuBar(); //重画菜单
}

/** @brief Return from the menu bar the CMenu with name 'DynaPopupMenu1'
* @return CMenu* a pointer on the menu found (NULL if failed)
* @todo should have a more generic implementation
*/
CMenu* CMainFrame::_GetDynaPopupMenu1()
{
	CMenu* pMenu = NULL;
//	CMenu* pTopMenu = GetMenu();
	CMenu* pTopMenu = AfxGetMainWnd()->GetMenu();
	CMenu* pSubMenu;
	CString strMenu;
	int i;
	int j;
	int iCount1;
	int iCount2;

	iCount1= pTopMenu->GetMenuItemCount();
	for(i= 0; i < iCount1; ++i)
	{
		pTopMenu->GetMenuString( i, strMenu, MF_BYPOSITION );
		if(strMenu == _T("MyDynaMenu"))
		{
			pSubMenu = pTopMenu->GetSubMenu(i);
			if(pSubMenu)
			{
				iCount2= pSubMenu->GetMenuItemCount();
				for(j= 0; j < iCount2; ++j)
				{
					pSubMenu->GetMenuString( j, strMenu, MF_BYPOSITION );
					if(strMenu == "DynaPopupMenu1")
					{
						pMenu= pSubMenu->GetSubMenu(j);
						if(pMenu){
							return pMenu;
						}
					}
				}
			}
		}
	}
	ASSERT(pMenu != NULL);
	return pMenu;
}

//开关量状态图、
void CMainFrame::OnCDS() 
{
	strCli = "OnCDS|"+strCli;
	C_Ts.CreateP(gstrTimeOut +"\\RS_YCurve.exe",m_Str2Data.CStringtocharp(strCli),5,0x00000001);
}
//柱状图
void CMainFrame::OnCDC() 
{
	strCli = "OnCDC|"+strCli;
	C_Ts.CreateP(gstrTimeOut +"\\RS_YCurve.exe", m_Str2Data.CStringtocharp(strCli),5,0x00000001);
}

void CMainFrame::OnCASelect() 
{
	strCli = "OnCASelect|"+strCli;
	C_Ts.CreateP(gstrTimeOut +"\\RS_YCurve.exe", m_Str2Data.CStringtocharp(strCli),5,0x00000001);
}

void CMainFrame::OnCAALARM() 
{
	strCli = "OnCAALARM|"+strCli;
	C_Ts.CreateP(gstrTimeOut +"\\RS_YCurve.exe", m_Str2Data.CStringtocharp(strCli),5,0x00000001);
}

void CMainFrame::OnCABREAK() 
{
	strCli = "OnCABREAK|"+strCli;
	C_Ts.CreateP(gstrTimeOut +"\\RS_YCurve.exe", m_Str2Data.CStringtocharp(strCli),5,0x00000001);
}

void CMainFrame::OnCAFEED() 
{
	strCli = "OnCAFEED|"+strCli;
	C_Ts.CreateP(gstrTimeOut +"\\RS_YCurve.exe", m_Str2Data.CStringtocharp(strCli),5,0x00000001);
}
//曲线页面编辑
void CMainFrame::OnCurveADP() 
{
	C_Ts.CreateP(gstrTimeOut +"\\RS_YCurve.exe", "OnCurveADP",5,0x00000001);
}

///////////////////////模拟图编辑显示/////////////////////////////
void CMainFrame::OnEDRAW() 
{
 /*       	CMDIFrameWnd *pFrame = (CMDIFrameWnd*)AfxGetApp()->m_pMainWnd;
         	CMDIChildWnd *pChild = (CMDIChildWnd *) pFrame->GetActiveFrame();
         	CDrawView *pView = (CDrawView*)pChild->GetActiveView();	
			if(!pView->IsKindOf(RUNTIME_CLASS(CDrawView)))
           		return;
			CDrawDoc* pThisOne = (CDrawDoc *)pChild->GetActiveDocument() ;
			pThisOne->OnCloseDocument();*/

	C_Ts.CreateP(gstrTimeOut +"\\YDraw.exe", "",5,0x00000001);
}

void CMainFrame::OnCLASSTIME() 
{
	CClassTime dlg;
	dlg.DoModal();
}

void CMainFrame::OnSafeMethod() 
{
	CDASafeMehod dlg;
	dlg.DoModal();
}

void CMainFrame::OnAdjustdis() 
{
	CAdjustDlg dlg;
	dlg.DoModal();
}

void CMainFrame::OnLOGIN() 
{
	theApp.curuser = "请登陆";
	CLoginDlg dlg;
	dlg.m_strdism = "login";
	dlg.DoModal();
}

void CMainFrame::OnLOGOUT() 
{
	CLoginDlg dlg;
	dlg.m_strdism = "login";
	dlg.DoModal();
}

void CMainFrame::OnSAVEFD() 
{
	CString strrsy ,strclm,strrsy1,strclm1;
    // 字符串 buf 表示要遍历的目录名   char dirName[300]; 
	strrsy = gstrTimeOut + "\\" + strMetrics+ "rsy\\";
	strrsy1 ="dispoint"+strMetrics;

		 CppSQLite3Query q;

    		CString strSQL,strSQL1;
           for(int m =0; m < theApp.m_addfilesy.size() ;m++)
		   {
			 strSQL1 = theApp.m_addfilesy[m];
				strSQL.Format("UPDATE '%s' SET LP0='%s' WHERE DISID = %d;",
					strrsy1,strSQL1,m+1);
             q = theApp.db3.execQuery(strSQL);
		   }
		     for(int i=theApp.m_addfilesy.size()+1 ;i<100;i++)
			 {
				strSQL.Format("UPDATE '%s' SET LP0='' WHERE DISID = %d;",
					strrsy1,i);
                q = theApp.db3.execQuery(strSQL);
			 }
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
//模拟图显示menu
void CMainFrame::OnMView(int menun,int myf) 
{
	CString strrsy,strTemp1 ;
	strrsy = theApp.m_strms[18].strl + strMetrics+ "rsy\\";
	strTemp1 = theApp.m_RTDM.m_strdf[theApp.m_RTDM.Initfbl(strMetrics)][menun].strl;
	strTemp1.Replace(strrsy,"");
	strrsy = gstrTimeOut + "\\" + strMetrics+ "rsy\\" ;
	if(myf == 1)
    	strTemp1 = strrsy + strTemp1;
	else if(myf == 0)
    	strTemp1 = theApp.m_addfilesy[menun];

            	CMDIFrameWnd *pFrame = (CMDIFrameWnd*)AfxGetApp()->m_pMainWnd;
              	CMDIChildWnd *pChild = (CMDIChildWnd *) pFrame->GetActiveFrame();
               	CDrawView *pView = (CDrawView*)pChild->GetActiveView();	
				CSampleFormView *sview =(CSampleFormView*)pChild->GetActiveView();
		        CString strTemp; int m_isdrawf = 0;
				m_ViewPos = NULL;

				for(int i=0;i<theApp.m_addfilesy.size()+2;i++)
				{
                	CString strclm = strTemp1;
             		int m_ishave = strclm.GetLength();
             		strclm = strclm.Mid(m_ishave-3,3);
		           if(strclm == "rsy")
				   {
    	        		if(m_ViewPos != NULL)
						{
			            	theApp.m_map.GetNextAssoc(m_ViewPos,strTemp,pView);
							if(strTemp == strTemp1)
							{
								m_isdrawf =100;
//       		            	if(pView != NULL)
			            		pView->GetParentFrame()->ActivateFrame();
								break;
							}
						}
		            	else 
		    	        	m_ViewPos = theApp.m_map.GetStartPosition() ;     //0415
				   }
				   else
				   {
    	        		if(s_ViewPos != NULL)
						{
			            	theApp.m_Sam.GetNextAssoc(s_ViewPos,strTemp,sview);
							if(strTemp == strTemp1)
							{
			            		sview->GetParentFrame()->ActivateFrame();
								break;
							}
						}
		            	else 
		    	        	s_ViewPos = theApp.m_Sam.GetStartPosition() ;     //0415
				   }
				}
				if(m_isdrawf ==0 && myf == 1)
				{
            		theApp.pDocTemplate->OpenDocumentFile(strTemp1) ;
         			theApp.m_addfilesy.push_back(strTemp1);
				}
}

void CMainFrame::Msg(int iItem, CString str1,CString str2,CString str3,CString str4,CString str5)
{
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


void CMainFrame::CreateP(CString str1,char *str2)
{
      PROCESS_INFORMATION pi; //启动窗口的信息
           STARTUPINFO si; //进程的信息
           memset(&si,0,sizeof(si));
           si.cb=sizeof(si);
           si.wShowWindow=SW_SHOW;
           si.dwFlags=STARTF_USESHOWWINDOW;
     int fRet=CreateProcess(str1,str2,NULL,FALSE,NULL,NULL,NULL,NULL,&si,&pi);
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
//	pZoomPane->SetWidth(130);
	
//	pZoomPane->SetPos(100);
//	pZoomPane->SetRange(0, 200);
//	pZoomPane->SetStyle(SBPS_NOBORDERS);

//	pZoomPane->SetBeginGroup(FALSE);

	pZoomPane->SetCaption(_T("&Zoom Slider"));
	pZoomPane->SetTooltip(_T("Zoom"));

}

void CMainFrame::AddSwitchButtons()
{
	static UINT switches[] =
	{
		IDI_STOP,
//			IDI_ICONMA,
//		ID_INDICATOR_PRINT,
//		ID_INDICATOR_FULLSCREEN,
//		ID_INDICATOR_WEB,
//		ID_INDICATOR_OUTLINE,
//		ID_INDICATOR_DRAFT,
	};

	CXTPStatusBarSwitchPane* pSwitchPane = (CXTPStatusBarSwitchPane*)m_wndStatusBar.AddIndicator(new CXTPStatusBarSwitchPane(), 5);
//	CXTPStatusBarSwitchPane* pSwitchPane = (CXTPStatusBarSwitchPane*)m_wndStatusBar.AddIndicator(new CXTPStatusBarSwitchPane(), ID_INDICATOR_VIEW);
	pSwitchPane->SetSwitches(switches, sizeof(switches)/sizeof(UINT));
	pSwitchPane->SetChecked(IDI_STOP);

	for (int i = 0; i < sizeof(switches)/sizeof(UINT); i++)
	{
		m_wndStatusBar.GetImageManager()->SetIcon(switches[i], switches[i]);
	}

	pSwitchPane->BestFit();

	m_wndStatusBar.UpdateAllPanes(TRUE, FALSE);

	m_strMessage.LoadString(IDI_STOP);
}

void CMainFrame::OnSoundStop()
{
    m_RepeatFlag=FALSE;
}

void CMainFrame::DoPlayWarnSound(CString strFileName)
{
//	strFileName.Format("%swarnsound%d.wav", GetAppPath() + "sound\\", uWarnNo+1);
	if(m_RepeatFlag && m_bSoundPath)
        sndPlaySound(strFileName,SND_ASYNC);	
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
	CXTPStatusBarPane* pPane = m_wndStatusBar.AddIndicator(ID_INDICATOR_EDIT,3);

	// Initialize the pane info and add the control.
	int nIndex = m_wndStatusBar.CommandToIndex(ID_INDICATOR_EDIT);
	ASSERT (nIndex != -1);

	m_wndStatusBar.SetPaneWidth(nIndex, 120);
	m_wndStatusBar.SetPaneStyle(nIndex, m_wndStatusBar.GetPaneStyle(nIndex) | SBPS_NOBORDERS);
//	m_wndStatusBar.AddControl(&m_wndEditCtrl, ID_INDICATOR_EDIT, FALSE);
	m_wndStatusBar.SetPaneText(m_wndStatusBar.CommandToIndex(ID_INDICATOR_EDIT),s); //显示时钟

//	pPane->SetCustomizationVisible(TRUE);
}

void CMainFrame::AddUser()
{
	// add the indicator to the status bar.   ID_INDICATOR_EDIT
	CXTPStatusBarPane* pPane = m_wndStatusBar.AddIndicator(ID_INDICATOR_USER,4);

	// Initialize the pane info and add the control.
	int nIndex = m_wndStatusBar.CommandToIndex(ID_INDICATOR_USER);
	ASSERT (nIndex != -1);

	m_wndStatusBar.SetPaneWidth(nIndex, 60);
	m_wndStatusBar.SetPaneStyle(nIndex, m_wndStatusBar.GetPaneStyle(nIndex) | SBPS_NOBORDERS);
//	m_wndStatusBar.AddControl(&m_wndEditCtrl, ID_INDICATOR_EDIT, FALSE);
	m_wndStatusBar.SetPaneText(m_wndStatusBar.CommandToIndex(ID_INDICATOR_USER),theApp.curuser); //显示用户

//	pPane->SetCustomizationVisible(TRUE);
}

void CMainFrame::AddMessage(CString strMessage)
{
	// add the indicator to the status bar.   ID_INDICATOR_EDIT
	CXTPStatusBarPane* pPane = m_wndStatusBar.AddIndicator(ID_INDICATOR_MESSAGE,2);

	// Initialize the pane info and add the control.
	int nIndex = m_wndStatusBar.CommandToIndex(ID_INDICATOR_MESSAGE);
	ASSERT (nIndex != -1);

	m_wndStatusBar.SetPaneWidth(nIndex, 300);
	m_wndStatusBar.SetPaneStyle(nIndex, m_wndStatusBar.GetPaneStyle(nIndex) | SBPS_NOBORDERS);
//	m_wndStatusBar.AddControl(&m_wndEditCtrl, ID_INDICATOR_EDIT, FALSE);
	m_wndStatusBar.SetPaneText(m_wndStatusBar.CommandToIndex(ID_INDICATOR_MESSAGE),strMessage); //显示操作信息

//	pPane->SetCustomizationVisible(TRUE);
}

void CMainFrame::AddLogo()
{
#if 0 // Obsolete 

	if (!m_wndLogoPane.Create(_T("阳光金力软件"), &m_wndStatusBar))
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
	pPane->SetText(_T("阳光金力软件"));
	pPane->SetTextColor(0x915f36);
	CXTPPaintManager::CNonClientMetrics ncm;
	ncm.lfMenuFont.lfWeight = FW_BOLD;
	pPane->SetTextFont(&ncm.lfMenuFont);
#else
	m_wndStatusBar.EnableMarkup(TRUE);
	pPane->SetText(_T("<TextBlock VerticalAlignment='Center'><Bold><Run Foreground='#365f91'>阳光金力</Run> <Run Foreground='Black'>软件</Run></Bold></TextBlock>"));
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
	CXTPStatusBarPane* pPane = m_wndStatusBar.AddIndicator(ID_INDICATOR_PROG,1);

	// Initialize the pane info and add the control.
	int nIndex = m_wndStatusBar.CommandToIndex(ID_INDICATOR_PROG);
	ASSERT (nIndex != -1);

	pPane->SetCaption(pPane->GetText());
	pPane->SetText(_T("edrrrgrdffffff"));

	m_wndStatusBar.SetPaneWidth(nIndex, 150);
	m_wndStatusBar.SetPaneStyle(nIndex, m_wndStatusBar.GetPaneStyle(nIndex) | SBPS_NOBORDERS);
	m_wndStatusBar.AddControl(&m_wndProgCtrl, ID_INDICATOR_PROG, FALSE);

	// initialize progress control.
//	m_wndProgCtrl.SetRange (0, 5000);
//	m_wndProgCtrl.SetPos (0);
//	m_wndProgCtrl.SetStep (1);
	pPane->SetCustomizationVisible(TRUE);
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

/*	CXTPPropExchangeXMLNode px(FALSE, 0, _T("Settings"));
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
*/

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
//	RecalcLayout(TRUE);
}

void CMainFrame::OnUpdateOnSoundPath(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_bSoundPath);
//	pCmdUI->Enable(theApp.m_bLogIn);
}

void CMainFrame::OnUpdateDis(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(theApp.m_bLogIn);
}

void CMainFrame::OnUpdateLog(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(!theApp.m_bLogIn);
}

void CMainFrame::OnOpenR() 
{
            	CMDIFrameWnd *pFrame = (CMDIFrameWnd*)AfxGetApp()->m_pMainWnd;
              	CMDIChildWnd *pChild = (CMDIChildWnd *) pFrame->GetActiveFrame();
//               	m_MadeCert = (CMadeCertView*)pChild->GetActiveView();
//    			if(m_MadeCert->IsKindOf(RUNTIME_CLASS(CMadeCertView)) && m_MadeCert != NULL)
				{
        			CRViewDoc* pThisOne ;//= (CRViewDoc *)pChild->GetActiveDocument() ;
	         		pThisOne->OnCloseD();
				}
//    m_ThreadPool.Add(new CThreadObject(*this, 3));  
}
void CMainFrame::OnCloseR() 
{
    m_ThreadPool.Add(new CThreadObject(*this, 4));
}

void CMainFrame::OnMadeMade() 
{
            	CMDIFrameWnd *pFrame = (CMDIFrameWnd*)AfxGetApp()->m_pMainWnd;
              	CMDIChildWnd *pChild = (CMDIChildWnd *) pFrame->GetActiveFrame();
               	CMadeCertView *prView = (CMadeCertView*)pChild->GetActiveView();
    			if(prView->IsKindOf(RUNTIME_CLASS(CMadeCertView)) && prView != NULL)
				{
        			CRViewDoc* pThisOne = (CRViewDoc *)pChild->GetActiveDocument() ;
	         		pThisOne->OnCloseDocument();
				}
	CString strrsy;
	strrsy = gstrTimeOut + "\\" + strMetrics+ "rsy\\";
    theApp.pRDocTemplate->OpenDocumentFile(strrsy + "实时数据.rsf") ;

	//	m_currentwin=4;//制作
/*	if(m_pMade!=NULL)
	{
		m_pMade->MDIActivate();
		return;
	}
	m_pMade=new CChildFrame();
	CCreateContext context;
	context.m_pNewViewClass=RUNTIME_CLASS(CMadeCertView);
//	m_MadeCert->m_stragrv = theApp.strargc;
	if(!m_pMade->LoadFrame(ID_INDICATOR_PRINT,WS_MAXIMIZE|WS_OVERLAPPEDWINDOW,this,&context))
		return;
//	m_pMade->SetWindowPos(this,0,0,GetSystemMetrics(SM_CXSCREEN)-8,140,SWP_NOMOVE|SWP_NOZORDER | SWP_NOACTIVATE|SWP_SHOWWINDOW);
	m_pMade->ShowWindow(SW_SHOWNORMAL);
//	m_pMade->InitialUpdateFrame(NULL,true);   //如用就加载两次
*/
}

void CMainFrame::ModifySystem()
{
//	CDynamicMenu  *dmenu;
// dmenu->modifyMenuItem("系统(&S)", "登录(&L)", "注销(&Z)");
// dmenu->addMenuItem("系统(&S)", "用户管理(&U)","注销(&Z)",140002);
//	dmenu->createMenu();
//	dmenu->addMenu("用户管理(&U)","登录(&L)",140003);
}

//////////////////////////////////////////////////////////////////////
void CMainFrame::addEqupmentManagerMenuItem()
{
//	CDynamicMenu  *dmenu;
// dmenu->createMenuItemChild();
// dmenu->appendMenuItem(150001, "设备管理(&D)");
// dmenu->appendMenuItem(150002,"用户编号管理(&U)");
// dmenu->addMenu("系统(&S)", "设备管理(&M)", 150000);
}

void CMainFrame::addCopyDataMenuItem()
{
//	CDynamicMenu  *dmenu;
// dmenu->createMenuItemChild();
// dmenu->appendMenuItem(160001, "抄录电表(&R)");
// dmenu->addMenu("设备管理(&M)", "抄录电表(&R)", 160000);
}

void CMainFrame::setEnableItem()
{
//	CDynamicMenu  *dmenu;
// dmenu->setEnable("设备管理(&M)", 150001, 1);
}

void CMainFrame::OnManipulate() 
{
		m_paneManager.ClosePane(201);
			paneResourceView->Select();

//	ModifySystem();
//	addEqupmentManagerMenuItem();
//	addCopyDataMenuItem();
//	setEnableItem();
/*
CMenu*pMenu=this->GetMenu(); 
CMenu*pmSub=pMenu->GetSubMenu(0);//2，port 


pmSub->InsertMenu(-1,MF_CHECKED|MF_STRING,100, "1 "); 
                  pmSub->InsertMenu(-1,MF_CHECKED|MF_STRING,200, "2 "); 
                  pmSub->InsertMenu(-1,MF_CHECKED|MF_STRING,300, "3 "); 

this->DrawMenuBar();

CMenu   sortMenu; 
sortMenu.CreatePopupMenu(); 
sortMenu.AppendMenu(MF_BYCOMMAND   |   MF_STRING   |   MF_ENABLED,TG::eSortForType,_T( "1 ")); 
sortMenu.AppendMenu(MF_BYCOMMAND   |   MF_STRING   |   MF_ENABLED,TG::eSortForState,_T( "2 ")); 
hMenu   =   sortMenu.GetSafeHmenu(); 

pMenu-> AppendMenu(MF_POPUP,(UINT)hMenu,_T( "port ")); 

HMENU hPopmenu;
hPopmenu=CreateMenu();

CMenu menu;
menu.CreatePopupMenu();
GetMenu()->AppendMenu(MF_POPUP,(UINT)menu.m_hMenu,"Append");
//并给它添加菜单项：
menu.AppendMenu(MF_STRING,111,"HELLO");
//然后在菜单的首位置插入一个子菜单：
GetMenu()->InsertMenu(MF_POPUP,(UINT)menu.m_hMenu,0,"Insert");
*/

//        AfxGetMainWnd()->SetMenu(NULL);
//		AfxGetMainWnd()->DrawMenuBar();
/*
CMenu addmenu,*mainmenu; 
if(!addmenu.LoadMenu(IDR_MAINFRAME)) //装入菜单资源。
{ 
MessageBox("菜单装入失败!","错误",MB_OK|MB_ICONERROR); 
return; //如装入失败，显示消息框，且返回。 
}
CString str="颜色(&C)"; //要增加的菜单项的标签。 
mainmenu=AfxGetMainWnd()->GetMenu(); 
//取得指向窗口菜单的Cmenu对象的指针。 
mainmenu->InsertMenu (1,MF_POPUP|MF_BYPOSITION|MF_STRING,(UINT)addmenu.GetSubMenu(0)->m_hMenu,str); 
//将弹出式菜单插入到第2项菜单之前（菜单项从0开始计算）。 
// addmenu.GetSubMenu(0)-> m_hMenu是被装入菜单的第一个菜单项的弹出式菜单的菜单句柄。 
mainmenu->Detach(); //将窗口菜单和Cmenu对象分离。 
addmenu.Detach(); //将资源菜单（IDR_MENU1）和Cmenu对象分离。 
DrawMenuBar(); //重画菜单。 
*/
}

void CMainFrame::OnLButtonDown(UINT nFlags, CPoint point) 
{
    MessageBox("菜单装入失败!","错误",MB_OK|MB_ICONERROR); 

	CMDIFrameWnd::OnLButtonDown(nFlags, point);
}

void CMainFrame::Sqlite3define() 
{
	CString strrsy,strclm ;
		 CppSQLite3Query q;

//         q = db3.execQuery(temp);
//		temp.Format("INSERT into dispoint1024 values(0, '', '', '', '', '', '', '', '', '', '', '', '', '', '', '', '', '', '', '');");
//		char  *temp3 = temp.GetBuffer(temp.GetLength());;
//			db3.execDML("INSERT into dispoint1024 values(0, '', '', '', '', '', '', '', '', '', '', '', '', '', '', '', '', '', '', '');");
//				strSQL.Format("INSERT into dispoint1024 SET DISID = %d;",i);
//			db3.execDML("INSERT into dispoint1024 values(0, '', '', '', '', '', '', '', '', '', '', '', '', '', '', '', '', '', '');");
//		 db3.SQLiteVersion();
//        remove(strclm);
		CString  temp;
        theApp.db3.execDML("create table dispoint1024(DISID int, LP0 char(500), LP1 char(100), LP2 char(100), LP3 char(100), LP4 char(100), LP5 char(100),LP6 char(100), LP7 char(100), LP8 char(100), LP9 char(100), LP10 char(100), LP11 char(100),LP12 char(100), LP13 char(100), LP14 char(100), LP15 char(100), LP16 char(100), LP17 char(100),LP18 char(100), LP19 char(100));");
        for(int i=0;i<1000;i++)
		{
			temp.Format("insert into dispoint1024 values(%d, '', '','', '', '', '', '', '', '', '', '', '', '', '', '', '', '', '', '', '');",i);
			theApp.db3.execDML(temp);
		}
        theApp.db3.execDML("create table dispoint1280(DISID int, LP0 char(500), LP1 char(100), LP2 char(100), LP3 char(100), LP4 char(100), LP5 char(100),LP6 char(100), LP7 char(100), LP8 char(100), LP9 char(100), LP10 char(100), LP11 char(100),LP12 char(100), LP13 char(100), LP14 char(100), LP15 char(100), LP16 char(100), LP17 char(100),LP18 char(100), LP19 char(100));");
        for( i=0;i<1000;i++)
		{
			temp.Format("insert into dispoint1280 values(%d, '', '','', '', '', '', '', '', '', '', '', '', '', '', '', '', '', '', '', '');",i);
			theApp.db3.execDML(temp);
		}
        theApp.db3.execDML("create table dispoint1360(DISID int, LP0 char(500), LP1 char(100), LP2 char(100), LP3 char(100), LP4 char(100), LP5 char(100),LP6 char(100), LP7 char(100), LP8 char(100), LP9 char(100), LP10 char(100), LP11 char(100),LP12 char(100), LP13 char(100), LP14 char(100), LP15 char(100), LP16 char(100), LP17 char(100),LP18 char(100), LP19 char(100));");
        for( i=0;i<1000;i++)
		{
			temp.Format("insert into dispoint1360 values(%d, '', '','', '', '', '', '', '', '', '', '', '', '', '', '', '', '', '', '', '');",i);
			theApp.db3.execDML(temp);
		}
        theApp.db3.execDML("create table dispoint1366(DISID int, LP0 char(500), LP1 char(100), LP2 char(100), LP3 char(100), LP4 char(100), LP5 char(100),LP6 char(100), LP7 char(100), LP8 char(100), LP9 char(100), LP10 char(100), LP11 char(100),LP12 char(100), LP13 char(100), LP14 char(100), LP15 char(100), LP16 char(100), LP17 char(100),LP18 char(100), LP19 char(100));");
        for( i=0;i<1000;i++)
		{
			temp.Format("insert into dispoint1366 values(%d, '', '','', '', '', '', '', '', '', '', '', '', '', '', '', '', '', '', '', '');",i);
			theApp.db3.execDML(temp);
		}

        theApp.db3.execDML("create table dispoint1400(DISID int, LP0 char(500), LP1 char(100), LP2 char(100), LP3 char(100), LP4 char(100), LP5 char(100),LP6 char(100), LP7 char(100), LP8 char(100), LP9 char(100), LP10 char(100), LP11 char(100),LP12 char(100), LP13 char(100), LP14 char(100), LP15 char(100), LP16 char(100), LP17 char(100),LP18 char(100), LP19 char(100));");
        for( i=0;i<1000;i++)
		{
			temp.Format("insert into dispoint1400 values(%d, '', '','', '', '', '', '', '', '', '', '', '', '', '', '', '', '', '', '', '');",i);
			theApp.db3.execDML(temp);
		}
        theApp.db3.execDML("create table dispoint1440(DISID int, LP0 char(500), LP1 char(100), LP2 char(100), LP3 char(100), LP4 char(100), LP5 char(100),LP6 char(100), LP7 char(100), LP8 char(100), LP9 char(100), LP10 char(100), LP11 char(100),LP12 char(100), LP13 char(100), LP14 char(100), LP15 char(100), LP16 char(100), LP17 char(100),LP18 char(100), LP19 char(100));");
        for( i=0;i<1000;i++)
		{
			temp.Format("insert into dispoint1440 values(%d, '', '','', '', '', '', '', '', '', '', '', '', '', '', '', '', '', '', '', '');",i);
			theApp.db3.execDML(temp);
		}
        theApp.db3.execDML("create table dispoint1600(DISID int, LP0 char(500), LP1 char(100), LP2 char(100), LP3 char(100), LP4 char(100), LP5 char(100),LP6 char(100), LP7 char(100), LP8 char(100), LP9 char(100), LP10 char(100), LP11 char(100),LP12 char(100), LP13 char(100), LP14 char(100), LP15 char(100), LP16 char(100), LP17 char(100),LP18 char(100), LP19 char(100));");
        for( i=0;i<1000;i++)
		{
			temp.Format("insert into dispoint1600 values(%d, '', '','', '', '', '', '', '', '', '', '', '', '', '', '', '', '', '', '', '');",i);
			theApp.db3.execDML(temp);
		}
        theApp.db3.execDML("create table dispoint1680(DISID int, LP0 char(500), LP1 char(100), LP2 char(100), LP3 char(100), LP4 char(100), LP5 char(100),LP6 char(100), LP7 char(100), LP8 char(100), LP9 char(100), LP10 char(100), LP11 char(100),LP12 char(100), LP13 char(100), LP14 char(100), LP15 char(100), LP16 char(100), LP17 char(100),LP18 char(100), LP19 char(100));");
        for( i=0;i<1000;i++)
		{
			temp.Format("insert into dispoint1680 values(%d, '', '','', '', '', '', '', '', '', '', '', '', '', '', '', '', '', '', '', '');",i);
			theApp.db3.execDML(temp);
		}
        theApp.db3.execDML("create table dispoint1920(DISID int, LP0 char(500), LP1 char(100), LP2 char(100), LP3 char(100), LP4 char(100), LP5 char(100),LP6 char(100), LP7 char(100), LP8 char(100), LP9 char(100), LP10 char(100), LP11 char(100),LP12 char(100), LP13 char(100), LP14 char(100), LP15 char(100), LP16 char(100), LP17 char(100),LP18 char(100), LP19 char(100));");
        for( i=0;i<1000;i++)
		{
			temp.Format("insert into dispoint1920 values(%d, '', '','', '', '', '', '', '', '', '', '', '', '', '', '', '', '', '', '', '');",i);
			theApp.db3.execDML(temp);
		}
        theApp.db3.execDML("create table dispoint2048(DISID int, LP0 char(500), LP1 char(100), LP2 char(100), LP3 char(100), LP4 char(100), LP5 char(100),LP6 char(100), LP7 char(100), LP8 char(100), LP9 char(100), LP10 char(100), LP11 char(100),LP12 char(100), LP13 char(100), LP14 char(100), LP15 char(100), LP16 char(100), LP17 char(100),LP18 char(100), LP19 char(100));");
        for( i=0;i<1000;i++)
		{
			temp.Format("insert into dispoint2048 values(%d, '', '','', '', '', '', '', '', '', '', '', '', '', '', '', '', '', '', '', '');",i);
			theApp.db3.execDML(temp);
		}
        theApp.db3.execDML("create table dispoint2560(DISID int, LP0 char(500), LP1 char(100), LP2 char(100), LP3 char(100), LP4 char(100), LP5 char(100),LP6 char(100), LP7 char(100), LP8 char(100), LP9 char(100), LP10 char(100), LP11 char(100),LP12 char(100), LP13 char(100), LP14 char(100), LP15 char(100), LP16 char(100), LP17 char(100),LP18 char(100), LP19 char(100));");
        for( i=0;i<1000;i++)
		{
			temp.Format("insert into dispoint2560 values(%d, '', '','', '', '', '', '', '', '', '', '', '', '', '', '', '', '', '', '', '');",i);
			theApp.db3.execDML(temp);
		}
}

void CMainFrame::Sqlite3init() 
{
	CString strrsy ,strclm,strclm1;
    CString strSQL,strSQL1,strrsy1;
	strrsy = gstrTimeOut + "\\" + strMetrics+ "rsy\\";
	strrsy1 ="dispoint"+strMetrics;
//		 CppSQLite3Query q;

		CString  temp;
//        theApp.db3.execDML("create table dispoint1024(DISID int, LP0 char(500), LP1 char(100), LP2 char(100), LP3 char(100), LP4 char(100), LP5 char(100),LP6 char(100), LP7 char(100), LP8 char(100), LP9 char(100), LP10 char(100), LP11 char(100),LP12 char(100), LP13 char(100), LP14 char(100), LP15 char(100), LP16 char(100), LP17 char(100),LP18 char(100), LP19 char(100));");
        for(int i=1;i<20;i++)
		{
            strSQL.Format("UPDATE '%s' SET LP%d='%d' WHERE DISID=10;",
			    	     strrsy1,i,(i-1)*3+1 );
//			temp.Format("UPDATE into dispoint1024 values(%d, '', '','', '', '', '', '', '', '', '', '', '', '', '', '', '', '', '', '', '');",i);
			theApp.db3.execDML(strSQL);
            strSQL.Format("UPDATE '%s' SET LP%d='%d' WHERE DISID=110;",
			    	     strrsy1,i,(i-1)*3+2 );
			theApp.db3.execDML(strSQL);
            strSQL.Format("UPDATE '%s' SET LP%d='%d' WHERE DISID=210;",
			    	     strrsy1,i,(i-1)*3+3 );
			theApp.db3.execDML(strSQL);
		}
}

//LRESULT CMainFrame::On1000ThreadMessage(WPARAM wParam, LPARAM)
void CMainFrame::OnTimer(UINT nIDEvent) 
{
//	 if(m_nPaneID == 60)
    CTime terror = CTime::GetCurrentTime();
	int  n_t =terror.GetYear();
	int  n_tm =terror.GetMonth();
	if(n_t>2010 && n_tm>6)
		return;

#ifdef _DEBUG
LARGE_INTEGER liCount1,liCount2,ui1,ui2;
LARGE_INTEGER liFrequency;
QueryPerformanceFrequency(&liFrequency);//每秒记数
#endif //_DEBUG
//	DWORD t1, t2; 
	switch(nIDEvent)
	{
    	case CALRTDATA: 
			{
				CString strclm1;
#ifdef _DEBUG
				QueryPerformanceCounter(&liCount1);
//				t1 = timeGetTime();
#endif //_DEBUG
				if(m_SlaveStation[1][0].Channel_state != 0xa0 && theApp.m_FdsScan ==50)
				{
					for(int i = n_m60; i<61 ;i++)//过滤没定义分站
					{
                     	if(m_ndkSend[i][1]>0 && m_ndkSend[i][1]<61)
						{ 
							if(m_SlaveStation[i][0].Channel_state != 0x90 && m_SlaveStation[i][0].Channel_state != 0xa1 && m_SerialF[i].cfds !=0)
							{
                             	theApp.b_startc =FALSE;
        		     		    theApp.m_RTDM.CalRTdata(i);
                             	theApp.b_startc = TRUE;
    		            		strclm1.Format(":      %d",i);
							}
    			        	n_m60 = i+1;
	       					if(n_m60==61)
            					n_m60 =1;
							break;
						}
						if(i==60)
        					n_m60 =1;
					}
				}

				//caohaitao
				CString strclm;
#ifdef _DEBUG
				QueryPerformanceCounter(&liCount2);
//				t2 = timeGetTime();
				double f_ms= (double)(liCount2.QuadPart-liCount1.QuadPart)*1000/(double)liFrequency.QuadPart;
				if(f_ms >5)
				{
    				strclm.Format("        RT:           %.3f ms",f_ms);
					theApp.m_DebugInfo.push_back(terror.Format("%Y-%m-%d,%H:%M:%S    ")+strclm +strclm1);
//                    g_Log.StatusOut(strclm);
				}
#endif //_DEBUG
			}
			break;
    	case UIREFRESH:  
			{
			}
     		break;
    	case ABFREFRESH:  
			{
#ifdef _DEBUG
				QueryPerformanceCounter(&liCount1);
#endif //_DEBUG
				CString strneterr;
				theApp.internet30s++;
				if((theApp.internet30s == 2||theApp.internet30s == 4)) //10 25
				{
					if(theApp.m_FdsScan ==0 && theApp.internet30s == 2)
					{
				    		theApp.StartClient();
					}
					if(theApp.m_FdsScan ==50 )//连接成功
					{
        	            CNDKMessage message1(SENDSTARTTIME);
	    				message1.Add(0x7E);
				    	if(theApp.DocNum == 0)
		            		theApp.Sync(message1,3);
			     		//caohaitao
#ifdef _DEBUG
						strneterr.Format("%s ：以太网通讯错误:%d次",terror.Format("%Y-%m-%d,%H:%M:%S"),theApp.internet30s);
						theApp.m_DebugInfo.push_back(strneterr);
#endif //_DEBUG
//                        g_Log.StatusOut("以太网通讯错误111");
					}
					if(theApp.internet30s == 4 && theApp.m_FdsScan ==50)//先关闭，试着连接
					{
								 theApp.m_FdsScan =0;
                                 theApp.socketClient.Close();
           				theApp.internet30s=0;
					}
				}
				else if(theApp.internet30s >10 && theApp.DocNum != 7)
				{
			    		 unsigned char   Warn_state = m_SlaveStation[1][0].Channel_state;
				       	    if(Warn_state != 0xa0)
							{
//    	                 socketClient.AddWarn( "以太网通讯错误", strCTime, "", "", "", "", "", "");
								theApp.m_RTDM.NCError();
								 theApp.m_FdsScan =0;
                        		if(theApp.socketClient.IsConnected())
                                      theApp.socketClient.Close();
							}
					theApp.internet30s = 0;
				}

            	CMDIFrameWnd *pFrame = (CMDIFrameWnd*)AfxGetApp()->m_pMainWnd;
              	CMDIChildWnd *pChild = (CMDIChildWnd *) pFrame->GetActiveFrame();
               	CSampleFormView *pFView = (CSampleFormView*)pChild->GetActiveView();
    			if(pFView->IsKindOf(RUNTIME_CLASS(CSampleFormView)) && pFView != NULL)
				{
				  	pFView->DisList123();
				}

				//caohaitao
				CString strclm;
#ifdef _DEBUG
				QueryPerformanceCounter(&liCount2);
//				t2 = timeGetTime();
				double f_ms= (double)(liCount2.QuadPart-liCount1.QuadPart)*1000/(double)liFrequency.QuadPart;
				if(f_ms >300)
				{
    				strclm.Format("ABF:%.3f ms",f_ms);
					theApp.m_DebugInfo.push_back(terror.Format("%Y-%m-%d,%H:%M:%S    ")+strclm );
//                    g_Log.StatusOut(strclm);
				}
#endif //_DEBUG
			}
     		break;
//      	default:
//    		break;
	}
	CMDIFrameWnd::OnTimer(nIDEvent);
//	return 0;
}

//窗口置顶代码
void CMainFrame::OnTopWindow() 
{
//	::SetWindowPos(AfxGetMainWnd()->m_hWnd,HWND_TOPMOST,
//    -1,-1,-1,-1,SWP_NOMOVE/SWP_NOSIZE);
   int i= SetWindowPos(&CWnd::wndTopMost,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE);
//   if (i==0)
//    return false;
//   else
//    return true;
}
//取消窗口置顶
/*
bool SetWindowTop(CWnd* pWnd)
{
if(!pWnd)
{
   return false;
}
if(pWnd->GetExStyle()&WS_EX_TOPMOST)
{
   return true;
}
else
{
   int i= pWnd->SetWindowPos(&CWnd::wndTopMost,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE);
   if (i==0)
    return false;
   else
    return true;

}
}
CancelWindowTop(CWnd* pWnd)
{
if(pWnd)
{
   int x=pWnd->SetWindowPos(&CWnd::wndNoTopMost,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE);
   if(x==0)
    return false;
   else
    return true;
}
else
{
   return false;
}
}*/

/*
//时间点１(例如按某个button的时间)
QueryPerformanceCounter(&liCount1);
//你的其他代码...
//时间点２(例如某事件完成的时间)
QueryPerformanceCounter(&liCount2);
fSeconds=(double)(liCount2.QuadPart -liCount1.QuadPart )/(double)liFrequency.QuadPart; //时间点２和时间点１之间的精确秒数
*/

// The thread message handler (WM_MY_THREAD_MESSAGE)
// -- #define WM_MY_THREAD_MESSAGE	WM_APP+100
// -- ON_MESSAGE(WM_MY_THREAD_MESSAGE, OnThreadMessage)
LRESULT CMainFrame::OnThreadMessage(WPARAM wParam, LPARAM)
{
//	int nProgress= (int)wParam;
//    CMainFrame* pFWnd=(CMainFrame*)AfxGetMainWnd();
    CTime terror = CTime::GetCurrentTime();
#ifdef _DEBUG
LARGE_INTEGER liCount1,liCount2,ui1,ui2;
LARGE_INTEGER liFrequency;
QueryPerformanceFrequency(&liFrequency);//每秒记数
#endif //_DEBUG

			     		//caohaitao
             	CString strt1,strt2,strt3 ; double f_ms;
#ifdef _DEBUG
				QueryPerformanceCounter(&ui1);
#endif //_DEBUG
//				t1 = timeGetTime();
//    CMainFrame* pFWnd=(CMainFrame*)AfxGetMainWnd();

            	CTime t = CTime::GetCurrentTime();
				int m_cnum =t.GetTime()%3600;
				if( (m_cnum==3599) || (m_cnum==1))//A D 量整点存数据
				{
                 		for(int i = 1; i < MAX_FDS;i++ )
                			for(int j = 1; j < MAX_CHAN;j++ )
              					m_SlaveStation[i][j].AlarmState =0;
	COleDateTime timetemp(t.GetYear(),t.GetMonth(),t.GetDay(),t.GetHour(),t.GetMinute(),t.GetSecond());
                 		for( i = 1; i < MAX_FDS;i++ )
						{
                			for(int j = 0; j < MAX_CHAN;j++ )
							{
	        					if(m_SlaveStation[i][j].WatchName != "")
								{
									theApp.m_RTDM.SaveRT24Data(i,j,24);
									m_SlaveStation[i][j].ValueTime =timetemp;
    	     						theApp.m_RTDM.SyncCRTData(i,j,0); 
								}//(m_SlaveStation[i][j].WatchName != "")
							}
						}
//						m_bIsDraw =TRUE;
				}//if( (m_cnum==3599) ||  (m_cnum==0) ||  (m_cnum==1))
	CString strrsy,strclm ;
				int hhh = m_Str2Data.String2Int(theApp.m_strms[15].strl);//主备切换时间
				theApp.master30++;//备
				theApp.slave30++;//主
				if(n_CPort == 111 || n_CPort == 0)
				{
    				theApp.master30 = 0;
	    			theApp.slave30 = 0;
				}
				if(theApp.master30>(hhh-2) && n_CPort == 999 && theApp.master30<(hhh+1)) //备机
				{
       	            CNDKMessage message1(MASTERSLAVER);
					message1.Add(555);//心跳
//		    		theApp.SendMessage(message1);
		    		theApp.Sync(message1,2);
				}
				if(theApp.master30 > (hhh+5) && n_CPort == 999)
				{
//					theApp.master30 =0;
					n_CPort =111;//主机标示
		    		theApp.sCb.Close();
                  	theApp.b_SaveRT = TRUE;//备机存数据
//            		AfxMessageBox("关备机客户端!");
				}
				//主机联系备机，确认是否存在
				if(theApp.slave30>(hhh-2) && n_CPort == 888 && theApp.slave30<(hhh+1)) 
				{
       	            CNDKMessage message(MASTERSLAVER);
					message.Add(222);//心跳
		    		theApp.sCb.SendMessage(message);
//		    		theApp.Sync(message1,2);
				}
				if(theApp.slave30 >(hhh+5)  && n_CPort == 888)//(hhh+1)
				{
//					strclm.Format("%d  ",theApp.slave30);
					theApp.slave30 = 0;
					n_CPort =111;//主机标示
		    		theApp.sCb.Close();
//            		AfxMessageBox(strclm+"关主机客户端!");
				}

				m_m300++;
				if(m_m300 == 300)
				{
    				theApp.b_5m =false;
					m_m300 =0;
						theApp.m_RDCHm5.clear();
    				theApp.b_5m =true;
				}

		if(t.GetHour() == 23 && t.GetMinute() == 59 && t.GetSecond()>57)
		{//取消标校，24小时最大、最小初始化 建日志
    		theApp.b_5m =false;
    		theApp.db3m.execDML("delete from rtdata;");
    		theApp.b_5m =true;
			CTimeSpan t1day(1,0,0,0);
			terror += t1day;
        	strclm = terror.Format(_T("%Y%m%d")); 
            g_Log.Init("\\log\\操作日志"+strclm+".ini");
            g_Log1.Init("\\log\\中心站运行日志"+strclm+".txt");
            g_Log.StatusOut(strclm+"操作日志记录：");
            g_Log1.StatusOut("系统继续运行！");

            for(int i = 1; i < MAX_FDS;i++)
			{
                for(int j = 0; j < MAX_CHAN;j++)
				{
                	m_SlaveStation[i][j].Adjust_state =0;
                	m_SlaveStation[i][j].strPN = m_SlaveStation[i][j].strPN.Mid(0,5);
					m_SlaveStation[i][j].m24_T = 0;
					m_SlaveStation[i][j].m24_AMaxValue = 0;
					m_SlaveStation[i][j].m24_AMinValue = 666666;
					m_SlaveStation[i][j].m24_Atotal =0;
					m_SlaveStation[i][j].m24_ATotalValue =0;
				}
			}
        	theApp.m_RTDM.InitDisplay();
		}

	if(theApp.m_senddata)
	{
//		BlockInput(TRUE);     //屏蔽键盘和鼠标
		OnWSYSTEM();
		theApp.m_senddata =false;
//		BlockInput(FALSE);   //解除屏蔽
	}
				if(paneResourceView->IsSelected() || theApp.idis ==1)
				{
					m_wndResourceView.InitFBA(1);
//                    paneResourceView->Select();
					theApp.idis =0;
				}
				else if(paneResourceView2->IsSelected()|| theApp.idis ==2)
				{
					m_wndResourceView2.InitFBA(2);
//                    paneResourceView2->Select();
					theApp.idis =0;
				}
				else if(paneResourceView3->IsSelected()|| theApp.idis ==3)
				{
					m_wndResourceView3.InitFBA(3);
//                    paneResourceView3->Select();
					theApp.idis =0;
				}
				else if(paneResourceView4->IsSelected()|| theApp.idis ==4)
				{
					m_wndResourceView4.InitFBA(4);
//                    paneResourceView4->Select();
					theApp.idis =0;
				}
				else if(paneResourceView5->IsSelected()|| theApp.idis ==5)
				{
					m_wndResourceView5.InitFBA(5);
//                    paneResourceView5->Select();
					theApp.idis =0;
				}
#ifdef _DEBUG
				QueryPerformanceCounter(&ui2);
				f_ms= (double)(ui2.QuadPart-ui1.QuadPart)*1000/(double)liFrequency.QuadPart;
				strt2.Format(":   %.3f ms",f_ms);
#endif //_DEBUG


//		SetEvent(m_ThreadParam.hTimerEvent);
            	AddEdit();
				if(theApp.fidis == 0 && theApp.b_SaveRT)//save db data
				{
					theApp.fidis =1;
					theApp.bidis =0;
                 	for(int i=1; i<6000 ;i++)
					{
						if(strRTData1[i] =="")
							break;
						//caohaitao
#ifdef _DEBUG
#else
                    	theApp.m_pConnection->Execute(_bstr_t(strRTData1[i]),NULL,adCmdText);
#endif //_DEBUG
						strRTData1[i] ="";
					}
					strt1.Format("num:%d   ",i);
				}
				else if(theApp.fidis == 1 && theApp.b_SaveRT)
				{
					theApp.fidis =0;
					theApp.bidis =0;
                 	for(int i=1; i<6000 ;i++)
					{
						if(strRTData2[i] =="")
							break;
						//caohaitao
#ifdef _DEBUG
#else
                     	theApp.m_pConnection->Execute(_bstr_t(strRTData2[i]),NULL,adCmdText);
#endif //_DEBUG
						strRTData2[i] ="";
					}
					strt1.Format("num:%d   ",i);
				}
#ifdef _DEBUG
				QueryPerformanceCounter(&ui2);
				f_ms= (double)(ui2.QuadPart-ui1.QuadPart)*1000/(double)liFrequency.QuadPart;
				strt3.Format(":   %.3f ms",f_ms);
#endif //_DEBUG
				if(n_timer60>0 && theApp.m_FdsScan ==50)//校时
				{
                	unsigned char nfds ; CString strPointNo;
                 	unsigned char* m_ndkSendt = new  unsigned char[11];
//					for(int i = 1; i<61 ;i++)//过滤没定义分站
					{
						if(n_timer60 == 1)
		    				m_pSetTimeDlg->m_listC.DeleteAllItems();
						if(m_SerialF[n_timer60].SFSd !=0)
						{
        		            m_ndkSendt[0] = 0x7E;
           		            m_ndkSendt[1] = n_timer60;
         		            m_ndkSendt[2] = 0x54;
                          	CTime t=CTime::GetCurrentTime();
         					strPointNo.Format("%d",t.GetYear()-2000);
        					nfds = m_Str2Data.Str2HEX(strPointNo);
        		            m_ndkSendt[3] = nfds;
        					strPointNo.Format("%d",t.GetMonth());
        					nfds = m_Str2Data.Str2HEX(strPointNo);
        		            m_ndkSendt[4] = nfds;
         					strPointNo.Format("%d",t.GetDay());
        					nfds = m_Str2Data.Str2HEX(strPointNo);
          		            m_ndkSendt[5] = nfds;
         					strPointNo.Format("%d",t.GetDayOfWeek()-1);
        					nfds = m_Str2Data.Str2HEX(strPointNo);
           		            m_ndkSendt[6] = nfds;
          					strPointNo.Format("%d",t.GetHour());
        					nfds = m_Str2Data.Str2HEX(strPointNo);
	        	            m_ndkSendt[7] = nfds;
		        			strPointNo.Format("%d",t.GetMinute());
		        			nfds = m_Str2Data.Str2HEX(strPointNo);
		                    m_ndkSendt[8] = nfds;
         					strPointNo.Format("%d",t.GetSecond());
           					nfds = m_Str2Data.Str2HEX(strPointNo);
	         	            m_ndkSendt[9] = nfds;
	           	            m_ndkSendt[10] = 0x21;
                          	CNDKMessage message1(VERIFYTIMER);
	          				message1.Add(m_ndkSendt , 200);
         					if(theApp.DocNum == 0)
		             			theApp.Sync(message1,1);
         					strPointNo.Format("%d号分站，校时完成。",n_timer60);
                            g_Log.StatusOut(strPointNo);
						}
					}
					n_timer60++;
					if(n_timer60 ==61)
					{
						n_timer60 =0;
					}
                	delete m_ndkSendt;
				}
				if(n_derr60>0 && theApp.m_FdsScan ==50)
				{
                	CString strPointNo;
                 	unsigned char* m_ndkSendt = new  unsigned char[11];
//					for(int i = 1; i<61 ;i++)//过滤没定义分站
					{
						if(n_derr60 == 1)
		    				m_pSetTimeDlg->m_listC.DeleteAllItems();
						if(m_SerialF[n_derr60].SFSd !=0)
						{
          				    m_ndkSendt[0] = 0x7E;
         		            m_ndkSendt[1] = n_derr60;
        		            m_ndkSendt[2] = 0x5A;
        		            m_ndkSendt[3] = 0x00;
          		            m_ndkSendt[4] = 0x21;
                        	CNDKMessage message1(FAULTATRESIA);
          					message1.Add(m_ndkSendt , 200);
	        				if(theApp.DocNum == 0)
        	    				theApp.Sync(message1,1);
							theApp.n_temp =0;
         					strPointNo.Format("%d号分站故障闭锁初始化,设为：关闭。",n_derr60);
                            g_Log.StatusOut(strPointNo);
						}
					}
					n_derr60++;
					if(n_derr60 ==61)
					{
						n_derr60 =0;
                		if(m_pSetTimeDlg != NULL)
            	             m_pSetTimeDlg->Init5A();
					}
                	delete m_ndkSendt;
				}

			     		//caohaitao
#ifdef _DEBUG
				QueryPerformanceCounter(&ui2);
//				t2 = timeGetTime();
				f_ms= (double)(ui2.QuadPart-ui1.QuadPart)*1000/(double)liFrequency.QuadPart;
				if(f_ms >30)
				{
			    	strclm.Format("UI: %.3f ms",f_ms);
					theApp.m_DebugInfo.push_back(terror.Format("%Y-%m-%d,%H:%M:%S    ")+strt1+strt2+strt3);
//                    g_Log.StatusOut(strclm);
				}
#endif //_DEBUG

	return 1;
}

void CMainFrame::StartTimer()
{
    	SetTimer(ABFREFRESH,1011,NULL);
//    	SetTimer(UIREFRESH,1031,NULL);
    	SetTimer(CALRTDATA,20,NULL);
    	// Start off the thread UIREFRESH
//    	AfxBeginThread(RTDATAThread, this);

    	m_ThreadParam.hWnd = GetSafeHwnd();
     	m_ThreadParam.nTime = 0;
    	TIMECAPS tc;
    	//获得定时器分辨率
    	if (timeGetDevCaps(&tc, sizeof(TIMECAPS)) != TIMERR_NOERROR) 
		{
     		return ;
		}
    	UINT nResolution = min(max(tc.wPeriodMin, 1), tc.wPeriodMax);
    	UINT nInterval = 1000;
	    if (nInterval < nResolution)
		{
	    	nInterval = nResolution;
		}
    	//设置定时最小分辨率
	    timeBeginPeriod(nResolution);
     	//设置定时器
    	m_nTimerID = timeSetEvent(nInterval, nResolution, 
     		(LPTIMECALLBACK)m_ThreadParam.hTimerEvent, 
     		(DWORD)this, TIME_PERIODIC | TIME_CALLBACK_EVENT_SET);
      	//创建定时线程
       	m_pTimerThread = (CTimerThread*)AfxBeginThread(RUNTIME_CLASS(CTimerThread),
      		THREAD_PRIORITY_ABOVE_NORMAL, 0, CREATE_SUSPENDED);
       	m_pTimerThread->m_bAutoDelete = FALSE;
     	m_pTimerThread->m_pThreadParam = &m_ThreadParam;
      	m_pTimerThread->ResumeThread();
}

UINT RTDATAThread(void *pParam)
{
	theApp.InitRTData(); //读取当天数据
//	CExample1_Dlg* pThis= (CExample1_Dlg*)pParam;	

//	for (int nValue = pThis->StartFrom; nValue <= pThis->EndTo;  ++nValue)
//		this->SendMessage(WM_MY_THREAD_MESSAGE, nValue);
//    CMainFrame* pFWnd=(CMainFrame*)AfxGetMainWnd();
//	for(;;)
	{
//		if(WaitForSingleObject(eventWriteD, INFINITE) == WAIT_OBJECT_0)
		{
//    	WaitForSingleObject(eventWriteD.m_hObject,INFINITE);
//            CMainFrame* pFWnd=(CMainFrame*)pParam;
//    		if(!theApp.socketClient.m_nodialog && theApp.b_startc)
			{
//			theApp.b_startc =FALSE;
//			pFWnd->SendMessage(WM_RTDATA_THREAD_MESSAGE, 1);
			}
		}

	}

	return 0;
}

int CMainFrame::FindItem(LPARAM lP)
{
	LVFINDINFO inf = {LVFI_PARAM,NULL,lP,{0,0},0};
//	return m_ListObjects.FindItem(&inf, -1);
	return 1;
}

void CMainFrame::UpdateThreadList()
{
	size_t m = m_ThreadPool.GetMaxThreadCount();
	CString s,s1;
	for (size_t n = 0; n < m; n++)
	{
//		DWORD dw = m_ListThreads.GetItemData(n);
		int threadID = (int)m_ThreadPool.GetThreadId(n);
		if (0 != threadID)
		{
//			if (0 == dw)
				s.Format(_T("%i"), threadID);
			s1 = (m_ThreadPool.GetThreadStatus(n)) ? _T("Working") : _T("Waiting");
		}
	}
}

LRESULT CMainFrame::OnObjectAdded(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& /*bHandled*/)
{
	return 0;
}

LRESULT CMainFrame::OnObjectStart(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/)
{
//	UpdateThreadList();
	return 0;
}

LRESULT CMainFrame::OnObjectProgress(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/)
{
//	int iItem = FindItem(lParam);
//	if (-1 == iItem)
//		return 0;
//	CString s;
//	s.Format(_T("%i of %i"), LOWORD(wParam), HIWORD(wParam));

	return 0;
}

LRESULT CMainFrame::OnObjectDone(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& /*bHandled*/)
{

	return 0;
}

LRESULT CMainFrame::OnObjectRemoved(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& /*bHandled*/)
{
	return 0;
}

//LRESULT CMainFrame::OnAddObject(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
//{
//	m_ThreadPool.Add(new CThreadObject(*this, 5 + (rand()%60)));
//	return 0;
//}

LRESULT CMainFrame::OnEmptyQueue(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	m_ThreadPool.EmptyQueue();
	return 0;
}

void CMainFrame::OnDebugInfo() //debug info
{
	CDCH5m dlg;
	dlg.n_select =5;
	dlg.DoModal();
}

void CMainFrame::OnTest() //test
{
	theApp.db3m.execDML("Drop TABLE rtdatar");
}

void CMainFrame::OnTest1() //test
{

		CString  temp,dddd,sztime,strTable;
        theApp.db3m.execDML("create table rtdatar(RTfds smallint, RTchan smallint, LP1 char(20), LP2 char(20) );");

		strTable ="Select * From rt201012data";
    CString strDBLink = _T("Provider=SQLOLEDB.1;Persist Security Info=True;\
                          User ID=sa;Password=sunset;\
                          Data Source=") +strDBname+ _T(";Initial Catalog=BJygjl");
	try
	{
		theApp.pRS.CreateInstance(__uuidof(ADOCust::Recordset));
		theApp.pRS->Open(_bstr_t(strTable),_bstr_t(strDBLink), ADOCust::adOpenStatic ,ADOCust::adLockReadOnly , ADOCust::adCmdText );
	}
	catch(_com_error &e)
	{
		AfxMessageBox(e.ErrorMessage());
	}

		while ( !theApp.pRS->EndOfFile)
		{
				int afds = theApp.pRS->Fields->Item["fds"]->Value.lVal;
				int achan = theApp.pRS->Fields->Item["chan"]->Value.lVal;
				int cv = theApp.pRS->Fields->Item["CDValue"]->Value.lVal;
				float av = theApp.pRS->Fields->Item["AValue"]->Value.fltVal;
         	    int nptype = m_SlaveStation[afds][achan].ptype;
    			int nstatus = theApp.pRS->Fields->Item["ADStatus"]->Value.lVal;
				COleDateTime dt(theApp.pRS->Fields->Item["recdate"]->Value);
//    	   	 int dbp = mPoint[theApp.pRS->Fields->Item["PID"]->Value.lVal];
//             if(dbp != 6666)
			 {
	            if(nptype ==1 || nptype ==0)
                	dddd.Format("%.2f%s",av,m_SlaveStation[afds][achan].m_Unit);
         		else if(nptype ==2 )
            	  	  dddd.Format("%.0f%s",av,m_SlaveStation[afds][achan].m_Unit);
        		else 
				{
								if(cv ==0)
				        		  dddd= m_SlaveStation[afds][achan].ZeroState;
			            		else if(cv == 1)
					        	  dddd= m_SlaveStation[afds][achan].OneState;
				         	    else if(cv == 2)
				          		  dddd= m_SlaveStation[afds][achan].TwoState;
				}
        		if((nstatus == 0x40)||(nstatus == 0x50)||(nstatus == 0x80)||(nstatus == 0x70)||(nstatus == 0x90)|| (nstatus == 0xa0) || (nstatus == 0xa1))
          		      dddd= theApp.m_RTDM.strstatus(nstatus);
				sztime = dt.Format(_T("%Y-%m-%d %H:%M:%S"));

    			temp.Format("insert into rtdatar values(%d, %d, '%s','%s');",afds,achan,dddd,sztime);
    			theApp.db3m.execDML(temp);
			 }//dbp != 6666
			theApp.pRS->MoveNext();
		}


}
//使对话框的关闭按钮无效：在对话框的OnInitDialog中调用如下代码
// CMenu *mnu=this->GetSystemMenu(FALSE);
//    mnu->ModifyMenu(SC_CLOSE,MF_BYCOMMAND|MF_GRAYED);
// mnu->EnableMenuItem(SC_CLOSE,MF_BYCOMMAND|MF_GRAYED);  也可
//去掉系统菜单
void CMainFrame::OnDisasysmenu()
{
CMenu *menu;  
menu = GetSystemMenu(FALSE);  
menu->RemoveMenu(SC_MINIMIZE,MF_BYCOMMAND);  
menu->RemoveMenu(SC_MAXIMIZE,MF_BYCOMMAND);  
menu->RemoveMenu(SC_MOVE,MF_BYCOMMAND);  
menu->RemoveMenu(SC_SIZE,MF_BYCOMMAND);
//menu->RemoveMenu(SC_CLOSE,MF_BYCOMMAND);
menu->RemoveMenu(SC_RESTORE,MF_BYCOMMAND);
menu->RemoveMenu(0,MF_BYCOMMAND);
}
//使最小化按钮无效
void CMainFrame::OnDisableMinbox()
{
    //获得窗口风格
    LONG style = ::GetWindowLong(m_hWnd,GWL_STYLE);
    //设置新的风格
    style &=  ~(WS_MINIMIZEBOX);
    ::SetWindowLong(m_hWnd,GWL_STYLE,style);
    //重化窗口边框
    CRect rc;
    GetWindowRect(&rc);
    ::SetWindowPos(m_hWnd,HWND_NOTOPMOST,rc.left,rc.top,rc.Width(),rc.Height(),SWP_DRAWFRAME);
}
//使最大化按钮无效
void CMainFrame::OnDisableMaxbox()
{
	//动态的改变窗口的风格
	ModifyStyle(WS_MAXIMIZEBOX, 0);
    //获得窗口风格
//    LONG style = ::GetWindowLong(m_hWnd,GWL_STYLE);
    //设置新的风格
//    style &=  ~(WS_MAXIMIZEBOX);
//    ::SetWindowLong(m_hWnd,GWL_STYLE,style);
    //重化窗口边框
//    CRect rc;
//    GetWindowRect(&rc);
//    ::SetWindowPos(m_hWnd,HWND_NOTOPMOST,rc.left,rc.top,rc.Width(),rc.Height(),SWP_DRAWFRAME);
}
//使关闭按钮无效
void CMainFrame::OnDisableClose()
{
    //获得系统菜单
    CMenu *pMenu=GetSystemMenu(FALSE);
    //获得关闭按钮的ID
    int x=pMenu->GetMenuItemCount();
    UINT pID=pMenu->GetMenuItemID(x-1);
    //使关闭按钮无效
    pMenu->EnableMenuItem(pID, MF_DISABLED);
}
//使最小化按钮有效
void CMainFrame::OnAbleMinbox()
{
    //获得窗口风格
    LONG style = ::GetWindowLong(m_hWnd,GWL_STYLE);
    //设置新的风格
    style |= WS_MINIMIZEBOX;
    ::SetWindowLong(m_hWnd,GWL_STYLE,style);
    //重化窗口边框
    CRect rc;
    GetWindowRect(&rc);
    ::SetWindowPos(m_hWnd,HWND_NOTOPMOST,rc.left,rc.top,rc.Width(),rc.Height(),SWP_DRAWFRAME);    
}
//使最大化按钮有效
void CMainFrame::OnAbleMaxbox()
{
    //获得窗口风格
    LONG style = ::GetWindowLong(m_hWnd,GWL_STYLE);
    //设置新的风格
    style |= WS_MAXIMIZEBOX;
    ::SetWindowLong(m_hWnd,GWL_STYLE,style);
    //重化窗口边框
    CRect rc;
    GetWindowRect(&rc);
    ::SetWindowPos(m_hWnd,HWND_NOTOPMOST,rc.left,rc.top,rc.Width(),rc.Height(),SWP_DRAWFRAME);
}
//使关闭按钮有效
void CMainFrame::OnAbleClose()
{
    //获得系统菜单
    CMenu *pMenu=GetSystemMenu(FALSE);
    //获得关闭按钮的ID
    int x=pMenu->GetMenuItemCount();
    UINT pID=pMenu->GetMenuItemID(x-1);
    //使关闭按钮有效
    pMenu->EnableMenuItem(pID, MF_ENABLED);
}