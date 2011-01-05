// RTDataManage.cpp: implementation of the CRTDataManage class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "GUI_VisualStudio.h"
#include "RTDataManage.h"
#include "MainFrm.h"

extern CString strRTData1[6000];
extern CString strRTData2[6000];
extern SerialF       m_ABFlist[MAX_FDS][MAX_CHAN]; 
extern SerialF               m_SerialF[MAX_FDS];
extern BYTE     m_ndkSend[MAX_FDS][44];//44BUFFER_SIZE
extern SerialF               m_AFans[MAX_FDS][MAX_CHAN];    //双风门主扇备扇报警
extern ADMainDis         m_ADMainDis[MAX_FDS][MAX_CHAN];          //调用显示
extern ADCbreakE             m_CFeed[MAX_FDS][MAX_CHAN][65];
extern ADCbreakE             m_ADCbreakE[MAX_FDS][MAX_CHAN][65];
extern SlaveStation             m_SlaveStation[MAX_FDS][MAX_CHAN];
//static int nYear, nMonth, nDay, nHour, nMinute, nSecond;
extern  CPointInfo m_CPointInfo[MAX_POINT_NUMBER];
CWarnPoint  m_CWarnPoint[MAX_POINT_NUMBER];
CStrWarn    m_CStrWarn[MAX_ROW];

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CRTDataManage::CRTDataManage()
{
	m_nodialog = TRUE;
	n_month = 0;
	strdbname= "";
	m_Initdata.clear();
}

CRTDataManage::~CRTDataManage()
{

}

//控制量馈电状态
void CRTDataManage::feedbr(unsigned char  hfds, unsigned char  hchan)
{
}
//模拟量开关量馈电存储
void CRTDataManage::Savefeedbr(unsigned char  hfds, unsigned char  hchan)
{
    CMainFrame* pFWnd=(CMainFrame*)AfxGetMainWnd();
	CString strtemp;
	int	ufData6 = m_SlaveStation[hfds][hchan].ptype;
	int n_oldfeed = m_SlaveStation[hfds][hchan].m_second;
	for(int i= 0 ;i<64 ; i++)
	{
		     int cfds = m_ADCbreakE[hfds][hchan][i].bFSd;
			 int cchan = m_ADCbreakE[hfds][hchan][i].bchanel;
			 if(cfds == 0)
				 break;
			 for(int j= 0 ;j<64 ; j++)
			 {
    		     int ffds = m_CFeed[cfds][cchan][j].bFSd;//被控量
	       		 int fchan = m_CFeed[cfds][cchan][j].bchanel;
				 if(ffds == 0)
	 				 break;
    			 int cvalue = m_SlaveStation[cfds][cchan+16].CValue;
				 strtemp = m_SlaveStation[ffds][fchan].FeedState;
	    		 int dvalue = m_SlaveStation[ffds][fchan].CValue;
				 if(cvalue == 1)
				 {
					 if(dvalue ==0)
					 {
						 m_SlaveStation[ffds][fchan].FeedState ="正常";
						 if(ufData6 <3)
						 {
    						 m_ABFlist[ffds][fchan].cchan =0;
//					pFWnd->m_wndResourceView3.InitFBA(3);
//									theApp.idis =3;
						 }
						 else
						 {
    						 m_ABFlist[ffds][fchan].fchan =0;
//					pFWnd->m_wndResourceView5.InitFBA(5);
//									theApp.idis =5;
						 }
					 }
					 else if(dvalue ==1)
					 {
						 m_SlaveStation[hfds][hchan].m_second++;
						 m_SlaveStation[ffds][fchan].FeedState ="异常";
						 if(ufData6 <3)
						 {
						        m_ABFlist[ffds][fchan].cchan =1;
								if(m_ABFlist[hfds][hchan].cchan == 0)
								{
									m_ABFlist[hfds][hchan].cchan =1;
									pFWnd->m_wndResourceView3.m_cpstr.push_back(m_SlaveStation[hfds][hchan].strPN);
									pFWnd->m_wndResourceView3.B_change = TRUE;
//					pFWnd->m_wndResourceView3.InitFBA(3);
                    pFWnd->paneResourceView3->Select();
//									theApp.idis =3;
								}
						 }
						 else
						 {
						        m_ABFlist[ffds][fchan].fchan =1;
								if(m_ABFlist[hfds][hchan].fchan == 0)
								{
									m_ABFlist[hfds][hchan].fchan =1;
									pFWnd->m_wndResourceView5.m_cpstr.push_back(m_SlaveStation[hfds][hchan].strPN);
									pFWnd->m_wndResourceView5.B_change = TRUE;
//					pFWnd->m_wndResourceView5.InitFBA(5);
                    pFWnd->paneResourceView5->Select();
//									theApp.idis =5;
								}
						 }
					 }
					 m_SlaveStation[hfds][hchan].m_ffds = ffds;
					 m_SlaveStation[hfds][hchan].m_fchan =fchan;
	         		int ufData4 = m_SlaveStation[hfds][hchan].Adjust_state;
	          		if(ufData4 == 1)
		      			SyncCRTData(hfds,hchan,3);     //adjustdata
	        		else
	     	      		SyncCRTData(hfds,hchan,2);     //rtdata
				 }
				 else if(cvalue ==0)
				 {
					 if((dvalue ==0) )
					 {
						 m_SlaveStation[hfds][hchan].m_second++;
						 m_SlaveStation[ffds][fchan].FeedState ="异常";
						 if(ufData6 <3)
						 {
        						 m_ABFlist[ffds][fchan].cchan =1;
								if(m_ABFlist[hfds][hchan].cchan == 0)
								{
									m_ABFlist[hfds][hchan].cchan =1;
									pFWnd->m_wndResourceView3.m_cpstr.push_back(m_SlaveStation[hfds][hchan].strPN);
									pFWnd->m_wndResourceView3.B_change = TRUE;
//					pFWnd->m_wndResourceView3.InitFBA(3);
                    pFWnd->paneResourceView3->Select();
//									theApp.idis =3;
								}
						 }
						 else
						 {
						        m_ABFlist[ffds][fchan].fchan =1;
								if(m_ABFlist[hfds][hchan].fchan == 0)
								{
									m_ABFlist[hfds][hchan].fchan =1;
									pFWnd->m_wndResourceView5.m_cpstr.push_back(m_SlaveStation[hfds][hchan].strPN);
									pFWnd->m_wndResourceView5.B_change = TRUE;
//					pFWnd->m_wndResourceView5.InitFBA(5);
                    pFWnd->paneResourceView5->Select();
//									theApp.idis =5;
								}
						 }
					 }
					 else if(dvalue ==1)
					 {
						 m_SlaveStation[ffds][fchan].FeedState ="正常";
						 if(ufData6 <3)
						 {
    						 m_ABFlist[ffds][fchan].cchan =0;
//					pFWnd->m_wndResourceView3.InitFBA(3);
//									theApp.idis =3;
						 }
						 else
						 {
    						 m_ABFlist[ffds][fchan].fchan =0;
//					pFWnd->m_wndResourceView5.InitFBA(5);
//									theApp.idis =5;
						 }
					 }
					 m_SlaveStation[hfds][hchan].m_ffds = ffds;
					 m_SlaveStation[hfds][hchan].m_fchan =fchan;
	         		int ufData4 = m_SlaveStation[hfds][hchan].Adjust_state;
	          		if(ufData4 == 1)
		      			SyncCRTData(hfds,hchan,3);     //adjustdata
	        		else
	     	      		SyncCRTData(hfds,hchan,2);     //rtdata 馈电
				 }
				m_ADMainDis[ffds][fchan].RTime = COleDateTime::GetCurrentTime();
			 }
	}
	int n_newfeed = m_SlaveStation[hfds][hchan].m_second;
	if(n_oldfeed == n_newfeed)
		m_SlaveStation[hfds][hchan].m_second =0;
	else
		m_SlaveStation[hfds][hchan].m_second =n_oldfeed+1;
}
//断电器 开关量
void CRTDataManage::handbr(unsigned char  hfds, unsigned char  hchan, unsigned char hbr)
{
//    CMainFrame* pFWnd=(CMainFrame*)AfxGetMainWnd();
	unsigned char cfds,cchan  ,nfds,nchan;
	for(int i= 0 ;i<64 ; i++)
	{
		     cfds = m_ADCbreakE[hfds][hchan][i].bFSd;
			 cchan = m_ADCbreakE[hfds][hchan][i].bchanel;
			 if(cfds == 0)
				 break;
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
    					theApp.Sync(message1,1);
//                         pFWnd->m_wndResourceView.InitLC(cfds,cchan+16);
						}
					}
					else
					{
//			CString strtemp;
    						bool isret = false;
						//只有控制通道关联的所有AD为正常，复电,不对本分站复电
						for(int j= 0 ;j<64 ; j++)
						{
							nfds = m_ADCbreakE[cfds][cchan+16][j].bFSd;
							nchan = m_ADCbreakE[cfds][cchan+16][j].bchanel;
							if(!((nfds >0) && (nchan >0)))
                     				 break;
							if(m_SlaveStation[nfds][nchan].Channel_state == 0x00)
							{
								if(cfds != nfds)
		    						isret = true;
							}
							else
							{
								isret = false;
								break;
							}
						}//for(int j= 0 ;j<64 ; j++)
	    					if(isret)
							{
    	CNDKMessage message1(AUTOCONTROL);
					message1.Add(m_ndkSend1 ,6);
					theApp.Sync(message1,1);
//                         pFWnd->m_wndResourceView.InitLC(cfds,cchan+16);
							}
					}//else
	}
}

void CRTDataManage::SyncCRTData(unsigned char  afds, unsigned char  achan,int dbtype)
{
	if(!theApp.m_bLogIn || !theApp.b_SaveRT)
		return;

	CString str1,str2,str3,str4,strSQL;  str2="";
    unsigned char  uc3,uc4;
	int m_nptype = m_SlaveStation[afds][achan].ptype;
	COleDateTime timec = m_SlaveStation[afds][achan].ValueTime;
	str1 = timec.Format("%Y-%m-%d %H:%M:%S");
    if(timec.GetDay() >27)
			ConnectDB();
	if(dbtype != 10 )
	{
//	    	AfxMessageBox(szConnect); 
//    	str1.Format("%d-%d-%d %d:%d:%d",eyear,ufData2,ufData3,ufData4,ufData5,ufData6);
	    //uc5 =m_SlaveStation[afds][achan].Channel_state;//	m_RealtimedataNew->m_szADStatus = ufData1;
	    //str2 = theApp.curuser; //m_RealtimedataNew->m_szUseridadd
		if(dbtype == 0 || dbtype == 1)
		{
    		str3 = "";  //m_szsafemtext
		    uc3 = 0;    //m_szffds
		    uc4 = 0;    //m_szfchan
		    str4 = "";  //m_szFeedStatus
		}
		else if(dbtype == 2 || dbtype == 3)
		{
    		str3 = m_SlaveStation[afds][achan].strSafe;  //m_szsafemtext
		    uc3 = m_SlaveStation[afds][achan].m_ffds;    //m_szffds
		    uc4 = m_SlaveStation[afds][achan].m_fchan;    //m_szfchan
		    str4 = m_SlaveStation[uc3][uc4].FeedState;  //m_szFeedStatus
		}
		else if(dbtype == 4 || dbtype == 5)
		{
    		str3 = "";  //m_szsafemtext
		    uc3 = 0;    //m_szffds
		    uc4 = 0;    //m_szfchan
		    str4 = m_SlaveStation[afds][achan].FeedState;  //m_szFeedStatus
		}
		if(dbtype == 0 || dbtype == 2 || dbtype == 4)
			str2 = strdbname;
		else if(dbtype == 1 || dbtype == 3 || dbtype == 5)
			str2 = "rtadjustdata";
    	strSQL.Format("INSERT INTO %s (PID,ptype,fds,chan,CDValue,AValue,ADStatus,recdate,Useridadd,safemtext,ffds,fchan,FeedStatus) VALUES(%d,%d,%d,%d,%d,%.2f,%d,'%s','%s','%s',%d,%d,'%s')"
    		,str2,m_SlaveStation[afds][achan].m_PID,m_nptype,afds,achan
			,m_SlaveStation[afds][achan].CValue,m_SlaveStation[afds][achan].AValue
			,m_SlaveStation[afds][achan].Channel_state,str1,theApp.curuser,str3,uc3,uc4,str4);
//     	theApp.m_pConnection->Execute(_bstr_t(strSQL),NULL,adCmdText);
	}
	else if(dbtype == 10 )
	{
			str2 = "rt5mdata";
			float av= m_SlaveStation[afds][achan].m5_ATotalValue/m_SlaveStation[afds][achan].m5_Atotal;
    	strSQL.Format("INSERT INTO %s (PID,ptype,fds,chan,AMinValue,AValue,ADStatus,recdate,Useridadd,AMaxValue) VALUES(%d,%d,%d,%d,%.2f,%.2f,%d,'%s','%s',%.2f)"
	    	,str2,m_SlaveStation[afds][achan].m_PID,m_nptype,afds,achan
			,m_SlaveStation[afds][achan].m5_AMinValue,av,m_SlaveStation[afds][achan].Channel_state
			,str1,theApp.curuser,m_SlaveStation[afds][achan].m5_AMaxValue);
//    	theApp.m_pConnection->Execute(_bstr_t(strSQL),NULL,adCmdText);
	}
	if(theApp.fidis == 0)
	{
    	theApp.bidis++;
    	strRTData1[theApp.bidis] =strSQL;
	}
	else if(theApp.fidis == 1)
	{
    	theApp.bidis++;
    	strRTData2[theApp.bidis] =strSQL;
	}
}

