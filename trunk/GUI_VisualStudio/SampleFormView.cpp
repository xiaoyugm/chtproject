// SampleFormView.cpp : implementation file
//

#include "stdafx.h"
#include "GUI_VisualStudio.h"
#include "SampleFormView.h"
#include "MainFrm.h"

#include "SettingHostDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern  SlaveStation             m_SlaveStation[65][25];
extern  FormView  m_FormView[20];
extern  DisplayPoint  m_DisplayPoint[32][64];
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

	m_nSortedCol = 1;
	m_bAscending = true;

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
//	ON_COMMAND(ID_A_D, OpenAddDel)
	ON_COMMAND(IDC_COMBO_THEMES, OnSelendokComboThemes)
//	ON_WM_CREATE()
//	ON_WM_ERASEBKGND()
//	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_WM_CONTEXTMENU()
    ON_NOTIFY(NM_RCLICK,IDC_LIST_POINT1, OnRclick1)
    ON_NOTIFY(NM_RCLICK,IDC_LIST_POINT2, OnRclick2)
    ON_NOTIFY(NM_RCLICK,IDC_LIST_POINT3, OnRclick3)
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

	CMainFrame* pFWnd=(CMainFrame*)AfxGetMainWnd();

   	pFWnd->m_pSampleFormView=this;

	if (!CreateImageList(m_SampleFormImageList, IDB_CLASSTREE))
		return ;
	// Create and attach image list
	m_ImageList.Create(16, 16, ILC_COLOR16 | ILC_MASK, 1, 0);
	m_ImageList.Add(AfxGetApp()->LoadIcon(IDR_GUI_WHTYPE));
	m_ImageList.Add(AfxGetApp()->LoadIcon(IDR_MAINFRAME));

	CString strlist1,strlist2,strlist3;
	strlist1.Format("%d",theApp.DocNum*3+1);
	strlist2.Format("%d",theApp.DocNum*3+2);
	strlist3.Format("%d",theApp.DocNum*3+3);

	m_List1.SetWindowText(strlist1);
	m_List2.SetWindowText(strlist2);
	m_List3.SetWindowText(strlist3);

	m_List1.SetImageList(&m_SampleFormImageList, LVSIL_SMALL);
	m_List2.SetImageList(&m_ImageList, LVSIL_SMALL);
	// Give better margin to editors
	m_List1.SetCellMargin(1.2);
	CGridRowTraitXP* pRowTrait = new CGridRowTraitXP;
	m_List1.SetDefaultRowTrait(pRowTrait);

	// Create Columns
	m_List1.InsertHiddenLabelColumn();	// Requires one never uses column 0
	m_List2.InsertHiddenLabelColumn();	// Requires one never uses column 0
	m_List3.InsertHiddenLabelColumn();	// Requires one never uses column 0

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
	m_List1.SetCellImage(1, 2, 0);
	m_List1.SetCellImage(2, 2, 0);
	m_List1.SetCellImage(3, 2, 1);

//	CGridColumnManagerProfile* pColumnProfile = new CGridColumnManagerProfile(_T("Sample List"));
//	pColumnProfile->AddColumnProfile(_T("Default"));
//	pColumnProfile->AddColumnProfile(_T("Special"));
//	m_List1.SetupColumnConfig(pColumnProfile);

	CString pString ;
	m_List1.GetWindowText(pString);
	BuildList(1, m_Str2Data.String2Int(pString));
	m_List2.GetWindowText(pString);
	BuildList(2, m_Str2Data.String2Int(pString));
	m_List3.GetWindowText(pString);
	BuildList(3, m_Str2Data.String2Int(pString));

}

