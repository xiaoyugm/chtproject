// SetTimeDlg.cpp : implementation file
//

#include "stdafx.h"
#include "GUI_VisualStudio.h"
#include "SetTimeDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSetTimeDlg dialog


CSetTimeDlg::CSetTimeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSetTimeDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSetTimeDlg)
	m_nSecond = 0;
	//}}AFX_DATA_INIT
}


void CSetTimeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSetTimeDlg)
	DDX_Text(pDX, IDC_EDIT_SECOND, m_nSecond);
	DDV_MinMaxUInt(pDX, m_nSecond, 0, 255);
		  DDX_Control(pDX, IDC_COMBO_VERIFYT, m_VERIFYT);
		  DDX_Control(pDX, IDC_COMBO_PORT, m_PORT);
		  DDX_Control(pDX, IDC_COMBO_FUNCTION, m_FUNCTION);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSetTimeDlg, CDialog)
	//{{AFX_MSG_MAP(CSetTimeDlg)
	ON_BN_CLICKED(IDOK_SEND, OnButSend)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSetTimeDlg message handlers
BOOL CSetTimeDlg::OnInitDialog()
{
  CDialog::OnInitDialog();

	// insert strings into the size combo box.
    	m_FUNCTION.AddString("打开");
    	m_FUNCTION.AddString("关闭");
	for(int i = 01; i < 65; i++)
	{
		CString strItem;
		strItem.Format(_T("%d"), i);
    	m_VERIFYT.AddString(strItem);
		if(i<9)
        	m_PORT.AddString(strItem);
	}
	m_VERIFYT.SetCurSel(0);
	m_PORT.SetCurSel(0);
	m_FUNCTION.SetCurSel(0);


	if(chcommand == 0x54)
	{
    	GetDlgItem(IDC_STATICV1)->ShowWindow(SW_HIDE);;
    	GetDlgItem(IDC_STATICV2)->ShowWindow(SW_HIDE);;
    	GetDlgItem(IDC_COMBO_PORT)->ShowWindow(SW_HIDE);;
    	GetDlgItem(IDC_COMBO_FUNCTION)->ShowWindow(SW_HIDE);;
	}
	else if(chcommand == 0x4B)
	{
		SetWindowText("手动控制操作");
	}

  return TRUE;  // return TRUE unless you set the focus to a control
  // EXCEPTION: OCX Property Pages should return FALSE
}

void CSetTimeDlg::OnButSend() 
{
	if(chcommand == 0x54)
	{
    	CNDKMessage message1(VERIFYTIMER);
					message1.Add(0x7E);

		unsigned char nfds = m_VERIFYT.GetCurSel()+1;
					message1.Add(nfds);
	 				message1.Add(chcommand);

    	CTime t=CTime::GetCurrentTime();
					message1.Add(t.GetYear()-2000);
					message1.Add(t.GetMonth());
					message1.Add(t.GetDay());
					message1.Add(t.GetDayOfWeek());
					message1.Add(t.GetHour());
					message1.Add(t.GetMinute());
					message1.Add(t.GetSecond());

					message1.Add(0x21);
					theApp.m_sendcom =true;
					theApp.m_sendmessage =NULL;
					theApp.m_sendmessage = message1;
//					theApp.Sync(message1);
	}
	else if(chcommand == 0x4B)
	{
    	CNDKMessage message1(MANUALCONTROL);
					message1.Add(0x7E);

		unsigned char nfds = m_VERIFYT.GetCurSel()+1;
					message1.Add(nfds);
	 				message1.Add(chcommand);

					nfds = m_PORT.GetCurSel()+1;
					message1.Add(nfds);
					nfds = m_FUNCTION.GetCurSel();
					message1.Add(nfds);

					message1.Add(0x21);
					theApp.m_sendcom =true;
					theApp.m_sendmessage =NULL;
					theApp.m_sendmessage = message1;
	}

}
