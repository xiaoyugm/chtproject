// MadeCertView.cpp : implementation file
//

#include "stdafx.h"
#include "GUI_VisualStudio.h"
#include "MadeCertView.h"
#include "ChildFrm.h"
//#include "ViewInfoDlg.h"
#include "MainFrm.h"
//#include "MadeCertDlg.h"

#include "ExcelFormat.h"
using namespace ExcelFormat;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern ADMainDis         m_ADRecord[65][25][266];          //记录查询
extern SlaveStation             m_SlaveStation[65][25];
extern  OthersSetting    m_OthersSetting;
extern SerialF               m_ClassTime[200];            //班设置
/////////////////////////////////////////////////////////////////////////////
// CMadeCertView
//extern CString str[35];
IMPLEMENT_DYNCREATE(CMadeCertView, CFormView)

CMadeCertView::CMadeCertView()
	: CFormView(CMadeCertView::IDD)
{
	//{{AFX_DATA_INIT(CMadeCertView)
	m_select=-1;
	m_stragrv ="";
	m_ctrlStartH = m_ClassTime[1].ffds;
	m_ctrlEndH = m_ClassTime[1].ffds-1;
	m_startDateTime = CTime::GetCurrentTime();
	m_endDateTime = CTime::GetCurrentTime();
//	m_bitMadeView.LoadBitmap(IDB_BITMAPVIEWMADE);
//	m_bitMadeViewUser.LoadBitmap(IDB_BITMAPVIEWUSER);
//	m_bitMadeCert.LoadBitmap(IDB_BITMAPMADECERT);
	//}}AFX_DATA_INIT

}

CMadeCertView::~CMadeCertView()
{
}

void CMadeCertView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMadeCertView)
	DDX_Text(pDX, IDC_E_START, m_ctrlStartH);
	DDX_Text(pDX, IDC_E_END, m_ctrlEndH);
	DDV_MinMaxUInt(pDX, m_ctrlStartH, 0, 23);
	DDV_MinMaxUInt(pDX, m_ctrlEndH, 0, 23);
	DDX_Control(pDX, IDC_R_START, m_ctrlStartTime);
	DDX_Control(pDX, IDC_R_END, m_ctrlEndTime);
	DDX_Control(pDX, IDC_COMBMADE, m_ComBoxSM);
//	DDX_Control(pDX, IDC_LIST_MADE, m_List);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMadeCertView, CFormView)
	//{{AFX_MSG_MAP(CMadeCertView)
	ON_BN_CLICKED(IDOKSEARCH, OnBOKSEARCH)
	ON_CBN_SELCHANGE(IDC_COMBMADE, OnchangeComboSM)
//	ON_BN_CLICKED(IDC_BUTTON_VIEWINFO, OnButtonViewinfo)
///	ON_BN_CLICKED(IDC_BUTTON_AUT_MADE, OnButtonAutMade)
//	ON_NOTIFY(NM_CLICK, IDC_LIST_MADE, OnClickListMade)
	ON_EN_CHANGE(IDC_E_START, OnChangeEditStarth)
	ON_EN_CHANGE(IDC_E_END, OnChangeEditEndh)
	ON_NOTIFY(DTN_CLOSEUP, IDC_R_START, OnDatetimestart)
	ON_NOTIFY(DTN_CLOSEUP, IDC_R_END, OnDatetimeend)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMadeCertView diagnostics

#ifdef _DEBUG
void CMadeCertView::AssertValid() const
{
	CFormView::AssertValid();
}

void CMadeCertView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMadeCertView message handlers

void CMadeCertView::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();
//	((CButton*)GetDlgItem(IDC_BUTTON_LINEANDMADE))->SetBitmap(m_bitMadeView);
//	((CButton*)GetDlgItem(IDC_BUTTON_VIEWINFO))->SetBitmap(m_bitMadeViewUser);
//	((CButton*)GetDlgItem(IDC_BUTTON_AUT_MADE))->SetBitmap(m_bitMadeCert);
//    	GetParentFrame()->MoveWindow(CRect(50,100,960,700));
//	GetParentFrame()->SetWindowPos(NULL,0,0,GetSystemMetrics(SM_CXSCREEN)-8,140,SWP_NOMOVE|SWP_NOZORDER | SWP_NOACTIVATE|SWP_SHOWWINDOW);
    CString szConnect = _T("Provider=SQLOLEDB.1;Persist Security Info=True;\
                          User ID=sa;Password=sunset;\
                          Data Source=") +m_OthersSetting.DBname+ _T(";Initial Catalog=BJygjl");
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
//		m_PointDes._SetRecordsetEvents(new CAccountSetEvents);
		m_PointDes.Open(_T("Select * From pointdescription WHERE fdel=0"), &m_Cn);
		m_PointDes.MarshalOptions(adMarshalModifiedOnly);
  }
  catch ( dbAx::CAxException *e )
  {
		AfxMessageBox(e->m_szErrorDesc +  _T("BJygjl Message"));
//    MessageBox(e->m_szErrorDesc, _T("BJygjl Message"), MB_OK);
    delete e;
    return ;
  }

	CString strstartTime,strname,dddd;
    	int eYear;
		int iItem = 0;
	if(theApp.strargc == "OnRECASR")
	{
    	if(!m_PointDes._IsEmpty())
		{
    		m_PointDes.MoveFirst();
	     	while ( !m_PointDes.IsEOF() )
			{
	    		eYear = m_PointDes.m_szptype;
	    		if(eYear < 3)
				{
				strname = m_PointDes.m_szName;
				strname.TrimRight();
				strstartTime = m_PointDes.m_szpointnum;
				strstartTime.TrimRight();
				dddd = strstartTime + strname;
               	m_ComBoxSM.AddString(dddd);
				}
	    		m_PointDes.MoveNext();
			}
		}
	}
	else if(theApp.strargc == "OnRECDSCD")
	{
    	if(!m_PointDes._IsEmpty())
		{
    		m_PointDes.MoveFirst();
	     	while ( !m_PointDes.IsEOF() )
			{
	    		eYear = m_PointDes.m_szptype;
	    		if(eYear > 9)
				{
				strname = m_PointDes.m_szName;
				strname.TrimRight();
				strstartTime = m_PointDes.m_szpointnum;
				strstartTime.TrimRight();
				dddd = strstartTime + strname;
               	m_ComBoxSM.AddString(dddd);
				}
	    		m_PointDes.MoveNext();
			}
		}
	}
	else
	{
    	if(!m_PointDes._IsEmpty())
		{
    		m_PointDes.MoveFirst();
	     	while ( !m_PointDes.IsEOF() )
			{
	    		eYear = m_PointDes.m_szptype;
	    		if((eYear < 3) || (eYear > 12)||(eYear == 10))
				{
				strname = m_PointDes.m_szName;
				strname.TrimRight();
				strstartTime = m_PointDes.m_szpointnum;
				strstartTime.TrimRight();
				dddd = strstartTime + strname;
               	m_ComBoxSM.AddString(dddd);
   		       iItem++;
				}
	    		m_PointDes.MoveNext();
			}
		}
	}
//	((CComboBox *)GetDlgItem(IDC_COMBO1))->SetCurSel(0);

	// TODO: Add your specialized code here and/or call the base class
//	m_List.SetWindowPos(NULL,0,0,1024,400,SWP_NOMOVE|SWP_NOZORDER | SWP_NOACTIVATE);
//	m_List.SetExtendedStyle(LVS_EX_FULLROWSELECT);

	for(int i=0;i<10;i++)
	{
//		m_List.InsertColumn(i,strname[i],LVCFMT_LEFT,120);
	}
	if(theApp.strargc == "OnALARMS")
	{
    	GetDlgItem(IDC_COMBMADE)->ShowWindow(SW_HIDE);;
//    	GetDlgItem(IDC_CHECK_ISALM)->ShowWindow(SW_SHOW);;
       	GetParentFrame()->SetWindowText("报警记录查询");
	}
	else if(theApp.strargc == "OnBREAKES")
	{
    	GetDlgItem(IDC_COMBMADE)->ShowWindow(SW_HIDE);;
       	GetParentFrame()->SetWindowText("断电记录查询");
	}
	else if(theApp.strargc == "OnFEEDES")
	{
    	GetDlgItem(IDC_COMBMADE)->ShowWindow(SW_HIDE);;
       	GetParentFrame()->SetWindowText("馈电异常记录查询");
	}
	else if(theApp.strargc == "OnSELECTS")
       	GetParentFrame()->SetWindowText("调用查询");
	else if(theApp.strargc == "OnRECAAD")
	{
    	GetDlgItem(IDC_COMBMADE)->ShowWindow(SW_HIDE);;
       	GetParentFrame()->SetWindowText("模拟量报警记录查询");
	}
	else if(theApp.strargc == "OnRECABD")
	{
    	GetDlgItem(IDC_COMBMADE)->ShowWindow(SW_HIDE);;
       	GetParentFrame()->SetWindowText("模拟量断电记录查询");
	}
	else if(theApp.strargc == "OnRECAFED")
	{
    	GetDlgItem(IDC_COMBMADE)->ShowWindow(SW_HIDE);;
       	GetParentFrame()->SetWindowText("模拟量馈电异常记录查询");
	}
	else if(theApp.strargc == "OnRECASR")
       	GetParentFrame()->SetWindowText("模拟量统计值记录查询");
	else if(theApp.strargc == "OnRECDABD")
	{
    	GetDlgItem(IDC_COMBMADE)->ShowWindow(SW_HIDE);;
       	GetParentFrame()->SetWindowText("开关量报警记录查询");
	}
	else if(theApp.strargc == "OnRECDABB")
	{
    	GetDlgItem(IDC_COMBMADE)->ShowWindow(SW_HIDE);;
       	GetParentFrame()->SetWindowText("开关量断电记录查询");
	}
	else if(theApp.strargc == "OnRECDFED")
	{
    	GetDlgItem(IDC_COMBMADE)->ShowWindow(SW_HIDE);;
       	GetParentFrame()->SetWindowText("开关量馈电异常记录查询");
	}
	else if(theApp.strargc == "OnRECDSCD")
       	GetParentFrame()->SetWindowText("开关量状态变动记录查询");
	else if(theApp.strargc == "OnRECDRIVERE")
	{
    	GetDlgItem(IDC_COMBMADE)->ShowWindow(SW_HIDE);;
       	GetParentFrame()->SetWindowText("监控设备故障记录查询");
	}

}

void CMadeCertView::OnBOKSEARCH() 
{
	UpdateData(TRUE);
	CString sztime,szConnect,szConnect1,strtime;
	int starty,endy;	unsigned char startm,endm;
	CTime t(m_startDateTime.GetYear(),m_startDateTime.GetMonth(),m_startDateTime.GetDay(),m_ctrlStartH,0,0);
	CTime t1(m_endDateTime.GetYear(),m_endDateTime.GetMonth(),m_endDateTime.GetDay(),m_ctrlEndH,59,59);
					if((t1.GetTime()-t.GetTime())<0)
					{
						strtime = "结束时间应该大于起始时间";
						AfxMessageBox(strtime);
						return;
					}
		if(theApp.strargc == "OnRECASR")
		{
					szConnect = "Select * From rt5mdata WHERE recdate>'";
 					  strtime = t.Format(_T("%Y-%m-%d %H:%M:%S")); 
					  sztime = t1.Format(_T("%Y-%m-%d %H:%M:%S")); 
      				  szConnect += strtime+"' and recdate<'" +sztime+"'";
		}
		else
		{
					theApp.socketClient.CalRtDB(t , starty , startm);
					theApp.socketClient.CalRtDB(t1 , endy , endm);
						strtime = "结束时间与起始时间应在两个月内";
					if(starty == endy)	{
    					if(endm-startm>1){
						AfxMessageBox(strtime);
						return;
						}
					}
					else{
    					if(endm-startm != -11)	{
						AfxMessageBox(strtime);
						return;
						}
					}
					szConnect = "Select * From rt";
					szConnect1 = "Select * From rt";
					if(endm != startm)
    					sztime.Format("%d",starty);
					szConnect1 += sztime;
    				sztime.Format("%d",endy);
					szConnect += sztime;
					if(endm != startm)
					{
    					if(startm>9)
     	     				sztime.Format("%d",startm);
       					else
           					sztime.Format("0%d",startm);
					}
					szConnect1 += sztime;
    					if(endm>9)
     	     				sztime.Format("%d",endm);
       					else
           					sztime.Format("0%d",endm);
					szConnect += sztime;
					szConnect1 += "data WHERE recdate>'";
					szConnect += "data WHERE recdate>'";
					if(endm != startm)
					{
    					if(m_ClassTime[1].ffds >12)
						{
        					  strtime = t.Format(_T("%Y-%m-%d %H:%M:%S")); 
        					  sztime.Format("%d-%d-%d %d:59:59",starty,startm,GetDayM(startm),m_ClassTime[1].ffds-1); 
            				  szConnect1 += strtime+"' and recdate<'" +sztime+"'";
        					  strtime.Format("%d-%d-%d %d:00:00",starty,startm,GetDayM(startm),m_ClassTime[1].ffds); 
        					  sztime = t1.Format(_T("%Y-%m-%d %H:%M:%S")); 
            				  szConnect += strtime+"' and recdate<'" +sztime+"'";
						}
						else
						{
        					  strtime = t.Format(_T("%Y-%m-%d %H:%M:%S")); 
        					  sztime.Format("%d-%d-1 %d:59:59",endy,endm,m_ClassTime[1].ffds-1); 
            				  szConnect1 += strtime+"' and recdate<'" +sztime+"'";
        					  strtime.Format("%d-%d-1 %d:00:00",endy,endm,m_ClassTime[1].ffds); 
        					  sztime = t1.Format(_T("%Y-%m-%d %H:%M:%S")); 
            				  szConnect += strtime+"' and recdate<'" +sztime+"'";
						}
					}
					else
					{
 					  strtime = t.Format(_T("%Y-%m-%d %H:%M:%S")); 
					  sztime = t1.Format(_T("%Y-%m-%d %H:%M:%S")); 
      				  szConnect += strtime+"' and recdate<'" +sztime+"'";
					}
		}

			//		sztime.Format(" WHERE recdate>'%d-%d-%d %d:00:00' and recdate<'",t.GetYear(),t.GetMonth(),t.GetDay(),m_ctrlStartH);
			//		sztime.Format("%d-%d-%d %d:59:59'",t1.GetYear(),t1.GetMonth(),t1.GetDay(),m_ctrlEndH);
				if(theApp.strargc == "OnALARMS")
					sztime.Format(" and ADStatus=16");
				else if(theApp.strargc == "OnBREAKES")
					sztime.Format(" and ADStatus=32");
				else if(theApp.strargc == "OnFEEDES")
					sztime.Format(" and FeedStatus='异常'");
				else if(theApp.strargc == "OnSELECTS" ||theApp.strargc == "OnRECASR"||theApp.strargc == "OnRECDSCD")
				{
     				CString strname,strf,strc;
    				int  kkkk = m_ComBoxSM.GetCurSel();
    				if(kkkk == -1 )
      					return;
       				m_ComBoxSM.GetLBText(kkkk,strname);
      				strname = strname.Mid(0,5);
    					strf = strname.Mid(0,2);
    					strc = strname.Mid(3);
					int afds = m_Str2Data.String2Int(strf);
					int achan;
					kkkk =strname.Find("C");
					if(kkkk != -1)
					     achan = m_Str2Data.String2Int(strc)+16;
					else
					     achan = m_Str2Data.String2Int(strc);
					sztime.Format(" and fds=%d and chan=%d",afds,achan);
				}
				else if(theApp.strargc == "OnRECAAD" ||theApp.strargc == "OnRECABD"||theApp.strargc == "OnRECAFED")
					sztime.Format(" and ptype<3");
				else if(theApp.strargc == "OnRECDABD"||theApp.strargc == "OnRECDABB"||theApp.strargc == "OnRECDFED")
					sztime.Format(" and ptype>3");
				else if(theApp.strargc == "OnRECDRIVERE")
					sztime = "";

					if(endm != startm)   //两个月
    					szConnect1 += sztime;
					szConnect += sztime;

		if(theApp.strargc == "OnRECASR")
		{
					if ( m_Rt5mdata._IsOpen() )
						 m_Rt5mdata.Close();
					m_Rt5mdata.Create();
					m_Rt5mdata.CursorType(adOpenDynamic);
					m_Rt5mdata.CacheSize(50);
					m_Rt5mdata.Open( szConnect , &m_Cn);
					m_Rt5mdata.MarshalOptions(adMarshalModifiedOnly);
		}
		else
		{
					if ( m_Realtimedata1._IsOpen() )
						 m_Realtimedata1.Close();
					if ( m_Realtimedata._IsOpen() )
						 m_Realtimedata.Close();

					if(endm != startm)   //两个月
					{
					m_Realtimedata1.Create();
					m_Realtimedata1.CursorType(adOpenDynamic);
					m_Realtimedata1.CacheSize(50);
					m_Realtimedata1._SetRecordsetEvents(new CAccountSetEvents);
					m_Realtimedata1.Open( szConnect1 , &m_Cn);
					m_Realtimedata1.MarshalOptions(adMarshalModifiedOnly);
					}
					m_Realtimedata.Create();
					m_Realtimedata.CursorType(adOpenDynamic);
					m_Realtimedata.CacheSize(50);
					m_Realtimedata.Open( szConnect , &m_Cn);
					m_Realtimedata.MarshalOptions(adMarshalModifiedOnly);
		}
	if(theApp.strargc == "OnALARMS")
		OnALARMSM();
	else if(theApp.strargc == "OnBREAKES")
		OnBREAKESM();
	else if(theApp.strargc == "OnFEEDES")
		OnFEEDES();
	else if(theApp.strargc == "OnSELECTS")
		OnSELECTSM();
	else if(theApp.strargc == "OnRECAAD")
		OnRECAAD();
	else if(theApp.strargc == "OnRECABD")
		OnRECABD();
	else if(theApp.strargc == "OnRECAFED")
		OnRECAFED();
	else if(theApp.strargc == "OnRECASR")
		OnRECASR();
	else if(theApp.strargc == "OnRECDABD")
		OnRECDABD();
	else if(theApp.strargc == "OnRECDABB")
		OnRECDABB();
	else if(theApp.strargc == "OnRECDFED")
		OnRECDFED();
	else if(theApp.strargc == "OnRECDSCD")
		OnRECDSCD();
	else if(theApp.strargc == "OnRECDRIVERE")
		OnRECDRIVERE();



 /*	m_List.DeleteAllItems();
	((CRaChildFrame*)GetParentFrame( ))->Msg("开始查询数据库");
	CString msg;
	if(str[35]=="2")
	{
		msg.Format("共查询到了%d条待制作证书,查询结束!",1);
		int i=0;
		m_List.InsertItem(i,str[28]);
		m_List.SetItemText(i,1,str[30]);
		m_List.SetItemText(i,2,str[31]);
		m_List.SetItemText(i,3,str[30]);
		m_List.SetItemText(i,4,str[29]);
		m_List.SetItemText(i,5,str[32]);
		m_List.SetItemText(i,6,str[33]);
		m_List.SetItemText(i,7,str[26]);
		m_List.SetItemText(i,8,str[34]);
		m_List.SetItemText(i,9,str[27]);
	}
	else
		msg.Format("没有查询到待制作证书,查询结束!");
	((CRaChildFrame*)GetParentFrame( ))->Msg(msg);*/
}

