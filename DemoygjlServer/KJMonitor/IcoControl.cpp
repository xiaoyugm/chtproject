// IcoControl.cpp : implementation file
//

#include "stdafx.h"
#include "kjmonitor.h"
#include "IcoControl.h"

#include "SQL\\String2DataType.h"

#include "ViewDeleteAddr.h"

#include "SetPortVsTrunkDlg.h"


#include "CommStatusFM.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CIcoControl dialog
extern NSEQ FAR 	SSeq[201];       //时序号,运行结构             //需要
extern BOOL StartSequence;
extern structANOLOG m_structANOLOG[MAX_POINT_NUMBER];
extern structValueState m_structValueState[MAX_POINT_NUMBER];


CIcoControl::CIcoControl(CWnd* pParent /*=NULL*/)
	: CDialog(CIcoControl::IDD, pParent)
{
	//{{AFX_DATA_INIT(CIcoControl)
	m_unDelayTimerICO = 8;
	//}}AFX_DATA_INIT
}


void CIcoControl::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CIcoControl)
	DDX_Control(pDX, IDC_BUTTON_HIGNWARN, m_ctrlBtnHighWarn);
	DDX_Control(pDX, IDC_BUTTON_HIGN2WARN, m_ctrlBtnHigh2Warn);
	DDX_Control(pDX, IDC_BUTTON_DEHIGNWARN, m_ctrlBtnDehighWarn);
	DDX_Control(pDX, IDC_BUTTON_DEHIGH2WARN, m_ctrlBtnDehigh2Warn);
	DDX_Control(pDX, IDOK, m_ctrlBtnOK);
	DDX_Control(pDX, IDC_LIST_SELECTPOINT, m_ctrlListSelectPoint);
	DDX_Control(pDX, IDC_LIST_COMINFO, m_ctrlListBoxCommInfo);
	DDX_Control(pDX, IDC_LIST_ALLPOINT, m_ctrlListAllPoint);
	DDX_Control(pDX, IDC_COMBO_TRUNKNO, m_ctrlComboTrunkNO);
	DDX_Control(pDX, IDC_BUTTON_SELECTALL, m_ctrlBtnSelectAll);
	DDX_Control(pDX, IDC_BUTTON_SELECT, m_ctrlBtnSelect);
	DDX_Control(pDX, IDC_BUTTON_DESELECTALL, m_ctrlBtnDeselectAll);
	DDX_Control(pDX, IDC_BUTTON_DESELECT, m_ctrlBtnDeselect);
	DDX_Text(pDX, IDC_EDITDELAYTIMERICO, m_unDelayTimerICO);
	DDV_MinMaxUInt(pDX, m_unDelayTimerICO, 1, 60);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CIcoControl, CDialog)
	//{{AFX_MSG_MAP(CIcoControl)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON_DEHIGH2WARN, OnButtonDehigh2warn)
	ON_BN_CLICKED(IDC_BUTTON_DEHIGNWARN, OnButtonDehignwarn)
	ON_BN_CLICKED(IDC_BUTTON_DESELECT, OnButtonDeselect)
	ON_BN_CLICKED(IDC_BUTTON_DESELECTALL, OnButtonDeselectall)
	ON_BN_CLICKED(IDC_BUTTON_HIGN2WARN, OnButtonHign2warn)
	ON_BN_CLICKED(IDC_BUTTON_HIGNWARN, OnButtonHignwarn)
	ON_BN_CLICKED(IDC_BUTTON_SELECT, OnButtonSelect)
	ON_BN_CLICKED(IDC_BUTTON_SELECTALL, OnButtonSelectall)
	ON_CBN_SELCHANGE(IDC_COMBO_TRUNKNO, OnSelchangeComboTrunkno)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_ALLPOINT, OnDblclkListAllpoint)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_SELECTPOINT, OnDblclkListSelectpoint)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CIcoControl message handlers

