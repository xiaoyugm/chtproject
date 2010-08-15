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

extern ADMainDis         m_ADMainDis[65][25][65];          //调用显示
extern SerialF               m_ClassTime[200];            //班设置
unsigned char *m_ndkRTD;
extern ADCbreakE             m_CFeed[65][9][65];
extern  OthersSetting    m_OthersSetting;
extern SerialF               m_SerialF[65][65];
extern ADCbreakE             m_ADCbreakE[65][25][65];
extern SlaveStation             m_SlaveStation[65][25];
static int nYear, nMonth, nDay, nHour, nMinute, nSecond;
extern  CPointInfo m_CPointInfo[MAX_POINT_NUMBER];
CWarnPoint  m_CWarnPoint[MAX_POINT_NUMBER];
CStrWarn    m_CStrWarn[MAX_ROW];
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMQClient::CMQClient()
{
//		m_ndkSend=NULL;
//	ConnectDB();
	m_nodialog = true;
	m_adjustnum = 0;
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

}

void CMQClient::OnDisconnect(NDKClientDisconnection disconnectionType)
{

}

//连接数据库
void CMQClient::ConnectDB()
{
    CString szConnect = _T("Provider=SQLOLEDB.1;Persist Security Info=True;\
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
		m_Adjustdata.Open("Select * From adjustdata" , &m_Cn);
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

	    m_ndkRTD = new unsigned char[6];
  }
  catch ( dbAx::CAxException *e )
  {
		AfxMessageBox(e->m_szErrorDesc +  _T("BJygjl Message"));
//    MessageBox(e->m_szErrorDesc, _T("BJygjl Message"), MB_OK);
    delete e;
    return ;
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
  try
  {
/*    if ( m_AccountSet._IsOpen() )
      m_AccountSet.Close();
    if ( m_ContactSet._IsOpen() )
      m_ContactSet.Close();
    if ( m_MAlocation._IsOpen() )
      m_MAlocation.Close();
    if ( m_PointDes._IsOpen() )
      m_PointDes.Close();
    if ( m_DisPoint._IsOpen() )
      m_DisPoint.Close();
    if ( m_Control._IsOpen() )
      m_Control.Close();
    if ( m_SControl._IsOpen() )
      m_SControl.Close();*/
    if ( m_Realtimedata._IsOpen() )
      m_Realtimedata.Close();
    if ( m_Adjustdata._IsOpen() )
      m_Adjustdata.Close();

    m_Cn.Close();
    //Cleanup the AxLib library
    dbAx::Term();
  }
  catch ( CAxException *e )
  {
		AfxMessageBox(e->m_szErrorDesc +  _T("BJygjl Message"));
 //    MessageBox(e->m_szErrorDesc, _T("BJygjl Message"), MB_OK);
    delete e;
  }
  		delete m_ndkRTD;

	CloseConnection();
}

//获得主机的启动时间
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
	theApp.m_senddata = true;
	theApp.internet30s = 0;

	//if(ConnectTime != StartTime)   
///	SyncHostAndClient();
}

void CMQClient::ManageServer(CNDKMessage& message)
{
	theApp.internet30s = 0;
    CMainFrame* pFWnd=(CMainFrame*)AfxGetMainWnd();
	CString ggggg,strtemp,strbegin;
    unsigned char  nstation ,nbegin,nend,ncommand ;
	int  ntimer;

	unsigned char* m_ndkSend2 = new  unsigned char[44];
	message.GetAt(0, m_ndkSend2 ,44);

//	message.GetAt(0,nbegin);
//	message.GetAt(1,nstation);
	nstation = m_ndkSend2[1];
    	strtemp.Format("[%d号分站]",nstation);
    	ggggg += strtemp;
//	message.GetAt(2,ncommand);
//	message.GetAt(3,ntimer);
	ncommand = m_ndkSend2[2];
	ntimer = m_ndkSend2[3];
	if(ncommand == 0x54)
	{
    	if(ntimer == 0x01)
        	ggggg += "：校时成功";
    	else
        	ggggg += "：校时失败";
        	pFWnd->m_pSetTimeDlg->ComDisMes(ggggg);
	}
	else if(ncommand == 0x4B)
	{
        	if(ntimer == 0x01)
            	ggggg += "：手动控制成功";
        	else if(ntimer == 0x02)
			{
            	ggggg += "：解除手动控制成功";
				pFWnd->m_pSetTimeDlg->m_nchangev =0;
				pFWnd->m_pSetTimeDlg->OnButRESre();
			}
        	else
              	ggggg += "：手动控制失败";
        	pFWnd->m_pSetTimeDlg->ComDisMes(ggggg);
	}
	else if(ncommand == 0x43)
	{
    	if(ntimer == 0x01)
        	ggggg += "：分站通道配置成功";
    	else
        	ggggg += "：分站通道配置失败";
        	pFWnd->m_pSetTimeDlg->ComDisMes(ggggg);
	}
	else if(ncommand == 0x46)
	{
    	if(ntimer == 0x01)
        	ggggg += "：风电瓦斯闭锁设置成功";
    	else
        	ggggg += "：风电瓦斯闭锁设置失败";
        	pFWnd->m_pSetTimeDlg->ComDisMes(ggggg);
	}
	else if(ncommand == 0x5A)
	{
    	if(ntimer == 0x01)
        	ggggg += "：故障闭锁设置成功";
    	else
        	ggggg += "：故障闭锁设置失败";
        	pFWnd->m_pSetTimeDlg->ComDisMes(ggggg);
	}
	else if(ncommand == 0x41)
	{
    	if(ntimer == 0x01)
        	ggggg = "64个分站设置成功";
    	else
        	ggggg = "64个分站设置失败";
        	pFWnd->m_pSetTimeDlg->ComDisMes(ggggg);
	}
	else if(ncommand == 0x45)
	{
		 strtemp.Format("[%d号串口]",nstation);
       	 ggggg = strtemp + "：串口通讯失败";
         AddWarn( ggggg, "", "", "", "", "", "", "");
		 for(int j = 0; j < 65;j++)
		 {
    		 nbegin = m_SerialF[nstation][j].SFSd;
			 if(nbegin == 0)
				 break;
			 else
			 {
//        		 for(int i = 0; i < 25;i++)
				 {
					 nend = m_SlaveStation[nbegin][0].Channel_state;
					 if(nend != 0x90)
					 {
                		 strtemp.Format("[%d号分站]",nbegin);
    	                 AddWarn( m_SlaveStation[nbegin][0].WatchName, ggggg, "", "", "", "", "", "");
		    			 m_SlaveStation[nbegin][0].Channel_state = 0x90;
					 }
				 }
			 }
		 }
	}
	else if(ncommand == 0x42)
	{
    	if(ntimer == 0x01)
        	ggggg += "：自动控制成功";
    	else
        	ggggg += "：自动控制失败";
         AddWarn( ggggg, "", "", "", "", "", "", "");
	}

		delete m_ndkSend2;
	//	message.GetAt(4,nend);
}

