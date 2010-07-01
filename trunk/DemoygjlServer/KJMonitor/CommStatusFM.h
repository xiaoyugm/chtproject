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

//����������ɫ��ֵ
#define ORANGE_STATUS 0
#define RED_STATUS  1
#define GREEN_STATUS 2
#define YELLOW_STATUS 3

struct structPOINTINFO
{
	unsigned short usPointNo;  //���
	BOOL bScan;   //1:scan   
};

struct structSCANADDR
{
	BOOL bScan;         //1:scan   
	BOOL bValueType;    //1:Anolog 0:Switch
	unsigned char snConVType;	//ת��������
//	unsigned char snFreq;
	structPOINTINFO structPointInfo[MAX_CHANNEL_NUMBER];
};

struct structANOLOG
{
	UINT  usProcessType1;  //��������
	double ufMeasure; //ģ����ʵ��ֵ
	unsigned short ufData2;   //16λ2��������2
	unsigned short ufData1;   //16λ2��������1
    UINT   unWarnDelay;//������ʱ
	UINT usWarnMode;  //����ģʽ0-��������1-�ߡ��ͱ�����2-�ߡ��߱�����3-�͡��ͱ���
	UINT   unWarnCause;  //����ԭ��
	double   unWarnMin;   //��������
	double   unWarnMax;   //��������
	double dfScopeMin;    //ֵ����Сֵ
	double dfScopeMax;    //ֵ�����ֵ
	UINT  usPrecision;    //����
	CString usUnit; //���̵�λ
};

struct structSWITCH    //�����������ṹ   
{
	UINT  usAC;  //AC-0��AO-1��NC-2��NO-3����A������Բ������� N ������Ҫ���� C���մ��� O ��������
	UINT   unWarnCause; //����ԭ��
    UINT   unWarnDelay;//������ʱ
	CString ucstrMode1; //ģʽ1
	CString ucstrMode2; //ģʽ2
};

struct structRunTime{	//ʵ������ʱ��

	BOOL bRecordKeepTime; //�Ƿ��¼����ʱ��
	UINT LastSwitchStatus; //��һ�ο�������״̬
	int udDay; //���ֵ�����
	int udHour;//Сʱ
	int udMin; //����
	int udSecond;//����
	CTime uStartTime;//��ʼ��¼��ʱ��
};

struct structValueState{
	//
	unsigned short ufData;   //16λ2��������
	unsigned char ucLowValue; //�Ͱ�λ
	unsigned char ucHighValue;  //�߰�λ
    BOOL  alarm_state;        //=0��ʾ����״̬  //=1��ʾ����״̬
    BOOL  Ac_state;           //=0��ʾͨѶ����  //=1��ʾͨѶ�쳣
	BYTE Warn_state;  //�±���״̬
	unsigned WarnColor;//������ɫ
    UINT   unDelay;//��ʱ
};

typedef struct structMONITORPOINT
{
	unsigned short usMonitorNo;  //����
	unsigned char ucTrunkNo;  //���ߺ���1��ʼ
	unsigned char ucAddrNo;  //��ַ��
	unsigned char ucConvID;  //ת��������
	BOOL bValueType; //1:Anolog 0:Switch
	BOOL bScan;   //1:scan  
	unsigned char unChannel; //ͨ����
	CString strLabel; //��ǩ
	CString strExplain; //˵��
    CString strWarnCause;  //����ԭ��
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
	BOOL m_bSendHandCmd;  //������λ����
	BOOL m_bSendBitCmd[MAX_TRUNK_NUMBER];//���ڸ����ߵ�λ����
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