void CMadeCertView::OnALARMSM() 
{
	BasicExcel xls;
//	xls.Load(gstrTimeOut +"\\report\\example.xls");
	xls.New(1);
	BasicExcelWorksheet* sheet = xls.GetWorksheet((size_t)0);
	XLSFormatManager fmt_mgr(xls);

	CString strtime;
	 // Create a table containing an header row in bold and four rows below.
	ExcelFont font_bold;
	font_bold._weight = FW_BOLD; // 700
	CellFormat fmt_bold(fmt_mgr);
	fmt_bold.set_font(font_bold);

    WCHAR * buf=new WCHAR[50];
	size_t col = 0;
	for(col=0; col<4; col++) {
		BasicExcelCell* cell = sheet->Cell(0, col);
		if(col==0)
             m_Str2Data.GB2312ToUnicode("安装地点|名称",buf);
		else if(col==1)
             m_Str2Data.GB2312ToUnicode("测点值",buf);
		else if(col==2)
             m_Str2Data.GB2312ToUnicode("状态",buf);
		else if(col==3)
             m_Str2Data.GB2312ToUnicode("时间",buf);
		cell->Set(buf);
		cell->SetFormat(fmt_bold);
	}
		int iItem = 1;
	if(!m_Realtimedata1._IsEmpty())
	{
		m_Realtimedata1.MoveFirst();
		while ( !m_Realtimedata1.IsEOF() )
		{
         	for(col=0; col<4; col++) {
				int afds = m_Realtimedata1.m_szfds;
				int achan = m_Realtimedata1.m_szchan;
         		BasicExcelCell* cell = sheet->Cell(iItem, col);
         		if(col==0)
                      m_Str2Data.GB2312ToUnicode(m_SlaveStation[afds][achan].WatchName,buf);
        		else if(col==1)
				{
				  int nptype = m_SlaveStation[afds][achan].ptype;
				  if( nptype <3)
				    	  strtime.Format("%.2f",m_Realtimedata1.m_szAValue);
				  else
				  {
					  int nstatus = m_Realtimedata1.m_szCDValue;
					  if(nstatus == 0)
						  strtime= m_SlaveStation[afds][achan].ZeroState;
					  else if(nstatus == 1)
						  strtime= m_SlaveStation[afds][achan].OneState;
					  else if(nstatus == 2)
						  strtime= m_SlaveStation[afds][achan].TwoState;
				  }
                      m_Str2Data.GB2312ToUnicode(strtime ,buf);
				}
         		else if(col==2)
                      m_Str2Data.GB2312ToUnicode("报警",buf);
         		else if(col==3)
				{
				  COleDateTime oleDateTime=m_Realtimedata1.m_szrecdate;
				  strtime   =   oleDateTime.Format(_T("%Y-%m-%d %H:%M:%S")); 
                      m_Str2Data.GB2312ToUnicode(strtime,buf);
				}
        		cell->Set(buf);
			}
			iItem++;
			m_Realtimedata1.MoveNext();
		}
	}
	if(!m_Realtimedata._IsEmpty())
	{
		m_Realtimedata.MoveFirst();
		while ( !m_Realtimedata.IsEOF() )
		{
         	for(col=0; col<4; col++) {
				int afds = m_Realtimedata.m_szfds;
				int achan = m_Realtimedata.m_szchan;
         		BasicExcelCell* cell = sheet->Cell(iItem, col);
         		if(col==0)
                      m_Str2Data.GB2312ToUnicode(m_SlaveStation[afds][achan].WatchName,buf);
        		else if(col==1)
				{
				  int nptype = m_SlaveStation[afds][achan].ptype;
				  if( nptype <3)
				    	  strtime.Format("%.2f",m_Realtimedata.m_szAValue);
				  else
				  {
					  int nstatus = m_Realtimedata.m_szCDValue;
					  if(nstatus == 0)
						  strtime= m_SlaveStation[afds][achan].ZeroState;
					  else if(nstatus == 1)
						  strtime= m_SlaveStation[afds][achan].OneState;
					  else if(nstatus == 2)
						  strtime= m_SlaveStation[afds][achan].TwoState;
				  }
                      m_Str2Data.GB2312ToUnicode(strtime ,buf);
				}
         		else if(col==2)
                      m_Str2Data.GB2312ToUnicode("报警",buf);
         		else if(col==3)
				{
				  COleDateTime oleDateTime=m_Realtimedata.m_szrecdate;
				  strtime   =   oleDateTime.Format(_T("%Y-%m-%d %H:%M:%S")); 
                      m_Str2Data.GB2312ToUnicode(strtime,buf);
				}
        		cell->Set(buf);
			}
			iItem++;
			m_Realtimedata.MoveNext();
		}
	}
    delete [] buf;
	xls.SaveAs(gstrTimeOut +"\\report\\example.xls");
	copy_sheet(gstrTimeOut +"\\report\\example.xls",gstrTimeOut +"\\report\\sexample.xls");
	ShellExecute(0, NULL, gstrTimeOut +"\\report\\sexample.xls", NULL, NULL, SW_NORMAL);


/*
	for(size_t row=0; row<8; ++row) {
		int color = 2;
//		int color = i++;
		int height = 100 * i;

		sprintf(buffer, "中文 New Roman %d", height/20);

        WCHAR * buf=new WCHAR[1000];
        m_Str2Data.GB2312ToUnicode("客户号     New Roman",buf);

		ExcelFont font;
		font.set_color_index(color);
		font.set_height(height);
		font.set_font_name(L"Times New Roman");

		CellFormat fmt(fmt_mgr, font);
//		fmt.set_background(MAKE_COLOR2(EGA_MAGENTA,0));	// solid magenta background

		BasicExcelCell* cell = sheet->Cell(row, 0);
		cell->Set(buf);
//		cell->Set(buffer);
		cell->SetFormat(fmt);
	}
*/

	/*
BasicExcelWorksheet* sheet = xls.GetWorksheet((size_t)0);

 XLSFormatManager fmt_mgr(xls);
 ExcelFont font_bold;
 font_bold._weight = 20000; // bold
 
 CellFormat fmt_bold(fmt_mgr);
// fmt_bold.set_borderlines(MAKE_BORDERSTYLE(EXCEL_LS_MEDIUM, 0, EXCEL_LS_MEDIUM, 0, 0, 0));
 fmt_bold.set_borderlines(120000);
 fmt_bold.set_font(font_bold);
 BasicExcelCell* cell = sheet->Cell(0, 0);
 WCHAR * buf=new WCHAR[1000];
 GB2312ToUnicode("客户号",buf);
 cell->Set(buf);
 cell->SetFormat(fmt_bold);
 
    cell = sheet->Cell(0, 1);
    GB2312ToUnicode("导入结果",buf);
    cell->Set(buf);
    cell->SetFormat(fmt_bold);
//  xls.SaveAs(path);
*/
//	xls.Save();
}

void CMadeCertView::OnBREAKESM() 
{
	BasicExcel xls;
//	xls.Load(gstrTimeOut +"\\report\\example.xls");
	xls.New(1);
	BasicExcelWorksheet* sheet = xls.GetWorksheet((size_t)0);
	XLSFormatManager fmt_mgr(xls);

	CString strtime;
	 // Create a table containing an header row in bold and four rows below.
	ExcelFont font_bold;
	font_bold._weight = FW_BOLD; // 700
	CellFormat fmt_bold(fmt_mgr);
	fmt_bold.set_font(font_bold);

    WCHAR * buf=new WCHAR[50];
	size_t col = 0;
	for(col=0; col<4; col++) {
		BasicExcelCell* cell = sheet->Cell(0, col);
		if(col==0)
             m_Str2Data.GB2312ToUnicode("安装地点|名称",buf);
		else if(col==1)
             m_Str2Data.GB2312ToUnicode("测点值",buf);
		else if(col==2)
             m_Str2Data.GB2312ToUnicode("状态",buf);
		else if(col==3)
             m_Str2Data.GB2312ToUnicode("时间",buf);
		cell->Set(buf);
		cell->SetFormat(fmt_bold);
	}
		int iItem = 1;
	if(!m_Realtimedata1._IsEmpty())
	{
		m_Realtimedata1.MoveFirst();
		while ( !m_Realtimedata1.IsEOF() )
		{
         	for(col=0; col<4; col++) {
				int afds = m_Realtimedata1.m_szfds;
				int achan = m_Realtimedata1.m_szchan;
         		BasicExcelCell* cell = sheet->Cell(iItem, col);
         		if(col==0)
                      m_Str2Data.GB2312ToUnicode(m_SlaveStation[afds][achan].WatchName,buf);
        		else if(col==1)
				{
				  int nptype = m_SlaveStation[afds][achan].ptype;
				  if( nptype <3)
				    	  strtime.Format("%.2f",m_Realtimedata1.m_szAValue);
				  else
				  {
					  int nstatus = m_Realtimedata1.m_szCDValue;
					  if(nstatus == 0)
						  strtime= m_SlaveStation[afds][achan].ZeroState;
					  else if(nstatus == 1)
						  strtime= m_SlaveStation[afds][achan].OneState;
					  else if(nstatus == 2)
						  strtime= m_SlaveStation[afds][achan].TwoState;
				  }
                      m_Str2Data.GB2312ToUnicode(strtime ,buf);
				}
         		else if(col==2)
                      m_Str2Data.GB2312ToUnicode("断电",buf);
         		else if(col==3)
				{
				  COleDateTime oleDateTime=m_Realtimedata1.m_szrecdate;
				  strtime   =   oleDateTime.Format(_T("%Y-%m-%d %H:%M:%S")); 
                      m_Str2Data.GB2312ToUnicode(strtime,buf);
				}
        		cell->Set(buf);
			}
			iItem++;
			m_Realtimedata1.MoveNext();
		}
	}
	if(!m_Realtimedata._IsEmpty())
	{
		m_Realtimedata.MoveFirst();
		while ( !m_Realtimedata.IsEOF() )
		{
         	for(col=0; col<4; col++) {
				int afds = m_Realtimedata.m_szfds;
				int achan = m_Realtimedata.m_szchan;
         		BasicExcelCell* cell = sheet->Cell(iItem, col);
         		if(col==0)
                      m_Str2Data.GB2312ToUnicode(m_SlaveStation[afds][achan].WatchName,buf);
        		else if(col==1)
				{
				  int nptype = m_SlaveStation[afds][achan].ptype;
				  if( nptype <3)
				    	  strtime.Format("%.2f",m_Realtimedata.m_szAValue);
				  else
				  {
					  int nstatus = m_Realtimedata.m_szCDValue;
					  if(nstatus == 0)
						  strtime= m_SlaveStation[afds][achan].ZeroState;
					  else if(nstatus == 1)
						  strtime= m_SlaveStation[afds][achan].OneState;
					  else if(nstatus == 2)
						  strtime= m_SlaveStation[afds][achan].TwoState;
				  }
                      m_Str2Data.GB2312ToUnicode(strtime ,buf);
				}
         		else if(col==2)
                      m_Str2Data.GB2312ToUnicode("断电",buf);
         		else if(col==3)
				{
				  COleDateTime oleDateTime=m_Realtimedata.m_szrecdate;
				  strtime   =   oleDateTime.Format(_T("%Y-%m-%d %H:%M:%S")); 
                      m_Str2Data.GB2312ToUnicode(strtime,buf);
				}
        		cell->Set(buf);
			}
			iItem++;
			m_Realtimedata.MoveNext();
		}
	}
    delete [] buf;
	xls.SaveAs(gstrTimeOut +"\\report\\example.xls");
	copy_sheet(gstrTimeOut +"\\report\\example.xls",gstrTimeOut +"\\report\\sexample.xls");
	ShellExecute(0, NULL, gstrTimeOut +"\\report\\sexample.xls", NULL, NULL, SW_NORMAL);
}

