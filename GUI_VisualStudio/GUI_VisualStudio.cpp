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

#include "MQClient.h"
#include "math.h"
#include "FlatTabViewView.h"
#include "FlatTabViewDoc.h"
#include "TabbedViewView.h"
#include "ControlXml.h"

#include "SettingHostDlg.h"
#include "SetTimeDlg.h"
#include "LoginDlg.h"
#include "Tlhelp32.h"
//#include "SplashWindow.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CNDKMessage m_NDKmes[50];

SerialF               m_AFans[MAX_FDS][MAX_CHAN];    //双风门主扇备扇报警
ADMainDis             m_ADMainDis[MAX_FDS][MAX_CHAN];          //调用显示
SerialF               m_ClassTime[200];            //班设置
SerialF               m_DCHlist[MAX_FDS][MAX_CHAN][65];        //D状态改变
SerialF               m_DFlist[MAX_FDS][MAX_CHAN][65];     //D馈电列表
SerialF               m_DABlist[MAX_FDS][MAX_CHAN][65];    //D报警\断电列表
SerialF               m_Flist[MAX_FDS][MAX_CHAN][65];       //A馈电列表
SerialF               m_Blist[MAX_FDS][MAX_CHAN][65];   //A断电列表
SerialF               m_Warnlist[MAX_FDS][MAX_CHAN];    //A报警列表
ADCbreakE             m_CFeed[MAX_FDS][9][65];    //馈电规则
SerialF               m_Colorref[200];
SerialF               m_SerialF[MAX_FDS][65];    //各串口连接的分站
ADCbreakE             m_ADCbreakE[MAX_FDS][MAX_CHAN][65];
DisplayDraw    m_DisplayDraw[MAX_POINT_NUMBER];
DisplayPoint   m_DisplayPoint[32][64];
SlaveStation             m_SlaveStation[MAX_FDS][MAX_CHAN];
extern  OthersSetting    m_OthersSetting;
extern  DrawView         m_DrawView[20];
extern  FormView  m_FormView[20];
extern  ViewWindows m_ViewWindows[4];
CPointInfo m_CPointInfo[MAX_POINT_NUMBER];
extern CWarnPoint m_CWarnPoint[MAX_POINT_NUMBER];
CString gstrTimeOut;
/////////////////////////////////////////////////////////////////////////////
// CGUI_VisualStudioApp

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
	DocNum = idis = internet30s = 0;
	m_senddata = false;
	m_sendcom = true;
	strargc ="";
	m_bLogIn = false;
	curuser ="";
	m_bsuper = false;
	b_SaveRT = FALSE;
#ifdef _DEBUG
	curuser ="cht";
	m_bLogIn = true;
	m_bsuper = true;
#endif //_DEBUG
	m_FdsScan = 0;
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
	CString strmes = strargc.Mid(0,2);
	if(strmes == "On")
	{
			pDocTemplate = new CMultiDocTemplate(
				IDR_DRAWTYPE,
				RUNTIME_CLASS(CDrawDoc),
				RUNTIME_CLASS(CChildFrame), // custom MDI child frame
				RUNTIME_CLASS(CMadeCertView));
        	AddDocTemplate(pDocTemplate);
	}
	else
	{
			pDocTemplate = new CMultiDocTemplate(
				IDR_DRAWTYPE,
				RUNTIME_CLASS(CDrawDoc),
				RUNTIME_CLASS(CChildFrame), // custom MDI child frame
				RUNTIME_CLASS(CDrawView));
//	pDocTemplate->SetContainerInfo(IDR_DRAWTYPE_CNTR_IP);
///	pDocTemplate->SetServerInfo(
///		IDR_DRAWTYPE_SRVR_EMB, IDR_DRAWTYPE_SRVR_IP,
///		RUNTIME_CLASS(CInPlaceFrame));
        	AddDocTemplate(pDocTemplate);
	}
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
//	}
	if(strmes == "On")
	{
	}
	else
	{
			pNewDocTemplate = new CMultiDocTemplate(
				IDR_DRAWTYPE,
				RUNTIME_CLASS(CFlatTabViewDoc),
				RUNTIME_CLASS(CChildFrame), // custom MDI child frame   CFlatTabViewDoc
				RUNTIME_CLASS(CSampleFormView));   //CTabbedViewView
			AddDocTemplate(pNewDocTemplate);
	}

			if(!InitUIInfo())
			{
				AfxMessageBox("没有找到合适的分辨率配置文件，请确认是否有当前屏幕分辨率的配置文件!");
				return FALSE;
			}
	if(!InitData())
	{
		AfxMessageBox("初始化数据库失败！");
		return FALSE;
	}

	// create main MDI Frame window
	CMainFrame* pMainFrame = new CMainFrame;
     	if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
       		return FALSE;
	m_pMainWnd = pMainFrame;

	// Enable drag/drop open 
	m_pMainWnd->DragAcceptFiles();

	// Enable DDE Execute open
