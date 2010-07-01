// BitCmdCtrlDlg.cpp : implementation file
//

#include "stdafx.h"
#include "kjmonitor.h"
#include "BitCmdCtrlDlg.h"

#include "SQL\\String2DataType.h"
#include "SetPortVsTrunkDlg.h"

#include "CommStatusFM.h"
#include "MainFrm.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBitCmdCtrlDlg dialog
extern structANOLOG m_structANOLOG[MAX_POINT_NUMBER];
extern structValueState m_structValueState[MAX_POINT_NUMBER];


CBitCmdCtrlDlg::CBitCmdCtrlDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBitCmdCtrlDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBitCmdCtrlDlg)
	m_unEditAddrDEC = 0;
	m_strEditAddrHEX = _T("");
	m_strEditData = _T("");
	m_strEditLcmdHEX = _T("");
	//}}AFX_DATA_INIT

}


void CBitCmdCtrlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBitCmdCtrlDlg)
	DDX_Control(pDX, IDC_BUTData, m_ctrlBtnData);
	DDX_Control(pDX, IDC_BUTTON_CLEAR, m_ctrlBtnClear);
	DDX_Control(pDX, IDC_BUTTON_COMPORT, m_ctrlBtnComPort);
	DDX_Control(pDX, IDC_EDIT_DATA, m_ctrlEditData);
	DDX_Control(pDX, IDOK, m_btnOK);
	DDX_Control(pDX, IDC_BUTTON_START, m_ctrlBtnStart);
	DDX_Control(pDX, IDC_COMBO_TRUNKNO, m_ctrlComboTrunkNO);
	DDX_Control(pDX, IDC_CHECK_L0, m_ctrlCheckL0);
	DDX_Control(pDX, IDC_CHECK_L1, m_ctrlCheckL1);
	DDX_Control(pDX, IDC_CHECK_L2, m_ctrlCheckL2);
	DDX_Control(pDX, IDC_CHECK_L3, m_ctrlCheckL3);
	DDX_Control(pDX, IDC_CHECK_L4, m_ctrlCheckL4);
	DDX_Control(pDX, IDC_CHECK_L5, m_ctrlCheckL5);
	DDX_Control(pDX, IDC_CHECK_L6, m_ctrlCheckL6);
	DDX_Control(pDX, IDC_CHECK_L7, m_ctrlCheckL7);
	DDX_Text(pDX, IDC_EDIT_ADDRDEC, m_unEditAddrDEC);
	DDX_Text(pDX, IDC_EDIT_ADDRHEX, m_strEditAddrHEX);
	DDX_Text(pDX, IDC_EDIT_DATA, m_strEditData);
	DDX_Text(pDX, IDC_EDIT_LCMDHEX, m_strEditLcmdHEX);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CBitCmdCtrlDlg, CDialog)
	//{{AFX_MSG_MAP(CBitCmdCtrlDlg)
	ON_BN_CLICKED(IDC_CHECK_L0, OnCheckL0)
	ON_BN_CLICKED(IDC_CHECK_L1, OnCheckL1)
	ON_BN_CLICKED(IDC_CHECK_L2, OnCheckL2)
	ON_BN_CLICKED(IDC_CHECK_L3, OnCheckL3)
	ON_BN_CLICKED(IDC_CHECK_L4, OnCheckL4)
	ON_BN_CLICKED(IDC_CHECK_L5, OnCheckL5)
	ON_BN_CLICKED(IDC_CHECK_L6, OnCheckL6)
	ON_BN_CLICKED(IDC_CHECK_L7, OnCheckL7)
	ON_EN_CHANGE(IDC_EDIT_ADDRDEC, OnChangeEditAddrdec)
	ON_EN_CHANGE(IDC_EDIT_LCMDHEX, OnChangeEditLcmdhex)
	ON_BN_CLICKED(IDC_BUTTON_START, OnButtonStart)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, OnButtonClear)
	ON_BN_CLICKED(IDC_BUTTON_COMPORT, OnButtonComport)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTData, OnBUTData)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBitCmdCtrlDlg message handlers