void CMadeCertView::OnFEEDES() 
{
	BasicExcel xls;
//	xls.Load(gstrTimeOut +"\\report\\example.xls");
	xls.New(1);
	BasicExcelWorksheet* sheet = xls.GetWorksheet((size_t)0);
	XLSFormatManager fmt_mgr(xls);

	CString strtime;
	 // Create a table containing an header row in bold and four rows below.
	ExcelFont font_bold;
	font_bold._weight = FW_BOLD; // 700
	CellFormat fmt_bold(fmt_mgr);
	fmt_bold.set_font(font_bold);

    WCHAR * buf=new WCHAR[50];
	size_t col = 0;
	for(col=0; col<5; col++) {
		BasicExcelCell* cell = sheet->Cell(0, col);
		if(col==0)
             m_Str2Data.GB2312ToUnicode("安装地点|名称",buf);
		else if(col==1)
             m_Str2Data.GB2312ToUnicode("测点值",buf);
		else if(col==2)
             m_Str2Data.GB2312ToUnicode("馈电状态",buf);
		else if(col==3)
             m_Str2Data.GB2312ToUnicode("时间",buf);
		else if(col==4)
             m_Str2Data.GB2312ToUnicode("断电区域",buf);
		cell->Set(buf);
		cell->SetFormat(fmt_bold);
	}
		int iItem = 1;
	if(!m_Realtimedata1._IsEmpty())
	{
		m_Realtimedata1.MoveFirst();
		while ( !m_Realtimedata1.IsEOF() )
		{
         	for(col=0; col<5; col++) {
				int afds = m_Realtimedata1.m_szfds;
				int achan = m_Realtimedata1.m_szchan;
         		BasicExcelCell* cell = sheet->Cell(iItem, col);
         		if(col==0)
                      m_Str2Data.GB2312ToUnicode(m_SlaveStation[afds][achan].WatchName,buf);
        		else if(col==1)
				{
				  int nptype = m_SlaveStation[afds][achan].ptype;
				  if( nptype <3)
				    	  strtime.Format("%.2f",m_Realtimedata1.m_szAValue);
				  else
				  {
					  int nstatus = m_Realtimedata1.m_szCDValue;
					  if(nstatus == 0)
						  strtime= m_SlaveStation[afds][achan].ZeroState;
					  else if(nstatus == 1)
						  strtime= m_SlaveStation[afds][achan].OneState;
					  else if(nstatus == 2)
						  strtime= m_SlaveStation[afds][achan].TwoState;
				  }
                      m_Str2Data.GB2312ToUnicode(strtime ,buf);
				}
         		else if(col==2)
                      m_Str2Data.GB2312ToUnicode("异常",buf);
         		else if(col==3)
				{
				  COleDateTime oleDateTime=m_Realtimedata1.m_szrecdate;
				  strtime   =   oleDateTime.Format(_T("%Y-%m-%d %H:%M:%S")); 
                      m_Str2Data.GB2312ToUnicode(strtime,buf);
				}
         		else if(col==4)
				{
		    		int ffds = m_Realtimedata1.m_szffds;
			    	int fchan = m_Realtimedata1.m_szfchan;
                      m_Str2Data.GB2312ToUnicode(m_SlaveStation[ffds][fchan].WatchName,buf);
				}
        		cell->Set(buf);
			}
			iItem++;
			m_Realtimedata1.MoveNext();
		}
	}
	if(!m_Realtimedata._IsEmpty())
	{
		m_Realtimedata.MoveFirst();
		while ( !m_Realtimedata.IsEOF() )
		{
         	for(col=0; col<5; col++) {
				int afds = m_Realtimedata.m_szfds;
				int achan = m_Realtimedata.m_szchan;
         		BasicExcelCell* cell = sheet->Cell(iItem, col);
         		if(col==0)
                      m_Str2Data.GB2312ToUnicode(m_SlaveStation[afds][achan].WatchName,buf);
        		else if(col==1)
				{
				  int nptype = m_SlaveStation[afds][achan].ptype;
				  if( nptype <3)
				    	  strtime.Format("%.2f",m_Realtimedata.m_szAValue);
				  else
				  {
					  int nstatus = m_Realtimedata.m_szCDValue;
					  if(nstatus == 0)
						  strtime= m_SlaveStation[afds][achan].ZeroState;
					  else if(nstatus == 1)
						  strtime= m_SlaveStation[afds][achan].OneState;
					  else if(nstatus == 2)
						  strtime= m_SlaveStation[afds][achan].TwoState;
				  }
                      m_Str2Data.GB2312ToUnicode(strtime ,buf);
				}
         		else if(col==2)
                      m_Str2Data.GB2312ToUnicode("异常",buf);
         		else if(col==3)
				{
				  COleDateTime oleDateTime=m_Realtimedata.m_szrecdate;
				  strtime   =   oleDateTime.Format(_T("%Y-%m-%d %H:%M:%S")); 
                      m_Str2Data.GB2312ToUnicode(strtime,buf);
				}
         		else if(col==4)
				{
		    		int ffds = m_Realtimedata.m_szffds;
			    	int fchan = m_Realtimedata.m_szfchan;
                      m_Str2Data.GB2312ToUnicode(m_SlaveStation[ffds][fchan].WatchName,buf);
				}
        		cell->Set(buf);
			}
			iItem++;
			m_Realtimedata.MoveNext();
		}
	}
    delete [] buf;
	xls.SaveAs(gstrTimeOut +"\\report\\example.xls");
	copy_sheet(gstrTimeOut +"\\report\\example.xls",gstrTimeOut +"\\report\\sexample.xls");
	ShellExecute(0, NULL, gstrTimeOut +"\\report\\sexample.xls", NULL, NULL, SW_NORMAL);
}

void CMadeCertView::OnSELECTSM() 
{
	BasicExcel xls;
//	xls.Load(gstrTimeOut +"\\report\\example.xls");
	xls.New(1);
	BasicExcelWorksheet* sheet = xls.GetWorksheet((size_t)0);
	XLSFormatManager fmt_mgr(xls);

	CString strtime;
	 // Create a table containing an header row in bold and four rows below.
	ExcelFont font_bold;
	font_bold._weight = FW_BOLD; // 700
	CellFormat fmt_bold(fmt_mgr);
	fmt_bold.set_font(font_bold);

    WCHAR * buf=new WCHAR[50];
	size_t col = 0;
	for(col=0; col<4; col++) {
		BasicExcelCell* cell = sheet->Cell(0, col);
		if(col==0)
             m_Str2Data.GB2312ToUnicode("安装地点|名称",buf);
		else if(col==1)
             m_Str2Data.GB2312ToUnicode("测点值",buf);
		else if(col==2)
             m_Str2Data.GB2312ToUnicode("状态",buf);
		else if(col==3)
             m_Str2Data.GB2312ToUnicode("时间",buf);
		cell->Set(buf);
		cell->SetFormat(fmt_bold);
	}
		int iItem = 1;
	if(!m_Realtimedata1._IsEmpty())
	{
		m_Realtimedata1.MoveFirst();
		while ( !m_Realtimedata1.IsEOF() )
		{
         	for(col=0; col<4; col++) {
				int afds = m_Realtimedata1.m_szfds;
				int achan = m_Realtimedata1.m_szchan;
         		BasicExcelCell* cell = sheet->Cell(iItem, col);
         		if(col==0)
                      m_Str2Data.GB2312ToUnicode(m_SlaveStation[afds][achan].WatchName,buf);
        		else if(col==1)
				{
				  int nptype = m_SlaveStation[afds][achan].ptype;
				  if( nptype <3)
				    	  strtime.Format("%.2f",m_Realtimedata1.m_szAValue);
				  else
				  {
					  int nstatus = m_Realtimedata1.m_szCDValue;
					  if(nstatus == 0)
						  strtime= m_SlaveStation[afds][achan].ZeroState;
					  else if(nstatus == 1)
						  strtime= m_SlaveStation[afds][achan].OneState;
					  else if(nstatus == 2)
						  strtime= m_SlaveStation[afds][achan].TwoState;
				  }
                      m_Str2Data.GB2312ToUnicode(strtime ,buf);
				}
         		else if(col==2)
				{
					int nstatus = m_Realtimedata1.m_szADStatus;
					strtime= theApp.socketClient.strstatus(nstatus);
                      m_Str2Data.GB2312ToUnicode(strtime ,buf);
				}
         		else if(col==3)
				{
				  COleDateTime oleDateTime=m_Realtimedata1.m_szrecdate;
				  strtime   =   oleDateTime.Format(_T("%Y-%m-%d %H:%M:%S")); 
                      m_Str2Data.GB2312ToUnicode(strtime,buf);
				}
        		cell->Set(buf);
			}
			iItem++;
			m_Realtimedata1.MoveNext();
		}
	}
	if(!m_Realtimedata._IsEmpty())
	{
		m_Realtimedata.MoveFirst();
		while ( !m_Realtimedata.IsEOF() )
		{
         	for(col=0; col<4; col++) {
				int afds = m_Realtimedata.m_szfds;
				int achan = m_Realtimedata.m_szchan;
         		BasicExcelCell* cell = sheet->Cell(iItem, col);
         		if(col==0)
                      m_Str2Data.GB2312ToUnicode(m_SlaveStation[afds][achan].WatchName,buf);
        		else if(col==1)
				{
				  int nptype = m_SlaveStation[afds][achan].ptype;
				  if( nptype <3)
				    	  strtime.Format("%.2f",m_Realtimedata.m_szAValue);
				  else
				  {
					  int nstatus = m_Realtimedata.m_szCDValue;
					  if(nstatus == 0)
						  strtime= m_SlaveStation[afds][achan].ZeroState;
					  else if(nstatus == 1)
						  strtime= m_SlaveStation[afds][achan].OneState;
					  else if(nstatus == 2)
						  strtime= m_SlaveStation[afds][achan].TwoState;
				  }
                      m_Str2Data.GB2312ToUnicode(strtime ,buf);
				}
         		else if(col==2)
				{
					int nstatus = m_Realtimedata.m_szADStatus;
					strtime= theApp.socketClient.strstatus(nstatus);
                      m_Str2Data.GB2312ToUnicode(strtime ,buf);
				}
         		else if(col==3)
				{
				  COleDateTime oleDateTime=m_Realtimedata.m_szrecdate;
				  strtime   =   oleDateTime.Format(_T("%Y-%m-%d %H:%M:%S")); 
                      m_Str2Data.GB2312ToUnicode(strtime,buf);
				}
        		cell->Set(buf);
			}
			iItem++;
			m_Realtimedata.MoveNext();
		}
	}
    delete [] buf;
	xls.SaveAs(gstrTimeOut +"\\report\\example.xls");
	copy_sheet(gstrTimeOut +"\\report\\example.xls",gstrTimeOut +"\\report\\sexample.xls");
	ShellExecute(0, NULL, gstrTimeOut +"\\report\\sexample.xls", NULL, NULL, SW_NORMAL);
}

void CMadeCertView::OnRECAAD() 
{
	CString strtime,strtime2;
	if(!m_Realtimedata1._IsEmpty())
	{
		m_Realtimedata1.MoveFirst();
		while ( !m_Realtimedata1.IsEOF() )
		{
				int afds = m_Realtimedata1.m_szfds;
				int achan = m_Realtimedata1.m_szchan;
			int m_alarm = m_Realtimedata1.m_szADStatus;
			if(m_alarm == 16)
			{
				if(m_ADRecord[afds][achan][0].duant == 0)
					m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].NTime =m_Realtimedata1.m_szrecdate;
				m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].BTime =m_Realtimedata1.m_szrecdate;

				if(m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].AMaxValue <m_Realtimedata1.m_szAValue)
				{
    				m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].AMaxValue = m_Realtimedata1.m_szAValue;
		    		m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].AMaxTime = m_Realtimedata1.m_szrecdate;
				}
				m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].strlocal="ddd";
					strtime = m_Realtimedata1.m_szsafemtext;
					strtime.TrimRight();
					if(strtime != "")
					{
          				  COleDateTime t=m_Realtimedata1.m_szrecdate;
		        		  strtime2   =   t.Format(_T("%Y-%m-%d %H:%M:%S")); 
//	       	    		m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].RTime = m_Realtimedata1.m_szrecdate;
	       	    		m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].strsafetext += strtime+"|"+strtime2+"|";
					}
				m_ADRecord[afds][achan][0].duant++;//n个报警值
			}
			else if(m_alarm == 0)
			{
				if(m_ADRecord[afds][achan][0].duant> 0)
				{
	    			m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].BTime =m_Realtimedata1.m_szrecdate;
	     			m_ADRecord[afds][achan][0].m_ATotalnum++;  //总报警次数
	     			m_ADRecord[afds][achan][0].duant = 0;  //状态转变
				}
			}
			m_Realtimedata1.MoveNext();
		}
	}
	if(!m_Realtimedata._IsEmpty())
	{
		m_Realtimedata.MoveFirst();
		while ( !m_Realtimedata.IsEOF() )
		{
				int afds = m_Realtimedata.m_szfds;
				int achan = m_Realtimedata.m_szchan;
			int m_alarm = m_Realtimedata.m_szADStatus;
			if(m_alarm == 16)
			{
				if(m_ADRecord[afds][achan][0].duant == 0)
					m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].NTime =m_Realtimedata.m_szrecdate;
				m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].BTime =m_Realtimedata.m_szrecdate;

				if(m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].AMaxValue <m_Realtimedata.m_szAValue)
				{
    				m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].AMaxValue = m_Realtimedata.m_szAValue;
		    		m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].AMaxTime = m_Realtimedata.m_szrecdate;
				}
				m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].strlocal="ddd";
					strtime = m_Realtimedata.m_szsafemtext;
					strtime.TrimRight();
					if(strtime != "")
					{
          				  COleDateTime t=m_Realtimedata.m_szrecdate;
		        		  strtime2   =   t.Format(_T("%Y-%m-%d %H:%M:%S")); 
	       	    		m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].strsafetext += strtime+"|"+strtime2+"|";
					}
				m_ADRecord[afds][achan][0].duant++;//n个报警值
			}
			else if(m_alarm == 0)
			{
				if(m_ADRecord[afds][achan][0].duant> 0)
				{
	    			m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].BTime =m_Realtimedata.m_szrecdate;
	     			m_ADRecord[afds][achan][0].m_ATotalnum++;  //总报警次数
	     			m_ADRecord[afds][achan][0].duant = 0;  //状态转变
				}
			}
			m_Realtimedata.MoveNext();
		}
	}
	BasicExcel xls;
