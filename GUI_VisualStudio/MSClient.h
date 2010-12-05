// MQClient.h: interface for the CMQClient class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MSCLIENT_H__06598D7B_DFFC_4FFF_B8E5_883979A1282E__INCLUDED_)
#define AFX_MSCLIENT_H__06598D7B_DFFC_4FFF_B8E5_883979A1282E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define MAX_ROW     400  //最大行数 50

#include "MQCommandType.h"
#include "drawobj.h"

class CMSClient :public CNDKClient
{
public:
	CMSClient();
	virtual ~CMSClient();
public:
	void GetServerd(CNDKMessage& message);
///	CDrawDoc* GetDocument();
	BOOL SendMessage(CNDKMessage& message);
	BOOL ConnectServer(CString strIp,UINT lPort);
	BOOL Ping();
	void Close();

//	BOOL m_nodialog;
	long m_adjustnum; 
	void HostStateCheck();

	void ConnectDB();

protected:

	void OnMessage(CNDKMessage& message);	
	void OnDisconnect(NDKClientDisconnection disconnectionType);
	void OnPing(long lNbMilliseconds);

	void WriteSQL(CNDKMessage& message);
//	CSQLDirect m_SQLDirect;

	CTime StartTime, ConnectTime;

};

#endif // !defined(AFX_MQCLIENT_H__06598D7B_DFFC_4FFF_B8E5_883979A1282F__INCLUDED_)
