// MFClient.h: interface for the CMQClient class.
//
//////////////////////////////////////////////////////////////////////


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <String2DataType.h>
#include "MQCommandType.h"

class CMFClient :public CNDKClient
{
public:
	CMFClient();
	virtual ~CMFClient();
public:
	void GetFiles(CNDKMessage& message);
///	CDrawDoc* GetDocument();
	BOOL SendMessage(CNDKMessage& message);
	BOOL ConnectServer(CString strIp,UINT lPort);
	BOOL Ping();
	void Close();
	CString2DataType    m_Str2Data;
	vector<CString> v_disdrawf;

	int  m_vdf; 
	void HostStateCheck();

	void ConnectDB();
	void SyncMenu(CNDKMessage& message);
	void Syncdown(int n_files);
	void downdfiles(CString strfile);
	void GetTableData(int nline);
	void SaveFileS3();

protected:

	void OnMessage(CNDKMessage& message);	
	void OnDisconnect(NDKClientDisconnection disconnectionType);
	void OnPing(long lNbMilliseconds);

	void WriteSQL(CNDKMessage& message);
//	CSQLDirect m_SQLDirect;

	CTime StartTime, ConnectTime;

//	CProgressCtrl  m_progressDownload;
	BOOL           m_bIsDownloading;
	CFile          m_fileDownload;
	int            m_nFileSize;
	BYTE           m_byteBuffer[BUFFER_SIZE];
	UINT		   m_unBufferLength;
};

