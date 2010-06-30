// KJ86Monitor.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "KJMonitor.h"

#include "MainFrm.h"
#include "KJMonitorDoc.h"
#include "KJMonitorView.h"


//以下两行是添加的代码
#include "MQServer.h"
#include "MQClient.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


//define global variable
CString gstrUser,gstrAuth;
volatile unsigned long  gunTimerCount,gunTimerCountOld; //for timer set
volatile UINT gunScantimeDelay,gunRepeaScantTimes,gunDataKeeptime;
CString gstrDispInfo;
//BOOL gbStartScan;

//双机热备参数全局变量
CString gstrIP,gstrPort,gstrTimeOut;
int nCom1,nCom2,nCom3,nCom4,nCom5,nCom6,nCom7,nCom8;
BOOL bIsConnect = FALSE;		//检测备机是否联机

CMQServer  SocketServer;
CMQClient socketClient;
BOOL bIsClient = FALSE;
/////////////////////////////////////////////////////////////////////////////
// CKJ86MonitorApp

BEGIN_MESSAGE_MAP(CKJMonitorApp, CWinApp)
	//{{AFX_MSG_MAP(CKJ86MonitorApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// Standard print setup command
//	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CKJ86MonitorApp construction

CKJMonitorApp::CKJMonitorApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
	m_bCancel=FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CKJ86MonitorApp object

CKJMonitorApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CKJ86MonitorApp initialization

BOOL CKJMonitorApp::InitInstance()
{
	// CG: The following block was added by the Splash Screen component.

	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#if _MSC_VER <= 1200 // MFC 6.0 or earlier
#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif
#endif // MFC 6.0 or earlier

	// Change the registry key under which our settings are stored.
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization.
// 	SetRegistryKey(_T("Xtreme Toolkit AppWizard-Generated Applications"));

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CKJMonitorDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CKJMonitorView));
	AddDocTemplate(pDocTemplate);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// The one and only window has been initialized, so show and update it.
	//在win98下改变字体
	LOGFONT lf;
	xtAfxData.font.GetLogFont(&lf);
	lf.lfHeight = 12;
	strcpy(lf.lfFaceName,_T("宋体"));
	CFont font;
	font.CreateFontIndirect(&lf);
	xtAfxData.SetGlobalFont(&font);
			
	m_pMainWnd->ShowWindow(SW_SHOWMAXIMIZED);
	m_pMainWnd->UpdateWindow();

	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
		// No message handlers
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CKJMonitorApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CKJ86MonitorApp message handlers


BOOL CKJMonitorApp::PreTranslateMessage(MSG* pMsg)
{
	// CG: The following lines were added by the Splash Screen component.
	if (CSplashWnd::PreTranslateAppMessage(pMsg))
		return TRUE;

	return CWinApp::PreTranslateMessage(pMsg);
}

int CKJMonitorApp::ExitInstance() 
{
	// TODO: Add your specialized code here and/or call the base class

	return CWinApp::ExitInstance();
}

//本机作为主机启动网络监听
BOOL CKJMonitorApp::StartServer()
{

	if(SocketServer.Listenning())
	{
		bIsClient = FALSE;
		return TRUE;
	}
	return FALSE;
}

//本机作为备机启动网络监听
BOOL CKJMonitorApp::StartClient()
{
	if(socketClient.ConnectServer(gstrIP,lPort))
	{
		bIsClient = TRUE;
		bIsConnect = TRUE;
		return TRUE;
	}
	else
	{
		AfxMessageBox("没有找到主机，本机将作为主机启动!");
		ChangeClientToHost();
	}
	return FALSE;
}

//发送SQL语句
void CKJMonitorApp::OnSendSQL(CString strSql)
{
	SocketServer.SendSQL(strSql);
}

//发送数据包
void CKJMonitorApp::SendMessage(CNDKMessage& message)
{
	SocketServer.SendMessage(message);
}

//检查本机状态
void CKJMonitorApp::Checked()
{
	if(bIsClient)
	{
		socketClient.HostStateCheck();
	}
	
}

//将备机该为主机进行监控
BOOL CKJMonitorApp::ChangeClientToHost()
{
	if(bIsConnect && bIsClient)
		socketClient.Close();
	
	typedef int (__stdcall *RESETPORT)(int, char *, int);	
	HINSTANCE hinstLib;
	RESETPORT ResetPort;
	hinstLib = LoadLibrary("Nport"); 
	if (hinstLib == NULL)
		AfxMessageBox("未获得动态连接库地址");
	else
	{
		ResetPort = (RESETPORT) GetProcAddress(hinstLib, "sio_resetport"); 
		if(ResetPort == NULL)
		{
			AfxMessageBox("未获得函数地址");
		}
		else
		{
			int i1 = (ResetPort)(nCom1,"",0);
			int i2 = (ResetPort)(nCom2,"",0);
			int i3 = (ResetPort)(nCom3,"",0);
			int i4 = (ResetPort)(nCom4,"",0);
			int i5 = (ResetPort)(nCom5,"",0);
			int i6 = (ResetPort)(nCom6,"",0);
			int i7 = (ResetPort)(nCom7,"",0);
			int i8 = (ResetPort)(nCom8,"",0);

		}
	}

	StartServer();

	bIsConnect = FALSE;
	bIsClient = FALSE;
	return TRUE;
}

//向主机发送信息
void CKJMonitorApp::Sync(CNDKMessage& message)
{
	if(bIsClient)
	{
		socketClient.SendMessage(message);
	}

}
