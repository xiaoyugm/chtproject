// Edit12ModeDlg.cpp : implementation file
//

#include "stdafx.h"
#include "kjmonitor.h"
#include "Edit12ModeDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEdit12ModeDlg dialog


CEdit12ModeDlg::CEdit12ModeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CEdit12ModeDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CEdit12ModeDlg)
	m_strEditMode1 = _T("");
	m_strEditMode2 = _T("");
	m_unEditNo = 1;
	//}}AFX_DATA_INIT
}


void CEdit12ModeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEdit12ModeDlg)
	DDX_Control(pDX, IDC_BUTTON_SAVESETTING, m_ctrlBtnSavesetting);
	DDX_Control(pDX, IDOK, m_ctrlBtnOK);
	DDX_Control(pDX, IDC_LIST_12MODE, m_ctrlList);
	DDX_Control(pDX, IDC_BUTTON_EDIT, m_ctrlBtnEdit);
	DDX_Text(pDX, IDC_EDIT_MODE1, m_strEditMode1);
	DDX_Text(pDX, IDC_EDIT_MODE2, m_strEditMode2);
	DDX_Text(pDX, IDC_EDIT_NO, m_unEditNo);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CEdit12ModeDlg, CDialog)
	//{{AFX_MSG_MAP(CEdit12ModeDlg)
	ON_BN_CLICKED(IDC_BUTTON_EDIT, OnButtonEdit)
///	ON_BN_CLICKED(IDC_BUTTON_SAVESETTING, OnButtonSavesetting)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEdit12ModeDlg message handlers

void CEdit12ModeDlg::OnButtonEdit() 
{
	// TODO: Add your control notification handler code here
	BOOL bSelect=0;
	int nItemCount=m_ctrlList.GetItemCount();
    for(int nItem=0;nItem<nItemCount;nItem++)
	{
		if(m_ctrlList.GetItemState(nItem,LVIS_SELECTED) & LVIS_SELECTED)
		{
			m_unEditNo=m_String2DataType.String2Int(m_ctrlList.GetItemText(nItem,0)); 
			m_strEditMode1=m_ctrlList.GetItemText(nItem,1);
			m_strEditMode2=m_ctrlList.GetItemText(nItem,2);
			UpdateData(FALSE);
			bSelect=1;
			break;
		}
	}
	if(!bSelect)
		AfxMessageBox("您还没有选择序号(提示：用鼠标/键盘方向键在左表中选择要删除的行)");
	
}

void CEdit12ModeDlg::OnButtonSavesetting() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if((m_unEditNo>MAX_12MODE_NUMBER)||(m_unEditNo<1))
	{
		CString str;
		str.Format("序号必须在 1 ~ %d 之间",MAX_12MODE_NUMBER);
		AfxMessageBox(str);
		return;
	}
	try{
		CString strSQL;
		strSQL.Format("UPDATE uMode12 SET strMode1='%s', strMode2='%s' WHERE (unModeNo = %d)",m_strEditMode1,m_strEditMode2,m_unEditNo);
		if( m_SQLDirect.ExecuteSQL(strSQL)==SQL_SUCCESS)
		{
			m_ctrlList.SetItemText(m_unEditNo-1,1,m_strEditMode1);
			m_ctrlList.SetItemText(m_unEditNo-1,2,m_strEditMode2);
			UpdateData(FALSE);
		}
	}
	catch(CDBException *e){
		e->ReportError();
		EndWaitCursor();
		return ;
	}

	
}

