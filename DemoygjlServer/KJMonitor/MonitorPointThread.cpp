// MonitorPointThread.cpp : implementation file
//

#include "stdafx.h"
#include "kjmonitor.h"
#include "MonitorPointThread.h"
#include "mainfrm.h"
#include "FMMonitorPoint.h"
#include "warningwin.h"
//#include "Sequence.h"
#include "Sequence\\dialogspumonitor.h"   
#include "Sequence\\shixuDlg.h"        
//#include "SetPortVsTrunkDlg.h"
#include "OutputBar.h"

//��������Ϊ��ӵĴ���
#include "NDK\\NDKMessage.h"
#include "MQCommandType.h"

///#include "WSocket.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMonitorPointThread
extern BOOL SeqFlag[SEQNUM];
//extern BOOL StartSequence;
BOOL StartSequence;
extern structRunTime m_structRunTime[MAX_POINT_NUMBER];
extern structSWITCH m_structSWITCH[MAX_POINT_NUMBER];
extern structANOLOG m_structANOLOG[MAX_POINT_NUMBER];
extern structValueState m_structValueState[MAX_POINT_NUMBER];

HANDLE hCommandList[201];
CDatabase	m_Database;
Cdialogspumonitor dlg_spumonitor;
CShixuDlg dlgshixu; 

DAYTIME  Dytim[100];  
BOOL exci[100], oldexci[100]; 
BOOL        g_ValueCorrect=FALSE;//�����ж�ȡֵ�Ƿ���ȷ     9.18

long  TotalDelay[SEQNUM], DelayStartTime[SEQNUM];      //��Ҫ
SEQSTACK	Sequence[SEQNUM];         //�޸�  ��Ҫ�޸�,  ����һ��ʱ���Ƿ�Ҫ���ñ��ʱ��
BYTE	  	WaitSeqLen;               //��Ҫ
STACK		WaitSeq[MAXWAITLEN];		// Sequence that are waiting for running
WORD		ExecSeq[SEQNUM];
NSEQ FAR 	SSeq[201];       //ʱ���,���нṹ             
UINT	    SeqReg[SEQNUM][64];
UINT		FixReg[48];          
BOOL 		SeqFlag[SEQNUM];

BOOL AllDate ;

IMPLEMENT_DYNCREATE(CMonitorPointThread, CWinThread)

CMonitorPointThread::CMonitorPointThread()
{

}

CMonitorPointThread::~CMonitorPointThread()
{

}

BOOL CMonitorPointThread::InitInstance()
{
	// TODO:  perform and per-thread initialization here
   m_RepeatFlag = FALSE;
   uWarnNo1=65;
   PointNow=0;
   PointNowCount=0;
   StartSequence=FALSE;
   m_usPointNoScanedNow=0;  
///	ConnectDB();

   m_WChangeDate = FALSE;
   m_ChangeStatus = FALSE;
   m_ChangeDate = FALSE;
   AllDate = FALSE;
	return TRUE;
}

int CMonitorPointThread::ExitInstance()
{
	// TODO:  perform any per-thread cleanup here
       m_SQLDirect.Close();
//	   m_SQLDirect1.Close();

       return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CMonitorPointThread, CWinThread)
	//{{AFX_MSG_MAP(CMonitorPointThread)
//	ON_BN_CLICKED(IDC_BUTTONCloseSound, OnBUTTONCloseSound)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMonitorPointThread message handlers

void CMonitorPointThread::ConnectDB()
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

void CMonitorPointThread::RefreshPoint(int iTrunk,unsigned char ucStatus)
{
///	DoRefreshPoint(iTrunk,ucStatus);
	if(StartSequence)
	{
          time_feg();
		  Schedule();
		  SeqSchedule();
	}
}

double CMonitorPointThread::ComputeValue(unsigned short ucRXch, double dfScopeMin, double dfScopeMax, UINT usPrecision)
{
	CString str;
	double  dfRXch = (double) ucRXch;
	double  dfScopeValue=dfScopeMax-dfScopeMin;
    str.Format("%f",(dfRXch/255)*dfScopeValue+dfScopeMin);   
	
	int index=str.Find('.');
	unsigned char ch=str.GetAt(index+usPrecision);
	unsigned char ch1=str.GetAt(index+usPrecision+1);
	if(ch1>'4')
		str.SetAt(index+usPrecision+1,ch+1);
	str=str.Left(index+usPrecision+1);
	return m_String2DataType.String2Double(str);
}

void CMonitorPointThread::SetKeepTime(unsigned short usPointNo)
{

	int udDay = m_structRunTime[usPointNo].udDay;
	int udHour = m_structRunTime[usPointNo].udHour;
	int udMin = m_structRunTime[usPointNo].udMin;
	int udSecond = m_structRunTime[usPointNo].udSecond;
	if (m_structValueState[usPointNo].ufData)
	{
		if (!m_structRunTime[usPointNo].LastSwitchStatus)
		{
			m_structRunTime[usPointNo].uStartTime = CTime::GetCurrentTime();
		}
		else{
			CTime thisTime = CTime::GetCurrentTime();
			CTimeSpan timeSpan = thisTime - m_structRunTime[usPointNo].uStartTime;
			long l_seconds = timeSpan.GetTotalSeconds();
			if (l_seconds >= 60){
				udSecond += l_seconds;
				udMin += udSecond / 60;
				udSecond = udSecond % 60;
				if (udMin >= 60){
					udMin -= 60;
					udHour++;
				}
				if (udHour >= 24){
					udHour -= 24;
					udDay++;
				}
				if (udDay >= 9999){
					udDay = 0;
				}
				//д���ݿ�
				CString usKeepTime;
				CString tmpstr;
				tmpstr.Format("%d", udDay);
				int addlen = 4 - tmpstr.GetLength(); 
				for(int k = 0; k < addlen; k++)
					tmpstr = "0" + tmpstr;
				usKeepTime = tmpstr;
				tmpstr.Format("%d", udHour);
				if (tmpstr.GetLength() == 1)
					tmpstr = "0" + tmpstr;
				usKeepTime = usKeepTime + tmpstr;
				tmpstr.Format("%d", udMin);
				if (tmpstr.GetLength() == 1)
					tmpstr = "0" + tmpstr;
				usKeepTime = usKeepTime + tmpstr;
				WriteKeepTimeStr(usPointNo,usKeepTime);
				m_structRunTime[usPointNo].uStartTime = CTime::GetCurrentTime();
			}
		}
		m_structRunTime[usPointNo].LastSwitchStatus = m_structValueState[usPointNo].ufData;
	}
	else{
		m_structRunTime[usPointNo].LastSwitchStatus = m_structValueState[usPointNo].ufData;
	}
	m_structRunTime[usPointNo].udDay = udDay;
	m_structRunTime[usPointNo].udHour = udHour;
	m_structRunTime[usPointNo].udMin = udMin;
	m_structRunTime[usPointNo].udSecond = udSecond;
}

void CMonitorPointThread::DoRefreshPoint(unsigned short iTrunk,unsigned char ucSetDisp)
{
	CMainFrame* pFWnd=(CMainFrame*)AfxGetMainWnd();
	CCommStatusFM *pCommStatusFM=pFWnd->m_pCommStatusFM;
	CFMMonitorPoint *pFMMonitorPoint=pFWnd->m_pFMMonitorPoint;

		unsigned short usMointorNo;
        unsigned char  Warn_state ,usPrecision ,ufData;
		double dfValue ,dfScopeMin ,dfScopeMax ,unWarnMin ,unWarnMax;

		if(iTrunk < 4 ){
            		dfScopeMin=m_structANOLOG[iTrunk].dfScopeMin;
            		dfScopeMax=m_structANOLOG[iTrunk].dfScopeMax;  
             	    unWarnMin=m_structANOLOG[iTrunk].unWarnMin;
            	    unWarnMax=m_structANOLOG[iTrunk].unWarnMax;
            		usPrecision=m_structANOLOG[iTrunk].usPrecision;
            		dfValue=ComputeValue(ucSetDisp,dfScopeMin,dfScopeMax,usPrecision);
					m_structANOLOG[iTrunk].ufMeasure = dfValue ;
                    StatusA( iTrunk,ucSetDisp);

				 if(AllDate )
				 {
    	    		Warn_state = m_structValueState[iTrunk].Warn_state;
             		ufData=m_structValueState[iTrunk].ucLowValue;
             		dfValue=m_structANOLOG[iTrunk].ufMeasure ;
//					CNDKMessage message(ALLDATA);
//					message.Add(1);
//					message.Add(iTrunk);
//	 				message.Add(Warn_state);
//					message.Add(ufData);
//					message.Add(dfValue);
//					theApp.SendMessage(message);
				 }
				 usMointorNo=pCommStatusFM->m_structMONITORPOINT[iTrunk].usMonitorNo;
               	 pFMMonitorPoint->SetDispMonitorNo(usMointorNo,1);//call disp function
		}
		else if(iTrunk == 4){
				 if(AllDate )
				 {
    	    		Warn_state = m_structValueState[iTrunk].Warn_state;
             		ufData=m_structValueState[iTrunk].ucLowValue;
             		dfValue=0 ;
//					CNDKMessage message(ALLDATA);
//					message.Add(3);
//					message.Add(iTrunk);
//                   	Warn_state= Warn_state | 0x80;
//	 				message.Add(Warn_state);
//					message.Add(ufData);
//					message.Add(dfValue);
//					theApp.SendMessage(message);
				 }
				 usMointorNo=pCommStatusFM->m_structMONITORPOINT[iTrunk].usMonitorNo;
               	 pFMMonitorPoint->SetDispMonitorNo(usMointorNo,1);//call disp function
		}
		else {
                        StatusD(iTrunk);
		     	    	 if(AllDate  )
						 {
                            ufData=m_structValueState[iTrunk].ucLowValue;
		                    Warn_state = m_structValueState[iTrunk].Warn_state;
//		         			CNDKMessage message(ALLDATA);
//		        			message.Add(2);
//		        			message.Add(iTrunk);
//	 	        			message.Add(Warn_state);
//			        		message.Add(ufData);
//			          		theApp.SendMessage(message);
						 }
	            		usMointorNo=pCommStatusFM->m_structMONITORPOINT[iTrunk].usMonitorNo;
	            		pFMMonitorPoint->SetDispMonitorNo(usMointorNo,1);//call disp function
		}
}

void CMonitorPointThread::CalA(unsigned short m_usPointNoScanedNow ,unsigned char ucRXch ,unsigned char ucRXAddr, unsigned char ucConvID )
{
	CMainFrame* pFWnd=(CMainFrame*)AfxGetMainWnd();
	CCommStatusFM *pCommStatusFM=pFWnd->m_pCommStatusFM;
	CFMMonitorPoint *pFMMonitorPoint=pFWnd->m_pFMMonitorPoint;
        UINT ProcessType ;
		unsigned char   iTrunk ,ucjAddr, uckConV ;    
		iTrunk=pCommStatusFM->m_structMONITORPOINT[m_usPointNoScanedNow].ucTrunkNo-1;
		ucjAddr=pCommStatusFM->m_structMONITORPOINT[m_usPointNoScanedNow].ucAddrNo;
		uckConV=pCommStatusFM->m_uckConV[iTrunk][ucjAddr];

	if ((ucConvID == 4) ||(ucConvID == 10))
	{
   	    if(pCommStatusFM->m_structMONITORPOINT[m_usPointNoScanedNow].unChannel == 1)
	      					 
		     m_structValueState[m_usPointNoScanedNow].ucLowValue=ucRXch;
					
	    else if(pCommStatusFM->m_structMONITORPOINT[m_usPointNoScanedNow].unChannel == 2)
		{
             unsigned short usPointNow=pCommStatusFM->m_structSCANADDR[iTrunk][ucjAddr][uckConV].structPointInfo[0].usPointNo;
                
	         if(usPointNow>0)
			 {
				 	    m_structValueState[m_usPointNoScanedNow].ucHighValue=ucRXch;
		     	 if(m_structValueState[usPointNow].ucLowValue>=0)
                      m_structValueState[m_usPointNoScanedNow].ucLowValue=m_structValueState[usPointNow].ucLowValue;

					  unsigned char ucValue = m_structValueState[m_usPointNoScanedNow].ucLowValue;
			    	  unsigned char ddvalue1 = m_structValueState[m_usPointNoScanedNow].ucHighValue;
			    	  unsigned short ddata = ddvalue1 * 256 +ucValue;

					  if(m_structANOLOG[m_usPointNoScanedNow].usProcessType1==0)
					  {
                          if(m_structValueState[m_usPointNoScanedNow].ufData!=ddata)
						  {
		                    	   m_structValueState[m_usPointNoScanedNow].ufData=ddata;
			                      WriteCollectData(m_usPointNoScanedNow,ddata);
						  }
					  }
					  else{
						   m_structANOLOG[m_usPointNoScanedNow].usProcessType1 ++;
						   ProcessType = m_structANOLOG[m_usPointNoScanedNow].usProcessType1 ;
						   if(ProcessType == 3)
							   m_structANOLOG[m_usPointNoScanedNow].ufData1 = ddata ;
						   if(ProcessType == 4)
							   m_structANOLOG[m_usPointNoScanedNow].ufData2 = ddata ;
						   if(ProcessType == 5){
							   m_structANOLOG[m_usPointNoScanedNow].usProcessType1 = 2 ;
                               AThreeCal(m_usPointNoScanedNow, ddata);
						   }
					  }
			 }
		}   
	}    //((ucConvID == 4) ||(ucConvID == 10))
	else if(ucConvID == 7)
	{
		 unsigned short ddata = ((ucRXAddr & 0xf0)>>4) * 256 +ucRXch;      
		 m_structValueState[m_usPointNoScanedNow].ucLowValue=ucRXch;
		 m_structValueState[m_usPointNoScanedNow].ucHighValue=(ucRXAddr & 0xf0)>>4;

					  if(m_structANOLOG[m_usPointNoScanedNow].usProcessType1==0)
					  {
                          if(m_structValueState[m_usPointNoScanedNow].ufData!=ddata)
						  {
		                    	   m_structValueState[m_usPointNoScanedNow].ufData=ddata;
			                      WriteCollectData(m_usPointNoScanedNow,ddata);
						  }
					  }
					  else{
						   m_structANOLOG[m_usPointNoScanedNow].usProcessType1 ++;
						   ProcessType = m_structANOLOG[m_usPointNoScanedNow].usProcessType1 ;
						   if(ProcessType == 3)
							   m_structANOLOG[m_usPointNoScanedNow].ufData1 = ddata ;
						   if(ProcessType == 4)
							   m_structANOLOG[m_usPointNoScanedNow].ufData2 = ddata ;
						   if(ProcessType == 5){
							   m_structANOLOG[m_usPointNoScanedNow].usProcessType1 = 2 ;
                               AThreeCal(m_usPointNoScanedNow, ddata);
						   }
					  }
	}
	else if(ucConvID == 9)
	{
		 unsigned char ddata = ucRXch & 0x3f;      
		 m_structValueState[m_usPointNoScanedNow].ucLowValue=ddata;

					  if(m_structANOLOG[m_usPointNoScanedNow].usProcessType1==0)
					  {
                          if(m_structValueState[m_usPointNoScanedNow].ufData!=ddata)
						  {
		                    	   m_structValueState[m_usPointNoScanedNow].ufData=ddata;
			                      WriteCollectData(m_usPointNoScanedNow,ddata);
						  }
					  }
					  else{
						   m_structANOLOG[m_usPointNoScanedNow].usProcessType1 ++;
						   ProcessType = m_structANOLOG[m_usPointNoScanedNow].usProcessType1 ;
						   if(ProcessType == 3)
							   m_structANOLOG[m_usPointNoScanedNow].ufData1 = ddata ;
						   if(ProcessType == 4)
							   m_structANOLOG[m_usPointNoScanedNow].ufData2 = ddata ;
						   if(ProcessType == 5){
							   m_structANOLOG[m_usPointNoScanedNow].usProcessType1 = 2 ;
                               AThreeCal(m_usPointNoScanedNow, ddata);
						   }
					  }
	}
	else
	{
		 unsigned short ddata = ucRXch;
		           m_structValueState[m_usPointNoScanedNow].ucLowValue=ucRXch;

					  if(m_structANOLOG[m_usPointNoScanedNow].usProcessType1==0)
					  {
                          if(m_structValueState[m_usPointNoScanedNow].ufData!=ddata)
						  {
		                    	   m_structValueState[m_usPointNoScanedNow].ufData=ddata;
			                      WriteCollectData(m_usPointNoScanedNow,ddata);
						  }
					  }
					  else{
						   m_structANOLOG[m_usPointNoScanedNow].usProcessType1 ++;
						   ProcessType = m_structANOLOG[m_usPointNoScanedNow].usProcessType1 ;
						   if(ProcessType == 3)
							   m_structANOLOG[m_usPointNoScanedNow].ufData1 = ddata ;
						   if(ProcessType == 4)
							   m_structANOLOG[m_usPointNoScanedNow].ufData2 = ddata ;
						   if(ProcessType == 5){
							   m_structANOLOG[m_usPointNoScanedNow].usProcessType1 = 2 ;
                               AThreeCal(m_usPointNoScanedNow, ddata);
						   }
					  }
	}
}

