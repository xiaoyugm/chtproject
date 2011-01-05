// MQClient.cpp: implementation of the CMQClient class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "GUI_VisualStudio.h"
#include "MQClient.h"
#include "MainFrm.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

extern SerialF               m_SerialF[MAX_FDS];
extern ListV    str_list[6];    //风电瓦斯闭锁list
extern BYTE     m_ndkSend[MAX_FDS][44];//44BUFFER_SIZE
extern SlaveStation             m_SlaveStation[MAX_FDS][MAX_CHAN];
//static int nYear, nMonth, nDay, nHour, nMinute, nSecond;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMQClient::CMQClient()
{
//		m_ndkSend=NULL;
//	ConnectDB();
}

CMQClient::~CMQClient()
{

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
BOOL CMQClient::ConnectServer(CString strIp,UINT lPort)
{
	LPCTSTR str1 =strIp;
	if(OpenConnection(str1, lPort))
	{
		ConnectTime = CTime::GetCurrentTime();
		return TRUE;
	}
	return FALSE;
}

BOOL CMQClient::Ping()
{
	CString strIp; long lPort;
	GetIpAndPort(strIp,lPort);
	PingServer();
	return FALSE;
}

//响应服务器发来的消息
void CMQClient::OnMessage(CNDKMessage& message)
{
    theApp.internet30s = 0;
	switch(message.GetId())
	{
	case SENDSTARTTIME:
		GetHostStartTime(message);
		break;
	case REALTIMEDATA:
       	CollectDate(message);
		break;
	case TESTCOMMUNICATION:
    	ManageServerG(message);
		break;
	case MANUALCONTROL:
	case VERIFYTIMER:
	case SENDCONFIG:
	case WINDGASATRESIA:
	case FAULTATRESIA:
	case INFODEFINE:
    case SERIALERROR:
	case AUTOCONTROL:
		ManageServer(message);
		break;
	default:
		break;
	}
}

void CMQClient::OnPing(long lNbMilliseconds)
{
	long lr =lNbMilliseconds;
	theApp.DocNum = 7;

}

void CMQClient::OnDisconnect(NDKClientDisconnection disconnectionType)
{

}


//将收到的SQL语句写入到数据库中
void CMQClient::WriteSQL(CNDKMessage& message)
{
	CString strSql;
//	message.GetAt(0,strSql);
//	if(!strSql.IsEmpty())
//		m_SQLDirect.ExecuteSQL(strSql);
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

//获得主机的启动时间
void CMQClient::GetHostStartTime(CNDKMessage& message)
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
//	if(nYear >2009)

	if(theApp.m_FdsScan ==50 && m_SlaveStation[1][0].Channel_state ==0xa0)
		theApp.m_RTDM.NCSuccess();

//	gggg.Format("%d  %d  %d  %d  %d  ",nYear,nMonth,nDay,nHour,nMinute);
//		AfxMessageBox(gggg);

	//if(ConnectTime != StartTime)   
///	SyncHostAndClient();
}

void CMQClient::ManageServer(CNDKMessage& message)
{
    CMainFrame* pFWnd=(CMainFrame*)AfxGetMainWnd();
	CString ggggg,strtemp,strSQL;
    unsigned char  nstation ,nend,ncommand ;
	int  ntimer;

	message.GetAt(0, m_ndkSend2 ,m_unBufferLength);//44

//	message.GetAt(0,nbegin);
//	message.GetAt(1,nstation);
	nstation = m_ndkSend2[1];
    	strtemp.Format("[%d号分站]",nstation);
	if(nstation <1 || nstation >60)
	{
		g_Log.StatusOut(strtemp +"错误！");
		return;
	}

    	ggggg = strtemp;
//	message.GetAt(2,ncommand);
//	message.GetAt(3,ntimer);
	ncommand = m_ndkSend2[2];
	ntimer = m_ndkSend2[3];
	if(ncommand == 0x54 )
	{
    	if(ntimer == 0x01)
        	ggggg += "：校时成功";
    	else
        	ggggg += "：校时失败";

	}
	else if(ncommand == 0x4B)
	{
        	if(ntimer == 0x01)
            	ggggg += "：手动控制成功";
        	else if(ntimer == 0x02)
			{
            	ggggg += "：解除手动控制成功";
        		if(pFWnd->m_pSetTimeDlg != NULL)
				{
				pFWnd->m_pSetTimeDlg->m_nchangev =0;
				pFWnd->m_pSetTimeDlg->OnButRESre();
				}
			}
        	else
			{
              	ggggg += "：手动控制失败";
         		if(pFWnd->m_pSetTimeDlg != NULL)
				{
				pFWnd->m_pSetTimeDlg->m_nchangev =0;
				pFWnd->m_pSetTimeDlg->OnButRESre();
				}
			}
	}
	else if(ncommand == 0x43)
	{
    	if(ntimer == 0x01)
        	ggggg += "：分站通道配置成功";
    	else
        	ggggg += "：分站通道配置失败";
	}
	else if(ncommand == 0x46)
	{
    	if(ntimer == 0x01)
		{
        	ggggg += "：风电瓦斯闭锁设置成功";
        	CString strim2;
        	strim2.Format("设置%d号分站风电瓦斯闭锁：",nstation);
        	for(int i =0;i<6;i++)
			{
				int k = nstation*6 +i+1;
        	strSQL.Format("UPDATE commonset SET strc30='%s' WHERE CommonID=%d;",str_list[i].strl,k);
        	theApp.m_pConnection->Execute(_bstr_t(strSQL),NULL,adCmdText);
			strim2 +="["+ str_list[i].strl+"]   ";
			}
            g_Log.StatusOut(strim2);
    		if(pFWnd->m_pSetTimeDlg != NULL )
         		pFWnd->m_pSetTimeDlg->InitWGas(nstation);
		}
    	else
        	ggggg += "：风电瓦斯闭锁设置失败";
	}
	else if(ncommand == 0x5A)
	{
    	if(ntimer == 0x01)
		{
        	ggggg += "：故障闭锁设置成功";
            	strSQL.Format("UPDATE specialcontrol SET SpeCtrol=%d WHERE SID=%d;",theApp.n_temp,nstation);
            	theApp.m_pConnection->Execute(_bstr_t(strSQL),NULL,adCmdText);
				theApp.n_temp =0;
    		if(pFWnd->m_pSetTimeDlg != NULL && pFWnd->n_derr60 == 0)
            	pFWnd->m_pSetTimeDlg->Init5A();
		}
    	else
        	ggggg += "：故障闭锁设置失败";
	}
	else if(ncommand == 0x41)
	{
    	if(ntimer == 0x01)
        	ggggg = "60个分站设置成功";
    	else
        	ggggg = "60个分站设置失败";
	}
	else if(ncommand == 0x45)
	{
		 strtemp.Format("[%d号分站]",nstation);//分站号
       	 ggggg = strtemp + "：分站通讯失败";
		 nend = m_SlaveStation[nstation][0].Channel_state;
		 if(nend != 0x90)
			theApp.m_RTDM.FCError(nstation);
	}
    if(ncommand != 0x42 && ncommand != 0x45)
	{
		if(pFWnd->m_pSetTimeDlg != NULL)
        	pFWnd->m_pSetTimeDlg->ComDisMes(ggggg);
		g_Log.StatusOut(ggggg);
	}
//         AddWarn( ggggg, "", "", "", "", "", "", "");
//	else if(ncommand == 0x42)
//	{
//    	if(ntimer == 0x01)
//        	ggggg += "：自动控制成功";
//   	else
//        	ggggg += "：自动控制失败";
//         AddWarn( ggggg, "", "", "", "", "", "", "");
//	}

	//	message.GetAt(4,nend);
}

void CMQClient::ManageServerG(CNDKMessage& message)
{
    CMainFrame* pFWnd=(CMainFrame*)AfxGetMainWnd();
	CString ggggg,strtemp,strbegin;
    unsigned char  nstation ,nbegin ;
	message.GetAt(0, m_ndkSend2 ,m_unBufferLength);//44
//	message.GetAt(0,nbegin);
//	message.GetAt(1,nstation);
	nstation = m_ndkSend2[1];
    	strtemp.Format("[%d号分站]",nstation);
	if(nstation <1 || nstation >60)
	{
		g_Log.StatusOut(strtemp +"错误！");
		return;
	}
	if(pFWnd->m_pSetTimeDlg == NULL)
		return;

//    	ggggg += strtemp;
//	message.GetAt(2,ncommand);
//	message.GetAt(3,nbegin);
	nbegin = m_ndkSend2[3];
    	ggggg = strtemp + ":1通道  " + theApp.m_RTDM.strstatus(nbegin);
    	pFWnd->m_pSetTimeDlg->ComDisMes(ggggg);
//	message.GetAt(4,nbegin);
    	ggggg = strtemp + ":2通道  " + theApp.m_RTDM.strstatus(m_ndkSend2[4]);
    	pFWnd->m_pSetTimeDlg->ComDisMes(ggggg);
//	message.GetAt(5,nbegin);
    	ggggg = strtemp + ":3通道  " + theApp.m_RTDM.strstatus(m_ndkSend2[5]);
    	pFWnd->m_pSetTimeDlg->ComDisMes(ggggg);
//	message.GetAt(6,nbegin);
    	ggggg = strtemp + ":4通道  " + theApp.m_RTDM.strstatus(m_ndkSend2[6]);
    	pFWnd->m_pSetTimeDlg->ComDisMes(ggggg);
//	message.GetAt(7,nbegin);
    	ggggg = strtemp + ":5通道  " + theApp.m_RTDM.strstatus(m_ndkSend2[7]);
    	pFWnd->m_pSetTimeDlg->ComDisMes(ggggg);
//	message.GetAt(8,nbegin);
    	ggggg = strtemp + ":6通道  " + theApp.m_RTDM.strstatus(m_ndkSend2[8]);
    	pFWnd->m_pSetTimeDlg->ComDisMes(ggggg);
//	message.GetAt(9,nbegin);
    	ggggg = strtemp + ":7通道  " + theApp.m_RTDM.strstatus(m_ndkSend2[9]);
    	pFWnd->m_pSetTimeDlg->ComDisMes(ggggg);
//	message.GetAt(10,nbegin);
    	ggggg = strtemp + ":8通道  " + theApp.m_RTDM.strstatus(m_ndkSend2[10]);
    	pFWnd->m_pSetTimeDlg->ComDisMes(ggggg);
//	message.GetAt(11,nbegin);
    	ggggg = strtemp + ":9通道  " + theApp.m_RTDM.strstatus(m_ndkSend2[11]);
    	pFWnd->m_pSetTimeDlg->ComDisMes(ggggg);
//	message.GetAt(12,nbegin);
    	ggggg = strtemp + ":10通道  " + theApp.m_RTDM.strstatus(m_ndkSend2[12]);
    	pFWnd->m_pSetTimeDlg->ComDisMes(ggggg);
//	message.GetAt(13,nbegin);
    	ggggg = strtemp + ":11通道  " + theApp.m_RTDM.strstatus(m_ndkSend2[13]);
    	pFWnd->m_pSetTimeDlg->ComDisMes(ggggg);
//	message.GetAt(14,nbegin);
    	ggggg = strtemp + ":12通道  " + theApp.m_RTDM.strstatus(m_ndkSend2[14]);
    	pFWnd->m_pSetTimeDlg->ComDisMes(ggggg);
//	message.GetAt(15,nbegin);
    	ggggg = strtemp + ":13通道  " + theApp.m_RTDM.strstatus(m_ndkSend2[15]);
    	pFWnd->m_pSetTimeDlg->ComDisMes(ggggg);
//	message.GetAt(16,nbegin);
    	ggggg = strtemp + ":14通道  " + theApp.m_RTDM.strstatus(m_ndkSend2[16]);
    	pFWnd->m_pSetTimeDlg->ComDisMes(ggggg);
//	message.GetAt(17,nbegin);
    	ggggg = strtemp + ":15通道  " + theApp.m_RTDM.strstatus(m_ndkSend2[17]);
    	pFWnd->m_pSetTimeDlg->ComDisMes(ggggg);
//	message.GetAt(18,nbegin);
    	ggggg = strtemp + ":16通道  " + theApp.m_RTDM.strstatus(m_ndkSend2[18]);
    	pFWnd->m_pSetTimeDlg->ComDisMes(ggggg);
//	message.GetAt(19,nbegin);
	nbegin = m_ndkSend2[19];
	if((nbegin & 0x01) == 0x01)
    	ggggg = strtemp + ":控制通道1  断开";
	else
    	ggggg = strtemp + ":控制通道1  吸和";
    	pFWnd->m_pSetTimeDlg->ComDisMes(ggggg);
	if((nbegin & 0x02) == 0x02)
    	ggggg = strtemp + ":控制通道2  断开";
	else
    	ggggg = strtemp + ":控制通道2  吸和";
    	pFWnd->m_pSetTimeDlg->ComDisMes(ggggg);
	if((nbegin & 0x04) == 0x04)
    	ggggg = strtemp + ":控制通道3  断开";
	else
    	ggggg = strtemp + ":控制通道3  吸和";
    	pFWnd->m_pSetTimeDlg->ComDisMes(ggggg);
	if((nbegin & 0x08) == 0x08)
    	ggggg = strtemp + ":控制通道4  断开";
	else
    	ggggg = strtemp + ":控制通道4  吸和";
    	pFWnd->m_pSetTimeDlg->ComDisMes(ggggg);
	if((nbegin & 0x10) == 0x10)
    	ggggg = strtemp + ":控制通道5  断开";
	else
    	ggggg = strtemp + ":控制通道5  吸和";
    	pFWnd->m_pSetTimeDlg->ComDisMes(ggggg);
	if((nbegin & 0x20) == 0x20)
    	ggggg = strtemp + ":控制通道6  断开";
	else
    	ggggg = strtemp + ":控制通道6  吸和";
    	pFWnd->m_pSetTimeDlg->ComDisMes(ggggg);
	if((nbegin & 0x40) == 0x40)
    	ggggg = strtemp + ":控制通道7  断开";
	else
    	ggggg = strtemp + ":控制通道7  吸和";
    	pFWnd->m_pSetTimeDlg->ComDisMes(ggggg);
	if((nbegin & 0x80) == 0x80)
    	ggggg = strtemp + ":控制通道8  断开";
	else
    	ggggg = strtemp + ":控制通道8  吸和";
    	pFWnd->m_pSetTimeDlg->ComDisMes(ggggg);
//	message.GetAt(20,nbegin);
	nbegin = m_ndkSend2[20];
	if(nbegin == 0x00)
    	ggggg = strtemp + ":交流供电";
	else
    	ggggg = strtemp + ":直流供电";
    	pFWnd->m_pSetTimeDlg->ComDisMes(ggggg);

		g_Log.StatusOut(strtemp +"通讯测试成功！");
//	message.GetAt(4,nend);
//    	ggggg += "：关闭";
//    	ggggg += "：打开";
}
//7E 01 0x44
void CMQClient::CollectDate(CNDKMessage& message)
{
//	CString xxx;
	if(!theApp.b_startc)//处理数据
		return;
    	message.GetAt(0, m_ndkSendRT ,m_unBufferLength);//44
//	xxx.Format(_T("%d    %d"),m_byteBuffer[0],m_byteBuffer[1]);
//       g_Log.StatusOut(xxx);
//	AfxMessageBox(xxx );

	int nstation = m_ndkSendRT[1];
	if(m_SerialF[nstation].SFSd == 0)//没巡检
		return;
	if(nstation <1 || nstation >60 )//1-60
		return;
	for(int i=0 ; i< 44; i++)
		m_ndkSend[nstation][i] = m_ndkSendRT[i];

	m_SerialF[nstation].cfds = nstation;//有数据时为
//0xa1 没有巡检  0x90 分站故障
	if(m_SlaveStation[nstation][0].Channel_state == 0xa1 || m_SlaveStation[nstation][0].Channel_state == 0x90)
        for(int i = 0; i < MAX_CHAN;i++)
		{
			m_SlaveStation[nstation][i].Channel_state =255;
	    	m_SlaveStation[nstation][i].ValueTime = COleDateTime::GetCurrentTime();
		}

//		eventWriteD.SetEvent();
//    	CalRTdata(nstation);

//    	m_CPointInfo[nPointNo].pnValue = (dfValue-fMin )/(fMax -fMin );
/*		strItem.Format(_T("Item %f"), m_CPointInfo[state].ldfValue);
		if((pFWnd)&&(pFWnd->m_pSampleFormView!= NULL))
    		pFWnd->m_pSampleFormView2->SetInfo(3,state,strItem,strSubA,strSubB);
*/

}