BOOL CBitCmdCtrlDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	m_btnOK.SetThemeHelper(&m_ThemeHelper);
	m_btnOK.SetIcon(IDI_ICON_EXIT);
	m_btnOK.SetTooltipText(_T("退出位命令控制器"));

	m_ctrlBtnClear.SetThemeHelper(&m_ThemeHelper);
	m_ctrlBtnClear.SetIcon(IDI_ICON_DISPLAYCLEAR,IDI_ICON_DISPLAY);
	m_ctrlBtnClear.SetTooltipText(_T("清空显示区"));

	m_ctrlBtnComPort.SetThemeHelper(&m_ThemeHelper);
	m_ctrlBtnComPort.SetIcon(IDI_ICON_SEARCH);
	m_ctrlBtnComPort.SetTooltipText(_T("查看和设置干线与串口的对应关系，并可测试所选串口是否存在"));


	m_ctrlBtnStart.SetThemeHelper(&m_ThemeHelper);
	m_ctrlBtnStart.SetIcon(IDI_ICON_START);
	m_ctrlBtnStart.SetTooltipText(_T("发送命令"));
	
	m_ctrlBtnData.SetThemeHelper(&m_ThemeHelper);
	m_ctrlBtnData.SetIcon(IDI_ICON_LOADDBFILE);
	m_ctrlBtnData.SetTooltipText(_T("请等一个扫描周期，再按下按钮"));

	m_ctrlComboTrunkNO.SetCurSel(0);
	m_ctrlEditData.textColor(RGB(0,0,0));
	m_ctrlEditData.bkColor(RGB(255,255,255));
	

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CBitCmdCtrlDlg::SetLcmdBit(unsigned char ucBit)
{
	BOOL bCheck;
	unsigned char ucOR=0x01;
	for(int i=0;i<8;i++)
	{
		if(ucBit & ucOR) 
			bCheck=1;
		else
			bCheck=0;
		ucOR<<=1;
		switch(i)
		{
		case 0: m_ctrlCheckL0.SetCheck(bCheck); break;
		case 1: m_ctrlCheckL1.SetCheck(bCheck); break;
		case 2: m_ctrlCheckL2.SetCheck(bCheck); break;
		case 3: m_ctrlCheckL3.SetCheck(bCheck); break;
		case 4: m_ctrlCheckL4.SetCheck(bCheck); break;
		case 5: m_ctrlCheckL5.SetCheck(bCheck); break;
		case 6: m_ctrlCheckL6.SetCheck(bCheck); break;
		case 7: m_ctrlCheckL7.SetCheck(bCheck); break;
		default: break;
		}
	}
	SetLcmdBitCheck();

}

unsigned char CBitCmdCtrlDlg::GetLcmd()
{
	unsigned char ucCh=0;
	if(m_ctrlCheckL0.GetCheck()) ucCh|=0x01;
	if(m_ctrlCheckL1.GetCheck()) ucCh|=0x02;
	if(m_ctrlCheckL2.GetCheck()) ucCh|=0x04;
	if(m_ctrlCheckL3.GetCheck()) ucCh|=0x08;
	if(m_ctrlCheckL4.GetCheck()) ucCh|=0x10;
	if(m_ctrlCheckL5.GetCheck()) ucCh|=0x20;
	if(m_ctrlCheckL6.GetCheck()) ucCh|=0x40;
	if(m_ctrlCheckL7.GetCheck()) ucCh|=0x80;
	return ucCh;
}


void CBitCmdCtrlDlg::OnCheckL0() 
{
	// TODO: Add your control notification handler code here
	if(m_ctrlCheckL0.GetCheck()) 
		m_ctrlCheckL0.SetWindowText("1");
	else
		m_ctrlCheckL0.SetWindowText("0");
	m_strEditLcmdHEX.Format("%02X",GetLcmd());
	UpdateData(FALSE);
	
}

void CBitCmdCtrlDlg::OnCheckL1() 
{
	// TODO: Add your control notification handler code here
	if(m_ctrlCheckL1.GetCheck()) 
		m_ctrlCheckL1.SetWindowText("1");
	else
		m_ctrlCheckL1.SetWindowText("0");
	m_strEditLcmdHEX.Format("%02X",GetLcmd());
	UpdateData(FALSE);
}

void CBitCmdCtrlDlg::OnCheckL2() 
{
	// TODO: Add your control notification handler code here
	if(m_ctrlCheckL2.GetCheck()) 
		m_ctrlCheckL2.SetWindowText("1");
	else
		m_ctrlCheckL2.SetWindowText("0");
	m_strEditLcmdHEX.Format("%02X",GetLcmd());
	UpdateData(FALSE);
	
}

