// CtrlCmdDlg.cpp : implementation file
//

#include "stdafx.h"
#include "kjmonitor.h"
#include "CtrlCmdDlg.h"

#include "SQL\\String2DataType.h"

#include "ViewDeleteAddr.h"

#include "CommStatusFM.h"
#include "MainFrm.h"

//#include "CSpreadSheet.h"  //test

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCtrlCmdDlg dialog
extern NSEQ FAR 	SSeq[201];       //时序号,运行结构             //需要
extern BOOL StartSequence;
extern structValueState m_structValueState[MAX_POINT_NUMBER];

CCtrlCmdDlg::CCtrlCmdDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCtrlCmdDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCtrlCmdDlg)
	m_unDelayTimerD = 8;
	//}}AFX_DATA_INIT
//	m_usCtrlPointNum=0;
}


void CCtrlCmdDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCtrlCmdDlg)
	DDX_Control(pDX, IDC_BUTTON_OFF, m_ctrlBtnOff);
	DDX_Control(pDX, IDC_BUTTON_OPEN, m_ctrlBtnOpen);
	DDX_Control(pDX, IDC_BUTTON_REVERSE, m_ctrlBtnReverse);
	DDX_Control(pDX, IDC_COMBO_TRUNKNO, m_ctrlComboTrunkNO);
	DDX_Control(pDX, IDOK, m_ctrlBtnOK);
	DDX_Control(pDX, IDC_LIST_SELECTPOINT, m_ctrlListSelectPoint);
	DDX_Control(pDX, IDC_LIST_ALLPOINT, m_ctrlListAllPoint);
	DDX_Control(pDX, IDC_BUTTON_SELECTALL, m_ctrlBtnSelectALL);
	DDX_Control(pDX, IDC_BUTTON_SELECT, m_ctrlBtnSelect);
	DDX_Control(pDX, IDC_BUTTON_DESELECTALL, m_ctrlBtnDeselectAll);
	DDX_Control(pDX, IDC_BUTTON_DESELECT, m_ctrlBtnDeselect);
	DDX_Control(pDX, IDC_LISTBOX_COMINFO, m_ctrlListBoxCommInfo);
	DDX_Text(pDX, IDC_EDITDELAYB, m_unDelayTimerD);
	DDV_MinMaxUInt(pDX, m_unDelayTimerD, 1, 60);
	//}}AFX_DATA_MAP
}
//DDX_Control(pDX, IDC_LISTBOX_COMINFO, m_ctrlListBoxCommInfo);

BEGIN_MESSAGE_MAP(CCtrlCmdDlg, CDialog)
	//{{AFX_MSG_MAP(CCtrlCmdDlg)
	ON_BN_CLICKED(IDC_BUTTON_SELECT, OnButtonSelect)
	ON_BN_CLICKED(IDC_BUTTON_DESELECT, OnButtonDeselect)
	ON_BN_CLICKED(IDC_BUTTON_SELECTALL, OnButtonSelectall)
	ON_BN_CLICKED(IDC_BUTTON_DESELECTALL, OnButtonDeselectall)
	ON_CBN_SELCHANGE(IDC_COMBO_TRUNKNO, OnSelchangeComboTrunkno)
	ON_WM_DESTROY()
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_ALLPOINT, OnDblclkListAllpoint)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_SELECTPOINT, OnDblclkListSelectpoint)
	ON_BN_CLICKED(IDC_BUTTON_REVERSE, OnButtonReverse)
	ON_BN_CLICKED(IDC_BUTTON_OPEN, OnButtonOpen)
	ON_BN_CLICKED(IDC_BUTTON_OFF, OnButtonOff)
//	ON_BN_CLICKED(IDC_BUTTON_VIEWPORT, OnButtonViewport)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCtrlCmdDlg message handlers

