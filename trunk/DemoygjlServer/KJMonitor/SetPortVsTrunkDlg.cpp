// SetPortVsTrunkDlg.cpp : implementation file
//

#include "stdafx.h"
#include "kjmonitor.h"
#include "SetPortVsTrunkDlg.h"
#include "CommStatusFM.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CSetPortVsTrunkDlg dialog

CSetPortVsTrunkDlg::CSetPortVsTrunkDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSetPortVsTrunkDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSetPortVsTrunkDlg)
	m_unEditTrunkNo = 1;
	m_unEditPortNo = 0;
	//}}AFX_DATA_INIT
//	m_unPortSelectStatus=0;
}


void CSetPortVsTrunkDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSetPortVsTrunkDlg)
	DDX_Control(pDX, IDC_BUTTON_TESTPORT, m_ctrlBtnTestPort);
	DDX_Control(pDX, IDC_BUTTON_EDIT, m_ctrlBtnEdit);
	DDX_Control(pDX, IDOK, m_btnOK);
	DDX_Control(pDX, IDC_BUTTON_SAVESETTING, m_ctrlBtnSaveSetting);
	DDX_Control(pDX, IDC_LIST_TRUNKVSPORTTABLE, m_ctrlList);
	DDX_Text(pDX, IDC_EDIT_TRUNKNO, m_unEditTrunkNo);
	DDX_Text(pDX, IDC_EDIT_PORTNO, m_unEditPortNo);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSetPortVsTrunkDlg, CDialog)
	//{{AFX_MSG_MAP(CSetPortVsTrunkDlg)
	ON_WM_DESTROY()
///	ON_BN_CLICKED(IDC_BUTTON_SAVESETTING, OnButtonSavesetting)
	ON_BN_CLICKED(IDC_BUTTON_EDIT, OnButtonEdit)
	ON_BN_CLICKED(IDC_BUTTON_TESTPORT, OnButtonTestport)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSetPortVsTrunkDlg message handlers

BOOL CSetPortVsTrunkDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	m_btnOK.SetThemeHelper(&m_ThemeHelper);
	m_btnOK.SetIcon(IDI_ICON_OK);
	m_btnOK.SetTooltipText(_T("!!!注意：退出之前如果没有保存设置，本次设置将不生效"));

	m_ctrlBtnSaveSetting.SetThemeHelper(&m_ThemeHelper);
	m_ctrlBtnSaveSetting.SetIcon(IDI_ICON_SAVECUSTOM);
	m_ctrlBtnSaveSetting.SetTooltipText(_T("将设置的干线号和与之对应的串口号保存进参数表"));


	m_ctrlBtnEdit.SetThemeHelper(&m_ThemeHelper);
	m_ctrlBtnEdit.SetIcon(IDI_ICON_ADD1);
	m_ctrlBtnEdit.SetTooltipText(_T("先在左边表中选择干线，点击此按钮显示干线号对应的串口号"));

	m_ctrlBtnTestPort.SetThemeHelper(&m_ThemeHelper);
	m_ctrlBtnTestPort.SetIcon(IDI_ICON_HELP);
	m_ctrlBtnTestPort.SetTooltipText(_T("点击此按钮测试左边显示的串口在主机上是否正常"));

	BOOL bConnectDB=1;
///	ConnectDB();
	//m_unPortSelectStatus=3;
//	SetPortSelectCheck(m_unPortSelectStatus);
    //Set Listtable
	SetListTableColumnName();
