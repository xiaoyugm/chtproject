// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "Curve.h"

#include "MainFrm.h"
#include "LoadDlg.h"
#include "CurveProp.h"
#include "String2DataType.h"
#include "math.h"
#include "Report.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CXTFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CXTFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
///	ON_COMMAND(ID_FILE_LOAD, OnFileLoad)
	ON_COMMAND(ID_MENU_EDIT_REPORT, OnMenuEditReport)
	ON_COMMAND(ID_GRAPHIC_PROPERTY, OnGraphicProperty)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
    xtAfxData.bXPMode = FALSE;
    xtAfxData.bMenuShadows = FALSE;
}

CMainFrame::~CMainFrame()
{
	try
	{
		m_PointMap.RemoveAll();
		m_sql.Close();
	}
	catch(...)
	{
	}
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CXTFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

    // Enable/Disable XP GUI Mode
    xtAfxData.bXPMode = TRUE;

    // Enable/Disable Menu Shadows
    xtAfxData.bMenuShadows = TRUE;

	if (!m_wndMenuBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndMenuBar.LoadMenuBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create menubar\n");
		return -1;      // fail to create  m_wndMenuBar
	}
	
	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	m_wndMenuBar.EnableDockingEx(CBRS_ALIGN_ANY, CBRS_XT_SEMIFLAT);
//	m_wndToolBar.EnableDockingEx(CBRS_ALIGN_ANY, CBRS_XT_SEMIFLAT);
	EnableDockingEx(CBRS_ALIGN_ANY, CBRS_XT_SEMIFLAT);
	DockControlBar(&m_wndMenuBar);
//	DockControlBar(&m_wndToolBar);

	InstallCoolMenus(IDR_MAINFRAME);
	///////////////装入数据库信息////////////////
	m_sql.Init();
	if(m_sql.Connect(_T("masterdefine"),_T("kj86"),_T("kj86")))
	{
		AfxMessageBox("NetThread:无法连接用户参数数据库,请确定SQL SERVER服务是否运行!");
		return 0;
	}
	LoadPointInfo();

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CXTFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	cs.style = WS_OVERLAPPED | WS_CAPTION | FWS_ADDTOTITLE
		| WS_THICKFRAME | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_MAXIMIZE;

	cs.lpszClass = AfxRegisterWndClass(0, NULL, NULL,
		AfxGetApp()->LoadIcon(IDR_MAINFRAME));

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CXTFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CXTFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

///////////装入点信息/////////////
void CMainFrame::LoadPointInfo()
{
	int nRet;
	if(m_PointMap.GetCount()>0)
		m_PointMap.RemoveAll();
	CSQLDirect SwitchSql,AnalogSql ;
	try
	{
		SwitchSql.Init();
		AnalogSql.Init();
		if(SwitchSql.Connect(_T("masterdefine"),_T("kj86"),_T("kj86")))
		{
			AfxMessageBox("NetThread:无法连接用户参数数据库,请确定SQL SERVER服务是否运行!");
			return;
		}
		if(AnalogSql.Connect(_T("masterdefine"),_T("kj86"),_T("kj86")))
		{
			AfxMessageBox("NetThread:无法连接用户参数数据库,请确定SQL SERVER服务是否运行!");
			return;
		}
		nRet = m_sql.ExecuteSQL(_T("select unPointNo from uPointProperty"));
		if(nRet != SQL_SUCCESS )
			return;
		int rows = m_sql.GetRowCount();
		CLoadDlg dlg;
		dlg.Create(IDD_DLG_LOADING,GetDesktopWindow());
		dlg.CenterWindow(GetDesktopWindow());
		dlg.ShowWindow(SW_SHOW);
		dlg.m_ProgressCtrl.SetRange(0,rows);
		dlg.m_ProgressCtrl.SetStep(1);
		nRet = m_sql.ExecuteSQL(_T("select * from uPointProperty"));
		if(nRet == SQL_SUCCESS )
		{
			CString str1,str2,str3;
			m_PointMap.InitHashTable(300);
			StructPoint point;
			while(m_sql.Fetch() == SQL_SUCCESS)
			{
				str1 = m_sql.GetCol("unPointNo");
				str2 = m_sql.GetCol("bValueType");
				str3 = m_sql.GetCol("unConnectorID");
				if((str1.GetLength() > 0)&&(str2.GetLength() > 0))
				{
					unsigned short PointNo;///点号
					//if(point == NULL)break;
					memset(&point,0,sizeof(StructPoint));
					PointNo = (unsigned short)atol(str1);
					point.m_StruSimulate.PointNo = PointNo;
					point.m_StruSwitch.PointNo = PointNo;
					point.Type = atoi(str2);
					point.unConnectorID = atoi(str3);
					if((point.Type == 0)||(point.Type == 1))
					{
						if(point.Type == 0)///开关量
						{
							str2.Format("select * from uSwitchPointProperty where (unPointNo = %d)",PointNo);
							nRet = SwitchSql.ExecuteSQL(str2);
							if(nRet != SQL_SUCCESS) 
								continue;
							if(SwitchSql.Fetch() == SQL_SUCCESS)
							{
								str1 = SwitchSql.GetCol("unAC");
								if(str1.GetLength() > 0)
								{
									point.m_StruSwitch.WarnMode = atoi(str1);
								}
							}
							else continue;
						}
						else///模拟量
						{
							str2.Format("select * from uAnologPointProperty where (unPointNo = %d) ",PointNo);
							nRet = AnalogSql.ExecuteSQL(str2);
							if(nRet != SQL_SUCCESS) 
								continue;
							if(AnalogSql.Fetch() == SQL_SUCCESS)
							{
								str1 = AnalogSql.GetCol("fMeasureMin");
								if(str1.GetLength() > 0)
								{
									point.m_StruSimulate.MinValue = atof(str1);
								}
								str1 = AnalogSql.GetCol("fMeasureMax");
								if(str1.GetLength() > 0)
								{
									point.m_StruSimulate.MaxValue = atof(str1);
								}
								str1 = AnalogSql.GetCol("unBitNumber");
								if(str1.GetLength() > 0)
								{
			                 		point.Standard = (unsigned short)pow(2,atoi(str1)+1)-1;
//									point.m_StruSimulate.BitNumber = atol(str1);
								}
								str1 = AnalogSql.GetCol("unWarnMode");
								if(str1.GetLength() > 0)
								{
									point.m_StruSimulate.WarnMode = atoi(str1);
								}
								str1 = AnalogSql.GetCol("unWarnMinValue");
								if(str1.GetLength() > 0)
								{
									point.m_StruSimulate.WarningMinValue = atof(str1);
								}
								str1 = AnalogSql.GetCol("unWarnMaxValue");
								if(str1.GetLength() > 0)
								{
									point.m_StruSimulate.WarningMaxValue = atof(str1);
								}
								str1 = AnalogSql.GetCol("strUnit");
								if(str1.GetLength() > 0)
								{
									_tcscpy(point.m_StruSimulate.StrUnit,str1);
								}
							}
							else continue;
						}
						StructPoint tmp;
						if(m_PointMap.Lookup(PointNo,tmp))///已经有此点号
							continue;
						else m_PointMap.SetAt(PointNo,point);
					}
				}
				dlg.m_ProgressCtrl.StepIt();
			}
		}
		dlg.ShowWindow(SW_HIDE);
		dlg.DestroyWindow();
		AnalogSql.Close();
		SwitchSql.Close();
	}
	catch(CDBException *e)
	{
		e->ReportError();
		return;
	}
}

void CMainFrame::OnFileLoad() 
{
	LoadPointInfo();
}

void CMainFrame::OnMenuEditReport() 
{
	// TODO: Add your command handler code here
	CReport ReportDlg;
	ReportDlg.DoModal();
}

void CMainFrame::OnGraphicProperty() 
{
	// TODO: Add your command handler code here
     CCurveProp	 curveProp;
	 curveProp.DoModal();
}
