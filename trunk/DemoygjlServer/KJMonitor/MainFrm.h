// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__6E6D0E87_D09B_4351_B57A_82C72131EC47__INCLUDED_)
#define AFX_MAINFRM_H__6E6D0E87_D09B_4351_B57A_82C72131EC47__INCLUDED_


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "OutputBar.h"
#include "CommStatusFM.h"
#include "FMMonitorPoint.h"
#include "WarningWin.h"

class CMainFrame : public CXTFrameWnd
{
	
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:
	CCommStatusFM* m_pCommStatusFM;
//	CShixuDlg   *m_CShixuDlg;
	CFMMonitorPoint* m_pFMMonitorPoint;
	CWarningWin* m_pWarningWin;
//	CCommStatusFM* m_pCommStatusFM;
	COutputBar     m_wndOutputBar;
	void StartTimer(int nTime);
	void StopTimer();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	public:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
public:
//	int m_xpara1;
	void SetStartStopScan(void);
	BOOL m_bCloseAllSerialPort;
	void StopScan(void);
	void StartScan(void);
	void WarnCauseEdit(void);
	void PointEditSwitchIn(void);
	void PointEditAnologIn(void);
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	void InitTabCtrlBar();

	//COutputBar     m_wndOutputBar;
	CXTTabCtrlBar    m_wndWarningBar;
    CXTTabCtrlBar    m_wndWrkspBar;
	CImageList       m_imageList;
	CImageList       m_imageList1;
	CXTStatusBar     m_wndStatusBar;
	CXTLogoPane      m_wndLogoPane;
	CStatic          m_wndStaticCtrl;  //用于F1操作提示
	CXTToolBar       m_wndToolBar;
	bool             m_bDestroy;
	CImageList		 m_ilLargeIcons;
	CImageList		 m_ilSmallIcons;
	CXTOutBarCtrl	 m_wndOutlookBar;
	CXTSplitterWnd   m_wndSplitter1;

	BOOL m_bStartStopScan;

// Generated message map functions
protected:
	void AddLogoPane(void);
	void AddFxStaticText(void);
	UINT m_unOutlookbarFolderNo;  //用于存贮outlookbar的folder号
	BOOL InitializeOutlookBar();

	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnMepointSwitchinput();
	afx_msg void OnMepointAnaloginput();
	afx_msg void OnSysUserpassword();
	afx_msg void OnMepointAlarmreason();
	afx_msg void OnMepointLoadparadata();
	afx_msg void OnMenuCommEditparaments();
	afx_msg void OnSysTrunkvsport();
	afx_msg void OnMenuSysStartscan();
	afx_msg void OnMenuSysStopscan();
	afx_msg void OnMenuBitcmd();
	afx_msg void OnMepointCtrlSwitchoutput();
	afx_msg void OnMenuTableAnalog();
	afx_msg void OnAppExit();
	afx_msg void OnMepointCtrlAnalogoutput();
	afx_msg void OnMepointCtrlGasinspect();
	afx_msg void OnMenuSquenceCommonreg();
	afx_msg void OnMenuSquenceStart();
	afx_msg void OnMenuSquenceEnd();
	afx_msg void OnMenuSquenceEdit();
	afx_msg void OnMenuSquenceMonitor();
	afx_msg void OnMenuSquenceTrigPointedit();
	afx_msg void OnMenuSquenceTime();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnSyncSync();
	afx_msg void OnUpdateMenuSysStartscan(CCmdUI* pCmdUI);
	afx_msg void OnUpdateMenuSysStopscan(CCmdUI* pCmdUI);
	afx_msg void OnUpdateMenuSquenceStart(CCmdUI* pCmdUI);
	afx_msg void OnUpdateMenuSquenceEnd(CCmdUI* pCmdUI);
	//}}AFX_MSG
	afx_msg LRESULT OnOutbarNotify(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__6E6D0E87_D09B_4351_B57A_82C72131EC47__INCLUDED_)
