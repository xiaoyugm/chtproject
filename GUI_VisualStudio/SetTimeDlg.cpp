// SetTimeDlg.cpp : implementation file
//

#include "stdafx.h"
#include "GUI_VisualStudio.h"
#include "SetTimeDlg.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern  ADCbreakE             m_ADCbreakE[65][25][65];
extern  OthersSetting    m_OthersSetting;
extern  SlaveStation             m_SlaveStation[65][25];
/////////////////////////////////////////////////////////////////////////////
// CSetTimeDlg dialog


CSetTimeDlg::CSetTimeDlg(CWnd* pParent /*=NULL*/)
	: CXTResizeDialog(CSetTimeDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSetTimeDlg)
    m_nSecond = 0;
	chcommand = 0x00;
	m_nchangev = 0;
	m_SControlNew = &m_SControl;

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
	ON_CBN_SELCHANGE(IDC_COMBO_VERIFYT, OnchangeComboD)
	ON_BN_CLICKED(IDCANCEL, OnButCancel)
	ON_BN_CLICKED(IDC_BUT_RES, OnButRES)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSetTimeDlg message handlers
BOOL CSetTimeDlg::OnInitDialog()
{
  CXTResizeDialog::OnInitDialog();

	CMainFrame* pFWnd=(CMainFrame*)AfxGetMainWnd();
   	pFWnd->m_pSetTimeDlg=this;

	SetResize(IDOK_SEND,                  SZ_BOTTOM_LEFT,   SZ_BOTTOM_LEFT);
	SetResize(IDCANCEL,              SZ_BOTTOM_LEFT,   SZ_BOTTOM_LEFT);
	if(chcommand == 0x43)       //配置测点 
	{
    	SetResize(IDC_LIST_C,         SZ_TOP_LEFT,    SZ_BOTTOM_CENTER);
    	SetResize(IDC_LIST_C2,         SZ_TOP_CENTER,    SZ_BOTTOM_RIGHT);
	}
	else
    	SetResize(IDC_LIST_C,         SZ_TOP_LEFT,    SZ_BOTTOM_RIGHT);

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
	m_listC.ModifyExtendedStyle(0, LVS_EX_GRIDLINES);
	m_listC2.ModifyExtendedStyle(0, LVS_EX_GRIDLINES);

	// insert strings into the size combo box.
	if(chcommand == 0x5A)        //故障闭锁
	{
    	m_FUNCTION.AddString("关闭");
    	m_FUNCTION.AddString("使能");
	}
	else
	{
    	m_FUNCTION.AddString("吸合");
    	m_FUNCTION.AddString("断开");
	}

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

    CString szConnect = _T("Provider=SQLOLEDB.1;Persist Security Info=True;\
                          User ID=sa;Password=sunset;\
                          Data Source=") +m_OthersSetting.DBname+ _T(";Initial Catalog=BJygjl");

//All calls to the AxLib should be wrapped in a try / catch block
  try
  {
    dbAx::Init();
    m_Cn.Create();
//    m_Cn._SetConnectionEvents(new CCardFileEvents);
    m_Cn.CursorLocation(adUseClient);
    m_Cn.Open((LPCTSTR)szConnect);

	if(chcommand == 0x54)         //校时
	{
    	GetDlgItem(IDC_STATICV1)->ShowWindow(SW_HIDE);;
    	GetDlgItem(IDC_STATICV2)->ShowWindow(SW_HIDE);;
    	GetDlgItem(IDC_COMBO_PORT)->ShowWindow(SW_HIDE);;
    	GetDlgItem(IDC_COMBO_FUNCTION)->ShowWindow(SW_HIDE);;
    	GetDlgItem(IDC_LIST_C2)->ShowWindow(SW_HIDE);;
    	GetDlgItem(IDC_BUT_RES)->ShowWindow(SW_HIDE);;
		m_listC.InsertColumn(0,"命令返回信息",LVCFMT_LEFT,450);
	}
	else if(chcommand == 0x4B)   //手动控制
	{
    	GetDlgItem(IDC_LIST_C2)->ShowWindow(SW_HIDE);;
		SetWindowText("手动控制操作");

		m_listC.InsertColumn(0,"安装地点/名称",LVCFMT_LEFT,300);
		m_listC.InsertColumn(1,"控制量",LVCFMT_LEFT,80);
		m_listC.InsertColumn(2,"关联量",LVCFMT_LEFT,80);

		int xxx = 0;
		int yyy = 0;
		unsigned char nfds = m_VERIFYT.GetCurSel()+1;
    	for( int iItem = 0; iItem < 8 ; iItem++)
		{
			yyy = xxx;
        	for( int i = 0; i < 64 ; i++)
			{
		      	if(m_ADCbreakE[nfds][iItem+17][i].bFSd != 0)
				{
				  m_listC.InsertItem(i+yyy, m_SlaveStation[nfds][iItem+17].WatchName);
				  m_listC.SetItemText(i+yyy, 1, m_ADCbreakE[nfds][iItem+17][i].cpoint);
				  m_listC.SetItemText(i+yyy, 2, m_ADCbreakE[nfds][iItem+17][i].adpoint);
				  xxx++;
				}
			}
		}
		m_nSecond = xxx;
	}
	else if(chcommand == 0x43)       //配置测点 
	{
    	GetDlgItem(IDC_STATICV1)->ShowWindow(SW_HIDE);;
    	GetDlgItem(IDC_STATICV2)->ShowWindow(SW_HIDE);;
    	GetDlgItem(IDC_COMBO_PORT)->ShowWindow(SW_HIDE);;
    	GetDlgItem(IDC_COMBO_FUNCTION)->ShowWindow(SW_HIDE);;
		SetWindowText("分站测点配置操作");
    	GetDlgItem(IDC_BUT_RES)->ShowWindow(SW_HIDE);;
		m_listC.InsertColumn(0,"命令返回信息",LVCFMT_LEFT,450);
    	GetDlgItem(IDC_LIST_C2)->ShowWindow(SW_HIDE);
	}
	else if(chcommand == 0x41)        //配置分站
	{
		m_SControl.Create();
		m_SControl.CursorType(adOpenDynamic);
		m_SControl.CacheSize(50);
		m_SControl._SetRecordsetEvents(new CAccountSetEvents);
		m_SControl.Open(_T("Select * From specialcontrol"), &m_Cn);
		m_SControl.MarshalOptions(adMarshalModifiedOnly);

    	GetDlgItem(IDC_LIST_C2)->ShowWindow(SW_HIDE);
		SetWindowText("配置分站操作");
    	GetDlgItem(IDC_STATICV2)->ShowWindow(SW_HIDE);
    	GetDlgItem(IDC_COMBO_FUNCTION)->ShowWindow(SW_HIDE);
    	GetDlgItem(IDC_STATICV1)->ShowWindow(SW_HIDE);
    	GetDlgItem(IDC_COMBO_PORT)->ShowWindow(SW_HIDE);;
    	GetDlgItem(IDC_COMBO_VERIFYT)->ShowWindow(SW_HIDE);
    	GetDlgItem(IDC_STATICV)->ShowWindow(SW_HIDE);;
//    	GetDlgItem(IDC_STATICV1)->SetWindowText("串口号");
    	GetDlgItem(IDC_BUT_RES)->ShowWindow(SW_HIDE);;

    	m_listC.InsertHiddenLabelColumn();	// Requires one never uses column 0
    	for(int col = 0; col < 2 ; ++col)
		{
		CString title;  int kkk;
		CGridColumnTrait* pTrait = NULL;
		if (col==0)	// Country
		{
			kkk = 270;
			title ="分站号";
		}
		if (col==1)	// Year won
		{
			kkk = 90;
			title ="串口号";
			CGridColumnTraitCombo* pComboTrait = new CGridColumnTraitCombo;
			pComboTrait->AddItem(0, "无配置");
         	for(int i = 01; i < 65; i++)
			{
         		CString strItem,strtemp;
          		strItem.Format(_T("%d"), i);
              	pComboTrait->AddItem(i, strItem);
			}
			pTrait = pComboTrait;
		}
		m_listC.InsertColumnTrait(col+1, title, LVCFMT_LEFT, kkk, col, pTrait);
		}
		int iItem = 0;
		m_SControl.MoveFirst();
		while ( !m_SControl.IsEOF() )
		{
				  m_listC.InsertItem(iItem, "通断");
				  CString dddd;
				  dddd.Format("%d",m_SControl.m_szSID);
				  m_listC.SetItemText(iItem, 1, dddd);
				  dddd.Format("%d",m_SControl.m_szSerialnum);
				  m_listC.SetItemText(iItem, 2, dddd);
				  iItem++;
			m_SControl.MoveNext();
		}
	}
	else if(chcommand == 0x47)        //通讯测试
	{
    	GetDlgItem(IDC_LIST_C2)->ShowWindow(SW_HIDE);;
		SetWindowText("通讯测试");
    	GetDlgItem(IDC_STATICV2)->ShowWindow(SW_HIDE);;
    	GetDlgItem(IDC_COMBO_FUNCTION)->ShowWindow(SW_HIDE);;
    	GetDlgItem(IDC_STATICV1)->ShowWindow(SW_HIDE);;
    	GetDlgItem(IDC_COMBO_PORT)->ShowWindow(SW_HIDE);;
    	GetDlgItem(IDC_BUT_RES)->ShowWindow(SW_HIDE);;
		m_listC.InsertColumn(0,"命令返回信息",LVCFMT_LEFT,450);
	}
	else if(chcommand == 0x5A)        //故障闭锁
	{
    	GetDlgItem(IDC_LIST_C2)->ShowWindow(SW_HIDE);
		SetWindowText("故障闭锁配置");
    	GetDlgItem(IDC_STATICV1)->ShowWindow(SW_HIDE);
    	GetDlgItem(IDC_COMBO_PORT)->ShowWindow(SW_HIDE);
    	GetDlgItem(IDC_STATICV2)->SetWindowText("故障闭锁状态");
    	GetDlgItem(IDC_BUT_RES)->ShowWindow(SW_HIDE);;

		m_SControl.Create();
		m_SControl.CursorType(adOpenDynamic);
		m_SControl.CacheSize(50);
		m_SControl._SetRecordsetEvents(new CAccountSetEvents);
		m_SControl.Open(_T("Select * From specialcontrol"), &m_Cn);
		m_SControl.MarshalOptions(adMarshalModifiedOnly);

		m_listC.InsertColumn(0,"分站号",LVCFMT_LEFT,300);
		m_listC.InsertColumn(1,"故障闭锁状态",LVCFMT_LEFT,120);
		int iItem = 0;
		m_SControl.MoveFirst();
		while ( !m_SControl.IsEOF() )
		{
				  CString dddd;
				  dddd.Format("%d",m_SControl.m_szSID);
				  m_listC.InsertItem(iItem, dddd);
				  if(m_SControl.m_szSpeCtrol)
    				  m_listC.SetItemText(iItem, 1, "使能");
				  else
    				  m_listC.SetItemText(iItem, 1, "关闭");
				  iItem++;
			m_SControl.MoveNext();
		}
	}
	else if(chcommand == 0x46)        //风电瓦斯闭锁
	{
    	GetDlgItem(IDC_LIST_C2)->ShowWindow(SW_HIDE);
		SetWindowText("风电瓦斯闭锁配置");
    	GetDlgItem(IDC_STATICV1)->ShowWindow(SW_HIDE);
    	GetDlgItem(IDC_COMBO_PORT)->ShowWindow(SW_HIDE);
    	GetDlgItem(IDC_STATICV2)->ShowWindow(SW_HIDE);
    	GetDlgItem(IDC_COMBO_FUNCTION)->ShowWindow(SW_HIDE);
    	GetDlgItem(IDC_BUT_RES)->ShowWindow(SW_HIDE);;

    	m_listC.InsertHiddenLabelColumn();	// Requires one never uses column 0
    	for(int col = 0; col < 2 ; ++col)
		{
		CString title;  int kkk;
		CGridColumnTrait* pTrait = NULL;
		if (col==0)	// Country
		{
			kkk = 300;
			title ="传感器位置";
		}
		if (col==1)	// Year won
		{
			kkk = 150;
			title ="通道号";
			unsigned char nfds = m_VERIFYT.GetCurSel()+1;
			CGridColumnTraitCombo* pComboTrait = new CGridColumnTraitCombo;
         	for(int i = 01; i < 17; i++)
			{
         		CString strItem,strtemp;
				strtemp = m_SlaveStation[nfds][i].WatchName;
				strtemp.TrimRight();
          		strItem.Format(_T("%d"), i);
              	pComboTrait->AddItem(i, strItem+strtemp);
			}
			pTrait = pComboTrait;
		}
		m_listC.InsertColumnTrait(col+1, title, LVCFMT_LEFT, kkk, col, pTrait);
		}

    	for( int iItem = 0; iItem < 6 ; iItem++)
		{
				  m_listC.InsertItem(iItem, "通断");
				  m_listC.SetItemText(iItem, 2, "");
		}
				  m_listC.SetItemText(0, 1, "进风瓦斯");
				  m_listC.SetItemText(1, 1, "回风瓦斯");
				  m_listC.SetItemText(2, 1, "串联通风");
				  m_listC.SetItemText(3, 1, "局扇");
				  m_listC.SetItemText(4, 1, "风筒风量");
				  m_listC.SetItemText(5, 1, "控制量通道");
	}
  }
  catch ( dbAx::CAxException *e )
  {
    MessageBox(e->m_szErrorDesc, _T("BJygjl Message"), MB_OK);
    delete e;
    return (FALSE);
  }


  return TRUE;  // return TRUE unless you set the focus to a control
  // EXCEPTION: OCX Property Pages should return FALSE
}

