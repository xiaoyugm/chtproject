// CommStatusFM.cpp : implementation file
//

#include "stdafx.h"
//#include "kj86monitor.h"
#include "CommStatusFM.h"
#include "CommStatusPointDlg.h"

#include "AddrPointScanStatusDlg.h"

#include "BitCmdCtrlDlg.h"
//#include "Sequence.h"

#include "MainFrm.h"

#include "CtrlCmdDlg.h"
#include "MQServer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

volatile BOOL gbScanTimeDelayThreadCtrl;
extern CMQServer  SocketServer;
//static int bdispafx=0;


#define MAX_LIST_ITEM_NUM          16   //list table rows 
#define MAX_LIST_SUBCOLLUM_NUM     6     //list table collums
#define OFFSETWINPATCH             0    //for windows timer patch ,for the user/dos 
#define MAX_LEDONOFF_TIMER_TIME    10
/////////////////////////////////////////////////////////////////////////////
// CCommStatusFM
structRunTime m_structRunTime[MAX_POINT_NUMBER];
structSWITCH m_structSWITCH[MAX_POINT_NUMBER];
structANOLOG m_structANOLOG[MAX_POINT_NUMBER];
structValueState m_structValueState[MAX_POINT_NUMBER];
extern  AllDate ;

IMPLEMENT_DYNCREATE(CCommStatusFM, CFormView)

CCommStatusFM::CCommStatusFM()
	: CFormView(CCommStatusFM::IDD)  //,m_ctrlList(COLUMNS_m_ctrlList)
{
	//{{AFX_DATA_INIT(CCommStatusFM)
//	m_strReturnValue = _T("");
	//}}AFX_DATA_INIT
	
	m_bCycleScan=FALSE;
	m_bStartScan=FALSE;
	m_bHaltDisp=0;
	m_unRepeaScantTimes = 0 ;
	m_bSerialPortChange=FALSE;
	for(int i=0;i<MAX_TRUNK_NUMBER;i++)
	{
		m_bSendBitCmd[i]=FALSE;
	}
	m_bSend=FALSE;   
	m_bSendHandCmd=FALSE;
	m_bHandCmdCanSend=FALSE;
	m_bHandCmdSendFail=FALSE;
	m_bBitCmdReceiveSuccess=FALSE;

}

CCommStatusFM::~CCommStatusFM()
{
//	delete m_SoundFile;
}

void CCommStatusFM::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCommStatusFM)
	DDX_Control(pDX, IDC_BUTTONCloseSound, m_ctrlBUTTONCloseSound);
	DDX_Control(pDX, IDC_STATIC_ONOFF7, m_ctrlStaticTrunkOnOff7);
	DDX_Control(pDX, IDC_STATIC_ONOFF6, m_ctrlStaticTrunkOnOff6);
	DDX_Control(pDX, IDC_STATIC_ONOFF5, m_ctrlStaticTrunkOnOff5);
	DDX_Control(pDX, IDC_STATIC_ONOFF4, m_ctrlStaticTrunkOnOff4);
	DDX_Control(pDX, IDC_STATIC_ONOFF3, m_ctrlStaticTrunkOnOff3);
	DDX_Control(pDX, IDC_STATIC_ONOFF2, m_ctrlStaticTrunkOnOff2);
	DDX_Control(pDX, IDC_STATIC_ONOFF1, m_ctrlStaticTrunkOnOff1);
	DDX_Control(pDX, IDC_STATIC_ONOFF0, m_ctrlStaticTrunkOnOff0);
	DDX_Control(pDX, IDC_PROGRESS0, m_ctrlProgress0);
	DDX_Control(pDX, IDC_PROGRESS1, m_ctrlProgress1);
	DDX_Control(pDX, IDC_PROGRESS2, m_ctrlProgress2);
	DDX_Control(pDX, IDC_PROGRESS3, m_ctrlProgress3);
	DDX_Control(pDX, IDC_PROGRESS4, m_ctrlProgress4);
	DDX_Control(pDX, IDC_PROGRESS5, m_ctrlProgress5);
	DDX_Control(pDX, IDC_PROGRESS6, m_ctrlProgress6);
	DDX_Control(pDX, IDC_PROGRESS7, m_ctrlProgress7);
	DDX_Control(pDX, IDC_PROGRESS8, m_ctrlProgress8);
	DDX_Control(pDX, IDC_PROGRESS9, m_ctrlProgress9);
	DDX_Control(pDX, IDC_PROGRESS10, m_ctrlProgress10);
	DDX_Control(pDX, IDC_PROGRESS11, m_ctrlProgress11);
	DDX_Control(pDX, IDC_PROGRESS12, m_ctrlProgress12);
	DDX_Control(pDX, IDC_PROGRESS13, m_ctrlProgress13);
	DDX_Control(pDX, IDC_PROGRESS14, m_ctrlProgress14);
	DDX_Control(pDX, IDC_PROGRESS15, m_ctrlProgress15);
	DDX_Control(pDX, IDC_COMBO_ADDRDISP, m_ctrlComboAddrDisp);
	DDX_Control(pDX, IDC_LIST1, m_ctrlList);
	DDX_Control(pDX, IDC_COMBO_TRUNKDISP, m_ctrlComboTrunkDisp);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCommStatusFM, CFormView)
	//{{AFX_MSG_MAP(CCommStatusFM)
	ON_MESSAGE(WM_COMM_RXCHAR, OnCommunication)
	ON_WM_DESTROY()
	ON_WM_TIMER()
	ON_CBN_SELCHANGE(IDC_COMBO_TRUNKDISP, OnSelchangeComboTrunkdisp)
	ON_CBN_SELCHANGE(IDC_COMBO_ADDRDISP, OnSelchangeComboAddrdisp)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, OnDblclkList1)
	ON_BN_CLICKED(IDC_BUTTONCloseSound, OnBUTTONCloseSound)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCommStatusFM diagnostics

#ifdef _DEBUG
void CCommStatusFM::AssertValid() const
{
	CFormView::AssertValid();
}

void CCommStatusFM::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCommStatusFM message handlers

void CCommStatusFM::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();
	// TODO: Add your specialized code here and/or call the base class
	m_hIconLedOn  = AfxGetApp()->LoadIcon(IDI_ICON_LEDON);
	m_hIconLedOff= AfxGetApp()->LoadIcon(IDI_ICON_LEDOFF);
	m_hIconPortOpen= AfxGetApp()->LoadIcon(IDI_ICON_NETWORK);

	m_ctrlBUTTONCloseSound.SetThemeHelper(&m_ThemeHelper);
	m_ctrlBUTTONCloseSound.SetIcon(IDI_ICON_STOP1);
	m_ctrlBUTTONCloseSound.SetTooltipText(_T("请及时关闭报警音乐，查看报警原因"));
//	m_ctrlBUTTONCloseSound.SetWindowText("");


	CMainFrame* pFWnd=(CMainFrame*)AfxGetMainWnd();
	pFWnd->m_pCommStatusFM=this;

	for(UINT i=0;i<MAX_TRUNK_NUMBER;i++)
	{
		m_unSerialPortforTrunk[i]=0;
		m_bTrunkPortOpen[i]=FALSE;
		SetDispTrunkSignal(i,0);
		m_ucTimerCount[i]=0;
		m_bScanLedOnOFF[i]=FALSE;
	}

///	ConnectDB();
//	m_bFirstRefreshProgress=TRUE; //progress procect the first time to refresh
	m_ctrlComboTrunkDisp.SetCurSel(0);
	m_ctrlComboAddrDisp.SetCurSel(0);
	m_ucTrunkDisp=0;
	m_ucAddrDisp=0;
	SetListCtrlTable();
	SetProgressCtrl();

}

					
LONG CCommStatusFM::OnCommunication(WPARAM ch, LPARAM port)
{
	CKJMonitorApp* pApp=(CKJMonitorApp* )AfxGetApp();
	unsigned char ucRXch;
	int iTrunkNo;
	UINT unPort=port;
	ucRXch=ch;
//	CString strSQL;
//	SYSTEMTIME  systime;
	
	for(UINT i=0;i<MAX_TRUNK_NUMBER;i++)
	{
		if(m_unSerialPortforTrunk[i]==unPort) 
		{
			iTrunkNo=i;
			break;
		}
	}

	m_bSend=FALSE; 

	if((!m_ucRxCount[iTrunkNo]))//****&&(ucRXch==(m_chCmd[iTrunkNo][0]&0x7F)))  //***对于借用高4位的情况需要处理
	{
		m_ucRXData[iTrunkNo][0]=ucRXch;
		m_ucRxCount[iTrunkNo]=1;
	}
	else 
	{
		m_ucRXData[iTrunkNo][1]=ucRXch;
		if(m_ucRxCount[iTrunkNo]==1)
		{
			m_bSend = TRUE ;
			m_ucRxCount[iTrunkNo]=2;
        	if ((m_ucRXData[iTrunkNo][0] & 0x0f)==(m_ucjAddr[iTrunkNo] & 0x0f))
			{
		    	pApp->pMPT->RefreshPoint(iTrunkNo,0);
			}
		}
	}
	return 0;
}

