// BackupSettingDlg.cpp : implementation file
//

#include "stdafx.h"
#include "kjmonitor.h"
#include "BackupSettingDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBackupSettingDlg dialog


CBackupSettingDlg::CBackupSettingDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBackupSettingDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBackupSettingDlg)
	m_BackupCOM1 = _T("");
	m_BackupCOM2 = _T("");
	m_BackupCOM3 = _T("");
	m_BackupCOM4 = _T("");
	m_BackupCOM5 = _T("");
	m_BackupCOM6 = _T("");
	m_BackupCOM7 = _T("");
	m_BackupCOM8 = _T("");
	m_BackupIP = _T("");
	m_BackupPort = _T("");
	m_BackupTimeout = _T("");
	//}}AFX_DATA_INIT
}


void CBackupSettingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBackupSettingDlg)
	DDX_CBString(pDX, IDC_COMBO_COM1, m_BackupCOM1);
	DDX_CBString(pDX, IDC_COMBO_COM2, m_BackupCOM2);
	DDX_CBString(pDX, IDC_COMBO_COM3, m_BackupCOM3);
	DDX_CBString(pDX, IDC_COMBO_COM4, m_BackupCOM4);
	DDX_CBString(pDX, IDC_COMBO_COM5, m_BackupCOM5);
	DDX_CBString(pDX, IDC_COMBO_COM6, m_BackupCOM6);
	DDX_CBString(pDX, IDC_COMBO_COM7, m_BackupCOM7);
	DDX_CBString(pDX, IDC_COMBO_COM8, m_BackupCOM8);
	DDX_Text(pDX, IDC_EDIT_IP, m_BackupIP);
	DDX_Text(pDX, IDC_EDIT_PORT, m_BackupPort);
	DDX_Text(pDX, IDC_EDIT_TIMEOUT, m_BackupTimeout);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CBackupSettingDlg, CDialog)
	//{{AFX_MSG_MAP(CBackupSettingDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBackupSettingDlg message handlers

void CBackupSettingDlg::OnOK() 
{
	UpdateData(TRUE);

	//进行用户输入的检查
	if(m_BackupIP.IsEmpty() || m_BackupPort.IsEmpty() || m_BackupTimeout.IsEmpty())
	{
		MessageBox("作为备机启动时，主机的参数必须设置!","提示",MB_ICONINFORMATION);
		return;
	}
	if(m_BackupCOM1.IsEmpty() || m_BackupCOM2.IsEmpty() || m_BackupCOM3.IsEmpty() ||
		m_BackupCOM4.IsEmpty() || m_BackupCOM3.IsEmpty() || m_BackupCOM6.IsEmpty() ||
		m_BackupCOM7.IsEmpty() || m_BackupCOM8.IsEmpty())
	{
		MessageBox("作为备机启动时，主机打开的端口必须设置!","提示",MB_ICONINFORMATION);
		return;
	}

	gstrIP = m_BackupIP;
	gstrPort = m_BackupPort;
	gstrTimeOut = m_BackupTimeout;
	nCom1 = atoi(m_BackupCOM1.Mid(4));
	nCom2 = atoi(m_BackupCOM2.Mid(4));
	nCom3 = atoi(m_BackupCOM3.Mid(4));
	nCom4 = atoi(m_BackupCOM4.Mid(4));
	nCom5 = atoi(m_BackupCOM5.Mid(4));
	nCom6 = atoi(m_BackupCOM6.Mid(4));
	nCom7 = atoi(m_BackupCOM7.Mid(4));
	nCom8 = atoi(m_BackupCOM8.Mid(4));

	if(m_ini.ReadFile())
	{
		m_ini.SetValue("HOST","IP",m_BackupIP);
		m_ini.SetValue("HOST","PORT",m_BackupPort);
		m_ini.SetValue("HOST","TIMEOUT",m_BackupTimeout);

		m_ini.SetValue("COM","1",m_BackupCOM1);
		m_ini.SetValue("COM","2",m_BackupCOM2);
		m_ini.SetValue("COM","3",m_BackupCOM3);
		m_ini.SetValue("COM","4",m_BackupCOM4);
		m_ini.SetValue("COM","5",m_BackupCOM5);
		m_ini.SetValue("COM","6",m_BackupCOM6);
		m_ini.SetValue("COM","7",m_BackupCOM7);
		m_ini.SetValue("COM","8",m_BackupCOM8);

		m_ini.WriteFile();
	}
	

	CDialog::OnOK();
}

void CBackupSettingDlg::OnCancel() 
{
	CDialog::OnCancel();
}

BOOL CBackupSettingDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	char m_iniPath[MAX_PATH];

	GetWindowsDirectory(m_iniPath,MAX_PATH);
	strcat(m_iniPath,"c:\Robustech.ini");

	m_ini.SetPath(m_iniPath);
	if(m_ini.ReadFile())
	{
		m_BackupIP		= m_ini.GetValue("HOST","IP");
		m_BackupPort	= m_ini.GetValue("HOST","PORT");
		m_BackupTimeout = m_ini.GetValue("HOST","TIMEOUT");

		m_BackupCOM1 =m_ini.GetValue("COM","1");
		m_BackupCOM2 =m_ini.GetValue("COM","2");
		m_BackupCOM3 =m_ini.GetValue("COM","3");
		m_BackupCOM4 =m_ini.GetValue("COM","4");
		m_BackupCOM5 =m_ini.GetValue("COM","5");
		m_BackupCOM6 =m_ini.GetValue("COM","6");
		m_BackupCOM7 =m_ini.GetValue("COM","7");
		m_BackupCOM8 =m_ini.GetValue("COM","8");
	}
	else
	{
		CFile m_file;
		m_file.Open(m_iniPath,CFile::modeCreate);
		m_file.Close();

		m_BackupPort = "80";
		m_BackupTimeout = "60000";
		
		m_BackupCOM1 ="COM 1";
		m_BackupCOM2 ="COM 2";
		m_BackupCOM3 ="COM 3";
		m_BackupCOM4 ="COM 4";
		m_BackupCOM5 ="COM 5";
		m_BackupCOM6 ="COM 6";
		m_BackupCOM7 ="COM 7";
		m_BackupCOM8 ="COM 8";
	}

	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
