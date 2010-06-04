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

#include "AddSQLDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using namespace dbAx;

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
	m_strtable = _T("");
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
	DDX_Control(pDX, IDC_LIST_CTRL, m_listCtrl);
	DDX_Control(pDX, IDC_CLR_SORTBACK, m_cpSortBack);
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
	ON_BN_CLICKED(IDC_BUT_DEL, OnBtnDEL)
	ON_BN_CLICKED(IDC_BUT_MOD, OnBtnMOD)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSettingHostDlg message handlers
BOOL CSettingHostDlg::OnInitDialog()
{
	CXTResizeDialog::OnInitDialog();

	// TODO: Add extra initialization here
    if ( !ConnectToProvider() )
       return (FALSE);
	
	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);         // Set big icon
	SetIcon(m_hIcon, FALSE);        // Set small icon

	// Set control resizing.
//	SetResize(IDOK,                  SZ_TOP_RIGHT,   SZ_TOP_RIGHT);
	SetResize(IDOK,                  SZ_BOTTOM_LEFT,   SZ_BOTTOM_LEFT);
	SetResize(IDCANCEL,              SZ_BOTTOM_LEFT,   SZ_BOTTOM_LEFT);
	SetResize(IDC_LIST_CTRL,         SZ_TOP_LEFT,    SZ_BOTTOM_RIGHT);

//	SetResize(IDC_GBOX_HEADER,       SZ_BOTTOM_LEFT, SZ_BOTTOM_RIGHT);
	SetResize(IDC_BUT_ADD,      SZ_BOTTOM_LEFT, SZ_BOTTOM_LEFT);
	SetResize(IDC_BUT_DEL,      SZ_BOTTOM_LEFT, SZ_BOTTOM_LEFT);
	SetResize(IDC_BUT_MOD,      SZ_BOTTOM_LEFT, SZ_BOTTOM_LEFT);

	SetResize(IDC_COMBO1,      SZ_BOTTOM_LEFT, SZ_BOTTOM_LEFT);
	SetResize(IDC_COMBO2,      SZ_BOTTOM_LEFT, SZ_BOTTOM_LEFT);
	SetResize(IDC_COMBO3,      SZ_BOTTOM_LEFT, SZ_BOTTOM_LEFT);
	SetResize(IDC_COMBO4,      SZ_BOTTOM_LEFT, SZ_BOTTOM_LEFT);
	SetResize(IDC_STATIC1,      SZ_BOTTOM_LEFT, SZ_BOTTOM_LEFT);
	SetResize(IDC_STATIC2,      SZ_BOTTOM_LEFT, SZ_BOTTOM_LEFT);
	SetResize(IDC_STATIC3,      SZ_BOTTOM_LEFT, SZ_BOTTOM_LEFT);
	SetResize(IDC_STATIC4,      SZ_BOTTOM_LEFT, SZ_BOTTOM_LEFT);

	// Enable Office XP themes.
	XTThemeManager()->SetTheme(xtThemeOfficeXP);

	// Load window placement
//	LoadPlacement(_T("CListCtrlDlg"));
	// Give better margin to editors
/*	m_listCtrl.SetCellMargin(1.2);
	CGridRowTraitXP* pRowTrait = new CGridRowTraitXP;
	m_listCtrl.SetDefaultRowTrait(pRowTrait);
	// Create Columns
	m_listCtrl.InsertHiddenLabelColumn();	// Requires one never uses column 0

	// TODO: Add extra initialization here
	int iItem;
	for (iItem = 0; iItem < 50; ++iItem)
	{
		CString strItem;
		strItem.Format(_T("Item %d"), iItem);
//		m_listCtrl.InsertItem(iItem, strItem, 0);
	}
*/
	// Get the windows handle to the header control for the
	// list control then subclass the control.
	HWND hWndHeader = m_listCtrl.GetDlgItem(0)->GetSafeHwnd();
	m_header.SubclassWindow(hWndHeader);

	// add bitmap images.
//	m_header.SetBitmap(0, IDB_COLUMN_0, FALSE, RGB(0,255,0));
//	m_header.SetBitmap(1, IDB_COLUMN_1, FALSE, RGB(0,255,0));
//	m_header.SetBitmap(2, IDB_COLUMN_2, FALSE, RGB(0,255,0));

	// enable auto sizing.
	m_header.EnableAutoSize(TRUE);
	m_header.ResizeColumnsToFit();
	SortColumn(m_nSortedCol, m_bAscending);

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