BOOL CCtrlCmdDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	//m_ctrlListBoxCommInfo.SubclassDlgItem(IDC_LISTBOX_COMINFO, this); // IDC_LISTBOX_COMINFO is the ListBox's resource ID

	// TODO: Add extra initialization here

	m_ctrlBtnOK.SetThemeHelper(&m_ThemeHelper);
	m_ctrlBtnOK.SetIcon(IDI_ICON_EXIT);
	m_ctrlBtnOK.SetTooltipText(_T("退出"));
	m_ctrlBtnOK.SetColor(0,RGB(255,000,000),TRUE);
	m_ctrlBtnOK.SetColor(1,RGB(255,255,255),TRUE);

	m_ctrlBtnSelectALL.SetThemeHelper(&m_ThemeHelper);
	m_ctrlBtnSelectALL.SetIcon(IDI_ICON_ADD1);
	m_ctrlBtnSelectALL.SetTooltipText(_T("将左表中所有点全部加入"));
	m_ctrlBtnSelectALL.SetColor(0,RGB(000,255,000),TRUE);
	m_ctrlBtnSelectALL.SetColor(1,RGB(255,255,255),TRUE);

	m_ctrlBtnSelect.SetThemeHelper(&m_ThemeHelper);
	m_ctrlBtnSelect.SetIcon(IDI_ICON_ADDSINGLE);
	m_ctrlBtnSelect.SetTooltipText(_T("先在左表中选择点所在行，再点击加入，双击点所在行也可加入"));
	m_ctrlBtnSelect.SetColor(0,RGB(000,153,000),TRUE);
	m_ctrlBtnSelect.SetColor(1,RGB(255,255,255),TRUE);
	
	m_ctrlBtnViewPort.SetThemeHelper(&m_ThemeHelper);
	m_ctrlBtnViewPort.SetIcon(IDI_ICON_SEARCH);
	m_ctrlBtnViewPort.SetTooltipText(_T("查看和设置干线与串口的对应关系，并可测试所选串口是否存在"));

	m_ctrlBtnDeselectAll.SetThemeHelper(&m_ThemeHelper);
	m_ctrlBtnDeselectAll.SetIcon(IDI_ICON_ADDDESELECT);
	m_ctrlBtnDeselectAll.SetTooltipText(_T("将右表中所有点均删除"));
	m_ctrlBtnDeselectAll.SetColor(0,RGB(255,000,000),TRUE);
	m_ctrlBtnDeselectAll.SetColor(1,RGB(255,255,255),TRUE);

	m_ctrlBtnDeselect.SetThemeHelper(&m_ThemeHelper);
	m_ctrlBtnDeselect.SetIcon(IDI_ICON_ADDDESELECT1);
	m_ctrlBtnDeselect.SetTooltipText(_T("先在右表中选择点所在行，再点击删除，双击点所在行也可删除"));
	m_ctrlBtnDeselect.SetColor(0,RGB(255,051,051),TRUE);
	m_ctrlBtnDeselect.SetColor(1,RGB(255,255,255),TRUE);

	m_ctrlBtnReverse.SetThemeHelper(&m_ThemeHelper);
	m_ctrlBtnReverse.SetIcon(IDI_ICON_RECYCLERED,IDI_ICON_RECYCLEGREEN);
	m_ctrlBtnReverse.SetTooltipText(_T("请先选择要控制的点，再将状态翻转，1<-->0"));

	m_ctrlBtnOpen.SetThemeHelper(&m_ThemeHelper);
	m_ctrlBtnOpen.SetIcon(IDI_ICON_CLOSE1);
	m_ctrlBtnOpen.SetTooltipText(_T("请先选择要控制的点，然后接通—给电"));

	m_ctrlBtnOff.SetThemeHelper(&m_ThemeHelper);
	m_ctrlBtnOff.SetIcon(IDI_ICON_OPEN1);
	m_ctrlBtnOff.SetTooltipText(_T("请先选择要控制的点，再断电"));

    m_ctrlListBoxCommInfo.AddString("OK",RGB(000,102,000));

	m_ctrlComboTrunkNO.SetCurSel(8);

///	ConnectDB();
	
	SetDBListHead();
	SetCtrlListHead();

///	SetDBListContent();

    m_ctrlListBoxCommInfo.AddString("在右侧列表框请用鼠标左键结合Ctrl键/Shift键选择要控制的点，然后点击控制键");
	m_ctrlListBoxCommInfo.SetCurSel(m_ctrlListBoxCommInfo.GetCount()-1);
//	m_ctrlListBoxCommInfo.AddString("这里显示的是测试信息");
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CCtrlCmdDlg::ConnectDB()
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

