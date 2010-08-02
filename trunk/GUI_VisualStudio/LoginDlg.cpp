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
	DDX_Control(pDX, IDC_EDT_PWD, m_ctrlEditPWD);
	DDX_Control(pDX, IDOK, m_btnOK);
//	DDX_Control(pDX, IDCANCEL, m_btnCANCEL);
	DDX_Text(pDX, IDC_EDT_PWD, m_strPasswd);
	DDX_Text(pDX, IDC_EDT_USER, m_strUser);
//	DDX_Text(pDX, IDC_EDIT_SATUS, m_strEditStatus);
	DDX_Control(pDX, IDC_LIST_USER, m_listUser);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CLoginDlg, CXTResizeDialog)
//{{AFX_MSG_MAP(CLoginDlg)
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
    	if (m_strUser =="" || m_strPasswd =="") 
		{ 
		AfxMessageBox("对不起，用户名或密码不能为空，请重新输入");
		CWnd* pWnd=GetDlgItem(IDC_EDT_USER);
		pWnd->SetFocus();
		return;
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
							break;
						}
					}
					else
                    	theApp.m_bLogIn=false;
        			m_SLogin.MoveNext();
				}
				if(theApp.m_bLogIn == false)
            		return;
			}
				//登陆成功判断
						bIsLoggin = TRUE;