void CMonitorPointThread::StatusD(unsigned short usPointNo )
{
	CMainFrame* pFWnd=(CMainFrame*)AfxGetMainWnd();
	CCommStatusFM *pCommStatusFM=pFWnd->m_pCommStatusFM;

     unsigned char CommStatus ;
	 unsigned short usAC =m_structSWITCH[usPointNo].usAC;
    unsigned char ucRecvChar=m_structValueState[usPointNo].ucLowValue;
	unsigned char unWarnDelay=m_structSWITCH[usPointNo].unWarnDelay;
    unsigned char WarnTime=m_structValueState[usPointNo].unDelay;
	BOOL Ac_state=m_structValueState[usPointNo].Ac_state;
	BOOL alarm_state=m_structValueState[usPointNo].alarm_state;
	CTime tDelay=CTime::GetCurrentTime();

    switch(usAC)   
	{
		 case 0:                    
		      if(ucRecvChar == 0x00)
			  {
     			     	m_structValueState[usPointNo].Ac_state=0;
                        m_structValueState[usPointNo].alarm_state=1;
					    m_structValueState[usPointNo].WarnColor = RED_STATUS;
                    
                    if(!unWarnDelay)
					{
    							CommStatus=0x2b;
	                 		    WriteToWarnCauseRecord(CommStatus ,usPointNo);
					}
	    			else 
					{
						if(m_structValueState[usPointNo].Warn_state == 0x6b)
						{
                            if(((WarnTime+unWarnDelay)>60) && (tDelay.GetSecond()>=(WarnTime+unWarnDelay-60)))
							{
    							CommStatus=0x2b;
			                    WriteToWarnCauseRecord(CommStatus ,usPointNo);
							}
							else if(((WarnTime+unWarnDelay)<=60) && (tDelay.GetSecond()>=(WarnTime+unWarnDelay)))
							{
    							CommStatus=0x2b;
			                    WriteToWarnCauseRecord(CommStatus ,usPointNo);
							}
							else 
			     					m_structValueState[usPointNo].Warn_state=0x6b;

						}
	    		    	else if(m_structValueState[usPointNo].Warn_state == 0x2b)
						{
    							CommStatus=0x2b;
			                    WriteToWarnCauseRecord(CommStatus ,usPointNo);
						}
						else 
						{
			     					m_structValueState[usPointNo].Warn_state=0x6b;
                                    m_structValueState[usPointNo].unDelay=tDelay.GetSecond();
						}
					}							
                    break;
			  }
		      if (ucRecvChar == 0x01)                   
			  {
						m_structValueState[usPointNo].WarnColor = GREEN_STATUS;
						CommStatus=0x83;

					if( Ac_state==1)
					{
		     	            WriteToWarnCauseRecord(CommStatus ,usPointNo);
     			     		m_structValueState[usPointNo].Ac_state=0;
					}
				   	else if( alarm_state==1)
					{
		         	        WriteToWarnCauseRecord(CommStatus, usPointNo);
     			    		m_structValueState[usPointNo].alarm_state=0;
					}
				   else
                         m_structValueState[usPointNo].Warn_state=0x83;
			        break;
			  }
		      break;
	     case 1:
		      if(ucRecvChar == 0x01)
			  {
     			     	m_structValueState[usPointNo].Ac_state=0;
     					m_structValueState[usPointNo].WarnColor = RED_STATUS;
					    m_structValueState[usPointNo].alarm_state=1;

                    if(!unWarnDelay)
					{
    							CommStatus=0xab;
	                		    WriteToWarnCauseRecord(CommStatus ,usPointNo);
					}
					else 
					{
						if(m_structValueState[usPointNo].Warn_state == 0xeb)
						{
                            if(((WarnTime+unWarnDelay)>60) && (tDelay.GetSecond()>=(WarnTime+unWarnDelay-60)))
							{
    							CommStatus=0xab;
	                		    WriteToWarnCauseRecord(CommStatus ,usPointNo);
							}
							else if(((WarnTime+unWarnDelay)<=60) && (tDelay.GetSecond()>=(WarnTime+unWarnDelay)))
							{
    							CommStatus=0xab;
	                		    WriteToWarnCauseRecord(CommStatus ,usPointNo);
							}
						}
	    		    	else if(m_structValueState[usPointNo].Warn_state == 0xab)
						{
    							CommStatus=0xab;
			                    WriteToWarnCauseRecord(CommStatus ,usPointNo);
						}
						else 
						{
			     					m_structValueState[usPointNo].Warn_state=0xeb;
                                    m_structValueState[usPointNo].unDelay=tDelay.GetSecond();
						}
					}									
                    break;
			  }
			  if (ucRecvChar == 0x00)                      
			  {
						 m_structValueState[usPointNo].WarnColor = GREEN_STATUS;
						 CommStatus=0x03;

					if( Ac_state==1)
					{
     		       			m_structValueState[usPointNo].Ac_state=0;
		     	            WriteToWarnCauseRecord(CommStatus ,usPointNo);
					}
				    else if( alarm_state==1)
					{
     			      		m_structValueState[usPointNo].alarm_state=0;
		     	            WriteToWarnCauseRecord(CommStatus ,usPointNo);
					}
				   else
                         m_structValueState[usPointNo].Warn_state=0x03;

			        break;
			  }
			  break;
		 case 2:
			  if(ucRecvChar == 0x00)
			  {
					    m_structValueState[usPointNo].WarnColor = GREEN_STATUS;

				  if( Ac_state==1)
				  {
			     			CommStatus=0x0b;
     			    		m_structValueState[usPointNo].Ac_state=0;
		     	            WriteToWarnCauseRecord(CommStatus ,usPointNo);
				  }
				   else
                         m_structValueState[usPointNo].Warn_state=0x0b;
                  break;
			  }
			  if  (ucRecvChar == 0x01)                   
			  {
						 m_structValueState[usPointNo].WarnColor = GREEN_STATUS;
				   if( Ac_state==1)
				   {
				    	     CommStatus =0x83;
     			     		m_structValueState[usPointNo].Ac_state=0;
		     	            WriteToWarnCauseRecord(CommStatus ,usPointNo);
				   }
				   else
                         m_structValueState[usPointNo].Warn_state=0x83;
				   break;
			  }                      
			  break;
		 case 3:
			  if(ucRecvChar == 0x00)
			  {
					    m_structValueState[usPointNo].WarnColor = GREEN_STATUS;
						CommStatus =0x03;

					if( Ac_state==1)
					{
     			     		m_structValueState[usPointNo].Ac_state=0;
		     	            WriteToWarnCauseRecord(CommStatus ,usPointNo);
					}
				   else
                         m_structValueState[usPointNo].Warn_state=0x03;
                    break;
			  }
			  if (ucRecvChar == 0x01)                    
			  {
						m_structValueState[usPointNo].WarnColor = GREEN_STATUS;

					if( Ac_state==1)
					{
						CommStatus = 0x8b;
     			    		m_structValueState[usPointNo].Ac_state=0;
		     	            WriteToWarnCauseRecord(CommStatus , usPointNo);
					}
				   else
                         m_structValueState[usPointNo].Warn_state=0x8b;
				    break;
			  }                      
			  break;
        default:
		      break;
	}

}