void CCtrlCmdDlg::SetDBListHead()
{
	m_ctrlListAllPoint.InsertColumn(0, _T("点号"),   LVCFMT_CENTER, 40);
	m_ctrlListAllPoint.InsertColumn(1, _T("地址"),   LVCFMT_CENTER, 40);
	m_ctrlListAllPoint.InsertColumn(2, _T("干线"),   LVCFMT_CENTER, 40);
	m_ctrlListAllPoint.InsertColumn(3, _T("通道"),   LVCFMT_CENTER, 40);
	m_ctrlListAllPoint.InsertColumn(4, _T("说明"),   LVCFMT_CENTER,120);
	// set some extnded styles
	m_ctrlListAllPoint.SetExtendedStyle (LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT|LVS_EX_FLATSB);

	// Get the windows handle to the header control for the
	// list control then subclass the control.
	//HWND hWndHeader = m_ctrlListAllPoint.GetDlgItem(0)->GetSafeHwnd();

	HWND hWndHeader = m_ctrlListAllPoint.GetDlgItem(IDC_LIST_ALLPOINT)->GetSafeHwnd();
	m_flatHeader.SubclassWindow (hWndHeader);

//	if (m_bSaveColumnWidth)
//		m_ctrlList.LoadColumnWidths();

	// size to fit the columns
	//m_ctrlListAllPoint.AutoSizeColumn ();

	// initialize the back color picker default colors.
	m_cpBack.SetColor(RGB(0x33,0x66,0xff));
	m_cpBack.SetDefaultColor(m_clrRowBack);

	// initialize the text color picker default colors.
	m_cpText.SetColor(RGB(0xff,0xff,0xff));
	m_cpText.SetDefaultColor(m_clrRowText);

	// set the text and back colors for the list control.
	m_ctrlListAllPoint.SetRowColors(m_cpText.GetColor(), m_cpBack.GetColor());

	m_bAscending=TRUE;
	m_nSortedCol=0;

	m_flatHeader.SetSortImage (m_nSortedCol, m_bAscending);

			// TODO: Add your sorting code here.
	CXTSortClass csc (&m_ctrlListAllPoint, m_nSortedCol);
	csc.Sort (m_bAscending ? true : false, DT_STRING);

}
/*
static UINT arIcons[] =
{
	IDI_ICON_STOP,    
	IDI_ICON_STOP1,     
	IDI_ICON_SEARCH    
};
*/
// o-o     o o
void CCtrlCmdDlg::SetCtrlListHead()
{
		// Create the image list used by the LISTCTRL to disp switch status control.IDB_BITMAP_STATUS
/*	if (!m_imageList.Create(IDB_IMGLIST_TAB, 16, 1, RGB( 0x00,0xFF,0x00 )))
	{
		AfxMessageBox("Failed to create image list. in CCtrlCmdDlg::OnInitDialog()");
		return ;
	}
	*/
/*	if (!m_imageList.Create (16, 16, ILC_MASK | ILC_COLOR16, 2, 1))
	{
		AfxMessageBox("Failed to create image list. in CCtrlCmdDlg::SetCtrlListHead()");
		return ;
	}
*/		

		// Add icons to the large and small image lists.
//	for (int i = 0; i < _countof(arIcons); ++i)
//	{
		//HICON hIcon = AfxGetApp()->LoadIcon(arIcons[i]);
//		ASSERT (hIcon != NULL);

	//	HICON hIcon = AfxGetApp()->LoadIcon(IDI_ICON_SEARCH);
		//m_imageList.DeleteImageList();
	//	m_imageList.Add (hIcon);
	//}

	//m_ilSmallIcons.;


//	m_ctrlListSelectPoint.SetImageList(&m_imageList,OBS_XT_SMALLICON);
	//m_ctrlListSelectPoint.SetImageList(&m_imageList,LVSIL_SMALL);

	m_ctrlListSelectPoint.InsertColumn(0, _T("点号"),   LVCFMT_CENTER, 40);
	m_ctrlListSelectPoint.InsertColumn(1, _T(" 说    明 "),   LVCFMT_CENTER, 100);
	m_ctrlListSelectPoint.InsertColumn(2, _T(" 工作状态 "),   LVCFMT_CENTER, 100);
	m_ctrlListSelectPoint.InsertColumn(3, _T("通信状态"),   LVCFMT_CENTER, 60);   // o-o     o o
	// set some extnded styles
	m_ctrlListSelectPoint.SetExtendedStyle (LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT|LVS_EX_FLATSB);

	// Get the windows handle to the header control for the
	// list control then subclass the control.
	//HWND hWndHeader = m_ctrlListSelectPoint.GetDlgItem(0)->GetSafeHwnd();

	HWND hWndHeader = m_ctrlListSelectPoint.GetDlgItem(IDC_LIST_SELECTPOINT)->GetSafeHwnd();
	m_flatHeader.SubclassWindow (hWndHeader);

//	if (m_bSaveColumnWidth)
//		m_ctrlList.LoadColumnWidths();

	// size to fit the columns
	//m_ctrlListSelectPoint.AutoSizeColumn ();

	// initialize the back color picker default colors.
	m_cpBack.SetColor(RGB(0x33,0x66,0xff));
	m_cpBack.SetDefaultColor(m_clrRowBack);

	// initialize the text color picker default colors.
	m_cpText.SetColor(RGB(0xff,0xff,0xff));
	m_cpText.SetDefaultColor(m_clrRowText);

	// set the text and back colors for the list control.
	m_ctrlListSelectPoint.SetRowColors(m_cpText.GetColor(), m_cpBack.GetColor());

	m_bAscending=TRUE;
	m_nSortedCol=0;

	m_flatHeader.SetSortImage (m_nSortedCol, m_bAscending);

			// TODO: Add your sorting code here.
	CXTSortClass csc (&m_ctrlListSelectPoint, m_nSortedCol);
	csc.Sort (m_bAscending ? true : false, DT_STRING);

}

