// DCH5m.cpp : implementation file
//

#include "stdafx.h"
#include "gui_visualstudio.h"
#include "DCH5m.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern  SlaveStation             m_SlaveStation[MAX_FDS][MAX_CHAN];
/////////////////////////////////////////////////////////////////////////////
// CDCH5m dialog


CDCH5m::CDCH5m(CWnd* pParent /*=NULL*/)
	: CDialog(CDCH5m::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDCH5m)
	n_select = 0;
	strPOINT="";
	CTimeSpan tpan(10,0,0,0);
	m_startDateTime = CTime::GetCurrentTime()-tpan;
	//}}AFX_DATA_INIT     
}


void CDCH5m::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDCH5m)
		  DDX_Control(pDX, IDC_DCHCB_FDS, m_DCHfds);
		  DDX_Control(pDX, IDC_DCHCB_POINT, m_DCHp);
	DDX_Control(pDX, IDC_LDCH, m_LDCH);
	DDX_Control(pDX, IDC_C_START, m_ctrlStartTime);
	DDX_Control(pDX, IDC_C_END, m_ctrlEndTime);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDCH5m, CDialog)
	//{{AFX_MSG_MAP(CDCH5m)
	ON_CBN_SELCHANGE(IDC_DCHCB_FDS, OnSelchangeDchcbFds)
	ON_CBN_SELCHANGE(IDC_DCHCB_POINT, OnSelchangeDchcbPoint)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_C_START, OnDatetimestart)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_C_END, OnDatetimeend)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDCH5m message handlers