void CMonitorPointThread::StatusA(unsigned short m_usPoint,unsigned char ucRXch )
{
        double dfValue = m_structANOLOG[m_usPoint].ufMeasure;
	    double unWarnMin=m_structANOLOG[m_usPoint].unWarnMin;
	    double unWarnMax=m_structANOLOG[m_usPoint].unWarnMax;
		unsigned char unWarnDelay=m_structANOLOG[m_usPoint].unWarnDelay;
		unsigned char WarnTime=m_structValueState[m_usPoint].unDelay;
		UINT usWarnMode=m_structANOLOG[m_usPoint].usWarnMode;
		BOOL Ac_state=m_structValueState[m_usPoint].Ac_state;
		BOOL alarm_state=m_structValueState[m_usPoint].alarm_state;

		unsigned char CommStatus ;
		CTime tDelay=CTime::GetCurrentTime();
	switch(usWarnMode)
	{
		case 0:
			{
         	m_structValueState[m_usPoint].WarnColor = GREEN_STATUS;
			CommStatus=0x01;

			if( Ac_state==1)
			{
         		m_structValueState[m_usPoint].Ac_state=0;
   		 	    WriteToWarnCauseRecord(CommStatus ,m_usPoint); 
			}
			}
			break;
		case 1:
			if((unWarnMin==0)&&(unWarnMax==0))
			{
         		m_structValueState[m_usPoint].WarnColor = GREEN_STATUS;
				CommStatus = 0x01;

				if( Ac_state==1)
				{
     			      m_structValueState[m_usPoint].Ac_state=0;
				      WriteToWarnCauseRecord(CommStatus ,m_usPoint); 
				}
				break;
			}
			else if((dfValue>unWarnMin)&&(dfValue<unWarnMax))
			{
         		m_structValueState[m_usPoint].WarnColor = GREEN_STATUS;
				CommStatus=0x01;

				if( Ac_state==1)
				{
     			      m_structValueState[m_usPoint].Ac_state=0;
				      WriteToWarnCauseRecord(CommStatus ,m_usPoint); 
				}
				if( alarm_state==1)
				{
     			      m_structValueState[m_usPoint].alarm_state=0;
		     	      WriteToWarnCauseRecord(CommStatus ,m_usPoint);
				}
 				break;
			}
			else if(dfValue>=unWarnMax)
			{
     			      m_structValueState[m_usPoint].Ac_state=0;
        		m_structValueState[m_usPoint].WarnColor = RED_STATUS;
				m_structValueState[m_usPoint].alarm_state=1;
					    
                if(!unWarnDelay)
				{
    				CommStatus=0x29;
       	     		WriteToWarnCauseRecord(CommStatus ,m_usPoint); 
				}
				else 
				{
					if(m_structValueState[m_usPoint].Warn_state == 0x69)
					{
                        if(((WarnTime+unWarnDelay)>60) && (tDelay.GetSecond()>=(WarnTime+unWarnDelay-60)))
						{
            				CommStatus=0x29;
       	            		WriteToWarnCauseRecord(CommStatus ,m_usPoint); 
						}
						else if(((WarnTime+unWarnDelay)<=60) && (tDelay.GetSecond()>=(WarnTime+unWarnDelay)))
						{
            				CommStatus=0x29;
       	            		WriteToWarnCauseRecord(CommStatus ,m_usPoint); 
						}
					}
	    		    else if(m_structValueState[m_usPoint].Warn_state == 0x29)
					{
    							CommStatus=0x29;
			                    WriteToWarnCauseRecord(CommStatus ,m_usPoint);
					}
					else 
					{
			     		m_structValueState[m_usPoint].Warn_state=0x69;
                        m_structValueState[m_usPoint].unDelay=tDelay.GetSecond();
					}
				}							
				break;
			}
            else if(dfValue <= unWarnMin) 
			{
     			      m_structValueState[m_usPoint].Ac_state=0;
        		m_structValueState[m_usPoint].WarnColor = ORANGE_STATUS;
		        m_structValueState[m_usPoint].alarm_state=1;

                if(!unWarnDelay)
				{
    				CommStatus=0x25;
       				WriteToWarnCauseRecord(CommStatus ,m_usPoint); 
				}
				else 
				{
					if(m_structValueState[m_usPoint].Warn_state == 0x65)
					{
                        if(((WarnTime+unWarnDelay)>60) && (tDelay.GetSecond()>=(WarnTime+unWarnDelay-60)))
						{
    	        			CommStatus=0x25;
       	        			WriteToWarnCauseRecord(CommStatus ,m_usPoint); 
						}
		    			else if(((WarnTime+unWarnDelay)<=60) && (tDelay.GetSecond()>=(WarnTime+unWarnDelay)))
						{
    	        			CommStatus=0x25;
       	        			WriteToWarnCauseRecord(CommStatus ,m_usPoint); 
						}
					}
	    		    else if(m_structValueState[m_usPoint].Warn_state == 0x25)
					{
    							CommStatus=0x25;
			                    WriteToWarnCauseRecord(CommStatus ,m_usPoint);
					}
					else 
					{
						m_structValueState[m_usPoint].Warn_state=0x65;
                        m_structValueState[m_usPoint].unDelay=tDelay.GetSecond();
					}
				}							
	    		break;
			}
			break;
		case 2:
			if((unWarnMin==0)&&(unWarnMax==0))
			{
       			m_structValueState[m_usPoint].WarnColor = GREEN_STATUS;
			    CommStatus =0x01;

				if( Ac_state==1)
				{
     	        	m_structValueState[m_usPoint].Ac_state=0;
		        	WriteToWarnCauseRecord(CommStatus ,m_usPoint); 
				}
				break;
			}
			else if(dfValue < unWarnMin)
			{
    		    m_structValueState[m_usPoint].WarnColor = GREEN_STATUS;
			    CommStatus =0x01;

				if( Ac_state==1)
				{
             		m_structValueState[m_usPoint].Ac_state=0;
	         		WriteToWarnCauseRecord(CommStatus ,m_usPoint); 
				}
		    	if( alarm_state==1)
				{
     	         	m_structValueState[m_usPoint].alarm_state=0;
	                WriteToWarnCauseRecord(CommStatus ,m_usPoint);
				}
				break;
			}
			else if((dfValue>=unWarnMin)&&(dfValue<unWarnMax))
			{
     			      m_structValueState[m_usPoint].Ac_state=0;
    			m_structValueState[m_usPoint].WarnColor = ORANGE_STATUS;
		        m_structValueState[m_usPoint].alarm_state=1;

                if(!unWarnDelay)
				{
    				CommStatus=0x25;
     				WriteToWarnCauseRecord(CommStatus ,m_usPoint); 
				}
				else 
				{
					if(m_structValueState[m_usPoint].Warn_state == 0x65)
					{
                        if(((WarnTime+unWarnDelay)>60) && (tDelay.GetSecond()>=(WarnTime+unWarnDelay-60)))
						{
    	          			CommStatus=0x25;
     	        			WriteToWarnCauseRecord(CommStatus ,m_usPoint); 
						}
	    				else if(((WarnTime+unWarnDelay)<=60) && (tDelay.GetSecond()>=(WarnTime+unWarnDelay)))
						{
    	          			CommStatus=0x25;
     	        			WriteToWarnCauseRecord(CommStatus ,m_usPoint); 
						}
					}
	    		    else if(m_structValueState[m_usPoint].Warn_state == 0x25)
					{
    							CommStatus=0x25;
			                    WriteToWarnCauseRecord(CommStatus ,m_usPoint);
					}
					else 
					{
			     		m_structValueState[m_usPoint].Warn_state=0x65;
                        m_structValueState[m_usPoint].unDelay=tDelay.GetSecond();
					}
				}							
		 		break;
			}
			else if(dfValue>=unWarnMax)
			{
     			      m_structValueState[m_usPoint].Ac_state=0;
				m_structValueState[m_usPoint].WarnColor = RED_STATUS;
            	m_structValueState[m_usPoint].alarm_state=1;

                if(!unWarnDelay)
				{
    				CommStatus =0x29;
       	    		WriteToWarnCauseRecord(CommStatus ,m_usPoint); 
				}
				else 
				{
					if(m_structValueState[m_usPoint].Warn_state == 0x69)
					{
                         if(((WarnTime+unWarnDelay)>60) && (tDelay.GetSecond()>=(WarnTime+unWarnDelay-60)))
						 {
    	        			CommStatus =0x29;
       	             		WriteToWarnCauseRecord(CommStatus ,m_usPoint); 
						 }
					     else if(((WarnTime+unWarnDelay)<=60) && (tDelay.GetSecond()>=(WarnTime+unWarnDelay)))
						 {
    	        			CommStatus =0x29;
       	             		WriteToWarnCauseRecord(CommStatus ,m_usPoint); 
						 }
					}
	    		    else if(m_structValueState[m_usPoint].Warn_state == 0x29)
					{
    							CommStatus=0x29;
			                    WriteToWarnCauseRecord(CommStatus ,m_usPoint);
					}
					else 
					{
			     		m_structValueState[m_usPoint].Warn_state=0x69;
                        m_structValueState[m_usPoint].unDelay=tDelay.GetSecond();
					}
				}							
			 	break;
			}
			break;
        case 3:
            if((unWarnMin==0)&&(unWarnMax==0))
			{
         			    	m_structValueState[m_usPoint].WarnColor = GREEN_STATUS;
						    CommStatus =0x01;

				if( Ac_state==1)
				{
     				        	m_structValueState[m_usPoint].Ac_state=0;
					        	WriteToWarnCauseRecord(CommStatus ,m_usPoint); 
				}
							break;
			}
		    else if((dfValue > unWarnMax))
			{
         				    m_structValueState[m_usPoint].WarnColor = GREEN_STATUS;
						    CommStatus =0x01;

				 if( Ac_state==1)
				 {
     			        		m_structValueState[m_usPoint].Ac_state=0;
				         		WriteToWarnCauseRecord(CommStatus ,m_usPoint); 
				 }
				 if( alarm_state==1)
				 {
     				        	m_structValueState[m_usPoint].alarm_state=0;
		     	                WriteToWarnCauseRecord(CommStatus ,m_usPoint);
				 }
 							break;
			}
		    else if((dfValue>=unWarnMin)&&(dfValue<=unWarnMax))
			{
     			      m_structValueState[m_usPoint].Ac_state=0;
        					m_structValueState[m_usPoint].WarnColor = RED_STATUS;
					        m_structValueState[m_usPoint].alarm_state=1;

                 if(!unWarnDelay)
				 {
    							CommStatus=0x29;
       	    					WriteToWarnCauseRecord(CommStatus ,m_usPoint); 
				 }
				 else 
				 {
					 if(m_structValueState[m_usPoint].Warn_state == 0x69)
					 {
                          if(((WarnTime+unWarnDelay)>60) && (tDelay.GetSecond()>=(WarnTime+unWarnDelay-60)))
						  {
    							CommStatus=0x29;
       	    					WriteToWarnCauseRecord(CommStatus ,m_usPoint); 
						  }
					      else if(((WarnTime+unWarnDelay)<=60) && (tDelay.GetSecond()>=(WarnTime+unWarnDelay)))
						  {
    							CommStatus=0x29;
       	    					WriteToWarnCauseRecord(CommStatus ,m_usPoint); 
						  }
					 }
	    		    else if(m_structValueState[m_usPoint].Warn_state == 0x29)
					{
    							CommStatus=0x29;
			                    WriteToWarnCauseRecord(CommStatus ,m_usPoint);
					}
					 else 
					 {
	  		     					m_structValueState[m_usPoint].Warn_state=0x69;
                                    m_structValueState[m_usPoint].unDelay=tDelay.GetSecond();
					 }
				 }							
	 			 break;
			}
			else if(dfValue<unWarnMin)
			{
     			      m_structValueState[m_usPoint].Ac_state=0;
        					m_structValueState[m_usPoint].WarnColor = ORANGE_STATUS;
					        m_structValueState[m_usPoint].alarm_state=1;

                 if(!unWarnDelay)
				 {
    							CommStatus = 0x25;
       	    					WriteToWarnCauseRecord(CommStatus ,m_usPoint); 
				 }
			     else 
				 {
					   if(m_structValueState[m_usPoint].Warn_state == 0x65)
					   {
                            if(((WarnTime+unWarnDelay)>60) && (tDelay.GetSecond()>=(WarnTime+unWarnDelay-60)))
							{
    							CommStatus = 0x25;
       	    					WriteToWarnCauseRecord(CommStatus ,m_usPoint); 
							}
						    else if(((WarnTime+unWarnDelay)<=60) && (tDelay.GetSecond()>=(WarnTime+unWarnDelay)))
							{
    							CommStatus = 0x25;
       	    					WriteToWarnCauseRecord(CommStatus ,m_usPoint); 
							}
					   }
	        		    else if(m_structValueState[m_usPoint].Warn_state == 0x25)
						{
    							CommStatus=0x25;
			                    WriteToWarnCauseRecord(CommStatus ,m_usPoint);
						}
					   else 
					   {
			     					m_structValueState[m_usPoint].Warn_state=0x65;
                                    m_structValueState[m_usPoint].unDelay=tDelay.GetSecond();
					   }
				 }							
							break;
			}
						break;
         default:
			break;
    }


}


void CMonitorPointThread::AThreeCal(unsigned short m_usPointNoScanedNow, unsigned short ddata)
{
	if(m_structANOLOG[m_usPointNoScanedNow].ufData2 > m_structANOLOG[m_usPointNoScanedNow].ufData1)
	{
         if(ddata > m_structANOLOG[m_usPointNoScanedNow].ufData2)
		 {
			if(m_structANOLOG[m_usPointNoScanedNow].ufData2!=m_structValueState[m_usPointNoScanedNow].ufData)
			{
	    	    m_structValueState[m_usPointNoScanedNow].ufData=m_structANOLOG[m_usPointNoScanedNow].ufData2;
	    		WriteCollectData(m_usPointNoScanedNow,m_structANOLOG[m_usPointNoScanedNow].ufData2);
			}
		 }
		 else
		 {
			if(ddata < m_structANOLOG[m_usPointNoScanedNow].ufData1)
			{
				 if(m_structANOLOG[m_usPointNoScanedNow].ufData1!=m_structValueState[m_usPointNoScanedNow].ufData)
				 {
     		    	 m_structValueState[m_usPointNoScanedNow].ufData=m_structANOLOG[m_usPointNoScanedNow].ufData1;
	    		     WriteCollectData(m_usPointNoScanedNow,m_structANOLOG[m_usPointNoScanedNow].ufData1);
				 }
			}
			else
			{
				 if(ddata!=m_structValueState[m_usPointNoScanedNow].ufData)
				 {
     		    	  m_structValueState[m_usPointNoScanedNow].ufData=ddata;
	    		      WriteCollectData(m_usPointNoScanedNow,ddata);
				 }
			}
		 }
	}
	else
	{
        if(ddata > m_structANOLOG[m_usPointNoScanedNow].ufData1)
		{
			if(m_structANOLOG[m_usPointNoScanedNow].ufData1!=m_structValueState[m_usPointNoScanedNow].ufData)
			{
	    	    m_structValueState[m_usPointNoScanedNow].ufData=m_structANOLOG[m_usPointNoScanedNow].ufData1;
	    		WriteCollectData(m_usPointNoScanedNow,m_structANOLOG[m_usPointNoScanedNow].ufData1);
			}
		}
        else
		{
			if(ddata < m_structANOLOG[m_usPointNoScanedNow].ufData2)
			{
				if(m_structANOLOG[m_usPointNoScanedNow].ufData2!=m_structValueState[m_usPointNoScanedNow].ufData)
				{
     		    	m_structValueState[m_usPointNoScanedNow].ufData=m_structANOLOG[m_usPointNoScanedNow].ufData2;
	    		    WriteCollectData(m_usPointNoScanedNow,m_structANOLOG[m_usPointNoScanedNow].ufData2);
				}
			}
			else
			{
				if(ddata!=m_structValueState[m_usPointNoScanedNow].ufData)
				{
     		    	m_structValueState[m_usPointNoScanedNow].ufData=ddata;
	    		    WriteCollectData(m_usPointNoScanedNow,ddata);
				}
			}
		}
	}
}

//���뱸������	theApp.OnWriteCollectData(pointno,data);
void CMonitorPointThread::WriteCollectData(unsigned short pointno, unsigned short data)
{
		m_WChangeDate = TRUE;
		m_ChangeDate = TRUE;
	SYSTEMTIME time;
	GetLocalTime(&time);
	CString strSql;

	    CString begintime;
		CString strTmp,strTmpS;
		begintime.Format("%d-%d-%d %d:%d:%d:%d",time.wYear,time.wMonth,time.wDay,time.wHour,time.wMinute,time.wSecond,time.wMilliseconds);		
		strTmp.Format("VALUES (%d,%d,'%s')",pointno,data,begintime);

/*		strSql = _T("INSERT INTO uCollectData (unPointNo,unCollectData,strBeginTime)");
		strSql += strTmp;
		try
		{
			if(m_SQLDirect.ExecuteSQL(strSql)!=SQL_SUCCESS)
			{
				AfxMessageBox("���ݿ��uCollectData����ʧ��!");
			}
			else		//��ӵĴ���
			{
				theApp.OnSendSQL(strSql);
			}
		}
		catch(CDBException *e)
		{
			e->ReportError();
			return ;
		}*/
}

void CMonitorPointThread::WriteKeepTimeStr(unsigned short usPointNo, CString usKeepTime)
{
/*	try
	{
		//get monitor info
		CString strSQL;
		strSQL.Format("update uSwitchPointProperty set unSetKTime='%s' where unPointNo=%d",usKeepTime,usPointNo);
		if(m_SQLDirect.ExecuteSQL(strSQL)!=SQL_SUCCESS)
		{
			AfxMessageBox("���ݿ��uSwitchPointProperty����ʧ��");
			//int nRet=m_SQLDirect.Fetch();//
		}
		else	//��ӵĴ���
		{
			theApp.OnSendSQL(strSQL);
		}
	}
	catch(CException e){ e.Delete();}*/
}

