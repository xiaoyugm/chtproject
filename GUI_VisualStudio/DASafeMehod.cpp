// DASafeMehod.cpp : implementation file
//

#include "stdafx.h"
#include "gui_visualstudio.h"
#include "DASafeMehod.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern ADMainDis         m_ADMainDis[MAX_FDS][MAX_CHAN];          //调用显示
extern SlaveStation             m_SlaveStation[MAX_FDS][MAX_CHAN];
/////////////////////////////////////////////////////////////////////////////
// CDASafeMehod dialog


CDASafeMehod::CDASafeMehod(CWnd* pParent /*=NULL*/)
	: CDialog(CDASafeMehod::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDASafeMehod)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDASafeMehod::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDASafeMehod)
		  DDX_Text(pDX, IDC_EDIT_SM, strsm);
	DDV_MaxChars(pDX, strsm, 50);
		  DDX_Control(pDX, IDC_CB_SAFE_M, m_ComBoxSM);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDASafeMehod, CDialog)
	//{{AFX_MSG_MAP(CDASafeMehod)
    ON_BN_CLICKED(IDOK, OnBnOkSM)
//	ON_CBN_SELCHANGE(IDC_CB_SAFE_M, OnchCB)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDASafeMehod message handlers

BOOL CDASafeMehod::OnInitDialog()
{
  CDialog::OnInitDialog();
  CString szConnect = _T("Provider=SQLOLEDB.1;Persist Security Info=True;\
                          User ID=sa;Password=sunset;\
                          Data Source=") +strDBname+ _T(";Initial Catalog=BJygjl");

//All calls to the AxLib should be wrapped in a try / catch block
  try
  {
    dbAx::Init();
    m_Cn.Create();
//    m_Cn._SetConnectionEvents(new CCardFileEvents);
    m_Cn.CursorLocation(adUseClient);
    m_Cn.Open((LPCTSTR)szConnect);
		m_PointDes.Create();
		m_PointDes.CursorType(adOpenDynamic);
		m_PointDes.CacheSize(50);
		m_PointDes._SetRecordsetEvents(new CAccountSetEvents);
		m_PointDes.Open(_T("Select * From pointdescription WHERE fdel=0"), &m_Cn);
		m_PointDes.MarshalOptions(adMarshalModifiedOnly);

//	    m_RealtimedataNew = &theApp.socketClient.m_Realtimedata;
  }
  catch ( dbAx::CAxException *e )
  {
    AfxMessageBox(e->m_szErrorDesc,  MB_OK);
    delete e;
    return (FALSE);
  }
	CString strstartTime,strname,dddd;
	int eYear;
		int iItem = 0;
		m_PointDes.MoveFirst();
		while ( !m_PointDes.IsEOF() )
		{
			eYear = m_PointDes.m_szptype;
			if((eYear < 3) || (eYear > 12)||(eYear == 10))
			{
             		int nfds = m_PointDes.m_szfds;
              		int nchan = m_PointDes.m_szchan;
				strname = m_SlaveStation[nfds][nchan].WatchName;
				strstartTime = m_PointDes.m_szpointnum;
				strstartTime.TrimRight();
				dddd = strstartTime + strname;
               	m_ComBoxSM.AddString(dddd);
   		       iItem++;
			}
			m_PointDes.MoveNext();
		}
  return TRUE;  // return TRUE unless you set the focus to a control
  // EXCEPTION: OCX Property Pages should return FALSE
}

void CDASafeMehod::OnchCB()
{
//			strSQL.Format("INSERT INTO uCollectData VALUES(%d,%d,'%s','%s')",unPointNo,unCollectData,strBeginTime,strEndTime);
/*	CString szConnect;
		int eyear;	unsigned char emonth;
		CTime t=CTime::GetCurrentTime();
		theApp.socketClient.CalRtDB(t , eyear , emonth);
		CString sztime;
		sztime.Format("%d",eyear);
		szConnect = "Select * From rt";
		szConnect += sztime;
		if(emonth>9)
     		sztime.Format("%d",emonth);
		else
     		sztime.Format("0%d",emonth);
		szConnect += sztime;
		szConnect += "data";

		m_Realtimedata.Create();
		m_Realtimedata.CursorType(adOpenDynamic);
		m_Realtimedata.CacheSize(50);
//		m_Realtimedata._SetRecordsetEvents(new CAccountSetEvents);
		m_Realtimedata.Open( szConnect , &m_Cn);
		m_Realtimedata.MarshalOptions(adMarshalModifiedOnly);*/
//	    m_RealtimedataNew = &theApp.socketClient.m_Realtimedata;
}

void CDASafeMehod::OnClose()
{
  //Closing of library objects is ensured as each object
  //goes out of scope, but doing a manual shutdown doesn抰 hurt.

  try
  {
    if ( m_PointDes._IsOpen() )
      m_PointDes.Close();
//    if ( m_Realtimedata._IsOpen() )
//      m_Realtimedata.Close();

    m_Cn.Close();

    //Cleanup the AxLib library
    dbAx::Term();
  }
  catch ( CAxException *e )
  {
    MessageBox(e->m_szErrorDesc, _T("BJygjl Message"), MB_OK);
    delete e;
  }
}

//BOOL CSafeMethod::DestroyWindow() 
//{
//	OnClose();
//	return CDialog::DestroyWindow();
//}