BOOL CDCH5m::OnInitDialog()
{
  CDialog::OnInitDialog();

//	CMainFrame* pFWnd=(CMainFrame*)AfxGetMainWnd();
//   	pFWnd->m_pSetTimeDlg=this;

//	SetResize(IDOK_SEND,                  SZ_BOTTOM_LEFT,   SZ_BOTTOM_LEFT);
//	SetResize(IDCANCEL,              SZ_BOTTOM_LEFT,   SZ_BOTTOM_LEFT);
//	{
//    	SetResize(IDC_LIST_C,         SZ_TOP_LEFT,    SZ_BOTTOM_CENTER);
//    	SetResize(IDC_LIST_C2,         SZ_TOP_CENTER,    SZ_BOTTOM_RIGHT);
//	}
//    	SetResize(IDC_LIST_C,         SZ_TOP_LEFT,    SZ_BOTTOM_RIGHT);

	// Enable Office XP themes.
//	XTThemeManager()->SetTheme(xtThemeOffice2003);

	HWND hWndHeader = m_LDCH.GetDlgItem(0)->GetSafeHwnd();
	m_header.SubclassWindow(hWndHeader);

	// add bitmap images.
//	m_header.SetBitmap(0, IDB_COLUMN_0, FALSE, RGB(0,255,0));
//	m_header.SetBitmap(1, IDB_COLUMN_1, FALSE, RGB(0,255,0));
	//m_header.SetBitmap(2, IDB_COLUMN_2, FALSE, RGB(0,255,0));

	// enable auto sizing.
//	m_header.EnableAutoSize(TRUE);
	m_header.ResizeColumnsToFit();
	//SortColumn(m_nSortedCol, m_bAscending);

//	m_listCtrl.ModifyExtendedStyle(0, LVS_EX_FULLROWSELECT|LVS_EX_FULLROWSELECT);
	m_LDCH.ModifyExtendedStyle(0, LVS_EX_GRIDLINES);
//	m_listC2.ModifyExtendedStyle(0, LVS_EX_GRIDLINES);

	m_ctrlStartTime.SetTime(&m_startDateTime);
		CString strItem,strclm;

	if(n_select == 1 || n_select == 4)
	{
		GetDlgItem(IDC_C_START)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_C_END)->ShowWindow(SW_HIDE);
		GetDlgItem(IDOK)->ShowWindow(SW_HIDE);
		if(n_select == 4)
         	SetWindowText("查询当天数据");
	}
	else
	{
		GetDlgItem(IDC_STADCH1)->SetWindowText("起始时间");
		GetDlgItem(IDC_STADCH2)->SetWindowText("结束时间");
		GetDlgItem(IDC_DCHCB_FDS)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_DCHCB_POINT)->ShowWindow(SW_HIDE);
    	strItem = gstrTimeOut + "\\" + "log\\";
      	if (!m_sdir.SetInitDir(strItem))
		{//\r\n--------------------\r\n
        AfxMessageBox("目录不存在!", MB_OK);
		return 0;
		}
      	m_sdir.m_nFileCount = 0;
      	m_sdir.m_nSubdirCount = 0;
	}
	if(n_select == 2)
	{
         	m_sdir.BeginBrowse("*.ini");
		for ( int i = 0 ; i < m_sdir.m_dirs.size() ; i++ )
		{
			strclm = m_sdir.m_dirs[i];
//    			strclm.Replace(strItem,"");
       		m_LDCH.InsertColumn(0,"操作日志文件名",LVCFMT_LEFT,520);
 				  m_LDCH.InsertItem(i, strclm);
 		}
	    SetWindowText("查询操作日志");
	}
	else if(n_select == 3)
	{
         	m_sdir.BeginBrowse("*.txt");
		for ( int i = 0 ; i < m_sdir.m_dirs.size() ; i++ )
		{
			strclm = m_sdir.m_dirs[i];
//    			strclm.Replace(strItem,"");
       		m_LDCH.InsertColumn(0,"中心站运行日志文件名",LVCFMT_LEFT,520);
 				  m_LDCH.InsertItem(i, strclm);
 		}
       	SetWindowText("查询中心站运行日志");
	}

	if(n_select == 1 || n_select == 4)
	{
	for(int i = 01; i < MAX_FDS; i++)
	{
		strItem.Format(_T("%d"), i);
    	m_DCHfds.AddString(strItem);
	}
	m_DCHfds.SetCurSel(0);

    CString szConnect = _T("Provider=SQLOLEDB.1;Persist Security Info=True;\
                          User ID=sa;Password=sunset;\
                          Data Source=") +strDBname+ _T(";Initial Catalog=BJygjl");

//All calls to the AxLib should be wrapped in a try / catch block
  try
  {
    dbAx::Init();
    m_Cn.Create();
//    m_Cn._SetConnectionEvents(new CCardFileEvents);
    m_Cn.CursorLocation(adUseClient);
    m_Cn.Open((LPCTSTR)szConnect);
    	m_PointDes.Create();
		m_PointDes.CursorType(adOpenDynamic);
		m_PointDes.CacheSize(50);
		m_PointDes._SetRecordsetEvents(new CAccountSetEvents);
		if(n_select == 1)
    		m_PointDes.Open(_T("Select * From pointdescription WHERE fdel=0 and ptype>9"), &m_Cn);
		else
    		m_PointDes.Open(_T("Select * From pointdescription WHERE fdel=0"), &m_Cn);
		m_PointDes.MarshalOptions(adMarshalModifiedOnly);

		CString dddd;
		m_PointDes.MoveFirst();
		while ( !m_PointDes.IsEOF() )
		{
    		dddd = m_PointDes.m_szpointnum;
    		dddd.TrimRight();
			int sfds = m_PointDes.m_szfds;
			int schan = m_PointDes.m_szchan;
			int ptype = m_PointDes.m_szptype;
			if(sfds == 1 && schan != 0)
			{
				dddd += "|" +m_SlaveStation[sfds][schan].WatchName;
	     	    m_DCHp.AddString(dddd);
			}
			m_PointDes.MoveNext();
		}
	     	    m_DCHp.SetCurSel(0);
		m_LDCH.InsertColumn(0,"安装地点/名称",LVCFMT_LEFT,200);
		m_LDCH.InsertColumn(1,"点号",LVCFMT_LEFT,60);
      	int n =strPOINT.Find("A");
		if(n_select == 4 && n != -1)
    		m_LDCH.InsertColumn(2,"测点值",LVCFMT_LEFT,80);
		else
    		m_LDCH.InsertColumn(2,"状态",LVCFMT_LEFT,80);
		m_LDCH.InsertColumn(3,"时间",LVCFMT_LEFT,150);
		if(n_select == 1)//状态变动
		{
    		for(int i = 0; i<theApp.m_RDCHm5.size(); i++)
			{
 				  m_LDCH.InsertItem(i, theApp.m_RDCHm5[i].str1);
    			  m_LDCH.SetItemText(i, 1, theApp.m_RDCHm5[i].str2);
    			  m_LDCH.SetItemText(i, 2, theApp.m_RDCHm5[i].str3);
    			  m_LDCH.SetItemText(i, 3, theApp.m_RDCHm5[i].str4);
			}
		}
		else if(n_select == 4)
		{
			n=0;
    		for(int i = 0; i<theApp.m_RTData.size(); i++)
			{
				dddd = theApp.m_RTData[i].str2;
				strPOINT = strPOINT.Mid(0,5);
				if(strPOINT == dddd)
				{
 				  m_LDCH.InsertItem(n, theApp.m_RTData[i].str1);
    			  m_LDCH.SetItemText(n, 1, dddd);
    			  m_LDCH.SetItemText(n, 2, theApp.m_RTData[i].str3);
    			  m_LDCH.SetItemText(n, 3, theApp.m_RTData[i].str4);
				  n++;
				}
			}
		}
  }
  catch ( dbAx::CAxException *e )
  {
    MessageBox(e->m_szErrorDesc, _T("BJygjl Message"), MB_OK);
    delete e;
    return (FALSE);
  }
	}

  return TRUE;  // return TRUE unless you set the focus to a control
  // EXCEPTION: OCX Property Pages should return FALSE
}

void CDCH5m::OnOK() 
{
	CString strP1;
	int nItemCount=m_LDCH.GetItemCount();
    for(int nItem=0;nItem<nItemCount;nItem++)
	{
		if(m_LDCH.GetItemState(nItem,LVIS_SELECTED) & LVIS_SELECTED)
		{
			strP1=m_LDCH.GetItemText(nItem,0);
					break;
		}
	}
	strP1 = "notepad "+strP1;
	C_Ts.CreateP(NULL, m_Str2Data.CStringtocharp(strP1),5,0x00000001);
//	CDialog::OnOK();
}

