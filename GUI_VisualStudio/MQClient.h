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

#include "dbAx\AxSControl.hpp"
//#include "dbAx\AxControl.hpp"
//#include "dbAx\AxAccountSet.hpp"
#include "dbAx\AxContactCmd.hpp"
//#include "dbAx\AxContactSet.hpp"
#include "dbAx\CardFileEvents.hpp"
#include "dbAx\AccountSetEvents.hpp"

class CMQClient :public CNDKClient
{
public:
	CMQClient();
	virtual ~CMQClient();
public:
	void GetHostStartTime(CNDKMessage& message);
///	CDrawDoc* GetDocument();
	BOOL SendMessage(CNDKMessage& message);
	BOOL ConnectServer(CString strIp,long lPort);
	BOOL Ping();
	void Close();
    void AddWarn(CString strtemp, CString strtemp1, CString strtemp2, CString strtemp3, CString strtemp4, CString strtemp5, CString strtemp6, CString strtemp7);
	void HostStateCheck();

	CString strstatus(unsigned char  ustatus);
	void handbr(unsigned char  hfds, unsigned char  hchan, unsigned char hbr);
	void SaveAdjust(unsigned char  afds, unsigned char  achan);
	void SaveRtdata(unsigned char  afds, unsigned char  achan);
    unsigned char *m_ndkSend;
    unsigned char *m_ndkSend1;
	BOOL m_nodialog;
	long m_adjustnum; 
	

    CAxConnection   m_Cn;
    CAxContactCmd   m_ContactCmd;
    CAdjustdata     m_Adjustdata;
    CAdjustdata     *m_AdjustdataNew;
	CRealtimedata   m_Realtimedata;
	CRealtimedata   *m_RealtimedataNew;

	void ConnectDB();

protected:

	void OnMessage(CNDKMessage& message);	
	void OnDisconnect(NDKClientDisconnection disconnectionType);
	void OnPing(long lNbMilliseconds);

	void WriteSQL(CNDKMessage& message);
	CSQLDirect m_SQLDirect;

	CTime StartTime, ConnectTime;
	
	void ManageServer(CNDKMessage& message);
	void ManageServerG(CNDKMessage& message);

	void DiaplayWarnTableC(unsigned short nPointNo);
	void CollectDate(CNDKMessage& message);
	
};

#endif // !defined(AFX_MQCLIENT_H__06598D7B_DFFC_4FFF_B8E5_883979A1282F__INCLUDED_)
