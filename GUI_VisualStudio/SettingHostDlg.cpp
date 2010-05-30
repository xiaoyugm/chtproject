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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);         // Set big icon
	SetIcon(m_hIcon, FALSE);        // Set small icon

	SetWindowText(_T("Settings"));

	// Set control resizing.
	SetResize(IDOK,                  SZ_TOP_RIGHT,   SZ_TOP_RIGHT);
	SetResize(IDCANCEL,              SZ_TOP_RIGHT,   SZ_TOP_RIGHT);
	SetResize(IDC_LIST_CTRL,         SZ_TOP_LEFT,    SZ_BOTTOM_RIGHT);

//	SetResize(IDC_GBOX_HEADER,       SZ_BOTTOM_LEFT, SZ_BOTTOM_RIGHT);
	SetResize(IDC_BUT_ADD,      SZ_BOTTOM_LEFT, SZ_BOTTOM_LEFT);
	SetResize(IDC_BUT_DEL,      SZ_BOTTOM_LEFT, SZ_BOTTOM_LEFT);
	SetResize(IDC_BUT_MOD,      SZ_BOTTOM_LEFT, SZ_BOTTOM_LEFT);

	// Enable Office XP themes.
	XTThemeManager()->SetTheme(xtThemeOfficeXP);

	// Load window placement
//	LoadPlacement(_T("CListCtrlDlg"));

	// TODO: Add extra initialization here
	m_listCtrl.InsertColumn(0, _T("Column One"),   LVCFMT_LEFT, 125);
	m_listCtrl.InsertColumn(1, _T("Column Two"),   LVCFMT_LEFT, 125);
	m_listCtrl.InsertColumn(2, _T("Column Three"), LVCFMT_LEFT, 125);

	int iItem;
	for (iItem = 0; iItem < 100; ++iItem)
	{
		CString strItem;
		CString strSubA;
		CString strSubB;

		strItem.Format(_T("Item %d"), iItem);
		strSubA.Format(_T("Sub A %d"), iItem);
		strSubB.Format(_T("Sub B %d"), iItem);

		m_listCtrl.InsertItem(iItem, strItem, 0);
		m_listCtrl.SetItem(iItem, 1, LVIF_TEXT, strSubA, 0, NULL, NULL, NULL);
		m_listCtrl.SetItem(iItem, 2, LVIF_TEXT, strSubB, 0, NULL, NULL, NULL);
	}

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
	m_listCtrl.ModifyExtendedStyle(0, LVS_EX_FULLROWSELECT|LVS_EX_FULLROWSELECT);
	m_listCtrl.EnableUserSortColor(BoolType(m_bSortColor));
	m_listCtrl.EnableUserListColor(BoolType(m_bListColor));
	m_listCtrl.EnableUserRowColor(BoolType(m_bRowColor));

//	OnSelendokComboThemes();

	return TRUE;  // return TRUE  unless you set the focus to a control
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
}

void CSettingHostDlg::OnBtnDEL()
{
}

void CSettingHostDlg::OnBtnMOD()
{
}