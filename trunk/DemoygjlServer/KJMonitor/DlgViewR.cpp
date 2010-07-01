// DlgViewR.cpp : implementation file
//

#include "stdafx.h"
#include "KJMonitor.h"
#include "DlgViewR.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgViewR dialog


CDlgViewR::CDlgViewR(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgViewR::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgViewR)
	//}}AFX_DATA_INIT
	//m_GridView.SetDataSource(dbUser);
	m_nSortedCol = -1;
	m_bAscending = true;

}


void CDlgViewR::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgViewR)
	DDX_Control(pDX, IDOK, m_btnOK);
	DDX_Control(pDX, IDC_BUTTON_SORTBYUSER, m_ctrlBtnSortByUser);
	DDX_Control(pDX, IDC_BUTTON_SORTBYAUTH, m_ctrlBtnSortByAuth);
	DDX_Control(pDX, IDC_BUTTON_DELETE, m_ctrlBtnDelete);
	DDX_Control(pDX, IDC_LIST_TABLE, m_ctrlListTable);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgViewR, CDialog)
	//{{AFX_MSG_MAP(CDlgViewR)
	ON_BN_CLICKED(IDC_BUTTON_SORTBYUSER, OnButtonSortbyuser)
	ON_BN_CLICKED(IDC_BUTTON_SORTBYAUTH, OnButtonSortbyauth)
///	ON_BN_CLICKED(IDC_BUTTON_DELETE, OnButtonDelete)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgViewR message handlers

BOOL CDlgViewR::OnInitDialog() 
{
	CDialog::OnInitDialog();

	m_btnOK.SetThemeHelper(&m_ThemeHelper);
	m_btnOK.SetIcon(IDI_ICON_OK);
	m_btnOK.SetTooltipText(_T("退出"));

	m_ctrlBtnSortByUser.SetThemeHelper(&m_ThemeHelper);
	m_ctrlBtnSortByUser.SetIcon(IDI_ICON_LOGIN);
	m_ctrlBtnSortByUser.SetTooltipText(_T("按用户名的首字顺序(英文字母或汉字拼音)排列"));

	m_ctrlBtnSortByAuth.SetThemeHelper(&m_ThemeHelper);
	m_ctrlBtnSortByAuth.SetIcon(IDI_ICON_CUSTOM1);
	m_ctrlBtnSortByAuth.SetTooltipText(_T("按用户操作级别权限排列"));

	m_ctrlBtnDelete.SetThemeHelper(&m_ThemeHelper);
	m_ctrlBtnDelete.SetIcon(IDI_ICON_CANCEL01);
	m_ctrlBtnDelete.SetTooltipText(_T("用鼠标/键盘方向键选择要删除的用户的行后，点击删除按钮"));

///	ConnectDB();//连接数据库

	m_ctrlListTable.InsertColumn(0, _T("用户名"),   LVCFMT_CENTER, 20);
	m_ctrlListTable.InsertColumn(1, _T("密码"),   LVCFMT_RIGHT, 20);
	m_ctrlListTable.InsertColumn(2, _T("权限"), LVCFMT_RIGHT, 20);
	m_ctrlListTable.InsertColumn(3, _T("部门"),   LVCFMT_CENTER, 20);
	m_ctrlListTable.InsertColumn(4, _T("登录时间"),   LVCFMT_RIGHT, 40);
	m_ctrlListTable.InsertColumn(5, _T("注销时间"), LVCFMT_RIGHT, 40);

///	GetDataFromDB();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgViewR::ConnectDB()
{
	try
	{
		m_SQLDirect.Init();
		if(m_SQLDirect.Connect(_T("masterdefine"),_T("kj86"),_T("kj86")))
			AfxMessageBox("AddUser:无法连接用户参数数据库,请确定SQL SERVER服务是否运行!");
	}
	catch(CDBException *e)
	{
		e->ReportError();
		return;
	}

}

void CDlgViewR::OnButtonSortbyuser() 
{
	// TODO: Add your control notification handler code here
	m_bAscending=TRUE;
	m_nSortedCol=0;

	m_flatHeader.SetSortImage (m_nSortedCol, m_bAscending);

			// TODO: Add your sorting code here.
	CXTSortClass csc (&m_ctrlListTable, m_nSortedCol);
	csc.Sort (m_bAscending ? true : false, DT_STRING);

	
}

void CDlgViewR::OnButtonSortbyauth() 
{
	// TODO: Add your control notification handler code here
	m_bAscending=TRUE;
	m_nSortedCol=2;

	m_flatHeader.SetSortImage (m_nSortedCol, m_bAscending);

			// TODO: Add your sorting code here.
	CXTSortClass csc (&m_ctrlListTable, m_nSortedCol);
	csc.Sort (m_bAscending ? true : false, DT_STRING);

	
}

void CDlgViewR::OnButtonDelete() 
{
	// TODO: Add your control notification handler code here
	BOOL bDelete=0;
	int nItemCount=m_ctrlListTable.GetItemCount();
    for(int nItem=0;nItem<nItemCount;nItem++)
	{
		if(m_ctrlListTable.GetItemState(nItem,LVIS_SELECTED) & LVIS_SELECTED)
		{
			CString strtemp,strMessage;
			strtemp=m_ctrlListTable.GetItemText(nItem,0);
			strMessage.Format("您肯定要从用户中删除 %s 吗?",strtemp);
			if(AfxMessageBox(strMessage, MB_ICONQUESTION |MB_OKCANCEL)==IDCANCEL)
				return;
			try
			{
				CString strSQL;
				strSQL.Format("DELETE FROM LOGIN WHERE NAME='%s'",strtemp);
				if(m_SQLDirect.ExecuteSQL(strSQL)==SQL_SUCCESS)
				{
					m_ctrlListTable.DeleteAllItems();
///					GetDataFromDB();
				}
				
			}
			catch(CDBException *e){
			e->ReportError();
			EndWaitCursor();
			return;
			}
			bDelete=1;
		}
	}
	if(!bDelete)
		AfxMessageBox("您还没有选择要删除的用户(提示：用鼠标/键盘方向键选择要删除的行)");
}

void CDlgViewR::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	m_SQLDirect.Close();
	
}

