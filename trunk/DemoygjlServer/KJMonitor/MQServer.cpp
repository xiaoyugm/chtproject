// MQServer.cpp: implementation of the CMQServer class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "kjmonitor.h"
#include "MQServer.h"
#include "MainFrm.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

static BOOL bIsConnect = FALSE;
extern  AllDate ;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMQServer::CMQServer()
{
	tHostStartTime = CTime::GetCurrentTime();
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
//	case COLLECTDATA:       //uCollectData:
//		SyncTableCollectData();
//		break;
//	case COLLECTDATAD:       //
//		SyncTableCollectData();
//		break;
	case SENDSTARTTIME:
		break;
	case REALTIMEDATA:    //uWarnCauseRecord:
//		SyncTableuWarnCauseRecord();
		ManageClientm(message);
		break;
//	case SYNC:
//		Sync(message);
//		break;
//	case ALLDATA:
//		SendAllData(message);
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
//			return TRUE;
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
		message.Add(tHostStartTime.GetYear());
		message.Add(tHostStartTime.GetMonth());
		message.Add(tHostStartTime.GetDay());
		message.Add(tHostStartTime.GetHour());
		message.Add(tHostStartTime.GetMinute());
		message.Add(tHostStartTime.GetSecond());
		
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
					+ gstrIP;
	try
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
	}
}

void CMQServer::ManageClientm(CNDKMessage& message)
{
	CString ggggg,strtemp,strbegin;
    unsigned char  nstation ,nbegin,nend,ncommand ,ufData;
	message.GetAt(0,nbegin);
	message.GetAt(1,nstation);
	message.GetAt(2,ncommand);
	message.GetAt(3,nend);

	srand( (unsigned)time( NULL ) );//srand()函数产生一个以当前时间开始的随机种子.应该放在for等循环语句前面 不然要很长时间等待
	unsigned char N100 = rand() % 101;
	unsigned char N8 = rand() % 9;
	unsigned char N255 = rand() % 255;
	CTime t = CTime::GetCurrentTime();

	if(ncommand == 0x44)   //D
	{
    	CNDKMessage message1(REALTIMEDATA);

					message1.Add(nbegin);
					message1.Add(nstation);
	 				message1.Add(ncommand);

					message1.Add(N8);
	 				message1.Add(N100);             //1通道
					message1.Add(N8);
	 				message1.Add(N100*2);          //2
					message1.Add(N8);
	 				message1.Add(N100+10);         //3
					message1.Add(N8);
	 				message1.Add(N8);               //4
					message1.Add(N8);
	 				message1.Add(N8*10);            //5
					message1.Add(N8);
	 				message1.Add(N8*20);           //6
					message1.Add(N8);
	 				message1.Add(N8*30);            //7

					message1.Add(N255);

//				    strtemp=t.Format("%Y-%m-%d %H:%M:%S");     //BCD转为标准日期格式，作为字符串发送
					message1.Add(10);
					message1.Add(07);
					message1.Add(01);
					message1.Add(17);
					message1.Add(8);
					message1.Add(9);

					message1.Add(nend);
					theApp.SendMessage(message1);

	}
	if(ncommand == 0x54)//T
	{
	}
	if(ncommand == 0x4B)//K
	{
	}
	if(ncommand == 0x43)//C
	{
	}
	if(ncommand == 0x47)//G
	{
	}
	if(ncommand == 0x46)//F
	{
	}
	if(ncommand == 0x5A)//Z
	{
	}





	strbegin.Format("[%d][%d][%d][%d]",nbegin,nstation,ncommand,nend);
	ggggg = ggggg + strbegin;

    AfxMessageBox(ggggg);
}


void CMQServer::SyncTableuWarnCauseRecord()
{
	CString strTable;
	CString strDate;
	strDate.Format("%d/%d/%d",tHostStartTime.GetMonth(), tHostStartTime.GetDay(), tHostStartTime.GetYear());
	strTable.Format("SELECT unPointNo,strExplain,strWarnCause,strWarnTime,strNormalTime,bConfirm FROM uWarnCauseRecord WHERE (strWarnTime>CONVERT(DATETIME,'%s', 101)) OR (strNormalTime>CONVERT(DATETIME,'%s', 101))",strDate,strDate);

	CString strDBLink = "Provider=SQLOLEDB.1;Persist Security Info=False;User ID=kj86;Password=kj86;Initial Catalog=masterdefine;Data Source="
					+ gstrIP;
	try
	{
		_RecordsetPtr pRS;
		pRS.CreateInstance(__uuidof(Recordset));
		pRS->Open(_bstr_t(strTable),_bstr_t(strDBLink), adOpenStatic ,adLockReadOnly , adCmdText );
		COleDateTime WarnTime,NormalTime;
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
	}
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
					+ gstrIP;

	try
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
				_variant_t strEndTime = pRS->Fields->Item["strEndTime"]->Value;
				strSQL.Format("INSERT INTO uCollectData VALUES(%d,%d,'%s','%s')",
							nPointNo,
							nCollectData,
							(char *)strBeginTime,
							(char *)strEndTime.bstrVal);
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
				float fMeasureMin	= pRS->Fields->Item["fMeasureMin"]->Value.fltVal;
				float fMeasureMax	= pRS->Fields->Item["fMeasureMax"]->Value.fltVal;
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
	}

}

void CMQServer::SendAllData(CNDKMessage& message)
{
       AllDate = TRUE;
}