void CDASafeMehod::OnBnOkSM()
{
    CMainFrame* pFWnd=(CMainFrame*)AfxGetMainWnd();
	CString strItem, strf,strc,strSQL;
    CString strstartTime,strname,dddd;
			UpdateData(TRUE);           //Exchange dialog data
	int  kkkk = m_ComBoxSM.GetCurSel();
	if(kkkk == -1 || strsm == "")
	{
        AfxMessageBox("请选择测点和输入安全措施！");
		return;
	}
	m_ComBoxSM.GetLBText(kkkk,strname);
	strname = strname.Mid(0,5);
    		strf = strname.Mid(0,2);
    		strc = strname.Mid(3);
		int afds = m_Str2Data.String2Int(strf);
		int achan = m_Str2Data.String2Int(strc);
//		strItem = _T("Select * From realtimedata WHERE ");
//		strname.Format("fds=%d and chan=%d",nfds,nchan);

			COleDateTime COTime;
		CTime t=CTime::GetCurrentTime();
		CString sztime1,sztime2,sztime;
		sztime1.Format("rt%d",t.GetYear());
   		sztime2.Format("%02ddata",t.GetMonth());
		sztime = sztime1+sztime2;
		sztime1 = t.Format(_T("%Y-%m-%d %H:%M:%S"));
//			CString strCTime;
	//		strNormalTime.Format("%d-%d-%d %d:%d:%d",NormalTime.GetYear(),NormalTime.GetMonth(),NormalTime.GetDay(),NormalTime.GetHour(),NormalTime.GetMinute(),NormalTime.GetSecond());
							 int m_nptype = m_SlaveStation[afds][achan].ptype;
					m_SlaveStation[afds][achan].ValueTime = COTime.GetCurrentTime();


					theApp.m_resnum = 10;
					m_SlaveStation[afds][achan].strSafe = strsm;
					m_SlaveStation[afds][achan].ValueTime = COTime.GetCurrentTime();
							 if(m_nptype >3)
							 {
 	strSQL.Format("INSERT INTO %s (PID,ptype,fds,chan,CDValue,AValue,ADStatus,recdate,Useridadd,safemtext,ffds,fchan,FeedStatus) VALUES(%d,%d,%d,%d,%d,0,%d,'%s','%s','%s',0,0,'')",sztime,m_SlaveStation[afds][achan].m_PID
		,m_nptype,afds,achan,m_SlaveStation[afds][achan].CValue,m_SlaveStation[afds][achan].Channel_state
		,sztime1,theApp.curuser,strsm);
        	theApp.m_pConnection->Execute(_bstr_t(strSQL),NULL,adCmdText);
							m_ADMainDis[afds][achan].NTime = COTime.GetCurrentTime();
                                  pFWnd->m_wndResourceView4.InitLDAB(afds,achan);
							 }
							 else
							 {
 	strSQL.Format("INSERT INTO %s (PID,ptype,fds,chan,CDValue,AValue,ADStatus,recdate,Useridadd,safemtext,ffds,fchan,FeedStatus) VALUES(%d,%d,%d,%d,0,%.2f,%d,'%s','%s','%s',0,0,'')",sztime,m_SlaveStation[afds][achan].m_PID
		,m_nptype,afds,achan,m_SlaveStation[afds][achan].AValue,m_SlaveStation[afds][achan].Channel_state
		,sztime1,theApp.curuser,strsm);
        	theApp.m_pConnection->Execute(_bstr_t(strSQL),NULL,adCmdText);
                                  pFWnd->m_wndResourceView.InitLC(afds,achan);
							 }
	
	/*            				try
							{
	         				 m_RealtimedataNew->m_szRTID  = 1;
		      			     m_RealtimedataNew->m_szPID = m_SlaveStation[afds][achan].m_PID;
							 int m_nptype = m_SlaveStation[afds][achan].ptype;
		    			     m_RealtimedataNew->m_szptype = m_nptype;
    						 m_RealtimedataNew->m_szfds = afds;
     						 m_RealtimedataNew->m_szchan = achan;
					theApp.m_resnum = 10;
					m_SlaveStation[afds][achan].strSafe = strsm;
					m_SlaveStation[afds][achan].ValueTime = CTime.GetCurrentTime();
							 if(m_nptype >3)
							 {
							m_ADMainDis[afds][achan].NTime = CTime.GetCurrentTime();
    						      m_RealtimedataNew->m_szCDValue = m_SlaveStation[afds][achan].CValue;
     				   		      m_RealtimedataNew->m_szAValue = 0;
                                  pFWnd->m_wndResourceView4.InitLDAB(afds,achan);
							 }
							 else
							 {
    						      m_RealtimedataNew->m_szCDValue = 0;
     				   		      m_RealtimedataNew->m_szAValue = m_SlaveStation[afds][achan].AValue;
                                  pFWnd->m_wndResourceView.InitLC(afds,achan);
							 }
    						 m_RealtimedataNew->m_szADStatus = m_SlaveStation[afds][achan].Channel_state;
    						 m_RealtimedataNew->m_szrecdate = CTime.GetCurrentTime();
     						 m_RealtimedataNew->m_szUseridadd = theApp.curuser;
//    						 m_RealtimedataNew->m_szsafemdate = CTime.GetCurrentTime();
    						 m_RealtimedataNew->m_szsafemtext = strsm;
							}*/
	OnClose();
    EndDialog(IDOK);
}

void CDASafeMehod::OnCancel() 
{
	// TODO: Add extra cleanup here
	OnClose();
	CDialog::OnCancel();
}