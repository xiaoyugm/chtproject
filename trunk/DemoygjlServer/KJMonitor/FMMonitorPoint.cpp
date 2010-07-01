// FMMonitorPoint.cpp : implementation file
//

#include "stdafx.h"
#include "kjmonitor.h"
#include "FMMonitorPoint.h"

#include "ViewDeleteAddr.h"

#include "CommStatusFM.h"
#include "MainFrm.h"
#include "MonitorPointThread.h"
#include "EditWatchPoint.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define MAX_LISTMONITOR_ITEM_NUM 16



/////////////////////////////////////////////////////////////////////////////
// CFMMonitorPoint
extern structRunTime m_structRunTime[MAX_POINT_NUMBER];
extern structSWITCH m_structSWITCH[MAX_POINT_NUMBER];
extern structANOLOG m_structANOLOG[MAX_POINT_NUMBER];
extern structValueState m_structValueState[MAX_POINT_NUMBER];


IMPLEMENT_DYNCREATE(CFMMonitorPoint, CFormView)

CFMMonitorPoint::CFMMonitorPoint()
	: CFormView(CFMMonitorPoint::IDD)
{
	//{{AFX_DATA_INIT(CFMMonitorPoint)
	m_snEditDispMonitorNo = 1;  //1
	//}}AFX_DATA_INIT
	m_bSearchPoint=FALSE;
}

CFMMonitorPoint::~CFMMonitorPoint()
{
}

void CFMMonitorPoint::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFMMonitorPoint)
//	DDX_Control(pDX, IDC_STATIC_CLOSEOPEN9, m_ctrlStaticCloseOpen9);
//	DDX_Control(pDX, IDC_STATIC_CLOSEOPEN8, m_ctrlStaticCloseOpen8);
//	DDX_Control(pDX, IDC_STATIC_CLOSEOPEN15, m_ctrlStaticCloseOpen15);
//	DDX_Control(pDX, IDC_STATIC_CLOSEOPEN14, m_ctrlStaticCloseOpen14);
//	DDX_Control(pDX, IDC_STATIC_CLOSEOPEN13, m_ctrlStaticCloseOpen13);
//	DDX_Control(pDX, IDC_STATIC_CLOSEOPEN12, m_ctrlStaticCloseOpen12);
//	DDX_Control(pDX, IDC_STATIC_CLOSEOPEN11, m_ctrlStaticCloseOpen11);
//	DDX_Control(pDX, IDC_STATIC_CLOSEOPEN10, m_ctrlStaticCloseOpen10);
	DDX_Control(pDX, IDC_CHECK_DISPASSAMPLEPOINT, m_ctrlCheckDispAsSamplePoint);
	DDX_Control(pDX, IDC_BUTTON_DISPMONITORNO, m_ctrlBtnDispMonitorNo);
//	DDX_Control(pDX, IDC_STATIC_CLOSEOPEN7,  m_ctrlStaticCloseOpen7);
//	DDX_Control(pDX, IDC_STATIC_CLOSEOPEN6,  m_ctrlStaticCloseOpen6);
//	DDX_Control(pDX, IDC_STATIC_CLOSEOPEN5,  m_ctrlStaticCloseOpen5);
//	DDX_Control(pDX, IDC_STATIC_CLOSEOPEN4,  m_ctrlStaticCloseOpen4);
//	DDX_Control(pDX, IDC_STATIC_CLOSEOPEN3,  m_ctrlStaticCloseOpen3);
//	DDX_Control(pDX, IDC_STATIC_CLOSEOPEN2,  m_ctrlStaticCloseOpen2);
//	DDX_Control(pDX, IDC_STATIC_CLOSEOPEN1,  m_ctrlStaticCloseOpen1);
//	DDX_Control(pDX, IDC_STATIC_CLOSEOPEN0,  m_ctrlStaticCloseOpen0);
	DDX_Control(pDX, IDC_LIST_MONITOR, m_ctrlListMonitor);
	DDX_Text(pDX, IDC_EDIT_DISPMOINTORNO, m_snEditDispMonitorNo);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFMMonitorPoint, CFormView)
	//{{AFX_MSG_MAP(CFMMonitorPoint)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON_DISPMONITORNO, OnButtonDispmonitorno)
	ON_WM_PAINT()                              //8/15
	ON_WM_SHOWWINDOW()                         //8/15   
	ON_WM_TIMER()                              //8/15
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_MONITOR, OnDblclkListMonitor)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFMMonitorPoint diagnostics

