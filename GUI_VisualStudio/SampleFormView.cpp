// SampleFormView.cpp : implementation file
//

#include "stdafx.h"
#include "GUI_VisualStudio.h"
#include "SampleFormView.h"
#include "MainFrm.h"

#include "SettingHostDlg.h"
#include "DCH5m.h"
#include "FormDraw.h"
#include "ColorSetDlg.h"
#include "DListEXT.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define BoolType(b) b?true:false

extern ADMainDis         m_ADMainDis[MAX_FDS][MAX_CHAN];          //调用显示
extern CommonStr             m_CommonStr[20];
extern ADCbreakE             m_CFeed[MAX_FDS][9][65];
extern ADCbreakE             m_ADCbreakE[MAX_FDS][MAX_CHAN][65];
extern SerialF                  m_Colorref[200];
extern  SlaveStation             m_SlaveStation[MAX_FDS][MAX_CHAN];
/////////////////////////////////////////////////////////////////////////////
// CSampleFormView

IMPLEMENT_DYNCREATE(CSampleFormView, CFormView)

CSampleFormView::CSampleFormView()
	: CFormView(CSampleFormView::IDD)
{
	//{{AFX_DATA_INIT(CSampleFormView)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_iTheme = 1;
	m_bSortArrow = TRUE;
	m_bHotTracking = TRUE;
	m_bWinTheme = TRUE;
	b_curdis = FALSE;

	m_nSortedCol = 0;
	m_bAscending = true;
	m_nSortedCol2 = 0;
	m_bAscending2 = true;
	m_nSortedCol3 = 0;
	m_bAscending3 = true;
	n_cF = 50;

	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	CXTPWinThemeWrapper themeWrapper;
	m_bWinTheme  = themeWrapper.IsThemeActive();
}

CSampleFormView::~CSampleFormView()
{

}

void CSampleFormView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSampleFormView)
	DDX_Control(pDX, IDC_LIST_POINT1, m_List1);
	DDX_Control(pDX, IDC_LIST_POINT2, m_List2);
	DDX_Control(pDX, IDC_LIST_POINT3, m_List3);
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSampleFormView, CFormView)
	//{{AFX_MSG_MAP(CSampleFormView)
	ON_COMMAND(ID_RCHART, OpenRTChart)
	ON_COMMAND(ID_DATADA, OpenDayRT)
	ON_COMMAND(ID_SELECT_POINT, OpenAddDel)
	ON_COMMAND(ID_ADJUST_POINT, Openadjust)
	ON_COMMAND(ID_DEL_ADJUST, Deladjust)
	ON_COMMAND(ID_ADJUST_ALL, AdjustAll)
	ON_COMMAND(ID_DEL_ADJUSTALL, DelAllAdjust)
	ON_COMMAND(IDC_COMBO_THEMES, OnSelendokComboThemes)
//	ON_WM_CREATE()
//	ON_WM_ERASEBKGND()
//	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_WM_CONTEXTMENU()
    ON_NOTIFY(NM_RCLICK,IDC_LIST_POINT1, OnRclick1)
    ON_NOTIFY(NM_RCLICK,IDC_LIST_POINT2, OnRclick2)
    ON_NOTIFY(NM_RCLICK,IDC_LIST_POINT3, OnRclick3)
	ON_NOTIFY(LVN_COLUMNCLICK,   IDC_LIST_POINT1,   OnColumnclickListstock) 
	ON_NOTIFY(LVN_COLUMNCLICK,   IDC_LIST_POINT2,   OnColumnclickListstock2) 
	ON_NOTIFY(LVN_COLUMNCLICK,   IDC_LIST_POINT3,   OnColumnclickListstock3) 
	ON_COMMAND(ID_DRAWS, OnDRAWS)//数据页改名
	ON_COMMAND(ID_FORMSCOLOR, OnFORMSCOLOR)//数据页color
	ON_COMMAND(ID_FORMPAGESO, OnFORMPAGESO)//数据页
	ON_COMMAND(ID_FORMSLISTEXT, OnFORMSLISTEXT)//数据页listext
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSampleFormView diagnostics

#ifdef _DEBUG
void CSampleFormView::AssertValid() const
{
	CFormView::AssertValid();
}

void CSampleFormView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSampleFormView message handlers

void CSampleFormView::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();

//	CMainFrame* pFWnd=(CMainFrame*)AfxGetMainWnd();
//   	pFWnd->m_pSampleFormView=this;

	if (!CreateImageList(m_SampleFormImageList, IDB_CLASSTREE))
		return ;
	// Create and attach image list
	m_ImageList.Create(16, 16, ILC_COLOR16 | ILC_MASK, 1, 0);
	m_ImageList.Add(AfxGetApp()->LoadIcon(IDR_GUI_WHTYPE));
	m_ImageList.Add(AfxGetApp()->LoadIcon(IDR_MAINFRAME));

//	::SetWindowText(pString);

//	m_List1.SetImageList(&m_SampleFormImageList, LVSIL_SMALL);   //每行图片
//	m_List2.SetImageList(&m_ImageList, LVSIL_SMALL);
	// Give better margin to editors
//	m_List1.SetCellMargin(1.2);
//	CGridRowTraitXP* pRowTrait = new CGridRowTraitXP;
//	m_List1.SetDefaultRowTrait(pRowTrait);

	// Create Columns
//	m_List1.InsertHiddenLabelColumn();	// Requires one never uses column 0
//	m_List2.InsertHiddenLabelColumn();	// Requires one never uses column 0
//	m_List3.InsertHiddenLabelColumn();	// Requires one never uses column 0

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
		m_List1.InsertColumnTrait(col+1, CString(title.c_str()), LVCFMT_LEFT, 100, col, pTrait);
	}

	// Insert data into list-control by copying from datamodel
	int nItem = 0;
	for(size_t rowId = 0; rowId < m_DataModel.GetRowIds() ; ++rowId)
	{
		nItem = m_List1.InsertItem(++nItem, CString(m_DataModel.GetCellText(rowId, 0).c_str()));
		m_List1.SetItemData(nItem, rowId);
		for(int col = 0; col < m_DataModel.GetColCount() ; ++col)
		{
			m_List1.SetItemText(nItem, col+1, CString(m_DataModel.GetCellText(rowId, col).c_str()));
		}
	}*/


	// TODO: Add your specialized code here and/or call the base class
//	GetParentFrame()->SetWindowText("实时显示");
	SetMonitorListHead();

	// Assign images to the list-control
//	m_List1.SetCellImage(0, 2, 0);
//	m_List1.SetCellImage(1, 2, 0);
//	m_List1.SetCellImage(2, 2, 0);
//	m_List1.SetCellImage(3, 2, 1);

//	CGridColumnManagerProfile* pColumnProfile = new CGridColumnManagerProfile(_T("Sample List"));
//	pColumnProfile->AddColumnProfile(_T("Default"));
//	pColumnProfile->AddColumnProfile(_T("Special"));
//	m_List1.SetupColumnConfig(pColumnProfile);

	SetInfo();
}

