// LoginDlg.cpp : implementation file
//

#include "stdafx.h"
#include "KJMonitor.h"
#include "LoginDlg.h"

#include "SQL\\String2DataType.h"
#include "BackupSettingDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//��½�ɹ��ж�
static BOOL bIsLoggin = FALSE;
/////////////////////////////////////////////////////////////////////////////
// CLoginDlg dialog


CLoginDlg::CLoginDlg(CWnd* pParent /*=NULL*/)
: CDialog(CLoginDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLoginDlg)
	m_strPasswd = _T("");
	m_strUser = _T("");
	m_strEditStatus = _T("");
	//}}AFX_DATA_INIT
	m_bLogInOut=0;
    
}


void CLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLoginDlg)
	DDX_Control(pDX, IDC_CHECK_MANACHINE, m_CheckManachine);
	DDX_Control(pDX, IDC_EDT_PWD, m_ctrlEditPWD);
	DDX_Control(pDX, IDOK, m_btnOK);
	DDX_Control(pDX, IDCANCEL, m_btnCANCEL);
	DDX_Text(pDX, IDC_EDT_PWD, m_strPasswd);
	DDX_Text(pDX, IDC_EDT_USER, m_strUser);
	DDX_Text(pDX, IDC_EDIT_SATUS, m_strEditStatus);
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
	
/*	if (m_strUser =="" ) 
	{ 
		AfxMessageBox("�Բ����û�������Ϊ�գ�����������");
		CWnd* pWnd=GetDlgItem(IDC_EDT_USER);
		pWnd->SetFocus();
		return;
	}  
	if (m_strPasswd =="" ) 
	{ 
		AfxMessageBox("�Բ������벻��Ϊ�գ���������������");
		CWnd* pWnd=GetDlgItem(IDC_EDT_PWD);
		pWnd->SetFocus();
		return;
	}
	else */
///	{
		try
		{
//			if( m_SQLDirect.ExecuteSQL("SELECT * FROM LOGIN")==SQL_SUCCESS)
			{
/*				int nRet=m_SQLDirect.Fetch();
				while(!nRet)
				{
					if(m_SQLDirect.GetCol(1)==m_strUser)
					{
						if (m_strPasswd != m_SQLDirect.GetCol(2))
						{
							AfxMessageBox("����������������룡");
							m_strPasswd.Empty();
							CWnd* pWnd=GetDlgItem(IDC_EDT_PWD);
							pWnd->SetFocus();
							return;
						}
						bResult=TRUE;
						gstrUser=m_strUser;
						gstrAuth=m_SQLDirect.GetCol(6);
						CTime loginTime = CTime::GetCurrentTime();
						strtemp=loginTime.Format("%Y��%m��%d��%Hʱ%M��%S��");
						CString2DataType Str2Data;
						CString strtemp1,strtemp2,strtemp3;
						strtemp1=strtemp.Left(4);
						strtemp2=strtemp.Mid(6);
						strtemp3=strtemp2.Left(2);
						int nMonth=Str2Data.String2Int(strtemp3);
						int nYear=Str2Data.String2Int(strtemp1);
						//							strtemp1.
						//							if(nYear!=2003)
						//							if((nMonth>=11)||(nMonth<5)||(nYear!=2003))
						//{
					//	AfxMessageBox("�Բ��𣬲��԰汾�ѳ���ʹ������");
					//	return;
				//	}
						
						if(!m_bLogInOut)
							strSQL="UPDATE LOGIN SET LOGONDATETIME='"+strtemp+"', LOGOFFDATETIME ='û�������˳�/��������ʹ��' WHERE NAME='"+m_strUser+"'";
						else
							strSQL="UPDATE LOGIN SET LOGOFFDATETIME='"+strtemp+"' WHERE NAME='"+m_strUser+"'";
						m_SQLDirect.ExecuteSQL(strSQL);
*/						
						//��½�ɹ��ж�
						bIsLoggin = TRUE;

///						break;
//					}
//					nRet=m_SQLDirect.Fetch();
				}
/*				if ((!bResult)&&(!m_bLogInOut))
				{
					AfxMessageBox("���û��������ڣ����������룡");
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
					AfxMessageBox("�����˳���лл��ʹ��Robustech���ϵͳ���ټ�",MB_ICONINFORMATION);
					
				}

				//���ѡ����Ϊ��������������˫���ȱ��������öԻ���
				if(m_CheckManachine.GetCheck() == 1)
				{
					CBackupSettingDlg dlgBackupSetting;
					if(dlgBackupSetting.DoModal() == IDCANCEL)
						return;
					if(bIsLoggin && !m_bLogInOut )
					{
						//�����������
						theApp.StartClient();
					}
				}
				else
				{
					if(bIsLoggin && !m_bLogInOut )
					{
						//�����������
						theApp.StartServer();
					}
				}

				m_SQLDirect.Close();
				CDialog::OnOK();
///			}
		}
		catch(CDBException *e){
			e->ReportError();
			EndWaitCursor();
			return ;
		}
///	}
}

BOOL CLoginDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	int screenx=GetSystemMetrics (SM_CXSCREEN);
	int screeny=GetSystemMetrics (SM_CYSCREEN);
	if((screenx!=1024)||(screeny!=768))
	{
		CString strtemp;
		strtemp.Format("��ϵͳ�����Ļ�ֱ���Ϊ 1024X768����ǰ��Ļ�ֱ���Ϊ %dX%d�������Ļ������������",screenx,screeny);
		AfxMessageBox(strtemp);
	}
	
	// TODO: Add extra initialization here
	m_btnOK.SetThemeHelper(&m_ThemeHelper);
	m_btnOK.SetIcon(IDI_ICON_OK);
	m_btnOK.SetTooltipText(_T("��ӭ��¼Robustech���ϵͳ���������йص������������Ա��ϵ"));
	m_btnCANCEL.SetThemeHelper(&m_ThemeHelper);
	m_btnCANCEL.SetIcon(IDI_ICON_CANCEL,IDI_ICON_CANCEL01);
	m_btnCANCEL.SetTooltipText(_T("ֹͣ��¼���˳�ϵͳ���������йص������������Ա��ϵ"));
	
///	ConnectDB();  //�������ݿ�
	if(!m_bLogInOut)
	{
		m_strEditStatus="�����ڵ�¼����ϵͳ���������û������������ȷ��";
///		DispLatestUser();
	}
	else
	{
		//�˳�ʱ����ʾ����ѡ��CheckBox
		m_CheckManachine.EnableWindow(FALSE);
		
		m_strEditStatus="�����ڵ�¼�˳�ϵͳ���������������ȷ��";
		m_strUser=gstrUser;
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
	try
	{
		m_SQLDirect.Init();
		if(m_SQLDirect.Connect(_T("masterdefine"),_T("kj86"),_T("kj86")))
			AfxMessageBox("AddUser:�޷������û��������ݿ�,��ȷ��SQL SERVER�����Ƿ�����!");
	}
	catch(CDBException *e)
	{
		e->ReportError();
		return;
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