/*	for(int col = 0; col < m_DataModel.GetColCount() ; ++col)
	{
		const string& title = m_DataModel.GetColTitle(col);
		CGridColumnTrait* pTrait = NULL;
		if (col==0)	// City
		{
			pTrait = new CGridColumnTraitEdit;
		}
		if (col==1)	// State
		{
			CGridColumnTraitCombo* pComboTrait = new CGridColumnTraitCombo;
			const vector<string>& states = m_DataModel.GetStates();
			for(size_t i=0; i < states.size() ; ++i)
				pComboTrait->AddItem((int)i, CString(states[i].c_str()));
			pTrait = pComboTrait;
		}
		if (col==2)	// Country
		{
			CGridColumnTraitCombo* pComboTrait = new CGridColumnTraitCombo;
			pComboTrait->SetStyle( pComboTrait->GetStyle() | CBS_DROPDOWNLIST);
			const vector<string>& countries = m_DataModel.GetCountries();
			for(size_t i=0; i < countries.size() ; ++i)
				pComboTrait->AddItem((int)i, CString(countries[i].c_str()));
			pTrait = pComboTrait;
		}
		m_listCtrl.InsertColumnTrait(col+1, CString(title.c_str()), LVCFMT_LEFT, 100, col, NULL);
	}*/
//	OnSelendokComboThemes();
	m_listCtrl.ModifyExtendedStyle(0, LVS_EX_FULLROWSELECT|LVS_SHOWSELALWAYS | LVS_EX_GRIDLINES);
	m_listCtrl.EnableUserSortColor(BoolType(m_bSortColor));
	m_listCtrl.EnableUserListColor(BoolType(m_bListColor));
	m_listCtrl.EnableUserRowColor(BoolType(m_bRowColor));


	if(m_ADTypeTable[1].TableName ==  m_strtable)
	{
		HideControls();
		SetWindowText(_T(m_ADTypeTable[1].NameD));
    	MoveWindow(CRect(50,100,960,700));
		m_listCtrl.InsertColumn(0,m_ADTypeTable[1].m_DTypeTFD.Name,LVCFMT_LEFT,100);
		m_listCtrl.InsertColumn(1,m_ADTypeTable[1].m_DTypeTFD.name0,LVCFMT_LEFT,100);
		m_listCtrl.InsertColumn(2,m_ADTypeTable[1].m_DTypeTFD.name1,LVCFMT_LEFT,100);
		m_listCtrl.InsertColumn(3,m_ADTypeTable[1].m_DTypeTFD.name2,LVCFMT_LEFT,100);
		m_listCtrl.InsertColumn(4,m_ADTypeTable[1].m_DTypeTFD.palms,LVCFMT_LEFT,100);
		m_listCtrl.InsertColumn(5,m_ADTypeTable[1].m_DTypeTFD.falm,LVCFMT_LEFT,100);
		m_listCtrl.InsertColumn(6,m_ADTypeTable[1].m_DTypeTFD.recdate,LVCFMT_LEFT,100);
		m_listCtrl.InsertColumn(7,m_ADTypeTable[1].m_DTypeTFD.Useridadd,LVCFMT_LEFT,100);
		m_listCtrl.InsertColumn(8,m_ADTypeTable[1].m_DTypeTFD.ptype,LVCFMT_LEFT,100);
	}
	if(m_ADTypeTable[0].TableName ==  m_strtable)
	{
		HideControls();
		SetWindowText(_T(m_ADTypeTable[0].NameD));
    	MoveWindow(CRect(50,100,960,700));
		m_listCtrl.InsertColumn(0,m_ADTypeTable[0].m_DTypeTFD.Name,LVCFMT_LEFT,100);
		m_listCtrl.InsertColumn(1,m_ADTypeTable[0].m_DTypeTFD.ltop,LVCFMT_LEFT,100);
		m_listCtrl.InsertColumn(2,m_ADTypeTable[0].m_DTypeTFD.lbom,LVCFMT_LEFT,100);
		m_listCtrl.InsertColumn(3,m_ADTypeTable[0].m_DTypeTFD.palmu,LVCFMT_LEFT,100);
		m_listCtrl.InsertColumn(4,m_ADTypeTable[0].m_DTypeTFD.palmd,LVCFMT_LEFT,100);
		m_listCtrl.InsertColumn(5,m_ADTypeTable[0].m_DTypeTFD.pbrk,LVCFMT_LEFT,100);
		m_listCtrl.InsertColumn(6,m_ADTypeTable[0].m_DTypeTFD.prtn,LVCFMT_LEFT,100);
		m_listCtrl.InsertColumn(7,m_ADTypeTable[0].m_DTypeTFD.punit,LVCFMT_LEFT,100);
		m_listCtrl.InsertColumn(8,m_ADTypeTable[0].m_DTypeTFD.recdate,LVCFMT_LEFT,100);
		m_listCtrl.InsertColumn(9,m_ADTypeTable[0].m_DTypeTFD.Useridadd,LVCFMT_LEFT,100);
	}
	if(m_ADTypeTable[2].TableName ==  m_strtable)
	{
		HideControls();
		SetWindowText(_T(m_ADTypeTable[2].NameD));
    	MoveWindow(CRect(300,300,460,700));
		m_listCtrl.InsertColumn(0,m_ADTypeTable[2].m_DTypeTFD.Name,LVCFMT_LEFT,300);
	}
	if(m_ADTypeTable[3].TableName ==  m_strtable)
	{
		HideControls();
		SetWindowText(_T(m_ADTypeTable[3].NameD));
    	MoveWindow(CRect(50,100,960,700));
		m_listCtrl.InsertColumn(0,m_ADTypeTable[3].m_DTypeTFD.Name,LVCFMT_LEFT,200);
		m_listCtrl.InsertColumn(1,m_ADTypeTable[3].m_DTypeTFD.pointnum,LVCFMT_LEFT,200);
		m_listCtrl.InsertColumn(2,m_ADTypeTable[3].m_DTypeTFD.utype,LVCFMT_LEFT,200);
	}

    BuildAccountList();

	return TRUE;  // return TRUE  unless you set the focus to a control 
}