void CSampleFormView::SetInfo(int m_List,int iItem,CString strSubA,CString strSubB,CString strSubC) 
{
	if (m_List == 1)
	{
	m_List1.SetCellImage(1, 1, 0);
	m_List1.SetCellImage(2, 1, 0);
	m_List1.SetCellImage(3, 1, 1);
		int ncolumn = m_List1.GetItemCount();
		CString strname;
		strname.Format("%d",ncolumn);
		m_List1.SetItem(iItem-1, 1, LVIF_TEXT, strSubA, 0, NULL, NULL, NULL);
		m_List1.SetItem(iItem, 2, LVIF_TEXT, strSubB, 0, NULL, NULL, NULL);
		m_List1.SetItem(ncolumn-1, 3, LVIF_TEXT, strname, 0, NULL, NULL, NULL);
		m_List1.SetRowColor(iItem, RGB(255,0,0), RGB(0,0,255));
	}
	if (m_List == 2)
	{
	m_List2.SetCellImage(1, 2, 0);
	m_List2.SetCellImage(2, 2, 0);
	m_List2.SetCellImage(3, 2, 1);
		int ncolumn1 = m_List2.GetItemCount();
		CString strname1;
		strname1.Format("%d",ncolumn1);
		m_List2.SetItem(iItem+1, 1, LVIF_TEXT, strSubA, 0, NULL, NULL, NULL);
		m_List2.SetItem(iItem+1, 2, LVIF_TEXT, strSubB, 0, NULL, NULL, NULL);
		m_List2.SetItem(ncolumn1-1, 3, LVIF_TEXT, strname1, 0, NULL, NULL, NULL);
	}
	if (m_List == 3)
	{
		m_List3.SetItem(iItem+2, 1, LVIF_TEXT, strSubA, 0, NULL, NULL, NULL);
		m_List3.SetItem(iItem+2, 2, LVIF_TEXT, strSubB, 0, NULL, NULL, NULL);
		m_List3.SetItem(iItem+2, 3, LVIF_TEXT, strSubC, 0, NULL, NULL, NULL);
	}

}