BOOL CEdit12ModeDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_ctrlBtnOK.SetThemeHelper(&m_ThemeHelper);
	m_ctrlBtnOK.SetIcon(IDI_ICON_CANCEL);
	m_ctrlBtnOK.SetTooltipText(_T("!!!注意：退出之前如果没有保存设置，本次设置将不生效"));

	m_ctrlBtnSavesetting.SetThemeHelper(&m_ThemeHelper);
	m_ctrlBtnSavesetting.SetIcon(IDI_ICON_SAVECUSTOM);
	m_ctrlBtnSavesetting.SetTooltipText(_T("将设置的序号号和与之对应的模式字保存"));


	m_ctrlBtnEdit.SetThemeHelper(&m_ThemeHelper);
	m_ctrlBtnEdit.SetIcon(IDI_ICON_ADD1);
	m_ctrlBtnEdit.SetTooltipText(_T("先在左边表中选择要编辑的序号，点击此按钮显示已保存的内容"));

	
///	ConnectDB();
	SetListTableColumnName();
///	SetListTable();

	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CEdit12ModeDlg::ConnectDB()
{
	try
	{
		m_SQLDirect.Init();
		if(m_SQLDirect.Connect(_T("masterdefine"),_T("kj86"),_T("kj86")))
			AfxMessageBox("无法连接用户参数数据库,请确定SQL SERVER服务是否运行!");
	}
	catch(CDBException *e)
	{
		e->ReportError();
		return;
	}
}

void CEdit12ModeDlg::SetListTableColumnName()
{

	m_ctrlList.InsertColumn(0, _T("序号"),   LVCFMT_CENTER, 30);
	m_ctrlList.InsertColumn(1, _T("模式字1"),   LVCFMT_CENTER, 50);
	m_ctrlList.InsertColumn(2, _T("模式字2"),   LVCFMT_CENTER, 50);
	// set some extnded styles
	m_ctrlList.SetExtendedStyle (LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT|LVS_EX_FLATSB);

	// Get the windows handle to the header control for the
	// list control then subclass the control.
	HWND hWndHeader = m_ctrlList.GetDlgItem(0)->GetSafeHwnd();
	m_flatHeader.SubclassWindow (hWndHeader);

//	if (m_bSaveColumnWidth)
//		m_ctrlList.LoadColumnWidths();

	// size to fit the columns
	m_ctrlList.AutoSizeColumn ();

	// initialize the back color picker default colors.
	m_cpBack.SetColor(RGB(0x33,0x66,0xff));
	m_cpBack.SetDefaultColor(m_clrRowBack);

	// initialize the text color picker default colors.
	m_cpText.SetColor(RGB(0xff,0xff,0xff));
	m_cpText.SetDefaultColor(m_clrRowText);

	// set the text and back colors for the list control.
	m_ctrlList.SetRowColors(m_cpText.GetColor(), m_cpBack.GetColor());

	m_bAscending=TRUE;
	m_nSortedCol=0;

	m_flatHeader.SetSortImage (m_nSortedCol, m_bAscending);

			// TODO: Add your sorting code here.
	CXTSortClass csc (&m_ctrlList, m_nSortedCol);
	csc.Sort (m_bAscending ? true : false, DT_STRING);

}

void CEdit12ModeDlg::SetListTable()
{
	try{
		if( m_SQLDirect.ExecuteSQL(_T("SELECT * FROM uMode12"))==SQL_SUCCESS)
		{
			for(UINT i=0;i<MAX_12MODE_NUMBER;i++)
			{
				m_SQLDirect.Fetch();
				CString strModeNo=m_SQLDirect.GetCol(1);
				CString strMode1=m_SQLDirect.GetCol(2);
				CString strMode2=m_SQLDirect.GetCol(3);
				m_ctrlList.InsertItem(i,strModeNo,0);
				m_ctrlList.SetItem(i, 1, LVIF_TEXT, strMode1, 0, NULL, NULL, NULL);
				m_ctrlList.SetItem(i, 2, LVIF_TEXT, strMode2, 0, NULL, NULL, NULL);
			} 
		}
	}
	catch(CDBException *e){
		e->ReportError();
		EndWaitCursor();
		return ;
	}

}

void CEdit12ModeDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	m_SQLDirect.Close();
	
}
