// SettingHostDlg.cpp : implementation file
//
/*
  CardFile main dialog
  10/17/2007 by Data Management Systems

  This sample application is intended to demonstrate the methods
  used to integrate the AxLib library into a project. AxLib is
  part of dbAx and provides a convenient set of classes to use
  ActiveX Data Objects (ADO) in a Visual C++ environment. The
  application developer is spared the details of interfacing
  with COM and handling variant data types.

  Procedure Summary
  1. Include the AxLib source files in your project and add a
     reference to the AxLib.h file (typically in stdafx.h)

  2. In Project Properties/Linker/Input - add a references to
     Rpcrt4.lib in the "Additional Dependencies" field

  3. Derive application specific versions of the CAxRecordset
     and CAxCommand (if neeeded) classes and add the source
     files to the project. If the AxGen utility was used to
     create these files, they will have .hpp as the file
     extension.

  4. At application startup, typically the InitInstance method
     of the main application module, make a call to the global
     AxLib function dbAx::Init(). At program termination make
     a call to the dbAx::Term function to ensure all references
     to any open connections are propery closed.

  For a full discussion of how to use the AxLib library, please
  see the dbAx.chm help file which is included as part of the
  dbAx library group.
*/

#include "stdafx.h"
#include "GUI_VisualStudio.h"
#include "SettingHostDlg.h"
#include "MainFrm.h"

#include "AddSQLDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using namespace dbAx;

extern SlaveStation             m_SlaveStation[MAX_FDS][MAX_CHAN];
extern  OthersSetting    m_OthersSetting;
extern  ADTypeTable	     m_ADTypeTable[9];
#define BoolType(b) b?true:false
/////////////////////////////////////////////////////////////////////////////
// CSettingHostDlg dialog

CSettingHostDlg::CSettingHostDlg(CWnd* pParent /*=NULL*/)
	: CXTResizeDialog(CSettingHostDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSettingHostDlg)
//	m_strHostIP = _T("");
//	m_strPort = _T("");
//	m_strTimeOut = _T("");
	m_bListColor = TRUE;
	m_bRowColor = TRUE;
	m_bSortColor = TRUE;
	sqlid = 0;
	PointDesid = 0;
	m_strtable = _T("");
	m_PointDesNew = &m_PointDes;
	m_DisPointNew = &m_DisPoint;
	m_ControlNew = &m_Control;
	m_SControlNew = &m_SControl;
	m_AxFeedENew = &m_AxFeedE;
	m_bADD = false;
	m_bSwitch = false;

	//}}AFX_DATA_INIT
}

void CSettingHostDlg::DoDataExchange(CDataExchange* pDX)
{
	CXTResizeDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSettingHostDlg)
//	DDX_Text(pDX, IDC_EDIT_HOST_IP, m_strHostIP);
//	DDV_MaxChars(pDX, m_strHostIP, 15);
//	DDX_Text(pDX, IDC_EDIT_PORT, m_strPort);
//	DDX_Text(pDX, IDC_EDIT_TIMEOUT, m_strTimeOut);
	DDX_Control(pDX, IDC_COMBO1, m_wndComboSize1);
	DDX_Control(pDX, IDC_COMBO2, m_wndComboSize2);
	DDX_Control(pDX, IDC_COMBO3, m_wndComboSize3);
	DDX_Control(pDX, IDC_COMBO4, m_wndComboSize4);
	DDX_Control(pDX, IDC_LIST_CTRL, m_listCtrl);
	DDX_Control(pDX, IDC_LIST_DISPLAY, m_listDis);
	DDX_Control(pDX, IDC_CLR_SORTBACK, m_cpSortBack);
	DDX_Control(pDX, IDC_CHECK_ISALM, m_ctrlCheckAlm);
    //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSettingHostDlg, CXTResizeDialog)
	//{{AFX_MSG_MAP(CSettingHostDlg)
		// NOTE: the ClassWizard will add message map macros here
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
    ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_CTRL, OnItemChangedList)
	ON_BN_CLICKED(IDC_BUT_ADD, OnBtnADD)
	ON_BN_CLICKED(IDC_BUT_ADD2, OnBtnADD2)
	ON_BN_CLICKED(IDC_BUT_DEL, OnBtnDEL)
	ON_BN_CLICKED(IDC_BUT_MOD, OnBtnMOD)
	ON_BN_CLICKED(IDOKADM, OnBtnOK)
	ON_BN_CLICKED(IDCANCELADM, OnBtnCANCEL)
	ON_BN_CLICKED(IDC_BUTTONDIS1, OnButtonSelect)
	ON_BN_CLICKED(IDC_BUTTONDIS2, OnButtonDeselect)
	ON_BN_CLICKED(IDC_BUTTONDIS3, OnButtonSelectall)
	ON_BN_CLICKED(IDC_BUTTONDIS4, OnButtonDeselectall)
	ON_BN_CLICKED(IDC_BUTTONDIS5, OnButtonSave)
//	ON_BN_CLICKED(IDC_BUTTONDIS6, OnButtonCANCEL)
	ON_CBN_SELCHANGE(IDC_COMBO3, OnchangeComboF)
	ON_CBN_SELCHANGE(IDC_COMBO2, OnchangeCombo2)
	ON_CBN_EDITCHANGE(IDC_COMBO3, OnChCB03)
	ON_CBN_EDITCHANGE(IDC_COMBO4, OnChCB04)
//	ON_CBN_EDITCHANGE(IDC_COMBO2, OnChCB02)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSettingHostDlg message handlers
BOOL CSettingHostDlg::OnInitDialog()
{
	CXTResizeDialog::OnInitDialog();

	CMainFrame* pFWnd=(CMainFrame*)AfxGetMainWnd();
   	pFWnd->m_pSetHostDlg=this;

	// TODO: Add extra initialization here
    if ( !ConnectToProvider() )
       return (FALSE);
	
	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);         // Set big icon
	SetIcon(m_hIcon, FALSE);        // Set small icon

	// Set control resizing.
//	SetResize(IDOK,                  SZ_TOP_RIGHT,   SZ_TOP_RIGHT);
	SetResize(IDOKADM,                  SZ_BOTTOM_LEFT,   SZ_BOTTOM_LEFT);
	SetResize(IDCANCELADM,              SZ_BOTTOM_LEFT,   SZ_BOTTOM_LEFT);
	SetResize(IDCANCEL,              SZ_BOTTOM_LEFT,   SZ_BOTTOM_LEFT);

	CRect   rectDialog;  
    GetClientRect(&rectDialog);  
    int   nWidth   =   rectDialog.right   -   rectDialog.left;  
    int   nHeight   =   rectDialog.bottom   -   rectDialog.top;  
	if(m_ADTypeTable[4].TableName == m_strtable || m_strtable == "AddControl" || m_strtable == "AddFeedE")
	{
		GetDlgItem(IDC_LIST_CTRL)->MoveWindow(CRect(8,5,nWidth/2+10 ,nHeight-15));
    	SetResize(IDC_LIST_CTRL,         SZ_TOP_LEFT,    SZ_BOTTOM_CENTER);
		if(m_strtable == "AddControl"  || m_strtable == "AddFeedE" ||m_ADTypeTable[4].TableName == m_strtable)  //加控制策略
		{
        	GetDlgItem(IDC_LIST_DISPLAY)->MoveWindow(nWidth/2+150,5,nWidth/2-168  ,nHeight-20);
        	GetDlgItem(IDC_COMBO3)->MoveWindow(nWidth/2 + 88,nHeight-84,40 ,20);
        	GetDlgItem(IDC_STATIC3)->MoveWindow(nWidth/2 + 35,nHeight-80,50 ,20);
        	GetDlgItem(IDC_COMBO2)->MoveWindow(nWidth/2 + 35,nHeight-35,90 ,20);
        	GetDlgItem(IDC_STATIC2)->MoveWindow(nWidth/2 + 35,nHeight-50,50 ,15);
        	GetDlgItem(IDC_CHECK_ISALM)->MoveWindow(nWidth/2 + 40,nHeight-160,100 ,20);
		}
		else
        	GetDlgItem(IDC_LIST_DISPLAY)->MoveWindow(CRect(nWidth/2+180,5,10 ,nHeight-15));
    	SetResize(IDC_LIST_DISPLAY,         SZ_TOP_CENTER,    SZ_BOTTOM_RIGHT);
	}
 	else
	{
    	if(m_ADTypeTable[1].TableName ==  m_strtable || m_ADTypeTable[5].TableName ==  m_strtable)//开关量
           	GetDlgItem(IDC_LIST_CTRL)->MoveWindow(CRect(8,5,nWidth-13 ,nHeight-40));
		else
           	GetDlgItem(IDC_LIST_CTRL)->MoveWindow(CRect(8,5,nWidth-13 ,nHeight-70));
    	SetResize(IDC_LIST_CTRL,         SZ_TOP_LEFT,    SZ_BOTTOM_RIGHT);
	}
//	SetResize(IDC_GBOX_HEADER,       SZ_BOTTOM_LEFT, SZ_BOTTOM_RIGHT);
	SetResize(IDC_BUT_ADD,      SZ_BOTTOM_LEFT, SZ_BOTTOM_LEFT);
	SetResize(IDC_BUT_ADD2,      SZ_BOTTOM_LEFT, SZ_BOTTOM_LEFT);
	SetResize(IDC_BUT_DEL,      SZ_BOTTOM_LEFT, SZ_BOTTOM_LEFT);
	SetResize(IDC_BUT_MOD,      SZ_BOTTOM_LEFT, SZ_BOTTOM_LEFT);

	SetResize(IDC_COMBO1,      SZ_BOTTOM_LEFT, SZ_BOTTOM_LEFT);
	SetResize(IDC_COMBO2,      SZ_BOTTOM_LEFT, SZ_BOTTOM_LEFT);
	SetResize(IDC_COMBO4,      SZ_BOTTOM_LEFT, SZ_BOTTOM_LEFT);
	SetResize(IDC_STATIC1,      SZ_BOTTOM_LEFT, SZ_BOTTOM_LEFT);
	SetResize(IDC_STATIC2,      SZ_BOTTOM_LEFT, SZ_BOTTOM_LEFT);
	SetResize(IDC_STATIC4,      SZ_BOTTOM_LEFT, SZ_BOTTOM_LEFT);

		if(m_strtable == "AddControl" ||m_strtable == "AddFeedE")  //加控制策略
		{
	SetResize(IDC_STATIC3,      SZ_MIDDLE_CENTER, SZ_MIDDLE_CENTER);
	SetResize(IDC_COMBO3,      SZ_MIDDLE_CENTER, SZ_MIDDLE_CENTER);
	SetResize(IDC_CHECK_ISALM,      SZ_MIDDLE_CENTER, SZ_MIDDLE_CENTER);
		}
		else
		{
  	SetResize(IDC_STATIC3,      SZ_BOTTOM_LEFT, SZ_BOTTOM_LEFT);
	SetResize(IDC_COMBO3,      SZ_BOTTOM_LEFT, SZ_BOTTOM_LEFT);
	SetResize(IDC_CHECK_ISALM,      SZ_BOTTOM_LEFT, SZ_BOTTOM_LEFT);
		}
	SetResize(IDC_BUTTONDIS1,      SZ_MIDDLE_CENTER, SZ_MIDDLE_CENTER);
	SetResize(IDC_BUTTONDIS2,      SZ_MIDDLE_CENTER, SZ_MIDDLE_CENTER);
	SetResize(IDC_BUTTONDIS3,      SZ_MIDDLE_CENTER, SZ_MIDDLE_CENTER);
	SetResize(IDC_BUTTONDIS4,      SZ_MIDDLE_CENTER, SZ_MIDDLE_CENTER);
	SetResize(IDC_BUTTONDIS5,      SZ_MIDDLE_CENTER, SZ_MIDDLE_CENTER);
	SetResize(IDC_BUTTONDIS6,      SZ_MIDDLE_CENTER, SZ_MIDDLE_CENTER);
	// insert strings into the size combo box.
		CString strItem;
	for(int i = 01; i < MAX_FDS; i++)
	{
		strItem.Format(_T("%d"), i);
    	m_wndComboSize3.AddString(strItem);
       		if(i<17)
            	m_wndComboSize4.AddString(strItem);
	}
		m_wndComboSize3.SetCurSel(0);
		m_wndComboSize4.SetCurSel(0);

	if(m_ADTypeTable[4].TableName == m_strtable)
	{
    	m_wndComboSize2.AddString(_T("电流电压型"));
    	m_wndComboSize2.AddString(_T("频率型"));
    	m_wndComboSize2.AddString(_T("频率型(累计)"));
        m_wndComboSize2.AddString("二态开关量");     //10  ptype
        m_wndComboSize2.AddString("分站");           //11
        m_wndComboSize2.AddString("控制量");     //12
        m_wndComboSize2.AddString("三态开关量");     //13
        m_wndComboSize2.AddString("通断量");         //14
	}
	else
	{
    	m_wndComboSize2.AddString(_T("电流电压型"));
    	m_wndComboSize2.AddString(_T("频率型"));
    	m_wndComboSize2.AddString(_T("频率型(累计)"));
	}
		m_wndComboSize2.SetCurSel(0);

		m_MAlocation.MoveFirst();
		while ( !m_MAlocation.IsEOF() )
		{
			strItem = m_MAlocation.m_szName;
			strItem.TrimRight();
        	m_wndComboSize1.AddString(strItem);
			m_MAlocation.MoveNext();
		}
        m_MAlocation.MoveFirst();
		m_wndComboSize1.SetCurSel(0);

		m_ctrlCheckAlm.SetCheck(1);

	// Enable Office XP themes.
	XTThemeManager()->SetTheme(xtThemeOffice2003);

	// Load window placement
//	LoadPlacement(_T("CListCtrlDlg"));
	// Get the windows handle to the header control for the
	// list control then subclass the control.
	HWND hWndHeader = m_listCtrl.GetDlgItem(0)->GetSafeHwnd();
	if(sqlid != 1)
	{
    	m_header.SubclassWindow(hWndHeader);
		sqlid = 1;
	}
	// add bitmap images.
//	m_header.SetBitmap(0, IDB_COLUMN_0, FALSE, RGB(0,255,0));
//	m_header.SetBitmap(1, IDB_COLUMN_1, FALSE, RGB(0,255,0));
//	m_header.SetBitmap(2, IDB_COLUMN_2, FALSE, RGB(0,255,0));

	// enable auto sizing.
//	m_header.EnableAutoSize(TRUE);
//	m_header.ResizeColumnsToFit();
//	SortColumn(m_nSortedCol, m_bAscending);

	m_cpSortBack.ShowText(TRUE);
	m_cpSortBack.SetColor(m_listCtrl.GetSortBackColor());
	m_cpSortBack.SetDefaultColor(m_listCtrl.GetSortBackColor());