void CCtrlCmdDlg::OnButtonSelect() 
{
	// TODO: Add your control notification handler code here
	int nItemCount=m_ctrlListAllPoint.GetItemCount();
	//CString2DataType Str2Data;
    for(int nItem=0;nItem<nItemCount;nItem++)
	{
		if(m_ctrlListAllPoint.GetItemState(nItem,LVIS_SELECTED) & LVIS_SELECTED)
		{
			CString strPointNo=m_ctrlListAllPoint.GetItemText(nItem,0);

			int nItemCount1=m_ctrlListSelectPoint.GetItemCount();
			BOOL bExist=FALSE;
			for(int j=0; j<nItemCount1; j++)
			{
				if(strPointNo==m_ctrlListSelectPoint.GetItemText(j,0))
				{
					bExist=TRUE;
					break;
				}
			}

			if(!bExist)
			{
				m_ctrlListSelectPoint.InsertItem(nItemCount1, strPointNo, 0);
				CString strExplain=m_ctrlListAllPoint.GetItemText(nItem,4);
			//	m_ctrlListSelectPoint.SetItem(nItemCount1, 1, LVIF_TEXT, strExplain, NULL, NULL,NULL,NULL);//NULL, NULL, NULL);
				m_ctrlListSelectPoint.SetItemText(nItemCount1, 1,strExplain);

			}
		}
	}
    if(!BuildCtrlPointQue()) return;
    DispStatus();
	
}

void CCtrlCmdDlg::OnButtonDeselect() 
{
	// TODO: Add your control notification handler code here
	int nItemCount=m_ctrlListSelectPoint.GetItemCount();
    for(int nItem=0;nItem<nItemCount;nItem++)
	{
		if(m_ctrlListSelectPoint.GetItemState(nItem,LVIS_SELECTED) & LVIS_SELECTED)
		{
			m_ctrlListSelectPoint.DeleteItem(nItem);
		}
	}
}

void CCtrlCmdDlg::OnButtonSelectall() 
{
	// TODO: Add your control notification handler code here
	int nItemCount=m_ctrlListAllPoint.GetItemCount();
	//CString2DataType Str2Data;
    for(int nItem=0;nItem<nItemCount;nItem++)
	{
		CString strPointNo=m_ctrlListAllPoint.GetItemText(nItem,0);
		int nItemCount1=m_ctrlListSelectPoint.GetItemCount();
		BOOL bExist=FALSE;
		for(int j=0; j<nItemCount1; j++)
		{
			if(strPointNo==m_ctrlListSelectPoint.GetItemText(j,0))
			{
				bExist=TRUE;
				break;
			}
		}
		if(!bExist)
		{
			m_ctrlListSelectPoint.InsertItem(nItemCount1, strPointNo, 0);
			CString strExplain=m_ctrlListAllPoint.GetItemText(nItem,4);
			m_ctrlListSelectPoint.SetItem(nItemCount1, 1, LVIF_TEXT, strExplain, 0, NULL, NULL, NULL);
		}
	}
	 if(!BuildCtrlPointQue()) return;
    DispStatus();
}

