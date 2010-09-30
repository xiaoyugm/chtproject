// MQServer.cpp: implementation of the CMQServer class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "GUI_VisualStudio.h"
#include "MQServer.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

extern SerialF               m_one[MAX_FDS][17];
extern SerialF               m_ClassTime[200];            //班设置
extern CNDKMessage m_NDKmes[50];
extern unsigned char *m_ndkRTD;
extern SlaveStation             m_SlaveStation[MAX_FDS][MAX_CHAN];
extern  OthersSetting    m_OthersSetting;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMQServer::CMQServer()
{
	tHostStartTime = CTime::GetCurrentTime();
	bIsConnect = FALSE;
}

CMQServer::~CMQServer()
{

}

//开始监听服务
BOOL CMQServer::Listenning(long lPort)
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
void CMQServer::StopServer()
{
	DisconnectAllUsers();
	Stop();
}

//服务器端发送消息
BOOL CMQServer::SendMessage(CNDKMessage& message)
{
	if(SendMessageToAllUsers(message))
		return TRUE;
	else
		return FALSE;
}


//响应客户机发来的消息
void CMQServer::OnMessage(long lUserId, CNDKMessage& message)
{
	switch(message.GetId())
	{
/*
	case uCollectData:
//		SyncTableCollectData();
		break;
	case SENDSTARTTIME:
		break;
	case uWarnCauseRecord:
//		SyncTableuWarnCauseRecord();
		break;
*///	case SYNC:
//		Sync(message);
//		break;

	default:
		break;
	}
}

void CMQServer::OnConnect(long lUserId)
{
	bIsConnect = TRUE;
	SendStartTime(tHostStartTime);
	//MessageBox(NULL,"双机热备已经开始!","提示",MB_ICONINFORMATION);
}

void CMQServer::OnDisconnect(long lUserId, NDKServerDisconnection disconnectionType)
{
	bIsConnect = FALSE;
	//MessageBox(NULL,"双机热备已经停止!","提示",MB_ICONINFORMATION);
}

//向连接的计算机发送SQL语句
BOOL CMQServer::SendSQL(CString strSql)
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

BOOL CMQServer::OnIsConnectionAccepted()
{
	return TRUE;
}