//	xls.Load(gstrTimeOut +"\\report\\example.xls");
	xls.New(1);
	BasicExcelWorksheet* sheet = xls.GetWorksheet((size_t)0);
	XLSFormatManager fmt_mgr(xls);

	 // Create a table containing an header row in bold and four rows below.
	ExcelFont font_bold;
	font_bold._weight = FW_BOLD; // 700
	CellFormat fmt_bold(fmt_mgr);
	fmt_bold.set_font(font_bold);

	CString strtime1;
		strtime.Format("(%d-%d-%d %d:00:00----",m_startDateTime.GetYear(),m_startDateTime.GetMonth(),m_startDateTime.GetDay(),m_ctrlStartH); 
		strtime1.Format("%d-%d-%d %d:59:59)",m_endDateTime.GetYear(),m_endDateTime.GetMonth(),m_endDateTime.GetDay(),m_ctrlEndH); 
		ExcelFont font;
//		font.set_color_index(color);
		font.set_weight(500);
		font.set_height(500);
		font.set_font_name(L"Times New Roman");
		CellFormat fmt(fmt_mgr, font);


    WCHAR * buf=new WCHAR[200];
		BasicExcelCell* cell = sheet->Cell(0, 2);
             m_Str2Data.GB2312ToUnicode("模拟量报警记录查询显示" ,buf);
		cell->Set(buf);
		cell->SetFormat(fmt);

        cell = sheet->Cell(1, 2);
		strtime += strtime1;
             m_Str2Data.GB2312ToUnicode(strtime ,buf);
		cell->Set(buf);
		cell->SetFormat(fmt_bold);

	size_t col = 0;
	for(col=0; col<8; col++) {
		BasicExcelCell* cell = sheet->Cell(2, col);
		if(col==0)
             m_Str2Data.GB2312ToUnicode("安装地点|名称",buf);
		else if(col==1)
             m_Str2Data.GB2312ToUnicode("报警次数",buf);
		else if(col==2)
             m_Str2Data.GB2312ToUnicode("报警时间",buf);
		else if(col==3)
             m_Str2Data.GB2312ToUnicode("最大值",buf);
		else if(col==4)
             m_Str2Data.GB2312ToUnicode("最大值时刻",buf);
		else if(col==5)
             m_Str2Data.GB2312ToUnicode("起始时刻",buf);
		else if(col==6)
             m_Str2Data.GB2312ToUnicode("终止时刻",buf);
		else if(col==7)
             m_Str2Data.GB2312ToUnicode("安全措施|时刻",buf);
		cell->Set(buf);
		cell->SetFormat(fmt_bold);
	}
		int iItem = 3;
		for (int i = 1; i < 65;i++)
		{
			for(int j = 1; j < 17;j++ )
			{
     			for(int k = 0; k < 266;k++ )
				{
    				if(m_ADRecord[i][j][k].strlocal!="ddd")
						break;
                       	for(col=0; col<8; col++) {
                		BasicExcelCell* cell = sheet->Cell(iItem, col);
                		if(col==0)
                             m_Str2Data.GB2312ToUnicode(m_SlaveStation[i][j].WatchName,buf);
                		else if(col==1)
//					  if((nstatus == 0x40)||(nstatus == 0x50)||(nstatus == 0x70))
//						  strtime= theApp.socketClient.strstatus(nstatus);
                             m_Str2Data.GB2312ToUnicode("1" ,buf);
                		else if(col==2)
						{
							COleDateTime o =m_ADRecord[i][j][k].NTime;
							COleDateTime o1 =m_ADRecord[i][j][k].BTime;
				         	COleDateTimeSpan t = o1-o;
			            	strtime.Format("%d %d:%d:%d",t.GetDays(),t.GetHours(),t.GetMinutes(),t.GetSeconds()); 
                            m_Str2Data.GB2312ToUnicode(strtime ,buf);
						}
                 		else if(col==3)
						{
				    	  strtime.Format("%.2f",m_ADRecord[i][j][k].AMaxValue);
                          m_Str2Data.GB2312ToUnicode(strtime,buf);
						}
                 		else if(col==4)
						{
          				  COleDateTime oleDateTime=m_ADRecord[i][j][k].AMaxTime;
		        		  strtime   =   oleDateTime.Format(_T("%Y-%m-%d %H:%M:%S")); 
                          m_Str2Data.GB2312ToUnicode(strtime,buf);
						}
                 		else if(col==5)
						{
          				  COleDateTime oleDateTime=m_ADRecord[i][j][k].NTime;
		        		  strtime   =   oleDateTime.Format(_T("%Y-%m-%d %H:%M:%S")); 
                          m_Str2Data.GB2312ToUnicode(strtime,buf);
						}
                 		else if(col==6)
						{
          				  COleDateTime oleDateTime=m_ADRecord[i][j][k].BTime;
		        		  strtime   =   oleDateTime.Format(_T("%Y-%m-%d %H:%M:%S")); 
                          m_Str2Data.GB2312ToUnicode(strtime,buf);
						}
                 		else if(col==7)
                          m_Str2Data.GB2312ToUnicode(m_ADRecord[i][j][k].strsafetext,buf);

						cell->Set(buf);
						}
		            	iItem++;
				}//k
			}//j
		}//i
    delete [] buf;
	xls.SaveAs(gstrTimeOut +"\\report\\example.xls");
	copy_sheet(gstrTimeOut +"\\report\\example.xls",gstrTimeOut +"\\report\\sexample.xls");
	ShellExecute(0, NULL, gstrTimeOut +"\\report\\sexample.xls", NULL, NULL, SW_NORMAL);
}

void CMadeCertView::OnRECABD() 
{
	CString strtime,strtime2;
	if(!m_Realtimedata1._IsEmpty())
	{
		m_Realtimedata1.MoveFirst();
		while ( !m_Realtimedata1.IsEOF() )
		{
				int afds = m_Realtimedata1.m_szfds;
				int achan = m_Realtimedata1.m_szchan;
			int m_alarm = m_Realtimedata1.m_szADStatus;
			if(m_alarm == 32)
			{
				if(m_ADRecord[afds][achan][0].duant == 0)
					m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].NTime =m_Realtimedata1.m_szrecdate;
				m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].BTime =m_Realtimedata1.m_szrecdate;

				if(m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].AMaxValue <m_Realtimedata1.m_szAValue)
				{
    				m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].AMaxValue = m_Realtimedata1.m_szAValue;
		    		m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].AMaxTime = m_Realtimedata1.m_szrecdate;
				}
				m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].havev =1;
					strtime = m_Realtimedata1.m_szsafemtext;
					strtime.TrimRight();
					if(strtime != "")
					{
          				  COleDateTime t=m_Realtimedata1.m_szrecdate;
		        		  strtime2   =   t.Format(_T("%Y-%m-%d %H:%M:%S")); 
	       	    		m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].strsafetext += strtime+"|"+strtime2+"|";
					}
				int ffds = m_Realtimedata1.m_szffds;
				int fchan = m_Realtimedata1.m_szfchan;
				if(ffds>0)
				{
          				  COleDateTime oleDateTime=m_Realtimedata1.m_szrecdate;
		        		  strtime2   =   oleDateTime.Format(_T("%Y-%m-%d %H:%M:%S")); 
					strtime = m_Realtimedata1.m_szFeedStatus;
					strtime.TrimRight();
					m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].strlocal +=m_SlaveStation[ffds][fchan].WatchName+"|"
						+strtime+"|"+strtime2+"|";
				}
				m_ADRecord[afds][achan][0].duant++;//n个断电值
			}
			else if(m_alarm == 0)
			{
				if(m_ADRecord[afds][achan][0].duant> 0)
				{
	    			m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].BTime =m_Realtimedata1.m_szrecdate;
	     			m_ADRecord[afds][achan][0].m_ATotalnum++;  //总断电次数
	     			m_ADRecord[afds][achan][0].duant = 0;  //状态转变
				}
			}
			m_Realtimedata1.MoveNext();
		}
	}
	if(!m_Realtimedata._IsEmpty())
	{
		m_Realtimedata.MoveFirst();
		while ( !m_Realtimedata.IsEOF() )
		{
				int afds = m_Realtimedata.m_szfds;
				int achan = m_Realtimedata.m_szchan;
			int m_alarm = m_Realtimedata.m_szADStatus;
			if(m_alarm == 32)
			{
				if(m_ADRecord[afds][achan][0].duant == 0)
					m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].NTime =m_Realtimedata.m_szrecdate;
				m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].BTime =m_Realtimedata.m_szrecdate;

				if(m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].AMaxValue <m_Realtimedata.m_szAValue)
				{
    				m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].AMaxValue = m_Realtimedata.m_szAValue;
		    		m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].AMaxTime = m_Realtimedata.m_szrecdate;
				}
				m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].havev =1;

					strtime = m_Realtimedata.m_szsafemtext;
					strtime.TrimRight();
					if(strtime != "")
					{
          				  COleDateTime t=m_Realtimedata.m_szrecdate;
		        		  strtime2   =   t.Format(_T("%Y-%m-%d %H:%M:%S")); 
	       	    		m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].strsafetext += strtime+"|"+strtime2+"|";
					}
				int ffds = m_Realtimedata.m_szffds;
				int fchan = m_Realtimedata.m_szfchan;
				if(ffds>0)
				{
          				  COleDateTime oleDateTime=m_Realtimedata.m_szrecdate;
		        		  strtime2   =   oleDateTime.Format(_T("%Y-%m-%d %H:%M:%S")); 
					strtime = m_Realtimedata.m_szFeedStatus;
					strtime.TrimRight();
					m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].strlocal +=m_SlaveStation[ffds][fchan].WatchName+"|"
						+strtime+"|"+strtime2+"|";
				}
				m_ADRecord[afds][achan][0].duant++;//n个断电值
			}
			else if(m_alarm == 0)
			{
				if(m_ADRecord[afds][achan][0].duant> 0)
				{
	    			m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].BTime =m_Realtimedata.m_szrecdate;
	     			m_ADRecord[afds][achan][0].m_ATotalnum++;  //总断电次数
	     			m_ADRecord[afds][achan][0].duant = 0;  //状态转变
				}
			}
			m_Realtimedata.MoveNext();
		}
	}
	BasicExcel xls;
//	xls.Load(gstrTimeOut +"\\report\\example.xls");
	xls.New(1);
	BasicExcelWorksheet* sheet = xls.GetWorksheet((size_t)0);
	XLSFormatManager fmt_mgr(xls);

	 // Create a table containing an header row in bold and four rows below.
	ExcelFont font_bold;
	font_bold._weight = FW_BOLD; // 700
	CellFormat fmt_bold(fmt_mgr);
	fmt_bold.set_font(font_bold);

	CString strtime1;
		strtime.Format("(%d-%d-%d %d:00:00----",m_startDateTime.GetYear(),m_startDateTime.GetMonth(),m_startDateTime.GetDay(),m_ctrlStartH); 
		strtime1.Format("%d-%d-%d %d:59:59)",m_endDateTime.GetYear(),m_endDateTime.GetMonth(),m_endDateTime.GetDay(),m_ctrlEndH); 
		ExcelFont font;
//		font.set_color_index(color);
		font.set_weight(500);
		font.set_height(500);
		font.set_font_name(L"Times New Roman");
		CellFormat fmt(fmt_mgr, font);


    WCHAR * buf=new WCHAR[1000];
		BasicExcelCell* cell = sheet->Cell(0, 2);
             m_Str2Data.GB2312ToUnicode("模拟量断电记录查询显示" ,buf);
		cell->Set(buf);
		cell->SetFormat(fmt);

        cell = sheet->Cell(1, 2);
		strtime += strtime1;
             m_Str2Data.GB2312ToUnicode(strtime ,buf);
		cell->Set(buf);
		cell->SetFormat(fmt_bold);

	size_t col = 0;
	for(col=0; col<9; col++) {
		BasicExcelCell* cell = sheet->Cell(2, col);
		if(col==0)
             m_Str2Data.GB2312ToUnicode("安装地点|名称",buf);
		else if(col==1)
             m_Str2Data.GB2312ToUnicode("断电次数",buf);
		else if(col==2)
             m_Str2Data.GB2312ToUnicode("断电时间",buf);
		else if(col==3)
             m_Str2Data.GB2312ToUnicode("最大值",buf);
		else if(col==4)
             m_Str2Data.GB2312ToUnicode("最大值时刻",buf);
		else if(col==5)
             m_Str2Data.GB2312ToUnicode("起始时刻",buf);
		else if(col==6)
             m_Str2Data.GB2312ToUnicode("终止时刻",buf);
		else if(col==7)
             m_Str2Data.GB2312ToUnicode("安全措施|时刻",buf);
		else if(col==8)
             m_Str2Data.GB2312ToUnicode("断电区域|馈电状态|时刻",buf);
//		else if(col==10)
//             m_Str2Data.GB2312ToUnicode("馈电状态|时刻",buf);
		cell->Set(buf);
		cell->SetFormat(fmt_bold);
	}
		int iItem = 3;
		for (int i = 1; i < 65;i++)
		{
			for(int j = 1; j < 17;j++ )
			{
     			for(int k = 0; k < 266;k++ )
				{
    				if(m_ADRecord[i][j][k].havev==0)
						break;
					{
                       	for(col=0; col<9; col++) {
                		BasicExcelCell* cell = sheet->Cell(iItem, col);
                		if(col==0)
                             m_Str2Data.GB2312ToUnicode(m_SlaveStation[i][j].WatchName,buf);
                		else if(col==1)
//					  if((nstatus == 0x40)||(nstatus == 0x50)||(nstatus == 0x70))
//						  strtime= theApp.socketClient.strstatus(nstatus);
                             m_Str2Data.GB2312ToUnicode("1" ,buf);
                		else if(col==2)
						{
							COleDateTime o =m_ADRecord[i][j][k].NTime;
							COleDateTime o1 =m_ADRecord[i][j][k].BTime;
				         	COleDateTimeSpan t = o1-o;
			            	strtime.Format("%d %d:%d:%d",t.GetDays(),t.GetHours(),t.GetMinutes(),t.GetSeconds()); 
                            m_Str2Data.GB2312ToUnicode(strtime ,buf);
						}
                 		else if(col==3)
						{
				    	  strtime.Format("%.2f",m_ADRecord[i][j][k].AMaxValue);
                          m_Str2Data.GB2312ToUnicode(strtime,buf);
						}
                 		else if(col==4)
						{
          				  COleDateTime oleDateTime=m_ADRecord[i][j][k].AMaxTime;
		        		  strtime   =   oleDateTime.Format(_T("%Y-%m-%d %H:%M:%S")); 
                          m_Str2Data.GB2312ToUnicode(strtime,buf);
						}
                 		else if(col==5)
						{
          				  COleDateTime oleDateTime=m_ADRecord[i][j][k].NTime;
		        		  strtime   =   oleDateTime.Format(_T("%Y-%m-%d %H:%M:%S")); 
                          m_Str2Data.GB2312ToUnicode(strtime,buf);
						}
                 		else if(col==6)
						{
          				  COleDateTime oleDateTime=m_ADRecord[i][j][k].BTime;
		        		  strtime   =   oleDateTime.Format(_T("%Y-%m-%d %H:%M:%S")); 
                          m_Str2Data.GB2312ToUnicode(strtime,buf);
						}
                 		else if(col==7)
                          m_Str2Data.GB2312ToUnicode(m_ADRecord[i][j][k].strsafetext,buf);
                 		else if(col==8)
                          m_Str2Data.GB2312ToUnicode(m_ADRecord[i][j][k].strlocal,buf);

						cell->Set(buf);
						}
		            	iItem++;
					}//if
				}//k
			}//j
		}//i
    delete [] buf;
	xls.SaveAs(gstrTimeOut +"\\report\\example.xls");
	copy_sheet(gstrTimeOut +"\\report\\example.xls",gstrTimeOut +"\\report\\sexample.xls");
	ShellExecute(0, NULL, gstrTimeOut +"\\report\\sexample.xls", NULL, NULL, SW_NORMAL);
}