//	EnableShellOpen();
//	RegisterShellFileTypes(TRUE);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

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
	m_server.UpdateRegistry(OAT_INPLACE_SERVER);
	COleObjectFactory::UpdateRegistryAll();

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
	}
#endif //_DEBUG

//    	CSplashWindow SplashW;
//        CSplashWindow::ShowSplashScreen( NULL, "Starting application...");
//    	CSplashWindow::ShowSplashScreen( NULL, "Initializing hardware...");
//       	CSplashWindow::ShowSplashScreen( NULL, "Initializing database...");
    	// display final splash screen and have it turn off after 3 seconds (3000 milliseconds)
//     	CSplashWindow::ShowSplashScreen( m_pMainWnd, "http://www.xxx.com/", 3000);


	gstrTimeOut = C_Ts.GetAppPath();
	CString strrsy ;
	strrsy.Format("%d",GetSystemMetrics(SM_CXSCREEN));

	if(strmes == "On")
	{
//		pDocTemplate->OpenDocumentFile(NULL) ;
	}
	else
	{
			for(int i = 0; i < 5;i++ )
			{
				if(m_ViewWindows[i].VWName == _T("FormView"))  //1
				{
          			for(DocNum =0; DocNum < m_ViewWindows[i].numFormView ;DocNum++)
					{
						pNewDocTemplate->OpenDocumentFile(gstrTimeOut + "\\" + strrsy+ "rsy\\" + m_FormView[DocNum].FormViewName) ;
					}
				}
				else if(m_ViewWindows[i].VWName == _T("DrawView")) //0
				{
          			DocNum =9;
          			for(int k =0; k < m_ViewWindows[i].numDrawView ; k++)
					{
						pDocTemplate->OpenDocumentFile(gstrTimeOut + "\\" + strrsy+ "rsy\\" + m_DrawView[k].DrawViewName) ;
					}
				}
			}
			if(!StartClient())
				return FALSE;

//			for(int k=0 ; k<50 ;k++)
//				m_NDKmes[k] = NULL;

#ifdef _DEBUG
#else
//         	curuser.Format("%d",n_process);
//    		AfxMessageBox(curuser);
    		C_Ts.KillProcess("RSDRAW-YSDB.EXE");

			CLoginDlg dlglogin;
			dlglogin.m_strdism = "login";
			if(dlglogin.DoModal()==IDOK) 
			{
				if(curuser == "")
    				m_bLogIn=false;
				else
    				m_bLogIn=true;
			}
			else
				return FALSE;

		     StartServer();
			 C_Ts.CreateP(gstrTimeOut +"\\RSDRAW-YSDB.EXE",NULL,7,0x00000001);
#endif //_DEBUG
//        return fRet;
	}

	return TRUE;
}

int CGUI_VisualStudioApp::ExitInstance() 
{
	OnWindowCloseAll();
	GdiplusShutdown(gdiplusToken);
//	LPCTSTR ExeName;
//	m_sql.Close();
//	OnCloseDB();

	return CWinApp::ExitInstance();
}