BOOL CCommStatusFM::StartScan()
{
	if(!GetCommPara()) 
		return FALSE;  //get gunScantimeDelay //ms gunRepeaScantTimes   should read data form DB
	if(ScanBuildQueue())
		AfxMessageBox("扫描参数加载没有成功");	//build scan queue
//	m_pData = NULL;
	BOOL bAnyPoint=FALSE;
/*	for(UINT iTrunk=0;iTrunk<MAX_TRUNK_NUMBER;iTrunk++)
	{
		m_ucRxCount[iTrunk]=0;
		if(!m_unScanTrunkPointNum[iTrunk]) continue; //no point to scan
		bAnyPoint=TRUE;
	}*/
	for(UINT iTrunk=0;iTrunk<MAX_TRUNK_NUMBER;iTrunk++) //% set %count 0 
	{
		for(UINT jAddr=0;jAddr<MAX_ADDR_NUMBER;jAddr++)
		{
			m_ucScanTXCount[iTrunk][jAddr]=0;
			m_ucScanSuccessCount[iTrunk][jAddr]=0;
		}
	}
/*	if((!bAnyPoint)&&(!m_bSendHandCmd)) //no points and have no hand cmd
	{
		AfxMessageBox("还没有编辑需要扫描的点");
		m_bStartScan=FALSE;
		return m_bStartScan;
	}
*/
	InitTrunkCOMPort();	//open serial port
	for( iTrunk=0;iTrunk<MAX_TRUNK_NUMBER;iTrunk++)
	{
		if(!m_unScanTrunkPointNum[iTrunk]) continue; //no point to scan
		if(!m_bTrunkPortOpen[iTrunk]) continue;
		SetDispTrunkSignal(iTrunk, 1);
	}
    //启动定时
	if(m_bStartScan)
	{
		ResetDispProgressCtrl();
		InitDispProgressCtrl();
		ResetListTable(m_ctrlComboTrunkDisp.GetCurSel(),m_ctrlComboAddrDisp.GetCurSel());
	}
    
//	m_bFirstRefreshProgress=TRUE; //用于在初次显示百分比时设置显示
	KillTimer(100);
	SetTimer(100,5,NULL);   //ManageClientD 300  SyncTableCollectData

	m_bCycleScan=FALSE;
///	Scan();

	return TRUE;
}

static int nncount=0;
BOOL CCommStatusFM::ScanGetNextCmd(unsigned char iTrunk)
{
	UINT unCmdNo=0; //记录模拟量命令号
	if(!m_bTrunkPortOpen[iTrunk]) 
	{
		m_unScanTrunkPointNum1[iTrunk]=0; //Because the port is not open, set m_unScanTrunkPointNum1[iTrunk]=0
		return FALSE;
	}

	if((m_bStartScan)&&(!m_bSendBitCmd[iTrunk]))   //m_bSendHandCmd=FALSE;
	{
		if(!m_unScanTrunkPointNum[iTrunk])   //no points on the turnk
			return FALSE;
		if(!m_unScanTrunkPointNum1[iTrunk])  //now the points have been scaned
			return FALSE;
		BOOL bGetNext=FALSE;  //ready to get next cmd bGetNext: False ->not get cmd yet
		BOOL bFail=FALSE;
		while((!bGetNext)&&(!bFail)) //find addr
		{
			if(!m_unScanAddrPointNum1[iTrunk][m_ucjAddr[iTrunk]]) //if no points on current addr
			{
				if(m_ucjAddr[iTrunk]<(MAX_ADDR_NUMBER-1))    
					m_ucjAddr[iTrunk]++;
				else 
					bFail=TRUE;
			}
			else
				bGetNext=TRUE;
		}
		bGetNext=FALSE;

		while((!bGetNext)&&(!bFail)) //find kConV
		{
			if(!m_ucScanConvPointNum1[iTrunk][m_ucjAddr[iTrunk]][m_uckConV[iTrunk][m_ucjAddr[iTrunk]]]) //if no points on current conv
			{
				if(m_uckConV[iTrunk][m_ucjAddr[iTrunk]]<(MAX_MULTICONV_NUMBER-1))
					m_uckConV[iTrunk][m_ucjAddr[iTrunk]]++;
				else
					bFail=TRUE;
			}
			else
				bGetNext=TRUE;
		}

		if(bFail) //测试错误  *****?
		{
			CString strtemp1;
			strtemp1.Format("测试错误:在规定的地址m_ucjAddr[%d]=%d,找不到点",iTrunk,m_ucjAddr[iTrunk]);
			AfxMessageBox(strtemp1);
			m_unScanTrunkPointNum1[iTrunk]=0;
			return FALSE;
		}
		
		if(bGetNext)
			bGetNext=FALSE;
		bFail=FALSE;

		unsigned char ucConVID=m_structSCANADDR[iTrunk][m_ucjAddr[iTrunk]][m_uckConV[iTrunk][m_ucjAddr[iTrunk]]].snConVType;
		unsigned char ucConvChannel=GetConvChannels(ucConVID);
		//if((snConVID==A8IN8BIT_MCA)||(snConVID==A8IN8BIT_MC8)||(snConVID==MA4IN))
		unCmdNo=0;
		//anolog value
        BOOL bValueType=m_structSCANADDR[iTrunk][m_ucjAddr[iTrunk]][m_uckConV[iTrunk][m_ucjAddr[iTrunk]]].bValueType;
		if(bValueType)
		{
			unsigned char ucChannel=0;
			for(unsigned char ichannel=0;ichannel<ucConvChannel;ichannel++)
			{
                BOOL bScan=m_structSCANADDR[iTrunk][m_ucjAddr[iTrunk]][m_uckConV[iTrunk][m_ucjAddr[iTrunk]]].structPointInfo[ichannel].bScan;
				if(bScan)
				{
					ucChannel++;

					if((m_ucScanConvPointNum[iTrunk][m_ucjAddr[iTrunk]][m_uckConV[iTrunk][m_ucjAddr[iTrunk]]]-
						m_ucScanConvPointNum1[iTrunk][m_ucjAddr[iTrunk]][m_uckConV[iTrunk][m_ucjAddr[iTrunk]]]+1)==ucChannel)
					{
						m_ucScanConvPointNum1[iTrunk][m_ucjAddr[iTrunk]][m_uckConV[iTrunk][m_ucjAddr[iTrunk]]]--;//传感器点数减去1***
						m_unScanAddrPointNum1[iTrunk][m_ucjAddr[iTrunk]]--;  //地址上的点数减去1
						m_unScanTrunkPointNum1[iTrunk]--;  //干线上的点数减去1
						unCmdNo=ichannel;
//						m_usPointNoScanedNow=m_structSCANADDR[iTrunk][m_ucjAddr[iTrunk]][m_uckConV[iTrunk][m_ucjAddr[iTrunk]]].structPointInfo[ichannel].usPointNo;//得到当前要扫描的模拟量点号

						break;
					}
				}
			}
//			if((ucChannel==ucConvChannel)&&(!unCmdNo))
			if((ucChannel==ucConvChannel)&&(!unCmdNo)&&(ucChannel!=1))
			{
				CString strtemp;
				strtemp.Format("ScanGetNextCmd:模拟量点数定义有错ucChannel=%d",ucChannel);
				AfxMessageBox(strtemp);
				return FALSE;
			}
		}
		else//switch value
		{
			
			m_unScanAddrPointNum1[iTrunk][m_ucjAddr[iTrunk]]-=
				m_ucScanConvPointNum1[iTrunk][m_ucjAddr[iTrunk]][m_uckConV[iTrunk][m_ucjAddr[iTrunk]]];//地址上的点数减去扫描点数
			m_unScanTrunkPointNum1[iTrunk]-=
				m_ucScanConvPointNum1[iTrunk][m_ucjAddr[iTrunk]][m_uckConV[iTrunk][m_ucjAddr[iTrunk]]];//干线上的点数减去扫描点数
			m_ucScanConvPointNum1[iTrunk][m_ucjAddr[iTrunk]][m_uckConV[iTrunk][m_ucjAddr[iTrunk]]]=0;
			unCmdNo=0x00;
		}
		
		m_ucRXConvID[iTrunk]=m_structSCANADDR[iTrunk][m_ucjAddr[iTrunk]][m_uckConV[iTrunk][m_ucjAddr[iTrunk]]].snConVType;
		GetAddrComd(iTrunk,m_ucjAddr[iTrunk],m_ucRXConvID[iTrunk],unCmdNo);   //得到命令

	}

	if(m_bSendBitCmd[iTrunk])//hand cmd: bitcmd m_bSendHandCmd=TRUE;
	{
			m_chCmd[iTrunk][0]=0x80 | m_structBITADDRCMD[iTrunk].ucAddr;
			m_chCmd[iTrunk][1]=m_structBITADDRCMD[iTrunk].ucLCmd;
     		m_bSendBitCmd[iTrunk]=FALSE;
	}
	return TRUE;
}

