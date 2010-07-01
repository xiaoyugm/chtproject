// WarnCauseEditDlg.cpp : implementation file
//

#include "stdafx.h"
#include "kjmonitor.h"
#include "WarnCauseEditDlg.h"

///#include "SQL\\String2DataType.h"
///#include "MainFrm.h"
///#include "CommStatusFM.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWarnCauseEditDlg dialog


CWarnCauseEditDlg::CWarnCauseEditDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWarnCauseEditDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CWarnCauseEditDlg)
	m_strWarnCause = _T("");
	m_unEditWarnclassNO = 1;
	//}}AFX_DATA_INIT
	m_bPlaySound=FALSE;
	m_bGifLoad=FALSE;
}


void CWarnCauseEditDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWarnCauseEditDlg)
	DDX_Control(pDX, IDC_STATIC_GIF, m_GifPic);
	DDX_Control(pDX, IDC_BUTTON_ADDEDITANDGOON, m_ctrlBtnAddEditAndGoOn);
	DDX_Control(pDX, IDC_LIST1, m_ctrlList);
	DDX_Control(pDX, IDC_BUTTON_TEST, m_ctrlBtnTest);
	DDX_Control(pDX, IDCANCEL, m_btnCANCEL);
	DDX_Text(pDX, IDC_EDIT_WARNCAUSE, m_strWarnCause);
	DDX_Text(pDX, IDC_EDIT_WARNCLASSNO, m_unEditWarnclassNO);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CWarnCauseEditDlg, CDialog)
	//{{AFX_MSG_MAP(CWarnCauseEditDlg)
	ON_BN_CLICKED(IDC_BUTTON_TEST, OnButtonTest)
	ON_WM_DESTROY()
///	ON_BN_CLICKED(IDC_BUTTON_ADDEDITANDGOON, OnButtonAddeditandgoon)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, OnDblclkList1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWarnCauseEditDlg message handlers

BOOL CWarnCauseEditDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	
	// TODO: Add extra initialization here
	//m_btnOK.SetThemeHelper(&m_ThemeHelper);
	//m_btnOK.SetIcon(IDI_ICON_OK);
	//m_btnOK.SetTooltipText(_T("确定当前编辑操作，并将结果加入到报警原因数据库文件中，然后退出"));

	m_btnCANCEL.SetThemeHelper(&m_ThemeHelper);
	m_btnCANCEL.SetIcon(IDI_ICON_CANCEL,IDI_ICON_CANCEL01);
	m_btnCANCEL.SetTooltipText(_T("退出编辑器"));

	m_ctrlBtnAddEditAndGoOn.SetThemeHelper(&m_ThemeHelper);
	m_ctrlBtnAddEditAndGoOn.SetIcon(IDI_ICON_OK);
	m_ctrlBtnAddEditAndGoOn.SetTooltipText(_T("将到报警原因文字保存到数据库文件中"));
 
	m_ctrlBtnTest.SetThemeHelper(&m_ThemeHelper);
	m_ctrlBtnTest.SetIcon(IDI_ICON_SOUND);
	m_ctrlBtnTest.SetTooltipText(_T("测试当前报警类声音"));

//	m_ctrlBtnAddEditAndGoOn.SetThemeHelper(&m_ThemeHelper);
//	m_ctrlBtnAddEditAndGoOn.SetIcon(IDI_ICON_OK);
//	m_ctrlBtnAddEditAndGoOn.SetTooltipText(_T("确定所有编辑操作，将结果加入到报警原因数据库文件中，继续编辑下一个传感器"));
	if (m_GifPic.Load(MAKEINTRESOURCE(IDR_GIF_SOUNDPLAY),_T("Gif")))
		m_bGifLoad=TRUE;

///	ConnectDB();

	SetListTableColumnName();
///	SetListTable();

	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

CString CWarnCauseEditDlg::GetAppPath()
{
	CString sModFileName;
	CString str1;
	GetModuleFileName(NULL, sModFileName.GetBuffer(MAX_PATH), MAX_PATH);
	sModFileName.ReleaseBuffer();
	str1=sModFileName;
	str1.MakeReverse();
	return(sModFileName.Left(sModFileName.GetLength() - str1.Find('\\')));

}