//BuildAccountList will populate the Account list with all
//available records. This method is called on startup and 
//each time a new Account record is added, edited, or deleted
void CSettingHostDlg::BuildAccountList()
{
    m_listCtrl.DeleteAllItems();

  try
  {
	  if(m_ADTypeTable[1].TableName ==  m_strtable)
	  {
		if ( m_AccountSet._IsEmpty() )
		{
		  m_listCtrl.InsertItem(0, _T("<< >>"));
		  return;
		}
		m_listCtrl.SetItemCount(m_AccountSet.RecordCount());
		int iItem = 0;
		m_AccountSet.MoveFirst();
		while ( !m_AccountSet.IsEOF() )
		{
				  CString dddd;
				  m_listCtrl.InsertItem(iItem, m_AccountSet.m_szName);
			//		dddd = m_AccountSet.m_szptype;
			//		bool xxx = m_AccountSet.m_szfdel;
				  m_listCtrl.SetItemText(iItem, 1, m_AccountSet.m_szname0);
				  m_listCtrl.SetItemText(iItem, 2, m_AccountSet.m_szname1);
				  m_listCtrl.SetItemText(iItem, 3, m_AccountSet.m_szname2);
				  dddd.Format("%d",m_AccountSet.m_szpalms);
				  m_listCtrl.SetItemText(iItem, 4, dddd);
				  m_listCtrl.SetItemText(iItem, 5, m_AccountSet.m_szfalm);
				  COleDateTime oleDateTime=m_AccountSet.m_szrecdate;
			//	  CString   str   =   oleDateTime.Format(_T("%A, %B %d, %Y")); 
				  CString   str   =   oleDateTime.Format(_T("%Y-%m-%d %H:%M:%S")); 
			//	  oleDateTime = m_AccountSet.m_szdeldate;
				  m_listCtrl.SetItemText(iItem, 6, str);
				  m_listCtrl.SetItemText(iItem, 7, m_AccountSet.m_szUseridadd);
				  m_listCtrl.SetItemText(iItem, 8, m_AccountSet.m_szptype);
			iItem++;
			sqlid = m_AccountSet.m_szDID +1;
			m_AccountSet.MoveNext();
		}
        m_AccountSet.MoveFirst();
	  }
	  else if(m_ADTypeTable[0].TableName ==  m_strtable)
	  {
		if ( m_ContactSet._IsEmpty() )
		{
//		  m_listCtrl.InsertItem(0, _T("<< >>"));
		  return;
		}
		m_listCtrl.SetItemCount(m_ContactSet.RecordCount());
		int iItem = 0;
		m_ContactSet.MoveFirst();
		while ( !m_ContactSet.IsEOF() )
		{
				  CString dddd;
				  m_listCtrl.InsertItem(iItem, m_ContactSet.m_szName);
				  dddd.Format("%.4f",m_ContactSet.m_szltop);
				  m_listCtrl.SetItemText(iItem, 1, dddd);
				  dddd.Format("%.4f",m_ContactSet.m_szlbom);
				  m_listCtrl.SetItemText(iItem, 2, dddd);
				  dddd.Format("%.4f",m_ContactSet.m_szpalmu);
				  m_listCtrl.SetItemText(iItem, 3, dddd);
				  dddd.Format("%.4f",m_ContactSet.m_szpalmd);
				  m_listCtrl.SetItemText(iItem, 4, dddd);
				  dddd.Format("%.4f",m_ContactSet.m_szpbrk);
				  m_listCtrl.SetItemText(iItem, 5, dddd);
				  dddd.Format("%.4f",m_ContactSet.m_szprtn);
				  m_listCtrl.SetItemText(iItem, 6, dddd);
				  m_listCtrl.SetItemText(iItem, 7, m_ContactSet.m_szpunit);
				  COleDateTime oleDateTime=m_ContactSet.m_szrecdate;
				  dddd   =   oleDateTime.Format(_T("%Y-%m-%d %H:%M:%S")); 
				  m_listCtrl.SetItemText(iItem, 8, dddd);
				  m_listCtrl.SetItemText(iItem, 9, m_ContactSet.m_szUseridadd);
			iItem++;
			sqlid = m_ContactSet.m_szAID +1;
			m_ContactSet.MoveNext();
		}
        m_ContactSet.MoveFirst();
	  }
	  else if(m_ADTypeTable[2].TableName ==  m_strtable)
	  {
		if ( m_MAlocation._IsEmpty() )
		{
//		  m_listCtrl.InsertItem(0, _T("<< >>"));
		  return;
		}
		m_listCtrl.SetItemCount(m_MAlocation.RecordCount());
		int iItem = 0;
		m_MAlocation.MoveFirst();
		while ( !m_MAlocation.IsEOF() )
		{
    		  m_listCtrl.InsertItem(iItem, m_MAlocation.m_szName);
			iItem++;
			sqlid = m_MAlocation.m_szlocationID +1;
			m_MAlocation.MoveNext();
		}
        m_MAlocation.MoveFirst();
	  }



       	// Insert data into list-control by copying from datamodel
//    	int nItem = 0;
/*    	for(size_t rowId = 0; rowId < m_DataModel.GetRowIds() ; ++rowId)
		{
		nItem = m_listCtrl.InsertItem(++nItem, CString(m_DataModel.GetCellText(rowId, 0).c_str()));
		m_listCtrl.SetItemData(nItem, rowId);
    		for(int col = 0; col < m_DataModel.GetColCount() ; ++col)
			{
			m_listCtrl.SetItemText(nItem, col+1, CString(m_DataModel.GetCellText(rowId, col).c_str()));
			}
		}
*/

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
    m_Cn._SetConnectionEvents(new CCardFileEvents);

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
		m_AccountSet.Open(_T("Select * From digitaltype"), &m_Cn);

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
		m_ContactSet.Open(_T("Select * From analogtype"), &m_Cn);
		m_ContactSet.MarshalOptions(adMarshalModifiedOnly);
	}
//	if(m_ADTypeTable[2].TableName ==  m_strtable)
	{
		m_MAlocation.Create();
		m_MAlocation.CursorType(adOpenDynamic);
		m_MAlocation.CacheSize(50);
		m_MAlocation._SetRecordsetEvents(new CAccountSetEvents);
		m_MAlocation.Open(_T("Select * From fixlocation"), &m_Cn);
		m_MAlocation.MarshalOptions(adMarshalModifiedOnly);
	}
		m_PointDes.Create();
		m_PointDes.CursorType(adOpenDynamic);
		m_PointDes.CacheSize(50);
		m_PointDes._SetRecordsetEvents(new CAccountSetEvents);
		m_PointDes.Open(_T("Select * From pointdescription"), &m_Cn);
		m_PointDes.MarshalOptions(adMarshalModifiedOnly);

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
       BuildAccountList();
   }   */
