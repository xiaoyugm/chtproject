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
	: CXTResizeDialog(CSetTimeDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSetTimeDlg)
	m_nSecond = 0;
	//}}AFX_DATA_INIT
}


void CSetTimeDlg::DoDataExchange(CDataExchange* pDX)
{
	CXTResizeDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSetTimeDlg)
	DDX_Text(pDX, IDC_EDIT_SECOND, m_nSecond);
	DDV_MinMaxUInt(pDX, m_nSecond, 0, 255);
		  DDX_Control(pDX, IDC_COMBO_VERIFYT, m_VERIFYT);
		  DDX_Control(pDX, IDC_COMBO_PORT, m_PORT);
		  DDX_Control(pDX, IDC_COMBO_FUNCTION, m_FUNCTION);
	DDX_Control(pDX, IDC_LIST_C, m_listC);
	DDX_Control(pDX, IDC_LIST_C2, m_listC2);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSetTimeDlg, CXTResizeDialog)
	//{{AFX_MSG_MAP(CSetTimeDlg)
	ON_BN_CLICKED(IDOK_SEND, OnButSend)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSetTimeDlg message handlers
BOOL CSetTimeDlg::OnInitDialog()
{
  CXTResizeDialog::OnInitDialog();

	SetResize(IDOK_SEND,                  SZ_BOTTOM_LEFT,   SZ_BOTTOM_LEFT);
	SetResize(IDCANCEL,              SZ_BOTTOM_LEFT,   SZ_BOTTOM_LEFT);
    	SetResize(IDC_LIST_C,         SZ_TOP_LEFT,    SZ_BOTTOM_CENTER);
    	SetResize(IDC_LIST_C2,         SZ_TOP_CENTER,    SZ_BOTTOM_RIGHT);

	// Enable Office XP themes.
	XTThemeManager()->SetTheme(xtThemeOfficeXP);

	HWND hWndHeader = m_listC.GetDlgItem(0)->GetSafeHwnd();
	m_header.SubclassWindow(hWndHeader);

	// add bitmap images.
	m_header.SetBitmap(0, IDB_COLUMN_0, FALSE, RGB(0,255,0));
	m_header.SetBitmap(1, IDB_COLUMN_1, FALSE, RGB(0,255,0));
	//m_header.SetBitmap(2, IDB_COLUMN_2, FALSE, RGB(0,255,0));

	// enable auto sizing.
	m_header.EnableAutoSize(TRUE);
	m_header.ResizeColumnsToFit();
	//SortColumn(m_nSortedCol, m_bAscending);

//	m_listCtrl.ModifyExtendedStyle(0, LVS_EX_FULLROWSELECT|LVS_EX_FULLROWSELECT);
//	m_listCtrl.EnableUserSortColor(BoolType(m_bSortColor));
//	m_listCtrl.EnableUserListColor(BoolType(m_bListColor));
//	m_listCtrl.EnableUserRowColor(BoolType(m_bRowColor));
	m_listC.ModifyExtendedStyle(0, LVS_EX_GRIDLINES);
	m_listC2.ModifyExtendedStyle(0, LVS_EX_GRIDLINES);

	
	
	// insert strings into the size combo box.
    	m_FUNCTION.AddString("��");
    	m_FUNCTION.AddString("�ر�");
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
    	GetDlgItem(IDC_LIST_C)->ShowWindow(SW_HIDE);;
    	GetDlgItem(IDC_LIST_C2)->ShowWindow(SW_HIDE);;
	}
	else if(chcommand == 0x4B)
	{
    	GetDlgItem(IDC_LIST_C)->ShowWindow(SW_HIDE);;
    	GetDlgItem(IDC_LIST_C2)->ShowWindow(SW_HIDE);;
		SetWindowText("�ֶ����Ʋ���");
	}
	else if(chcommand == 0x43)
	{
    	GetDlgItem(IDC_STATICV1)->ShowWindow(SW_HIDE);;
    	GetDlgItem(IDC_STATICV2)->ShowWindow(SW_HIDE);;
    	GetDlgItem(IDC_COMBO_PORT)->ShowWindow(SW_HIDE);;
    	GetDlgItem(IDC_COMBO_FUNCTION)->ShowWindow(SW_HIDE);;
		SetWindowText("��վ���ò���");

       	// Create Columns
    	m_listC.InsertHiddenLabelColumn();	// Requires one never uses column 0
    	m_listC2.InsertHiddenLabelColumn();	// Requires one never uses column 0

    	for(int col = 0; col < 4 ; ++col)
		{
		CString title;  int kkk;
		CGridColumnTrait* pTrait = NULL;
		CGridColumnTrait* pTrait1 = NULL;
		if (col==0)	// Country
		{
			kkk = 45;
			title ="ͨ��";
		    m_listC2.InsertColumnTrait(col+1, title, LVCFMT_LEFT, kkk, col, pTrait1);
		}
		if (col==1)	// City
		{
			kkk = 80;
			title ="�߼���ϵ";
			pTrait = new CGridColumnTraitEdit;
		}
		if (col==2)	// Year won
		{
			kkk = 150;
			title ="ͨ������";
			CGridColumnTraitCombo* pComboTrait = new CGridColumnTraitCombo;
    			pComboTrait->AddItem(0, "");
    			pComboTrait->AddItem(1, "ģ�����������ͣ�");
    			pComboTrait->AddItem(2, "�ۼ�����Ƶ���ͣ�");
    			pComboTrait->AddItem(3, "����������̬����");
    			pComboTrait->AddItem(4, "����������̬����");
    			pComboTrait->AddItem(5, "ģ������Ƶ���ͣ�");
    			pComboTrait->AddItem(6, "");
    			pComboTrait->AddItem(7, "��������ͨ������");
			pTrait = pComboTrait;
			CGridColumnTraitCombo* pComboTrait1 = new CGridColumnTraitCombo;
    			pComboTrait1->AddItem(0, "");
    			pComboTrait1->AddItem(1, "����");
    			pComboTrait1->AddItem(2, "����");
    			pComboTrait1->AddItem(3, "��ƽ");
			pTrait1 = pComboTrait1;
		    m_listC2.InsertColumnTrait(col, title, LVCFMT_LEFT, 100, col-1, pTrait1);
		}
		if (col==3)	// Year won
		{
			kkk = 150;
			title ="����������";
			CGridColumnTraitCombo* pComboTrait = new CGridColumnTraitCombo;
    			pComboTrait->AddItem(0, "");
    			pComboTrait->AddItem(1, "ģ�����������ͣ�");
    			pComboTrait->AddItem(2, "�ۼ�����Ƶ���ͣ�");
    			pComboTrait->AddItem(3, "����������̬����");
    			pComboTrait->AddItem(4, "����������̬����");
    			pComboTrait->AddItem(5, "ģ������Ƶ���ͣ�");
    			pComboTrait->AddItem(6, "");
    			pComboTrait->AddItem(7, "��������ͨ������");
			pTrait = pComboTrait;
		}

		m_listC.InsertColumnTrait(col+1, title, LVCFMT_LEFT, kkk, col, pTrait);
		}

	// Insert data into list-control by copying from datamodel
    	for( int iItem = 0; iItem < 16 ; iItem++)
		{
				  m_listC.InsertItem(iItem, "ͨ��");
				  CString dddd;
				  dddd.Format("%d",iItem+1);
				  m_listC.SetItemText(iItem, 1, dddd);
				  m_listC.SetItemText(iItem, 2, "");
				  m_listC.SetItemText(iItem, 3, "");
				  m_listC.SetItemText(iItem, 4, "");
				  if(iItem < 8)
				  {
				  m_listC2.InsertItem(iItem, "ͨ��");
				  m_listC2.SetItemText(iItem, 1, dddd);
				  m_listC2.SetItemText(iItem, 2, "");
				  }
		}
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
	else if(chcommand == 0x43)
	{
    	CNDKMessage message1(SENDCONFIG);
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