void CMonitorPointThread::WriteToWarnCauseRecord(unsigned char  CommStatus, unsigned short usPointNoNow)
{
	CMainFrame* pFWnd=(CMainFrame*)AfxGetMainWnd();
	CCommStatusFM *pCommStatusFM=pFWnd->m_pCommStatusFM;

        unsigned char     SecondStatus  ;    
        SecondStatus= m_structValueState[usPointNoNow].Warn_state;
	
	UINT uWarnNo;	
	CTime t=CTime::GetCurrentTime();

	if(CommStatus !=SecondStatus )
	{
		try
		{
           if(((CommStatus & 0x20) == 0x20 ) || ((CommStatus & 0x10) == 0x10 ))
		   {
//        		m_ChangeStatus = TRUE;
			    CString  str,strSQL;
///			    strSQL=_T("INSERT INTO uWarnCauseRecord (unPointNo,strExplain,strWarnCause,strWarnTime,strNormalTime,bConfirm)");
				 
				CString strTemp,strExplaintemp,strWarnCausetemp,strWarnTime;
								 
				strExplaintemp =pCommStatusFM->m_structMONITORPOINT[usPointNoNow].strExplain;      
								 
                BOOL bValueType=pCommStatusFM->m_structMONITORPOINT[usPointNoNow].bValueType;
				if(bValueType)
				    uWarnNo=m_structANOLOG[usPointNoNow].unWarnCause;
				else
	    			uWarnNo=m_structSWITCH[usPointNoNow].unWarnCause;	
                
				strWarnCausetemp=pCommStatusFM->m_structMONITORPOINT[usPointNoNow].strWarnCause;   
								 
				strWarnTime.Format("%d-%d-%d %d:%d:%d",t.GetYear(),t.GetMonth(),t.GetDay(),t.GetHour(),t.GetMinute(),t.GetSecond());
		        
				if((CommStatus & 0x10) == 0x10 )
				{
	    			strTemp.Format("VALUES (%d,'%s','%s','%s','',1)",usPointNoNow,strExplaintemp,strWarnCausetemp,strWarnTime);
				}				
				else
			    	strTemp.Format("VALUES (%d,'%s','%s','%s','',0)",usPointNoNow,strExplaintemp,strWarnCausetemp,strWarnTime);
                
				strSQL +=strTemp;
/*				if(m_SQLDirect.ExecuteSQL(strSQL) != SQL_SUCCESS)
					AfxMessageBox("���ݿ��uWarnCauseRecord����ʧ��");
				else    //��ӵĴ���
				{
					theApp.OnSendSQL(strSQL);
				}*/
				strTemp.Format("  %d",usPointNoNow);
				str=strExplaintemp;    
				strTemp+="�ŵ�" +str;
				str=strWarnCausetemp;      
				strTemp+="!" +str;
				str=strWarnTime;           
			    strTemp+="!"+str;

				if((CommStatus & 0x0c) == 0x04 )
     				pFWnd->m_wndOutputBar.AddDispWarnItem(1,strTemp);
				else if((CommStatus & 0x0c) == 0x08)
     				pFWnd->m_wndOutputBar.AddDispWarnItem(2,strTemp);
				else 
     				pFWnd->m_wndOutputBar.AddDispWarnItem(3,strTemp);

///				pFWnd->m_pWarningWin->AddDispWarnStr(strTemp,1);			
                m_structValueState[usPointNoNow].Warn_state = CommStatus;
				//::AfxBeginThread(PlaySoundFunc, (LPVOID)usPointNoNow);
                if(!m_RepeatFlag)
				{
						DoPlayWarnSound(uWarnNo);
                        uWarnNo1=uWarnNo;
                        PointNow=usPointNoNow;
				}
		   }
           else
		   {
///        		m_ChangeStatus = TRUE;
				CString strTemp,strExplaintemp,strWarnCausetemp;
				strExplaintemp =pCommStatusFM->m_structMONITORPOINT[usPointNoNow].strExplain; 
                strWarnCausetemp=pCommStatusFM->m_structMONITORPOINT[usPointNoNow].strWarnCause;   
				CString strNormalTime,str,strSQL;
				strNormalTime.Format("%d-%d-%d %d:%d:%d",t.GetYear(),t.GetMonth(),t.GetDay(),t.GetHour(),t.GetMinute(),t.GetSecond());
								
				strTemp.Format("  %d",usPointNoNow);
				str=strExplaintemp;         
				strTemp+="�ŵ�" +str;
				str=strWarnCausetemp;         
				strTemp+="|" +str;
//				str=m_SQLDirect.GetCol(4);
//				strTemp+=" "+str;
				strTemp+="|"+strNormalTime;
				pFWnd->m_wndOutputBar.AddDispWarnItem(0,strTemp);
///				pFWnd->m_pWarningWin->AddDispWarnStr(strTemp, 0);

/*				strSQL.Format("UPDATE uWarnCauseRecord SET strNormalTime='%s' WHERE (unPointNo = %d) ",strNormalTime,usPointNoNow); 
				if(m_SQLDirect.ExecuteSQL(strSQL) != SQL_SUCCESS)
					AfxMessageBox("���ݿ��uWarnCauseRecord����ʧ��");
				else	//��ӵĴ���
				{
					theApp.OnSendSQL(strSQL);
				}*/
                m_structValueState[usPointNoNow].Warn_state = CommStatus;
			    if(PointNow==usPointNoNow)
				{
                	m_RepeatFlag=FALSE;
				}
		   }

		}
    	catch(CDBException *e)
		{
        	e->ReportError();
        	return ;
		}
	}
	else if((m_RepeatFlag)&&(PointNow==usPointNoNow))
	{
		PointNowCount++;
		if(PointNowCount==9)
		{
	    	DoPlayWarnSound(uWarnNo1);
            PointNowCount=0;
		}
	}

}

void CMonitorPointThread::DoPlayWarnSound(UINT uWarnNo)
{
	CString strFileName;
	strFileName.Format("%swarnsound%d.wav", GetAppPath() + "sound\\", uWarnNo+1);
    sndPlaySound(strFileName,SND_ASYNC);	
    m_RepeatFlag=TRUE;
}


CString CMonitorPointThread::GetAppPath()
{
	CString sModFileName;
	CString str1;
		GetModuleFileName(NULL, sModFileName.GetBuffer(MAX_PATH), MAX_PATH);
	sModFileName.ReleaseBuffer();
	str1=sModFileName;
	str1.MakeReverse();
	return(sModFileName.Left(sModFileName.GetLength() - str1.Find('\\')));

}

void CMonitorPointThread::CloseWarning()
{
	m_RepeatFlag=FALSE;
}


BOOL CMonitorPointThread::time_feg()
{
  int i;

   CTime tEventTime = CTime::GetCurrentTime();

	for (i=0; i<100; i++)   //100  11/1	
	 {//Ϊʲôֻ�Ǽ��ǰ�볡Dytim16��
       // Should it be active ?
       if (Dytim[i].Active != 'y')
           continue;
       if (Dytim[i].Daily != 'y')
	   if (Dytim[i].Month != tEventTime.GetMonth())
		   continue;
	   if (Dytim[i].Day !=tEventTime.GetDay() )
		   continue;
	   if (Dytim[i].Hour != tEventTime.GetHour())
		   continue;
	   if (tEventTime.GetMinute() != Dytim[i].Minute)
		   continue;
	   if (tEventTime.GetSecond()!=0)
           continue;

	   if (SeqFlag[i]) 
		   continue; 

       // Insert in executive quene
       InsertSeq(Dytim[i].Seqnum);//���붨ʱʱ��   // 
	}
    return TRUE;


}

void CMonitorPointThread::Schedule()
{

	int 		i;
   extern TRIG FAR TrigSeq[100]; 

   for (i=0; i<100; i++)    //TrigSeq[i]��ȷ�����˲���100��   100  11/1
      if ((TrigSeq[i].Point!=0)&&(TrigSeq[i].Point<MAX_POINT_NUMBER-1))
	  {
//	  p=FindPAddr(TrigSeq[i].Point);
		unsigned short   ucjAdd, uckCon;    
        ucjAdd=TrigSeq[TrigSeq[i].Point].PntStat;
        uckCon=m_structValueState[TrigSeq[i].Point].Warn_state;

		if(ucjAdd !=uckCon )
		{
						BOOL Ac_state=m_structValueState[TrigSeq[i].Point].Ac_state;
						BOOL alarm_state=m_structValueState[TrigSeq[i].Point].alarm_state;
		 switch (TrigSeq[i].Condition)
		 {
	      case 1:   //״̬��������
	     	  if (( alarm_state==0)&&( Ac_state==0))
			  {
	     		if ((!oldexci[i]) &&((m_structValueState[TrigSeq[i].Point].Warn_state & 0x31)==0x01)) 
				{
			    	exci[i] = oldexci[i] = TRUE;
				}
	     		else exci[i] = FALSE;  //�Ѿ�ִ����ʱ��Ķ��β���ִ��
			  }
              else 
			  {
				  exci[i] =oldexci[i] = FALSE;   //exci[i] = 
                  TrigSeq[TrigSeq[i].Point].PntStat = m_structValueState[TrigSeq[i].Point].Warn_state;
			  }
	    	  break;
	      case 2:  //����״̬����
    		  if (( alarm_state==1)&&( Ac_state==0))
			  {
	     		if ((!oldexci[i]) &&((m_structValueState[TrigSeq[i].Point].Warn_state & 0x31)==0x21)) 
				{
		    		exci[i] = oldexci[i] = TRUE;
				}
	  	     	else exci[i] = FALSE;
			  }
              else 
			  {
				  exci[i] =oldexci[i] = FALSE;    // 
                  TrigSeq[TrigSeq[i].Point].PntStat = m_structValueState[TrigSeq[i].Point].Warn_state;
			  }
	    	  break;
	      case 3:    //��������mod1
	     	  if ((m_structValueState[TrigSeq[i].Point].ufData==0 )&&( Ac_state==0)) 
			  {
	     		if ((!oldexci[i]) &&((m_structValueState[TrigSeq[i].Point].Warn_state & 0x93)==0x03))
				{	
					exci[i] = oldexci[i] = TRUE;
				}
		    	else exci[i] = FALSE;
			  }
              else  
			  {
				  exci[i] =oldexci[i] = FALSE;   //exci[i] =
                  TrigSeq[TrigSeq[i].Point].PntStat = m_structValueState[TrigSeq[i].Point].Warn_state;
			  }
     		  break;
	      case 4:   //�����෴mod2
		      if ((m_structValueState[TrigSeq[i].Point].ufData==1)&&( Ac_state==0)) 
			  {
				  if ((!oldexci[i]) &&((m_structValueState[TrigSeq[i].Point].Warn_state & 0x93)==0x83))
				{
			    	exci[i] = oldexci[i] = TRUE;
				}
			    else exci[i] = FALSE;
			  }
              else 
			  {
				  exci[i] = oldexci[i] = FALSE;
                  TrigSeq[TrigSeq[i].Point].PntStat = m_structValueState[TrigSeq[i].Point].Warn_state;
			  }
	    	  break;
	      case 5:
	    	  break;
	      case 6:
	    	  break;
	      case 7://ͨѶ��������
		      if ( Ac_state==0)  
			  {
	    		if ((!oldexci[i]) &&((m_structValueState[TrigSeq[i].Point].Warn_state & 0x10)==0x00))
				{
					exci[i] = oldexci[i] = TRUE;
				}
	    		else exci[i] = FALSE;
			  }
              else 
			  {
				  exci[i] = oldexci[i] = FALSE;
                  TrigSeq[TrigSeq[i].Point].PntStat = m_structValueState[TrigSeq[i].Point].Warn_state;
			  }
	    	  break;
	      case 8:  //ͨѶʧ������
	    	  if ( Ac_state==1) 
			  {
	    		if ((!oldexci[i]) &&((m_structValueState[TrigSeq[i].Point].Warn_state & 0x10)==0x10))
				{
					exci[i] = oldexci[i] = TRUE;
				}
	    		else exci[i] = FALSE;
			  }
              else 
			  {
				  exci[i] = oldexci[i] = FALSE;
                  TrigSeq[TrigSeq[i].Point].PntStat = m_structValueState[TrigSeq[i].Point].Warn_state;
			  }
    		  break;
           default:
			  break;
		 }

		 if (exci[i]&& (SeqFlag[i] == FALSE))
		{
   	         InsertSeq(TrigSeq[i].Seq);//���������ж�ʱ��  
             TrigSeq[TrigSeq[i].Point].PntStat = m_structValueState[TrigSeq[i].Point].Warn_state;

		} 
	  }
    }
     //����ֻ����״̬�ı��ִ�У�ִ��һ��

}

void CMonitorPointThread::SeqSchedule()      
{
      //���е��ܿ���        ������ִ�еĹ���
//	Cdialogspumonitor  dlg_spumonitor;
	CMainFrame* pFWnd=(CMainFrame*)AfxGetMainWnd();
	CCommStatusFM *pCommStatusFM=pFWnd->m_pCommStatusFM;

   char		string[32];
   BYTE		pointer;
   STACK    *stackptr;
   int 		i;	  
   for (i=0; i<SEQNUM; i++)	
   {
       if (!SeqFlag[i]) 
	   {
                TotalDelay[i] = 0;
	        	continue;
       }
       // Look for next active sequence   ����ִ�е�ʱ��
       pointer = Sequence[i].ptr;
       stackptr = &Sequence[i].seqstack[pointer];
       CALL_SEQ(stackptr->seqnum, stackptr->seqevent, (BYTE)i);  // ��������д�˺��� 
       // This sequence is finished
       if (!(Sequence[i].ptr))	
	   {
               TotalDelay[i] = 0;
	           sprintf(string," %-3d  ֹͣ",  ExecSeq[i]);
	           SetDlgItemText(dlg_spumonitor,IDM_SA_SQ1+i,string);
		       pCommStatusFM->m_bBitCmdReceiveSuccess=TRUE;

                                              // ��ʾʱ�������� ״̬ 
	          if (WaitSeqLen) 
			  {
	                   WaitSeqLen--;
	                   Sequence[i].ptr = 1;
	                   stackptr = &Sequence[i].seqstack[1];
	                   stackptr->seqnum = WaitSeq[i].seqnum;
                       stackptr->seqevent = WaitSeq[i].seqevent;// ��δ��������� 
	                   ExecSeq[i] = stackptr->seqnum;

///0303					   sprintf(string,"%-3d ����", i, ExecSeq[i]);
					   SetDlgItemText(dlg_spumonitor,IDM_SA_SQ1+i,string);
                                                        // ��ʾʱ�������״̬
			  }
			  else 
			  {
                     SeqFlag[i] = FALSE;
			         Sequence[i].ptr = 0;                    // �޸ı�ʾֹͣ
			  }
	   }
   }


}


void CMonitorPointThread::InsertSeq(int seqnum)
{
   int      i,j,k;
   char	    string[32];
   STACK    *stackptr;

       if (SSeq[seqnum].SPUhold==TRUE)    //((SSeq[seqnum].SPUhold==TRUE)||(SSeq[seqnum].SPUnum!=seqnum )) 
		   return;
//       for (k=0; k<SEQNUM; k++)//ֻ��һ���Ҵ˸�Ϊֹͣ״̬

       for (k=0; k<SEQNUM; k++)//Ѱ�ҿɲ�Ŀռ�,һ��16��Ѱ�ҿ��Բ���Ŀռ�
	   {
           if ((seqnum==ExecSeq[k])&& (Sequence[k].ptr==1))    
		       return;           		   
//           if (Sequence[k].ptr!=0)     
//		       return;           		   		   
		   if ((!SeqFlag[k])&& (Sequence[k].ptr<=0))	           // �����ж�ʱ�����   
		   {
            for (i=0; i<64; i++)  
    	    SeqReg[k][i] = 0;                

	       SeqFlag[k] = TRUE;
	       Sequence[k].ptr = 1;
	       Sequence[k].depth = 0;
	       stackptr = &Sequence[k].seqstack[1];
	       stackptr->seqnum = seqnum;
           stackptr->seqevent = 0; //��ʼ����

	       ExecSeq[k] = seqnum;
        
           sprintf(string," %-3d  ����", ExecSeq[k]);
		   SetDlgItemText(dlg_spumonitor,IDM_SA_SQ1+k,string);
	                             //  ��ʾ״̬
	       break;
		   }
//		break;
	   }
	   // No sub window is idle, Insert it in waiting queue
		   //������밴�����ȼ���255���,SPUproriֵ�;Ͳ���ǰ��,��ʾԽ����
       if ((k >= SEQNUM)&&(WaitSeqLen<MAXWAITLEN))	
	   {
           for (k=WaitSeqLen-1; k>=0; k--)

	       if (SSeq[WaitSeq[k].seqnum].SPUprori<=SSeq[seqnum].SPUprori)
							break;
	           for (j=WaitSeqLen-1; j>k; j--) 
			   {
	           WaitSeq[j+1].seqnum = WaitSeq[j].seqnum;
               WaitSeq[j+1].seqevent = WaitSeq[j].seqevent;//added by ljh
			   }
	        WaitSeq[k+1].seqnum = seqnum;
	        WaitSeq[k+1].seqevent = 0;
            WaitSeqLen++;
       }
}