void CDCH5m::OnCancel() 
{
	if(n_select == 1 || n_select == 4)
	{
  try
  {
    if ( m_PointDes._IsOpen() )
      m_PointDes.Close();
    m_Cn.Close();

    //Cleanup the AxLib library
    dbAx::Term();
  }
  catch ( CAxException *e )
  {
    MessageBox(e->m_szErrorDesc, _T("BJygjl Message"), MB_OK);
    delete e;
  }
	}
	
	CDialog::OnCancel();
}

void CDCH5m::OnDatetimestart(NMHDR* pNMHDR, LRESULT* pResult) 
{
	UpdateData(TRUE);
	m_ctrlStartTime.GetTime(m_startDateTime);
	UpdateData(FALSE);
	*pResult = 0;
}

void CDCH5m::OnDatetimeend(NMHDR* pNMHDR, LRESULT* pResult) 
{
	UpdateData(TRUE);
	m_ctrlEndTime.GetTime(m_endDateTime);
	UpdateData(FALSE);
	*pResult = 0;
}

void CDCH5m::OnSelchangeDchcbFds() 
{
     	m_LDCH.DeleteAllItems();
	UpdateData(TRUE);
		CString cccc; int nfds3;
    CString strname,dddd;
			UpdateData(TRUE);           //Exchange dialog data
	int  kkkk = m_DCHfds.GetCurSel();
	if(kkkk == -1)
	{
        AfxMessageBox("请选择正确的分站号！");
		return;
	}
	int k=0;
	if(n_select == 1)
	{
		for(int i = 0; i<theApp.m_RDCHm5.size(); i++)
		{
			cccc = theApp.m_RDCHm5[i].str2;
         	cccc = cccc.Mid(0,2);
			nfds3 =m_Str2Data.String2Int(cccc);
			if(nfds3 == (kkkk +1))
			{
				  m_LDCH.InsertItem(k, theApp.m_RDCHm5[i].str1);
    			  m_LDCH.SetItemText(k, 1, theApp.m_RDCHm5[i].str2);
    			  m_LDCH.SetItemText(k, 2, theApp.m_RDCHm5[i].str3);
    			  m_LDCH.SetItemText(k, 3, theApp.m_RDCHm5[i].str4);
				  k++;
			}
		}
	}
	m_DCHp.ResetContent();
		m_PointDes.MoveFirst();
		while ( !m_PointDes.IsEOF() )
		{
    		CString dddd = m_PointDes.m_szpointnum;
    		dddd.TrimRight();
			int sfds = m_PointDes.m_szfds;
			int schan = m_PointDes.m_szchan;
			int ptype = m_PointDes.m_szptype;
			if(sfds == (kkkk +1) && schan != 0)
			{
				dddd += "|" +m_SlaveStation[sfds][schan].WatchName;
	     	    m_DCHp.AddString(dddd);
			}
			m_PointDes.MoveNext();
		}
	    m_DCHp.SetCurSel(0);
		
}

void CDCH5m::OnSelchangeDchcbPoint() 
{
     	m_LDCH.DeleteAllItems();
	UpdateData(TRUE);
		CString cccc; int nfds3;
    CString strname,dddd;
			UpdateData(TRUE);           //Exchange dialog data
	int  kkkk = m_DCHp.GetCurSel();
	if(kkkk == -1)
	{
        AfxMessageBox("请选择正确的点号！");
		return;
	}
	m_DCHp.GetLBText(kkkk,strname);
	strname = strname.Mid(0,5);
	kkkk =0;
	if(n_select == 1)
	{
		for(int i = 0; i<theApp.m_RDCHm5.size(); i++)
		{
			cccc = theApp.m_RDCHm5[i].str2;
			if(strname == cccc)
			{
				  m_LDCH.InsertItem(kkkk, theApp.m_RDCHm5[i].str1);
    			  m_LDCH.SetItemText(kkkk, 1, theApp.m_RDCHm5[i].str2);
    			  m_LDCH.SetItemText(kkkk, 2, theApp.m_RDCHm5[i].str3);
    			  m_LDCH.SetItemText(kkkk, 3, theApp.m_RDCHm5[i].str4);
				  kkkk++;
			}
		}
	}
		else if(n_select == 4)
		{
			int n=0;
    		for(int i = 0; i<theApp.m_RTData.size(); i++)
			{
				dddd = theApp.m_RTData[i].str2;
				if(strname == dddd)
				{
 				  m_LDCH.InsertItem(n, theApp.m_RTData[i].str1);
    			  m_LDCH.SetItemText(n, 1, dddd);
    			  m_LDCH.SetItemText(n, 2, theApp.m_RTData[i].str3);
    			  m_LDCH.SetItemText(n, 3, theApp.m_RTData[i].str4);
				  n++;
				}
			}
		}
}
