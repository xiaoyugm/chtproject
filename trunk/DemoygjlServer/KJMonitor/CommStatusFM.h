#if !defined(AFX_COMMSTATUSFM_H__1E913AA4_97DB_4B03_B8AB_D416C49F6BA5__INCLUDED_)
#define AFX_COMMSTATUSFM_H__1E913AA4_97DB_4B03_B8AB_D416C49F6BA5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CommStatusFM.h : header file
//

//////////////////////////////////////////////////////////////////////////////
// CCommStatusFM form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

#include "KJMonitor.h"
#include "FMMonitorPoint.h"
#include "monitorPointThread.h"
#include "Com\\SerialPort.h"
//#include "MMTimerCustom.h" 
#include "SQL\\sqldirect.h"
#include "SQL\\String2DataType.h"
#include "Controls\\ProgressCtrlX.h"
#include "Controls\\XPStyleButtonST.h"
#include "Controls\\ThemeHelperST.h"


//#include "BitCmdCtrlDlg.h"

#define MAX_POINT_NUM_ANOLOG  8
#define MAX_SUCCESS_DISP_NUM  20

//设置四种颜色的值
#define ORANGE_STATUS 0
#define RED_STATUS  1
#define GREEN_STATUS 2
#define YELLOW_STATUS 3

struct structPOINTINFO
{
	unsigned short usPointNo;  //点号
	BOOL bScan;   //1:scan   
};

struct structSCANADDR
{
	BOOL bScan;         //1:scan   
	BOOL bValueType;    //1:Anolog 0:Switch
	unsigned char snConVType;	//转接器类型
//	unsigned char snFreq;
	structPOINTINFO structPointInfo[MAX_CHANNEL_NUMBER];
};

struct structANOLOG
{
	UINT  usProcessType1;  //处理类型
	double ufMeasure; //模拟量实际值
	unsigned short ufData2;   //16位2进制数据2
	unsigned short ufData1;   //16位2进制数据1
    UINT   unWarnDelay;//报警延时
	UINT usWarnMode;  //报警模式0-不报警，1-高、低报警，2-高、高报警，3-低、低报警
	UINT   unWarnCause;  //报警原因
	double   unWarnMin;   //报警下限
	double   unWarnMax;   //报警上限
	double dfScopeMin;    //值域最小值
	double dfScopeMax;    //值域最大值
	UINT  usPrecision;    //精度
	CString usUnit; //工程单位
};

struct structSWITCH    //开关量报警结构   
{
	UINT  usAC;  //AC-0（AO-1、NC-2、NO-3）：A代表可以产生报警 N 代表不需要报警 C常闭触点 O 常开触点
	UINT   unWarnCause; //报警原因
    UINT   unWarnDelay;//报警延时
	CString ucstrMode1; //模式1
	CString ucstrMode2; //模式2
};

struct structRunTime{	//实际运行时间

	BOOL bRecordKeepTime; //是否纪录运行时间
	UINT LastSwitchStatus; //上一次开关量的状态
	int udDay; //保持的天数
	int udHour;//小时
	int udMin; //分钟
	int udSecond;//秒钟
	CTime uStartTime;//开始记录的时间
};

struct structValueState{
	//
	unsigned short ufData;   //16位2进制数据
	unsigned char ucLowValue; //低八位
	unsigned char ucHighValue;  //高八位
    BOOL  alarm_state;        //=0表示正常状态  //=1表示报警状态
    BOOL  Ac_state;           //=0表示通讯正常  //=1表示通讯异常
	BYTE Warn_state;  //新报警状态
	unsigned WarnColor;//报警颜色
    UINT   unDelay;//延时
};

typedef struct structMONITORPOINT
{
	unsigned short usMonitorNo;  //监测号
	unsigned char ucTrunkNo;  //干线号由1开始
	unsigned char ucAddrNo;  //地址号
	unsigned char ucConvID;  //转接器类型
	BOOL bValueType; //1:Anolog 0:Switch
	BOOL bScan;   //1:scan  
	unsigned char unChannel; //通道号
	CString strLabel; //标签
	CString strExplain; //说明
    CString strWarnCause;  //报警原因
}MONITORPOINT;

struct structBITADDRCMD
{
	unsigned char ucAddr;
	unsigned char ucLCmd;
};