int CMonitorPointThread::CALL_SEQ(WORD Snum, BYTE event, BYTE id)
{
  //event �� 0��ʼ��ʾ��һ���¼�һ��3��,idһ��16��
  //enent ���ż�һ
  int step=0;
  STACK   *stackptr;
  BYTE	  pointer, oldevent;
  WORD    oldSnum;//yuanlaide shixuhao
//  aPoint	*pp1;
  BYTE    addr,trunck,convid;
  BYTE Data_ctrl=0;
  CMainFrame* pFWnd=(CMainFrame*)AfxGetMainWnd();
  CCommStatusFM* pCommStatusFM=pFWnd->m_pCommStatusFM;
	CKJMonitorApp* pApp=(CKJMonitorApp* )AfxGetApp();
//	pApp->pMPT->RefreshPoint(iTrunk);
  char		string[32];
  unsigned int i;
  int para1;
  int para2;
  int para3;
  int para4;
  int command_type;
  unsigned int com_num;
  char parastr1;
  char parastr2;
  char parastr3;
  char parastr4;
  UINT p1,p2,p3,p4;
  BYTE moni;
  p1=0;
  p2=0;
  p3=0;
  p4=0;

  BOOL get1,get2,get3,get4,test;
  test=FALSE;
  get1=FALSE;
  get2=FALSE;
  get3=FALSE;
  get4=FALSE;
 // CString str;
   //
  do{//0

      while((Snum/*ʱ���*/==0)&&(Sequence[id].ptr>0))
	  {                     //���Snum=0,˵���¿�һ������Sequence[id].pt  �Ĳ���
    	  pointer = --Sequence[id].ptr;
    	  Sequence[id].depth--;//�ָ�
	    if (pointer>0)
		{
	      stackptr = &Sequence[id].seqstack[pointer];
	      Snum = stackptr->seqnum;
          event = stackptr->seqevent;//����ִ��ԭ�е�ָ��
		}
      }
         //�� ��ʽ���������趨


///      sprintf(string,"%2d) Sequence%-3d  Event%1d", id, Snum, event+1);
      sprintf(string," %d    �� %d", Snum, event+1);

///	  sprintf(string,"        %-3d  ", event);
	  SetDlgItemText(dlg_spumonitor,IDM_SA_SQ1+id,string);

/*
      if (hMonitorWnd != NULL) 
	  {
	  SetDlgItemText(hMonitorWnd,IDM_MON_SQ1+id,string);
      }
      if (hStartWnd != NULL) 
	  {
	  SetDlgItemText(hStartWnd,IDM_SA_SQ1+id,string);
      }
*/
      if (Sequence[id].ptr<=0) continue;//ֹͣδ2

	   command_type=SSeq[Snum].command[event+1].command_type;
       com_num=SSeq[Snum].num_of_command;
	   para1=chartoint(SSeq[Snum].command[event+1].Para1);
	   para2=chartoint(SSeq[Snum].command[event+1].Para2);
	   para3=chartoint(SSeq[Snum].command[event+1].Para3);
   	   para4=chartoint(SSeq[Snum].command[event+1].Para4);
       parastr1=SSeq[Snum].command[event+1].Para1[0];
       parastr2=SSeq[Snum].command[event+1].Para2[0];
       parastr3=SSeq[Snum].command[event+1].Para3[0];
       parastr4=SSeq[Snum].command[event+1].Para4[0];

	   //ȡ��ʵ��ֵ
	   if((parastr1=='R'||parastr1=='r')
            && (para1>0 )&& (para1<=48))
	   {
		   get1=TRUE;
		   p1=FixReg[para1-1];
	   }
	   else if((parastr1=='X'||parastr1=='x')
            && (para1>0 )&& (para1<=64))
	   {   get1=TRUE;
		   p1=SeqReg[id][para1-1];
	   }
	   else if((parastr1=='P'||parastr1=='p')
            && (para1>0 )&& (para1<=MAX_POINT_NUMBER-1))
	   {
		   get1=TRUE;
		  p1= m_structValueState[para1].ufData;  //lpPointValue[para1].Data16;
	   }
	   else if(parastr1=='#'||(parastr1>=48&&parastr1<=57 ))
	   {
		   get1=TRUE;
		   p1=para1;
	   }
       else
	   { 
		   get1=FALSE;
	   }
	   if((parastr2=='R'||parastr2=='r')
            && (para2>0 )&& (para2<=48))
	   {
		   get2=TRUE;
		   p2=FixReg[para2-1];
	   }
	   else if((parastr2=='X'||parastr2=='x')
            && (para2>0 )&& (para2<=64))
	   {
		   		   get2=TRUE;
		   p2=SeqReg[id][para2-1];
	   }
	   else if((parastr2=='P'||parastr2=='p')
            && (para2>0 )&& (para2<=MAX_POINT_NUMBER-1))
	   {		   get2=TRUE;
		  p2= m_structValueState[para2].ufData;  //lpPointValue[para2].Data16;
	   }
	   else if(parastr2=='#'||(parastr2>=48&&parastr2<=57 ))
	   {   get2=TRUE;
		   p2=para2;
	   }
       else
	   {
		   		   get2=FALSE;
	   }
	   if((parastr3=='R'||parastr3=='r')
            && (para3>0 )&& (para3<=48))
	   {
		  get3=TRUE;
		   p1=FixReg[para3-1];
	   }
	   else if((parastr3=='X'||parastr3=='x')
            && (para3>0 )&& (para3<=64))
	   {  get3=TRUE;
		   p3=SeqReg[id][para3-1];
	   }
	   else if((parastr3=='P'||parastr3=='p')
            && (para3>0 )&& (para3<=MAX_POINT_NUMBER-1))
	   {
		   get3=TRUE;
		  p3= m_structValueState[para3].ufData;  //lpPointValue[para3].Data16;
	   }
	   else if(parastr3=='#'||(parastr3>=48&&parastr3<=57 ))
	   {
		   get3=TRUE;
		   p3=para3;
	   }
       else
	   {get3=FALSE;
	   }
	   if((parastr4=='R'||parastr4=='r')
            && (para4>0 )&& (para4<=48))
	   {
		   get4=TRUE;
		   p4=FixReg[para4-1];
	   }
	   else if((parastr4=='X'||parastr4=='x')
            && (para4>0 )&& (para4<=64))
	   {
		   get4=TRUE;
		   p4=SeqReg[id][para4-1];

	   }
	   else if((parastr4=='P'||parastr4=='p')
            && (para4>0 )&& (para4<=MAX_POINT_NUMBER-1))
	   {
		  get4=TRUE;
		  p4= m_structValueState[para4].ufData;  //lpPointValue[para4].Data16;
	   }
	   else if(parastr4=='#'||(parastr4>=48&&parastr4<=57 ))
	   {
		   get4=TRUE;
		   p4=para4;
	   }
       else
	   {
		   get4=FALSE;
	   }
//  1  ���п��¼�
      if (command_type==45) //���¼�
	  {//���Ϊ��ģ���
	    if (++event>=com_num)
		{
	      Snum = 0; event=0;//ִ����һʱ��
		}
          continue;
      }
      else if(command_type==1)  //ֹͣ
	  {
         Snum = 0; event=0;//ִ����һʱ��
	  }
      else if(command_type==14)  //ת�Ʋ�
	  {
          if(para1>0&&(p1>0&&p1<=com_num))

          event=p1-1;
	  }
	  else if(command_type==15)  //����ĳһ���е�һ��
	  { 
		     oldSnum = Snum;  oldevent = event;
			if (++event>=com_num) 
			  {
	              Snum = 0; event=0;
			  }
			if(p1>0
				&&p1<=200
					&&p2>0
					&&p2<=SSeq[p1].num_of_command && SSeq[p1].SPUnum==p1  )
			{
				  if (Sequence[id].depth<=3  )
				  {
		          pointer = Sequence[id].ptr;
		          stackptr = &Sequence[id].seqstack[pointer];
		          stackptr->seqnum = Snum;
		          stackptr->seqevent = event;//��ǰ,Ҳ�п�����NextSPU
		          Sequence[id].ptr++;
		          Sequence[id].depth++;
		          Snum = p1;
                      
			      event = p2-1;
                  }
			}
	  }
      else if(command_type==16) //ת�Ʋ���
	  {                     
			if(p1>0&&
				p1<=200
					&&p2>0
					&&p2<=SSeq[p1].num_of_command && 
                    SSeq[p1].SPUnum==p1 )    
			{
				Snum=p1;
               event=p2-1;
			}
			else
			{	    
				if (++event>=com_num)
				{
	             Snum = 0; event=0;//ִ����һʱ��
				}
                continue;
			}
	  }
	  else if(command_type==22)     //������⿪ʱ��
	  {
		  if(p1>0 &&	p1<=200 && para2>=0	&&para2<=1)
		  {
                if(para2==1)  //����
				{
              	   for (i=0; i<SEQNUM; i++)
				    if ((SeqFlag[i])&&(ExecSeq[i] == p1))	break;//Ѱ�Һ��ʵ�i
                 	if (i <SEQNUM)
					{
                        SeqFlag[i]=FALSE;
					}
				}
				else
				{
              	   for (i=0; i<SEQNUM; i++)
				    if ((!SeqFlag[i])&&(ExecSeq[i] == p1))	break;//Ѱ�Һ��ʵ�i
                 	if (i <SEQNUM)
					{
                        SeqFlag[i]=TRUE;
					}
				}
		  }
			 if (++event>=com_num)
				{
	             Snum = 0; event=0;//ִ����һʱ��
				}
                continue;
	  }
      else if (command_type==20)   //����ʱ��
	  {   
		  if(para1>0)
		  {    
			  if(parastr1=='#'||(parastr1>=48&&parastr1<=57))   //ֱ��ʱ���
			  {
				  if(para1<=200)
					  pApp->pMPT->InsertSeq(para1);
			  }
			   if(parastr1=='R'|| parastr1=='r')
			  {
				  if( para1<=48)
				  { if(FixReg[para1-1]>0&&FixReg[para1-1]<=200 )
				       			  pApp->pMPT->InsertSeq(FixReg[para1-1]);
				  }
			  }
              if(parastr1=='X'|| parastr1=='x')
			  {
				  if( para1<=64)
				  {
                        if(SeqReg[id][para1-1]>0 &&SeqReg[id][para1-1]<=200)
             		       			  pApp->pMPT->InsertSeq(SeqReg[id][para1-1]);
				  }
			  }
		  }
			 if (++event>=com_num)
				{
	             Snum = 0; event=0;//ִ����һʱ��
				}
                continue;
	  }
	  else if(command_type==21 )          //�ж�ʱ��
	  {
    		  if(para1>0)
			  {    
			   if(parastr1=='#'||(parastr1>=48&&parastr1<=57))   //ֱ��ʱ���
			   {
				  if(para1<=200)
				  {
					  for (i=0; i<SEQNUM; i++)
					   if ((ExecSeq[i] == para1))	break;//Ѱ�Һ��ʵ�i
				      if (i < SEQNUM)
					  {
					   Sequence[i].ptr = 0;
					  }
				  }
			   }
			   if(parastr1=='R'|| parastr1=='r')
			   {
				  if( para1<=48)
				  { if(FixReg[para1-1]>0&&FixReg[para1-1]<=200 )
				  {
					  for (i=0; i<SEQNUM; i++)
					   if ((ExecSeq[i] == FixReg[para1-1]))	break;//Ѱ�Һ��ʵ�i
				      if (i < SEQNUM)
					  {
					   Sequence[i].ptr = 0;
					  }
                  }
				  }
			   }
               if(parastr1=='X'|| parastr1=='x')
			   {
				  if( para1<=64)
				  {
                        if(SeqReg[id][para1-1]>0 &&SeqReg[id][para1-1]<=200)
						{ for (i=0; i<SEQNUM; i++)
						if ((ExecSeq[i] ==SeqReg[id][para1-1]))	break;//Ѱ�Һ��ʵ�i
				         if (i < SEQNUM)
						 {
					       Sequence[i].ptr = 0;
						 }
						}
				  }
			   }
			  }
			 if (++event>=com_num)
				{
	             Snum = 0; event=0;//ִ����һʱ��
				}
                continue;
	  }
      else if( command_type==19)           //��ʱ����
	  {   
		  //�Ӳ�����ȡ����Ӧ����
          if(para1>0&&para1<=3600)
		  {
		  //��ʱ�ṹ���� 
                 if (TotalDelay[id]==0)
				 {
				  TotalDelay[id] =para1*CLK_TCK;
				  DelayStartTime[id] = clock();
                 }
			     else
				 {
			   	   if ((clock()-DelayStartTime[id])>=TotalDelay[id])
				   {
					  	TotalDelay[id] = 0;         			
					 if (++event>=com_num)
					 {
	                 Snum = 0; event=0;//ִ����һʱ��
					 }
                     continue;
				   }
				 }
		  }
		  else
		  { 
			  		if (++event>=com_num)
					 {
	                 Snum = 0; event=0;//ִ����һʱ��
					 }
                     continue;
		  }
				 //��ʱ�ṹ���� 
	  }
	  else if( command_type>=2 && command_type<=13)           //�Ե���д���
	  {  
		  if(para1>0&&para2>0&&para3>0)
		  {
		    if((parastr1=='R'|| parastr1=='r')&& get1 && get2 && get3)
			{
				if( para1>0&&para1<=48)
				{
					switch(command_type)
					{
					case 2:
						FixReg[para1-1]+=p2+p3;
						break;
					case 3:
						FixReg[para1-1]-=p2+p3;
						break;
					case 4:
						FixReg[para1-1]=p1&p2&p3;
						break;
					case 5:
						FixReg[para1-1]=p1|p2|p3;
						break;
					case 6:
						FixReg[para1-1]=p1^p2^p3;
						break;
					case 7:
						FixReg[para1-1]=p2+p3;
						break;
					case 8:
						FixReg[para1-1]=p2-p3;
						break;
					case 9:
						FixReg[para1-1]=p2&p3;
						break;
					case 10:
						FixReg[para1-1]=p2|p3;
						break;
					case 11:
						FixReg[para1-1]=p2^p3;
						break;						
					case 12:
						FixReg[para1-1]=p2*p3;
						break;						
					case 13:
						if(p3)
						FixReg[para1-1]=p2/p3;
						break;
					default:
						break;
					}
				}
			}
            else
			if((parastr1=='P'|| parastr1=='p')&&get1&&get2&&get3)
			{
				if( para1>0&&para1<=MAX_POINT_NUMBER-1)
				{
					switch(command_type)
					{
					case 2:
                        m_structValueState[para1].ufData +=p2+p3;
						break;
					case 3:
                        m_structValueState[para1].ufData=p1+p2+p3;
						break;
					case 4:
						m_structValueState[para1].ufData=p1&p2&p3;
						break;
					case 5:
						m_structValueState[para1].ufData=p1|p2|p3;
						break;
					case 6:
						m_structValueState[para1].ufData=p1^p2^p3;
						break;
					case 7:
						m_structValueState[para1].ufData=p2+p3;
						break;
					case 8:
						m_structValueState[para1].ufData=p2-p3;
						break;
					case 9:
						m_structValueState[para1].ufData=p2&p3;
						break;
					case 10:
					    m_structValueState[para1].ufData=p2|p3;
						break;
					case 11:
						m_structValueState[para1].ufData=p2^p3;
						break;						
					case 12:
						m_structValueState[para1].ufData=p2*p3;
						break;						
					case 13:
						if(p3)
						m_structValueState[para1].ufData=p2/p3;
						break;
					default:
						break;
					}
				}
			}
			else if((parastr1=='X'|| parastr1=='x')&&get1&&get2&&get3)
			{
				if( para1>0&&para1<=64)
				{
					switch(command_type)
					{
					case 2:
                       SeqReg[id][para1-1]+=p2+p3;
						break;
					case 3:
                         SeqReg[id][para1-1]=p1+p2+p3;
						break;
					case 4:
						 SeqReg[id][para1-1]=p1&p2&p3;
						break;
					case 5:
						 SeqReg[id][para1-1]=p1|p2|p3;
						break;
					case 6:
						 SeqReg[id][para1-1]=p1^p2^p3;
						break;
					case 7:
						 SeqReg[id][para1-1]=p2+p3;
						break;
					case 8:
						 SeqReg[id][para1-1]=p2-p3;
						break;
					case 9:
						 SeqReg[id][para1-1]=p2&p3;
						break;
					case 10:
					     SeqReg[id][para1-1]=p2|p3;
						break;
					case 11:
						 SeqReg[id][para1-1]=p2^p3;
						break;						
					case 12:
						 SeqReg[id][para1-1]=p2*p3;
						break;						
					case 13:
						if(p3)
						 SeqReg[id][para1-1]=p2/p3;
						break;
					default:
						break;
					}
				}
			}
			else
			{
			}
		  }          //if(para1>0&&para2>0&&para3>0)
		  if (++event>=com_num)
				{
	             Snum = 0; event=0;//ִ����һʱ��
				}
                continue;   
	  }
 	  else if (command_type==17)   //��ֵ�Ӹ����Ĵ�����ʼ�ļĴ���
	  {
		    if((parastr1=='R'|| parastr1=='r')&& get1 && get2 && get3)
			{
				if( para1>0&&(para1+p3)<=48&&p3>=1 )
					for( i=0;i<p3;i++)
					{FixReg[para1+i-1]=p2;
					}
			}
		       if (++event>=com_num)
				{
	             Snum = 0; event=0;//ִ����һʱ��
				}
                continue;   
	  }
	  else if (command_type==18)   //�Ĵ���ֵ��һ���ڸ�ֵ����ʱת�Ƶ�ָ����
	  {
            if((parastr1=='R'|| parastr1=='r')&& get1 && get2 )
			{				
				if( para1>0&&para1<=48)
				{
					if(p1!=0&&p2>0&&p2<=com_num)
					{
						FixReg[para1-1]--;
						event=p2-1;
					}
					else
					{
		               if (++event>=com_num)
					   {
	                   Snum = 0; event=0;//ִ����һʱ��
					   }
                        continue;   
					}
				}  //if( para1>0&&para1<=48)
			}
	  }
	  else if(command_type==23||command_type==24)  //��ȡʱ��
	  {
	        if((parastr1=='R'|| parastr1=='r')&& (parastr2=='R'|| parastr2=='r')
			&&(parastr3=='R'|| parastr3=='r') )
			{
				if( para1>0&&para1<=48&&para2>0&&para2<=48&&para3>0&&para3<=48)
				{
					CTime tEventTime = CTime::GetCurrentTime();
				    if(command_type==23)
					{ FixReg[para1-1]=tEventTime.GetHour();
					  FixReg[para2-1]=tEventTime.GetMinute();
                      FixReg[para3-1]=tEventTime.GetSecond();
					}
					else
					{ FixReg[para1-1]=tEventTime.GetMonth();
					  FixReg[para2-1]=tEventTime.GetDay();
                      FixReg[para3-1]=tEventTime.GetYear();
					}
				}
			}
		       if (++event>=com_num)
				{
	             Snum = 0; event=0;//ִ����һʱ��
				}
                continue;   
		}
 		else if(command_type>=28&&command_type<=39)//��ʵִ��
		{//1
			if(get1&&get2&&get4)
			{//2 
				switch( command_type)
				{//3
			     case 28:
				  if(p1>p2)
				  test=TRUE;
				  else
				  test=FALSE;
				  break;
			     case 29:
				  if(p1>=p2)
				  test=TRUE;
				  else
				  test=FALSE;

				  break;
			     case 30:
				  if(p1==p2)
				  test=TRUE;
				  else
				  test=FALSE;
				  break;
			     case 31:
				  if(p1<=p2)
				  test=TRUE;
				  else
				  test=FALSE;
				  break;
			     case 32:
				  if(p1<p2)
				  test=TRUE;
				  else
				  test=FALSE;
				  break;
			     case 33:
				  if(p1!=p2)
				  test=TRUE;
				  else
				  test=FALSE;
				  break;
			     case 34:
				  if(p1>p2)
				  test=TRUE;
				  else
				  test=FALSE;
				  break;
			     case 35:
				  if(p1>=p2)
				  test=TRUE;
				  else
				  test=FALSE;
				  break;
			     case 36:
				  if(p1==p2)
				  test=TRUE;
				  else
				  test=FALSE;
				  break;
			     case 37:
				  if(p1<=p2)
				  test=TRUE;
				  else
				  test=FALSE;
				  break;
			     case 38:
				  if(p1<p2)
				  test=TRUE;
				  else
				  test=FALSE;
				  break;
			      case 39:
				  if(p1!=p2)
				  test=TRUE;
				  else
				  test=FALSE;				
				  break;
			     default:
				  break;
				}//3
			   if(test)  //ִ����ת�����
			   {//3
				   if((parastr3=='c'||parastr3=='C')&&p4>0&&p4<=200&&SSeq[p4].SPUnum==p4 )

				   {//4
					   if (Sequence[id].depth<=3)
					   {//5
		               pointer = Sequence[id].ptr;
		               stackptr = &Sequence[id].seqstack[pointer];
		               stackptr->seqnum = Snum;
		               stackptr->seqevent = event;//��ǰ,Ҳ�п�����NextSPU
		               Sequence[id].ptr++;
		               Sequence[id].depth++;
		               Snum = p4;
			           event = 0;
					   }//5
					   else
					   {//5
						   		if (++event>=com_num)
								{
					              Snum = 0; event=0;//ִ����һʱ��
								}
				                continue;   
					   }//5
				   }//4
				   else if( (parastr3=='J'||parastr3=='j')&&p4>0&&p4<=com_num)
				   {//4
					   event=p4-1;
				   }//4
				   else
				   {//4
						   		if (++event>=com_num)
								{
					              Snum = 0; event=0;//ִ����һʱ��
								}
				                continue;   
				   }//4
			   }//test end
			   else//3
			   {
				   if (++event>=com_num)
				   {//4
					   Snum = 0; event=0;//ִ����һʱ��
				   }//4
				   continue;   
			   }//3
			}//2
			else  //if(get1&&get2)
			{//2
				if (++event>=com_num)
				{
	             Snum = 0; event=0;//ִ����һʱ��
				}
                continue;   
			}//2
	  }	  
	  else if(command_type==25)  //�����������  
	  {   
		  if((parastr1=='P'||parastr1=='p')&& (para1>0 )&& (para1<=MAX_POINT_NUMBER-1)
			    && para3>0 && (p2==1|| p2==2||p2==40||p2==42||p2==32||p2==34||p2==98)                 )
		  {
//						pFWnd->m_xpara1=para1; 
				
                    addr =pCommStatusFM->m_structMONITORPOINT[para1].ucAddrNo;                 //  add
                    trunck =pCommStatusFM->m_structMONITORPOINT[para1].ucTrunkNo-1;  //  add
                    convid=pCommStatusFM->m_structMONITORPOINT[para1].ucConvID;

			     if (TotalDelay[id]==0)
				 {
                  //����ֻ�о���ʽ1��2�����ڸߵͱ���Ҳ����д
                    switch (pCommStatusFM->m_structMONITORPOINT[para1].ucConvID)     
					//�������ͣ������һ������һ������ֱ�ӷ�������������㹫��һ���ص�ַ��Ҫָ�����ڵ�λ��
					{
						case   S5OUT_B25:              //����������һַ���  
						case   MS5OUT_B25:
		BYTE    mask;
		mask = 0x01;
		mask = mask <<(pCommStatusFM->m_structMONITORPOINT[para1].unChannel-1);
				                      //open 
							if(p2==1)
							{
			mask=~mask;
              Data_ctrl =m_structValueState[para1].ucLowValue & mask;

			  SeqCtrl(trunck,addr, 0x7F &(0x60| Data_ctrl));					
								
								g_ValueCorrect=FALSE;// ���临ԭ���Ա��´�ʹ�á�
									
       							TotalDelay[id] =para3*CLK_TCK;
                  			    DelayStartTime[id] = clock();
				
								break;
							}
				     //close it
							else if(p2==2)
							{

              Data_ctrl =m_structValueState[para1].ucLowValue | mask;

			SeqCtrl(trunck,addr, 0x7F &(0x60| Data_ctrl));
									   
								       TotalDelay[id] =para3*CLK_TCK;
            				           DelayStartTime[id] = clock();
								   break;
							}
							else 
							{
								   TotalDelay[id] = 0;         			
					                if (++event>=com_num)
									{
	                                Snum = 0; event=0;//ִ����һʱ��
									}
									break;
							}
						case A1IN8BIT_CH4ICO:

							if(p2==40)//�رո߱�  ����߱���
							{
								SeqCtrl(trunck,addr,0x28);   //ֱ�ӷ���
						  	 TotalDelay[id] =para3*CLK_TCK;
            				    DelayStartTime[id] = clock();
								break;
							}
							else if(p2==34)//�߸߱������ϵ磩
							{
								SeqCtrl(trunck,addr,0x2a);   //ֱ�ӷ���

							TotalDelay[id] =para3*CLK_TCK;
            				 DelayStartTime[id] = clock();
                             break;
							}
							else if( p2==32)//�򿪸߱�    �߱���
							{
								SeqCtrl(trunck,addr,0x20);   //ֱ�ӷ���
								 TotalDelay[id] =para3*CLK_TCK;
            				    DelayStartTime[id] = clock();
								break;
							}
							else  if(p2==42) //����߸߱��������磩
							{
								SeqCtrl(trunck,addr,0x22);   //ֱ�ӷ���
								 TotalDelay[id] =para3*CLK_TCK;
            				    DelayStartTime[id] = clock();
								break;
							}
							else if(p2==98) //�򿪱�׼
							{
								SeqCtrl(trunck,addr,0x24);   //ֱ�ӷ���    ����
								 TotalDelay[id] =para3*CLK_TCK;
            				    DelayStartTime[id] = clock();
				      			break;
							}
							else
							{
								   TotalDelay[id] = 0;         			
					                if (++event>=com_num)
									{
	                                Snum = 0; event=0;//ִ����һʱ��
									}
									break;
							}
						default:
								   TotalDelay[id] = 0;         			
					                if (++event>=com_num)
									{
	                                Snum = 0; event=0;//ִ����һʱ��
									}
									break;
                      }
                 }
			     else
				 {
			   	     if ((clock()-DelayStartTime[id])>=TotalDelay[id])
					 {
					  	TotalDelay[id] = 0;         			
					    if (++event>=com_num)
						{
	                    Snum = 0; event=0;//ִ����һʱ��
						}
                        continue;
					 }
				 }           //��ʱ����
		  }
		  else
		  {
    			  TotalDelay[id] = 0;    //��ĵط�Ҳ����   
			  		if (++event>=com_num)
					 {
	                 Snum = 0; event=0;//ִ����һʱ��
					 }
                     continue;
		  }
	  }
      else if(command_type==26)  //��ģ����������ֵ  0+��ַ��7λ 0~127 ��ʾ128����ַ�� +��ֵ  
	  {
		   if(para3>0&&(parastr1=='P'||parastr1=='p')&& para1>0 && para1<=MAX_POINT_NUMBER-1 && p2>=0&&p2<=65535)
		   {
			   	if (TotalDelay[id]==0)
				{
			   	    addr =pCommStatusFM->m_structMONITORPOINT[para1].ucAddrNo;                 //  add
                    trunck =pCommStatusFM->m_structMONITORPOINT[para1].ucTrunkNo-1;  //  add
//					if(pCommStatusFM->m_structMONITORPOINT[para1].ucConvID>4)
//					convid=0;
//					else if(pCommStatusFM->m_structMONITORPOINT[para1].ucConvID>0)
                    convid=pCommStatusFM->m_structMONITORPOINT[para1].ucConvID;
//					else
//                    convid=0;
						    
					moni=p2;
//					moni=(BYTE)p2/255;
					SeqCtrl(trunck,addr, moni);   //ֱ�ӷ���  һ��ģ���������Σ�������
//				    moni= (BYTE)(p2%255);
//					SeqCtrl(trunck,addr, moni);   //ֱ�ӷ���

							TotalDelay[id] =para3*CLK_TCK;
            				 DelayStartTime[id] = clock();
				}
				else
				{
					 if ((clock()-DelayStartTime[id])>=TotalDelay[id])
					 {
					  	TotalDelay[id] = 0;         			
					    if (++event>=com_num)
						{
	                    Snum = 0; event=0;//ִ����һʱ��
						}
                        continue;
					 }
				}
		   }
		   else
		   {
			   		   if (++event>=com_num)
						{
	                    Snum = 0; event=0;//ִ����һʱ��
						}
                        continue;
		   }
	  }
	  else if(command_type==27)  //��Ƶ����������ʮ����
	  {
		  if(para3>0&&(parastr1=='P'||parastr1=='p')&& para1>0 && para1<=MAX_POINT_NUMBER-1 && p2>=0&&p2<=256)
		   {
			   	if (TotalDelay[id]==0)
				{
			   	   addr =pCommStatusFM->m_structMONITORPOINT[para1].ucAddrNo;                 //  add
                    trunck =pCommStatusFM->m_structMONITORPOINT[para1].ucTrunkNo-1;  //  add
//					if(pCommStatusFM->m_structMONITORPOINT[para1].ucConvID>4)
//					convid=0;
//					else if(pCommStatusFM->m_structMONITORPOINT[para1].ucConvID>0)
                    convid=pCommStatusFM->m_structMONITORPOINT[para1].ucConvID;
//					else
//                    convid=0;
								pCommStatusFM->m_bSendBitCmd[trunck]=TRUE;

					moni=(BYTE)p2;
					SeqCtrl(trunck,addr, moni);   //ֱ�ӷ��� 
					TotalDelay[id] =para3*CLK_TCK;
					DelayStartTime[id] = clock();
				}
				else
				{
					 if ((clock()-DelayStartTime[id])>=TotalDelay[id])
					 {
					  	TotalDelay[id] = 0;         			
					    if (++event>=com_num)
						{
	                    Snum = 0; event=0;//ִ����һʱ��
						}
                        continue;
					 }
				}
		   }
		   else
		   {
			   		   if (++event>=com_num)
						{
	                    Snum = 0; event=0;//ִ����һʱ��
						}
                        continue;
		   }
	  }
	  else   //ִ�� ��������     ����41   42   43  44  �����Ҳ���
	  {  // ִ����Ӧ�Ĳ���

		       if (++event>=com_num)
				{
	             Snum = 0; event=0;//ִ����һʱ��
				}
                continue;   
	  }
//	     CommandEvent(Snum, SeqReg[id], event, id);      //idΪ���пں�    
	  		  //��ο
            p1=0;
            p2=0;
            p3=0;
            p4=0;
			if (TotalDelay[id]) continue;//�����ʱ���´λ���ִ�����е����� ������ִ����ʱ����
//0  
   }
    while((Sequence[id].ptr>0)&&(++step<MAXSTEP));  //MAXSTEP=1
  if (Sequence[id].ptr>0)
  {
      pointer = Sequence[id].ptr;
      stackptr = &Sequence[id].seqstack[pointer];
      stackptr->seqnum = Snum;
      stackptr->seqevent = event;
  }
   return 1;
}

