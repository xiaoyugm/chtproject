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

//开始监听服务
BOOL CMSServer::Listenning(long lPort)
{
	if (IsStarted())
	{
		MessageBox(NULL,"网络监听服务已经启动!","提示",MB_ICONINFORMATION);
	}
	else
	{
		if (!StartListening(lPort))
		{
			MessageBox(NULL,"网络监听服务启动失败!","提示",MB_ICONERROR);
		}
		else
			return TRUE;
	}
	return FALSE;
}

//关闭网络服务
void CMSServer::StopServer()
{
	DisconnectAllUsers();
	Stop();
}

//服务器端发送消息
BOOL CMSServer::SendMessage(CNDKMessage& message)
{
	if(SendMessageToAllUsers(message))
		return TRUE;
	else
		return FALSE;
}


//响应客户机发来的消息
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
	//MessageBox(NULL,"双机热备已经开始!","提示",MB_ICONINFORMATION);
}

void CMSServer::OnDisconnect(long lUserId, NDKServerDisconnection disconnectionType)
{
	bIsConnect = FALSE;
	//MessageBox(NULL,"双机热备已经停止!","提示",MB_ICONINFORMATION);
}

//向连接的计算机发送SQL语句
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

//发送本机开始运行的时间
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
//	else if(nYear == 333 && n_CPort == 999)//备机有主机启动
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
//连接本地SQLSERVER数据库
void CMSServer::ConnectDB()
{
/*	try
	{
		m_SQLDirect.Init();
		if(m_SQLDirect.Connect(_T("masterdefine"),_T("kj86"),_T("kj86")))
			AfxMessageBox("AddUser:无法连接用户参数数据库,请确定SQL SERVER服务是否运行!");
	}
	catch(CDBException *e)
	{
		e->ReportError();
		return;
	}*/
}

