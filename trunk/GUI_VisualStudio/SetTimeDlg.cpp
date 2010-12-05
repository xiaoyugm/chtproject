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

extern CommonStr             m_CommonStr[20];
extern  ADCbreakE             m_ADCbreakE[MAX_FDS][MAX_CHAN][65];
extern  SlaveStation             m_SlaveStation[MAX_FDS][MAX_CHAN];
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
	m_nchange=0;
	//}}AFX_DATA_INIT
}


void CSetTimeDlg::DoDataExchange(CDataExchange* pDX)
{
	CXTResizeDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSetTimeDlg)
//	DDX_Text(pDX, IDC_EDIT_SECOND, m_nSecond);
//	DDV_MinMaxUInt(pDX, m_nSecond, 0, 255);
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
	ON_CBN_EDITCHANGE(IDC_COMBO_VERIFYT, OnChCBV)
	ON_CBN_EDITCHANGE(IDC_COMBO_PORT, OnChCBP)
	ON_CBN_EDITCHANGE(IDC_COMBO_FUNCTION, OnChCBF)
	ON_CBN_SELCHANGE(IDC_COMBO_PORT, OnChCBP)
	ON_CBN_SELCHANGE(IDC_COMBO_FUNCTION, OnChCBF)
    ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_C, OnItemChangedList)
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
	XTThemeManager()->SetTheme(xtThemeOffice2003);

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

	for(int i = 01; i < MAX_FDS; i++)
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
                          Data Source=") +strDBname+ _T(";Initial Catalog=BJygjl");

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
		m_listC.DeleteAllItems();
    	GetDlgItem(IDC_LIST_C2)->ShowWindow(SW_HIDE);;
		SetWindowText("手动控制操作");

		m_listC.InsertColumn(0,"命令返回信息",LVCFMT_LEFT,450);
//		m_listC.InsertColumn(1,"控制量",LVCFMT_LEFT,80);
//		m_listC.InsertColumn(2,"关联量",LVCFMT_LEFT,80);