void CCtrlCmdDlg::OnButtonDeselectall() 
{
	// TODO: Add your control notification handler code here
	m_ctrlListSelectPoint.DeleteAllItems();
}
/*
#define MS5OUT_B25  	  2     //M1
#define S8OUT_B48        12     //
#define S5OUT_B25  	     13     //M1
*/
void CCtrlCmdDlg::SetDBListContent()
{

	CString2DataType Str2Data;
	CString strSQL;
	m_ctrlListAllPoint.DeleteAllItems();
 	try
	{
		if(m_ctrlComboTrunkNO.GetCurSel()==8)
			strSQL.Format("SELECT * FROM uPointProperty WHERE (bValueType = 0) AND (bScan = 1) AND  ((unConnectorID=12) OR (unConnectorID=13) OR (unConnectorID=2))"); //S8OUT_B48  S5OUT_B25  MS5OUT_B25
		else
			strSQL.Format("SELECT * FROM uPointProperty WHERE (unTrunkNo = %d ) AND (bScan = 1) AND (bValueType = 0) AND ((unConnectorID=12) OR (unConnectorID=13) OR (unConnectorID=2))",m_ctrlComboTrunkNO.GetCurSel()+1);
		if( m_SQLDirect.ExecuteSQL(strSQL)==SQL_SUCCESS)
		{
			int nRet=m_SQLDirect.Fetch();
			int iItem=0;
			while(!nRet)
			{
				CString strunPointNo=m_SQLDirect.GetCol(1);
				CString strunTrunkNo=m_SQLDirect.GetCol(2);
				CString strunAddress=m_SQLDirect.GetCol(3);
				CString strExplaintemp=m_SQLDirect.GetCol(11);
				CString strunChannel=m_SQLDirect.GetCol(12); 

				//CViewDeleteAddr* pViewDeleteAddr;
				//pViewDeleteAddr = new CViewDeleteAddr;
				//CString strunConvIDCH = pViewDeleteAddr->GetConvName(Str2Data.String2Int(strunConnectorID));
				//delete pViewDeleteAddr;

                BOOL Ac_state=m_structValueState[Str2Data.String2Int(strunPointNo)].Ac_state;
				if( Ac_state==0)
				{
				m_ctrlListAllPoint.InsertItem(iItem, strunPointNo, 0);
				m_ctrlListAllPoint.SetItem(iItem, 1, LVIF_TEXT, strunAddress, 0, NULL, NULL, NULL);
				m_ctrlListAllPoint.SetItem(iItem, 2, LVIF_TEXT, strunTrunkNo, 0, NULL, NULL, NULL);
				m_ctrlListAllPoint.SetItem(iItem, 3, LVIF_TEXT, strunChannel, 0, NULL, NULL, NULL);
				m_ctrlListAllPoint.SetItem(iItem, 4, LVIF_TEXT, strExplaintemp, 0, NULL, NULL, NULL);
				iItem++;
				}
				nRet=m_SQLDirect.Fetch();
			}
		}

	}
	catch(CDBException *e){
	e->ReportError();
	return;
	}

	// initialize the back color picker default colors.
	m_cpBack.SetColor(RGB(0x33,0x66,0xff));
	m_cpBack.SetDefaultColor(m_clrRowBack);

	// initialize the text color picker default colors.
	m_cpText.SetColor(RGB(0xff,0xff,0xff));
	m_cpText.SetDefaultColor(m_clrRowText);

	// set the text and back colors for the list control.
	m_ctrlListAllPoint.SetRowColors(m_cpText.GetColor(), m_cpBack.GetColor());

	//m_ctrlList.AutoSizeColumn ();
}

void CCtrlCmdDlg::OnSelchangeComboTrunkno() 
{
	// TODO: Add your control notification handler code here
	SetDBListContent();
}

void CCtrlCmdDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	m_SQLDirect.Close();
}

BOOL CCtrlCmdDlg::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult) 
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
			CXTSortClass csc (&m_ctrlListAllPoint, m_nSortedCol);
			if(m_nSortedCol==4)
				csc.Sort (m_bAscending ? true : false, DT_STRING);
			else
				csc.Sort (m_bAscending ? true : false, DT_INT);

		}
	}

	return CDialog::OnNotify(wParam, lParam, pResult);
}

void CCtrlCmdDlg::OnDblclkListAllpoint(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	OnButtonSelect();
	*pResult = 0;
}

void CCtrlCmdDlg::OnDblclkListSelectpoint(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	OnButtonDeselect();
	*pResult = 0;
}


void CCtrlCmdDlg::OnButtonReverse() 
{
	// TODO: Add your control notification handler code here

	if(!BuildCtrlPointQue()) return;  //得到命令队列
	m_ucSendCtrlFlag=2;  //to send the first scan cmd //0: ready to send cmd get state 1: get state and ready to send output cmd 2:get the result state  
    m_usCtrlPointNumCount=0;
    StartCmd(m_usCtrlPointNumCount);	

	SetTimer(300,m_unDelayTimerD*400,NULL);
}

void CCtrlCmdDlg::OnButtonOpen() 
{
	// TODO: Add your control notification handler code here

	if(!BuildCtrlPointQue()) return;
	m_ucSendCtrlFlag = 1;
    m_usCtrlPointNumCount=0;
    StartCmd(m_usCtrlPointNumCount);	
	SetTimer(300,m_unDelayTimerD*400,NULL);
	
}

void CCtrlCmdDlg::OnButtonOff() 
{
	// TODO: Add your control notification handler code here gunScantimeDelay

	if(!BuildCtrlPointQue()) return;
	m_ucSendCtrlFlag = 0;
    m_usCtrlPointNumCount=0;
    StartCmd(m_usCtrlPointNumCount);	
	SetTimer(300,m_unDelayTimerD*400,NULL);

}

BOOL CCtrlCmdDlg::BuildCtrlPointQue()
{

	CString2DataType Str2Data;
	m_usCtrlPointNum=m_ctrlListSelectPoint.GetItemCount();
	m_usCtrlPointNumCount=0; 
	if(!m_usCtrlPointNum)
	{
		AfxMessageBox("控制表中没有点，请先选择要控制的点");
		return FALSE;
	}
	if(m_usCtrlPointNum>MAX_CTRL_POINT_NUM)
	{
		CString strmsg;
		strmsg.Format("控制表中点数不能超过 %d，请先调整点数",MAX_CTRL_POINT_NUM);
		AfxMessageBox(strmsg);
		return FALSE;
	}

	//if(m_ctrlListBoxCommInfo.GetCount()>200)
	m_ctrlListBoxCommInfo.ResetContent();

	return TRUE;
}

void CCtrlCmdDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	CMainFrame* pFWnd=(CMainFrame*)AfxGetMainWnd();
	CCommStatusFM* pCommStatusFM=pFWnd->m_pCommStatusFM;
	CKJMonitorApp* pApp=(CKJMonitorApp* )AfxGetApp();
        pApp->pMPT->CloseWarning();
	
        if(pCommStatusFM->m_bBitCmdReceiveSuccess==FALSE)
		{
                DispStatus();
		}
        else
			StopSendCtrlCmd();  //发送后的恢复

	CDialog::OnTimer(nIDEvent);
}


void CCtrlCmdDlg::StopSendCtrlCmd()
{
	CMainFrame* pFWnd=(CMainFrame*)AfxGetMainWnd();
	CCommStatusFM* pCommStatusFM=pFWnd->m_pCommStatusFM;

	KillTimer(300);

	if(!pCommStatusFM->m_bStartScan)
	{
		pCommStatusFM->StartScan();
	}
	m_ctrlBtnOff.EnableWindow(TRUE);   //Enable 
	m_ctrlBtnOpen.EnableWindow(TRUE);
	m_ctrlBtnReverse.EnableWindow(TRUE);
}

void CCtrlCmdDlg::DispStatus()
{
	CMainFrame* pFWnd=(CMainFrame*)AfxGetMainWnd();
	CCommStatusFM* pCommStatusFM=pFWnd->m_pCommStatusFM;

	CString2DataType Str2Data;

	for(int m_usCtrlPointNumCount=0;m_usCtrlPointNumCount<m_usCtrlPointNum;m_usCtrlPointNumCount++)
	{
	    unsigned short usPointNoW =	Str2Data.String2Int(m_ctrlListSelectPoint.GetItemText(m_usCtrlPointNumCount,0));//m_structCTRLPOINT[m_usCtrlPointNumCount].usPointNo;
         unsigned char ucAddress = pCommStatusFM->m_structMONITORPOINT[usPointNoW].ucAddrNo;//m_structCTRLPOINT[m_usCtrlPointNumCount].ucAddrNo;

		BOOL Ac_state=m_structValueState[usPointNoW].Ac_state;
		 if( Ac_state==0)
		{
	    		m_ctrlListSelectPoint.SetItemText(m_usCtrlPointNumCount, 3,"√成功");
            
			if(m_structValueState[usPointNoW].ufData==1)
                m_ctrlListSelectPoint.SetItemText(m_usCtrlPointNumCount, 2,"●▄● 给电 1");
	        else
			{
                m_ctrlListSelectPoint.SetItemText(m_usCtrlPointNumCount, 2,"○ ○ 断电 0");
			}
			CString strmsg;
			strmsg.Format(" √成功收到返回数据: 地址：0X%02X , 数据：%s ,通道：%d",
				ucAddress,
				Str2Data.Char2Binary(m_structValueState[usPointNoW].ucLowValue),
                pCommStatusFM->m_structMONITORPOINT[usPointNoW].unChannel);
 
			m_ctrlListBoxCommInfo.AddString(strmsg,RGB(000,102,000));
			m_ctrlListBoxCommInfo.SetCurSel(m_ctrlListBoxCommInfo.GetCount()-1);
		}
        else
		{
     		m_ctrlListSelectPoint.SetItemText(m_usCtrlPointNumCount, 3,"×失败");
		    CString str;
		    str.Format("  %d 点 通信失败",usPointNoW);
     		m_ctrlListBoxCommInfo.AddString(str,RGB(255,000,000));
    		m_ctrlListBoxCommInfo.SetCurSel(m_ctrlListBoxCommInfo.GetCount()-1);
		}
	}

}


