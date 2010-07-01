// DlgAddUser.cpp : implementation file
//

#include "stdafx.h"
#include "KJMonitor.h"
#include "DlgAddUser.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgAddUser dialog


CDlgAddUser::CDlgAddUser(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgAddUser::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgAddUser)
	m_strCfmPWD = _T("");
	m_strPWD = _T("");
	m_strUser = _T("");
	m_strDpt = _T("");
	m_strAut = _T("");
	//}}AFX_DATA_INIT
	//dbUser.Open("user",FALSE,FALSE,"ODBC",FALSE);
    //rsUser.Open();
}


void CDlgAddUser::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgAddUser)
	DDX_Control(pDX, IDC_AUTHORITY, m_ctrlComboAuthority);
	DDX_Control(pDX, IDOK, m_btnOK);
	DDX_Control(pDX, IDCANCEL, m_btnCANCEL);
	DDX_Text(pDX, IDC_CFMPWD, m_strCfmPWD);
	DDX_Text(pDX, IDC_PASSWD, m_strPWD);
	DDX_Text(pDX, IDC_USER, m_strUser);
	DDX_Text(pDX, IDC_DEPART, m_strDpt);
	DDX_CBString(pDX, IDC_AUTHORITY, m_strAut);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgAddUser, CDialog)
	//{{AFX_MSG_MAP(CDlgAddUser)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgAddUser message handlers

void CDlgAddUser::OnOK() 
{
	// TODO: Add extra validation here
	 UpdateData(TRUE);
	 bool bNew=TRUE;
	 //m_strUser.TrimRight();
/*     if (m_strUser =="" ) 
	 { 
	    AfxMessageBox("�Բ����û�������Ϊ�գ�����������");
	    CWnd* pWnd=GetDlgItem(IDC_USER);
	    pWnd->SetFocus();
	    return;
	 }  
	 if (m_strPWD =="" ) 
	 { 
	    AfxMessageBox("�Բ������벻��Ϊ�գ���������������");
	    CWnd* pWnd=GetDlgItem(IDC_PASSWD);
	    pWnd->SetFocus();
	    return;
	 }    
	 if (m_strPWD != m_strCfmPWD)
	 {
		AfxMessageBox("�Բ���������������벻��ͬ������������");
		m_strPWD.Empty();
		CWnd* pWnd=GetDlgItem(IDC_PASSWD);
		pWnd->SetFocus();
		return;
	 }
	else */
	{
		try
		{
/*			if( m_SQLDirect.ExecuteSQL("SELECT * FROM LOGIN")==SQL_SUCCESS)
			{
				int nRet=m_SQLDirect.Fetch();
				while(!nRet)
				{
					//AfxMessageBox(m_SQLDirect.GetCol(1));
					if(m_SQLDirect.GetCol(1)==m_strUser)
					{ 
						bNew=FALSE;
						AfxMessageBox("�Բ��𣬸��û����Ѿ����ڣ���ı��û�������������");
						m_strUser.Empty();
						CWnd* pWnd=GetDlgItem(IDC_USER);
						pWnd->SetFocus();
						return;
					}
					nRet=m_SQLDirect.Fetch();
				}
				CString strSQL,strtemp;
				CTime t = CTime::GetCurrentTime();
				strtemp=t.Format("%Y��%m��%d��%Hʱ%M��%S��");
				strSQL="INSERT INTO LOGIN (NAME, PASSWORD, DEPARTMENT, LOGONDATETIME, LOGOFFDATETIME,AUTHORITY) VALUES ('";
				strSQL+=m_strUser+"','"+m_strPWD+"','"+m_strDpt+"','"+strtemp+"','"+strtemp+"','"+m_strAut+"')";
				if(!m_SQLDirect.ExecuteSQL(strSQL))
					AfxMessageBox("���û���ӳɹ�!");
				m_SQLDirect.Close();
				CDialog::OnOK();
			}*/
		}
		catch(CDBException *e){
		e->ReportError();
		EndWaitCursor();
		return ;
		}
	}


}

BOOL CDlgAddUser::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_btnOK.SetThemeHelper(&m_ThemeHelper);
	m_btnOK.SetIcon(IDI_ICON_OK);
	m_btnOK.SetTooltipText(_T("ȷ����ӵ��û�"));

	m_btnCANCEL.SetThemeHelper(&m_ThemeHelper);
	m_btnCANCEL.SetIcon(IDI_ICON_CANCEL,IDI_ICON_CANCEL01);
	m_btnCANCEL.SetTooltipText(_T("�����޸�"));

	m_ctrlComboAuthority.SetCurSel(2);

///	ConnectDB();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgAddUser::ConnectDB()
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