void CMadeCertView::OnRECAFED() 
{
	CString strtime,strtime2;
	if(!m_Realtimedata1._IsEmpty())
	{
		m_Realtimedata1.MoveFirst();
		while ( !m_Realtimedata1.IsEOF() )
		{
				int afds = m_Realtimedata1.m_szfds;
				int achan = m_Realtimedata1.m_szchan;
			strtime = m_Realtimedata1.m_szFeedStatus;
			strtime.TrimRight();
			if(strtime == "异常")
			{
				if(m_ADRecord[afds][achan][0].duant == 0)
					m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].NTime =m_Realtimedata1.m_szrecdate;
				m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].BTime =m_Realtimedata1.m_szrecdate;

					strtime = m_Realtimedata1.m_szsafemtext;
					strtime.TrimRight();
					if(strtime != "")
					{
          				  COleDateTime t=m_Realtimedata1.m_szrecdate;
		        		  strtime2   =   t.Format(_T("%Y-%m-%d %H:%M:%S")); 
	       	    		m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].strsafetext += strtime+"|"+strtime2+"|";
					}
				int ffds = m_Realtimedata1.m_szffds;
				int fchan = m_Realtimedata1.m_szfchan;
				if(ffds>0)
				{
          				  COleDateTime oleDateTime=m_Realtimedata1.m_szrecdate;
		        		  strtime2   =   oleDateTime.Format(_T("%Y-%m-%d %H:%M:%S")); 
					strtime = m_Realtimedata1.m_szFeedStatus;
					strtime.TrimRight();
					m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].strlocal +=m_SlaveStation[ffds][fchan].WatchName+"|"
						+strtime+"|"+strtime2+"|";
				}
				m_ADRecord[afds][achan][0].duant++;//n个馈电异常记录
			}
			else if(strtime == "正常")
			{
				if(m_ADRecord[afds][achan][0].duant> 0)
				{
	    			m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].BTime =m_Realtimedata1.m_szrecdate;
	     			m_ADRecord[afds][achan][0].m_ATotalnum++;  //总馈电异常记录次数
	     			m_ADRecord[afds][achan][0].duant = 0;  //状态转变
				}
			}
			m_Realtimedata1.MoveNext();
		}
	}
	if(!m_Realtimedata._IsEmpty())
	{
		m_Realtimedata.MoveFirst();
		while ( !m_Realtimedata.IsEOF() )
		{
				int afds = m_Realtimedata.m_szfds;
				int achan = m_Realtimedata.m_szchan;
			strtime = m_Realtimedata.m_szFeedStatus;
			strtime.TrimRight();
			if(strtime == "异常")
			{
				if(m_ADRecord[afds][achan][0].duant == 0)
					m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].NTime =m_Realtimedata.m_szrecdate;
				m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].BTime =m_Realtimedata.m_szrecdate;

					strtime = m_Realtimedata.m_szsafemtext;
					strtime.TrimRight();
					if(strtime != "")
					{
          				  COleDateTime t=m_Realtimedata.m_szrecdate;
		        		  strtime2   =   t.Format(_T("%Y-%m-%d %H:%M:%S")); 
	       	    		m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].strsafetext += strtime+"|"+strtime2+"|";
					}
				int ffds = m_Realtimedata.m_szffds;
				int fchan = m_Realtimedata.m_szfchan;
				if(ffds>0)
				{
          				  COleDateTime oleDateTime=m_Realtimedata.m_szrecdate;
		        		  strtime2   =   oleDateTime.Format(_T("%Y-%m-%d %H:%M:%S")); 
					strtime = m_Realtimedata.m_szFeedStatus;
					strtime.TrimRight();
					m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].strlocal +=m_SlaveStation[ffds][fchan].WatchName+"|"
						+strtime+"|"+strtime2+"|";
				}
				m_ADRecord[afds][achan][0].duant++;//n个馈电异常记录值
			}
			else if(strtime == "正常")
			{
				if(m_ADRecord[afds][achan][0].duant> 0)
				{
	    			m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].BTime =m_Realtimedata.m_szrecdate;
	     			m_ADRecord[afds][achan][0].m_ATotalnum++;  //总馈电异常记录次数
	     			m_ADRecord[afds][achan][0].duant = 0;  //状态转变
				}
			}
			m_Realtimedata.MoveNext();
		}
	}
	BasicExcel xls;
//	xls.Load(gstrTimeOut +"\\report\\example.xls");
	xls.New(1);
	BasicExcelWorksheet* sheet = xls.GetWorksheet((size_t)0);
	XLSFormatManager fmt_mgr(xls);

	char buffer[100];
	 // Create a table containing an header row in bold and four rows below.
	ExcelFont font_bold;
	font_bold._weight = FW_BOLD; // 700
	CellFormat fmt_bold(fmt_mgr);
	fmt_bold.set_font(font_bold);

	CString strtime1;
		strtime.Format("(%d-%d-%d %d:00:00----",m_startDateTime.GetYear(),m_startDateTime.GetMonth(),m_startDateTime.GetDay(),m_ctrlStartH); 
		strtime1.Format("%d-%d-%d %d:59:59)",m_endDateTime.GetYear(),m_endDateTime.GetMonth(),m_endDateTime.GetDay(),m_ctrlEndH); 
		ExcelFont font;
//		font.set_color_index(color);
		font.set_weight(500);
		font.set_height(500);
		font.set_font_name(L"Times New Roman");
		CellFormat fmt(fmt_mgr, font);

    WCHAR * buf=new WCHAR[1000];
		BasicExcelCell* cell = sheet->Cell(0, 2);
             m_Str2Data.GB2312ToUnicode("模拟量馈电异常记录查询显示" ,buf);
		cell->Set(buf);
		cell->SetFormat(fmt);

        cell = sheet->Cell(1, 2);
		strtime += strtime1;
             m_Str2Data.GB2312ToUnicode(strtime ,buf);
		cell->Set(buf);
		cell->SetFormat(fmt_bold);

	size_t col = 0;
	for(col=0; col<7; col++) {
		BasicExcelCell* cell = sheet->Cell(2, col);
		if(col==0)
             m_Str2Data.GB2312ToUnicode("安装地点|名称",buf);
		else if(col==1)
             m_Str2Data.GB2312ToUnicode("异常次数",buf);
		else if(col==2)
             m_Str2Data.GB2312ToUnicode("异常时间",buf);
		else if(col==3)
             m_Str2Data.GB2312ToUnicode("起始时刻",buf);
		else if(col==4)
             m_Str2Data.GB2312ToUnicode("终止时刻",buf);
		else if(col==5)
             m_Str2Data.GB2312ToUnicode("安全措施|时刻",buf);
		else if(col==6)
             m_Str2Data.GB2312ToUnicode("断电区域|馈电状态|时刻",buf);
		cell->Set(buf);
		cell->SetFormat(fmt_bold);
	}
		int iItem = 3;
		for (int i = 1; i < 65;i++)
		{
			for(int j = 1; j < 17;j++ )
			{
     			for(int k = 0; k < 266;k++ )
				{
    				if(m_ADRecord[i][j][k].strlocal == "")
						break;
					{
                       	for(col=0; col<7; col++) {
                		BasicExcelCell* cell = sheet->Cell(iItem, col);
                		if(col==0)
                             m_Str2Data.GB2312ToUnicode(m_SlaveStation[i][j].WatchName,buf);
                		else if(col==1)
                             m_Str2Data.GB2312ToUnicode("1" ,buf);
                		else if(col==2)
						{
							COleDateTime o =m_ADRecord[i][j][k].NTime;
							COleDateTime o1 =m_ADRecord[i][j][k].BTime;
				         	COleDateTimeSpan t = o1-o;
			            	strtime.Format("%d %d:%d:%d",t.GetDays(),t.GetHours(),t.GetMinutes(),t.GetSeconds()); 
                            m_Str2Data.GB2312ToUnicode(strtime ,buf);
						}
                 		else if(col==3)
						{
          				  COleDateTime oleDateTime=m_ADRecord[i][j][k].NTime;
		        		  strtime   =   oleDateTime.Format(_T("%Y-%m-%d %H:%M:%S")); 
                          m_Str2Data.GB2312ToUnicode(strtime,buf);
						}
                 		else if(col==4)
						{
          				  COleDateTime oleDateTime=m_ADRecord[i][j][k].BTime;
		        		  strtime   =   oleDateTime.Format(_T("%Y-%m-%d %H:%M:%S")); 
                          m_Str2Data.GB2312ToUnicode(strtime,buf);
						}
                 		else if(col==5)
                          m_Str2Data.GB2312ToUnicode(m_ADRecord[i][j][k].strsafetext,buf);
                 		else if(col==6)
                          m_Str2Data.GB2312ToUnicode(m_ADRecord[i][j][k].strlocal,buf);

						cell->Set(buf);
						}
		            	iItem++;
					}//if
				}//k
			}//j
		}//i
    delete [] buf;
	xls.SaveAs(gstrTimeOut +"\\report\\example.xls");
	copy_sheet(gstrTimeOut +"\\report\\example.xls",gstrTimeOut +"\\report\\sexample.xls");
	ShellExecute(0, NULL, gstrTimeOut +"\\report\\sexample.xls", NULL, NULL, SW_NORMAL);
}

void CMadeCertView::OnRECASR() 
{
	CString strtime,strtime2,strname;
	int m_Atotal =0;
	float fmax,fv,ATotalV;
	ATotalV=fmax =0;
	COleDateTime t;
	if(!m_Rt5mdata._IsEmpty())
	{
		m_Rt5mdata.MoveFirst();
		while ( !m_Rt5mdata.IsEOF() )
		{
				int afds = m_Rt5mdata.m_szfds;
				int achan = m_Rt5mdata.m_szchan;
			strname = m_SlaveStation[afds][achan].WatchName;
						float fcurmax =m_Rt5mdata.m_szAMaxValue;
						if(fmax < fcurmax)
						{
							fmax = fcurmax;
							t = m_Rt5mdata.m_szrecdate;
						}
						float fcurv =m_Rt5mdata.m_szAValue;
						m_Atotal++;
						ATotalV +=fcurv;
			m_Rt5mdata.MoveNext();
		}
	}
	BasicExcel xls;
//	xls.Load(gstrTimeOut +"\\report\\example.xls");
	xls.New(1);
	BasicExcelWorksheet* sheet = xls.GetWorksheet((size_t)0);
	XLSFormatManager fmt_mgr(xls);

	 // Create a table containing an header row in bold and four rows below.
	ExcelFont font_bold;
	font_bold._weight = FW_BOLD; // 700
	CellFormat fmt_bold(fmt_mgr);
	fmt_bold.set_font(font_bold);

	CString strtime1;
		strtime.Format("(%d-%d-%d %d:00:00----",m_startDateTime.GetYear(),m_startDateTime.GetMonth(),m_startDateTime.GetDay(),m_ctrlStartH); 
		strtime1.Format("%d-%d-%d %d:59:59)",m_endDateTime.GetYear(),m_endDateTime.GetMonth(),m_endDateTime.GetDay(),m_ctrlEndH); 
		ExcelFont font;
//		font.set_color_index(color);
		font.set_weight(500);
		font.set_height(500);
		font.set_font_name(L"Times New Roman");
		CellFormat fmt(fmt_mgr, font);

    WCHAR * buf=new WCHAR[1000];
		BasicExcelCell* cell = sheet->Cell(0, 2);
             m_Str2Data.GB2312ToUnicode("模拟量统计值记录查询显示" ,buf);
		cell->Set(buf);
		cell->SetFormat(fmt);

        cell = sheet->Cell(1, 2);
		strtime += strtime1;
             m_Str2Data.GB2312ToUnicode(strtime ,buf);
		cell->Set(buf);
		cell->SetFormat(fmt_bold);

	size_t col = 0;
	for(col=0; col<7; col++) {
		BasicExcelCell* cell = sheet->Cell(2, col);
		if(col==0)
             m_Str2Data.GB2312ToUnicode("安装地点|名称",buf);
		else if(col==1)
             m_Str2Data.GB2312ToUnicode("最大值",buf);
		else if(col==2)
             m_Str2Data.GB2312ToUnicode("最大值时刻",buf);
		else if(col==3)
             m_Str2Data.GB2312ToUnicode("平均值",buf);
		else if(col==4)
             m_Str2Data.GB2312ToUnicode("每五分最大值",buf);
		else if(col==5)
             m_Str2Data.GB2312ToUnicode("每五分平均值",buf);
		else if(col==6)
             m_Str2Data.GB2312ToUnicode("每五分时刻",buf);
		cell->Set(buf);
		cell->SetFormat(fmt_bold);
	}
		int iItem = 3;
	if(!m_Rt5mdata._IsEmpty())
	{
			    	strtime2.Format(_T("%.2f"), fmax);
					fv =ATotalV/m_Atotal;
					strtime1.Format(_T("%.2f"), fv);
		            strtime   =   t.Format(_T("%Y-%m-%d %H:%M:%S")); 
		m_Rt5mdata.MoveFirst();
		while ( !m_Rt5mdata.IsEOF() )
		{
            	CString str1,str2;
			    	str1.Format(_T("%.2f"), m_Rt5mdata.m_szAMaxValue);
					str2.Format(_T("%.2f"), m_Rt5mdata.m_szAValue);
                  for(col=0; col<7; col++) {
                		BasicExcelCell* cell = sheet->Cell(iItem, col);
                		if(col==0)
                             m_Str2Data.GB2312ToUnicode(strname,buf);
                		else if(col==1)
                             m_Str2Data.GB2312ToUnicode(strtime2 ,buf);
                		else if(col==2)
                          m_Str2Data.GB2312ToUnicode(strtime,buf);
                 		else if(col==3)
                             m_Str2Data.GB2312ToUnicode(strtime1 ,buf);
                 		else if(col==4)
                          m_Str2Data.GB2312ToUnicode(str1,buf);
                 		else if(col==5)
                          m_Str2Data.GB2312ToUnicode(str2,buf);
                 		else if(col==6)
						{
          				  COleDateTime oleDateTime=m_Rt5mdata.m_szrecdate;
		        		  str1   =   oleDateTime.Format(_T("%Y-%m-%d %H:%M:%S")); 
                          m_Str2Data.GB2312ToUnicode(str1,buf);
						}
						cell->Set(buf);
				  }
		          iItem++;
			m_Rt5mdata.MoveNext();
		}
	}
    delete [] buf;
	xls.SaveAs(gstrTimeOut +"\\report\\example.xls");
	copy_sheet(gstrTimeOut +"\\report\\example.xls",gstrTimeOut +"\\report\\sexample.xls");
	ShellExecute(0, NULL, gstrTimeOut +"\\report\\sexample.xls", NULL, NULL, SW_NORMAL);
}