void CWarnCauseEditDlg::OnButtonTest() 
{
	// TODO: Add your control notification handler code here
	m_bPlaySound=!m_bPlaySound;
	if(m_bPlaySound)
	{
		UpdateData(TRUE);
		CString str1;
		str1=GetAppPath();
		str1+="sound\\";
		//CreateDirectory( str1, NULL );
		if(!SetCurrentDirectory(str1))
			AfxMessageBox("设置报警声音文件夹失败 setcurrentdirectory");
		
		m_ctrlBtnTest.SetThemeHelper(&m_ThemeHelper);
		m_ctrlBtnTest.SetIcon(IDI_ICON_STOP1);
		m_ctrlBtnTest.SetTooltipText(_T("停止测试声音"));
		m_ctrlBtnTest.SetWindowText("停止测试声音");

		CString strFileName;
		strFileName.Format("warnsound%d.wav",m_unEditWarnclassNO);
		if(m_bGifLoad)
			m_GifPic.Draw();
        sndPlaySound(strFileName,SND_ASYNC);	

	}
	else
	{
		m_ctrlBtnTest.SetThemeHelper(&m_ThemeHelper);
		m_ctrlBtnTest.SetIcon(IDI_ICON_START);
		m_ctrlBtnTest.SetTooltipText(_T("开始测试声音"));
		m_ctrlBtnTest.SetWindowText("开始测试声音");
//		StopPlayingFromFile();
		if(m_bGifLoad)
			m_GifPic.Stop();
	}
}

void CWarnCauseEditDlg::ConnectDB()
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

void CWarnCauseEditDlg::SetListTableColumnName()
{

	m_ctrlList.InsertColumn(0, _T("序号"),   LVCFMT_CENTER, 36);
	m_ctrlList.InsertColumn(1, _T("    报警原因文字描述"),   LVCFMT_LEFT, 160);
	// set some extnded styles
	m_ctrlList.SetExtendedStyle (LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT|LVS_EX_FLATSB);

	// Get the windows handle to the header control for the
	// list control then subclass the control.
	HWND hWndHeader = m_ctrlList.GetDlgItem(0)->GetSafeHwnd();
	m_flatHeader.SubclassWindow (hWndHeader);

//	if (m_bSaveColumnWidth)
//		m_ctrlList.LoadColumnWidths();

	// size to fit the columns
	//m_ctrlList.AutoSizeColumn ();

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
	csc.Sort (m_bAscending ? true : false, DT_INT);

}

void CWarnCauseEditDlg::SetListTable()
{
	try{
		for(UINT i=0;i<MAX_WARNCLASS_NUMBER;i++)
		{
            CString	strSQL;
	    	strSQL.Format("SELECT * FROM uWarnClass WHERE unWarnClassNo = %d",i+1);
            if(m_SQLDirect.ExecuteSQL(strSQL) == SQL_SUCCESS)
			{
				if(!m_SQLDirect.Fetch()){
		         		CString strWarnClassNo=m_SQLDirect.GetCol(1);
		        		CString strWarnCause=m_SQLDirect.GetCol(2);
			        	m_ctrlList.InsertItem(i,strWarnClassNo,0);
		        		m_ctrlList.SetItem(i, 1, LVIF_TEXT, strWarnCause, 0, NULL, NULL, NULL);
				}
			}
			else
			       AfxMessageBox("数据库表uWarnClass查询失败");
		}
	}
	catch(CDBException *e){
		e->ReportError();
		EndWaitCursor();
		return ;
	}

}



void CWarnCauseEditDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	m_SQLDirect.Close();
	
}

void CWarnCauseEditDlg::OnButtonAddeditandgoon() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if((m_unEditWarnclassNO<1)||(m_unEditWarnclassNO>MAX_WARNCLASS_NUMBER))
	{
		CString strtemp;
		strtemp.Format("报警类编号不能超过 %d ",MAX_WARNCLASS_NUMBER);
		AfxMessageBox(strtemp);
		return;
	}
	if(m_strWarnCause.GetLength()>24)
	{
		AfxMessageBox("报警原因不能超过 12 个汉字(或 24 个字母)");
		return;
	}
	if(m_strWarnCause.IsEmpty())
		m_strWarnCause="未定义";
	try{
		CString strSQL;
		strSQL.Format("UPDATE uWarnClass SET strWarnCause='%s' WHERE unWarnClassNo=%d",m_strWarnCause,m_unEditWarnclassNO);

		if( m_SQLDirect.ExecuteSQL(strSQL)==SQL_SUCCESS)
		{
			m_ctrlList.SetItem(m_unEditWarnclassNO-1, 1, LVIF_TEXT, m_strWarnCause, 0, NULL, NULL, NULL);
		}
	}
	catch(CDBException *e){
		e->ReportError();
		EndWaitCursor();
		return ;
	}

	
}

void CWarnCauseEditDlg::OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	CString2DataType String2Data;
	CString strWarnCauseNo;
	int nItemCount=m_ctrlList.GetItemCount();
    for(int nItem=0;nItem<nItemCount;nItem++)
	{
		if(m_ctrlList.GetItemState(nItem,LVIS_SELECTED) & LVIS_SELECTED)
		{
			strWarnCauseNo=m_ctrlList.GetItemText(nItem,0);
			m_strWarnCause=m_ctrlList.GetItemText(nItem,1);
			m_unEditWarnclassNO=String2Data.String2Int(strWarnCauseNo);
			UpdateData(FALSE);
		}
	}
	
	*pResult = 0;
}