int CMonitorPointThread::chartoint(char *str)
{
     char buffer[8];
	 strcpy(buffer,str);
	 int i=strlen(buffer);
	 int j;
	 int k;
	 int temp;

     long int_reurn;
     int_reurn=0;
	 if(buffer[0]==80||buffer[0]==112  //p P
       || buffer[0]==82||buffer[0]==114  //r R
	   || buffer[0]==88||buffer[0]==120   //xX
	   || buffer[0]==73||buffer[0]==105   // i I
	   || buffer[0]==35                  //#
		 )
	 {
		 if(strlen(buffer)>=2)
		 {
			 for (j=1;j<=i-1;j++)
			 {
				 if(buffer[j]>=48&&buffer[j]<=57)
				 {
					 temp=1;
					 for(k=1;k<i-j;k++)
						 temp=temp*10;
                  int_reurn+=temp*(buffer[j]-48);        
				 }
				 else
					 return -1;
			 }
		 }
	    else
		 return -1;
	 }
	 else if(buffer[0]=='C'||buffer[0]=='c')
	 {
		 		 if(strlen(buffer)==1)
					 return  -2;           //��ʾ����
				 else   
					 return  -1;             //��ʾ��Ч
	 }
	 else if(buffer[0]=='J'||buffer[0]=='j')
	 {
		 		 if(strlen(buffer)==1)
					 return  -3;           //��ʾ��ת
				 else   
					 return  -1;             //��ʾ��Ч     
	 }
     else if(buffer[0]>=48&&buffer[0]<=57)
	 {
		 if(strlen(buffer)>=1)
		 {
			 for (j=0;j<=i-1;j++)
			 {
				 if(buffer[j]>=48&&buffer[j]<=57)
				 {
					 temp=1;
					 for(k=0;k<i-j-1;k++)
						 temp=temp*10;
                  int_reurn+=temp*(buffer[j]-48);        
				 }
				 else
					 return -1;
			 }
		 }
				 else 
					 return -1;
	 }
     else
		 return -1;

	 return int_reurn;
}