void CMQClient::ManageServerG(CNDKMessage& message)
{
	theApp.internet30s = 0;
    CMainFrame* pFWnd=(CMainFrame*)AfxGetMainWnd();
	CString ggggg,strtemp,strbegin;
    unsigned char  nstation ,nbegin ;
	unsigned char* m_ndkSend2 = new  unsigned char[44];
	message.GetAt(0, m_ndkSend2 ,44);
//	message.GetAt(0,nbegin);
//	message.GetAt(1,nstation);
	nstation = m_ndkSend2[1];
    	strtemp.Format("[%d号分站]",nstation);
//    	ggggg += strtemp;
//	message.GetAt(2,ncommand);
//	message.GetAt(3,nbegin);
	nbegin = m_ndkSend2[3];
    	ggggg = strtemp + ":1通道  " + strstatus(nbegin);
    	pFWnd->m_pSetTimeDlg->ComDisMes(ggggg);
//	message.GetAt(4,nbegin);
    	ggggg = strtemp + ":2通道  " + strstatus(m_ndkSend2[4]);
    	pFWnd->m_pSetTimeDlg->ComDisMes(ggggg);
//	message.GetAt(5,nbegin);
    	ggggg = strtemp + ":3通道  " + strstatus(m_ndkSend2[5]);
    	pFWnd->m_pSetTimeDlg->ComDisMes(ggggg);
//	message.GetAt(6,nbegin);
    	ggggg = strtemp + ":4通道  " + strstatus(m_ndkSend2[6]);
    	pFWnd->m_pSetTimeDlg->ComDisMes(ggggg);
//	message.GetAt(7,nbegin);
    	ggggg = strtemp + ":5通道  " + strstatus(m_ndkSend2[7]);
    	pFWnd->m_pSetTimeDlg->ComDisMes(ggggg);
//	message.GetAt(8,nbegin);
    	ggggg = strtemp + ":6通道  " + strstatus(m_ndkSend2[8]);
    	pFWnd->m_pSetTimeDlg->ComDisMes(ggggg);
//	message.GetAt(9,nbegin);
    	ggggg = strtemp + ":7通道  " + strstatus(m_ndkSend2[9]);
    	pFWnd->m_pSetTimeDlg->ComDisMes(ggggg);
//	message.GetAt(10,nbegin);
    	ggggg = strtemp + ":8通道  " + strstatus(m_ndkSend2[10]);
    	pFWnd->m_pSetTimeDlg->ComDisMes(ggggg);
//	message.GetAt(11,nbegin);
    	ggggg = strtemp + ":9通道  " + strstatus(m_ndkSend2[11]);
    	pFWnd->m_pSetTimeDlg->ComDisMes(ggggg);
//	message.GetAt(12,nbegin);
    	ggggg = strtemp + ":10通道  " + strstatus(m_ndkSend2[12]);
    	pFWnd->m_pSetTimeDlg->ComDisMes(ggggg);
//	message.GetAt(13,nbegin);
    	ggggg = strtemp + ":11通道  " + strstatus(m_ndkSend2[13]);
    	pFWnd->m_pSetTimeDlg->ComDisMes(ggggg);
//	message.GetAt(14,nbegin);
    	ggggg = strtemp + ":12通道  " + strstatus(m_ndkSend2[14]);
    	pFWnd->m_pSetTimeDlg->ComDisMes(ggggg);
//	message.GetAt(15,nbegin);
    	ggggg = strtemp + ":13通道  " + strstatus(m_ndkSend2[15]);
    	pFWnd->m_pSetTimeDlg->ComDisMes(ggggg);
//	message.GetAt(16,nbegin);
    	ggggg = strtemp + ":14通道  " + strstatus(m_ndkSend2[16]);
    	pFWnd->m_pSetTimeDlg->ComDisMes(ggggg);
//	message.GetAt(17,nbegin);
    	ggggg = strtemp + ":15通道  " + strstatus(m_ndkSend2[17]);
    	pFWnd->m_pSetTimeDlg->ComDisMes(ggggg);
//	message.GetAt(18,nbegin);
    	ggggg = strtemp + ":16通道  " + strstatus(m_ndkSend2[18]);
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

		delete m_ndkSend2;
//	message.GetAt(4,nend);
//	if(nend == 0x01)
//    	ggggg += "：关闭";
//	else
//    	ggggg += "：打开";
}