void CBitCmdCtrlDlg::OnCheckL3() 
{
	// TODO: Add your control notification handler code here
	if(m_ctrlCheckL3.GetCheck()) 
		m_ctrlCheckL3.SetWindowText("1");
	else
		m_ctrlCheckL3.SetWindowText("0");
	m_strEditLcmdHEX.Format("%02X",GetLcmd());
	UpdateData(FALSE);
	
}

void CBitCmdCtrlDlg::OnCheckL4() 
{
	// TODO: Add your control notification handler code here
	if(m_ctrlCheckL4.GetCheck()) 
		m_ctrlCheckL4.SetWindowText("1");
	else
		m_ctrlCheckL4.SetWindowText("0");
	m_strEditLcmdHEX.Format("%02X",GetLcmd());
	UpdateData(FALSE);
	
}

void CBitCmdCtrlDlg::OnCheckL5() 
{
	// TODO: Add your control notification handler code here
	if(m_ctrlCheckL5.GetCheck()) 
		m_ctrlCheckL5.SetWindowText("1");
	else
		m_ctrlCheckL5.SetWindowText("0");
	m_strEditLcmdHEX.Format("%02X",GetLcmd());
	UpdateData(FALSE);
	
}

void CBitCmdCtrlDlg::OnCheckL6() 
{
	// TODO: Add your control notification handler code here
	if(m_ctrlCheckL6.GetCheck()) 
		m_ctrlCheckL6.SetWindowText("1");
	else
		m_ctrlCheckL6.SetWindowText("0");
	m_strEditLcmdHEX.Format("%02X",GetLcmd());
	UpdateData(FALSE);
	
}

void CBitCmdCtrlDlg::OnCheckL7() 
{
	// TODO: Add your control notification handler code here
	if(m_ctrlCheckL7.GetCheck()) 
		m_ctrlCheckL7.SetWindowText("1");
	else
		m_ctrlCheckL7.SetWindowText("0");
	m_strEditLcmdHEX.Format("%02X",GetLcmd());
	UpdateData(FALSE);
	
}

void CBitCmdCtrlDlg::OnChangeEditAddrdec() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	UpdateData(TRUE);
	if(m_unEditAddrDEC>=MAX_ADDR_NUMBER)
	{
		m_unEditAddrDEC=MAX_ADDR_NUMBER-1;

	}
	m_strEditAddrHEX.Format("%02X",m_unEditAddrDEC);
	UpdateData(FALSE);
	
	// TODO: Add your control notification handler code here
	
}


void CBitCmdCtrlDlg::OnChangeEditLcmdhex() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_strEditLcmdHEX.Replace(" ","");
	if(m_strEditLcmdHEX.GetLength()>2)
	{
		AfxMessageBox("命令不能多于 2 个十六进制字符");
		return;
	}
	CString2DataType str2data;
	SetLcmdBit(str2data.Str2HEX(m_strEditLcmdHEX));
}

void CBitCmdCtrlDlg::SetLcmdBitCheck()
{
	if(m_ctrlCheckL0.GetCheck()) 
		m_ctrlCheckL0.SetWindowText("1");
	else
		m_ctrlCheckL0.SetWindowText("0");
	if(m_ctrlCheckL1.GetCheck()) 
		m_ctrlCheckL1.SetWindowText("1");
	else
		m_ctrlCheckL1.SetWindowText("0");
	if(m_ctrlCheckL2.GetCheck()) 
		m_ctrlCheckL2.SetWindowText("1");
	else
		m_ctrlCheckL2.SetWindowText("0");
	if(m_ctrlCheckL3.GetCheck()) 
		m_ctrlCheckL3.SetWindowText("1");
	else
		m_ctrlCheckL3.SetWindowText("0");
	if(m_ctrlCheckL4.GetCheck()) 
		m_ctrlCheckL4.SetWindowText("1");
	else
		m_ctrlCheckL4.SetWindowText("0");
	if(m_ctrlCheckL5.GetCheck()) 
		m_ctrlCheckL5.SetWindowText("1");
	else
		m_ctrlCheckL5.SetWindowText("0");
	if(m_ctrlCheckL6.GetCheck()) 
		m_ctrlCheckL6.SetWindowText("1");
	else
		m_ctrlCheckL6.SetWindowText("0");
	if(m_ctrlCheckL7.GetCheck()) 
		m_ctrlCheckL7.SetWindowText("1");
	else
		m_ctrlCheckL7.SetWindowText("0");

}

