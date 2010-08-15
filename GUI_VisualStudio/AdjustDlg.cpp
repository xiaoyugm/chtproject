// AdjustDlg.cpp : implementation file
//

#include "stdafx.h"
#include "GUI_VisualStudio.h"
#include "AdjustDlg.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern ADCbreakE             m_CFeed[65][9][65];
extern ADCbreakE             m_ADCbreakE[65][25][65];
extern  OthersSetting    m_OthersSetting;
extern  SlaveStation             m_SlaveStation[65][25];
/////////////////////////////////////////////////////////////////////////////
// CAdjustDlg dialog


CAdjustDlg::CAdjustDlg(CWnd* pParent /*=NULL*/)
	: CXTResizeDialog(CAdjustDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAdjustDlg)
	m_startDateTime = 0;
	m_start = 0;
	m_end = 0;
//    m_nSecond = 0;
//	chcommand = 0x00;
//	m_nchangev = 0;
//	m_SControlNew = &m_SControl;

	//}}AFX_DATA_INIT
}


void CAdjustDlg::DoDataExchange(CDataExchange* pDX)
{
	CXTResizeDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAdjustDlg)
//	DDX_Text(pDX, IDC_EDIT_SECOND, m_nSecond);
//	DDV_MinMaxUInt(pDX, m_nSecond, 0, 255);
		  DDX_Control(pDX, IDC_CB_A, m_CB_A);
		  DDX_Control(pDX, IDC_CB_C, m_CB_C);
		  DDX_Control(pDX, IDC_CB_F, m_CB_F);
	DDX_Control(pDX, IDC_L_A, m_L_A);
	DDX_Control(pDX, IDC_L_C, m_L_C);
	DDX_Control(pDX, IDC_L_F, m_L_F);
	DDX_Control(pDX, IDC_DT_ADJUST, m_LTime);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAdjustDlg, CXTResizeDialog)
	//{{AFX_MSG_MAP(CAdjustDlg)
//	ON_BN_CLICKED(IDOK_SEND, OnButSend)
//	ON_CBN_SELCHANGE(IDC_COMBO_VERIFYT, OnchangeComboD)
//	ON_BN_CLICKED(IDCANCEL, OnButCancel)
//	ON_BN_CLICKED(IDC_BUT_RES, OnButRES)
	ON_WM_DESTROY()
	ON_NOTIFY(DTN_CLOSEUP, IDC_DT_ADJUST, OnDtimeA)
	ON_CBN_SELCHANGE(IDC_CB_A, OnCB_A)
	ON_CBN_SELCHANGE(IDC_CB_C, OnCB_C)
	ON_CBN_SELCHANGE(IDC_CB_F, OnCB_F)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAdjustDlg message handlers