/*	m_cpSortText.ShowText(TRUE);
	m_cpSortText.SetColor(m_listCtrl.GetSortTextColor());
	m_cpSortText.SetDefaultColor(m_listCtrl.GetSortTextColor());

	m_cpListBack.ShowText(TRUE);
	m_cpListBack.SetColor(m_listCtrl.GetListBackColor());
	m_cpListBack.SetDefaultColor(m_listCtrl.GetListBackColor());

	m_cpListText.ShowText(TRUE);
	m_cpListText.SetColor(m_listCtrl.GetListTextColor());
	m_cpListText.SetDefaultColor(m_listCtrl.GetListTextColor());

	m_cpRowBack.ShowText(TRUE);
	m_cpRowText.SetColor(m_listCtrl.GetListTextColor());
	m_cpRowBack.SetDefaultColor(m_listCtrl.GetListBackColor());

	m_cpRowText.ShowText(TRUE);
	m_cpRowBack.SetColor(m_listCtrl.GetListBackColor());
	m_cpRowText.SetDefaultColor(m_listCtrl.GetListTextColor());
*/

//	OnSelendokComboThemes();
	m_listCtrl.ModifyExtendedStyle(0, LVS_EX_FULLROWSELECT|LVS_SHOWSELALWAYS | LVS_EX_GRIDLINES);
	m_listCtrl.EnableUserSortColor(BoolType(m_bSortColor));
	m_listCtrl.EnableUserListColor(BoolType(m_bListColor));
	m_listCtrl.EnableUserRowColor(BoolType(m_bRowColor));
	m_listDis.ModifyExtendedStyle(0, LVS_EX_FULLROWSELECT|LVS_SHOWSELALWAYS | LVS_EX_GRIDLINES);


	if(m_ADTypeTable[0].TableName ==  m_strtable)   //模拟量
         InsA();
	if(m_ADTypeTable[1].TableName ==  m_strtable)//开关量
         InsD();
	if(m_ADTypeTable[2].TableName ==  m_strtable)  //安装地点
	{
    	HideDISPLAY();
		HideControls();
		SetWindowText(_T(m_ADTypeTable[2].NameD));
//		SetWindowPos(NULL, 100, 100, 200, 500, SWP_NOZORDER);
		m_listCtrl.InsertColumn(0,m_ADTypeTable[2].m_DTypeTFD.Name,LVCFMT_LEFT,300);
	}
	if(m_ADTypeTable[3].TableName ==  m_strtable)     //pointdescription
         InsP();
	if(m_ADTypeTable[4].TableName ==  m_strtable)    //选择测点显示
         InsDIS();
	if(m_ADTypeTable[5].TableName ==  m_strtable)   //控制策略显示
         InsC();
	if(m_strtable == "AddControl")    //加控制策略
         InsAddC();
	if("feedelectricity" ==  m_strtable)   //馈电策略显示
         Insfeed();
	if(m_strtable == "AddFeedE")    //加馈电策略
         InsAddfeed();

    BuildAccountList();

	return TRUE;  // return TRUE  unless you set the focus to a control 
}