void CRTDataManage::SendPP(unsigned char  afds)
{
    CMainFrame* pFWnd=(CMainFrame*)AfxGetMainWnd();
	CString strim2;
		            m_ndkSend2[0] = 0x7E;
		            m_ndkSend2[1] = afds;
		            m_ndkSend2[2] = 0x43;
					strim2.Format("%x|%x|%x",m_ndkSend2[0],m_ndkSend2[1],m_ndkSend2[2]);
//       g_Log.StatusOut("配置测点：" + strim2 );
        if(pFWnd->m_pSetTimeDlg != NULL)
				pFWnd->m_pSetTimeDlg->ComDisMes(strim2);

        for(int i=1;i<17 ;i++)
		{
		            m_ndkSend2[i*10-7] = m_SlaveStation[afds][i].RangeH8;
		            m_ndkSend2[i*10-6] = m_SlaveStation[afds][i].RangeL8;      //
		            m_ndkSend2[i*10-5] = m_SlaveStation[afds][i].AValueH8;
		            m_ndkSend2[i*10-4] = m_SlaveStation[afds][i].AValueL8;      //
		            m_ndkSend2[i*10-3] = m_SlaveStation[afds][i].ApbrkH8;
		            m_ndkSend2[i*10-2] = m_SlaveStation[afds][i].ApbrkL8;      //
		            m_ndkSend2[i*10-1] = m_SlaveStation[afds][i].AprtnH8;
		            m_ndkSend2[i*10] = m_SlaveStation[afds][i].AprtnL8;     //
		            m_ndkSend2[i*10+1] = m_SlaveStation[afds][i].Control_state;
		            m_ndkSend2[i*10+2] = m_SlaveStation[afds][i].Channel8;      //

			strim2.Format("%x|%x|%x|%x|%x|%x|%x|%x|%x|%x    %d|%d|%d|%d|%d|%d|%d|%d|%d|%d",m_ndkSend2[i*10-7],m_ndkSend2[i*10-6],m_ndkSend2[i*10-5],m_ndkSend2[i*10-4],m_ndkSend2[i*10-3],m_ndkSend2[i*10-2],m_ndkSend2[i*10-1],
				m_ndkSend2[i*10],m_ndkSend2[i*10+1],m_ndkSend2[i*10+2],
				m_ndkSend2[i*10-7],m_ndkSend2[i*10-6],m_ndkSend2[i*10-5],m_ndkSend2[i*10-4],m_ndkSend2[i*10-3],m_ndkSend2[i*10-2],m_ndkSend2[i*10-1],
				m_ndkSend2[i*10],m_ndkSend2[i*10+1],m_ndkSend2[i*10+2]);
        if(pFWnd->m_pSetTimeDlg != NULL)
				pFWnd->m_pSetTimeDlg->ComDisMes(strim2);
//       g_Log.StatusOut("配置测点：" + strim2 );
//			strim1 +=strim2;
		}
		            m_ndkSend2[163] = m_SlaveStation[afds][0].RangeH8;      //控制量类型
		            m_ndkSend2[164] = m_SlaveStation[afds][0].RangeL8;      //
		            m_ndkSend2[165] = 0x21;      //
					strim2.Format("%x|%x|%x",m_ndkSend2[163],m_ndkSend2[164],m_ndkSend2[165]);
    	CNDKMessage message1(SENDCONFIG);
					message1.Add(m_ndkSend2 , 200);
					theApp.Sync(message1,1);
        if(pFWnd->m_pSetTimeDlg != NULL)
				pFWnd->m_pSetTimeDlg->ComDisMes(strim2);
		strim2.Format("配置%d号分站测点。",afds);
       g_Log.StatusOut( strim2 );
}

CString CRTDataManage::strstatus(unsigned char ustatus)
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
		str = "ERROR";
	else if((ustatus == 0x90))
		str = "分站故障";
	else if((ustatus == 0xa0))
		str = "网络故障";
	else if((ustatus == 0xa1))
		str = "没有巡检";
	else 
		str = "";
	return  str;
}