/*		int xxx = 0;
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
		m_nSecond = xxx;*/
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
         	for(int i = 01; i < MAX_FDS; i++)
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
    	GetDlgItem(IDC_BUT_RES)->ShowWindow(SW_HIDE);
		InitWGas(0);
	}
	else if(chcommand == 0xf0)        //双风门、主扇备扇报警
	{
		m_Records1.clear();
		m_Records2.clear();
    	GetDlgItem(IDC_LIST_C2)->ShowWindow(SW_HIDE);
		SetWindowText("双设备报警逻辑管理");
    	GetDlgItem(IDOK_SEND)->SetWindowText("添加");
    	GetDlgItem(IDC_BUT_RES)->SetWindowText("删除");
    	GetDlgItem(IDC_STATICV1)->SetWindowText("开关量1");
    	GetDlgItem(IDC_STATICV2)->SetWindowText("开关量2");
    	GetDlgItem(IDC_STATICV)->SetWindowText(_T("报警态"));
//    	GetDlgItem(IDC_COMBO_VERIFYT)->ShowWindow(SW_HIDE);
	 	    m_PORT.ResetContent();
	 	    m_FUNCTION.ResetContent();
			m_VERIFYT.ResetContent();
			m_VERIFYT.AddString(_T("0态"));
			m_VERIFYT.AddString(_T("1态"));
          	m_VERIFYT.SetCurSel(0);

		m_PointDes.Create();
		m_PointDes.CursorType(adOpenDynamic);
		m_PointDes.CacheSize(50);
		m_PointDes._SetRecordsetEvents(new CAccountSetEvents);
		m_PointDes.Open(_T("Select * From pointdescription WHERE fdel=0"), &m_Cn);
		m_PointDes.MarshalOptions(adMarshalModifiedOnly);

		m_Fans.Create();
		m_Fans.CursorType(adOpenDynamic);
		m_Fans.CacheSize(50);
		m_Fans._SetRecordsetEvents(new CAccountSetEvents);
		m_Fans.Open(_T("Select * From fanscon"), &m_Cn);
		m_Fans.MarshalOptions(adMarshalModifiedOnly);

		m_PointDes.MoveFirst();
		while ( !m_PointDes.IsEOF() )
		{
    		CString dddd = m_PointDes.m_szpointnum;
    		dddd.TrimRight();
			int sfds = m_PointDes.m_szfds;
			int schan = m_PointDes.m_szchan;
			int ptype = m_PointDes.m_szptype;
			if(ptype == 10 || ptype == 13 ||ptype == 14)
			{
				dddd += "|" +m_SlaveStation[sfds][schan].WatchName;
	     	    m_PORT.AddString(dddd);
	    	    m_FUNCTION.AddString(dddd);
			}
			m_PointDes.MoveNext();
		}
	     	    m_PORT.SetCurSel(0);
	    	    m_FUNCTION.SetCurSel(0);
		m_listC.InsertColumn(0,"开关量1",LVCFMT_LEFT,60);
		m_listC.InsertColumn(1,"安装地点/名称1",LVCFMT_LEFT,200);
		m_listC.InsertColumn(2,"开关量2",LVCFMT_LEFT,60);
		m_listC.InsertColumn(3,"安装地点/名称2",LVCFMT_LEFT,200);
		m_listC.InsertColumn(4,"报警状态",LVCFMT_LEFT,60);
//		m_listC.InsertColumn(5,"ID",LVCFMT_LEFT,30);
		int iItem = 0;
		m_Fans.MoveFirst();
		while ( !m_Fans.IsEOF() )
		{
				  CString dddd = m_Fans.m_szpointnum1;
    		dddd.TrimRight();
				  m_listC.InsertItem(iItem, dddd);
				  m_Records1.push_back(dddd);
				  dddd = m_Fans.m_szName1;
    		dddd.TrimRight();
    			  m_listC.SetItemText(iItem, 1, dddd);
				  dddd = m_Fans.m_szpointnum2;
    		dddd.TrimRight();
    			  m_listC.SetItemText(iItem, 2, dddd);
				  m_Records2.push_back(dddd);
				  dddd = m_Fans.m_szName2;
    		dddd.TrimRight();
    			  m_listC.SetItemText(iItem, 3, dddd);
            dddd.Format(_T("%d态"), m_Fans.m_szAStatus);
    			  m_listC.SetItemText(iItem, 4, dddd);
 			m_nSecond = m_Fans.m_szFansID+1;
//            dddd.Format(_T("%d"), m_nSecond-1);
//    			  m_listC.SetItemText(iItem, 5, dddd);
			iItem++;
			m_Fans.MoveNext();
		}
	}
	else if(chcommand == 0xf1)            //数据显示页属性
	{
		m_Records1.clear();
    	GetDlgItem(IDC_LIST_C2)->ShowWindow(SW_HIDE);
		SetWindowText("数据显示页属性");
    	GetDlgItem(IDOK_SEND)->SetWindowText("保存");
    	GetDlgItem(IDC_BUT_RES)->ShowWindow(SW_HIDE);
    	GetDlgItem(IDC_STATICV1)->SetWindowText("文件名");
    	GetDlgItem(IDC_STATICV2)->SetWindowText("列表");
    	GetDlgItem(IDC_STATICV)->SetWindowText(_T("存表"));
    	GetDlgItem(IDC_COMBO_VERIFYT)->EnableWindow(FALSE);

		CString strPointNo,cccc,strrsy,strrsy1;
    	strrsy = gstrTimeOut + "\\" + strMetrics+ "rsy\\";
	 	    m_PORT.ResetContent();
	 	    m_FUNCTION.ResetContent();
			m_VERIFYT.ResetContent();

        for(int i =0; i < theApp.m_addfilesy.size() ;i++)
		{
    		strPointNo = theApp.m_addfilesy[i];
       		int m_ishave = strPointNo.GetLength();
    		cccc = strPointNo.Mid(m_ishave-3,3);
    		strPointNo.Replace(strrsy,"");
    		if(cccc =="rsf")
			{
				m_Records1.push_back(strPointNo);
    			m_PORT.AddString(strPointNo);
			}
		}
//          	m_VERIFYT.SetCurSel(0);
        for(int k =1; k < 4 ;k++)
		{
	    		cccc.Format("%d",k);
    	 	    m_FUNCTION.AddString(cccc);
            	m_FUNCTION.SetCurSel(0);
		}

	// Give better margin to editors
     	m_listC.SetCellMargin(1.2);
    	CGridRowTraitXP* pRowTrait = new CGridRowTraitXP;
    	m_listC.SetDefaultRowTrait(pRowTrait);
	// Create Columns
     	m_listC.InsertHiddenLabelColumn();	// Requires one never uses column 0
    	for(int col = 0; col < 2 ; ++col)
		{
    		CString title;  int kkk;
			CGridColumnTrait* pTrait = NULL;
      		if (col==0)	// Country
			{
		    	kkk = 350;
	    		title ="数据显示页属性";
			}
	    	if (col==1)	// City
			{
		    	kkk = 100;
	    		title ="参数(整数)";
      			pTrait = new CGridColumnTraitEdit;
			}
    		m_listC.InsertColumnTrait(col+1, title, LVCFMT_LEFT, kkk, col, pTrait);
		}
		CString strl[35];
//		strl[0] = "是否可见(1可见|0隐藏)";		strl[1] = "子类头控制(1或0)";
//		strl[2] = "列表左上顶点x坐标";
//		strl[3] = "列表宽度";		strl[4] = "列表高度";		strl[5] = "第一列名字";
//		strl[6] = "第一列宽度";		strl[7] = "第二列名字";		strl[8] = "第二列宽度";
//		strl[9] = "第三列名字";		strl[10] = "第三列宽度";		strl[11] = "行数";
		strl[0] = "是否可见(1可见|0隐藏)";		strl[1] = "子类头控制(1或0)";
		strl[2] = "列表左上顶点x坐标";
		strl[3] = "列表宽度";		strl[4] = "列表高度";		strl[5] = "第一列宽度";
		strl[6] = "第二列宽度";
		strl[7] = "第三列宽度";		//strl[8] = "行数";

		strl[8] = "最大值列宽度";		strl[9] = "最小值列宽度";		strl[10] = "平均值列宽度";
		strl[11] = "断电值列宽度";		strl[12] = "复电值列宽度";		strl[13] = "报警上限列宽度";
		strl[14] = "报警下限列宽度";		strl[15] = "量程高值列宽度";		strl[16] = "量程低值列宽度";
		strl[17] = "断电时刻列宽度";		strl[18] = "复电时刻列宽度";		strl[19] = "报警时刻列宽度";
		strl[20] = "馈电状态及时刻列宽度";		strl[21] = "断电范围列宽度";		strl[22] = "开停次数列宽度";	
		strl[23] = "工作时间列宽度";
		for( k =0; k < 22 ;k++)
		{
				  m_listC.InsertItem(k, "通断");
				  m_listC.SetItemText(k, 1, strl[k]);
				  m_listC.SetItemText(k, 2, "");
		}
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
    if ( m_Control._IsOpen() )
      m_Control.Close();*/
    if ( m_SControl._IsOpen() )
      m_SControl.Close();
    if ( m_PointDes._IsOpen() )
      m_PointDes.Close();
    if ( m_Fans._IsOpen() )
      m_Fans.Close();
    if ( m_CommonSet._IsOpen() )
       m_CommonSet.Close();

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

void CSetTimeDlg::OnChCBF() 
{
	UpdateData(TRUE);
		CString cccc; int nfds3;
	if(chcommand == 0xf1)            //数据显示页属性
	{
    	int  mp = m_FUNCTION.GetCurSel()+1;
//		GetDlgItem(IDC_COMBO_FUNCTION)->GetWindowText(cccc);
//		nfds3 = m_Str2Data.String2Int(cccc);
		 if(mp ==1)
		 {
            for(int k =0; k < 25 ;k++)
			{
			 if(k < 8)
    			m_listC.SetItemText(k, 2, m_CommonStr[m_nSecond].strc[k+1]);
			 else
    			m_listC.SetItemText(k, 2, m_CommonStr[m_nSecond].strc[k+2]);
			}
		 }
		 else if(mp ==2)
		 {
            for(int k =0; k < 25 ;k++)
			{
			 if(k < 8)
    			m_listC.SetItemText(k, 2, m_CommonStr[m_nSecond].strc[k+31]);
			 else
    			m_listC.SetItemText(k, 2, m_CommonStr[m_nSecond].strc[k+32]);
			}
		 }
		 else if(mp ==3)
		 {
            for(int k =0; k < 25 ;k++)
			{
			 if(k < 8)
    			m_listC.SetItemText(k, 2, m_CommonStr[m_nSecond].strc[k+61]);
			 else
    			m_listC.SetItemText(k, 2, m_CommonStr[m_nSecond].strc[k+62]);
			}
		 }
	}
}

void CSetTimeDlg::OnChCBV() 
{
	UpdateData(TRUE);
		CString cccc; int nfds3;
		GetDlgItem(IDC_COMBO_VERIFYT)->GetWindowText(cccc);
		nfds3 = m_Str2Data.String2Int(cccc);
		if(nfds3 <1 || nfds3>60)
		{
          	AfxMessageBox("分站号在1-60间选择！", MB_OK);
    		GetDlgItem(IDC_COMBO_VERIFYT)->SetWindowText("1");
	    	  return;
		}

	if(chcommand == 0x46)          //风电瓦斯闭锁
	{
		InitWGas(nfds3);
	}
	else if(chcommand == 0x4B)   //手动控制
	{
     	m_listC.DeleteAllItems();
//	    for (int iItem1 = 2; iItem1 >= 0; iItem1--)
//    		m_listC.DeleteColumn(iItem1);
		int xxx = 0;
		int yyy = 0;
		unsigned char nfds = nfds3;
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


	UpdateData(FALSE);
}

void CSetTimeDlg::OnChCBP() 
{
	UpdateData(TRUE);
		CString cccc;
		GetDlgItem(IDC_COMBO_PORT)->GetWindowText(cccc);
		int nfds3 = m_Str2Data.String2Int(cccc);
	if(chcommand != 0xf1)            //数据显示页属性
	{
		if(nfds3 <1 || nfds3>8)
		{
          	AfxMessageBox("通道号在1-8间选择！", MB_OK);
    		GetDlgItem(IDC_COMBO_PORT)->SetWindowText("1");
	    	  return;
		}
	}
	if(chcommand == 0xf1)            //数据显示页属性
	{
		m_VERIFYT.ResetContent();
    	int  mp = m_PORT.GetCurSel();
		cccc = m_Records1[mp];
//    	GetDlgItem(IDC_COMBO_VERIFYT)->EnableWindow(TRUE);
    	CString strPointNo,strrsy,strrsy1;
    	strrsy = gstrTimeOut + "\\" + strMetrics+ "rsy\\";
		int ishave=0;

		strrsy1 ="dispoint"+strMetrics;
		CppSQLite3Query q;
				strPointNo.Format("select * from '%s' WHERE DISID=1;",strrsy1);
         q = theApp.db3.execQuery(strPointNo);

        for(int k =2; k < 21 ;k++)
		{
            strPointNo = q.getStringField(k);
			strPointNo.TrimRight();
			if(cccc == strPointNo)
			{
				m_nSecond =k-1;
				ishave =k;
	    		cccc.Format("%d",k-1);
    	 	    m_VERIFYT.AddString(cccc);
            	m_VERIFYT.SetCurSel(0);
				break;
			}
		}
		if(ishave == 0)
		{
           for(int k =2; k < 21 ;k++)
		   {
            strPointNo = q.getStringField(k);
			strPointNo.TrimRight();
			if(strPointNo == "")
			{
				m_nSecond =k-1;
	    		cccc.Format("%d",k-1);
    	 	    m_VERIFYT.AddString(cccc);
            	m_VERIFYT.SetCurSel(0);
				break;
			}
		   }
		}
		m_FUNCTION.SetCurSel(0);
//		GetDlgItem(IDC_COMBO_FUNCTION)->GetWindowText(cccc);
//		nfds3 = m_Str2Data.String2Int(cccc);
//		 if(cccc =="1")
//	        m_cChWT.SetCheck(m_Str2Data.String2Int(m_CommonStr[m_ntrans].strc[105+20*(m_nlist-1)]));
         for( k =0; k < 25 ;k++)
		 {
			 if(k < 8)
    			m_listC.SetItemText(k, 2, m_CommonStr[m_nSecond].strc[k+1]);
			 else
    			m_listC.SetItemText(k, 2, m_CommonStr[m_nSecond].strc[k+2]);
		 }
/*		 else if(cccc =="2")
		 strPointNo.Format("select * from '%s' WHERE DISID>110 and DISID<120;",strrsy1);
    				  m_listC.SetItemText(ishave-111, 2, strPointNo);
		 strPointNo.Format("select * from '%s' WHERE DISID>210 and DISID<220;",strrsy1);
    				  m_listC.SetItemText(ishave-211, 2, strPointNo);
		 }*/
		q.finalize();
	}

	UpdateData(FALSE);
}

void CSetTimeDlg::OnchangeComboD() 
{
	if(chcommand == 0x46)          //风电瓦斯闭锁
	{
		InitWGas(0);
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
//        swprintf(pTTTW->szText,L"%s",strB); 
 //      swprintf((wchar_t *)pTTTW->szText,L"%s",tooltip.AllocSysString()); 
//			 _stprintf((LPTSTR)word,_T("%s"),strB); 

	m_ndkSend = new  unsigned char[200];
	CString strPointNo,cccc,strim2;
	UpdateData(TRUE);
		GetDlgItem(IDC_COMBO_VERIFYT)->GetWindowText(cccc);
		unsigned char nfds3 = m_Str2Data.String2Int(cccc);
		GetDlgItem(IDC_COMBO_PORT)->GetWindowText(cccc);
		int nfdsP = m_Str2Data.String2Int(cccc);
	unsigned char nfds =nfds3;

	if(chcommand == 0x54)   //校时
	{
		            m_ndkSend[0] = 0x7E;
		            m_ndkSend[1] = nfds3;
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
					theApp.Sync(message1,1);
       g_Log.StatusOut("校时完成。" );
	}
	else if(chcommand == 0x4B)            //手动控制
	{
		            m_ndkSend[0] = 0x7E;
		            m_ndkSend[1] = nfds3;
		            m_ndkSend[2] = chcommand;
		            m_ndkSend[3] = nfdsP;
					nfds = m_FUNCTION.GetCurSel();
					if(nfds >1)
					{
          	AfxMessageBox("请选择“吸合”或“断开”！", MB_OK);
			m_FUNCTION.SetCurSel(0);
         	delete m_ndkSend;
			return;
					}
		            m_ndkSend[4] = nfds;
		            m_ndkSend[5] = 0x21;
    	CNDKMessage message1(MANUALCONTROL);
					message1.Add(m_ndkSend , 200);
					theApp.Sync(message1,1);

					m_nchangev = chcommand;
        GetDlgItem(IDC_BUT_RES)->ShowWindow(SW_SHOW);
					strim2.Format("%x|%x|%x",nfds3,nfdsP,nfds);
       g_Log.StatusOut("手动控制：" +strim2);
	}
	else if(chcommand == 0x43)       //配置测点
	{
//		int nptype;
		            m_ndkSend[0] = 0x7E;
		            m_ndkSend[1] = nfds3;
		            m_ndkSend[2] = chcommand;
					strim2.Format("%x|%x|%x",m_ndkSend[0],m_ndkSend[1],m_ndkSend[2]);
       g_Log.StatusOut("配置测点：" + strim2 );
			ComDisMes(strim2);

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

			strim2.Format("%x|%x|%x|%x|%x|%x|%x|%x|%x|%x    %d|%d|%d|%d|%d|%d|%d|%d|%d|%d",m_ndkSend[i*10-7],m_ndkSend[i*10-6],m_ndkSend[i*10-5],m_ndkSend[i*10-4],m_ndkSend[i*10-3],m_ndkSend[i*10-2],m_ndkSend[i*10-1],
				m_ndkSend[i*10],m_ndkSend[i*10+1],m_ndkSend[i*10+2],
				m_ndkSend[i*10-7],m_ndkSend[i*10-6],m_ndkSend[i*10-5],m_ndkSend[i*10-4],m_ndkSend[i*10-3],m_ndkSend[i*10-2],m_ndkSend[i*10-1],
				m_ndkSend[i*10],m_ndkSend[i*10+1],m_ndkSend[i*10+2]);
			ComDisMes(strim2);
       g_Log.StatusOut("配置测点：" + strim2 );
//			strim1 +=strim2;
		}
		            m_ndkSend[163] = m_SlaveStation[nfds][0].RangeH8;      //控制量类型
		            m_ndkSend[164] = m_SlaveStation[nfds][0].RangeL8;      //
		            m_ndkSend[165] = 0x21;      //
					strim2.Format("%x|%x|%x",m_ndkSend[163],m_ndkSend[164],m_ndkSend[165]);
    	CNDKMessage message1(SENDCONFIG);
					message1.Add(m_ndkSend , 200);
					theApp.Sync(message1,1);
			ComDisMes(strim2);
       g_Log.StatusOut("配置测点：" + strim2 );
	}
	else if(chcommand == 0x41)            //配置分站
	{
		int n_fen;
		            m_ndkSend[0] = 0x7E;
		            m_ndkSend[1] = 0x01;
		            m_ndkSend[2] = chcommand;
        for(int nItem=0;nItem<60;nItem++)
		{
    		strPointNo=m_listC.GetItemText(nItem,2);
			n_fen = m_Str2Data.String2Int(strPointNo);
			if(n_fen >60 || n_fen <0)
				break;
			if(n_fen == 0)
	      		m_listC.SetItemText(nItem,2,"0");
              m_ndkSend[nItem+3] = n_fen;
		}
		if(n_fen >60 || n_fen <0)
		{
          	AfxMessageBox("分站号在0-60间选择！", MB_OK);
			m_listC.SetItemText(nItem,2,"0");
         	delete m_ndkSend;
			return;
		}
		            m_ndkSend[63] = 0x21;
    	CNDKMessage message1(INFODEFINE);
					message1.Add(m_ndkSend , 200);
					theApp.Sync(message1,1);
        for( nItem=0;nItem<60;nItem++)
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
					strPointNo.Format("%x|",m_ndkSend[nItem+3]);
					strim2 +=strPointNo;
		}//for
		theApp.InitData();
       g_Log.StatusOut("配置分站：" +strim2);
	}
	else if(chcommand == 0x47)            //通讯测试
	{
		            m_ndkSend[0] = 0x7E;
		            m_ndkSend[1] = nfds3;
		            m_ndkSend[2] = chcommand;
		            m_ndkSend[3] = 0x21;
    	CNDKMessage message1(TESTCOMMUNICATION);
					message1.Add(m_ndkSend , 200);
					theApp.Sync(message1,1);
 	  strim2.Format("%x",nfds3);
      g_Log.StatusOut("通讯测试:分站：" +strim2);
	}
	else if(chcommand == 0x5A)            //故障闭锁
	{
				    m_ndkSend[0] = 0x7E;
		            m_ndkSend[1] = nfds3;
		            m_ndkSend[2] = chcommand;
					nfds = m_FUNCTION.GetCurSel();
					if(nfds >1)
					{
          	AfxMessageBox("请选择“使能”或“关闭”！", MB_OK);
			m_FUNCTION.SetCurSel(0);
         	delete m_ndkSend;
			return;
					}
		            m_ndkSend[3] = nfds;
		            m_ndkSend[4] = 0x21;
    	CNDKMessage message1(FAULTATRESIA);
					message1.Add(m_ndkSend , 200);
					theApp.Sync(message1,1);

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
 	  strim2.Format("%x||%x",nfds3,m_ndkSend[3]);
      g_Log.StatusOut("故障闭锁:分站：" +strim2);

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
		bool b_gas =true;
		            m_ndkSend[0] = 0x7E;
		            m_ndkSend[1] = nfds3;
		            m_ndkSend[2] = chcommand;
        for(int nItem=0;nItem<6;nItem++)
		{
    		strPointNo=m_listC.GetItemText(nItem,2);
			if(strPointNo == "")
			{
				b_gas =false;
				break;
			}
			strPointNo = strPointNo.Mid(3,2);
			nfds = m_Str2Data.String2Int(strPointNo);
	        		m_ndkSend[nItem+3] = nfds;
		}
		if(b_gas)
		{
		            m_ndkSend[9] = 0x21;
                	CNDKMessage message1(WINDGASATRESIA);
					message1.Add(m_ndkSend , 200);
					theApp.Sync(message1,1);

        	CString strSQL;
        	for(int i =0;i<6;i++)
			{
    		strPointNo=m_listC.GetItemText(i,2);
				int k = nfds3*6 +i+1;
	strSQL.Format("UPDATE commonset SET strc30='%s' WHERE CommonID=%d;",strPointNo,k);
        	theApp.m_pConnection->Execute(_bstr_t(strSQL),NULL,adCmdText);
			strim2 +="["+ strPointNo+"]";
			}
      g_Log.StatusOut("风电瓦斯闭锁：" +strim2);
		}
		else
		{
			strPointNo.Format("第%d项不能为空！",nItem+1);
            AfxMessageBox(strPointNo);
		}
	}
	else if(chcommand == 0xf0)            //双风门、主扇备扇报警
	{
       	LPCTSTR str1 = "",str2 = "",str3 = "";
      	CString  m_strsel,m_strsel2 ,str11,str12;
		int kkk=0;
		int nItem;
            				try
							{
         					 m_Fans.m_szFansID = m_nSecond;
							 m_PORT.GetWindowText(m_strsel);
           	m_Str2Data.SplittoCString(m_strsel,str1,str2,str3);
			str11 =str1;
			m_strsel =str2;
			m_strsel +="|";
			m_strsel +=str3;
	         				 m_Fans.m_szName1 = m_strsel;
	         				 m_Fans.m_szpointnum1 = str11 ;
							 m_FUNCTION.GetWindowText(m_strsel2);
           	m_Str2Data.SplittoCString(m_strsel2,str1,str2,str3);
			str12 =str1;
			m_strsel2 =str2;
			m_strsel2 +="|";
			m_strsel2 +=str3;
	         				 m_Fans.m_szName2 = m_strsel2;
	         				 m_Fans.m_szpointnum2 = str12;
				if(str11 == str12)
				{
                 	AfxMessageBox("点号不能相同，请重选！", MB_OK);
                   	delete m_ndkSend;
          			return;
				}
				for ( int i = 0 ; i < m_Records1.size() ; i++ )
				{
    				if((str11 == m_Records1[i])&&(str12 == m_Records2[i]))
					{
						kkk =100;
                    	AfxMessageBox("关联点号已定义，请重选！", MB_OK);
                     	delete m_ndkSend;
           	    		break;
					}
				}
				if(kkk == 100)
           	    		return;

				kkk = m_Records1.size();
				  m_listC.InsertItem(kkk, str11);
    			  m_listC.SetItemText(kkk, 1, m_strsel);
    			  m_listC.SetItemText(kkk, 2, str12);
    			  m_listC.SetItemText(kkk, 3, m_strsel2);
		strim2 = str11 +"|"+m_strsel+"||||"+str12 + "|"+m_strsel2+ "|";  
            m_strsel.Format(_T("%d态"), m_VERIFYT.GetCurSel());
			strim2 += m_strsel;
    			  m_listC.SetItemText(kkk, 4, m_strsel);
            m_strsel.Format(_T("%d"), m_nSecond);
    			  m_listC.SetItemText(kkk, 5, m_strsel);

				  m_Records1.push_back(str11);
				  m_Records2.push_back(str12);
	
				m_Fans.m_szAStatus = m_VERIFYT.GetCurSel();

      						m_Fans.AddNew();  //Add a new, blank record
					   	    m_Fans.Update();    //Update the recordset
						    m_Fans.Requery();
							m_nSecond++;
							}
		     			    catch (CAxException *e)
							{
					        	AfxMessageBox(e->m_szErrorDesc, MB_OK);
				        		delete e;
							}

		theApp.InitData();
      g_Log.StatusOut("双设备报警关系添加：" +strim2);
	}
	else if(chcommand == 0xf1)            //数据显示页属性
	{
		if(m_nSecond <1)
		{
                 	AfxMessageBox("请选择文件名！", MB_OK);
          			return;
		}
    	CString strPointNo,strrsy,strrsy1,strSQL;
		int ishave=0;
		strrsy1 ="dispoint"+strMetrics;
		strrsy.Format("LP%d",m_nSecond);
		CppSQLite3Query q;
		GetDlgItem(IDC_COMBO_PORT)->GetWindowText(cccc);
//				strSQL.Format("UPDATE '%s' SET LP1='' WHERE DISID =0;",
//					strrsy1);
				strSQL.Format("UPDATE '%s' SET '%s'='%s' WHERE DISID =1;",
					strrsy1,strrsy,cccc);
             q = theApp.db3.execQuery(strSQL);
		GetDlgItem(IDC_COMBO_FUNCTION)->GetWindowText(cccc);

		 if(cccc =="1")
		 {
           for(int m =0; m < 25 ;m++)
		   {
			   if(m < 8)
				strSQL.Format("UPDATE '%s' SET '%s'='%s' WHERE DISID = %d;",
					strrsy1,strrsy,m_listC.GetItemText(m,2),m+11);
			   else
				strSQL.Format("UPDATE '%s' SET '%s'='%s' WHERE DISID = %d;",
					strrsy1,strrsy,m_listC.GetItemText(m,2),m+12);
                q = theApp.db3.execQuery(strSQL);
		   }
		 }
		 else if(cccc =="2")
		 {
           for(int m =0; m < 25 ;m++)
		   {
			   if(m < 8)
				strSQL.Format("UPDATE '%s' SET '%s'='%s' WHERE DISID = %d;",
					strrsy1,strrsy,m_listC.GetItemText(m,2),m+111);
			   else
				strSQL.Format("UPDATE '%s' SET '%s'='%s' WHERE DISID = %d;",
					strrsy1,strrsy,m_listC.GetItemText(m,2),m+112);
             q = theApp.db3.execQuery(strSQL);
		   }
		 }
		 else if(cccc =="3")
		 {
           for(int m =0; m < 25 ;m++)
		   {
			   if(m < 8)
				strSQL.Format("UPDATE '%s' SET '%s'='%s' WHERE DISID = %d;",
					strrsy1,strrsy,m_listC.GetItemText(m,2),m+211);
			   else
				strSQL.Format("UPDATE '%s' SET '%s'='%s' WHERE DISID = %d;",
					strrsy1,strrsy,m_listC.GetItemText(m,2),m+212);
             q = theApp.db3.execQuery(strSQL);
		   }
		 }
    	q.finalize();
       AfxMessageBox("保存成功！", MB_OK);
		m_nchange =1000;
	}
	delete m_ndkSend;
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
					theApp.Sync(message1,1);
//		m_nchangev = 0;
	}
    if(chcommand == 0xf0)   //双风门、主扇备扇报警
	{
    	int nItemCount=m_listC.GetItemCount();
        for(int nItem=0;nItem<nItemCount;nItem++)
		{
    		if(m_listC.GetItemState(nItem,LVIS_SELECTED) & LVIS_SELECTED)
			{
				  CString dddd = "";
				  dddd += m_listC.GetItemText(nItem,0) +"|||"+m_listC.GetItemText(nItem,1) +"|||"
					  +m_listC.GetItemText(nItem,2) +"|||"+m_listC.GetItemText(nItem,3) +"|||";
	    		m_listC.DeleteItem(nItem);
//       			nItem = m_Str2Data.String2Int(strPointNo);
      g_Log.StatusOut("双设备报警关系删除" + dddd);
	     		break;
			}
		}
		m_Fans.Delete();

        if ( m_Fans._IsOpen() )
             m_Fans.Close();
		m_Records1.clear();
		m_Records2.clear();
		m_listC.DeleteAllItems();

		m_Fans.Create();
		m_Fans.CursorType(adOpenDynamic);
		m_Fans.CacheSize(50);
		m_Fans._SetRecordsetEvents(new CAccountSetEvents);
		m_Fans.Open(_T("Select * From fanscon"), &m_Cn);
		m_Fans.MarshalOptions(adMarshalModifiedOnly);

		int iItem = 0;
		m_Fans.MoveFirst();
		while ( !m_Fans.IsEOF() )
		{
				  CString dddd = m_Fans.m_szpointnum1;
    		dddd.TrimRight();
				  m_listC.InsertItem(iItem, dddd);
				  m_Records1.push_back(dddd);
				  dddd = m_Fans.m_szName1;
    		dddd.TrimRight();
    			  m_listC.SetItemText(iItem, 1, dddd);
				  dddd = m_Fans.m_szpointnum2;
    		dddd.TrimRight();
    			  m_listC.SetItemText(iItem, 2, dddd);
				  m_Records2.push_back(dddd);
				  dddd = m_Fans.m_szName2;
    		dddd.TrimRight();
    			  m_listC.SetItemText(iItem, 3, dddd);
            dddd.Format(_T("%d态"), m_Fans.m_szAStatus);
    			  m_listC.SetItemText(iItem, 4, dddd);
 			m_nSecond = m_Fans.m_szFansID+1;
//            dddd.Format(_T("%d"), m_nSecond-1);
//    			  m_listC.SetItemText(iItem, 5, dddd);
			iItem++;
			m_Fans.MoveNext();
		}
		theApp.InitData();
	}
	delete m_ndkSend;
}

