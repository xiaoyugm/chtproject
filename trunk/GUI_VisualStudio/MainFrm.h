// MainFrm.h : interface of the CMainFrame class
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


#if !defined(AFX_MAINFRM_H__57DF813D_6BDB_4AA1_A29E_0AAA116BC4D5__INCLUDED_)
#define AFX_MAINFRM_H__57DF813D_6BDB_4AA1_A29E_0AAA116BC4D5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "ClassViewPane.h"
#include "ResourceViewPane.h"
#include "SolutionExplorerPane.h"
#include "PropertiesPane.h"
#include "OutputPane.h"

#include "SampleFormView.h"
#include "TabbedViewView.h"
#include "SetTimeDlg.h"
#include "DCH5m.h"
#include "ChildFrm.h"
#include "MadeCertView.h"
#include "SettingHostDlg.h"
#include "TimerThread.h"	// Added by ClassView

#define WMX_OBJECT_ADDED		(WM_APP+1)
#define WMX_OBJECT_START		(WM_APP+2)
#define WMX_OBJECT_PROGRESS	(WM_APP+3)
#define WMX_OBJECT_DONE			(WM_APP+4)
#define WMX_OBJECT_REMOVED	(WM_APP+5)

class CThreadObject : public CThreadObjectBase
{
public:
	static LONG s_lNext;
	static LONG s_lCount;
	ULONG m_n;
	int		m_nRuns;
	HWND	m_hWndNotify;

	CThreadObject(HWND hWnd, int nRuns);

	// overrides CThreadObjectBase
	virtual void Run(CThreadPoolThreadCallback &pool);
	virtual void Done();
};

class CMainFrame : public CXTPMDIFrameWnd
{
	DECLARE_DYNAMIC(CMainFrame)
public:
	CMainFrame();

// Attributes
public:
//    CMenu *m_pMenu;
//	CChildFrame    *m_pMade;
	CXTPToolBar    m_wndToolBar;

	CXTPDockingPaneManager m_paneManager;
	CXTPTabClientWnd m_MTIClientWnd;

	CClassViewPane m_wndClassView;
	CSolutionExplorerPane m_wndSolutionExplorer;
	CPropertiesPane m_wndProperties;
	COutputPane m_wndOutput;

	CResourceViewPane       m_wndResourceView;
	CResourceViewPane       m_wndResourceView2;
	CResourceViewPane       m_wndResourceView3;
	CResourceViewPane       m_wndResourceView4;
	CResourceViewPane       m_wndResourceView5;
//	CResourceViewPane       m_wndResourceView6;
//	CXTPDockingPane* paneResourceView6;
	CXTPDockingPane* paneResourceView5;
	CXTPDockingPane* paneResourceView4;
	CXTPDockingPane* paneResourceView3;
	CXTPDockingPane* paneResourceView2;
	CXTPDockingPane* paneResourceView;

	CXTPCommandBars* pCommandBars;
//	CXTPMenuBar* pMenuBar;

	CMadeCertView*           m_MadeCert;
	CSampleFormView*		m_pSampleFormView;
	CTabbedViewView*        m_pTabbedViewView;
	CSetTimeDlg*	 	m_pSetTimeDlg;
	CSettingHostDlg*		m_pSetHostDlg;
	CDCH5m*              m_pDCH5m;

	CommonTools C_Ts;
    void ModifySystem();
	void addEqupmentManagerMenuItem();
	void addCopyDataMenuItem();
	void setEnableItem();

	void OnDisableMinbox();
	void OnDisableMaxbox();
	void OnDisableClose();
	void OnAbleMinbox();
	void OnAbleMaxbox();
	void OnAbleClose();
	void OnDisasysmenu();