void CSetTimeDlg::OnClose()
{
  //Closing of library objects is ensured as each object
  //goes out of scope, but doing a manual shutdown doesn抰 hurt.

  try
  {
/*    if ( m_AccountSet._IsOpen() )
      m_AccountSet.Close();
    if ( m_ContactSet._IsOpen() )
      m_ContactSet.Close();
    if ( m_MAlocation._IsOpen() )
      m_MAlocation.Close();
    if ( m_PointDes._IsOpen() )
      m_PointDes.Close();
    if ( m_DisPoint._IsOpen() )
      m_DisPoint.Close();
    if ( m_Control._IsOpen() )
      m_Control.Close();*/
    if ( m_SControl._IsOpen() )
      m_SControl.Close();

    m_Cn.Close();

    //Cleanup the AxLib library
    dbAx::Term();
  }
  catch ( CAxException *e )
  {
    MessageBox(e->m_szErrorDesc, _T("BJygjl Message"), MB_OK);
    delete e;
  }

//  CDialog::OnClose();
}

void CSetTimeDlg::OnchangeComboD() 
{
	if(chcommand == 0x46)          //风电瓦斯闭锁
	{
		m_nSecond =  6;
     	m_listC.DeleteAllItems();
	    for (int iItem1 = 2; iItem1 >= 0; iItem1--)
    		m_listC.DeleteColumn(iItem1);

    	m_listC.InsertHiddenLabelColumn();	// Requires one never uses column 0
    	for(int col = 0; col < 2 ; ++col)
		{
		CString title;  int kkk;
		CGridColumnTrait* pTrait = NULL;
		if (col==0)	// Country
		{
			kkk = 200;
			title ="传感器位置";
		}
		if (col==1)	// Year won
		{
			kkk = 150;
			title ="通道号";
			unsigned char nfds = m_VERIFYT.GetCurSel()+1;
			CGridColumnTraitCombo* pComboTrait = new CGridColumnTraitCombo;
         	for(int i = 01; i < 17; i++)
			{
         		CString strItem,strtemp;
				strtemp = m_SlaveStation[nfds][i].WatchName;
				strtemp.TrimRight();
          		strItem.Format(_T("%d"), i);
              	pComboTrait->AddItem(i, strItem+strtemp);
			}
			pTrait = pComboTrait;
		}
		m_listC.InsertColumnTrait(col+1, title, LVCFMT_LEFT, kkk, col, pTrait);
		}

    	for( int iItem = 0; iItem < 6 ; iItem++)
		{
				  m_listC.InsertItem(iItem, "通断");
				  m_listC.SetItemText(iItem, 2, "");
		}
				  m_listC.SetItemText(0, 1, "进风瓦斯");
				  m_listC.SetItemText(1, 1, "回风瓦斯");
				  m_listC.SetItemText(2, 1, "串联通风");
				  m_listC.SetItemText(3, 1, "局扇");
				  m_listC.SetItemText(4, 1, "风筒风量");
				  m_listC.SetItemText(5, 1, "控制量通道");
	}
	else if(chcommand == 0x4B)   //手动控制
	{
     	m_listC.DeleteAllItems();
//	    for (int iItem1 = 2; iItem1 >= 0; iItem1--)
//    		m_listC.DeleteColumn(iItem1);
		int xxx = 0;
		int yyy = 0;
		unsigned char nfds = m_VERIFYT.GetCurSel()+1;
    	for( int iItem = 0; iItem < 8 ; iItem++)
		{
			yyy = xxx;
        	for( int i = 0; i < 64 ; i++)
			{
		      	if(m_ADCbreakE[nfds][iItem+17][i].bFSd != 0)
				{
				  m_listC.InsertItem(i+yyy, m_SlaveStation[nfds][iItem+17].WatchName);
				  m_listC.SetItemText(i+yyy, 1, m_ADCbreakE[nfds][iItem+17][i].cpoint);
				  m_listC.SetItemText(i+yyy, 2, m_ADCbreakE[nfds][iItem+17][i].adpoint);
				  xxx++;
				}
			}
		}
		m_nSecond = xxx;
	}
}