class CCommStatusFM : public CFormView
{
protected:
	CCommStatusFM();           // protected constructor used by dynamic creation
	virtual ~CCommStatusFM();

	DECLARE_DYNCREATE(CCommStatusFM)

// Form Data
public:
	//{{AFX_DATA(CCommStatusFM)
	enum { IDD = IDD_DLG_FMCOMMSTATUS };
	CXPStyleButtonST	m_ctrlBUTTONCloseSound;
	CStatic	m_ctrlStaticTrunkOnOff7;
	CStatic	m_ctrlStaticTrunkOnOff6;
	CStatic	m_ctrlStaticTrunkOnOff5;
	CStatic	m_ctrlStaticTrunkOnOff4;
	CStatic	m_ctrlStaticTrunkOnOff3;
	CStatic	m_ctrlStaticTrunkOnOff2;
	CStatic	m_ctrlStaticTrunkOnOff1;
	CStatic	m_ctrlStaticTrunkOnOff0;
	CProgressCtrlX	m_ctrlProgress0;
	CProgressCtrlX	m_ctrlProgress1;
	CProgressCtrlX	m_ctrlProgress2;
	CProgressCtrlX	m_ctrlProgress3;
	CProgressCtrlX	m_ctrlProgress4;
	CProgressCtrlX	m_ctrlProgress5;
	CProgressCtrlX	m_ctrlProgress6;
	CProgressCtrlX	m_ctrlProgress7;
	CProgressCtrlX	m_ctrlProgress8;
	CProgressCtrlX	m_ctrlProgress9;
	CProgressCtrlX	m_ctrlProgress10;
	CProgressCtrlX	m_ctrlProgress11;
	CProgressCtrlX	m_ctrlProgress12;
	CProgressCtrlX	m_ctrlProgress13;
	CProgressCtrlX	m_ctrlProgress14;
	CProgressCtrlX	m_ctrlProgress15;
	CComboBox	m_ctrlComboAddrDisp;
	CXTListCtrl	m_ctrlList;
	CComboBox	m_ctrlComboTrunkDisp;
	//}}AFX_DATA

// Attributes
public:


// Operations
public:
	unsigned char ucSuccessProcent;
	BOOL m_bBitCmdReceiveSuccess;
	BOOL m_bHandCmdSendFail;
	BOOL m_bHandCmdCanSend;
	structBITADDRCMD m_structBITADDRCMD[MAX_TRUNK_NUMBER];  
	BOOL m_bSendHandCmd;  //暂用于位命令
	BOOL m_bSendBitCmd[MAX_TRUNK_NUMBER];//用于各干线的位命令
    BOOL m_bSend;      
//	BOOL m_bFirstRefreshProgress;
	BOOL m_bSerialPortChange;
	void SetStructMONITORPOINT(unsigned short usPointNo, 
								unsigned short usMonitorNo,
								unsigned char ucTrunkNo,
								unsigned char ucAddrNo,
								unsigned char ucConvID,
								BOOL bValueType,
								BOOL bScan,
                                unsigned char unChannel);
	unsigned char GetConvChannels(unsigned char ucConvID);
	UINT m_bHaltDisp;             
	void SetDispTrunkSignal(unsigned char ucTrunkNo,unsigned char ucDispNo);
	void ResetDispProgressCtrl(void);
	void InitDispProgressCtrl(void);
	void SetProgressPos(unsigned char ucNo,unsigned char ucPos);
	void SetProgressColor(unsigned char ucNo,BOOL bUse);
	void SetProgressCtrl(void);
	void SetListCtrlTable(void);
	BOOL m_bStartScan;
	void ResetListTable(UINT unTrunk,UINT unAddr);

	BOOL ResetTimer(void);
	BOOL ScanGetNextCmd(unsigned char iTrunk);
	BOOL CloseAllSerailPort(void);
	BOOL TestSerailPort(UINT nPort);
	BOOL GetCommPara(void);
	unsigned char m_chCmd[MAX_TRUNK_NUMBER][2];
	unsigned char m_ucRXData[MAX_TRUNK_NUMBER][2];

	unsigned short m_ucRxCount[MAX_TRUNK_NUMBER];
	unsigned char m_ucRXConvID[MAX_TRUNK_NUMBER];
	BOOL InitTrunkCOMPort(void);