	void OnMView(int menun,int myf);
	void AddMessage(CString strMessage);
	void AddUser();
	void AddEdit();
	void AddLogo();
	void AddAnimation();
	void AddButton(int nIcon, int nID);
	void AddSwitchButtons();
	void AddZoomButton();
	void AddZoomSlider();
	void AddProgress();
	void TestProgress();
	CString m_strMessage;
	CEdit         m_wndEditCtrl;
	CAnimateCtrl  m_wndAnimCtrl;
	CProgressCtrl m_wndProgCtrl;
	BOOL m_bPlayAnimation;
	BOOL          m_RepeatFlag;
    void         DoPlayWarnSound(CString strFileName);
	UINT m_nPaneID;
	CString2DataType    m_Str2Data;
	int  m_m300,n_m60,n_timer60,n_derr60;
	BOOL  m_bIsDraw;

	POSITION	s_ViewPos;
	POSITION	m_ViewPos;

	void StartTimer();
//	afx_msg LRESULT On1000ThreadMessage(WPARAM wParam, LPARAM lParam);

	UINT m_nTimerID;
	CTimerThread* m_pTimerThread;
	THREAD_PARAM m_ThreadParam;
	LRESULT OnThreadMessage(WPARAM, LPARAM);

	CThreadPool		m_ThreadPool;
	int FindItem(LPARAM lP);
	void UpdateThreadList();
	LRESULT OnObjectAdded(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& /*bHandled*/);
	LRESULT OnObjectStart(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/);
	LRESULT OnObjectProgress(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/);
	LRESULT OnObjectDone(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& /*bHandled*/);
	LRESULT OnObjectRemoved(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& /*bHandled*/);
	LRESULT OnEmptyQueue(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);

// Operations
public:
///	void RemoveLogo();
	void CreateP(CString str1,char *str2);
	void Msg(int iItem, CString str1,CString str2,CString str3,CString str4,CString str5);

protected:
	CImageList	m_imageList;
	CXTWindowPos      m_wndPosition;
	CDialogBar         m_wndBar;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	void OnSetPreviewMode(BOOL bPreview, CPrintPreviewState* pState);
	//}}AFX_VIRTUAL	
	CMenu* _GetDynaPopupMenu1();
//	CMenu* _GetDynaPopupMenu2();
//	MenuCommandSet* m_pMenuCommandSet;
	
	void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	void ShowDockingPanePopupMenu(CXTPDockingPane* pPopupPane, CPoint pt, LPRECT lprcExclude);

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	afx_msg void OnTopWindow();

	afx_msg void OnDisAAR();
	afx_msg void OnDisABR();
	afx_msg void OnDisAFER();
	afx_msg void OnDisDABR();
	afx_msg void OnDisDFER();
	afx_msg void OnDisDSC();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnOPTXT();
	afx_msg void OnWORKTXT();
	afx_msg void OnDebugInfo();
	afx_msg void OnTest();
	afx_msg void OnTest1();

	void OnWSYSTEM();
	void OnOpenR();
	void OnCloseR();

//	BOOL ShowWindowEx(int nCmdShow);
///	void SetMousePosText(CPoint Logpoint,CPoint Devpoint);

protected:  // control bar embedded members
	CXTPStatusBar  m_wndStatusBar;

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnWindowAutohideall();
	afx_msg void OnWindowMore();
	afx_msg void OnClose();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
//}}AFX_MSG
	afx_msg void Sqlite3init();
	afx_msg void Sqlite3define();
	afx_msg void OnManipulate();
	afx_msg void OnFileMenuItems(UINT nID) ;
	afx_msg LRESULT OnDockingPaneNotify(WPARAM wParam, LPARAM lParam);
	afx_msg void OnShowView(UINT nID);
	afx_msg void OnShowViewOther(UINT nID);
	afx_msg void OnViewOther();
	afx_msg void OnEmptyCommandRange(UINT);
	afx_msg int OnCreateControl(LPCREATECONTROLSTRUCT lpCreateControl);
	afx_msg void OnCustomize();
	afx_msg void OnUpdateViewOther(CCmdUI* pCmdUI);
	int m_nOtherView;