BOOL CAdjustDlg::OnInitDialog()
{
  CXTResizeDialog::OnInitDialog();
//	CMainFrame* pFWnd=(CMainFrame*)AfxGetMainWnd();
//   	pFWnd->m_pSetTimeDlg=this;
	    SetResize(IDC_L_A,         SZ_TOP_LEFT,    SZ_BOTTOM_CENTER);
    	SetResize(IDC_L_C,         SZ_TOP_CENTER,    SZ_BOTTOM_CENTER);
		SetResize(IDC_L_F,         SZ_TOP_CENTER,    SZ_BOTTOM_RIGHT);
	    SetResize(IDC_CB_A,         SZ_TOP_LEFT,    SZ_TOP_CENTER);
    	SetResize(IDC_CB_C,         SZ_TOP_CENTER,    SZ_TOP_CENTER);
    	SetResize(IDC_CB_F,         SZ_TOP_CENTER,    SZ_TOP_RIGHT);
	    SetResize(IDC_DT_ADJUST,         SZ_BOTTOM_LEFT,    SZ_BOTTOM_CENTER);
    	SetResize(IDOK,         SZ_BOTTOM_CENTER,    SZ_BOTTOM_CENTER);
    	SetResize(IDCANCEL,         SZ_BOTTOM_CENTER,    SZ_BOTTOM_RIGHT);

	// Enable Office XP themes.
	XTThemeManager()->SetTheme(xtThemeOfficeXP);
	HWND hWndHeader = m_L_A.GetDlgItem(0)->GetSafeHwnd();
	m_header.SubclassWindow(hWndHeader);

	// add bitmap images.
//	m_header.SetBitmap(0, IDB_COLUMN_0, FALSE, RGB(0,255,0));
//	m_header.SetBitmap(1, IDB_COLUMN_1, FALSE, RGB(0,255,0));
	//m_header.SetBitmap(2, IDB_COLUMN_2, FALSE, RGB(0,255,0));

	// enable auto sizing.
//	m_header.EnableAutoSize(TRUE);
//	m_header.ResizeColumnsToFit();
	//SortColumn(m_nSortedCol, m_bAscending);

//	m_listCtrl.ModifyExtendedStyle(0, LVS_EX_FULLROWSELECT|LVS_EX_FULLROWSELECT);
	m_L_A.ModifyExtendedStyle(0, LVS_EX_GRIDLINES);
	m_L_C.ModifyExtendedStyle(0, LVS_EX_GRIDLINES);
	m_L_F.ModifyExtendedStyle(0, LVS_EX_GRIDLINES);

		m_L_A.InsertColumn(0,"测点值",LVCFMT_LEFT,60);
		m_L_A.InsertColumn(1,"状态",LVCFMT_LEFT,60);
		m_L_A.InsertColumn(2,"时间|模拟量",LVCFMT_LEFT,160);
		m_L_C.InsertColumn(0,"测点值",LVCFMT_LEFT,70);
		m_L_C.InsertColumn(1,"时间|控制量",LVCFMT_LEFT,160);
		m_L_F.InsertColumn(0,"测点值",LVCFMT_LEFT,70);
		m_L_F.InsertColumn(1,"时间|馈电量",LVCFMT_LEFT,160);

	// insert strings into the size combo box. DeleteString
/*    	m_CB_A.AddString("关闭");

	for(int i = 01; i < 65; i++)
	{
		CString strItem;
		strItem.Format(_T("%d"), i);
	m_FUNCTION.SetCurSel(0);
*/
    CString szConnect = _T("Provider=SQLOLEDB.1;Persist Security Info=True;\
                          User ID=sa;Password=sunset;\
                          Data Source=") +m_OthersSetting.DBname+ _T(";Initial Catalog=BJygjl");

//All calls to the AxLib should be wrapped in a try / catch block
  try
  {
    dbAx::Init();
    m_Cn.Create();
//    m_Cn._SetConnectionEvents(new CCardFileEvents);
    m_Cn.CursorLocation(adUseClient);
    m_Cn.Open((LPCTSTR)szConnect);

	CString strstartTime,strname;
	CString dddd = "Select * From adjustdata WHERE recdate>'";

	UpdateData(TRUE);
	m_LTime.GetTime(m_startDateTime);
	UpdateData(FALSE);
	int eYear,eMonth,eDay,m_cba;
	eYear = m_startDateTime.GetYear();
	eMonth = m_startDateTime.GetMonth();
	eDay = m_startDateTime.GetDay();
	strstartTime.Format("%d-%d-%d 00:00:00",eYear,eMonth,eDay);
	dddd = dddd + strstartTime +"' and recdate<'";
	strstartTime.Format("%d-%d-%d 23:59:59",eYear,eMonth,eDay);
	dddd = dddd + strstartTime +"'";

		m_Adjustdata.Create();
		m_Adjustdata.CursorType(adOpenDynamic);
		m_Adjustdata.CacheSize(50);
		m_Adjustdata._SetRecordsetEvents(new CAccountSetEvents);
		m_Adjustdata.Open(dddd , &m_Cn);
		m_Adjustdata.MarshalOptions(adMarshalModifiedOnly);

		int iItem = 0;
		m_Adjustdata.MoveFirst();
		while ( !m_Adjustdata.IsEOF() )
		{
			eYear = m_Adjustdata.m_szptype;
			if(eYear < 3 )
			{
						m_cba =66;
            	eMonth = m_Adjustdata.m_szfds;
               	eDay = m_Adjustdata.m_szchan;
				strstartTime.Format("%dA%d ",eMonth,eDay);
				strname = m_Adjustdata.m_szName;
				strname.TrimRight();
				dddd = strstartTime + strname;
				if(iItem == 0)
				{
						m_cba =100;
                      	m_CB_A.AddString(dddd);
	        	        m_Records.push_back(dddd );
    		       iItem++;
				}
            	for(iter = m_Records.begin(); iter != m_Records.end(); ++iter)
				{
	           		strstartTime = *iter;
					if(strstartTime == dddd)
					{
						m_cba =100;
						break;
					}
				}
				if(m_cba == 66)
				{
                      	m_CB_A.AddString(dddd);
	        	        m_Records.push_back(dddd );
    		       iItem++;
				}
			}
			m_Adjustdata.MoveNext();
		}
  }
  catch ( dbAx::CAxException *e )
  {
    MessageBox(e->m_szErrorDesc, _T("BJygjl Message"), MB_OK);
    delete e;
    return (FALSE);
  }
  MoveWindow(CRect(50,100,960,700));
  return TRUE;  // return TRUE unless you set the focus to a control
  // EXCEPTION: OCX Property Pages should return FALSE
}