BOOL CMonitorPointThread::EndSequence()
{
  int k;

  for (k=0; k<SEQNUM; k++)
  if (SeqFlag[k])  
	  return FALSE;
//      return;
   for (k=0; k<MAXBLOCK; k++) 
   {
//      GlobalUnlock(hPointList[k]);
//      GlobalFree(hPointList[k]);
	  }
   for (k=1; k<201; k++) 
   {
      GlobalUnlock(hCommandList[k]);
      GlobalFree(hCommandList[k]);
	  
   }
  StartSequence = FALSE;

  //  KillTimer(NULL, idTrigTimer);
//  KillTimer(NULL, idSeqTimer);
  return TRUE;	
}


BOOL CMonitorPointThread::InitSequence()
{
  int		i,k,x;
  //  aPoint far * p;
  BOOL returnvalue=TRUE;
//  int xx=15;
     if(!m_Database.IsOpen())
	{
     	try
		{
	    	m_Database.Open(NULL,FALSE,FALSE,_T("ODBC;DSN=masterdefine;UID=kj86;PWD=kj86;"),FALSE);
		}
    	catch(CDBException *e)
		{
		AfxMessageBox("Open Database Failed.");
		e->Delete();
		}
    }
  //Initialize Register
  for(i=0; i<SEQNUM; i++)
  for (k=0; k<64; k++)  
	  SeqReg[i][k] = 0;

  for (k=0; k<48; k++) 
	  FixReg[k] = 0;  //    ��̬�Ĵ���

  for (k=0; k<SEQNUM; k++) 
	  TotalDelay[k] = 0;
      
  CString str;

  //���ش����ݿ��������ݿ�ʼ
    //1��
      for(i=1;i<=200;i++)
	  {
        SSeq[i].SPUnum=0;
        SSeq[i].SPUhold=TRUE;
        SSeq[i].SPUprori=(BYTE)999;
        SSeq[i].num_of_command=0;
		/*
		for(k=1;k<=2000;k++)
		{
			SSeq[i].command[k].command_type=0;
			strcpy(SSeq[i].command[k].Para1,"");
			strcpy(SSeq[i].command[k].Para2,"");
			strcpy(SSeq[i].command[k].Para3,"");
			strcpy(SSeq[i].command[k].Para4,"");
		}
		*/                    //��̬�����ڴ�
	  }
//�����ݿ�
	    i=0;
		k=0;
	    SpuInform  *spuinform;
        Spudetailed_me *spudetailed;
        spuinform	 = new SpuInform(&m_Database);
        spudetailed   =new  Spudetailed_me(&m_Database);

		spuinform->Open(CRecordset::dynaset, "Spu_information");
         if(spuinform->IsBOF())
     		 return FALSE;
         spuinform->MoveFirst();

	    while(!spuinform->IsEOF())
		{
			if(spuinform->m_exit_or_empty&&spuinform->m_num_of_command)
			{
		            i=spuinform->m_ID;
					x=spuinform->m_priority;
	    		 if(i>=0&&i<=200)
				 {
                     SSeq[i].SPUnum=i;         //һһ��Ӧ�Ĺ�ϵ
                     SSeq[i].SPUhold=spuinform->m_active_hangup;
                     SSeq[i].SPUprori=x;
                     SSeq[i].num_of_command=spuinform->m_num_of_command;
				 }
			}
			spuinform->MoveNext();
		}
	    for(i=1;i<=200;i++)
		{
              if(SSeq[i].num_of_command>=0 && SSeq[i].num_of_command<200)
			  {
            		 hCommandList[i] = GlobalAlloc(GPTR,(DWORD)(sizeof(COMMAND1)*MINCOMMAND));
			  }
	          else if(SSeq[i].num_of_command>=200 && SSeq[i].num_of_command<500)
			  {
	                 hCommandList[i] = GlobalAlloc(GPTR,(DWORD)(sizeof(COMMAND1)*MEDIUMCOMMAND));
			  }
	          else if(SSeq[i].num_of_command>=500 && SSeq[i].num_of_command<1000)
			  {	
	           	   hCommandList[i] = GlobalAlloc(GPTR,(DWORD)(sizeof(COMMAND1)*HIGHCOMMAND));
			  }
	          else 
	        	   hCommandList[i] = GlobalAlloc(GPTR,(DWORD)(sizeof(COMMAND1)*MAXCOMMAND));
      		  if (!hCommandList[i]) return FALSE;
              SSeq[i].command = (COMMAND1 *) GlobalLock(hCommandList[i]);
          	  if (! SSeq[i].command ) return FALSE;
		}
		spudetailed->Open(CRecordset::snapshot);

		 if(spudetailed->IsBOF())
		 return FALSE;
         spudetailed->MoveFirst();
         
		 while(!spudetailed->IsEOF())
		 {
			 i=spudetailed->m_spu_num;
             k=spudetailed->m_step_num;
			 if(i>=0 && i<=200 && k>=0 && k<=2000 && SSeq[i].SPUnum)
			 { 
				 SSeq[i].command[k].command_type=spudetailed->m_command_index;
                 str=spudetailed->m_para1;
				 if(!str.IsEmpty())
                     sprintf(SSeq[i].command[k].Para1,str); 

                 str=spudetailed->m_para2;
				 if(!str.IsEmpty())
                     sprintf(SSeq[i].command[k].Para2,str); 

                 str=spudetailed->m_para3;
				 if(!str.IsEmpty())
                     sprintf(SSeq[i].command[k].Para3,str); 

				 str=spudetailed->m_para4;
				 if(!str.IsEmpty())
                     sprintf(SSeq[i].command[k].Para4,str); 
			 }
			 spudetailed->MoveNext();
		 }
		delete spudetailed;
       	delete spuinform;
  //���ش����ݿ��������ݽ���
  StartSequence = TRUE;

  return(returnvalue);
}

