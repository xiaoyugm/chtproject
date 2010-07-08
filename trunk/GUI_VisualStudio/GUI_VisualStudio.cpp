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

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

DisplayDraw    m_DisplayDraw[MAX_POINT_NUMBER];
FDSscan               m_FDSscan[65];
DisplayPoint   m_DisplayPoint[32][64];
SlaveStation             m_SlaveStation[65][25];
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
	DocNum = idis = 0;
	m_senddata = false;
	m_sendcom = false;
	curuser ="cht";
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

	// Connect the COleTemplateServer to the document template.
	//  The COleTemplateServer creates new documents on behalf
	//  of requesting OLE containers by using information
	//  specified in the document template.
	m_server.ConnectTemplate(clsid, pDocTemplate, FALSE);

	// Register all OLE server factories as running.  This enables the
	//  OLE libraries to create objects from other applications.
	COleTemplateServer::RegisterAll();
		// Note: MDI applications register all server objects without regard
		//  to the /Embedding or /Automation on the command line.

	pNewDocTemplate = new CMultiDocTemplate(
		IDR_DRAWTYPE,
		RUNTIME_CLASS(CFlatTabViewDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame   CFlatTabViewDoc
		RUNTIME_CLASS(CSampleFormView));
	AddDocTemplate(pNewDocTemplate);

	pTabViewDocTemplate = new CMultiDocTemplate(
		IDR_DRAWTYPE,
		RUNTIME_CLASS(CFlatTabViewDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame   CFlatTabViewDoc
		RUNTIME_CLASS(CTabbedViewView));
	AddDocTemplate(pTabViewDocTemplate);

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
	pMainFrame->ShowWindow(SW_SHOWMAXIMIZED);
	pMainFrame->UpdateWindow();

	// Initialize GDI+.   
	GdiplusStartupInput gdiplusStartupInput;
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

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

	CSettingHostDlg dlg;
//	dlg.m_strtable =  _T("specialcontrol");   
//	dlg.PointDesid = 1;
//	if(dlg.DoModal() != IDOK)
//		return FALSE;

	CString ddd= "7E";
	unsigned char eee = m_Str2Data.Str2HEX(ddd);
	ddd= "S";
	eee = m_Str2Data.Str2HEX(ddd);

	gstrTimeOut = GetAppPath();

	CString strrsy ;
	strrsy.Format("%d",GetSystemMetrics(SM_CXSCREEN));

	for(int i = 0; i < 4;i++ )
	{
		if(m_ViewWindows[i].VWName == _T("FormView"))
		{
          	for(DocNum =0; DocNum < m_ViewWindows[i].numFormView ;DocNum++)
			{
                pNewDocTemplate->OpenDocumentFile(gstrTimeOut + "\\rsy\\" + m_FormView[DocNum].FormViewName) ;
			}
		}
		else if(m_ViewWindows[i].VWName == _T("DrawView"))
		{
          	DocNum =9;
          	for(int k =0; k < m_ViewWindows[i].numDrawView ; k++)
			{
                pDocTemplate->OpenDocumentFile(gstrTimeOut + "\\" + strrsy+ "rsy\\" + m_DrawView[k].DrawViewName) ;
			}
		}
	}
//	pDocTemplate->OpenDocumentFile(gstrTimeOut + "\\rsy\\窗口_4.rsy") ;

//	gstrIP = dlg.m_strHostIP;
//	gstrPort = dlg.m_strPort;
//	gstrTimeOut = dlg.m_strTimeOut;

//	if(gstrIP.IsEmpty()) 
//		gstrIP = m_OthersSetting.IP;
//	if(gstrPort.IsEmpty()) 
//		IPPort = m_OthersSetting.Port;
//	if(gstrTimeOut.IsEmpty()) gstrTimeOut = "6000";

	if(!StartClient())
		return FALSE;




	return TRUE;
}

int CGUI_VisualStudioApp::ExitInstance() 
{
	GdiplusShutdown(gdiplusToken);	

//	m_sql.Close();
//	OnCloseDB();
		
	socketClient.Close();
	return CWinApp::ExitInstance();
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


/******************************************************************************
//获得应用程序所在的路径
******************************************************************************/
CString CGUI_VisualStudioApp::GetAppPath()
{
	char AppPath[MAX_PATH];
	GetModuleFileName(NULL,AppPath,MAX_PATH);
	CString strAppPath=CString(AppPath);
	int i=strAppPath.ReverseFind('\\');
	strAppPath.Delete(i,strAppPath.GetLength()-i);
	return strAppPath;
}

//作为客户端连接主机
BOOL CGUI_VisualStudioApp::StartClient()
{
	if(socketClient.ConnectServer(m_OthersSetting.IP,m_OthersSetting.Port))
	{
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
    m_Cn._SetConnectionEvents(new CCardFileEvents);

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
	CString strAppPath = GetAppPath();
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
    return true;
}

void  CGUI_VisualStudioApp::pushDIS(CString  str1,CString  str2,CString  str3)
{
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
	CString  strf,strc;
		int p =strItem.Find("C");

    		strf = strItem.Mid(0,2);
    		strc = strItem.Mid(3);

		int nlist = m_DisPoint.m_szDISID;
		int nfds = m_Str2Data.String2Int(strf);
		int nchan = m_Str2Data.String2Int(strc);
		  m_DisplayPoint[nlist][idis].fds = nfds;
		  m_DisplayPoint[nlist][idis].chan = nchan;

			  if(p != -1)
				  nchan = nchan+15;
    		  m_DisplayPoint[nlist][idis].ptype = m_SlaveStation[nfds][nchan].ptype;
       		  m_DisplayPoint[nlist][idis].CPName = m_SlaveStation[nfds][nchan].WatchName;
         	  m_DisplayPoint[nlist][idis].CPpointnum = strItem;

		  m_DisplayPoint[nlist][60].fds = idis;
		  idis++;
}

BOOL CGUI_VisualStudioApp::InitPointInfo()
{
	//初始化点
		if ( m_PointDes._IsEmpty() )
		  return TRUE;
		int xxx = m_PointDes.RecordCount();
		int iItem = 0;
		m_PointDes.MoveFirst();
		while ( !m_PointDes.IsEOF() )
		{
	    	int nptype = m_PointDes.m_szptype;
    		int nfds = m_PointDes.m_szfds;
    		int nchan = m_PointDes.m_szchan;
			if(nptype == 0  || nptype == 1 || nptype == 2)
			{
        		m_ContactSet.MoveFirst();
        		while ( !m_ContactSet.IsEOF() )
				{
				if(m_ContactSet.m_szAID == m_PointDes.m_sztypeID)
					break;
    			m_ContactSet.MoveNext();
				}
  				m_SlaveStation[nfds][nchan].ptype = nptype;
  				m_SlaveStation[nfds][nchan].WatchName = m_PointDes.m_szName;
    			m_SlaveStation[nfds][nchan].m_RangeH = m_ContactSet.m_szltop;
//    			m_SlaveStation[nfds][nchan].m_Atype.m_RangeL = m_ContactSet.m_szlbom;
    			m_SlaveStation[nfds][nchan].AlarmValueH = m_ContactSet.m_szpalmu;
//    			m_SlaveStation[nfds][nchan].m_Atype.AlarmValueL = m_ContactSet.m_szpalmd;
    			m_SlaveStation[nfds][nchan].Apbrk = m_ContactSet.m_szpbrk;
    			m_SlaveStation[nfds][nchan].Aprtn =m_ContactSet.m_szprtn;
    			m_SlaveStation[nfds][nchan].utype = m_PointDes.m_szutype;
    			m_SlaveStation[nfds][nchan].m_Unit = m_ContactSet.m_szpunit;
    			m_SlaveStation[nfds][nchan].falma = m_ContactSet.m_szfalm;

				m_DisplayDraw[m_PointDes.m_szPID].fds = nfds;
				m_DisplayDraw[m_PointDes.m_szPID].chan = nchan;
			}
			else
			{
        		m_AccountSet.MoveFirst();
        		while ( !m_AccountSet.IsEOF() )
				{
				if(m_AccountSet.m_szDID == m_PointDes.m_sztypeID)
					break;
    			m_AccountSet.MoveNext();
				}
//            m_AccountSet.MoveFirst();
			int nptype = m_PointDes.m_szptype;
					if(nptype == 12)
						nchan = nchan+16;
					if(nptype == 11)
						nchan = 0;
  				m_SlaveStation[nfds][nchan].ptype = nptype;
    			m_SlaveStation[nfds][nchan].WatchName = m_PointDes.m_szName;
    			m_SlaveStation[nfds][nchan].AlarmState = m_AccountSet.m_szpalms;
    			m_SlaveStation[nfds][nchan].ZeroState = m_AccountSet.m_szname0;
    			m_SlaveStation[nfds][nchan].OneState = m_AccountSet.m_szname1;
    			m_SlaveStation[nfds][nchan].TwoState = m_AccountSet.m_szname2;
    			m_SlaveStation[nfds][nchan].utype = m_PointDes.m_szutype;
    			m_SlaveStation[nfds][nchan].falma = m_AccountSet.m_szfalm;

				m_DisplayDraw[m_PointDes.m_szPID].fds = nfds;
				m_DisplayDraw[m_PointDes.m_szPID].chan = nchan;
			}
    		m_PointDes.MoveNext();
		}
        m_PointDes.MoveFirst();

		//需要巡检分站
		iItem = 0;
		m_SControl.MoveFirst();
		while ( !m_SControl.IsEOF() )
		{
			if(m_SControl.m_szIsScan)
			{
				m_FDSscan[iItem].scanfds = m_SControl.m_szSID;
			    iItem++;
			}
			m_SControl.MoveNext();
		}
		m_FDSscan[64].scanfds = iItem;

		//通道控制状态
		if ( m_Control._IsEmpty() )
		  return TRUE;
		m_Control.MoveFirst();
		while ( !m_Control.IsEOF() )
		{
        	CString  strf,strc,strItem;
			strItem = m_Control.m_szpointnum;
    		strf = strItem.Mid(0,2);
    		strc = strItem.Mid(3);
	    	int nfds = m_Str2Data.String2Int(strf);
	    	int nchan = m_Str2Data.String2Int(strc);
			strItem = m_Control.m_szcpointnum;
    		strf = strItem.Mid(0,2);
    		strc = strItem.Mid(3);
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
			m_Control.MoveNext();
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
//    if ( m_MAlocation._IsOpen() )
//      m_MAlocation.Close();
    if ( m_PointDes._IsOpen() )
      m_PointDes.Close();
    if ( m_DisPoint._IsOpen() )
      m_DisPoint.Close();
    if ( m_SControl._IsOpen() )
      m_SControl.Close();
    if ( m_Control._IsOpen() )
      m_Control.Close();

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
void CGUI_VisualStudioApp::Sync()
{
	if(m_senddata)
	{
		socketClient.SendMessage(m_sendmessage);
	}

}

