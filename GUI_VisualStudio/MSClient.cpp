// MQClient.cpp: implementation of the CMQClient class.
//
//////////////////////////////////////////////////////////////////////


#include "stdafx.h"
#include "GUI_VisualStudio.h"
#include "MSClient.h"

#include "MainFrm.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMSClient::CMSClient()
{
//	ConnectDB();
}

CMSClient::~CMSClient()
{

}

//向主机发送信息
BOOL CMSClient::SendMessage(CNDKMessage &message)
{
	if(SendMessageToServer(message))
	{
		return TRUE;
	}
	return FALSE;
}

//连接主机
BOOL CMSClient::ConnectServer(CString strIp,UINT lPort)
{
	if(OpenConnection(strIp, lPort))
	{
		ConnectTime = CTime::GetCurrentTime();
		return TRUE;
	}
	return FALSE;
}

BOOL CMSClient::Ping()
{
	return FALSE;
}

//响应服务器发来的消息
void CMSClient::OnMessage(CNDKMessage& message)
{
	switch(message.GetId())
	{
	case MASTERSLAVER:
		GetServerd(message);
		break;

	default:
		break;
	}
}

void CMSClient::OnPing(long lNbMilliseconds)
{

}

void CMSClient::OnDisconnect(NDKClientDisconnection disconnectionType)
{

}

//连接数据库
void CMSClient::ConnectDB()
{

}

//将收到的SQL语句写入到数据库中
void CMSClient::WriteSQL(CNDKMessage& message)
{
	CString strSql;
//	message.GetAt(0,strSql);
//	if(!strSql.IsEmpty())
//		m_SQLDirect.ExecuteSQL(strSql);
}

//根据NowTime 和 MessageTime,检查主机的状态
void CMSClient::HostStateCheck()
{
	if(!PingServer())
	{
		//此时备机做主机启动
		AfxMessageBox("与主机的通讯联系失败,请检查!");
	}
}

//关闭到主机的连接
void CMSClient::Close()
{
/*  try
  {
/*    if ( m_AccountSet._IsOpen() )
      m_AccountSet.Close();

    m_Cn.Close();
    //Cleanup the AxLib library
    dbAx::Term();
  }
  catch ( CAxException *e )
  {
		AfxMessageBox(e->m_szErrorDesc +  _T("BJygjl Message"));
 //    MessageBox(e->m_szErrorDesc, _T("BJygjl Message"), MB_OK);
    delete e;
  }*/
	CloseConnection();
}

//获得主机的启动时间
void CMSClient::GetServerd(CNDKMessage& message)
{
	int nYear;
	message.GetAt(0,nYear);
//	message.GetAt(1,nMonth);
//	message.GetAt(2,nDay);
//	message.GetAt(3,nHour);
//	message.GetAt(4,nMinute);
//	message.GetAt(5,nSecond);
//	CTime time(nYear, nMonth, nDay, nHour, nMinute, nSecond);
//	StartTime = time;
	CString gggg;
//	gggg.Format("%d  %d  %d  %d  %d  ",nYear,nMonth,nDay,nHour,nMinute);
//		AfxMessageBox(gggg);
	if(nYear == 555)
	{
//    	gggg.Format("%d    ",theApp.master30 );
//		AfxMessageBox(gggg +"555!");
		theApp.master30 = 0;
	}
	if(nYear == 222)
	{
//					gggg.Format("%d  ",theApp.slave30);
//            		AfxMessageBox(gggg+"222!");
		theApp.slave30 = 0;
	}

	//if(ConnectTime != StartTime)   
///	SyncHostAndClient();
}