#ifdef _DEBUG
void CFMMonitorPoint::AssertValid() const
{
	CFormView::AssertValid();
}

void CFMMonitorPoint::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CFMMonitorPoint message handlers

void CFMMonitorPoint::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();
	
	// TODO: Add your specialized code here and/or call the base class
	CMainFrame* pFWnd=(CMainFrame*)AfxGetMainWnd();
	pFWnd->m_pFMMonitorPoint=this;

///	for(int i=0;i<MAX_LISTMONITOR_ITEM_NUM;i++)
//		SetSwitchStatus(i,2);
	SetBtnStyle();
	
	SetMonitorListHead();
	
	m_ucOldTrunkNo=0;
	m_ctrlCheckDispAsSamplePoint.SetCheck(0);
	m_snEditDispMonitorNo=m_usDispStartMonitorNo=1;  //1
	UpdateData(FALSE);
	
	//创建一个定时器
//	bStartMonitor = FALSE;
}

void CFMMonitorPoint::OnDestroy() 
{
	CFormView::OnDestroy();	
	// TODO: Add your message handler code here
	m_SQLDirect.Close();
	//KillTimer(1001);
}

//SET ALL ITEMS

//设置点号与监测信息的代码
//set  monitorno' info
//SET ONE ITEM
// ucSetContent 0: set orignal info  1:set dynamic value
void CFMMonitorPoint::SetDispMonitorNo(unsigned short usMonitor,unsigned char ucSetContent)
{
	if((usMonitor<m_usDispStartMonitorNo)||(usMonitor>=m_usDispStartMonitorNo+MAX_LISTMONITOR_ITEM_NUM))
	{
		//AfxMessageBox("the monitor num is not between STARTPOINTer and the MAX"); //for test
		return;
	}
	if((usMonitor>15000)||(usMonitor==0))
		return;
	CMainFrame* pFWnd=(CMainFrame*)AfxGetMainWnd();
	CCommStatusFM *pCommStatusFM=pFWnd->m_pCommStatusFM;
	CString2DataType Str2Data;
	CViewDeleteAddr viewdelteaddr;
	short sPointNo = m_nPointNoForMonitorNo[usMonitor];
	CString temp;
	unsigned char ucTrunkNo =pCommStatusFM->m_structMONITORPOINT[sPointNo].ucTrunkNo;
	
	unsigned char   ucjAddr, ucConvID;//,muckConV; //ucRXch ,   
	ucjAddr=pCommStatusFM->m_structMONITORPOINT[sPointNo].ucAddrNo;   //pCommStatusFM->m_ucjAddr[ucTrunkNo-1];
    ucConvID=pCommStatusFM->m_structMONITORPOINT[sPointNo].ucConvID;

	unsigned char iItem=usMonitor-m_usDispStartMonitorNo;
	CString strde,strtemp,strunConvIDName,strbScan,strRX1;
 		BOOL Ac_state=m_structValueState[sPointNo].Ac_state;

	//更新点的状态
//	pApp->pMPT->GetPointStatus(sPointNo);
	DrawMonitorStatus(usMonitor);
//    SetMointorStatus(sPointNo);

	CString strwatch ,strunPointNo ,strunTrunkNo ,strunAddress ,strRX10 ,strRXUnit ,stractValue ,strChannel;


	switch(ucSetContent)
	{
	case 0:
		if(sPointNo==-1)
		{
			strwatch.Format("◇%d",usMonitor); //◎◎··●●□□◇▓■
			strunPointNo = "未定义";
			strunTrunkNo = "      " ;
			strunAddress  = "     " ;
			strunConvIDName = "            " ;
			strbScan = "              " ;
			strRX1 = "             " ;				
			strRX10 = "              " ;				
			stractValue = "                   " ;				
			strRXUnit = "                              " ;	
           	strChannel = "      " ;
		}
		else 
		{
			strwatch.Format("□%d",usMonitor); //◎◎··●●□□◇▓■
			strunPointNo.Format("%d",sPointNo);
			strunTrunkNo.Format("%d",ucTrunkNo);
			strunAddress.Format("%d",ucjAddr);
			strunConvIDName = viewdelteaddr.GetConvName(ucConvID);
			strbScan="不扫描";
			strRX1 = "             " ;				
			strRX10 = "              " ;				
			stractValue = "                   " ;				
			strRXUnit = "                              " ;	
           	strChannel.Format("%d",pCommStatusFM->m_structMONITORPOINT[sPointNo].unChannel);

///            SetMointorStatus(sPointNo);
		}
			m_ctrlListMonitor.SetItem(2*iItem, 0, LVIF_TEXT, strwatch, 0, NULL, NULL, NULL);
			m_ctrlListMonitor.SetItem(2*iItem, 1, LVIF_TEXT, strunPointNo, 0, NULL, NULL, NULL);
			m_ctrlListMonitor.SetItem(2*iItem, 2, LVIF_TEXT, strunTrunkNo, 0, NULL, NULL, NULL);
			m_ctrlListMonitor.SetItem(2*iItem, 3, LVIF_TEXT, strunAddress, 0, NULL, NULL, NULL);
			m_ctrlListMonitor.SetItem(2*iItem, 4, LVIF_TEXT, strunConvIDName, 0, NULL, NULL, NULL);
			m_ctrlListMonitor.SetItem(2*iItem, 5, LVIF_TEXT, strbScan, 0, NULL, NULL, NULL);
	          		m_ctrlListMonitor.SetItem(2*iItem, 6, LVIF_TEXT, strRX1, 0, NULL, NULL, NULL);
	         		m_ctrlListMonitor.SetItem(2*iItem, 7, LVIF_TEXT, strRX10, 0, NULL, NULL, NULL);
		        	m_ctrlListMonitor.SetItem(2*iItem, 8, LVIF_TEXT, stractValue, 0, NULL, NULL, NULL);
		        	m_ctrlListMonitor.SetItem(2*iItem, 9, LVIF_TEXT, strRXUnit, 0, NULL, NULL, NULL);
		        	m_ctrlListMonitor.SetItem(2*iItem, 10, LVIF_TEXT, strChannel, 0, NULL, NULL, NULL);

		break;
	case 1:
/*
点监测：点是模拟量：二进制，十进制，数据（实际值），工程单位
           点是开关量：二进制，十进制，状态（1/0），1/2模式对，运行时间
测点编辑去掉的点，在点监测中也要自动去掉。
点颜色的变化，要反映到点监测相应的点上，在二进制的相应位上显示（黄、绿、橙、红）。
模拟量  实际值 = (最大值 - 最小值)/255 *实际的十进制值 + 最小值 = 实际值
*/
       if( Ac_state==1)
	   {
			strwatch.Format("▓%d",usMonitor); //◎◎··●●□□◇▓■
			strunPointNo.Format("%d",sPointNo);
			strunTrunkNo.Format("%d",ucTrunkNo);
			strunAddress.Format("%d",ucjAddr);
			strunConvIDName  = viewdelteaddr.GetConvName(ucConvID);;
			strbScan="扫描";
			strRX1 = "             " ;				
			strRX10 = "              " ;				
			stractValue = "                   " ;				
			strRXUnit = "                              " ;	
           	strChannel.Format("%d",pCommStatusFM->m_structMONITORPOINT[sPointNo].unChannel);
	   }
	   else 
	   {
			strwatch.Format("■%d",usMonitor); //◎◎··●●□□◇▓■
			strunPointNo.Format("%d",sPointNo);
			strunTrunkNo.Format("%d",ucTrunkNo);
			strunAddress.Format("%d",ucjAddr);
			strunConvIDName = viewdelteaddr.GetConvName(ucConvID);
			strbScan="扫描";

			BOOL bValueType=pCommStatusFM->m_structMONITORPOINT[sPointNo].bValueType;
			if(bValueType){ 
				unsigned char ucValue = m_structValueState[sPointNo].ucLowValue;  	//单点值
				unsigned char ddvalue1 = m_structValueState[sPointNo].ucHighValue; 	//二进制数据：
				double actValue = m_structANOLOG[sPointNo].ufMeasure ;//实际值
				if ((ucConvID == 4)||(ucConvID == 10)){
					strRX1.Format("%s",Str2Data.Char2Binary(ucValue));				
					strRX10.Format("%d", ucValue);				
					stractValue = "" ;				
					strRXUnit.Format("%s",m_structANOLOG[sPointNo].usUnit);
                 	strChannel.Format("%d",pCommStatusFM->m_structMONITORPOINT[sPointNo].unChannel);
				}          //是否是脉冲量
				else if(ucConvID == 7)
				{
					strRX1.Format("%s%s",Str2Data.Char2Binary(ddvalue1),Str2Data.Char2Binary(ucValue));				
					strRX10.Format("%d", ddvalue1*256+ucValue);				
					stractValue.Format("%4.2f", actValue);				
					strRXUnit.Format("%s",m_structANOLOG[sPointNo].usUnit);
                 	strChannel.Format("%d",pCommStatusFM->m_structMONITORPOINT[sPointNo].unChannel);
				}
				else {
					strRX1.Format("%s",Str2Data.Char2Binary(ucValue));				
					strRX10.Format("%d", ucValue);				
					stractValue.Format("%4.2f", actValue);				
					strRXUnit.Format("%s",m_structANOLOG[sPointNo].usUnit);
                 	strChannel.Format("%d",pCommStatusFM->m_structMONITORPOINT[sPointNo].unChannel);
				}
			}
			else{
	     			unsigned char ddvalue = m_structValueState[sPointNo].ucLowValue; //二进制数据：	
     				int ucStatus = m_structValueState[sPointNo].ufData;
					strRX1.Format("%s",Str2Data.Char2Binary(ddvalue));
					if(ddvalue)
    					strRX10.Format("●▄● %d", ddvalue);	
					else
     					strRX10.Format("○ ○ %d", ddvalue);				
	     			if (ddvalue == 1)
		     			stractValue = m_structSWITCH[sPointNo].ucstrMode2;
		    		else
			       		stractValue = m_structSWITCH[sPointNo].ucstrMode1;				
		    		strRXUnit.Format("%d天%d时%d分", m_structRunTime[sPointNo].udDay,
		          			m_structRunTime[sPointNo].udHour,
			         		m_structRunTime[sPointNo].udMin);
                 	strChannel.Format("%d",pCommStatusFM->m_structMONITORPOINT[sPointNo].unChannel);
			}
	   }

			m_ctrlListMonitor.SetItem(2*iItem, 0, LVIF_TEXT, strwatch, 0, NULL, NULL, NULL);
			m_ctrlListMonitor.SetItem(2*iItem, 1, LVIF_TEXT, strunPointNo, 0, NULL, NULL, NULL);
			m_ctrlListMonitor.SetItem(2*iItem, 2, LVIF_TEXT, strunTrunkNo, 0, NULL, NULL, NULL);
			m_ctrlListMonitor.SetItem(2*iItem, 3, LVIF_TEXT, strunAddress, 0, NULL, NULL, NULL);
			m_ctrlListMonitor.SetItem(2*iItem, 4, LVIF_TEXT, strunConvIDName, 0, NULL, NULL, NULL);
			m_ctrlListMonitor.SetItem(2*iItem, 5, LVIF_TEXT, strbScan, 0, NULL, NULL, NULL);
	          		m_ctrlListMonitor.SetItem(2*iItem, 6, LVIF_TEXT, strRX1, 0, NULL, NULL, NULL);
	         		m_ctrlListMonitor.SetItem(2*iItem, 7, LVIF_TEXT, strRX10, 0, NULL, NULL, NULL);
		        	m_ctrlListMonitor.SetItem(2*iItem, 8, LVIF_TEXT, stractValue, 0, NULL, NULL, NULL);
		        	m_ctrlListMonitor.SetItem(2*iItem, 9, LVIF_TEXT, strRXUnit, 0, NULL, NULL, NULL);
		        	m_ctrlListMonitor.SetItem(2*iItem, 10, LVIF_TEXT, strChannel, 0, NULL, NULL, NULL);

///		    SetMointorStatus(sPointNo);
		break;
	default:
		break;
	}


}