void CMQClient::CollectDate(CNDKMessage& message)
{
    CMainFrame* pFWnd=(CMainFrame*)AfxGetMainWnd();
	theApp.internet30s = 0;
	CString2DataType m_Str2Data;
//	float    dfOld , fMin ,fMax ; 
	unsigned char  n_cdata;
//	unsigned char Warn_state ,state ,lWarn_state;
	CString strtemp,strtemp1,strtemp2,strtemp3,strtemp4,strtemp5,strtemp6;
    unsigned char  nstation ,nbegin ,ufData,ufData1,ufData2,ufData3,ufData4,ufData5,ufData6;
	int ndata,olddata;
	bool b5m,bhour,bhalf;
	b5m = false;    	bhour = false;  	bhalf = false;

	 m_ndkSend = new  unsigned char[44];
	message.GetAt(0, m_ndkSend ,44);
	nstation = 	m_ndkSend[1];

	ufData1 = 	m_ndkSend[37];
	ufData2 = 	m_ndkSend[38];
	ufData3 = 	m_ndkSend[39];
	ufData4 = 	m_ndkSend[40];
	ufData5 = 	m_ndkSend[41];
	ufData6 = 	m_ndkSend[42];
	strtemp1.Format(_T("%x"), ufData1);
	strtemp2.Format(_T("%x"), ufData2);
	strtemp3.Format(_T("%x"), ufData3);
	strtemp4.Format(_T("%x"), ufData4);
	strtemp5.Format(_T("%x"), ufData5);
	strtemp6.Format(_T("%x"), ufData6);
	m_ndkRTD[0] = m_Str2Data.String2Int(strtemp1);
	m_ndkRTD[1] = m_Str2Data.String2Int(strtemp2);
	m_ndkRTD[2] = m_Str2Data.String2Int(strtemp3);
	m_ndkRTD[3] = m_Str2Data.String2Int(strtemp4);
	m_ndkRTD[4] = m_Str2Data.String2Int(strtemp5);
	m_ndkRTD[5] = m_Str2Data.String2Int(strtemp6);
	CTime t = CTime::GetCurrentTime();
	COleDateTime told;
	COleDateTime timetemp(2000+m_ndkRTD[0],m_ndkRTD[1],m_ndkRTD[2],m_ndkRTD[3],m_ndkRTD[4],m_ndkRTD[5]);
	strtemp.Format(_T("20%x-%x-%x %x:%x:%x"), ufData1,ufData2,ufData3,ufData4,ufData5,ufData6);

	unsigned char nItem =1;
	for(int i=3 ; i< 34 ;i=i+2)     //3,4 1     33,34 16
	{
		if(m_SlaveStation[nstation][nItem].WatchName != "")
		{
	    	ufData6 = m_SlaveStation[nstation][nItem].ptype;
//    	    message.GetAt(i, ufData);
			ufData = m_ndkSend[i];
			ufData1 = ufData & 0xf0;
			ufData5 = m_SlaveStation[nstation][nItem].Channel_state;
//		    m_SlaveStation[nstation][nItem].OldChannel_state = ufData5;
		    m_SlaveStation[nstation][nItem].Channel_state = ufData1;
//    	    message.GetAt(i+1, n_cdata);
			n_cdata = m_ndkSend[i+1];
			ndata = (ufData & 0x0f)*256 +n_cdata;
			ufData4 = m_SlaveStation[nstation][nItem].Adjust_state;

			told = m_SlaveStation[nstation][nItem].ValueTime;
        	CTime t1(told.GetYear(),told.GetMonth(),told.GetDay(),told.GetHour(),told.GetMinute(),told.GetSecond());
			if((t.GetTime()-t1.GetTime())>1800)
				bhalf = true;

			if(ufData6 < 3)
			{
				olddata = m_SlaveStation[nstation][nItem].CValue;
				if((olddata != ndata)|| bhalf)
				{
			    	m_SlaveStation[nstation][nItem].CValue = ndata;
	             	if(ufData6 == 0)
					{
	    	        	m_SlaveStation[nstation][nItem].AValue = (m_SlaveStation[nstation][nItem].m_RangeH-m_SlaveStation[nstation][nItem].m_RangeL)*(ndata-300)/1200;
	             		m_SlaveStation[nstation][nItem].pnValue = (ndata-300)/12;
					}
		         	else if(ufData6 == 1 || ufData6 == 2)
					{
	             		m_SlaveStation[nstation][nItem].pnValue = (ndata-200)/8;
		         		m_SlaveStation[nstation][nItem].AValue = (m_SlaveStation[nstation][nItem].m_RangeH-m_SlaveStation[nstation][nItem].m_RangeL)*(ndata-200)/800;
					}
          			if(ufData4 == 1)
	     				theApp.SocketServer.SyncCRTData(nstation,nItem,1); 
					else
					{
	     				theApp.SocketServer.SyncCRTData(nstation,nItem,0); 
						float fcurv =m_SlaveStation[nstation][nItem].AValue;
						if(m_SlaveStation[nstation][nItem].AMaxValue<fcurv)
							m_SlaveStation[nstation][nItem].AMaxValue = fcurv;
						if(m_SlaveStation[nstation][nItem].AMinValue>fcurv)
							m_SlaveStation[nstation][nItem].AMinValue = fcurv;
						m_SlaveStation[nstation][nItem].m_Atotal++;
						m_SlaveStation[nstation][nItem].ATotalValue +=fcurv;

						CTime vt(2000+m_ndkRTD[0],m_ndkRTD[1],m_ndkRTD[2],m_ndkRTD[3],m_ndkRTD[4],m_ndkRTD[5]);
						CTime m5minute = m_SlaveStation[nstation][nItem].m_5m;
						if(vt.GetTime()-m5minute.GetTime() >=300)
						{
	        				theApp.SocketServer.SyncCRTData(nstation,nItem,10); 
							m_SlaveStation[nstation][nItem].m_5m = vt;
							m_SlaveStation[nstation][nItem].AMaxValue=fcurv;
							m_SlaveStation[nstation][nItem].AMinValue=fcurv;
							m_SlaveStation[nstation][nItem].m_Atotal=0;
							m_SlaveStation[nstation][nItem].ATotalValue=0;
						}
					}
					bhalf = false;
         			m_SlaveStation[nstation][nItem].ValueTime = timetemp;
					//调用显示最大值、平均值
					if(m_ADMainDis[nstation][nItem][0].AMaxValue < m_SlaveStation[nstation][nItem].AValue)
						m_ADMainDis[nstation][nItem][0].AMaxValue = m_SlaveStation[nstation][nItem].AValue;
					m_ADMainDis[nstation][nItem][0].m_ATotalnum++;
					m_ADMainDis[nstation][nItem][0].ATotalV += m_SlaveStation[nstation][nItem].AValue;
				}
				strtemp1.Format(_T("%.2f"), m_SlaveStation[nstation][nItem].AValue);
			    if((ufData1 == 0x40)|| (ufData1 == 0x50)  || (ufData1 == 0x60))
				{
					//第二次断电确认
            		int m_two =m_SlaveStation[nstation][nItem].m_second;
                    if(ufData5 != ufData1 || m_two ==1) 
					{
	    	    			 if(m_SlaveStation[nstation][0].AlarmState ==1)
							 {
	        					m_ADMainDis[nstation][nItem][0].BTime = timetemp;
                               pFWnd->m_wndResourceView.InitLC(nstation,nItem);
                               pFWnd->m_wndResourceView2.InitLB(nstation,nItem);
                               pFWnd->m_wndResourceView3.InitLF(nstation,nItem);
							 }
						if(m_two ==0)
			        		 m_SlaveStation[nstation][nItem].m_second++;
						else
							 m_SlaveStation[nstation][nItem].m_second =0;
						if(ufData5 != ufData1)
					     	//0通道故障闭锁使能
	    	    			 if(m_SlaveStation[nstation][0].AlarmState ==1)
    			        		   handbr(nstation,nItem,1);
						Savefeedbr(nstation,nItem);  //馈电状态
					}
				}
			}
			else
			{
				olddata = m_SlaveStation[nstation][nItem].CValue;
				if((olddata != n_cdata)|| bhalf)
				{
					m_SlaveStation[nstation][nItem].CValue = n_cdata;
					strtemp1.Format(_T("%d"), n_cdata);
          			if(ufData4 == 1)
	     				theApp.SocketServer.SyncCRTData(nstation,nItem,1); 
					else
	     				theApp.SocketServer.SyncCRTData(nstation,nItem,0); 
					bhalf = false;
         			m_SlaveStation[nstation][nItem].ValueTime = timetemp;
                    pFWnd->m_wndResourceView6.InitLDCH(nstation,nItem);
				}
			}

			if(ufData1 == 0x00)
			{
    			int m_two = m_SlaveStation[nstation][nItem].m_second;
				//报警后不用复电
				if(((ufData5 != 0x10)&&(ufData1 != ufData5)) || m_two ==1)
				{
					if(m_two ==0)
			            m_SlaveStation[nstation][nItem].m_second++;
					else
			            m_SlaveStation[nstation][nItem].m_second =0;
					if((ufData5 != 0x10)&&(ufData1 != ufData5))
    			    		handbr(nstation,nItem,0);
                 		if(ufData6 < 3)
						{
	     				m_ADMainDis[nstation][nItem][0].NTime = timetemp;
                         pFWnd->m_wndResourceView.InitLC(nstation,nItem);
                         pFWnd->m_wndResourceView3.InitLF(nstation,nItem);
						}
			    		else
                         pFWnd->m_wndResourceView5.InitLDF(nstation,nItem);
					Savefeedbr(nstation,nItem);  //馈电状态
				}
			}
			else if(ufData1 == 0x10)
			{
                if(ufData5 != 0x10)
				{
						m_ADMainDis[nstation][nItem][0].ATime = timetemp;
	        		if(ufData6 < 3)
					{
                         pFWnd->m_wndResourceView.InitLC(nstation,nItem);
					}
					else
                         pFWnd->m_wndResourceView4.InitLDAB(nstation,nItem);
				}
			}
			else if(ufData1 == 0x20)
			{
    			int m_two = m_SlaveStation[nstation][nItem].m_second;
                if(ufData5 != 0x20 || m_two==1)
				{
					m_ADMainDis[nstation][nItem][0].BTime = timetemp;
	        		if(ufData6 < 3)
					{
                         pFWnd->m_wndResourceView.InitLC(nstation,nItem);
                         pFWnd->m_wndResourceView2.InitLB(nstation,nItem);
                         pFWnd->m_wndResourceView3.InitLF(nstation,nItem);
					}
					else
					{
                         pFWnd->m_wndResourceView4.InitLDAB(nstation,nItem);
                         pFWnd->m_wndResourceView5.InitLDF(nstation,nItem);
					}
					if(ufData5 != 0x20)
     					handbr(nstation,nItem,1);
					if(m_two ==0)
			            m_SlaveStation[nstation][nItem].m_second++;
					else
			            m_SlaveStation[nstation][nItem].m_second =0;
					Savefeedbr(nstation,nItem);  //馈电状态
				}
			}
			else if(ufData1 == 0x70)
			{
                if(ufData5 != ufData1)
				{
					if(m_SlaveStation[nstation][0].AlarmState ==1)
					{
    					handbr(nstation,nItem,1);
	    				m_ADMainDis[nstation][nItem][0].BTime = timetemp;
					}
	        		if(ufData6 < 3)
					{
                         pFWnd->m_wndResourceView.InitLC(nstation,nItem);
                         pFWnd->m_wndResourceView2.InitLB(nstation,nItem);
                         pFWnd->m_wndResourceView3.InitLF(nstation,nItem);
					}
					else
					{
                         pFWnd->m_wndResourceView4.InitLDAB(nstation,nItem);
                         pFWnd->m_wndResourceView5.InitLDF(nstation,nItem);
					}
					Savefeedbr(nstation,nItem);  //馈电状态
				}
			}
		}
		nItem++;
	}
//	message.GetAt(35, nbegin);    //控制量状态
	nbegin = m_ndkSend[35];
	for( i =17 ;i <25 ;i++)
	{
		if(i == 17)
    		ufData = nbegin & 0x01;
		else if(i == 18)
    		ufData = nbegin & 0x02;
		else if(i == 19)
    		ufData = nbegin & 0x04;
		else if(i == 20)
    		ufData = nbegin & 0x08;
		else if(i == 21)
    		ufData = nbegin & 0x10;
		else if(i == 22)
    		ufData = nbegin & 0x20;
		else if(i == 23)
    		ufData = nbegin & 0x40;
		else if(i == 24)
    		ufData = nbegin & 0x80;

			told = m_SlaveStation[nstation][i].ValueTime;
        	CTime t2(told.GetYear(),told.GetMonth(),told.GetDay(),told.GetHour(),told.GetMinute(),told.GetSecond());
			if((t.GetTime()-t2.GetTime())>1800)
				bhalf = true;

		//第二次断电确认
        int m_two =m_SlaveStation[nstation][i].m_second;
		ufData1 = m_SlaveStation[nstation][i].CValue;
		if((ufData1 != ufData)|| bhalf || m_two==1)
		{
			if(m_two ==1)
			{
				m_SlaveStation[nstation][i].m_second =0;
	    		feedbr(nstation , i );//馈电状态
			}
			else
			{
			    m_SlaveStation[nstation][i].m_second++;
            	m_SlaveStation[nstation][i].CValue = ufData;
    			m_SlaveStation[nstation][i].ValueTime = timetemp;
    			ufData4 = m_SlaveStation[nstation][i].Adjust_state;
    			if(ufData4 == 1)
					theApp.SocketServer.SyncCRTData(nstation,i,1);     //adjustdata
       			else
	     			theApp.SocketServer.SyncCRTData(nstation,i,0);     //rtdata
			}
			bhalf = false;
		}
	}
	ufData = m_ndkSend[36];
//	message.GetAt(36, ufData);    //AC/DC+电池电压
	m_SlaveStation[nstation][0].CValue = ufData & 0xf0;
	m_SlaveStation[nstation][0].ValueTime = timetemp;

		delete m_ndkSend;
		m_ndkSend=NULL;

//	message.GetAt(43, nend);
//    	m_CPointInfo[nPointNo].pnValue = (dfValue-fMin )/(fMax -fMin );
/*		strItem.Format(_T("Item %f"), m_CPointInfo[state].ldfValue);
		if((pFWnd)&&(pFWnd->m_pSampleFormView!= NULL))
    		pFWnd->m_pSampleFormView2->SetInfo(3,state,strItem,strSubA,strSubB);
*/

}
//控制量馈电状态
void CMQClient::feedbr(unsigned char  hfds, unsigned char  hchan)
{
    CMainFrame* pFWnd=(CMainFrame*)AfxGetMainWnd();
	CString strtemp;
			 int cvalue = m_SlaveStation[hfds][hchan].CValue;
			 for(int j= 0 ;j<64 ; j++)
			 {
    		     int ffds = m_CFeed[hfds][hchan-16][j].bFSd;
	       		 int fchan = m_CFeed[hfds][hchan-16][j].bchanel;
				 if(ffds == 0)
	 				 break;
				 strtemp = m_SlaveStation[ffds][fchan].FeedState;
	    		 int dvalue = m_SlaveStation[ffds][fchan].CValue;
				 if(cvalue == 1)
				 {
					 if(dvalue ==0)
						 m_SlaveStation[ffds][fchan].FeedState ="正常";
					 else if(strtemp =="正常")
						 m_SlaveStation[ffds][fchan].FeedState ="异常";
	         		int ufData4 = m_SlaveStation[ffds][fchan].Adjust_state;
	          		if(ufData4 == 1)
		      			theApp.SocketServer.SyncCRTData(ffds,fchan,5);     //adjustdata
	        		else
	     	      		theApp.SocketServer.SyncCRTData(ffds,fchan,4);     //rtdata
				 }
				 else if(cvalue ==0)
				 {
					 if((dvalue ==0) &&(strtemp =="正常"))
						 m_SlaveStation[ffds][fchan].FeedState ="异常";
					 else if(dvalue ==1)
						 m_SlaveStation[ffds][fchan].FeedState ="正常";
	         		int ufData4 = m_SlaveStation[ffds][fchan].Adjust_state;
	          		if(ufData4 == 1)
		      			theApp.SocketServer.SyncCRTData(ffds,fchan,5);     //adjustdata
	        		else
	     	      		theApp.SocketServer.SyncCRTData(ffds,fchan,4);     //rtdata 馈电
				 }
				m_ADMainDis[ffds][fchan][0].RTime = COleDateTime::GetCurrentTime();
			 }
}
//模拟量开关量馈电存储
void CMQClient::Savefeedbr(unsigned char  hfds, unsigned char  hchan)
{
    CMainFrame* pFWnd=(CMainFrame*)AfxGetMainWnd();
	CString strtemp;
	for(int i= 0 ;i<64 ; i++)
	{
		     int cfds = m_ADCbreakE[hfds][hchan][i].bFSd;
			 int cchan = m_ADCbreakE[hfds][hchan][i].bchanel;
			 if(cfds == 0)
				 break;
			 for(int j= 0 ;j<64 ; j++)
			 {
    		     int ffds = m_CFeed[cfds][cchan][j].bFSd;
	       		 int fchan = m_CFeed[cfds][cchan][j].bchanel;
				 if(ffds == 0)
	 				 break;
    			 int cvalue = m_SlaveStation[cfds][cchan+16].CValue;
				 strtemp = m_SlaveStation[ffds][fchan].FeedState;
	    		 int dvalue = m_SlaveStation[ffds][fchan].CValue;
				 if(cvalue == 1)
				 {
					 if(dvalue ==0)
						 m_SlaveStation[ffds][fchan].FeedState ="正常";
					 else if(strtemp =="正常")
						 m_SlaveStation[ffds][fchan].FeedState ="异常";
					 m_SlaveStation[hfds][hchan].m_ffds = ffds;
					 m_SlaveStation[hfds][hchan].m_fchan =fchan;
	         		int ufData4 = m_SlaveStation[hfds][hchan].Adjust_state;
	          		if(ufData4 == 1)
		      			theApp.SocketServer.SyncCRTData(hfds,hchan,3);     //adjustdata
	        		else
	     	      		theApp.SocketServer.SyncCRTData(hfds,hchan,2);     //rtdata
				 }
				 else if(cvalue ==0)
				 {
					 if((dvalue ==0) &&(strtemp =="正常"))
						 m_SlaveStation[ffds][fchan].FeedState ="异常";
					 else if(dvalue ==1)
						 m_SlaveStation[ffds][fchan].FeedState ="正常";
					 m_SlaveStation[hfds][hchan].m_ffds = ffds;
					 m_SlaveStation[hfds][hchan].m_fchan =fchan;
	         		int ufData4 = m_SlaveStation[hfds][hchan].Adjust_state;
	          		if(ufData4 == 1)
		      			theApp.SocketServer.SyncCRTData(hfds,hchan,3);     //adjustdata
	        		else
	     	      		theApp.SocketServer.SyncCRTData(hfds,hchan,2);     //rtdata 馈电
				 }
				m_ADMainDis[ffds][fchan][0].RTime = COleDateTime::GetCurrentTime();
			 }
	}
}
//断电器 开关量
void CMQClient::handbr(unsigned char  hfds, unsigned char  hchan, unsigned char hbr)
{
    CMainFrame* pFWnd=(CMainFrame*)AfxGetMainWnd();
	unsigned char cfds,cchan  ,nfds,nchan;
	for(int i= 0 ;i<64 ; i++)
	{
	m_ndkSend1 = new unsigned char[6];
		     cfds = m_ADCbreakE[hfds][hchan][i].bFSd;
			 cchan = m_ADCbreakE[hfds][hchan][i].bchanel;
			 if(cfds == 0)
			 {
            		delete m_ndkSend1;
            		m_ndkSend1=NULL;
				 break;
			 }
			CTime t=CTime::GetCurrentTime();
			CString strCTime;
			strCTime.Format("%d-%d-%d %d:%d:%d",t.GetYear(),t.GetMonth(),t.GetDay(),t.GetHour(),t.GetMinute(),t.GetSecond());
                    m_ndkSend1[0] = 0x7E;
                    m_ndkSend1[1] = cfds;
                    m_ndkSend1[2] = 0x42;
                    m_ndkSend1[3] = cchan;
                    m_ndkSend1[4] = hbr;
                    m_ndkSend1[5] = 0x21;
					if(hbr)    //断电
					{
						if(hfds != cfds)
						{
    	CNDKMessage message1(AUTOCONTROL);
					message1.Add(m_ndkSend1 ,6);
					theApp.Sync(message1);
//                         pFWnd->m_wndResourceView.InitLC(cfds,cchan+16);
						}
					}
					else
					{
						//只有控制通道关联的所有AD为正常，复电,不对本分站复电
						bool isret = false;
						for(int j= 0 ;j<64 ; j++)
						{
							nfds = m_ADCbreakE[cfds][cchan+16][j].bFSd;
							nchan = m_ADCbreakE[cfds][cchan+16][j].bchanel;
							if(!((nfds >0) && (nchan >0)))
                     				 break;
							if(m_SlaveStation[nfds][nchan].Channel_state == 0x00)
							{
								if(hfds != nfds)
		    						isret = true;
							}
							else
							{
								isret = false;
								break;
							}
						}
						if(isret)
						{
    	CNDKMessage message1(AUTOCONTROL);
					message1.Add(m_ndkSend1 ,6);
					theApp.Sync(message1);
//                         pFWnd->m_wndResourceView.InitLC(cfds,cchan+16);
						}
					}

		delete m_ndkSend1;
		m_ndkSend1=NULL;
	}
}