BOOL CGUI_VisualStudioApp::PreTranslateMessage(MSG* pMsg) 
{
	if (CSplashWindow::PreTranslateAppMessage(pMsg))
		return TRUE;
		
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

//作为客户端连接主机
BOOL CGUI_VisualStudioApp::StartClient()
{
	if(socketClient.ConnectServer(m_OthersSetting.IP,m_OthersSetting.Port))
	{
		socketClient.ConnectDB();
		return TRUE;
	}
	else
	{
		AfxMessageBox("没有找到主机，请确认主机设置是否正确!");
	}
	return FALSE;
}

//初始化结构
BOOL CGUI_VisualStudioApp::ConnectDB()
{
  CString szConnect = _T("Provider=SQLOLEDB.1;Persist Security Info=True;\
                          User ID=sa;Password=sunset;\
                          Data Source=") +m_OthersSetting.DBname+ _T(";Initial Catalog=BJygjl");

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

		m_DisPoint.Create();
		m_DisPoint.CursorType(adOpenDynamic);
		m_DisPoint.CacheSize(50);
		m_DisPoint._SetRecordsetEvents(new CAccountSetEvents);
		m_DisPoint.Open(_T("Select * From dispoint"), &m_Cn);
		m_DisPoint.MarshalOptions(adMarshalModifiedOnly);

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
		m_CommonSet.Open(_T("Select * From commonset"), &m_Cn);
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
  }
  catch ( dbAx::CAxException *e )
  {
    AfxMessageBox(e->m_szErrorDesc,  MB_OK);
    delete e;
    return (FALSE);
  }
  return (TRUE);
}

BOOL CGUI_VisualStudioApp::InitUIInfo()
{
	CString strAppPath = C_Ts.GetAppPath();
	CString strxmlFile ;
	strxmlFile.Format("%d",GetSystemMetrics(SM_CXSCREEN));
	strxmlFile = strAppPath + "\\" +strxmlFile + ".xml";

    CControlXml controlXml;
    return controlXml.ParseXml(strxmlFile);
}

BOOL CGUI_VisualStudioApp::InitData()
{
    if ( !ConnectDB() )
       return (FALSE);
	if(!InitPointInfo())
		return FALSE;
	if(!InitDisplay())
		return FALSE;
	OnCloseDB();

			COleDateTime CTime(1900,1,1,0,0,0);
		for(int i = 1; i < MAX_FDS;i++ )
			for(int j = 1; j < MAX_CHAN;j++ )
			{
					m_ADMainDis[i][j].m_ATotalnum = 0;
					m_ADMainDis[i][j].ATotalV = 0;
					m_ADMainDis[i][j].ATime = CTime;
					m_ADMainDis[i][j].BTime = CTime;
					m_ADMainDis[i][j].NTime = CTime;
					m_ADMainDis[i][j].RTime = CTime;
					m_Warnlist[i][j].SFSd = 500;
				for(int k = 0; k < 65;k++)
				{
					m_Blist[i][j][k].SFSd = 500;
					m_Flist[i][j][k].SFSd = 500;
					m_DABlist[i][j][k].SFSd = 500;
					m_DFlist[i][j][k].SFSd = 500;
					m_DCHlist[i][j][k].SFSd = 500;
				}
			}
	idis =bidis = fidis= dabidis =dfidis = dchidis=0;

    return true;
}

void  CGUI_VisualStudioApp::pushDIS(CString  str1,CString  str2,CString  str3)
{
//					str1.TrimRight();
        			BuildDIS(str1);
					str2.TrimRight();
				if((str2.Find("A")!=-1) || (str2.Find("D")!=-1 )||(str2.Find("C")!=-1) ||(str2.Find("F")!=-1))
				{
           			BuildDIS(str2);
				}
					str3.TrimRight();
				if((str3.Find("A")!=-1) || (str3.Find("D")!=-1) ||(str3.Find("C")!=-1) ||(str3.Find("F")!=-1) )
				{
					if(str3 != str1 )
            			BuildDIS(str3);
				}
}

void  CGUI_VisualStudioApp::BuildDIS(CString  strItem)
{
//		if(strItem =="")
//			return;
	CString  strf,strc;
		int p =strItem.Find("C");
    		strf = strItem.Mid(0,2);
    		strc = strItem.Mid(3);

		int nlist = m_DisPoint.m_szDISID;
		int nfds = m_Str2Data.String2Int(strf);
		int nchan = m_Str2Data.String2Int(strc);
    	strc = m_SlaveStation[nfds][nchan].WatchName;
		if(strc =="")
			return;
		  m_DisplayPoint[nlist][idis].fds = nfds;
			  if(p != -1)
				  nchan = nchan+16;
		  m_DisplayPoint[nlist][idis].chan = nchan;
       	  m_DisplayPoint[nlist][idis].CPpointnum = strItem;
	    	  idis++;
}

