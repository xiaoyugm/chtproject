// MQClient.h: interface for the CMQClient class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MQCLIENT_H__06598D7B_DFFC_4FFF_B8E5_883979A1282F__INCLUDED_)
#define AFX_MQCLIENT_H__06598D7B_DFFC_4FFF_B8E5_883979A1282F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "NDK\\NDKClient.h"
#include "MQCommandType.h"
#include "SQL\\sqldirect.h"

class CMQClient :public CNDKClient
{
public:
	CMQClient();
	virtual ~CMQClient();
public:

	BOOL SendMessage(CNDKMessage& message);
	BOOL ConnectServer(CString strIp,long lPort);
	BOOL Ping();
	void Close();

	void HostStateCheck();
protected:

	void OnMessage(CNDKMessage& message);	
	void OnDisconnect(NDKClientDisconnection disconnectionType);
	void OnPing(long lNbMilliseconds);

	void ConnectDB();
	void WriteSQL(CNDKMessage& message);
	CSQLDirect m_SQLDirect;
	CString2DataType    m_Str2Data;

	CTime StartTime, ConnectTime;
	
	void GetHostStartTime(CNDKMessage& message);
	BOOL SyncHostAndClient();
};

#endif // !defined(AFX_MQCLIENT_H__06598D7B_DFFC_4FFF_B8E5_883979A1282F__INCLUDED_)
