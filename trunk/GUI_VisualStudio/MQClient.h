// MQClient.h: interface for the CMQClient class.
//
//////////////////////////////////////////////////////////////////////


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define MAX_ROW     400  //最大行数 50

#include "MQCommandType.h"
//#include "drawobj.h"

class CMQClient :public CNDKClient
{
public:
	CMQClient();
	virtual ~CMQClient();
public:
	void GetHostStartTime(CNDKMessage& message);
///	CDrawDoc* GetDocument();
	BOOL SendMessage(CNDKMessage& message);
	BOOL ConnectServer(CString strIp,UINT lPort);
	BOOL Ping();
	void Close();
	void HostStateCheck();

    BYTE     m_ndkSendRT[BUFFER_SIZE];//44BUFFER_SIZE
	BYTE     m_ndkSend2[BUFFER_SIZE];//44如果小于发来数据，退出报错  derror
	UINT		   m_unBufferLength;

protected:

	virtual void OnMessage(CNDKMessage& message);	
	virtual void OnDisconnect(NDKClientDisconnection disconnectionType);
	virtual void OnPing(long lNbMilliseconds);

	void WriteSQL(CNDKMessage& message);
//	CSQLDirect m_SQLDirect;

	CTime StartTime, ConnectTime;
	
	void ManageServer(CNDKMessage& message);
	void ManageServerG(CNDKMessage& message);

	void CollectDate(CNDKMessage& message);
	
};

