// EditWatchPoint.cpp : implementation file
//

#include "stdafx.h"
#include "kjmonitor.h"
#include "EditWatchPoint.h"

#include "MainFrm.h"
#include "FMMonitorPoint.h"
#include "ViewDeleteAddr.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEditWatchPoint dialog


CEditWatchPoint::CEditWatchPoint(CWnd* pParent /*=NULL*/)
	: CDialog(CEditWatchPoint::IDD, pParent)
{
	//{{AFX_DATA_INIT(CEditWatchPoint)
	m_unEditWatchNo = 1;
	m_unEditPointNo = 1;
	m_unEditSeePoint = 1;
	//}}AFX_DATA_INIT
	m_bSearchPoint=FALSE;
}


void CEditWatchPoint::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEditWatchPoint)
	DDX_Control(pDX, IDC_BUTTON_SEEPOINT, m_ctrlBtnSeePoint);
	DDX_Control(pDX, IDC_BUTTON_DELETEWATCHNO, m_ctrlBtnDeleteWatchNo);
	DDX_Control(pDX, IDC_BUTTON_ADDWATCH, m_ctrlBtnAddWatch);
	DDX_Control(pDX, IDC_BUTTON_POINT, m_ctrlBtnPoint);
	DDX_Control(pDX, IDC_COMBO_TRUNK, m_ctrlComboTrunk);
	DDX_Control(pDX, IDC_LISTPOINT, m_ctrlListPoint);
	DDX_Control(pDX, IDC_LISTWATCH, m_ctrlListWatch);
	DDX_Text(pDX, IDC_EDIT_WATCHNO, m_unEditWatchNo);
	DDV_MinMaxUInt(pDX, m_unEditWatchNo, 1, 15000);
	DDX_Text(pDX, IDC_EDIT_POINTNO, m_unEditPointNo);
	DDV_MinMaxUInt(pDX, m_unEditPointNo, 1, 15000);
	DDX_Text(pDX, IDC_EDIT_SEEPOINT, m_unEditSeePoint);
	DDV_MinMaxUInt(pDX, m_unEditSeePoint, 1, 15000);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CEditWatchPoint, CDialog)
	//{{AFX_MSG_MAP(CEditWatchPoint)
	ON_CBN_SELCHANGE(IDC_COMBO_TRUNK, OnSelchangeComboTrunk)
	ON_BN_CLICKED(IDC_BUTTON_POINT, OnButtonPoint)
///	ON_BN_CLICKED(IDC_BUTTON_ADDWATCH, OnButtonAddwatch)
///	ON_BN_CLICKED(IDC_BUTTON_DELETEWATCHNO, OnButtonDeletewatchno)
	ON_BN_CLICKED(IDC_BUTTON_SEEPOINT, OnButtonSeepoint)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEditWatchPoint message handlers

BOOL CEditWatchPoint::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
///	ConnectDB();
	SetBtnStyle();
	SetPointListHead();
	SetWatchPointListHead();
	
	m_ctrlComboTrunk.SetCurSel(0);
//	m_ucOldTrunkNo=0;
	UpdateData(FALSE);
	
///	GetDataFromDBWatch();
///	GetDataFromDBPoint();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}







void CEditWatchPoint::SetWatchPointListHead()
{
	m_ctrlListWatch.InsertColumn(0, _T("监测号"),   LVCFMT_CENTER, 10);
	m_ctrlListWatch.InsertColumn(1, _T("点号 "),   LVCFMT_CENTER, 10);

	m_ctrlListWatch.SetExtendedStyle (LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT|LVS_EX_FLATSB);

	// Get the windows handle to the header control for the
	// list control then subclass the control.
	HWND hWndHeader = m_ctrlListWatch.GetDlgItem(IDC_LISTPOINT)->GetSafeHwnd();
	m_flatHeader.SubclassWindow (hWndHeader);

//	if (m_bSaveColumnWidth)
//		m_ctrlListEditMonitor.LoadColumnWidths();

	// size to fit the columns
	m_ctrlListWatch.AutoSizeColumn ();

	// initialize the back color picker default colors.
	m_cpBack.SetColor(RGB(0x33,0x66,0xff));
	m_cpBack.SetDefaultColor(m_clrRowBack);

	// initialize the text color picker default colors.
	m_cpText.SetColor(RGB(0xff,0xff,0xff));
	m_cpText.SetDefaultColor(m_clrRowText);

	// set the text and back colors for the list control.
	m_ctrlListWatch.SetRowColors(m_cpText.GetColor(), m_cpBack.GetColor());

}