void CFMMonitorPoint::SetMonitorListHead()
{
	m_ctrlListMonitor.InsertColumn(0, _T("监测号"),   LVCFMT_CENTER, 20);
	m_ctrlListMonitor.InsertColumn(1, _T(" 点号 "),   LVCFMT_CENTER, 20);
	m_ctrlListMonitor.InsertColumn(2, _T("干线"),   LVCFMT_CENTER, 5);
	m_ctrlListMonitor.InsertColumn(3, _T("地址"),   LVCFMT_CENTER, 5);
	m_ctrlListMonitor.InsertColumn(4, _T("  转接器  "),   LVCFMT_CENTER, 40);
	m_ctrlListMonitor.InsertColumn(5, _T(" 巡检 "),   LVCFMT_CENTER, 5);
	m_ctrlListMonitor.InsertColumn(6, _T("     二进制     "),   LVCFMT_CENTER, 30);
	m_ctrlListMonitor.InsertColumn(7, _T("状态/十进制"),   LVCFMT_CENTER, 30);
	m_ctrlListMonitor.InsertColumn(8, _T("1/2模式对/实际值"),   LVCFMT_CENTER, 20);
	m_ctrlListMonitor.InsertColumn(9, _T("运行时间/工程单位"),   LVCFMT_CENTER, 10);
	m_ctrlListMonitor.InsertColumn(10, _T("通道"),   LVCFMT_CENTER, 5);
	for(int iItem=0;iItem<MAX_LISTMONITOR_ITEM_NUM;iItem++)
	{
		CString strtemp = "" ;
//		strtemp.Format("□%d",iItem); //◎◎··●●□□◇   //**change subscript
		m_ctrlListMonitor.InsertItem(2*iItem, strtemp, 0);      //4*
//		strtemp.Format("·%d",m_nPointNoForMonitorNo[iItem]);
		m_ctrlListMonitor.InsertItem(2*iItem+1, "", 0);
//		m_ctrlListMonitor.InsertItem(4*iItem+2, "", 0);
//		m_ctrlListMonitor.InsertItem(4*iItem+3, "", 0);            //"_____"
	}

	// Get the windows handle to the header control for the
	// list control then subclass the control.
	HWND hWndHeader = m_ctrlListMonitor.GetDlgItem(IDC_LIST_MONITOR)->GetSafeHwnd();
	m_flatHeader.SubclassWindow (hWndHeader);

//	if (m_bSaveColumnWidth)
//		m_ctrlListMonitor.LoadColumnWidths();

	// size to fit the columns
	m_ctrlListMonitor.AutoSizeColumn ();

	// initialize the back color picker default colors.
	m_cpBack.SetColor(RGB(0x33,0x66,0xff));
	m_cpBack.SetDefaultColor(m_clrRowBack);

	// initialize the text color picker default colors.
	m_cpText.SetColor(RGB(0xff,0xff,0xff));
	m_cpText.SetDefaultColor(m_clrRowText);

	// set the text and back colors for the list control.
	m_ctrlListMonitor.SetRowColors(m_cpText.GetColor(), m_cpBack.GetColor());

	// set some extnded styles
	m_ctrlListMonitor.SetExtendedStyle (LVS_EX_FULLROWSELECT|LVS_EX_FLATSB);
//	m_ctrlListMonitor.SetExtendedStyle (LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT|LVS_EX_FLATSB);

/*	m_bAscending=TRUE;
	m_nSortedCol=0;

	m_flatHeader.SetSortImage (m_nSortedCol, m_bAscending);

			// TODO: Add your sorting code here.
	CXTSortClass csc (&m_ctrlListMonitor, m_nSortedCol);
	csc.Sort (m_bAscending ? true : false, DT_INT);*/
}

