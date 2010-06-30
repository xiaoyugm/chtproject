// MQClient.cpp: implementation of the CMQClient class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "GUI_VisualStudio.h"
#include "MQClient.h"
///#include "mainfrm.h"
///#include "drawobj.h"
///#include "DrawRect.h"
///#include "drawwarn.h"
///#include "drawchart.h"
///#include "drawbutton.h"
///#include "drawview.h"
///#include "DrawPoly.h"
///#include "DrawRotary.h"
///#include "DrawConduit.h"
///#include "DrawCar.h"
#include "MainFrm.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

static int nYear, nMonth, nDay, nHour, nMinute, nSecond;
extern  CPointInfo m_CPointInfo[MAX_POINT_NUMBER];
CWarnPoint  m_CWarnPoint[MAX_POINT_NUMBER];
CStrWarn    m_CStrWarn[MAX_ROW];
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

//向主机发送信息
BOOL CMQClient::SendMessage(CNDKMessage &message)
{
	if(SendMessageToServer(message))
	{
		return TRUE;
	}
	return FALSE;
}

//连接主机
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

//响应服务器发来的消息
void CMQClient::OnMessage(CNDKMessage& message)
{
	switch(message.GetId())
	{
//	case SENDSQL:
///		WriteSQL(message);
//		break;
	case SENDSTARTTIME:
		InitPointDate(message);
		break;
//	case WARNCAUSERECORD:
///		DiaplayWarnTableC(message);
//		break;
//	case KEEPTIMESTR:
//		break;
//	case ALLDATA:
//    	CollectDate(message);
//		break;
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

//连接数据库
void CMQClient::ConnectDB()
{
	try
	{
		m_SQLDirect.Init();
		if(m_SQLDirect.Connect(_T("masterdefine"),_T("kj86"),_T("kj86")))
			AfxMessageBox("AddUser:无法连接用户参数数据库,请确定SQL SERVER服务是否运行!");
	}
	catch(CDBException *e)
	{
		e->ReportError();
		return;
	}
}

//将收到的SQL语句写入到数据库中
void CMQClient::WriteSQL(CNDKMessage& message)
{
	CString strSql;
	message.GetAt(0,strSql);
	if(!strSql.IsEmpty())
		m_SQLDirect.ExecuteSQL(strSql);
}

//根据NowTime 和 MessageTime,检查主机的状态
void CMQClient::HostStateCheck()
{
	if(!PingServer())
	{
		//此时备机做主机启动
		AfxMessageBox("与主机的通讯联系失败,请检查!");
	}
}

//关闭到主机的连接
void CMQClient::Close()
{
	CloseConnection();
}

void CMQClient::CollectDate(CNDKMessage& message)
{
	double dfValue , fMin ,fMax ; 
	unsigned short nPointNo,ufData;
	unsigned char Warn_state ,state ,lWarn_state;

	message.GetAt(0, state);
	message.GetAt(1, nPointNo);
	message.GetAt(2, Warn_state);
	message.GetAt(3, ufData);
	message.GetAt(4, dfValue);

	if(state == 1)
	{
        lWarn_state = m_CPointInfo[nPointNo].lWarn_state ;
		m_CPointInfo[nPointNo].lufdata = ufData;
		m_CPointInfo[nPointNo].ldfValue = dfValue;
        fMin = m_CPointInfo[nPointNo].fMin ;
        fMax = m_CPointInfo[nPointNo].fMax ;
    	m_CPointInfo[nPointNo].pnValue = (dfValue-fMin )/(fMax -fMin );

			if((lWarn_state == 255)&&((Warn_state & 0x30) == 0x20)){
        		m_CPointInfo[nPointNo].lWarn_state = Warn_state;
	         	DiaplayWarnTableC(nPointNo);
			}
			else if((lWarn_state == 255)&&((Warn_state & 0x30) == 0x00)){
        		m_CPointInfo[nPointNo].lWarn_state = Warn_state;
			}
			else if(lWarn_state  != Warn_state ){
        		m_CPointInfo[nPointNo].lWarn_state = Warn_state;
	         	DiaplayWarnTableC(nPointNo);
			}

	}
	if(state == 3)
	{
		m_CPointInfo[nPointNo].lWarn_state = Warn_state;
		m_CPointInfo[nPointNo].lufdata = ufData;
	}
	if(state == 2)
	{
        lWarn_state = m_CPointInfo[nPointNo].lWarn_state ;
		m_CPointInfo[nPointNo].lufdata = ufData;

			if((lWarn_state == 255)&&((Warn_state & 0x30) == 0x20)){
        		m_CPointInfo[nPointNo].lWarn_state = Warn_state;
	         	DiaplayWarnTableC(nPointNo);
			}
			else if((lWarn_state == 255)&&((Warn_state & 0x30) == 0x00)){
        		m_CPointInfo[nPointNo].lWarn_state = Warn_state;
			}
			else if((lWarn_state & 0x30) != (Warn_state & 0x30)){
        		m_CPointInfo[nPointNo].lWarn_state = Warn_state;
	         	DiaplayWarnTableC(nPointNo);
			}
	}

    CMainFrame* pFWnd=(CMainFrame*)AfxGetMainWnd();
	
		CString strItem;
		CString strSubA;
		CString strSubB;

/*		strItem.Format(_T("Item %f"), m_CPointInfo[state].ldfValue);
		strSubA.Format(_T("Sub A %f"), m_CPointInfo[state].fMax);
		strSubB.Format(_T("Sub b %s"), m_CPointInfo[state].usUnit);
		if((pFWnd)&&(pFWnd->m_pSampleFormView!= NULL))
    		pFWnd->m_pSampleFormView->SetInfo(1,state,strItem,strSubA,strSubB);
		if((pFWnd)&&(pFWnd->m_pSampleFormView1!= NULL))
    		pFWnd->m_pSampleFormView1->SetInfo(2,state,strItem,strSubA,strSubB);
		if((pFWnd)&&(pFWnd->m_pSampleFormView2!= NULL))
    		pFWnd->m_pSampleFormView2->SetInfo(3,state,strItem,strSubA,strSubB);
*/

}
//        CString  str;
//		str.Format("%d %d-%d ",nPointNo,Warn_state,ufData);		
//         AfxMessageBox(str);

void CMQClient::InitPointDate(CNDKMessage& message)
{
//	CNDKMessage syncdata(ALLDATA);
//	syncdata.Add(1);
//	SendMessage(syncdata);
}

//更新报警表
void CMQClient::DiaplayWarnTableC(unsigned short nPointNo)
{
	CString strPoint,strDate,strTime ,strText ,strWarn;
	CString strWarnDate, strPointNo;;
	CString strExplaintemp,strWarnCausetemp,strWarnTime ,usUnit;
	double dfValue ;
	unsigned short ufData;
	unsigned char Warn_state ;

   	CTime t=CTime::GetCurrentTime();
	strWarnTime.Format("%d-%d-%d %d:%d:%d",t.GetYear(),t.GetMonth(),t.GetDay(),t.GetHour(),t.GetMinute(),t.GetSecond());
	m_CPointInfo[nPointNo].strWarnTime = strWarnTime;

 	  Warn_state = m_CPointInfo[nPointNo].lWarn_state ;
      usUnit = m_CPointInfo[nPointNo].usUnit ;
      strExplaintemp = m_CPointInfo[nPointNo].strExplaintemp ;
      strWarnCausetemp = m_CPointInfo[nPointNo].strWarnCausetemp ;
	  dfValue = m_CPointInfo[nPointNo].ldfValue ;
	  ufData = m_CPointInfo[nPointNo].lufdata ;

		    if((Warn_state & 0x30) == 0x00) 
			{
	            strPointNo.Format("%d",nPointNo);
				if (nPointNo < 4) 
                    strWarnDate.Format("正常 %d -- %4.2f %s",ufData,dfValue,usUnit);
				else if (nPointNo > 4)
                 	strWarnDate.Format(" 正常  %d ",ufData );
	            AddWarn( strPointNo, strWarnDate, strExplaintemp, strWarnCausetemp, strWarnTime);
			}
         	else if((Warn_state & 0x30) == 0x20)
			{
                strPointNo.Format("%d",nPointNo);
				if (nPointNo < 4) 
                    strWarnDate.Format(" 报警 %d-- %4.2f %s",ufData,dfValue,usUnit);
				else if (nPointNo > 4)
            		strWarnDate.Format(" 报警 %d ",ufData );
	       		AddWarn( strPointNo, strWarnDate, strExplaintemp, strWarnCausetemp, strWarnTime);
			}
			
    	m_CWarnPoint[0].warnPoint = nPointNo;

}

void CMQClient::AddWarn( CString strPoint, CString strDate, CString strTime, CString strText, CString strWarn)
{
		m_CStrWarn[0].strPoint = strPoint;
		m_CStrWarn[0].strDate = strDate;
		m_CStrWarn[0].strTime = strTime;
		m_CStrWarn[0].strText = strText;
		m_CStrWarn[0].strWarn = strWarn;
	for(int i=MAX_ROW-1;i>0;i--)
	{
		m_CStrWarn[i].strPoint = m_CStrWarn[i-1].strPoint;
		m_CStrWarn[i].strDate = m_CStrWarn[i-1].strDate;
		m_CStrWarn[i].strTime = m_CStrWarn[i-1].strTime;
		m_CStrWarn[i].strText = m_CStrWarn[i-1].strText;
		m_CStrWarn[i].strWarn = m_CStrWarn[i-1].strWarn;
	}

    CMainFrame* pFWnd=(CMainFrame*)AfxGetMainWnd();
    pFWnd->Msg(0,m_CStrWarn[0].strPoint , m_CStrWarn[0].strDate , m_CStrWarn[0].strText ,m_CStrWarn[0].strWarn ,m_CStrWarn[0].strTime);
    pFWnd->m_wndResourceView.InitLC();

}

