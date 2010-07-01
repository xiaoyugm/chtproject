// CommParaDlg.cpp : implementation file
//

#include "stdafx.h"
#include "kjmonitor.h"
#include "CommParaDlg.h"

#include "CommStatusFM.h"
#include "MainFrm.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCommParaDlg dialog


CCommParaDlg::CCommParaDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCommParaDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCommParaDlg)
	m_unEditRepeattimes = 0;
	m_unEditScanDelayTime = 0;
	//}}AFX_DATA_INIT
}


void CCommParaDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCommParaDlg)
		DDX_Control(pDX, IDOK, m_btnOK);
		DDX_Control(pDX, IDCANCEL, m_btnCANCEL);
	DDX_Text(pDX, IDC_EDIT_REPEATSCANTIMES, m_unEditRepeattimes);
	DDX_Text(pDX, IDC_EDIT_SCANDELAYTIME, m_unEditScanDelayTime);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCommParaDlg, CDialog)
	//{{AFX_MSG_MAP(CCommParaDlg)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCommParaDlg message handlers

BOOL CCommParaDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_btnOK.SetThemeHelper(&m_ThemeHelper);
	m_btnOK.SetIcon(IDI_ICON_OK);
	m_btnOK.SetTooltipText(_T("修改原有参数，使用新设置值"));

	m_btnCANCEL.SetThemeHelper(&m_ThemeHelper);
	m_btnCANCEL.SetIcon(IDI_ICON_CANCEL,IDI_ICON_CANCEL01);
	m_btnCANCEL.SetTooltipText(_T("保持原有参数，取消本次操作"));

	

///	ConnectDB();

	GetDatafromDB();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CCommParaDlg::OnOK() 
{
	// TODO: Add extra validation here
	//UpdateData(TRUE);
	//CDialog::OnOK();
	//	UINT	m_unEditRepeattimes;
//	UINT	m_unEditScanDelayTime;
//
	 UpdateData(TRUE);
	 bool bSavesuccess=FALSE;
	 //m_strUser.TrimRight();
/*	 if ((m_unEditScanDelayTime>20000) ||(m_unEditScanDelayTime<10))// 2003/8/18 100
	 { 
	    AfxMessageBox("对不起，扫描延迟时间不能超过200 ms或小于10ms，请重新输入");
	    CWnd* pWnd=GetDlgItem(IDC_EDIT_SCANDELAYTIME);
	    pWnd->SetFocus();
	    return;
	 }    

     if (m_unEditRepeattimes >3 ) 
	 { 
	    AfxMessageBox("对不起，重复扫描次数不能超过3次，请重新输入");
	    CWnd* pWnd=GetDlgItem(IDC_EDIT_REPEATSCANTIMES);
	    pWnd->SetFocus();
	    return;
	 }  */
	try
	{
/*		CString strSQL;
		if( m_SQLDirect.ExecuteSQL("SELECT * FROM uScanPara")==SQL_SUCCESS)
		{
			int nRet=m_SQLDirect.Fetch();
			if(!nRet)
			{
				strSQL.Format("UPDATE uScanPara SET unScanTimeDelay = %d, unRepeatTimes = %d",m_unEditScanDelayTime,m_unEditRepeattimes);
				if(m_SQLDirect.ExecuteSQL(strSQL)==SQL_SUCCESS)
					bSavesuccess=TRUE;
			}
			else
			{
				strSQL.Format("INSERT INTO uScanPara (unScanTimeDelay, unRepeatTimes) VALUES (%d, %d)",m_unEditScanDelayTime,m_unEditRepeattimes);
				if(m_SQLDirect.ExecuteSQL(strSQL)==SQL_SUCCESS)
					bSavesuccess=TRUE;
			}
			if(bSavesuccess)
			{*/
				gunScantimeDelay=m_unEditScanDelayTime;
				gunRepeaScantTimes= 0 ;

				CMainFrame* pFWnd=(CMainFrame*)AfxGetMainWnd();
				CCommStatusFM *m_pCommStatusFM=pFWnd->m_pCommStatusFM;
				if(m_pCommStatusFM->ResetTimer())
				AfxMessageBox("参数设置成功!");
///			}
			CDialog::OnOK();
///		}
	}
	catch(CDBException *e){
	e->ReportError();
	return ;
	}

}

void CCommParaDlg::ConnectDB()
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

void CCommParaDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	m_SQLDirect.Close();
	
}

void CCommParaDlg::GetDatafromDB()
{
	try
	{
/*		CString strSQL;
		if( m_SQLDirect.ExecuteSQL("SELECT * FROM uScanPara")==SQL_SUCCESS)
		{
			int nRet=m_SQLDirect.Fetch();
			if(!nRet)
			{*/
				m_unEditScanDelayTime= gunScantimeDelay ;
				m_unEditRepeattimes= 0 ;
				UpdateData(FALSE);
///			}
///		}
	}
	catch(CDBException *e){
	e->ReportError();
	return ;
	}

}


