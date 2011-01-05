// DCH5m.cpp : implementation file
//

#include "stdafx.h"
#include "gui_visualstudio.h"
#include "DCH5m.h"
#include "MainFrm.h"

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
	m_success = 0;
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

	CMainFrame* pFWnd=(CMainFrame*)AfxGetMainWnd();
   	pFWnd->m_pDCH5m=this;

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
       		m_LDCH.InsertColumn(0,"操作日志文件名",LVCFMT_LEFT,520);
		for ( int i = 0 ; i < m_sdir.m_dirs.size() ; i++ )
		{
			strclm = m_sdir.m_dirs[i];
//    			strclm.Replace(strItem,"");
 				  m_LDCH.InsertItem(i, strclm);
 		}
	    SetWindowText("查询操作日志");
	}
	else if(n_select == 3)
	{
         	m_sdir.BeginBrowse("*.txt");
       		m_LDCH.InsertColumn(0,"中心站运行日志文件名",LVCFMT_LEFT,520);
		for ( int i = 0 ; i < m_sdir.m_dirs.size() ; i++ )
		{
			strclm = m_sdir.m_dirs[i];
//    			strclm.Replace(strItem,"");
 				  m_LDCH.InsertItem(i, strclm);
 		}
       	SetWindowText("查询中心站运行日志");
	}
	else if(n_select == 5)
	{
		m_LDCH.DeleteColumn(0);
       		m_LDCH.InsertColumn(0,"操作日志文件名",LVCFMT_LEFT,520);
				for(int k=0; k< theApp.m_DebugInfo.size(); k++)
				{
					strclm = theApp.m_DebugInfo[k];
 				  m_LDCH.InsertItem(k, strclm);
				}
	}

	if(n_select == 1 || n_select == 4)
	{
    	for(int i = 01; i < MAX_FDS; i++)
		{
		strItem.Format(_T("%d"), i);
    	m_DCHfds.AddString(strItem);
		}
    	m_DCHfds.SetCurSel(0);

	CString dddd;	int eYear;	
	if(n_select == 1)
	{
			for(int j = 0; j < MAX_CHAN;j++ )
			{
       			eYear = m_SlaveStation[1][j].ptype;
       			if(eYear >9 && m_SlaveStation[1][j].WatchName !="")
				{
    				dddd = m_SlaveStation[1][j].strPN + "|"+m_SlaveStation[1][j].WatchName;
    	     	    m_DCHp.AddString(dddd);
				}
			}
	}
	else if(n_select == 4)
	{
			for(int j = 0; j < MAX_CHAN;j++ )
			{
       			if(m_SlaveStation[1][j].WatchName !="")
				{
    				dddd = m_SlaveStation[1][j].strPN + "|"+m_SlaveStation[1][j].WatchName;
    	     	    m_DCHp.AddString(dddd);
				}
			}
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
            pFWnd->m_ThreadPool.Add(new CThreadObject(*this, 2));
//			DCH5mInitList();
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
	C_Ts.CreateP(NULL, theApp.m_Str2Data.CStringtocharp(strP1),5,0x00000001);
//	CDialog::OnOK();
}

void CDCH5m::OnCancel() 
{
	if(m_success ==11)
		return;
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
			nfds3 =theApp.m_Str2Data.String2Int(cccc);
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
			for(int j = 0; j < MAX_CHAN;j++ )
			{
       			if(m_SlaveStation[kkkk +1][j].WatchName !="")
				{
    				dddd = m_SlaveStation[kkkk +1][j].strPN + "|"+m_SlaveStation[kkkk +1][j].WatchName;
    	     	    m_DCHp.AddString(dddd);
				}
			}
	    m_DCHp.SetCurSel(0);
		
}

void CDCH5m::OnSelchangeDchcbPoint() 
{
     	m_LDCH.DeleteAllItems();
	UpdateData(TRUE);
		CString cccc; 
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
			strPOINT =strname;
          	CMainFrame* pFWnd=(CMainFrame*)AfxGetMainWnd();
            pFWnd->m_ThreadPool.Add(new CThreadObject(*this, 2));
		}
}

void CDCH5m::DCH5mInitList()
{
	m_success =11;
        	CString strf,strc,dddd; int n;
		    strf = strPOINT.Mid(0,2);
    		strc = strPOINT.Mid(3,2);
    		int nfds = theApp.m_Str2Data.String2Int(strf);
     		int nchan = theApp.m_Str2Data.String2Int(strc);
        	n =strPOINT.Find("C");
			if(n>0)
				nchan += 16;
			n=0;

			CppSQLite3Query q; //int m_fds,m_chan;
    		dddd.Format("select * from rtdata where RTfds=%d and RTchan=%d;",nfds,nchan);
            q = theApp.db3m.execQuery(dddd);
            while (!q.eof())
			{
//    			   m_fds = q.getIntField(0);
//                   m_chan = q.getIntField(1);
//				if(nfds == m_fds && nchan == m_chan)
				{
    				  m_LDCH.InsertItem(n, m_SlaveStation[nfds][nchan].WatchName);
        			  m_LDCH.SetItemText(n, 1, m_SlaveStation[nfds][nchan].strPN);
        			  m_LDCH.SetItemText(n, 2, q.getStringField(2));
    	    		  m_LDCH.SetItemText(n, 3, q.getStringField(3));
			    	  n++;
				}
                q.nextRow();
			}
			//caohaitao
#ifdef _DEBUG
			strf.Format("%d  hang",n);
			theApp.m_DebugInfo.push_back(strf);
#endif //_DEBUG
     		q.finalize();
	m_success =0;
}