BOOL CCommStatusFM::ResetTimer()
{
	KillTimer(100);
	if(SetTimer(100,gunScantimeDelay+OFFSETWINPATCH,NULL))
		return TRUE;
	else
		return FALSE;
}

void CCommStatusFM::StopScan()
{
	KillTimer(100);
	for(UINT iTrunk=0;iTrunk<MAX_TRUNK_NUMBER;iTrunk++)
	{
		if(!m_unScanTrunkPointNum[iTrunk]) continue; //no point to scan
		if(!m_bTrunkPortOpen[iTrunk]) continue;
		SetDispTrunkSignal(iTrunk, 1);
	}
	m_bStartScan=FALSE;

}

static UINT counttest=0;

void CCommStatusFM::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	CKJMonitorApp* pApp=(CKJMonitorApp* )AfxGetApp();

//	SocketServer.ManageClientD();
	SocketServer.SyncTableCollectData();


	unsigned char ucSuccessProcent=0;
	unsigned char m_ucRXData ;
	CString strProcent,strTXNum,strRXNum,strCommStatus,strRX0,strRX1;

				m_bScanLedOnOFF[0]=!m_bScanLedOnOFF[0];
				if(m_bScanLedOnOFF[0])
					SetDispTrunkSignal(0, 2);
				else
					SetDispTrunkSignal(0, 0);

	    		m_ucScanSuccessCount[0][m_unRepeaScantTimes]++;
	    		m_ucScanTXCount[0][m_unRepeaScantTimes]++ ;
	    		ucSuccessProcent=100;
			if(m_ucScanSuccessCount[0][m_unRepeaScantTimes] > 10)
				m_ucScanSuccessCount[0][m_unRepeaScantTimes] = 1 ;
			if(m_ucScanTXCount[0][m_unRepeaScantTimes] > 10)
				m_ucScanTXCount[0][m_unRepeaScantTimes] = 1 ;
            if(m_unRepeaScantTimes < 4){
		   		m_structValueState[m_unRepeaScantTimes+1].ucLowValue =m_structValueState[m_unRepeaScantTimes+1].ucLowValue +10 ;
		    	 m_ucRXData = m_structValueState[m_unRepeaScantTimes+1].ucLowValue ;
			}
            else{
		    	 m_ucRXData = m_ucScanSuccessCount[0][m_unRepeaScantTimes]  ;
				if(m_ucRXData < 6)
		        	 m_ucRXData = m_structValueState[m_unRepeaScantTimes+1].ucLowValue = 1 ;
				else
		        	 m_ucRXData = m_structValueState[m_unRepeaScantTimes+1].ucLowValue = 0 ;
			}

 			unsigned char ucAddr2ItemPos = m_unRepeaScantTimes % MAX_LIST_ITEM_NUM;
    		if((m_ucTrunkDisp== 0 ) && (m_ucAddrDisp*MAX_LIST_ITEM_NUM <= m_unRepeaScantTimes) && ((m_ucAddrDisp+1)*MAX_LIST_ITEM_NUM > m_unRepeaScantTimes))
			{
				    strTXNum.Format("%d",m_ucScanTXCount[0][m_unRepeaScantTimes]);
			    	strRXNum.Format("%d",m_ucScanSuccessCount[0][m_unRepeaScantTimes]);
					// "地址号""发送""接收""点数""剩余" &&(bdispafx)& 0x0f
					    m_ctrlList.SetItemText(ucAddr2ItemPos*2+1,1, LPCTSTR(strTXNum));
					    m_ctrlList.SetItemText(ucAddr2ItemPos*2+1,2, LPCTSTR(strRXNum));

			    		strProcent="√正确";
			     		strRX0.Format("=0X%02X=%3d",m_unRepeaScantTimes,m_unRepeaScantTimes);
			            strRX0=m_String2DataType.Char2Binary(m_unRepeaScantTimes)+strRX0;
		                strRX1.Format("=0X%02X=%3d",m_ucRXData ,m_ucRXData );
			            strRX1=m_String2DataType.Char2Binary(m_ucRXData)+strRX1;

						m_ctrlList.SetItemText(ucAddr2ItemPos*2+1,4, LPCTSTR(strRX0));
				    	m_ctrlList.SetItemText(ucAddr2ItemPos*2+1,5, LPCTSTR(strRX1));

				m_ctrlList.SetItemText(ucAddr2ItemPos*2+1,3, LPCTSTR(strProcent));
			    SetProgressPos(ucAddr2ItemPos, ucSuccessProcent);

			}

//			if(m_ucRXData >254)
//				m_structValueState[m_unRepeaScantTimes+1].ucLowValue = 0 ;
		    	pApp->pMPT->DoRefreshPoint(m_unRepeaScantTimes+1,m_ucRXData);

    m_unRepeaScantTimes++ ;
	if(m_unRepeaScantTimes > 7)
		m_unRepeaScantTimes = 0 ;

	CFormView::OnTimer(nIDEvent);
}


void CCommStatusFM::ResetDispProgressCtrl()
{
	if(!m_unScanTrunkPointNum[m_ucTrunkDisp]) return; //no point to scan
	if(!m_bTrunkPortOpen[m_ucTrunkDisp]) return;  //port not open
	for(int j = m_ucAddrDisp*MAX_LIST_ITEM_NUM; j < (m_ucAddrDisp+1)*MAX_LIST_ITEM_NUM; j++)
	{
		//if(!m_unScanAddrPointNum[m_ucTrunkDisp][j]) continue;
		unsigned char ucAddr2ItemPos = j % MAX_LIST_ITEM_NUM;
		SetProgressColor(ucAddr2ItemPos,FALSE);
		SetProgressPos(ucAddr2ItemPos,0);
	}

}

void CCommStatusFM::InitDispProgressCtrl()
{
	if(!m_unScanTrunkPointNum[m_ucTrunkDisp]) return; //no point to scan
	if(!m_bTrunkPortOpen[m_ucTrunkDisp]) return;  //port not open
//	BYTE  LIST_ITEM_NUM =m_ucAddrDisp*MAX_LIST_ITEM_NUM;
    
//	UINT k = m_ucAddrDisp*MAX_LIST_ITEM_NUM;

	for(unsigned char j = m_ucAddrDisp*MAX_LIST_ITEM_NUM; j < ((m_ucAddrDisp+1)*MAX_LIST_ITEM_NUM); j++)
	{
		if(!m_unScanAddrPointNum[m_ucTrunkDisp][j]) continue;
		unsigned char ucAddr2ItemPos = j % MAX_LIST_ITEM_NUM;
		SetProgressColor(ucAddr2ItemPos,TRUE);
	}
//	m_bFirstRefreshProgress=TRUE;

}