//发送本机开始运行的时间
BOOL CMQServer::SendStartTime(CTime time)
{
	if(bIsConnect)
	{
		CNDKMessage message(SENDSTARTTIME);
		message.Add(m_OthersSetting.DBname);
		message.Add(m_ClassTime[1].ffds);
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

//连接本地SQLSERVER数据库
void CMQServer::ConnectDB()
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

void CMQServer::SyncTableCollectData()
{
	CString strTable;
	CString strDate;
	strDate.Format("%d/%d/%d",tHostStartTime.GetMonth(), tHostStartTime.GetDay(), tHostStartTime.GetYear());
	strTable.Format("SELECT unPointNo,unCollectData,strBeginTime,strEndTime FROM uCollectData WHERE (strBeginTime>CONVERT(DATETIME,'%s', 101))",strDate);

	CString strDBLink = "Provider=SQLOLEDB.1;Persist Security Info=False;User ID=kj86;Password=kj86;Initial Catalog=masterdefine;Data Source="
					+ m_OthersSetting.IP;
/*	try
	{
		_RecordsetPtr pRS;
		pRS.CreateInstance(__uuidof(Recordset));
		pRS->Open(_bstr_t(strTable),_bstr_t(strDBLink), adOpenStatic ,adLockReadOnly , adCmdText );
		int unPointNo,unCollectData ;
		COleDateTime BeginTime,EndTime;
		CString strBeginTime,strEndTime;

		while(!pRS->EndOfFile)
		{
			unPointNo = pRS->Fields->Item["unPointNo"]->Value.lVal;
			unCollectData = pRS->Fields->Item["unCollectData"]->Value.lVal;
			BeginTime = pRS->Fields->Item["strBeginTime"]->Value;
			EndTime = pRS->Fields->Item["strEndTime"]->Value;
			
			strBeginTime.Format("%d-%d-%d %d:%d:%d",BeginTime.GetYear(),BeginTime.GetMonth(),BeginTime.GetDay(),BeginTime.GetHour(),BeginTime.GetMinute(),BeginTime.GetSecond());
			strEndTime.Format("%d-%d-%d %d:%d:%d",EndTime.GetYear(),EndTime.GetMonth(),EndTime.GetDay(),EndTime.GetHour(),EndTime.GetMinute(),EndTime.GetSecond());
			
			CString strSQL;
			strSQL.Format("INSERT INTO uCollectData VALUES(%d,%d,'%s','%s')",unPointNo,unCollectData,strBeginTime,strEndTime);

			SendSQL(strSQL);
			pRS->MoveNext();
		}
		pRS->Close();
	}
	catch(_com_error &e)
	{
		AfxMessageBox(e.ErrorMessage());
	}*/
}

void CMQServer::SyncTableuWarnCauseRecord()
{
	CString strTable;
	CString strDate;
	strDate.Format("%d/%d/%d",tHostStartTime.GetMonth(), tHostStartTime.GetDay(), tHostStartTime.GetYear());
	strTable.Format("SELECT unPointNo,strExplain,strWarnCause,strWarnTime,strNormalTime,bConfirm FROM uWarnCauseRecord WHERE (strWarnTime>CONVERT(DATETIME,'%s', 101)) OR (strNormalTime>CONVERT(DATETIME,'%s', 101))",strDate,strDate);

	CString strDBLink = "Provider=SQLOLEDB.1;Persist Security Info=False;User ID=kj86;Password=kj86;Initial Catalog=masterdefine;Data Source="
					+ m_OthersSetting.IP;
/*	try
	{
		_RecordsetPtr pRS;
		pRS.CreateInstance(__uuidof(Recordset));
		pRS->Open(_bstr_t(strTable),_bstr_t(strDBLink), adOpenStatic ,adLockReadOnly , adCmdText );
		COleDateTime WarnTime,NormalT閙e;
		int nPointNo,bConfirm;
		_bstr_t Explain,WarnCause;
		CString strWarnTime,strNormalTime;


		while(!pRS->EndOfFile)
		{
			nPointNo = pRS->Fields->Item["unPointNo"]->Value.lVal;
			Explain = pRS->Fields->Item["strExplain"]->Value;
			WarnCause = pRS->Fields->Item["strWarnCause"]->Value;
			bConfirm = pRS->Fields->Item["bConfirm"]->Value.lVal;

			WarnTime = pRS->Fields->Item["strWarnTime"]->Value;
			NormalTime = pRS->Fields->Item["strNormalTime"]->Value;
			
			strWarnTime.Format("%d-%d-%d %d:%d:%d",WarnTime.GetYear(),WarnTime.GetMonth(),WarnTime.GetDay(),WarnTime.GetHour(),WarnTime.GetMinute(),WarnTime.GetSecond());
			if(NormalTime.GetYear() > 0 && NormalTime.GetHour() > 0)
				strNormalTime.Format("%d-%d-%d %d:%d:%d",NormalTime.GetYear(),NormalTime.GetMonth(),NormalTime.GetDay(),NormalTime.GetHour(),NormalTime.GetMinute(),NormalTime.GetSecond());
			else
				strNormalTime ="";

			CString strSQL;
			strSQL.Format("INSERT INTO uWarnCauseRecord VALUES(%d,'%s','%s','%s','%s',%d)",nPointNo,(char *)Explain,(char *)WarnCause,strWarnTime,strNormalTime,bConfirm);

			SendSQL(strSQL);
			pRS->MoveNext();
		}
		pRS->Close();
	}
	catch(_com_error &e)
	{
		AfxMessageBox(e.ErrorMessage());
	}*/
}

//同步检索本地数据库，生成SQL语句并发送
void CMQServer::Sync(CNDKMessage &message)
{
	int nIndex;
	CString strTableName, strInSql, strSQL;

	message.GetAt(0, strTableName);
	message.GetAt(1, nIndex);
	message.GetAt(2, strInSql);
	
	COleDateTime oleData1,oleData2;
	CString strDBLink = "Provider=SQLOLEDB.1;Persist Security Info=False;User ID=kj86;Password=kj86;Initial Catalog=masterdefine;Data Source="
					+ m_OthersSetting.IP;

/*	try
	{
		_RecordsetPtr pRS;
		pRS.CreateInstance(__uuidof(Recordset));
		pRS->Open(_bstr_t(strInSql),_bstr_t(strDBLink), adOpenStatic ,adLockReadOnly , adCmdText );

		while(!pRS->EndOfFile)
		{
			//uCollectData表
			if(strTableName.CollateNoCase("uCollectData") == 0)
			{
				long nPointNo		= pRS->Fields->Item["unPointNo"]->Value.lVal;
				long nCollectData	= pRS->Fields->Item["unCollectData"]->Value.lVal;
				_bstr_t strBeginTime = pRS->Fields->Item["strBeginTime"]->Value;
				_bstr_t strEndTime	= pRS->Fields->Item["strEndTime"]->Value;

				strSQL.Format("INSERT INTO uCollectData VALUES(%ld,%ld,'%s','%s')",
							nPointNo,
							nCollectData,
							(char *)strBeginTime,
							(char *)strEndTime);
			}

			//uWarnCauseRecord表
			if(strTableName.CollateNoCase("uWarnCauseRecord") == 0)
			{
				long nPointNo		= pRS->Fields->Item["unPointNo"]->Value.lVal;
				_bstr_t Explain		= pRS->Fields->Item["strExplain"]->Value;
				_bstr_t WarnCause	= pRS->Fields->Item["strWarnCause"]->Value;
				_bstr_t strWarnTime = pRS->Fields->Item["strWarnTime"]->Value;
				_bstr_t strNormalTime= pRS->Fields->Item["strNormalTime"]->Value;
				VARIANT va = pRS->Fields->Item["bConfirm"]->Value;
				int nConfirm =0;
				if(va.boolVal)
					nConfirm = 1;

				strSQL.Format("INSERT INTO uWarnCauseRecord VALUES(%ld,'%s','%s','%s','%s',%d)",
							nPointNo,
							(char *)Explain,
							(char *)WarnCause,
							(char *)strWarnTime,
							(char *)strNormalTime,
							nConfirm);

			}

			//uAnologPointProperty表
			if(strTableName.CollateNoCase("uAnologPointProperty") == 0)
			{
				long nPoint			= pRS->Fields->Item["unPointNo"]->Value.lVal;
				double fMeasureMin	= pRS->Fields->Item["fMeasureMin"]->Value.fltVal;
				double fMeasureMax	= pRS->Fields->Item["fMeasureMax"]->Value.fltVal;
				long unBitNumber	= pRS->Fields->Item["unBitNumber"]->Value.lVal;
				long unWarnCause	= pRS->Fields->Item["unWarnCause"]->Value.lVal;
				int unWarnMode		= pRS->Fields->Item["unWarnMode"]->Value.iVal;
				long unWarnMinValue = pRS->Fields->Item["unWarnMinValue"]->Value.lVal;
				long unWarnMaxValue = pRS->Fields->Item["unWarnMaxValue"]->Value.lVal;
				_bstr_t bstrUnit	= pRS->Fields->Item["strUnit"]->Value;
				VARIANT va = pRS->Fields->Item["bPrint"]->Value;
				int nPrint = 0;
				if(va.boolVal)
					nPrint=1;
				int unProcessType	= pRS->Fields->Item["unProcessType"]->Value.iVal;
				int unPrecision		= pRS->Fields->Item["unPrecision"]->Value.iVal;
				long unWarnDelay	= pRS->Fields->Item["unWarnDelay"]->Value.lVal;
				int unProcessType2	=  pRS->Fields->Item["unProcessType2"]->Value.iVal;

				strSQL.Format("UPDATE uAnologPointProperty SET	fMeasureMin = %f,fMeasureMax = %f,unBitNumber = %ld,unWarnCause = %ld,unWarnMode = %d,unWarnMinValue = %ld,unWarnMaxValue = %ld,strUnit = '%s',bPrint = %d,unProcessType = %d,unPrecision = %d,unWarnDelay = %ld,unProcessType2 =%d WHERE unPointNo = %ld",
						fMeasureMin,
						fMeasureMax,
						unBitNumber,
						unWarnCause,
						unWarnMode,
						unWarnMinValue,
						unWarnMaxValue,
						(char *) bstrUnit,
						nPrint,
						unProcessType,
						unPrecision,
						unWarnDelay,
						unProcessType2,
						nPoint);
			}

			//uPointProperty表
			if(strTableName.CollateNoCase("uPointProperty") == 0)
			{
				long nPoint			= pRS->Fields->Item["unPointNo"]->Value.lVal;
				long unTrunkNo		= pRS->Fields->Item["unTrunkNo"]->Value.lVal;
				long unAddress		= pRS->Fields->Item["unAddress"]->Value.lVal;
				int unScanFreq		= pRS->Fields->Item["unScanFreq"]->Value.iVal;
				int nScan = 0, nValueType = 0;
				VARIANT vaScan		= pRS->Fields->Item["bScan"]->Value;
				VARIANT vaType		= pRS->Fields->Item["bValueType"]->Value;
				if (vaScan.boolVal) nScan = 1;
				if (vaType.boolVal) nValueType = 1;
				int unConnectorID	= pRS->Fields->Item["unConnectorID"]->Value.iVal;
				int unSamePointNumber = pRS->Fields->Item["unSamePointNumber"]->Value.iVal;
				int bMultiConv		= pRS->Fields->Item["bMultiConv"]->Value.iVal;
				_bstr_t strLabel	= pRS->Fields->Item["strLabel"]->Value;
				_bstr_t strExplain	= pRS->Fields->Item["strExplain"]->Value;
				int unChannel		= pRS->Fields->Item["unChannel"]->Value.iVal;

				strSQL.Format("UPDATE uPointProperty SET unTrunkNo = %ld,unAddress = %ld,unScanFreq = %d,bScan = %d,bValueType = %d,unConnectorID = %d,unSamePointNumber = %d,bMultiConv = %d,strLabel = '%s',strExplain = '%s',unChannel = %d WHERE unPointNo = %ld",
						unTrunkNo,
						unAddress,
						unScanFreq,
						nScan,
						nValueType,
						unConnectorID,
						unSamePointNumber,
						bMultiConv,
						(char *)strLabel,
						(char *)strExplain,
						unChannel,
						nPoint);
			}

			//uSwitchPointProperty表
			if(strTableName.CollateNoCase("uSwitchPointProperty") == 0)
			{
				long nPoint		= pRS->Fields->Item["unPointNo"]->Value.lVal;
				int unAC		= pRS->Fields->Item["unAC"]->Value.iVal;
				int unWarnCause = pRS->Fields->Item["unWarnCause"]->Value.iVal;
				long un21mode   = pRS->Fields->Item["un21mode"]->Value.lVal;
				int unProcessType = pRS->Fields->Item["unProcessType"]->Value.iVal;
				int unWarnDelay = pRS->Fields->Item["unWarnDelay"]->Value.iVal;
				int unRecordKTime = 0;
				VARIANT vaTime	= pRS->Fields->Item["unRecordKTime"]->Value;
				if(vaTime.boolVal) unRecordKTime = 1;
				_bstr_t strSetKTime = pRS->Fields->Item["unSetKTime"]->Value;
				int nPrint = 0;
				VARIANT vaPrint = pRS->Fields->Item["bPrint"]->Value;
				if(vaPrint.boolVal) nPrint = 1;
				
				strSQL.Format("UPDATE uSwitchPointProperty SET unAC=%d,unWarnCause=%d,un21mode=%ld,unProcessType=%d,unWarnDelay=%d,unRecordKTime=%d,unSetKTime='%s',bPrint=%d WHERE unPointNo = %ld",
						unAC,
						unWarnCause,
						un21mode,
						unProcessType,
						unWarnDelay,
						unRecordKTime,
						(char *)strSetKTime,
						nPrint,
						nPoint);
			}

			//AfxMessageBox(strSQL);	
			SendSQL(strSQL);
			pRS->MoveNext();
		}
		pRS->Close();
	}
	catch(_com_error &e)
	{
		AfxMessageBox(e.ErrorMessage());
	}*/

}

void CMQServer::SyncCRTData(unsigned char  afds, unsigned char  achan,int dbtype)
{
	if(m_one[afds][achan].SFSd == 1)
		return;
	if(!theApp.m_bLogIn)
		return;
	if(!theApp.b_SaveRT)
		return;

	CString strTable;
	int m_nptype = m_SlaveStation[afds][achan].ptype;
	if(dbtype == 0 || dbtype == 2|| dbtype == 4)
	{
		CNDKMessage message(SAVEDBREALTIMEDATA);
		message.Add(1);
		message.Add(m_SlaveStation[afds][achan].m_PID);
		message.Add(m_nptype);
		message.Add(afds);
		message.Add(achan);
   		message.Add(m_SlaveStation[afds][achan].CValue);
   		message.Add(m_SlaveStation[afds][achan].AValue);
		message.Add(m_SlaveStation[afds][achan].Channel_state);
		message.Add(m_ndkRTD[0]);
		message.Add(m_ndkRTD[1]);
		message.Add(m_ndkRTD[2]);
		message.Add(m_ndkRTD[3]);
		message.Add(m_ndkRTD[4]);
		message.Add(m_ndkRTD[5]);
    	strTable = theApp.curuser;
		message.Add(strTable);
		if(dbtype == 0)
		{
		message.Add("");
		message.Add(0);
		message.Add(0);
		message.Add("");
		}
		else if(dbtype == 2)
		{
		message.Add(m_SlaveStation[afds][achan].strSafe);
		message.Add(m_SlaveStation[afds][achan].m_ffds);
		message.Add(m_SlaveStation[afds][achan].m_fchan);
		message.Add(m_SlaveStation[m_SlaveStation[afds][achan].m_ffds][m_SlaveStation[afds][achan].m_fchan].FeedState);
		}
		else
		{
		message.Add("");
		message.Add(0);
		message.Add(0);
		message.Add(m_SlaveStation[afds][achan].FeedState);
		}
//		m_NDKmes[theApp.m_message] =message;
		SendMessageToAllUsers(message);
	}
	else if(dbtype == 1 || dbtype == 3|| dbtype == 5)
	{
		CNDKMessage message(SAVEADJUSTDATA);
		message.Add(1);
		message.Add(m_SlaveStation[afds][achan].m_PID);
		message.Add(m_nptype);
		message.Add(afds);
		message.Add(achan);
   		message.Add(m_SlaveStation[afds][achan].CValue);
    	message.Add(m_SlaveStation[afds][achan].AValue);
		message.Add(m_SlaveStation[afds][achan].Channel_state);
		message.Add(m_ndkRTD[0]);
		message.Add(m_ndkRTD[1]);
		message.Add(m_ndkRTD[2]);
		message.Add(m_ndkRTD[3]);
		message.Add(m_ndkRTD[4]);
		message.Add(m_ndkRTD[5]);
   		strTable = theApp.curuser;
		message.Add(strTable);
		if(dbtype == 1)
		{
		message.Add("");
		message.Add(0);
		message.Add(0);
		message.Add("");
		}
		else if(dbtype == 3)
		{
		message.Add(m_SlaveStation[afds][achan].strSafe);
		message.Add(m_SlaveStation[afds][achan].m_ffds);
		message.Add(m_SlaveStation[afds][achan].m_fchan);
		message.Add(m_SlaveStation[m_SlaveStation[afds][achan].m_ffds][m_SlaveStation[afds][achan].m_fchan].FeedState);
		}
		else
		{
		message.Add("");
		message.Add(0);
		message.Add(0);
		message.Add(m_SlaveStation[afds][achan].FeedState);
		}
		SendMessageToAllUsers(message);
//		m_NDKmes[theApp.m_message] =message;
	}
	else if(dbtype == 10 )
	{
		CNDKMessage message(SAVE5MRTDATA);
		message.Add(1);
		message.Add(m_SlaveStation[afds][achan].m_PID);
		message.Add(m_nptype);
		message.Add(afds);
		message.Add(achan);  //4
    		message.Add(m_SlaveStation[afds][achan].AMinValue);
			float av= m_SlaveStation[afds][achan].ATotalValue/m_SlaveStation[afds][achan].m_Atotal;
    		message.Add(av);
		message.Add(m_SlaveStation[afds][achan].Channel_state);
		message.Add(m_ndkRTD[0]);
		message.Add(m_ndkRTD[1]);
		message.Add(m_ndkRTD[2]);
		message.Add(m_ndkRTD[3]);
		message.Add(m_ndkRTD[4]);
		message.Add(m_ndkRTD[5]);
    	strTable = theApp.curuser;
		message.Add(strTable);
		message.Add(m_SlaveStation[afds][achan].AMaxValue);
		SendMessageToAllUsers(message);
//		m_NDKmes[theApp.m_message] =message;
	}
//	theApp.m_message++;
//	if(theApp.m_message == 50)
//		theApp.m_message = 0;



//    FX_DateTime          (bSave, _T("safemdate"),       m_szsafemdate);
//    FX_VarChar           (bSave, _T("safemtext"),     m_szsafemtext);

//				  COleDateTime oleDateTime=m_SlaveStation[afds][achan].ValueTime;
//				  CString dddd   =   oleDateTime.Format(_T("%Y-%m-%d %H:%M:%S")); 


}