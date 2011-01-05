// TimerThread.cpp : implementation file
// Download by http://www.codefans.net

#include "stdafx.h"
//#include "GUI_VisualStudio.h"
#include "TimerThread.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTimerThread

IMPLEMENT_DYNCREATE(CTimerThread, CWinThread)

CTimerThread::CTimerThread()
{
	m_pThreadParam = NULL;
}

CTimerThread::~CTimerThread()
{
}

BOOL CTimerThread::InitInstance()
{
	// TODO:  perform and per-thread initialization here
	return TRUE;
}

int CTimerThread::ExitInstance()
{
	// TODO:  perform any per-thread cleanup here
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CTimerThread, CWinThread)
	//{{AFX_MSG_MAP(CTimerThread)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTimerThread message handlers

int CTimerThread::Run() 
{
	while (TRUE)
	{
//    CTime terror = CTime::GetCurrentTime();
//    CString sss = terror.Format("1: %Y-%m-%d,%H:%M:%S");	
//    g_Log.StatusOut(sss);
		//等待定时事件
		while (WAIT_TIMEOUT == 
			WaitForSingleObject(m_pThreadParam->hTimerEvent, 1000))
		{
			//等待退出事件
			if (WaitForSingleObject(m_pThreadParam->hExitEvent, 0) == WAIT_OBJECT_0)
			{
				::AfxEndThread(0);
			}
		}

//		m_pThreadParam->nTime += 1000;

		//向主线程窗口发送消息  WM_THREADMSG
		::PostMessage(m_pThreadParam->hWnd, WM_RTDATA_THREAD_MESSAGE, 0, 0);

		//复位定时事件
		ResetEvent(m_pThreadParam->hTimerEvent);
//		terror = CTime::GetCurrentTime();
//       sss = terror.Format("2: %Y-%m-%d,%H:%M:%S");	
//       g_Log.StatusOut(sss);
	}
}