void CEditWatchPoint::SetPointListHead()
{
	m_ctrlListPoint.InsertColumn(0, _T("地址"),   LVCFMT_CENTER, 10);
	m_ctrlListPoint.InsertColumn(1, _T("点号"),   LVCFMT_CENTER, 10);
	m_ctrlListPoint.InsertColumn(2, _T("转接器类型"),LVCFMT_LEFT, 40);
	m_ctrlListPoint.InsertColumn(4, _T("扫描"),   LVCFMT_CENTER, 10);
	m_ctrlListPoint.InsertColumn(5, _T("频率"),   LVCFMT_CENTER, 10);
	// set some extnded styles
	m_ctrlListPoint.SetExtendedStyle (LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT|LVS_EX_FLATSB);

	// Get the windows handle to the header control for the
	// list control then subclass the control.
	HWND hWndHeader = m_ctrlListPoint.GetDlgItem(IDC_LISTWATCH)->GetSafeHwnd();
	m_flatHeader.SubclassWindow (hWndHeader);

//	if (m_bSaveColumnWidth)
//		m_ctrlListSamplePoint.LoadColumnWidths();

	// size to fit the columns
	m_ctrlListPoint.AutoSizeColumn ();

	// initialize the back color picker default colors.
	m_cpBack.SetColor(RGB(0x33,0x66,0xff));
	m_cpBack.SetDefaultColor(m_clrRowBack);

	// initialize the text color picker default colors.
	m_cpText.SetColor(RGB(0xff,0xff,0xff));
	m_cpText.SetDefaultColor(m_clrRowText);

	// set the text and back colors for the list control.
	m_ctrlListPoint.SetRowColors(m_cpText.GetColor(), m_cpBack.GetColor());

	m_bAscending=TRUE;
	m_nSortedCol=0;

	m_flatHeader.SetSortImage (m_nSortedCol, m_bAscending);

			// TODO: Add your sorting code here.
	CXTSortClass csc (&m_ctrlListPoint, m_nSortedCol);
	csc.Sort (m_bAscending ? true : false, DT_INT);
}

void CEditWatchPoint::ConnectDB()
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