//   AfxMessageBox(sTemp);
  *pResult = 0;

  if ( pNMLV->uNewState == 3 )
  {
	  if(m_ADTypeTable[1].TableName ==  m_strtable && !m_AccountSet._IsEmpty() ) 
	  {
           m_AccountSet.AbsolutePosition(pNMLV->iItem + 1);
	  }
	  else if(m_ADTypeTable[0].TableName ==  m_strtable && !m_ContactSet._IsEmpty() )
	  {
           m_ContactSet.AbsolutePosition(pNMLV->iItem + 1);
	  }
	  else if(m_ADTypeTable[2].TableName ==  m_strtable && !m_MAlocation._IsEmpty() )
	  {
           m_MAlocation.AbsolutePosition(pNMLV->iItem + 1);
	  }
	  else if(m_ADTypeTable[3].TableName ==  m_strtable && !m_PointDes._IsEmpty() )
	  {
           m_PointDes.AbsolutePosition(pNMLV->iItem + 1);
	  }
//    BuildAccountList();
  }
}

void CSettingHostDlg::OnClose()
{
  //Closing of library objects is ensured as each object
  //goes out of scope, but doing a manual shutdown doesn’t hurt.

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
  CAccountDlg dlg(this);
  dlg.acdid= sqlid;
  dlg.strtable= m_strtable;

  if ( dlg.DoModal() == IDOK )
    BuildAccountList();
}

