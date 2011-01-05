// RTDataManage.h: interface for the CRTDataManage class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RTDATAMANAGE_H__4B85A571_00A1_4CD5_85D6_DF9E2533017E__INCLUDED_)
#define AFX_RTDATAMANAGE_H__4B85A571_00A1_4CD5_85D6_DF9E2533017E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CRTDataManage  
{
public:
	CRTDataManage();
	virtual ~CRTDataManage();

	CString strstatus(unsigned char  ustatus);
	void Savefeedbr(unsigned char  hfds, unsigned char  hchan);
	void feedbr(unsigned char  hfds, unsigned char  hchan);
	void handbr(unsigned char  hfds, unsigned char  hchan, unsigned char hbr);
	void SendPP(unsigned char  afds);
	void SyncCRTData(unsigned char  afds, unsigned char  achan,int dbtype);
	BOOL m_nodialog;
	CString  strdbname;
	int      n_month; 
	BYTE     m_ndkSend1[6];//6
	BYTE     m_ndkSend2[BUFFER_SIZE];//44如果小于发来数据，退出报错  derror
	vector<CString> m_Initdata;
	ListV m_strdf[11][101];
	ListV m_strdfall[11][101];
	ListV m_s3draw[101];
	DIDVer m_iddf[11][101];
	
	void CalRtDB(CTime time ,int &eYear, unsigned char  &eMonth);
	void CalTime(COleDateTime time);
	void CalRTdata(int fds);
	void ConnectDB();
	void FCError(int nstation);
	void NCSuccess();
	void NCError();
	void SaveRT24Data(unsigned char  nstation, unsigned char  nItem,unsigned char  n524);
	BOOL CalRelationW(unsigned char  nfds, unsigned char  nchan);
	BOOL CalRelationD(unsigned char  nfds, unsigned char  nchan);
	BOOL CalRelationF(unsigned char  nfds, unsigned char  nchan);
	BOOL CalRelationC(unsigned char  nfds, unsigned char  nchan);
	void ResumeAB(unsigned char  nstation, unsigned char  nItem);

	POSITION	m_ViewPos;
	BOOL   Initdrawfile();
	void CloseDrawfile(CString dfile);

	int    Initfbl(CString strfbl);
	BOOL   InitDisplay();

	void DiaplayWarnTableC(unsigned short nPointNo);
    void AddWarn(CString strtemp, CString strtemp1, CString strtemp2, CString strtemp3, CString strtemp4, CString strtemp5, CString strtemp6, CString strtemp7);
};

#endif // !defined(AFX_RTDATAMANAGE_H__4B85A571_00A1_4CD5_85D6_DF9E2533017E__INCLUDED_)