//BuildAccountList will populate the Account list with all
//available records. This method is called on startup and 
//each time a new Account record is added, edited, or deleted
void CSettingHostDlg::BuildAccountList()
{
    m_listCtrl.DeleteAllItems();
	LPCTSTR str1 = "",str2 = "",str3 = "";
    CString dddd;
  try
  {
	  if(m_ADTypeTable[1].TableName ==  m_strtable)//开关量
	  {
		if ( m_AccountSet._IsEmpty() )
		  return;
		m_listCtrl.SetItemCount(m_AccountSet.RecordCount());
		int iItem = 0;
		m_AccountSet.MoveFirst();
		while ( !m_AccountSet.IsEOF() )
		{
				  dddd = m_AccountSet.m_szName;
				  dddd.TrimRight();
				  m_listCtrl.InsertItem(iItem, dddd);
			//		dddd = m_AccountSet.m_szptype;
			//		bool xxx = m_AccountSet.m_szfdel;
				  dddd = m_AccountSet.m_szname0;
				  dddd.TrimRight();
				  m_listCtrl.SetItemText(iItem, 1, dddd);
				  dddd = m_AccountSet.m_szname1;
				  dddd.TrimRight();
				  m_listCtrl.SetItemText(iItem, 2, dddd);
				  dddd = m_AccountSet.m_szname2;
				  dddd.TrimRight();
				  m_listCtrl.SetItemText(iItem, 3, dddd);

				  int xxx = m_AccountSet.m_szpalms;
				  if(xxx == 0)
					  dddd = "不报警";
				  else if(xxx == 1)
					  dddd = "0态报警";
				  else if(xxx == 2)
					  dddd = "1态报警";
				  else if(xxx == 3)
					  dddd = "0态断电";
				  else if(xxx == 4)
					  dddd = "1态断电";
				  else if(xxx == 5)
					  dddd = "常开";
				  else if(xxx == 6)
					  dddd = "常闭";
				  else if(xxx == 7)
					  dddd = "电平";

				  m_listCtrl.SetItemText(iItem, 4, dddd);

				  dddd = m_AccountSet.m_szfalm;
				  dddd.TrimRight();
				  m_listCtrl.SetItemText(iItem, 5, dddd);
				  COleDateTime oleDateTime=m_AccountSet.m_szrecdate;
			//	  CString   str   =   oleDateTime.Format(_T("%A, %B %d, %Y")); 
				  CString   str   =   oleDateTime.Format(_T("%Y-%m-%d %H:%M:%S")); 
			//	  oleDateTime = m_AccountSet.m_szdeldate;
				  m_listCtrl.SetItemText(iItem, 6, str);
				  dddd = m_AccountSet.m_szUseridadd;
				  dddd.TrimRight();
				  m_listCtrl.SetItemText(iItem, 7, dddd);

				  if(m_AccountSet.m_szptype == 0)
					  dddd = "二态开关量";
				  else if(m_AccountSet.m_szptype == 1)
					  dddd = "分站";
				  else if(m_AccountSet.m_szptype == 2)
					  dddd = "控制量";
				  else if(m_AccountSet.m_szptype == 3)
					  dddd = "三态开关量";
				  else if(m_AccountSet.m_szptype == 4)
					  dddd = "通断量";
				  m_listCtrl.SetItemText(iItem, 8, dddd);
			iItem++;
			sqlid = m_AccountSet.m_szDID +1;
			m_AccountSet.MoveNext();
		}
	  }
	  else if(m_ADTypeTable[0].TableName ==  m_strtable)   //模拟量
	  {
		if ( m_ContactSet._IsEmpty() )
		  return;
		m_listCtrl.SetItemCount(m_ContactSet.RecordCount());
		int iItem = 0;
		m_ContactSet.MoveFirst();
		while ( !m_ContactSet.IsEOF() )
		{
				  dddd = m_ContactSet.m_szName;
				  dddd.TrimRight();
				  m_listCtrl.InsertItem(iItem, dddd);
				  dddd.Format("%.2f",m_ContactSet.m_szltop);
				  m_listCtrl.SetItemText(iItem, 1, dddd);
				  dddd.Format("%.2f",m_ContactSet.m_szlbom);
				  m_listCtrl.SetItemText(iItem, 2, dddd);
				  dddd.Format("%.2f",m_ContactSet.m_szpalmu);
				  m_listCtrl.SetItemText(iItem, 3, dddd);
				  dddd.Format("%.2f",m_ContactSet.m_szpalmd);
				  m_listCtrl.SetItemText(iItem, 4, dddd);
				  dddd.Format("%.2f",m_ContactSet.m_szpbrk);
				  m_listCtrl.SetItemText(iItem, 5, dddd);
				  dddd.Format("%.2f",m_ContactSet.m_szprtn);
				  m_listCtrl.SetItemText(iItem, 6, dddd);
				  dddd = m_ContactSet.m_szfalm;
				  dddd.TrimRight();
				  m_listCtrl.SetItemText(iItem, 7, dddd);
				  dddd = m_ContactSet.m_szpunit;
				  dddd.TrimRight();
				  m_listCtrl.SetItemText(iItem, 8, dddd);
				  COleDateTime oleDateTime=m_ContactSet.m_szrecdate;
				  dddd   =   oleDateTime.Format(_T("%Y-%m-%d %H:%M:%S")); 
				  m_listCtrl.SetItemText(iItem, 9, dddd);
				  dddd = m_ContactSet.m_szUseridadd;
				  dddd.TrimRight();
				  m_listCtrl.SetItemText(iItem, 10, dddd);
			iItem++;
			sqlid = m_ContactSet.m_szAID +1;
			m_ContactSet.MoveNext();
		}
	  }
	  else if(m_ADTypeTable[2].TableName ==  m_strtable)    //安装地点
	  {
		if ( m_MAlocation._IsEmpty() )
		  return;
		m_listCtrl.SetItemCount(m_MAlocation.RecordCount());
		int iItem = 0;
		m_MAlocation.MoveFirst();
		while ( !m_MAlocation.IsEOF() )
		{
				  dddd = m_MAlocation.m_szName;
				  dddd.TrimRight();
    		  m_listCtrl.InsertItem(iItem, dddd);
			iItem++;
			sqlid = m_MAlocation.m_szlocationID +1;
			m_MAlocation.MoveNext();
		}
	  }
	  else if(m_ADTypeTable[3].TableName ==  m_strtable)   //pointdescription
	  {
		if ( m_PointDes._IsEmpty() )
		  return;
		m_listCtrl.SetItemCount(m_PointDes.RecordCount());
		int iItem = 0;
        m_Records.clear();
		m_PointDes.MoveFirst();
		while ( !m_PointDes.IsEOF() )
		{
    		int nfds = m_PointDes.m_szfds;
    		int nchan = m_PointDes.m_szchan;
    		m_listCtrl.InsertItem(iItem, m_SlaveStation[nfds][nchan].WatchName);
				  dddd = m_PointDes.m_szpointnum;
				  dddd.TrimRight();
    		m_listCtrl.SetItemText(iItem, 1, dddd);
				  dddd = m_PointDes.m_szutype;
				  dddd.TrimRight();
			m_listCtrl.SetItemText(iItem, 2, dddd);
				  dddd.Format("%d",m_PointDes.m_szPID);
			m_listCtrl.SetItemText(iItem, 3, dddd);
			iItem++;
			PointDesid = m_PointDes.m_szPID +1;
				  dddd = m_PointDes.m_szpointnum;
				  dddd.TrimRight();
			m_Records.push_back(dddd );
			m_PointDes.MoveNext();
		}
	  }
	  else if(m_ADTypeTable[4].TableName ==  m_strtable)    //选择测点显示
	  {
    	if ( m_DisPoint._IsEmpty() )
		{
      		m_bADD =true;
   		    return;
		}
//		m_listDis.SetItemCount(m_DisPoint.RecordCount());
        m_Records.clear();
		m_DisPoint.MoveFirst();
		while ( !m_DisPoint.IsEOF() )
		{
			if( m_DisPoint.m_szDISID == PointDesid)
			{
    			m_bADD =false;
				str1 = "",str2 = "",str3 = "";
					m_DisPoint.m_szstr0.TrimRight();
				if(m_DisPoint.m_szstr0 != "")
				{
                	m_Str2Data.SplittoCString(m_DisPoint.m_szstr0,str1,str2,str3);
					pushDIS(str1);  pushDIS(str2);   pushDIS(str3);
				}
				str1 = "",str2 = "",str3 = "";
					m_DisPoint.m_szstr1.TrimRight();
				if(m_DisPoint.m_szstr1 != "")
				{
                	m_Str2Data.SplittoCString(m_DisPoint.m_szstr1,str1,str2,str3);
					pushDIS(str1);  pushDIS(str2);   pushDIS(str3);
				}
				str1 = "",str2 = "",str3 = "";
					m_DisPoint.m_szstr2.TrimRight();
				if(m_DisPoint.m_szstr2 != "")
				{
                	m_Str2Data.SplittoCString(m_DisPoint.m_szstr2,str1,str2,str3);
					pushDIS(str1);  pushDIS(str2);   pushDIS(str3);
				}
				str1 = "",str2 = "",str3 = "";
					m_DisPoint.m_szstr3.TrimRight();
				if(m_DisPoint.m_szstr3 != "")
				{
                	m_Str2Data.SplittoCString(m_DisPoint.m_szstr3,str1,str2,str3);
					pushDIS(str1);  pushDIS(str2);   pushDIS(str3);
				}
				str1 = "",str2 = "",str3 = "";
					m_DisPoint.m_szstr4.TrimRight();
				if(m_DisPoint.m_szstr4 != "")
				{
                	m_Str2Data.SplittoCString(m_DisPoint.m_szstr4,str1,str2,str3);
					pushDIS(str1);  pushDIS(str2);   pushDIS(str3);
				}
				str1 = "",str2 = "",str3 = "";
					m_DisPoint.m_szstr5.TrimRight();
				if(m_DisPoint.m_szstr5 != "")
				{
                	m_Str2Data.SplittoCString(m_DisPoint.m_szstr5,str1,str2,str3);
					pushDIS(str1);  pushDIS(str2);   pushDIS(str3);
				}
				str1 = "",str2 = "",str3 = "";
					m_DisPoint.m_szstr6.TrimRight();
				if(m_DisPoint.m_szstr6 != "")
				{
                	m_Str2Data.SplittoCString(m_DisPoint.m_szstr6,str1,str2,str3);
					pushDIS(str1);  pushDIS(str2);   pushDIS(str3);
				}
				str1 = "",str2 = "",str3 = "";
					m_DisPoint.m_szstr7.TrimRight();
				if(m_DisPoint.m_szstr7 != "")
				{
                	m_Str2Data.SplittoCString(m_DisPoint.m_szstr7,str1,str2,str3);
					pushDIS(str1);  pushDIS(str2);   pushDIS(str3);
				}
				str1 = "",str2 = "",str3 = "";
					m_DisPoint.m_szstr8.TrimRight();
				if(m_DisPoint.m_szstr8 != "")
				{
                	m_Str2Data.SplittoCString(m_DisPoint.m_szstr8,str1,str2,str3);
					pushDIS(str1);  pushDIS(str2);   pushDIS(str3);
				}
				str1 = "",str2 = "",str3 = "";
					m_DisPoint.m_szstr9.TrimRight();
				if(m_DisPoint.m_szstr9 != "")
				{
                	m_Str2Data.SplittoCString(m_DisPoint.m_szstr9,str1,str2,str3);
					pushDIS(str1);  pushDIS(str2);   pushDIS(str3);
				}
				str1 = "",str2 = "",str3 = "";
					m_DisPoint.m_szstr10.TrimRight();
				if(m_DisPoint.m_szstr10 != "")
				{
                	m_Str2Data.SplittoCString(m_DisPoint.m_szstr10,str1,str2,str3);
					pushDIS(str1);  pushDIS(str2);   pushDIS(str3);
				}
				str1 = "",str2 = "",str3 = "";
					m_DisPoint.m_szstr11.TrimRight();
				if(m_DisPoint.m_szstr11 != "")
				{
                	m_Str2Data.SplittoCString(m_DisPoint.m_szstr11,str1,str2,str3);
					pushDIS(str1);  pushDIS(str2);   pushDIS(str3);
				}
				str1 = "",str2 = "",str3 = "";
					m_DisPoint.m_szstr12.TrimRight();
				if(m_DisPoint.m_szstr12 != "")
				{
                	m_Str2Data.SplittoCString(m_DisPoint.m_szstr12,str1,str2,str3);
					pushDIS(str1);  pushDIS(str2);   pushDIS(str3);
				}
				str1 = "",str2 = "",str3 = "";
					m_DisPoint.m_szstr13.TrimRight();
				if(m_DisPoint.m_szstr13 != "")
				{
                	m_Str2Data.SplittoCString(m_DisPoint.m_szstr13,str1,str2,str3);
					pushDIS(str1);  pushDIS(str2);   pushDIS(str3);
				}
				str1 = "",str2 = "",str3 = "";
					m_DisPoint.m_szstr14.TrimRight();
				if(m_DisPoint.m_szstr14 != "")
				{
                	m_Str2Data.SplittoCString(m_DisPoint.m_szstr14,str1,str2,str3);
					pushDIS(str1);  pushDIS(str2);   pushDIS(str3);
				}
				str1 = "",str2 = "",str3 = "";
					m_DisPoint.m_szstr15.TrimRight();
				if(m_DisPoint.m_szstr15 != "")
				{
                	m_Str2Data.SplittoCString(m_DisPoint.m_szstr15,str1,str2,str3);
					pushDIS(str1);  pushDIS(str2);   pushDIS(str3);
				}
				str1 = "",str2 = "",str3 = "";
					m_DisPoint.m_szstr16.TrimRight();
				if(m_DisPoint.m_szstr16 != "")
				{
                	m_Str2Data.SplittoCString(m_DisPoint.m_szstr16,str1,str2,str3);
					pushDIS(str1);  pushDIS(str2);   pushDIS(str3);
				}
				str1 = "",str2 = "",str3 = "";
					m_DisPoint.m_szstr17.TrimRight();
				if(m_DisPoint.m_szstr17 != "")
				{
                	m_Str2Data.SplittoCString(m_DisPoint.m_szstr17,str1,str2,str3);
					pushDIS(str1);  pushDIS(str2);   pushDIS(str3);
				}
				str1 = "",str2 = "",str3 = "";
					m_DisPoint.m_szstr18.TrimRight();
				if(m_DisPoint.m_szstr18 != "")
				{
                	m_Str2Data.SplittoCString(m_DisPoint.m_szstr18,str1,str2,str3);
					pushDIS(str1);  pushDIS(str2);   pushDIS(str3);
				}
				str1 = "",str2 = "",str3 = "";
					m_DisPoint.m_szstr19.TrimRight();
				if(m_DisPoint.m_szstr19 != "")
				{
                	m_Str2Data.SplittoCString(m_DisPoint.m_szstr19,str1,str2,str3);
					pushDIS(str1);  pushDIS(str2);   pushDIS(str3);
				}
				break;
			}
			else
        		m_bADD =true;
			m_DisPoint.MoveNext();
		}

		if ( m_PointDes._IsEmpty() )
		  return;
		m_listCtrl.SetItemCount(m_PointDes.RecordCount());
		int iItem = 0;
//        m_Records.clear();
		m_PointDes.MoveFirst();
		while ( !m_PointDes.IsEOF() )
		{
    		int nfds = m_PointDes.m_szfds;
    		int nchan = m_PointDes.m_szchan;
    		dddd = m_SlaveStation[nfds][nchan].WatchName;
//     	m_Str2Data.SplittoCString(dddd,str1,str2,str3);
    		m_listCtrl.InsertItem(iItem, dddd);
			dddd = m_PointDes.m_szpointnum;
			dddd.TrimRight();
    		m_listCtrl.SetItemText(iItem, 1, dddd);
			dddd = m_PointDes.m_szutype;
			dddd.TrimRight();
			m_listCtrl.SetItemText(iItem, 2, dddd);
			iItem++;
			m_PointDes.MoveNext();
		}

		for ( int i = 0 ; i < m_Records.size() ; i++ )
            	m_listDis.InsertItem(i, m_Records[i]);
	  }
	  else if(m_ADTypeTable[5].TableName ==  m_strtable)  //控制策略显示
	  {
		if ( m_Control._IsEmpty() )
		  return;
     	m_listCtrl.DeleteAllItems();
		m_listCtrl.SetItemCount(m_Control.RecordCount());
        m_Records.clear();
		int iItem = 0;
		m_Control.MoveFirst();
		while ( !m_Control.IsEOF() )
		{
        	CString  strf,strc;
			dddd = m_Control.m_szpointnum;
			dddd.TrimRight();
    		strf = dddd.Mid(0,2);
    		strc = dddd.Mid(3);
	    	int nfds = m_Str2Data.String2Int(strf);
	    	int nchan = m_Str2Data.String2Int(strc);

			m_listCtrl.InsertItem(iItem, m_SlaveStation[nfds][nchan].WatchName);
    		m_listCtrl.SetItemText(iItem, 1, dddd);
				  dddd = m_Control.m_szcpointnum;
				  dddd.TrimRight();
			m_listCtrl.SetItemText(iItem, 2, dddd);
				  dddd.Format("%d",m_Control.m_szByFds);
    		m_listCtrl.SetItemText(iItem, 3, dddd);
				  COleDateTime oleDateTime=m_Control.m_szrecdate;
				  dddd   =   oleDateTime.Format(_T("%Y-%m-%d %H:%M:%S")); 
			m_listCtrl.SetItemText(iItem, 4, dddd);
				  dddd = m_Control.m_szUseridadd;
				  dddd.TrimRight();
			m_listCtrl.SetItemText(iItem, 5, dddd);
				  dddd = m_Control.m_szpcpointnum;
				  dddd.TrimRight();
			m_Records.push_back(dddd);
			iItem++;
			PointDesid = m_Control.m_szCID +1;
			m_Control.MoveNext();
		}
	  }
	  else if(m_strtable == "AddControl")   //加控制策略
	  {
		if ( m_PointDes._IsEmpty() )
		  return;
//		m_listCtrl.SetItemCount(m_PointDes.RecordCount());
     	m_listCtrl.DeleteAllItems();
     	m_listDis.DeleteAllItems();
		CString cccc;
		int iItem = 0;
		int iItem1 = 0;
		int nfds = m_wndComboSize3.GetCurSel();
		m_PointDes.MoveFirst();
		while ( !m_PointDes.IsEOF() )
		{
    		dddd = m_PointDes.m_szpointnum;
				  dddd.TrimRight();
			cccc.Format("%d", m_PointDes.m_szPID);
			if(m_PointDes.m_szfds == nfds+1  && dddd.Find("C") == -1 && dddd.Find("F") == -1)
			{
        		int nfds = m_PointDes.m_szfds;
    	       	int nchan = m_PointDes.m_szchan;
         		m_listCtrl.InsertItem(iItem, m_SlaveStation[nfds][nchan].WatchName);
        		m_listCtrl.SetItemText(iItem, 1, dddd);
        		m_listCtrl.SetItemText(iItem, 2, cccc);
    			iItem++;
			}
			if(dddd.Find("C") != -1)
			{
         		m_listDis.InsertItem(iItem1, dddd);
        		m_listDis.SetItemText(iItem1, 1, cccc);
    			iItem1++;
			}
			m_PointDes.MoveNext();
		}
	  }
	  else if("feedelectricity" ==  m_strtable)     //馈电规则显示
	  {
		if ( m_AxFeedE._IsEmpty() )
		  return;
//     	m_listCtrl.DeleteAllItems();
		m_listCtrl.SetItemCount(m_AxFeedE.RecordCount());
		int iItem = 0;
		m_AxFeedE.MoveFirst();
		while ( !m_AxFeedE.IsEOF() )
		{
        	CString  strf,strc;
			dddd = m_AxFeedE.m_szcpointnum;
			dddd.TrimRight();
    		strf = dddd.Mid(0,2);
    		strc = dddd.Mid(3);
	    	int nfds = m_Str2Data.String2Int(strf);
	    	int nchan = m_Str2Data.String2Int(strc) + 16;

    		m_listCtrl.InsertItem(iItem, m_SlaveStation[nfds][nchan].WatchName);
    		m_listCtrl.SetItemText(iItem, 1, dddd);
    		dddd = m_AxFeedE.m_szepointnum;
				  dddd.TrimRight();
			m_listCtrl.SetItemText(iItem, 2, dddd);
				  COleDateTime oleDateTime=m_AxFeedE.m_szrecdate;
				  CString dddd   =   oleDateTime.Format(_T("%Y-%m-%d %H:%M:%S")); 
			m_listCtrl.SetItemText(iItem, 3, dddd);
    		dddd = m_AxFeedE.m_szUseridadd;
				  dddd.TrimRight();
			m_listCtrl.SetItemText(iItem, 4, dddd);
    		dddd = m_AxFeedE.m_szecpointnum;
				  dddd.TrimRight();
			m_Records.push_back(dddd);
			iItem++;
			PointDesid = m_AxFeedE.m_szEID +1;
			m_AxFeedE.MoveNext();
		}
	  }
	  else if(m_strtable == "AddFeedE")   //加馈电规则
	  {
		if ( m_PointDes._IsEmpty() )
		  return;
//		m_listCtrl.SetItemCount(m_PointDes.RecordCount());
     	m_listCtrl.DeleteAllItems();
     	m_listDis.DeleteAllItems();
		CString cccc;
		int iItem = 0;
		int iItem1 = 0;
		int nfds = m_wndComboSize3.GetCurSel();
		m_PointDes.MoveFirst();
		while ( !m_PointDes.IsEOF() )
		{
    		dddd = m_PointDes.m_szpointnum;
				  dddd.TrimRight();
			cccc.Format("%d", m_PointDes.m_szPID);
			if(m_PointDes.m_szfds == nfds+1  && dddd.Find("C") != -1)
			{
        		int nfds = m_PointDes.m_szfds;
    	       	int nchan = m_PointDes.m_szchan;
           		m_listCtrl.InsertItem(iItem, m_SlaveStation[nfds][nchan].WatchName);
        		m_listCtrl.SetItemText(iItem, 1, dddd);
        		m_listCtrl.SetItemText(iItem, 2, cccc);
    			iItem++;
			}
			if(dddd.Find("D") != -1)
			{
         		m_listDis.InsertItem(iItem1, dddd);
        		m_listDis.SetItemText(iItem1, 1, cccc);
    			iItem1++;
			}
			m_PointDes.MoveNext();
		}
	  }

       	// Insert data into list-control by copying from datamodel
//    	int nItem = 0;


    //Highlight the first item
/*    LV_ITEM lvi;
		lvi.mask = LVIF_TEXT;
		lvi.iItem = 0;
		lvi.iSubItem = 0;
	  lvi.stateMask = LVIS_SELECTED | LVIS_FOCUSED;
	  lvi.state = LVIS_SELECTED | LVIS_FOCUSED;
		lvi.pszText = (LPSTR)(LPCTSTR)m_AccountSet.m_szAccountID;
		lvi.iImage = 0;
		lvi.iIndent = 0;
		lvi.cchTextMax = 50;

    m_AccountSet.MoveFirst();
    m_listCtrl.SetItemState(lvi.iItem, &lvi);*/
  }
  catch ( dbAx::CAxException *e )
  {
    MessageBox(e->m_szErrorDesc, _T("BJygjl Message"), MB_OK);
    delete e;
  }
}

void  CSettingHostDlg::pushDIS(CString str1)
{
         	str1.TrimRight();
			if(str1 == "")
				return;
    	CString  strf,strc;
    		strf = str1.Mid(0,2);
    		strc = str1.Mid(3);
		int nfds = m_Str2Data.String2Int(strf);
		int nchan = m_Str2Data.String2Int(strc);
    	strc = m_SlaveStation[nfds][nchan].WatchName;
			if(strc == "")
				return;
		m_Records.push_back(str1);
//				if((str3.Find("A")!=-1) || (str3.Find("D")!=-1) ||(str3.Find("C")!=-1) ||(str3.Find("F")!=-1) )
}

void  CSettingHostDlg::BuildDisList()
{

}

void CSettingHostDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CSettingHostDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CSettingHostDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

