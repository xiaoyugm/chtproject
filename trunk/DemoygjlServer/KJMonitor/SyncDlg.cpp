// SyncDlg.cpp : implementation file
//

#include "stdafx.h"
#include "kjmonitor.h"
#include "SyncDlg.h"
#include "MQCommandType.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSyncDlg dialog


CSyncDlg::CSyncDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSyncDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSyncDlg)
	m_strAnolog = _T("不同步");
	m_strData = _T("不同步");
	m_strPoint = _T("不同步");
	m_strRecord = _T("不同步");
	m_strSwitch = _T("不同步");
	m_DataStart = COleDateTime::GetCurrentTime();
	m_DataEnd = COleDateTime::GetCurrentTime();
	m_RecordStart = COleDateTime::GetCurrentTime();
	m_RecordEnd = COleDateTime::GetCurrentTime();
	m_lAnologEnd = 0;
	m_lAnologStart = 0;
	m_lPointEnd = 0;
	m_lPointStart = 0;
	m_lSwitchEnd = 0;
	m_lSwitchStart = 0;
	//}}AFX_DATA_INIT
}


void CSyncDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSyncDlg)
	DDX_CBString(pDX, IDC_COMBO_ANOLOG, m_strAnolog);
	DDX_CBString(pDX, IDC_COMBO_DATA, m_strData);
	DDX_CBString(pDX, IDC_COMBO_POINT, m_strPoint);
	DDX_CBString(pDX, IDC_COMBO_RECORD, m_strRecord);
	DDX_CBString(pDX, IDC_COMBO_SWITCH, m_strSwitch);
	DDX_Text(pDX, IDC_EDIT_DATA_START, m_DataStart);
	DDX_Text(pDX, IDC_EDIT_DATA_END, m_DataEnd);
	DDX_Text(pDX, IDC_EDIT_RECORD_START, m_RecordStart);
	DDX_Text(pDX, IDC_EDIT_RECORD_END, m_RecordEnd);
	DDX_Text(pDX, IDC_EDIT_ANOLOG_END, m_lAnologEnd);
	DDX_Text(pDX, IDC_EDIT_ANOLOG_START, m_lAnologStart);
	DDX_Text(pDX, IDC_EDIT_POINT_END, m_lPointEnd);
	DDX_Text(pDX, IDC_EDIT_POINT_START, m_lPointStart);
	DDX_Text(pDX, IDC_EDIT_SWITCH_END, m_lSwitchEnd);
	DDX_Text(pDX, IDC_EDIT_SWITCH_START, m_lSwitchStart);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSyncDlg, CDialog)
	//{{AFX_MSG_MAP(CSyncDlg)
	ON_BN_CLICKED(ID_SYNC, OnSync)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSyncDlg message handlers