void CFMMonitorPoint::SetBtnStyle()
{
	m_ctrlBtnDispMonitorNo.SetThemeHelper(&m_ThemeHelper);
	m_ctrlBtnDispMonitorNo.SetIcon(IDI_ICON_RIGHTARROW);
	m_ctrlBtnDispMonitorNo.SetTooltipText(_T("在左框中填入监测号或点号（若为点号，要选中左边的点号框）作为第一个框中的显示号"));
}

//ucDispNo 0-7   ucStatus 0: OPEN 1: CLOSE 2: NNNN
void CFMMonitorPoint::SetSwitchStatus(unsigned char ucDispNo, unsigned short ucStatus)
{
	HICON hIconOpen = AfxGetApp()->LoadIcon(IDI_ICON_OPEN1);
	HICON hIconClose = AfxGetApp()->LoadIcon(IDI_ICON_CLOSE1);
	HICON hIconNnnn = AfxGetApp()->LoadIcon(IDI_ICON_NNNN);
	HICON hIcon;
	if(!ucStatus)
		hIcon=hIconOpen;
	else if(ucStatus==1)
		hIcon=hIconClose;
	else
		hIcon=hIconNnnn;
	switch(ucDispNo)
	{
	case 0:
		m_ctrlStaticCloseOpen0.SetIcon(hIcon);
		break;
	case 1:
		m_ctrlStaticCloseOpen1.SetIcon(hIcon);
		break;
	case 2:
		m_ctrlStaticCloseOpen2.SetIcon(hIcon);
		break;
	case 3:
		m_ctrlStaticCloseOpen3.SetIcon(hIcon);
		break;
	case 4:
		m_ctrlStaticCloseOpen4.SetIcon(hIcon);
		break;
	case 5:
		m_ctrlStaticCloseOpen5.SetIcon(hIcon);
		break;
	case 6:
		m_ctrlStaticCloseOpen6.SetIcon(hIcon);
		break;
	case 7:
		m_ctrlStaticCloseOpen7.SetIcon(hIcon);
		break;
	case 8:
		m_ctrlStaticCloseOpen8.SetIcon(hIcon);
		break;
	case 9:
		m_ctrlStaticCloseOpen9.SetIcon(hIcon);
		break;
	case 10:
		m_ctrlStaticCloseOpen10.SetIcon(hIcon);
		break;
	case 11:
		m_ctrlStaticCloseOpen11.SetIcon(hIcon);
		break;
	case 12:
		m_ctrlStaticCloseOpen12.SetIcon(hIcon);
		break;
	case 13:
		m_ctrlStaticCloseOpen13.SetIcon(hIcon);
		break;
	case 14:
		m_ctrlStaticCloseOpen14.SetIcon(hIcon);
		break;
	case 15:
		m_ctrlStaticCloseOpen15.SetIcon(hIcon);
		break;
	default:
		break;
	}
	//SetSwitchWarnStatus(ucDispNo, ucStatus);
}


