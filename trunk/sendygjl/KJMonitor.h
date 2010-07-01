// KJ86Monitor.h : main header file for the KJ86MONITOR application
//

#if !defined(AFX_KJMONITOR_H__F9D0FC72_C6C0_478F_B499_5CAEB3BB4190__INCLUDED_)
#define AFX_KJMONITOR_H__F9D0FC72_C6C0_478F_B499_5CAEB3BB4190__INCLUDED_


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols
#include "NDK\\NDKMessage.h"

extern CString gstrUser,gstrAuth;
extern CString gstrDispInfo;
extern volatile unsigned long  gunTimerCount,gunTimerCountOld;
extern volatile UINT gunScantimeDelay,gunRepeaScantTimes,gunDataKeeptime;

//双机热备全局参数
extern CString gstrIP,gstrPort,gstrTimeOut;
extern int nCom1,nCom2,nCom3,nCom4,nCom5,nCom6,nCom7,nCom8;
extern BOOL bIsConnect;
//extern BOOL gbStartScan;   //to start scan or not:first in 



class CKJMonitorApp : public CWinApp
{
public:
	CMonitorPointThread* pMPT;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CKJMonitorApp();

//双机联备要加入的函数
	BOOL StartServer();
	BOOL StartClient();
	void OnSendSQL(CString strSql);
	void SendMessage(CNDKMessage& message);     //211
	void Checked();
	BOOL ChangeClientToHost();

	void Sync(CNDKMessage& message);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CKJ86MonitorApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CKJ86MonitorApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
protected:
	BOOL m_bCancel;
};

extern CKJMonitorApp theApp;
/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_KJ86MONITOR_H__F9D0FC72_C6C0_478F_B499_5CAEB3BB4190__INCLUDED_)
