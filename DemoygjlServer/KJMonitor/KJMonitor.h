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

//˫���ȱ�ȫ�ֲ���
extern CString gstrIP,gstrPort,gstrTimeOut;
extern int nCom1,nCom2,nCom3,nCom4,nCom5,nCom6,nCom7,nCom8;
extern BOOL bIsConnect;
//extern BOOL gbStartScan;   //to start scan or not:first in 

#define MAX_POINT_NUMBER     15001  //������  1-15000
#define MAX_TRUNK_NUMBER     8      //��������1-8
#define MAX_ADDR_NUMBER      128    //����ַ��0--127

#define MAX_MULTICONV_NUMBER 5      //�๦��ת������ת�������� 
#define MAX_POINT_ON_ADDR    19     //ͬһ��ַ�������� 8+4+5+2
#define MAX_CHANNEL_NUMBER   16     //ͬһ�����������ͨ����

#define MAX_12MODE_NUMBER    8     //12Mode Number
#define MAX_WARNCLASS_NUMBER 64    //����������� 64

#define MAX_CTRL_POINT_NUM   512  //Ⱥ�����ʱÿ���ܿ��Ƶ������� 128*8=1024


// Anolog/SWitch channel · ��� λ�� ���� 
//becare: all num >=1    
//ע��ǰ��M��ʾ�๦��ת����֧��
#define MS8IN_B38  	      1     //M0  
#define MS5OUT_B25  	  2     //M1
#define MA4IN             3     //M3
#define MP16IN            4     //M4
#define A1IN8BIT_CH4ICO  5      //CH4     
#define A1IN8BIT_A50     6
#define A8IN8BIT_MCA     7
#define A8IN8BIT_MC8     8
#define A1OUT8BIT_C35    9
#define P16IN            10     //pulse 16 channel
#define S8IN_B38  	     11     //M0
#define S8OUT_B48        12     //
#define S5OUT_B25  	     13     //M1
#define MULTICONV        14 
#define A4IN             15     //M3
#define S16IN           16


//��ӵĴ���
extern BOOL bIsClient;
/////////////////////////////////////////////////////////////////////////////
// CKJ86MonitorApp:
// See KJ86Monitor.cpp for the implementation of this class
//
#include "MonitorPointThread.h"

class CKJMonitorApp : public CWinApp
{
public:
	CMonitorPointThread* pMPT;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CKJMonitorApp();

//˫������Ҫ����ĺ���
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