void CSetTimeDlg::OnItemChangedList(NMHDR *pNMHDR, LRESULT *pResult)
{
  LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);

   CString sTemp;          
  *pResult = 0;

  if ( pNMLV->uNewState == 3 )
  {
	  if(chcommand == 0xf0 && !m_Fans._IsEmpty() ) //
           m_Fans.AbsolutePosition(pNMLV->iItem + 1);
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
		if(m_nchange == 1000)
		{
			theApp.InitSQLite3();
        	theApp.InitDisplay();
		}
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

void CSetTimeDlg::InitWGas(int gasfds)
{
    if ( m_CommonSet._IsOpen() )
       m_CommonSet.Close();
		m_nSecond =  6;
		m_CommonSet.Create();
		m_CommonSet.CursorType(adOpenDynamic);
		m_CommonSet.CacheSize(50);
		m_CommonSet._SetRecordsetEvents(new CAccountSetEvents);
		m_CommonSet.Open(_T("Select * From commonset"), &m_Cn);
		m_CommonSet.MarshalOptions(adMarshalModifiedOnly);
		unsigned char nfds;
		if(gasfds == 0)
    		nfds= m_VERIFYT.GetCurSel()+1;
		else
    		nfds= gasfds;

		m_CommonSet.MoveFirst();
		while ( !m_CommonSet.IsEOF() )
		{
			int sfds = m_CommonSet.m_szCommonID;
			if(sfds >(nfds*6) && sfds <( (nfds+1)*6+1 ) )
			{
        		CString dddd = m_CommonSet.m_szstrc30;
				dddd.TrimRight();
				m_wgas[sfds-nfds*6-1].strl = dddd;
			}
			m_CommonSet.MoveNext();
		}

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
			int k=0;
			kkk = 250;
			title ="通道号";
			CGridColumnTraitCombo* pComboTrait = new CGridColumnTraitCombo;
         	for(int i = 01; i < MAX_CHAN; i++)
			{
         		CString strfds,strtemp,strchan;
				strtemp = m_SlaveStation[nfds][i].WatchName;
				if(strtemp != "")
				{
					int n=i;
					if(i>16)
						n = i-16;
                	strfds.Format(_T("%02d"), nfds);
                	strchan.Format(_T("%02d"), n);
					int n_ptype = m_SlaveStation[nfds][i].ptype;
					if(n_ptype < 3)
					{
                    	pComboTrait->AddItem(k, strfds+"A"+strchan+"|"+strtemp);
					    k++;
					}
					else if(n_ptype==10 || n_ptype==13 ||n_ptype==14)
					{
                    	pComboTrait->AddItem(k, strfds+"D"+strchan+"|"+strtemp);
					    k++;
					}
					else if(n_ptype == 12)
					{
                    	pComboTrait->AddItem(k, strfds+"C"+strchan+"|"+strtemp);
					    k++;
					}
				}
			}
			pTrait = pComboTrait;
		}
		m_listC.InsertColumnTrait(col+1, title, LVCFMT_LEFT, kkk, col, pTrait);
		}

    	for( int iItem = 0; iItem < 6 ; iItem++)
		{
				  m_listC.InsertItem(iItem, "通断");
				  m_listC.SetItemText(iItem, 2, m_wgas[iItem].strl);
		}
				  m_listC.SetItemText(0, 1, "进风瓦斯");
				  m_listC.SetItemText(1, 1, "回风瓦斯");
				  m_listC.SetItemText(2, 1, "串联通风");
				  m_listC.SetItemText(3, 1, "局扇");
				  m_listC.SetItemText(4, 1, "风筒风量");
				  m_listC.SetItemText(5, 1, "控制量通道");
}
