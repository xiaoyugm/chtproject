// LoginDlg.cpp : implementation file
//

#include "stdafx.h"
#include "GUI_VisualStudio.h"
#include "LoginDlg.h"

#include "MainFrm.h"
//#include "SQL\\String2DataType.h"
//#include "BackupSettingDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//登陆成功判断
static BOOL bIsLoggin = FALSE;
extern ADMainDis         m_ADMainDis[MAX_FDS][MAX_CHAN];          //调用显示
extern SlaveStation             m_SlaveStation[MAX_FDS][MAX_CHAN];
extern  OthersSetting    m_OthersSetting;
/////////////////////////////////////////////////////////////////////////////
// CLoginDlg dialog


CLoginDlg::CLoginDlg(CWnd* pParent /*=NULL*/)
: CXTResizeDialog(CLoginDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLoginDlg)
	m_strPasswd = _T("");
	m_strUser = _T("");
	m_strdism = _T("");
//	m_strEditStatus = _T("");
	m_SLoginNew = &m_SLogin;

	//}}AFX_DATA_INIT
	m_bAddUser=0;
	nrecord = 0;
}

void CLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CXTResizeDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLoginDlg)
//	DDX_Control(pDX, IDC_CHECK_MANACHINE, m_CheckManachine);
	DDX_Text(pDX, IDC_EDT_USER, m_strUser);
	DDV_MaxChars(pDX, m_strUser, 10);
	DDX_Text(pDX, IDC_EDT_PWD, m_strPasswd);
	DDV_MaxChars(pDX, m_strUser, 8);
	DDX_Control(pDX, IDOK, m_btnOK);
//	DDX_Control(pDX, IDCANCEL, m_btnCANCEL);
//	DDX_Text(pDX, IDC_EDIT_SATUS, m_strEditStatus);
	DDX_Control(pDX, IDC_EDT_PWD, m_ctrlEditPWD);
	DDX_Control(pDX, IDC_LIST_USER, m_listUser);
	DDX_Control(pDX, IDC_COMBLOG, m_ComBoxSM);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CLoginDlg, CXTResizeDialog)
//{{AFX_MSG_MAP(CLoginDlg)
	ON_CBN_SELCHANGE(IDC_COMBLOG, OnchangeComboSM)
	ON_BN_CLICKED(IDC_BUTADD, AddODUser)
	ON_BN_CLICKED(ID_DELUSER, DelUser)
    ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_USER, OnItemChangedList)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLoginDlg message handlers