void CEditWatchPoint::GetDataFromDBPoint()
{
	CString strSQL;
	CString2DataType Str2Data;
 	try
	{
		if(m_bSearchPoint)
			strSQL.Format("SELECT * FROM uPointProperty WHERE unPointNo = %d",m_unEditSeePoint);
		else
			strSQL.Format("SELECT * FROM uPointProperty WHERE unTrunkNo = %d",m_ctrlComboTrunk.GetCurSel()+1);  //**change subscript
		if( m_SQLDirect.ExecuteSQL(strSQL)==SQL_SUCCESS)
		{
			int nRet=m_SQLDirect.Fetch();
			if(nRet)
			{
				CString strtemp;
				if(m_bSearchPoint)
				{
					strtemp.Format("点 %d 还没有编辑，可用",m_unEditSeePoint);
					m_bSearchPoint=FALSE;
				}
				//else
				//	strtemp=_T("所选干线上还没有编辑点，所有地址均可用");
				//AfxMessageBox(strtemp);
				EndWaitCursor();
				return;
			}
			int iItem=0;
			while(!nRet)
			{
				CString strunPointNo=m_SQLDirect.GetCol(1);
				CString strunTrunkNo=m_SQLDirect.GetCol(2);
				CString strunAddress=m_SQLDirect.GetCol(3);
				CString strunScanFreq=m_SQLDirect.GetCol(4);
				CString strbScan=m_SQLDirect.GetCol(5);
				CString strbValueType=m_SQLDirect.GetCol(6);
				CString strunConnectorID=m_SQLDirect.GetCol(7);
				CString strunSamePointNumber=m_SQLDirect.GetCol(8);
				CString strbMultiConv=m_SQLDirect.GetCol(9);

				//CMainFrame* pFWnd=(CMainFrame*)AfxGetMainWnd();
				//CCommStatusFM *m_pCommStatusFM=pFWnd->m_pCommStatusFM;
				//if(m_pCommStatusFM->ResetTimer())
				CViewDeleteAddr viewdelteaddr;
				CString strunConvIDCH = viewdelteaddr.GetConvName(Str2Data.String2Int(strunConnectorID));
				UpdateData(FALSE);
				if(strbScan=="1")
					strbScan="扫描";
				else
					strbScan="不扫描";
				m_ctrlListPoint.InsertItem(iItem, strunAddress, 0);
				m_ctrlListPoint.SetItem(iItem, 1, LVIF_TEXT, strunPointNo, 0, NULL, NULL, NULL);
				m_ctrlListPoint.SetItem(iItem, 2, LVIF_TEXT, strunConvIDCH, 0, NULL, NULL, NULL);
				//m_ctrlListSamplePoint.SetItem(iItem, 3, LVIF_TEXT, strunConnectorID, 0, NULL, NULL, NULL);
				m_ctrlListPoint.SetItem(iItem, 3, LVIF_TEXT, strbScan, 0, NULL, NULL, NULL);
				m_ctrlListPoint.SetItem(iItem, 4, LVIF_TEXT, strunScanFreq, 0, NULL, NULL, NULL);
			//	m_ctrlListSamplePoint.SetItem(iItem, 5, LVIF_TEXT, strLogoff, 0, NULL, NULL, NULL);
				if(m_bSearchPoint)
					m_ctrlComboTrunk.SetCurSel(Str2Data.String2Int(strunTrunkNo)-1);//**change subscript
				nRet=m_SQLDirect.Fetch();
				iItem++;
			}
		}
		EndWaitCursor();
	}
	catch(CDBException *e){
	e->ReportError();
	m_bSearchPoint=FALSE;
	return;
	}

	// initialize the back color picker default colors.
	m_cpBack.SetColor(RGB(0x33,0x66,0xff));
	m_cpBack.SetDefaultColor(m_clrRowBack);

	// initialize the text color picker default colors.
	m_cpText.SetColor(RGB(0xff,0xff,0xff));
	m_cpText.SetDefaultColor(m_clrRowText);

	// set the text and back colors for the list control.
	m_ctrlListPoint.SetRowColors(m_cpText.GetColor(), m_cpBack.GetColor());

	m_ctrlListPoint.AutoSizeColumn ();
	m_bSearchPoint=FALSE;

}

void CEditWatchPoint::OnSelchangeComboTrunk() 
{
	// TODO: Add your control notification handler code here
//	if(m_ucOldTrunkNo==m_ctrlComboSelectTrunk.GetCurSel()) return;
//	else
	m_ctrlListPoint.DeleteAllItems();
///	GetDataFromDBPoint();
///	m_ucOldTrunkNo=m_ctrlComboTrunk.GetCurSel();
}

void CEditWatchPoint::SetBtnStyle()
{
	m_ctrlBtnAddWatch.SetThemeHelper(&m_ThemeHelper);
	m_ctrlBtnAddWatch.SetIcon(IDI_ICON_ADD);
	m_ctrlBtnAddWatch.SetTooltipText(_T("选用/更改监测号和采样点号，当前显示的监测号为系统可用的最小监测号(可以手工输入更改)，采样点号必须在右表中选择(以保证该点进行过点编辑)，击此加入监测"));

	m_ctrlBtnPoint.SetThemeHelper(&m_ThemeHelper);
	m_ctrlBtnPoint.SetIcon(IDI_ICON_ADD);
	m_ctrlBtnPoint.SetTooltipText(_T("在右表中选中要监测的采样点号，采样点号必须在右表中选择(以保证该点进行过点编辑)，击此确认所选点号"));

	m_ctrlBtnDeleteWatchNo.SetThemeHelper(&m_ThemeHelper);
	m_ctrlBtnDeleteWatchNo.SetIcon(IDI_ICON_ADD1);
	m_ctrlBtnDeleteWatchNo.SetTooltipText(_T("在左表中选中要删除的监测号，击此删除"));

	m_ctrlBtnSeePoint.SetThemeHelper(&m_ThemeHelper);
	m_ctrlBtnSeePoint.SetIcon(IDI_ICON_SEARCH);
	m_ctrlBtnSeePoint.SetTooltipText(_T("快速查找点号信息，请在下面框中输入点号"));
}

