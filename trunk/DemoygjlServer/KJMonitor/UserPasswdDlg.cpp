// UserPasswdDlg.cpp : implementation file
//

#include "stdafx.h"
#include "KJMonitor.h"
#include "UserPasswdDlg.h"
#include "DlgAddUser.h"
#include "DlgViewR.h"
#include "DlgModify.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUserPasswdDlg dialog


CUserPasswdDlg::CUserPasswdDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CUserPasswdDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CUserPasswdDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CUserPasswdDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CUserPasswdDlg)
	DDX_Control(pDX, IDC_BUTTON_ADDUSER, m_btnADDUSER);
	DDX_Control(pDX, IDC_BUTTON_VIEWRECORD, m_btnVIEWRECORD);
	DDX_Control(pDX, IDC_BUTTON_MODIFYPWD, m_btnMODEFYPWD);
	DDX_Control(pDX, IDOK, m_btnOK);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CUserPasswdDlg, CDialog)
	//{{AFX_MSG_MAP(CUserPasswdDlg)
	ON_BN_CLICKED(IDC_BUTTON_MODIFYPWD, OnButtonModifypwd)
	ON_BN_CLICKED(IDC_BUTTON_ADDUSER, OnButtonAdduser)
	ON_BN_CLICKED(IDC_BUTTON_VIEWRECORD, OnButtonViewrecord)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUserPasswdDlg message handlers

void CUserPasswdDlg::OnButtonModifypwd() 
{
	// TODO: Add your control notification handler code here
	CDlgModify dlgm;
	dlgm.DoModal();
}

void CUserPasswdDlg::OnButtonAdduser() 
{
	// TODO: Add your control notification handler code here
	if(gstrAuth=="ϵͳ��")
	{
		CDlgAddUser dlga;
		dlga.DoModal();
	}
	else
		AfxMessageBox("�Բ���������ϵͳ����Ա��û������û���Ȩ��");
}

void CUserPasswdDlg::OnButtonViewrecord() 
{
	// TODO: Add your control notification handler code here
	if(gstrAuth=="ϵͳ��")
	{
		CDlgViewR dlgv;
		dlgv.DoModal();
	}
	else
		AfxMessageBox("�Բ���������ϵͳ����Ա��û�в鿴/ɾ���û���Ȩ��");
}

BOOL CUserPasswdDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_btnOK.SetThemeHelper(&m_ThemeHelper);
	m_btnOK.SetIcon(IDI_ICON_OK);
	m_btnOK.SetTooltipText(_T("�˳�"));

	m_btnADDUSER.SetThemeHelper(&m_ThemeHelper);
	m_btnADDUSER.SetIcon(IDI_ICON_LOGIN);
	m_btnADDUSER.SetTooltipText(_T("����µ��û���ֻ��ϵͳ����Ա���д�Ȩ��"));

	m_btnVIEWRECORD.SetThemeHelper(&m_ThemeHelper);
	m_btnVIEWRECORD.SetIcon(IDI_ICON_SEARCH);
	m_btnVIEWRECORD.SetTooltipText(_T("�鿴��ǰ�����û�����Ϣ��ֻ��ϵͳ����Ա���д�Ȩ��"));

	m_btnMODEFYPWD.SetThemeHelper(&m_ThemeHelper);
	m_btnMODEFYPWD.SetIcon(IDI_ICON_KEY);
	m_btnMODEFYPWD.SetTooltipText(_T("�޸ĵ�ǰ�û��ĵ�¼����"));

//	m_btnCANCEL.SetThemeHelper(&m_ThemeHelper);
//	m_btnCANCEL.SetIcon(IDI_ICON_CANCEL,IDI_ICON_CANCEL01);
//	m_btnCANCEL.SetTooltipText(_T("�˳�"));

	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