void CBitCmdCtrlDlg::OnButtonStart() 
{
	// TODO: Add your control notification handler code here

	//gstrDispInfo.Empty();
	CMainFrame* pFWnd=(CMainFrame*)AfxGetMainWnd();
	CCommStatusFM* pCommStatusFM=pFWnd->m_pCommStatusFM;
	CString2DataType str2data;
 
	UpdateData(TRUE);
	OnButtonClear(); //clear receive area
	m_ctrlEditData.textColor(RGB(000,000,000));
	m_ctrlEditData.bkColor(RGB(255,255,255));

	int iTrunk=m_ctrlComboTrunkNO.GetCurSel();
	if((iTrunk<0)||(iTrunk>=MAX_TRUNK_NUMBER))
	{
		AfxMessageBox("干线号必须在1-8之间");
		return;
	}

	if(!m_strEditLcmdHEX.GetLength())
	{
		AfxMessageBox("[低位]命令不能为空");
		return;
	}

	pCommStatusFM->m_bBitCmdReceiveSuccess=FALSE;

	pCommStatusFM->m_structBITADDRCMD[iTrunk].ucAddr=m_unEditAddrDEC;
	pCommStatusFM->m_structBITADDRCMD[iTrunk].ucLCmd
		=str2data.Str2HEX(m_strEditLcmdHEX);
	m_strEditData.Format("位命令：干线%d, 地址%d, (低位)命令：0X%s,",
		iTrunk+1,m_unEditAddrDEC,m_strEditLcmdHEX);
	
	pCommStatusFM->m_bSendBitCmd[iTrunk]=TRUE;
	UpdateData(FALSE);

	m_ctrlBtnStart.EnableWindow(FALSE);
	m_ctrlComboTrunkNO.EnableWindow(FALSE);
	
	pCommStatusFM->m_bHandCmdCanSend=TRUE;

//	pCommStatusFM->m_bSendBitCmd[iTrunk]=FALSE;
	
	if(!pCommStatusFM->m_bStartScan)
	{
		pCommStatusFM->StartScan();
	}
	
}

void CBitCmdCtrlDlg::OnButtonClear() 
{
	// TODO: Add your control notification handler code here
	m_strEditData.Empty();
	m_ctrlEditData.textColor(RGB(000,000,000));
	m_ctrlEditData.bkColor(RGB(255,255,255));
	UpdateData(FALSE);
}

void CBitCmdCtrlDlg::OnButtonComport() 
{
	// TODO: Add your control notification handler code here
	CSetPortVsTrunkDlg* pSetPortVsTrunkDlg;
	pSetPortVsTrunkDlg=new CSetPortVsTrunkDlg;
	pSetPortVsTrunkDlg->DoModal();
	delete pSetPortVsTrunkDlg;
}
//static int iTem=0;
void CBitCmdCtrlDlg::DispSendReceiveInfo()
{
	//m_strSendReceiveInfo.Format("\r\n◇time%d",100);
	//m_strEditData+=m_strSendReceiveInfo;
//	int nLen=m_ctrlEditData.GetWindowTextLength();
//	m_ctrlEditData.SetSel(nLen, nLen);
//	m_ctrlEditData.ReplaceSel(gstrDispInfo);
		int nLen=m_ctrlEditData.GetWindowTextLength();
	m_ctrlEditData.SetSel(nLen, nLen);
	m_ctrlEditData.ReplaceSel(m_strSendReceiveInfo);
//	gstrDispInfo="eewrqwre";
//	AfxMessageBox(gstrDispInfo+"this");
}