BOOL CSettingHostDlg::ConnectToProvider()
{
  //Connection string generated by AxGen. Change the settings as 
  //required for a particular environment
//  CString szConnect = _T("Provider=SQLOLEDB.1;Persist Security Info=True;\
//                          User ID=sa;Password=sunset;\
//                          Data Source=(local)\\SQLEXPRESS;Initial Catalog=BJygjl");
  CString szConnect = _T("Provider=SQLOLEDB.1;Persist Security Info=True;\
                          User ID=sa;Password=sunset;\
                          Data Source=") +m_OthersSetting.DBname+ _T(";Initial Catalog=BJygjl");

//All calls to the AxLib should be wrapped in a try / catch block
  try
  {
    //Call the global Init function from the AxLib library. This will
    //initialize COM and setup the library's connection collection.
    //Use the namespace identifier to avoid conflict with any other
    //init functions that may exist.
    dbAx::Init();

    //Create the connection object
    m_Cn.Create();

    //Create the Connection events object on the heap. We don't need
    //to worry with deleting the Events object since this is handled
    //internally by its Release function. When no longer needed, the
    //Events object deletes itself.
//    m_Cn._SetConnectionEvents(new CCardFileEvents);

    //Set the cursor location and open the database connection
    m_Cn.CursorLocation(adUseClient);
    m_Cn.Open((LPCTSTR)szConnect);

//	if(m_ADTypeTable[1].TableName ==  m_strtable)
	{
		//Create the AccountSet, Recordset events, and Open
		//Note that options are set on the CAxRecordset object
		//before callint the Open method. In this instance,
		//the Create method must be called first. See the
		//note below regarding m_ContactSet.
		m_AccountSet.Create();
		m_AccountSet.CursorType(adOpenDynamic);
		m_AccountSet.CacheSize(50);
		m_AccountSet._SetRecordsetEvents(new CAccountSetEvents);
		m_AccountSet.Open(_T("Select * From digitaltype WHERE fdel=0"), &m_Cn);

		//Set the marshal options to minimize records returned to server
		//to only those that have been edited.
		m_AccountSet.MarshalOptions(adMarshalModifiedOnly);
	}
    //Setup the command object that will execute the stored
    //procedure "get_Contacts" to match contact information
    //with the currently selected Account record.
//    m_ContactCmd.Create();
//    m_ContactCmd.ActiveConnection(&m_Cn);
//    m_ContactCmd.CommandText(_T("[get_Contacts]"));
//    m_ContactCmd.CommandType(adCmdStoredProc);
//    m_ContactCmd.m_szAccntIDParam = _T("A");  //Initial dummy value

    //Open the Contact recordset based on the Contact Command object.
    //An open recordset may be updated by setting the associated command
    //object's parameter(s) and calling the recordset's Requery() method.
    //A recordset set opened directly can also use Requery. This has the
    //same effect as closing and reopening the recordset.
    //Note that since there are no calls to any of the recordset object's
    //methods prior to the Open statement, it unnecessary to make a call
    //to the Create method. This is handled automatically when opening
    //the recordset.
//    m_ContactSet.Open(&m_ContactCmd, adOpenDynamic);
//	if(m_ADTypeTable[0].TableName ==  m_strtable)
	{
		m_ContactSet.Create();
		m_ContactSet.CursorType(adOpenDynamic);
		m_ContactSet.CacheSize(50);
		m_ContactSet._SetRecordsetEvents(new CAccountSetEvents);
		m_ContactSet.Open(_T("Select * From analogtype WHERE fdel=0 "), &m_Cn);
		m_ContactSet.MarshalOptions(adMarshalModifiedOnly);
	}
//	if(m_ADTypeTable[2].TableName ==  m_strtable)
	{
		m_MAlocation.Create();
		m_MAlocation.CursorType(adOpenDynamic);
		m_MAlocation.CacheSize(50);
//		m_MAlocation._SetRecordsetEvents(new CAccountSetEvents);
		m_MAlocation.Open(_T("Select * From fixlocation"), &m_Cn);
		m_MAlocation.MarshalOptions(adMarshalModifiedOnly);
	}
		m_PointDes.Create();
		m_PointDes.CursorType(adOpenDynamic);
		m_PointDes.CacheSize(50);
		m_PointDes._SetRecordsetEvents(new CAccountSetEvents);
		m_PointDes.Open(_T("Select * From pointdescription WHERE fdel=0"), &m_Cn);
		m_PointDes.MarshalOptions(adMarshalModifiedOnly);

		m_DisPoint.Create();
		m_DisPoint.CursorType(adOpenDynamic);
		m_DisPoint.CacheSize(50);
		m_DisPoint._SetRecordsetEvents(new CAccountSetEvents);
		m_DisPoint.Open(_T("Select * From dispoint"), &m_Cn);
		m_DisPoint.MarshalOptions(adMarshalModifiedOnly);

		m_Control.Create();
		m_Control.CursorType(adOpenDynamic);
		m_Control.CacheSize(50);
		m_Control._SetRecordsetEvents(new CAccountSetEvents);
		m_Control.Open(_T("Select * From control WHERE fdel=0"), &m_Cn);
		m_Control.MarshalOptions(adMarshalModifiedOnly);

		m_SControl.Create();
		m_SControl.CursorType(adOpenDynamic);
		m_SControl.CacheSize(50);
		m_SControl._SetRecordsetEvents(new CAccountSetEvents);
		m_SControl.Open(_T("Select * From specialcontrol"), &m_Cn);
		m_SControl.MarshalOptions(adMarshalModifiedOnly);

		m_AxFeedE.Create();
		m_AxFeedE.CursorType(adOpenDynamic);
		m_AxFeedE.CacheSize(50);
		m_AxFeedE._SetRecordsetEvents(new CAccountSetEvents);
		m_AxFeedE.Open(_T("Select * From feedelectricity WHERE fdel=0"), &m_Cn);
		m_AxFeedE.MarshalOptions(adMarshalModifiedOnly);
  }
  catch ( dbAx::CAxException *e )
  {
    MessageBox(e->m_szErrorDesc, _T("BJygjl Message"), MB_OK);
    delete e;
    return (FALSE);
  }

  return (TRUE);
}

void CSettingHostDlg::OnItemChangedList(NMHDR *pNMHDR, LRESULT *pResult)
{
  LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);

// TODO: Add your control notification handler code here                
   CString sTemp;          
/*   if((pNMListView->uOldState & LVIS_FOCUSED) == LVIS_FOCUSED &&
	   (pNMListView->uNewState & LVIS_FOCUSED) == 0)        
   {                 
	   sTemp.Format("%d losted focus",pNMListView->iItem);            
   }        
   else if((pNMListView->uOldState & LVIS_FOCUSED) == 0 &&
	   (pNMListView->uNewState & LVIS_FOCUSED) == LVIS_FOCUSED)         
   {                 
	   sTemp.Format("%d got focus",pNMListView->iItem);            
   }        
   if((pNMListView->uOldState & LVIS_SELECTED) == LVIS_SELECTED &&
	   (pNMListView->uNewState & LVIS_SELECTED) == 0)            
   {                 
	   sTemp.Format("%d losted selected",pNMListView->iItem);            
   }            
   else 
	   if((pNMListView->uOldState & LVIS_SELECTED) == 0 &&
	   (pNMListView->uNewState & LVIS_SELECTED) == LVIS_SELECTED)
   {                 
	   sTemp.Format("%d got selected",pNMListView->iItem);            
       m_AccountSet.AbsolutePosition(pNMListView->iItem + 1);
   }   */
//   AfxMessageBox(sTemp);
  *pResult = 0;

  if ( pNMLV->uNewState == 3 )
  {
	  if(m_ADTypeTable[1].TableName ==  m_strtable && !m_AccountSet._IsEmpty() ) //开关量
           m_AccountSet.AbsolutePosition(pNMLV->iItem + 1);
	  else if(m_ADTypeTable[0].TableName ==  m_strtable && !m_ContactSet._IsEmpty() )//模拟量
           m_ContactSet.AbsolutePosition(pNMLV->iItem + 1);
	  else if(m_ADTypeTable[2].TableName ==  m_strtable && !m_MAlocation._IsEmpty() )//安装地点
           m_MAlocation.AbsolutePosition(pNMLV->iItem + 1);
	  else if(m_ADTypeTable[3].TableName ==  m_strtable && !m_PointDes._IsEmpty() ) //pointdescription
           m_PointDes.AbsolutePosition(pNMLV->iItem + 1);
	  else if(m_ADTypeTable[5].TableName ==  m_strtable && !m_Control._IsEmpty() )  //控制策略显示
           m_Control.AbsolutePosition(pNMLV->iItem + 1);
	  else if(m_ADTypeTable[6].TableName ==  m_strtable && !m_SControl._IsEmpty() )
           m_SControl.AbsolutePosition(pNMLV->iItem + 1);
	  else if("feedelectricity" ==  m_strtable && !m_AxFeedE._IsEmpty() )  //馈电规则显示
           m_AxFeedE.AbsolutePosition(pNMLV->iItem + 1);
  }
}

void CSettingHostDlg::OnClose()
{
  //Closing of library objects is ensured as each object
  //goes out of scope, but doing a manual shutdown doesn抰 hurt.

  try
  {
    if ( m_AccountSet._IsOpen() )
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
      m_Control.Close();
    if ( m_SControl._IsOpen() )
      m_SControl.Close();
    if ( m_AxFeedE._IsOpen() )
      m_AxFeedE.Close();

    m_Cn.Close();

    //Cleanup the AxLib library
    dbAx::Term();
  }
  catch ( CAxException *e )
  {
    MessageBox(e->m_szErrorDesc, _T("BJygjl Message"), MB_OK);
    delete e;
  }

  CDialog::OnClose();
}

void CSettingHostDlg::SortColumn(int iCol, bool bAsc)
{
	m_bAscending = bAsc;
	m_nSortedCol = iCol;

	// set sort image for header and sort column.
	m_listCtrl.SetSortImage(m_nSortedCol, m_bAscending);

	CXTSortClass csc(&m_listCtrl, m_nSortedCol);
	csc.Sort(m_bAscending, xtSortString);
}

void CSettingHostDlg::OnBtnADD()
{
	if(m_ADTypeTable[3].TableName ==  m_strtable ) //pointdescription
	{
		m_bADD = true;
		m_bSwitch = false;
          m_listCtrl.DeleteColumn(2);
          m_listCtrl.DeleteColumn(1);
          m_listCtrl.DeleteColumn(0);
		  HideAMD();
		  InsA();
		  m_strtable = m_ADTypeTable[0].TableName;  //模拟量
		  BuildAccountList();
		  ShowControls();
           GetDlgItem(IDC_STATIC2)->ShowWindow(SW_SHOW);
           GetDlgItem(IDC_COMBO2)->ShowWindow(SW_SHOW);
		   TrueFC();
	}
	else if(m_ADTypeTable[5].TableName ==  m_strtable )  //控制策略显示
	{
		m_bADD = true;    
//		m_bSwitch = false;
    	for (int iItem = 5; iItem >= 0; iItem--)
    		m_listCtrl.DeleteColumn(iItem);

		m_strtable = "AddControl";   //加控制策略
		OnClose();
        OnInitDialog();
	}
	else if("feedelectricity" ==  m_strtable )  //馈电规则显示
	{
		m_bADD = true;
//		m_bSwitch = false;
    	for (int iItem = 4; iItem >= 0; iItem--)
    		m_listCtrl.DeleteColumn(iItem);

		m_strtable = "AddFeedE";   //加馈电规则
		OnClose();
        OnInitDialog();
	}

/*	else if((m_ADTypeTable[6].TableName ==  m_strtable )&& !m_bADD)
	{
      CString str;
      for(int i=0; i<m_listCtrl.GetItemCount(); i++)
      {
		try
		{
					if ( m_SControl._IsOpen() )
						   m_SControl.Close();
					m_SControl.Create();
					m_SControl.CursorType(adOpenDynamic);
					m_SControl.CacheSize(50);
					m_SControl._SetRecordsetEvents(new CAccountSetEvents);
					CString strPointNo; 
					strPointNo.Format(_T("SELECT * From specialcontrol WHERE SID = %d"),i+1);
					m_SControl.Open(strPointNo, &m_Cn);
					m_SControl.MarshalOptions(adMarshalModifiedOnly);
			   if( m_listCtrl.GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED || m_listCtrl.GetCheck(i))
			   {
//            	UpdateData(TRUE);           //Exchange dialog data
					if(m_listCtrl.GetCheck(i))
			    	{
              		m_SControl.m_szSID = i+1;
            		m_SControl.m_szSpeCtrol = true;
            		m_SControl.Update();    //Update the recordset
	//                str.Format(_T("第%d行的checkbox为选中状态"), i);
	//                AfxMessageBox(str);
				    }
				    else
				    {
              		m_SControl.m_szSID = i+1;
            		m_SControl.m_szSpeCtrol = false;
            		m_SControl.Update();    //Update the recordset
				    }
			   }
			   else
			   {
              		m_SControl.m_szSID = i+1;
            		m_SControl.m_szSpeCtrol = false;
            		m_SControl.Update();    //Update the recordset
			   }
	   	}
		catch (CAxException *e)
		{
			AfxMessageBox(e->m_szErrorDesc, MB_OK);
			delete e;
		}
      }
		  AfxMessageBox("特殊控制分站已保存", MB_OK);
//        MessageBeep(MB_OK);
//        EndDialog(IDOK);
	}
	else if((m_ADTypeTable[6].TableName ==  m_strtable )&& m_bADD)
	{
      CString str;
      for(int i=0; i<m_listCtrl.GetItemCount(); i++)
      {
		try
		{
					if ( m_SControl._IsOpen() )
						   m_SControl.Close();
					m_SControl.Create();
					m_SControl.CursorType(adOpenDynamic);
					m_SControl.CacheSize(50);
					m_SControl._SetRecordsetEvents(new CAccountSetEvents);
					CString strPointNo; 
					strPointNo.Format(_T("SELECT * From specialcontrol WHERE SID = %d"),i+1);
					m_SControl.Open(strPointNo, &m_Cn);
					m_SControl.MarshalOptions(adMarshalModifiedOnly);
			   if( m_listCtrl.GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED || m_listCtrl.GetCheck(i))
			   {
//            	UpdateData(TRUE);           //Exchange dialog data
					if(m_listCtrl.GetCheck(i))
			    	{
              		m_SControl.m_szSID = i+1;
//            		m_SControl.m_szSerialnum = true;
            		m_SControl.Update();    //Update the recordset
	//                str.Format(_T("第%d行的checkbox为选中状态"), i);
	//                AfxMessageBox(str);
				    }
				    else
				    {
              		m_SControl.m_szSID = i+1;
//            		m_SControl.m_szSerialnum = false;
            		m_SControl.Update();    //Update the recordset
				    }
			   }
			   else
			   {
              		m_SControl.m_szSID = i+1;
//            		m_SControl.m_szSerialnum = false;
            		m_SControl.Update();    //Update the recordset
			   }
	   	}
		catch (CAxException *e)
		{
			AfxMessageBox(e->m_szErrorDesc, MB_OK);
			delete e;
		}
      }
		  AfxMessageBox("巡检分站已保存", MB_OK);
//        EndDialog(IDOK);
	}*/
	else//安装地点
	{
		if(m_ADTypeTable[2].TableName ==  m_strtable)
		{
        	if(!m_bADD)
			{
          	CAccountDlg *dlgc = new CAccountDlg(); 
	    	  dlgc->acdid= sqlid;
	     	  dlgc->strtable= m_strtable;
        	dlgc->Create(CAccountDlg::IDD,this); //创建对话框 
        	dlgc->SetWindowPos(NULL,400,200,GetSystemMetrics(SM_CXSCREEN)/3+30,GetSystemMetrics(SM_CYSCREEN)/2+80, SWP_SHOWWINDOW);//SWP_NOMOVE);//|SWP_NOACTIVATE);
//        	dlgc->SetWindowPos(&CWnd::wndBottom,400,200,GetSystemMetrics(SM_CXSCREEN)/3+30,GetSystemMetrics(SM_CYSCREEN)/2+80, SWP_SHOWWINDOW);//SWP_NOMOVE);//|SWP_NOACTIVATE);
        	dlgc->UpdateWindow(); 
			m_bADD =true;
			}
      		else
	    	  AfxMessageBox("添加安装地点对话框已打开！", MB_OK);
		}
		else
		{
    		  CAccountDlg dlg(this);
	    	  dlg.acdid= sqlid;
	    	  dlg.strtable= m_strtable;
	    	  if ( dlg.DoModal() == IDOK )
			  {
        		theApp.InitData();
	    		BuildAccountList();
			  }
		}
	}
}