BOOL CGUI_VisualStudioApp::InitPointInfo()
{
	//初始化点
		for(int i = 1; i < MAX_FDS;i++ )
		{
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
					m_SlaveStation[i][j].Channel_state = 255;
					m_SlaveStation[i][j].AValue = 0;
					m_SlaveStation[i][j].m_RangeH = 0;
					m_SlaveStation[i][j].m_RangeL = 0;
					m_SlaveStation[i][j].AlarmValueH = 0;
					m_SlaveStation[i][j].AlarmValueL = 0;
					m_SlaveStation[i][j].Apbrk = 0;
					m_SlaveStation[i][j].Aprtn = 0;
					m_SlaveStation[i][j].pnValue = 0;
					m_SlaveStation[i][j].CValue = 6;
					m_SlaveStation[i][j].AlarmState = 0;
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
					m_SlaveStation[i][j].m_5m = 0;
					m_SlaveStation[i][j].AMaxValue = 0;
					m_SlaveStation[i][j].AMinValue = 0;
					m_SlaveStation[i][j].ATotalValue = 0;
					m_SlaveStation[i][j].m_Atotal = 0;

	          COleDateTime timetemp;//(2010,1,1,0,0,0);
					m_SlaveStation[i][j].ValueTime = timetemp.GetCurrentTime();
					m_SlaveStation[i][j].m_PID = 0;
			}
					m_SlaveStation[i][0].RangeH8 = 0;
					m_SlaveStation[i][0].RangeL8 = 0;
		}
		
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
			if(nptype == 0  || nptype == 1 || nptype == 2) //模拟量
			{
        		m_ContactSet.MoveFirst();
        		while ( !m_ContactSet.IsEOF() )
				{
		    		if(m_ContactSet.m_szAID == m_PointDes.m_sztypeID)
		    			break;
    			m_ContactSet.MoveNext();
				}
          		m_MAlocation.MoveFirst();
         		while ( !m_MAlocation.IsEOF() )
				{
		    		if(m_MAlocation.m_szlocationID == m_PointDes.m_szpositionid)
		    			break;
           			m_MAlocation.MoveNext();
				}

  				m_SlaveStation[nfds][nchan].ptype = nptype;
     			strtemp = m_MAlocation.m_szName;
    			strtemp.TrimRight();
				strtemp1 = m_ContactSet.m_szName;
				strtemp1.TrimRight();
				m_SlaveStation[nfds][nchan].WatchName = strtemp+ "|" +strtemp1;
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

				int xxx;
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
			else      //开关量
			{
        		m_AccountSet.MoveFirst();
        		while ( !m_AccountSet.IsEOF() )
				{
    				if(m_AccountSet.m_szDID == m_PointDes.m_sztypeID)
			    		break;
    	    		m_AccountSet.MoveNext();
				}
          		m_MAlocation.MoveFirst();
         		while ( !m_MAlocation.IsEOF() )
				{
		    		if(m_MAlocation.m_szlocationID == m_PointDes.m_szpositionid)
		    			break;
           			m_MAlocation.MoveNext();
				}

				int nptype = m_PointDes.m_szptype;
//					if(nptype == 12)
//						nchan = nchan+16;
//					if(nptype == 11)
//						nchan = 0;
  				m_SlaveStation[nfds][nchan].ptype = nptype;
     			strtemp = m_MAlocation.m_szName;
    			strtemp.TrimRight();
				strtemp1 = m_AccountSet.m_szName;
				strtemp1.TrimRight();
				m_SlaveStation[nfds][nchan].WatchName = strtemp+ "|" +strtemp1;

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

				int xxx;
				unsigned char chanalarm,chanb,chanr,chanalarm1,chanb1,chanr1;
				if((nptype == 10) ||(nptype == 13)||(nptype == 14))
				{
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
				
				m_DisplayDraw[m_PointDes.m_szPID].fds = nfds;
				m_DisplayDraw[m_PointDes.m_szPID].chan = nchan;
			}

    		m_PointDes.MoveNext();
		}

		//显示班设置
		m_CommonSet.MoveFirst();
		while ( !m_CommonSet.IsEOF() )
		{
			//班设置 1
        	CString  strc = m_CommonSet.m_szstrc1;
			strc.TrimRight();
			if(strc == "")
				break;
			int coxx = m_CommonSet.m_szCommonID;
			if(coxx == 1)
	     		m_ClassTime[1].ffds = m_Str2Data.String2Int(strc);   //班初始时间
            else
	       		m_ClassTime[1].fchan = m_Str2Data.String2Int(strc);  //班次
			m_CommonSet.MoveNext();
		}
		//显示颜色
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

		//馈电规则
		if ( !m_AxFeedE._IsEmpty() )
		{
			for( i = 1; i < MAX_FDS;i++ )
			{
	    		for(int j = 1; j < 9;j++ )
				{
	         		for(int k = 0; k < 65;k++ )
	   	    			m_CFeed[i][j][k].bFSd = 0;
				}
			}
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
			int j;
			for( j = 0; j < 65;j++)
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
			strItem = m_AxFeedE.m_szName;
			strItem.TrimRight();
			m_CFeed[nfds][nchan][j].CName = strItem;
//			iItem++;
			m_AxFeedE.MoveNext();
		}
		}
		//需要故障闭锁分站
		for( i = 0; i < MAX_FDS;i++ )
		{
			for(int j = 0; j < 65;j++ )
			{
					m_SerialF[i][j].SFSd = 0;
			}
		}
		iItem = 0;
		m_SControl.MoveFirst();
		while ( !m_SControl.IsEOF() )
		{
			//故障闭锁
			m_SlaveStation[m_SControl.m_szSID][0].AlarmState = m_SControl.m_szSpeCtrol;
			//各串口连接的分站
			m_SerialF[m_SControl.m_szSerialnum][iItem].SFSd = m_SControl.m_szSID;
			iItem++;
			m_SControl.MoveNext();
		}

		//通道控制状态
		if ( !m_Control._IsEmpty())
		{
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
				//C  模拟量开关量控制的控制量
				m_ADCbreakE[nfds][nchan][m_ADCbreakE[nfds][nchan][64].bFSd].bFSd = cnfds;
				m_ADCbreakE[nfds][nchan][m_ADCbreakE[nfds][nchan][64].bFSd].bchanel = cnchan;   //1-8
				m_ADCbreakE[nfds][nchan][m_ADCbreakE[nfds][nchan][64].bFSd].adpoint = strItem;
				m_ADCbreakE[nfds][nchan][m_ADCbreakE[nfds][nchan][64].bFSd].cpoint = strItem1;
//				strc = m_Control.m_szName;
//				strc.TrimRight();
//				m_ADCbreakE[cnfds][cnchan+16][m_ADCbreakE[nfds][nchan][64].bFSd].CName = strc;
				m_ADCbreakE[nfds][nchan][64].bFSd++;
				//A D 控制量控制的
				m_ADCbreakE[cnfds][cnchan+16][m_ADCbreakE[cnfds][cnchan+16][64].bFSd].bFSd = nfds;
				m_ADCbreakE[cnfds][cnchan+16][m_ADCbreakE[cnfds][cnchan+16][64].bFSd].bchanel = nchan;
				m_ADCbreakE[cnfds][cnchan+16][m_ADCbreakE[cnfds][cnchan+16][64].bFSd].adpoint = strItem;
				m_ADCbreakE[cnfds][cnchan+16][m_ADCbreakE[cnfds][cnchan+16][64].bFSd].cpoint = strItem1;
				m_ADCbreakE[cnfds][cnchan+16][64].bFSd++;
			m_Control.MoveNext();
		}
		}

		if ( !m_Fans._IsEmpty())
		{
			for( i = 1; i < MAX_FDS;i++ )
			{
		    	for(int j = 1; j < MAX_CHAN;j++ )
				{
			    		m_AFans[i][j].cfds = 0;
			    		m_AFans[i][j].cchan = 0;
						m_AFans[i][j].SFSd = 0;
				}
			}
    		m_Fans.MoveFirst();
    		while ( !m_Fans.IsEOF() )
			{
				  CString dddd = m_Fans.m_szpointnum1;
            	dddd.TrimRight();
            	CString  strf,strc;
           		strf = dddd.Mid(0,2);
        		strc = dddd.Mid(3);
    	    	int nfds = m_Str2Data.String2Int(strf);
	        	int nchan = m_Str2Data.String2Int(strc);
				  dddd = m_Fans.m_szpointnum2;
        		dddd.TrimRight();
          		strf = dddd.Mid(0,2);
         		strc = dddd.Mid(3);
     	    	int cnfds = m_Str2Data.String2Int(strf);
      	    	int cnchan = m_Str2Data.String2Int(strc);
			    		m_AFans[nfds][nchan].cfds = cnfds;
			    		m_AFans[nfds][nchan].cchan = cnchan;
						m_AFans[nfds][nchan].SFSd = m_Fans.m_szAStatus;
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

BOOL CGUI_VisualStudioApp::InitDisplay()
{
		for(int i = 0; i < 32;i++ )
		{
			for(int j = 0; j < 64;j++ )
			{
					m_DisplayPoint[i][j].fds = 0;
			}
		}

	LPCTSTR str1 = "",str2 = "",str3 = "";
    	if ( m_DisPoint._IsEmpty() )
   		    return TRUE;
//		m_listDis.SetItemCount(m_DisPoint.RecordCount());
		m_DisPoint.MoveFirst();
		while ( !m_DisPoint.IsEOF() )
		{
			idis =0;
				str1 = "",str2 = "",str3 = "";
					m_DisPoint.m_szstr0.TrimRight();
				if(m_DisPoint.m_szstr0 != "")
				{
                	m_Str2Data.SplittoCString(m_DisPoint.m_szstr0,str1,str2,str3);
					pushDIS(str1, str2, str3);
				}
				str1 = "",str2 = "",str3 = "";
					m_DisPoint.m_szstr1.TrimRight();
				if(m_DisPoint.m_szstr1 != "")
				{
                	m_Str2Data.SplittoCString(m_DisPoint.m_szstr1,str1,str2,str3);
					pushDIS(str1, str2, str3);
				}
				str1 = "",str2 = "",str3 = "";
					m_DisPoint.m_szstr2.TrimRight();
				if(m_DisPoint.m_szstr2 != "")
				{
                	m_Str2Data.SplittoCString(m_DisPoint.m_szstr2,str1,str2,str3);
					pushDIS(str1, str2, str3);
				}
				str1 = "",str2 = "",str3 = "";
					m_DisPoint.m_szstr3.TrimRight();
				if(m_DisPoint.m_szstr3 != "")
				{
                	m_Str2Data.SplittoCString(m_DisPoint.m_szstr3,str1,str2,str3);
					pushDIS(str1, str2, str3);
				}
				str1 = "",str2 = "",str3 = "";
					m_DisPoint.m_szstr4.TrimRight();
				if(m_DisPoint.m_szstr4 != "")
				{
                	m_Str2Data.SplittoCString(m_DisPoint.m_szstr4,str1,str2,str3);
					pushDIS(str1, str2, str3);
				}
				str1 = "",str2 = "",str3 = "";
					m_DisPoint.m_szstr5.TrimRight();
				if(m_DisPoint.m_szstr5 != "")
				{
                	m_Str2Data.SplittoCString(m_DisPoint.m_szstr5,str1,str2,str3);
					pushDIS(str1, str2, str3);
				}
				str1 = "",str2 = "",str3 = "";
					m_DisPoint.m_szstr6.TrimRight();
				if(m_DisPoint.m_szstr6 != "")
				{
                	m_Str2Data.SplittoCString(m_DisPoint.m_szstr6,str1,str2,str3);
					pushDIS(str1, str2, str3);
				}
				str1 = "",str2 = "",str3 = "";
					m_DisPoint.m_szstr7.TrimRight();
				if(m_DisPoint.m_szstr7 != "")
				{
                	m_Str2Data.SplittoCString(m_DisPoint.m_szstr7,str1,str2,str3);
					pushDIS(str1, str2, str3);
				}
				str1 = "",str2 = "",str3 = "";
					m_DisPoint.m_szstr8.TrimRight();
				if(m_DisPoint.m_szstr8 != "")
				{
                	m_Str2Data.SplittoCString(m_DisPoint.m_szstr8,str1,str2,str3);
					pushDIS(str1, str2, str3);
				}
				str1 = "",str2 = "",str3 = "";
					m_DisPoint.m_szstr9.TrimRight();
				if(m_DisPoint.m_szstr9 != "")
				{
                	m_Str2Data.SplittoCString(m_DisPoint.m_szstr9,str1,str2,str3);
					pushDIS(str1, str2, str3);
				}
				str1 = "",str2 = "",str3 = "";
					m_DisPoint.m_szstr10.TrimRight();
				if(m_DisPoint.m_szstr10 != "")
				{
                	m_Str2Data.SplittoCString(m_DisPoint.m_szstr10,str1,str2,str3);
					pushDIS(str1, str2, str3);
				}
				str1 = "",str2 = "",str3 = "";
					m_DisPoint.m_szstr11.TrimRight();
				if(m_DisPoint.m_szstr11 != "")
				{
                	m_Str2Data.SplittoCString(m_DisPoint.m_szstr11,str1,str2,str3);
					pushDIS(str1, str2, str3);
				}
				str1 = "",str2 = "",str3 = "";
					m_DisPoint.m_szstr12.TrimRight();
				if(m_DisPoint.m_szstr12 != "")
				{
                	m_Str2Data.SplittoCString(m_DisPoint.m_szstr12,str1,str2,str3);
					pushDIS(str1, str2, str3);
				}
				str1 = "",str2 = "",str3 = "";
					m_DisPoint.m_szstr13.TrimRight();
				if(m_DisPoint.m_szstr13 != "")
				{
                	m_Str2Data.SplittoCString(m_DisPoint.m_szstr13,str1,str2,str3);
					pushDIS(str1, str2, str3);
				}
				str1 = "",str2 = "",str3 = "";
					m_DisPoint.m_szstr14.TrimRight();
				if(m_DisPoint.m_szstr14 != "")
				{
                	m_Str2Data.SplittoCString(m_DisPoint.m_szstr14,str1,str2,str3);
					pushDIS(str1, str2, str3);
				}
				str1 = "",str2 = "",str3 = "";
					m_DisPoint.m_szstr15.TrimRight();
				if(m_DisPoint.m_szstr15 != "")
				{
                	m_Str2Data.SplittoCString(m_DisPoint.m_szstr15,str1,str2,str3);
					pushDIS(str1, str2, str3);
				}
				str1 = "",str2 = "",str3 = "";
					m_DisPoint.m_szstr16.TrimRight();
				if(m_DisPoint.m_szstr16 != "")
				{
                	m_Str2Data.SplittoCString(m_DisPoint.m_szstr16,str1,str2,str3);
					pushDIS(str1, str2, str3);
				}
				str1 = "",str2 = "",str3 = "";
					m_DisPoint.m_szstr17.TrimRight();
				if(m_DisPoint.m_szstr17 != "")
				{
                	m_Str2Data.SplittoCString(m_DisPoint.m_szstr17,str1,str2,str3);
					pushDIS(str1, str2, str3);
				}
				str1 = "",str2 = "",str3 = "";
					m_DisPoint.m_szstr18.TrimRight();
				if(m_DisPoint.m_szstr18 != "")
				{
                	m_Str2Data.SplittoCString(m_DisPoint.m_szstr18,str1,str2,str3);
					pushDIS(str1, str2, str3);
				}
				str1 = "",str2 = "",str3 = "";
					m_DisPoint.m_szstr19.TrimRight();
				if(m_DisPoint.m_szstr19 != "")
				{
                	m_Str2Data.SplittoCString(m_DisPoint.m_szstr19,str1,str2,str3);
					pushDIS(str1, str2, str3);
				}
				m_DisPoint.MoveNext();
		}
        m_DisPoint.MoveFirst();

		CSampleFormView *psView;
		CString strTemp;
		POSITION m_ViewPos = m_Sam.GetStartPosition() ;     //0415
		for( i = 0; i < 10;i++ )
		{
    	   	if(m_ViewPos != NULL)
			{
         	    m_Sam.GetNextAssoc(m_ViewPos,strTemp,psView);
				psView->b_curdis =TRUE;
			}
			else
				break;
		}
		return TRUE;
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
    if ( m_DisPoint._IsOpen() )
      m_DisPoint.Close();
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

    m_Cn.Close();

    //Cleanup the AxLib library
    dbAx::Term();
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
	SocketServer.SendMessage(message);
}

//向主机发送信息
void CGUI_VisualStudioApp::Sync(CNDKMessage& message)
{
//	if(m_senddata)
	{
		socketClient.SendMessage(message);
	}

}

//本机作为主机启动网络监听
BOOL CGUI_VisualStudioApp::StartServer()
{
	if(SocketServer.Listenning())
	{
		m_message =0;
//		bIsClient = FALSE;
		return TRUE;
	}
	return FALSE;
}



