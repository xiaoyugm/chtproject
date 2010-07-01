// AddrPointScanStatusDlg.cpp : implementation file
//

#include "stdafx.h"
#include "kjmonitor.h"
#include "AddrPointScanStatusDlg.h"
#include "ViewDeleteAddr.h"


#include "CommStatusFM.h"
#include "MainFrm.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAddrPointScanStatusDlg dialog


CAddrPointScanStatusDlg::CAddrPointScanStatusDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAddrPointScanStatusDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAddrPointScanStatusDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CAddrPointScanStatusDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAddrPointScanStatusDlg)
	DDX_Control(pDX, IDC_LIST_POINTSTATUS, m_ctrlListPointStatus);
	DDX_Control(pDX, IDC_STATIC_TRUNKADDR, m_ctrlSaticTrunkAddr);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAddrPointScanStatusDlg, CDialog)
	//{{AFX_MSG_MAP(CAddrPointScanStatusDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAddrPointScanStatusDlg message handlers

BOOL CAddrPointScanStatusDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CString strtemp;
	strtemp.Format("当前显示的是干线%d上的地址%d",m_ucTrunkNo,m_ucAddrNo);
	m_ctrlSaticTrunkAddr.SetWindowText(strtemp);

	SetListCtrlHead();
	SetDispStaticContent();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CAddrPointScanStatusDlg::SetListCtrlHead()
{
	m_ctrlListPointStatus.InsertColumn(0, _T("点号"),   LVCFMT_CENTER, 30);
	m_ctrlListPointStatus.InsertColumn(1, _T("点描述"),   LVCFMT_CENTER, 10);
	m_ctrlListPointStatus.InsertColumn(2, _T("点值"), LVCFMT_CENTER, 50);
	m_ctrlListPointStatus.InsertColumn(3, _T("单位"), LVCFMT_CENTER, 50);
	m_ctrlListPointStatus.InsertColumn(4, _T("扫描"),   LVCFMT_CENTER, 10);
	m_ctrlListPointStatus.InsertColumn(5, _T("通信状态"), LVCFMT_CENTER, 20);
	m_ctrlListPointStatus.InsertColumn(6, _T("转接器名称"), LVCFMT_CENTER, 50);
	m_ctrlListPointStatus.InsertColumn(7, _T("说明"), LVCFMT_CENTER, 20);

	// set some extnded styles
	//m_ctrlListPointStatus.SetExtendedStyle (LVS_EX_FULLROWSELECT|LVS_EX_FLATSB);
	m_ctrlListPointStatus.SetExtendedStyle (LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT|LVS_EX_FLATSB);

	// Get the windows handle to the header control for the
	// list control then subclass the control.
	HWND hWndHeader = m_ctrlListPointStatus.GetDlgItem(0)->GetSafeHwnd();
	m_flatHeader.SubclassWindow (hWndHeader);

//	if (m_bSaveColumnWidth)
//		m_ctrlListPointStatus.LoadColumnWidths();

	// size to fit the columns
	m_ctrlListPointStatus.AutoSizeColumn();

	// initialize the back color picker default colors.
	m_cpBack.SetColor(RGB(0x33,0x66,0xff));
	m_cpBack.SetDefaultColor(m_clrRowBack);

	// initialize the text color picker default colors.
	m_cpText.SetColor(RGB(0xff,0xff,0xff));
	m_cpText.SetDefaultColor(m_clrRowText);

	// set the text and back colors for the list control.
	m_ctrlListPointStatus.SetRowColors(m_cpText.GetColor(), m_cpBack.GetColor());

	

/*
	m_bAscending=FALSE;
	m_nSortedCol=0;

	m_flatHeader.SetSortImage (m_nSortedCol, m_bAscending);

			// TODO: Add your sorting code here.
	CXTSortClass csc (&m_ctrlListPointStatus, m_nSortedCol);
	csc.Sort (m_bAscending ? true : false, DT_INT);
*/

}

