// Draw.h : main header file for the DRAW application
//

#if !defined(AFX_DRAW_H__55AA697D_A012_4BC9_9EBF_53421EDCF3B9__INCLUDED_)
#define AFX_DRAW_H__55AA697D_A012_4BC9_9EBF_53421EDCF3B9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CDrawApp:
// See Draw.cpp for the implementation of this class
//

class CDrawApp : public CWinApp
{
public:
	CDrawApp();

	CString GetAppPath();				//返回应用程序所在路径
	ULONG_PTR           gdiplusToken;
	
	UINT   m_nView;
	BOOL   ProcessShellCommand(CCommandLineInfo& rCmdInfo);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDrawApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
	COleTemplateServer m_server;
		// Server object for document creation
	//{{AFX_MSG(CDrawApp)
	afx_msg void OnAppAbout();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

extern CDrawApp theApp;
/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DRAW_H__55AA697D_A012_4BC9_9EBF_53421EDCF3B9__INCLUDED_)