BOOL CCommStatusFM::Scan()
{
	UINT iTrunk,jAddr,kConV;
	if(!m_bCycleScan)  //初始新的扫描周期
	{
		for(iTrunk=0;iTrunk<MAX_TRUNK_NUMBER;iTrunk++)
		{
			if(!m_unScanTrunkPointNum[iTrunk]) continue; //no point to scan
			m_unScanTrunkPointNum1[iTrunk]=m_unScanTrunkPointNum[iTrunk];
			m_unScanTrunkPointNum2[iTrunk]=m_unScanTrunkPointNum[iTrunk];

			m_ucjAddr[iTrunk]=0;
			for( jAddr=0;jAddr<MAX_ADDR_NUMBER;jAddr++)
			{
				if(!m_unScanAddrPointNum[iTrunk][jAddr]) continue;
				m_unScanAddrPointNum1[iTrunk][jAddr]=m_unScanAddrPointNum[iTrunk][jAddr];
				m_unScanAddrPointNum2[iTrunk][jAddr]=m_unScanAddrPointNum[iTrunk][jAddr];

				m_uckConV[iTrunk][jAddr]=0;
				for( kConV=0;kConV<MAX_MULTICONV_NUMBER;kConV++)
				{
					m_ucScanConvPointNum1[iTrunk][jAddr][kConV]=m_ucScanConvPointNum[iTrunk][jAddr][kConV];
					m_ucScanConvPointNum2[iTrunk][jAddr][kConV]=m_ucScanConvPointNum[iTrunk][jAddr][kConV];
				}
			}
		}
		m_bCycleScan=TRUE;  //cycle begin
	}

   for(iTrunk=0;iTrunk<MAX_TRUNK_NUMBER;iTrunk++)
   {
//  	if(m_ucRxCount[iTrunk] == 0)
	{
	   if(ScanGetNextCmd(iTrunk))
	   {
		   if((m_bStartScan)&&(!m_bSendBitCmd[iTrunk]))   //m_bSendHandCmd=FALSE;&&(!m_bSendspuCmd[iTrunk])
		   {
			   if(ScanSendCommand(iTrunk))
			   {
					m_ucScanTXCount[iTrunk][m_ucjAddr[iTrunk]]++;
					if(m_ucScanTXCount[iTrunk][m_ucjAddr[iTrunk]]>MAX_SUCCESS_DISP_NUM)
					{
						m_ucScanTXCount[iTrunk][m_ucjAddr[iTrunk]]=1;
						m_ucScanSuccessCount[iTrunk][m_ucjAddr[iTrunk]]=0;
					}
			   }
		   }
		   if((m_bSendBitCmd[iTrunk])&&(m_bHandCmdCanSend)) //m_bSendHandCmd=TRUE; and can send now&&(!m_bSendspuCmd[iTrunk])
		   {
			   if(ScanSendCommand(iTrunk))
			   {
				   //AfxMessageBox("send success");
				   m_bHandCmdSendFail=FALSE; //发送成功
				   m_bHandCmdCanSend=FALSE;  //现在不能再发送
			   }
			   else
			   {
				   m_bHandCmdSendFail=TRUE;  //发送失败，一般原因是串口没有打开
			   }
		   }
	   }
	}
/*	else
	{
		   if((m_bStartScan)&&(!m_bSendBitCmd[iTrunk])) 
		   {
			   if(ScanSendCommand(iTrunk))
			   {
					m_ucScanTXCount[iTrunk][m_ucjAddr[iTrunk]]++;
					if(m_ucScanTXCount[iTrunk][m_ucjAddr[iTrunk]]>MAX_SUCCESS_DISP_NUM)
					{
						m_ucScanTXCount[iTrunk][m_ucjAddr[iTrunk]]=1;
						m_ucScanSuccessCount[iTrunk][m_ucjAddr[iTrunk]]=0;
					}
			   }
		   }
	}*/
   }
	if(m_bCycleScan)  //扫描周期是否结束
	{
		BOOL bCycleEnd=TRUE;
		for(iTrunk=0;iTrunk<MAX_TRUNK_NUMBER;iTrunk++)
		{
			if(m_unScanTrunkPointNum1[iTrunk]>0) 
			{
				bCycleEnd=FALSE;
				break;
			}
		}
		if(bCycleEnd)
		{
			m_bCycleScan=FALSE;  //cycle begin
			if(AllDate)
				m_bHaltDisp++;
		}
	}

	return TRUE;
}


unsigned char CCommStatusFM::GetConvChannels(unsigned char ucConvID)
{
	unsigned char ucChannel = 0;//9/9/1
	switch(ucConvID)
	{

	case MS8IN_B38:  ucChannel = 8; break;//1. ◆B38-开关量输入[8路]
	case A8IN8BIT_MCA: 
		ucChannel = 8; break;//7. MCA-8路模拟量输入信号转接器[12位8路]
	case S8IN_B38: 
		ucChannel = 8; break;//11. B38-开关量输入[8路]
	case A8IN8BIT_MC8 : 
		ucChannel = 8; break;//8  MC8-8路模拟量输入信号转接器[8位8路]
	case S8OUT_B48:    // 12. B48-开关量输出[8路]
		ucChannel=8;
		break;
	case MS5OUT_B25: 
		ucChannel = 5;
		break;//2. ◆B25-开关量输出[5路]
	case S5OUT_B25:  //13 . B25-开关量输出[5路]
		ucChannel = 5;
		break;
	case MA4IN:  //3. ◆4-A50
		ucChannel = 4;
		break;
	case A4IN: 
		//15. 4-A50
		ucChannel=4;
		break;
	case MP16IN:  //4.◆ D1-脉冲计数输入累加器[16位] 
		ucChannel = 2;
		break;
	case P16IN :         // 10 D1-脉冲计数输入累加器[16位]
		ucChannel = 2;
		break;
	case A1IN8BIT_CH4ICO:  	//5. ICO-智能型甲烷/一氧化碳传感器[8位1路]
		ucChannel = 1;
		break;
	case A1IN8BIT_A50:    // 6. A50-A型单路模拟量输入信号转接器[8位1路]
		ucChannel = 1;
		break;
	case A1OUT8BIT_C35 :  //9. C35-模拟量输出信号转接器(C3-C5)[6位]
		ucChannel=1;
		break;
	default:
		break;
	}
	return ucChannel;
}

//GetAddrComd中unCmdNo=0~7
UINT CCommStatusFM::GetAddrComd(UINT unTrunkNo,UINT unAddr,UINT unConvID,UINT unCmdNo)
{
	if(unAddr>127) return 10;
	//地址赋值
	m_chCmd[unTrunkNo][0]=0x80|unAddr;

	switch(unConvID)
	{
	case MS8IN_B38:  //1. ◆B38-开关量输入[8路]
		m_chCmd[unTrunkNo][1]=0x00;
		break;
	case MS5OUT_B25:  //2. ◆B25-开关量输出[5路]
			m_chCmd[unTrunkNo][1]=0x40; // 0x40:ask for answer, no out
		break;
	case MA4IN:  //3. ◆4-A50
		m_chCmd[unTrunkNo][1]=0x10|unCmdNo;
		break;
	case MP16IN:  //4.◆ D1-脉冲计数输入累加器[16位]
		m_chCmd[unTrunkNo][1] = 0x01 + unCmdNo;;  
		break;
	case A1IN8BIT_CH4ICO:  //5. ICO-智能型甲烷/一氧化碳传感器[8位1路]
		m_chCmd[unTrunkNo][1]=0x08;
		break;
	case A1IN8BIT_A50:    // 6. A50-A型单路模拟量输入信号转接器[8位1路]
		m_chCmd[unTrunkNo][1]=0x08;
		break;
	case  A8IN8BIT_MCA:    //7. MCA-8路模拟量输入信号转接器[12位8路]
		m_chCmd[unTrunkNo][1]=0x10|unCmdNo;  ///10-17 (0/1/2) low8 high4
		break;
	case A8IN8BIT_MC8 :   //8  MC8-8路模拟量输入信号转接器[8位8路]
		m_chCmd[unTrunkNo][1]=0x10|unCmdNo;  ///10-17 (0/1/2) low8 high0
		break;
	case A1OUT8BIT_C35 :  //9. C35-模拟量输出信号转接器(C3-C5)[6位]
			m_chCmd[unTrunkNo][1]=0x03;  //读数后6位输出0-63个码
		break;
    case P16IN :         // 10 D1-脉冲计数输入累加器[16位]
		m_chCmd[unTrunkNo][1]=0x01 + unCmdNo;
		
		break;
	case S8IN_B38:  	   //11. B38-开关量输入[8路]
		m_chCmd[unTrunkNo][1]=0x00;
		break;
	case S8OUT_B48:    // 12. B48-开关量输出[8路]
		m_chCmd[unTrunkNo][1]=0x70;
		break;
	case S5OUT_B25:  //13 . B25-开关量输出[5路]
			m_chCmd[unTrunkNo][1]=0x40; // 0x40:ask for answer, no out
		break;
	case A4IN:  //15. 4-A50
		m_chCmd[unTrunkNo][1]=0x10|unCmdNo;
		break;
	default:
		break;
	}
	return 0;
}

