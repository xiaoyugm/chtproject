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
	case MANUALCONTROL:
//		DiaplayWarnTableC(message);
		ManageServerK(message);
		break;
	case VERIFYTIMER:
		ManageServerT(message);
		break;
	case REALTIMEDATA:
    	CollectDate(message);
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
		AfxMessageBox("��������ͨѶ��ϵʧ��,����!");
	}
}

//�رյ�����������
void CMQClient::Close()
{
	CloseConnection();
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

	theApp.m_senddata = true;
//	CNDKMessage message1(REALTIMEDATA);
//					message1.Add(0x7E);
//					message1.Add(0x01);
//	 				message1.Add(0x44);
//					message1.Add(0x21);
//					theApp.Sync(message1);


	//if(ConnectTime != StartTime)   
///	SyncHostAndClient();
}

void CMQClient::ManageServerT(CNDKMessage& message)
{
    CMainFrame* pFWnd=(CMainFrame*)AfxGetMainWnd();
	CString ggggg,strtemp,strbegin;
    unsigned char  nstation ,nbegin,nend,ncommand ,ufData;
	int  ntimer;
	message.GetAt(0,nbegin);
    	strtemp.Format("[%d��]",nbegin);
    	ggggg += strtemp;
	message.GetAt(1,nstation);
    	strtemp.Format("[%d�ŷ�վ]",nstation);
    	ggggg += strtemp;
	message.GetAt(2,ncommand);
    	strtemp.Format("[%d��]",ncommand);
    	ggggg += strtemp;
	message.GetAt(3,ntimer);
	if(ntimer == 0x01)
	{
//	strtemp.Format("[%d]",ntimer);
	ggggg += "��Уʱ�ɹ�";
	}
	else
    	ggggg += "��Уʱʧ��";
	message.GetAt(4,nend);
    	strtemp.Format("[%d��]",nend);
    	ggggg += strtemp;
	pFWnd->AddMessage(ggggg);
}

void CMQClient::ManageServerK(CNDKMessage& message)
{
    CMainFrame* pFWnd=(CMainFrame*)AfxGetMainWnd();
	CString ggggg,strtemp,strbegin;
    unsigned char  nstation ,nbegin,nend,ncommand ,ufData;
	int  ntimer;
//	message.GetAt(0,nbegin);
	message.GetAt(1,nstation);
    	strtemp.Format("[%d�ŷ�վ]",nstation);
    	ggggg += strtemp;
	message.GetAt(2,ncommand);
    	strtemp.Format("[%dͨ��]",ncommand);
    	ggggg += strtemp;
	message.GetAt(3,ntimer);
	if(ntimer == 0x01)
	{
//	strtemp.Format("[%d]",ntimer);
	ggggg += "���ֶ����Ƴɹ�";
	}
	else
    	ggggg += "���ֶ�����ʧ��";
	message.GetAt(4,nend);
	if(nend == 0x01)
	{
//	strtemp.Format("[%d]",ntimer);
	ggggg += "���ر�";
	}
	else
    	ggggg += "����";
	pFWnd->AddMessage(ggggg);
}

void CMQClient::CollectDate(CNDKMessage& message)
{
//	double dfValue , fMin ,fMax ; 
	unsigned char  nPointNo;
//	unsigned char Warn_state ,state ,lWarn_state;
    unsigned char  usPrecision ;
	CString ggggg,strtemp;
    unsigned char  nstation ,nbegin,nend,ncommand ,ufData;

	message.GetAt(0, nbegin);
	strtemp.Format("[%d]",nbegin);
	ggggg += strtemp;
	message.GetAt(1, nstation);
	strtemp.Format("[%d]",nstation);
	ggggg += strtemp;
	message.GetAt(2, ncommand);
	strtemp.Format("[%d]",ncommand);
	ggggg += strtemp;

	message.GetAt(3, ufData);
	strtemp.Format("[%d]",ufData);
	ggggg += strtemp;
	message.GetAt(4, ufData);       //1
	strtemp.Format("[%d]",ufData);
	ggggg += strtemp;
	message.GetAt(5, ufData);
	strtemp.Format("[%d]",ufData);
	ggggg += strtemp;
	message.GetAt(6, ufData);       //2
	strtemp.Format("[%d]",ufData);
	ggggg += strtemp;
	message.GetAt(7, ufData);
	message.GetAt(8, ufData);       //3
	message.GetAt(9, ufData);
	message.GetAt(10, ufData);      //4
	message.GetAt(11, ufData);
	message.GetAt(12, ufData);      //5
	message.GetAt(13, ufData);
	message.GetAt(14, ufData);      //6
	message.GetAt(15, ufData);
	message.GetAt(16, ufData);      //7
	strtemp.Format("[%d]",ufData);
	ggggg += strtemp;

	message.GetAt(17, ufData);
	strtemp.Format("[%d]",ufData);
	ggggg += strtemp;

	message.GetAt(18, ufData);
	strtemp.Format("[%d]",ufData);
	ggggg += strtemp;
	message.GetAt(19, ufData);
	strtemp.Format("[%d]",ufData);
	ggggg += strtemp;
	message.GetAt(20, ufData);
	strtemp.Format("[%d]",ufData);
	ggggg += strtemp;
	message.GetAt(21, ufData);
	strtemp.Format("[%d]",ufData);
	ggggg += strtemp;
	message.GetAt(22, ufData);
	strtemp.Format("[%d]",ufData);
	ggggg += strtemp;
	message.GetAt(23, ufData);
	strtemp.Format("[%d]",ufData);
	ggggg += strtemp;

	message.GetAt(24, nend);
	strtemp.Format("[%d]",nend);
	ggggg += strtemp;

    AfxMessageBox(ggggg);
/*	if(state == 1)
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
*/
//    CMainFrame* pFWnd=(CMainFrame*)AfxGetMainWnd();
	
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

//���±�����
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
                    strWarnDate.Format("���� %d -- %4.2f %s",ufData,dfValue,usUnit);
				else if (nPointNo > 4)
                 	strWarnDate.Format(" ����  %d ",ufData );
	            AddWarn( strPointNo, strWarnDate, strExplaintemp, strWarnCausetemp, strWarnTime);
			}
         	else if((Warn_state & 0x30) == 0x20)
			{
                strPointNo.Format("%d",nPointNo);
				if (nPointNo < 4) 
                    strWarnDate.Format(" ���� %d-- %4.2f %s",ufData,dfValue,usUnit);
				else if (nPointNo > 4)
            		strWarnDate.Format(" ���� %d ",ufData );
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