BOOL CSyncDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	UpdateData(FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSyncDlg::OnSync() 
{
	UpdateData(TRUE);
	SyncData();
	SyncRecord();
	SyncAnolog();
	SyncPoint();
	SyncSwitch();
	AfxMessageBox("数据同步完成!");
}

//同步uCollectData表
void CSyncDlg::SyncData()
{
	CString strStartDate, strEndDate, strDataSql;

	strStartDate.Format("%d-%d-%d %d:%d:%d",m_DataStart.GetYear(),
											m_DataStart.GetMonth(),
											m_DataStart.GetDay(),
											m_DataStart.GetHour(),
											m_DataStart.GetMinute(),
											m_DataStart.GetSecond());

	strEndDate.Format("%d-%d-%d %d:%d:%d",	m_DataEnd.GetYear(),
											m_DataEnd.GetMonth(),
											m_DataEnd.GetDay(),
											m_DataEnd.GetHour(),
											m_DataEnd.GetMinute(),
											m_DataEnd.GetSecond());

	if(m_strData.CollateNoCase("不同步") == 0)
		return;
	if(m_strData.CollateNoCase("全部同步") == 0)
		strDataSql.Format("SELECT unPointNo,unCollectData,strBeginTime,strEndTime FROM uCollectData");
	if(m_strData.CollateNoCase("时间同步") == 0)
		strDataSql.Format("SELECT unPointNo,unCollectData,strBeginTime,strEndTime FROM uCollectData WHERE (strBeginTime>CONVERT(DATETIME,'%s', 101) AND strBeginTime <CONVERT(DATETIME,'%s', 101))",
							strStartDate,strEndDate);

//	CNDKMessage syncdata(SYNC);
//	syncdata.Add("uCollectData");
//	syncdata.Add(4);
//	syncdata.Add(strDataSql);

//	theApp.Sync(syncdata);
}

//同步uWarnCauseRecord表
void CSyncDlg::SyncRecord()
{
	CString strStartDate, strEndDate, strWarnSql;

	strStartDate.Format("%d-%d-%d %d:%d:%d",m_RecordStart.GetYear(),
											m_RecordStart.GetMonth(),
											m_RecordStart.GetDay(),
											m_RecordStart.GetHour(),
											m_RecordStart.GetMinute(),
											m_RecordStart.GetSecond());

	strEndDate.Format("%d-%d-%d %d:%d:%d",	m_RecordEnd.GetYear(),
											m_RecordEnd.GetMonth(),
											m_RecordEnd.GetDay(),
											m_RecordEnd.GetHour(),
											m_RecordEnd.GetMinute(),
											m_RecordEnd.GetSecond());

	if(m_strRecord.CollateNoCase("不同步") == 0)
		return;
	if(m_strRecord.CollateNoCase("全部同步") == 0)
		strWarnSql.Format("SELECT unPointNo,strExplain,strWarnCause,strWarnTime,strNormalTime,bConfirm FROM uWarnCauseRecord");
	if(m_strRecord.CollateNoCase("时间同步") == 0)
		strWarnSql.Format("SELECT unPointNo,strExplain,strWarnCause,strWarnTime,strNormalTime,bConfirm FROM uWarnCauseRecord WHERE (strWarnTime BETWEEN CONVERT(DATETIME,'%s', 101) AND CONVERT(DATETIME,'%s', 101)) OR (strNormalTime BETWEEN CONVERT(DATETIME,'%s', 101) AND CONVERT(DATETIME,'%s', 101))",
							strStartDate,strEndDate,strStartDate,strEndDate);

//	CNDKMessage syncwarn(SYNC);
//	syncwarn.Add("uWarnCauseRecord");
//	syncwarn.Add(6);
//	syncwarn.Add(strWarnSql);

//	theApp.Sync(syncwarn);
}

//同步uAnologPointProperty表
void CSyncDlg::SyncAnolog()
{
	CString strAnologSql;
	if(m_strAnolog.CollateNoCase("不同步") == 0)
		return;
	if(m_strAnolog.CollateNoCase("全部同步") == 0)
		strAnologSql.Format("SELECT * FROM uAnologPointProperty");
	if(m_strAnolog.CollateNoCase("点号同步") == 0)
		strAnologSql.Format("SELECT * FROM uAnologPointProperty WHERE unPointNo BETWEEN %d AND %d",m_lAnologStart,m_lAnologEnd);
	
//	AfxMessageBox(strAnologSql);

//	CNDKMessage syncanolog(SYNC);
//	syncanolog.Add("uAnologPointProperty");
//	syncanolog.Add(14);
//	syncanolog.Add(strAnologSql);

//	theApp.Sync(syncanolog);

}

//同步uPointProperty表
void CSyncDlg::SyncPoint()
{
	CString strPoingSql;
	if(m_strPoint.CollateNoCase("不同步") == 0)
		return;
	if(m_strPoint.CollateNoCase("全部同步") == 0)
		strPoingSql.Format("SELECT * FROM uPointProperty");
	if(m_strPoint.CollateNoCase("点号同步") == 0)
		strPoingSql.Format("SELECT * FROM uPointProperty WHERE unPointNo BETWEEN %d AND %d",m_lPointStart,m_lPointEnd);
	
//	AfxMessageBox(strPoingSql);
//	CNDKMessage syncpoing(SYNC);
//	syncpoing.Add("uPointProperty");
//	syncpoing.Add(12);
//	syncpoing.Add(strPoingSql);

//	theApp.Sync(syncpoing);
}

//同步uSwitchPointProperty表
void CSyncDlg::SyncSwitch()
{
	CString strSwitchSql;
	if(m_strSwitch.CollateNoCase("不同步") == 0)
		return;
	if(m_strSwitch.CollateNoCase("全部同步") == 0)
		strSwitchSql.Format("SELECT * FROM uSwitchPointProperty");
	if(m_strSwitch.CollateNoCase("点号同步") == 0)
		strSwitchSql.Format("SELECT * FROM uSwitchPointProperty WHERE unPointNo BETWEEN %d AND %d",m_lSwitchStart,m_lSwitchEnd);
	
//	AfxMessageBox(strSwitchSql);
//	CNDKMessage syncswitch(SYNC);
//	syncswitch.Add("uSwitchPointProperty");
//	syncswitch.Add(9);
//	syncswitch.Add(strSwitchSql);

//	theApp.Sync(syncswitch);

}