	UINT ScanBuildQueue();
	void ConnectDB(void);
	unsigned short m_unRepeaScantTimes;
	void StopScan(void);
	BOOL StartScan(void);
//	BOOL GetResponseData(UINT unCommPort);
	BOOL ScanSendCommand(UINT unTrunk);
	UINT GetAddrComd(UINT unTrunkNo,UINT unAddr,UINT unConvID,UINT unCmdNo);
	BOOL Scan(void);

	//CMMTimerCustom m_MMTimerCustom;
	CSQLDirect m_SQLDirect;
	CSQLDirect m_SQLDirect1;
	CString2DataType m_String2DataType;
	CSerialPort m_SerialPort[MAX_TRUNK_NUMBER];
	CSerialPort m_SerialPortTest;
	UINT m_unSerialPortforTrunk[MAX_TRUNK_NUMBER];
	BOOL m_bTrunkPortOpen[MAX_TRUNK_NUMBER];
	UINT m_unScanTrunkPointNum[MAX_TRUNK_NUMBER];
	UINT m_unScanTrunkPointNum1[MAX_TRUNK_NUMBER];
	UINT m_unScanAddrPointNum[MAX_TRUNK_NUMBER][MAX_ADDR_NUMBER];
	UINT m_unScanAddrPointNum1[MAX_TRUNK_NUMBER][MAX_ADDR_NUMBER];
	unsigned char m_ucScanConvPointNum[MAX_TRUNK_NUMBER][MAX_ADDR_NUMBER][MAX_MULTICONV_NUMBER];
	unsigned char m_ucScanConvPointNum1[MAX_TRUNK_NUMBER][MAX_ADDR_NUMBER][MAX_MULTICONV_NUMBER];

	structSCANADDR m_structSCANADDR[MAX_TRUNK_NUMBER][MAX_ADDR_NUMBER][MAX_MULTICONV_NUMBER];
	unsigned char m_uckConV[MAX_TRUNK_NUMBER][MAX_ADDR_NUMBER];
	unsigned char m_ucScanTXCount[MAX_TRUNK_NUMBER][MAX_ADDR_NUMBER];
	unsigned char m_ucScanSuccessCount[MAX_TRUNK_NUMBER][MAX_ADDR_NUMBER];
	unsigned char m_ucjAddr[MAX_TRUNK_NUMBER];
	unsigned char m_ucTrunkDisp,m_ucAddrDisp;  //disp trunk and addr page
	structMONITORPOINT m_structMONITORPOINT[MAX_POINT_NUMBER];


	UINT m_unScanTrunkPointNum2[MAX_TRUNK_NUMBER];
	UINT m_unScanAddrPointNum2[MAX_TRUNK_NUMBER][MAX_ADDR_NUMBER];
	unsigned char m_ucScanConvPointNum2[MAX_TRUNK_NUMBER][MAX_ADDR_NUMBER][MAX_MULTICONV_NUMBER];

	BOOL m_bCycleScan;

	CXTColorPicker	m_cpText;
	CXTColorPicker	m_cpBack;
	COLORREF m_clrRowText;
	COLORREF m_clrRowBack;

	int               m_nSortedCol;
	BOOL              m_bAscending;
	CXTFlatHeaderCtrl m_flatHeader;

	HICON m_hIconLedOn;
	HICON m_hIconLedOff;
	HICON m_hIconPortOpen;

	BOOL m_bScanLedOnOFF[MAX_TRUNK_NUMBER];
	unsigned char m_ucTimerCount[MAX_TRUNK_NUMBER];
//	SYSTEMTIME   m_ScanTime;
    UINT unCmdNo;
//	CWinThread *pReadThread, *pWriteThread; 

//	CCriticalSection m_Section;            //11/1

//	#define COLUMNS_m_ctrlList 23

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCommStatusFM)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	




#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CCommStatusFM)
	afx_msg LONG OnCommunication(WPARAM ch, LPARAM port);
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnSelchangeComboTrunkdisp();
	afx_msg void OnSelchangeComboAddrdisp();
	afx_msg void OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBUTTONCloseSound();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()


private:

	CThemeHelperST	m_ThemeHelper;
//    CBitCmdCtrlDlg *m_pBitCmdCtrlDlg;

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COMMSTATUSFM_H__1E913AA4_97DB_4B03_B8AB_D416C49F6BA5__INCLUDED_)
