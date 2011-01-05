// GUI_VisualStudio.cpp : Defines the class behaviors for the application.
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
#include "ChildFrm.h"
#include "GUI_VisualStudioDoc.h"
#include "GUI_VisualStudioView.h"

#include "AboutDlg.h"

#include "DrawDoc.h"
#include "DrawView.h"

#include "math.h"
#include "FlatTabViewView.h"
#include "FlatTabViewDoc.h"
#include "TabbedViewView.h"
#include "ControlXml.h"

#include "SettingHostDlg.h"
#include "SetTimeDlg.h"
#include "LoginDlg.h"
//#include "Tlhelp32.h"
//#include "SplashWindow.h"
#include "GUI_OutlookView.h"
#include "SplashWnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

SerialF       m_ABFlist[MAX_FDS][MAX_CHAN]; //AD have ABF SFSd/aa cfds/ab cchan/af ffds/dab fchan/df
BYTE     m_ndkSend[MAX_FDS][44];//44BUFFER_SIZE
CommonStr             m_CommonStr[20];
SerialF               m_AFans[MAX_FDS][MAX_CHAN];    //双风门主扇备扇报警
ADMainDis             m_ADMainDis[MAX_FDS][MAX_CHAN];          //调用显示
//D状态改变//D馈电列表//D报警\断电列表//A馈电列表//A断电列表//A报警列表
ADCbreakE             m_CFeed[MAX_FDS][MAX_CHAN][65];    //馈电规则
SerialF               m_Colorref[200];
SerialF               m_SerialF[MAX_FDS];    //各分站连接的串口   班设置
ADCbreakE             m_ADCbreakE[MAX_FDS][MAX_CHAN][65];
DisplayDraw           m_DisplayDraw[MAX_POINT_NUMBER];//点号查分站、通道
SlaveStation             m_SlaveStation[MAX_FDS][MAX_CHAN];
CPointInfo m_CPointInfo[MAX_POINT_NUMBER];
extern CWarnPoint m_CWarnPoint[MAX_POINT_NUMBER];
CString gstrTimeOut,strMetrics,strSer,strCli,strDBname;
long n_SPort,n_CPort;
CSAStatusLog g_Log,g_Log1;
/////////////////////////////////////////////////////////////////////////////
// CGUI_VisualStudioApp
//CAppModule _Module;

BEGIN_MESSAGE_MAP(CGUI_VisualStudioApp, CWinApp)
	//{{AFX_MSG_MAP(CGUI_VisualStudioApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_COMMAND(ID_WINDOW_CLOSE_ALL, OnWindowCloseAll)
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_NEW_PROJECT, OnFileNew)

	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGUI_VisualStudioApp construction