void CSampleFormView::SetMonitorListHead()
{
//	m_List1.SetWindowPos(NULL,0,0,GetSystemMetrics(SM_CXSCREEN)-8,140,SWP_NOMOVE|SWP_NOZORDER | SWP_NOACTIVATE|SWP_SHOWWINDOW);
	CListCtrl* ctext2;
    ctext2 = (CListCtrl*)GetDlgItem(IDC_LIST_POINT1);//get the pointer
    RECT rect2 = {m_FormView[theApp.DocNum].m_ListCtrl[0].MoveWindowx, 0, 0, 0};
	ctext2->MoveWindow(&rect2);//Move window 

	m_List1.SetWindowPos(NULL,0,0,m_FormView[theApp.DocNum].m_ListCtrl[0].SetWindowPosX,m_FormView[theApp.DocNum].m_ListCtrl[0].SetWindowPosY,SWP_NOMOVE|SWP_NOZORDER | SWP_NOACTIVATE);
//	m_List1.SetExtendedStyle(LVS_EX_FULLROWSELECT);

//		m_List1.InsertColumn(0,m_FormView[theApp.DocNum].m_ListCtrl[0].ColumnHeading1,LVCFMT_LEFT,m_FormView[theApp.DocNum].m_ListCtrl[0].ColumnWidth1);
		m_List1.InsertColumn(1,m_FormView[theApp.DocNum].m_ListCtrl[0].ColumnHeading1,LVCFMT_LEFT,m_FormView[theApp.DocNum].m_ListCtrl[0].ColumnWidth1);
		m_List1.InsertColumn(2,m_FormView[theApp.DocNum].m_ListCtrl[0].ColumnHeading2,LVCFMT_LEFT,m_FormView[theApp.DocNum].m_ListCtrl[0].ColumnWidth2);
		m_List1.InsertColumn(3,m_FormView[theApp.DocNum].m_ListCtrl[0].ColumnHeading3,LVCFMT_LEFT,m_FormView[theApp.DocNum].m_ListCtrl[0].ColumnWidth3);
//		m_List1.SetImageList(&m_SampleFormView, TVSIL_NORMAL);
//获得原有风格
     DWORD dwStyle = ::GetWindowLong(m_List1.m_hWnd, GWL_STYLE);
//dwStyle &= ~(LVS_TYPEMASK);
//dwStyle &= ~(LVS_EDITLABELS);
	 if(!m_FormView[theApp.DocNum].m_ListCtrl[0].Visible)
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

	CListCtrl* ctext;
    ctext = (CListCtrl*)GetDlgItem(IDC_LIST_POINT2);//get the pointer
    RECT rect = {m_FormView[theApp.DocNum].m_ListCtrl[1].MoveWindowx, 0, 0, 0};
	ctext->MoveWindow(&rect);//Move window 
	m_List2.SetWindowPos(this,0,0,m_FormView[theApp.DocNum].m_ListCtrl[1].SetWindowPosX,m_FormView[theApp.DocNum].m_ListCtrl[1].SetWindowPosY,SWP_NOMOVE|SWP_NOZORDER | SWP_NOACTIVATE);
	m_List2.SetExtendedStyle(LVS_EX_ONECLICKACTIVATE);
//		m_List2.InsertColumn(0,m_FormView[theApp.DocNum].m_ListCtrl[1].ColumnHeading1,LVCFMT_LEFT,m_FormView[theApp.DocNum].m_ListCtrl[1].ColumnWidth1);
		m_List2.InsertColumn(1,m_FormView[theApp.DocNum].m_ListCtrl[1].ColumnHeading1,LVCFMT_LEFT,m_FormView[theApp.DocNum].m_ListCtrl[1].ColumnWidth1);
		m_List2.InsertColumn(2,m_FormView[theApp.DocNum].m_ListCtrl[1].ColumnHeading2,LVCFMT_LEFT,m_FormView[theApp.DocNum].m_ListCtrl[1].ColumnWidth2);
		m_List2.InsertColumn(3,m_FormView[theApp.DocNum].m_ListCtrl[1].ColumnHeading3,LVCFMT_LEFT,m_FormView[theApp.DocNum].m_ListCtrl[1].ColumnWidth3);

     dwStyle = ::GetWindowLong(m_List2.m_hWnd, GWL_STYLE);
	 if(!m_FormView[theApp.DocNum].m_ListCtrl[1].Visible)
          dwStyle &= ~(WS_VISIBLE);
     SetWindowLong(m_List2.m_hWnd, GWL_STYLE,dwStyle );

	CListCtrl* ctext1;
    ctext1 = (CListCtrl*)GetDlgItem(IDC_LIST_POINT3);//get the pointer
    RECT rect1 = {m_FormView[theApp.DocNum].m_ListCtrl[2].MoveWindowx, 0, 0, 0};
	ctext1->MoveWindow(&rect1);//Move window 
	m_List3.SetWindowPos(NULL,0,0,m_FormView[theApp.DocNum].m_ListCtrl[2].SetWindowPosX,m_FormView[theApp.DocNum].m_ListCtrl[2].SetWindowPosY,SWP_NOMOVE|SWP_NOZORDER | SWP_NOACTIVATE);
	m_List3.SetExtendedStyle(LVS_EX_TWOCLICKACTIVATE);
//		m_List3.InsertColumn(0,m_FormView[theApp.DocNum].m_ListCtrl[2].ColumnHeading1,LVCFMT_LEFT,m_FormView[theApp.DocNum].m_ListCtrl[2].ColumnWidth1);
		m_List3.InsertColumn(1,m_FormView[theApp.DocNum].m_ListCtrl[2].ColumnHeading1,LVCFMT_LEFT,m_FormView[theApp.DocNum].m_ListCtrl[2].ColumnWidth1);
		m_List3.InsertColumn(2,m_FormView[theApp.DocNum].m_ListCtrl[2].ColumnHeading2,LVCFMT_LEFT,m_FormView[theApp.DocNum].m_ListCtrl[2].ColumnWidth2);
		m_List3.InsertColumn(3,m_FormView[theApp.DocNum].m_ListCtrl[2].ColumnHeading3,LVCFMT_LEFT,m_FormView[theApp.DocNum].m_ListCtrl[2].ColumnWidth3);

     dwStyle = ::GetWindowLong(m_List3.m_hWnd, GWL_STYLE);
	 if(!m_FormView[theApp.DocNum].m_ListCtrl[2].Visible)
          dwStyle &= ~(WS_VISIBLE);
     SetWindowLong(m_List3.m_hWnd, GWL_STYLE,dwStyle );

	m_List1.SubclassHeader(m_FormView[theApp.DocNum].m_ListCtrl[0].SubclassHeader);
	m_List2.SubclassHeader(m_FormView[theApp.DocNum].m_ListCtrl[1].SubclassHeader);
	m_List3.SubclassHeader(m_FormView[theApp.DocNum].m_ListCtrl[2].SubclassHeader);

//		strtemp.Format("□%d",iItem); //◎◎··●●□□◇   //**change subscript
	CXTFlatHeaderCtrl* pHeaderCtrl = m_List2.GetFlatHeaderCtrl( );
	if ( pHeaderCtrl != NULL )
	{
//		pHeaderCtrl->EnableAutoSize();
//    	pHeaderCtrl->SetBitmap(0, IDB_COLUMN_0, FALSE, RGB(0,255,0));
//    	pHeaderCtrl->SetBitmap(1, IDB_COLUMN_1, FALSE, RGB(0,255,0));
//		pHeaderCtrl->SetBitmap(2, IDB_COLUMN_2, FALSE, RGB(0,255,0));
	}
	CXTFlatHeaderCtrl* pHeaderCtrl1 = m_List3.GetFlatHeaderCtrl( );
	if ( pHeaderCtrl1 != NULL )
	{
//		pHeaderCtrl1->EnableAutoSize();
//    	pHeaderCtrl1->SetBitmap(0, IDB_COLUMN_0, FALSE, RGB(0,255,0));
//    	pHeaderCtrl1->SetBitmap(1, IDB_COLUMN_1, FALSE, RGB(0,255,0));
//		pHeaderCtrl1->SetBitmap(2, IDB_COLUMN_2, FALSE, RGB(0,255,0));
	}

	// Get the windows handle to the header control for the
	// list control then subclass the control.
//	HWND hWndHeader = m_List1.GetDlgItem(IDC_LIST_POINT1)->GetSafeHwnd();
//	m_flatHeader.SubclassWindow (hWndHeader);
	m_flatHeader = m_List1.GetFlatHeaderCtrl( );

	// add bitmap images.
//	m_flatHeader->SetBitmap(0, IDB_COLUMN_0, FALSE, RGB(0,255,0));
//	m_flatHeader->SetBitmap(1, IDB_COLUMN_1, FALSE, RGB(0,255,0));
//	m_flatHeader->SetBitmap(2, IDB_COLUMN_2, FALSE, RGB(0,255,0));
//	m_flatHeader.InitializeHeader(TRUE);	
//	if (m_bSaveColumnWidth)
//		m_ctrlListMonitor.LoadColumnWidths();

	// enable auto sizing.
//	m_flatHeader->EnableAutoSize(TRUE);
//	m_flatHeader->ResizeColumnsToFit();
	SortColumn(m_nSortedCol, m_bAscending);

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
	m_List1.SetRowColors(m_FormView[theApp.DocNum].m_ListCtrl[0].TextColor, m_FormView[theApp.DocNum].m_ListCtrl[0].BackColor);
	m_List2.SetRowColors(m_FormView[theApp.DocNum].m_ListCtrl[1].TextColor, m_FormView[theApp.DocNum].m_ListCtrl[1].BackColor);
	m_List3.SetRowColors(m_FormView[theApp.DocNum].m_ListCtrl[2].TextColor, m_FormView[theApp.DocNum].m_ListCtrl[2].BackColor);

	// set some extnded styles
//	m_List1.SetExtendedStyle (LVS_EX_FULLROWSELECT|LVS_EX_FLATSB);
	m_List1.SetExtendedStyle (LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_List2.SetExtendedStyle (LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES|LVS_EX_FLATSB);
	m_List3.SetExtendedStyle (LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES|LVS_EX_FLATSB);

//	m_List1.ModifyExtendedStyle(0, LVS_EX_FULLROWSELECT);
	m_List1.EnableUserSortColor(true);
	m_List1.EnableUserListColor(true);
	m_List1.EnableUserRowColor(true);
	m_List2.EnableUserSortColor(true);
	m_List2.EnableUserListColor(true);
	m_List2.EnableUserRowColor(true);
	m_List3.EnableUserSortColor(true);
	m_List3.EnableUserListColor(true);
	m_List3.EnableUserRowColor(true);

	OnSelendokComboThemes();

//行数
	CString strItem = _T("");
	for (int iItem = 0; iItem < m_FormView[theApp.DocNum].m_ListCtrl[0].ColumniItem; ++iItem)
		m_List1.InsertItem(iItem, strItem, 0);
	for (iItem = 0; iItem < m_FormView[theApp.DocNum].m_ListCtrl[1].ColumniItem; ++iItem)
		m_List2.InsertItem(iItem, strItem, 0);
	for (iItem = 0; iItem < m_FormView[theApp.DocNum].m_ListCtrl[2].ColumniItem; ++iItem)
		m_List3.InsertItem(iItem, strItem, 0);
}


void CSampleFormView::OnSelendokComboThemes()
{
	UpdateData();

	switch (m_iTheme)
	{
	case 0:
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
		break;
	}

	UpdateData(FALSE);

	DWORD dwStyle = 0L;
	if (m_bWinTheme && m_iTheme >= 2)
		dwStyle |= XTTHEME_WINXPTHEMES;

	if (m_bWinTheme && m_iTheme >= 2 && m_bHotTracking)
		dwStyle |= XTTHEME_HOTTRACKING;

	if (m_bSortArrow)
		dwStyle |= XTTHEME_SORTARROW;

	CXTHeaderCtrlTheme* pTheme = m_flatHeader->GetTheme();
	if (pTheme)
	{
		pTheme->SetDrawStyle(dwStyle, m_flatHeader);
		EnableControls();
	}
}

void CSampleFormView::SortColumn(int iCol, bool bAsc)
{
	m_bAscending = bAsc;
	m_nSortedCol = iCol;

	// set sort image for header and sort column.
	m_List1.SetSortImage(m_nSortedCol, m_bAscending);

	CXTSortClass csc(&m_List1, m_nSortedCol);
	csc.Sort(m_bAscending, xtSortString);
}

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
	CString pString ;
	m_List1.GetWindowText(pString);
//	CListCtrl &CList =  GetListCtrl();//获取当前列表控件的指针
       CMenu       menu ,* pSubMenu;//定义下面要用到的cmenu对象

       menu.LoadMenu(IDC_POPLISTCONTROL);//装载自定义的右键菜单

       pSubMenu = menu.GetSubMenu(0);//获取第一个弹出菜单，所以第一个菜单必须有子菜单

    CPoint oPoint;//定义一个用于确定光标位置的位置

    GetCursorPos( &oPoint);//获取当前光标的位置，以便使得菜单可以跟随光标

//       int istat;//=CList.GetSelectionMark();//用istat存放当前选定的是第几项

//    CString pString; //=CList.GetItemText(istat,0);//获取当前项中的数据，0代表是第0列
//	pString="您选择的路径是:"+pString ;//显示当前选择项
//       MessageBox(pString);//显示当前选中的路径
//       pSubMenu->TrackPopupMenu (TPM_LEFTALIGN, oPoint.x, oPoint.y, this); //在指定位置显示弹出菜单

	// Will return zero if no selection was made (TPM_RETURNCMD)
	int nResult = pSubMenu->TrackPopupMenu (TPM_LEFTALIGN, oPoint.x, oPoint.y, this); //在指定位置显示弹出菜单
	switch(nResult)
	{
		case 0: break;
		case 1:	OpenAddDel(1, m_Str2Data.String2Int(pString)); break;
//		case 2: m_pColumnManager->OpenColumnPicker(*this); break;
//		case 3: m_pColumnManager->ResetColumnsDefault(*this); break;
		default: break;
	}
}
void CSampleFormView::OnRclick2(NMHDR* pNMHDR, LRESULT* pResult)
{
	CString pString ;
	m_List2.GetWindowText(pString);


       CMenu       menu ,* pSubMenu;//定义下面要用到的cmenu对象
       menu.LoadMenu(IDC_POPLISTCONTROL);//装载自定义的右键菜单
       pSubMenu = menu.GetSubMenu(0);//获取第一个弹出菜单，所以第一个菜单必须有子菜单
    CPoint oPoint;//定义一个用于确定光标位置的位置
    GetCursorPos( &oPoint);//获取当前光标的位置，以便使得菜单可以跟随光标
//       pSubMenu->TrackPopupMenu (TPM_LEFTALIGN, oPoint.x, oPoint.y, this); //在指定位置显示弹出菜单

	// Will return zero if no selection was made (TPM_RETURNCMD)
	int nResult = pSubMenu->TrackPopupMenu (TPM_LEFTALIGN, oPoint.x, oPoint.y, this); //在指定位置显示弹出菜单
	switch(nResult)
	{
		case 0: break;
		case 1:	OpenAddDel(2, m_Str2Data.String2Int(pString)); break;
		default: break;
	}
}