void CEditWatchPoint::OnButtonSeepoint() 
{
	// TODO: Add your control notification handler code here
	m_ctrlListPoint.DeleteAllItems(); 
	
	UpdateData(TRUE);
	if((m_unEditSeePoint<=0)||(m_unEditSeePoint>MAX_POINT_NUMBER-1))
	{
		CString strtemp;
		strtemp.Format("点号应定义在1~%d，请重新输入",MAX_POINT_NUMBER-1);
		AfxMessageBox(strtemp);
		return;
	}
	m_bSearchPoint=TRUE;
///	GetDataFromDBPoint();
	
}

void CEditWatchPoint::OnButtonAddwatch()
{
	CMainFrame* pFWnd=(CMainFrame*)AfxGetMainWnd();
	CCommStatusFM *pCommStatusFM=pFWnd->m_pCommStatusFM;
	CFMMonitorPoint *pFMMonitorPoint=pFWnd->m_pFMMonitorPoint;

	UpdateData(TRUE);
	CString strSQL;
	CString2DataType Str2Data;
	if((m_unEditWatchNo<=0)||(m_unEditWatchNo>MAX_POINT_NUMBER-1))   //**change subscript
	{
		CString strtemp;
		strtemp.Format("监测号应定义为1~%d，请重新输入",MAX_POINT_NUMBER-1);//**change subscript
		AfxMessageBox(strtemp);
		return;
	}

 	try
	{
	   int nItemCount=m_ctrlListPoint.GetItemCount();
	//CString2DataType Str2Data;
       for(int nItem=0;nItem<nItemCount;nItem++)
	   {
		if(m_ctrlListPoint.GetItemState(nItem,LVIS_SELECTED) & LVIS_SELECTED)
		{
		CString strEditPointNo = m_ctrlListPoint.GetItemText(nItem,1);
		m_unEditPointNo=(UINT)Str2Data.String2Int(strEditPointNo);
		BOOL bDelete=FALSE, bUpdate=FALSE;
		strSQL.Format("SELECT * FROM uMonitorPointEdit WHERE unPointNo = %d",m_unEditPointNo);
		if( m_SQLDirect.ExecuteSQL(strSQL)==SQL_SUCCESS)
		{
			int nRet=m_SQLDirect.Fetch();
			if(!nRet)
			{
				CString strunMonitorNo=m_SQLDirect.GetCol(1);
				CString strunPointNo=m_SQLDirect.GetCol(2);
				CString strMessage;
				
				UINT     unPointNo1=(UINT)Str2Data.String2Int(strunMonitorNo);   //11/1
				if(unPointNo1==m_unEditWatchNo)//the same Str2Data.String2Int(strunMonitorNo)
				{
					strMessage.Format("监测号 %d 已与采样点 %d 对应",m_unEditWatchNo,m_unEditPointNo);
					AfxMessageBox(strMessage);
					return;
				}
//				strMessage.Format("监测窗号 %s 已与采样点 %s 对应，要继续把监测窗号 %d 已与采样点 %d 对应码？(选择确定，原对应关系将被删除!)",
//					strunMonitorNo,strunPointNo,m_unEditMonitorNo,m_unEditSelectPointNo);
//				if(AfxMessageBox(strMessage, MB_ICONQUESTION |MB_OKCANCEL)==IDOK)
					bDelete=TRUE;
//				else 
//					return;
			}
		}
		if(bDelete)
		{
			strSQL.Format("DELETE FROM uMonitorPointEdit WHERE unPointNo = %d",m_unEditPointNo);
			if( m_SQLDirect.ExecuteSQL(strSQL)==SQL_SUCCESS)
			{
//				AfxMessageBox("原对应关系已被删除!",MB_ICONINFORMATION);
			}
		}
		strSQL.Format("SELECT * FROM uMonitorPointEdit WHERE unMonitorNo = %d",m_unEditWatchNo);
		if( m_SQLDirect.ExecuteSQL(strSQL)==SQL_SUCCESS)
		{
			int nRet=m_SQLDirect.Fetch();
			if(!nRet)
			{
				CString strunMonitorNo=m_SQLDirect.GetCol(1);
				CString strunPointNo=m_SQLDirect.GetCol(2);
				CString strMessage;
//				strMessage.Format("当前监测窗号 %s 已与采样点 %s 对应，要继续把监测窗号 %d 已与采样点 %d 对应码？(选择确定，原对应关系将被删除!)",
//					strunMonitorNo,strunPointNo,m_unEditMonitorNo,m_unEditSelectPointNo);
//				if(AfxMessageBox(strMessage, MB_ICONQUESTION |MB_OKCANCEL)==IDOK)
					bUpdate=TRUE;
//				else
//					return;
			}
		}
		if(bUpdate)
		{
			strSQL.Format("UPDATE uMonitorPointEdit SET unPointNo=%d  WHERE (unMonitorNo = %d)",m_unEditPointNo,m_unEditWatchNo);
			if( m_SQLDirect.ExecuteSQL(strSQL)==SQL_SUCCESS)
			{
//				AfxMessageBox("原对应关系已被删除! 新的对应关系设置成功",MB_ICONINFORMATION);
			}
		}
		else
		{
			strSQL.Format("INSERT INTO uMonitorPointEdit(unMonitorNo, unPointNo,bEdit) VALUES(%d, %d, 1)",
				m_unEditWatchNo, m_unEditPointNo);
			if( m_SQLDirect.ExecuteSQL(strSQL)==SQL_SUCCESS)
			{
				m_unEditWatchNo++;
//				AfxMessageBox("设置成功",MB_ICONINFORMATION);
			}
		}
		}
	   }
	}
	catch(CDBException *e){
	e->ReportError();
	return;
	}
	m_ctrlListWatch.DeleteAllItems();
///	GetDataFromDBWatch();
	if(pCommStatusFM->m_bStartScan)
	{
		pCommStatusFM->StopScan();
		pCommStatusFM->m_bStartScan=TRUE;
		pCommStatusFM->StartScan();
		pFMMonitorPoint->UpdatePointsStatus();
		//for(int i=0;i<MAX_LISTMONITOR_ITEM_NUM;i++)
		//	SetSwitchStatus(i,2);
	}
}

