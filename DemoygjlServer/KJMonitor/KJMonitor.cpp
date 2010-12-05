// KJ86Monitor.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "KJMonitor.h"

#include "MainFrm.h"
#include "KJMonitorDoc.h"
#include "KJMonitorView.h"
#include "LoginDlg.h"
#include "Others\\Splash.h"
//#include "ComfirmDlg.h"
#include "SetPortVsTrunkDlg.h"

//������������ӵĴ���
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

//˫���ȱ�����ȫ�ֱ���
CString gstrIP,gstrPort,gstrTimeOut;
int nCom1,nCom2,nCom3,nCom4,nCom5,nCom6,nCom7,nCom8;
BOOL bIsConnect = FALSE;		//��ⱸ���Ƿ�����

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
	 m1000 = 0;
	 m1500 = 0;
	 m4095 = 0;
	 m8 = 0;
	 N8 =0;
	 N1 =0;
	 N2 =0;
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CKJ86MonitorApp object

CKJMonitorApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CKJ86MonitorApp initialization

BOOL CKJMonitorApp::InitInstance()
{
	// CG: The following block was added by the Splash Screen component.
/*
\
	{
\
		CCommandLineInfo cmdInfo;
\
		ParseCommandLine(cmdInfo);
\

\
		CSplashWnd::EnableSplashScreen(cmdInfo.m_bShowSplash);
\
	}*/
///	::CoInitialize(NULL);

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
	//��win98�¸ı�����
	LOGFONT lf;
	xtAfxData.font.GetLogFont(&lf);
	lf.lfHeight = 12;
	strcpy(lf.lfFaceName,_T("����"));
	CFont font;
	font.CreateFontIndirect(&lf);
	xtAfxData.SetGlobalFont(&font);
			
	m_pMainWnd->ShowWindow(SW_SHOWMAXIMIZED);
	m_pMainWnd->UpdateWindow();

	StartServer();

	//�޸Ĵ�������
    //login dlg
//	CLoginDlg dlg;
//	if(dlg.DoModal()==IDCANCEL) 
//	{
//		m_bCancel=TRUE;
//		return FALSE;
//	}

	//	CSetPortVsTrunkDlg setporttrunkdlg;
//	setporttrunkdlg.DoModal();
//	CKJ86MonitorApp* pApp=(CKJ86MonitorApp* )AfxGetApp();
//	CMainFrame* pFWnd=(CMainFrame*)AfxGetMainWnd();
//    this->pMPT=(CMonitorPointThread* );
//	CMonitorPointThread* pMPT = pApp->pMPT;
///	this->pMPT=(CMonitorPointThread* )AfxBeginThread(RUNTIME_CLASS(CMonitorPointThread));  //0201

		//ѡ���Ƿ�������ݲ�����
///	CMainFrame* pFWnd=(CMainFrame*)AfxGetMainWnd();
///	pFWnd->SetStartStopScan();
//11/16	CComfirmDlg  firmdlg;
//16	firmdlg.DoModal();
//	if(firmdlg.DoModal()==IDOK)
//		gbStartScan=TRUE;
//	else
//		gbStartScan=FALSE;
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
/*	if(!m_bCancel)
	{
		CLoginDlg dlg;
		dlg.m_bLogInOut=1;
		dlg.DoModal();
	}
*/	
	return CWinApp::ExitInstance();
}

//������Ϊ���������������
BOOL CKJMonitorApp::StartServer()
{
	
	this->pMPT=(CMonitorPointThread* )AfxBeginThread(RUNTIME_CLASS(CMonitorPointThread));

		//ѡ���Ƿ�������ݲ�����
	CMainFrame* pFWnd=(CMainFrame*)AfxGetMainWnd();
	pFWnd->SetStartStopScan();
	pFWnd->StopTimer();
	if(SocketServer.Listenning())
	{
		bIsClient = FALSE;
		return TRUE;
	}
	return FALSE;
}

//������Ϊ���������������
BOOL CKJMonitorApp::StartClient()
{
	this->pMPT=(CMonitorPointThread* )AfxBeginThread(RUNTIME_CLASS(CMonitorPointThread));

	long lPort = atol(gstrPort);
	//������ʱ��
	int i = atoi(gstrTimeOut);
	CMainFrame* pFWnd=(CMainFrame*)AfxGetMainWnd();
	pFWnd->StartTimer(i);

	if(socketClient.ConnectServer(gstrIP,lPort))
	{
		bIsClient = TRUE;
		bIsConnect = TRUE;
		return TRUE;
	}
	else
	{
		AfxMessageBox("û���ҵ���������������Ϊ��������!");
		ChangeClientToHost();
	}
	return FALSE;
}

//����SQL���
void CKJMonitorApp::OnSendSQL(CString strSql)
{
	SocketServer.SendSQL(strSql);
}

//�������ݰ�
void CKJMonitorApp::SendMessage(CNDKMessage& message)
{
	SocketServer.SendMessage(message);
}

//��鱾��״̬
void CKJMonitorApp::Checked()
{
	if(bIsClient)
	{
		socketClient.HostStateCheck();
	}
	
}

//��������Ϊ�������м��
BOOL CKJMonitorApp::ChangeClientToHost()
{
	if(bIsConnect && bIsClient)
		socketClient.Close();
	
	typedef int (__stdcall *RESETPORT)(int, char *, int);	
	HINSTANCE hinstLib;
	RESETPORT ResetPort;
	hinstLib = LoadLibrary("Nport"); 
	if (hinstLib == NULL)
		AfxMessageBox("δ��ö�̬���ӿ��ַ");
	else
	{
		ResetPort = (RESETPORT) GetProcAddress(hinstLib, "sio_resetport"); 
		if(ResetPort == NULL)
		{
			AfxMessageBox("δ��ú�����ַ");
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

//			CString lee;
//			lee.Format("%d,%d,%d,%d,%d,%d,%d,%d",i1,i2,i3,i4,i5,i6,i7,i8);
//			AfxMessageBox(lee);

			FreeLibrary(hinstLib);
		}
	}

	StartServer();

	bIsConnect = FALSE;
	bIsClient = FALSE;
	return TRUE;
}

//������������Ϣ
void CKJMonitorApp::Sync(CNDKMessage& message)
{
	if(bIsClient)
	{
		socketClient.SendMessage(message);
	}

}