void CSetTimeDlg::OnButSend() 
{
	m_ndkSend = new  unsigned char[200];
	CString strPointNo;
	unsigned char nfds;
	if(chcommand == 0x54)   //校时
	{
		            m_ndkSend[0] = 0x7E;
		     nfds = m_VERIFYT.GetCurSel()+1;
		            m_ndkSend[1] = nfds;
		            m_ndkSend[2] = chcommand;
    	CTime t=CTime::GetCurrentTime();
					strPointNo.Format("%d",t.GetYear()-2000);
					nfds = m_Str2Data.Str2HEX(strPointNo);
		            m_ndkSend[3] = nfds;
					strPointNo.Format("%d",t.GetMonth());
					nfds = m_Str2Data.Str2HEX(strPointNo);
		            m_ndkSend[4] = nfds;
					strPointNo.Format("%d",t.GetDay());
					nfds = m_Str2Data.Str2HEX(strPointNo);
		            m_ndkSend[5] = nfds;
					strPointNo.Format("%d",t.GetDayOfWeek()-1);
					nfds = m_Str2Data.Str2HEX(strPointNo);
		            m_ndkSend[6] = nfds;
					strPointNo.Format("%d",t.GetHour());
					nfds = m_Str2Data.Str2HEX(strPointNo);
		            m_ndkSend[7] = nfds;
					strPointNo.Format("%d",t.GetMinute());
					nfds = m_Str2Data.Str2HEX(strPointNo);
		            m_ndkSend[8] = nfds;
					strPointNo.Format("%d",t.GetSecond());
					nfds = m_Str2Data.Str2HEX(strPointNo);
		            m_ndkSend[9] = nfds;
		            m_ndkSend[10] = 0x21;
    	CNDKMessage message1(VERIFYTIMER);
					message1.Add(m_ndkSend , 200);
					theApp.Sync(message1);
	}
	else if(chcommand == 0x4B)            //手动控制
	{
		            m_ndkSend[0] = 0x7E;
		     nfds = m_VERIFYT.GetCurSel()+1;
		            m_ndkSend[1] = nfds;
		            m_ndkSend[2] = chcommand;
					nfds = m_PORT.GetCurSel()+1;
		            m_ndkSend[3] = nfds;
					nfds = m_FUNCTION.GetCurSel();
		            m_ndkSend[4] = nfds;
		            m_ndkSend[5] = 0x21;
    	CNDKMessage message1(MANUALCONTROL);
					message1.Add(m_ndkSend , 200);
					theApp.Sync(message1);

					m_nchangev = chcommand;
	}
	else if(chcommand == 0x43)       //配置测点
	{
//		int nptype;
		            m_ndkSend[0] = 0x7E;
		     nfds = m_VERIFYT.GetCurSel()+1;
		            m_ndkSend[1] = nfds;
		            m_ndkSend[2] = chcommand;

        for(int i=1;i<17 ;i++)
		{
		            m_ndkSend[i*10-7] = m_SlaveStation[nfds][i].RangeH8;
		            m_ndkSend[i*10-6] = m_SlaveStation[nfds][i].RangeL8;      //
		            m_ndkSend[i*10-5] = m_SlaveStation[nfds][i].AValueH8;
		            m_ndkSend[i*10-4] = m_SlaveStation[nfds][i].AValueL8;      //
		            m_ndkSend[i*10-3] = m_SlaveStation[nfds][i].ApbrkH8;
		            m_ndkSend[i*10-2] = m_SlaveStation[nfds][i].ApbrkL8;      //
		            m_ndkSend[i*10-1] = m_SlaveStation[nfds][i].AprtnH8;
		            m_ndkSend[i*10] = m_SlaveStation[nfds][i].AprtnL8;     //
		            m_ndkSend[i*10+1] = m_SlaveStation[nfds][i].Control_state;
		            m_ndkSend[i*10+2] = m_SlaveStation[nfds][i].Channel8;      //
		}
		            m_ndkSend[163] = m_SlaveStation[nfds][0].RangeH8;      //
		            m_ndkSend[164] = m_SlaveStation[nfds][0].RangeL8;      //
		            m_ndkSend[165] = 0x21;      //

    	CNDKMessage message1(SENDCONFIG);
					message1.Add(m_ndkSend , 200);
					theApp.Sync(message1);
	}
	else if(chcommand == 0x41)            //配置分站
	{
		            m_ndkSend[0] = 0x7E;
		            m_ndkSend[1] = 0x01;
		            m_ndkSend[2] = chcommand;
        for(int nItem=0;nItem<64;nItem++)
		{
    		strPointNo=m_listC.GetItemText(nItem,2);
			if(strPointNo == "无配置")
		            m_ndkSend[nItem+3] = 0x00;
			else
		            m_ndkSend[nItem+3] = m_Str2Data.String2Int(strPointNo);
		}
		            m_ndkSend[67] = 0x21;
    	CNDKMessage message1(INFODEFINE);
					message1.Add(m_ndkSend , 200);
					theApp.Sync(message1);
        for( nItem=0;nItem<64;nItem++)
		{
            				try
							{
                             m_SControl.AbsolutePosition(nItem + 1);
         					 m_SControlNew->m_szSID = nItem+1;
	         				 m_SControlNew->m_szSerialnum = m_ndkSend[nItem+3];
					   	     m_SControlNew->Update();    //Update the recordset
							}
		     			    catch (CAxException *e)
							{
					        	AfxMessageBox(e->m_szErrorDesc, MB_OK);
				        		delete e;
							}
		}//for
		theApp.InitData();
	}
	else if(chcommand == 0x47)            //通讯测试
	{
		            m_ndkSend[0] = 0x7E;
		     nfds = m_VERIFYT.GetCurSel()+1;
		            m_ndkSend[1] = nfds;
		            m_ndkSend[2] = chcommand;
		            m_ndkSend[3] = 0x21;
    	CNDKMessage message1(TESTCOMMUNICATION);
					message1.Add(m_ndkSend , 200);
					theApp.Sync(message1);
	}
	else if(chcommand == 0x5A)            //故障闭锁
	{
				    m_ndkSend[0] = 0x7E;
		     nfds = m_VERIFYT.GetCurSel()+1;
		            m_ndkSend[1] = nfds;
		            m_ndkSend[2] = chcommand;
					nfds = m_FUNCTION.GetCurSel();
		            m_ndkSend[3] = nfds;
		            m_ndkSend[4] = 0x21;
    	CNDKMessage message1(FAULTATRESIA);
					message1.Add(m_ndkSend , 200);
					theApp.Sync(message1);

            				try
							{
                             m_SControl.AbsolutePosition(m_ndkSend[1]);
         					 m_SControlNew->m_szSID = m_ndkSend[1];
	         				 m_SControlNew->m_szSpeCtrol = (bool)m_ndkSend[3];
					   	     m_SControlNew->Update();    //Update the recordset
							}
		     			    catch (CAxException *e)
							{
					        	AfxMessageBox(e->m_szErrorDesc, MB_OK);
				        		delete e;
							}
     	m_listC.DeleteAllItems();
        if ( m_SControl._IsOpen() )
            m_SControl.Close();
		m_SControl.Create();
		m_SControl.CursorType(adOpenDynamic);
		m_SControl.CacheSize(50);
		m_SControl._SetRecordsetEvents(new CAccountSetEvents);
		m_SControl.Open(_T("Select * From specialcontrol"), &m_Cn);
		m_SControl.MarshalOptions(adMarshalModifiedOnly);
		int iItem = 0;
		m_SControl.MoveFirst();
		while ( !m_SControl.IsEOF() )
		{
				  CString dddd;
				  dddd.Format("%d",m_SControl.m_szSID);
				  m_listC.InsertItem(iItem, dddd);
				  if(m_SControl.m_szSpeCtrol)
    				  m_listC.SetItemText(iItem, 1, "使能");
				  else
    				  m_listC.SetItemText(iItem, 1, "关闭");
				  iItem++;
			m_SControl.MoveNext();
		}
		m_nSecond = 64;
		theApp.InitData();
	}
	else if(chcommand == 0x46)            //风电瓦斯闭锁
	{
		            m_ndkSend[0] = 0x7E;
		     nfds = m_VERIFYT.GetCurSel()+1;
		            m_ndkSend[1] = nfds;
		            m_ndkSend[2] = chcommand;
        for(int nItem=0;nItem<6;nItem++)
		{
    		strPointNo=m_listC.GetItemText(nItem,2);
			strPointNo = strPointNo.Mid(0,1);
			nfds = m_Str2Data.String2Int(strPointNo);
	        		m_ndkSend[nItem+3] = nfds;
		}
		            m_ndkSend[9] = 0x21;
    	CNDKMessage message1(WINDGASATRESIA);
					message1.Add(m_ndkSend , 200);
					theApp.Sync(message1);
	}
	delete m_ndkSend;
	m_ndkSend=NULL;
}