void CEditWatchPoint::OnButtonPoint() 
{
	// TODO: Add your control notification handler code here
	int nItemCount=m_ctrlListPoint.GetItemCount();
	CString2DataType Str2Data;
    for(int nItem=0;nItem<nItemCount;nItem++)
	{
		if(m_ctrlListPoint.GetItemState(nItem,LVIS_SELECTED) & LVIS_SELECTED)
		{
			CString strSelectPointNo;
			strSelectPointNo=m_ctrlListPoint.GetItemText(nItem,1);
			m_unEditPointNo=Str2Data.String2Int(strSelectPointNo);
			UpdateData(FALSE);
		}
	}
}

void CEditWatchPoint::GetDataFromDBWatch()
{
	CString strSQL;
	CString2DataType Str2Data;
 	try
	{
		if(!m_bSearchPoint)
			strSQL="SELECT * FROM uMonitorPointEdit";   //bEdit    
		else
			strSQL.Format("SELECT * FROM uMonitorPointEdit WHERE (unMonitorNo = %d) OR (unPointNo = %d)",m_unEditWatchNo,m_unEditPointNo);
		if( m_SQLDirect.ExecuteSQL(strSQL)==SQL_SUCCESS)
		{
			int nRet=m_SQLDirect.Fetch();
			int iItem=0;
			while(!nRet)
			{
				CString strunMonitorNo=m_SQLDirect.GetCol(1);
				CString strunPointNo=m_SQLDirect.GetCol(2);
				UINT     unPointNo=(UINT)Str2Data.String2Int(strunMonitorNo);
				m_ctrlListWatch.InsertItem(iItem, strunMonitorNo, 0);
				m_ctrlListWatch.SetItem(iItem, 1, LVIF_TEXT, strunPointNo, 0, NULL, NULL, NULL);
				if(m_unEditWatchNo < unPointNo)
					m_unEditWatchNo=unPointNo;
				nRet=m_SQLDirect.Fetch();
				iItem++;
			}
		}
	}
	catch(CDBException *e){
	e->ReportError();
	m_bSearchPoint=FALSE;
	return;
	}
	m_unEditWatchNo++;
	// initialize the back color picker default colors.
	m_cpBack.SetColor(RGB(0x33,0x66,0xff));
	m_cpBack.SetDefaultColor(m_clrRowBack);

	// initialize the text color picker default colors.
	m_cpText.SetColor(RGB(0xff,0xff,0xff));
	m_cpText.SetDefaultColor(m_clrRowText);

	// set the text and back colors for the list control.
	m_ctrlListPoint.SetRowColors(m_cpText.GetColor(), m_cpBack.GetColor());

	m_ctrlListPoint.AutoSizeColumn ();
	m_bSearchPoint=FALSE;
}

