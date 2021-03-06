// MQServer.h: interface for the CMQServer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MQSERVER_H__F9E39710_AF00_4A6B_A158_7E80CB1399BD__INCLUDED_)
#define AFX_MQSERVER_H__F9E39710_AF00_4A6B_A158_7E80CB1399BD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "NDK\\NDKServer.h"
#include "MQCommandType.h"

class CMQServer :public CNDKServer
{
public:
	CMQServer();
	virtual ~CMQServer();
public:
	BOOL Listenning(long lPort = 6000);
	BOOL SendMessage(CNDKMessage& message);

	BOOL SendSQL(CString strSql);
	BOOL SendStartTime(CTime time);

	CString2DataType m_String2DataType;
	void StopServer();
    unsigned char *m_ndkSend;
	void ManageClientD();
	void SyncTableCollectData();

protected:
	CString m_strIP;
	CString m_strPort;
	
	CTime tHostStartTime;
	// Called when a user is connected to the server. The derived class must 
	// override this method.
	void OnConnect(long lUserId);

	// Called whenever a message is received from a user. The derived class must 
	// override this method.
	void OnMessage(long lUserId, CNDKMessage& message);

	void OnDisconnect(long lUserId, NDKServerDisconnection disconnectionType);
	BOOL OnIsConnectionAccepted();

	CSQLDirect m_SQLDirect;
	void ConnectDB();
	void SyncTableuWarnCauseRecord();

	void ManageClientG(CNDKMessage& message);
	void ManageClientK(CNDKMessage& message);

	void Sync(CNDKMessage& message);
	void SendAllData(CNDKMessage& message);

};

#endif // !defined(AFX_MQSERVER_H__F9E39710_AF00_4A6B_A158_7E80CB1399BD__INCLUDED_)