void CFMMonitorPoint::SetMointorStatus(UINT unMonitorPointNo)
{
	CMainFrame* pFWnd=(CMainFrame*)AfxGetMainWnd();
	CCommStatusFM *pCommStatusFM=pFWnd->m_pCommStatusFM;
	unsigned short usMonitorNo=pCommStatusFM->m_structMONITORPOINT[unMonitorPointNo].usMonitorNo;

	unsigned short ucLowValue=m_structValueState[unMonitorPointNo].ufData;
	BOOL bValueType=pCommStatusFM->m_structMONITORPOINT[unMonitorPointNo].bValueType;
//	if(! bValueType) 
///		SetSwitchStatus(usMonitorNo-m_usDispStartMonitorNo,ucLowValue);
//	else 
//		SetSwitchStatus(usMonitorNo-m_usDispStartMonitorNo,2);

}

void CFMMonitorPoint::OnButtonDispmonitorno() 
{
	CMainFrame* pFWnd=(CMainFrame*)AfxGetMainWnd();
	CCommStatusFM *pCommStatusFM=pFWnd->m_pCommStatusFM;

	UpdateData(TRUE);

	if((m_snEditDispMonitorNo!=0)&&(m_snEditDispMonitorNo<MAX_POINT_NUMBER))
	{
	if(m_ctrlCheckDispAsSamplePoint.GetCheck())  //pointno
	{
		m_usDispStartMonitorNo = pCommStatusFM->m_structMONITORPOINT[m_snEditDispMonitorNo].usMonitorNo; 
		if(m_usDispStartMonitorNo==0){
             m_usDispStartMonitorNo=1;
		CString strtemp1;
		strtemp1.Format("点号不存在，请重新输入");
		AfxMessageBox(strtemp1);
		return;
		}

//		m_usDispStartPointNo = m_nPointNoForMonitorNo[usMonitor];//m_snEditDispMonitorNo;
	}
	else
	{
		m_usDispStartMonitorNo = m_snEditDispMonitorNo;
//		m_usDispStartPointNo = m_nPointNoForMonitorNo[m_snEditDispMonitorNo];
	}

///	bStartMonitor = TRUE;
	for(int iItem=0;iItem<MAX_LISTMONITOR_ITEM_NUM;iItem++)
	{
		SetDispMonitorNo(m_usDispStartMonitorNo+iItem,0);
//		SetSwitchStatus(iItem,2);
	}
	}
	else
		return;
}