void CEditWatchPoint::OnButtonDeletewatchno() 
{
	// TODO: Add your control notification handler code here
	int nItemCount=m_ctrlListWatch.GetItemCount();
///	CString2DataType Str2Data;
	CString strSelectMonitorNo,strSelectPointNo;
	int nItem;
	BOOL bSelect=FALSE;

//    CMainFrame* pFrm=(CMainFrame* )AfxGetMainWnd();
//	CCommStatusFM* pCommStatusFM=pFrm->m_pCommStatusFM;
	CMainFrame* pFWnd=(CMainFrame*)AfxGetMainWnd();
	CCommStatusFM *pCommStatusFM=pFWnd->m_pCommStatusFM;
	CFMMonitorPoint *pFMMonitorPoint=pFWnd->m_pFMMonitorPoint;

    for(nItem=0;nItem<nItemCount;nItem++)
	{
		if(m_ctrlListWatch.GetItemState(nItem,LVIS_SELECTED) & LVIS_SELECTED)
		{
			strSelectMonitorNo=m_ctrlListWatch.GetItemText(nItem,0);
			strSelectPointNo=m_ctrlListWatch.GetItemText(nItem,1);
			bSelect=TRUE;
//			break;
//		}
//	}
//	if(!bSelect)
//	{
//		AfxMessageBox("还没有选择要删除的监测号");
//		return;
//	}
	CString strSQL;
	CString strMessage;
 	try
	{
		strMessage.Format("确实要删除监测号 %s (与采样点 %s 对应)?",strSelectMonitorNo,strSelectPointNo);
		if(AfxMessageBox(strMessage, MB_ICONQUESTION |MB_OKCANCEL)==IDCANCEL)
			return;
		strSQL.Format("DELETE FROM uMonitorPointEdit WHERE unMonitorNo = %s",strSelectMonitorNo);
		if( m_SQLDirect.ExecuteSQL(strSQL)==SQL_SUCCESS)
		{
//			AfxMessageBox("删除成功!",MB_ICONINFORMATION);
		}
	}
	catch(CDBException *e){
	e->ReportError();
	return;
	}
		}
	}
	m_ctrlListWatch.DeleteAllItems();
///	GetDataFromDBWatch();
	if(pCommStatusFM->m_bStartScan)
	{
		pCommStatusFM->StopScan();
		pCommStatusFM->m_bStartScan=TRUE;
		pCommStatusFM->StartScan();
		pFMMonitorPoint->UpdatePointsStatus();
		//for(int i=0;i<MAX_LISTMONITOR_ITEM_NUM;i++)
		//	SetSwitchStatus(i,2);
	}
}

BOOL CEditWatchPoint::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult) 
{
	// TODO: Add your specialized code here and/or call the base class

	HD_NOTIFY *pHDNotify = (HD_NOTIFY*)lParam;

	switch( pHDNotify->hdr.code )
	{
	case HDN_ITEMCLICKA:
	case HDN_ITEMCLICKW:
		{
			// left mouse button.
			if (pHDNotify->iButton == 0)
			{
				if (pHDNotify->iItem == m_nSortedCol) 
				{
					m_bAscending = !m_bAscending;
				}
				else 
				{
					m_bAscending = true;
				}
			}
			// right mouse button.
			else if (pHDNotify->iButton == 1) 	
			{
				m_bAscending = m_flatHeader.GetAscending();
			}
			else 
			{
				break;
			}
			// set sort image for header.
			m_nSortedCol = pHDNotify->iItem;
			m_flatHeader.SetSortImage (m_nSortedCol, m_bAscending);
			// TODO: Add your sorting code here.
			//if(wParam==IDC_LIST_SAMPLEPOINT)
		//	if(wParam==1310)
		//	{
			CXTSortClass csc (&m_ctrlListPoint, m_nSortedCol);
			if((m_nSortedCol==4)||(m_nSortedCol==2))
				csc.Sort (m_bAscending ? true : false, DT_STRING);
			else
				csc.Sort (m_bAscending ? true : false, DT_INT);

			CXTSortClass csc1 (&m_ctrlListWatch, m_nSortedCol);
			csc1.Sort (m_bAscending ? true : false, DT_INT);
		//	}
		}
	}
	return CDialog::OnNotify(wParam, lParam, pResult);
}

void CEditWatchPoint::OnDestroy() 
{
	CDialog::OnDestroy();
	
	m_SQLDirect.Close();
	
}