void CSampleFormView::SetInfo() 
{
	if(n_cF == 50)
		return;
	m_vl1.clear();
	m_vl2.clear();
	m_vl3.clear();
    	CString  strf,strc;
      	CString strrsy ,strclm,strrsy1,strclm1,strSQL;
		int n_isdata =0;
		int n_ismore =0;
     	strrsy = gstrTimeOut + "\\" + strMetrics+ "rsy\\";
     	strrsy1 ="dispoint"+strMetrics;
		CppSQLite3Query q;

		for(int i=1;i<4;i++)
		{
	        for(int k=0;k<100;k++)
         		  m_strl1[k].strl= "";
    		if(i ==1)
        		strSQL.Format("select * from '%s' WHERE DISID>500 and DISID<600;",strrsy1);
	    	else if(i ==2)
        		strSQL.Format("select * from '%s' WHERE DISID>600 and DISID<700;",strrsy1);
	    	else if(i ==3)
        		strSQL.Format("select * from '%s' WHERE DISID>700 and DISID<800;",strrsy1);
            q = theApp.db3.execQuery(strSQL);
            while (!q.eof()) 
			{
	    		n_isdata = q.getIntField(0);
	    		strclm = q.getStringField(n_cF+1);
	    		strclm.TrimRight();
	    		if(strclm != "")
				{
					int oacd ;
                	oacd =strclm.Find(_T("C"));
            		strf = strclm.Mid(0,2);
            		strc = strclm.Mid(3,2);
            		int nfds = m_Str2Data.String2Int(strf);
            		int nchan = m_Str2Data.String2Int(strc);
					if(oacd != -1)
						nchan =16+nchan;
                	strc = m_SlaveStation[nfds][nchan].WatchName;
            		int mptype =m_SlaveStation[nfds][nchan].ptype;
					if(mptype <3)
                		oacd =strclm.Find(_T("A"));
					else if(mptype == 11)
                		oacd =strclm.Find(_T("F"));
					else if(mptype == 12)
                		oacd =strclm.Find(_T("C"));
					else
                		oacd =strclm.Find(_T("D"));
			    	if(strc != "" && oacd != -1)
					{
                 		if(i ==1)
		        			m_strl1[n_isdata-501].strl=m_SlaveStation[nfds][nchan].strPN;
                 		else if(i ==2)
		      	    		m_strl1[n_isdata-601].strl=m_SlaveStation[nfds][nchan].strPN;
            	    	else if(i ==3)
			        		m_strl1[n_isdata-701].strl=m_SlaveStation[nfds][nchan].strPN;
					}
		    		else
		    			n_ismore = 100;
				}
                q.nextRow();
			}
                if(i ==1)
				{
                    for(int k=0;k<100;k++)
					{
						strclm = m_strl1[k].strl;
						if( strclm != "")
							m_vl1.push_back(strclm);
					}
				}
           		else if(i ==2)
				{
                    for(int k=0;k<100;k++)
					{
						strclm = m_strl1[k].strl;
						if( strclm != "")
							m_vl2.push_back(strclm);
					}
				}
       	    	else if(i ==3)
				{
                    for(int k=0;k<100;k++)
					{
						strclm = m_strl1[k].strl;
						if( strclm != "")
							m_vl3.push_back(strclm);
					}
				}

			if(n_ismore == 100)
			{
        		strclm.Format("LP%d",n_cF);
        		if(i ==1)
				{
                    for(int nItem=0;nItem<m_vl1.size();nItem++)
					{
                	    	strSQL.Format("UPDATE '%s' SET '%s'='%s' WHERE DISID =%d;",
			    	         strrsy1,strclm,m_vl1[nItem],nItem+501);
			    	    	q = theApp.db3.execQuery(strSQL);
					}
                    for( nItem=m_vl1.size();nItem<100;nItem++)
					{
                	    	strSQL.Format("UPDATE '%s' SET '%s'='' WHERE DISID =%d;",
			    	         strrsy1,strclm,nItem+501);
			    	    	q = theApp.db3.execQuery(strSQL);
					}
				}
        		else if(i ==2)
				{
                    for(int nItem=0;nItem<m_vl2.size();nItem++)
					{
                	    	strSQL.Format("UPDATE '%s' SET '%s'='%s' WHERE DISID =%d;",
			    	         strrsy1,strclm,m_vl2[nItem],nItem+601);
			    	    	q = theApp.db3.execQuery(strSQL);
					}
                    for( nItem=m_vl2.size();nItem<100;nItem++)
					{
                	    	strSQL.Format("UPDATE '%s' SET '%s'='' WHERE DISID =%d;",
			    	         strrsy1,strclm,nItem+601);
			    	    	q = theApp.db3.execQuery(strSQL);
					}
				}
        		else if(i ==3)
				{
                    for(int nItem=0;nItem<m_vl3.size();nItem++)
					{
                	    	strSQL.Format("UPDATE '%s' SET '%s'='%s' WHERE DISID =%d;",
			    	         strrsy1,strclm,m_vl3[nItem],nItem+701);
			    	    	q = theApp.db3.execQuery(strSQL);
					}
                    for( nItem=m_vl3.size();nItem<100;nItem++)
					{
                	    	strSQL.Format("UPDATE '%s' SET '%s'='' WHERE DISID =%d;",
			    	         strrsy1,strclm,nItem+701);
			    	    	q = theApp.db3.execQuery(strSQL);
					}
				}
			}//n_ismore == 100
		}
   		q.finalize();

//	m_List1.SetCellImage(3, 1, 1);
//	m_List1.GetWindowText(pString);
	BuildList(1, n_cF);
	BuildList(2, n_cF);
	BuildList(3, n_cF);

	SortColumn(m_nSortedCol, m_bAscending ,1);
	SortColumn(m_nSortedCol2, m_bAscending2 ,2);
	SortColumn(m_nSortedCol3, m_bAscending3 ,3);
}

