// DlgModify.cpp : implementation file
//

#include "stdafx.h"
#include "KJMonitor.h"
#include "DlgModify.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgModify dialog


CDlgModify::CDlgModify(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgModify::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgModify)
	m_strCfmpwd = _T("");
	m_strNewPWD = _T("");
	//}}AFX_DATA_INIT
}


void CDlgModify::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgModify)
	DDX_Control(pDX, IDCANCEL, m_btnCANCEL);
	DDX_Control(pDX, IDOK, m_btnOK);
	DDX_Text(pDX, IDC_CONFIRM, m_strCfmpwd);
	DDX_Text(pDX, IDC_NEWPWD, m_strNewPWD);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgModify, CDialog)
	//{{AFX_MSG_MAP(CDlgModify)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgModify message handlers

void CDlgModify::OnOK() 
{
	// TODO: Add extra validation here
	 UpdateData(TRUE);
/*    if (m_strNewPWD != m_strCfmpwd)
	   {
	   	 AfxMessageBox("输入密码不相同，请重新输入！");
	 	 m_strNewPWD.Empty();
		 CWnd* pWnd=GetDlgItem(IDC_NEWPWD);
		 pWnd->SetFocus();
		 return;}
	else
	{
		try
		{
			CString strSQL;
			strSQL="UPDATE LOGIN SET PASSWORD='" + m_strNewPWD + "'WHERE NAME='" + gstrUser +"'";
			if(!m_SQLDirect.ExecuteSQL(strSQL))
				AfxMessageBox("密码修改成功!");
			m_SQLDirect.Close();
			CDialog::OnOK();
		}
		catch(CDBException *e){
		e->ReportError();
		EndWaitCursor();
		return ;
		}
	}	*/	
}

BOOL CDlgModify::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_btnOK.SetThemeHelper(&m_ThemeHelper);
	m_btnOK.SetIcon(IDI_ICON_OK);
	m_btnOK.SetTooltipText(_T("确认修改"));

	m_btnCANCEL.SetThemeHelper(&m_ThemeHelper);
	m_btnCANCEL.SetIcon(IDI_ICON_CANCEL,IDI_ICON_CANCEL01);
	m_btnCANCEL.SetTooltipText(_T("放弃修改"));

///	ConnectDB();

	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgModify::ConnectDB()
{
	try
	{
		m_SQLDirect.Init();
		if(m_SQLDirect.Connect(_T("masterdefine"),_T("kj86"),_T("kj86")))
			AfxMessageBox("AddUser:无法连接用户参数数据库,请确定SQL SERVER服务是否运行!");
	}
	catch(CDBException *e)
	{
		e->ReportError();
		return;
	}

}
