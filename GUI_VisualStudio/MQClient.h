// MQClient.h: interface for the CMQClient class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MQCLIENT_H__06598D7B_DFFC_4FFF_B8E5_883979A1282F__INCLUDED_)
#define AFX_MQCLIENT_H__06598D7B_DFFC_4FFF_B8E5_883979A1282F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define MAX_ROW     50  //最大行数 50

#include "MQCommandType.h"
#include "drawobj.h"

class CMQClient :public CNDKClient
{
public:
	CMQClient();
	virtual ~CMQClient();
public:

///	CDrawDoc* GetDocument();
	BOOL SendMessage(CNDKMessage& message);
	BOOL ConnectServer(CString strIp,long lPort);
	BOOL Ping();
	void Close();
    void AddWarn( CString strPoint, CString strDate, CString strTime, CString strText, CString strWarn);

	void HostStateCheck();
protected:

	void OnMessage(CNDKMessage& message);	
	void OnDisconnect(NDKClientDisconnection disconnectionType);
	void OnPing(long lNbMilliseconds);

	void ConnectDB();
	void WriteSQL(CNDKMessage& message);
	CSQLDirect m_SQLDirect;

	CTime StartTime, ConnectTime;
	
	void DiaplayWarnTableC(unsigned short nPointNo);
	void CollectDate(CNDKMessage& message);
	void InitPointDate(CNDKMessage& message);
	
};

#endif // !defined(AFX_MQCLIENT_H__06598D7B_DFFC_4FFF_B8E5_883979A1282F__INCLUDED_)
