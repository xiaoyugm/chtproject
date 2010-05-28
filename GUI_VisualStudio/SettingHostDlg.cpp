// SettingHostDlg.cpp : implementation file
//

#include "stdafx.h"
#include "GUI_VisualStudio.h"
#include "SettingHostDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSettingHostDlg dialog


CSettingHostDlg::CSettingHostDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSettingHostDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSettingHostDlg)
	m_strHostIP = _T("");
	m_strPort = _T("");
	m_strTimeOut = _T("");
	//}}AFX_DATA_INIT
}


void CSettingHostDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSettingHostDlg)
	DDX_Text(pDX, IDC_EDIT_HOST_IP, m_strHostIP);
	DDV_MaxChars(pDX, m_strHostIP, 15);
	DDX_Text(pDX, IDC_EDIT_PORT, m_strPort);
	DDX_Text(pDX, IDC_EDIT_TIMEOUT, m_strTimeOut);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSettingHostDlg, CDialog)
	//{{AFX_MSG_MAP(CSettingHostDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSettingHostDlg message handlers