void CAddrPointScanStatusDlg::SetDispStaticContent()
{
	//m_ucTrunkNo,m_ucAddrNo
	CString2DataType Str2Data;
	CMainFrame* pFWnd=(CMainFrame*)AfxGetMainWnd();
	CCommStatusFM *pCommStatusFM=pFWnd->m_pCommStatusFM;
/*	m_ctrlListPointStatus.InsertColumn(0, _T("点号"),   LVCFMT_CENTER, 30);
	m_ctrlListPointStatus.InsertColumn(1, _T("点描述"),   LVCFMT_CENTER, 10);
	m_ctrlListPointStatus.InsertColumn(2, _T("点值"), LVCFMT_CENTER, 50);
	m_ctrlListPointStatus.InsertColumn(3, _T("单位"), LVCFMT_CENTER, 50);
	m_ctrlListPointStatus.InsertColumn(4, _T("扫描"),   LVCFMT_CENTER, 10);
	m_ctrlListPointStatus.InsertColumn(5, _T("通信状态"), LVCFMT_CENTER, 20);
	m_ctrlListPointStatus.InsertColumn(6, _T("转接器名称"), LVCFMT_CENTER, 50);
	m_ctrlListPointStatus.InsertColumn(7, _T("说明"), LVCFMT_CENTER, 20);

*/
	unsigned char ucITEM_ALL=0;
	for(unsigned char iConv=0; iConv<MAX_MULTICONV_NUMBER;iConv++)
	{
        BOOL bScan=pCommStatusFM->m_structSCANADDR[m_ucTrunkNo-1][m_ucAddrNo][iConv].bScan;
		if(!bScan) continue;
		//MAX_POINT_NUM_ANOLOG;
		unsigned char ucConvType=pCommStatusFM->m_structSCANADDR[m_ucTrunkNo-1][m_ucAddrNo][iConv].snConVType;
		unsigned char ucConvChanel=pCommStatusFM->GetConvChannels(ucConvType);
		//A8IN8BIT_MCA:    //7. MCA-8路模拟量输入信号转接器[12位8路]
		//A8IN8BIT_MC8 :   //8  MC8-8路模拟量输入信号转接器[8位8路]
		//MA4IN                 MC8-4路模拟量输入信号转接器[8位4路]
		for(unsigned char ucItem=0; ucItem<ucConvChanel;ucItem++)
		{
			CString strbScan,strPointNo,strConvName;
			strPointNo=Str2Data.Int2CString(pCommStatusFM->m_structSCANADDR[m_ucTrunkNo-1][m_ucAddrNo][iConv].structPointInfo[ucItem].usPointNo);
            BOOL bscan=pCommStatusFM->m_structSCANADDR[m_ucTrunkNo-1][m_ucAddrNo][iConv].structPointInfo[ucItem].bScan;
			if( bscan)
				strbScan="扫描";
			else
				strbScan="不扫描";
			CViewDeleteAddr ViewDeleteAddr;
			strConvName=ViewDeleteAddr.GetConvName(ucConvType);
			
			
			m_ctrlListPointStatus.InsertItem(ucITEM_ALL,strPointNo,0);
			m_ctrlListPointStatus.SetItem(ucITEM_ALL,4,LVIF_TEXT,strbScan, 0, NULL, NULL, NULL);
			m_ctrlListPointStatus.SetItem(ucITEM_ALL,6,LVIF_TEXT,strConvName, 0, NULL, NULL, NULL);
		//	m_ctrlListPointStatus.SetItem(ucITEM_ALL,4,LVIF_TEXT,strbScan, 0, NULL, NULL, NULL);
		//	m_ctrlListPointStatus.SetItem(ucITEM_ALL,4,LVIF_TEXT,strbScan, 0, NULL, NULL, NULL);

			ucITEM_ALL++;


		}
	}


	m_ctrlListPointStatus.AutoSizeColumn();
}