void CMadeCertView::OnRECDABD() 
{
	CString strtime,strtime2;
	if(!m_Realtimedata1._IsEmpty())
	{
		m_Realtimedata1.MoveFirst();
		while ( !m_Realtimedata1.IsEOF() )
		{
				int afds = m_Realtimedata1.m_szfds;
				int achan = m_Realtimedata1.m_szchan;
			int m_alarm = m_Realtimedata1.m_szADStatus;
			if(m_alarm == 16)
			{
				if(m_ADRecord[afds][achan][0].duant == 0)
					m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].NTime =m_Realtimedata1.m_szrecdate;
				m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].BTime =m_Realtimedata1.m_szrecdate;

    				int nstatus=m_Realtimedata1.m_szCDValue;
     			   	if(nstatus ==0)
                          m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].strlocal=m_SlaveStation[afds][achan].ZeroState;
					  else if(nstatus == 1)
						  m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].strlocal= m_SlaveStation[afds][achan].OneState;
					  else if(nstatus == 2)
						  m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].strlocal= m_SlaveStation[afds][achan].TwoState;
					strtime.TrimRight();
					if(strtime != "")
					{
          				  COleDateTime t=m_Realtimedata1.m_szrecdate;
		        		  strtime2   =   t.Format(_T("%Y-%m-%d %H:%M:%S")); 
	       	    		m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].strsafetext += strtime+"|"+strtime2+"|";
					}
				m_ADRecord[afds][achan][0].duant++;//n个报警值
			}
			else if(m_alarm == 0)
			{
				if(m_ADRecord[afds][achan][0].duant> 0)
				{
	    			m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].BTime =m_Realtimedata1.m_szrecdate;
	     			m_ADRecord[afds][achan][0].m_ATotalnum++;  //总报警次数
	     			m_ADRecord[afds][achan][0].duant = 0;  //状态转变
				}
			}
			m_Realtimedata1.MoveNext();
		}
	}
	if(!m_Realtimedata._IsEmpty())
	{
		m_Realtimedata.MoveFirst();
		while ( !m_Realtimedata.IsEOF() )
		{
				int afds = m_Realtimedata.m_szfds;
				int achan = m_Realtimedata.m_szchan;
          if(achan<17)
		  {
			int m_alarm = m_Realtimedata.m_szADStatus;
			if(m_alarm == 16)
			{
				if(m_ADRecord[afds][achan][0].duant == 0)
					m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].NTime =m_Realtimedata.m_szrecdate;
				m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].BTime =m_Realtimedata.m_szrecdate;

    				int nstatus=m_Realtimedata.m_szCDValue;
     			   	if(nstatus ==0)
                          m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].strlocal=m_SlaveStation[afds][achan].ZeroState;
					  else if(nstatus == 1)
						  m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].strlocal= m_SlaveStation[afds][achan].OneState;
					  else if(nstatus == 2)
						  m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].strlocal= m_SlaveStation[afds][achan].TwoState;
					strtime = m_Realtimedata.m_szsafemtext;
					strtime.TrimRight();
					if(strtime != "")
					{
          				  COleDateTime t=m_Realtimedata.m_szrecdate;
		        		  strtime2   =   t.Format(_T("%Y-%m-%d %H:%M:%S")); 
	       	    		m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].strsafetext += strtime+"|"+strtime2+"|";
					}
				m_ADRecord[afds][achan][0].duant++;//n个报警值
			}
			else if(m_alarm == 0)
			{
				if(m_ADRecord[afds][achan][0].duant> 0)
				{
	    			m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].BTime =m_Realtimedata.m_szrecdate;
	     			m_ADRecord[afds][achan][0].m_ATotalnum++;  //总报警次数
	     			m_ADRecord[afds][achan][0].duant = 0;  //状态转变
				}
			}
		  }
			m_Realtimedata.MoveNext();
		}
	}
	BasicExcel xls;
//	xls.Load(gstrTimeOut +"\\report\\example.xls");
	xls.New(1);
	BasicExcelWorksheet* sheet = xls.GetWorksheet((size_t)0);
	XLSFormatManager fmt_mgr(xls);

	 // Create a table containing an header row in bold and four rows below.
	ExcelFont font_bold;
	font_bold._weight = FW_BOLD; // 700
	CellFormat fmt_bold(fmt_mgr);
	fmt_bold.set_font(font_bold);

	CString strtime1;
		strtime.Format("(%d-%d-%d %d:00:00----",m_startDateTime.GetYear(),m_startDateTime.GetMonth(),m_startDateTime.GetDay(),m_ctrlStartH); 
		strtime1.Format("%d-%d-%d %d:59:59)",m_endDateTime.GetYear(),m_endDateTime.GetMonth(),m_endDateTime.GetDay(),m_ctrlEndH); 
		ExcelFont font;
//		font.set_color_index(color);
		font.set_weight(500);
		font.set_height(500);
		font.set_font_name(L"Times New Roman");
		CellFormat fmt(fmt_mgr, font);


    WCHAR * buf=new WCHAR[200];
		BasicExcelCell* cell = sheet->Cell(0, 2);
             m_Str2Data.GB2312ToUnicode("开关量报警记录查询显示" ,buf);
		cell->Set(buf);
		cell->SetFormat(fmt);

        cell = sheet->Cell(1, 2);
		strtime += strtime1;
             m_Str2Data.GB2312ToUnicode(strtime ,buf);
		cell->Set(buf);
		cell->SetFormat(fmt_bold);

	size_t col = 0;
	for(col=0; col<7; col++) {
		BasicExcelCell* cell = sheet->Cell(2, col);
		if(col==0)
             m_Str2Data.GB2312ToUnicode("安装地点|名称",buf);
		else if(col==1)
             m_Str2Data.GB2312ToUnicode("报警次数",buf);
		else if(col==2)
             m_Str2Data.GB2312ToUnicode("报警时间",buf);
		else if(col==3)
             m_Str2Data.GB2312ToUnicode("报警状态",buf);
		else if(col==4)
             m_Str2Data.GB2312ToUnicode("起始时刻",buf);
		else if(col==5)
             m_Str2Data.GB2312ToUnicode("终止时刻",buf);
		else if(col==6)
             m_Str2Data.GB2312ToUnicode("安全措施|时刻",buf);
		cell->Set(buf);
		cell->SetFormat(fmt_bold);
	}
		int iItem = 3;
		for (int i = 1; i < 65;i++)
		{
			for(int j = 1; j < 17;j++ )
			{
     			for(int k = 0; k < 266;k++ )
				{
    				if(m_ADRecord[i][j][k].strlocal == "")
						break;
					{
                       	for(col=0; col<7; col++) {
                		BasicExcelCell* cell = sheet->Cell(iItem, col);
                		if(col==0)
                             m_Str2Data.GB2312ToUnicode(m_SlaveStation[i][j].WatchName,buf);
                		else if(col==1)
                             m_Str2Data.GB2312ToUnicode("1" ,buf);
                		else if(col==2)
						{
							COleDateTime o =m_ADRecord[i][j][k].NTime;
							COleDateTime o1 =m_ADRecord[i][j][k].BTime;
				         	COleDateTimeSpan t = o1-o;
			            	strtime.Format("%d %d:%d:%d",t.GetDays(),t.GetHours(),t.GetMinutes(),t.GetSeconds()); 
                            m_Str2Data.GB2312ToUnicode(strtime ,buf);
						}
                 		else if(col==3)
                          m_Str2Data.GB2312ToUnicode(m_ADRecord[i][j][k].strlocal,buf);
                 		else if(col==4)
						{
          				  COleDateTime oleDateTime=m_ADRecord[i][j][k].NTime;
		        		  strtime   =   oleDateTime.Format(_T("%Y-%m-%d %H:%M:%S")); 
                          m_Str2Data.GB2312ToUnicode(strtime,buf);
						}
                 		else if(col==5)
						{
          				  COleDateTime oleDateTime=m_ADRecord[i][j][k].BTime;
		        		  strtime   =   oleDateTime.Format(_T("%Y-%m-%d %H:%M:%S")); 
                          m_Str2Data.GB2312ToUnicode(strtime,buf);
						}
                 		else if(col==6)
                          m_Str2Data.GB2312ToUnicode(m_ADRecord[i][j][k].strsafetext,buf);
						cell->Set(buf);
						}
		            	iItem++;
					}//if
				}//k
			}//j
		}//i
    delete [] buf;
	xls.SaveAs(gstrTimeOut +"\\report\\example.xls");
	copy_sheet(gstrTimeOut +"\\report\\example.xls",gstrTimeOut +"\\report\\sexample.xls");
	ShellExecute(0, NULL, gstrTimeOut +"\\report\\sexample.xls", NULL, NULL, SW_NORMAL);
}

void CMadeCertView::OnRECDABB() //开关量断电
{
	CString strtime,strtime2;
	if(!m_Realtimedata1._IsEmpty())
	{
		m_Realtimedata1.MoveFirst();
		while ( !m_Realtimedata1.IsEOF() )
		{
				int afds = m_Realtimedata1.m_szfds;
				int achan = m_Realtimedata1.m_szchan;
          if(achan<17)
		  {
			int m_alarm = m_Realtimedata1.m_szADStatus;
			if(m_alarm == 32)
			{
				if(m_ADRecord[afds][achan][0].duant == 0)
					m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].NTime =m_Realtimedata1.m_szrecdate;
				m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].BTime =m_Realtimedata1.m_szrecdate;

    				int nstatus=m_Realtimedata1.m_szCDValue;
     			   	if(nstatus ==0)
                          m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].strlocal=m_SlaveStation[afds][achan].ZeroState;
					  else if(nstatus == 1)
						  m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].strlocal= m_SlaveStation[afds][achan].OneState;
					  else if(nstatus == 2)
						  m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].strlocal= m_SlaveStation[afds][achan].TwoState;
					strtime.TrimRight();
					if(strtime != "")
					{
          				  COleDateTime t=m_Realtimedata1.m_szrecdate;
		        		  strtime2   =   t.Format(_T("%Y-%m-%d %H:%M:%S")); 
	       	    		m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].strsafetext += strtime+"|"+strtime2+"|";
					}
				m_ADRecord[afds][achan][0].duant++;//n个断电值
			}
			else if(m_alarm == 0)
			{
				if(m_ADRecord[afds][achan][0].duant> 0)
				{
	    			m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].BTime =m_Realtimedata1.m_szrecdate;
	     			m_ADRecord[afds][achan][0].m_ATotalnum++;  //总断电次数
	     			m_ADRecord[afds][achan][0].duant = 0;  //状态转变
				}
			}
		  }
			m_Realtimedata1.MoveNext();
		}
	}
	if(!m_Realtimedata._IsEmpty())
	{
		m_Realtimedata.MoveFirst();
		while ( !m_Realtimedata.IsEOF() )
		{
				int afds = m_Realtimedata.m_szfds;
				int achan = m_Realtimedata.m_szchan;
			int m_alarm = m_Realtimedata.m_szADStatus;
			if(m_alarm == 16)
			{
				if(m_ADRecord[afds][achan][0].duant == 0)
					m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].NTime =m_Realtimedata.m_szrecdate;
				m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].BTime =m_Realtimedata.m_szrecdate;

    				int nstatus=m_Realtimedata.m_szCDValue;
     			   	if(nstatus ==0)
                          m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].strlocal=m_SlaveStation[afds][achan].ZeroState;
					  else if(nstatus == 1)
						  m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].strlocal= m_SlaveStation[afds][achan].OneState;
					  else if(nstatus == 2)
						  m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].strlocal= m_SlaveStation[afds][achan].TwoState;
					strtime = m_Realtimedata.m_szsafemtext;
					strtime.TrimRight();
					if(strtime != "")
					{
          				  COleDateTime t=m_Realtimedata.m_szrecdate;
		        		  strtime2   =   t.Format(_T("%Y-%m-%d %H:%M:%S")); 
	       	    		m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].strsafetext += strtime+"|"+strtime2+"|";
					}
				m_ADRecord[afds][achan][0].duant++;//n个断电值
			}
			else if(m_alarm == 0)
			{
				if(m_ADRecord[afds][achan][0].duant> 0)
				{
	    			m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].BTime =m_Realtimedata.m_szrecdate;
	     			m_ADRecord[afds][achan][0].m_ATotalnum++;  //总断电次数
	     			m_ADRecord[afds][achan][0].duant = 0;  //状态转变
				}
			}
			m_Realtimedata.MoveNext();
		}
	}
	BasicExcel xls;
//	xls.Load(gstrTimeOut +"\\report\\example.xls");
	xls.New(1);
	BasicExcelWorksheet* sheet = xls.GetWorksheet((size_t)0);
	XLSFormatManager fmt_mgr(xls);

	 // Create a table containing an header row in bold and four rows below.
	ExcelFont font_bold;
	font_bold._weight = FW_BOLD; // 700
	CellFormat fmt_bold(fmt_mgr);
	fmt_bold.set_font(font_bold);

	CString strtime1;
		strtime.Format("(%d-%d-%d %d:00:00----",m_startDateTime.GetYear(),m_startDateTime.GetMonth(),m_startDateTime.GetDay(),m_ctrlStartH); 
		strtime1.Format("%d-%d-%d %d:59:59)",m_endDateTime.GetYear(),m_endDateTime.GetMonth(),m_endDateTime.GetDay(),m_ctrlEndH); 
		ExcelFont font;