void CSampleFormView::OnRclick3(NMHDR* pNMHDR, LRESULT* pResult)
{
	CString pString ;
	m_List3.GetWindowText(pString);

	CMenu       menu ,* pSubMenu;//定义下面要用到的cmenu对象
       menu.LoadMenu(IDC_POPLISTCONTROL);//装载自定义的右键菜单
       pSubMenu = menu.GetSubMenu(0);//获取第一个弹出菜单，所以第一个菜单必须有子菜单
    CPoint oPoint;//定义一个用于确定光标位置的位置
    GetCursorPos( &oPoint);//获取当前光标的位置，以便使得菜单可以跟随光标
//      pSubMenu->TrackPopupMenu (TPM_LEFTALIGN, oPoint.x, oPoint.y, this); //在指定位置显示弹出菜单

	// Will return zero if no selection was made (TPM_RETURNCMD)
	int nResult = pSubMenu->TrackPopupMenu (TPM_LEFTALIGN, oPoint.x, oPoint.y, this); //在指定位置显示弹出菜单
	switch(nResult)
	{
		case 0: break;
		case 1:	OpenAddDel(3, m_Str2Data.String2Int(pString)); break;
		default: break;
	}
}

void CSampleFormView::OpenAddDel(int nlist ,int ilist) 
{
	CSettingHostDlg dlg;
	dlg.m_strtable =  _T("dispoint");
	dlg.PointDesid = ilist;
	if(dlg.DoModal() == IDOK)
		BuildList(nlist, ilist);
}