void CMQClient::SaveRtdata(unsigned char  afds, unsigned char  achan)
{
//            				try
							{
	         				 m_RealtimedataNew->m_szRTID  = 1;
		      			     m_RealtimedataNew->m_szName = m_SlaveStation[afds][achan].WatchName;
							 int m_nptype = m_SlaveStation[afds][achan].ptype;
		    			     m_RealtimedataNew->m_szptype = m_nptype;
    						 m_RealtimedataNew->m_szfds = afds;
     						 m_RealtimedataNew->m_szchan = achan;
							 if(m_nptype >3)
							 {
    						      m_RealtimedataNew->m_szCDValue = m_SlaveStation[afds][achan].CValue;
     				   		      m_RealtimedataNew->m_szAValue = 0;
							 }
							 else
							 {
    						      m_RealtimedataNew->m_szCDValue = 0;
     				   		      m_RealtimedataNew->m_szAValue = m_SlaveStation[afds][achan].AValue;
							 }
    						 m_RealtimedataNew->m_szADStatus = m_SlaveStation[afds][achan].Channel_state;
    						 m_RealtimedataNew->m_szrecdate = m_SlaveStation[afds][achan].ValueTime;
     						 m_RealtimedataNew->m_szUseridadd = theApp.curuser;
      						m_RealtimedataNew->AddNew();  //Add a new, blank record
					   	    m_RealtimedataNew->Update();    //Update the recordset
							//If this is a new record, requery the database table
							//otherwise we may out-of-sync
						    m_RealtimedataNew->Requery();
							}
//		     			    catch (CAxException *e)
							{
//					        	AfxMessageBox(e->m_szErrorDesc, MB_OK);
//				        		delete e;
							}
}