///	SetListTable();
	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CSetPortVsTrunkDlg::SetListTable()
{


	try{

		//get the serail no
		if( m_SQLDirect.ExecuteSQL(_T("SELECT * FROM trunkvsport"))==SQL_SUCCESS)
		{
			for(UINT i=0;i<MAX_TRUNK_NUMBER;i++)
			{
				m_SQLDirect.Fetch();
				CString strComTrunkNo="干线";
				strComTrunkNo+=m_SQLDirect.GetCol(1);
				m_ctrlList.InsertItem(i,strComTrunkNo,0);
				strComTrunkNo="COM";
				strComTrunkNo+=m_SQLDirect.GetCol(2);
				m_ctrlList.SetItem(i, 1, LVIF_TEXT, strComTrunkNo, 0, NULL, NULL, NULL);
				if(m_SQLDirect.GetCol(3)=="1")
					strComTrunkNo="●使用";//··□□◇
				else
					strComTrunkNo="不使用";
				m_ctrlList.SetItem(i, 2, LVIF_TEXT, strComTrunkNo, 0, NULL, NULL, NULL);
			} 
		}
	}
	catch(CDBException *e){
		e->ReportError();
		EndWaitCursor();
		return ;
	}
}

void CSetPortVsTrunkDlg::SetListTableColumnName()
{

	m_ctrlList.InsertColumn(0, _T("干线号"),   LVCFMT_CENTER, 30);
	m_ctrlList.InsertColumn(1, _T("串口号"),   LVCFMT_CENTER, 30);
	m_ctrlList.InsertColumn(2, _T("干线状态"),   LVCFMT_CENTER, 40);
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



void CSetPortVsTrunkDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	m_SQLDirect.Close();
}

void CSetPortVsTrunkDlg::ConnectDB()
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


void CSetPortVsTrunkDlg::OnButtonSavesetting() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if((m_unEditTrunkNo<=0)||(m_unEditTrunkNo>MAX_TRUNK_NUMBER))
	{
		CString strtemp;
		strtemp.Format("干线号必须为1~%d",MAX_TRUNK_NUMBER);
		AfxMessageBox(strtemp);
		return;
	}
	try{
	//get trunk number
		CString strSQL,strPortNo,strstatus;
		UINT unbstatus;
		if(!m_unEditPortNo)
		{
			unbstatus=0;
			strstatus="不使用";//◎··●□□◇
		}
		else
		{
			unbstatus=1;
			strstatus="●使用";
		}
		strSQL.Format("UPDATE trunkvsport SET unPortNO=%d, bPortStatus=%d  WHERE (unTrunkNO = %d)",m_unEditPortNo,unbstatus,m_unEditTrunkNo);
		strPortNo=m_String2DataType.Int2CString(m_unEditPortNo);
		m_SQLDirect.ExecuteSQL(strSQL);
		strPortNo=_T("COM")+strPortNo;
		m_ctrlList.SetItemText(m_unEditTrunkNo-1,1,strPortNo);
		m_ctrlList.SetItemText(m_unEditTrunkNo-1,2,strstatus);

	}
	catch(CDBException *e){
	e->ReportError();
	EndWaitCursor();
	return ;
	}
}


void CSetPortVsTrunkDlg::OnButtonEdit() 
{
	BOOL bSelect=0;
	int nItemCount=m_ctrlList.GetItemCount();
    for(int nItem=0;nItem<nItemCount;nItem++)
	{
		if(m_ctrlList.GetItemState(nItem,LVIS_SELECTED) & LVIS_SELECTED)
		{
			m_unEditTrunkNo=nItem+1; 
			CString strtemp=m_ctrlList.GetItemText(nItem,1);
			strtemp.Replace("COM",NULL);
		//	AfxMessageBox(strtemp);
			m_unEditPortNo=m_String2DataType.String2Int(strtemp);
			UpdateData(FALSE);
			bSelect=1;
			break;
		}
	}
	if(!bSelect)
		AfxMessageBox("您还没有选择要干线(提示：用鼠标/键盘方向键选择要删除的行)");
}

void CSetPortVsTrunkDlg::OnButtonTestport() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if(!m_unEditPortNo)
	{
		AfxMessageBox("串口号不能为零(COM0),请重新输入串口号");
		return;
	}
	CMainFrame* pFWnd=(CMainFrame*)AfxGetMainWnd();
	CCommStatusFM *m_pCommStatusFM=pFWnd->m_pCommStatusFM;
	m_pCommStatusFM->TestSerailPort(m_unEditPortNo);
}