void CAdjustDlg::OnDtimeA(NMHDR* pNMHDR, LRESULT* pResult) 
{
    m_CB_A.ResetContent();
    m_CB_C.ResetContent();
    m_CB_F.ResetContent();
   	m_L_A.DeleteAllItems();
   	m_L_C.DeleteAllItems();
   	m_L_F.DeleteAllItems();

	UpdateData(TRUE);
	m_LTime.GetTime(m_startDateTime);
	UpdateData(FALSE);
	*pResult = 0;

    if ( m_Adjustdata._IsOpen() )
        m_Adjustdata.Close();
	CString strstartTime,strname;
	CString dddd = "Select * From adjustdata WHERE recdate>'";
	int eYear,eMonth,eDay,m_cba;
	eYear = m_startDateTime.GetYear();
	eMonth = m_startDateTime.GetMonth();
	eDay = m_startDateTime.GetDay();
	strstartTime.Format("%d-%d-%d 00:00:00",eYear,eMonth,eDay);
	dddd = dddd + strstartTime +"' and recdate<'";
	strstartTime.Format("%d-%d-%d 23:59:59",eYear,eMonth,eDay);
	dddd = dddd + strstartTime +"'";
		m_Adjustdata.Create();
		m_Adjustdata.CursorType(adOpenDynamic);
		m_Adjustdata.CacheSize(50);
		m_Adjustdata._SetRecordsetEvents(new CAccountSetEvents);
		m_Adjustdata.Open(dddd , &m_Cn);
		m_Adjustdata.MarshalOptions(adMarshalModifiedOnly);

		int iItem = 0;
		m_Records.clear();
		m_Adjustdata.MoveFirst();
		while ( !m_Adjustdata.IsEOF() )
		{
			eYear = m_Adjustdata.m_szptype;
			if(eYear < 3 )
			{
						m_cba =66;
            	eMonth = m_Adjustdata.m_szfds;
               	eDay = m_Adjustdata.m_szchan;
				strstartTime.Format("%dA%d ",eMonth,eDay);
				strname = m_Adjustdata.m_szName;
				strname.TrimRight();
				dddd = strstartTime + strname;
				if(iItem == 0)
				{
						m_cba =100;
                      	m_CB_A.AddString(dddd);
	        	        m_Records.push_back(dddd );
    		       iItem++;
				}
            	for(iter = m_Records.begin(); iter != m_Records.end(); ++iter)
				{
	           		strstartTime = *iter;
					if(strstartTime == dddd)
					{
						m_cba =100;
						break;
					}
				}
				if(m_cba == 66)
				{
                      	m_CB_A.AddString(dddd);
	        	        m_Records.push_back(dddd );
    		       iItem++;
				}
			}
			m_Adjustdata.MoveNext();
		}
}