	afx_msg void OnEditState(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnUpdateEditState(CCmdUI* pCmdUI);

	afx_msg void OnSoundPath();
	afx_msg void OnUpdateOnSoundPath(CCmdUI* pCmdUI);
	afx_msg void OnEditPlatform(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnUpdateEditPlatform(CCmdUI* pCmdUI);
	afx_msg void OnFullScreen();
	afx_msg void OnUpdateFullScreen(CCmdUI* pCmdUI);
	afx_msg void OnTheme(UINT nID);
	afx_msg void OnUpdateTheme(CCmdUI* pCmdUI);
	afx_msg void OnSkinFramework(UINT nID);

	afx_msg void OnUpdateLog(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDis(CCmdUI* pCmdUI);
///	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnMadeMade();
	afx_msg void OnSoundStop();

//	afx_msg void OnWAERATION();
	afx_msg void OnWGAS();

	afx_msg void OnEDRAW();
	afx_msg void OnCDS();
	afx_msg void OnCDC();
	afx_msg void OnCASelect();
	afx_msg void OnCAALARM();
	afx_msg void OnCABREAK();
	afx_msg void OnCAFEED();
	afx_msg void OnCurveADP();

	afx_msg void OnALARMS();
	afx_msg void OnBREAKES();
	afx_msg void OnFEEDES();
	afx_msg void OnSELECTS();

	afx_msg void OnSDisA();
	afx_msg void OnSDisD();

	afx_msg void OnDRIVERE();
	
	afx_msg void OnRECAAD();
	afx_msg void OnRECABD();
	afx_msg void OnRECAFED();
	afx_msg void OnRECASR();
	afx_msg void OnRECDABD();
	afx_msg void OnRECDABB();
	afx_msg void OnRECDSCD();
	afx_msg void OnRECDFED();
	afx_msg void OnRECDRIVERE();

	afx_msg void OnEXCELA();
	afx_msg void OnEXCELAA();
	afx_msg void OnEXCELAB();
	afx_msg void OnEXCELAFE();
	afx_msg void OnEXCELASR();
	afx_msg void OnEXCELDA();
	afx_msg void OnEXCELDAB();
	afx_msg void OnEXCELDSCD();
	afx_msg void OnEXCELDFE();
	afx_msg void OnEXCELDRIVERE();

	afx_msg void OnFORMS();

	afx_msg void OnSAVEFD();
	afx_msg void OnFORMPROP();
	afx_msg void OnFansA();
	afx_msg void OnCLASSTIME();
	afx_msg void OnAdjustdis();
	afx_msg void OnLOGOUT();
	afx_msg void OnLOGIN();
	afx_msg void OnSafeMethod();
	afx_msg void OnFDSconfig();
	afx_msg void OnFAILUREA();
	afx_msg void OnWINDGASA();
	afx_msg void OnTESTC();
	afx_msg void OnFDSC();
	afx_msg void OnManualC();
	afx_msg void OnVerifyT();
	afx_msg void OnColorS();
	afx_msg void OnFeedE();
	afx_msg void OnControlT();
	afx_msg void OnPBrowser();
	afx_msg void OnLocation();
	afx_msg void OnDigital();
	afx_msg void OnAnalog();
	afx_msg void OnSimulation();
	afx_msg void OnGenus();
	afx_msg LRESULT OnTabbarMouseMsg(WPARAM wParam,LPARAM lParam);
	afx_msg void OnSelchangeTabInfo(NMHDR* pNMHDR, LRESULT* pResult);

	void ExchangeLayout(CXTPPropExchange* pPX, BOOL bSerializeControls = TRUE);
	
	CWnd* CreateToolBox();
	void ResetToolboxItems();

	BOOL m_bSoundPath;
	int m_nState;
	int m_nPlatform;
	CString m_strIniFileName;
	BOOL m_bFullScreen;
	CRect m_rcMainFrame;
	UINT m_nTheme;
	
	CXTPPropExchangeXMLNode* m_pFullScreenLayout;

	CXTPTaskPanelGroup* CreateToolboxGroup(UINT nID);
	CXTPOfficeBorder<CXTPTaskPanel> m_wndTaskPanel;


	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__57DF813D_6BDB_4AA1_A29E_0AAA116BC4D5__INCLUDED_)