CGUI_VisualStudioApp::CGUI_VisualStudioApp()
{
//	EnableManifestEditor();

	pDocTemplate = NULL ;
	pNewDocTemplate = NULL ;
	pRDocTemplate = NULL ;
	DocNum = idis = internet30s = master30 =slave30 =n_temp =0;
	m_senddata = false;
	m_message =0;
	b_5m = true;
	strargc ="";
	m_bLogIn = false;
	curuser ="请登陆";
	m_bsuper = false;
	b_SaveRT = FALSE;
	b_startc = TRUE;
#ifdef _DEBUG
	curuser ="cht";
	m_bLogIn = true;
	b_SaveRT = TRUE;
//	m_bsuper = true;
#endif //_DEBUG
	m_FdsScan = 0;
	m_resnum = 11;
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CGUI_VisualStudioApp object

CGUI_VisualStudioApp theApp;

// This identifier was generated to be statistically unique for your app.
// You may change it if you prefer to choose a specific identifier.

// {39E53923-BD3F-11D4-96C7-00A0C932550C}
static const CLSID clsid =
{ 0x39e53923, 0xbd3f, 0x11d4, { 0x96, 0xc7, 0x0, 0xa0, 0xc9, 0x32, 0x55, 0xc } };

/////////////////////////////////////////////////////////////////////////////
// CGUI_VisualStudioApp initialization

BOOL CGUI_VisualStudioApp::InitInstance()
{
	CString strmes;
	CTime t=CTime::GetCurrentTime();
	strmes = t.Format(_T("%Y%m%d")); 
       g_Log.Init("\\log\\操作日志"+strmes+".ini");
       g_Log.PrintTime(TRUE);
       g_Log1.Init("\\log\\中心站运行日志"+strmes+".txt");
       g_Log1.PrintTime(TRUE);
       g_Log.StatusOut("操作日志记录：");
       g_Log1.StatusOut("系统开始运行！");

	AfxEnableControlContainer();

	CXTPWinDwmWrapper().SetProcessDPIAware();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

//	AfxEnableControlContainer();
//	::CoInitialize(NULL);

//	AfxSockInit();

#if _MSC_VER <= 1200 // MFC 6.0 or earlier
#ifdef _AFXDLL
	Enable3dControls();         // Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();   // Call this when linking to MFC statically
#endif
#endif // MFC 6.0 or earlier

	// Change the registry key under which our settings are stored.
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization.
//	SetRegistryKey(_T("Codejock Software Sample Applications"));

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

/*	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(
		IDR_GUI_WHTYPE,
		RUNTIME_CLASS(CGUI_VisualStudioDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CGUI_VisualStudioView));
	AddDocTemplate(pDocTemplate);

	// create main MDI Frame window
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
		return FALSE;
	m_pMainWnd = pMainFrame;

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// The main window has been initialized, so show and update it.
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();*/

	strargc.Format("%s",__argv[0]);
//	strargc.Format("%s",__argv[1]);
//	strargc.Format("%s",__argv[2]);
//	strargc = "OnEXCELA";
	strmes = strargc.Mid(0,2);
//	if(strmes == "On")
	{
			pRDocTemplate = new CMultiDocTemplate(
				IDR_MAINFRAME,
//				IDR_MREPORT,
//				IDR_DRAWTYPE,
//				RUNTIME_CLASS(CDrawDoc),
				RUNTIME_CLASS(CRViewDoc),
				RUNTIME_CLASS(CChildFrame), // custom MDI child frame
				RUNTIME_CLASS(CMadeCertView));
        	AddDocTemplate(pRDocTemplate);
	}
//	else
	{
			pDocTemplate = new CMultiDocTemplate(
				IDR_MAINFRAME,
//				IDR_DRAWTYPE,
				RUNTIME_CLASS(CDrawDoc),
				RUNTIME_CLASS(CChildFrame), // custom MDI child frame
				RUNTIME_CLASS(CDrawView));
//	pDocTemplate->SetContainerInfo(IDR_DRAWTYPE_CNTR_IP);
///	pDocTemplate->SetServerInfo(
///		IDR_DRAWTYPE_SRVR_EMB, IDR_DRAWTYPE_SRVR_IP,
///		RUNTIME_CLASS(CInPlaceFrame));
        	AddDocTemplate(pDocTemplate);

	// Connect the COleTemplateServer to the document template.
	//  The COleTemplateServer creates new documents on behalf
	//  of requesting OLE containers by using information
	//  specified in the document template.
        	m_server.ConnectTemplate(clsid, pDocTemplate, FALSE);

	// Register all OLE server factories as running.  This enables the
	//  OLE libraries to create objects from other applications.
//        	COleTemplateServer::RegisterAll();
		// Note: MDI applications register all server objects without regard
		//  to the /Embedding or /Automation on the command line.

			pNewDocTemplate = new CMultiDocTemplate(
				IDR_MAINFRAME,
//				IDR_DRAWTYPE,
				RUNTIME_CLASS(CFlatTabViewDoc),
				RUNTIME_CLASS(CChildFrame), // custom MDI child frame   CFlatTabViewDoc
				RUNTIME_CLASS(CSampleFormView));   //CTabbedViewView
			AddDocTemplate(pNewDocTemplate);

	}

	strMetrics.Format("%d",GetSystemMetrics(SM_CXSCREEN));
	CString strrsy1,strclm1,strclm;
	gstrTimeOut = C_Ts.GetAppPath();
         strclm = gstrTimeOut+ ("\\DrawForms.db3");
		 strclm = m_Str2Data.MbcsToUtf8(strclm);
         db3.open(strclm);

	 strrsy1 ="dispoint"+strMetrics;
			strclm1.Format("select * from '%s' WHERE DISID>100 and DISID<103;",strrsy1);
		CppSQLite3Query q;
            q = db3.execQuery(strclm1);
			strclm1 ="";
            while (!q.eof())
			{
				int m_ishave = q.getIntField(0);
                strclm = q.getStringField(1);
	    		strclm.TrimRight();
				if(m_ishave == 101)
    				strDBname = strclm;
				else if(m_ishave == 102)
					strclm1 = strclm;
                q.nextRow();
			}
   		q.finalize();

			if(!InitUIInfo())
			{
				AfxMessageBox("没有找到合适的分辨率配置文件，请确认是否有当前屏幕分辨率的配置文件!");
				return FALSE;
			}
		for(int i = 0; i < MAX_FDS;i++ )
		{
			for(int j = 0; j < MAX_CHAN;j++ )
			{
					m_SlaveStation[i][j].Channel_state = 255;
					m_SlaveStation[i][j].AValue = 666666;
					m_SlaveStation[i][j].m5_T = 0;
					m_SlaveStation[i][j].m5_AMaxValue = 0;
					m_SlaveStation[i][j].m5_AMinValue = 666666;
					m_SlaveStation[i][j].m5_ATotalValue = 0;
					m_SlaveStation[i][j].m5_Atotal = 0;
					m_SlaveStation[i][j].pnValue = 0;
					m_SlaveStation[i][j].CValue = 6;
					m_SlaveStation[i][j].AlarmState = 0;
					m_SlaveStation[i][0].AValue = 0;
	                COleDateTime timetemp;//(2010,1,1,0,0,0);
					m_SlaveStation[i][j].ValueTime = timetemp.GetCurrentTime();
					m_SlaveStation[i][j].m24_T = 0;
					m_SlaveStation[i][j].m24_AMaxValue = 0;
					m_SlaveStation[i][j].m24_AMinValue = 666666;
					m_SlaveStation[i][j].m24_ATotalValue = 0;
					m_SlaveStation[i][j].m24_Atotal = 0;
					m_ABFlist[i][j].SFSd = 0;
					m_ABFlist[i][j].cfds = 0;
					m_ABFlist[i][j].cchan = 0;
					m_ABFlist[i][j].ffds = 0;
					m_ABFlist[i][j].fchan = 0;
			}
		}

	if(!InitData())
	{
		AfxMessageBox("初始化数据库失败！");
		return FALSE;
	}

	if(strclm1 == "")
        m_strms[3].strl = "1024";    //模拟图默认分辨率
	else 
        m_strms[3].strl = strclm1;    //模拟图默认分辨率

		for( i = 0; i < MAX_FDS;i++ )
			for(int j = 0; j < 44;j++ )
				m_ndkSend[i][j] = 255;
//		AfxMessageBox("步1");
	UINT idCursors[] = 
	{
		IDC_LOUPE, IDC_LOUPEPLUS, IDC_LOUPEMINUS, IDC_GRIPOPEN, IDC_GRIPCLOSED
	};
//	for (int i = 0; i < sizeof(idCursors) / sizeof(UINT); i++)
//		VERIFY(QZoomView::LoadCursor(i, idCursors[i]));

	// create main MDI Frame window
	CMainFrame* pMainFrame = new CMainFrame;
     	if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
       		return FALSE;
	m_pMainWnd = pMainFrame;

//    pMainMenu = m_pMainWnd->GetMenu();
//    ASSERT_VALID(pMainMenu);
//    CMenu* pHelpMenu = pMainMenu->GetSubMenu(pMainMenu->GetMenuItemCount() - 1);
//   ASSERT_VALID(pHelpMenu);
//    pHelpMenu->InsertMenu(0, MF_STRING | MF_BYPOSITION, 40100, _T("Test"));

	// Enable drag/drop open 
	m_pMainWnd->DragAcceptFiles();

	// Enable DDE Execute open
//	EnableShellOpen();
//	RegisterShellFileTypes(TRUE);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	//MDI启动时不建立一个新的文件
//    CommandLineInfo cmdInfo;
//	if(cmdInfo.m_nShellCommand == CCommandLineInfo::FileNew){
//		cmdInfo.m_nShellCommand = CCommandLineInfo::FileNothing;
//	}
//	ParseCommandLine(cmdInfo);


	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// Check to see if launched as OLE server
	if (cmdInfo.m_bRunEmbedded || cmdInfo.m_bRunAutomated)
	{
		// Application was run with /Embedding or /Automation.  Don't show the
		//  main window in this case.
		return TRUE;
	}

	// When a server application is launched stand-alone, it is a good idea
	//  to update the system registry in case it has been damaged.
	if(strmes != "On")  //0x39e53923 改为0x39e53924 0x39e53925 报错
	{
	m_server.UpdateRegistry(OAT_INPLACE_SERVER);
	COleObjectFactory::UpdateRegistryAll();
	}
	// The main window has been initialized, so show and update it.
	//SW_SHOWMAXIMIZED              SW_SHOWNORMAL
//	pMainFrame->ShowWindow(m_nCmdShow);
	if(strmes == "On")
    	pMainFrame->ShowWindow(SW_NORMAL);
	else
    	pMainFrame->ShowWindow(SW_SHOWMAXIMIZED);
	pMainFrame->UpdateWindow();

	// Initialize GDI+.   
	GdiplusStartupInput gdiplusStartupInput;
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

//    InitRTData(); //读取当天数据
#ifdef _DEBUG
#else
	if(strmes != "On")
	{
		int n_process = C_Ts.FindProcess("RSDRAW-YRun.EXE");
		if(n_process == 2)
		{
    		AfxMessageBox("应用程序已打开！");
    		return FALSE;
		}
	CSplashWnd::EnableSplashScreen(cmdInfo.m_bShowSplash);
	// Create and show the splash screen.
	CSplashWnd::ShowSplashScreen(500, IDB_CLASSTREE, m_pMainWnd);
	Sleep(4000);
	}
#endif //_DEBUG

//    CMainFrame* pFWnd=(CMainFrame*)AfxGetMainWnd();
//    	CSplashWindow SplashW;
//        CSplashWindow::ShowSplashScreen( NULL, "Starting application...");
//    	CSplashWindow::ShowSplashScreen( NULL, "Initializing hardware...");
//       	CSplashWindow::ShowSplashScreen( NULL, "Initializing database...");
    	// display final splash screen and have it turn off after 3 seconds (3000 milliseconds)
 //    	CSplashWindow::ShowSplashScreen( pFWnd, "http://www.xxx.com/", 3000);
//	Sleep ( 2000 );

//		AfxMessageBox("步2");
//		AfxMessageBox("步3");

	if(strmes == "On")
	{
//		pDocTemplate->OpenDocumentFile(NULL) ;
	}
	else
	{
    		DocNum = 1;
			InitSQLite3();
			C_Ts.GetPCNameIP();
       g_Log1.StatusOut("系统初始化完成！");
//   g_statusLog.PrintAppName(TRUE);
	}
#ifdef _DEBUG
	   CString stros[35];
	   for( i=0 ;i<C_Ts.m_osIP.size(); i++)
		   stros[i] = C_Ts.m_osIP[i];

//			n_SPort = 8001;
//		     StartServer();
//				if(!StartMC())
#else
//         	curuser.Format("%d",n_process);
//    		AfxMessageBox(curuser);
	if(strmes != "On")
	{
			if(C_Ts.m_osIP[0] == m_strms[11].strl) //主机
			{
//    		C_Ts.KillProcess("RSDRAW-YSDB.EXE");
			n_SPort = 8001;
		     StartServer();
       g_Log1.StatusOut("启动程序内数据服务器。");
//			 C_Ts.CreateP(gstrTimeOut +"\\RSDRAW-YSDB.EXE",NULL,7,0x00000001);
//       g_Log1.StatusOut("启动数据存储程序。");

    			CLoginDlg dlglogin;
	    		dlglogin.m_strdism = "login";
	    		if(dlglogin.DoModal()==IDOK) 
				{
				if(curuser == "")
    				m_bLogIn=false;
				else
    				m_bLogIn=true;
       g_Log1.StatusOut("用户：" +curuser+ "登陆。");
				}
		    	else
	    			return FALSE;

				if(StartMC())
                     g_Log1.StatusOut("主机监听!");
			}
//			else if("192.168.1.12" == m_strms[16].strl) //备机
			else if(C_Ts.m_osIP[0] == m_strms[16].strl) //备机
			{
//    		C_Ts.KillProcess("RSDRAW-YSDBB.EXE");
			n_SPort = 8002;
		     StartServer();
       g_Log1.StatusOut("启动程序内数据服务器。"); //备机监听8002
//			 C_Ts.CreateP(gstrTimeOut +"\\RSDRAW-YSDBB.EXE",NULL,7,0x00000001);
//       g_Log1.StatusOut("启动数据存储程序。");

    			CLoginDlg dlglogin;
	    		dlglogin.m_strdism = "login";
	    		if(dlglogin.DoModal()==IDOK) 
				{
    				if(curuser == "")
        				m_bLogIn=false;
	    			else
    	    			m_bLogIn=true;
                    g_Log1.StatusOut("用户：" +curuser+ "登陆。");
				}
		    	else
	    			return FALSE;

               	b_SaveRT = FALSE;
				if(StartBC())
                     g_Log1.StatusOut("备机监听!");
				else
                 	b_SaveRT = TRUE;

			}
			else
			{
            	curuser ="";
//        		C_Ts.KillProcess("RSDRAW-YSDBB.EXE");
//        		C_Ts.KillProcess("RSDRAW-YSDB.EXE");
       g_Log1.StatusOut("非主、备机用户关闭数据存储程序。");
			}
//			n_SPort = 8004;
//		     StartServerB();
	}
#endif //_DEBUG
	if(strmes != "On")
	{
    	m_RTDM.ConnectDB();
		m_DebugInfo.clear();
		m_RDCHm5.clear();
			if(!StartClient())
			{
        		AfxMessageBox("没有找到服务器，请确认服务器设置是否正确!");
				return FALSE;
			}
       g_Log1.StatusOut("正常连接数据服务器，开始监控设备。");
			if(!StartFC())
			{
        		AfxMessageBox("没有找到在线文件服务器，请确认在线文件服务器设置是否正确!");
			}
	}
        	CMainFrame* pFWnd=(CMainFrame*)AfxGetMainWnd();
			pFWnd->StartTimer();

	return TRUE;
}

int CGUI_VisualStudioApp::ExitInstance() 
{
//	AfxEndThread(0);
    if ( m_Realtimedata._IsOpen() )
      m_Realtimedata.Close();
    m_Cn.Close();
    //Cleanup the AxLib library
    dbAx::Term();

	OnWindowCloseAll();
	GdiplusShutdown(gdiplusToken);
//	LPCTSTR ExeName;
//	m_sql.Close();
//	OnCloseDB();
    db3.close();
    db3m.close();
	m_pConnection->Close(); 
	::CoUninitialize();
       g_Log1.StatusOut("正常退出系统，再见！");

	return CWinApp::ExitInstance();
}

BOOL CGUI_VisualStudioApp::PreTranslateMessage(MSG* pMsg) 
{
#ifdef _DEBUG
#else
	if (CSplashWnd::PreTranslateAppMessage(pMsg))
		return TRUE;
#endif //_DEBUG
	
    	return CWinApp::PreTranslateMessage(pMsg);
}

BOOL CGUI_VisualStudioApp::ProcessShellCommand(CCommandLineInfo& rCmdInfo)
{
	BOOL bResult = TRUE;
	switch (rCmdInfo.m_nShellCommand)
	{
	case CCommandLineInfo::FileNew:
//		if (!AfxGetApp()->OnCmdMsg(ID_FILE_NEW, 0, NULL, NULL))
//			OnFileNew();
		if (m_pMainWnd == NULL)
			bResult = FALSE;
		break;

		// If we've been asked to open a file, call OpenDocumentFile()

	case CCommandLineInfo::FileOpen:
		if (!OpenDocumentFile(rCmdInfo.m_strFileName))
			bResult = FALSE;
		break;

		// If the user wanted to print, hide our main window and
		// fire a message to ourselves to start the printing

	case CCommandLineInfo::FilePrintTo:
	case CCommandLineInfo::FilePrint:
		m_nCmdShow = SW_HIDE;
		ASSERT(m_pCmdInfo == NULL);
		OpenDocumentFile(rCmdInfo.m_strFileName);
		m_pCmdInfo = &rCmdInfo;
		m_pMainWnd->SendMessage(WM_COMMAND, ID_FILE_PRINT_DIRECT);
		m_pCmdInfo = NULL;
		bResult = FALSE;
		break;

		// If we're doing DDE, hide ourselves

	case CCommandLineInfo::FileDDE:
		m_pCmdInfo = (CCommandLineInfo*)m_nCmdShow;
		m_nCmdShow = SW_HIDE;
		break;

	// If we've been asked to unregister, unregister and then terminate
	case CCommandLineInfo::AppUnregister:
		{
			UnregisterShellFileTypes();
			BOOL bUnregistered = Unregister();

			// if you specify /EMBEDDED, we won't make an success/failure box
			// this use of /EMBEDDED is not related to OLE

			if (!rCmdInfo.m_bRunEmbedded)
			{
				if (bUnregistered)
					AfxMessageBox(AFX_IDP_UNREG_DONE);
				else
					AfxMessageBox(AFX_IDP_UNREG_FAILURE);
			}
			bResult = FALSE;    // that's all we do

			// If nobody is using it already, we can use it.
			// We'll flag that we're unregistering and not save our state
			// on the way out. This new object gets deleted by the
			// app object destructor.

			if (m_pCmdInfo == NULL)
			{
				m_pCmdInfo = new CCommandLineInfo;
				m_pCmdInfo->m_nShellCommand = CCommandLineInfo::AppUnregister;
			}
		}
		break;
	}
	return bResult;

}

//作为客户端连接服务器
BOOL CGUI_VisualStudioApp::StartClient()
{
	if(socketClient.ConnectServer(m_strms[13].strl,m_Str2Data.String2Int(m_strms[14].strl)))
	{
        internet30s=20;
		m_FdsScan = 50;
		return TRUE;
	}
	else
	{
       g_Log1.StatusOut("没有找到数据服务器，请确认服务器设置是否正确!");
	}
	return FALSE;
}
BOOL CGUI_VisualStudioApp::StartFC()
{
	sFC.ConnectDB();
	UINT u_port =8003;
	if(sFC.ConnectServer(m_strms[17].strl, u_port))
	{
//		m_FdsScan = 50;
		return TRUE;
	}
	else
	{
           m_senddata =true;
       g_Log1.StatusOut("没有找到在线文件服务器，请确认在线文件服务器设置是否正确!");
	}
	return FALSE;
}
//作为客户端连接主机
BOOL CGUI_VisualStudioApp::StartBC()
{
	if(socketClient.ConnectServer(m_strms[11].strl,8001))
//	if(sCb.ConnectServer("caohaita-257e56",8003))
	{
//		AfxMessageBox("备机监听!");
               	b_SaveRT = FALSE;
				if(n_CPort != 999)
				{
       	        CNDKMessage message1(MASTERSLAVER);
				message1.Add(444);//备-主
				Sync(message1,2);
				}
    	n_CPort =999;//备
		return TRUE;
	}
	else
	{
    	n_CPort =0;  //主备机监听失败
//		AfxMessageBox("备机监听失败!");
	}
	return FALSE;
}

//作为主机连接    备机 8002
BOOL CGUI_VisualStudioApp::StartMC()
{
//	if(sCb.ConnectServer("",8002))
//	if(sCb.ConnectServer("192.168.1.12",8002))
	if(sCb.ConnectServer(m_strms[16].strl,8002))
	{
				if(n_CPort != 888)
				{
       	        CNDKMessage message1(MASTERSLAVER);
				message1.Add(333);//主--备
				Sync(message1,2);
//		AfxMessageBox("主机监听!");
				}
    	n_CPort =888;//主
		return TRUE;
	}
	else
	{
    	n_CPort =0;  //主备机监听失败
//		AfxMessageBox("主机监听失败!");
	}
	return FALSE;
}
//初始化结构
BOOL CGUI_VisualStudioApp::ConnectDB()
{
		m_PointDes.Create();
		m_PointDes.CursorType(adOpenDynamic);
		m_PointDes.CacheSize(50);
		m_PointDes._SetRecordsetEvents(new CAccountSetEvents);
		m_PointDes.Open(_T("Select * From pointdescription WHERE fdel=0"), &m_Cn);
		m_PointDes.MarshalOptions(adMarshalModifiedOnly);

		m_AccountSet.Create();
		m_AccountSet.CursorType(adOpenDynamic);
		m_AccountSet.CacheSize(50);
		m_AccountSet._SetRecordsetEvents(new CAccountSetEvents);
		m_AccountSet.Open(_T("Select * From digitaltype WHERE fdel=0"), &m_Cn);
		m_AccountSet.MarshalOptions(adMarshalModifiedOnly);

		m_ContactSet.Create();
		m_ContactSet.CursorType(adOpenDynamic);
		m_ContactSet.CacheSize(50);
		m_ContactSet._SetRecordsetEvents(new CAccountSetEvents);
		m_ContactSet.Open(_T("Select * From analogtype WHERE fdel=0 "), &m_Cn);
		m_ContactSet.MarshalOptions(adMarshalModifiedOnly);

		m_SControl.Create();
		m_SControl.CursorType(adOpenDynamic);
		m_SControl.CacheSize(50);
		m_SControl._SetRecordsetEvents(new CAccountSetEvents);
		m_SControl.Open(_T("Select * From specialcontrol"), &m_Cn);
		m_SControl.MarshalOptions(adMarshalModifiedOnly);

		m_Control.Create();
		m_Control.CursorType(adOpenDynamic);
		m_Control.CacheSize(50);
		m_Control._SetRecordsetEvents(new CAccountSetEvents);
		m_Control.Open(_T("Select * From control WHERE fdel=0"), &m_Cn);
		m_Control.MarshalOptions(adMarshalModifiedOnly);

		m_Colorset.Create();
		m_Colorset.CursorType(adOpenDynamic);
		m_Colorset.CacheSize(50);
		m_Colorset._SetRecordsetEvents(new CAccountSetEvents);
		m_Colorset.Open(_T("Select * From colorset"), &m_Cn);
		m_Colorset.MarshalOptions(adMarshalModifiedOnly);

		m_AxFeedE.Create();
		m_AxFeedE.CursorType(adOpenDynamic);
		m_AxFeedE.CacheSize(50);
		m_AxFeedE._SetRecordsetEvents(new CAccountSetEvents);
		m_AxFeedE.Open(_T("Select * From feedelectricity WHERE fdel=0"), &m_Cn);
		m_AxFeedE.MarshalOptions(adMarshalModifiedOnly);

		m_CommonSet.Create();
		m_CommonSet.CursorType(adOpenDynamic);
		m_CommonSet.CacheSize(50);
		m_CommonSet._SetRecordsetEvents(new CAccountSetEvents);
		m_CommonSet.Open(_T("Select * From commonset WHERE CommonID<20"), &m_Cn);
		m_CommonSet.MarshalOptions(adMarshalModifiedOnly);

		m_MAlocation.Create();
		m_MAlocation.CursorType(adOpenDynamic);
		m_MAlocation.CacheSize(50);
		m_MAlocation._SetRecordsetEvents(new CAccountSetEvents);
		m_MAlocation.Open(_T("Select * From fixlocation"), &m_Cn);
		m_MAlocation.MarshalOptions(adMarshalModifiedOnly);

		m_Fans.Create();
		m_Fans.CursorType(adOpenDynamic);
		m_Fans.CacheSize(50);
		m_Fans._SetRecordsetEvents(new CAccountSetEvents);
		m_Fans.Open(_T("Select * From fanscon"), &m_Cn);
		m_Fans.MarshalOptions(adMarshalModifiedOnly);

		m_LID.clear();		m_Lstr.clear();
		CString strtemp;
          		m_MAlocation.MoveFirst();
         		while ( !m_MAlocation.IsEOF() )
				{//安装地点
					m_LID.push_back(m_MAlocation.m_szlocationID);
					strtemp = m_MAlocation.m_szName;
    	    		strtemp.TrimRight();
					m_Lstr.push_back(strtemp);
           			m_MAlocation.MoveNext();
				}

  return (TRUE);
}

BOOL CGUI_VisualStudioApp::InitUIInfo()
{
  CString szConnect = _T("Provider=SQLOLEDB.1;Persist Security Info=True;\
                          User ID=sa;Password=sunset;\
                          Data Source=") +strDBname+ _T(";Initial Catalog=BJygjl");

	::CoInitialize(NULL);
	m_pConnection.CreateInstance(_uuidof(ADOCust::Connection)); 
	try
	{
		m_pConnection->Open(_bstr_t(szConnect),"","",adModeUnknown); //连接叫作ADOTest的ODBC数据源
	}
	catch(_com_error e)
	{
		CString strSql1 = "数据库错误："+szConnect;
		AfxMessageBox(strSql1+e.ErrorMessage()); 
		return FALSE;
	}
//All calls to the AxLib should be wrapped in a try / catch block
  try
  {
    //Call the global Init function from the AxLib library. This will
    //initialize COM and setup the library's connection collection.
    //Use the namespace identifier to avoid conflict with any other
    //init functions that may exist.
    dbAx::Init();

    //Create the connection object
    m_Cn.Create();

    //Create the Connection events object on the heap. We don't need
    //to worry with deleting the Events object since this is handled
    //internally by its Release function. When no longer needed, the
    //Events object deletes itself.
//    m_Cn._SetConnectionEvents(new CCardFileEvents);

    //Set the cursor location and open the database connection
    m_Cn.CursorLocation(adUseClient);
    m_Cn.Open((LPCTSTR)szConnect);

  }
  catch ( dbAx::CAxException *e )
  {
    AfxMessageBox(e->m_szErrorDesc,  MB_OK);
    delete e;
    return (FALSE);
  }
       g_Log1.StatusOut("数据库运行正常。");

	CString strAppPath = C_Ts.GetAppPath();
	CString strxmlFile ;
	strxmlFile = strAppPath + "\\1024.xml";
    CControlXml controlXml;
    return controlXml.ParseXml(strxmlFile);
}

BOOL CGUI_VisualStudioApp::InitRTData()//读取当天数据
{
    	db3m.open(":memory:");
		CString  temp,dddd;
        db3m.execDML("create table rtdata(RTfds smallint, RTchan smallint, LP1 char(20), LP2 char(20) );");

    	int eyear;	unsigned char emonth;
		CTime t=CTime::GetCurrentTime();
		CString sztime,szConnect;
		m_RTDM.CalRtDB(t , eyear , emonth);
		sztime.Format("%d",eyear);
		szConnect = "Select * From rt";
		szConnect += sztime;
   		sztime.Format("%02d",emonth);
		szConnect += sztime;
		szConnect += "data WHERE recdate>'";
   		sztime = t.Format(_T("%Y-%m-%d 00:00:00"));
		szConnect += sztime +"' and recdate<'";
   		sztime = t.Format(_T("%Y-%m-%d %H:%M:%S"));
		szConnect += sztime +"'";

		m_Realtimedata.Create();
		m_Realtimedata.CursorType(adOpenDynamic);
		m_Realtimedata.CacheSize(50);
		m_Realtimedata.Open(szConnect , &m_Cn);
		m_Realtimedata.MarshalOptions(adMarshalModifiedOnly);

	int   nRange=m_Realtimedata.RecordCount();
	if(!m_Realtimedata._IsEmpty())
	{
		m_Realtimedata.MoveFirst();
		while ( !m_Realtimedata.IsEOF() )
		{
				int afds = m_Realtimedata.m_szfds;
				int achan = m_Realtimedata.m_szchan;
				int cv = m_Realtimedata.m_szCDValue;
				float av = m_Realtimedata.m_szAValue;
         	    int nptype = m_SlaveStation[afds][achan].ptype;
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
        	    unsigned char nstatus = m_Realtimedata.m_szADStatus;
        		if((nstatus == 0x40)||(nstatus == 0x50)||(nstatus == 0x80)||(nstatus == 0x70)||(nstatus == 0x90)|| (nstatus == 0xa0) || (nstatus == 0xa1))
          		      dddd= m_RTDM.strstatus(nstatus);
				sztime = m_Realtimedata.m_szrecdate.Format(_T("%Y-%m-%d %H:%M:%S"));

    			temp.Format("insert into rtdata values(%d, %d, '%s','%s');",afds,achan,dddd,sztime);
    			db3m.execDML(temp);
				
				m_Realtimedata.MoveNext();
		}
	}
    	for(int kk = 1; kk < MAX_FDS;kk++ )
		{
 			if(m_SerialF[kk].SFSd == 0 )
    			for(int i = 0; i < MAX_CHAN;i++ )
				{
					m_ndkSend[kk][1] = 255;
					m_SlaveStation[kk][i].CValue = 6;
					m_SlaveStation[kk][i].AValue = 666666;
					m_SlaveStation[kk][i].Channel_state =0xa1;
					m_SlaveStation[kk][i].ValueTime = COleDateTime::GetCurrentTime();
    	    		temp.Format("insert into rtdata values(%d, %d, '%s','%s');",kk,i,m_RTDM.strstatus(0xa1)
						    ,m_SlaveStation[kk][i].ValueTime.Format(_T("%Y-%m-%d %H:%M:%S")));
    	    		db3m.execDML(temp);
				}
		}
		m_resnum =13;
    g_Log1.StatusOut("读取当天数据正常。");

    return TRUE;
}

BOOL CGUI_VisualStudioApp::InitSQLite3()
{
	if(DocNum == 1)
    	OnWindowCloseAll();
     for(int k=1;k<100;k++)
         		  m_strl[k].strl= "";

	CString strrsy ,strclm,strrsy1,strclm1;
	int m_del =0;
	int m_ishave =0;
    // 字符串 buf 表示要遍历的目录名   char dirName[300]; 
	strrsy = gstrTimeOut + "\\" + strMetrics+ "rsy\\";
	strrsy1 ="dispoint"+strMetrics;

	if (!m_sdir.SetInitDir(strrsy))
	{//\r\n--------------------\r\n
        AfxMessageBox("目录不存在!", MB_OK);
		return 0;
	}
	m_sdir.m_nFileCount = 0;
	m_sdir.m_nSubdirCount = 0;
    try
    {
		CppSQLite3Query q;
    	m_addfilesy.clear();
//    	for ( int m = 0 ; m < 2 ; m++ )

//         	if(m == 0)
             	m_sdir.BeginBrowse("*.*");
//         	else if(m ==1)
//            	m_sdir.BeginBrowse("*.rsy");
			strclm1.Format("select * from '%s' WHERE DISID<100;",strrsy1);
            q = db3.execQuery(strclm1);
            while (!q.eof())
			{
				m_ishave = q.getIntField(0);
                strclm = q.getStringField(1);
	    		strclm.TrimRight();
	      		if(strclm != "")
		        	m_strl[m_ishave].strl=strclm;  //1 start要打开的文件
//					m_addfilesy.push_back(strclm);
                q.nextRow();
			}

			m_ishave =0;
//    		for(vector<CString>::iterator iter=m_addfilesy.begin(); iter!=m_addfilesy.end(); )
    		for(int i =1; i<100; i++)//剔出已删除文件，目录下无  第一列
			{
	    		strclm = m_strl[i].strl;
				if(strclm != "")
				{
					for ( int k = 0 ; k < m_sdir.m_dirs.size() ; k++ )
					{
			        	if(strclm == m_sdir.m_dirs[k])
						{
				        	m_ishave=100;       	break;
						}
			        	else
			    	    	m_ishave =0;
					}
	         		if(m_ishave == 0)//已删除文件
					{
			    		m_strl[i].strl ="";
			        	m_del++;
//		        		iter = m_addfilesy.erase(iter);
					}
//	    	    	else
//		    	    	iter++;
				}
			}
                    for(int k=1;k<100;k++)
					{
						strclm = m_strl[k].strl;
						if( strclm != "")
							m_addfilesy.push_back(strclm);//目前要打开文件
					}

    		CString strSQL,strSQL1;
		if(m_del>0)  //剔出已删除文件 重新保存现有文件 第一列
		{
           for(int m =0; m < m_addfilesy.size() ;m++)
		   {
			 strSQL1 = m_addfilesy[m];
				strSQL.Format("UPDATE '%s' SET LP0='%s' WHERE DISID = %d;",
					strrsy1,strSQL1,m+1);
             q = db3.execQuery(strSQL);
		   }
		     for(int i=m_addfilesy.size()+1 ;i<100;i++)
			 {
				strSQL.Format("UPDATE '%s' SET LP0='' WHERE DISID = %d;",
					strrsy1,i);
                q = db3.execQuery(strSQL);
			 }
		}

		int ishave=0;
	    	strSQL.Format("select * from '%s' WHERE DISID=1;",strrsy1);
            q = db3.execQuery(strSQL);
        for( k =2; k < 21 ;k++)//删除不在第一列的文件在dispoint中第一行的信息
		{
            strclm = q.getStringField(k);
			strclm.TrimRight();
			strSQL = strrsy + strclm;
			for(int m =0; m < m_addfilesy.size() ;m++)
			{
				strSQL1 = m_addfilesy[m];
      			if(strSQL1 == strSQL)
				{
    				ishave =100;
    				break;
				}
				else
    				ishave =0;
			}
    		if(ishave == 0 && strclm !="")
			{
				strSQL.Format("UPDATE '%s' SET LP%d='' WHERE DISID=1;",
					strrsy1,k-1);
			     db3.execDML(strSQL);
				for(int i = 501; i<800 ;i++) //点号清空
				{
	    			strSQL.Format("UPDATE '%s' SET LP%d='' WHERE DISID =%d;",
			    		strrsy1,k-1,i);
     			     db3.execDML(strSQL);
				}
			}
		}
		strSQL.Format("select * from '%s' WHERE DISID<300;",strrsy1);
         q = db3.execQuery(strSQL);
        while (!q.eof())
        {
    			ishave = q.getIntField(0);
				if(ishave == 1)
				{
          			for(int m =2; m < 21 ;m++)
					{
						strSQL1= q.getStringField(m);
						strSQL1.TrimRight();
	        			m_CommonStr[m-1].strc[0]= strSQL1;//文件名0
					}
				}
				else if(ishave > 10 && ishave < 36)
				{
          			for(int m =2; m < 21 ;m++)
					{
						strSQL1= q.getStringField(m);
						strSQL1.TrimRight();
	        			m_CommonStr[m-1].strc[ishave-10]= strSQL1;//list1初始化数据1
					}
				}
				else if(ishave > 110 && ishave < 136)
				{
          			for(int m =2; m < 21 ;m++)
					{
						strSQL1= q.getStringField(m);
						strSQL1.TrimRight();
	        			m_CommonStr[m-1].strc[ishave-80]= strSQL1;//list2初始化数据31
					}
				}
				else if(ishave > 210 && ishave < 236)
				{
          			for(int m =2; m < 21 ;m++)
					{
						strSQL1= q.getStringField(m);
						strSQL1.TrimRight();
	        			m_CommonStr[m-1].strc[ishave-150]= strSQL1;//list3初始化数据61
					}
				}
				else if(ishave > 49 && ishave < 66)
				{
          			for(int m =2; m < 21 ;m++)
					{
						strSQL1= q.getStringField(m);
						strSQL1.TrimRight();
	        			m_CommonStr[m-1].strc[ishave+40]= strSQL1;//list1ext 90
					}
				}
				else if(ishave > 149 && ishave < 166)
				{
          			for(int m =2; m < 21 ;m++)
					{
						strSQL1= q.getStringField(m);
						strSQL1.TrimRight();
	        			m_CommonStr[m-1].strc[ishave-40]= strSQL1;//list2ext 110
					}
				}
				else if(ishave > 249 && ishave < 266)
				{
          			for(int m =2; m < 21 ;m++)
					{
						strSQL1= q.getStringField(m);
						strSQL1.TrimRight();
	        			m_CommonStr[m-1].strc[ishave-120]= strSQL1;//list3ext 130
					}
				}

            q.nextRow();
        }
			strclm1.Format("select * from '%s' WHERE DISID=100;",strrsy1);
            q = db3.execQuery(strclm1);
			m_del =1000;
            while (!q.eof())//查找初始页面的序号
			{
				m_ishave = q.getIntField(0);
                strclm = q.getStringField(1);
	    		strclm.TrimRight();
				strclm = strrsy +strclm;
                for(int m =0; m < m_addfilesy.size() ;m++)
				{
		        	 strSQL1 = m_addfilesy[m];
					 if(strclm == strSQL1)
					 {
						 m_del = m;			 break;
					 }
				}
                q.nextRow();
			}
   		q.finalize();
	}
    catch (CppSQLite3Exception& e)
    {
		strclm = e.errorCode() + ":" ;
		strclm += e.errorMessage();
        AfxMessageBox(strclm, MB_OK);
        return FALSE;
    }
    CMainFrame* pFWnd=(CMainFrame*)AfxGetMainWnd();
	if(DocNum == 1)
	{
        for(int i =0; i < m_addfilesy.size() ;i++)
		{
		strclm = m_addfilesy[i];
		m_ishave = strclm.GetLength();
		strclm = strclm.Mid(m_ishave-3,3);
		if(strclm =="rsy")
    		pDocTemplate->OpenDocumentFile(m_addfilesy[i]) ;
		else if(strclm =="rsf")
    		pNewDocTemplate->OpenDocumentFile(m_addfilesy[i]) ;
		}
		if(m_del != 1000)
			pFWnd->OnMView(m_del,0);
		DocNum =0;
	}

//	pFWnd->OnWSYSTEM();

    return TRUE;
}

BOOL CGUI_VisualStudioApp::InitData()
{
    if ( !ConnectDB() )
       return (FALSE);
	if(!InitPointInfo())
		return FALSE;
	if(!m_RTDM.InitDisplay())
		return FALSE;
	OnCloseDB();

			COleDateTime CT1900(1900,1,1,0,0,0);
		for(int i = 1; i < MAX_FDS;i++ )
			for(int j = 0; j < MAX_CHAN;j++ )
			{
					m_ADMainDis[i][j].duant = 0;
					m_ADMainDis[i][j].m_ATotalnum = 0;
					m_ADMainDis[i][j].ATotalV = 0;
					m_ADMainDis[i][j].ATime = CT1900;
					m_ADMainDis[i][j].BTime = CT1900;
					m_ADMainDis[i][j].NTime = CT1900;
					m_ADMainDis[i][j].RTime = CT1900;
			}
	idis =bidis = fidis= dabidis =dfidis = dchidis=0;

    return true;
}

BOOL CGUI_VisualStudioApp::InitPointInfo()
{
	//初始化点
		for(int i = 0; i < MAX_FDS;i++ )
		{
		//需要故障闭锁分站  derror 数组数据越界 IAtlStringMgr* CAfxStringMgr::Clone() throw()
			m_SerialF[i].SFSd = 0;
			m_SerialF[i].cfds = 0;  //没有数据时为0
			for(int j = 0; j < MAX_CHAN;j++ )
			{
					m_SlaveStation[i][j].RangeH8 = 0xff;
					m_SlaveStation[i][j].RangeL8 = 0xff;
					m_SlaveStation[i][j].AValueH8 = 0xff;
					m_SlaveStation[i][j].AValueL8 = 0xff;
					m_SlaveStation[i][j].ApbrkH8 = 0xff;
					m_SlaveStation[i][j].ApbrkL8 = 0xff;
					m_SlaveStation[i][j].AprtnH8 = 0xff;
					m_SlaveStation[i][j].AprtnL8 = 0xff;
					m_SlaveStation[i][j].Control_state = 0;
					m_SlaveStation[i][j].Channel8 = 0xff;
					m_SlaveStation[i][j].ptype = 0;
					m_SlaveStation[i][j].m_RangeH = 0;
					m_SlaveStation[i][j].m_RangeL = 0;
					m_SlaveStation[i][j].AlarmValueH = 0;
					m_SlaveStation[i][j].AlarmValueL = 0;
					m_SlaveStation[i][j].Apbrk = 0;
					m_SlaveStation[i][j].Aprtn = 0;
					m_SlaveStation[i][j].falma = "";
					m_SlaveStation[i][j].WatchName = "";
					m_SlaveStation[i][j].utype = "";
					m_SlaveStation[i][j].m_Unit = "";
					m_SlaveStation[i][j].ZeroState = "";
					m_SlaveStation[i][j].OneState = "";
					m_SlaveStation[i][j].TwoState = "";
					m_SlaveStation[i][j].FeedState = "正常";
					m_SlaveStation[i][j].Adjust_state = 0;
					m_SlaveStation[i][j].m_second = 0;
					m_SlaveStation[i][j].m_ffds = 0;
					m_SlaveStation[i][j].m_fchan = 0;
					m_SlaveStation[i][j].strSafe = "";
					m_SlaveStation[i][j].m_PID = 0;
					m_SlaveStation[i][j].strBS = "";
			}
					m_SlaveStation[i][0].RangeH8 = 0;
					m_SlaveStation[i][0].RangeL8 = 0;
		}
		m_UpModA.clear();
		m_UpModD.clear();
		
		if ( m_PointDes._IsEmpty() )
		  return TRUE;
		int xxx = m_PointDes.RecordCount();
		int iItem = 0;
		m_PointDes.MoveFirst();
		while ( !m_PointDes.IsEOF() )
		{
			CString  strtemp,strtemp1;
	    	int nptype = m_PointDes.m_szptype;
    		int nfds = m_PointDes.m_szfds;
    		int nchan = m_PointDes.m_szchan;
			if(nptype <3) //模拟量
			{
        		m_ContactSet.MoveFirst();
        		while ( !m_ContactSet.IsEOF() )
				{
		    		if(m_ContactSet.m_szAID == m_PointDes.m_sztypeID)
					{
						xxx =9;//哪些名称被使用
						for(int k=0; k< m_UpModA.size(); k++)
						{
							if(m_ContactSet.m_szAID == m_UpModA[k])
							{
								xxx =13;
								break;
							}
						}
						if(xxx == 9)
							m_UpModA.push_back(m_ContactSet.m_szAID);
		    			break;
					}
    			m_ContactSet.MoveNext();
				}
				int n_suc =99;//无安装地点，不初始化
            	for (int n_lid = 0; n_lid < m_LID.size(); n_lid++)//安装地点
		    		if(m_LID[n_lid] == m_PointDes.m_szpositionid)
					{
						n_suc= 0;
		    			break;
					}

				if(n_suc == 0)
				{
  				m_SlaveStation[nfds][nchan].ptype = nptype;
				strtemp1 = m_ContactSet.m_szName;
				strtemp1.TrimRight();
				m_SlaveStation[nfds][nchan].WatchName = m_Lstr[n_lid]+ "|" +strtemp1;
    			m_SlaveStation[nfds][nchan].m_RangeH = m_ContactSet.m_szltop;
    			m_SlaveStation[nfds][nchan].m_RangeL = m_ContactSet.m_szlbom;
    			m_SlaveStation[nfds][nchan].AlarmValueH = m_ContactSet.m_szpalmu;
    			m_SlaveStation[nfds][nchan].AlarmValueL = m_ContactSet.m_szpalmd;
    			m_SlaveStation[nfds][nchan].Apbrk = m_ContactSet.m_szpbrk;
    			m_SlaveStation[nfds][nchan].Aprtn =m_ContactSet.m_szprtn;
				strtemp = m_PointDes.m_szutype;
				strtemp.TrimRight();
    			m_SlaveStation[nfds][nchan].utype = strtemp;
				strtemp = m_ContactSet.m_szpunit;
				strtemp.TrimRight();
    			m_SlaveStation[nfds][nchan].m_Unit = strtemp;
				strtemp = m_ContactSet.m_szfalm;
				strtemp.TrimRight();
    			m_SlaveStation[nfds][nchan].falma = strtemp;
				strtemp.Format("%02dA%02d",nfds,nchan);
    			m_SlaveStation[nfds][nchan].strPN = strtemp;

//				if(nptype == 0)
				    xxx = (int)m_SlaveStation[nfds][nchan].m_RangeH*10/10;
//				    xxx = 1200*m_SlaveStation[nfds][nchan].m_RangeH/(m_SlaveStation[nfds][nchan].m_RangeH-m_SlaveStation[nfds][nchan].m_RangeL) - 300;
//				else
//				    xxx = 800*m_SlaveStation[nfds][nchan].m_RangeH/(m_SlaveStation[nfds][nchan].m_RangeH-m_SlaveStation[nfds][nchan].m_RangeL) - 200;
				m_SlaveStation[nfds][nchan].RangeH8 = xxx/256;
    			m_SlaveStation[nfds][nchan].RangeL8 = xxx%256;
				if(nptype == 0)
				    xxx = 1200*m_SlaveStation[nfds][nchan].AlarmValueH/(m_SlaveStation[nfds][nchan].m_RangeH-m_SlaveStation[nfds][nchan].m_RangeL) + 300;
				else if (nptype == 1)
				    xxx = 800*m_SlaveStation[nfds][nchan].AlarmValueH/(m_SlaveStation[nfds][nchan].m_RangeH-m_SlaveStation[nfds][nchan].m_RangeL) + 200;
				else if (nptype == 2)
				    xxx = (int)m_SlaveStation[nfds][nchan].AlarmValueH*10/10 ;
    			m_SlaveStation[nfds][nchan].AValueH8 = xxx/256;
    			m_SlaveStation[nfds][nchan].AValueL8 = xxx%256;
				if(nptype == 0)
				    xxx = 1200*m_SlaveStation[nfds][nchan].Apbrk/(m_SlaveStation[nfds][nchan].m_RangeH-m_SlaveStation[nfds][nchan].m_RangeL) + 300;
				else if(nptype == 1)
				    xxx = 800*m_SlaveStation[nfds][nchan].Apbrk/(m_SlaveStation[nfds][nchan].m_RangeH-m_SlaveStation[nfds][nchan].m_RangeL) + 200;
				else if (nptype == 2)
				    xxx = (int)m_SlaveStation[nfds][nchan].Apbrk*10/10 ;
    			m_SlaveStation[nfds][nchan].ApbrkH8 = xxx/256;
    			m_SlaveStation[nfds][nchan].ApbrkL8 = xxx%256;
				if(nptype == 0)
				    xxx = 1200*m_SlaveStation[nfds][nchan].Aprtn/(m_SlaveStation[nfds][nchan].m_RangeH-m_SlaveStation[nfds][nchan].m_RangeL) + 300;
				else if(nptype == 1)
				    xxx = 800*m_SlaveStation[nfds][nchan].Aprtn/(m_SlaveStation[nfds][nchan].m_RangeH-m_SlaveStation[nfds][nchan].m_RangeL) + 200;
				else if(nptype == 2)
				    xxx = (int)m_SlaveStation[nfds][nchan].Aprtn*10/10 ;
    			m_SlaveStation[nfds][nchan].AprtnH8 =xxx/256;
    			m_SlaveStation[nfds][nchan].AprtnL8 = xxx%256;
				unsigned char chanh;
				if(nptype == 0)
					chanh =0x20;
				else if(nptype == 1)
					chanh =0xa0;
				else if(nptype == 2)
					chanh =0x40;
    			m_SlaveStation[nfds][nchan].Channel8 = 0x01 |chanh;
    			m_SlaveStation[nfds][nchan].m_PID = m_PointDes.m_szPID;

				m_DisplayDraw[m_PointDes.m_szPID].fds = nfds;
				m_DisplayDraw[m_PointDes.m_szPID].chan = nchan;
				}
			}
			else      //开关量
			{
        		m_AccountSet.MoveFirst();
        		while ( !m_AccountSet.IsEOF() )
				{
    				if(m_AccountSet.m_szDID == m_PointDes.m_sztypeID)
					{
						xxx =9;//那些名称被使用
						for(int k=0; k< m_UpModD.size(); k++)
						{
							if(m_AccountSet.m_szDID == m_UpModD[k])
							{
								xxx =13;
								break;
							}
						}
						if(xxx == 9)
							m_UpModD.push_back(m_AccountSet.m_szDID);
			    		break;
					}
    	    		m_AccountSet.MoveNext();
				}
				int n_suc =99;
            	for ( int n_lid = 0; n_lid < m_LID.size(); n_lid++)//安装地点
		    		if(m_LID[n_lid] == m_PointDes.m_szpositionid)
					{
						n_suc =0;
		    			break;
					}

				if(n_suc == 0)
				{
				int nptype = m_PointDes.m_szptype;
//					if(nptype == 12)
//						nchan = nchan+16;
//					if(nptype == 11)
//						nchan = 0;
  				m_SlaveStation[nfds][nchan].ptype = nptype;
				strtemp1 = m_AccountSet.m_szName;
				strtemp1.TrimRight();
				m_SlaveStation[nfds][nchan].WatchName = m_Lstr[n_lid]+ "|" +strtemp1;
				m_SlaveStation[nfds][nchan].AValue = 6;


    			m_SlaveStation[nfds][nchan].AlarmState = m_AccountSet.m_szpalms;
				strtemp = m_AccountSet.m_szname0;
				strtemp.TrimRight();
    			m_SlaveStation[nfds][nchan].ZeroState = strtemp;
//				if(nptype == 11)
//    	    		m_SlaveStation[nfds][0].ZeroState = "交流供电";
				strtemp = m_AccountSet.m_szname1;
				strtemp.TrimRight();
    			m_SlaveStation[nfds][nchan].OneState = strtemp;
//				if(nptype == 11)
//    	    		m_SlaveStation[nfds][0].OneState = "直流供电";
				strtemp = m_AccountSet.m_szname2;
				strtemp.TrimRight();
    			m_SlaveStation[nfds][nchan].TwoState = strtemp;
				strtemp = m_PointDes.m_szutype;
				strtemp.TrimRight();
    			m_SlaveStation[nfds][nchan].utype = strtemp;
				strtemp = m_AccountSet.m_szfalm;
				strtemp.TrimRight();
    			m_SlaveStation[nfds][nchan].falma = strtemp;
    			m_SlaveStation[nfds][nchan].m_PID = m_PointDes.m_szPID;

				unsigned char chanalarm,chanb,chanr,chanalarm1,chanb1,chanr1;
				if((nptype == 10) ||(nptype == 13)||(nptype == 14))
				{
    				strtemp.Format("%02dD%02d",nfds,nchan);
        			m_SlaveStation[nfds][nchan].strPN = strtemp;
					xxx = m_SlaveStation[nfds][nchan].AlarmState;//palms
					if(xxx == 0)   //不报警，不断电
					{
						chanalarm =0xff;
						chanb =0xff;
						chanr = 0xff;
						chanalarm1 =0xff;
						chanb1 =0xff;
						chanr1 = 0xff;
					}
					else if(xxx == 1)  //0态报警
					{
						chanalarm =0x00;
						chanb =0xff;
						chanr = 0xff;
						chanalarm1 =0x00;
						chanb1 =0xff;
						chanr1 = 0xff;
					}
					else if(xxx == 2) //1态报警
					{
						chanalarm =0x01;
						chanb =0xff;
						chanr = 0xff;
						chanalarm1 =0x00;
						chanb1 =0xff;
						chanr1 = 0xff;
					}
					else if(xxx == 3) //1态复电
					{
						chanalarm =0xff;
						chanb =0x00;
						chanr = 0x01;
						chanalarm1 =0xff;
						chanb1 =0x00;
						chanr1 = 0x00;
					}
					else if(xxx == 4)//1态断电
					{
						chanalarm =0xff;
						chanb =0x01;
						chanr = 0x00;
						chanalarm1 =0xff;
						chanb1 =0x00;
						chanr1 = 0x00;
					}
		    		m_SlaveStation[nfds][nchan].RangeH8 = 0x00;
    			m_SlaveStation[nfds][nchan].RangeL8 = 0x01;
    			m_SlaveStation[nfds][nchan].AValueH8 = chanalarm1;
    			m_SlaveStation[nfds][nchan].AValueL8 = chanalarm;
    			m_SlaveStation[nfds][nchan].ApbrkH8 = chanb1;
    			m_SlaveStation[nfds][nchan].ApbrkL8 = chanb;
    			m_SlaveStation[nfds][nchan].AprtnH8 = chanr1;
    	    		m_SlaveStation[nfds][nchan].AprtnL8 = chanr;
		     		unsigned char chanh;
		    		if(nptype == 10)
		    			chanh =0x60;
		     		else if(nptype == 13)
			    		chanh =0x80;
			      	else if(nptype == 14)
			    		chanh =0xe0;
    	    		m_SlaveStation[nfds][nchan].Channel8 = 0x01 |chanh;
				}
				if(nptype == 12) 
				{
    				strtemp.Format("%02dC%02d",nfds,nchan-16);
        			m_SlaveStation[nfds][nchan].strPN = strtemp;
					xxx = m_SlaveStation[nfds][nchan].AlarmState;
					if(nchan == 17)    // 低两位
					{
						chanr1 = 0x00;
    					chanr =xxx -4;   // 1--3   567
					}
					else if(nchan == 18)
					{
						chanr1 = 0x00;
    					chanr =(xxx -4)*4;
					}
					else if(nchan == 19)
					{
						chanr1 = 0x00;
    					chanr =(xxx -4)*16;
					}
					else if(nchan == 20)
					{
						chanr1 = 0x00;
    					chanr =(xxx -4)*64;
					}
					else if(nchan == 21)
					{
						chanr1 = xxx -4;
    					chanr =0x00;
					}
					else if(nchan == 22)
					{
						chanr1 = (xxx -4)*4;
    					chanr =0x00;
					}
					else if(nchan == 23)
					{
						chanr1 = (xxx -4)*16;
    					chanr =0x00;
					}
					else if(nchan == 24)
					{
						chanr1 = (xxx -4)*64;
    					chanr =0x00;
					}
        			m_SlaveStation[nfds][0].RangeH8 =m_SlaveStation[nfds][0].RangeH8 |chanr1;
        			m_SlaveStation[nfds][0].RangeL8 =m_SlaveStation[nfds][0].RangeL8 |chanr;
				}
				if(nptype == 11)
				{
    				strtemp.Format("%02dF00",nfds);
        			m_SlaveStation[nfds][0].strPN = strtemp;
				}
				
				m_DisplayDraw[m_PointDes.m_szPID].fds = nfds;
				m_DisplayDraw[m_PointDes.m_szPID].chan = nchan;
				}
			}

    		m_PointDes.MoveNext();
		}

        for(int k=0;k<20;k++)
         		  m_strms[k].strl= "";
		//显示班设置1班初始时间2班次 11主机、16备机 13服务器名 14服务器端口 15超时时间
		//CommonID<20
		m_CommonSet.MoveFirst();
		while ( !m_CommonSet.IsEOF() )
		{
			//班设置 1
        	CString  strc = m_CommonSet.m_szstrc1;
			strc.TrimRight();
			int coxx = m_CommonSet.m_szCommonID;
			m_strms[coxx].strl = strc;
			m_CommonSet.MoveNext();
		}
	     		m_SerialF[0].SFSd = m_Str2Data.String2Int(m_strms[1].strl);   //班初始时间
	       		m_SerialF[0].cfds = m_Str2Data.String2Int(m_strms[2].strl);  //班次

		//显示颜色
//		for( i = 0; i < 200;i++ )
//			m_Colorref[i].SFSd = 0;
		m_Colorset.MoveFirst();
		while ( !m_Colorset.IsEOF() )
		{
			//数据状态
			int coxx = m_Colorset.m_szColorID;
			//颜色值
			int vcolor = m_Colorset.m_szColorrefset;
			m_Colorref[coxx].SFSd = vcolor;
			m_Colorset.MoveNext();
		}

			for( i = 0; i < MAX_FDS;i++ )
			{
	    		for(int j = 0; j < 9;j++ )
				{
	         		for(int k = 0; k < 65;k++ )
	   	    			m_CFeed[i][j][k].bFSd = 0;
				}
			}
		//馈电规则
		if ( !m_AxFeedE._IsEmpty() )
		{
//		    iItem = 0;
		m_AxFeedE.MoveFirst();
		while ( !m_AxFeedE.IsEOF() )
		{
        	CString  strf,strc,strItem;
			strItem = m_AxFeedE.m_szcpointnum;
    		strf = strItem.Mid(0,2);
    		strc = strItem.Mid(3);
	    	int nfds = m_Str2Data.String2Int(strf);  
	     	int nchan = m_Str2Data.String2Int(strc);   //1-8
			for(int j = 0; j < 65;j++)
			{
    			int nfeed = m_CFeed[nfds][nchan][j].bFSd;
				if(nfeed == 0)
					break;
			}
			m_CFeed[nfds][nchan][j].cpoint = strItem;
			strItem = m_AxFeedE.m_szepointnum;
			m_CFeed[nfds][nchan][j].adpoint = strItem;
    		strf = strItem.Mid(0,2);
    		strc = strItem.Mid(3);
	    	int fnfds = m_Str2Data.String2Int(strf);
	     	int fnchan = m_Str2Data.String2Int(strc);
			m_CFeed[nfds][nchan][j].bFSd = fnfds;
			m_CFeed[nfds][nchan][j].bchanel = fnchan;
			for(int i = 0; i < 65;i++)
			{
    			int nfeed = m_CFeed[fnfds][fnchan][i].bFSd;
				if(nfeed == 0)
					break;
			}
			m_CFeed[fnfds][fnchan][i].bFSd = nfds;
			m_CFeed[fnfds][fnchan][i].bchanel = nchan;
			strItem = m_AxFeedE.m_szName;
			strItem.TrimRight();
			m_CFeed[nfds][nchan][j].CName = strItem;
//			iItem++;
			m_AxFeedE.MoveNext();
		}
		}
//		iItem = 0;
		m_SControl.MoveFirst();
		while ( !m_SControl.IsEOF() )
		{
      		CString  temp;
			int kk = m_SControl.m_szSID;
			//故障闭锁
			m_SlaveStation[kk][0].AlarmState = m_SControl.m_szSpeCtrol;
			//各串口连接的分站
			m_SerialF[kk].SFSd = m_SControl.m_szSerialnum;
			//没有巡检
			if(m_SerialF[kk].SFSd == 0 && m_Realtimedata._IsOpen())
    			for(int i = 0; i < MAX_CHAN;i++ )
				{
					m_ndkSend[kk][1] = 255;
					m_SlaveStation[kk][i].CValue = 6;
					m_SlaveStation[kk][i].AValue = 666666;
					m_SlaveStation[kk][i].Channel_state =0xa1;
					m_SlaveStation[kk][i].ValueTime = COleDateTime::GetCurrentTime();
    	    		temp.Format("insert into rtdata values(%d, %d, '%s','%s');",kk,i,m_RTDM.strstatus(0xa1)
						    ,m_SlaveStation[kk][i].ValueTime.Format(_T("%Y-%m-%d %H:%M:%S")));
    	    		db3m.execDML(temp);
				}
//			m_SerialF[m_SControl.m_szSerialnum][iItem].SFSd = m_SControl.m_szSID;
//			iItem++;
			m_SControl.MoveNext();
		}

			for( i = 1; i < MAX_FDS;i++ )
			{
		    	for(int j = 1; j < MAX_CHAN;j++ )
				{
	     	    	for(int k = 1; k < 65;k++ )
					{
			    		m_ADCbreakE[i][j][k].bFSd = 0;
					}
				}
			}
		//通道控制状态
		if ( !m_Control._IsEmpty())
		{
		m_Control.MoveFirst();
		while ( !m_Control.IsEOF() )
		{
        	CString  strf,strc,strItem,strItem1;
			strItem = m_Control.m_szpointnum;
			strItem.TrimRight();
    		strf = strItem.Mid(0,2);
    		strc = strItem.Mid(3);
	    	int nfds = m_Str2Data.String2Int(strf);
	    	int nchan = m_Str2Data.String2Int(strc);
			strItem1 = m_Control.m_szcpointnum;
			strItem1.TrimRight();
    		strf = strItem1.Mid(0,2);
    		strc = strItem1.Mid(3);
	    	int cnfds = m_Str2Data.String2Int(strf);
	    	int cnchan = m_Str2Data.String2Int(strc);
			unsigned char charc;
			if(nfds == cnfds)
			{
				if(cnchan == 1)					charc = 0x01;
				else if(cnchan == 2)					charc = 0x02;
				else if(cnchan == 3)					charc = 0x04;
				else if(cnchan == 4)					charc = 0x08;
				else if(cnchan == 5)					charc = 0x10;
				else if(cnchan == 6)					charc = 0x20;
				else if(cnchan == 7)					charc = 0x40;
				else if(cnchan == 8)					charc = 0x80;
				m_SlaveStation[nfds][nchan].Control_state |= charc;
			}
	LPCTSTR str1 = "",str2 = "",str3 = "";
	m_Str2Data.SplittoCString(m_SlaveStation[nfds][nchan].WatchName,str1,str2,str3);
	strf =str1;  strf +=" ";
	        m_SlaveStation[nfds][nchan].strBS.Replace(strf,"");
			m_SlaveStation[nfds][nchan].strBS +=strf;
		str1 = "",str2 = "",str3 = "";
	m_Str2Data.SplittoCString(m_SlaveStation[cnfds][cnchan+16].WatchName,str1,str2,str3);
	strf =str1;  strf +=" ";
	        m_SlaveStation[nfds][nchan].strBS.Replace(strf,"");
			m_SlaveStation[nfds][nchan].strBS +=strf;

				//C  模拟量开关量控制的控制量
				m_ADCbreakE[nfds][nchan][m_ADCbreakE[nfds][nchan][64].bFSd].bFSd = cnfds;
				m_ADCbreakE[nfds][nchan][m_ADCbreakE[nfds][nchan][64].bFSd].bchanel = cnchan;   //1-8
				m_ADCbreakE[nfds][nchan][m_ADCbreakE[nfds][nchan][64].bFSd].adpoint = strItem;
				m_ADCbreakE[nfds][nchan][m_ADCbreakE[nfds][nchan][64].bFSd].cpoint = strItem1;
//				strc = m_Control.m_szName;
//				strc.TrimRight();
//				m_ADCbreakE[cnfds][cnchan+16][m_ADCbreakE[nfds][nchan][64].bFSd].CName = strc;
				m_ADCbreakE[nfds][nchan][64].bFSd++;
				//A D 控制量控制源
				m_ADCbreakE[cnfds][cnchan+16][m_ADCbreakE[cnfds][cnchan+16][64].bFSd].bFSd = nfds;
				m_ADCbreakE[cnfds][cnchan+16][m_ADCbreakE[cnfds][cnchan+16][64].bFSd].bchanel = nchan;
				m_ADCbreakE[cnfds][cnchan+16][m_ADCbreakE[cnfds][cnchan+16][64].bFSd].adpoint = strItem;
				m_ADCbreakE[cnfds][cnchan+16][m_ADCbreakE[cnfds][cnchan+16][64].bFSd].cpoint = strItem1;
				m_ADCbreakE[cnfds][cnchan+16][64].bFSd++;
			m_Control.MoveNext();
		}
		}

			for( i = 1; i < MAX_FDS;i++ )
			{
		    	for(int j = 1; j < MAX_CHAN;j++ )
				{
			    		m_AFans[i][j].ffds = 0;  //标校存第一个值
			    		m_AFans[i][j].fchan = 0;  //已报警
			    		m_AFans[i][j].cfds = 0;
			    		m_AFans[i][j].cchan = 0;
						m_AFans[i][j].SFSd = 0;  //0 or 1 状态 alarm
				}
			}
		if ( !m_Fans._IsEmpty())
		{
    		m_Fans.MoveFirst();
    		while ( !m_Fans.IsEOF() )
			{
				  CString dddd = m_Fans.m_szpointnum1;//D1
            	dddd.TrimRight();
            	CString  strf,strc;
           		strf = dddd.Mid(0,2);
        		strc = dddd.Mid(3);
    	    	int nfds = m_Str2Data.String2Int(strf);
	        	int nchan = m_Str2Data.String2Int(strc);
				  dddd = m_Fans.m_szpointnum2;//D2
        		dddd.TrimRight();
          		strf = dddd.Mid(0,2);
         		strc = dddd.Mid(3);
     	    	int cnfds = m_Str2Data.String2Int(strf);
      	    	int cnchan = m_Str2Data.String2Int(strc);
			    		m_AFans[nfds][nchan].cfds = cnfds;
			    		m_AFans[nfds][nchan].cchan = cnchan;
						m_AFans[nfds][nchan].SFSd = m_Fans.m_szAStatus;//状态
			    		m_AFans[cnfds][cnchan].cfds = nfds;
			    		m_AFans[cnfds][cnchan].cchan = nchan;
						m_AFans[cnfds][cnchan].SFSd = m_Fans.m_szAStatus;//状态
    			m_Fans.MoveNext();
			}
		}

		return TRUE;

/*	CString strSQL;
	unsigned short k = 1;
	try
	{
		strSQL.Format("SELECT * FROM uPointProperty");
		if(m_sql.ExecuteSQL(strSQL)==SQL_SUCCESS)
		{
			int nRet=m_sql.Fetch();
			while(!nRet)
			{
				unsigned short unPointNo=(unsigned short)m_String2DataType.String2Int(m_sql.GetCol(1));
				BOOL bValueTypetemp= m_String2DataType.Str2Bool(m_sql.GetCol(6));
///				CString strLabeltemp=m_sql.GetCol(10);
				CString strExplaintemp=m_sql.GetCol(11);
				m_CPointInfo[unPointNo].strExplaintemp = strExplaintemp ;
				m_CWarnPoint[k].warnPoint = unPointNo ;
				k++;
				m_CWarnPoint[1].OldwarnPoint = k ;

				if(bValueTypetemp)
				{
            		strSQL.Format("SELECT * FROM uAnologPointProperty WHERE unPointNo = %d",unPointNo);
	             	if(m_sqlA.ExecuteSQL( strSQL )==SQL_SUCCESS)
					{
	            		if(!m_sqlA.Fetch())
						{
		            		m_CPointInfo[unPointNo].fMin = (double)m_String2DataType.String2Double(m_sqlA.GetCol(2));   //fMeasureMin
		            		m_CPointInfo[unPointNo].fMax = (double)m_String2DataType.String2Double(m_sqlA.GetCol(3));   //"fMeasureMax"
		                	UINT unWarnCause=(UINT)m_String2DataType.String2Int(m_sqlA.GetCol(5));
		         	    	m_CPointInfo[unPointNo].unWarnMin = (double)m_String2DataType.String2Double(m_sqlA.GetCol(7));   //"unWarnMinValue"
		        	    	m_CPointInfo[unPointNo].unWarnMax = (double)m_String2DataType.String2Double(m_sqlA.GetCol(8));  //"unWarnMaxValue"
		        	    	m_CPointInfo[unPointNo].usUnit = m_sqlA.GetCol(9);

		    		    	strSQL.Format("SELECT * FROM uWarnClass WHERE unWarnClassNo = %d",unWarnCause+1);
                           if(m_sqlA.ExecuteSQL(strSQL) == SQL_SUCCESS)
						   {
			            		if(!m_sqlA.Fetch())
                                   m_CPointInfo[unPointNo].strWarnCausetemp=m_sqlA.GetCol(2);
						   }
					     	else{
			            		AfxMessageBox("数据库表uWarnClass查询失败");
			                      return FALSE;
							}
						}  
					}
        	    	else
					{
        	    		AfxMessageBox("数据库表uAnologPointProperty没有打开");
                        return FALSE;
					}
				}
				else
				{
					strSQL.Format("SELECT * FROM uSwitchPointProperty WHERE unPointNo = %d",unPointNo);
					if(m_sqlD.ExecuteSQL( strSQL )==SQL_SUCCESS)
					{
						if(!m_sqlD.Fetch())
						{
							UINT unWarnCause=(UINT)m_String2DataType.String2Int(m_sqlD.GetCol(3));
			        		strSQL.Format("SELECT * FROM uWarnClass WHERE unWarnClassNo = %d", unWarnCause+1);
                            if(m_sqlD.ExecuteSQL(strSQL) == SQL_SUCCESS)
							{
			        	       	if(!m_sqlD.Fetch())
                                    m_CPointInfo[unPointNo].strWarnCausetemp=m_sqlD.GetCol(2);
							}
				     		else{
			            		AfxMessageBox("数据库表uWarnClass查询失败");
			                         return FALSE;
							}
						}
					}
					else
					{
						AfxMessageBox("数据库表uSwitchPointProperty没有打开");
			             return FALSE;
					}
				}
				nRet=m_sql.Fetch();
			}
     		return TRUE;
		}
		else
		{
			AfxMessageBox("数据库表uMonitorPointEdit没有打开");
			return FALSE;
		}
	}
	catch(CDBException *e)
	{
		e->ReportError();
		return FALSE;
	}*/
}


void CGUI_VisualStudioApp::OnCloseDB()
{
  try
  {
    if ( m_AccountSet._IsOpen() )
      m_AccountSet.Close();
    if ( m_ContactSet._IsOpen() )
      m_ContactSet.Close();
    if ( m_MAlocation._IsOpen() )
      m_MAlocation.Close();
    if ( m_PointDes._IsOpen() )
      m_PointDes.Close();
    if ( m_SControl._IsOpen() )
      m_SControl.Close();
    if ( m_Control._IsOpen() )
      m_Control.Close();
    if ( m_Colorset._IsOpen() )
      m_Colorset.Close();
    if ( m_AxFeedE._IsOpen() )
      m_AxFeedE.Close();
    if ( m_CommonSet._IsOpen() )
      m_CommonSet.Close();
    if ( m_Fans._IsOpen() )
        m_Fans.Close();

  }
  catch ( CAxException *e )
  {
    AfxMessageBox(e->m_szErrorDesc,  MB_OK);
    delete e;
  }
}


// App command to run the dialog
void CGUI_VisualStudioApp::OnAppAbout()
{
	CAboutDlg dlgAbout;
	dlgAbout.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CGUI_VisualStudioApp message handlers


void CGUI_VisualStudioApp::OnWindowCloseAll()
{
	CloseAllDocuments(FALSE);

}

//发送数据包
void CGUI_VisualStudioApp::SendMessage(CNDKMessage& message)
{
	sMSb.SendMessage(message);
}

//向主机发送信息
void CGUI_VisualStudioApp::Sync(CNDKMessage& message,int uuu)
{
		DocNum = 5;
	if(uuu == 1 && b_SaveRT)//主机存、发
	{
		socketClient.SendMessage(message);
	}
	else if(uuu == 2)
	{
		sCb.SendMessage(message);
	}
	else if(uuu == 3)//备机连接数据服务器
	{
		socketClient.SendMessage(message);
	}
		DocNum = 0;

}

//本机作为主机启动网络监听
BOOL CGUI_VisualStudioApp::StartServer()
{
	if(SocketServer.Listenning(n_SPort))
	{
//		bIsClient = FALSE;
		return TRUE;
	}
	return FALSE;
}

//本机作为主机启动网络监听
BOOL CGUI_VisualStudioApp::StartServerB()
{
	if(sMSb.Listenning(n_SPort))
	{
//		bIsClient = FALSE;
		return TRUE;
	}
	return FALSE;
}


CString CGUI_VisualStudioApp::SplitPath(CString strpath)
{
     	CString  strclm,strSQL;
			// Retrieve the file name with the extension
			char szFileName[_MAX_FNAME];
			char szExtension[_MAX_EXT];
			char szf1[_MAX_PATH];
			char szf2[_MAX_PATH];
			_splitpath(strpath, szf1, szf2, szFileName, szExtension);
			strclm = szf1 ;
			strclm += szf2;
			strSQL = szFileName;
			strSQL += szExtension;
	return strSQL;
}