void CAdjustDlg::OnCB_A() 
{
   	m_L_A.DeleteAllItems();
	int eYear,eMonth,eDay,m_fds,m_chan;
	CString   strname,strstartTime,strfc,dddd;
	UpdateData(TRUE);
	int  kkkk = m_CB_A.GetCurSel();
	m_CB_A.GetLBText(kkkk,strname);
//	UpdateData(FALSE);
		int iItem = 0;
		m_Adjustdata.MoveFirst();
		while ( !m_Adjustdata.IsEOF() )
		{
			eYear = m_Adjustdata.m_szptype;
			if(eYear < 3 )
			{
            	eMonth = m_Adjustdata.m_szfds;
               	eDay = m_Adjustdata.m_szchan;
				strstartTime.Format("%dA%d ",eMonth,eDay);
				strfc = m_Adjustdata.m_szName;
				strfc.TrimRight();
				dddd = strstartTime + strfc;
				if(strname == dddd)
				{
			    strfc.Format("%.2f",m_Adjustdata.m_szAValue);
        		m_L_A.InsertItem(iItem, strfc);
        		m_L_A.SetItemText(iItem, 1, socketClient.strstatus(m_Adjustdata.m_szADStatus));
				  COleDateTime oleDateTime=m_Adjustdata.m_szrecdate;
				  strfc  =   oleDateTime.Format(_T("%Y-%m-%d %H:%M:%S")); 
	    		m_L_A.SetItemText(iItem, 2, strfc);
				m_fds = eMonth;
				m_chan = eDay;
					iItem++;
				}
			}
			m_Adjustdata.MoveNext();
		}
    m_CB_C.ResetContent();
	for(int i=0 ; i< 65 ;i++)
	{
		if(m_ADCbreakE[m_fds][m_chan][i].bFSd == 0)
			break;
            	eMonth = m_ADCbreakE[m_fds][m_chan][i].bFSd;
               	eDay = m_ADCbreakE[m_fds][m_chan][i].bchanel;
       	m_CB_C.AddString(m_ADCbreakE[m_fds][m_chan][i].cpoint+" " +m_SlaveStation[eMonth][eDay+16].WatchName);
	}
}

void CAdjustDlg::OnCB_C() 
{
   	m_L_C.DeleteAllItems();
	int eYear,eMonth,eDay,m_fds,m_chan;
	CString   strname,strstartTime,strfc,dddd;
	UpdateData(TRUE);
	int  kkkk = m_CB_C.GetCurSel();
	m_CB_C.GetLBText(kkkk,strname);
		int iItem = 0;
		m_Adjustdata.MoveFirst();
		while ( !m_Adjustdata.IsEOF() )
		{
			eYear = m_Adjustdata.m_szptype;
			if(eYear == 12 )
			{
            	eMonth = m_Adjustdata.m_szfds;
               	eDay = m_Adjustdata.m_szchan-16;     //1-8
				if(eMonth<10)
					strstartTime.Format("0%dC",eMonth); 
				else
					strstartTime.Format("%d",eMonth); 
				strfc.Format("0%d ",eDay); 

				dddd = m_Adjustdata.m_szName;
				dddd.TrimRight();
				dddd = strstartTime +strfc +dddd;
				if(strname == dddd)
				{
			    strfc.Format("%d",m_Adjustdata.m_szCDValue);
        		m_L_C.InsertItem(iItem, strfc);
				  COleDateTime oleDateTime=m_Adjustdata.m_szrecdate;
				  strfc  =   oleDateTime.Format(_T("%Y-%m-%d %H:%M:%S")); 
	    		m_L_C.SetItemText(iItem, 1, strfc);
				m_fds = eMonth;
				m_chan = eDay;
					iItem++;
				}
			}
			m_Adjustdata.MoveNext();
		}
    m_CB_F.ResetContent();
	for(int i=0 ; i< 65 ;i++)
	{
		if(m_CFeed[m_fds][m_chan][i].bFSd == 0)
			break;
            	eMonth = m_CFeed[m_fds][m_chan][i].bFSd;
               	eDay = m_CFeed[m_fds][m_chan][i].bchanel;
       	m_CB_F.AddString(m_CFeed[m_fds][m_chan][i].adpoint+" " +m_SlaveStation[eMonth][eDay].WatchName);
	}
}