BOOL CCommStatusFM::ScanSendCommand(UINT unTrunk)
{
	if(!m_bTrunkPortOpen[unTrunk])
	{
		CString strtemp;
		strtemp.Format("干线 %d 对应的串口没有打开，请查找相关原因：干线与串口设置是否正确",unTrunk);
		AfxMessageBox(strtemp);
		return FALSE;
	}
		unsigned char cmd[2];
		
	cmd[0]=m_chCmd[unTrunk][0];
	cmd[1]=m_chCmd[unTrunk][1];
	m_SerialPort[unTrunk].WriteToPort(cmd,2);

	return TRUE;
}
/*
BOOL CCommStatusFM::GetResponseData(UINT unCommPort)
{
	
	return TRUE;
}
*/
void CCommStatusFM::ConnectDB()
{
	try
	{
		m_SQLDirect.Init();
		m_SQLDirect1.Init();
		if(m_SQLDirect.Connect(_T("masterdefine"),_T("kj86"),_T("kj86")))
			AfxMessageBox("AddUser:无法连接用户参数数据库,请确定SQL SERVER服务是否运行!");
		if(m_SQLDirect1.Connect(_T("masterdefine"),_T("kj86"),_T("kj86")))
			AfxMessageBox("AddUser:无法连接用户参数数据库,请确定SQL SERVER服务是否运行!");
	}
	catch(CDBException *e)
	{
		e->ReportError();
		return;
	}
}

void CCommStatusFM::OnDestroy() 
{
	CFormView::OnDestroy();
	
	// TODO: Add your message handler code here
	m_SQLDirect.Close();
	m_SQLDirect1.Close();
	if(gbScanTimeDelayThreadCtrl)
		this->StopScan();
	for(UINT i=0;i<MAX_TRUNK_NUMBER;i++)
	{
		if(!m_bTrunkPortOpen[i]) continue;
		m_SerialPort[i].ClosePort();
	}
	if(m_SerialPortTest.m_hComm!=NULL)
		m_SerialPortTest.ClosePort();
}

void CCommStatusFM::SetStructMONITORPOINT(unsigned short usPointNo, 
										  unsigned short usMonitorNo,
											unsigned char ucTrunkNo,
											unsigned char ucAddrNo,
											unsigned char ucConvID,
											BOOL bValueType,
											BOOL bScan,
                                            unsigned char unChannel)
{
	m_structMONITORPOINT[usPointNo].usMonitorNo=usMonitorNo;
	m_structMONITORPOINT[usPointNo].ucTrunkNo=ucTrunkNo;
	m_structMONITORPOINT[usPointNo].ucAddrNo=ucAddrNo;
	m_structMONITORPOINT[usPointNo].bValueType=bValueType;
	m_structMONITORPOINT[usPointNo].bScan=bScan;
	m_structMONITORPOINT[usPointNo].unChannel = unChannel;

	m_structMONITORPOINT[usPointNo].strLabel =_T("");
	m_structMONITORPOINT[usPointNo].strExplain =_T("");
	m_structMONITORPOINT[usPointNo].strWarnCause =_T("");
}

UINT CCommStatusFM::ScanBuildQueue()
{
	CString strSQL;
///	UINT unConvOnAddrID;
	m_bCycleScan=FALSE;
	CMainFrame* pFWnd=(CMainFrame*)AfxGetMainWnd();
	CFMMonitorPoint *pFMMonitorPoint=pFWnd->m_pFMMonitorPoint;

	for(UINT i=0;i<MAX_TRUNK_NUMBER;i++)
	{
		m_unScanTrunkPointNum[i]=m_unScanTrunkPointNum1[i]=m_unScanTrunkPointNum2[i]=0; //point num on trunk
		for(UINT j=0;j<MAX_ADDR_NUMBER;j++)
		{
			m_unScanAddrPointNum[i][j]=m_unScanAddrPointNum1[i][j]=m_unScanAddrPointNum2[i][j]=0;
			for(UINT k=0;k<MAX_MULTICONV_NUMBER;k++)
			{
				m_ucScanConvPointNum1[i][j][k]=0;
				m_ucScanConvPointNum2[i][j][k]=0;

				m_ucScanConvPointNum[i][j][k]=0;    //how many points to scan on CONV
				m_structSCANADDR[i][j][k].bScan=0;
				m_structSCANADDR[i][j][k].bValueType=0;
				m_structSCANADDR[i][j][k].snConVType=0;
//				m_structSCANADDR[i][j][k].snFreq=0;
				for(unsigned char kucChannel=0; kucChannel<MAX_CHANNEL_NUMBER; kucChannel++)
				{
					m_structSCANADDR[i][j][k].structPointInfo[kucChannel].usPointNo=0;
					m_structSCANADDR[i][j][k].structPointInfo[kucChannel].bScan=0;
				}
			}
		}
	}

	for(int m=0;m<MAX_POINT_NUMBER;m++)       //init monitor
	{
		SetStructMONITORPOINT(m,0,0,0,0,0,0,0);
		pFMMonitorPoint->m_nPointNoForMonitorNo[m]=-1;
	}

	try
	{
		//get monitor info
		for(UINT m=1;m<9;m++)
		{
				int intMonitorNo=m ;
				int intPointNo=m ;
				SetStructMONITORPOINT(intPointNo,intMonitorNo,0,0,0,0,0,0);  //**change subscript
				pFMMonitorPoint->m_nPointNoForMonitorNo[intMonitorNo]=intPointNo;
		}

		for(UINT n=1;n<9;n++)
		{
					m_structValueState[n].Ac_state=0;
					m_structValueState[n].alarm_state=0;
					m_structValueState[n].ucHighValue= 0;
					m_structValueState[n].ucLowValue= 0;
					m_structValueState[n].ufData=0;
					m_structValueState[n].unDelay=0;
					m_structValueState[n].Warn_state=0;
					m_structValueState[n].WarnColor=2;
					m_structValueState[1].ucLowValue = 0;
					m_structValueState[2].ucLowValue = 64;
					m_structValueState[3].ucLowValue = 128;
					m_structValueState[4].ucLowValue = 192;

					m_structMONITORPOINT[n].bScan= 1;
					m_structMONITORPOINT[n].ucTrunkNo= 1 ;
					m_structMONITORPOINT[n].ucAddrNo= n-1 ;
				if(n<5){
					m_structMONITORPOINT[n].bValueType= 1;
	    			m_structSCANADDR[0][n-1][0].bValueType=1;
				}
				else{
					m_structMONITORPOINT[n].bValueType= 0;
		    		m_structSCANADDR[0][n-1][0].bValueType=0;
				}
					m_structMONITORPOINT[n].unChannel = 1;       
					m_structMONITORPOINT[n].strLabel = "RobusTech";       
					m_structMONITORPOINT[n].strExplain = "  润蓝科技  010-81405430/13501325918 ";    
                    m_structMONITORPOINT[n].strWarnCause="  演示版  ";
		}
		
					m_structMONITORPOINT[1].ucConvID=5;
							m_structANOLOG[1].dfScopeMin = (double) 0 ;   //fMeasureMin
							m_structANOLOG[1].dfScopeMax = (double) 5 ;   //"fMeasureMax"
					    	m_structANOLOG[1].unWarnCause=(UINT) 10;
							m_structANOLOG[1].usWarnMode = (int) 1 ; //"unWarnMode"
							m_structANOLOG[1].unWarnMin = (double) 3 ;   //"unWarnMinValue"
							m_structANOLOG[1].unWarnMax = (double) 4 ;  //"unWarnMaxValue"
							m_structANOLOG[1].unWarnDelay =  0 ;  
							m_structANOLOG[1].usPrecision =  2 ;  
							m_structANOLOG[1].usUnit = "v";

					m_structMONITORPOINT[2].ucConvID=6;
							m_structANOLOG[2].dfScopeMin = (double) 4 ;   //fMeasureMin
							m_structANOLOG[2].dfScopeMax = (double) 20 ;   //"fMeasureMax"
					    	m_structANOLOG[2].unWarnCause=(UINT) 10;
							m_structANOLOG[2].usWarnMode = (int) 2 ; //"unWarnMode"
							m_structANOLOG[2].unWarnMin = (double) 10 ;   //"unWarnMinValue"
							m_structANOLOG[2].unWarnMax = (double) 15 ;  //"unWarnMaxValue"
							m_structANOLOG[2].unWarnDelay =  0 ;  
							m_structANOLOG[2].usPrecision =  2 ;  
							m_structANOLOG[2].usUnit = "ma";

					m_structMONITORPOINT[3].ucConvID=5;
							m_structANOLOG[3].dfScopeMin = (double) 1 ;   //fMeasureMin
							m_structANOLOG[3].dfScopeMax = (double) 5 ;   //"fMeasureMax"
					    	m_structANOLOG[3].unWarnCause=(UINT) 10;
							m_structANOLOG[3].usWarnMode = (int) 3 ; //"unWarnMode"
							m_structANOLOG[3].unWarnMin = (double) 3 ;   //"unWarnMinValue"
							m_structANOLOG[3].unWarnMax = (double) 4 ;  //"unWarnMaxValue"
							m_structANOLOG[3].unWarnDelay =  0 ;  
							m_structANOLOG[3].usPrecision =  2 ;  
							m_structANOLOG[3].usUnit = "v";

					m_structMONITORPOINT[4].ucConvID=10;
							m_structANOLOG[4].usUnit = "k";


				    m_structMONITORPOINT[5].ucConvID=11;
							m_structSWITCH[5].usAC= 1;
							m_structSWITCH[5].unWarnDelay= 0;
							m_structSWITCH[5].unWarnCause=(UINT)10;

				    m_structMONITORPOINT[6].ucConvID=13;
							m_structSWITCH[6].usAC= 2;
							m_structSWITCH[6].unWarnDelay= 0;
							m_structSWITCH[6].unWarnCause=(UINT)10;

				    m_structMONITORPOINT[7].ucConvID=11;
							m_structSWITCH[7].usAC= 3;
							m_structSWITCH[7].unWarnDelay= 0;
							m_structSWITCH[7].unWarnCause=(UINT)10;

				    m_structMONITORPOINT[8].ucConvID=11;
							m_structSWITCH[8].usAC= 0;
							m_structSWITCH[8].unWarnDelay= 0;
							m_structSWITCH[8].unWarnCause=(UINT)10;

        
	}
	catch(CDBException *e)
	{
		e->ReportError();
		return 10;
	}

	//get the point number to scan on every trunk and its addr 
	CString strtemp="",strtemp1="";  //test

	for(i=0;i<MAX_TRUNK_NUMBER;i++)
	{
		for(UINT j=0;j<MAX_ADDR_NUMBER;j++)
		{
			for(UINT k=0;k<MAX_MULTICONV_NUMBER;k++)
			{
				m_unScanAddrPointNum[i][j]+=m_ucScanConvPointNum[i][j][k];//需要扫描的点数
				
				if(m_ucScanConvPointNum[i][j][k]) //test
				{
					strtemp1.Format("m_ucScanConvPointNum[%d][%d][%d]=%d\n\r",i,j,k,m_ucScanConvPointNum[i][j][k]);
					strtemp+=strtemp1;
				}

			}
			m_unScanTrunkPointNum[i]+=m_unScanAddrPointNum[i][j];
		}

	}

	return 0;
}