void CRTDataManage::CalTime(COleDateTime time)
{
}
/*
void CRTDataManage::CalRTdata(int fds)
{
	theApp.b_startc = FALSE;
	m_nodialog = FALSE;
    CMainFrame* pFWnd=(CMainFrame*)AfxGetMainWnd();
	CString2DataType m_Str2Data;
//	float    dfOld , fMin ,fMax ; 
	unsigned char  n_cdata;
	CString strtemp,strtemp1,strtemp2,strtemp3,strtemp4,strtemp5,strtemp6,strtime2;
    unsigned char  nstation ,nbegin ,ufData,ufData1,ufData4,ufData5,ufData6;
	int ndata,olddata;
	bool b5m,bhour,bhalf;
	b5m = false;    	bhour = false;  	bhalf = false;
	float f_ch,f_limit,f_curch;

	nstation = m_ndkSend[fds][1];//fds;
	CTime t = CTime::GetCurrentTime();
//	m_ndkRTD[0] = t.GetYear()-2000;
//	m_ndkRTD[1] = t.GetMonth();
//	m_ndkRTD[2] = t.GetDay();
//	m_ndkRTD[3] = t.GetHour();
//	m_ndkRTD[4] = t.GetMinute();
//	m_ndkRTD[5] = t.GetSecond();
//	COleDateTime told;
//	COleDateTimeSpan olespan(0,0,0,2);
	COleDateTime timetemp = COleDateTime::GetCurrentTime();
//	COleDateTime timetemp1 = timetemp-olespan;
//	strtemp = timetemp.Format(_T("%Y-%m-%d %H:%M:%S"));
//	strtemp = timetemp1.Format(_T("%Y-%m-%d %H:%M:%S"));
//	strtemp.Format(_T("20%x-%x-%x %x:%x:%x"), ufData1,ufData2,ufData3,ufData4,ufData5,ufData6);
    strtime2   =   timetemp.Format(_T("%Y-%m-%d %H:%M:%S")); 

	unsigned char nItem =1;
	for(int i=3 ; i< 34 ;i=i+2)     //3,4 1     33,34 16
	{
		if(m_SlaveStation[nstation][nItem].WatchName != "")
		{
	    	ufData6 = m_SlaveStation[nstation][nItem].ptype;
//    	    message.GetAt(i, ufData);
			ufData =  m_ndkSend[nstation][i];
			ufData1 = ufData & 0xf0;
			ufData5 = m_SlaveStation[nstation][nItem].Channel_state;//old
//    	    message.GetAt(i+1, n_cdata);
			n_cdata = m_ndkSend[nstation][i+1];
			ndata = (ufData & 0x0f)*256 +n_cdata;
			ufData4 = m_SlaveStation[nstation][nItem].Adjust_state;

//			told = m_SlaveStation[nstation][nItem].ValueTime;
//        	CTime t1(told.GetYear(),told.GetMonth(),told.GetDay(),told.GetHour(),told.GetMinute(),told.GetSecond());
//			if((t.GetTime()-t1.GetTime())>1800 )   //1800
//				bhalf = true;
			if(ufData4 == 1)
				m_AFans[nstation][nItem].ffds++;
			else
				m_AFans[nstation][nItem].ffds = 0;
			int m_Adjust  = m_AFans[nstation][nItem].ffds; //存标校第一个值

			int m_two ;
			if(ufData1 != ufData5)
				m_SlaveStation[nstation][nItem].m_second =0;
			m_two = m_SlaveStation[nstation][nItem].m_second;
			olddata = m_SlaveStation[nstation][nItem].CValue;
//	strtemp.Format(_T("%.2f |%d"),m_SlaveStation[nstation][nItem].AValue,m_SlaveStation[nstation][nItem].CValue);
			if(ufData6 < 3 )
			{
//	strtemp.Format(_T("%.2f |%d |%d |%d |%.2f |%.2f |%d"),f_curch,olddata,ndata,nItem
//		,f_ch,f_limit,ufData6);
//                g_Log.StatusOut(strtemp);
    		    m_SlaveStation[nstation][nItem].Channel_state = ufData1;
	             			if(ufData6 == 0 && ndata !=olddata)
							{
								//数据变化在区间内不存如1%
//								f_oldch = m_SlaveStation[nstation][nItem].AValue;
//	     		    			m_SlaveStation[nstation][nItem].CValue = ndata;
	                			f_ch=0;    f_limit=0;	f_curch=0;
	    	        			f_curch = (m_SlaveStation[nstation][nItem].m_RangeH-m_SlaveStation[nstation][nItem].m_RangeL)*(ndata-300)/1200;
//	             				m_SlaveStation[nstation][nItem].pnValue = (ndata-300)/12;
								f_ch = fabs(f_curch - m_SlaveStation[nstation][nItem].AValue);//
								if(f_curch<10)			f_limit = 0.009;
								else if(f_curch<100)	f_limit = 0.09;
								else if(f_curch<1000)	f_limit = 1;
								else if(f_curch<10000)	f_limit = 10;
								if(f_ch > f_limit && f_curch>0 && f_curch<=m_SlaveStation[nstation][nItem].m_RangeH)
								{
									if(m_SlaveStation[nstation][nItem].AlarmState ==0)
									{
//	strtemp.Format(_T("%.2f |%.2f |%d |%d |%.2f |%.2f |%d"),f_curch,m_SlaveStation[nstation][nItem].AValue,ndata,nItem
//		,f_ch,f_limit,m_SlaveStation[nstation][nItem].AlarmState);
//                g_Log.StatusOut(strtemp);
	     		    			m_SlaveStation[nstation][nItem].CValue = ndata;
	    	        			m_SlaveStation[nstation][nItem].AValue = f_curch;
	             				m_SlaveStation[nstation][nItem].pnValue = (ndata-300)/12;
								m_SlaveStation[nstation][nItem].AlarmState =121;
									}
								}
							}
		         			else if(ufData6 == 1 && ndata !=olddata)
							{
	                			f_ch=0;    f_limit=0;	f_curch=0;
		         				f_curch = (m_SlaveStation[nstation][nItem].m_RangeH-m_SlaveStation[nstation][nItem].m_RangeL)*(ndata-200)/800;
								f_ch = fabs(f_curch - m_SlaveStation[nstation][nItem].AValue);
								if(f_curch<10)   			f_limit = 0.009;
								else if(f_curch<100)		f_limit = 0.09;
								else if(f_curch<1000)		f_limit = 1;
								else if(f_curch<10000)		f_limit = 10;
								if(f_ch > f_limit && f_curch>0 && f_curch<=m_SlaveStation[nstation][nItem].m_RangeH)
								{
									if(m_SlaveStation[nstation][nItem].AlarmState ==0)
									{
//	strtemp.Format(_T("%.2f |%.2f |%d |%d |%.2f |%.2f |%d"),f_curch,m_SlaveStation[nstation][nItem].AValue,ndata,nItem
//		,f_ch,f_limit,m_SlaveStation[nstation][nItem].AlarmState);
//                g_Log.StatusOut(strtemp);
	    		    			m_SlaveStation[nstation][nItem].CValue = ndata;
	             				m_SlaveStation[nstation][nItem].pnValue = (ndata-200)/8;
		         				m_SlaveStation[nstation][nItem].AValue = f_curch;
								m_SlaveStation[nstation][nItem].AlarmState =121;
									}
								}
							}
		         			else if(ufData6 == 2 && ndata !=olddata)
							{
	                			f_ch=0;    f_limit=0;	f_curch=0;
//								f_ch = m_SlaveStation[nstation][nItem].AValue;
								int k =m_SlaveStation[nstation][nItem].AValue/4096;
								if(m_SlaveStation[nstation][nItem].AValue <m_SlaveStation[nstation][nItem].m_RangeH)
								{
		     						if(olddata > ndata)
				    					f_curch =4096*(k+1)+ndata;
				    				else
				      					f_curch =4096*k +ndata;
								}
								else
								{
				    					f_curch = ndata;
								}
								f_ch = fabs(f_curch - m_SlaveStation[nstation][nItem].AValue);
								if(f_curch<1000)				f_limit = 0.9;
								else if(f_curch<10000)			f_limit = 9;
								if(f_ch > f_limit && f_curch>0 ) //&& ndata !=olddata
								{
									if(m_SlaveStation[nstation][nItem].AlarmState ==0)
									{
	    		        	    		m_SlaveStation[nstation][nItem].CValue = ndata;
	                				m_SlaveStation[nstation][nItem].pnValue = m_SlaveStation[nstation][nItem].AValue/m_SlaveStation[nstation][nItem].m_RangeH*100;
				    					m_SlaveStation[nstation][nItem].AValue = f_curch;
										m_SlaveStation[nstation][nItem].AlarmState =121;
									}
								}
							}
                 if(m_SlaveStation[nstation][nItem].AlarmState ==121 || m_two>0 ||m_Adjust==1)
//                 if((olddata != ndata)|| bhalf||m_two>0)
				 {
         							m_SlaveStation[nstation][nItem].ValueTime = timetemp;
          							if(ufData4 == 1 )//调校//adjustdata
									{
	     								theApp.SocketServer.SyncCRTData(nstation,nItem,1);
									}
									else if(m_SlaveStation[nstation][nItem].AlarmState ==121)
									{
//	strtemp.Format(_T("%.2f |%.2f |%d |%d |%.2f |%.2f |%d"),f_curch,m_SlaveStation[nstation][nItem].AValue,m_SlaveStation[nstation][nItem].CValue,nItem
//		,f_ch,f_limit,m_SlaveStation[nstation][nItem].AlarmState);
//                g_Log.StatusOut(strtemp);
										m_SlaveStation[nstation][nItem].AlarmState =0;
	     	    		    				theApp.SocketServer.SyncCRTData(nstation,nItem,0); 
									if(theApp.b_5m)
									{
                            CString dddd ;
					  	  dddd.Format("%.2f%s",m_SlaveStation[nstation][nItem].AValue,m_SlaveStation[nstation][nItem].m_Unit);
//									theApp.m_RTData.push_back(DCHm5(m_SlaveStation[nstation][nItem].WatchName,
//										m_SlaveStation[nstation][nItem].strPN, dddd,strtime2));
									}

										float fcurv =m_SlaveStation[nstation][nItem].AValue;
										//5m
										if(m_SlaveStation[nstation][nItem].m5_AMaxValue<fcurv)
											m_SlaveStation[nstation][nItem].m5_AMaxValue = fcurv;
										if(m_SlaveStation[nstation][nItem].m5_AMinValue>fcurv)
											m_SlaveStation[nstation][nItem].m5_AMinValue = fcurv;
										m_SlaveStation[nstation][nItem].m5_Atotal++;
										m_SlaveStation[nstation][nItem].m5_ATotalValue +=fcurv;

										//24h
										if(m_SlaveStation[nstation][nItem].m24_AMaxValue<fcurv)
											m_SlaveStation[nstation][nItem].m24_AMaxValue = fcurv;
										if(m_SlaveStation[nstation][nItem].m24_AMinValue>fcurv)
											m_SlaveStation[nstation][nItem].m24_AMinValue = fcurv;
										m_SlaveStation[nstation][nItem].m24_Atotal++;
										m_SlaveStation[nstation][nItem].m24_ATotalValue +=fcurv;

//										CTime vt(2000+m_ndkRTD[0],m_ndkRTD[1],m_ndkRTD[2],m_ndkRTD[3],m_ndkRTD[4],m_ndkRTD[5]);
										CTime m5minute = m_SlaveStation[nstation][nItem].m5_T;
//										if(vt.GetTime()-m5minute.GetTime() >=300) //5分钟
										{
	        								theApp.SocketServer.SyncCRTData(nstation,nItem,10); 
//											m_SlaveStation[nstation][nItem].m5_T = vt;
											m_SlaveStation[nstation][nItem].m5_AMaxValue=fcurv;
											m_SlaveStation[nstation][nItem].m5_AMinValue=fcurv;
											m_SlaveStation[nstation][nItem].m5_Atotal=0;
											m_SlaveStation[nstation][nItem].m5_ATotalValue=0;
										}
									}
									//调用显示最大值、平均值
									if(m_ADMainDis[nstation][nItem].AMaxValue < m_SlaveStation[nstation][nItem].AValue)
										m_ADMainDis[nstation][nItem].AMaxValue = m_SlaveStation[nstation][nItem].AValue;
									m_ADMainDis[nstation][nItem].m_ATotalnum++;
									m_ADMainDis[nstation][nItem].ATotalV += m_SlaveStation[nstation][nItem].AValue;

					if(ufData1 == 0x00)
					{
						//报警后不用复电
						if(((ufData5 != 0x10)&&(ufData1 != ufData5)&&(ufData5 !=255)) || m_two >0)
						{
	    						if(m_two >0)
								{
     					     		Savefeedbr(nstation,nItem);  //馈电状态
 	    							m_SlaveStation[nstation][nItem].m_second =0;
//								 pFWnd->m_wndResourceView3.InitAF(nstation,nItem);
								}
							if(m_two ==0)
							{
 								m_SlaveStation[nstation][nItem].m_second++;
    		      				m_ADMainDis[nstation][nItem].NTime = timetemp;
    			    				handbr(nstation,nItem,0);
							}
						}
						if(ufData5 == 0x10)
						{
						}
					}//ufData1 == 0x00
					if(ufData1 == 0x10)
					{
                            if(pFWnd->m_RepeatFlag)
	    						pFWnd->DoPlayWarnSound(m_SlaveStation[nstation][nItem].falma);
						if(ufData5 != 0x10 )
						{
                            	pFWnd->m_RepeatFlag = TRUE;
								m_ADMainDis[nstation][nItem].ATime = timetemp;
//								 pFWnd->m_wndResourceView.InitAA(nstation,nItem);
						}
//						m_SlaveStation[nstation][nItem].m_second++;
					}//ufData1 == 0x10)
					if(ufData1 == 0x20)
					{
                            if(pFWnd->m_RepeatFlag)
	    						pFWnd->DoPlayWarnSound(m_SlaveStation[nstation][nItem].falma);
						if(ufData5 != 0x20 || m_two>0)
						{
                            	pFWnd->m_RepeatFlag = TRUE;
	    						if(m_two >0)
								{
     					     		Savefeedbr(nstation,nItem);  //馈电状态
							    	m_SlaveStation[nstation][nItem].m_second = 0;
//						    		 pFWnd->m_wndResourceView2.InitAB(nstation,nItem);
//						    		 pFWnd->m_wndResourceView3.InitAF(nstation,nItem);
								}
							if(m_two ==0)
							{
								m_SlaveStation[nstation][nItem].m_second++;
     							handbr(nstation,nItem,1);
    							m_ADMainDis[nstation][nItem].BTime = timetemp;
							}
						}
					}//ufData1 == 0x20)
					if((ufData1 == 0x40)|| (ufData1 == 0x50)  || (ufData1 == 0x60) || ufData1 == 0x70 ||ufData1 == 0x80)
					{
//							if(ufData1 != 0x60)
							{
//		    					m_SlaveStation[nstation][nItem].CValue = 0;
//                				m_SlaveStation[nstation][nItem].pnValue = 0;
//	    						m_SlaveStation[nstation][nItem].AValue = 0;
							}
                            if(pFWnd->m_RepeatFlag)
	    						pFWnd->DoPlayWarnSound(m_SlaveStation[nstation][nItem].falma);
						//第二次断电确认
						if(ufData5 != ufData1 || m_two >0) 
						{
				     			//0通道故障闭锁使能
							if(m_SlaveStation[nstation][0].AlarmState ==1)
							{
                            	pFWnd->m_RepeatFlag = TRUE;
	    						if(m_two >0)
								{
     					     		Savefeedbr(nstation,nItem);  //馈电状态
					    			m_SlaveStation[nstation][nItem].m_second = 0;
//						    		 pFWnd->m_wndResourceView2.InitAB(nstation,nItem);
//						    		 pFWnd->m_wndResourceView3.InitAF(nstation,nItem);
								}
	    						if(m_two ==0)
								{
					    			m_SlaveStation[nstation][nItem].m_second++;
            						m_ADMainDis[nstation][nItem].BTime = timetemp;
      					    		handbr(nstation,nItem,1);
								}
							}
						}
					}//ufData1 == 0x40)|| (ufData1 == 0x50)  || (ufData1 == 0x60
				 }//olddata != ndata)|| bhalf||m_two==1
	//				strtemp1.Format(_T("%.2f"), m_SlaveStation[nstation][nItem].AValue);
			}
			else if(ufData6 >9)
			{
        		    m_SlaveStation[nstation][nItem].Channel_state = ufData1;
//					m_SlaveStation[nstation][nItem].CValue = n_cdata;
//					int m_two = m_SlaveStation[nstation][nItem].m_second;
					if(olddata != n_cdata || (m_two >0) ||m_Adjust==1)
					{
	    				if((ufData1 == 0x00)||(ufData1 == 0x10)||(ufData1 == 0x20)||(ufData1 == 0x70)||(ufData1 == 0x80))
						{
							if(olddata != n_cdata)//故障时数据不变
							{
                        		    m_SlaveStation[nstation][nItem].ValueTime = timetemp;
//                        		    m_SlaveStation[nstation][nItem].Channel_state = ufData1;
	                				m_SlaveStation[nstation][nItem].CValue = n_cdata;
                					m_SlaveStation[nstation][nItem].AValue = n_cdata;
          							if(ufData4 == 1)//调校//adjustdata
	     								theApp.SocketServer.SyncCRTData(nstation,nItem,1); 
									else
	     					    		theApp.SocketServer.SyncCRTData(nstation,nItem,0);
//    	    						pFWnd->m_wndResourceView6.InitLDCH(nstation,nItem);
									if(theApp.b_5m)
									{
                      CString dddd,strtime1 ;
					  if(n_cdata == 0)
						  dddd= m_SlaveStation[nstation][nItem].ZeroState;
					  else if(n_cdata == 1)
						  dddd= m_SlaveStation[nstation][nItem].OneState;
					  else if(n_cdata == 2)
						  dddd= m_SlaveStation[nstation][nItem].TwoState;
						  strtime1 = m_SlaveStation[nstation][nItem].strPN;
									theApp.m_RDCHm5.push_back(DCHm5(m_SlaveStation[nstation][nItem].WatchName,
										strtime1, dddd,strtime2));
//									theApp.m_RTData.push_back(DCHm5(m_SlaveStation[nstation][nItem].WatchName,
//										strtime1, dddd,strtime2));
									}
							}
						}
	    				if(ufData1 == 0x00)
						{
							//报警后不用复电
							if(((ufData5 != 0x10)&&(ufData1 != ufData5)&&(ufData5 !=255)) || (m_two>0))
							{
	    						if(m_two >0)
								{
     					     		Savefeedbr(nstation,nItem);  //馈电状态
    	    						m_SlaveStation[nstation][nItem].m_second = 0;
								}
		    	    			int m_sleep = m_two%60;
								if(m_two ==0)
								{
    	    						m_SlaveStation[nstation][nItem].m_second++;
            						m_ADMainDis[nstation][nItem].NTime = timetemp;
			    						handbr(nstation,nItem,0);
								}
//								else if(m_sleep ==1)
//        							 pFWnd->m_wndResourceView5.InitDF(nstation,nItem);
							}
						}//ufData1 == 0x00)
						if(ufData1 == 0x10)
						{
                            if(pFWnd->m_RepeatFlag)
	    						pFWnd->DoPlayWarnSound(m_SlaveStation[nstation][nItem].falma);
//			    			int m_sleep = m_two%55;
							if(ufData5 != 0x10 )
							{
                            	pFWnd->m_RepeatFlag = TRUE;
									m_ADMainDis[nstation][nItem].ATime = timetemp;
//  								 pFWnd->m_wndResourceView4.InitDAB(nstation,nItem);
							}
//    							m_SlaveStation[nstation][nItem].m_second++;
						}
						if(ufData1 == 0x20)
						{
                            if(pFWnd->m_RepeatFlag)
	    						pFWnd->DoPlayWarnSound(m_SlaveStation[nstation][nItem].falma);
							if(ufData5 != 0x20 || m_two>0)
							{
                            	pFWnd->m_RepeatFlag = TRUE;
	    						if(m_two >0)
								{
     					     		Savefeedbr(nstation,nItem);  //馈电状态
    									m_SlaveStation[nstation][nItem].m_second = 0;
//									 pFWnd->m_wndResourceView4.InitDAB(nstation,nItem);
//									 pFWnd->m_wndResourceView5.InitDF(nstation,nItem);
								}
								if(m_two ==0)
								{
    									m_SlaveStation[nstation][nItem].m_second++;
    								m_ADMainDis[nstation][nItem].BTime = timetemp;
         								handbr(nstation,nItem,1);
								}
							}
						}//ufData1 == 0x20
						if((ufData1 == 0x70) ||(ufData1 == 0x80))
						{
                            if(pFWnd->m_RepeatFlag)
	    						pFWnd->DoPlayWarnSound(m_SlaveStation[nstation][nItem].falma);
				     		//第二次断电确认
		      				if((ufData5 != ufData1) || (m_two >0))
							{
				     			if(m_SlaveStation[nstation][0].AlarmState ==1)
								{
                                	pFWnd->m_RepeatFlag = TRUE;
	    	    					if(m_two >0)
									{
     				    	     		Savefeedbr(nstation,nItem);  //馈电状态
    									m_SlaveStation[nstation][nItem].m_second = 0;
//									 pFWnd->m_wndResourceView4.InitDAB(nstation,nItem);
//									 pFWnd->m_wndResourceView5.InitDF(nstation,nItem);
									}
	    				     		if(m_two ==0)
									{
       									m_SlaveStation[nstation][nItem].m_second++;
	    					        	m_ADMainDis[nstation][nItem].BTime = timetemp;
        					    		handbr(nstation,nItem,1);
									}
								}
							}
						}//ufData1 == 0x70
					}//olddata != n_cdata || (m_two >0))
					m_two = m_AFans[nstation][nItem].fchan;
						if(m_AFans[nstation][nItem].cfds != 0)  //双风门主扇备扇报警
						{
                            if(pFWnd->m_RepeatFlag)
	    						pFWnd->DoPlayWarnSound(m_SlaveStation[nstation][nItem].falma);
                    	    	int cnfds = m_AFans[nstation][nItem].cfds;
                      	    	int cnchan = m_AFans[nstation][nItem].cchan;
								int n_fans = m_AFans[nstation][nItem].SFSd;
								int n_value = m_SlaveStation[nstation][nItem].CValue;
								int cn_value = m_SlaveStation[cnfds][cnchan].CValue;
//			    			int m_sleep = m_two%55;
							if(n_value == n_fans && cn_value == n_fans && m_two==0)
							{
                            	pFWnd->m_RepeatFlag = TRUE;
									m_ADMainDis[nstation][nItem].ATime = timetemp;
//  								 pFWnd->m_wndResourceView4.InitDAB(nstation,nItem);
								 m_AFans[nstation][nItem].fchan++;
							}
							else if(n_value != n_fans || cn_value != n_fans)
								 m_AFans[nstation][nItem].fchan =0;
//    							m_SlaveStation[nstation][nItem].m_second++;
						}//双风门主扇备扇报警

			}//>3
		}//if
		nItem++;
	}//for
//	message.GetAt(35, nbegin);    //控制量状态
	nbegin = m_ndkSend[nstation][35];
	for( i =17 ;i <MAX_CHAN ;i++)
	{
		if(i == 17)
    		ufData = nbegin & 0x01;
		else if(i == 18)
		{
    		ufData = nbegin & 0x02;
			if(ufData == 0)
				ufData =0;
			else
				ufData =1;
		}
		else if(i == 19)
		{
    		ufData = nbegin & 0x04;
			if(ufData == 0)
				ufData =0;
			else
				ufData =1;
		}
		else if(i == 20)
		{
    		ufData = nbegin & 0x08;
			if(ufData == 0)
				ufData =0;
			else
				ufData =1;
		}
		else if(i == 21)
		{
    		ufData = nbegin & 0x10;
			if(ufData == 0)
				ufData =0;
			else
				ufData =1;
		}
		else if(i == 22)
		{
    		ufData = nbegin & 0x20;
			if(ufData == 0)
				ufData =0;
			else
				ufData =1;
		}
		else if(i == 23)
		{
    		ufData = nbegin & 0x40;
			if(ufData == 0)
				ufData =0;
			else
				ufData =1;
		}
		else if(i == 24)
		{
    		ufData = nbegin & 0x80;
			if(ufData == 0)
				ufData =0;
			else
				ufData =1;
		}
//			told = m_SlaveStation[nstation][i].ValueTime;
//        	CTime t2(told.GetYear(),told.GetMonth(),told.GetDay(),told.GetHour(),told.GetMinute(),told.GetSecond());
//			if((t.GetTime()-t2.GetTime())>1800)
//				bhalf = true;

		if(m_SlaveStation[nstation][i].WatchName != "")
		{
    		//第二次断电确认
    		ufData4 = m_SlaveStation[nstation][i].Adjust_state;
			if(ufData4 == 1)
				m_SlaveStation[nstation][i].m_second++;
			else
				m_SlaveStation[nstation][i].m_second = 0;
            int m_two =m_SlaveStation[nstation][i].m_second;   //存标校第一个值
            m_SlaveStation[nstation][i].Channel_state = 0;
      		ufData1 = m_SlaveStation[nstation][i].CValue;
    		if((ufData1 != ufData) ||m_two==1)
			{
//		    	    m_SlaveStation[nstation][i].m_second++;
            	m_SlaveStation[nstation][i].AValue = ufData;
            	m_SlaveStation[nstation][i].CValue = ufData;
    			m_SlaveStation[nstation][i].ValueTime = timetemp;
    	    		if(ufData4 == 1)
			       		theApp.SocketServer.SyncCRTData(nstation,i,1);     //adjustdata
       	    		else
					{
						m_SlaveStation[nstation][i].m_second = 0;
	     	    		theApp.SocketServer.SyncCRTData(nstation,i,0);     //rtdata
 									if(theApp.b_5m)
									{
                     CString dddd,strtime1 ;
					  if(ufData == 0)
						  dddd= m_SlaveStation[nstation][i].ZeroState;
					  else if(ufData == 1)
						  dddd= m_SlaveStation[nstation][i].OneState;
					  else if(ufData == 2)
						  dddd= m_SlaveStation[nstation][i].TwoState;
						  strtime1 = m_SlaveStation[nstation][i].strPN;
									theApp.m_RDCHm5.push_back(DCHm5(m_SlaveStation[nstation][i].WatchName,
										strtime1, dddd,strtime2));
//									theApp.m_RTData.push_back(DCHm5(m_SlaveStation[nstation][i].WatchName,
//										strtime1, dddd,strtime2));
									}
					}
			}
		}
	}
	ufData = m_ndkSend[nstation][36];
//	message.GetAt(36, ufData);    //AC/DC+电池电压
	ufData =ufData & 0x10;
	if(ufData == 0x10)
		ufData =1;
	else
		ufData =0;
	if(ufData != m_SlaveStation[nstation][0].CValue)
	{
    	if(ufData == 0)
		{
    	m_SlaveStation[nstation][0].CValue = 0;
		m_SlaveStation[nstation][0].Channel_state = 0x00;
		}
    	else 
		{
    	m_SlaveStation[nstation][0].CValue = 1;
		m_SlaveStation[nstation][0].Channel_state = 0x10;
		}
    	m_SlaveStation[nstation][0].ValueTime = timetemp;
	    theApp.SocketServer.SyncCRTData(nstation,0,0);     //rtdata  theApp.SocketServer.
 									if(theApp.b_5m)
									{
                     CString dddd,strtime1 ;
					 dddd="";
					  if(ufData == 0)
						  dddd= m_SlaveStation[nstation][0].ZeroState;
					  else if(ufData == 1)
						  dddd= m_SlaveStation[nstation][0].OneState;
//					  else if(ufData == 2)
//						  dddd= m_SlaveStation[nstation][0].TwoState;
						  strtime1 = m_SlaveStation[nstation][0].strPN;
						theApp.m_RDCHm5.push_back(DCHm5(m_SlaveStation[nstation][0].WatchName,
										strtime1, dddd,strtime2));
//				    	theApp.m_RTData.push_back(DCHm5(m_SlaveStation[nstation][0].WatchName,
//										strtime1, dddd,strtime2));
									}
	}
    	if(ufData == 0)
		{
    	m_SlaveStation[nstation][0].CValue = 0;
		m_SlaveStation[nstation][0].Channel_state = 0x00;
		}
    	else if(ufData == 1)
		{
    	m_SlaveStation[nstation][0].CValue = 1;
		m_SlaveStation[nstation][0].Channel_state = 0x10;
		}
    	m_SlaveStation[nstation][0].ValueTime = timetemp;

//       CString dddd ;
//dddd.Format("%d %d %d %d %d %d",m_ndkSend[0],m_ndkSend[1],m_ndkSend[42],m_ndkSend[43],m_ndkSend[44],m_ndkSend[45]);
//       g_Log.StatusOut(dddd);

    m_nodialog = TRUE;
	theApp.b_startc = TRUE;
}
*/
//更新报警表
void CRTDataManage::DiaplayWarnTableC(unsigned short nPointNo)
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