void CAdjustDlg::OnCB_F() 
{
   	m_L_F.DeleteAllItems();
	int eYear,eMonth,eDay;
	CString   strname,strstartTime,strfc,dddd;
	UpdateData(TRUE);
	int  kkkk = m_CB_F.GetCurSel();
	m_CB_F.GetLBText(kkkk,strname);
		int iItem = 0;
		m_Adjustdata.MoveFirst();
		while ( !m_Adjustdata.IsEOF() )
		{
			eYear = m_Adjustdata.m_szptype;
			if(eYear > 3 )
			{
            	eMonth = m_Adjustdata.m_szfds;
               	eDay = m_Adjustdata.m_szchan;    
				if(eMonth<10)
					strstartTime.Format("0%dD",eMonth); 
				else
					strstartTime.Format("%dD",eMonth); 
				if(eDay<10)
					strfc.Format("0%d ",eDay); 
				else
					strfc.Format("%d ",eDay); 

				dddd = m_Adjustdata.m_szName;
				dddd.TrimRight();
				dddd = strstartTime +strfc +dddd;
				if(strname == dddd)
				{
		int dvalue= m_Adjustdata.m_szCDValue;
		if(dvalue == 0)
    		strfc =  m_SlaveStation[eMonth][eDay].ZeroState;
		else if(dvalue == 1)
    		strfc =  m_SlaveStation[eMonth][eDay].OneState;
		else if(dvalue == 2)
    		strfc =  m_SlaveStation[eMonth][eDay].TwoState;
//			    strfc.Format("%d",m_Adjustdata.m_szCDValue);
        		m_L_F.InsertItem(iItem, strfc);
				  COleDateTime oleDateTime=m_Adjustdata.m_szrecdate;
				  strfc  =   oleDateTime.Format(_T("%Y-%m-%d %H:%M:%S")); 
	    		m_L_F.SetItemText(iItem, 1, strfc);
					iItem++;
				}
			}
			m_Adjustdata.MoveNext();
		}
}

BOOL CAdjustDlg::DestroyWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	UpdateData(TRUE);  //0115
//	m_ctrlEndTime.GetTime(m_endDateTime);	
	m_LTime.GetTime(m_startDateTime);
	UpdateData(FALSE);
	OnClose();
	
	return CXTResizeDialog::DestroyWindow();
}

void CAdjustDlg::OnClose()
{
  //Closing of library objects is ensured as each object
  //goes out of scope, but doing a manual shutdown doesn抰 hurt.

  try
  {
    if ( m_Adjustdata._IsOpen() )
      m_Adjustdata.Close();
    m_Cn.Close();
    //Cleanup the AxLib library
    dbAx::Term();
  }
  catch ( CAxException *e )
  {
    MessageBox(e->m_szErrorDesc, _T("BJygjl Message"), MB_OK);
    delete e;
  }
//  CDialog::OnClose();
}
/*
void CAdjustDlg::OnchangeComboD() 
{

}

void CAdjustDlg::OnButSend() 
{

}

void CAdjustDlg::OnButRES() 
{
//		m_nchangev = 0;
	}
}

void CAdjustDlg::OnButRESre()
{
//    GetDlgItem(IDC_BUT_RES)->ShowWindow(SW_HIDE);
}
void CAdjustDlg::OnButCancel() 
{
	if(m_nchangev == 0)
	{
		OnClose();
        EndDialog(IDCANCEL);
	}
	else
        AfxMessageBox("请先点击解除按钮");
}

void CAdjustDlg::ComDisMes(CString strmes)
{
//     	m_listC.DeleteAllItems();
//        m_listC.InsertItem(m_nSecond, strmes);
//		if(chcommand == 0x46)            //风电瓦斯闭锁
//        	m_listC.SetItemText(m_nSecond, 1, strmes);
//		m_nSecond++;
}
*/