BOOL CCommStatusFM::InitTrunkCOMPort()
{
	UINT i;
	for(i=0;i<MAX_TRUNK_NUMBER;i++)
	{
		m_unSerialPortforTrunk[i]=0;
	}

//******	AfxMessageBox("IN数据表trunkvsport中没数,打开不成功");

/*	try
	{
		if( m_SQLDirect.ExecuteSQL(_T("SELECT * FROM trunkvsport"))==SQL_SUCCESS)
		{
			int nRet=m_SQLDirect.Fetch();
			while(!nRet)
			{
				UINT untrunkno=m_String2DataType.String2Int(m_SQLDirect.GetCol(1));
				UINT unportno=m_String2DataType.String2Int(m_SQLDirect.GetCol(2));
				BOOL buse=m_String2DataType.Str2Bool(m_SQLDirect.GetCol(3));
				if((buse)&&(unportno))
				{
					m_unSerialPortforTrunk[untrunkno-1]=unportno;   //**change subscript
				}
				nRet=m_SQLDirect.Fetch();
			}
		}
		else
			AfxMessageBox("数据表trunkvsport中没数,打开不成功");

	}
	catch(CDBException *e){
	e->ReportError();
	EndWaitCursor();
	return FALSE;
	}
*/
					m_unSerialPortforTrunk[0]=1;   //**change subscript


	int nBaud=4800;
	int nCom=0;
	char cParity='E';
	int nDatabits=8;
	int nStopbits=1;
	DWORD dwCommEvents=EV_RXFLAG | EV_RXCHAR;
	CString strStatus,strStatus1;
	strStatus.Empty();
	BOOL bAnyComOpen=FALSE;
	for(i=0;i<MAX_TRUNK_NUMBER;i++)
	{
		if(!m_unSerialPortforTrunk[i]) 
			continue;
		nCom=m_unSerialPortforTrunk[i];
		if(m_bTrunkPortOpen[i]) continue;  //already open
		if(m_SerialPort[i].m_hComm!=NULL)
		{
			m_bTrunkPortOpen[i]=TRUE; continue;
		}
	
		//if(m_SerialPort[i].m_hComm!=NULL)
		//	m_SerialPort[i].ClosePort();

		if (m_SerialPort[i].InitPort(this, nCom, nBaud,cParity,nDatabits,nStopbits,dwCommEvents,512))
		{
			m_SerialPort[i].StartMonitoring();
			m_bTrunkPortOpen[i]=TRUE;
			SetDispTrunkSignal(i, 1);
			bAnyComOpen=TRUE;

			//strStatus+=strStatus1;
		}
		else
		{
			strStatus.Format("在主机上没有发现干线%d对应的串口%d",i+1,nCom);
			AfxMessageBox(strStatus);
			m_SerialPort[i].ClosePort();
		}
		//if(bAnyComOpen)
		//	strStatus+="已经打开";
		//AfxMessageBox(strStatus);
	}
	return TRUE;

}

BOOL CCommStatusFM::GetCommPara()
{
/*	try
	{
		CString strSQL;
		if( m_SQLDirect.ExecuteSQL("SELECT * FROM uScanPara")==SQL_SUCCESS)
		{
			int nRet=m_SQLDirect.Fetch();
			if(!nRet)
			{
				gunScantimeDelay = m_String2DataType.String2Int(m_SQLDirect.GetCol(1));
				gunRepeaScantTimes = m_String2DataType.String2Int(m_SQLDirect.GetCol(2));
				return TRUE;
			}
			else
			{
				AfxMessageBox("无法从数据库表uScanPara得到扫描时间和扫描重复次数等参数，请先设置通信参数");
				return FALSE;
			}
		}
		else
		{
			AfxMessageBox("无法打开数据库表uScanPara");
			return FALSE;
		}

	}
	catch(CDBException *e){
	e->ReportError();
	return FALSE;
	}*/
				gunScantimeDelay = 1000;
				gunRepeaScantTimes =  0 ;
				return TRUE;
}

