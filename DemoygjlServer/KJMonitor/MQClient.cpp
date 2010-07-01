// MQClient.cpp: implementation of the CMQClient class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "kjmonitor.h"
#include "MQClient.h"
#include "MonitorPointThread.h"
#include "mainfrm.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

static int nYear, nMonth, nDay, nHour, nMinute, nSecond;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMQClient::CMQClient()
{
///	ConnectDB();
}

CMQClient::~CMQClient()
{
	m_SQLDirect.Close();
	if(IsConnected())
		CloseConnection();
}

//������������Ϣ
BOOL CMQClient::SendMessage(CNDKMessage &message)
{
	if(SendMessageToServer(message))
	{
		return TRUE;
	}
	return FALSE;
}

//��������
BOOL CMQClient::ConnectServer(CString strIp,long lPort)
{
	if(OpenConnection(strIp, lPort))
	{

		ConnectTime = CTime::GetCurrentTime();

		return TRUE;
	}
	return FALSE;
}

BOOL CMQClient::Ping()
{
	return FALSE;
}

//��Ӧ��������������Ϣ
void CMQClient::OnMessage(CNDKMessage& message)
{
	switch(message.GetId())
	{
//	case SENDSQL:
///		WriteSQL(message);
//		break;
	case SENDSTARTTIME:
		GetHostStartTime(message);
		break;
	default:
		break;
	}
}

void CMQClient::OnPing(long lNbMilliseconds)
{

}

void CMQClient::OnDisconnect(NDKClientDisconnection disconnectionType)
{

}

//�������ݿ�
void CMQClient::ConnectDB()
{
	try
	{
		m_SQLDirect.Init();
		if(m_SQLDirect.Connect(_T("masterdefine"),_T("kj86"),_T("kj86")))
			AfxMessageBox("AddUser:�޷������û��������ݿ�,��ȷ��SQL SERVER�����Ƿ�����!");
	}
	catch(CDBException *e)
	{
		e->ReportError();
		return;
	}
}

//���յ���SQL���д�뵽���ݿ���
void CMQClient::WriteSQL(CNDKMessage& message)
{
	CString strSql;
	message.GetAt(0,strSql);
	if(!strSql.IsEmpty())
		m_SQLDirect.ExecuteSQL(strSql);
}

//����NowTime �� MessageTime,���������״̬
void CMQClient::HostStateCheck()
{
	if(!PingServer())
	{
		//��ʱ��������������
		theApp.ChangeClientToHost();
	}
}

//�������������ʱ��
void CMQClient::GetHostStartTime(CNDKMessage& message)
{
	message.GetAt(0,nYear);
	message.GetAt(1,nMonth);
	message.GetAt(2,nDay);
	message.GetAt(3,nHour);
	message.GetAt(4,nMinute);
	message.GetAt(5,nSecond);
	CTime time(nYear, nMonth, nDay, nHour, nMinute, nSecond);
	StartTime = time;
	//if(ConnectTime != StartTime)
///	SyncHostAndClient();
}

//���±����е�����
BOOL CMQClient::SyncHostAndClient()
{
	CString strDate, strDataSql, strWarnSql;
	strDate.Format("%d-%d-%d %d:%d:%d", nYear,nMonth,nDay,nHour,nMinute,nSecond);
	
	strDataSql.Format("SELECT unPointNo,unCollectData,strBeginTime,strEndTime FROM uCollectData WHERE (strBeginTime>CONVERT(DATETIME,'%s', 101))",strDate);
	strWarnSql.Format("SELECT unPointNo,strExplain,strWarnCause,strWarnTime,strNormalTime,bConfirm FROM uWarnCauseRecord WHERE (strWarnTime>CONVERT(DATETIME,'%s', 101)) OR (strNormalTime>CONVERT(DATETIME,'%s', 101))",strDate,strDate);

/*	CNDKMessage syncdata(SYNC);
	syncdata.Add("uCollectData");
	syncdata.Add(4);
	syncdata.Add(strDataSql);
	SendMessage(syncdata);

/*	CNDKMessage syncwarn(SYNC);
	syncwarn.Add("uWarnCauseRecord");
	syncwarn.Add(6);
	syncwarn.Add(strWarnSql);
	SendMessage(syncwarn);
*/
	return FALSE;
}

//�رյ�����������
void CMQClient::Close()
{
	CloseConnection();
}