void CBitCmdCtrlDlg::GetBitCmdtoSend()
{
	CMainFrame* pFWnd=(CMainFrame*)AfxGetMainWnd();
	CCommStatusFM* pCommStatusFM=pFWnd->m_pCommStatusFM;
	UpdateData(TRUE);
	CString2DataType str2data;

	int iTrunk=m_ctrlComboTrunkNO.GetCurSel();
		unsigned char   ucjAddr,ucLCmd ,ucConvID ,uckConV;    
		ucjAddr=m_unEditAddrDEC;
		ucLCmd=str2data.Str2HEX(m_strEditLcmdHEX);
        uckConV=pCommStatusFM->m_uckConV[iTrunk][ucjAddr];
        if(uckConV!=0)
		{
             if((ucLCmd==0x10)||(ucLCmd==0x11)||(ucLCmd==0x12)||(ucLCmd==0x13))
			 {
                 uckConV=3;
			 }
             else if((ucLCmd==0x00))
			 {
                 uckConV=1;
			 }
             else if((ucLCmd==0x40)||((ucLCmd&0x60)==0x60))
			 {
                 uckConV=2;
			 }
             else if((ucLCmd==0x01)||(ucLCmd==0x02)||(ucLCmd==0x20))
			 {
                 uckConV=4;
			 }
		}
	    ucConvID=pCommStatusFM->m_structSCANADDR[iTrunk][ucjAddr][uckConV].snConVType;
		BOOL bValueType=pCommStatusFM->m_structSCANADDR[iTrunk][ucjAddr][uckConV].bValueType;

	if(pCommStatusFM->m_bHandCmdSendFail)
	{
		m_strSendReceiveInfo.Format("发送失败，可能串口没有打开");
	}

	OnButtonClear(); //clear receive area
	m_ctrlEditData.textColor(RGB(000,000,000));
	m_ctrlEditData.bkColor(RGB(255,255,255));
 
	CString strtemp;
	if(bValueType)  //anolog value
	{
        UINT i=(UINT) ucLCmd & 0X07;
        unsigned short usPointNow=pCommStatusFM->m_structSCANADDR[iTrunk][ucjAddr][uckConV].structPointInfo[i].usPointNo;
		if((ucConvID == 4) ||(ucConvID == 10))
		{
      	m_strSendReceiveInfo.Format("\r\n   √成功收到返回数据:地址：0X%02X ,   低位数据:    %d",
				ucjAddr,m_structValueState[usPointNow].ucLowValue);
    	             strtemp.Format("\r\n            [十进制]          %d     高位数据:    %d  ",                         
				ucjAddr,m_structValueState[usPointNow].ucHighValue);
			m_strSendReceiveInfo+=strtemp;
    	             strtemp.Format("\r\n            [实际值]                           %d  ",                         
				(unsigned short)m_structValueState[usPointNow].ufData);
		}
        else
		{
         	m_strSendReceiveInfo.Format("\r\n   √成功收到返回数据:地址：0X%02X ,  数据：0X%02X",
				ucjAddr,m_structValueState[usPointNow].ufData);
    	             strtemp.Format("\r\n            [十进制]        %d             %d  ",                         
				ucjAddr,m_structValueState[usPointNow].ufData);
			m_strSendReceiveInfo+=strtemp;
    	             strtemp.Format("\r\n            [实际值]                      %4.2f  ",                         
				m_structANOLOG[usPointNow].ufMeasure);
		}

	}
	else  
	{
        UINT i=(UINT) ucLCmd & 0X01;
        unsigned short usPointNow=pCommStatusFM->m_structSCANADDR[iTrunk][ucjAddr][uckConV].structPointInfo[i].usPointNo;
      	m_strSendReceiveInfo.Format("\r\n   √成功收到返回数据:地址：0X%02X ,          数据：0X%02X",
				ucjAddr,m_structValueState[usPointNow].ucLowValue);
    	             strtemp.Format("\r\n            [十进制]         %d                    %d  ",                         
				ucjAddr,m_structValueState[usPointNow].ucLowValue);
			m_strSendReceiveInfo+=strtemp;
    	             strtemp.Format("\r\n            [二进制]         %s             %s  ",                         
				str2data.Char2Binary(ucjAddr),str2data.Char2Binary(m_structValueState[usPointNow].ucLowValue));
	}
	
			m_strSendReceiveInfo+=strtemp;
			DispSendReceiveInfo();

			m_ctrlEditData.textColor(RGB(000,153,000));
			m_ctrlEditData.bkColor(RGB(255,255,153));

}

void CBitCmdCtrlDlg::OnBUTData() 
{
	// TODO: Add your control notification handler code here
	CKJMonitorApp* pApp=(CKJMonitorApp* )AfxGetApp();
	pApp->pMPT->CloseWarning();
	GetBitCmdtoSend();

	m_ctrlBtnStart.EnableWindow(TRUE);
	m_ctrlComboTrunkNO.EnableWindow(TRUE);
	
}