void CSetTimeDlg::OnButRES() 
{
	m_ndkSend = new  unsigned char[100];
    if(chcommand == 0x4B)   //手动控制
	{
		            m_ndkSend[0] = 0x7E;
		     unsigned char nfds = m_VERIFYT.GetCurSel()+1;
		            m_ndkSend[1] = nfds;
		            m_ndkSend[2] = chcommand;
		            m_ndkSend[3] = 0xff;
		            m_ndkSend[4] = 0x02;
		            m_ndkSend[5] = 0x21;
    	CNDKMessage message1(MANUALCONTROL);
					message1.Add(m_ndkSend , 100);
					theApp.Sync(message1);
//		m_nchangev = 0;
	}
}

void CSetTimeDlg::OnButRESre()
{
    GetDlgItem(IDC_BUT_RES)->ShowWindow(SW_HIDE);
}
void CSetTimeDlg::OnButCancel() 
{
	if(m_nchangev == 0)
	{
		OnClose();
        EndDialog(IDCANCEL);
	}
	else
        AfxMessageBox("请先点击解除按钮");
}

void CSetTimeDlg::ComDisMes(CString strmes)
{
//     	m_listC.DeleteAllItems();
        m_listC.InsertItem(m_nSecond, strmes);
//		if(chcommand == 0x46)            //风电瓦斯闭锁
        	m_listC.SetItemText(m_nSecond, 1, strmes);
		m_nSecond++;
}