void CSettingHostDlg::OnBtnADD2()
{
		m_bADD = true;
		m_bSwitch = true;
          m_listCtrl.DeleteColumn(2);
          m_listCtrl.DeleteColumn(1);
          m_listCtrl.DeleteColumn(0);
		  HideAMD();
		  InsD();
		  m_strtable = m_ADTypeTable[1].TableName;  //开关量
		  BuildAccountList();
		  ShowControls();
        GetDlgItem(IDC_STATIC2)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_COMBO2)->ShowWindow(SW_HIDE);
		TrueFC();
}

void CSettingHostDlg::OnBtnOK()
{
  try
  {
	vector<CString>::iterator  iter;
	int fff = 0;
	m_PointDesNew->m_szPID  = PointDesid;

	UpdateData(TRUE);           //Exchange dialog data
	COleDateTime CTime;
	CString  m_strsel,dddd,szFind;

	m_wndComboSize1.GetWindowText(m_strsel);

		m_MAlocation.MoveFirst();
		while ( !m_MAlocation.IsEOF() )
		{
			dddd = m_MAlocation.m_szName;
			dddd.TrimRight();
			if(m_strsel == dddd)
			{
            	m_PointDesNew->m_szpositionid = m_MAlocation.m_szlocationID;
				break;
			}
			else
            	m_PointDesNew->m_szpositionid = 0;
			m_MAlocation.MoveNext();
		}
        m_PointDesNew->m_szName ="";
//	if(m_bSwitch)
//    	m_PointDesNew->m_szName = m_strsel +"|" + m_AccountSet.m_szName;
//	else
//    	m_PointDesNew->m_szName = m_strsel +"|" + m_ContactSet.m_szName;
	m_wndComboSize3.GetWindowText(m_strsel);
	m_PointDesNew->m_szfds = m_Str2Data.String2Int(m_strsel);
	m_wndComboSize4.GetWindowText(dddd);
	m_PointDesNew->m_szchan = m_Str2Data.String2Int(dddd);

	if(m_strsel.GetLength() ==1)
		m_strsel ="0" + m_strsel;
	if(dddd.GetLength() ==1)
		dddd ="0" + dddd;
	if(m_bSwitch)
	{
		if(m_AccountSet.m_szptype == 0  || m_AccountSet.m_szptype == 3 || m_AccountSet.m_szptype == 4)
        	m_PointDesNew->m_szpointnum = m_strsel +"D"+dddd;
		if(m_AccountSet.m_szptype == 1 )
		{
        	m_PointDesNew->m_szpointnum = m_strsel +"F"+"00";
         	m_PointDesNew->m_szchan = 0;
		}
		if(m_AccountSet.m_szptype == 2 )
		{
        	m_PointDesNew->m_szpointnum = m_strsel +"C"+dddd;
			int n_chan = m_Str2Data.String2Int(dddd);
			if(n_chan>8)
			{
     			AfxMessageBox("控制量通道号不能大于8！", MB_OK);
	    		return;
			}
         	m_PointDesNew->m_szchan = n_chan +16;//控制量
		}
	}
	else
    	m_PointDesNew->m_szpointnum = m_strsel +"A"+dddd;

	for(iter = m_Records.begin(); iter != m_Records.end(); ++iter)
	{
			szFind = *iter;
			szFind.TrimRight();
		if(szFind == m_PointDesNew->m_szpointnum)
		{
			fff = 100;		break;
		}

		dddd = m_PointDesNew->m_szpointnum;
		int m =dddd.Find(_T("D"));
		int o =dddd.Find(_T("A"));
		if(m != -1)
			dddd.Replace(_T("D"),_T("A"));
 		if(o != -1)
			dddd.Replace(_T("A"),_T("D"));
		if(szFind == dddd)
		{
			fff = 100;		break;
		}
	}
	if(m_bADD)
	{
		if(fff == 100)
		{
			AfxMessageBox("点号已存在，重新选择", MB_OK);
			return;
		}
	}
	UpdateData(TRUE);           //Exchange dialog data
	m_wndComboSize2.GetWindowText(m_strsel);
	int s = m_wndComboSize2.GetCurSel();
	if(m_bSwitch)
	{
				  if(m_AccountSet.m_szptype == 0)
					  dddd = "二态开关量";
				  else if(m_AccountSet.m_szptype == 1)
					  dddd = "分站";
				  else if(m_AccountSet.m_szptype == 2)
					  dddd = "控制量";
				  else if(m_AccountSet.m_szptype == 3)
					  dddd = "三态开关量";
				  else if(m_AccountSet.m_szptype == 4)
					  dddd = "通断量";
		m_PointDesNew->m_szutype = dddd;
    	m_PointDesNew->m_szptype = 10+m_AccountSet.m_szptype;     //开关量
    	m_PointDesNew->m_sztypeID = m_AccountSet.m_szDID;
	}
	else
	{
    	m_PointDesNew->m_szutype = m_strsel;
		if(s == 0)
        	m_PointDesNew->m_szptype = 0;     //电流电压
		if(s == 1)
        	m_PointDesNew->m_szptype = 1;     //频率
		if(s == 2)
        	m_PointDesNew->m_szptype = 2;     //频率(累计)
    	m_PointDesNew->m_sztypeID = m_ContactSet.m_szAID;
	}
	if(m_ctrlCheckAlm.GetCheck())
    	m_PointDesNew->m_szsubOpr = true;
	else
    	m_PointDesNew->m_szsubOpr = false;
	m_PointDesNew->m_szfdel = false;
	m_PointDesNew->m_szrecdate = CTime.GetCurrentTime();
   	m_PointDesNew->m_szUseridadd = theApp.curuser;

	if(m_bADD)
        m_PointDesNew->AddNew();  //Add a new, blank record
	m_PointDesNew->Update();    //Update the recordset
		//If this is a new record, requery the database table
		//otherwise we may out-of-sync
	if(m_bADD)
        m_PointDesNew->Requery();
  }
  catch (CAxException *e)
  {
    AfxMessageBox(e->m_szErrorDesc, MB_OK);
    delete e;
  }
		theApp.InitData();
	for (int iItem = 10; iItem >= 0; iItem--)
		m_listCtrl.DeleteColumn(iItem);
		  InsP();
		  ShowAMD();
		  m_strtable = m_ADTypeTable[3].TableName;  
		  BuildAccountList();

}
//回到浏览测点状态
void CSettingHostDlg::OnBtnCANCEL()
{
	for (int iItem = 10; iItem >= 0; iItem--)
		m_listCtrl.DeleteColumn(iItem);
		  InsP();
		  ShowAMD();
		  m_strtable = m_ADTypeTable[3].TableName;  
		  BuildAccountList();

}
//分站、通道可以编辑
void CSettingHostDlg::TrueFC()
{
    GetDlgItem(IDC_COMBO3)->EnableWindow(TRUE);
    GetDlgItem(IDC_COMBO4)->EnableWindow(TRUE);
}
void CSettingHostDlg::FalseFC()
{
    GetDlgItem(IDC_COMBO3)->EnableWindow(FALSE);
    GetDlgItem(IDC_COMBO4)->EnableWindow(FALSE);
}

void CSettingHostDlg::HideControls()
{
    	GetDlgItem(IDC_STATIC1)->ShowWindow(SW_HIDE);
    	GetDlgItem(IDC_STATIC2)->ShowWindow(SW_HIDE);
    	GetDlgItem(IDC_STATIC3)->ShowWindow(SW_HIDE);
    	GetDlgItem(IDC_STATIC4)->ShowWindow(SW_HIDE);
    	GetDlgItem(IDC_COMBO1)->ShowWindow(SW_HIDE);
    	GetDlgItem(IDC_COMBO2)->ShowWindow(SW_HIDE);
    	GetDlgItem(IDC_COMBO3)->ShowWindow(SW_HIDE);
    	GetDlgItem(IDC_COMBO4)->ShowWindow(SW_HIDE);
    	GetDlgItem(IDOKADM)->ShowWindow(SW_HIDE);
    	GetDlgItem(IDCANCELADM)->ShowWindow(SW_HIDE);
    	GetDlgItem(IDC_BUT_ADD2)->ShowWindow(SW_HIDE);
    	GetDlgItem(IDC_CHECK_ISALM)->ShowWindow(SW_HIDE);
}

void CSettingHostDlg::ShowControls()
{
    	GetDlgItem(IDC_STATIC1)->ShowWindow(SW_SHOW);;
    	GetDlgItem(IDC_STATIC2)->ShowWindow(SW_SHOW);;
    	GetDlgItem(IDC_STATIC3)->ShowWindow(SW_SHOW);;
    	GetDlgItem(IDC_STATIC4)->ShowWindow(SW_SHOW);;
    	GetDlgItem(IDC_COMBO1)->ShowWindow(SW_SHOW);;
    	GetDlgItem(IDC_COMBO2)->ShowWindow(SW_SHOW);;
    	GetDlgItem(IDC_COMBO3)->ShowWindow(SW_SHOW);;
    	GetDlgItem(IDC_COMBO4)->ShowWindow(SW_SHOW);;
    	GetDlgItem(IDOKADM)->ShowWindow(SW_SHOW);;
    	GetDlgItem(IDCANCELADM)->ShowWindow(SW_SHOW);;
    	GetDlgItem(IDC_BUT_ADD2)->ShowWindow(SW_HIDE);;
    	GetDlgItem(IDC_CHECK_ISALM)->ShowWindow(SW_SHOW);;
}

void CSettingHostDlg::HideAMD()
{
    	GetDlgItem(IDC_BUT_ADD)->ShowWindow(SW_HIDE);
    	GetDlgItem(IDC_BUT_ADD2)->ShowWindow(SW_HIDE);
    	GetDlgItem(IDC_BUT_DEL)->ShowWindow(SW_HIDE);
    	GetDlgItem(IDC_BUT_MOD)->ShowWindow(SW_HIDE);
    	GetDlgItem(IDCANCEL)->ShowWindow(SW_HIDE);
}

void CSettingHostDlg::HideDISPLAY()
{
    	GetDlgItem(IDC_LIST_DISPLAY)->ShowWindow(SW_HIDE);;
    	GetDlgItem(IDC_BUTTONDIS1)->ShowWindow(SW_HIDE);;
    	GetDlgItem(IDC_BUTTONDIS2)->ShowWindow(SW_HIDE);;
    	GetDlgItem(IDC_BUTTONDIS3)->ShowWindow(SW_HIDE);;
    	GetDlgItem(IDC_BUTTONDIS4)->ShowWindow(SW_HIDE);;
    	GetDlgItem(IDC_BUTTONDIS5)->ShowWindow(SW_HIDE);;
    	GetDlgItem(IDC_BUTTONDIS6)->ShowWindow(SW_HIDE);;
}

void CSettingHostDlg::ShowDISPLAY()
{
    	GetDlgItem(IDC_LIST_DISPLAY)->ShowWindow(SW_SHOW);;
//    	GetDlgItem(IDC_BUTTONDIS1)->ShowWindow(SW_SHOW);;
    	GetDlgItem(IDC_BUTTONDIS2)->ShowWindow(SW_SHOW);;
//    	GetDlgItem(IDC_BUTTONDIS3)->ShowWindow(SW_SHOW);;
    	GetDlgItem(IDC_BUTTONDIS4)->ShowWindow(SW_SHOW);;
//    	GetDlgItem(IDC_BUTTONDIS5)->ShowWindow(SW_SHOW);;
//    	GetDlgItem(IDC_BUTTONDIS6)->ShowWindow(SW_SHOW);;
        GetDlgItem(IDC_COMBO3)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_STATIC3)->ShowWindow(SW_SHOW);
//        GetDlgItem(IDC_COMBO4)->ShowWindow(SW_SHOW);
//        GetDlgItem(IDC_STATIC4)->ShowWindow(SW_SHOW);
//        GetDlgItem(IDC_CHECK_ISALM)->ShowWindow(SW_SHOW);
}

void CSettingHostDlg::ShowAMD()
{
    	GetDlgItem(IDC_BUT_ADD)->ShowWindow(SW_SHOW);;
    	GetDlgItem(IDC_BUT_ADD2)->ShowWindow(SW_SHOW);;
    	GetDlgItem(IDC_BUT_DEL)->ShowWindow(SW_SHOW);;
    	GetDlgItem(IDC_BUT_MOD)->ShowWindow(SW_SHOW);;
    	GetDlgItem(IDCANCEL)->ShowWindow(SW_SHOW);
}
void CSettingHostDlg::InsA()  //模拟量类型
{
	HideDISPLAY();
		HideControls();
//    	MoveWindow(CRect(50,100,960,700));
		SetWindowText(m_ADTypeTable[0].NameD);
		m_listCtrl.InsertColumn(0,m_ADTypeTable[0].m_DTypeTFD.Name,LVCFMT_LEFT,100);
		m_listCtrl.InsertColumn(1,m_ADTypeTable[0].m_DTypeTFD.ltop,LVCFMT_LEFT,70);
		m_listCtrl.InsertColumn(2,m_ADTypeTable[0].m_DTypeTFD.lbom,LVCFMT_LEFT,70);
		m_listCtrl.InsertColumn(3,m_ADTypeTable[0].m_DTypeTFD.palmu,LVCFMT_LEFT,70);
		m_listCtrl.InsertColumn(4,m_ADTypeTable[0].m_DTypeTFD.palmd,LVCFMT_LEFT,70);
		m_listCtrl.InsertColumn(5,m_ADTypeTable[0].m_DTypeTFD.pbrk,LVCFMT_LEFT,70);
		m_listCtrl.InsertColumn(6,m_ADTypeTable[0].m_DTypeTFD.prtn,LVCFMT_LEFT,70);
		m_listCtrl.InsertColumn(7,m_ADTypeTable[0].m_DTypeTFD.falm,LVCFMT_LEFT,150);
		m_listCtrl.InsertColumn(8,m_ADTypeTable[0].m_DTypeTFD.punit,LVCFMT_LEFT,40);
		m_listCtrl.InsertColumn(9,m_ADTypeTable[0].m_DTypeTFD.recdate,LVCFMT_LEFT,120);
		m_listCtrl.InsertColumn(10,m_ADTypeTable[0].m_DTypeTFD.Useridadd,LVCFMT_LEFT,40);
}

