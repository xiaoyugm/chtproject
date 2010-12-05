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
//		m_ndkSend=NULL;
//	ConnectDB();
//	m_nodialog = true;
	m_adjustnum = 0;
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
/*    CString szConnect = _T("Provider=SQLOLEDB.1;Persist Security Info=True;\
                          User ID=sa;Password=sunset;\
                          Data Source=") +m_OthersSetting.DBname+ _T(";Initial Catalog=BJygjl");
//All calls to the AxLib should be wrapped in a try / catch block
  try
  {
    dbAx::Init();
    m_Cn.Create();
//    m_Cn._SetConnectionEvents(new CCardFileEvents);
    m_Cn.CursorLocation(adUseClient);
    m_Cn.Open((LPCTSTR)szConnect);

		m_Adjustdata.Create();
		m_Adjustdata.CursorType(adOpenDynamic);
		m_Adjustdata.CacheSize(50);
//		m_Adjustdata._SetRecordsetEvents(new CAccountSetEvents);
		m_Adjustdata.Open("Select * From rtadjustdata" , &m_Cn);
		m_Adjustdata.MarshalOptions(adMarshalModifiedOnly);
	    m_AdjustdataNew = &m_Adjustdata;

		CTime t=CTime::GetCurrentTime();
		CString sztime;
		sztime.Format("%d",t.GetYear());
		szConnect = "Select * From rt";
		szConnect += sztime;
		int m_mon = t.GetMonth();
		if(m_mon>9)
     		sztime.Format("%d",m_mon);
		else
     		sztime.Format("0%d",m_mon);
		szConnect += sztime;
		szConnect += "data";

		m_Realtimedata.Create();
		m_Realtimedata.CursorType(adOpenDynamic);
		m_Realtimedata.CacheSize(50);
		m_Realtimedata.Open(szConnect , &m_Cn);
		m_Realtimedata.MarshalOptions(adMarshalModifiedOnly);
	    m_RealtimedataNew = &m_Realtimedata;

//	    m_ndkRTD = new unsigned char[6];
  }
  catch ( dbAx::CAxException *e )
  {
		AfxMessageBox(e->m_szErrorDesc +  _T("BJygjl Message"));
//    MessageBox(e->m_szErrorDesc, _T("BJygjl Message"), MB_OK);
    delete e;
    return ;
  }*/

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
    if ( m_ContactSet._IsOpen() )
      m_ContactSet.Close();
    if ( m_MAlocation._IsOpen() )
      m_MAlocation.Close();
    if ( m_PointDes._IsOpen() )
      m_PointDes.Close();
    if ( m_Control._IsOpen() )
      m_Control.Close();
    if ( m_SControl._IsOpen() )
      m_SControl.Close();
//    if ( m_Realtimedata._IsOpen() )
//      m_Realtimedata.Close();
//    if ( m_Adjustdata._IsOpen() )
//      m_Adjustdata.Close();

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