void CSettingHostDlg::HideControls()
{
    	GetDlgItem(IDC_STATIC1)->ShowWindow(SW_HIDE);;
    	GetDlgItem(IDC_STATIC2)->ShowWindow(SW_HIDE);;
    	GetDlgItem(IDC_STATIC3)->ShowWindow(SW_HIDE);;
    	GetDlgItem(IDC_STATIC4)->ShowWindow(SW_HIDE);;
    	GetDlgItem(IDC_COMBO1)->ShowWindow(SW_HIDE);;
    	GetDlgItem(IDC_COMBO2)->ShowWindow(SW_HIDE);;
    	GetDlgItem(IDC_COMBO3)->ShowWindow(SW_HIDE);;
    	GetDlgItem(IDC_COMBO4)->ShowWindow(SW_HIDE);;
    	GetDlgItem(IDOK)->ShowWindow(SW_HIDE);;
    	GetDlgItem(IDCANCEL)->ShowWindow(SW_HIDE);;
}

void CSettingHostDlg::HideAMD()
{
    	GetDlgItem(IDC_BUT_ADD)->ShowWindow(SW_HIDE);;
    	GetDlgItem(IDC_BUT_DEL)->ShowWindow(SW_HIDE);;
    	GetDlgItem(IDC_BUT_MOD)->ShowWindow(SW_HIDE);;
}

void CSettingHostDlg::OnBtnDEL()
{
  CString szMsg;
	  if(m_ADTypeTable[1].TableName ==  m_strtable ) 
	  {
         szMsg.Format(_T("Delete %s?"), m_AccountSet.m_szName);
	  }
	  else if(m_ADTypeTable[0].TableName ==  m_strtable )
	  {
         szMsg.Format(_T("Delete %s?"), m_ContactSet.m_szName);
	  }
	  else if(m_ADTypeTable[2].TableName ==  m_strtable )
	  {
         szMsg.Format(_T("Delete %s?"), m_MAlocation.m_szName);
	  }
	  else if(m_ADTypeTable[3].TableName ==  m_strtable )
	  {
         szMsg.Format(_T("Delete %s?"), m_PointDes.m_szName);
	  }



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

	  if(m_ADTypeTable[1].TableName ==  m_strtable ) 
         m_AccountSet.Delete();
	  else if(m_ADTypeTable[0].TableName ==  m_strtable )
         m_ContactSet.Delete();
	  else if(m_ADTypeTable[2].TableName ==  m_strtable )
         m_MAlocation.Delete();
	  else if(m_ADTypeTable[3].TableName ==  m_strtable )
         m_PointDes.Delete();
//      m_Cn.Execute(szExecStr);

      BuildAccountList();
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
  CAccountDlg dlg(TRUE, this);
  dlg.strtable= m_strtable;
  if ( dlg.DoModal() == IDOK )
    BuildAccountList();
}