void CSettingHostDlg::InsD()
{
	HideDISPLAY();
		HideControls();
		SetWindowText(m_ADTypeTable[1].NameD);
//    	MoveWindow(CRect(50,100,960,700));
		m_listCtrl.InsertColumn(0,m_ADTypeTable[1].m_DTypeTFD.Name,LVCFMT_LEFT,100);
		m_listCtrl.InsertColumn(1,m_ADTypeTable[1].m_DTypeTFD.name0,LVCFMT_LEFT,80);
		m_listCtrl.InsertColumn(2,m_ADTypeTable[1].m_DTypeTFD.name1,LVCFMT_LEFT,80);
		m_listCtrl.InsertColumn(3,m_ADTypeTable[1].m_DTypeTFD.name2,LVCFMT_LEFT,80);
		m_listCtrl.InsertColumn(4,m_ADTypeTable[1].m_DTypeTFD.palms,LVCFMT_LEFT,60);
		m_listCtrl.InsertColumn(5,m_ADTypeTable[1].m_DTypeTFD.falm,LVCFMT_LEFT,120);
		m_listCtrl.InsertColumn(6,m_ADTypeTable[1].m_DTypeTFD.recdate,LVCFMT_LEFT,120);
		m_listCtrl.InsertColumn(7,m_ADTypeTable[1].m_DTypeTFD.Useridadd,LVCFMT_LEFT,50);
		m_listCtrl.InsertColumn(8,m_ADTypeTable[1].m_DTypeTFD.ptype,LVCFMT_LEFT,90);
}

void CSettingHostDlg::InsP()
{
	HideDISPLAY();
		HideControls();
    	GetDlgItem(IDC_BUT_ADD2)->ShowWindow(SW_SHOW);;
    	GetDlgItem(IDC_BUT_ADD)->SetWindowText(_T("增加模拟量"));;
		SetWindowText(m_ADTypeTable[3].NameD);
//    	MoveWindow(CRect(50,100,960,700));
		m_listCtrl.InsertColumn(0,m_ADTypeTable[3].m_DTypeTFD.Name,LVCFMT_LEFT,150);
		m_listCtrl.InsertColumn(1,m_ADTypeTable[3].m_DTypeTFD.pointnum,LVCFMT_LEFT,150);
		m_listCtrl.InsertColumn(2,m_ADTypeTable[3].m_DTypeTFD.utype,LVCFMT_LEFT,150);
		m_listCtrl.InsertColumn(3,m_ADTypeTable[3].m_DTypeTFD.pointnum,LVCFMT_LEFT,150);
}

void CSettingHostDlg::InsC()
{
	HideDISPLAY();
		HideControls();
//    	GetDlgItem(IDC_BUT_ADD)->SetWindowText(_T("增加模拟量"));;
		SetWindowText(m_ADTypeTable[5].NameD);
//    	MoveWindow(CRect(50,100,960,700));
		m_listCtrl.InsertColumn(0,m_ADTypeTable[5].m_DTypeTFD.Name,LVCFMT_LEFT,200);
		m_listCtrl.InsertColumn(1,m_ADTypeTable[5].m_DTypeTFD.pointnum,LVCFMT_LEFT,80);
		m_listCtrl.InsertColumn(2,m_ADTypeTable[5].m_DTypeTFD.chan,LVCFMT_LEFT,80);
		m_listCtrl.InsertColumn(3,m_ADTypeTable[5].m_DTypeTFD.falm,LVCFMT_LEFT,80);
		m_listCtrl.InsertColumn(4,m_ADTypeTable[5].m_DTypeTFD.recdate,LVCFMT_LEFT,150);
		m_listCtrl.InsertColumn(5,m_ADTypeTable[5].m_DTypeTFD.Useridadd,LVCFMT_LEFT,80);
		GetDlgItem(IDC_BUT_MOD)->ShowWindow(SW_HIDE);
}

void CSettingHostDlg::InsAddC()
{
        	HideAMD();
    		HideControls();
    		SetWindowText(_T("增加控制策略"));
        	GetDlgItem(IDC_CHECK_ISALM)->SetWindowText(_T("由分站实施"));
        	GetDlgItem(IDC_BUTTONDIS2)->SetWindowText(_T("增加"));
        	GetDlgItem(IDC_BUTTONDIS4)->SetWindowText(_T("取消"));
        GetDlgItem(IDC_STATIC3)->SetWindowText(_T("被控分站"));
//        GetDlgItem(IDC_STATIC4)->SetWindowText(_T("控制分站"));
   		    ShowDISPLAY();
		m_listCtrl.InsertColumn(0,m_ADTypeTable[5].m_DTypeTFD.Name,LVCFMT_LEFT,200);
		m_listCtrl.InsertColumn(1,m_ADTypeTable[5].m_DTypeTFD.pointnum,LVCFMT_LEFT,75);
		m_listCtrl.InsertColumn(2,_T("PID"),LVCFMT_LEFT,60);

		m_listDis.InsertColumn(0,m_ADTypeTable[5].m_DTypeTFD.chan,LVCFMT_LEFT,100);
		m_listDis.InsertColumn(1,_T("CID"),LVCFMT_LEFT,100);
}

void CSettingHostDlg::Insfeed()
{
	HideDISPLAY();
		HideControls();
		SetWindowText(_T("馈电规则定义"));
//    	MoveWindow(CRect(50,100,960,700));
		m_listCtrl.InsertColumn(0,m_ADTypeTable[5].m_DTypeTFD.Name,LVCFMT_LEFT,200);
		m_listCtrl.InsertColumn(1,_T("控制量"),LVCFMT_LEFT,80);
		m_listCtrl.InsertColumn(2,_T("馈电量"),LVCFMT_LEFT,80);
		m_listCtrl.InsertColumn(3,m_ADTypeTable[5].m_DTypeTFD.recdate,LVCFMT_LEFT,200);
		m_listCtrl.InsertColumn(4,m_ADTypeTable[5].m_DTypeTFD.Useridadd,LVCFMT_LEFT,200);
		GetDlgItem(IDC_BUT_MOD)->ShowWindow(SW_HIDE);
}

void CSettingHostDlg::InsAddfeed()
{
        	HideAMD();
    		HideControls();
    		SetWindowText(_T("增加馈电策略"));
        	GetDlgItem(IDC_BUTTONDIS2)->SetWindowText(_T("增加"));;
        	GetDlgItem(IDC_BUTTONDIS4)->SetWindowText(_T("取消"));;
        GetDlgItem(IDC_STATIC3)->SetWindowText(_T("控制分站"));
//        GetDlgItem(IDC_STATIC4)->SetWindowText(_T("控制分站"));
   		    ShowDISPLAY();
		m_listCtrl.InsertColumn(0,m_ADTypeTable[5].m_DTypeTFD.Name,LVCFMT_LEFT,200);
		m_listCtrl.InsertColumn(1,m_ADTypeTable[5].m_DTypeTFD.pointnum,LVCFMT_LEFT,80);
		m_listCtrl.InsertColumn(2,_T("PID"),LVCFMT_LEFT,60);

		m_listDis.InsertColumn(0,_T("馈电测点"),LVCFMT_LEFT,100);
		m_listDis.InsertColumn(1,_T("PID"),LVCFMT_LEFT,100);
}

void CSettingHostDlg::InsDIS()
{
//	LPCTSTR str1 = "",str2 = "",str3 = "";
    	HideAMD();
		HideControls();
		SetWindowText(m_ADTypeTable[4].NameD);
        GetDlgItem(IDC_COMBO3)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_STATIC3)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_COMBO2)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_STATIC2)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_STATIC2)->SetWindowText(_T("类型"));
//    	MoveWindow(CRect(50,100,960,700));
		m_listCtrl.InsertColumn(0,_T("安装地点/名称"),LVCFMT_LEFT,180);
		m_listCtrl.InsertColumn(1,_T("点号"),LVCFMT_LEFT,80);
		m_listCtrl.InsertColumn(2,_T("类型"),LVCFMT_LEFT,110);

		m_listDis.InsertColumn(0,m_ADTypeTable[4].m_DTypeTFD.pointnum,LVCFMT_LEFT,100);
		m_listDis.InsertColumn(1,"",LVCFMT_LEFT,100);
	// TODO: Add extra initialization here
//	for (int iItem = 0; iItem < 80; ++iItem)
	{
//		CString strItem;
//		strItem.Format(_T("Item %d"), iItem);
//		m_listDis.InsertItem(iItem, _T(""), 0);
	}
}

void CSettingHostDlg::OnBtnDEL()
{
  CString szMsg;
	  if(m_ADTypeTable[1].TableName ==  m_strtable ) //开关量
         szMsg.Format(_T("删除 %s?"), m_AccountSet.m_szName);
	  else if(m_ADTypeTable[0].TableName ==  m_strtable )//模拟量
         szMsg.Format(_T("删除 %s?"), m_ContactSet.m_szName);
	  else if(m_ADTypeTable[2].TableName ==  m_strtable )//安装地点
         szMsg.Format(_T("删除 %s?"), m_MAlocation.m_szName);
	  else if(m_ADTypeTable[3].TableName ==  m_strtable ) //pointdescription
         szMsg.Format(_T("删除 %s?"), m_PointDes.m_szName);
	  else if(m_ADTypeTable[5].TableName ==  m_strtable )  //控制策略显示
         szMsg.Format(_T("删除 %s?"), m_Control.m_szName);
	  else if("feedelectricity" ==  m_strtable )  //控制策略显示
         szMsg.Format(_T("删除 %s?"), m_AxFeedE.m_szName);

  MessageBeep(MB_ICONEXCLAMATION);
  int Reply = AfxMessageBox(szMsg, MB_YESNO);

  try
  {
    if ( Reply == IDYES )
    {
      //Delete the current Account and all
      //related Contact information
//      CString szExecStr;
//      szExecStr.Format(_T("Delete From Contact Where AccountID = '%s'"),
//        m_AccountSet.m_szName);
			COleDateTime CTime;

	int nItemCount=m_listCtrl.GetItemCount();
    for(int nItem=0;nItem<nItemCount;nItem++)
	{
		if(m_listCtrl.GetItemState(nItem,LVIS_SELECTED) & LVIS_SELECTED)
		{
			m_listCtrl.DeleteItem(nItem);
			break;
		}
	}
			  if(m_ADTypeTable[1].TableName ==  m_strtable ) //开关量
			  {
                	m_AccountSet.m_szUseriddel = theApp.curuser;
        			m_AccountSet.m_szfdel = true;
        			m_AccountSet.m_szdeldate = CTime.GetCurrentTime();
				   m_AccountSet.Update();    //Update the recordset
			  }
			  else if(m_ADTypeTable[0].TableName ==  m_strtable )//模拟量
			  {
                	m_ContactSet.m_szUseriddel = theApp.curuser;
        			m_ContactSet.m_szfdel = true;
        			m_ContactSet.m_szdeldate = CTime.GetCurrentTime();
				   m_ContactSet.Update();    //Update the recordset
			  }
			  else if(m_ADTypeTable[2].TableName ==  m_strtable )//安装地点
				 m_MAlocation.Delete();
			  else if(m_ADTypeTable[3].TableName ==  m_strtable )  //pointdescription
			  {
                	m_PointDes.m_szUseriddel = theApp.curuser;
        			m_PointDes.m_szfdel = true;
        			m_PointDes.m_szdeldate = CTime.GetCurrentTime();
				   m_PointDes.Update();    //Update the recordset
//				 m_PointDes.Delete();
			  }
			  else if(m_ADTypeTable[5].TableName ==  m_strtable )  //控制策略显示
			  {
                	m_Control.m_szUseriddel = theApp.curuser;
        			m_Control.m_szfdel = true;
        			m_Control.m_szdeldate = CTime.GetCurrentTime();
				   m_Control.Update();    //Update the recordset
			  }
			  else if("feedelectricity" ==  m_strtable )  //控制策略显示
			  {
                	m_AxFeedE.m_szUseriddel = theApp.curuser;
        			m_AxFeedE.m_szfdel = true;
        			m_AxFeedE.m_szdeldate = CTime.GetCurrentTime();
				   m_AxFeedE.Update();    //Update the recordset
			  }
		//      m_Cn.Execute(szExecStr);
			  OnClose();
			  ConnectToProvider();
			  BuildAccountList();
		theApp.InitData();
    }
  }
  catch ( dbAx::CAxException *e )
  {
    MessageBox(e->m_szErrorDesc, _T("BJygjl Message"), MB_OK);
    delete e;
  }
}

void CSettingHostDlg::OnBtnMOD()
{
	LPCTSTR str1 = "",str2 = "",str3 = "",str4 = "";
	CString strItem, strf,strc;
	if(m_ADTypeTable[3].TableName ==  m_strtable ) //pointdescription
	{
		m_bADD = false;
    		int nfds = m_PointDesNew->m_szfds;
    		int nchan = m_PointDesNew->m_szchan;
		strItem = m_SlaveStation[nfds][nchan].WatchName;
      	m_Str2Data.SplittoCString(strItem,str1,str2,str3);
		m_wndComboSize1.SetWindowText(str1);
		strItem = m_PointDesNew->m_szutype;
		strItem.TrimRight();
		m_wndComboSize2.SetWindowText(strItem);
		strItem = m_PointDesNew->m_szpointnum;
		strItem.TrimRight();
		int n =strItem.Find("A");
		if(n != -1)
		{
			m_bSwitch = false;
    		strf = strItem.Mid(0,n);
    		strc = strItem.Mid(n+1);
		}
		int m =strItem.Find("D");
		int o =strItem.Find("F");
		int p =strItem.Find("C");

		if(m != -1)
		{
			m_bSwitch = true;
    		strf = strItem.Mid(0,m);
    		strc = strItem.Mid(m+1);
		}
		if(o != -1)
		{
			m_bSwitch = true;
    		strf = strItem.Mid(0,o);
    		strc = strItem.Mid(o+1);
		}
		if(p != -1)
		{
			m_bSwitch = true;
    		strf = strItem.Mid(0,p);
    		strc = strItem.Mid(p+1);
		}

		m_wndComboSize3.SetWindowText(strf);
		m_wndComboSize4.SetWindowText(strc);

          m_listCtrl.DeleteColumn(2);
          m_listCtrl.DeleteColumn(1);
          m_listCtrl.DeleteColumn(0);
		  HideAMD();

    	if(m_bSwitch)
		{
		  InsD();
		  m_strtable = m_ADTypeTable[1].TableName;  //开关量
		}
		else
		{
		  InsA();
		  m_strtable = m_ADTypeTable[0].TableName;  //模拟量
		}
		  BuildAccountList();
		  ShowControls();
    	if(m_bSwitch)
		{
           GetDlgItem(IDC_STATIC2)->ShowWindow(SW_HIDE);
           GetDlgItem(IDC_COMBO2)->ShowWindow(SW_HIDE);
		}
		else
		{
           GetDlgItem(IDC_STATIC2)->ShowWindow(SW_SHOW);
           GetDlgItem(IDC_COMBO2)->ShowWindow(SW_SHOW);
		}
		FalseFC();
	}
	else if(m_ADTypeTable[6].TableName ==  m_strtable )
	{
	}//安装地点
	else 
	{
		  CAccountDlg dlg(TRUE, this);
		  dlg.strtable= m_strtable;
		  if ( dlg.DoModal() == IDOK )
		  {
    		theApp.InitData();
			BuildAccountList();
		  }
	}
}

