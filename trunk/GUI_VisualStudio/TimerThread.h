#if !defined(AFX_TIMERTHREAD_H__F62616BF_B20C_4276_8C71_0E5F1A2257F2__INCLUDED_)
#define AFX_TIMERTHREAD_H__F62616BF_B20C_4276_8C71_0E5F1A2257F2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TimerThread.h : header file
//

#define WM_THREADMSG WM_USER+1
#define WM_RTDATA_THREAD_MESSAGE	WM_APP+100

typedef struct THREAD_PARAM 
{
	HWND hWnd;
	int nTime;
	HANDLE hTimerEvent;
	HANDLE hExitEvent;
}_THREAD_PARAM;
/////////////////////////////////////////////////////////////////////////////
// CTimerThread thread

class CTimerThread : public CWinThread
{
	DECLARE_DYNCREATE(CTimerThread)
public:
	CTimerThread();           // protected constructor used by dynamic creation

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTimerThread)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	virtual int Run();
	//}}AFX_VIRTUAL

// Implementation
public:
	THREAD_PARAM* m_pThreadParam;
	virtual ~CTimerThread();

	// Generated message map functions
	//{{AFX_MSG(CTimerThread)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TIMERTHREAD_H__F62616BF_B20C_4276_8C71_0E5F1A2257F2__INCLUDED_)
