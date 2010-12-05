// MFClient.h: interface for the CMQClient class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MFCLIENT_H__07598D7B_DFFC_4FFF_B8E5_883979A1282A__INCLUDED_)
#define AFX_MFCLIENT_H__07598D7B_DFFC_4FFF_B8E5_883979A1282A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <String2DataType.h>
#include "MQCommandType.h"
#include "dbAx\CardFileEvents.hpp"
#include "dbAx\AxLogin.hpp"

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
    CCardFileEvents *pCnEvents;
    CAxConnection   m_Cn;
	CAxDrawfile     m_Drawfile;
	BOOL   Initdrawfile();
	ListV m_s3draw[101];
	ListV m_strdfall[11][101];
	ListV m_strdf[11][101];
	DIDVer m_iddf[11][101];
	vector<CString> v_disdrawf;
	POSITION	m_ViewPos;

//	BOOL m_nodialog;
	int  m_vdf; 
	void HostStateCheck();

	void ConnectDB();
	void SyncMenu(CNDKMessage& message);
	void Syncdown(int n_files);
	void downdfiles(CString strfile);
	void GetTableData(int nline);
	void CloseDrawfile(CString dfile);
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

#endif // !defined(AFX_MFCLIENT_H__06598D7B_DFFC_4FFF_B8E5_883979A1282G__INCLUDED_)