void CMQClient::SaveAdjust(unsigned char  afds, unsigned char  achan)
{
            				try
							{
	         				 m_AdjustdataNew->m_szADID  = 1;
		      			     m_AdjustdataNew->m_szName = m_SlaveStation[afds][achan].WatchName;
							 int m_nptype = m_SlaveStation[afds][achan].ptype;
		    			     m_AdjustdataNew->m_szptype = m_nptype;
    						 m_AdjustdataNew->m_szfds = afds;
     						 m_AdjustdataNew->m_szchan = achan;
							 if(m_nptype >3)
							 {
    						      m_AdjustdataNew->m_szCDValue = m_SlaveStation[afds][achan].CValue;
     				   		      m_AdjustdataNew->m_szAValue = 0;
							 }
							 else
							 {
    						      m_AdjustdataNew->m_szCDValue = 0;
     				   		      m_AdjustdataNew->m_szAValue = m_SlaveStation[afds][achan].AValue;
							 }
    						 m_AdjustdataNew->m_szADStatus = m_SlaveStation[afds][achan].Channel_state;
    						 m_AdjustdataNew->m_szrecdate = m_SlaveStation[afds][achan].ValueTime;
     						 m_AdjustdataNew->m_szUseridadd = theApp.curuser;
      						m_AdjustdataNew->AddNew();  //Add a new, blank record
					   	    m_AdjustdataNew->Update();    //Update the recordset
							//If this is a new record, requery the database table
							//otherwise we may out-of-sync
						    m_AdjustdataNew->Requery();
							}
		     			    catch (CAxException *e)
							{
					        	AfxMessageBox(e->m_szErrorDesc, MB_OK);
				        		delete e;
							}
}