void CRTDataManage::AddWarn( CString strtemp, CString strtemp1, CString strtemp2, CString strtemp3, CString strtemp4, CString strtemp5, CString strtemp6, CString strtemp7)
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

//    CMainFrame* pFWnd=(CMainFrame*)AfxGetMainWnd();
//    pFWnd->Msg(0,m_CStrWarn[0].strPoint , m_CStrWarn[0].strDate , m_CStrWarn[0].strText ,m_CStrWarn[0].strWarn ,m_CStrWarn[0].strTime);

}
//derror 数组数据越界 mbscmp.c - Compare MBCS strings
void CRTDataManage::CalRtDB(CTime time,int  &eYear, unsigned char  &eMonth)
{
	int m_h = m_SerialF[0].SFSd;
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

//连接数据库
void CRTDataManage::ConnectDB()
{
    	int eyear;	unsigned char emonth;
		CTime t=CTime::GetCurrentTime();
		CalRtDB(t , eyear , emonth);
		CString sztime;
		sztime.Format("%d",eyear);
		strdbname = "rt";
		strdbname += sztime;
   		sztime.Format("%02d",emonth);
		strdbname += sztime;
		strdbname += "data";
		n_month = emonth;
}
//分站通讯失败
void CRTDataManage::FCError(int nstation)
{
      for(int i = 0; i < MAX_CHAN;i++)
	  {
            unsigned char ufData4 = m_SlaveStation[nstation][i].Adjust_state;
		    m_SlaveStation[nstation][i].Channel_state =0x90;
			m_SlaveStation[nstation][i].ValueTime = COleDateTime::GetCurrentTime();
          	if(ufData4 == 1 )//调校//adjustdata
	     		 theApp.m_RTDM.SyncCRTData(nstation,i,1);
			else 
	     	     theApp.m_RTDM.SyncCRTData(nstation,i,0); 
            SaveRT24Data(nstation,i,24);
	  }
}
//网络故障恢复
void CRTDataManage::NCSuccess()
{
     for(int i = 1; i < MAX_FDS;i++)
	 {
          for(int j = 0; j < MAX_CHAN;j++)
		  {
	            m_SlaveStation[i][j].ValueTime = COleDateTime::GetCurrentTime();
                m_SlaveStation[i][j].Channel_state = m_ADMainDis[i][j].duant ;
		  }
	 }
}

//网络故障
void CRTDataManage::NCError()
{
          for(int j = 1; j < MAX_FDS;j++)
		  {
                for(int i = 0; i < MAX_CHAN;i++)
				{
			    	 m_SlaveStation[j][i].ValueTime = COleDateTime::GetCurrentTime();
					 m_ADMainDis[j][i].duant = m_SlaveStation[j][i].Channel_state;//保存上个状态
             		 m_SlaveStation[j][i].Channel_state = 0xa0;
                   	 unsigned char ufData4 = m_SlaveStation[j][i].Adjust_state;
                  	if(ufData4 == 1 )//调校//adjustdata
	     				SyncCRTData(j,i,1);
					else 
	     	    		SyncCRTData(j,i,0); 

				   	SaveRT24Data(j,i,24);
				}
		  }
}

//save rtdata memory db  m_RDCHm5
void CRTDataManage::SaveRT24Data(unsigned char  nstation, unsigned char  nItem,unsigned char  n524)
{
        CString dddd,strtime2,temp ;
        strtime2   =  CTime::GetCurrentTime().Format(_T("%Y-%m-%d %H:%M:%S")); 
   	    int nptype = m_SlaveStation[nstation][nItem].ptype;
	    if(nptype ==1 || nptype ==0)
    	dddd.Format("%.2f%s",m_SlaveStation[nstation][nItem].AValue,m_SlaveStation[nstation][nItem].m_Unit);
		else if(nptype ==2 )
       	  	  dddd.Format("%.0f%s",m_SlaveStation[nstation][nItem].AValue,m_SlaveStation[nstation][nItem].m_Unit);
   		else 
		{
								int ncvalue = m_SlaveStation[nstation][nItem].CValue;
								if(ncvalue ==0)
				        		  dddd= m_SlaveStation[nstation][nItem].ZeroState;
			            		else if(ncvalue == 1)
					        	  dddd= m_SlaveStation[nstation][nItem].OneState;
				         	    else if(ncvalue == 2)
				          		  dddd= m_SlaveStation[nstation][nItem].TwoState;
		}
	    unsigned char nstatus = m_SlaveStation[nstation][nItem].Channel_state;
		if((nstatus == 0x40)||(nstatus == 0x50)||(nstatus == 0x80)||(nstatus == 0x70)||(nstatus == 0x90)|| (nstatus == 0xa0) || (nstatus == 0xa1))
		      dddd= theApp.m_RTDM.strstatus(nstatus);

		if(n524 == 5)
			theApp.m_RDCHm5.push_back(DCHm5(m_SlaveStation[nstation][nItem].WatchName,
						m_SlaveStation[nstation][nItem].strPN, dddd,strtime2));
		else if(n524 == 24 && theApp.b_5m)
		{
    		temp.Format("insert into rtdata values(%d, %d, '%s','%s');",nstation,nItem,dddd,strtime2);
			if(theApp.m_resnum == 11)
    			m_Initdata.push_back(temp);
			else if(theApp.m_resnum == 13)
			{
				for(int i=0;i<m_Initdata.size();i++)
            		theApp.db3m.execDML(m_Initdata[i]);
				m_Initdata.clear();
        		theApp.db3m.execDML(temp);
				theApp.m_resnum =12;
			}
			else if(theApp.m_resnum == 12)
        		theApp.db3m.execDML(temp);
		}

}


void CRTDataManage::CalRTdata(int fds)
{
    CMainFrame* pFWnd=(CMainFrame*)AfxGetMainWnd();
	CString2DataType m_Str2Data;
//	float    dfOld , fMin ,fMax ; 
	unsigned char  n_cdata;
	CString strtemp,strtemp1,strtemp2,strtemp3,strtemp4,strtemp5,strtemp6,strtime2;
    unsigned char  nstation ,nbegin ,ufData,ufData1,ufData4,ufData5,ufData6;
	int ndata,olddata;
	bool b5m,bhour,bhalf;
	b5m = false;    	bhour = false;  	bhalf = false;
	float f_ch,f_limit,f_curch;

	nstation = fds;
//	COleDateTimeSpan olespan(0,0,0,2);
	COleDateTime timetemp = COleDateTime::GetCurrentTime();
//	COleDateTime timetemp1 = timetemp-olespan;
//	strtemp.Format(_T("20%x-%x-%x %x:%x:%x"), ufData1,ufData2,ufData3,ufData4,ufData5,ufData6);
    strtime2   =   timetemp.Format(_T("%Y-%m-%d %H:%M:%S")); 

	unsigned char nItem =1;
	for(int i=3 ; i< 34 ;i=i+2)     //3,4 1     33,34 16
	{
		if(m_SlaveStation[nstation][nItem].WatchName != "")
		{
	    	ufData6 = m_SlaveStation[nstation][nItem].ptype;
//    	    message.GetAt(i, ufData);
			ufData =  m_ndkSend[nstation][i];   //m_ndkSend[i];
//			ufData =  theApp.socketClient.m_ndkSend[i];
			ufData1 = ufData & 0xf0;  //current Channel_state
			ufData5 = m_SlaveStation[nstation][nItem].Channel_state;//old Channel_state
//    	    message.GetAt(i+1, n_cdata);
			n_cdata = m_ndkSend[nstation][i+1];
			ndata = (ufData & 0x0f)*256 +n_cdata;
			ufData4 = m_SlaveStation[nstation][nItem].Adjust_state;

			if(ufData4 == 1)
				m_AFans[nstation][nItem].ffds++;
			else
				m_AFans[nstation][nItem].ffds = 0;
			int m_Adjust  = m_AFans[nstation][nItem].ffds; //存标校第一个值

			int m_two ;
			if(ufData1 != ufData5)
				m_SlaveStation[nstation][nItem].m_second =0;
			m_two = m_SlaveStation[nstation][nItem].m_second;
			olddata = m_SlaveStation[nstation][nItem].CValue;
			if((ufData1 == 0x40)|| (ufData1 == 0x50) || ufData1 == 0x70 ||ufData1 == 0x80)
			{
				ndata = ufData1;//故障时，数据置为ufData1
				n_cdata = ufData1;
			}
			if(ufData6 < 3 )
			{
    		    m_SlaveStation[nstation][nItem].Channel_state = ufData1;
	             			if(ufData6 == 0 && ndata !=olddata)
							{
								//数据变化在区间内不存如1%
//								f_oldch = m_SlaveStation[nstation][nItem].AValue;
//	     		    			m_SlaveStation[nstation][nItem].CValue = ndata;
	                			f_ch=0;    f_limit=0;	f_curch=0;
								//当前值
	    	        			f_curch = (m_SlaveStation[nstation][nItem].m_RangeH-m_SlaveStation[nstation][nItem].m_RangeL)*(ndata-300)/1200;
//								f_ch = fabs(f_curch - m_SlaveStation[nstation][nItem].AValue);//
//								if(f_curch<10)			f_limit = 0.009;
//								else if(f_curch<100)	f_limit = 0.09;
//								else if(f_curch<1000)	f_limit = 1;
//								else if(f_curch<10000)	f_limit = 10;
//								if(f_ch > f_limit && f_curch>0 && f_curch<=m_SlaveStation[nstation][nItem].m_RangeH)
								{
									if(m_SlaveStation[nstation][nItem].AlarmState ==0)
									{
	     		    			m_SlaveStation[nstation][nItem].CValue = ndata;
	    	        			m_SlaveStation[nstation][nItem].AValue = f_curch;
	             				m_SlaveStation[nstation][nItem].pnValue = (ndata-300)/12;
								m_SlaveStation[nstation][nItem].AlarmState =121;
									}
								}
							}
		         			else if(ufData6 == 1 && ndata !=olddata)
							{
	                			f_ch=0;    f_limit=0;	f_curch=0;
		         				f_curch = (m_SlaveStation[nstation][nItem].m_RangeH-m_SlaveStation[nstation][nItem].m_RangeL)*(ndata-200)/800;
//								f_ch = fabs(f_curch - m_SlaveStation[nstation][nItem].AValue);
//								if(f_curch<10)   			f_limit = 0.009;
//								else if(f_curch<100)		f_limit = 0.09;
//								else if(f_curch<1000)		f_limit = 1;
//								else if(f_curch<10000)		f_limit = 10;
//								if(f_ch > f_limit && f_curch>0 && f_curch<=m_SlaveStation[nstation][nItem].m_RangeH)
								{
									if(m_SlaveStation[nstation][nItem].AlarmState ==0)
									{
//	strtemp.Format(_T("%.2f |%.2f |%d |%d |%.2f |%.2f |%d"),f_curch,m_SlaveStation[nstation][nItem].AValue,ndata,nItem
//		,f_ch,f_limit,m_SlaveStation[nstation][nItem].AlarmState);
//                g_Log.StatusOut(strtemp);
	    		    			m_SlaveStation[nstation][nItem].CValue = ndata;
	             				m_SlaveStation[nstation][nItem].pnValue = (ndata-200)/8;
		         				m_SlaveStation[nstation][nItem].AValue = f_curch;
								m_SlaveStation[nstation][nItem].AlarmState =121;
									}
								}
							}
		         			else if(ufData6 == 2 && ndata !=olddata)
							{
	                			f_ch=0;    f_limit=0;	f_curch=0;
//								f_ch = m_SlaveStation[nstation][nItem].AValue;
								int k =m_SlaveStation[nstation][nItem].AValue/4096;
								if(m_SlaveStation[nstation][nItem].AValue <m_SlaveStation[nstation][nItem].m_RangeH)
								{
		     						if(olddata > ndata)
				    					f_curch =4096*(k+1)+ndata;
				    				else
				      					f_curch =4096*k +ndata;
								}
								else
								{
				    					f_curch = ndata;
								}
//								f_ch = fabs(f_curch - m_SlaveStation[nstation][nItem].AValue);
//								if(f_curch<1000)				f_limit = 0.9;
//								else if(f_curch<10000)			f_limit = 9;
//								if(f_ch > f_limit && f_curch>0 ) //&& ndata !=olddata
								{
									if(m_SlaveStation[nstation][nItem].AlarmState ==0)
									{
	    		        	    		m_SlaveStation[nstation][nItem].CValue = ndata;
	                				m_SlaveStation[nstation][nItem].pnValue = m_SlaveStation[nstation][nItem].AValue/m_SlaveStation[nstation][nItem].m_RangeH*100;
				    					m_SlaveStation[nstation][nItem].AValue = f_curch;
										m_SlaveStation[nstation][nItem].AlarmState =121;
									}
								}
							}
                 if(m_SlaveStation[nstation][nItem].AlarmState ==121 || m_two>0 ||m_Adjust==1)
//                 if((olddata != ndata)|| bhalf||m_two>0)
				 {
         							m_SlaveStation[nstation][nItem].ValueTime = timetemp;
          							if(ufData4 == 1 )//调校//adjustdata
									{
	     								theApp.m_RTDM.SyncCRTData(nstation,nItem,1);
									}
									else if(m_SlaveStation[nstation][nItem].AlarmState ==121)
									{
										m_SlaveStation[nstation][nItem].AlarmState =0;
	     	    		    				theApp.m_RTDM.SyncCRTData(nstation,nItem,0); 
									if(theApp.b_5m)
    									theApp.m_RTDM.SaveRT24Data(nstation,nItem,24);

										float fcurv =m_SlaveStation[nstation][nItem].AValue;
										//5m
										if(m_SlaveStation[nstation][nItem].m5_AMaxValue<fcurv)
											m_SlaveStation[nstation][nItem].m5_AMaxValue = fcurv;
										if(m_SlaveStation[nstation][nItem].m5_AMinValue>fcurv)
											m_SlaveStation[nstation][nItem].m5_AMinValue = fcurv;
										m_SlaveStation[nstation][nItem].m5_Atotal++;
										m_SlaveStation[nstation][nItem].m5_ATotalValue +=fcurv;

										//24h
										if(m_SlaveStation[nstation][nItem].m24_AMaxValue<fcurv)
											m_SlaveStation[nstation][nItem].m24_AMaxValue = fcurv;
										if(m_SlaveStation[nstation][nItem].m24_AMinValue>fcurv)
											m_SlaveStation[nstation][nItem].m24_AMinValue = fcurv;
										m_SlaveStation[nstation][nItem].m24_Atotal++;
										m_SlaveStation[nstation][nItem].m24_ATotalValue +=fcurv;

										CTime vt = CTime::GetCurrentTime();
										CTime m5minute = m_SlaveStation[nstation][nItem].m5_T;
										if(vt.GetTime()-m5minute.GetTime() >=300) //5分钟
										{
	        								theApp.m_RTDM.SyncCRTData(nstation,nItem,10); 
											m_SlaveStation[nstation][nItem].m5_T = vt;
											m_SlaveStation[nstation][nItem].m5_AMaxValue=fcurv;
											m_SlaveStation[nstation][nItem].m5_AMinValue=fcurv;
											m_SlaveStation[nstation][nItem].m5_Atotal=0;
											m_SlaveStation[nstation][nItem].m5_ATotalValue=0;
										}
									}
									//调用显示最大值、平均值
									if(m_ADMainDis[nstation][nItem].AMaxValue < m_SlaveStation[nstation][nItem].AValue)
										m_ADMainDis[nstation][nItem].AMaxValue = m_SlaveStation[nstation][nItem].AValue;
									m_ADMainDis[nstation][nItem].m_ATotalnum++;
									m_ADMainDis[nstation][nItem].ATotalV += m_SlaveStation[nstation][nItem].AValue;

					if(ufData1 == 0x00)
					{
						//报警后不用复电
						if(((ufData5 != 0x10)&&(ufData1 != ufData5)&&(ufData5 !=255)) || m_two >0)
						{
	    						if(m_two >0)
								{
     					     		theApp.m_RTDM.Savefeedbr(nstation,nItem);  //馈电状态
 	    							m_SlaveStation[nstation][nItem].m_second =0;
//    								 m_wndResourceView3.InitAF(nstation,nItem);
								}
							if(m_two ==0)
							{
 								m_SlaveStation[nstation][nItem].m_second++;
    		      				m_ADMainDis[nstation][nItem].NTime = timetemp;
    			    				theApp.m_RTDM.handbr(nstation,nItem,0);
							}
						}
						ResumeAB(nstation,nItem);
					}//ufData1 == 0x00
					if(ufData1 == 0x10)
					{
                            if(pFWnd->m_RepeatFlag)
	    						pFWnd->DoPlayWarnSound(m_SlaveStation[nstation][nItem].falma);
						if(ufData5 != 0x10 )
						{
                            	pFWnd->m_RepeatFlag = TRUE;
								m_ADMainDis[nstation][nItem].ATime = timetemp;
								if(m_ABFlist[nstation][nItem].SFSd == 0)
								{
									m_ABFlist[nstation][nItem].SFSd =1;
									pFWnd->m_wndResourceView.m_cpstr.push_back(m_SlaveStation[nstation][nItem].strPN);
									pFWnd->m_wndResourceView.B_change = TRUE;
//					m_wndResourceView.InitFBA(1);
                    pFWnd->paneResourceView->Select();
//									theApp.idis =1;
								}
//								 m_wndResourceView.InitAA(nstation,nItem);
						}
//						m_SlaveStation[nstation][nItem].m_second++;
					}//ufData1 == 0x10)
					if(ufData1 == 0x20)
					{
                            if(pFWnd->m_RepeatFlag)
	    						pFWnd->DoPlayWarnSound(m_SlaveStation[nstation][nItem].falma);
						if(ufData5 != 0x20 || m_two>0)
						{
                            	pFWnd->m_RepeatFlag = TRUE;
	    						if(m_two >0)
								{
     					     		theApp.m_RTDM.Savefeedbr(nstation,nItem);  //馈电状态
							    	m_SlaveStation[nstation][nItem].m_second = 0;
					    			if(m_ABFlist[nstation][nItem].cfds == 0)
									{
									m_ABFlist[nstation][nItem].cfds =1;
									pFWnd->m_wndResourceView2.m_cpstr.push_back(m_SlaveStation[nstation][nItem].strPN);
									pFWnd->m_wndResourceView2.B_change = TRUE;
//					m_wndResourceView2.InitFBA(2);
                    pFWnd->paneResourceView2->Select();
//									theApp.idis =2;
									}
//						    		 m_wndResourceView2.InitAB(nstation,nItem);
//						    		 m_wndResourceView3.InitAF(nstation,nItem);
								}
							if(m_two ==0)
							{
								m_SlaveStation[nstation][nItem].m_second++;
     							theApp.m_RTDM.handbr(nstation,nItem,1);
    							m_ADMainDis[nstation][nItem].BTime = timetemp;
//								 m_wndResourceView.InitAA(nstation,nItem);
							}
						}
					}//ufData1 == 0x20)
					if((ufData1 == 0x40)|| (ufData1 == 0x50)  || (ufData1 == 0x60) || ufData1 == 0x70 ||ufData1 == 0x80)
					{//故障类型
//							if(ufData1 != 0x60)
							{
//		    					m_SlaveStation[nstation][nItem].CValue = 0;
//                				m_SlaveStation[nstation][nItem].pnValue = 0;
//	    						m_SlaveStation[nstation][nItem].AValue = 0;
							}
                            if(pFWnd->m_RepeatFlag)
	    						pFWnd->DoPlayWarnSound(m_SlaveStation[nstation][nItem].falma);
						//第二次断电确认
						if(ufData5 != ufData1 || m_two >0) 
						{
				     			//0通道故障闭锁使能
							if(m_SlaveStation[nstation][0].AlarmState ==1)
							{
                            	pFWnd->m_RepeatFlag = TRUE;
	    						if(m_two >0)
								{
     					     		theApp.m_RTDM.Savefeedbr(nstation,nItem);  //馈电状态
					    			m_SlaveStation[nstation][nItem].m_second = 0;
					    			if(m_ABFlist[nstation][nItem].cfds == 0)
									{
									m_ABFlist[nstation][nItem].cfds =1;
									pFWnd->m_wndResourceView2.m_cpstr.push_back(m_SlaveStation[nstation][nItem].strPN);
									pFWnd->m_wndResourceView2.B_change = TRUE;
//					m_wndResourceView2.InitFBA(2);
                    pFWnd->paneResourceView2->Select();
//									theApp.idis =2;
									}
//						    		 m_wndResourceView2.InitAB(nstation,nItem);
//						    		 m_wndResourceView3.InitAF(nstation,nItem);
								}
	    						if(m_two ==0)
								{
					    			m_SlaveStation[nstation][nItem].m_second++;
            						m_ADMainDis[nstation][nItem].BTime = timetemp;
      					    		theApp.m_RTDM.handbr(nstation,nItem,1);
								}
							}
						}
					}//ufData1 == 0x40)|| (ufData1 == 0x50)  || (ufData1 == 0x60
				 }//olddata != ndata)|| bhalf||m_two==1
	//				strtemp1.Format(_T("%.2f"), m_SlaveStation[nstation][nItem].AValue);
			}
			else if(ufData6 >9)
			{
        		    m_SlaveStation[nstation][nItem].Channel_state = ufData1;
//					int m_two = m_SlaveStation[nstation][nItem].m_second;
					if(olddata != n_cdata || (m_two >0) ||m_Adjust==1)
					{
	    				if((ufData1 == 0x00)||(ufData1 == 0x10)||(ufData1 == 0x20)||(ufData1 == 0x70)||(ufData1 == 0x80))
						{
							if(olddata != n_cdata)//故障时数据不变
							{
                        		    m_SlaveStation[nstation][nItem].ValueTime = timetemp;
//                        		    m_SlaveStation[nstation][nItem].Channel_state = ufData1;
	                				m_SlaveStation[nstation][nItem].CValue = n_cdata;
                					m_SlaveStation[nstation][nItem].AValue = n_cdata;
          							if(ufData4 == 1)//调校//adjustdata
	     								theApp.m_RTDM.SyncCRTData(nstation,nItem,1); 
									else
	     					    		theApp.m_RTDM.SyncCRTData(nstation,nItem,0);
//    	    						pFWnd->m_wndResourceView6.InitLDCH(nstation,nItem);
									if(theApp.b_5m)
									{
                                    theApp.m_RTDM.SaveRT24Data(nstation,nItem,5);
                                    theApp.m_RTDM.SaveRT24Data(nstation,nItem,24);
									}
							}
						}
	    				if(ufData1 == 0x00)
						{
							//报警后不用复电
							if(((ufData5 != 0x10)&&(ufData1 != ufData5)&&(ufData5 !=255)) || (m_two>0))
							{
	    						if(m_two >0)
								{
     					     		theApp.m_RTDM.Savefeedbr(nstation,nItem);  //馈电状态
    	    						m_SlaveStation[nstation][nItem].m_second = 0;
								}
//		    	    			int m_sleep = m_two%60;
								if(m_two ==0)
								{
    	    						m_SlaveStation[nstation][nItem].m_second++;
            						m_ADMainDis[nstation][nItem].NTime = timetemp;
			    						theApp.m_RTDM.handbr(nstation,nItem,0);
								}
//								else if(m_sleep ==1)
//        							 m_wndResourceView5.InitDF(nstation,nItem);
							}
			    			ResumeAB(nstation,nItem);
						}//ufData1 == 0x00)
						if(ufData1 == 0x10)
						{
                            if(pFWnd->m_RepeatFlag)
	    						pFWnd->DoPlayWarnSound(m_SlaveStation[nstation][nItem].falma);
//			    			int m_sleep = m_two%55;
							if(ufData5 != 0x10 )
							{
                            	pFWnd->m_RepeatFlag = TRUE;
									m_ADMainDis[nstation][nItem].ATime = timetemp;
					    			if(m_ABFlist[nstation][nItem].ffds == 0)
									{
									m_ABFlist[nstation][nItem].ffds =1;
									pFWnd->m_wndResourceView4.m_cpstr.push_back(m_SlaveStation[nstation][nItem].strPN);
									pFWnd->m_wndResourceView4.B_change = TRUE;
//					m_wndResourceView4.InitFBA(4);
                    pFWnd->paneResourceView4->Select();
//									theApp.idis =4;
									}
//  								 m_wndResourceView4.InitDAB(nstation,nItem);
							}
//    							m_SlaveStation[nstation][nItem].m_second++;
						}
						if(ufData1 == 0x20)
						{
                            if(pFWnd->m_RepeatFlag)
	    						pFWnd->DoPlayWarnSound(m_SlaveStation[nstation][nItem].falma);
							if(ufData5 != 0x20 || m_two>0)
							{
                            	pFWnd->m_RepeatFlag = TRUE;
	    						if(m_two >0)
								{
     					     		theApp.m_RTDM.Savefeedbr(nstation,nItem);  //馈电状态
    									m_SlaveStation[nstation][nItem].m_second = 0;
					    			if(m_ABFlist[nstation][nItem].ffds == 0)
									{
									m_ABFlist[nstation][nItem].ffds =1;
									pFWnd->m_wndResourceView4.m_cpstr.push_back(m_SlaveStation[nstation][nItem].strPN);
									pFWnd->m_wndResourceView4.B_change = TRUE;
//					m_wndResourceView4.InitFBA(4);
                    pFWnd->paneResourceView4->Select();
//									theApp.idis =4;
									}
//									 m_wndResourceView4.InitDAB(nstation,nItem);
//									 m_wndResourceView5.InitDF(nstation,nItem);
								}
								if(m_two ==0)
								{
    									m_SlaveStation[nstation][nItem].m_second++;
    								m_ADMainDis[nstation][nItem].BTime = timetemp;
         								theApp.m_RTDM.handbr(nstation,nItem,1);
								}
							}
						}//ufData1 == 0x20
						if((ufData1 == 0x70) ||(ufData1 == 0x80))
						{
                            if(pFWnd->m_RepeatFlag)
	    						pFWnd->DoPlayWarnSound(m_SlaveStation[nstation][nItem].falma);
				     		//第二次断电确认
		      				if((ufData5 != ufData1) || (m_two >0))
							{
				     			if(m_SlaveStation[nstation][0].AlarmState ==1)
								{
                                	pFWnd->m_RepeatFlag = TRUE;
	    	    					if(m_two >0)
									{
     				    	     		theApp.m_RTDM.Savefeedbr(nstation,nItem);  //馈电状态
    									m_SlaveStation[nstation][nItem].m_second = 0;
					    			if(m_ABFlist[nstation][nItem].ffds == 0)
									{
									m_ABFlist[nstation][nItem].ffds =1;
									pFWnd->m_wndResourceView4.m_cpstr.push_back(m_SlaveStation[nstation][nItem].strPN);
									pFWnd->m_wndResourceView4.B_change = TRUE;
//					m_wndResourceView4.InitFBA(4);
                    pFWnd->paneResourceView4->Select();
//									theApp.idis =4;
									}
//									 m_wndResourceView4.InitDAB(nstation,nItem);
//									 m_wndResourceView5.InitDF(nstation,nItem);
									}
	    				     		if(m_two ==0)
									{
       									m_SlaveStation[nstation][nItem].m_second++;
	    					        	m_ADMainDis[nstation][nItem].BTime = timetemp;
        					    		theApp.m_RTDM.handbr(nstation,nItem,1);
									}
								}
							}
						}//ufData1 == 0x70
					}//olddata != n_cdata || (m_two >0))
					m_two = m_AFans[nstation][nItem].fchan;//1 alarm 0 no
						if(m_AFans[nstation][nItem].cfds != 0)  //双风门主扇备扇报警
						{
                            if(pFWnd->m_RepeatFlag && m_two ==1)
	    						pFWnd->DoPlayWarnSound(m_SlaveStation[nstation][nItem].falma);
                    	    	int cnfds = m_AFans[nstation][nItem].cfds;
                      	    	int cnchan = m_AFans[nstation][nItem].cchan;
								int n_fans = m_AFans[nstation][nItem].SFSd;
								int n_value = m_SlaveStation[nstation][nItem].CValue;
								int cn_value = m_SlaveStation[cnfds][cnchan].CValue;
//			    			int m_sleep = m_two%55;
							if(n_value == n_fans && cn_value == n_fans && m_two==0)
							{
                            	pFWnd->m_RepeatFlag = TRUE;
									m_ADMainDis[cnfds][cnchan].ATime = timetemp;
									m_ADMainDis[nstation][nItem].ATime = timetemp;
					    			if(m_ABFlist[nstation][nItem].ffds == 0)
									{
									m_ABFlist[nstation][nItem].ffds =1;
									pFWnd->m_wndResourceView4.m_cpstr.push_back(m_SlaveStation[nstation][nItem].strPN);
									pFWnd->m_wndResourceView4.m_cpstr.push_back(m_SlaveStation[cnfds][cnchan].strPN);
									pFWnd->m_wndResourceView4.B_change = TRUE;
//					m_wndResourceView4.InitFBA(4);
                    pFWnd->paneResourceView4->Select();
//									theApp.idis =4;
									}
//  								 m_wndResourceView4.InitDAB(nstation,nItem);
								 m_AFans[nstation][nItem].fchan++;
								 m_AFans[cnfds][cnchan].fchan++;
							}
							else if(n_value != n_fans || cn_value != n_fans)
							{
								 m_AFans[nstation][nItem].fchan =0;
								 m_AFans[cnfds][cnchan].fchan =0;
							}
//    							m_SlaveStation[nstation][nItem].m_second++;
						}//双风门主扇备扇报警

			}//>3
		}//if
		nItem++;
	}//for
//	message.GetAt(35, nbegin);    //控制量状态
	nbegin = m_ndkSend[nstation][35];
	for( i =17 ;i <MAX_CHAN ;i++)
	{
		if(i == 17)
    		ufData = nbegin & 0x01;
		else if(i == 18)
		{
    		ufData = nbegin & 0x02;
			if(ufData == 0)
				ufData =0;
			else
				ufData =1;
		}
		else if(i == 19)
		{
    		ufData = nbegin & 0x04;
			if(ufData == 0)
				ufData =0;
			else
				ufData =1;
		}
		else if(i == 20)
		{
    		ufData = nbegin & 0x08;
			if(ufData == 0)
				ufData =0;
			else
				ufData =1;
		}
		else if(i == 21)
		{
    		ufData = nbegin & 0x10;
			if(ufData == 0)
				ufData =0;
			else
				ufData =1;
		}
		else if(i == 22)
		{
    		ufData = nbegin & 0x20;
			if(ufData == 0)
				ufData =0;
			else
				ufData =1;
		}
		else if(i == 23)
		{
    		ufData = nbegin & 0x40;
			if(ufData == 0)
				ufData =0;
			else
				ufData =1;
		}
		else if(i == 24)
		{
    		ufData = nbegin & 0x80;
			if(ufData == 0)
				ufData =0;
			else
				ufData =1;
		}
		if(m_SlaveStation[nstation][i].WatchName != "")
		{
    		//第二次断电确认
    		ufData4 = m_SlaveStation[nstation][i].Adjust_state;
			if(ufData4 == 1)
				m_SlaveStation[nstation][i].m_second++;
			else
				m_SlaveStation[nstation][i].m_second = 0;
            int m_two =m_SlaveStation[nstation][i].m_second;   //存标校第一个值
            m_SlaveStation[nstation][i].Channel_state = 0;
      		ufData1 = m_SlaveStation[nstation][i].CValue;
    		if((ufData1 != ufData) ||m_two==1)
			{
//		    	    m_SlaveStation[nstation][i].m_second++;
            	m_SlaveStation[nstation][i].AValue = ufData;
            	m_SlaveStation[nstation][i].CValue = ufData;
    			m_SlaveStation[nstation][i].ValueTime = timetemp;
    	    		if(ufData4 == 1)
			       		theApp.m_RTDM.SyncCRTData(nstation,i,1);     //adjustdata
       	    		else
					{
						m_SlaveStation[nstation][i].m_second = 0;
	     	    		theApp.m_RTDM.SyncCRTData(nstation,i,0);     //rtdata2010
 									if(theApp.b_5m)
									{
                                    theApp.m_RTDM.SaveRT24Data(nstation,i,5);
                                    theApp.m_RTDM.SaveRT24Data(nstation,i,24);
									}
					}
			}
		}
	}
	ufData = m_ndkSend[nstation][36];
//	message.GetAt(36, ufData);    //AC/DC+电池电压
	ufData =ufData & 0x10;
	if(ufData == 0x10)
		ufData =1;
	else
		ufData =0;
	if(ufData != m_SlaveStation[nstation][0].CValue)
	{
    	if(ufData == 0)
		{
    	m_SlaveStation[nstation][0].CValue = 0;
		m_SlaveStation[nstation][0].Channel_state = 0x00;
		}
    	else 
		{
    	m_SlaveStation[nstation][0].CValue = 1;
		m_SlaveStation[nstation][0].Channel_state = 0x10;
		}
    	m_SlaveStation[nstation][0].ValueTime = timetemp;
	    theApp.m_RTDM.SyncCRTData(nstation,0,0);     //rtdata  theApp.SocketServer.
 									if(theApp.b_5m)
									{
                                    theApp.m_RTDM.SaveRT24Data(nstation,0,5);
                                    theApp.m_RTDM.SaveRT24Data(nstation,0,24);
									}
	}
    	if(ufData == 0)
		{
    	m_SlaveStation[nstation][0].CValue = 0;
		m_SlaveStation[nstation][0].Channel_state = 0x00;
		}
    	else if(ufData == 1)
		{
    	m_SlaveStation[nstation][0].CValue = 1;
		m_SlaveStation[nstation][0].Channel_state = 0x10;
		}
    	m_SlaveStation[nstation][0].ValueTime = timetemp;

//    theApp.socketClient.m_nodialog = TRUE;
//	eventWriteD.ResetEvent(); 
}
//关系不起作用时，要删、改测点必须先删除关系
BOOL CRTDataManage::CalRelationC(unsigned char  nfds, unsigned char  nchan)
{
    		for(int j=0; j<65; j++)
			{
		    	if(m_ADCbreakE[nfds][nchan][j].bFSd ==0)
		       		break;
			}//int j=0; j<65; j++)
			if(j == 0)
				return TRUE;
 	    	else
			{
    			AfxMessageBox(m_SlaveStation[nfds][nchan].WatchName+"|"+m_SlaveStation[nfds][nchan].strPN +"：有控制关系,不能删除、修改！", MB_OK);
				return FALSE;
			}
}

BOOL CRTDataManage::CalRelationF(unsigned char  nfds, unsigned char  nchan)
{
          		for(int k=0; k<65; k++)
				{   //馈电关联断电control
	    	     	if(m_CFeed[nfds][nchan][k].bFSd ==0)
		         		break;
				}
			if(k == 0)
				return TRUE;
 	    	else
			{
    			AfxMessageBox(m_SlaveStation[nfds][nchan].WatchName+"|"+m_SlaveStation[nfds][nchan].strPN +"：有馈电关系,不能删除、修改！", MB_OK);
				return FALSE;
			}
}

BOOL CRTDataManage::CalRelationD(unsigned char  nfds, unsigned char  nchan)
{
			if(m_AFans[nfds][nchan].cfds == 0)
				return TRUE;
 	    	else
			{
    			AfxMessageBox(m_SlaveStation[nfds][nchan].WatchName+"|"+m_SlaveStation[nfds][nchan].strPN +"：有双设备关系,不能删除、修改！", MB_OK);
				return FALSE;
			}
}

BOOL CRTDataManage::CalRelationW(unsigned char  nfds, unsigned char  nchan)
{
	int nstart = nfds*6;
	int nend = (nfds+1)*6+1;
	CString dddd;
    if ( theApp.m_CommonSet._IsOpen() )
       theApp.m_CommonSet.Close();
		theApp.m_CommonSet.Create();
		theApp.m_CommonSet.CursorType(adOpenDynamic);
		theApp.m_CommonSet.CacheSize(50);
		theApp.m_CommonSet._SetRecordsetEvents(new CAccountSetEvents);
		dddd.Format("Select * From commonset where CommonID>%d and CommonID<%d",nstart,nend);
		theApp.m_CommonSet.Open( dddd, &theApp.m_Cn);
		theApp.m_CommonSet.MarshalOptions(adMarshalModifiedOnly);

		theApp.m_CommonSet.MoveFirst();
		while ( !theApp.m_CommonSet.IsEOF() )
		{
			int sfds = theApp.m_CommonSet.m_szCommonID;
			if(sfds >nstart && sfds < nend )
			{
        		CString dddd = theApp.m_CommonSet.m_szstrc30;
				dddd = dddd.Mid(0,5);
              	CString strf,strc;
        		int p =dddd.Find("C");
        		    strf = dddd.Mid(0,2);
            		strc = dddd.Mid(3,2);
//          		int nfds = m_Str2Data.String2Int(strf);
         		int cnchan = theApp.m_Str2Data.String2Int(strc);
				if(p >0)
					cnchan = cnchan +16;
				if(nchan == cnchan)
					nstart =66666;
			}
			theApp.m_CommonSet.MoveNext();
		}
    if ( theApp.m_CommonSet._IsOpen() )
       theApp.m_CommonSet.Close();

		if(nstart ==66666)
		{
    			AfxMessageBox(m_SlaveStation[nfds][nchan].WatchName+"|"+m_SlaveStation[nfds][nchan].strPN +"：有风电瓦斯闭锁关系,不能删除、修改！", MB_OK);
				return FALSE;
		}
		else
				return TRUE;
}
//测点正常 m_wndResourceView
void CRTDataManage::ResumeAB(unsigned char  nstation, unsigned char  nItem)
{
    CMainFrame* pFWnd=(CMainFrame*)AfxGetMainWnd();
	CString strtemp6 ;
	if(m_ABFlist[nstation][nItem].SFSd == 1)
	{
		m_SlaveStation[nstation][nItem].strSafe = "";
    		for(vector<CString>::iterator iter=pFWnd->m_wndResourceView.m_cpstr.begin(); iter!=pFWnd->m_wndResourceView.m_cpstr.end(); )
			{
	    		strtemp6 = *iter;
				if(strtemp6 == m_SlaveStation[nstation][nItem].strPN)
				{
	        		iter = pFWnd->m_wndResourceView.m_cpstr.erase(iter);
									m_ABFlist[nstation][nItem].SFSd =0;
									pFWnd->m_wndResourceView.B_change = TRUE;
					break;
				}
		    	else
			    	iter++;
			}
	}
	if(m_ABFlist[nstation][nItem].cfds == 1)
	{
		m_SlaveStation[nstation][nItem].strSafe = "";
    		for(vector<CString>::iterator iter=pFWnd->m_wndResourceView2.m_cpstr.begin(); iter!=pFWnd->m_wndResourceView2.m_cpstr.end(); )
			{
	    		strtemp6 = *iter;
				if(strtemp6 == m_SlaveStation[nstation][nItem].strPN)
				{
	        		iter = pFWnd->m_wndResourceView2.m_cpstr.erase(iter);
									m_ABFlist[nstation][nItem].cfds =0;
									pFWnd->m_wndResourceView2.B_change = TRUE;
					break;
				}
		    	else
			    	iter++;
			}
	}
	if(m_ABFlist[nstation][nItem].ffds == 1)
	{
		m_SlaveStation[nstation][nItem].strSafe = "";
    		for(vector<CString>::iterator iter=pFWnd->m_wndResourceView4.m_cpstr.begin(); iter!=pFWnd->m_wndResourceView4.m_cpstr.end(); )
			{
	    		strtemp6 = *iter;
				if(strtemp6 == m_SlaveStation[nstation][nItem].strPN)
				{
	        		iter = pFWnd->m_wndResourceView4.m_cpstr.erase(iter);
									m_ABFlist[nstation][nItem].ffds =0;
									pFWnd->m_wndResourceView4.B_change = TRUE;
					break;
				}
		    	else
			    	iter++;
			}
	}
}

//关闭打开文件
void CRTDataManage::CloseDrawfile(CString dfile)
{
	CString strrsy = gstrTimeOut + "\\" + strMetrics+ "rsy\\" ;
	CString strTemp1 =strrsy+dfile;
            	CMDIFrameWnd *pFrame = (CMDIFrameWnd*)AfxGetApp()->m_pMainWnd;
              	CMDIChildWnd *pChild = (CMDIChildWnd *) pFrame->GetActiveFrame();
				CDrawView *pView = (CDrawView*)pChild->GetActiveView();	
//     			if(!pView->IsKindOf(RUNTIME_CLASS(CDrawView)))
//            		return;

		        CString strTemp;   m_ViewPos = NULL;
				for(int i=0;i<theApp.m_addfilesy.size()+2;i++)
				{
    	        		if(m_ViewPos != NULL)
						{
			            	theApp.m_map.GetNextAssoc(m_ViewPos,strTemp,pView);
							if(strTemp == strTemp1)
							{
//       		            	if(pView != NULL)
                        		pView->GetParentFrame()->ActivateFrame();
								pChild = (CMDIChildWnd *) pFrame->GetActiveFrame();
                    			CDrawDoc* pThisOne = (CDrawDoc *)pChild->GetActiveDocument() ;
                    			pThisOne->OnCloseDocument();
								break;
							}
						}
		            	else 
		    	        	m_ViewPos = theApp.m_map.GetStartPosition() ;     //0415
				}
}

BOOL CRTDataManage::Initdrawfile()
{
			for(int i = 0; i < 11;i++ )
		    	for(int j = 0; j < 101;j++ )
				{
			    		m_strdf[i][j].strl = "";  //
			    		m_strdfall[i][j].strl = "";  //
						m_s3draw[j].strl = "";
						m_iddf[i][j].n_iddf =0;
				}

    if ( theApp.m_Drawfile._IsOpen() )
      theApp.m_Drawfile.Close();
		theApp.m_Drawfile.Create();
		theApp.m_Drawfile.CursorType(adOpenDynamic);
		theApp.m_Drawfile.CacheSize(50);
		theApp.m_Drawfile._SetRecordsetEvents(new CAccountSetEvents);
		theApp.m_Drawfile.Open(_T("Select * From drawfile WHERE DRAWID<100"), &theApp.m_Cn);
		theApp.m_Drawfile.MarshalOptions(adMarshalModifiedOnly);

            	CString  strf,strc,strItem;
	LPCTSTR str1 = "",str2 = "",str3 = "";
	    if ( !theApp.m_Drawfile._IsEmpty() )
		{
	    	theApp.m_Drawfile.MoveFirst();
    		while ( !theApp.m_Drawfile.IsEOF() )//读文件信息
			{
	        	int nfds = theApp.m_Drawfile.m_szDRAWID; 
        		strItem = theApp.m_Drawfile.m_szD1024;
       			strItem.TrimRight();
				m_strdfall[0][nfds].strl =strItem;//全文件 id ver
				str1 = "",str2 = "",str3 = "";
     	theApp.m_Str2Data.SplittoCString(strItem,str1,str2,str3);
        		strItem = str1;
				m_strdf[0][nfds].strl =strItem;  //文件名
        		strItem = str2;
				m_iddf[0][nfds].n_iddf = theApp.m_Str2Data.String2Int(strItem);
//				Isdfdel(0 ,strItem ,nfds);
     			strItem = theApp.m_Drawfile.m_szD1280;
       			strItem.TrimRight();
				m_strdfall[1][nfds].strl =strItem;
				str1 = "",str2 = "",str3 = "";
     	theApp.m_Str2Data.SplittoCString(strItem,str1,str2,str3);
        		strItem = str1;
				m_strdf[1][nfds].strl =strItem;
        		strItem = str2;
				m_iddf[1][nfds].n_iddf = theApp.m_Str2Data.String2Int(strItem);
//				Isdfdel(1 ,strItem,nfds);
     			strItem = theApp.m_Drawfile.m_szD1360;
       			strItem.TrimRight();
				m_strdfall[2][nfds].strl =strItem;
				str1 = "",str2 = "",str3 = "";
     	theApp.m_Str2Data.SplittoCString(strItem,str1,str2,str3);
        		strItem = str1;
				m_strdf[2][nfds].strl =strItem;
        		strItem = str2;
				m_iddf[2][nfds].n_iddf = theApp.m_Str2Data.String2Int(strItem);
//				Isdfdel(2 ,strItem,nfds);
     			strItem = theApp.m_Drawfile.m_szD1366;
       			strItem.TrimRight();
				m_strdfall[3][nfds].strl =strItem;
				str1 = "",str2 = "",str3 = "";
     	theApp.m_Str2Data.SplittoCString(strItem,str1,str2,str3);
        		strItem = str1;
				m_strdf[3][nfds].strl =strItem;
        		strItem = str2;
				m_iddf[3][nfds].n_iddf = theApp.m_Str2Data.String2Int(strItem);
//				Isdfdel(3 ,strItem,nfds);
     			strItem = theApp.m_Drawfile.m_szD1400;
       			strItem.TrimRight();
				m_strdfall[4][nfds].strl =strItem;
				str1 = "",str2 = "",str3 = "";
     	theApp.m_Str2Data.SplittoCString(strItem,str1,str2,str3);
        		strItem = str1;
				m_strdf[4][nfds].strl =strItem;
        		strItem = str2;
				m_iddf[4][nfds].n_iddf = theApp.m_Str2Data.String2Int(strItem);
//				Isdfdel(4 ,strItem,nfds);
     			strItem = theApp.m_Drawfile.m_szD1440;
       			strItem.TrimRight();
				m_strdfall[5][nfds].strl =strItem;
				str1 = "",str2 = "",str3 = "";
     	theApp.m_Str2Data.SplittoCString(strItem,str1,str2,str3);
        		strItem = str1;
				m_strdf[5][nfds].strl =strItem;
        		strItem = str2;
				m_iddf[5][nfds].n_iddf = theApp.m_Str2Data.String2Int(strItem);
//				Isdfdel(5 ,strItem,nfds);
     			strItem = theApp.m_Drawfile.m_szD1600;
       			strItem.TrimRight();
				m_strdfall[6][nfds].strl =strItem;
				str1 = "",str2 = "",str3 = "";
     	theApp.m_Str2Data.SplittoCString(strItem,str1,str2,str3);
        		strItem = str1;
				m_strdf[6][nfds].strl =strItem;
        		strItem = str2;
				m_iddf[6][nfds].n_iddf = theApp.m_Str2Data.String2Int(strItem);
//				Isdfdel(6 ,strItem,nfds);
     			strItem = theApp.m_Drawfile.m_szD1680;
       			strItem.TrimRight();
				m_strdfall[7][nfds].strl =strItem;
				str1 = "",str2 = "",str3 = "";
     	theApp.m_Str2Data.SplittoCString(strItem,str1,str2,str3);
        		strItem = str1;
				m_strdf[7][nfds].strl =strItem;
        		strItem = str2;
				m_iddf[7][nfds].n_iddf = theApp.m_Str2Data.String2Int(strItem);
//				Isdfdel(7 ,strItem,nfds);
     			strItem = theApp.m_Drawfile.m_szD1920;
       			strItem.TrimRight();
				m_strdfall[8][nfds].strl =strItem;
				str1 = "",str2 = "",str3 = "";
     	theApp.m_Str2Data.SplittoCString(strItem,str1,str2,str3);
        		strItem = str1;
				m_strdf[8][nfds].strl =strItem;
        		strItem = str2;
				m_iddf[8][nfds].n_iddf = theApp.m_Str2Data.String2Int(strItem);
//				Isdfdel(8 ,strItem,nfds);
     			strItem = theApp.m_Drawfile.m_szD2048;
       			strItem.TrimRight();
				m_strdfall[9][nfds].strl =strItem;
				str1 = "",str2 = "",str3 = "";
     	theApp.m_Str2Data.SplittoCString(strItem,str1,str2,str3);
        		strItem = str1;
				m_strdf[9][nfds].strl =strItem;
        		strItem = str2;
				m_iddf[9][nfds].n_iddf = theApp.m_Str2Data.String2Int(strItem);
//				Isdfdel(9 ,strItem,nfds);
     			strItem = theApp.m_Drawfile.m_szD2560;
       			strItem.TrimRight();
				m_strdfall[10][nfds].strl =strItem;
				str1 = "",str2 = "",str3 = "";
     	theApp.m_Str2Data.SplittoCString(strItem,str1,str2,str3);
        		strItem = str1;
		    		m_strdf[10][nfds].strl =strItem;
        		strItem = str2;
				m_iddf[10][nfds].n_iddf = theApp.m_Str2Data.String2Int(strItem);
//    				Isdfdel(10 ,strItem,nfds);
				theApp.m_Drawfile.MoveNext();
			}
		}

	CString strrsy ,strrsy1,strclm;
	strrsy = gstrTimeOut + "\\" + strMetrics+ "rsy\\";
	strrsy1 ="dispoint"+strMetrics;
    	int m_ishave =0;
		CppSQLite3Query q;
		theApp.sFC.v_disdrawf.clear();
			strItem.Format("select * from '%s' WHERE DISID<300 and DISID>199;",strrsy1);
            q = theApp.db3.execQuery(strItem);
            while (!q.eof())
			{
//            	int m_del =0;
				m_ishave = q.getIntField(0);
                strclm = q.getStringField(1);
	    		strclm.TrimRight(); //初始化时rsy文件
				if(strclm == "")
					break;
				m_s3draw[m_ishave-200].strl=strclm;
                q.nextRow();
			}

	//设置要遍历的目录
	if (!theApp.m_sdir.SetInitDir(strrsy))
	{//\r\n--------------------\r\n
        AfxMessageBox("目录不存在!", MB_OK);
		return 0;
	}
	theApp.m_sdir.m_nFileCount = 0;
	theApp.m_sdir.m_nSubdirCount = 0;
	//开始遍历
	theApp.m_sdir.BeginBrowse("*.rsy");
	//统计结果中，子目录个数不含 . 及 ..

		for( i = 0 ; i < 100 ; i++ )//清空不在目录文件
		{
			m_ishave = 0;
			strclm = m_s3draw[i].strl;
			str1 = "",str2 = "",str3 = "";
         	theApp.m_Str2Data.SplittoCString(strclm,str1,str2,str3);
			strclm = str1;
			strclm.Replace(theApp.m_strms[18].strl,"");
			strclm = gstrTimeOut + "\\"+strclm;
				if(strclm == "")
					break;
     		for ( int k = 0 ; k < theApp.m_sdir.m_dirs.size() ; k++ )
			{
				if(strclm == theApp.m_sdir.m_dirs[k])
				{
					m_ishave =100;
					break;
				}
				else
					m_ishave =0;
			}
			if(m_ishave == 0)
				m_s3draw[i].strl = "";

		}

		    for ( int k = 0 ; k < 100 ; k++ )//生成下载文件
			{
				m_ishave =0;
				strclm = m_strdfall[Initfbl(strMetrics)][k].strl;
				if(strclm == "")
					break;
               	for ( int i = 0 ; i < 100 ; i++ )//比较文件是否修改
				{
					strItem =m_s3draw[i].strl;
					if(strItem == "")
						break;
					if(strItem == strclm)
					{
						m_ishave =100;
			    		break;
					}
				}
				if(m_ishave ==0)//修改或无文件
				{
					strclm = m_strdf[Initfbl(strMetrics)][k].strl;
					theApp.sFC.v_disdrawf.push_back(strclm);//需要下载的文件
					strclm = theApp.SplitPath(strclm);
					CloseDrawfile(strclm);//关闭正在打开文件
					theApp.sFC.GetTableData(m_iddf[Initfbl(strMetrics)][k].n_iddf);
				}
			}

				for( k=0;k<theApp.m_addfilesy.size();k++)//关闭没有管理文件
				{
                   	strclm = theApp.m_addfilesy[k];
             		m_ishave = strclm.GetLength();
             		strItem = strclm.Mid(m_ishave-3,3);
					m_ishave= 0;
		           if(strItem == "rsy")
				   {
                    	for ( int i = 0 ; i < 100 ; i++ )//比较文件是否修改
						{
				        	strItem =m_strdf[Initfbl(strMetrics)][i].strl;
			          		if(strItem == "")
			          			break;
			           		if(strItem == strclm)
							{
				          		m_ishave =100;
			               		break;
							}
						}
						if(m_ishave == 0)
						{
	        				strclm = theApp.SplitPath(strclm);
        					CloseDrawfile(strclm);//关闭正在打开文件
							k--;//数目变化
						}
				   }
				}



/*			for(int i=0;i<theApp.m_addfilesy.size();i++)
			{
                	strclm = theApp.m_addfilesy[i];
             		int m_ishave = strclm.GetLength();
             		strclm = strclm.Mid(m_ishave-3,3);
		         if(strclm == "rsy")
				 {
                  	for ( int i = 0 ; i < 100 ; i++ )//比较文件是否存在
					{
			    		strItem =m_strdf[theApp.Initfbl(strMetrics)][i].strl;
			    		if(strItem == "")
						break;
				     	if(strItem == strclm)
						{
						m_ishave =100;
			    		break;
						}
					}
				 }
			}*/
//			m_ishave =v_disdrawf.size();
    if(theApp.sFC.v_disdrawf.size() == 0)
           theApp.m_senddata =true;
	else
	{
//            strSQL.Format("UPDATE '%s' SET LP%d='%d' WHERE DISID=%d;",
//			    	     strrsy1, m_ntrans ,m_color1 , coxx );
//			theApp.db3.execDML(strSQL);
	}
    if ( theApp.m_Drawfile._IsOpen() )
      theApp.m_Drawfile.Close();

    return TRUE;
}

int  CRTDataManage::Initfbl(CString strfbl)
{
		if(strfbl == "1024")
			return 0;
		else if(strfbl == "1280")
			return 1;
		else if(strfbl == "1360")
			return 2;
		else if(strfbl == "1366")
			return 3;
		else if(strfbl == "1400")
			return 4;
		else if(strfbl == "1440")
			return 5;
		else if(strfbl == "1600")
			return 6;
		else if(strfbl == "1680")
			return 7;
		else if(strfbl == "1920")
			return 8;
		else if(strfbl == "2048")
			return 9;
		else if(strfbl == "2560")
			return 10;
		else 
			return 0;
}

BOOL CRTDataManage::InitDisplay()
{
		CSampleFormView *psView;
		CString strTemp;
		m_ViewPos = theApp.m_Sam.GetStartPosition() ;     //0415
		for(int i = 0; i < 22;i++ )
		{
    	   	if(m_ViewPos != NULL)
			{
         	    theApp.m_Sam.GetNextAssoc(m_ViewPos,strTemp,psView);
				psView->b_curdis =TRUE;//点改变，更新
			}
			else
				break;
		}
		return TRUE;
}