//		font.set_color_index(color);
		font.set_weight(500);
		font.set_height(500);
		font.set_font_name(L"Times New Roman");
		CellFormat fmt(fmt_mgr, font);


    WCHAR * buf=new WCHAR[200];
		BasicExcelCell* cell = sheet->Cell(0, 2);
             m_Str2Data.GB2312ToUnicode("开关量断电记录查询显示" ,buf);
		cell->Set(buf);
		cell->SetFormat(fmt);

        cell = sheet->Cell(1, 2);
		strtime += strtime1;
             m_Str2Data.GB2312ToUnicode(strtime ,buf);
		cell->Set(buf);
		cell->SetFormat(fmt_bold);

	size_t col = 0;
	for(col=0; col<7; col++) {
		BasicExcelCell* cell = sheet->Cell(2, col);
		if(col==0)
             m_Str2Data.GB2312ToUnicode("安装地点|名称",buf);
		else if(col==1)
             m_Str2Data.GB2312ToUnicode("断电次数",buf);
		else if(col==2)
             m_Str2Data.GB2312ToUnicode("断电时间",buf);
		else if(col==3)
             m_Str2Data.GB2312ToUnicode("断电状态",buf);
		else if(col==4)
             m_Str2Data.GB2312ToUnicode("起始时刻",buf);
		else if(col==5)
             m_Str2Data.GB2312ToUnicode("终止时刻",buf);
		else if(col==6)
             m_Str2Data.GB2312ToUnicode("安全措施|时刻",buf);
		cell->Set(buf);
		cell->SetFormat(fmt_bold);
	}
		int iItem = 3;
		for (int i = 1; i < 65;i++)
		{
			for(int j = 1; j < 17;j++ )
			{
     			for(int k = 0; k < 266;k++ )
				{
    				if(m_ADRecord[i][j][k].strlocal == "")
						break;
					{
                       	for(col=0; col<7; col++) {
                		BasicExcelCell* cell = sheet->Cell(iItem, col);
                		if(col==0)
                             m_Str2Data.GB2312ToUnicode(m_SlaveStation[i][j].WatchName,buf);
                		else if(col==1)
                             m_Str2Data.GB2312ToUnicode("1" ,buf);
                		else if(col==2)
						{
							COleDateTime o =m_ADRecord[i][j][k].NTime;
							COleDateTime o1 =m_ADRecord[i][j][k].BTime;
				         	COleDateTimeSpan t = o1-o;
			            	strtime.Format("%d %d:%d:%d",t.GetDays(),t.GetHours(),t.GetMinutes(),t.GetSeconds()); 
                            m_Str2Data.GB2312ToUnicode(strtime ,buf);
						}
                 		else if(col==3)
                          m_Str2Data.GB2312ToUnicode(m_ADRecord[i][j][k].strlocal,buf);
                 		else if(col==4)
						{
          				  COleDateTime oleDateTime=m_ADRecord[i][j][k].NTime;
		        		  strtime   =   oleDateTime.Format(_T("%Y-%m-%d %H:%M:%S")); 
                          m_Str2Data.GB2312ToUnicode(strtime,buf);
						}
                 		else if(col==5)
						{
          				  COleDateTime oleDateTime=m_ADRecord[i][j][k].BTime;
		        		  strtime   =   oleDateTime.Format(_T("%Y-%m-%d %H:%M:%S")); 
                          m_Str2Data.GB2312ToUnicode(strtime,buf);
						}
                 		else if(col==6)
                          m_Str2Data.GB2312ToUnicode(m_ADRecord[i][j][k].strsafetext,buf);
						cell->Set(buf);
						}
		            	iItem++;
					}//if
				}//k
			}//j
		}//i
    delete [] buf;
	xls.SaveAs(gstrTimeOut +"\\report\\example.xls");
	copy_sheet(gstrTimeOut +"\\report\\example.xls",gstrTimeOut +"\\report\\sexample.xls");
	ShellExecute(0, NULL, gstrTimeOut +"\\report\\sexample.xls", NULL, NULL, SW_NORMAL);
}

void CMadeCertView::OnRECDFED() //开关量馈电异常
{
	CString strtime,strtime2;
	if(!m_Realtimedata1._IsEmpty())
	{
		m_Realtimedata1.MoveFirst();
		while ( !m_Realtimedata1.IsEOF() )
		{
				int afds = m_Realtimedata1.m_szfds;
				int achan = m_Realtimedata1.m_szchan;
			strtime = m_Realtimedata1.m_szFeedStatus;
			strtime.TrimRight();
			if(strtime == "异常")
			{
				if(m_ADRecord[afds][achan][0].duant == 0)
					m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].NTime =m_Realtimedata1.m_szrecdate;
				m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].BTime =m_Realtimedata1.m_szrecdate;

					strtime = m_Realtimedata1.m_szsafemtext;
					strtime.TrimRight();
					if(strtime != "")
					{
          				  COleDateTime t=m_Realtimedata1.m_szrecdate;
		        		  strtime2   =   t.Format(_T("%Y-%m-%d %H:%M:%S")); 
	       	    		m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].strsafetext += strtime+"|"+strtime2+"|";
					}
				int ffds = m_Realtimedata1.m_szffds;
				int fchan = m_Realtimedata1.m_szfchan;
				if(ffds>0)
				{
          				  COleDateTime oleDateTime=m_Realtimedata1.m_szrecdate;
		        		  strtime2   =   oleDateTime.Format(_T("%Y-%m-%d %H:%M:%S")); 
					strtime = m_Realtimedata1.m_szFeedStatus;
					strtime.TrimRight();
					m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].strlocal +=m_SlaveStation[ffds][fchan].WatchName+"|"
						+strtime+"|"+strtime2+"|";
				}
				m_ADRecord[afds][achan][0].duant++;//n个馈电异常记录
			}
			else if(strtime == "正常")
			{
				if(m_ADRecord[afds][achan][0].duant> 0)
				{
	    			m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].BTime =m_Realtimedata1.m_szrecdate;
	     			m_ADRecord[afds][achan][0].m_ATotalnum++;  //总馈电异常记录次数
	     			m_ADRecord[afds][achan][0].duant = 0;  //状态转变
				}
			}
			m_Realtimedata1.MoveNext();
		}
	}
	if(!m_Realtimedata._IsEmpty())
	{
		m_Realtimedata.MoveFirst();
		while ( !m_Realtimedata.IsEOF() )
		{
				int afds = m_Realtimedata.m_szfds;
				int achan = m_Realtimedata.m_szchan;
			strtime = m_Realtimedata.m_szFeedStatus;
			strtime.TrimRight();
			if(strtime == "异常")
			{
				if(m_ADRecord[afds][achan][0].duant == 0)
					m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].NTime =m_Realtimedata.m_szrecdate;
				m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].BTime =m_Realtimedata.m_szrecdate;

					strtime = m_Realtimedata.m_szsafemtext;
					strtime.TrimRight();
					if(strtime != "")
					{
          				  COleDateTime t=m_Realtimedata.m_szrecdate;
		        		  strtime2   =   t.Format(_T("%Y-%m-%d %H:%M:%S")); 
	       	    		m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].strsafetext += strtime+"|"+strtime2+"|";
					}
				int ffds = m_Realtimedata.m_szffds;
				int fchan = m_Realtimedata.m_szfchan;
				if(ffds>0)
				{
          				  COleDateTime oleDateTime=m_Realtimedata.m_szrecdate;
		        		  strtime2   =   oleDateTime.Format(_T("%Y-%m-%d %H:%M:%S")); 
					strtime = m_Realtimedata.m_szFeedStatus;
					strtime.TrimRight();
					m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].strlocal +=m_SlaveStation[ffds][fchan].WatchName+"|"
						+strtime+"|"+strtime2+"|";
				}
				m_ADRecord[afds][achan][0].duant++;//n个馈电异常记录值
			}
			else if(strtime == "正常")
			{
				if(m_ADRecord[afds][achan][0].duant> 0)
				{
	    			m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].BTime =m_Realtimedata.m_szrecdate;
	     			m_ADRecord[afds][achan][0].m_ATotalnum++;  //总馈电异常记录次数
	     			m_ADRecord[afds][achan][0].duant = 0;  //状态转变
				}
			}
			m_Realtimedata.MoveNext();
		}
	}
	BasicExcel xls;
//	xls.Load(gstrTimeOut +"\\report\\example.xls");
	xls.New(1);
	BasicExcelWorksheet* sheet = xls.GetWorksheet((size_t)0);
	XLSFormatManager fmt_mgr(xls);

	 // Create a table containing an header row in bold and four rows below.
	ExcelFont font_bold;
	font_bold._weight = FW_BOLD; // 700
	CellFormat fmt_bold(fmt_mgr);
	fmt_bold.set_font(font_bold);

	CString strtime1;
		strtime.Format("(%d-%d-%d %d:00:00----",m_startDateTime.GetYear(),m_startDateTime.GetMonth(),m_startDateTime.GetDay(),m_ctrlStartH); 
		strtime1.Format("%d-%d-%d %d:59:59)",m_endDateTime.GetYear(),m_endDateTime.GetMonth(),m_endDateTime.GetDay(),m_ctrlEndH); 
		ExcelFont font;
//		font.set_color_index(color);
		font.set_weight(500);
		font.set_height(500);
		font.set_font_name(L"Times New Roman");
		CellFormat fmt(fmt_mgr, font);

    WCHAR * buf=new WCHAR[20000];
		BasicExcelCell* cell = sheet->Cell(0, 2);
             m_Str2Data.GB2312ToUnicode("开关量馈电异常记录查询显示" ,buf);
		cell->Set(buf);
		cell->SetFormat(fmt);

        cell = sheet->Cell(1, 2);
		strtime += strtime1;
             m_Str2Data.GB2312ToUnicode(strtime ,buf);
		cell->Set(buf);
		cell->SetFormat(fmt_bold);

	size_t col = 0;
	for(col=0; col<7; col++) {
		BasicExcelCell* cell = sheet->Cell(2, col);
		if(col==0)
             m_Str2Data.GB2312ToUnicode("安装地点|名称",buf);
		else if(col==1)
             m_Str2Data.GB2312ToUnicode("异常次数",buf);
		else if(col==2)
             m_Str2Data.GB2312ToUnicode("异常时间",buf);
		else if(col==3)
             m_Str2Data.GB2312ToUnicode("起始时刻",buf);
		else if(col==4)
             m_Str2Data.GB2312ToUnicode("终止时刻",buf);
		else if(col==5)
             m_Str2Data.GB2312ToUnicode("安全措施|时刻",buf);
		else if(col==6)
             m_Str2Data.GB2312ToUnicode("断电区域|馈电状态|时刻",buf);
		cell->Set(buf);
		cell->SetFormat(fmt_bold);
	}
		int iItem = 3;
		for (int i = 1; i < 65;i++)
		{
			for(int j = 1; j < 17;j++ )
			{
     			for(int k = 0; k < 266;k++ )
				{
    				if(m_ADRecord[i][j][k].strlocal == "")
						break;
					{
                       	for(col=0; col<7; col++) {
                		BasicExcelCell* cell = sheet->Cell(iItem, col);
                		if(col==0)
                             m_Str2Data.GB2312ToUnicode(m_SlaveStation[i][j].WatchName,buf);
                		else if(col==1)
                             m_Str2Data.GB2312ToUnicode("1" ,buf);
                		else if(col==2)
						{
							COleDateTime o =m_ADRecord[i][j][k].NTime;
							COleDateTime o1 =m_ADRecord[i][j][k].BTime;
				         	COleDateTimeSpan t = o1-o;
			            	strtime.Format("%d %d:%d:%d",t.GetDays(),t.GetHours(),t.GetMinutes(),t.GetSeconds()); 
                            m_Str2Data.GB2312ToUnicode(strtime ,buf);
						}
                 		else if(col==3)
						{
          				  COleDateTime oleDateTime=m_ADRecord[i][j][k].NTime;
		        		  strtime   =   oleDateTime.Format(_T("%Y-%m-%d %H:%M:%S")); 
                          m_Str2Data.GB2312ToUnicode(strtime,buf);
						}
                 		else if(col==4)
						{
          				  COleDateTime oleDateTime=m_ADRecord[i][j][k].BTime;
		        		  strtime   =   oleDateTime.Format(_T("%Y-%m-%d %H:%M:%S")); 
                          m_Str2Data.GB2312ToUnicode(strtime,buf);
						}
                 		else if(col==5)
                          m_Str2Data.GB2312ToUnicode(m_ADRecord[i][j][k].strsafetext,buf);
                 		else if(col==6)
                          m_Str2Data.GB2312ToUnicode(m_ADRecord[i][j][k].strlocal,buf);

						cell->Set(buf);
						}
		            	iItem++;
					}//if
				}//k
			}//j
		}//i
    delete [] buf;
	xls.SaveAs(gstrTimeOut +"\\report\\example.xls");
	copy_sheet(gstrTimeOut +"\\report\\example.xls",gstrTimeOut +"\\report\\sexample.xls");
	ShellExecute(0, NULL, gstrTimeOut +"\\report\\sexample.xls", NULL, NULL, SW_NORMAL);
}