//					AfxMessageBox("正常退出，谢谢您使用Robustech监控系统，再见",MB_ICONINFORMATION);
		}
	}
	else if(m_bAddUser && theApp.m_bsuper)
	{
		int nuid;
         		m_SLogin.MoveFirst();
          		while ( !m_SLogin.IsEOF() )
				{
					nuid = m_SLogin.m_szUID;
			       	strtemp = m_SLogin.m_szName;
		    		strtemp.TrimRight();
					if(strtemp == m_strUser)
					{
						nuid =1;
						break;
					}
					if(nrecord <= nuid)
						nrecord = nuid;
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
	else
	{
    	theApp.curuser = "";
    	theApp.m_bLogIn=false;
	}
    CMainFrame* pFWnd=(CMainFrame*)AfxGetMainWnd();
	pFWnd->AddUser();
    if ( m_SLogin._IsOpen() )
      m_SLogin.Close();
    m_Cn.Close();
    dbAx::Term();
	CDialog::OnOK();
}

void CLoginDlg::OnCancel() 
{
    if ( m_SLogin._IsOpen() )
      m_SLogin.Close();
    m_Cn.Close();
    dbAx::Term();
	CDialog::OnCancel();
}

BOOL CLoginDlg::OnInitDialog() 
{
	CXTResizeDialog::OnInitDialog();
	
	int screenx=GetSystemMetrics (SM_CXSCREEN);
	int screeny=GetSystemMetrics (SM_CYSCREEN);
	ConnectDB();  //连接数据库
	m_listUser.ModifyExtendedStyle(0, LVS_EX_FULLROWSELECT|LVS_SHOWSELALWAYS | LVS_EX_GRIDLINES);
	SetResize(IDC_LIST_USER,         SZ_TOP_LEFT,    SZ_BOTTOM_RIGHT);

	if(m_strdism == "login")
	{
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
        			GetDlgItem(ID_DELUSER)->ShowWindow(SW_HIDE);;
        			GetDlgItem(IDC_BUTADD)->ShowWindow(SW_HIDE);;
    				SetWindowText(_T("注销用户"));
				}
    			GetDlgItem(IDOK)->SetWindowText(_T("注销"));
    			GetDlgItem(IDC_EDT_USER)->ShowWindow(SW_HIDE);;
    			GetDlgItem(IDC_EDT_PWD)->ShowWindow(SW_HIDE);;
    			GetDlgItem(IDC_STATICL1)->ShowWindow(SW_HIDE);;
    			GetDlgItem(IDC_STATICL2)->ShowWindow(SW_HIDE);;

				CString dddd;
				int iItem = 0;
         				m_SLogin.MoveFirst();
          				while ( !m_SLogin.IsEOF() )
						{
						  m_listUser.InsertItem(iItem, m_SLogin.m_szName);
						  if(m_SLoginNew->m_szclasser == 1)
							  dddd = "超级用户";
						  else
							  dddd = "操作员";
						  m_listUser.SetItemText(iItem, 1, dddd);
						  iItem++;
        					m_SLogin.MoveNext();
						}
			}
			else
			{
    			GetDlgItem(IDC_LIST_USER)->ShowWindow(SW_HIDE);;
    			GetDlgItem(ID_DELUSER)->ShowWindow(SW_HIDE);;
    			GetDlgItem(IDC_BUTADD)->ShowWindow(SW_HIDE);;
			}
	}
	else
	{
    			GetDlgItem(IDC_EDT_USER)->ShowWindow(SW_HIDE);;
    			GetDlgItem(IDC_EDT_PWD)->ShowWindow(SW_HIDE);;
    			GetDlgItem(IDC_STATICL1)->ShowWindow(SW_HIDE);;
    			GetDlgItem(IDC_STATICL2)->ShowWindow(SW_HIDE);;
    			GetDlgItem(ID_DELUSER)->ShowWindow(SW_HIDE);;
    			GetDlgItem(IDC_BUTADD)->ShowWindow(SW_HIDE);;
    			GetDlgItem(IDOK)->ShowWindow(SW_HIDE);;
    	MoveWindow(CRect(50,100,960,300));
	}
	if(m_strdism == "SDisA")
	{
    		SetWindowText(_T("模拟量调用显示"));
			m_listUser.InsertColumn(0,"安装地点/名称",LVCFMT_LEFT,120);
			m_listUser.InsertColumn(1,_T("单位"),LVCFMT_LEFT,40);
			m_listUser.InsertColumn(2,"报警值",LVCFMT_LEFT,60);
			m_listUser.InsertColumn(3,_T("断电值"),LVCFMT_LEFT,60);
			m_listUser.InsertColumn(4,"复电值",LVCFMT_LEFT,60);
			m_listUser.InsertColumn(5,_T("监测值"),LVCFMT_LEFT,60);
			m_listUser.InsertColumn(6,"最近最大值",LVCFMT_LEFT,80);
			m_listUser.InsertColumn(7,_T("平均值"),LVCFMT_LEFT,60);
			m_listUser.InsertColumn(8,"最后报警时刻",LVCFMT_LEFT,120);
			m_listUser.InsertColumn(9,_T("最后解除报警时刻"),LVCFMT_LEFT,120);
			m_listUser.InsertColumn(10,"最后断电时刻",LVCFMT_LEFT,120);
			m_listUser.InsertColumn(11,_T("最后复电时刻"),LVCFMT_LEFT,120);
	}
	else if(m_strdism == "DisAAR")
	{
    		SetWindowText(_T("模拟量报警记录查询显示"));
			m_listUser.InsertColumn(0,"用户",LVCFMT_LEFT,100);
			m_listUser.InsertColumn(1,_T("等级"),LVCFMT_LEFT,100);
	}
	else if(m_strdism == "DisABR")
	{
    		SetWindowText(_T("模拟量断电记录查询显示"));
			m_listUser.InsertColumn(0,"用户",LVCFMT_LEFT,100);
			m_listUser.InsertColumn(1,_T("等级"),LVCFMT_LEFT,100);
	}
	else if(m_strdism == "DisAFER")
	{
    		SetWindowText(_T("模拟量馈电异常记录查询显示"));
			m_listUser.InsertColumn(0,"用户",LVCFMT_LEFT,100);
			m_listUser.InsertColumn(1,_T("等级"),LVCFMT_LEFT,100);
	}
	else if(m_strdism == "DisASR")
	{
    		SetWindowText(_T("模拟量统计值记录查询显示"));
			m_listUser.InsertColumn(0,"用户",LVCFMT_LEFT,100);
			m_listUser.InsertColumn(1,_T("等级"),LVCFMT_LEFT,100);
	}
	else if(m_strdism == "SDisD")
	{
    		SetWindowText(_T("开关量调用显示"));
			m_listUser.InsertColumn(0,"用户",LVCFMT_LEFT,100);
			m_listUser.InsertColumn(1,_T("等级"),LVCFMT_LEFT,100);
	}
	else if(m_strdism == "DisDABR")
	{
    		SetWindowText(_T("开关量报警及断电记录查询显示"));
			m_listUser.InsertColumn(0,"用户",LVCFMT_LEFT,100);
			m_listUser.InsertColumn(1,_T("等级"),LVCFMT_LEFT,100);
	}
	else if(m_strdism == "DisDSC")
	{
    		SetWindowText(_T("开关量状态变动记录查询显示"));
			m_listUser.InsertColumn(0,"用户",LVCFMT_LEFT,100);
			m_listUser.InsertColumn(1,_T("等级"),LVCFMT_LEFT,100);
	}
	else if(m_strdism == "DisDFER")
	{
    		SetWindowText(_T("开关量馈电异常记录查询显示"));
			m_listUser.InsertColumn(0,"用户",LVCFMT_LEFT,100);
			m_listUser.InsertColumn(1,_T("等级"),LVCFMT_LEFT,100);
	}


	
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
		m_SLogin._SetRecordsetEvents(new CAccountSetEvents);
		m_SLogin.Open(_T("Select * From ygjluser"), &m_Cn);
		m_SLogin.MarshalOptions(adMarshalModifiedOnly);
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
    	GetDlgItem(IDC_EDT_USER)->ShowWindow(SW_SHOW);;
    	GetDlgItem(IDC_EDT_PWD)->ShowWindow(SW_SHOW);;
    	GetDlgItem(IDC_STATICL1)->ShowWindow(SW_SHOW);;
    	GetDlgItem(IDC_STATICL2)->ShowWindow(SW_SHOW);;
    	GetDlgItem(IDC_BUTADD)->ShowWindow(SW_HIDE);;
    	GetDlgItem(ID_DELUSER)->ShowWindow(SW_HIDE);;
    	GetDlgItem(IDC_LIST_USER)->ShowWindow(SW_HIDE);;
}

void CLoginDlg::OnItemChangedList(NMHDR *pNMHDR, LRESULT *pResult)
{
  LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);

  *pResult = 0;

  if ( pNMLV->uNewState == 3 )
  {
      if(!m_SLogin._IsEmpty() )
           m_SLogin.AbsolutePosition(pNMLV->iItem + 1);
  }
}

void CLoginDlg::DelUser()
{
	bool isselect = true;
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
    if ( m_SLogin._IsOpen() )
      m_SLogin.Close();
    m_Cn.Close();
    dbAx::Term();
	OnInitDialog();
}