void CSettingHostDlg::OnButtonSelect() 
{
	// TODO: Add your control notification handler code here
	int nItemCount=m_listCtrl.GetItemCount();
    for(int nItem=0;nItem<nItemCount;nItem++)
	{
		if(m_listCtrl.GetItemState(nItem,LVIS_SELECTED) & LVIS_SELECTED)
		{
			CString strPointNo=m_listCtrl.GetItemText(nItem,1);
			int nItemCount1=m_listDis.GetItemCount();
			BOOL bExist=FALSE;
			for(int j=0; j<nItemCount1; j++)
			{
				if(strPointNo==m_listDis.GetItemText(j,0))
				{
					bExist=TRUE;
					break;
				}
			}
			if(!bExist)
				m_listDis.InsertItem(nItemCount1, strPointNo, 0);
		}
	}
//		theApp.InitData();
}

void CSettingHostDlg::OnButtonDeselect() 
{
	if(m_strtable == "AddControl")   //加控制策略
	{
//		UpdateData(TRUE);           //Exchange dialog data
    	vector<CString>::iterator  iter;
		int fff = 0;
//        BOOL bExist=TRUE;
    	int nlistCount=0;
    	int ndisCount=0;
    	int nItemlist=m_listCtrl.GetItemCount();
    	int nItemdis=m_listDis.GetItemCount();
		CString strP1,strP2,strP3,szFind;
        for(int nItem=0;nItem<nItemlist;nItem++)
		{
     		if(m_listCtrl.GetItemState(nItem,LVIS_SELECTED) & LVIS_SELECTED)
			{
	        	 nlistCount++;
				 strP1 = m_listCtrl.GetItemText(nItem,1);
				for(int ndisItem=0;ndisItem<nItemdis;ndisItem++)
				{
     				if(m_listDis.GetItemState(ndisItem,LVIS_SELECTED) & LVIS_SELECTED)
					{
         				 strP2 = m_listDis.GetItemText(ndisItem,0);
						for(iter = m_Records.begin(); iter != m_Records.end(); ++iter)
						{
								szFind = *iter;
								szFind.TrimRight();
								strP1.TrimRight();
								strP2.TrimRight();
							if(szFind == (strP1 +strP2))
							{
								fff = 100;
								break;
							}
						}
						if(fff == 100)
						{
							strP3.Format(_T("%s关联%s已存在，重新选择"),strP1,strP2);
								AfxMessageBox(strP3, MB_OK);
								break;
						}
					}
				}
				if(fff == 100)
					break;
			}//if
		}
		for(int ndisItem=0;ndisItem<nItemdis;ndisItem++)
		{
     			if(m_listDis.GetItemState(ndisItem,LVIS_SELECTED) & LVIS_SELECTED)
         			 ndisCount++;
		}
		if(fff == 100)
			return;
		if(nlistCount>1 && ndisCount >1)
		{
			AfxMessageBox(_T("不可以多对多选择，请重新选择"), MB_OK);
			return;
		}
		if(nlistCount ==0  || ndisCount == 0)
		{
			AfxMessageBox(_T("列表未选择，请重新选择"), MB_OK);
			return;
		}

        for( nItem=0;nItem<nItemlist;nItem++)
		{
     		if(m_listCtrl.GetItemState(nItem,LVIS_SELECTED) & LVIS_SELECTED)
			{
				CString strPoint1=m_listCtrl.GetItemText(nItem,0);
				CString strPoint2=m_listCtrl.GetItemText(nItem,1);
				CString strPoint3=m_listCtrl.GetItemText(nItem,2);
					int fff = 0;
//						UpdateData(TRUE);           //Exchange dialog data
					COleDateTime CTime;
//					CString  m_strsel,dddd,szFind;

					for(int ndis=0;ndis<nItemdis;ndis++)
					{
//						UpdateData(TRUE);           //Exchange dialog data
     					if(m_listDis.GetItemState(ndis,LVIS_SELECTED) & LVIS_SELECTED)
						{
            				try
							{
	         				 m_ControlNew->m_szCID  = PointDesid;
					m_ControlNew->m_szName = strPoint1;
					m_ControlNew->m_szpointnum = strPoint2;
					m_ControlNew->m_szPID = m_Str2Data.String2Int(strPoint3);
				             strP1=m_listDis.GetItemText(ndis,0);
				             strP2=m_listDis.GetItemText(ndis,1);
      			    		 m_ControlNew->m_szcpointnum = strP1;
		    			     m_ControlNew->m_szcPID = m_Str2Data.String2Int(strP2);
							 strPoint2.TrimRight();
							 strP1.TrimRight();
							 strP2 = strPoint2.Mid(0,2);
							 strP3 = strP1.Mid(0,2);
							 if(strP2 == strP3)
		        			     m_ControlNew->m_szByFds = true;
							 else
		        			     m_ControlNew->m_szByFds = false;

		    			     m_ControlNew->m_szpcpointnum = strPoint2 +strP1;
							 m_ControlNew->m_szfdel = false;
    						 m_ControlNew->m_szrecdate = CTime.GetCurrentTime();
     						 m_ControlNew->m_szUseridadd = theApp.curuser;
      						m_ControlNew->AddNew();  //Add a new, blank record
					   	    m_ControlNew->Update();    //Update the recordset
							//If this is a new record, requery the database table
							//otherwise we may out-of-sync
						    m_ControlNew->Requery();
							PointDesid++;
							}
		     			    catch (CAxException *e)
							{
					        	AfxMessageBox(e->m_szErrorDesc, MB_OK);
				        		delete e;
							}
						}//if
					}//for
            }//if
		}//for

    	for (int iItem = 2; iItem >= 0; iItem--)
		{
    		m_listCtrl.DeleteColumn(iItem);
			m_listDis.DeleteColumn(iItem);
		}
   	    m_strtable = m_ADTypeTable[5].TableName;  //控制策略显示
		OnClose();
        OnInitDialog();
		ShowAMD();
		GetDlgItem(IDC_BUT_ADD2)->ShowWindow(SW_HIDE);;
		GetDlgItem(IDC_BUT_MOD)->ShowWindow(SW_HIDE);;

		theApp.InitData();
	}
	else if(m_strtable == _T("AddFeedE"))   //加馈电策略
	{
//		UpdateData(TRUE);           //Exchange dialog data
    	vector<CString>::iterator  iter;
		int fff = 0;
//        BOOL bExist=TRUE;
    	int nlistCount=0;
    	int ndisCount=0;
    	int nItemlist=m_listCtrl.GetItemCount();
    	int nItemdis=m_listDis.GetItemCount();
		CString strP1,strP2,strP3,szFind;
        for(int nItem=0;nItem<nItemlist;nItem++)
		{
     		if(m_listCtrl.GetItemState(nItem,LVIS_SELECTED) & LVIS_SELECTED)
			{
	        	 nlistCount++;
				 strP1 = m_listCtrl.GetItemText(nItem,1);
				for(int ndisItem=0;ndisItem<nItemdis;ndisItem++)
				{
     				if(m_listDis.GetItemState(ndisItem,LVIS_SELECTED) & LVIS_SELECTED)
					{
         				 strP2 = m_listDis.GetItemText(ndisItem,0);
						for(iter = m_Records.begin(); iter != m_Records.end(); ++iter)
						{
								szFind = *iter;
								szFind.TrimRight();
								strP1.TrimRight();
								strP2.TrimRight();
							if(szFind == (strP1 +strP2))
							{
								fff = 100;
								break;
							}
						}
						if(fff == 100)
						{
							strP3.Format(_T("%s关联%s已存在，重新选择"),strP1,strP2);
								AfxMessageBox(strP3, MB_OK);
								break;
						}
					}
				}
				if(fff == 100)
					break;
			}//if
		}
		for(int ndisItem=0;ndisItem<nItemdis;ndisItem++)
		{
     			if(m_listDis.GetItemState(ndisItem,LVIS_SELECTED) & LVIS_SELECTED)
         			 ndisCount++;
		}
		if(fff == 100)
			return;
		if(nlistCount>1 && ndisCount >1)
		{
			AfxMessageBox(_T("多对多，请重新选择"), MB_OK);
			return;
		}
		if(nlistCount ==0  || ndisCount == 0)
		{
			AfxMessageBox(_T("列表未选择，请重新选择"), MB_OK);
			return;
		}

        for( nItem=0;nItem<nItemlist;nItem++)
		{
     		if(m_listCtrl.GetItemState(nItem,LVIS_SELECTED) & LVIS_SELECTED)
			{
				CString strPoint1=m_listCtrl.GetItemText(nItem,0);
				CString strPoint2=m_listCtrl.GetItemText(nItem,1);
				strPoint1.TrimRight();
				strPoint2.TrimRight();
//					int fff = 0;
					COleDateTime CTime;

					for(int ndis=0;ndis<nItemdis;ndis++)
					{
     					if(m_listDis.GetItemState(ndis,LVIS_SELECTED) & LVIS_SELECTED)
						{
            				try
							{
	         				 m_AxFeedENew->m_szEID  = PointDesid;
					m_AxFeedENew->m_szName = strPoint1;
					m_AxFeedENew->m_szcpointnum = strPoint2;
				             strP1=m_listDis.GetItemText(ndis,0);
			             	 strP1.TrimRight();
		      			     m_AxFeedENew->m_szepointnum = strP1;
		    			     m_AxFeedENew->m_szecpointnum = strPoint2 +strP1;
    						 m_AxFeedENew->m_szrecdate = CTime.GetCurrentTime();
     						 m_AxFeedENew->m_szUseridadd = theApp.curuser;
      						m_AxFeedENew->AddNew();  //Add a new, blank record
					   	    m_AxFeedENew->Update();    //Update the recordset
							//If this is a new record, requery the database table
							//otherwise we may out-of-sync
						    m_AxFeedENew->Requery();
							PointDesid++;
							}
		     			    catch (CAxException *e)
							{
					        	AfxMessageBox(e->m_szErrorDesc, MB_OK);
				        		delete e;
							}
						}//if
					}//for
            }//if
		}//for

    	for (int iItem = 2; iItem >= 0; iItem--)
		{
    		m_listCtrl.DeleteColumn(iItem);
			m_listDis.DeleteColumn(iItem);
		}
   	    m_strtable = "feedelectricity";  //控制策略显示
		OnClose();
        OnInitDialog();
		ShowAMD();
		GetDlgItem(IDC_BUT_ADD2)->ShowWindow(SW_HIDE);;
		GetDlgItem(IDC_BUT_MOD)->ShowWindow(SW_HIDE);;

		theApp.InitData();
	}
	else
	{
	int nItemCount=m_listDis.GetItemCount();
    for(int nItem=0;nItem<nItemCount;nItem++)
	{
		if(m_listDis.GetItemState(nItem,LVIS_SELECTED) & LVIS_SELECTED)
		{
			m_listDis.DeleteItem(nItem);
		}
	}
	}
//		theApp.InitData();
}

void CSettingHostDlg::OnButtonSelectall() 
{
    	int nItemCount=m_listCtrl.GetItemCount();
        for(int nItem=0;nItem<nItemCount;nItem++)
		{
    		CString strPointNo=m_listCtrl.GetItemText(nItem,1);
	    	int nItemCount1=m_listDis.GetItemCount();
	    	BOOL bExist=FALSE;
    		for(int j=0; j<nItemCount1; j++)
			{
		    	if(strPointNo==m_listDis.GetItemText(j,0))
				{
		    		bExist=TRUE;
		    		break;
				}
			}
	    	if(!bExist)
	    		m_listDis.InsertItem(nItemCount1, strPointNo, 0);
		}
}

void CSettingHostDlg::OnButtonDeselectall() 
{
	if(m_strtable == _T("AddControl"))    //加控制策略   取消时回到控制策略显示
	{
    	for (int iItem = 2; iItem >= 0; iItem--)
		{
    		m_listCtrl.DeleteColumn(iItem);
			m_listDis.DeleteColumn(iItem);
		}
   	    m_strtable = m_ADTypeTable[5].TableName;  //控制策略显示
		OnClose();
        OnInitDialog();
		ShowAMD();
		GetDlgItem(IDC_BUT_ADD2)->ShowWindow(SW_HIDE);;
		GetDlgItem(IDC_BUT_MOD)->ShowWindow(SW_HIDE);;
	}
	else if(m_strtable == _T("AddFeedE"))    //加馈电策略   取消时回到馈电策略显示
	{
    	for (int iItem = 2; iItem >= 0; iItem--)
		{
    		m_listCtrl.DeleteColumn(iItem);
			m_listDis.DeleteColumn(iItem);
		}
   	    m_strtable = "feedelectricity";  //馈电策略显示
		OnClose();
        OnInitDialog();
		ShowAMD();
		GetDlgItem(IDC_BUT_ADD2)->ShowWindow(SW_HIDE);;
		GetDlgItem(IDC_BUT_MOD)->ShowWindow(SW_HIDE);;
	}
	else
	{
    	m_listDis.DeleteAllItems();
//    	theApp.InitData();
	}
}