void CSampleFormView::SetMonitorListHead()
{
	CString pString,strpo;
	pString =GetDocument()->GetTitle();
       		int m_ishave = pString.GetLength();
    		strpo = pString.Mid(m_ishave-3,3);
	if(strpo != "rsf")
	    pString += ".rsf";
	for(int i=0 ;i<20; i++ )
	{
		if(m_CommonStr[i].strc[0] == pString)//找到位置，唯一标示
		{
           	n_cF =i;
			break;
		}
	}
	if(n_cF == 50)
		return;
	
//	m_List1.SetWindowPos(NULL,0,0,GetSystemMetrics(SM_CXSCREEN)-8,140,SWP_NOMOVE|SWP_NOZORDER | SWP_NOACTIVATE|SWP_SHOWWINDOW);
//	CListCtrl* ctext2;
//    ctext2 = (CListCtrl*)GetDlgItem(IDC_LIST_POINT1);//get the pointer
	int	n_cur = m_Str2Data.String2Int(m_CommonStr[n_cF].strc[3]);
    RECT rect2 = {n_cur, 0, 0, 0};
	m_List1.MoveWindow(&rect2);//Move window 
	n_cur = m_Str2Data.String2Int(m_CommonStr[n_cF].strc[4]);
	int	n_cury = m_Str2Data.String2Int(m_CommonStr[n_cF].strc[5]);
	m_List1.SetWindowPos(NULL,0,0,n_cur,n_cury,SWP_NOMOVE);//|SWP_NOZORDER | SWP_NOACTIVATE

	n_cur = m_Str2Data.String2Int(m_CommonStr[n_cF].strc[6]);
	n_cury = m_Str2Data.String2Int(m_CommonStr[n_cF].strc[7]);
	int	n_curz = m_Str2Data.String2Int(m_CommonStr[n_cF].strc[8]);
	for (int iItem = 20; iItem > -1; iItem--)
	{
         	m_List1.DeleteColumn(iItem);
         	m_List2.DeleteColumn(iItem);
         	m_List3.DeleteColumn(iItem);
	}
		m_List1.InsertColumn(0,"安装地点/名称",LVCFMT_LEFT,n_cur);
		m_List1.InsertColumn(1,"检测值",LVCFMT_LEFT,n_cury);
		m_List1.InsertColumn(2,"点号",LVCFMT_LEFT,n_curz);
		SetLHeadEXT(1);
//		m_List1.SetImageList(&m_SampleFormView, TVSIL_NORMAL);
//获得原有风格
     DWORD dwStyle = ::GetWindowLong(m_List1.m_hWnd, GWL_STYLE);
//dwStyle &= ~(LVS_TYPEMASK);
//dwStyle &= ~(LVS_EDITLABELS);
	 if(m_CommonStr[n_cF].strc[1]== "0")  //不可见
          dwStyle &= ~(WS_VISIBLE);
//dwStyle |=  LVS_EX_SUBITEMIMAGES;
//设置新风格
     SetWindowLong(m_List1.m_hWnd, GWL_STYLE,dwStyle );
//SetWindowLong(m_List1.m_hWnd, GWL_STYLE,dwStyle |LVS_REPORT | LVS_NOLABELWRAP | LVS_SHOWSELALWAYS);
// 设置扩展风格
//DWORD styles = LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_CHECKBOXES;
//ListView_SetExtendedListViewStyleEx(m_List1.m_hWnd, styles, styles );
//其中 LVS_EX_FULLROWSELECT　就是前面说得整行选中
//LVS_EX_GRIDLINES　网格线（只适用与report风格的listctrl）
//LVS_EX_CHECKBOXES 　前面加个checkbox

		//	((CComboBox *)GetDlgItem(IDC_COMBO1))->SetCurSel(0);
	n_cur = m_Str2Data.String2Int(m_CommonStr[n_cF].strc[33]);
    RECT rect = {n_cur, 0, 0, 0};
	m_List2.MoveWindow(&rect);//Move window 
	n_cur = m_Str2Data.String2Int(m_CommonStr[n_cF].strc[34]);
	n_cury = m_Str2Data.String2Int(m_CommonStr[n_cF].strc[35]);
	m_List2.SetWindowPos(this,0,0,n_cur,n_cury,SWP_NOMOVE|SWP_NOZORDER | SWP_NOACTIVATE);
//	m_List2.SetExtendedStyle(LVS_EX_ONECLICKACTIVATE);
	n_cur = m_Str2Data.String2Int(m_CommonStr[n_cF].strc[36]);
	n_cury = m_Str2Data.String2Int(m_CommonStr[n_cF].strc[37]);
	n_curz = m_Str2Data.String2Int(m_CommonStr[n_cF].strc[38]);
		m_List2.InsertColumn(0,"安装地点/名称",LVCFMT_LEFT,n_cur);
		m_List2.InsertColumn(1,"检测值",LVCFMT_LEFT,n_cury);
		m_List2.InsertColumn(2,"点号",LVCFMT_LEFT,n_curz);
		SetLHeadEXT(2);

     dwStyle = ::GetWindowLong(m_List2.m_hWnd, GWL_STYLE);
	 if(m_CommonStr[n_cF].strc[31]== "0")//不可见
          dwStyle &= ~(WS_VISIBLE);
     SetWindowLong(m_List2.m_hWnd, GWL_STYLE,dwStyle );

	n_cur = m_Str2Data.String2Int(m_CommonStr[n_cF].strc[63]);
    RECT rect1 = {n_cur, 0, 0, 0};
	m_List3.MoveWindow(&rect1);//Move window 
	n_cur = m_Str2Data.String2Int(m_CommonStr[n_cF].strc[64]);
	n_cury = m_Str2Data.String2Int(m_CommonStr[n_cF].strc[65]);
	m_List3.SetWindowPos(this,0,0,n_cur,n_cury,SWP_NOMOVE|SWP_NOZORDER | SWP_NOACTIVATE);
//	m_List3.SetExtendedStyle(LVS_EX_TWOCLICKACTIVATE);
	n_cur = m_Str2Data.String2Int(m_CommonStr[n_cF].strc[66]);
	n_cury = m_Str2Data.String2Int(m_CommonStr[n_cF].strc[67]);
	n_curz = m_Str2Data.String2Int(m_CommonStr[n_cF].strc[68]);
		m_List3.InsertColumn(0,"安装地点/名称",LVCFMT_LEFT,n_cur);
		m_List3.InsertColumn(1,"检测值",LVCFMT_LEFT,n_cury);
		m_List3.InsertColumn(2,"点号",LVCFMT_LEFT,n_curz);
//		m_List3.InsertColumn(3,m_FormView[theApp.DocNum].m_ListCtrl[2].ColumnHeading3,LVCFMT_LEFT,m_FormView[theApp.DocNum].m_ListCtrl[2].ColumnWidth3);
		SetLHeadEXT(3);

     dwStyle = ::GetWindowLong(m_List3.m_hWnd, GWL_STYLE);
	 if(m_CommonStr[n_cF].strc[61]== "0")
          dwStyle &= ~(WS_VISIBLE);
     SetWindowLong(m_List3.m_hWnd, GWL_STYLE,dwStyle );

//	n_cur = m_Str2Data.String2Int(m_CommonStr[n_cF].strc[2]);
//	n_cury = m_Str2Data.String2Int(m_CommonStr[n_cF].strc[12]);
//	n_curz = m_Str2Data.String2Int(m_CommonStr[n_cF].strc[22]);
	 //列表头右键菜单
//	m_List1.SubclassHeader(FALSE);

//		strtemp.Format("□%d",iItem); //◎◎··●●□□◇   //**change subscript
//	CXTFlatHeaderCtrl* pHeaderCtrl1 = m_List3.GetFlatHeaderCtrl( );
//	if ( pHeaderCtrl1 != NULL )
	{
//		pHeaderCtrl1->EnableAutoSize();
//    	pHeaderCtrl1->SetBitmap(0, IDB_COLUMN_0, FALSE, RGB(0,255,0));
//    	pHeaderCtrl1->SetBitmap(1, IDB_COLUMN_1, FALSE, RGB(0,255,0));
//		pHeaderCtrl1->SetBitmap(2, IDB_COLUMN_2, FALSE, RGB(0,255,0));
	}

	// Get the windows handle to the header control for the
	// list control then subclass the control.
/*	HWND hWndHeader = m_List1.GetDlgItem(IDC_LIST_POINT1)->GetSafeHwnd();
//	m_flatHeader.SubclassWindow (hWndHeader);
	m_flatHeader = m_List1.GetFlatHeaderCtrl();
	OnSelendokComboThemes();
	 hWndHeader = m_List2.GetDlgItem(IDC_LIST_POINT2)->GetSafeHwnd();
	m_flatHeader = m_List2.GetFlatHeaderCtrl();
	OnSelendokComboThemes();
	 hWndHeader = m_List3.GetDlgItem(IDC_LIST_POINT3)->GetSafeHwnd();
	m_flatHeader = m_List3.GetFlatHeaderCtrl();
	OnSelendokComboThemes();*/

	// add bitmap images.
//	m_flatHeader->SetBitmap(0, IDB_COLUMN_0, FALSE, RGB(0,255,0));
//	m_flatHeader->SetBitmap(1, IDB_COLUMN_1, FALSE, RGB(0,255,0));
//	m_flatHeader->SetBitmap(2, IDB_COLUMN_2, FALSE, RGB(0,255,0));
//	m_flatHeader->InitializeHeader(TRUE);	
//	if (m_bSaveColumnWidth)
//		m_ctrlListMonitor.LoadColumnWidths();


	HWND hWndHeader = m_List1.GetDlgItem(IDC_LIST_POINT1)->GetSafeHwnd();
//	m_flatHeader = m_List1.GetFlatHeaderCtrl();
	m_flatHeader.SubclassWindow(hWndHeader);
	HWND hWndHeader2 = m_List2.GetDlgItem(IDC_LIST_POINT2)->GetSafeHwnd();
	m_flatHeader2.SubclassWindow(hWndHeader2);
	HWND hWndHeader3 = m_List3.GetDlgItem(IDC_LIST_POINT3)->GetSafeHwnd();
	m_flatHeader3.SubclassWindow(hWndHeader3);
	// enable auto sizing.
//	m_flatHeader->EnableAutoSize(TRUE);
//	m_flatHeader->ResizeColumnsToFit();

	// size to fit the columns
//	m_List1.AutoSizeColumn ();

	// initialize the back color picker default colors.
//	int red = 255;
//	int green = 255;
//	int blue = 255;
//	COLORREF RowBackcolor = RGB(red,green,blue);
//	m_cpBack.SetColor(m_FormView[theApp.DocNum].m_ListCtrl[0].BackColor);
//	m_cpBack.SetDefaultColor(RowBackcolor);

	// initialize the text color picker default colors.
//	m_cpText.SetColor(m_FormView[theApp.DocNum].m_ListCtrl[0].TextColor);
//	m_cpText.SetDefaultColor(m_clrRowText);

	// set the text and back colors for the list control.
//	m_List1.SetRowColors(m_cpText.GetColor(), m_cpBack.GetColor());

	// set some extnded styles
//	m_List1.SetExtendedStyle (LVS_EX_FULLROWSELECT|LVS_EX_FLATSB);
	m_List1.SetExtendedStyle (LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_List2.SetExtendedStyle (LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES|LVS_EX_FLATSB);
	m_List3.SetExtendedStyle (LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES|LVS_EX_FLATSB);

//	m_List1.ModifyExtendedStyle(0, LVS_EX_FULLROWSELECT);
//	m_List1.EnableUserSortColor(true);
	m_List1.EnableUserListColor(true);
	m_List2.EnableUserListColor(true);
	m_List3.EnableUserListColor(true);
	m_List1.EnableUserRowColor(true);
	m_List2.EnableUserRowColor(true);
	m_List3.EnableUserRowColor(true);

//	OnSelendokComboThemes();
	m_List1.SetListBackColor(m_Str2Data.String2Int(m_CommonStr[n_cF].strc[9]));
	m_List2.SetListBackColor(m_Str2Data.String2Int(m_CommonStr[n_cF].strc[39]));
	m_List3.SetListBackColor(m_Str2Data.String2Int(m_CommonStr[n_cF].strc[69]));

//行数
/*	n_cur = m_Str2Data.String2Int(m_CommonStr[n_cF].strc[9]);
	n_cury = m_Str2Data.String2Int(m_CommonStr[n_cF].strc[19]);
	n_curz = m_Str2Data.String2Int(m_CommonStr[n_cF].strc[29]);
	CString strItem = _T("");
	for (int iItem = 0; iItem < n_cur; ++iItem)
	{
		m_List1.InsertItem(iItem, strItem, 0);
//        m_List1.SetRowColor(iItem, RGB(255,0,0), RGB(255,255,255));
	}
	for (iItem = 0; iItem < n_cury; ++iItem)
		m_List2.InsertItem(iItem, strItem, 0);
	for (iItem = 0; iItem < n_curz; ++iItem)
		m_List3.InsertItem(iItem, strItem, 0);*/
}

void CSampleFormView::SetLHeadEXT(int mlist)
{
		CString strl[35];
//		strl[0] = "是否可见(1可见|0隐藏)";		strl[1] = "子类头控制(1或0)";
//		strl[2] = "列表左上顶点x坐标";
		strl[3] = "最大值";		strl[4] = "最小值";		strl[5] = "平均值";
		strl[6] = "断电值";		strl[7] = "复电值";		strl[8] = "报警上限";
		strl[9] = "报警下限";		strl[10] = "量程高值";		strl[11] = "量程低值";
		strl[12] = "断电时刻";		strl[13] = "复电时刻";		strl[14] = "报警时刻";
		strl[15] = "馈电状态及时刻";		strl[16] = "断电范围";		strl[17] = "开停次数";	
		strl[18] = "工作时间";
		int k=3;
       	for (int i = 3; i < 19; i++)
		{
			if(m_CommonStr[n_cF].strc[90+20*(mlist-1)+(i-3)] == "1")
			{
				if(mlist ==1)
        	    	m_List1.InsertColumn(k,strl[i],LVCFMT_LEFT,m_Str2Data.String2Int(m_CommonStr[n_cF].strc[10+30*(mlist-1)+(i-3)]));
				else if(mlist ==2)
        	    	m_List2.InsertColumn(k,strl[i],LVCFMT_LEFT,m_Str2Data.String2Int(m_CommonStr[n_cF].strc[10+30*(mlist-1)+(i-3)]));
				else if(mlist ==3)
        	    	m_List3.InsertColumn(k,strl[i],LVCFMT_LEFT,m_Str2Data.String2Int(m_CommonStr[n_cF].strc[10+30*(mlist-1)+(i-3)]));
				k++;
			}
		}
}

void CSampleFormView::OnSelendokComboThemes()
{
	UpdateData();

	switch (m_iTheme)
	{
/*	case 0:
		m_bHotTracking = FALSE;
		m_bWinTheme = FALSE;
		m_flatHeader->SetTheme(new CXTHeaderCtrlThemeOfficeXP());
		CXTPPaintManager::SetTheme(xtpThemeOfficeXP);
		break;
	case 1:
		m_bHotTracking = FALSE;
		m_bWinTheme = FALSE;
		m_flatHeader->SetTheme(new CXTHeaderCtrlThemeOffice2003());
		CXTPPaintManager::SetTheme(xtpThemeOffice2003);
		break;
	case 2:
		m_bHotTracking = TRUE;
		m_bWinTheme = TRUE;
		m_flatHeader->SetTheme(new CXTHeaderCtrlThemeExplorer());
		CXTPPaintManager::SetTheme(xtpThemeOffice2000);
		break;
	case 3:
		m_bHotTracking = TRUE;
		m_bWinTheme = TRUE;
		m_flatHeader->SetTheme(new CXTHeaderCtrlTheme());
		CXTPPaintManager::SetTheme(xtpThemeOffice2000);
		break;*/
	}

	UpdateData(FALSE);

	DWORD dwStyle = 0L;
	if (m_bWinTheme && m_iTheme >= 2)
		dwStyle |= XTTHEME_WINXPTHEMES;

	if (m_bWinTheme && m_iTheme >= 2 && m_bHotTracking)
		dwStyle |= XTTHEME_HOTTRACKING;

	if (m_bSortArrow)
		dwStyle |= XTTHEME_SORTARROW;

//	CXTHeaderCtrlTheme* pTheme = m_flatHeader->GetTheme();
//	if (pTheme)
	{
//		pTheme->SetDrawStyle(dwStyle, m_flatHeader);
//		EnableControls();
	}
}

void CSampleFormView::SortColumn(int iCol, bool bAsc ,int mlist)
{
	// set sort image for header and sort column.
//	m_List1.SetSortImage(m_nSortedCol, m_bAscending);

	if(mlist == 1)
	{
     	m_bAscending = bAsc;
       	m_nSortedCol = iCol;
		if(m_nSortedCol != 1)
		{
        	CXTSortClass csc(&m_List1, m_nSortedCol);
        	csc.Sort(m_bAscending, xtSortString);
		}
	}
	else if(mlist == 2)
	{
     	m_bAscending2 = bAsc;
       	m_nSortedCol2 = iCol;
		if(m_nSortedCol2 != 1)
		{
        	CXTSortClass csc(&m_List2, m_nSortedCol2);
        	csc.Sort(m_bAscending2, xtSortString);
		}
	}
	else if(mlist == 3)
	{
     	m_bAscending3 = bAsc;
       	m_nSortedCol3 = iCol;
		if(m_nSortedCol3 != 1)
		{
        	CXTSortClass csc(&m_List3, m_nSortedCol3);
        	csc.Sort(m_bAscending3, xtSortString);
		}
	}
}
/*
BOOL CSampleFormView::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	HD_NOTIFY *pHDNotify = (HD_NOTIFY*)lParam;

	if (pHDNotify->hdr.code == HDN_ITEMCLICKA ||
		pHDNotify->hdr.code == HDN_ITEMCLICKW)
	{
		if(nlist ==1)
		{
    		if (pHDNotify->iItem == m_nSortedCol)
		    	SortColumn(pHDNotify->iItem, !m_bAscending,1);
    		else
		    	SortColumn(pHDNotify->iItem, BoolType(m_flatHeader.GetAscending()),1);
		}
		else if(nlist ==2)
		{
    		if (pHDNotify->iItem == m_nSortedCol2)
		    	SortColumn(pHDNotify->iItem, !m_bAscending2,2);
    		else
		    	SortColumn(pHDNotify->iItem, BoolType(m_flatHeader2.GetAscending()),2);
		}
		else if(nlist ==3)
		{
    		if (pHDNotify->iItem == m_nSortedCol3)
		    	SortColumn(pHDNotify->iItem, !m_bAscending3,3);
    		else
		    	SortColumn(pHDNotify->iItem, BoolType(m_flatHeader3.GetAscending()),3);
		}
	}

	return CFormView::OnNotify(wParam, lParam, pResult);
}
*/
void CSampleFormView::EnableControls(BOOL bRedraw/*=TRUE*/)
{
//	m_editMinSize.EnableWindow(m_bMinSize);
//	m_comboDisableSize.EnableWindow(m_bDisableSizing);
//	m_btnWinTheme.EnableWindow(XTOSVersionInfo()->IsWinXPOrGreater());
//	m_btnHotTracking.EnableWindow(XTOSVersionInfo()->IsWinXPOrGreater() && m_bWinTheme);
//	m_cpSortBack.EnableWindow(m_bSortColor);
//	m_cpSortText.EnableWindow(m_bSortColor);
//	m_cpRowBack.EnableWindow(m_bRowColor);
//	m_cpRowText.EnableWindow(m_bRowColor);
//	m_cpListBack.EnableWindow(m_bListColor);
//	m_cpListText.EnableWindow(m_bListColor);
	if (bRedraw)
	{
		RedrawWindow(NULL, NULL,
			RDW_INVALIDATE|RDW_UPDATENOW|RDW_ERASE|RDW_ALLCHILDREN);
	}
}
/*
CScrollBar* CSampleFormView::GetScrollBarCtrl(int nBar) const
{
    if (nBar == SB_HORZ)
    {
        return (CScrollBar *)&m_ScrollBarH;
    }
	
	return CFormView::GetScrollBarCtrl(nBar);
}

int CSampleFormView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CFormView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
    m_ScrollBarH.Create(WS_CHILD, CRect(0, 0, 0, 0), this, 0);

	return 0;
}

BOOL CSampleFormView::OnEraseBkgnd(CDC* pDC) 
{
	UNREFERENCED_PARAMETER(pDC);	
	return TRUE;
}

void CSampleFormView::OnPaint() 
{
	CPaintDC dc(this);
	
	// Get the client rect, and paint to a memory device context.  This will 
	// help reduce screen flicker. Pass the memory device context to the
	// default window proceedure do default painting.
	
	CRect r;
	GetClientRect(&r);
	CXTMemDC memDC(&dc, r);
	
	CFormView::DefWindowProc( WM_PAINT, (WPARAM)memDC.m_hDC, 0 );
}
*/

void CSampleFormView::OnRclick1(NMHDR* pNMHDR, LRESULT* pResult)
{
//	CListCtrl &CList =  GetListCtrl();//获取当前列表控件的指针
    CPoint point;//定义一个用于确定光标位置的位置
    GetCursorPos( &point);//获取当前光标的位置，以便使得菜单可以跟随光标
		CMenu menu;
   	nlistaj = 1;
     LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	 m_Itemnum = pNMLV->iItem;
	 strItem=m_List1.GetItemText(m_Itemnum,2);    //3
	 if(strItem =="")
	 {
		if (menu.LoadMenu(IDC_POPLISTCONTROL))
		{
			CMenu* pPopup = menu.GetSubMenu(0);
			ASSERT(pPopup != NULL);
			int nResult = pPopup->TrackPopupMenu(TPM_RIGHTBUTTON | TPM_LEFTALIGN,
								   point.x, point.y,
								   AfxGetMainWnd()); // route commands through main window
		}
	 }
	 else
	 {
		 strCli = strItem;
		if (menu.LoadMenu(IDC_POPPOINT))
		{
			CMenu* pPopup = menu.GetSubMenu(0);
			ASSERT(pPopup != NULL);
			int nResult = pPopup->TrackPopupMenu(TPM_RIGHTBUTTON | TPM_LEFTALIGN,
								   point.x, point.y,
								   AfxGetMainWnd()); // route commands through main window
		}
	 }
     *pResult = 0;
/*       CMenu       menu ,* pSubMenu;//定义下面要用到的cmenu对象
       menu.LoadMenu(IDC_POPLISTCONTROL);//装载自定义的右键菜单
       pSubMenu = menu.GetSubMenu(0);//获取第一个弹出菜单，所以第一个菜单必须有子菜单
    CPoint oPoint;//定义一个用于确定光标位置的位置
    GetCursorPos( &oPoint);//获取当前光标的位置，以便使得菜单可以跟随光标
//       int istat;//=CList.GetSelectionMark();//用istat存放当前选定的是第几项
//    CString pString; //=CList.GetItemText(istat,0);//获取当前项中的数据，0代表是第0列
//	pString="您选择的路径是:"+pString ;//显示当前选择项
       MessageBox(pString);//显示当前选中的路径
//       pSubMenu->TrackPopupMenu (TPM_LEFTALIGN, oPoint.x, oPoint.y, this); //在指定位置显示弹出菜单
	// Will return zero if no selection was made (TPM_RETURNCMD)
	int nResult = pSubMenu->TrackPopupMenu (TPM_LEFTALIGN, oPoint.x, oPoint.y, this); //在指定位置显示弹出菜单
	switch(nResult)
	{
		case 0: break;
		case 1:	OpenAddDel(1, m_Str2Data.String2Int(pString)); break;
		case 2: Openadjust(1, m_Str2Data.String2Int(pString)); break;
//		case 3: m_pColumnManager->ResetColumnsDefault(*this); break;
		default: break;
	}*/
//        pString.Format("%d",n_curFormnum);
//        AfxMessageBox(pString);
}
void CSampleFormView::OnRclick2(NMHDR* pNMHDR, LRESULT* pResult)
{
    CPoint point;//定义一个用于确定光标位置的位置
    GetCursorPos( &point);//获取当前光标的位置，以便使得菜单可以跟随光标
		CMenu menu;
	nlistaj = 2;
     LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	 m_Itemnum = pNMLV->iItem;
	 strItem=m_List2.GetItemText(m_Itemnum,2);
	 if(strItem =="")
	 {
		if (menu.LoadMenu(IDC_POPLISTCONTROL))
		{
			CMenu* pPopup = menu.GetSubMenu(0);
			ASSERT(pPopup != NULL);
			int nResult = pPopup->TrackPopupMenu(TPM_RIGHTBUTTON | TPM_LEFTALIGN,
								   point.x, point.y,
								   AfxGetMainWnd()); // route commands through main window
		}
	 }
	 else
	 {
		 strCli = strItem;
		if (menu.LoadMenu(IDC_POPPOINT))
		{
			CMenu* pPopup = menu.GetSubMenu(0);
			ASSERT(pPopup != NULL);
			int nResult = pPopup->TrackPopupMenu(TPM_RIGHTBUTTON | TPM_LEFTALIGN,
								   point.x, point.y,
								   AfxGetMainWnd()); // route commands through main window
		}
	 }
     *pResult = 0;
}

void CSampleFormView::OnRclick3(NMHDR* pNMHDR, LRESULT* pResult)
{
    CPoint point;//定义一个用于确定光标位置的位置
    GetCursorPos( &point);//获取当前光标的位置，以便使得菜单可以跟随光标
//	theApp.idis = m_Str2Data.String2Int(pString);
		CMenu menu;
	nlistaj = 3;
     LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	 m_Itemnum = pNMLV->iItem;
	 strItem=m_List3.GetItemText(m_Itemnum,2);
	 if(strItem =="")
	 {
		if (menu.LoadMenu(IDC_POPLISTCONTROL))
		{
			CMenu* pPopup = menu.GetSubMenu(0);
			ASSERT(pPopup != NULL);
			int nResult = pPopup->TrackPopupMenu(TPM_RIGHTBUTTON | TPM_LEFTALIGN,
								   point.x, point.y,
								   AfxGetMainWnd()); // route commands through main window
		}
	 }
	 else
	 {
		 strCli = strItem;
		if (menu.LoadMenu(IDC_POPPOINT))
		{
			CMenu* pPopup = menu.GetSubMenu(0);
			ASSERT(pPopup != NULL);
			int nResult = pPopup->TrackPopupMenu(TPM_RIGHTBUTTON | TPM_LEFTALIGN,
								   point.x, point.y,
								   AfxGetMainWnd()); // route commands through main window
		}
	 }
     *pResult = 0;
}
//选择显示测点
void CSampleFormView::OpenAddDel() 
{
	if(n_cF == 50)
	{
        AfxMessageBox("列表没有定义，请点击菜单:{页面编辑}项下{列表}！");
		return;
	}
	CSettingHostDlg dlg;
	dlg.m_strtable =  _T("dispoint");
	dlg.PointDesid = n_cF;
	dlg.nlist = nlistaj;
//	dlg.PointDesid = ilistaj;
	if(dlg.DoModal() == IDOK)
	{
		theApp.InitData();
		BuildList(nlistaj, n_cF);
    	SortColumn(m_nSortedCol, m_bAscending ,nlistaj);
	}
}

void CSampleFormView::OpenDayRT() 
{
	CString strf,strc;
//	int n ;;
		    strf = strItem.Mid(0,2);
    		strc = strItem.Mid(3,2);
		int nfds = m_Str2Data.String2Int(strf);
//		int nchan = m_Str2Data.String2Int(strc);
	if(nfds == 0)
	{
        AfxMessageBox("请选择测点！");
		return;
	}
	CDCH5m dlg;
	dlg.n_select =4;
	dlg.strPOINT = strItem;
	dlg.DoModal();
}

void CSampleFormView::OpenRTChart() 
{
	CString strf,strc;
		    strf = strItem.Mid(0,2);
    		strc = strItem.Mid(3,2);
		int nfds = m_Str2Data.String2Int(strf);
		int nchan = m_Str2Data.String2Int(strc);
	if(nfds == 0)
	{
        AfxMessageBox("请选择测点！");
		return;
	}
	int ptype =m_SlaveStation[nfds][nchan].ptype;
	if(ptype >3)
	{
        AfxMessageBox("请选择模拟量！");
		return;
	}

	theApp.m_message = m_SlaveStation[nfds][nchan].m_PID;

	strc = gstrTimeOut + "\\" + strMetrics+ "rsy\\实时曲线.rsy";
		CDrawView *pView;
		m_ViewPos = theApp.m_map.GetStartPosition() ;     //0415
		for(int i = 0; i < 50;i++ )
		{
    	   	if(m_ViewPos != NULL)
			{
         	    theApp.m_map.GetNextAssoc(m_ViewPos,strf,pView);
				if(strc == strf)
				{
		    		nfds = 0;
			        pView->GetParentFrame()->ActivateFrame();
					break;
				}
			}
			else
			{
				nfds = 66;
				break;
			}
		}
		if(nfds == 66)
		{
    		theApp.pDocTemplate->OpenDocumentFile(strc) ;
			theApp.m_addfilesy.push_back(strc);
		}
}

void CSampleFormView::Openadjust() 
{
	CString strf,strc;
	int n =strItem.Find("A");
	if(n == -1)
	{
        AfxMessageBox("请选择模拟量");
		return;
	}
		    strf = strItem.Mid(0,2);
    		strc = strItem.Mid(3,2);
		int nfds = m_Str2Data.String2Int(strf);
		int nchan = m_Str2Data.String2Int(strc);
	n = m_SlaveStation[nfds][nchan].Adjust_state;
	if(n == 1)
	{
        AfxMessageBox("已经设为标校！");
		return;
	}
	m_SlaveStation[nfds][nchan].Adjust_state =1;
	m_SlaveStation[nfds][nchan].strPN += "标校";

	for(int i=0 ; i<65 ;i++)
	{
		int cfds = m_ADCbreakE[nfds][nchan][i].bFSd;
		int cchan = m_ADCbreakE[nfds][nchan][i].bchanel;
		if(cfds == 0)
			break;
		//关联的开关量
     	m_SlaveStation[cfds][cchan+16].Adjust_state =1;
    	for(int j=0 ; j<65 ;j++)
		{
    		int ffds = m_CFeed[cfds][cchan][j].bFSd;
	    	int fchan = m_CFeed[cfds][cchan][j].bchanel;
	      	if(ffds == 0)
		     	break;
			//关联的馈电量
         	m_SlaveStation[ffds][fchan].Adjust_state =1;
		}
	}
	theApp.InitDisplay();

	strItem += "标校";
//	m_DisplayPoint[ilistaj][m_Itemnum].CPpointnum =strItem;
/*    	if(nlistaj == 3)
        	m_List3.SetItemText(m_Itemnum, 2, strItem); //3
     	else if(nlistaj == 2)
        	m_List2.SetItemText(m_Itemnum, 2, strItem);
       	else if(nlistaj == 1)
         	m_List1.SetItemText(m_Itemnum, 2, strItem);
*/
      g_Log.StatusOut(strItem);
}

void CSampleFormView::Deladjust() 
{
	CString strf,strc;
	int n =strItem.Find("A");
	if(n == -1)
	{
        AfxMessageBox("请选择模拟量");
		return;
	}
		    strf = strItem.Mid(0,2);
    		strc = strItem.Mid(n+1);
		int nfds = m_Str2Data.String2Int(strf);
		int nchan = m_Str2Data.String2Int(strc);
	n = m_SlaveStation[nfds][nchan].Adjust_state;
	if(n == 0)
	{
        AfxMessageBox("标校已经取消！");
		return;
	}
	m_SlaveStation[nfds][nchan].Adjust_state =0;
	m_SlaveStation[nfds][nchan].strPN = m_SlaveStation[nfds][nchan].strPN.Mid(0,5);

	for(int i=0 ; i<65 ;i++)
	{
		int cfds = m_ADCbreakE[nfds][nchan][i].bFSd;
		int cchan = m_ADCbreakE[nfds][nchan][i].bchanel;
		if(cfds == 0)
			break;
     	m_SlaveStation[cfds][cchan+16].Adjust_state =0;
    	for(int j=0 ; j<65 ;j++)
		{
    		int ffds = m_CFeed[cfds][cchan][j].bFSd;
	    	int fchan = m_CFeed[cfds][cchan][j].bchanel;
	      	if(ffds == 0)
		     	break;
         	m_SlaveStation[ffds][fchan].Adjust_state =0;
		}
	}
	theApp.InitDisplay();
	strItem = strItem.Mid(0,5);
//	m_DisplayPoint[ilistaj][m_Itemnum].CPpointnum =strItem;
/*    	if(nlistaj == 3)
        	m_List3.SetItemText(m_Itemnum, 2, strItem);
     	else if(nlistaj == 2)
        	m_List2.SetItemText(m_Itemnum, 2, strItem);
       	else if(nlistaj == 1)
         	m_List1.SetItemText(m_Itemnum, 2, strItem);*/

      g_Log.StatusOut(strItem +"标校完成");
}

void CSampleFormView::AdjustAll() 
{
}

void CSampleFormView::DelAllAdjust() 
{
}

void CSampleFormView::DisList123() 
{
	DisList(1, n_cF);
	DisList(2, n_cF);
	DisList(3, n_cF);
}

//nlist 列表控件 ilist  控件序号
void CSampleFormView::BuildList(int nlist ,int ilist) 
{
    	CString  strf,strc,strdate;
		int nItemCount;
		if(nlist == 1)
		{
            m_List1.DeleteAllItems();
			nItemCount = m_vl1.size();
//    		m_List1.SetItemCount(ncount);
		}
		else if(nlist == 2)
		{
            m_List2.DeleteAllItems();
			nItemCount = m_vl2.size();
		}
		else if(nlist == 3)
		{
            m_List3.DeleteAllItems();
			nItemCount = m_vl3.size();
		}
		   for(int i = 0; i < nItemCount; i ++)
		   {
        		if(nlist == 1)
	    		   strdate = m_vl1[i];
        		else if(nlist == 2)
	    		   strdate = m_vl2[i];
        		else if(nlist == 3)
	    		   strdate = m_vl3[i];
            		strf = strdate.Mid(0,2);
            		strc = strdate.Mid(3,2);
            		int nfds = m_Str2Data.String2Int(strf);
            		int nchan = m_Str2Data.String2Int(strc);
					int oacd ;
                	oacd =strdate.Find(_T("C"));
					if(oacd != -1)
						nchan =nchan+16;
                	strc = m_SlaveStation[nfds][nchan].WatchName;
        		if(nlist == 1)
				{
	    			  m_List1.InsertItem(i, strc);
	    			  m_List1.SetItemText(i, 2, strdate);
					  BuildLEXT(nlist , nfds, nchan, i);
				}
        		else if(nlist == 2)
				{
	    			  m_List2.InsertItem(i, strc);
	    			  m_List2.SetItemText(i, 2, strdate);
					  BuildLEXT(nlist , nfds, nchan, i);
				}
        		else if(nlist == 3)
				{
	    			  m_List3.InsertItem(i, strc);
	    			  m_List3.SetItemText(i, 2, strdate);
					  BuildLEXT(nlist , nfds, nchan, i);
				}
		   }
}

void CSampleFormView::BuildLEXT(int nlist ,int nfds,int nchan,int i) 
{
    	CString  strf;
		int nItemCount;

		int k=3;
       	for (int j = 3; j < 19; j++)
		{
			if(m_CommonStr[n_cF].strc[90+20*(nlist-1)+(j-3)] == "1" )
			{
				float f_value = 0;
				if(j == 6)
					f_value = m_SlaveStation[nfds][nchan].Apbrk;
				if(j == 7)
					f_value = m_SlaveStation[nfds][nchan].Aprtn;
				if(j == 8)
					f_value = m_SlaveStation[nfds][nchan].AlarmValueH;
				if(j == 9)
					f_value = m_SlaveStation[nfds][nchan].AlarmValueL;
				if(j == 10)
					f_value = m_SlaveStation[nfds][nchan].m_RangeH;
				if(j == 11)
					f_value = m_SlaveStation[nfds][nchan].m_RangeL;
				if(m_SlaveStation[nfds][nchan].ptype == 2)
					strf.Format("%.0f",f_value);
				else if( m_SlaveStation[nfds][nchan].ptype < 3)
					strf.Format("%.2f",f_value);
				else
					strf ="";
				if(j == 3 || j == 4 ||j == 5 ||j == 12 || j == 13 ||j == 14 ||j == 15 || j == 17 ||j == 18)
					strf ="";
				else if(j == 16 )
        	    	strf = m_SlaveStation[nfds][nchan].strBS;
				if(nlist == 1)
        	    	m_List1.SetItemText(i,k,strf);
				else if(nlist == 2)
        	    	m_List2.SetItemText(i,k,strf);
				else if(nlist == 3)
        	    	m_List3.SetItemText(i,k,strf);
				k++;
			}
		}
}

void CSampleFormView::DisList(int nlist ,int ilist) 
{
	if(b_curdis)
	{
        for(int i=0;i<3;i++)
            for(int j=0;j<MAX_FDS;j++)
                for(int k=0;k<MAX_CHAN;k++)
                    m_ls[i][j][k].oldstate = 254;
		SetMonitorListHead();
      	SetInfo();
		b_curdis =FALSE;
	}
     	CString dddd,strdate,strf,strc ;
		dddd=strdate=strf=strc="";
		int nItemCount=0;

		    if(nlist == 1)
                 nItemCount=m_List1.GetItemCount();
    		else if(nlist == 2)
                 nItemCount=m_List2.GetItemCount();
    		else if(nlist == 3)
                 nItemCount=m_List3.GetItemCount();
            for(int i=0;i<nItemCount;i++)
//		   for(int i = 0; i <m_vl1.size(); i ++)
			{
        		if(nlist == 1)
        			   strdate = m_List1.GetItemText(i,2);//m_vl1[i];
        		else if(nlist == 2)
        			   strdate = m_List2.GetItemText(i,2);
        		else if(nlist == 3)
        			   strdate = m_List3.GetItemText(i,2);
            		strf = strdate.Mid(0,2);
            		strc = strdate.Mid(3,2);
            		int nfds = m_Str2Data.String2Int(strf);
            		int nchan = m_Str2Data.String2Int(strc);
					int oacd ;
                	oacd =strdate.Find(_T("C"));
					if(oacd != -1)
						nchan =nchan+16;
    				 unsigned char oldstatus = m_ls[nlist-1][nfds][nchan].oldstate;
				     unsigned char nstatus = m_SlaveStation[nfds][nchan].Channel_state;
					 m_ls[nlist-1][nfds][nchan].oldstate =nstatus;
					 int nptype = m_SlaveStation[nfds][nchan].ptype;
				  dddd ="";
	     			  if( nptype<3)
					  {
						  if(m_SlaveStation[nfds][nchan].AValue > m_SlaveStation[nfds][nchan].m_RangeH)
						  {}
				    	  else
						  {
							  if(nptype == 2)
            					  dddd.Format("%.0f",m_SlaveStation[nfds][nchan].AValue);
							  else
    	     			    	  dddd.Format("%.2f",m_SlaveStation[nfds][nchan].AValue);
							  dddd += m_SlaveStation[nfds][nchan].m_Unit;
						  }
					  }
			    	  else
					  {
				    	  int nstatus1 = m_SlaveStation[nfds][nchan].CValue;
					     if(nstatus1 == 0)
						  dddd= m_SlaveStation[nfds][nchan].ZeroState;
					     else if(nstatus1 == 1)
						  dddd= m_SlaveStation[nfds][nchan].OneState;
				     	  else if(nstatus1 == 2)
						  dddd= m_SlaveStation[nfds][nchan].TwoState;
					  }
					  if((nstatus == 0x40)||(nstatus == 0x50)||(nstatus == 0x80)||(nstatus == 0x70)||(nstatus == 0x90)|| (nstatus == 0xa0))
				    		  dddd= socketClient.strstatus(nstatus);
//							  if(m_SlaveStation[nfds][nchan].AValue<666660)
            		if(nlist == 1)
    	     	      	  m_List1.SetItemText(i, 1, dddd);
            		if(nlist == 2)
    	     	      	  m_List2.SetItemText(i, 1, dddd);
            		if(nlist == 3)
    	     	      	  m_List3.SetItemText(i, 1, dddd);
					DisLEXT( nlist , nfds, nchan, i);
				  if(oldstatus != nstatus)// && m_SlaveStation[nfds][nchan].AValue<666660
				  {
                		if(nlist == 1)
                             m_List1.SetRowColor(i, m_Colorref[nstatus].SFSd, m_Str2Data.String2Int(m_CommonStr[n_cF].strc[9]));
                		else if(nlist == 2)
                             m_List2.SetRowColor(i, m_Colorref[nstatus].SFSd, m_Str2Data.String2Int(m_CommonStr[n_cF].strc[39]));
                		else if(nlist == 3)
                             m_List3.SetRowColor(i, m_Colorref[nstatus].SFSd, m_Str2Data.String2Int(m_CommonStr[n_cF].strc[69]));
				  }
//            m_List1.UpdateTextColor(i, m_Colorref[m_SlaveStation[nfds][nchan].Channel_state].SFSd);
			}
}

void CSampleFormView::DisLEXT(int nlist ,int nfds,int nchan,int i) 
{
    	CString  strf="";

		int k=3;
       	for (int j = 3; j < 19; j++)
		{
			strf = m_CommonStr[n_cF].strc[90+20*(nlist-1)+(j-3)];
			if(strf == "1" )
			{
        		int nItemCount = 0;
				strf ="";
				float f_value = 0;
				if(j == 3)
				{
					f_value = m_SlaveStation[nfds][nchan].m24_AMaxValue;
					if(f_value < 0.0001)
						nItemCount =10;
				}
				if(j == 4)
				{
					f_value = m_SlaveStation[nfds][nchan].m24_AMinValue;
					if(f_value > 666661)
						nItemCount =10;
				}
				if(j == 5)
				{
					int n_v = m_SlaveStation[nfds][nchan].m24_Atotal;
					if(n_v >0)
			    		f_value = m_SlaveStation[nfds][nchan].m24_ATotalValue/n_v;
					else
						nItemCount =10;
				}
				if(nItemCount !=10)
				{
    				if(m_SlaveStation[nfds][nchan].ptype == 2)
	    				strf.Format("%.0f",f_value);
		    		else if( m_SlaveStation[nfds][nchan].ptype < 3)
		    			strf.Format("%.2f",f_value);
				}
				if(j == 12)
				  if(m_ADMainDis[nfds][nchan].BTime.GetYear() != 1900)
     				  strf = m_ADMainDis[nfds][nchan].BTime.Format(_T("%Y-%m-%d %H:%M:%S")); 
				  else
					  strf ="";
				if(j == 13)
				  if(m_ADMainDis[nfds][nchan].NTime.GetYear() != 1900)
     				  strf = m_ADMainDis[nfds][nchan].NTime.Format(_T("%Y-%m-%d %H:%M:%S")); 
				  else
					  strf ="";
				if(j == 14)
				  if(m_ADMainDis[nfds][nchan].ATime.GetYear() != 1900)
     				  strf = m_ADMainDis[nfds][nchan].ATime.Format(_T("%Y-%m-%d %H:%M:%S")); 
				  else
					  strf ="";
				if(j == 15)
				  if(m_ADMainDis[nfds][nchan].RTime.GetYear() != 1900)
				  {
     				  strf = m_ADMainDis[nfds][nchan].RTime.Format(_T("%Y-%m-%d %H:%M:%S")); 
					  strf += "|" +m_SlaveStation[nfds][nchan].FeedState;
				  }
				  else
					  strf ="";
				if(j == 6 || j == 7 ||j == 8 ||j == 9 || j == 10 ||j == 11 ||j == 16)
				{}
				else
				{
    				if(nlist == 1)
        	        	m_List1.SetItemText(i,k,strf);
		    		else if(nlist == 2)
        	        	m_List2.SetItemText(i,k,strf);
			     	else if(nlist == 3)
        	        	m_List3.SetItemText(i,k,strf);
				}
				k++;
			}
		}
}

void CSampleFormView::OnContextMenu(CWnd* pWnd, CPoint point) 
{
//	CString pString ;
//    CMenu menu,* pSubMenu; // 定义CMenu类对象
//    menu.LoadMenu(IDC_POPLISTCONTROL); //装入刚建立的菜单 IDC_POPMENU menu.GetSubMenu(0)->TrackPopupMenu(TPM_LEFTALIGN,point.x,point.y,pWnd); 
/*GetSubMenu(0) 得到IDC_POPMENU的第一层子菜单，TrackPopupMenu将菜单弹出到（x,y）处。由于设置为TPM_LEFTALIGN，所以菜单以（x,y）为左上角。*/
}

//bool CSampleFormView::SortList(int /*nCol*/, bool /*bAscending*/)
/*{
	CXTSortClass csc (&m_List1, m_nSortedCol);
    	csc.Sort (m_bAscending, xtSortInt);
	CXTSortClass csc2 (&m_List2, m_nSortedCol);
    	csc2.Sort (m_bAscending, xtSortInt);
	CXTSortClass csc3 (&m_List3, m_nSortedCol);
    	csc3.Sort (m_bAscending, xtSortInt);

//	if(m_Planting ==4)
//    	csc.Sort (m_bAscending, xtSortDateTime);
//	else
    	//csc.Sort (0, xtSortInt);          //max>> min
//    	csc.Sort (m_bAscending, xtSortString);
	return true;
}*/

void   CSampleFormView::OnColumnclickListstock(NMHDR*   pNMHDR,   LRESULT*   pResult)  
{
   NM_LISTVIEW*   pNMListView   =   (NM_LISTVIEW*)pNMHDR;
//   static int iSorted=-1;//排列序号
   if (pNMListView->iSubItem  == -1) return;
//   m_nSortedCol = pNMListView->iSubItem;
    		if (pNMListView->iSubItem == m_nSortedCol)
		    	SortColumn(pNMListView->iSubItem, !m_bAscending,1);
    		else
		    	SortColumn(pNMListView->iSubItem, BoolType(m_flatHeader.GetAscending()),1);
   *pResult   =   0;
}

void   CSampleFormView::OnColumnclickListstock2(NMHDR*   pNMHDR,   LRESULT*   pResult)  
{
   NM_LISTVIEW*   pNMListView   =   (NM_LISTVIEW*)pNMHDR;
   if (pNMListView->iSubItem  == -1) return;
    		if (pNMListView->iSubItem == m_nSortedCol2)
		    	SortColumn(pNMListView->iSubItem, !m_bAscending2,2);
    		else
		    	SortColumn(pNMListView->iSubItem, BoolType(m_flatHeader2.GetAscending()),2);
   *pResult   =   0;
}

void   CSampleFormView::OnColumnclickListstock3(NMHDR*   pNMHDR,   LRESULT*   pResult)  
{
   NM_LISTVIEW*   pNMListView   =   (NM_LISTVIEW*)pNMHDR;
   if (pNMListView->iSubItem  == -1) return;
    		if (pNMListView->iSubItem == m_nSortedCol3)
		    	SortColumn(pNMListView->iSubItem, !m_bAscending3,3);
    		else
		    	SortColumn(pNMListView->iSubItem, BoolType(m_flatHeader3.GetAscending()),3);
   *pResult   =   0;
}

void CSampleFormView::OnDRAWS() 
{
	CString pString,strpo;
	pString =GetDocument()->GetTitle();
       		int m_ishave = pString.GetLength();
    		strpo = pString.Mid(m_ishave-3,3);
	if(strpo != "rsf")
	    pString += ".rsf";
	CFormDraw dlg;
	dlg.m_dorf=2;
	dlg.m_result = pString;
	dlg.DoModal();
}

void CSampleFormView::OnFORMSCOLOR() 
{
	CColorSetDlg dlg;
	dlg.m_ntrans= n_cF;
	dlg.m_nlist = nlistaj;
	dlg.DoModal();
}

void CSampleFormView::OnFORMPAGESO() 
{
      	CString strrsy ,strrsy1;
     	strrsy = gstrTimeOut + "\\" + strMetrics+ "rsy\\";
     	strrsy1 ="dispoint"+strMetrics;
	CString pString,strpo;
	pString =GetDocument()->GetTitle();
       		int m_ishave = pString.GetLength();
    		strpo = pString.Mid(m_ishave-3,3);
	if(strpo != "rsf")
	    pString += ".rsf";
            strpo.Format("UPDATE '%s' SET LP0='%s' WHERE DISID=100;",
			    	     strrsy1,pString );
			theApp.db3.execDML(strpo);
}

void CSampleFormView::OnFORMSLISTEXT() 
{
	CDListEXT dlg;
	dlg.m_ntrans= n_cF;
	dlg.m_nlist = nlistaj;
	dlg.DoModal();
}