BOOL CIcoControl::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_ctrlBtnOK.SetThemeHelper(&m_ThemeHelper);
	m_ctrlBtnOK.SetIcon(IDI_ICON_EXIT);
	m_ctrlBtnOK.SetTooltipText(_T("退出"));
	m_ctrlBtnOK.SetColor(0,RGB(255,000,000),TRUE);
	m_ctrlBtnOK.SetColor(1,RGB(255,255,255),TRUE);

	m_ctrlBtnSelectAll.SetThemeHelper(&m_ThemeHelper);
	m_ctrlBtnSelectAll.SetIcon(IDI_ICON_ADD1);
	m_ctrlBtnSelectAll.SetTooltipText(_T("将左表中所有点全部加入"));
	m_ctrlBtnSelectAll.SetColor(0,RGB(000,255,000),TRUE);
	m_ctrlBtnSelectAll.SetColor(1,RGB(255,255,255),TRUE);

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

	m_ctrlBtnDehighWarn.SetThemeHelper(&m_ThemeHelper);
	m_ctrlBtnDehighWarn.SetIcon(IDI_ICON_CLOSE1);
	m_ctrlBtnDehighWarn.SetTooltipText(_T("请先选择要控制的点，然后关闭高报警—给电"));

	m_ctrlBtnHighWarn.SetThemeHelper(&m_ThemeHelper);
	m_ctrlBtnHighWarn.SetIcon(IDI_ICON_OPEN1);
	m_ctrlBtnHighWarn.SetTooltipText(_T("请先选择要控制的点，然后高报警断电"));

	m_ctrlBtnDehigh2Warn.SetThemeHelper(&m_ThemeHelper);
	m_ctrlBtnDehigh2Warn.SetIcon(IDI_ICON_CLOSE1);
	m_ctrlBtnDehigh2Warn.SetTooltipText(_T("请先选择要控制的点，然后接通—复电"));

	m_ctrlBtnHigh2Warn.SetThemeHelper(&m_ThemeHelper);
	m_ctrlBtnHigh2Warn.SetIcon(IDI_ICON_OPEN1);
	m_ctrlBtnHigh2Warn.SetTooltipText(_T("请先选择要控制的点，然后高高报警断电"));

	m_ctrlListBoxCommInfo.AddString("OK",RGB(000,102,000));

	m_ctrlComboTrunkNO.SetCurSel(8);

///	ConnectDB();
	
	SetDBListHead();
	SetCtrlListHead();

///	SetDBListContent();

    m_ctrlListBoxCommInfo.AddString("在右侧列表框请用鼠标左键结合Ctrl键/Shift键选择要控制的点，然后点击控制键");
	m_ctrlListBoxCommInfo.SetCurSel(m_ctrlListBoxCommInfo.GetCount()-1);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
void CIcoControl::ConnectDB()
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

void CIcoControl::SetDBListHead()
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