CString CMQClient::strstatus(unsigned char ustatus)
{
	CString str;
	if(ustatus == 0x00)
		str = "正常";
	else if((ustatus == 0x01) ||(ustatus == 0x10))
		str = "报警";
	else if((ustatus == 0x02) ||(ustatus == 0x20))
		str = "断电";
	else if((ustatus == 0x04) ||(ustatus == 0x40))
		str = "断线";
	else if((ustatus == 0x05) ||(ustatus == 0x50))
		str = "溢出";
	else if((ustatus == 0x06) ||(ustatus == 0x60))
		str = "负漂";
	else if((ustatus == 0x07) ||(ustatus == 0x70))
		str = "故障";
	else if((ustatus == 0x08) ||(ustatus == 0x80))
		str = "标校";
	else if((ustatus == 0x90))
		str = "串口故障";
	else if((ustatus == 0xa0))
		str = "以太网故障";
	return  str;
}

//更新报警表
void CMQClient::DiaplayWarnTableC(unsigned short nPointNo)
{
/*	CString strPoint,strDate,strTime ,strText ,strWarn;
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
			}
         	else if((Warn_state & 0x30) == 0x20)
			{
                strPointNo.Format("%d",nPointNo);
				if (nPointNo < 4) 
                    strWarnDate.Format(" 报警 %d-- %4.2f %s",ufData,dfValue,usUnit);
				else if (nPointNo > 4)
            		strWarnDate.Format(" 报警 %d ",ufData );
			}
			
    	m_CWarnPoint[0].warnPoint = nPointNo;
*/
}

