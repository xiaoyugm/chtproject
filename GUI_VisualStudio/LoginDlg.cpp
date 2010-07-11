// LoginDlg.cpp : implementation file
//

#include "stdafx.h"
#include "GUI_VisualStudio.h"
#include "LoginDlg.h"

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
: CDialog(CLoginDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLoginDlg)
	m_strPasswd = _T("");
	m_strUser = _T("");
	m_strEditStatus = _T("");
	m_SLoginNew = &m_SLogin;

	//}}AFX_DATA_INIT
	m_bLogInOut=0;
    
}


void CLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLoginDlg)
//	DDX_Control(pDX, IDC_CHECK_MANACHINE, m_CheckManachine);
	DDX_Control(pDX, IDC_EDT_PWD, m_ctrlEditPWD);
	DDX_Control(pDX, IDOK, m_btnOK);
	DDX_Control(pDX, IDCANCEL, m_btnCANCEL);
	DDX_Text(pDX, IDC_EDT_PWD, m_strPasswd);
	DDX_Text(pDX, IDC_EDT_USER, m_strUser);
//	DDX_Text(pDX, IDC_EDIT_SATUS, m_strEditStatus);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLoginDlg, CDialog)
//{{AFX_MSG_MAP(CLoginDlg)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLoginDlg message handlers

void CLoginDlg::OnOK() 
{
	// TODO: Add extra validation here
	CString strSQL,strtemp;
	UpdateData(TRUE);
	bool bResult=FALSE;
	
	if (m_strUser =="" || m_strPasswd =="") 
	{ 
		AfxMessageBox("对不起，用户名\密码不能为空，请重新输入");
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
		}
		else
		{
						//登陆成功判断
						bIsLoggin = TRUE;

/*				if ((!bResult)&&(!m_bLogInOut))
				{
					AfxMessageBox("该用户名不存在，请重新输入！");
					m_strUser.Empty();
					m_strPasswd.Empty();
					UpdateData(FALSE);
					CWnd* pWnd=GetDlgItem(IDC_EDT_USER);
					pWnd->SetFocus();
					return;
				}*/
				if(m_bLogInOut)
				{
///					CString strSQL;
///					strSQL.Format("UPDATE uSysInfo SET strLatestUser='%s'",m_strUser); 
///					m_SQLDirect.ExecuteSQL(strSQL);
					AfxMessageBox("正常退出，谢谢您使用Robustech监控系统，再见",MB_ICONINFORMATION);
					
				}


		}
	}

	theApp.m_bLogIn=true;
	theApp.curuser = m_strUser;
    CMainFrame* pFWnd=(CMainFrame*)AfxGetMainWnd();
	pFWnd->AddUser();
    if ( m_SLogin._IsOpen() )
      m_SLogin.Close();
    m_Cn.Close();
    dbAx::Term();
	CDialog::OnOK();
}

BOOL CLoginDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	int screenx=GetSystemMetrics (SM_CXSCREEN);
	int screeny=GetSystemMetrics (SM_CYSCREEN);
	
	// TODO: Add extra initialization here
//	m_btnOK.SetThemeHelper(&m_ThemeHelper);
//	m_btnOK.SetIcon(IDI_ICON_OK);
//	m_btnOK.SetTooltipText(_T("欢迎登录Robustech监控系统，与密码有关的问题请与管理员联系"));
//	m_btnCANCEL.SetThemeHelper(&m_ThemeHelper);
//	m_btnCANCEL.SetIcon(IDI_ICON_CANCEL,IDI_ICON_CANCEL01);
//	m_btnCANCEL.SetTooltipText(_T("停止登录，退出系统，与密码有关的问题请与管理员联系"));
	
	ConnectDB();  //连接数据库
	if(!m_bLogInOut)
	{
		m_strEditStatus="您正在登录进入系统，请输入用户名和密码后点击确定";
///		DispLatestUser();
	}
	else
	{
		//退出时不显示主备选择CheckBox
		m_CheckManachine.EnableWindow(FALSE);
		
		m_strEditStatus="您正在登录退出系统，请输入密码后点击确定";
//		m_strUser=gstrUser;
		//m_btnCANCEL.EnableWindow(0);
		CWnd* pWnd=GetDlgItem(IDC_EDT_PWD);
		pWnd->SetFocus();
		//	m_ctrlEditPWD.SetFoucus();
	}
	
	
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
       m_Cn.Create();
       m_Cn._SetConnectionEvents(new CCardFileEvents);
       m_Cn.CursorLocation(adUseClient);
       m_Cn.Open((LPCTSTR)szConnect);

		m_SLogin.Create();
		m_SLogin.CursorType(adOpenDynamic);
		m_SLogin.CacheSize(50);
		m_SLogin._SetRecordsetEvents(new CAccountSetEvents);
		m_SLogin.Open(_T("Select * From user"), &m_Cn);
		m_SLogin.MarshalOptions(adMarshalModifiedOnly);
	}
    catch ( dbAx::CAxException *e )
	{
    MessageBox(e->m_szErrorDesc, _T("BJygjl Message"), MB_OK);
    delete e;
    return ;
	}
}

void CLoginDlg::DispLatestUser()
{
	
	try
	{
		if( m_SQLDirect.ExecuteSQL("SELECT * FROM uSysInfo")==SQL_SUCCESS)
		{
			int nRet=m_SQLDirect.Fetch();
			if(!nRet)
			{
				m_strUser=m_SQLDirect.GetCol(1);
				CWnd* pWnd;
				pWnd=GetDlgItem(IDC_EDT_PWD);  //IDC_EDT_USER  IDC_EDT_PWD
				pWnd->SetFocus();
			}
			else
			{
				CWnd* pWnd;
				pWnd=GetDlgItem(IDC_EDT_USER);
				pWnd->SetFocus();
			}
		}
		
	}
	catch(CDBException *e){
		e->ReportError();
		EndWaitCursor();
		return ;
	}
}