BOOL CCommStatusFM::TestSerailPort(UINT nPort)
{
	int nBaud=4800;
	int nCom=(int)nPort;
	char cParity='E';
	int nDatabits=8;
	int nStopbits=1;
	DWORD dwCommEvents=EV_RXFLAG | EV_RXCHAR;
	CString strStatus;

	for(UINT i=0;i<MAX_TRUNK_NUMBER;i++)
	{
		if(m_unSerialPortforTrunk[i]!=nPort) continue;
		if(m_bTrunkPortOpen[i]) 
		{
			strStatus.Format("串口%d正常，且正在使用",nCom);
			AfxMessageBox(strStatus,MB_ICONINFORMATION);
			return TRUE;  //already open
		}
	}

	if (m_SerialPortTest.InitPort(this, nCom, nBaud,cParity,nDatabits,nStopbits,dwCommEvents,512))
	{
		strStatus.Format("串口 %d (COM%d) 正常, 可以使用",nCom,nCom);
		AfxMessageBox(strStatus,MB_ICONINFORMATION);
		m_SerialPortTest.ClosePort();
	}
	else
	{
		strStatus.Format("在主机上没有发现串口%d",nCom);
		AfxMessageBox(strStatus);
	}
	return TRUE;
}

BOOL CCommStatusFM::CloseAllSerailPort()
{
	for(UINT i=0;i<MAX_TRUNK_NUMBER;i++)
	{
		//if(((!m_bTrunkPortOpen[i]))&&(m_SerialPort[i].m_hComm==NULL))
		//	continue;  //not open
		if(!m_bTrunkPortOpen[i])
			continue;  //not open

		if(m_SerialPort[i].m_hComm!=NULL)
		{
			//m_SerialPort[i].StopMonitoring();
			m_SerialPort[i].ClosePort();
			m_bTrunkPortOpen[i]=FALSE;
			m_unSerialPortforTrunk[i]=0;
		}
		SetDispTrunkSignal(i, 0);
	}
//	if(m_SerialPortTest.m_hComm!=NULL)
//		m_SerialPortTest.ClosePort();

	return TRUE;
}

void CCommStatusFM::OnSelchangeComboTrunkdisp() 
{
	if(m_ucTrunkDisp==m_ctrlComboTrunkDisp.GetCurSel())
		return;
	m_ctrlComboAddrDisp.SetCurSel(0);
	ResetListTable(m_ucTrunkDisp,m_ucAddrDisp);
	ResetDispProgressCtrl();
	m_ucTrunkDisp=m_ctrlComboTrunkDisp.GetCurSel();
	m_ucAddrDisp=m_ctrlComboAddrDisp.GetCurSel();
	InitDispProgressCtrl();
}

void CCommStatusFM::OnSelchangeComboAddrdisp() 
{
	if(m_ucAddrDisp==m_ctrlComboAddrDisp.GetCurSel())
		return;
	ResetListTable(m_ucTrunkDisp,m_ucAddrDisp);
	ResetDispProgressCtrl();
	m_ucAddrDisp=m_ctrlComboAddrDisp.GetCurSel();
	InitDispProgressCtrl();
}


void CCommStatusFM::ResetListTable(UINT unTrunk,UINT unAddr)  //unAddr = m_ucAddrDisp
{
	int iItemOffset2Addr0=unAddr * MAX_LIST_ITEM_NUM;  //unAddr=0-7
	int iItemOffset2Addr1=m_ctrlComboAddrDisp.GetCurSel() * MAX_LIST_ITEM_NUM;
	
	for(int iItem=0;iItem<MAX_LIST_ITEM_NUM;iItem++)
	{
		CString strAddr;
		strAddr.Format("     地址%d",iItem + iItemOffset2Addr1  );    //**change subscript
		m_ctrlList.SetItemText(2*iItem+1, 0,strAddr);
		//m_ctrlList.SetItem(iItem, 0, LVIF_TEXT, strAddr, 0, NULL, NULL, NULL);

	}
   //m_ctrlList.SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, 0, (LPARAM)LVS_EX_FULLROWSELECT); 
 
   for (iItem=0; iItem<MAX_LIST_ITEM_NUM;iItem++)
    {
		//if(!m_unScanAddrPointNum[unTrunk][iItem + iItemOffset2Addr0]) continue;  //
		for(int iSubPos=1;iSubPos<MAX_LIST_SUBCOLLUM_NUM ;iSubPos++)
		{
			m_ctrlList.SetItemText(iItem*2+1,iSubPos, LPCTSTR(""));
		}
	}
/*	for(int i=0;i<MAX_ADDR_NUMBER;i++)
		for(int j=0;j<MAX_SUCCESS_DISP_NUM;j++)
		{
			m_structDISP[i][j].bFirst=TRUE;
			m_structDISP[i][j].bStatus=FALSE;
		}
*/
  
}

void CCommStatusFM::SetListCtrlTable()
{
	m_ctrlList.InsertColumn(0, _T("  地址号 "),   LVCFMT_CENTER, 20);
	m_ctrlList.InsertColumn(1, _T("发送"),   LVCFMT_CENTER, 10);
	m_ctrlList.InsertColumn(2, _T("接收"),   LVCFMT_CENTER, 10);
	m_ctrlList.InsertColumn(3, _T("通信状态"), LVCFMT_CENTER, 20);
	m_ctrlList.InsertColumn(4, _T("    标识符     "), LVCFMT_CENTER, 40);
	m_ctrlList.InsertColumn(5, _T("    采样数据     "), LVCFMT_CENTER, 40);
//	m_ctrlList.InsertColumn(6, _T(""), LVCFMT_CENTER, 20);

	// set some extnded styles
	m_ctrlList.SetExtendedStyle (LVS_EX_FULLROWSELECT|LVS_EX_FLATSB);
//	m_ctrlList.SetExtendedStyle (LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT|LVS_EX_FLATSB);

	for(int iItem=0;iItem<MAX_LIST_ITEM_NUM;iItem++)
	{
		CString strAddr;
		strAddr.Format("%d",iItem);   //**change subscript    //11/1地址
		m_ctrlList.InsertItem(2*iItem, "", 0);
		m_ctrlList.InsertItem(2*iItem+1, 0/*strAddr*/, 0);      //11/1
		//m_ctrlList.SetItem(iItem, 0, LVIF_TEXT, strAddr, 0, NULL, NULL, NULL);

	}

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

}


void CCommStatusFM::SetProgressCtrl()
{
	CFont font;
	LOGFONT lf;
	memset (&lf, 0, sizeof (LOGFONT));
	_tcscpy (lf.lfFaceName, _T("Arial")); 
	lf.lfWeight = 400;
	lf.lfHeight = 15;
	font.CreateFontIndirect(&lf);
	m_ctrlProgress0.SetFont(&font);
	m_ctrlProgress1.SetFont(&font);
	m_ctrlProgress2.SetFont(&font);
	m_ctrlProgress3.SetFont(&font);
	m_ctrlProgress4.SetFont(&font);
	m_ctrlProgress5.SetFont(&font);
	m_ctrlProgress6.SetFont(&font);
	m_ctrlProgress7.SetFont(&font);
	m_ctrlProgress8.SetFont(&font);
	m_ctrlProgress9.SetFont(&font);
	m_ctrlProgress10.SetFont(&font);
	m_ctrlProgress11.SetFont(&font);
	m_ctrlProgress12.SetFont(&font);
	m_ctrlProgress13.SetFont(&font);
	m_ctrlProgress14.SetFont(&font);
	m_ctrlProgress15.SetFont(&font);

	for(unsigned char i=0;i<MAX_LIST_ITEM_NUM;i++)
		SetProgressColor(i,FALSE);
}