void CMQClient::AddWarn( CString strtemp, CString strtemp1, CString strtemp2, CString strtemp3, CString strtemp4, CString strtemp5, CString strtemp6, CString strtemp7)
{
		m_CStrWarn[0].locationname = strtemp;
		m_CStrWarn[0].strValue = strtemp1;
		m_CStrWarn[0].warnTime = strtemp2;
		m_CStrWarn[0].breakTime = strtemp3;
		m_CStrWarn[0].restoreTime = strtemp4;
//		m_CStrWarn[0].feedStatus = strtemp5;
		m_CStrWarn[0].feedTime = strtemp6;
		m_CStrWarn[0].safetyprecautions = strtemp7;
	for(int i=MAX_ROW-1;i>0;i--)
	{
		m_CStrWarn[i].locationname = m_CStrWarn[i-1].locationname;
		m_CStrWarn[i].strValue = m_CStrWarn[i-1].strValue;
		m_CStrWarn[i].warnTime = m_CStrWarn[i-1].warnTime;
		m_CStrWarn[i].breakTime = m_CStrWarn[i-1].breakTime;
		m_CStrWarn[i].restoreTime = m_CStrWarn[i-1].restoreTime;
//		m_CStrWarn[i].feedStatus = m_CStrWarn[i-1].feedStatus;
		m_CStrWarn[i].feedTime = m_CStrWarn[i-1].feedTime;
		m_CStrWarn[i].safetyprecautions = m_CStrWarn[i-1].safetyprecautions;
	}

    CMainFrame* pFWnd=(CMainFrame*)AfxGetMainWnd();
//    pFWnd->Msg(0,m_CStrWarn[0].strPoint , m_CStrWarn[0].strDate , m_CStrWarn[0].strText ,m_CStrWarn[0].strWarn ,m_CStrWarn[0].strTime);

}

void CMQClient::CalRtDB(CTime time,int  &eYear, unsigned char  &eMonth)
{
	int m_h = m_ClassTime[1].ffds;
		int m_year = time.GetYear();
		int m_mon = time.GetMonth();
	if(m_h >12)
	{
    	long m_addt = time.GetTime()+(24-m_h)*3600;
		CTime t1 (m_addt);
		int t1_year = t1.GetYear();
		int t1_mon = t1.GetMonth();
		if(t1_mon != m_mon)
		{
			eYear = t1_year;
			eMonth = t1_mon;
		}
		else
		{
			eYear = m_year;
			eMonth = m_mon;
		}
	}
	else
	{
    	long m_addt = time.GetTime()-m_h*3600;
		CTime t1 (m_addt);
		int t1_year = t1.GetYear();
		int t1_mon = t1.GetMonth();
		if(t1_mon != m_mon)
		{
			eYear = t1_year;
			eMonth = t1_mon;
		}
		else
		{
			eYear = m_year;
			eMonth = m_mon;
		}
	}
}
