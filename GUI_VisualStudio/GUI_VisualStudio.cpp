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
	DocNum =0;
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
	pDocTemplate->SetContainerInfo(IDR_DRAWTYPE_CNTR_IP);
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

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

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

	CSettingHostDlg dlg;
//	dlg.m_strtable =  _T("dispoint");
//	dlg.PointDesid = 1;
//	if(dlg.DoModal() != IDOK)
//		return FALSE;

	gstrTimeOut = GetAppPath();

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
                pDocTemplate->OpenDocumentFile(gstrTimeOut + "\\rsy\\" + m_DrawView[k].DrawViewName) ;
			}
		}
	}
//	pDocTemplate->OpenDocumentFile(gstrTimeOut + "\\rsy\\窗口_4.rsy") ;
///	ConnectDB();

	if(!InitPointInfo())
	{
		return FALSE;
	}

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

	m_sql.Close();
	m_sqlA.Close();
	m_sqlD.Close();
		
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
void CGUI_VisualStudioApp::ConnectDB()
{
	try
	{
		m_sql.Init();
		m_sqlA.Init();
		m_sqlD.Init();
		if(m_sql.Connect(_T("masterdefine"),_T("kj86"),_T("kj86")))
			AfxMessageBox("AddUser:无法连接用户参数数据库,请确定SQL SERVER服务是否运行!");
		if(m_sqlA.Connect(_T("masterdefine"),_T("kj86"),_T("kj86")))
			AfxMessageBox("AddUser:无法连接用户参数数据库,请确定SQL SERVER服务是否运行!");
		if(m_sqlD.Connect(_T("masterdefine"),_T("kj86"),_T("kj86")))
			AfxMessageBox("AddUser:无法连接用户参数数据库,请确定SQL SERVER服务是否运行!");
	}
	catch(CDBException *e)
	{
		e->ReportError();
		return;
	}
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

BOOL CGUI_VisualStudioApp::InitPointInfo()
{
				m_CWarnPoint[0].OldwarnPoint = 9 ;
				m_CWarnPoint[0].warnPoint = 9 ;

		       	m_CPointInfo[1].fMin = 0 ;   //fMeasureMin
		   		m_CPointInfo[1].fMax = 5 ;  
		    	m_CPointInfo[1].unWarnMin = 3 ;   //"unWarnMinValue"
		     	m_CPointInfo[1].unWarnMax = 4 ;  //"unWarnMaxValue"
		      	m_CPointInfo[1].usUnit = "v" ;
				
		       	m_CPointInfo[2].fMin = 4 ;   //fMeasureMin
		   		m_CPointInfo[2].fMax = 20 ;  
		    	m_CPointInfo[2].unWarnMin = 10 ;   //"unWarnMinValue"
		     	m_CPointInfo[2].unWarnMax = 15 ;  //"unWarnMaxValue"
		      	m_CPointInfo[2].usUnit = "ma" ;

		       	m_CPointInfo[3].fMin = 1 ;   //fMeasureMin
		   		m_CPointInfo[3].fMax = 5 ;  
		    	m_CPointInfo[3].unWarnMin = 3 ;   //"unWarnMinValue"
		     	m_CPointInfo[3].unWarnMax = 4 ;  //"unWarnMaxValue"
		      	m_CPointInfo[3].usUnit = "v" ;
				
		      	m_CPointInfo[4].usUnit = "k" ;
    
		for(UINT n=1;n<9;n++)
		{
                m_CPointInfo[n].lWarn_state = 255 ;
				m_CPointInfo[n].strExplaintemp = "  13501325918 " ;
                m_CPointInfo[n].strWarnCausetemp = "  演示版  ";
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