void CDlgViewR::GetDataFromDB()
{
		try
		{
			if( m_SQLDirect.ExecuteSQL("SELECT * FROM LOGIN")==SQL_SUCCESS)
			{
				int nRet=m_SQLDirect.Fetch();
				int iItem=0;
				while(!nRet)
				{
					CString strUser=m_SQLDirect.GetCol(1);
					CString strPwd=m_SQLDirect.GetCol(2);
					CString strDpt=m_SQLDirect.GetCol(3);
					CString strLogin=m_SQLDirect.GetCol(4);
					CString strLogoff=m_SQLDirect.GetCol(5);
					CString strAut=m_SQLDirect.GetCol(6);

					m_ctrlListTable.InsertItem(iItem, strUser, 0);
					m_ctrlListTable.SetItem(iItem, 1, LVIF_TEXT, strPwd, 0, NULL, NULL, NULL);
					m_ctrlListTable.SetItem(iItem, 2, LVIF_TEXT, strAut, 0, NULL, NULL, NULL);
					m_ctrlListTable.SetItem(iItem, 3, LVIF_TEXT, strDpt, 0, NULL, NULL, NULL);
					m_ctrlListTable.SetItem(iItem, 4, LVIF_TEXT, strLogin, 0, NULL, NULL, NULL);
					m_ctrlListTable.SetItem(iItem, 5, LVIF_TEXT, strLogoff, 0, NULL, NULL, NULL);

					nRet=m_SQLDirect.Fetch();
					iItem++;
				}
			}
		}
		catch(CDBException *e){
		e->ReportError();
		EndWaitCursor();
		return;
		}


//			m_ctrlListTable.SetRowColors(RGB(0x33,0x66,0xff), RGB(0xff,0x66,0xff));

	
	// Get the windows handle to the header control for the
	// list control then subclass the control.
	HWND hWndHeader = m_ctrlListTable.GetDlgItem(0)->GetSafeHwnd();
	m_flatHeader.SubclassWindow (hWndHeader);

//	if (m_bSaveColumnWidth)
//		m_ctrlListTable.LoadColumnWidths();

	// size to fit the columns
	m_ctrlListTable.AutoSizeColumn ();
//	m_comboColumn.SetCurSel(3);

	// initialize the back color picker default colors.
	m_cpBack.SetColor(RGB(0x33,0x66,0xff));
	m_cpBack.SetDefaultColor(m_clrRowBack);

	// initialize the text color picker default colors.
	m_cpText.SetColor(RGB(0xff,0xff,0xff));
	m_cpText.SetDefaultColor(m_clrRowText);

	// set the text and back colors for the list control.
	m_ctrlListTable.SetRowColors(m_cpText.GetColor(), m_cpBack.GetColor());

	m_bAscending=TRUE;
	m_nSortedCol=0;

	m_flatHeader.SetSortImage (m_nSortedCol, m_bAscending);

			// TODO: Add your sorting code here.
	CXTSortClass csc (&m_ctrlListTable, m_nSortedCol);
	csc.Sort (m_bAscending ? true : false, DT_STRING);


	// set some extnded styles
	m_ctrlListTable.SetExtendedStyle (LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT|LVS_EX_FLATSB);



}