void CLoginDlg::OnOK() 
{
	// TODO: Add extra validation here
	CString strSQL,strtemp;
	UpdateData(TRUE);

	if(!theApp.m_bLogIn)
	{
    	if (m_strUser =="" && m_strPasswd =="") 
		{ 
               	theApp.m_bLogIn=false;
             	theApp.curuser = "";
//		AfxMessageBox("对不起，用户名或密码不能为空，请重新输入！");
//		CWnd* pWnd=GetDlgItem(IDC_EDT_USER);
//		pWnd->SetFocus();
//		return;
		}  
    	else 
		{
    		if ( m_SLogin._IsEmpty() )
			{
					m_SLoginNew->m_szUID = 1;
					m_SLoginNew->m_szName = m_strUser;
					m_SLoginNew->m_szupwd = m_strPasswd;
					m_SLoginNew->m_szclasser = 1;
      						m_SLoginNew->AddNew();  //Add a new, blank record
					   	    m_SLoginNew->Update();    //Update the recordset
						    m_SLoginNew->Requery();
               	theApp.m_bLogIn=true;
             	theApp.curuser = m_strUser;
				theApp.m_bsuper = true;

			}
	    	else
			{
         		m_SLogin.MoveFirst();
          		while ( !m_SLogin.IsEOF() )
				{
					strtemp = m_SLogin.m_szName;
					strtemp.TrimRight();
					if(strtemp == m_strUser)
					{
			       		strtemp = m_SLogin.m_szupwd;
		    			strtemp.TrimRight();
						if(strtemp == m_strPasswd)
						{
                        	theApp.m_bLogIn=true;
                           	theApp.curuser = m_strUser;
							if(m_SLogin.m_szclasser == 1)
								theApp.m_bsuper = true;
							else
								theApp.m_bsuper = false;
           					if("主机" == m_strUser)
								theApp.b_SaveRT = TRUE;
							break;
						}
					}
					else
                    	theApp.m_bLogIn=false;
        			m_SLogin.MoveNext();
				}
				if(theApp.m_bLogIn == false)
				{
					AfxMessageBox("用户名或密码错误，请重新输入！",MB_ICONINFORMATION);
            		return;
				}
			}
				//登陆成功判断
						bIsLoggin = TRUE;

//					AfxMessageBox("正常退出，谢谢您使用Robustech监控系统，再见",MB_ICONINFORMATION);
		}
	}
	else if(m_bAddUser && theApp.m_bsuper)
	{
		int nuid =0;
         		m_SLogin.MoveFirst();
          		while ( !m_SLogin.IsEOF() )
				{
					nrecord = m_SLogin.m_szUID;
			       	strtemp = m_SLogin.m_szName;
		    		strtemp.TrimRight();
					if(strtemp == m_strUser)
						nuid =1;
        			m_SLogin.MoveNext();
				}
				if(nuid == 1)
				{
					AfxMessageBox("该用户名存在，请重新输入！");
					m_strUser.Empty();
					m_strPasswd.Empty();
					return;
				}
 					m_SLoginNew->m_szUID = nrecord+1;
					m_SLoginNew->m_szName = m_strUser;
					m_SLoginNew->m_szupwd = m_strPasswd;
					m_SLoginNew->m_szclasser = 2;
      						m_SLoginNew->AddNew();  //Add a new, blank record
					   	    m_SLoginNew->Update();    //Update the recordset
						    m_SLoginNew->Requery();
	}
	else if(theApp.m_bLogIn)
	{
				theApp.b_SaveRT = FALSE;
				theApp.m_bsuper = false;
               	theApp.m_bLogIn=false;
             	theApp.curuser = "";
	}

    CMainFrame* pFWnd=(CMainFrame*)AfxGetMainWnd();
	pFWnd->AddUser();
        if ( m_PointDes._IsOpen() )
            m_PointDes.Close();
    if ( m_SLogin._IsOpen() )
      m_SLogin.Close();
    m_Cn.Close();
    dbAx::Term();
	CDialog::OnOK();
}

void CLoginDlg::OnCancel() 
{
//	if(m_strdism != "OnDRIVERE")
	{
        if ( m_PointDes._IsOpen() )
            m_PointDes.Close();
        if ( m_SLogin._IsOpen() )
            m_SLogin.Close();
        m_Cn.Close();
        dbAx::Term();
	}
	CDialog::OnCancel();
}