void CCtrlCmdDlg::StartCmd(int m_usCtrlPointNumCount)
{
	CMainFrame* pFWnd=(CMainFrame*)AfxGetMainWnd();
	CCommStatusFM* pCommStatusFM=pFWnd->m_pCommStatusFM;
	CKJMonitorApp* pApp=(CKJMonitorApp* )AfxGetApp();
 
	m_ctrlBtnOff.EnableWindow(FALSE);   //Disable 
	m_ctrlBtnOpen.EnableWindow(FALSE);
	m_ctrlBtnReverse.EnableWindow(FALSE);

	UpdateData(TRUE);

	CString2DataType Str2Data;

    if(StartSequence == FALSE)
	{
     		m_ctrlListBoxCommInfo.AddString("请先启动序列,然后再发控制命令");
	    	m_ctrlListBoxCommInfo.SetCurSel(m_ctrlListBoxCommInfo.GetCount()-1);
            pCommStatusFM->m_bBitCmdReceiveSuccess=TRUE;
	}
	//	pApp->pMPT->InitSequence();
    else
	{
	for(m_usCtrlPointNumCount=0;m_usCtrlPointNumCount<m_usCtrlPointNum;m_usCtrlPointNumCount++)
	{	
	  if(m_ctrlListSelectPoint.GetItemState(m_usCtrlPointNumCount,LVIS_SELECTED) & LVIS_SELECTED)
	  {

		unsigned short usPointNoW =	Str2Data.String2Int(m_ctrlListSelectPoint.GetItemText(m_usCtrlPointNumCount,0));//m_structCTRLPOINT[m_usCtrlPointNumCount].usPointNo;
    	int iTrunk=pCommStatusFM->m_structMONITORPOINT[usPointNoW].ucTrunkNo;//m_structCTRLPOINT[m_usCtrlPointNumCount].ucTrunkNo;
        unsigned char ucAddress = pCommStatusFM->m_structMONITORPOINT[usPointNoW].ucAddrNo;//m_structCTRLPOINT[m_usCtrlPointNumCount].ucAddrNo;

    	if((pCommStatusFM->m_structMONITORPOINT[usPointNoW].ucConvID==MS5OUT_B25)||
     		(pCommStatusFM->m_structMONITORPOINT[usPointNoW].ucConvID==S5OUT_B25))
		{
    		switch(m_ucSendCtrlFlag) 
			{
	        	case 0:
                    if(m_structValueState[usPointNoW].ufData==0)
					{
                   		CString str;
	                 	str.Format("====%d号干线，    地址%d，    %d号点，    打开  当前状态不需改变，继续",iTrunk,ucAddress,usPointNoW);
                   		m_ctrlListBoxCommInfo.AddString(str);
                		m_ctrlListBoxCommInfo.SetCurSel(m_ctrlListBoxCommInfo.GetCount()-1);
					}
                    else
					{
                            SSeq[99].SPUnum=99;
                            SSeq[99].SPUhold=0;
                            SSeq[99].SPUprori=0;
                            SSeq[99].num_of_command=m_usCtrlPointNum;

							SSeq[99].command[m_usCtrlPointNumCount+1].command_type = 25 ;
                    		CString str;
	                    	str.Format("p%d",usPointNoW);
                            sprintf(SSeq[99].command[m_usCtrlPointNumCount+1].Para1,str); 
                    		CString str1;
	                    	str1.Format("#%d",1);
                            sprintf(SSeq[99].command[m_usCtrlPointNumCount+1].Para2,str1); 
                    		CString str2;
	                    	str2.Format("#%d",m_unDelayTimerD);
                            sprintf(SSeq[99].command[m_usCtrlPointNumCount+1].Para3,str2); 
                    		CString str3;
	                    	str3.Format("%dn",1);
                            sprintf(SSeq[99].command[m_usCtrlPointNumCount+1].Para4,str3); 

							CString str4;
	                    	str4.Format("====%d号干线，    地址%d，    %d号点，    打开",iTrunk,ucAddress,usPointNoW);
                     		m_ctrlListBoxCommInfo.AddString(str4);
                    		m_ctrlListBoxCommInfo.SetCurSel(m_ctrlListBoxCommInfo.GetCount()-1);
                        	pApp->pMPT->InsertSeq(99);  //启动控制时序    
					}
	         		break;
        		case 1:
                    if(m_structValueState[usPointNoW].ufData==1)
					{
                   		CString str;
	                 	str.Format("====%d号干线，    地址%d，    %d号点，    闭合  当前状态不需改变，继续",iTrunk,ucAddress,usPointNoW);
                   		m_ctrlListBoxCommInfo.AddString(str);
                		m_ctrlListBoxCommInfo.SetCurSel(m_ctrlListBoxCommInfo.GetCount()-1);
					}					
                    else
					{
                            SSeq[99].SPUnum=99;
                            SSeq[99].SPUhold=0;
                            SSeq[99].SPUprori=0;
                            SSeq[99].num_of_command=m_usCtrlPointNum;

							SSeq[99].command[m_usCtrlPointNumCount+1].command_type = 25 ;
                    		CString str;
	                    	str.Format("p%d",usPointNoW);
                            sprintf(SSeq[99].command[m_usCtrlPointNumCount+1].Para1,str); 
                    		CString str1;
	                    	str1.Format("#%d",2);
                            sprintf(SSeq[99].command[m_usCtrlPointNumCount+1].Para2,str1); 
                    		CString str2;
	                    	str2.Format("#%d",m_unDelayTimerD);
                            sprintf(SSeq[99].command[m_usCtrlPointNumCount+1].Para3,str2); 
                    		CString str3;
	                    	str3.Format("%dn",1);
                            sprintf(SSeq[99].command[m_usCtrlPointNumCount+1].Para4,str3); 

							CString str4;
	                    	str4.Format("====%d号干线，    地址%d，    %d号点，    闭合",iTrunk,ucAddress,usPointNoW);
                     		m_ctrlListBoxCommInfo.AddString(str4);
                    		m_ctrlListBoxCommInfo.SetCurSel(m_ctrlListBoxCommInfo.GetCount()-1);
                        	pApp->pMPT->InsertSeq(99);  //启动控制时序    
					}	         
					break;
        		case 2:
                    if(m_structValueState[usPointNoW].ufData==0)
					{
                            SSeq[99].SPUnum=99;
                            SSeq[99].SPUhold=0;
                            SSeq[99].SPUprori=0;
                            SSeq[99].num_of_command=m_usCtrlPointNum;

							SSeq[99].command[m_usCtrlPointNumCount+1].command_type = 25 ;
                    		CString str;
	                    	str.Format("p%d",usPointNoW);
                            sprintf(SSeq[99].command[m_usCtrlPointNumCount+1].Para1,str); 
                    		CString str1;
	                    	str1.Format("#%d",2);
                            sprintf(SSeq[99].command[m_usCtrlPointNumCount+1].Para2,str1); 
                    		CString str2;
	                    	str2.Format("#%d",m_unDelayTimerD);
                            sprintf(SSeq[99].command[m_usCtrlPointNumCount+1].Para3,str2); 
                    		CString str3;
	                    	str3.Format("%dn",1);
                            sprintf(SSeq[99].command[m_usCtrlPointNumCount+1].Para4,str3); 

							CString str4;
	                    	str4.Format("====%d号干线，    地址%d，    %d号点，    闭合",iTrunk,ucAddress,usPointNoW);
                     		m_ctrlListBoxCommInfo.AddString(str4);
                    		m_ctrlListBoxCommInfo.SetCurSel(m_ctrlListBoxCommInfo.GetCount()-1);
                        	pApp->pMPT->InsertSeq(99);  //启动控制时序    
					}
					else
					{
                            SSeq[99].SPUnum=99;
                            SSeq[99].SPUhold=0;
                            SSeq[99].SPUprori=0;
                            SSeq[99].num_of_command=m_usCtrlPointNum;

							SSeq[99].command[m_usCtrlPointNumCount+1].command_type = 25 ;
                    		CString str;
	                    	str.Format("p%d",usPointNoW);
                            sprintf(SSeq[99].command[m_usCtrlPointNumCount+1].Para1,str); 
                    		CString str1;
	                    	str1.Format("#%d",1);
                            sprintf(SSeq[99].command[m_usCtrlPointNumCount+1].Para2,str1); 
                    		CString str2;
	                    	str2.Format("#%d",m_unDelayTimerD);
                            sprintf(SSeq[99].command[m_usCtrlPointNumCount+1].Para3,str2); 
                    		CString str3;
	                    	str3.Format("%dn",1);
                            sprintf(SSeq[99].command[m_usCtrlPointNumCount+1].Para4,str3); 

							CString str4;
	                    	str4.Format("====%d号干线，    地址%d，    %d号点，    打开",iTrunk,ucAddress,usPointNoW);
                     		m_ctrlListBoxCommInfo.AddString(str4);
                    		m_ctrlListBoxCommInfo.SetCurSel(m_ctrlListBoxCommInfo.GetCount()-1);
                        	pApp->pMPT->InsertSeq(99);  //启动控制时序    
					}	         
					break;
	        	default:
	         		break;
			}
		}
        else if(pCommStatusFM->m_structMONITORPOINT[usPointNoW].ucConvID==S8OUT_B48)
		{
	    	switch(m_ucSendCtrlFlag) {
	         	case 0:
	        	case 2:
//	           		pCommStatusFM->m_chCmd[iTrunk][1] = 0x70;
	        		break;
	        	case 1:
//	         		pCommStatusFM->m_chCmd[iTrunk][1] = 0x78 | m_ucCurrentState;
	         		break;
	        	default:
	    		break;
			}
		}
      } //if
	}//for

        if(m_usCtrlPointNumCount>=m_usCtrlPointNum)
		{
    		m_ctrlListBoxCommInfo.AddString("控制命令已发送,请等待返回数据");
	    	m_ctrlListBoxCommInfo.SetCurSel(m_ctrlListBoxCommInfo.GetCount()-1);
            pCommStatusFM->m_bBitCmdReceiveSuccess=TRUE;
		}
    }//else
	UpdateData(FALSE);
}