void CIcoControl::SetCtrlListHead()
{
	m_ctrlListSelectPoint.InsertColumn(0, _T("点号"),   LVCFMT_CENTER, 40);
	m_ctrlListSelectPoint.InsertColumn(1, _T(" 说    明 "),   LVCFMT_CENTER, 100);
	m_ctrlListSelectPoint.InsertColumn(2, _T("通信状态"),   LVCFMT_CENTER, 60);
	m_ctrlListSelectPoint.InsertColumn(3, _T("数据"),   LVCFMT_CENTER, 60);   // o-o     o o
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

void CIcoControl::SetDBListContent()
{

	CString2DataType Str2Data;
	CString strSQL;
	m_ctrlListAllPoint.DeleteAllItems();
 	try
	{
		if(m_ctrlComboTrunkNO.GetCurSel()==8)
			strSQL.Format("SELECT * FROM uPointProperty WHERE (bValueType = 1) AND (unConnectorID= 5)"); //A1IN8BIT_CH4ICO
		else
			strSQL.Format("SELECT * FROM uPointProperty WHERE (unTrunkNo = %d ) AND (bValueType = 1) AND (unConnectorID=5)",m_ctrlComboTrunkNO.GetCurSel()+1);
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


void CIcoControl::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	m_SQLDirect.Close();
	
}

void CIcoControl::OnButtonDehigh2warn() 
{
	if(!BuildCtrlPointQue()) return;  //得到命令队列
    m_ucCurrentState =42;
    m_usCtrlPointNumCount=0;
    StartCmd(m_usCtrlPointNumCount);
	SetTimer(500,m_unDelayTimerICO*400,NULL);
	
}

void CIcoControl::OnButtonDehignwarn() 
{
	if(!BuildCtrlPointQue()) return;  //得到命令队列
    m_ucCurrentState =40;
    m_usCtrlPointNumCount=0;
    StartCmd(m_usCtrlPointNumCount);
	SetTimer(500,m_unDelayTimerICO*400,NULL);
	
}

void CIcoControl::OnButtonDeselect() 
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

void CIcoControl::OnButtonDeselectall() 
{
	// TODO: Add your control notification handler code here
		m_ctrlListSelectPoint.DeleteAllItems();
}

void CIcoControl::OnButtonHign2warn() 
{
	if(!BuildCtrlPointQue()) return;  //得到命令队列
    m_ucCurrentState =34;
    m_usCtrlPointNumCount=0;
    StartCmd(m_usCtrlPointNumCount);
	SetTimer(500,m_unDelayTimerICO*400,NULL);
	
}

void CIcoControl::OnButtonHignwarn() 
{
	if(!BuildCtrlPointQue()) return;  //得到命令队列
    m_ucCurrentState =32;
    m_usCtrlPointNumCount=0;
    StartCmd(m_usCtrlPointNumCount);
	SetTimer(500,m_unDelayTimerICO*400,NULL);
	
}

void CIcoControl::OnButtonSelect() 
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

void CIcoControl::OnButtonSelectall() 
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

void CIcoControl::OnSelchangeComboTrunkno() 
{
	// TODO: Add your control notification handler code here
///	SetDBListContent();
	
}

void CIcoControl::OnDblclkListAllpoint(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	OnButtonSelect();
	*pResult = 0;
}

void CIcoControl::OnDblclkListSelectpoint(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	OnButtonDeselect();
	*pResult = 0;
}

BOOL CIcoControl::BuildCtrlPointQue()
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

void CIcoControl::OnTimer(UINT nIDEvent) 
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

BOOL CIcoControl::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult) 
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

void CIcoControl::StopSendCtrlCmd()
{
	CMainFrame* pFWnd=(CMainFrame*)AfxGetMainWnd();
	CCommStatusFM* pCommStatusFM=pFWnd->m_pCommStatusFM;

	KillTimer(500);

	if(!pCommStatusFM->m_bStartScan)
	{
		pCommStatusFM->StartScan();
	}
	m_ctrlBtnHighWarn.EnableWindow(TRUE);   //Enable 
	m_ctrlBtnHigh2Warn.EnableWindow(TRUE);
	m_ctrlBtnDehighWarn.EnableWindow(TRUE);
	m_ctrlBtnDehigh2Warn.EnableWindow(TRUE);
}

void CIcoControl::DispStatus()
{
	CMainFrame* pFWnd=(CMainFrame*)AfxGetMainWnd();
	CCommStatusFM* pCommStatusFM=pFWnd->m_pCommStatusFM;

	CString2DataType Str2Data;

	for(int m_usCtrlPointNumCount=0;m_usCtrlPointNumCount<m_usCtrlPointNum;m_usCtrlPointNumCount++)
	{
	    unsigned short usPointNoW =	Str2Data.String2Int(m_ctrlListSelectPoint.GetItemText(m_usCtrlPointNumCount,0));//m_structCTRLPOINT[m_usCtrlPointNumCount].usPointNo;
    	int iTrunk=pCommStatusFM->m_structMONITORPOINT[usPointNoW].ucTrunkNo;
         unsigned char ucAddress = pCommStatusFM->m_structMONITORPOINT[usPointNoW].ucAddrNo;//m_structCTRLPOINT[m_usCtrlPointNumCount].ucAddrNo;

		BOOL Ac_state=m_structValueState[usPointNoW].Ac_state;
		 if(m_structValueState[usPointNoW].Ac_state==0)
		{
	    		m_ctrlListSelectPoint.SetItemText(m_usCtrlPointNumCount, 2,"√成功");
            
                m_ctrlListSelectPoint.SetItemText(m_usCtrlPointNumCount, 3,Str2Data.Short2Binary(m_structValueState[usPointNoW].ufData));

			CString strmsg;
			strmsg.Format(" √点号：%d ,干线：%d, 地址：%d ,二进制：%s ,实际值：%4.2f",usPointNoW,iTrunk,
				ucAddress,
				Str2Data.Short2Binary(m_structValueState[usPointNoW].ufData),
                m_structANOLOG[usPointNoW].ufMeasure);
 
			m_ctrlListBoxCommInfo.AddString(strmsg,RGB(000,102,000));
			m_ctrlListBoxCommInfo.SetCurSel(m_ctrlListBoxCommInfo.GetCount()-1);
		}
        else
		{
     		m_ctrlListSelectPoint.SetItemText(m_usCtrlPointNumCount, 2,"×失败");
		    CString str;
		    str.Format("  %d 点 通信失败",usPointNoW);
     		m_ctrlListBoxCommInfo.AddString(str,RGB(255,000,000));
    		m_ctrlListBoxCommInfo.SetCurSel(m_ctrlListBoxCommInfo.GetCount()-1);
		}
	}

}

void CIcoControl::StartCmd(int m_usCtrlPointNumCount)
{
	CMainFrame* pFWnd=(CMainFrame*)AfxGetMainWnd();
	CCommStatusFM* pCommStatusFM=pFWnd->m_pCommStatusFM;
	CKJMonitorApp* pApp=(CKJMonitorApp* )AfxGetApp();
 
	m_ctrlBtnHighWarn.EnableWindow(FALSE);   //Disable 
	m_ctrlBtnHigh2Warn.EnableWindow(FALSE);
	m_ctrlBtnDehighWarn.EnableWindow(FALSE);
	m_ctrlBtnDehigh2Warn.EnableWindow(FALSE);

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


		unsigned short usPointNoW =	Str2Data.String2Int(m_ctrlListSelectPoint.GetItemText(m_usCtrlPointNumCount,0));
    	int iTrunk=pCommStatusFM->m_structMONITORPOINT[usPointNoW].ucTrunkNo;
        unsigned char ucAddress = pCommStatusFM->m_structMONITORPOINT[usPointNoW].ucAddrNo;

                            SSeq[99].SPUnum=99;
                            SSeq[99].SPUhold=0;
                            SSeq[99].SPUprori=0;
                            SSeq[99].num_of_command=m_usCtrlPointNum;

							SSeq[99].command[m_usCtrlPointNumCount+1].command_type = 25 ;
                    		CString str;
	                    	str.Format("p%d",usPointNoW);
                            sprintf(SSeq[99].command[m_usCtrlPointNumCount+1].Para1,str); 
                    		CString str1;
	                    	str1.Format("#%d",m_ucCurrentState);
                            sprintf(SSeq[99].command[m_usCtrlPointNumCount+1].Para2,str1); 
                    		CString str2;
	                    	str2.Format("#%d",m_unDelayTimerICO);
                            sprintf(SSeq[99].command[m_usCtrlPointNumCount+1].Para3,str2); 
                    		CString str3;
	                    	str3.Format("%dn",1);
                            sprintf(SSeq[99].command[m_usCtrlPointNumCount+1].Para4,str3); 

							CString str4;
							if((m_ucCurrentState==40)||(m_ucCurrentState==42))
							{
	                        	str4.Format("====%d号干线，    地址%d，    %d号点，    给电",iTrunk,ucAddress,usPointNoW);
							}
							else
	                        	str4.Format("====%d号干线，    地址%d，    %d号点，    断电",iTrunk,ucAddress,usPointNoW);

							m_ctrlListBoxCommInfo.AddString(str4);
                    		m_ctrlListBoxCommInfo.SetCurSel(m_ctrlListBoxCommInfo.GetCount()-1);
                        	pApp->pMPT->InsertSeq(99);  //启动控制时序 
			}
		}

        if(m_usCtrlPointNumCount>=m_usCtrlPointNum)
		{
    		m_ctrlListBoxCommInfo.AddString("控制命令已发送,请等待返回数据");
	    	m_ctrlListBoxCommInfo.SetCurSel(m_ctrlListBoxCommInfo.GetCount()-1);
            pCommStatusFM->m_bBitCmdReceiveSuccess=TRUE;
		}
    }
	UpdateData(FALSE);
}