BOOL CLoginDlg::OnInitDialog() 
{
	CXTResizeDialog::OnInitDialog();
	
	int screenx=GetSystemMetrics (SM_CXSCREEN);
	int screeny=GetSystemMetrics (SM_CYSCREEN);
//	if(m_strdism != "OnDRIVERE")
    	ConnectDB();  //连接数据库
	m_listUser.ModifyExtendedStyle(0, LVS_EX_FULLROWSELECT|LVS_SHOWSELALWAYS | LVS_EX_GRIDLINES);
	SetResize(IDC_LIST_USER,         SZ_TOP_LEFT,    SZ_BOTTOM_RIGHT);

	if(m_strdism == "login")
	{
         		GetDlgItem(IDC_EDT_USER)->SetFocus();
    	GetDlgItem(IDC_COMBLOG)->ShowWindow(SW_HIDE);
			m_listUser.InsertColumn(0,"用户",LVCFMT_LEFT,100);
			m_listUser.InsertColumn(1,_T("等级"),LVCFMT_LEFT,100);
			if(theApp.m_bLogIn)
			{
				if(theApp.m_bsuper)
				{
    				SetWindowText(_T("注销/添加/删除用户"));
				}
				else
				{
        			GetDlgItem(IDC_LIST_USER)->ShowWindow(SW_HIDE);
        			GetDlgItem(ID_DELUSER)->ShowWindow(SW_HIDE);
        			GetDlgItem(IDC_BUTADD)->ShowWindow(SW_HIDE);
    				SetWindowText(_T("注销用户"));
				}
    			GetDlgItem(IDOK)->SetWindowText(_T("注销"));
    			GetDlgItem(IDC_EDT_USER)->ShowWindow(SW_HIDE);
    			GetDlgItem(IDC_EDT_PWD)->ShowWindow(SW_HIDE);
    			GetDlgItem(IDC_STATICL1)->ShowWindow(SW_HIDE);
    			GetDlgItem(IDC_STATICL2)->ShowWindow(SW_HIDE);
    			GetDlgItem(IDCANCEL)->ShowWindow(SW_HIDE);

				CString dddd;
				int iItem = 0;
         				m_SLogin.MoveFirst();
          				while ( !m_SLogin.IsEOF() )
						{
							if(m_SLoginNew->m_szclasser != 1)
							{
			    			  m_listUser.InsertItem(iItem, m_SLogin.m_szName);
//					    	  if(m_SLoginNew->m_szclasser == 1)
//							  dddd = "超级用户";
//					    	  else
							  dddd = "操作员";
				    		  m_listUser.SetItemText(iItem, 1, dddd);
					    	  iItem++;
							}
        					m_SLogin.MoveNext();
						}
			}
			else
			{
    			GetDlgItem(IDC_LIST_USER)->ShowWindow(SW_HIDE);
    			GetDlgItem(ID_DELUSER)->ShowWindow(SW_HIDE);
    			GetDlgItem(IDC_BUTADD)->ShowWindow(SW_HIDE);
         		GetDlgItem(IDC_EDT_USER)->SetFocus();
			}
	}
	else
	{
    			GetDlgItem(IDC_EDT_USER)->ShowWindow(SW_HIDE);
    			GetDlgItem(IDC_EDT_PWD)->ShowWindow(SW_HIDE);
    			GetDlgItem(IDC_STATICL1)->ShowWindow(SW_HIDE);
    			GetDlgItem(IDC_STATICL2)->ShowWindow(SW_HIDE);
    			GetDlgItem(ID_DELUSER)->ShowWindow(SW_HIDE);
    			GetDlgItem(IDC_BUTADD)->ShowWindow(SW_HIDE);
    			GetDlgItem(IDOK)->ShowWindow(SW_HIDE);
    	MoveWindow(CRect(50,100,960,300));
	}
	if(m_strdism == "OnSDisA")
	{
    		SetWindowText(_T("模拟量调用显示"));
			m_listUser.InsertColumn(0,"安装地点/名称",LVCFMT_LEFT,150);
//			m_listUser.InsertColumn(1,_T("单位"),LVCFMT_LEFT,40);
//			m_listUser.InsertColumn(2,"报警值",LVCFMT_LEFT,60);
//			m_listUser.InsertColumn(3,_T("断电值"),LVCFMT_LEFT,60);
//			m_listUser.InsertColumn(4,"复电值",LVCFMT_LEFT,60);
			m_listUser.InsertColumn(1,_T("监测值"),LVCFMT_LEFT,60);
			m_listUser.InsertColumn(2,"最近最大值",LVCFMT_LEFT,80);
			m_listUser.InsertColumn(3,_T("平均值"),LVCFMT_LEFT,60);
			m_listUser.InsertColumn(4,"最后报警时刻",LVCFMT_LEFT,150);
//			m_listUser.InsertColumn(5,_T("最后正常时刻"),LVCFMT_LEFT,120);
			m_listUser.InsertColumn(5,"最后断电时刻",LVCFMT_LEFT,150);
			m_listUser.InsertColumn(6,_T("最后复电(正常)时刻"),LVCFMT_LEFT,150);

     	CString strstartTime,strname,dddd;
//    	int eYear;
		int iItem = 0;
		m_PointDes.MoveFirst();
		while ( !m_PointDes.IsEOF() )
		{
//			eYear = m_PointDes.m_szptype;
//			if((eYear < 3) || (eYear > 12)||(eYear == 10))
			{
             		int nfds = m_PointDes.m_szfds;
              		int nchan = m_PointDes.m_szchan;
				strname = m_SlaveStation[nfds][nchan].WatchName;
				strstartTime = m_PointDes.m_szpointnum;
				strstartTime.TrimRight();
				dddd = strstartTime + strname;
               	m_ComBoxSM.AddString(dddd);
   		       iItem++;
			}
			m_PointDes.MoveNext();
		}
	}
	else if(m_strdism == "OnSDisD")
	{
    		SetWindowText(_T("开关量调用显示"));
			m_listUser.InsertColumn(0,"安装地点/名称",LVCFMT_LEFT,150);
			m_listUser.InsertColumn(1,_T("设备状态"),LVCFMT_LEFT,90);
			m_listUser.InsertColumn(2,"时刻",LVCFMT_LEFT,150);
			m_listUser.InsertColumn(3,"报警时刻",LVCFMT_LEFT,150);
			m_listUser.InsertColumn(4,"断电时刻",LVCFMT_LEFT,150);
			m_listUser.InsertColumn(5,_T("馈电状态/时刻"),LVCFMT_LEFT,190);
			m_listUser.InsertColumn(6,_T("措施/时刻"),LVCFMT_LEFT,300);

     	CString strstartTime,strname,dddd;
		int iItem = 0;
		m_PointDes.MoveFirst();
		while ( !m_PointDes.IsEOF() )
		{
             		int nfds = m_PointDes.m_szfds;
              		int nchan = m_PointDes.m_szchan;
				strname = m_SlaveStation[nfds][nchan].WatchName;
				strstartTime = m_PointDes.m_szpointnum;
				strstartTime.TrimRight();
				if(strstartTime.Find("D") != -1)
				{
		     		dddd = strstartTime + strname;
                	m_ComBoxSM.AddString(dddd);
   		            iItem++;
				}
			m_PointDes.MoveNext();
		}
	}
	if(m_strdism == "OnDRIVERE")
	{
       	m_listUser.DeleteAllItems();
    	GetDlgItem(IDC_COMBLOG)->ShowWindow(SW_HIDE);;
    		SetWindowText(_T("设备故障显示"));
			m_listUser.InsertColumn(0,"安装地点/名称",LVCFMT_LEFT,200);
			m_listUser.InsertColumn(1,_T("故障状态"),LVCFMT_LEFT,80);
			m_listUser.InsertColumn(2,"开始时间",LVCFMT_LEFT,150);
			m_listUser.InsertColumn(3,_T("措施"),LVCFMT_LEFT,100);
			m_listUser.InsertColumn(4,"措施时刻",LVCFMT_LEFT,150);

		int iItem = 0;
		CString strtemp,strtemp1;
		for (int i = 1; i < MAX_FDS;i++)
		{
			for(int j = 1; j < MAX_CHAN;j++ )
			{
				strtemp1 = m_SlaveStation[i][j].WatchName;
				if(strtemp1 !="")
				{
					int n_ptype = m_SlaveStation[i][j].ptype;
    				unsigned char m_state=m_SlaveStation[i][j].Channel_state;
    				if(m_state > 63 && m_state !=255)
					{
						if((n_ptype > 3 && m_state >111) || n_ptype <3)
						{
      	        	      m_listUser.InsertItem(iItem, m_SlaveStation[i][j].WatchName);
//      	    	      m_listUser.SetItemText(iItem,0, m_SlaveStation[i][j].WatchName);
				  	  strtemp = theApp.socketClient.strstatus(m_state);
            		  m_listUser.SetItemText(iItem, 1, strtemp);
				      COleDateTime o=m_SlaveStation[i][j].ValueTime;
  	    			  strtemp = o.Format(_T("%Y-%m-%d %H:%M:%S")); 
             		  m_listUser.SetItemText(iItem, 2, strtemp);
					  strtemp1 = m_SlaveStation[i][j].strSafe;
				     	  if(strtemp1 != ""){
                  		  m_listUser.SetItemText(iItem, 3, strtemp1);
                		  m_listUser.SetItemText(iItem, 4, strtemp);
						  }
				     	  iItem++;
						}
					}//if
				}
			}//j
		}//i

	}
//		CWnd* pWnd=GetDlgItem(IDC_EDT_USER);
//		pWnd->SetFocus();
//	UpdateData(TRUE);

	// TODO: Add extra initialization here
//	m_btnOK.SetThemeHelper(&m_ThemeHelper);
//	m_btnOK.SetIcon(IDI_ICON_OK);
//	m_btnOK.SetTooltipText(_T("欢迎登录Robustech监控系统，与密码有关的问题请与管理员联系"));
//	m_btnCANCEL.SetThemeHelper(&m_ThemeHelper);
//	m_btnCANCEL.SetIcon(IDI_ICON_CANCEL,IDI_ICON_CANCEL01);
//	m_btnCANCEL.SetTooltipText(_T("停止登录，退出系统，与密码有关的问题请与管理员联系"));
//		m_strEditStatus="您正在登录进入系统，请输入用户名和密码后点击确定";
		//退出时不显示主备选择CheckBox
//		m_CheckManachine.EnableWindow(FALSE);  
//		m_strEditStatus="您正在登录退出系统，请输入密码后点击确定";
	//	CWnd* pWnd=GetDlgItem(IDC_EDT_PWD);
	//	pWnd->SetFocus();
	//	m_ctrlEditPWD.SetSel(0,-1,FALSE);
	
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CLoginDlg::ConnectDB()
{
  CString szConnect = _T("Provider=SQLOLEDB.1;Persist Security Info=True;\
                          User ID=sa;Password=sunset;\
                          Data Source=") +m_OthersSetting.DBname+ _T(";Initial Catalog=BJygjl");
	try
	{
       dbAx::Init();
       m_Cn.Create();
//       m_Cn._SetConnectionEvents(new CCardFileEvents);
       m_Cn.CursorLocation(adUseClient);
       m_Cn.Open((LPCTSTR)szConnect);

		m_SLogin.Create();
		m_SLogin.CursorType(adOpenDynamic);
		m_SLogin.CacheSize(50);
//		m_SLogin._SetRecordsetEvents(new CAccountSetEvents);
		m_SLogin.Open(_T("Select * From ygjluser"), &m_Cn);
		m_SLogin.MarshalOptions(adMarshalModifiedOnly);

		m_PointDes.Create();
		m_PointDes.CursorType(adOpenDynamic);
		m_PointDes.CacheSize(50);
//		m_PointDes._SetRecordsetEvents(new CAccountSetEvents);
     	if(m_strdism == "OnSDisA")
			szConnect = "Select * From pointdescription WHERE fdel=0 and ptype<3";
		else if(m_strdism == "OnSDisD")
			szConnect = "Select * From pointdescription WHERE fdel=0 and ptype>3";
		else 
			szConnect = "Select * From pointdescription WHERE fdel=0 and ptype<3";
       	m_PointDes.Open(szConnect, &m_Cn);
		m_PointDes.MarshalOptions(adMarshalModifiedOnly);
	}
    catch ( dbAx::CAxException *e )
	{
    MessageBox(e->m_szErrorDesc, _T("BJygjl Message"), MB_OK);
    delete e;
    return ;
	}
}

void CLoginDlg::AddODUser()
{
//	UpdateData();
		SetWindowText(_T("添加用户"));
    	GetDlgItem(IDOK)->SetWindowText(_T("确定"));
		m_bAddUser = 1;
    	GetDlgItem(IDC_EDT_USER)->ShowWindow(SW_SHOW);
    	GetDlgItem(IDC_EDT_PWD)->ShowWindow(SW_SHOW);
    	GetDlgItem(IDC_STATICL1)->ShowWindow(SW_SHOW);
    	GetDlgItem(IDC_STATICL2)->ShowWindow(SW_SHOW);
    	GetDlgItem(IDC_BUTADD)->ShowWindow(SW_HIDE);
    	GetDlgItem(ID_DELUSER)->ShowWindow(SW_HIDE);
    	GetDlgItem(IDC_LIST_USER)->ShowWindow(SW_HIDE);
    	GetDlgItem(IDCANCEL)->ShowWindow(SW_SHOW);
}

void CLoginDlg::OnItemChangedList(NMHDR *pNMHDR, LRESULT *pResult)
{
    LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);

    *pResult = 0;

    if(m_strdism == "OnSDisA"||m_strdism == "OnSDisD"||m_strdism == "OnDRIVERE")
    {
    }
    else
	{
      if ( pNMLV->uNewState == 3 )
	  {
          if(!m_SLogin._IsEmpty() )
           m_SLogin.AbsolutePosition(pNMLV->iItem + 2);  //1 超级用户隐藏
	  }
	}
}