LPSTR CMonitorPointThread::GetDes(int mode, int command)
{
      //����ģʽ�ŵ�����
      /*mode 1:description
	   mode 2:command description
	   mode 3:para1
	   mode 4:para2
	   mode 5:para3
	   mode 6:para4
     */
       LPSTR ss;
       switch(command)
	   {
	      case 1:
                  switch(mode)
				  {
				  case 1:
                       	  ss="���н���";
					  break;
                  case 2:
					  ss="END";
                      break;
				  case 3:
					  ss="";
					  break;
				  case 4:
					  ss="";
					  break;
				  case 5:
					  ss="";
					  break;
				  case 6:
					  ss="";
					  break;
				  }
				 break;
		   	case 2:
                  switch(mode)
				  {
				  case 1:
					  ss="�ӷ�";
					  break;
                  case 2:
					  ss="ADDD";
                      break;
				  case 3:
					  ss="P1";
					  break;
				  case 4:
					  ss="P2";
					  break;
				  case 5:
					  ss="P3";
					  break;
				  case 6:
					  ss="";
					  break;
				  }
				 break;
		   	case 3:
                  switch(mode)
				  {
				  case 1:
					  ss="����";
					  break;
                  case 2:
					  ss="SUBD";
                      break;
				  case 3:
					  ss="P1";
					  break;
				  case 4:
					  ss="P2";
					  break;
				  case 5:
					  ss="P3";
					  break;
				  case 6:
					  ss="";
					  break;
				  }
				 break;
		   	case 4:
                  switch(mode)
				  {
				  case 1:
					  ss="�߼���";
					  break;
                  case 2:
					  ss="ANDD";
                      break;
				  case 3:
					  ss="P1";
					  break;
				  case 4:
					  ss="P2";
					  break;
				  case 5:
					  ss="P3";
					  break;
				  case 6:
					  ss="";
					  break;
				  }
				 break;
		   	case 5:
                  switch(mode)
				  {
				  case 1:
					  ss="�߼���";
					  break;
                  case 2:
					  ss="ORLD";
                      break;
				  case 3:
					  ss="P1";
					  break;
				  case 4:
					  ss="p2";
					  break;
				  case 5:
					  ss="p3";
					  break;
				  case 6:
					  ss="";
					  break;
				  }
				 break;
		   	case 6:
                  switch(mode)
				  {
				  case 1:
					  ss="�߼����: P1=P1 XOR P2 XOR P3";
					  break;
                  case 2:
					  ss="XORD";
                      break;
				  case 3:
					  ss="P1";
					  break;
				  case 4:
					  ss="P2";
					  break;
				  case 5:
					  ss="P3";
					  break;
				  case 6:
					  ss="";
					  break;
				  }
				 break;
		   	case 7:
                  switch(mode)
				  {
				  case 1:
					  ss="�ӷ�  P1=P2 + P3";
					  break;
                  case 2:
					  ss="ADD";
                      break;
				  case 3:
					  ss="P1";
					  break;
				  case 4:
					  ss="P2";
					  break;
				  case 5:
					  ss="P3";
					  break;
				  case 6:
					  ss="";
					  break;
				  }
				 break;
		   	case 8:
                  switch(mode)
				  {
				  case 1:
					  ss="����  P1=P2 - P3";
					  break;
                  case 2:
					  ss="SUB";
                      break;
				  case 3:
					  ss="P1";
					  break;
				  case 4:
					  ss="P2";
					  break;
				  case 5:
					  ss="P3";
					  break;
				  case 6:
					  ss="";
					  break;
				  }
				 break;
		   	case 9:
                  switch(mode)
				  {
				  case 1:
					  ss="�߼���   P1=P2 AND P3";
					  break;
                  case 2:
					  ss="AND";
                      break;
				  case 3:
					  ss="P1";
					  break;
				  case 4:
					  ss="P2";
					  break;
				  case 5:
					  ss="P3";
					  break;
				  case 6:
					  ss="";
					  break;
				  }
				 break;
		   	case 10:
                  switch(mode)
				  {
				  case 1:
					  ss="�߼���  P1=P2 OR P3";
					  break;
                  case 2:
					  ss="ARL";
                      break;
				  case 3:
					  ss="P1";
					  break;
				  case 4:
					  ss="P2";
					  break;
				  case 5:
					  ss="P3";
					  break;
				  case 6:
					  ss="";
					  break;
				  }
				 break;
		   	case 11:
                  switch(mode)
				  {
				  case 1:
					  ss="�߼����  P1=P2 XOR P3";
					  break;
                  case 2:
					  ss="XOR";
                      break;
				  case 3:
					  ss="P1";
					  break;
				  case 4:
					  ss="P2";
					  break;
				  case 5:
					  ss="P3";
					  break;
				  case 6:
					  ss="";
					  break;
				  }
				 break;
		   	case 12:
                  switch(mode)
				  {
				  case 1:
					  ss="�˷�  P1=P2 * P3";
					  break;
                  case 2:
					  ss="MUL";
                      break;
				  case 3:
					  ss="P1";
					  break;
				  case 4:
					  ss="P2";
					  break;
				  case 5:
					  ss="P3";
					  break;
				  case 6:
					  ss="";
					  break;
				  }
				 break;
		   	case 13:
                  switch(mode)
				  {
				  case 1:
					  ss="����  P1=P2 / P3";
					  break;
                  case 2:
					  ss="DIV";
                      break;
				  case 3:
					  ss="P1";
					  break;
				  case 4:
					  ss="P2";
					  break;
				  case 5:
					  ss="P3";
					  break;
				  case 6:
					  ss="";
					  break;
				  }
				 break;
		   	case 14:
                  switch(mode)
				  {
				  case 1:
					  ss="ת�Ƶ�������ĳһ����";
					  break;
                  case 2:
					  ss="GOTO";
                      break;
				  case 3:
					  ss="��������";
					  break;
				  case 4:
					  ss="";
					  break;
				  case 5:
					  ss="";
					  break;
				  case 6:
					  ss="";
					  break;
				  }
				 break;
		   	case 15:
                  switch(mode)
				  {
				  case 1:
					  ss="����ĳһ�����е�ĳһ��";
					  break;
                  case 2:
					  ss="CALL";
                      break;
				  case 3:
					  ss="������ʱ���";
					  break;
				  case 4:
					  ss="��Ӧ����";
					  break;
				  case 5:
					  ss="";
					  break;
				  case 6:
					  ss="";
					  break;
				  }
				 break;
		   	case 16:
                  switch(mode)
				  {
				  case 1:
					  ss="ת�Ƶ�һ�����е�ĳһ��";
					  break;
                  case 2:
					  ss="GOTOSQ";
                      break;
				  case 3:
					  ss="��������ʱ���";
					  break;
				  case 4:
					  ss="��Ӧ����";
					  break;
				  case 5:
					  ss="";
					  break;
				  case 6:
					  ss="";
					  break;
				  }
				 break;
		   	case 17:
                  switch(mode)
				  {
				  case 1:
					  ss="��ֵ����ָ���Ĵ�����ʼ�ļĴ���";
					  break;
                  case 2:
					  ss="FILL";
                      break;
				  case 3:
					  ss="��ʼ�Ĵ�����";
					  break;
				  case 4:
					  ss="ֵ";
					  break;
				  case 5:
					  ss="�Ĵ�������";
					  break;
				  case 6:
					  ss="";
					  break;
				  }
				 break;
		   	case 18:
                  switch(mode)
				  {
				  case 1:
					  ss="�Ĵ���ֵ��һ���ڸ�ֵ����ʱת�Ƶ�ָ����";
					  break;
                  case 2:
					  ss="DJNZ";
                      break;
				  case 3:
					  ss="�Ĵ�����";
					  break;
				  case 4:
					  ss="����";
					  break;
				  case 5:
					  ss="";
					  break;
				  case 6:
					  ss="";
					  break;
				  }
				 break;
		   	case 19:
                  switch(mode)
				  {
				  case 1:
					  ss="�������ӳ�ִ��";
					  break;
                  case 2:
					  ss="DELAY";
                      break;
				  case 3:
					  ss="�ӳٵ�����";
					  break;
				  case 4:
					  ss="";
					  break;
				  case 5:
					  ss="";
					  break;
				  case 6:
					  ss="";
					  break;
				  }
				 break;
		   	case 20:
                  switch(mode)
				  {
				  case 1:
					  ss="������ʱ��";
					  break;
                  case 2:
					  ss="STRSEQ";
                      break;
				  case 3:
					  ss="ʱ�����";
					  break;
				  case 4:
					  ss="";
					  break;
				  case 5:
					  ss="";
					  break;
				  case 6:
					  ss="";
					  break;
				  }
				 break;
		   	case 21:
                  switch(mode)
				  {
				  case 1:
					  ss="�ж����";
					  break;
                  case 2:
					  ss="ABTSEQ";
                      break;
				  case 3:
					  ss="ʱ���";
					  break;
				  case 4:
					  ss="";
					  break;
				  case 5:
					  ss="";
					  break;
				  case 6:
					  ss="";
					  break;
				  }
				 break;
		   	case 22:
                  switch(mode)
				  {
				  case 1:
					  ss="����ʱ���ģʽ��";
					  break;
                  case 2:
					  ss="LCKSEQ";
                      break;
				  case 3:
					  ss="ʱ���";
					  break;
				  case 4:
					  ss="������ʽ";
					  break;
				  case 5:
					  ss="";
					  break;
				  case 6:
					  ss="";
					  break;
				  }
				 break;
			case 23:
                  switch(mode)
				  {
				  case 1:
					  ss="����ǰʱ�䵽�Ĵ���";
					  break;
                  case 2:
					  ss="RDTIME";
                      break;
				  case 3:
					  ss="Сʱ�Ĵ�����";
					  break;
				  case 4:
					  ss="���ӼĴ�����";
					  break;
				  case 5:
					  ss="��Ĵ�����";
					  break;
				  case 6:
					  ss="";
					  break;
				  }
				 break;
		   	case 24:
                  switch(mode)
				  {
				  case 1:
					  ss="����ǰ���ڵ��Ĵ���";
					  break;
                  case 2:
					  ss="RDDATE";
                      break;
				  case 3:
					  ss="�·ݼĴ���";
					  break;
				  case 4:
					  ss="�ռĴ���";
					  break;
				  case 5:
					  ss="��ݼĴ���";
					  break;
				  case 6:
					  ss="";
					  break;
				  }
				 break;
		   	case 25:
                  switch(mode)
				  {
				  case 1:
					  ss="�����������";
					  break;
                  case 2:
					  ss="DOUT";
                      break;
				  case 3:
					  ss="Pt#";
					  break;
				  case 4:
					  ss="���ʽ";
					  break;
				  case 5:
					  ss="�ӳ�����";
					  break;
				  case 6:
					  ss="��λ��ʽ";
					  break;
				  }
				 break;
		   	case 26:
                  switch(mode)
				  {
				  case 1:
					  ss="ģ���������";
					  break;
                  case 2:
					  ss="AOUT";
                      break;
				  case 3:
					  ss="����Pt#";
					  break;
				  case 4:
					  ss="������õ���ֵ";
					  break;
				  case 5:
					  ss="��ʱ����";
					  break;
				  case 6:
					  ss="��λ��ʽ";
					  break;
				  }
				 break;
		   	case 27:
                  switch(mode)
				  {
				  case 1:
					  ss="ֱ�ӿ���";
					  break;
                  case 2:
					  ss="DROUT";
                      break;
				  case 3:
					  ss="����";
					  break;
				  case 4:
					  ss="����ֵ";
					  break;
				  case 5:
					  ss="��ʱ����";
					  break;
				  case 6:
					  ss="�Ƿ�λ";
					  break;
				  }
				 break;
		   	case 28:
                  switch(mode)
				  {
				  case 1:
					  ss="���Val1>Val2��ת�ƻ���õ�����";
					  break;
                  case 2:
					  ss="IFGTV2";
                      break;
				  case 3:
					  ss="Val1";
					  break;
				  case 4:
					  ss="Val2";
					  break;
				  case 5:
					  ss="ת�ƻ����";
					  break;
				  case 6:
					  ss="���Ż�ʱ���";
					  break;
				  }
				 break;
		   	case 29:
                  switch(mode)
				  {
			  case 1:
					  ss="���Val1>=Val2��ת�ƻ���õ�����";
					  break;
                  case 2:
					  ss="IFGEV2";
                      break;
				  case 3:
					  ss="Val1";
					  break;
				  case 4:
					  ss="Val2";
					  break;
				  case 5:
					  ss="ת�ƻ����";
					  break;
				  case 6:
					  ss="���Ż�ʱ���";
					  break;
				  }
				 break;
		   	case 30:
                  switch(mode)
				  {
	     		  case 1:
					  ss="���Val1=Val2��ת�ƻ���õ�����";
					  break;
                  case 2:
					  ss="IFEQV2";
                      break;
				  case 3:
					  ss="Val1";
					  break;
				  case 4:
					  ss="Val2";
					  break;
				  case 5:
					  ss="ת�ƻ����";
					  break;
				  case 6:
					  ss="���Ż�ʱ���";
					  break;
				  }
				 break;
		   	case 31:
                  switch(mode)
				  {
	     		  case 1:
					  ss="���Val1<=Val2��ת�ƻ���õ�����";
					  break;
                  case 2:
					  ss="IFLEV2";
                      break;
				  case 3:
					  ss="Val1";
					  break;
				  case 4:
					  ss="Val2";
					  break;
				  case 5:
					  ss="ת�ƻ����";
					  break;
				  case 6:
					  ss="���Ż�ʱ���";
					  break;
				  }
				 break;
		   	case 32:
                  switch(mode)
				  {
	     		  case 1:
					  ss="���Val1<Val2��ת�ƻ���õ�����";
					  break;
                  case 2:
					  ss="IFLTV2";
                      break;
				  case 3:
					  ss="Val1";
					  break;
				  case 4:
					  ss="Val2";
					  break;
				  case 5:
					  ss="ת�ƻ����";
					  break;
				  case 6:
					  ss="���Ż�ʱ���";
					  break;
				  }
				 break;
		   	case 33:
                  switch(mode)
				  {
	     		  case 1:
					  ss="���Val1<>Val2��ת�ƻ���õ�����";
					  break;
                  case 2:
					  ss="IFNEV2";
                      break;
				  case 3:
					  ss="Val1";
					  break;
				  case 4:
					  ss="Val2";
					  break;
				  case 5:
					  ss="ת�ƻ����";
					  break;
				  case 6:
					  ss="���Ż�ʱ���";
					  break;
				  }
				 break;
		   	case 34:
                  switch(mode)
				  {
				  case 1:
					  ss="���Val1>CONS ת�ƻ���õ�����";
					  break;
                  case 2:
					  ss="IFGTCN";
                      break;
				  case 3:
					  ss="Val1";
					  break;
				  case 4:
					  ss="Cons2";
					  break;
				  case 5:
					  ss="ת�ƻ����";
					  break;
				  case 6:
					  ss="���Ż�ʱ���";
					  break;
				  }
				 break;
		   	case 35:
                  switch(mode)
				  {
				  case 1:
					  ss="���Val1>=CONS ת�ƻ���õ�����";
					  break;
                  case 2:
					  ss="IFGECN";
                      break;
				  case 3:
					  ss="Val1";
					  break;
				  case 4:
					  ss="Cons2";
					  break;
				  case 5:
					  ss="ת�ƻ����";
					  break;
				  case 6:
					  ss="���Ż�ʱ���";
					  break;
				  }
				 break;
		   	case 36:
                  switch(mode)
				  {
				  case 1:
					  ss="���Val1=CONS ת�ƻ���õ�����";
					  break;
                  case 2:
					  ss="IFEQCN";
                      break;
				  case 3:
					  ss="Val1";
					  break;
				  case 4:
					  ss="Cons2";
					  break;
				  case 5:
					  ss="ת�ƻ����";
					  break;
				  case 6:
					  ss="���Ż�ʱ���";
					  break;
				  }
				 break;
		   	case 37:
                  switch(mode)
				  {
				  case 1:
					  ss="���Val1<=CONS ת�ƻ���õ�����";
					  break;
                  case 2:
					  ss="IFLECN";
                      break;
				  case 3:
					  ss="Val1";
					  break;
				  case 4:
					  ss="Cons2";
					  break;
				  case 5:
					  ss="ת�ƻ����";
					  break;
				  case 6:
					  ss="���Ż�ʱ���";
					  break;
				  }
				 break;
		   	case 38:
                  switch(mode)
				  {
				  case 1:
					  ss="���Val1<CONS ת�ƻ���õ�����";
					  break;
                  case 2:
					  ss="IFLTCN";
                      break;
				  case 3:
					  ss="Val1";
					  break;
				  case 4:
					  ss="Cons2";
					  break;
				  case 5:
					  ss="ת�ƻ����";
					  break;
				  case 6:
					  ss="���Ż�ʱ���";
					  break;
				  }
				 break;
		   	case 39:
                  switch(mode)
				  {
				  case 1:
					  ss="���Val1<>CONS ת�ƻ����";
					  break;
                  case 2:
					  ss="IFNECN";
                      break;
				  case 3:
					  ss="Val1";
					  break;
				  case 4:
					  ss="Cons2";
					  break;
				  case 5:
					  ss="ת�ƻ����";
					  break;
				  case 6:
					  ss="���Ż�ʱ���";
					  break;
				  }
				 break;
		   	case 40:
                  switch(mode)
				  {
				  case 1:
					  ss="���Val1=��ǰСʱ��Val2=��ǰ���� ת�ƻ����";
					  break;
                  case 2:
					  ss="IFTIME";
                      break;
				  case 3:
					  ss="СʱVal1";
					  break;
				  case 4:
					  ss="����Val2";
					  break;
				  case 5:
					  ss="ת�ƻ����";
					  break;
				  case 6:
					  ss="���Ż�ʱ���";
					  break;
				  }
				 break;
		   	case 41:
                  switch(mode)
				  {
				  case 1:
					  ss="��ָ��������";
					  break;
                  case 2:
					  ss="HORN";
                      break;
				  case 3:
					  ss="���ȺŻ�Ĵ�����";
					  break;
				  case 4:
					  ss="";
					  break;
				  case 5:
					  ss="";
					  break;
				  case 6:
					  ss="";
					  break;
				  }
				 break;
		   	case 42:
                  switch(mode)
				  {
				  case 1:
					  ss="��������� Pt# ״̬�Ͳ��ֵ��������·";
					  break;
                  case 2:
					  ss="SNDDL";
                      break;
				  case 3:
					  ss="Pt#";
					  break;
				  case 4:
					  ss="";
					  break;
				  case 5:
					  ss="";
					  break;
				  case 6:
					  ss="";
					  break;
				  }
				 break;
		   	case 43:
                  switch(mode)
				  {
				  case 1:
					  ss="��ӡ���� ����� ��ʼ��� �������";
					  break;
                  case 2:
					  ss="PRPRT";
                      break;
				  case 3:
					  ss="�������";
					  break;
				  case 4:
					  ss="Start Item #";
					  break;
				  case 5:
					  ss="End Item #";
					  break;
				  case 6:
					  ss="";
					  break;
				  }
				 break;
		   	case 44:
                  switch(mode)
				  {
				  case 1:
					  ss="ģ��ߵ�ƽ��ֵ�������";
					  break;
                  case 2:
					  ss="HLACTL";
                      break;
				  case 3:
					  ss="�Ƿ�λ";
					  break;
				  case 4:
					  ss="�Ƿ��ӡ";
					  break;
				  case 5:
					  ss="";
					  break;
				  case 6:
					  ss="";
					  break;
				  }
				 break;
		   	case 45:
                  switch(mode)
				  {
				  case 1:
					  ss="������";
					  break;
                  case 2:
					  ss="NOOPR";
                      break;
				  case 3:
					  ss="";
					  break;
				  case 4:
					  ss="";
					  break;
				  case 5:
					  ss="";
					  break;
				  case 6:
					  ss="";
					  break;
				  }
				 break;
		   	case 46:
                  switch(mode)
				  {
				  case 1:
					  ss="";
					  break;
                  case 2:
					  ss="";
                      break;
				  case 3:
					  ss="";
					  break;
				  case 4:
					  ss="";
					  break;
				  case 5:
					  ss="";
					  break;
				  case 6:
					  ss="";
					  break;
				  }
				 break;
		   	case 47:
                  switch(mode)
				  {
				  case 1:
					  ss="";
					  break;
                  case 2:
					  ss="";
                      break;
				  case 3:
					  ss="";
					  break;
				  case 4:
					  ss="";
					  break;
				  case 5:
					  ss="";
					  break;
				  case 6:
					  ss="";
					  break;
				  }
				 break;
				  default:
					  ss="������û�ж���";
	   }
    return(ss);
}

void CMonitorPointThread::SeqCtrl(BYTE trunck, BYTE addr, BYTE command)
{
	CMainFrame* pFWnd=(CMainFrame*)AfxGetMainWnd();
	CCommStatusFM* pCommStatusFM=pFWnd->m_pCommStatusFM;
	
	pCommStatusFM->UpdateData(TRUE);
	pCommStatusFM->m_bBitCmdReceiveSuccess=FALSE;

	pCommStatusFM->m_structBITADDRCMD[trunck].ucAddr=addr;
	pCommStatusFM->m_structBITADDRCMD[trunck].ucLCmd =command;

	pCommStatusFM->m_bSendBitCmd[trunck]=TRUE;
	pCommStatusFM->UpdateData(FALSE);

	pCommStatusFM->m_bHandCmdCanSend=TRUE;


//	pCommStatusFM->m_bSendBitCmd[trunck]=FALSE;

	if(!pCommStatusFM->m_bStartScan)
	{
		pCommStatusFM->StartScan();
	}
}