void CSampleFormView::DisList123() 
{
	int ilist ,nlist;
	CString pString ;
	m_List1.GetWindowText(pString);
	ilist = m_Str2Data.String2Int(pString);
	nlist =  ilist%3;
	if(nlist == 0)
		nlist =3;
	BuildList(nlist, ilist);

	m_List2.GetWindowText(pString);
	ilist = m_Str2Data.String2Int(pString);
	nlist =  ilist%3;
	if(nlist == 0)
		nlist =3;
	BuildList(nlist, ilist);

	m_List3.GetWindowText(pString);
	ilist = m_Str2Data.String2Int(pString);
	nlist =  ilist%3;
	if(nlist == 0)
		nlist =3;
	BuildList(nlist, ilist);
}

//nlist 列表控件 ilist  控件序号
void CSampleFormView::BuildList(int nlist ,int ilist) 
{
		if(nlist == 1)
		{
			int ncount = m_DisplayPoint[ilist][60].fds;
            m_List1.DeleteAllItems();
    		m_List1.SetItemCount(ncount);
		   for(int i = 0; i <= ncount; i ++)
		   {
		int nfds = m_DisplayPoint[ilist][i].fds;
		if(!nfds)
			return;
		int nchan = m_DisplayPoint[ilist][i].chan;
				  CString dddd =m_DisplayPoint[ilist][i].CPName;
				  dddd.TrimRight();
				  m_List1.InsertItem(i, "");
				  m_List1.SetItemText(i, 1, dddd);
				  int nptype = m_DisplayPoint[ilist][i].ptype;
				  if( nptype== 0)
					  dddd.Format("%.4f",m_SlaveStation[nfds][nchan].AValue);
				  else
					  dddd.Format("%d",m_SlaveStation[nfds][nchan].CValue);
    			  m_List1.SetItemText(i, 2, dddd);
				  dddd =m_DisplayPoint[ilist][i].CPpointnum;
				  dddd.TrimRight();
				  m_List1.SetItemText(i, 3, dddd);
		   }
		}
		if(nlist == 2)
		{
			int ncount = m_DisplayPoint[ilist][60].fds;
            m_List2.DeleteAllItems();
    		m_List2.SetItemCount(ncount);
		   for(int i = 0; i <= ncount; i ++)
		   {
		int nfds = m_DisplayPoint[ilist][i].fds;
		if(!nfds)
			return;
		int nchan = m_DisplayPoint[ilist][i].chan;
				  CString dddd =m_DisplayPoint[ilist][i].CPName;
				  dddd.TrimRight();
				  m_List2.InsertItem(i, "");
				  m_List2.SetItemText(i, 1, dddd);
				  int nptype = m_DisplayPoint[ilist][i].ptype;
				  if( nptype== 0)
					  dddd.Format("%.4f",m_SlaveStation[nfds][nchan].AValue);
				  else
					  dddd.Format("%d",m_SlaveStation[nfds][nchan].CValue);
    			  m_List2.SetItemText(i, 2, dddd);
				  dddd =m_DisplayPoint[ilist][i].CPpointnum;
				  dddd.TrimRight();
				  m_List2.SetItemText(i, 3, dddd);
		   }
		}
		if(nlist == 3)
		{
			int ncount = m_DisplayPoint[ilist][60].fds;
            m_List3.DeleteAllItems();
    		m_List3.SetItemCount(ncount);
		   for(int i = 0; i <= ncount; i ++)
		   {
		int nfds = m_DisplayPoint[ilist][i].fds;
		if(!nfds)
			return;
		int nchan = m_DisplayPoint[ilist][i].chan;
				  CString dddd =m_DisplayPoint[ilist][i].CPName;
				  dddd.TrimRight();
				  m_List3.InsertItem(i, "");
				  m_List3.SetItemText(i, 1, dddd);
				  int nptype = m_DisplayPoint[ilist][i].ptype;
				  if( nptype== 0 )
					  dddd.Format("%.4f",m_SlaveStation[nfds][nchan].AValue);
				  else
					  dddd.Format("%d",m_SlaveStation[nfds][nchan].CValue);
    			  m_List3.SetItemText(i, 2, dddd);
				  dddd =m_DisplayPoint[ilist][i].CPpointnum;
				  dddd.TrimRight();
				  m_List3.SetItemText(i, 3, dddd);
		   }
		}
}

void CSampleFormView::OnContextMenu(CWnd* pWnd, CPoint point) 
{
CMenu menu; // 定义CMenu类对象
menu.LoadMenu(IDC_POPLISTCONTROL); //装入刚建立的菜单 IDC_POPMENU menu.GetSubMenu(0)->TrackPopupMenu(TPM_LEFTALIGN,point.x,point.y,pWnd); 
/*GetSubMenu(0) 得到IDC_POPMENU的第一层子菜单，TrackPopupMenu将菜单弹出到（x,y）处。由于设置为TPM_LEFTALIGN，所以菜单以（x,y）为左上角。*/

}