void CMadeCertView::OnRECDSCD() //开关量状态变动记录
{
	BasicExcel xls;
//	xls.Load(gstrTimeOut +"\\report\\example.xls");
	xls.New(1);
	BasicExcelWorksheet* sheet = xls.GetWorksheet((size_t)0);
	XLSFormatManager fmt_mgr(xls);

	CString strtime,strtime1;
	 // Create a table containing an header row in bold and four rows below.
	ExcelFont font_bold;
	font_bold._weight = FW_BOLD; // 700
	CellFormat fmt_bold(fmt_mgr);
	fmt_bold.set_font(font_bold);

		strtime.Format("(%d-%d-%d %d:00:00----",m_startDateTime.GetYear(),m_startDateTime.GetMonth(),m_startDateTime.GetDay(),m_ctrlStartH); 
		strtime1.Format("%d-%d-%d %d:59:59)",m_endDateTime.GetYear(),m_endDateTime.GetMonth(),m_endDateTime.GetDay(),m_ctrlEndH); 
		ExcelFont font;
//		font.set_color_index(color);
		font.set_weight(500);
		font.set_height(500);
		font.set_font_name(L"Times New Roman");
		CellFormat fmt(fmt_mgr, font);

    WCHAR * buf=new WCHAR[1000];
		BasicExcelCell* cell = sheet->Cell(0, 2);
             m_Str2Data.GB2312ToUnicode("开关量状态变动记录查询显示" ,buf);
		cell->Set(buf);
		cell->SetFormat(fmt);

        cell = sheet->Cell(1, 2);
		strtime += strtime1;
             m_Str2Data.GB2312ToUnicode(strtime ,buf);
		cell->Set(buf);
		cell->SetFormat(fmt_bold);

	size_t col = 0;
	for(col=0; col<5; col++) {
		BasicExcelCell* cell = sheet->Cell(2, col);
		if(col==0)
             m_Str2Data.GB2312ToUnicode("安装地点|名称",buf);
		else if(col==1)
             m_Str2Data.GB2312ToUnicode("动作次数",buf);
		else if(col==2)
             m_Str2Data.GB2312ToUnicode("动作状态",buf);
		else if(col==3)
             m_Str2Data.GB2312ToUnicode("起始时刻",buf);
		else if(col==4)
             m_Str2Data.GB2312ToUnicode("累计时间",buf);
		cell->Set(buf);
		cell->SetFormat(fmt_bold);
	}
		int iItem = 3;
		int m_s[10000];
		COleDateTime o[10000];
	if(!m_Realtimedata1._IsEmpty())
	{
		m_Realtimedata1.MoveFirst();
		while ( !m_Realtimedata1.IsEOF() )
		{
				int afds = m_Realtimedata1.m_szfds;
				int achan = m_Realtimedata1.m_szchan;
				int nstatus = m_Realtimedata1.m_szCDValue;
				m_s[iItem]=nstatus;
			if(nstatus != m_s[iItem-1])
			{
            	for(col=0; col<5; col++) {
         		BasicExcelCell* cell = sheet->Cell(iItem, col);
         		if(col==0)
                      m_Str2Data.GB2312ToUnicode(m_SlaveStation[afds][achan].WatchName,buf);
        		else if(col==1)
                      m_Str2Data.GB2312ToUnicode("1" ,buf);
         		else if(col==2)
				{
					  if(nstatus == 0)
						  strtime= m_SlaveStation[afds][achan].ZeroState;
					  else if(nstatus == 1)
						  strtime= m_SlaveStation[afds][achan].OneState;
					  else if(nstatus == 2)
						  strtime= m_SlaveStation[afds][achan].TwoState;
                      m_Str2Data.GB2312ToUnicode(strtime ,buf);
				}
         		else if(col==3)
				{
				  COleDateTime oleDateTime=m_Realtimedata1.m_szrecdate;
				  strtime   =   oleDateTime.Format(_T("%Y-%m-%d %H:%M:%S")); 
                      m_Str2Data.GB2312ToUnicode(strtime,buf);
				}
         		else if(col==4)
				{
					o[iItem] =m_Realtimedata1.m_szrecdate;
					if(iItem != 3)
					{
							cell = sheet->Cell(iItem-1, 4);
				         	COleDateTimeSpan t = o[iItem]-o[iItem-1];
			            	strtime.Format("%d %d:%d:%d",t.GetDays(),t.GetHours(),t.GetMinutes(),t.GetSeconds()); 
                            m_Str2Data.GB2312ToUnicode(strtime ,buf);
					}
				}
        		cell->Set(buf);
				}
	    		iItem++;
			}
			m_Realtimedata1.MoveNext();
		}
	}
	if(!m_Realtimedata._IsEmpty())
	{
		m_Realtimedata.MoveFirst();
		while ( !m_Realtimedata.IsEOF() )
		{
				int afds = m_Realtimedata.m_szfds;
				int achan = m_Realtimedata.m_szchan;
				int nstatus = m_Realtimedata.m_szCDValue;
				m_s[iItem]=nstatus;
			if(nstatus != m_s[iItem-1])
			{
            	for(col=0; col<5; col++) {
         		BasicExcelCell* cell = sheet->Cell(iItem, col);
         		if(col==0)
                      m_Str2Data.GB2312ToUnicode(m_SlaveStation[afds][achan].WatchName,buf);
        		else if(col==1)
                      m_Str2Data.GB2312ToUnicode("1" ,buf);
         		else if(col==2)
				{
					  if(nstatus == 0)
						  strtime= m_SlaveStation[afds][achan].ZeroState;
					  else if(nstatus == 1)
						  strtime= m_SlaveStation[afds][achan].OneState;
					  else if(nstatus == 2)
						  strtime= m_SlaveStation[afds][achan].TwoState;
                      m_Str2Data.GB2312ToUnicode(strtime ,buf);
				}
         		else if(col==3)
				{
				  COleDateTime oleDateTime=m_Realtimedata.m_szrecdate;
				  strtime   =   oleDateTime.Format(_T("%Y-%m-%d %H:%M:%S")); 
                      m_Str2Data.GB2312ToUnicode(strtime,buf);
				}
         		else if(col==4)
				{
					o[iItem] =m_Realtimedata.m_szrecdate;
					if(iItem != 3)
					{
							cell = sheet->Cell(iItem-1, 4);
				         	COleDateTimeSpan t = o[iItem]-o[iItem-1];
			            	strtime.Format("%d %d:%d:%d",t.GetDays(),t.GetHours(),t.GetMinutes(),t.GetSeconds()); 
                            m_Str2Data.GB2312ToUnicode(strtime ,buf);
					}
				}
        		cell->Set(buf);
				}
	      		iItem++;
			}
			m_Realtimedata.MoveNext();
		}
	}
    delete [] buf;
	xls.SaveAs(gstrTimeOut +"\\report\\example.xls");
	copy_sheet(gstrTimeOut +"\\report\\example.xls",gstrTimeOut +"\\report\\sexample.xls");
	ShellExecute(0, NULL, gstrTimeOut +"\\report\\sexample.xls", NULL, NULL, SW_NORMAL);
}

void CMadeCertView::OnRECDRIVERE()   //设备故障记录
{
	CString strtime,strtime2;
	if(!m_Realtimedata1._IsEmpty())
	{
		m_Realtimedata1.MoveFirst();
		while ( !m_Realtimedata1.IsEOF() )
		{
				int afds = m_Realtimedata1.m_szfds;
				int achan = m_Realtimedata1.m_szchan;
			int m_alarm = m_Realtimedata1.m_szADStatus;
			if(m_alarm > 63)
			{
				if(m_ADRecord[afds][achan][0].duant == 0)
					m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].NTime =m_Realtimedata1.m_szrecdate;
				m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].BTime =m_Realtimedata1.m_szrecdate;

    			m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].strlocal = "ddd";

					strtime = m_Realtimedata1.m_szsafemtext;
					strtime.TrimRight();
					if(strtime != "")
					{
          				  COleDateTime t=m_Realtimedata1.m_szrecdate;
		        		  strtime2   =   t.Format(_T("%Y-%m-%d %H:%M:%S")); 
//	       	    		m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].RTime = m_Realtimedata1.m_szrecdate;
	       	    		m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].strsafetext += strtime+"|"+strtime2+"|";
					}
				m_ADRecord[afds][achan][0].duant++;//n个报警值
			}
			else if(m_alarm < 48)
			{
				if(m_ADRecord[afds][achan][0].duant> 0)
				{
	    			m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].BTime =m_Realtimedata1.m_szrecdate;
	     			m_ADRecord[afds][achan][0].m_ATotalnum++;  //总报警次数
	     			m_ADRecord[afds][achan][0].duant = 0;  //状态转变
				}
			}
			m_Realtimedata1.MoveNext();
		}
	}
	if(!m_Realtimedata._IsEmpty())
	{
		m_Realtimedata.MoveFirst();
		while ( !m_Realtimedata.IsEOF() )
		{
				int afds = m_Realtimedata.m_szfds;
				int achan = m_Realtimedata.m_szchan;
			int m_alarm = m_Realtimedata.m_szADStatus;
			if(m_alarm > 63)
			{
				if(m_ADRecord[afds][achan][0].duant == 0)
					m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].NTime =m_Realtimedata.m_szrecdate;
				m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].BTime =m_Realtimedata.m_szrecdate;

    			m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].strlocal = "ddd";

				strtime = m_Realtimedata.m_szsafemtext;
					strtime.TrimRight();
					if(strtime != "")
					{
          				  COleDateTime t=m_Realtimedata.m_szrecdate;
		        		  strtime2   =   t.Format(_T("%Y-%m-%d %H:%M:%S")); 
	       	    		m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].strsafetext += strtime+"|"+strtime2+"|";
					}
				m_ADRecord[afds][achan][0].duant++;//n个报警值
			}
			else if(m_alarm < 48)
			{
				if(m_ADRecord[afds][achan][0].duant> 0)
				{
	    			m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].BTime =m_Realtimedata.m_szrecdate;
	     			m_ADRecord[afds][achan][0].m_ATotalnum++;  //总报警次数
	     			m_ADRecord[afds][achan][0].duant = 0;  //状态转变
				}
			}
			m_Realtimedata.MoveNext();
		}
	}
	BasicExcel xls;
//	xls.Load(gstrTimeOut +"\\report\\example.xls");
	xls.New(1);
	BasicExcelWorksheet* sheet = xls.GetWorksheet((size_t)0);
	XLSFormatManager fmt_mgr(xls);

	 // Create a table containing an header row in bold and four rows below.
	ExcelFont font_bold;
	font_bold._weight = FW_BOLD; // 700
	CellFormat fmt_bold(fmt_mgr);
	fmt_bold.set_font(font_bold);

	CString strtime1;
		strtime.Format("(%d-%d-%d %d:00:00----",m_startDateTime.GetYear(),m_startDateTime.GetMonth(),m_startDateTime.GetDay(),m_ctrlStartH); 
		strtime1.Format("%d-%d-%d %d:59:59)",m_endDateTime.GetYear(),m_endDateTime.GetMonth(),m_endDateTime.GetDay(),m_ctrlEndH); 
		ExcelFont font;
//		font.set_color_index(color);
		font.set_weight(500);
		font.set_height(500);
		font.set_font_name(L"Times New Roman");
		CellFormat fmt(fmt_mgr, font);


    WCHAR * buf=new WCHAR[200];
		BasicExcelCell* cell = sheet->Cell(0, 2);
             m_Str2Data.GB2312ToUnicode("监控设备故障记录查询显示" ,buf);
		cell->Set(buf);
		cell->SetFormat(fmt);

        cell = sheet->Cell(1, 2);
		strtime += strtime1;
             m_Str2Data.GB2312ToUnicode(strtime ,buf);
		cell->Set(buf);
		cell->SetFormat(fmt_bold);

	size_t col = 0;
	for(col=0; col<6; col++) {
		BasicExcelCell* cell = sheet->Cell(2, col);
		if(col==0)
             m_Str2Data.GB2312ToUnicode("安装地点|名称",buf);
		else if(col==1)
             m_Str2Data.GB2312ToUnicode("累计次数",buf);
		else if(col==2)
             m_Str2Data.GB2312ToUnicode("累计时间",buf);
		else if(col==3)
             m_Str2Data.GB2312ToUnicode("起始时刻",buf);
		else if(col==4)
             m_Str2Data.GB2312ToUnicode("终止时刻",buf);
		else if(col==5)
             m_Str2Data.GB2312ToUnicode("安全措施|时刻",buf);
		cell->Set(buf);
		cell->SetFormat(fmt_bold);
	}
		int iItem = 3;
		for (int i = 1; i < 65;i++)
		{
			for(int j = 1; j < 25;j++ )
			{
     			for(int k = 0; k < 266;k++ )
				{
    				if(m_ADRecord[i][j][k].strlocal != "ddd")
						break;

					    for(col=0; col<6; col++) {
                		BasicExcelCell* cell = sheet->Cell(iItem, col);
                		if(col==0)
                             m_Str2Data.GB2312ToUnicode(m_SlaveStation[i][j].WatchName,buf);
                		else if(col==1)
                             m_Str2Data.GB2312ToUnicode("1" ,buf);
                		else if(col==2)
						{
							COleDateTime o =m_ADRecord[i][j][k].NTime;
							COleDateTime o1 =m_ADRecord[i][j][k].BTime;
				         	COleDateTimeSpan t = o1-o;
			            	strtime.Format("%d %d:%d:%d",t.GetDays(),t.GetHours(),t.GetMinutes(),t.GetSeconds()); 
                            m_Str2Data.GB2312ToUnicode(strtime ,buf);
						}
                 		else if(col==3)
						{
          				  COleDateTime oleDateTime=m_ADRecord[i][j][k].NTime;
		        		  strtime   =   oleDateTime.Format(_T("%Y-%m-%d %H:%M:%S")); 
                          m_Str2Data.GB2312ToUnicode(strtime,buf);
						}
                 		else if(col==4)
						{
          				  COleDateTime oleDateTime=m_ADRecord[i][j][k].BTime;
		        		  strtime   =   oleDateTime.Format(_T("%Y-%m-%d %H:%M:%S")); 
                          m_Str2Data.GB2312ToUnicode(strtime,buf);
						}
                 		else if(col==5)
                          m_Str2Data.GB2312ToUnicode(m_ADRecord[i][j][k].strsafetext,buf);

						cell->Set(buf);
						}
		            	iItem++;
				}//k
			}//j
		}//i
    delete [] buf;
	xls.SaveAs(gstrTimeOut +"\\report\\example.xls");
	copy_sheet(gstrTimeOut +"\\report\\example.xls",gstrTimeOut +"\\report\\sexample.xls");
	ShellExecute(0, NULL, gstrTimeOut +"\\report\\sexample.xls", NULL, NULL, SW_NORMAL);
}










void CMadeCertView::copy_sheet(const char* from, const char* to)
{
	BasicExcel xls;
	xls.Load(from);
	xls.SaveAs(to);
}

void CMadeCertView::OnButtonViewinfo() 
{
	// TODO: Add your control notification handler code here
	if(m_select==-1) return;
//	CViewInfoDlg dlg;
//	dlg.DoModal();

}

void CMadeCertView::OnButtonAutMade() 
{
	// TODO: Add your control notification handler code here
/*	if(m_select==-1) return;

	((CRaChildFrame*)GetParentFrame( ))->Msg("开始证书制作,请等待");
	CMadeCertDlg dlg;
	dlg.DoModal();
	m_List.DeleteItem(m_select);
	((CRaChildFrame*)GetParentFrame( ))->Msg("证书制作成功!");
	str[35]=3;
	m_select=-1;*/
	
}

void CMadeCertView::OnClickListMade(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
/*	m_select=m_List.GetSelectionMark();
	if(m_select==-1) return;
	m_List.SetItemState(m_select,LVIS_SELECTED,LVIS_SELECTED);
	m_List.SetFocus();
	m_num=m_List.GetItemText(m_select,0);//内部编号*/

//	*pResult = 0;
}

void CMadeCertView::OnDestroy() 
{
  try
  {
    if ( m_PointDes._IsOpen() )
      m_PointDes.Close();
    if ( m_Realtimedata._IsOpen() )
      m_Realtimedata.Close();
    if ( m_Realtimedata1._IsOpen() )
      m_Realtimedata1.Close();
	if ( m_Rt5mdata._IsOpen() )
	    m_Rt5mdata.Close();

    m_Cn.Close();
    //Cleanup the AxLib library
    dbAx::Term();
  }
  catch ( CAxException *e )
  {
    MessageBox(e->m_szErrorDesc, _T("BJygjl Message"), MB_OK);
    delete e;
  }

	CFormView::OnDestroy();
	((CMainFrame*)AfxGetMainWnd())->m_pMade=NULL; // 清空窗口指针
}

void CMadeCertView::OnChangeEditStarth() 
{
	UpdateData(TRUE);
//	m_strEditAddrHEX.Format("%02X",m_unEditAddrDEC);
	UpdateData(FALSE);
}

void CMadeCertView::OnChangeEditEndh() 
{
	UpdateData(TRUE);
	UpdateData(FALSE);
}

void CMadeCertView::OnDatetimestart(NMHDR* pNMHDR, LRESULT* pResult) 
{
	UpdateData(TRUE);
	m_ctrlStartTime.GetTime(m_startDateTime);
	UpdateData(FALSE);
	*pResult = 0;
}

void CMadeCertView::OnDatetimeend(NMHDR* pNMHDR, LRESULT* pResult) 
{
	UpdateData(TRUE);
	m_ctrlEndTime.GetTime(m_endDateTime);
	UpdateData(FALSE);
	*pResult = 0;
}

void CMadeCertView::OnchangeComboSM() 
{

}

int CMadeCertView::GetDayM(int monthM)
{
	int m_day;
	if(monthM == 2)
		m_day =28;
	else if(monthM == 4 && monthM == 6 && monthM == 8 && monthM == 11)
		m_day =30;
	else
		m_day =31;
	return m_day;
}