//bUse: 0: No point 1: in use
void CCommStatusFM::SetProgressColor(unsigned char ucNo,BOOL bUse)
{
	COLORREF colorBK;
	COLORREF colorGrad1;
	COLORREF colorGrad2;
	COLORREF white = RGB(255,255,255);
	COLORREF blue = RGB(0,0,127);
	COLORREF red=RGB(255,0,0);
	COLORREF green=RGB(051,153,051);

	colorGrad1=green;
	colorGrad2=green;

	if(bUse)
	{
		colorBK=red;
	}
	else
	{
		colorBK=white;
	}

	switch(ucNo)
	{
	case 0:
		m_ctrlProgress0.SetBkColor(colorBK);
		m_ctrlProgress0.SetGradientColors(colorGrad1,colorGrad2);
		m_ctrlProgress0.SetShowPercent(bUse);
		m_ctrlProgress0.Invalidate(TRUE);
		break;
	case 1:
		m_ctrlProgress1.SetBkColor(colorBK);
		m_ctrlProgress1.SetGradientColors(colorGrad1,colorGrad2);
		m_ctrlProgress1.SetShowPercent(bUse);
		m_ctrlProgress1.Invalidate(TRUE);
		break;
	case 2:
		m_ctrlProgress2.SetBkColor(colorBK);
		m_ctrlProgress2.SetGradientColors(colorGrad1,colorGrad2);
		m_ctrlProgress2.SetShowPercent(bUse);
		m_ctrlProgress2.Invalidate(TRUE);
		break;
	case 3:
		m_ctrlProgress3.SetBkColor(colorBK);
		m_ctrlProgress3.SetGradientColors(colorGrad1,colorGrad2);
		m_ctrlProgress3.SetShowPercent(bUse);
		m_ctrlProgress3.Invalidate(TRUE);
		break;
	case 4:
		m_ctrlProgress4.SetBkColor(colorBK);
		m_ctrlProgress4.SetGradientColors(colorGrad1,colorGrad2);
		m_ctrlProgress4.SetShowPercent(bUse);
		m_ctrlProgress4.Invalidate(TRUE);
		break;
	case 5:
		m_ctrlProgress5.SetBkColor(colorBK);
		m_ctrlProgress5.SetGradientColors(colorGrad1,colorGrad2);
		m_ctrlProgress5.SetShowPercent(bUse);
		m_ctrlProgress5.Invalidate(TRUE);
		break;
	case 6:
		m_ctrlProgress6.SetBkColor(colorBK);
		m_ctrlProgress6.SetGradientColors(colorGrad1,colorGrad2);
		m_ctrlProgress6.SetShowPercent(bUse);
		m_ctrlProgress6.Invalidate(TRUE);
		break;
	case 7:
		m_ctrlProgress7.SetBkColor(colorBK);
		m_ctrlProgress7.SetGradientColors(colorGrad1,colorGrad2);
		m_ctrlProgress7.SetShowPercent(bUse);
		m_ctrlProgress7.Invalidate(TRUE);
		break;
	case 8:
		m_ctrlProgress8.SetBkColor(colorBK);
		m_ctrlProgress8.SetGradientColors(colorGrad1,colorGrad2);
		m_ctrlProgress8.SetShowPercent(bUse);
		m_ctrlProgress8.Invalidate(TRUE);
		break;
	case 9:
		m_ctrlProgress9.SetBkColor(colorBK);
		m_ctrlProgress9.SetGradientColors(colorGrad1,colorGrad2);
		m_ctrlProgress9.SetShowPercent(bUse);
		m_ctrlProgress9.Invalidate(TRUE);
		break;
	case 10:
		m_ctrlProgress10.SetBkColor(colorBK);
		m_ctrlProgress10.SetGradientColors(colorGrad1,colorGrad2);
		m_ctrlProgress10.SetShowPercent(bUse);
		m_ctrlProgress10.Invalidate(TRUE);
		break;
	case 11:
		m_ctrlProgress11.SetBkColor(colorBK);
		m_ctrlProgress11.SetGradientColors(colorGrad1,colorGrad2);
		m_ctrlProgress11.SetShowPercent(bUse);
		m_ctrlProgress11.Invalidate(TRUE);
		break;
	case 12:
		m_ctrlProgress12.SetBkColor(colorBK);
		m_ctrlProgress12.SetGradientColors(colorGrad1,colorGrad2);
		m_ctrlProgress12.SetShowPercent(bUse);
		m_ctrlProgress12.Invalidate(TRUE);
		break;
	case 13:
		m_ctrlProgress13.SetBkColor(colorBK);
		m_ctrlProgress13.SetGradientColors(colorGrad1,colorGrad2);
		m_ctrlProgress13.SetShowPercent(bUse);
		m_ctrlProgress13.Invalidate(TRUE);
		break;
	case 14:
		m_ctrlProgress14.SetBkColor(colorBK);
		m_ctrlProgress14.SetGradientColors(colorGrad1,colorGrad2);
		m_ctrlProgress14.SetShowPercent(bUse);
		m_ctrlProgress14.Invalidate(TRUE);
		break;
	case 15:
		m_ctrlProgress15.SetBkColor(colorBK);
		m_ctrlProgress15.SetGradientColors(colorGrad1,colorGrad2);
		m_ctrlProgress15.SetShowPercent(bUse);
		m_ctrlProgress15.Invalidate(TRUE);
	default:
		break;
	}
}

void CCommStatusFM::SetProgressPos(unsigned char ucNo, unsigned char ucPos)
{
	switch(ucNo)
	{
	case 0:
		m_ctrlProgress0.SetPos(ucPos);
		break;
	case 1:
		m_ctrlProgress1.SetPos(ucPos);
		break;
	case 2:
		m_ctrlProgress2.SetPos(ucPos);
		break;
	case 3:
		m_ctrlProgress3.SetPos(ucPos);
		break;
	case 4:
		m_ctrlProgress4.SetPos(ucPos);
		break;
	case 5:
		m_ctrlProgress5.SetPos(ucPos);
		break;
	case 6:
		m_ctrlProgress6.SetPos(ucPos);
		break;
	case 7:
		m_ctrlProgress7.SetPos(ucPos);
		break;
	case 8:
		m_ctrlProgress8.SetPos(ucPos);
		break;
	case 9:
		m_ctrlProgress9.SetPos(ucPos);
		break;
	case 10:
		m_ctrlProgress10.SetPos(ucPos);
		break;
	case 11:
		m_ctrlProgress11.SetPos(ucPos);
		break;
	case 12:
		m_ctrlProgress12.SetPos(ucPos);
		break;
	case 13:
		m_ctrlProgress13.SetPos(ucPos);
		break;
	case 14:
		m_ctrlProgress14.SetPos(ucPos);
		break;
	case 15:
		m_ctrlProgress15.SetPos(ucPos);
	default:
		break;
	}
}

//ucDispNo 0: m_hIconLedOff 1: m_hIconPortOpen 2: m_hIconLedOn
void CCommStatusFM::SetDispTrunkSignal(unsigned char ucTrunkNo, unsigned char ucDispNo)
{
	HICON hIcon;
	if(!ucDispNo)
		hIcon=m_hIconLedOff;
	else if(ucDispNo==1)
		hIcon=m_hIconPortOpen;
	else
		hIcon=m_hIconLedOn;
	switch(ucTrunkNo)
	{
	case 0:
		m_ctrlStaticTrunkOnOff0.SetIcon(hIcon);
		break;
	case 1:
		m_ctrlStaticTrunkOnOff1.SetIcon(hIcon);
		break;
	case 2:
		m_ctrlStaticTrunkOnOff2.SetIcon(hIcon);
		break;
	case 3:
		m_ctrlStaticTrunkOnOff3.SetIcon(hIcon);
		break;
	case 4:
		m_ctrlStaticTrunkOnOff4.SetIcon(hIcon);
		break;
	case 5:
		m_ctrlStaticTrunkOnOff5.SetIcon(hIcon);
		break;
	case 6:
		m_ctrlStaticTrunkOnOff6.SetIcon(hIcon);
		break;
	case 7:
		m_ctrlStaticTrunkOnOff7.SetIcon(hIcon);
		break;
	default:
		break;
	}
}

void CCommStatusFM::OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	CString strAddr;
	int nItemCount=m_ctrlList.GetItemCount();
    for(int nItem=0;nItem<nItemCount;nItem++)
	{
		if(m_ctrlList.GetItemState(nItem,LVIS_SELECTED) & LVIS_SELECTED)
		{
			if(nItem%2==0)
				strAddr=m_ctrlList.GetItemText(nItem+1,0);
			else
				strAddr=m_ctrlList.GetItemText(nItem,0);
			break;
		}
	}
	strAddr.Replace("地址",NULL);
	CAddrPointScanStatusDlg AddrPointScanStatusDlg;
	AddrPointScanStatusDlg.m_ucTrunkNo=m_ctrlComboTrunkDisp.GetCurSel()+1;
	AddrPointScanStatusDlg.m_ucAddrNo=m_String2DataType.String2Int(strAddr);
	AddrPointScanStatusDlg.DoModal();
	*pResult = 0;
}

void CCommStatusFM::OnBUTTONCloseSound() 
{
	// TODO: Add your control notification handler code here
	CKJMonitorApp* pApp=(CKJMonitorApp* )AfxGetApp();
	pApp->pMPT->CloseWarning();
///    	Scan();  //continue scan
}