void CFMMonitorPoint::OnDraw(CDC* pDC) 
{
	// TODO: Add your specialized code here and/or call the base class
}

void CFMMonitorPoint::DrawMonitorStatus(unsigned short usMonitorNo)
{
	if((usMonitorNo < m_usDispStartMonitorNo)||(usMonitorNo >= m_usDispStartMonitorNo+MAX_LISTMONITOR_ITEM_NUM))
	{
		//AfxMessageBox("the monitor num is not between STARTPOINTer and the MAX"); //for test
		return;
	}
	CMainFrame* pFWnd=(CMainFrame*)AfxGetMainWnd();
	CCommStatusFM *pCommStatusFM=pFWnd->m_pCommStatusFM;

///	CString2DataType Str2Data;
	short sPointNo = m_nPointNoForMonitorNo[usMonitorNo];
///	CString temp;
///	temp.Format("%d",pCommStatusFM->m_structMONITORPOINT[sPointNo].unChannel);

	unsigned char iItem=usMonitorNo - m_usDispStartMonitorNo;

	CWnd* wnd = GetDlgItem(IDC_STATUS1 + iItem);
	CDC *pdc = wnd->GetDC();
	COLORREF color;
	int nStatus;
	if ((sPointNo == -1)||(usMonitorNo == 0))
       nStatus = YELLOW_STATUS;
	else
	   nStatus = m_structValueState[sPointNo].WarnColor;
	if (nStatus == ORANGE_STATUS)
		color = RGB(255,128,0);
	else if (nStatus == GREEN_STATUS)
		color = RGB(0,255,0);
	else if (nStatus == RED_STATUS)
		color = RGB(255,0,0);
	else if (nStatus == YELLOW_STATUS)
		color = RGB(255,255,0);
	RECT arect;
	wnd->GetClientRect(&arect);
	pdc->FillSolidRect( &arect, color);
//	int x,y;
//	x = (arect.left + arect.right) / 2 - 3; 
//	y = arect.top + 1;
//	pdc->TextOut(x,y,temp);
	ReleaseDC(pdc);
}

void CFMMonitorPoint::UpdatePointsStatus()
{
//    m_ctrlListSamplePoint.DeleteAllItems();
//    GetDataFromDBSamplePoint();
//	m_ctrlListEditMonitor.DeleteAllItems();
//    GetDataFromDBMointorEdit();
		
	OnButtonDispmonitorno();
}


void CFMMonitorPoint::OnDblclkListMonitor(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	CEditWatchPoint WatchPointDlg;
	WatchPointDlg.DoModal();
	
	*pResult = 0;
}
