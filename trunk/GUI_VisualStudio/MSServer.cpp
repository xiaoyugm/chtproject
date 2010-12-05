// MQServer.cpp: implementation of the CMQServer class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "GUI_VisualStudio.h"
#include "MSServer.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMSServer::CMSServer()
{
	tHostStartTime = CTime::GetCurrentTime();
	bIsConnect = FALSE;
}

CMSServer::~CMSServer()
{

}

//��ʼ��������
BOOL CMSServer::Listenning(long lPort)
{
	if (IsStarted())
	{
		MessageBox(NULL,"������������Ѿ�����!","��ʾ",MB_ICONINFORMATION);
	}
	else
	{
		if (!StartListening(lPort))
		{
			MessageBox(NULL,"���������������ʧ��!","��ʾ",MB_ICONERROR);
		}
		else
			return TRUE;
	}
	return FALSE;
}

//�ر��������
void CMSServer::StopServer()
{
	DisconnectAllUsers();
	Stop();
}

//�������˷�����Ϣ
BOOL CMSServer::SendMessage(CNDKMessage& message)
{
	if(SendMessageToAllUsers(message))
		return TRUE;
	else
		return FALSE;
}


//��Ӧ�ͻ�����������Ϣ
void CMSServer::OnMessage(long lUserId, CNDKMessage& message)
{
	switch(message.GetId())
	{
//	case uCollectData:
//		SyncTableCollectData();
//		break;
	case MASTERSLAVER:
		GetClient(message);
		break;
//	case uWarnCauseRecord:
//		SyncTableuWarnCauseRecord();
//		break;
//	case SYNC:
//		Sync(message);
//		break;

	default:
		break;
	}
}

void CMSServer::OnConnect(long lUserId)
{
	bIsConnect = TRUE;
//	SendStartTime(555);
	CString gggg;
	gggg.Format("%d     ",lUserId);
//		AfxMessageBox(gggg);
//	SendStartTime(tHostStartTime);
	//MessageBox(NULL,"˫���ȱ��Ѿ���ʼ!","��ʾ",MB_ICONINFORMATION);
}

void CMSServer::OnDisconnect(long lUserId, NDKServerDisconnection disconnectionType)
{
	bIsConnect = FALSE;
	//MessageBox(NULL,"˫���ȱ��Ѿ�ֹͣ!","��ʾ",MB_ICONINFORMATION);
}

//�����ӵļ��������SQL���
BOOL CMSServer::SendSQL(CString strSql)
{
	if(bIsConnect)
	{
//		CNDKMessage message(SENDSQL);
//		message.Add(strSql);
//		if(SendMessageToAllUsers(message))
			return TRUE;
	}
	return FALSE;
}

BOOL CMSServer::OnIsConnectionAccepted()
{
	return TRUE;
}

//���ͱ�����ʼ���е�ʱ��
BOOL CMSServer::SendStartTime(int time)
{
//	if(bIsConnect)
	{
		CNDKMessage message(MASTERSLAVER);
		message.Add(time);
//		message.Add(m_ClassTime[1].ffds);
//		message.Add(tHostStartTime.GetDay());
//		message.Add(tHostStartTime.GetHour());
//		message.Add(tHostStartTime.GetMinute());
//		message.Add(tHostStartTime.GetSecond());
		
		if(SendMessageToAllUsers(message))
		{
			return TRUE;
		}
	}
	return FALSE;
}

void CMSServer::GetClient(CNDKMessage& message)
{
	int nYear,nMonth;
	message.GetAt(0,nYear);
//	message.GetAt(1,nMonth);
	CString gggg;
	gggg.Format("%d  ",nYear);
//		AfxMessageBox(gggg);
	if(nYear == 444 && n_CPort != 888)
	{
   //         		AfxMessageBox(gggg+"C444!");
		theApp.StartMC();
//		SendStartTime(333);
	}
	if(nYear == 333 && n_CPort != 999)
	{
 //           		AfxMessageBox(gggg+"C333!");
		theApp.StartBC();
//		SendStartTime(444);
	}
//	else if(nYear == 333 && n_CPort == 999)//��������������
//	{
//		theApp.StartBC();
//		theApp.master30 =0;
//	}
	if(nYear == 555 )
	{
//            		AfxMessageBox(gggg+"C555!");
		CNDKMessage message(MASTERSLAVER);
		message.Add(555);
		SendMessageToAllUsers(message);
//		SendStartTime(555);
	}
	if(nYear == 222 )
	{
		CNDKMessage message(MASTERSLAVER);
		message.Add(222);
//            		AfxMessageBox(gggg+"C222!");
		SendMessageToAllUsers(message);
//		SendStartTime(222);
	}

	//if(ConnectTime != StartTime)   
///	SyncHostAndClient();
}
//���ӱ���SQLSERVER���ݿ�
void CMSServer::ConnectDB()
{
/*	try
	{
		m_SQLDirect.Init();
		if(m_SQLDirect.Connect(_T("masterdefine"),_T("kj86"),_T("kj86")))
			AfxMessageBox("AddUser:�޷������û��������ݿ�,��ȷ��SQL SERVER�����Ƿ�����!");
	}
	catch(CDBException *e)
	{
		e->ReportError();
		return;
	}*/
}