void CLoginDlg::DelUser()
{
	bool isselect = false;
	int nItemCount=m_listUser.GetItemCount();
    for(int nItem=0;nItem<nItemCount;nItem++)
	{
		if(m_listUser.GetItemState(nItem,LVIS_SELECTED) & LVIS_SELECTED)
		{
    		isselect = true;
			m_listUser.DeleteItem(nItem);
			break;
		}
		else
    		isselect = false;
	}
	if(!isselect)
		return;
	m_SLogin.Delete();

    m_listUser.DeleteAllItems();
          m_listUser.DeleteColumn(1);
          m_listUser.DeleteColumn(0);
        if ( m_PointDes._IsOpen() )
            m_PointDes.Close();
    if ( m_SLogin._IsOpen() )
      m_SLogin.Close();
    m_Cn.Close();
    dbAx::Term();
	OnInitDialog();
}

void CLoginDlg::OnchangeComboSM() 
{
	CString strname, strf,strc;
	UpdateData(TRUE);           //Exchange dialog data
	int  kkkk = m_ComBoxSM.GetCurSel();
	if(kkkk == -1 )
		return;
	m_listUser.DeleteAllItems();
	m_ComBoxSM.GetLBText(kkkk,strname);
	strname = strname.Mid(0,5);
    		strf = strname.Mid(0,2);
    		strc = strname.Mid(3);
		int afds = m_Str2Data.String2Int(strf);
		int achan = m_Str2Data.String2Int(strc);
	if(m_strdism == "OnSDisA")
	{
		  m_listUser.InsertItem(0, m_SlaveStation[afds][achan].WatchName);
			strname.Format(_T("%.2f"), m_SlaveStation[afds][achan].AValue);
   		  m_listUser.SetItemText(0, 1, strname);
			strname.Format(_T("%.2f"), m_ADMainDis[afds][achan].AMaxValue);
		  m_listUser.SetItemText(0, 2, strname);
		  int n_meant = m_ADMainDis[afds][achan].m_ATotalnum;
		  if(n_meant == 0)
			strname ="0.00";
		  else
			strname.Format(_T("%.2f"), m_ADMainDis[afds][achan].ATotalV/n_meant);
		  m_listUser.SetItemText(0, 3, strname);
				  COleDateTime oleDateTime=m_ADMainDis[afds][achan].ATime;
				  if(oleDateTime.GetYear() != 1900)
     				  strname   =   oleDateTime.Format(_T("%Y-%m-%d %H:%M:%S")); 
				  else
					  strname = "";
		  m_listUser.SetItemText(0, 4, strname);
				   oleDateTime=m_ADMainDis[afds][achan].BTime;
				  if(oleDateTime.GetYear() != 1900)
     				  strname   =   oleDateTime.Format(_T("%Y-%m-%d %H:%M:%S")); 
				  else
					  strname = "";
		  m_listUser.SetItemText(0, 5, strname);
				   oleDateTime=m_ADMainDis[afds][achan].NTime;
				  if(oleDateTime.GetYear() != 1900)
     				  strname   =   oleDateTime.Format(_T("%Y-%m-%d %H:%M:%S")); 
				  else
					  strname = "";
		  m_listUser.SetItemText(0, 6, strname);
	}
	else if(m_strdism == "OnSDisD")
	{
		  strname = "";
		  m_listUser.InsertItem(0, m_SlaveStation[afds][achan].WatchName);
					  int nstatus = m_SlaveStation[afds][achan].CValue;
					  if(nstatus == 0)
						  strname= m_SlaveStation[afds][achan].ZeroState;
					  else if(nstatus == 1)
						  strname= m_SlaveStation[afds][achan].OneState;
					  else if(nstatus == 2)
						  strname= m_SlaveStation[afds][achan].TwoState;
   		  m_listUser.SetItemText(0, 1, strname);
				  COleDateTime oleDateTime=m_SlaveStation[afds][achan].ValueTime;
				  if(oleDateTime.GetYear() != 1900)
     				  strname   =   oleDateTime.Format(_T("%Y-%m-%d %H:%M:%S")); 
				  else
					  strname = "";
		  m_listUser.SetItemText(0, 2, strname);
				   oleDateTime=m_ADMainDis[afds][achan].ATime;
				  if(oleDateTime.GetYear() != 1900)
     				  strname   =   oleDateTime.Format(_T("%Y-%m-%d %H:%M:%S")); 
				  else
					  strname = "";
		  m_listUser.SetItemText(0, 3, strname);
				   oleDateTime=m_ADMainDis[afds][achan].BTime;
				  if(oleDateTime.GetYear() != 1900)
     				  strname   =   oleDateTime.Format(_T("%Y-%m-%d %H:%M:%S")); 
				  else
					  strname = "";
		  m_listUser.SetItemText(0, 4, strname);
				   oleDateTime=m_ADMainDis[afds][achan].RTime; //馈电状态/时刻
				  if(oleDateTime.GetYear() != 1900)
     				  strname   =   oleDateTime.Format(_T("%Y-%m-%d %H:%M:%S")); 
				  else
					  strname = "";
		  m_listUser.SetItemText(0, 5, m_SlaveStation[afds][achan].FeedState+"|"+strname);
				   oleDateTime=m_ADMainDis[afds][achan].NTime;  //措施/时刻
				  if(oleDateTime.GetYear() != 1900)
     				  strname   =   oleDateTime.Format(_T("%Y-%m-%d %H:%M:%S")); 
				  else
					  strname = "";
		  m_listUser.SetItemText(0, 6, m_SlaveStation[afds][achan].strSafe+"|"+strname);
	}

}