void CSettingHostDlg::OnButtonSave() 
{
  try
  {
	if(!m_bADD)
	{
        if ( m_DisPoint._IsOpen() )
               m_DisPoint.Close();
		m_DisPoint.Create();
		m_DisPoint.CursorType(adOpenDynamic);
		m_DisPoint.CacheSize(50);
		m_DisPoint._SetRecordsetEvents(new CAccountSetEvents);
		CString strPointNo; 
		strPointNo.Format(_T("SELECT * From dispoint WHERE DISID = %d"),PointDesid);
		m_DisPoint.Open(strPointNo, &m_Cn);
		m_DisPoint.MarshalOptions(adMarshalModifiedOnly);
	}

	UpdateData(TRUE);           //Exchange dialog data
       m_DisPointNew->m_szDISID  = PointDesid;

	   if(m_listDis.GetItemText(0,0) != _T(""))
    	   m_DisPointNew->m_szstr0 = m_listDis.GetItemText(0,0)+_T("|")+m_listDis.GetItemText(1,0)+"|"+m_listDis.GetItemText(2,0);
	   else
    	   m_DisPointNew->m_szstr0 = _T("");
	   if(m_listDis.GetItemText(3,0) != _T(""))
    	   m_DisPointNew->m_szstr1 = m_listDis.GetItemText(3,0)+_T("|")+m_listDis.GetItemText(4,0)+"|"+m_listDis.GetItemText(5,0);
	   else
    	   m_DisPointNew->m_szstr1 = _T("");
	   if(m_listDis.GetItemText(6,0) != _T(""))
    	   m_DisPointNew->m_szstr2 = m_listDis.GetItemText(6,0)+_T("|")+m_listDis.GetItemText(7,0)+"|"+m_listDis.GetItemText(8,0);
	   else
    	   m_DisPointNew->m_szstr2 = _T("");
	   if(m_listDis.GetItemText(9,0) != _T(""))
    	   m_DisPointNew->m_szstr3 = m_listDis.GetItemText(9,0)+_T("|")+m_listDis.GetItemText(10,0)+"|"+m_listDis.GetItemText(11,0);
	   else
    	   m_DisPointNew->m_szstr3 = _T("");
	   if(m_listDis.GetItemText(12,0) != _T(""))
    	   m_DisPointNew->m_szstr4 = m_listDis.GetItemText(12,0)+_T("|")+m_listDis.GetItemText(13,0)+"|"+m_listDis.GetItemText(14,0);
	   else
    	   m_DisPointNew->m_szstr4 = _T("");
	   if(m_listDis.GetItemText(15,0) != _T(""))
    	   m_DisPointNew->m_szstr5 = m_listDis.GetItemText(15,0)+_T("|")+m_listDis.GetItemText(16,0)+"|"+m_listDis.GetItemText(17,0);
	   else
    	   m_DisPointNew->m_szstr5 = _T("");
	   if(m_listDis.GetItemText(18,0) != _T(""))
    	   m_DisPointNew->m_szstr6 = m_listDis.GetItemText(18,0)+_T("|")+m_listDis.GetItemText(19,0)+"|"+m_listDis.GetItemText(20,0);
	   else
    	   m_DisPointNew->m_szstr6 = _T("");
	   if(m_listDis.GetItemText(21,0) != _T(""))
    	   m_DisPointNew->m_szstr7 = m_listDis.GetItemText(21,0)+_T("|")+m_listDis.GetItemText(22,0)+"|"+m_listDis.GetItemText(23,0);
	   else
    	   m_DisPointNew->m_szstr7 = _T("");
	   if(m_listDis.GetItemText(24,0) != _T(""))
    	   m_DisPointNew->m_szstr8 = m_listDis.GetItemText(24,0)+_T("|")+m_listDis.GetItemText(25,0)+"|"+m_listDis.GetItemText(26,0);
	   else
    	   m_DisPointNew->m_szstr8 = _T("");
	   if(m_listDis.GetItemText(27,0) != _T(""))
	       m_DisPointNew->m_szstr9 = m_listDis.GetItemText(27,0)+_T("|")+m_listDis.GetItemText(28,0)+"|"+m_listDis.GetItemText(29,0);
	   else
    	   m_DisPointNew->m_szstr9 = _T("");
	   if(m_listDis.GetItemText(30,0) != _T(""))
    	   m_DisPointNew->m_szstr10 = m_listDis.GetItemText(30,0)+_T("|")+m_listDis.GetItemText(31,0)+"|"+m_listDis.GetItemText(32,0);
	   else
    	   m_DisPointNew->m_szstr10 = _T("");
	   if(m_listDis.GetItemText(33,0) != _T(""))
    	   m_DisPointNew->m_szstr11 = m_listDis.GetItemText(33,0)+_T("|")+m_listDis.GetItemText(34,0)+"|"+m_listDis.GetItemText(35,0);
	   else
    	   m_DisPointNew->m_szstr11 = _T("");
	   if(m_listDis.GetItemText(36,0) != _T(""))
    	   m_DisPointNew->m_szstr12 = m_listDis.GetItemText(36,0)+_T("|")+m_listDis.GetItemText(37,0)+"|"+m_listDis.GetItemText(38,0);
	   else
    	   m_DisPointNew->m_szstr12 = "";
	   if(m_listDis.GetItemText(39,0) != "")
    	   m_DisPointNew->m_szstr13 = m_listDis.GetItemText(39,0)+"|"+m_listDis.GetItemText(40,0)+"|"+m_listDis.GetItemText(41,0);
	   else
    	   m_DisPointNew->m_szstr13 = "";
	   if(m_listDis.GetItemText(42,0) != "")
    	   m_DisPointNew->m_szstr14 = m_listDis.GetItemText(42,0)+"|"+m_listDis.GetItemText(43,0)+"|"+m_listDis.GetItemText(44,0);
	   else
    	   m_DisPointNew->m_szstr14 = "";
	   if(m_listDis.GetItemText(45,0) != "")
    	   m_DisPointNew->m_szstr15 = m_listDis.GetItemText(45,0)+"|"+m_listDis.GetItemText(46,0)+"|"+m_listDis.GetItemText(47,0);
	   else
    	   m_DisPointNew->m_szstr15 = "";
	   if(m_listDis.GetItemText(48,0) != "")
    	   m_DisPointNew->m_szstr16 = m_listDis.GetItemText(48,0)+"|"+m_listDis.GetItemText(49,0)+"|"+m_listDis.GetItemText(50,0);
	   else
    	   m_DisPointNew->m_szstr16 = "";
	   if(m_listDis.GetItemText(51,0) != "")
    	   m_DisPointNew->m_szstr17 = m_listDis.GetItemText(51,0)+"|"+m_listDis.GetItemText(52,0)+"|"+m_listDis.GetItemText(53,0);
	   else
    	   m_DisPointNew->m_szstr17 = "";
	   if(m_listDis.GetItemText(54,0) != "")
    	   m_DisPointNew->m_szstr18 = m_listDis.GetItemText(54,0)+"|"+m_listDis.GetItemText(55,0)+"|"+m_listDis.GetItemText(56,0);
	   else
    	   m_DisPointNew->m_szstr18 = "";
	   if(m_listDis.GetItemText(57,0) != "")
    	   m_DisPointNew->m_szstr19 = m_listDis.GetItemText(57,0)+"|"+m_listDis.GetItemText(58,0)+"|"+m_listDis.GetItemText(59,0);
	   else
    	   m_DisPointNew->m_szstr19 = "";

	if(m_bADD)
        m_DisPoint.AddNew();  //Add a new, blank record
	m_DisPoint.Update();    //Update the recordset
		//If this is a new record, requery the database table
		//otherwise we may out-of-sync
	if(m_bADD)
        m_DisPoint.Requery();

//	AfxMessageBox("需要显示的测点已保存", MB_OK);
  }
  catch (CAxException *e)
  {
    AfxMessageBox(e->m_szErrorDesc, MB_OK);
    delete e;
  }

  theApp.InitData();
  MessageBeep(MB_OK);
  EndDialog(IDOK);
}

void CSettingHostDlg::OnchangeComboF() 
{
	UpdateData(TRUE);           //Exchange dialog data
	if("AddControl" ==  m_strtable)   //加控制策略
	{
		if ( m_PointDes._IsEmpty() )
		  return;
     	m_listCtrl.DeleteAllItems();
//     	m_listDis.DeleteAllItems();
		CString dddd,cccc;
		int iItem = 0;
		int iItem1 = 0;
		int nfds3 = m_wndComboSize3.GetCurSel();
//		int nfds4 = m_wndComboSize4.GetCurSel();
		m_PointDes.MoveFirst();
		while ( !m_PointDes.IsEOF() )
		{
    		dddd = m_PointDes.m_szpointnum;
			cccc.Format("%d", m_PointDes.m_szPID);
			if(m_PointDes.m_szfds == nfds3+1  && dddd.Find("C") == -1)
			{
             		int nfds = m_PointDes.m_szfds;
              		int nchan = m_PointDes.m_szchan;
         		m_listCtrl.InsertItem(iItem, m_SlaveStation[nfds][nchan].WatchName);
        		m_listCtrl.SetItemText(iItem, 1, m_PointDes.m_szpointnum);
        		m_listCtrl.SetItemText(iItem, 2, cccc);
    			iItem++;
			}
			m_PointDes.MoveNext();
		}
	}
	else if("AddFeedE" ==  m_strtable)   //加馈电策略
	{
		if ( m_PointDes._IsEmpty() )
		  return;
     	m_listCtrl.DeleteAllItems();
//     	m_listDis.DeleteAllItems();
		CString dddd,cccc;
		int iItem = 0;
		int iItem1 = 0;
		int nfds3 = m_wndComboSize3.GetCurSel();
		int nfds4 = m_wndComboSize4.GetCurSel();
		m_PointDes.MoveFirst();
		while ( !m_PointDes.IsEOF() )
		{
    		dddd = m_PointDes.m_szpointnum;
			cccc.Format("%d", m_PointDes.m_szPID);
			if(m_PointDes.m_szfds == nfds3+1  && dddd.Find("C") != -1)
			{
             		int nfds = m_PointDes.m_szfds;
              		int nchan = m_PointDes.m_szchan;
         		m_listCtrl.InsertItem(iItem, m_SlaveStation[nfds][nchan].WatchName);
        		m_listCtrl.SetItemText(iItem, 1, m_PointDes.m_szpointnum);
        		m_listCtrl.SetItemText(iItem, 2, cccc);
    			iItem++;
			}
			m_PointDes.MoveNext();
		}
	}
	else if(m_ADTypeTable[4].TableName ==  m_strtable)    //选择测点显示
	{
		if ( m_PointDes._IsEmpty() )
		  return;
     	m_listCtrl.DeleteAllItems();
//     	m_listDis.DeleteAllItems();
		CString dddd,cccc;
		int iItem = 0;
		int nfds3 = m_wndComboSize3.GetCurSel();
		m_PointDes.MoveFirst();
		while ( !m_PointDes.IsEOF() )
		{
    		dddd = m_PointDes.m_szpointnum;
			dddd.TrimRight();
			if(m_PointDes.m_szfds == nfds3+1 )
			{
             		int nfds = m_PointDes.m_szfds;
              		int nchan = m_PointDes.m_szchan;
         		m_listCtrl.InsertItem(iItem, m_SlaveStation[nfds][nchan].WatchName);
        		m_listCtrl.SetItemText(iItem, 1, dddd);
         		dddd = m_PointDes.m_szutype;
    			dddd.TrimRight();
        		m_listCtrl.SetItemText(iItem, 2, dddd);
    			iItem++;
			}
			m_PointDes.MoveNext();
		}
	}
}

//void CSettingHostDlg::OnButtonCANCEL() 
//{

//}
void CSettingHostDlg::OnchangeCombo2() 
{
//	m_ComBoxD.GetWindowText(m_strsel);
	if(m_bADD)
	{
    	if(m_wndComboSize2.GetCurSel() == 2)
		{
    		m_wndComboSize4.SetCurSel(3);
            GetDlgItem(IDC_COMBO4)->EnableWindow(FALSE);
		}
      	else
            GetDlgItem(IDC_COMBO4)->EnableWindow(TRUE);
	}
	else
            GetDlgItem(IDC_COMBO4)->EnableWindow(FALSE);

	if(m_ADTypeTable[4].TableName ==  m_strtable)    //选择测点显示
	{
		if ( m_PointDes._IsEmpty() )
		  return;
     	m_listCtrl.DeleteAllItems();
		CString dddd,cccc;
		int iItem = 0;
		int nfds3 = m_wndComboSize2.GetCurSel();
			if(nfds3 >2)
				nfds3 = 7+nfds3;
		m_PointDes.MoveFirst();
		while ( !m_PointDes.IsEOF() )
		{
    		dddd = m_PointDes.m_szpointnum;
			dddd.TrimRight();
			if(m_PointDes.m_szptype == nfds3 )
			{
             		int nfds = m_PointDes.m_szfds;
              		int nchan = m_PointDes.m_szchan;
         		m_listCtrl.InsertItem(iItem, m_SlaveStation[nfds][nchan].WatchName);
        		m_listCtrl.SetItemText(iItem, 1, dddd);
         		dddd = m_PointDes.m_szutype;
    			dddd.TrimRight();
        		m_listCtrl.SetItemText(iItem, 2, dddd);
    			iItem++;
			}
			m_PointDes.MoveNext();
		}
	}
}

void CSettingHostDlg::OnChCB03() 
{
	UpdateData(TRUE);
		CString dddd,cccc;
		GetDlgItem(IDC_COMBO3)->GetWindowText(cccc);
		int nfds3 = m_Str2Data.String2Int(cccc);
		if(nfds3 <1 || nfds3>60)
		{
          	AfxMessageBox("分站号在1-60间选择！", MB_OK);
    		GetDlgItem(IDC_COMBO3)->SetWindowText("1");
	    	  return;
		}
	if(m_ADTypeTable[4].TableName ==  m_strtable)    //选择测点显示
	{
		if ( m_PointDes._IsEmpty() )
		  return;
     	m_listCtrl.DeleteAllItems();
//     	m_listDis.DeleteAllItems();
		int iItem = 0;
		m_PointDes.MoveFirst();
		while ( !m_PointDes.IsEOF() )
		{
    		dddd = m_PointDes.m_szpointnum;
    			dddd.TrimRight();
			if(m_PointDes.m_szfds == nfds3 )
			{
             		int nfds = m_PointDes.m_szfds;
              		int nchan = m_PointDes.m_szchan;
         		m_listCtrl.InsertItem(iItem, m_SlaveStation[nfds][nchan].WatchName);
        		m_listCtrl.SetItemText(iItem, 1, dddd);
         		dddd = m_PointDes.m_szutype;
    			dddd.TrimRight();
        		m_listCtrl.SetItemText(iItem, 2, dddd);
    			iItem++;
			}
			m_PointDes.MoveNext();
		}
	}
	UpdateData(FALSE);
}

void CSettingHostDlg::OnChCB04() 
{
	UpdateData(TRUE);
		CString dddd,cccc;
		GetDlgItem(IDC_COMBO4)->GetWindowText(cccc);
		int nfds3 = m_Str2Data.String2Int(cccc);
		if(nfds3 <1 || nfds3>16)
		{
          	AfxMessageBox("通道号在1-16间选择！", MB_OK);
    		GetDlgItem(IDC_COMBO4)->SetWindowText("1");
	    	  return;
		}
	UpdateData(FALSE);
}