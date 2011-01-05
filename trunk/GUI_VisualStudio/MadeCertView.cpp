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
#include "excel2003.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define BoolType(b) b?true:false

extern SerialF               m_SerialF[MAX_FDS];
extern ADCbreakE             m_CFeed[MAX_FDS][MAX_CHAN][65];
extern ADCbreakE             m_ADCbreakE[MAX_FDS][MAX_CHAN][65];
extern SlaveStation             m_SlaveStation[MAX_FDS][MAX_CHAN];
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
	CTimeSpan tpan(1,0,0,0);
	m_ctrlStartH = m_SerialF[0].SFSd;
	m_ctrlEndH = m_SerialF[0].SFSd-1;
	m_endDateTime = CTime::GetCurrentTime();
	if(m_ctrlStartH == 0)
   	{
    	m_endDateTime = CTime::GetCurrentTime()-tpan;
		m_ctrlEndH =23;
	}

	m_startDateTime = CTime::GetCurrentTime()-tpan;
	b_twodb = FALSE;
//	CString strna = m_startDateTime.Format(_T("%Y-%m-%d %H:%M:%S"));
//    		AfxMessageBox(strna);

//	m_bitMadeView.LoadBitmap(IDB_BITMAPVIEWMADE);
//	m_bitMadeViewUser.LoadBitmap(IDB_BITMAPVIEWUSER);
//	m_bitMadeCert.LoadBitmap(IDB_BITMAPMADECERT);
	//}}AFX_DATA_INIT
	m_bExcelInit=false;

	m_nSortedCol = 1;
	m_bAscending = true;
}

CMadeCertView::~CMadeCertView()
{
}

void CMadeCertView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMadeCertView)
	DDX_Text(pDX, IDC_E_START, m_ctrlStartH);
	DDV_MinMaxUInt(pDX, m_ctrlStartH, 0, 23);
	DDX_Text(pDX, IDC_E_END, m_ctrlEndH);
	DDV_MinMaxUInt(pDX, m_ctrlEndH, 0, 23);
	DDV_MinMaxUInt(pDX, m_ctrlStartH, 0, 23);
	DDV_MinMaxUInt(pDX, m_ctrlEndH, 0, 23);
	DDX_Control(pDX, IDC_R_START, m_ctrlStartTime);
	DDX_Control(pDX, IDC_R_END, m_ctrlEndTime);
	DDX_Control(pDX, IDC_COMBMADE, m_ComBoxSM);
	DDX_Control(pDX, IDC_LCEXCEL_1, m_LCEXCEL1);
	DDX_Control(pDX, IDC_LCEXCEL_2, m_LCEXCEL2);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMadeCertView, CFormView)
	//{{AFX_MSG_MAP(CMadeCertView)
//	ON_WM_SYSCOMMAND()
//	ON_WM_PAINT()
//	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOKSEARCH, OnBOKSEARCH)
	ON_CBN_SELCHANGE(IDC_COMBMADE, OnchangeComboSM)
//	ON_BN_CLICKED(IDC_BUTTON_VIEWINFO, OnButtonViewinfo)
//	ON_NOTIFY(NM_CLICK, IDC_LIST_MADE, OnClickListMade)
	ON_BN_CLICKED(IDC_BEXCELADD, OnBES)
	ON_BN_CLICKED(IDCANCELEXCEL, OnBED)
	ON_EN_CHANGE(IDC_E_START, OnChangeEditStarth)
	ON_EN_CHANGE(IDC_E_END, OnChangeEditEndh)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_R_START, OnDatetimestart)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_R_END, OnDatetimeend)
//	ON_NOTIFY(DTN_CLOSEUP, IDC_R_START, OnDatetimestart)
//	ON_NOTIFY(DTN_CLOSEUP, IDC_R_END, OnDatetimeend)
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
	CMainFrame* pFWnd=(CMainFrame*)AfxGetMainWnd();
   	pFWnd->m_MadeCert=this;

	::CoInitialize(NULL);
	CString strna[3];
	strna[0] = "��װ�ص�|����";
		strna[1] ="���";
		strna[2] ="PID";
		int m_widge[3];
		m_widge[0] =160;
		m_widge[1]=75;
		m_widge[2]=40;
	for(int i=0;i<3;i++)
	{
		m_LCEXCEL1.InsertColumn(i,strna[i],LVCFMT_LEFT,m_widge[i]);
		m_LCEXCEL2.InsertColumn(i,strna[i],LVCFMT_LEFT,m_widge[i]);
	}
	m_ctrlStartTime.SetTime(&m_startDateTime);
	m_ctrlEndTime.SetTime(&m_endDateTime);
	
//	((CComboBox *)GetDlgItem(IDC_COMBO1))->SetCurSel(0);
	// TODO: Add your specialized code here and/or call the base class
//	m_List.SetWindowPos(NULL,0,0,1024,400,SWP_NOMOVE|SWP_NOZORDER | SWP_NOACTIVATE);
    	GetDlgItem(IDC_COMBMADE)->ShowWindow(SW_HIDE);;

		m_widge[0] = 0 ;//all point
	if(theApp.strargc == "OnALARMS")
//       	GetParentFrame()->SetWindowText("������¼��ѯ");
		GetDocument()->SetTitle("������¼��ѯ");
	else if(theApp.strargc == "OnBREAKES")
		GetDocument()->SetTitle("�ϵ��¼��ѯ");
	else if(theApp.strargc == "OnFEEDES")
		GetDocument()->SetTitle("�����쳣��¼��ѯ");
	else if(theApp.strargc == "OnSELECTS")
		GetDocument()->SetTitle("���ò�ѯ");
	else if(theApp.strargc == "OnRECAAD")
	{
		m_widge[0] = 1 ;//A point
		GetDocument()->SetTitle("ģ����������¼��ѯ");
	}
	else if(theApp.strargc == "OnRECABD")
	{
		m_widge[0] = 1 ;//A point
		GetDocument()->SetTitle("ģ�����ϵ��¼��ѯ");
	}
	else if(theApp.strargc == "OnRECAFED")
	{
		m_widge[0] = 1 ;//A point
		GetDocument()->SetTitle("ģ���������쳣��¼��ѯ");
	}
	else if(theApp.strargc == "OnRECASR")
	{
		m_widge[0] = 1 ;//A point
		GetDocument()->SetTitle("ģ����ͳ��ֵ��¼��ѯ");
	}
	else if(theApp.strargc == "OnRECDABD")
	{
		m_widge[0] = 2 ;//D point
		GetDocument()->SetTitle("�����������ϵ��¼��ѯ");
	}
	else if(theApp.strargc == "OnRECDABB")
	{
		m_widge[0] = 2 ;//D point
		GetDocument()->SetTitle("�������ϵ��¼��ѯ");
	}
	else if(theApp.strargc == "OnRECDFED")
	{
		m_widge[0] = 2 ;//D point
		GetDocument()->SetTitle("�����������쳣��¼��ѯ");
	}
	else if(theApp.strargc == "OnRECDSCD")
	{
		m_widge[0] = 2 ;//D point
		GetDocument()->SetTitle("������״̬�䶯��¼��ѯ");
	}
	else if(theApp.strargc == "OnRECDRIVERE")
	{
		GetDocument()->SetTitle("����豸���ϼ�¼��ѯ");
	}

	else if(theApp.strargc == "OnEXCELA")
	{
		m_widge[0] = 1 ;//A point
		GetDocument()->SetTitle("ģ������(��)����");
	}
	else if(theApp.strargc == "OnEXCELAA")
	{
		m_widge[0] = 1 ;//A point
		GetDocument()->SetTitle("ģ����������(��)����");
	}
	else if(theApp.strargc == "OnEXCELAB")
	{
		m_widge[0] = 1 ;//A point
		GetDocument()->SetTitle("ģ�����ϵ���(��)����");
	}
	else if(theApp.strargc == "OnEXCELAFE")
	{
		m_widge[0] = 1 ;//A point
		GetDocument()->SetTitle("ģ���������쳣��(��)����");
	}
	else if(theApp.strargc == "OnEXCELASR")
	{
		m_widge[0] = 1 ;//A point
		GetDocument()->SetTitle("ģ����ͳ��ֵ��(��)����");
	}
	else if(theApp.strargc == "OnEXCELDA")
	{
		m_widge[0] = 2 ;//D point
		GetDocument()->SetTitle("������������(��)����");
	}
	else if(theApp.strargc == "OnEXCELDAB")
	{
		m_widge[0] = 2 ;//D point
		GetDocument()->SetTitle("�������ϵ���(��)����");
	}
	else if(theApp.strargc == "OnEXCELDFE")
	{
		m_widge[0] = 2 ;//D point
		GetDocument()->SetTitle("�����������쳣��(��)����");
	}
	else if(theApp.strargc == "OnEXCELDSCD")
	{
		m_widge[0] = 2 ;//D point
		GetDocument()->SetTitle("������״̬�䶯��(��)����");
	}
	else if(theApp.strargc == "OnEXCELDRIVERE")
	{
		GetDocument()->SetTitle("����豸������(��)����");
	}

       InitStr();
	CString strstartTime,strname,dddd;
    	int eYear;
		m_CommonSet.Create();
		m_CommonSet.CursorType(adOpenDynamic);
		m_CommonSet.CacheSize(50);
//		m_CommonSet._SetRecordsetEvents(new CAccountSetEvents);
		m_CommonSet.Open(_T("Select * From commonset"), &theApp.m_Cn);
		m_CommonSet.MarshalOptions(adMarshalModifiedOnly);
		int iItem = 0;
    	if(!m_CommonSet._IsEmpty())
		{
    		m_CommonSet.MoveFirst();
	     	while ( !m_CommonSet.IsEOF() )
			{
                 if(theApp.strargc == "OnALARMS")
	    	    		strstartTime = m_CommonSet.m_szstrc2;
              	else if(theApp.strargc == "OnBREAKES")
	    	    		strstartTime = m_CommonSet.m_szstrc3;
            	else if(theApp.strargc == "OnFEEDES")
	    	    		strstartTime = m_CommonSet.m_szstrc4;
            	else if(theApp.strargc == "OnSELECTS")
	    	    		strstartTime = m_CommonSet.m_szstrc5;
               	else if(theApp.strargc == "OnRECAAD")
	    	    		strstartTime = m_CommonSet.m_szstrc6;
            	else if(theApp.strargc == "OnRECABD")
	    	    		strstartTime = m_CommonSet.m_szstrc7;
            	else if(theApp.strargc == "OnRECAFED")
	    	    		strstartTime = m_CommonSet.m_szstrc8;
            	else if(theApp.strargc == "OnRECASR")
	    	    		strstartTime = m_CommonSet.m_szstrc9;
            	else if(theApp.strargc == "OnRECDABD")
	    	    		strstartTime = m_CommonSet.m_szstrc10;
            	else if(theApp.strargc == "OnRECDABB")
	    	    		strstartTime = m_CommonSet.m_szstrc11;
            	else if(theApp.strargc == "OnRECDFED")
	    	    		strstartTime = m_CommonSet.m_szstrc12;
            	else if(theApp.strargc == "OnRECDSCD")
	    	    		strstartTime = m_CommonSet.m_szstrc13;
            	else if(theApp.strargc == "OnRECDRIVERE")
	    	    		strstartTime = m_CommonSet.m_szstrc14;

            	else if(theApp.strargc == "OnEXCELA")
	    	    		strstartTime = m_CommonSet.m_szstrc15;
               	else if(theApp.strargc == "OnEXCELAA")
	    	    		strstartTime = m_CommonSet.m_szstrc16;
            	else if(theApp.strargc == "OnEXCELAB")
	    	    		strstartTime = m_CommonSet.m_szstrc17;
            	else if(theApp.strargc == "OnEXCELAFE")
	    	    		strstartTime = m_CommonSet.m_szstrc18;
            	else if(theApp.strargc == "OnEXCELASR")
	    	    		strstartTime = m_CommonSet.m_szstrc19;
            	else if(theApp.strargc == "OnEXCELDA")
	    	    		strstartTime = m_CommonSet.m_szstrc20;
            	else if(theApp.strargc == "OnEXCELDAB")
	    	    		strstartTime = m_CommonSet.m_szstrc21;
            	else if(theApp.strargc == "OnEXCELDFE")
	    	    		strstartTime = m_CommonSet.m_szstrc22;
            	else if(theApp.strargc == "OnEXCELDSCD")
	    	    		strstartTime = m_CommonSet.m_szstrc23;
            	else if(theApp.strargc == "OnEXCELDRIVERE")
	    	    		strstartTime = m_CommonSet.m_szstrc24;

    			 strstartTime.TrimRight();
				 if(strstartTime=="")
					 break;
				int m_cba =0;
				 eYear = m_Str2Data.String2Int(strstartTime);

        		for(int i = 1; i < MAX_FDS;i++ )
				{
	        		for(int j = 0; j < MAX_CHAN;j++ )
					{
		    			int n_cp= m_SlaveStation[i][j].m_PID;
	       				if(eYear == n_cp)
						{
					    	m_cba =100;
       				    	 break;
						}
					}
				}
				if(m_cba == 100)//have point
				{
					mPoint[eYear]=iItem;
    	        	m_Points.push_back(eYear);
    		        iItem++;
				}
	    		m_CommonSet.MoveNext();
			}
		}
             for ( i = 0 ; i < m_Points.size() ; i++ )
        		m_LCEXCEL2.InsertItem(i, "ddd");

		 iItem = 0;      BOOL B_is;
 		for( i = 1; i < MAX_FDS;i++ )
		{
			for(int j = 0; j < MAX_CHAN;j++ )
			{
				B_is =FALSE;
       			eYear = m_SlaveStation[i][j].ptype;
				if(m_widge[0] == 1 && eYear<3)
					B_is = TRUE;
				else if(m_widge[0] == 2 && eYear>9)
					B_is = TRUE;
				else if(m_widge[0] == 0)
					B_is = TRUE;

				int m_cba =0;
	    		if(B_is && m_SlaveStation[i][j].WatchName!="")
				{
					eYear = m_SlaveStation[i][j].m_PID;
    				dddd.Format("%d",eYear);
             		for (int k = 0 ; k < m_Points.size() ; k++ )
					{
		      			if(eYear == m_Points[k])
						{
    						m_cba =100;
      						break;
						}
					}
					if(m_cba == 100)
					{
            				m_LCEXCEL2.SetItemText(k, 0, m_SlaveStation[i][j].WatchName);
            				m_LCEXCEL2.SetItemText(k, 1, m_SlaveStation[i][j].strPN);
        	    			m_LCEXCEL2.SetItemText(k, 2, dddd);
					}
					else
					{
        				m_LCEXCEL1.InsertItem(iItem, m_SlaveStation[i][j].WatchName);
         				m_LCEXCEL1.SetItemText(iItem, 1, m_SlaveStation[i][j].strPN);
        				m_LCEXCEL1.SetItemText(iItem, 2, dddd);
    	    	        iItem++;
					}
				}//B_is && m_SlaveStation[i][j]
			}//for(int j
		}//for(int i
	HWND hWndHeader = m_LCEXCEL2.GetDlgItem(IDC_LCEXCEL_2)->GetSafeHwnd();
	m_header.SubclassWindow(hWndHeader);
	// enable auto sizing.
	m_header.EnableAutoSize(TRUE);
//	m_header.ResizeColumnsToFit();
	SortColumn(m_nSortedCol, m_bAscending);
	m_LCEXCEL1.ModifyExtendedStyle(0, LVS_EX_FULLROWSELECT|LVS_SHOWSELALWAYS | LVS_EX_GRIDLINES);
	m_LCEXCEL2.ModifyExtendedStyle(0, LVS_EX_FULLROWSELECT|LVS_SHOWSELALWAYS | LVS_EX_GRIDLINES);
//	m_LCEXCEL2.EnableUserSortColor(BoolType(m_bSortColor));
//	m_LCEXCEL2.EnableUserListColor(BoolType(m_bListColor));
//	m_LCEXCEL2.EnableUserRowColor(BoolType(m_bRowColor));
/*	if (::CoInitialize(NULL)!=0)   //EXCEL
	{ 
		AfxMessageBox("��ʼ��COM֧�ֿ�ʧ��,�޷����EXCEL����!");
		m_bExcelInit=false;
	} 
	else
		m_bExcelInit=true;*/
}

void CMadeCertView::OnBOKSEARCH() 
{
	UpdateData(TRUE);
	CMainFrame* pFWnd=(CMainFrame*)AfxGetMainWnd();
    pFWnd->m_ThreadPool.Add(new CThreadObject(*this, 5));
}

void CMadeCertView::OnTAuto() 
{
//       	GetParentFrame()->EnableWindow(FALSE);
  	GetDlgItem(IDOKSEARCH)->EnableWindow(FALSE);;
  	GetDlgItem(IDC_BEXCELADD)->EnableWindow(FALSE);;
  	GetDlgItem(IDCANCELEXCEL)->EnableWindow(FALSE);;

	CommonTools C_Ts;
	if(m_ctrlStartH >23)
		return;
	if(m_ctrlEndH >23)
		return;
	CString sztime,szConnect,szConnect1,strtime;
	int starty,endy;	unsigned char startm,endm;
	t = CTime(m_startDateTime.GetYear(),m_startDateTime.GetMonth(),m_startDateTime.GetDay(),m_ctrlStartH,0,0);
	t1 = CTime(m_endDateTime.GetYear(),m_endDateTime.GetMonth(),m_endDateTime.GetDay(),m_ctrlEndH,59,59);
					if((t1.GetTime()-t.GetTime())<0)
					{
						strtime = "����ʱ��Ӧ�ô�����ʼʱ��";
						AfxMessageBox(strtime);
						return;
					}
		if(theApp.strargc == "OnRECASR" ||theApp.strargc == "OnEXCELASR")
		{
					szConnect = "Select * From rt5mdata WHERE recdate>'";
 					  strtime = t.Format(_T("%Y-%m-%d %H:%M:%S")); 
					  sztime = t1.Format(_T("%Y-%m-%d %H:%M:%S")); 
      				  szConnect += strtime+"' and recdate<'" +sztime+"'";
		}
		else
		{
					theApp.m_RTDM.CalRtDB(t , starty , startm);
					theApp.m_RTDM.CalRtDB(t1 , endy , endm);
						strtime = "����ʱ������ʼʱ��Ӧ����������";
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
    					if(m_SerialF[0].SFSd >12)
						{
        					  strtime = t.Format(_T("%Y-%m-%d %H:%M:%S")); 
        					  sztime.Format("%d-%d-%d %d:59:59",starty,startm,C_Ts.GetDayM(starty,startm),m_SerialF[0].SFSd-1); 
            				  szConnect1 += strtime+"' and recdate<'" +sztime+"'";
        					  strtime.Format("%d-%d-%d %d:00:00",starty,startm,C_Ts.GetDayM(starty,startm),m_SerialF[0].SFSd); 
        					  sztime = t1.Format(_T("%Y-%m-%d %H:%M:%S")); 
            				  szConnect += strtime+"' and recdate<'" +sztime+"'";
						}
						else
						{
        					  strtime = t.Format(_T("%Y-%m-%d %H:%M:%S")); 
        					  sztime.Format("%d-%d-1 %d:59:59",endy,endm,m_SerialF[0].SFSd-1); 
            				  szConnect1 += strtime+"' and recdate<'" +sztime+"'";
        					  strtime.Format("%d-%d-1 %d:00:00",endy,endm,m_SerialF[0].SFSd); 
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
					sztime.Format(" and FeedStatus='�쳣'");
				else if(theApp.strargc == "OnRECAAD" ||theApp.strargc == "OnRECABD"||theApp.strargc == "OnRECAFED"
					||theApp.strargc == "OnEXCELA" ||theApp.strargc == "OnEXCELAA"||theApp.strargc == "OnEXCELAB"
					||theApp.strargc == "OnEXCELAFE")
					sztime.Format(" and ptype<3");
				else if(theApp.strargc == "OnRECDABD"||theApp.strargc == "OnRECDABB"||theApp.strargc == "OnRECDFED"||theApp.strargc == "OnRECDSCD"
					||theApp.strargc == "OnEXCELDA"||theApp.strargc == "OnEXCELDAB"||theApp.strargc == "OnEXCELDFE"||theApp.strargc == "OnEXCELDSCD")
					sztime.Format(" and ptype>3");
				else //if(theApp.strargc == "OnRECDRIVERE")
					sztime = "";

					if(endm != startm)   //������
    					szConnect1 += sztime;
					szConnect += sztime;

		if(theApp.strargc == "OnRECASR" ||theApp.strargc == "OnEXCELASR")
		{
						ADODBS(szConnect,0);
		}
		else
		{
					if(endm != startm)   //������
					{
						ADODBS(szConnect1,1);
					}
						ADODBS(szConnect,0);
		}
	if(theApp.strargc == "OnALARMS")
		OnSABFE();
	else if(theApp.strargc == "OnBREAKES")
		OnSABFE();
	else if(theApp.strargc == "OnFEEDES")
		OnSABFE();
	else if(theApp.strargc == "OnSELECTS")
		OnSABFE();
	else if(theApp.strargc == "OnRECAAD"||theApp.strargc == "OnEXCELAA")
		OnRECAAD();
	else if(theApp.strargc == "OnRECABD"||theApp.strargc == "OnEXCELAB")
		OnRECABD();
	else if(theApp.strargc == "OnRECAFED"||theApp.strargc == "OnEXCELAFE")
		OnRECAFED();
	else if(theApp.strargc == "OnRECASR"||theApp.strargc == "OnEXCELASR")
		OnRECASR();
	else if(theApp.strargc == "OnRECDABD"||theApp.strargc == "OnEXCELDA")
		OnRECDABD();
	else if(theApp.strargc == "OnRECDABB"||theApp.strargc == "OnEXCELDAB")
		OnRECDABB();
	else if(theApp.strargc == "OnRECDFED"||theApp.strargc == "OnEXCELDFE")
		OnRECDFED();
	else if(theApp.strargc == "OnRECDSCD"||theApp.strargc == "OnEXCELDSCD")
		OnRECDSCD();
	else if(theApp.strargc == "OnRECDRIVERE"||theApp.strargc == "OnEXCELDRIVERE")
		OnRECDRIVERE();
	else if(theApp.strargc == "OnEXCELA")
		OnEXCELA();

  	GetDlgItem(IDOKSEARCH)->EnableWindow(TRUE);;
  	GetDlgItem(IDC_BEXCELADD)->EnableWindow(TRUE);;
  	GetDlgItem(IDCANCELEXCEL)->EnableWindow(TRUE);;
 /*		((CRaChildFrame*)GetParentFrame( ))->Msg("��ʼ��ѯ���ݿ�");
		msg.Format("û�в�ѯ��������֤��,��ѯ����!");
	((CRaChildFrame*)GetParentFrame( ))->Msg(msg);*/
}

void CMadeCertView::OnSABFE() 
{
    CMainFrame* pFWnd=(CMainFrame*)AfxGetMainWnd();
	// initialize progress control.
	pFWnd->m_wndProgCtrl.SetRange (0, theApp.pRS->GetRecordCount());
	pFWnd->m_wndProgCtrl.SetPos (0);
	pFWnd->m_wndProgCtrl.SetStep (1);
	CString strcan,strtime;
	CString strDBr[16];
    	strtime = "TRUNCATE TABLE reported";
    	try{
    		theApp.m_pConnection->Execute(_bstr_t(strtime),NULL,adCmdText);  }
    	catch(_com_error e){
    		AfxMessageBox(e.ErrorMessage()); }

		while ( !theApp.pRS->EndOfFile)
		{
				int afds = theApp.pRS->Fields->Item["fds"]->Value.lVal;
				int achan = theApp.pRS->Fields->Item["chan"]->Value.lVal;
				int cv = theApp.pRS->Fields->Item["CDValue"]->Value.lVal;
				float av = theApp.pRS->Fields->Item["AValue"]->Value.fltVal;
         	    int nptype = m_SlaveStation[afds][achan].ptype;
    			int nstatus = theApp.pRS->Fields->Item["ADStatus"]->Value.lVal;
				COleDateTime dt(theApp.pRS->Fields->Item["recdate"]->Value);
				strDBr[0] =m_SlaveStation[afds][achan].WatchName+"|"+m_SlaveStation[afds][achan].strPN;
	            if(nptype ==1 || nptype ==0)
                	strDBr[1].Format("%.2f%s",av,m_SlaveStation[afds][achan].m_Unit);
         		else if(nptype ==2 )
            	  	  strDBr[1].Format("%.0f%s",av,m_SlaveStation[afds][achan].m_Unit);
        		else 
				{
								if(cv ==0)
				        		  strDBr[1]= m_SlaveStation[afds][achan].ZeroState;
			            		else if(cv == 1)
					        	  strDBr[1]= m_SlaveStation[afds][achan].OneState;
				         	    else if(cv == 2)
				          		  strDBr[1]= m_SlaveStation[afds][achan].TwoState;
				}
        		if((nstatus == 0x40)||(nstatus == 0x50)||(nstatus == 0x80)||(nstatus == 0x70)||(nstatus == 0x90)|| (nstatus == 0xa0) || (nstatus == 0xa1))
          		      strDBr[1]= theApp.m_RTDM.strstatus(nstatus);
				strDBr[2] = theApp.m_RTDM.strstatus(nstatus);
				strDBr[3] = dt.Format(_T("%Y-%m-%d %H:%M:%S"));

    	strtime.Format("INSERT INTO reported (R0,R1,R2,R3,R4,R5) VALUES('%s','%s','%s','%s','%s','%s')"
    		,strDBr[0],strDBr[1],strDBr[2],strDBr[3],strDBr[4],strDBr[5]);
     	theApp.m_pConnection->Execute(_bstr_t(strtime),NULL,adCmdText);
	    	pFWnd->m_wndProgCtrl.StepIt();
			theApp.pRS->MoveNext();
		}

	pFWnd->m_wndProgCtrl.SetPos (0);
    theApp.pRS->Close();

		strcan ="9,"+t.Format(_T("%Y-%m-%d,%H:%M:%S"))+","+t1.Format(_T("%Y-%m-%d,%H:%M:%S"));
	ShellExecute(0, "open", gstrTimeOut +"\\reportday.exe",m_Str2Data.CStringtocharp(strcan), 0, SW_NORMAL);
/*	CString sztime,strtime,stnames;
	if(theApp.strargc == "OnALARMS")
       	stnames= "������ѯ";
	else if(theApp.strargc == "OnBREAKES")
      	stnames= "�ϵ��ѯ";
	else if(theApp.strargc == "OnFEEDES")
       	stnames= "�����쳣��ѯ";
	else if(theApp.strargc == "OnSELECTS")
    	stnames= "���ò�ѯ";
*/
/*
	for(size_t row=0; row<8; ++row) {
		int color = 2;
//		int color = i++;
		int height = 100 * i;

		sprintf(buffer, "���� New Roman %d", height/20);

        WCHAR * buf=new WCHAR[1000];
        m_Str2Data.GB2312ToUnicode("�ͻ���     New Roman",buf);

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
 GB2312ToUnicode("�ͻ���",buf);
 cell->Set(buf);
 cell->SetFormat(fmt_bold);
 
    cell = sheet->Cell(0, 1);
    GB2312ToUnicode("������",buf);
    cell->Set(buf);
    cell->SetFormat(fmt_bold);
//  xls.SaveAs(path);
*/
//	xls.Save();
}
//ģ����������¼  
void CMadeCertView::OnRECAAD() 
{
    CMainFrame* pFWnd=(CMainFrame*)AfxGetMainWnd();
	// initialize progress control.
	pFWnd->m_wndProgCtrl.SetRange (0, 3840);
	pFWnd->m_wndProgCtrl.SetPos (0);
	pFWnd->m_wndProgCtrl.SetStep (1);

		for(int i = 1; i < MAX_FDS;i++ )
			for(int j = 1; j < MAX_CHAN;j++ )
			{
				for(int h = 0; h < 300;h++)
				{
					m_ADRecord[i][j][h].m_ATotalnum = 0;
					m_ADRecord[i][j][h].ATotalV = 0;
					m_ADRecord[i][j][h].duant = 0;
					m_ADRecord[i][j][h].strlocal = "";
					m_ADRecord[i][j][h].havev = 0;
					m_ADRecord[i][j][h].tmid = 0;
					m_ADRecord[i][j][h].AavV = 0;
					m_ADRecord[i][j][h].strsafetext = "";
					m_ADRecord[i][j][h].AMaxValue = 0;
					m_ADRecord[i][j][h].AMinValue = 666666;
				}
	    	pFWnd->m_wndProgCtrl.StepIt();
			}
	CString strtime,strtime2;
	if(b_twodb)
	{
		while ( !pRS1->EndOfFile)
		{
				int afds = pRS1->Fields->Item["fds"]->Value.lVal;
				int achan = pRS1->Fields->Item["chan"]->Value.lVal;
    			int m_alarm = pRS1->Fields->Item["ADStatus"]->Value.lVal;
				float s_curd = pRS1->Fields->Item["AValue"]->Value.fltVal;
				COleDateTime dt(pRS1->Fields->Item["recdate"]->Value);
	   		int dbp = mPoint[pRS1->Fields->Item["PID"]->Value.lVal];
             if(dbp != 6666)
			 {
			if(m_alarm == 16)
			{
				if(m_ADRecord[afds][achan][1].m_ATotalnum == 0)//��һ�α���ʱ��
					m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].BTime =dt;
//				m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].BTime =m_Realtimedata1.m_szrecdate;
				//����ģ����ͳ�ƴ���  ͳ��ֵ   ƽ��ֵ(���ջ򱾰౨���ڼ�ƽ��ֵ)
			    	m_ADRecord[afds][achan][299].m_ATotalnum++;
			    	m_ADRecord[afds][achan][299].AavV +=s_curd;
					//���ֵ��ʱ��(���ջ򱾰౨���ڼ����ֵ)
				if(m_ADRecord[afds][achan][299].AMaxValue <s_curd)
				{//�������ֵ��ʱ��   m_ADRecord[afds][achan][0].m_ATotalnum ����
    				m_ADRecord[afds][achan][299].AMaxValue = s_curd;
		    		m_ADRecord[afds][achan][299].ATime = dt;
				}

					//ÿ�α����ڼ�ƽ��ֵ�����ֵ��ʱ��
			    	m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].duant++;
			    	m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].AavV +=s_curd;
				if(m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].AMaxValue <s_curd)
				{//ÿ�����ֵ��ʱ��   m_ADRecord[afds][achan][0].m_ATotalnum ����
    				m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].AMaxValue = s_curd;
		    		m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].AMaxTime = dt;
				}
//				m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].strlocal="ddd";
   				_bstr_t Explain =pRS1->Fields->Item["safemtext"]->Value;
				strtime.Format("%s",(char *)Explain);
					strtime.TrimRight();
					if(strtime != "")
					{//ÿ�δ�ʩ����ȡ��ʩʱ��
		        		  strtime2   =   dt.Format(_T("%Y-%m-%d %H:%M:%S")); 
//	       	    		m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].RTime = m_Realtimedata1.m_szrecdate;
	       	    		m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].strsafetext += strtime+"|"+strtime2+"|";
					}
				m_ADRecord[afds][achan][1].m_ATotalnum++;//n������ֵ
			}
			else if(m_alarm != 16)
			{
				if(m_ADRecord[afds][achan][1].m_ATotalnum> 0)
				{//����ʱ�� ������1 �´γ�ʼ��  ÿ�α���ʱ��
	    			m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].NTime =dt;
					m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].tmid =dt-m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].BTime;
					//�ۼƱ���ʱ��(���ջ򱾰��ۼƱ���ʱ��)
					m_ADRecord[afds][achan][299].tmid +=m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].tmid;
					//��������(���ջ򱾰��ۼƱ�������)
	     			m_ADRecord[afds][achan][0].m_ATotalnum++;  //�ܱ�������
	     			m_ADRecord[afds][achan][1].m_ATotalnum = 0;  //״̬ת��
				}
			}
			 }
            	m_ADRecord[afds][achan][0].ATime = dt;
			pRS1->MoveNext();
		}
	}
//	if(!m_Realtimedata._IsEmpty())
	{
		while ( !theApp.pRS->EndOfFile)
		{
				int afds = theApp.pRS->Fields->Item["fds"]->Value.lVal;
				int achan = theApp.pRS->Fields->Item["chan"]->Value.lVal;
    			int m_alarm = theApp.pRS->Fields->Item["ADStatus"]->Value.lVal;
			float s_curd = theApp.pRS->Fields->Item["AValue"]->Value.fltVal;
			COleDateTime dt(theApp.pRS->Fields->Item["recdate"]->Value);
	   		int dbp = mPoint[theApp.pRS->Fields->Item["PID"]->Value.lVal];
             if(dbp != 6666)
			 {
			if(m_alarm == 16)
			{
				if(m_ADRecord[afds][achan][1].m_ATotalnum == 0)
					m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].BTime =dt;
//				m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].BTime =m_Realtimedata.m_szrecdate;
				//����ģ����ͳ�ƴ���  ͳ��ֵ   ƽ��ֵ(���ջ򱾰౨���ڼ�ƽ��ֵ)
			    	m_ADRecord[afds][achan][299].m_ATotalnum++;
			    	m_ADRecord[afds][achan][299].AavV +=s_curd;
					//���ֵ��ʱ��(���ջ򱾰౨���ڼ����ֵ)
				if(m_ADRecord[afds][achan][299].AMaxValue <s_curd)
				{//�������ֵ��ʱ��   m_ADRecord[afds][achan][0].m_ATotalnum ����
    				m_ADRecord[afds][achan][299].AMaxValue = s_curd;
		    		m_ADRecord[afds][achan][299].ATime = dt;
				}

					//ÿ�α����ڼ�ƽ��ֵ�����ֵ��ʱ��
			    	m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].duant++;
			    	m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].AavV +=s_curd;
				if(m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].AMaxValue <s_curd)
				{
    				m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].AMaxValue = s_curd;
		    		m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].AMaxTime = dt;
				}
//				m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].strlocal="ddd";
            	_bstr_t Explain =theApp.pRS->Fields->Item["safemtext"]->Value;
				strtime.Format("%s",(char *)Explain);
					strtime.TrimRight();
					if(strtime != "")
					{
		        		  strtime2   =   dt.Format(_T("%Y-%m-%d %H:%M:%S")); 
	       	    		m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].strsafetext += strtime+"|"+strtime2+"|";
					}
				m_ADRecord[afds][achan][1].m_ATotalnum++;//n������ֵ
			}
			else if(m_alarm != 16)
			{
				if(m_ADRecord[afds][achan][1].m_ATotalnum> 0)//�б���
				{
	    			m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].NTime =dt;
					m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].tmid =dt-m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].BTime;
					//�ۼƱ���ʱ��(���ջ򱾰��ۼƱ���ʱ��)
					m_ADRecord[afds][achan][299].tmid +=m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].tmid;
					//��������(���ջ򱾰��ۼƱ�������)
	     			m_ADRecord[afds][achan][0].m_ATotalnum++;  //�ܱ�������
	     			m_ADRecord[afds][achan][1].m_ATotalnum = 0;  //״̬ת��
				}
			}
			 }
            	m_ADRecord[afds][achan][0].ATime = dt;
			theApp.pRS->MoveNext();
		}
	}
		for( i = 1; i < MAX_FDS;i++ )
			for(int j = 1; j < MAX_CHAN;j++ )
			{
				if(m_ADRecord[i][j][1].m_ATotalnum> 0)//�б���
				{
	    			m_ADRecord[i][j][m_ADRecord[i][j][0].m_ATotalnum].NTime =m_ADRecord[i][j][0].ATime;
					m_ADRecord[i][j][m_ADRecord[i][j][0].m_ATotalnum].tmid =m_ADRecord[i][j][0].ATime-m_ADRecord[i][j][m_ADRecord[i][j][0].m_ATotalnum].BTime;
					//�ۼƱ���ʱ��(���ջ򱾰��ۼƱ���ʱ��)
					m_ADRecord[i][j][299].tmid +=m_ADRecord[i][j][m_ADRecord[i][j][0].m_ATotalnum].tmid;
					//��������(���ջ򱾰��ۼƱ�������)
	     			m_ADRecord[i][j][0].m_ATotalnum++;  //�ܱ�������
	     			m_ADRecord[i][j][1].m_ATotalnum = 0;  //״̬ת��
				}
	    	pFWnd->m_wndProgCtrl.StepIt();
			}
    if (b_twodb)
	{
		b_twodb = FALSE;
      	pRS1->Close();
	}
    theApp.pRS->Close();

	CString strtime1,strtime3,strtime4,stnames,strcan;
		strcan ="2,"+t.Format(_T("%Y-%m-%d,%H:%M:%S"))+","+t1.Format(_T("%Y-%m-%d,%H:%M:%S"));
		strtime = "��ʼ����:"+t.Format(_T("%Y-%m-%d %H:%M:%S")); 
		strtime1 = "��ֹ����:"+ t1.Format(_T("%Y-%m-%d %H:%M:%S")); 
		int m_hours = (t1.GetTime()-t.GetTime()+1)/3600;
		strtime2.Format("%d",m_hours); 
		strtime2 = "ʱ����:" +strtime2+"Сʱ";
		strtime3 = "��ӡʱ��:" + CTime::GetCurrentTime().Format(_T("%Y-%m-%d %H:%M:%S"));
		if(m_hours >20)
	     	strtime4 = t1.Format(_T("%Y-%m-%d"))+"�ձ���:";
		else
	     	strtime4 = t1.Format(_T("%Y-%m-%d"))+ "�౨��:";

		if(theApp.strargc == "OnEXCELAA")
		{
			if(m_hours >20)
				stnames = "ģ���������ձ���";
			else
				stnames = "ģ���������౨��";
		}
		else
				stnames = "ģ����������¼��ѯ��ʾ";
		strtime += "    "+strtime1+"    "+strtime2;
		//��Deleteɾ����ʽ��ǳ���  ����˸����ݱ�����������־ Drop   table   testɾ����
		//delete   *   from   ����    delete   ����
    	strtime = "TRUNCATE TABLE reportaad";
    	try{
    		theApp.m_pConnection->Execute(_bstr_t(strtime),NULL,adCmdText);  }
    	catch(_com_error e){
    		AfxMessageBox(e.ErrorMessage()); }
	CString strDBr[16];
	CTime t = CTime::GetCurrentTime();
	int t_curse = t.GetTime();
	size_t col = 0;
		int iItem = 3;
		for ( i = 1; i < MAX_FDS;i++)
		{
			for(int j = 1; j < 17;j++ )
			{
     			for(int k = 0; k < 300;k++ )
				{
    				if(m_ADRecord[i][j][k].duant==0)
						break;
                       	for(col=0; col<11; col++) {
							strtime ="";
//                		BasicExcelCell* cell = sheet->Cell(iItem, col);
                		if(col==0)
							strtime =m_SlaveStation[i][j].WatchName+"|"+m_SlaveStation[i][j].strPN;
//                             m_Str2Data.GB2312ToUnicode(m_SlaveStation[i][j].WatchName,buf);
                		else if(col==1)
							strtime =m_SlaveStation[i][j].m_Unit;
                		else if(col==2)
				        	  strtime.Format("%.2f",m_SlaveStation[i][j].AlarmValueH);
                		else if(col==3)
							//��������(���ջ򱾰��ۼƱ�������)
				        	  strtime.Format("%d",m_ADRecord[i][j][0].m_ATotalnum);
//							strtime ="1";
//                             m_Str2Data.GB2312ToUnicode("1" ,buf);
                		else if(col==4)
						{//�ۼƱ���ʱ��(���ջ򱾰��ۼƱ���ʱ��)
							COleDateTimeSpan t = m_ADRecord[i][j][299].tmid;
			            	strtime.Format("%d %d:%d:%d",t.GetDays(),t.GetHours(),t.GetMinutes(),t.GetSeconds()); 
//                            m_Str2Data.GB2312ToUnicode(strtime ,buf);
						}
                 		else if(col==5)
						{//���ֵ��ʱ��(���ջ򱾰౨���ڼ����ֵ)
				    	  strtime.Format("%.2f|",m_ADRecord[i][j][299].AMaxValue);
						  strtime = strtime +m_ADRecord[i][j][299].ATime.Format(_T("%Y:%m:%d %H:%M:%S")); 
//                          m_Str2Data.GB2312ToUnicode(strtime,buf);
						}
                 		else if(col==6)
						{//ƽ��ֵ(���ջ򱾰౨���ڼ�ƽ��ֵ);
				    	  strtime.Format("%.2f",m_ADRecord[i][j][299].AavV/m_ADRecord[i][j][299].m_ATotalnum);
//                          m_Str2Data.GB2312ToUnicode(strtime,buf);
						}
                 		else if(col==7)
						{//ÿ�α���ʱ�̼��������ʱ��
		        		  strtime =m_ADRecord[i][j][k].BTime.Format(_T("%Y:%m:%d %H:%M:%S")) +"|"+ m_ADRecord[i][j][k].NTime.Format(_T("%Y:%m:%d %H:%M:%S")) ; 
//                          m_Str2Data.GB2312ToUnicode(strtime,buf);
						}
                 		else if(col==8)
						{//ÿ�α���ʱ��
							COleDateTimeSpan t = m_ADRecord[i][j][k].tmid;
			            	strtime.Format("%d %d:%d:%d",t.GetDays(),t.GetHours(),t.GetMinutes(),t.GetSeconds()); 
//                          m_Str2Data.GB2312ToUnicode(strtime,buf);
						}
                		else if(col==9)
						{//ÿ�α����ڼ�ƽ��ֵ�����ֵ��ʱ��
				    	  strtime.Format("%.2f|%.2f|",m_ADRecord[i][j][k].AavV/m_ADRecord[i][j][k].duant,m_ADRecord[i][j][k].AMaxValue);
							strtime =strtime + m_ADRecord[i][j][k].AMaxTime.Format(_T("%Y:%m:%d %H:%M:%S"));
//                          m_Str2Data.GB2312ToUnicode(m_ADRecord[i][j][k].strsafetext,buf);
						}
                		else if(col==10)
						{//ÿ�δ�ʩ����ȡ��ʩʱ��
							strtime =m_ADRecord[i][j][k].strsafetext;
//                          m_Str2Data.GB2312ToUnicode(m_ADRecord[i][j][k].strsafetext,buf);
						}
//					rgMyRge.SetItem(_variant_t((long)iItem),_variant_t((long)(col+1)),_variant_t(strtime)); 
                        strDBr[col]=strtime;
						}
    	strtime.Format("INSERT INTO reportaad (R0,R1,R2,R3,R4,R5,R6,R7,R8,R9,R10) VALUES('%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s')"
    		,strDBr[0],strDBr[1],strDBr[2],strDBr[3],strDBr[4],strDBr[5],strDBr[6],strDBr[7],strDBr[8],strDBr[9],strDBr[10]);
     	theApp.m_pConnection->Execute(_bstr_t(strtime),NULL,adCmdText);
		            	iItem++;
				}//k
	    	pFWnd->m_wndProgCtrl.StepIt();
			}//j
		}//i
	pFWnd->m_wndProgCtrl.SetPos (0);
	ShellExecute(0, "open", gstrTimeOut +"\\reportday.exe",m_Str2Data.CStringtocharp(strcan), 0, SW_NORMAL);
//	theApp.C_Ts.CreateP(gstrTimeOut +"\\reportday.exe", m_Str2Data.CStringtocharp(strcan),5,0x00000001);
}

void CMadeCertView::OnRECABD() 
{
    CMainFrame* pFWnd=(CMainFrame*)AfxGetMainWnd();
	// initialize progress control.
	pFWnd->m_wndProgCtrl.SetRange (0, 3840);
	pFWnd->m_wndProgCtrl.SetPos (0);
	pFWnd->m_wndProgCtrl.SetStep (1);

	  for(int i = 1; i < MAX_FDS;i++ )
			for(int j = 1; j < MAX_CHAN;j++ )
			{
				for(int h = 0; h < 300;h++)
				{
					m_ADRecord[i][j][h].m_ATotalnum = 0;
					m_ADRecord[i][j][h].ATotalV = 0;
					m_ADRecord[i][j][h].duant = 0;
					m_ADRecord[i][j][h].strlocal = "";
					m_ADRecord[i][j][h].havev = 0;
					m_ADRecord[i][j][h].tmid = 0;
					m_ADRecord[i][j][h].AavV = 0;
					m_ADRecord[i][j][h].strsafetext = "";
					m_ADRecord[i][j][h].AMaxValue = 0;
					m_ADRecord[i][j][h].AMinValue = 666666;
				}
	    	pFWnd->m_wndProgCtrl.StepIt();
			}
	CString strtime,strtime2;
	if(b_twodb)
	{
		while ( !pRS1->EndOfFile)
		{
				int afds = pRS1->Fields->Item["fds"]->Value.lVal;
				int achan = pRS1->Fields->Item["chan"]->Value.lVal;
				int ffds = pRS1->Fields->Item["ffds"]->Value.lVal;
				int fchan = pRS1->Fields->Item["fchan"]->Value.lVal;
    			int m_alarm = pRS1->Fields->Item["ADStatus"]->Value.lVal;
				float s_curd = pRS1->Fields->Item["AValue"]->Value.fltVal;
				COleDateTime dt(pRS1->Fields->Item["recdate"]->Value);
   		int dbp = mPoint[pRS1->Fields->Item["PID"]->Value.lVal];
             if(dbp != 6666)
			 {
			if(m_alarm == 32)
			{
				if(m_ADRecord[afds][achan][1].m_ATotalnum == 0)//��һ�ζϵ�ʱ��
					m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].BTime =dt;
//				m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].BTime =m_Realtimedata1.m_szrecdate;
				//�ϵ�ģ����ͳ�ƴ���  ͳ��ֵ   ƽ��ֵ(���ջ򱾰�ϵ��ڼ�ƽ��ֵ)
			    	m_ADRecord[afds][achan][299].m_ATotalnum++;
			    	m_ADRecord[afds][achan][299].AavV +=s_curd;
					//���ֵ��ʱ��(���ջ򱾰�ϵ��ڼ����ֵ)
				if(m_ADRecord[afds][achan][299].AMaxValue <s_curd)
				{//�������ֵ��ʱ��   m_ADRecord[afds][achan][0].m_ATotalnum ����
    				m_ADRecord[afds][achan][299].AMaxValue = s_curd;
		    		m_ADRecord[afds][achan][299].ATime = dt;
				}

					//ÿ�ζϵ��ڼ�ƽ��ֵ�����ֵ��ʱ��
			    	m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].duant++;
			    	m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].AavV +=s_curd;
				if(m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].AMaxValue <s_curd)
				{//ÿ�����ֵ��ʱ��   m_ADRecord[afds][achan][0].m_ATotalnum ����
    				m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].AMaxValue = s_curd;
		    		m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].AMaxTime = dt;
				}
            	_bstr_t Explain =pRS1->Fields->Item["safemtext"]->Value;
				strtime.Format("%s",(char *)Explain);
					strtime.TrimRight();
					if(strtime != "")
					{//ÿ�δ�ʩ����ȡ��ʩʱ��
		        		  strtime2   =   dt.Format(_T("%Y-%m-%d %H:%M:%S")); 
//	       	    		m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].RTime = m_Realtimedata1.m_szrecdate;
	       	    		m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].strsafetext += strtime+"|"+strtime2+"|";
					}
            	 Explain =pRS1->Fields->Item["FeedStatus"]->Value;
				strtime.Format("%s",(char *)Explain);
					strtime.TrimRight();
					if(strtime != "")
					{//����״̬����ʱ�̡��ۼ�ʱ��
		        		  strtime2   =   dt.Format(_T("%Y-%m-%d %H:%M:%S")); 
//	       	    		m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].RTime = m_Realtimedata1.m_szrecdate;
	       	    		m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].strlocal += m_SlaveStation[ffds][fchan].WatchName +"|"+ m_SlaveStation[ffds][fchan].strPN +"|"+ strtime+"|"+strtime2+"|";
					}
				m_ADRecord[afds][achan][1].m_ATotalnum++;//n���ϵ�ֵ
			}
			else if(m_alarm != 32)
			{
				if(m_ADRecord[afds][achan][1].m_ATotalnum> 0)
				{//����ʱ�� ������1 �´γ�ʼ��  ÿ�ζϵ�ʱ��
	    			m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].NTime =dt;
					m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].tmid =dt-m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].BTime;
					//�ۼƶϵ�ʱ��(���ջ򱾰��ۼƶϵ�ʱ��)
					m_ADRecord[afds][achan][299].tmid +=m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].tmid;
		        	strtime2   =   dt.Format(_T("%Y-%m-%d %H:%M:%S")); 
	       	    	m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].strlocal += strtime2;
					//�ϵ����(���ջ򱾰��ۼƶϵ����)
	     			m_ADRecord[afds][achan][0].m_ATotalnum++;  //�ܶϵ����
	     			m_ADRecord[afds][achan][1].m_ATotalnum = 0;  //״̬ת��
				}
			}
			 }
            	m_ADRecord[afds][achan][0].ATime = dt;
			pRS1->MoveNext();
		}
	}
//	if(!m_Realtimedata._IsEmpty())
	{
//		m_Realtimedata.MoveFirst();
		while ( !theApp.pRS->EndOfFile)
		{
				int afds = theApp.pRS->Fields->Item["fds"]->Value.lVal;
				int achan = theApp.pRS->Fields->Item["chan"]->Value.lVal;
				int ffds = theApp.pRS->Fields->Item["ffds"]->Value.lVal;
				int fchan = theApp.pRS->Fields->Item["fchan"]->Value.lVal;
    			int m_alarm = theApp.pRS->Fields->Item["ADStatus"]->Value.lVal;
				float s_curd = theApp.pRS->Fields->Item["AValue"]->Value.fltVal;
			COleDateTime dt(theApp.pRS->Fields->Item["recdate"]->Value);
	   		int dbp = mPoint[theApp.pRS->Fields->Item["PID"]->Value.lVal];
             if(dbp != 6666)
			 {
			if(m_alarm == 32)
			{
				if(m_ADRecord[afds][achan][1].m_ATotalnum == 0)
					m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].BTime =dt;
//				m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].BTime =m_Realtimedata.m_szrecdate;
				//�ϵ�ģ����ͳ�ƴ���  ͳ��ֵ   ƽ��ֵ(���ջ򱾰�ϵ��ڼ�ƽ��ֵ)
			    	m_ADRecord[afds][achan][299].m_ATotalnum++;
			    	m_ADRecord[afds][achan][299].AavV +=s_curd;
					//���ֵ��ʱ��(���ջ򱾰�ϵ��ڼ����ֵ)
				if(m_ADRecord[afds][achan][299].AMaxValue <s_curd)
				{//�������ֵ��ʱ��   m_ADRecord[afds][achan][0].m_ATotalnum ����
    				m_ADRecord[afds][achan][299].AMaxValue = s_curd;
		    		m_ADRecord[afds][achan][299].ATime = dt;
				}
					//ÿ�ζϵ��ڼ�ƽ��ֵ�����ֵ��ʱ��
			    	m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].duant++;
			    	m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].AavV +=s_curd;
				if(m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].AMaxValue <s_curd)
				{
    				m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].AMaxValue = s_curd;
		    		m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].AMaxTime = dt;
				}
            	_bstr_t Explain =theApp.pRS->Fields->Item["safemtext"]->Value;
				strtime.Format("%s",(char *)Explain);
					strtime.TrimRight();
					if(strtime != "")
					{
		        		  strtime2   =   dt.Format(_T("%Y-%m-%d %H:%M:%S")); 
	       	    		m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].strsafetext += strtime+"|"+strtime2+"|";
					}
            	 Explain =theApp.pRS->Fields->Item["FeedStatus"]->Value;
				strtime.Format("%s",(char *)Explain);
					strtime.TrimRight();
					if(strtime != "")
					{//����״̬����ʱ�̡��ۼ�ʱ��
		        		  strtime2   =   dt.Format(_T("%Y-%m-%d %H:%M:%S")); 
	       	    		m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].strlocal += m_SlaveStation[ffds][fchan].WatchName +"|"+ m_SlaveStation[ffds][fchan].strPN +"|"+ strtime+"|"+strtime2+"|";
					}
				m_ADRecord[afds][achan][1].m_ATotalnum++;//n���ϵ�ֵ
			}
			else if(m_alarm != 32)
			{
				if(m_ADRecord[afds][achan][1].m_ATotalnum> 0)//�жϵ�
				{
	    			m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].NTime =dt;
					m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].tmid =dt-m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].BTime;
					//�ۼƶϵ�ʱ��(���ջ򱾰��ۼƶϵ�ʱ��)
					m_ADRecord[afds][achan][299].tmid +=m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].tmid;
		        	strtime2   =   dt.Format(_T("%Y-%m-%d %H:%M:%S")); 
	       	    	m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].strlocal += strtime2;
					//�ϵ����(���ջ򱾰��ۼƶϵ����)
	     			m_ADRecord[afds][achan][0].m_ATotalnum++;  //�ܶϵ����
	     			m_ADRecord[afds][achan][1].m_ATotalnum = 0;  //״̬ת��
				}
			}
			 }
            	m_ADRecord[afds][achan][0].ATime = dt;
			theApp.pRS->MoveNext();
		}
	}

		for( i = 1; i < MAX_FDS;i++ )
			for(int j = 1; j < MAX_CHAN;j++ )
			{
				if(m_ADRecord[i][j][1].m_ATotalnum> 0)//�жϵ�
				{
	    			m_ADRecord[i][j][m_ADRecord[i][j][0].m_ATotalnum].NTime =m_ADRecord[i][j][0].ATime;
					m_ADRecord[i][j][m_ADRecord[i][j][0].m_ATotalnum].tmid =m_ADRecord[i][j][0].ATime-m_ADRecord[i][j][m_ADRecord[i][j][0].m_ATotalnum].BTime;
					//�ۼƶϵ�ʱ��(���ջ򱾰��ۼƶϵ�ʱ��)
					m_ADRecord[i][j][299].tmid +=m_ADRecord[i][j][m_ADRecord[i][j][0].m_ATotalnum].tmid;
					//�ϵ����(���ջ򱾰��ۼƱ�������)
	     			m_ADRecord[i][j][0].m_ATotalnum++;  //�ܶϵ����
	     			m_ADRecord[i][j][1].m_ATotalnum = 0;  //״̬ת��
				}
	    	pFWnd->m_wndProgCtrl.StepIt();
			}
    if (b_twodb)
	{
		b_twodb = FALSE;
      	pRS1->Close();
	}
    theApp.pRS->Close();

	CString strtime1,strtime3,strtime4,stnames,strcan;
		strcan ="3,"+t.Format(_T("%Y-%m-%d,%H:%M:%S"))+","+t1.Format(_T("%Y-%m-%d,%H:%M:%S"));
		strtime = "��ʼ����:"+t.Format(_T("%Y-%m-%d %H:%M:%S")); 
		strtime1 = "��ֹ����:"+ t1.Format(_T("%Y-%m-%d %H:%M:%S")); 
		int m_hours = (t1.GetTime()-t.GetTime()+1)/3600;
		strtime2.Format("%d",m_hours); 
		strtime2 = "ʱ����:" +strtime2+"Сʱ";
		strtime3 = "��ӡʱ��:" + CTime::GetCurrentTime().Format(_T("%Y-%m-%d %H:%M:%S"));
		if(m_hours >20)
	     	strtime4 = t1.Format(_T("%Y-%m-%d"))+"�ձ���:";
		else
	     	strtime4 = t1.Format(_T("%Y-%m-%d"))+ "�౨��:";

		if(theApp.strargc == "OnEXCELAB")
		{
			if(m_hours >20)
				stnames = "ģ�����ϵ��ձ���";
			else
				stnames = "ģ�����ϵ�౨��";
		}
		else
				stnames = "ģ�����ϵ��¼��ѯ��ʾ";

		strtime += "    "+strtime1+"    "+strtime2;
    	strtime = "TRUNCATE TABLE reportabd";
    	try{
    		theApp.m_pConnection->Execute(_bstr_t(strtime),NULL,adCmdText);  }
    	catch(_com_error e){
    		AfxMessageBox(e.ErrorMessage()); }
	CString strDBr[16];
	CTime t = CTime::GetCurrentTime();
	int t_curse = t.GetTime();

	size_t col = 0;
		int iItem = 3;
		for ( i = 1; i < MAX_FDS;i++)
		{
			for(int j = 1; j < 17;j++ )
			{
     			for(int k = 0; k < 300;k++ )
				{
    				if(m_ADRecord[i][j][k].duant==0)
						break;
					{
                       	for(col=0; col<14; col++) {
							strtime="";
//                		BasicExcelCell* cell = sheet->Cell(iItem, col);
                		if(col==0)
							strtime =m_SlaveStation[i][j].WatchName+"|"+m_SlaveStation[i][j].strPN;
//                             m_Str2Data.GB2312ToUnicode(m_SlaveStation[i][j].WatchName,buf);
                		else if(col==1)
							strtime =m_SlaveStation[i][j].m_Unit;
                		else if(col==2)
				        	  strtime.Format("%.2f",m_SlaveStation[i][j].Apbrk);
                		else if(col==3)
				        	  strtime.Format("%.2f",m_SlaveStation[i][j].Aprtn);
                		else if(col==4)
				        	  strtime.Format("%s",m_SlaveStation[i][j].strBS);
                		else if(col==5)
							//�ϵ����(���ջ򱾰��ۼƶϵ����)
				        	  strtime.Format("%d",m_ADRecord[i][j][0].m_ATotalnum);
//                             m_Str2Data.GB2312ToUnicode("1" ,buf);
//							strtime ="1";
                		else if(col==6)
						{//�ۼƶϵ�ʱ��(���ջ򱾰��ۼƶϵ�ʱ��)
							COleDateTimeSpan t = m_ADRecord[i][j][299].tmid;
			            	strtime.Format("%d %d:%d:%d",t.GetDays(),t.GetHours(),t.GetMinutes(),t.GetSeconds()); 
//                            m_Str2Data.GB2312ToUnicode(strtime ,buf);
						}
                 		else if(col==7)
						{//���ֵ��ʱ��(���ջ򱾰�ϵ��ڼ����ֵ)
				    	  strtime.Format("%.2f|",m_ADRecord[i][j][299].AMaxValue);
						  strtime = strtime +m_ADRecord[i][j][299].ATime.Format(_T("%Y:%m:%d %H:%M:%S")); 
//                          m_Str2Data.GB2312ToUnicode(strtime,buf);
						}
                 		else if(col==8)
						{//ƽ��ֵ(���ջ򱾰�ϵ��ڼ�ƽ��ֵ);
				    	  strtime.Format("%.2f",m_ADRecord[i][j][299].AavV/m_ADRecord[i][j][299].m_ATotalnum);
//                          m_Str2Data.GB2312ToUnicode(strtime,buf);
						}
                 		else if(col==9)
						{//ÿ�ζϵ�ʱ�̼�����ʱ��
		        		  strtime =m_ADRecord[i][j][k].BTime.Format(_T("%Y:%m:%d %H:%M:%S")) +"|"+ m_ADRecord[i][j][k].NTime.Format(_T("%Y:%m:%d %H:%M:%S")); 
//                          m_Str2Data.GB2312ToUnicode(strtime,buf);
						}
                 		else if(col==10)
						{//ÿ�ζϵ��ۼ�ʱ��
							COleDateTimeSpan t = m_ADRecord[i][j][k].tmid;
			            	strtime.Format("%d %d:%d:%d",t.GetDays(),t.GetHours(),t.GetMinutes(),t.GetSeconds()); 
//                          m_Str2Data.GB2312ToUnicode(strtime,buf);
						}
                 		else if(col==11)//ÿ�ζϵ��ڼ�ƽ��ֵ�����ֵ��ʱ��
						{
				    	  strtime.Format("%.2f|%.2f|",m_ADRecord[i][j][k].AavV/m_ADRecord[i][j][k].duant,m_ADRecord[i][j][k].AMaxValue);
							strtime =strtime + m_ADRecord[i][j][k].AMaxTime.Format(_T("%Y:%m:%d %H:%M:%S"));
//                          m_Str2Data.GB2312ToUnicode(m_ADRecord[i][j][k].strsafetext,buf);
						}
                 		else if(col==12)//�ϵ�����|����״̬|ʱ��|�ۼ�ʱ��
						{
							strtime =m_ADRecord[i][j][k].strlocal;
							int strl = strtime.GetLength();
							if(strl>799)
								strtime = strtime.Mid(0,799);
						}
//                          m_Str2Data.GB2312ToUnicode(m_ADRecord[i][j][k].strlocal,buf);
						else if(col==13)//��ȫ��ʩ|ʱ��
							strtime =m_ADRecord[i][j][k].strsafetext;
//					rgMyRge.SetItem(_variant_t((long)iItem),_variant_t((long)(col+1)),_variant_t(strtime)); 
//						cell->Set(buf);
                        strDBr[col]=strtime;
						}
    	strtime.Format("INSERT INTO reportabd (R0,R1,R2,R3,R4,R5,R6,R7,R8,R9,R10,R11,R12,R13) VALUES('%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s')"
    		,strDBr[0],strDBr[1],strDBr[2],strDBr[3],strDBr[4],strDBr[5],strDBr[6],strDBr[7],strDBr[8],strDBr[9],strDBr[10],strDBr[11],strDBr[12],strDBr[13]);
     	theApp.m_pConnection->Execute(_bstr_t(strtime),NULL,adCmdText);
		            	iItem++;
					}//if
				}//k
	    	pFWnd->m_wndProgCtrl.StepIt();
			}//j
		}//i
	pFWnd->m_wndProgCtrl.SetPos (0);
	ShellExecute(0, "open", gstrTimeOut +"\\reportday.exe",m_Str2Data.CStringtocharp(strcan), 0, SW_NORMAL);
//	theApp.C_Ts.CreateP(gstrTimeOut +"\\reportday.exe", m_Str2Data.CStringtocharp(strcan),5,0x00000001);
}

void CMadeCertView::OnRECAFED() 
{
    CMainFrame* pFWnd=(CMainFrame*)AfxGetMainWnd();
	// initialize progress control.
	pFWnd->m_wndProgCtrl.SetRange (0, 3840);
	pFWnd->m_wndProgCtrl.SetPos (0);
	pFWnd->m_wndProgCtrl.SetStep (1);

	  for(int i = 1; i < MAX_FDS;i++ )
			for(int j = 1; j < MAX_CHAN;j++ )
			{
				for(int h = 0; h < 300;h++)
				{
					m_ADRecord[i][j][h].m_ATotalnum = 0;
					m_ADRecord[i][j][h].ATotalV = 0;
					m_ADRecord[i][j][h].duant = 0;
					m_ADRecord[i][j][h].strlocal = "";
					m_ADRecord[i][j][h].havev = 0;
					m_ADRecord[i][j][h].tmid = 0;
					m_ADRecord[i][j][h].AavV = 0;
					m_ADRecord[i][j][h].strsafetext = "";
					m_ADRecord[i][j][h].AMaxValue = 0;
					m_ADRecord[i][j][h].AMinValue = 666666;
				}
	    	pFWnd->m_wndProgCtrl.StepIt();
			}

	CString strtime,strtime2;
	if(b_twodb)
	{
		while ( !pRS1->EndOfFile)
		{
				int afds = pRS1->Fields->Item["ffds"]->Value.lVal;
				int achan = pRS1->Fields->Item["fchan"]->Value.lVal;
				COleDateTime dt(pRS1->Fields->Item["recdate"]->Value);
//				int afds = m_Realtimedata1.m_szffds;
//				int achan = m_Realtimedata1.m_szfchan;
	   		int dbp = mPoint[pRS1->Fields->Item["PID"]->Value.lVal];
//             if(dbp != 6666)
			 {
            	_bstr_t Explain =pRS1->Fields->Item["FeedStatus"]->Value;
				strtime.Format("%s",(char *)Explain);
			strtime.TrimRight();
			if(strtime == "�쳣")
			{
				if(m_ADRecord[afds][achan][1].m_ATotalnum == 0)//��һ�������쳣ʱ��
					m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].BTime =dt;

				Explain =pRS1->Fields->Item["safemtext"]->Value;
				strtime.Format("%s",(char *)Explain);
					strtime.TrimRight();
					if(strtime != "")
					{//ÿ�δ�ʩ����ȡ��ʩʱ��
		        		  strtime2   =   dt.Format(_T("%Y-%m-%d %H:%M:%S")); 
	       	    		m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].strsafetext += strtime+"|"+strtime2+"|";
					}
				m_ADRecord[afds][achan][1].m_ATotalnum++;//n�������쳣��¼
			}
			else if(strtime == "����")
			{
				if(m_ADRecord[afds][achan][1].m_ATotalnum> 0)
				{//����ʱ�� ������1 �´γ�ʼ��  ÿ�������쳣ʱ��
	    			m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].NTime =dt;
					m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].tmid =dt-m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].BTime;
					//�ۼ������쳣ʱ��(���ջ򱾰��ۼ������쳣ʱ��)
//					m_ADRecord[afds][achan][299].tmid +=m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].tmid;
					//�����쳣����(���ջ򱾰��ۼ������쳣����)
	     			m_ADRecord[afds][achan][0].m_ATotalnum++;  //�������쳣����
	     			m_ADRecord[afds][achan][1].m_ATotalnum = 0;  //״̬ת��
				}
			}
			 }
            	m_ADRecord[afds][achan][0].ATime = dt;
			pRS1->MoveNext();
		}
	}
//	if(!m_Realtimedata._IsEmpty())
	{
		while ( !theApp.pRS->EndOfFile)
		{
				int afds = theApp.pRS->Fields->Item["ffds"]->Value.lVal;
				int achan = theApp.pRS->Fields->Item["fchan"]->Value.lVal;
			COleDateTime dt(theApp.pRS->Fields->Item["recdate"]->Value);
//				int afds = m_Realtimedata.m_szffds;
//				int achan = m_Realtimedata.m_szfchan;
	   		int dbp = mPoint[theApp.pRS->Fields->Item["PID"]->Value.lVal];
//             if(dbp != 6666)
			 {
            	_bstr_t Explain =theApp.pRS->Fields->Item["FeedStatus"]->Value;
				strtime.Format("%s",(char *)Explain);
			strtime.TrimRight();
			if(strtime == "�쳣")
			{
				if(m_ADRecord[afds][achan][1].m_ATotalnum == 0)//��һ�������쳣ʱ��
					m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].BTime =dt;

            	Explain =theApp.pRS->Fields->Item["safemtext"]->Value;
				strtime.Format("%s",(char *)Explain);
					strtime.TrimRight();
					if(strtime != "")
					{//ÿ�δ�ʩ����ȡ��ʩʱ��
		        		  strtime2   =   dt.Format(_T("%Y-%m-%d %H:%M:%S")); 
	       	    		m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].strsafetext += strtime+"|"+strtime2+"|";
					}
				m_ADRecord[afds][achan][1].m_ATotalnum++;//n�������쳣��¼
			}
			else if(strtime == "����")
			{
				if(m_ADRecord[afds][achan][1].m_ATotalnum> 0)
				{//����ʱ�� ������1 �´γ�ʼ��  ÿ�������쳣ʱ��
	    			m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].NTime =dt;
					m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].tmid =dt-m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].BTime;
					//�ۼ������쳣ʱ��(���ջ򱾰��ۼ������쳣ʱ��)
//					m_ADRecord[afds][achan][299].tmid +=m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].tmid;
					//�����쳣����(���ջ򱾰��ۼ������쳣����)
	     			m_ADRecord[afds][achan][0].m_ATotalnum++;  //�������쳣����
	     			m_ADRecord[afds][achan][1].m_ATotalnum = 0;  //״̬ת��
				}
			}
			 }
            	m_ADRecord[afds][achan][0].ATime = dt;
			theApp.pRS->MoveNext();
		}
	}
		for( i = 1; i < MAX_FDS;i++ )
			for(int j = 1; j < MAX_CHAN;j++ )
			{
				if(m_ADRecord[i][j][1].m_ATotalnum> 0)//�������쳣
				{
	    			m_ADRecord[i][j][m_ADRecord[i][j][0].m_ATotalnum].NTime =m_ADRecord[i][j][0].ATime;
					m_ADRecord[i][j][m_ADRecord[i][j][0].m_ATotalnum].tmid =m_ADRecord[i][j][0].ATime-m_ADRecord[i][j][m_ADRecord[i][j][0].m_ATotalnum].BTime;
					//�ۼ������쳣ʱ��(���ջ򱾰��ۼ������쳣ʱ��)
//					m_ADRecord[i][j][299].tmid +=m_ADRecord[i][j][m_ADRecord[i][j][0].m_ATotalnum].tmid;
					//�����쳣����(���ջ򱾰��ۼ������쳣����)
	     			m_ADRecord[i][j][0].m_ATotalnum++;  //�������쳣����
	     			m_ADRecord[i][j][1].m_ATotalnum = 0;  //״̬ת��
				}
	    	pFWnd->m_wndProgCtrl.StepIt();
			}

		for ( i = 1; i < MAX_FDS;i++)
		{
			for(int j = 1; j < 17;j++ )
			{
         		int m_fen=0;
	   	    	int dbp = mPoint[m_SlaveStation[i][j].m_PID];
                if(dbp != 6666)
				{
                 	for(int h= 0 ;h<64 ; h++)
					{
            		     int cfds = m_ADCbreakE[i][j][h].bFSd;
            			 int cchan = m_ADCbreakE[i][j][h].bchanel;
            			 if(cfds == 0)
	            			 break;
            			 for(int m= 0 ;m<64 ; m++)
						 {
    	            	     int ffds = m_CFeed[cfds][cchan][m].bFSd;//������
	                		 int fchan = m_CFeed[cfds][cchan][m].bchanel;
		            		 if(ffds == 0)
	 	            			 break;
               	    		for(int k = 0; k < m_ADRecord[ffds][fchan][0].m_ATotalnum;k++ )
							{
								m_ADRecord[i][j][m_fen].BTime =m_ADRecord[ffds][fchan][k].BTime;
								m_ADRecord[i][j][m_fen].NTime =m_ADRecord[ffds][fchan][k].NTime;
								m_ADRecord[i][j][m_fen].tmid =m_ADRecord[ffds][fchan][k].tmid;
								m_ADRecord[i][j][m_fen].strsafetext =m_ADRecord[ffds][fchan][k].strsafetext;
								m_ADRecord[i][j][299].tmid += m_ADRecord[ffds][fchan][k].tmid;
								m_fen++;
							}
							m_ADRecord[i][j][0].m_ATotalnum += m_ADRecord[ffds][fchan][0].m_ATotalnum;
						 }//for(int m= 0 ;m<64 ; m++)
					}//for(int h= 0 ;h<64 ; h++)
				}//if(dbp != 6666)
			}//for(int j = 1; j < 17;j++ )
		}//for ( i = 1; i < MAX_FDS;i++)
    if (b_twodb)
	{
		b_twodb = FALSE;
      	pRS1->Close();
	}
    theApp.pRS->Close();

	CString strtime1,strtime3,strtime4,stnames,strcan;
		strcan ="4,"+t.Format(_T("%Y-%m-%d,%H:%M:%S"))+","+t1.Format(_T("%Y-%m-%d,%H:%M:%S"));
		strtime = "��ʼ����:"+t.Format(_T("%Y-%m-%d %H:%M:%S")); 
		strtime1 = "��ֹ����:"+ t1.Format(_T("%Y-%m-%d %H:%M:%S")); 
		int m_hours = (t1.GetTime()-t.GetTime()+1)/3600;
		strtime2.Format("%d",m_hours); 
		strtime2 = "ʱ����:" +strtime2+"Сʱ";
		strtime3 = "��ӡʱ��:" + CTime::GetCurrentTime().Format(_T("%Y-%m-%d %H:%M:%S"));
		if(m_hours >20)
	     	strtime4 = t1.Format(_T("%Y-%m-%d"))+"�ձ���:";
		else
	     	strtime4 = t1.Format(_T("%Y-%m-%d"))+ "�౨��:";

		if(theApp.strargc == "OnEXCELAFE")
		{
			if(m_hours >20)
				stnames = "ģ���������쳣�ձ���";
			else
 				stnames = "ģ���������쳣�౨��";
		}
		else
				stnames = "ģ���������쳣��¼��ѯ��ʾ";

		strtime += "    "+strtime1+"     "+strtime2;
    	strtime = "TRUNCATE TABLE reportafd";
    	try{
    		theApp.m_pConnection->Execute(_bstr_t(strtime),NULL,adCmdText);  }
    	catch(_com_error e){
    		AfxMessageBox(e.ErrorMessage()); }
	CString strDBr[16];
	CTime t = CTime::GetCurrentTime();
	int t_curse = t.GetTime();

	size_t col = 0;
		int iItem = 3;
		for ( i = 1; i < MAX_FDS;i++)
		{
			for(int j = 1; j < 17;j++ )
			{
	   	    	int dbp = mPoint[m_SlaveStation[i][j].m_PID];
                if(dbp != 6666)
				{
				for(int k = 0; k < m_ADRecord[i][j][0].m_ATotalnum;k++ )
				{
					{
                       	for(col=0; col<6; col++) {
							strtime="";
//                		BasicExcelCell* cell = sheet->Cell(iItem, col);
                		if(col==0)
							strtime =m_SlaveStation[i][j].WatchName+"|"+m_SlaveStation[i][j].strPN;
//                             m_Str2Data.GB2312ToUnicode(m_SlaveStation[i][j].WatchName,buf);
                		else if(col==1)
				        	  strtime.Format("%s",m_SlaveStation[i][j].strBS);
                		else if(col==2)
							//�����쳣����(���ջ򱾰��ۼƶϵ����)
				        	  strtime.Format("%d",m_ADRecord[i][j][0].m_ATotalnum);
//                             m_Str2Data.GB2312ToUnicode("1" ,buf);
                		else if(col==3)
						{//�ۼ������쳣ʱ��(���ջ򱾰��ۼ������쳣ʱ��)
							COleDateTimeSpan t = m_ADRecord[i][j][299].tmid;
			            	strtime.Format("%d %d:%d:%d",t.GetDays(),t.GetHours(),t.GetMinutes(),t.GetSeconds()); 
//                            m_Str2Data.GB2312ToUnicode(strtime ,buf);
						}
                 		else if(col==4)//ÿ������״̬ÿ���ۼ�ʱ�估��ֹʱ��
						{
						  COleDateTimeSpan t = m_ADRecord[i][j][k].tmid;
			            	strtime.Format("�쳣|%d %d:%d:%d",t.GetDays(),t.GetHours(),t.GetMinutes(),t.GetSeconds()); 
		        		  strtime +="|"+m_ADRecord[i][j][k].BTime.Format(_T("%Y:%m:%d %H:%M:%S")) +"|"+ m_ADRecord[i][j][k].NTime.Format(_T("%Y:%m:%d %H:%M:%S")) ; 
//                          m_Str2Data.GB2312ToUnicode(strtime,buf);
						}
                 		else if(col==5)
						{
							strtime =m_ADRecord[i][j][k].strsafetext;
//                          m_Str2Data.GB2312ToUnicode(strtime,buf);
						}
//					rgMyRge.SetItem(_variant_t((long)iItem),_variant_t((long)(col+1)),_variant_t(strtime)); 
//						cell->Set(buf);
                        strDBr[col]=strtime;
						}
    	strtime.Format("INSERT INTO reportafd (R0,R1,R2,R3,R4,R5) VALUES('%s','%s','%s','%s','%s','%s')"
    		,strDBr[0],strDBr[1],strDBr[2],strDBr[3],strDBr[4],strDBr[5]);
     	theApp.m_pConnection->Execute(_bstr_t(strtime),NULL,adCmdText);
		            	iItem++;
					}//if
				}//k
				}
	    	pFWnd->m_wndProgCtrl.StepIt();
			}//j
		}//i
	pFWnd->m_wndProgCtrl.SetPos (0);
	ShellExecute(0, "open", gstrTimeOut +"\\reportday.exe",m_Str2Data.CStringtocharp(strcan), 0, SW_NORMAL);
//	theApp.C_Ts.CreateP(gstrTimeOut +"\\reportday.exe", m_Str2Data.CStringtocharp(strcan),5,0x00000001);
}
//ģ����ͳ��ֵ��ʷ��¼��ѯ����
void CMadeCertView::OnRECASR() 
{
    CMainFrame* pFWnd=(CMainFrame*)AfxGetMainWnd();
	// initialize progress control.
	pFWnd->m_wndProgCtrl.SetRange (0, 2400);
	pFWnd->m_wndProgCtrl.SetPos (0);
	pFWnd->m_wndProgCtrl.SetStep (1);

	for(int i = 1; i < MAX_FDS;i++ )
			for(int j = 1; j < MAX_CHAN;j++ )
			{
				for(int h = 0; h < 300;h++)
				{
					m_ADRecord[i][j][h].m_ATotalnum = 0;
					m_ADRecord[i][j][h].ATotalV = 0;
					m_ADRecord[i][j][h].duant = 0;
					m_ADRecord[i][j][h].strlocal = "";
					m_ADRecord[i][j][h].havev = 0;
					m_ADRecord[i][j][h].tmid = 0;
					m_ADRecord[i][j][h].AavV = 0;
					m_ADRecord[i][j][h].strsafetext = "";
					m_ADRecord[i][j][h].AMaxValue = 0;
					m_ADRecord[i][j][h].AMinValue = 666666;
				}
	    	pFWnd->m_wndProgCtrl.StepIt();
			}
	CString strtime,strtime2,strname;
//	if(!m_Rt5mdata._IsEmpty())
	{
		while ( !theApp.pRS->EndOfFile)
		{
				int afds = theApp.pRS->Fields->Item["fds"]->Value.lVal;
				int achan = theApp.pRS->Fields->Item["chan"]->Value.lVal;
			float s_curd = theApp.pRS->Fields->Item["AValue"]->Value.fltVal;
			float s_curdmax = theApp.pRS->Fields->Item["AMaxValue"]->Value.fltVal;
			COleDateTime dt(theApp.pRS->Fields->Item["recdate"]->Value);
	   		int dbp = mPoint[theApp.pRS->Fields->Item["PID"]->Value.lVal];
             if(dbp != 6666)
			 {
				//ģ����ͳ�ƴ���  ͳ��ֵ   ƽ��ֵ(���ջ򱾰�ͳ��ֵ��ʷ��¼ƽ��ֵ)
//			    	m_ADRecord[afds][achan][299].m_ATotalnum++;//��ͳ�Ƽ�¼����
			    	m_ADRecord[afds][achan][299].AavV +=s_curd;
					//���ֵ��ʱ��(���ջ򱾰��ڼ����ֵ)
				if(m_ADRecord[afds][achan][299].AMaxValue <s_curdmax)
				{//�������ֵ��ʱ��   m_ADRecord[afds][achan][0].m_ATotalnum ����
    				m_ADRecord[afds][achan][299].AMaxValue = s_curdmax;
		    		m_ADRecord[afds][achan][299].AMaxTime = dt;
				}

					//ÿ���ڼ�ƽ��ֵ�����ֵ��ʱ��
			    	m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].AavV =s_curd;
				//ÿ�����ֵ��ʱ��   m_ADRecord[afds][achan][0].m_ATotalnum ����
    				m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].AMaxValue = s_curdmax;
		    		m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].AMaxTime = dt;
	     	    m_ADRecord[afds][achan][0].m_ATotalnum++;  //��ͳ�Ƽ�¼����
			 }
			theApp.pRS->MoveNext();
		}
	}
	theApp.pRS->Close();

	CString strtime1,strtime3,strtime4,stnames,strcan;
		strcan ="5,"+t.Format(_T("%Y-%m-%d,%H:%M:%S"))+","+t1.Format(_T("%Y-%m-%d,%H:%M:%S"));
		strtime = "��ʼ����:"+t.Format(_T("%Y-%m-%d %H:%M:%S")); 
		strtime1 = "��ֹ����:"+ t1.Format(_T("%Y-%m-%d %H:%M:%S")); 
		int m_hours = (t1.GetTime()-t.GetTime()+1)/3600;
		strtime2.Format("%d",m_hours); 
		strtime2 = "ʱ����:" +strtime2+"Сʱ";
		strtime3 = "��ӡʱ��:" + CTime::GetCurrentTime().Format(_T("%Y-%m-%d %H:%M:%S"));
		if(m_hours >20)
	     	strtime4 = t1.Format(_T("%Y-%m-%d"))+"�ձ���:";
		else
	     	strtime4 = t1.Format(_T("%Y-%m-%d"))+ "�౨��:";

		if(theApp.strargc == "OnEXCELASR")
		{
			if(m_hours >20)
				stnames = "ģ����ͳ��ֵ�ձ���";
			else
				stnames = "ģ����ͳ��ֵ�౨��";
		}
		else
				stnames = "ģ����ͳ��ֵ��¼��ѯ��ʾ";

		strtime += "    "+strtime1+"    "+strtime2;

    	strtime = "TRUNCATE TABLE reportahd";
    	try{
    		theApp.m_pConnection->Execute(_bstr_t(strtime),NULL,adCmdText);  }
    	catch(_com_error e){
    		AfxMessageBox(e.ErrorMessage()); }
	CString strDBr[16];
	CTime t = CTime::GetCurrentTime();
	int t_curse = t.GetTime();

	size_t col = 0;
		int iItem = 3;
		for ( i = 1; i < MAX_FDS;i++)
		{
			for(int j = 1; j < 17;j++ )
			{
     			for(int k = 0; k < 300;k++ )
				{
					if(m_ADRecord[i][j][k].AMaxValue <= 0.0001)
						break;
                    for(col=0; col<8; col++) {
						strtime="";
//             		BasicExcelCell* cell = sheet->Cell(iItem, col);
						if(col==0)
						{
				         	COleDateTimeSpan tspan(0,0,5,0);
							COleDateTime o1 =m_ADRecord[i][j][k].AMaxTime - tspan;
						  strtime = "5|" +o1.Format(_T("%Y:%m:%d %H:%M:%S"))+"|"+m_ADRecord[i][j][k].AMaxTime.Format(_T("%Y:%m:%d %H:%M:%S")) ;
						}
                        else if(col==1)
							strtime =m_SlaveStation[i][j].WatchName+"|"+m_SlaveStation[i][j].strPN;
//                        m_Str2Data.GB2312ToUnicode(m_SlaveStation[i][j].WatchName,buf);
                		else if(col==2)
							strtime =m_SlaveStation[i][j].m_Unit;
                		else if(col==3)
				        	  strtime.Format("%.2f",m_SlaveStation[i][j].AlarmValueH);
                		else if(col==4)
				        	  strtime.Format("%.2f",m_SlaveStation[i][j].Apbrk);
                		else if(col==5)
				        	  strtime.Format("%.2f",m_SlaveStation[i][j].Aprtn);
              		else if(col==6)
					{//���ֵ���ֵʱ��ƽ��ֵ(���ջ򱾰��ڼ����ֵ)
				    	  strtime2.Format("|%.2f",m_ADRecord[i][j][299].AavV/m_ADRecord[i][j][0].m_ATotalnum);
				    	  strtime.Format("%.2f|",m_ADRecord[i][j][299].AMaxValue);
						  strtime = strtime +m_ADRecord[i][j][299].AMaxTime.Format(_T("%Y:%m:%d %H:%M:%S")) +strtime2; 
//                        m_Str2Data.GB2312ToUnicode(strtime1,buf);
					}
              		else if(col==7)
					{//ÿ��ʱ����ƽ��ֵ�����ֵ
				    	  strtime2.Format("%.2f|%.2f",m_ADRecord[i][j][k].AavV,m_ADRecord[i][j][k].AMaxValue);
//						  strtime = strtime2 +m_ADRecord[i][j][299].BTime.Format(_T("%Y:%m:%d %H:%M:%S")) +strtime2; 
//                         m_Str2Data.GB2312ToUnicode(strtime ,buf);
					}
//					rgMyRge.SetItem(_variant_t((long)iItem),_variant_t((long)(col+1)),_variant_t(strtime)); 
//					cell->Set(buf);
                        strDBr[col]=strtime;
					}
    	strtime.Format("INSERT INTO reportahd (R0,R1,R2,R3,R4,R5,R6,R7) VALUES('%s','%s','%s','%s','%s','%s','%s','%s')"
    		,strDBr[0],strDBr[1],strDBr[2],strDBr[3],strDBr[4],strDBr[5],strDBr[6],strDBr[7]);
     	theApp.m_pConnection->Execute(_bstr_t(strtime),NULL,adCmdText);
		          iItem++;
				}
	    	pFWnd->m_wndProgCtrl.StepIt();
			}
		}
	pFWnd->m_wndProgCtrl.SetPos (0);
	ShellExecute(0, "open", gstrTimeOut +"\\reportday.exe",m_Str2Data.CStringtocharp(strcan), 0, SW_NORMAL);
//	theApp.C_Ts.CreateP(gstrTimeOut +"\\reportday.exe", m_Str2Data.CStringtocharp(strcan),5,0x00000001);
}
//�����������ϵ��ձ�
void CMadeCertView::OnRECDABD() 
{
    CMainFrame* pFWnd=(CMainFrame*)AfxGetMainWnd();
	// initialize progress control.
	pFWnd->m_wndProgCtrl.SetRange (0, 3840);
	pFWnd->m_wndProgCtrl.SetPos (0);
	pFWnd->m_wndProgCtrl.SetStep (1);

	for(int i = 1; i < MAX_FDS;i++ )
			for(int j = 1; j < MAX_CHAN;j++ )
			{
				for(int h = 0; h < 300;h++)
				{
					m_ADRecord[i][j][h].m_ATotalnum = 0;
					m_ADRecord[i][j][h].ATotalV = 0;
					m_ADRecord[i][j][h].duant = 6;
					m_ADRecord[i][j][h].strlocal = "";
					m_ADRecord[i][j][h].havev = 0;
					m_ADRecord[i][j][h].tmid = 0;
					m_ADRecord[i][j][h].tmid1 = 0;
					m_ADRecord[i][j][h].AavV = 0;
					m_ADRecord[i][j][h].strsafetext = "";
					m_ADRecord[i][j][h].AMaxValue = 0;
					m_ADRecord[i][j][h].AMinValue = 666666;
				}
	    	pFWnd->m_wndProgCtrl.StepIt();
			}
	CString strtime,strtime2;
	if(b_twodb)
	{
		while ( !pRS1->EndOfFile)
		{
				int afds = pRS1->Fields->Item["fds"]->Value.lVal;
				int achan = pRS1->Fields->Item["chan"]->Value.lVal;
				int ffds = pRS1->Fields->Item["ffds"]->Value.lVal;
				int fchan = pRS1->Fields->Item["fchan"]->Value.lVal;
    			int m_alarm = pRS1->Fields->Item["ADStatus"]->Value.lVal;
				int s_curd = pRS1->Fields->Item["CDValue"]->Value.lVal;
				COleDateTime dt(pRS1->Fields->Item["recdate"]->Value);
	   		int dbp = mPoint[pRS1->Fields->Item["PID"]->Value.lVal];
             if(dbp != 6666)
			 {
			if(m_alarm == 16)
			{
				if(m_ADRecord[afds][achan][1].m_ATotalnum == 0)//��һ�α���ʱ��
					m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].BTime =dt;
					//ÿ�ο����������ڼ�״̬��ʱ��
			    	m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].duant =s_curd;
               	_bstr_t Explain =pRS1->Fields->Item["safemtext"]->Value;
				strtime.Format("%s",(char *)Explain);
					strtime.TrimRight();
					if(strtime != "")
					{//ÿ�δ�ʩ����ȡ��ʩʱ��
		        		  strtime2   =   dt.Format(_T("%Y-%m-%d %H:%M:%S")); 
	       	    		m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].strsafetext += strtime+"|"+strtime2+"|";
					}
            	 Explain =pRS1->Fields->Item["FeedStatus"]->Value;
				strtime.Format("%s",(char *)Explain);
					strtime.TrimRight();
					if(strtime != "")
					{//����״̬����ʱ�̡��ۼ�ʱ��
		        		  strtime2   =   dt.Format(_T("%Y-%m-%d %H:%M:%S")); 
	       	    		m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].strlocal += m_SlaveStation[ffds][fchan].WatchName +"|"+ m_SlaveStation[ffds][fchan].strPN +"|"+ strtime+"|"+strtime2+"|";
					}
				m_ADRecord[afds][achan][1].m_ATotalnum++;//n������ֵ
			}
			else if(m_alarm != 16)
			{
				if(m_ADRecord[afds][achan][1].m_ATotalnum> 0)
				{//����ʱ�� ������1 �´γ�ʼ��  ÿ�α���ʱ��
	    			m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].NTime =dt;
					m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].tmid =dt-m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].BTime;
					//�ۼƱ���ʱ��(���ջ򱾰��ۼƱ���ʱ��)
					m_ADRecord[afds][achan][299].tmid +=m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].tmid;
					//��������(���ջ򱾰��ۼƱ�������)
	     			m_ADRecord[afds][achan][0].m_ATotalnum++;  //�ܱ�������
	     			m_ADRecord[afds][achan][1].m_ATotalnum = 0;  //״̬ת��
				}
			}
			 }
							COleDateTimeSpan t(0,0,0,1);
            	m_ADRecord[afds][achan][0].ATime = dt +t;
			pRS1->MoveNext();
		}
	}
//	if(!m_Realtimedata._IsEmpty())
	{
		while ( !theApp.pRS->EndOfFile)
		{
				int afds = theApp.pRS->Fields->Item["fds"]->Value.lVal;
				int achan = theApp.pRS->Fields->Item["chan"]->Value.lVal;
				int ffds = theApp.pRS->Fields->Item["ffds"]->Value.lVal;
				int fchan = theApp.pRS->Fields->Item["fchan"]->Value.lVal;
    			int m_alarm = theApp.pRS->Fields->Item["ADStatus"]->Value.lVal;
			COleDateTime dt(theApp.pRS->Fields->Item["recdate"]->Value);
	   		int dbp = mPoint[theApp.pRS->Fields->Item["PID"]->Value.lVal];
             if(dbp != 6666)
			 {
			if(m_alarm == 16)
			{
				if(m_ADRecord[afds][achan][1].m_ATotalnum == 0)
					m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].BTime =dt;
					//ÿ�ο����������ڼ�״̬��ʱ��
			    	m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].duant =theApp.pRS->Fields->Item["CDValue"]->Value.lVal;
            	_bstr_t Explain =theApp.pRS->Fields->Item["safemtext"]->Value;
				strtime.Format("%s",(char *)Explain);
					strtime.TrimRight();
					if(strtime != "")
					{
		        		  strtime2   =   dt.Format(_T("%Y-%m-%d %H:%M:%S")); 
	       	    		m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].strsafetext += strtime+"|"+strtime2+"|";
					}
            	    Explain =theApp.pRS->Fields->Item["FeedStatus"]->Value;
				strtime.Format("%s",(char *)Explain);
					strtime.TrimRight();
					if(strtime != "")
					{//����״̬����ʱ�̡��ۼ�ʱ��
		        		  strtime2   =   dt.Format(_T("%Y-%m-%d %H:%M:%S")); 
	       	    		m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].strlocal += m_SlaveStation[ffds][fchan].WatchName +"|"+ m_SlaveStation[ffds][fchan].strPN +"|"+ strtime+"|"+strtime2+"|";
					}
				m_ADRecord[afds][achan][1].m_ATotalnum++;//n������ֵ
			}
			else if(m_alarm != 16)
			{
				if(m_ADRecord[afds][achan][1].m_ATotalnum> 0)//�б���
				{
	    			m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].NTime =dt;
					m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].tmid =dt-m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].BTime;
					//�ۼƱ���ʱ��(���ջ򱾰��ۼƱ���ʱ��)
					m_ADRecord[afds][achan][299].tmid +=m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].tmid;
					//��������(���ջ򱾰��ۼƱ�������)
	     			m_ADRecord[afds][achan][0].m_ATotalnum++;  //�ܱ�������
	     			m_ADRecord[afds][achan][1].m_ATotalnum = 0;  //״̬ת��
				}
			}
			 }
							COleDateTimeSpan t(0,0,0,1);
            	m_ADRecord[afds][achan][0].ATime = dt+t;
			theApp.pRS->MoveNext();
		}
	}
		for( i = 1; i < MAX_FDS;i++ )
			for(int j = 1; j < MAX_CHAN;j++ )
				if(m_ADRecord[i][j][1].m_ATotalnum> 0)//�б���
				{
	    			m_ADRecord[i][j][m_ADRecord[i][j][0].m_ATotalnum].NTime =m_ADRecord[i][j][0].ATime;
					m_ADRecord[i][j][m_ADRecord[i][j][0].m_ATotalnum].tmid =m_ADRecord[i][j][0].ATime-m_ADRecord[i][j][m_ADRecord[i][j][0].m_ATotalnum].BTime;
					//�ۼƱ���ʱ��(���ջ򱾰��ۼƱ���ʱ��)
					m_ADRecord[i][j][299].tmid +=m_ADRecord[i][j][m_ADRecord[i][j][0].m_ATotalnum].tmid;
					//��������(���ջ򱾰��ۼƱ�������)
	     			m_ADRecord[i][j][0].m_ATotalnum++;  //�ܱ�������
	     			m_ADRecord[i][j][1].m_ATotalnum = 0;  //״̬ת��
				}

//	if(theApp.pRS->GetEndOfFile() ==0)
	if(b_twodb)
	{
		if(pRS1->GetRecordCount() !=0)
			pRS1->MoveFirst();
		while ( !pRS1->EndOfFile)
		{
				int afds = pRS1->Fields->Item["fds"]->Value.lVal;
				int achan = pRS1->Fields->Item["chan"]->Value.lVal;
				int ffds = pRS1->Fields->Item["ffds"]->Value.lVal;
				int fchan = pRS1->Fields->Item["fchan"]->Value.lVal;
    			int m_alarm = pRS1->Fields->Item["ADStatus"]->Value.lVal;
				COleDateTime dt(pRS1->Fields->Item["recdate"]->Value);
	   		int dbp = mPoint[pRS1->Fields->Item["PID"]->Value.lVal];
             if(dbp != 6666)
			 {
			if(m_alarm == 32)
			{
				if(m_ADRecord[afds][achan][1].m_ATotalnum == 0)//��һ�ζϵ�ʱ��
					m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].BTime =dt;
					//ÿ�ο������ϵ��ڼ�״̬��ʱ��
			    	m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].duant =pRS1->Fields->Item["CDValue"]->Value.lVal;
                 	_bstr_t Explain =pRS1->Fields->Item["safemtext"]->Value;
		    		strtime.Format("%s",(char *)Explain);
					strtime.TrimRight();
					if(strtime != "")
					{//ÿ�δ�ʩ����ȡ��ʩʱ��
		        		  strtime2   =   dt.Format(_T("%Y-%m-%d %H:%M:%S")); 
	       	    		m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].strsafetext += strtime+"|"+strtime2+"|";
					}
                 	 Explain =pRS1->Fields->Item["FeedStatus"]->Value;
		    		strtime.Format("%s",(char *)Explain);
					strtime.TrimRight();
					if(strtime != "")
					{//����״̬����ʱ�̡��ۼ�ʱ��
		        		  strtime2   =   dt.Format(_T("%Y-%m-%d %H:%M:%S")); 
	       	    		m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].strlocal += m_SlaveStation[ffds][fchan].WatchName +"|"+ m_SlaveStation[ffds][fchan].strPN +"|"+ strtime+"|"+strtime2+"|";
					}
				m_ADRecord[afds][achan][1].m_ATotalnum++;//n���ϵ�ֵ
			}
			else if(m_alarm != 32)
			{
				if(m_ADRecord[afds][achan][1].m_ATotalnum> 0)
				{//����ʱ�� ������1 �´γ�ʼ��  ÿ�ζϵ�ʱ��
	    			m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].NTime =dt;
					m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].tmid =dt-m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].BTime;
					//�ۼƶϵ�ʱ��(���ջ򱾰��ۼƶϵ�ʱ��)
					m_ADRecord[afds][achan][299].tmid +=m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].tmid;
					//�ϵ����(���ջ򱾰��ۼƶϵ����)
	     			m_ADRecord[afds][achan][0].m_ATotalnum++;  //�ܶϵ����
	     			m_ADRecord[afds][achan][1].m_ATotalnum = 0;  //״̬ת��
				}
			}
			 }
							COleDateTimeSpan t(0,0,0,1);
            	m_ADRecord[afds][achan][0].ATime = dt+t;
			pRS1->MoveNext();
		}
	}
//	if(!m_Realtimedata._IsEmpty())
	{
		if(theApp.pRS->GetRecordCount() !=0)
    		theApp.pRS->MoveFirst();
		while ( !theApp.pRS->EndOfFile)
		{
				int afds = theApp.pRS->Fields->Item["fds"]->Value.lVal;
				int achan = theApp.pRS->Fields->Item["chan"]->Value.lVal;
				int ffds = theApp.pRS->Fields->Item["ffds"]->Value.lVal;
				int fchan = theApp.pRS->Fields->Item["fchan"]->Value.lVal;
    			int m_alarm = theApp.pRS->Fields->Item["ADStatus"]->Value.lVal;
			COleDateTime dt(theApp.pRS->Fields->Item["recdate"]->Value);
	   		int dbp = mPoint[theApp.pRS->Fields->Item["PID"]->Value.lVal];
             if(dbp != 6666)
			 {
			if(m_alarm == 32)
			{
				if(m_ADRecord[afds][achan][1].m_ATotalnum == 0)
					m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].BTime =dt;
					//ÿ�ο������ϵ��ڼ�״̬��ʱ��
			    	m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].duant =theApp.pRS->Fields->Item["CDValue"]->Value.lVal;
                	_bstr_t Explain =theApp.pRS->Fields->Item["safemtext"]->Value;
	    			strtime.Format("%s",(char *)Explain);
					strtime.TrimRight();
					if(strtime != "")
					{
		        		  strtime2   =   dt.Format(_T("%Y-%m-%d %H:%M:%S")); 
	       	    		m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].strsafetext += strtime+"|"+strtime2+"|";
					}
            	    Explain =theApp.pRS->Fields->Item["FeedStatus"]->Value;
	    			strtime.Format("%s",(char *)Explain);
					strtime.TrimRight();
					if(strtime != "")
					{//����״̬����ʱ�̡��ۼ�ʱ��
		        		  strtime2   =   dt.Format(_T("%Y-%m-%d %H:%M:%S")); 
	       	    		m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].strlocal += m_SlaveStation[ffds][fchan].WatchName +"|"+ m_SlaveStation[ffds][fchan].strPN +"|"+ strtime+"|"+strtime2+"|";
					}
				m_ADRecord[afds][achan][1].m_ATotalnum++;//n���ϵ�ֵ
			}
			else if(m_alarm != 32)
			{
				if(m_ADRecord[afds][achan][1].m_ATotalnum> 0)//�жϵ�
				{
	    			m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].NTime =dt;
					m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].tmid =dt-m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].BTime;
					//�ۼƶϵ�ʱ��(���ջ򱾰��ۼƶϵ�ʱ��)
					m_ADRecord[afds][achan][299].tmid +=m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].tmid;
					//�ϵ����(���ջ򱾰��ۼƶϵ����)
	     			m_ADRecord[afds][achan][0].m_ATotalnum++;  //�ܶϵ����
	     			m_ADRecord[afds][achan][1].m_ATotalnum = 0;  //״̬ת��
				}
			}
			 }
							COleDateTimeSpan t(0,0,0,1);
            	m_ADRecord[afds][achan][0].ATime = dt+t;
			theApp.pRS->MoveNext();
		}
	}
		for( i = 1; i < MAX_FDS;i++ )
			for(int j = 1; j < MAX_CHAN;j++ )
			{
				if(m_ADRecord[i][j][1].m_ATotalnum> 0)//�жϵ�
				{
	    			m_ADRecord[i][j][m_ADRecord[i][j][0].m_ATotalnum].NTime =m_ADRecord[i][j][0].ATime;
					m_ADRecord[i][j][m_ADRecord[i][j][0].m_ATotalnum].tmid =m_ADRecord[i][j][0].ATime-m_ADRecord[i][j][m_ADRecord[i][j][0].m_ATotalnum].BTime;
					//�ۼƶϵ�ʱ��(���ջ򱾰��ۼƶϵ�ʱ��)
					m_ADRecord[i][j][299].tmid +=m_ADRecord[i][j][m_ADRecord[i][j][0].m_ATotalnum].tmid;
					//�ϵ����(���ջ򱾰��ۼƶϵ����)
	     			m_ADRecord[i][j][0].m_ATotalnum++;  //�ܶϵ����
	     			m_ADRecord[i][j][1].m_ATotalnum = 0;  //״̬ת��
				}

	    	pFWnd->m_wndProgCtrl.StepIt();
			}
    if (b_twodb)
	{
		b_twodb = FALSE;
      	pRS1->Close();
	}
    theApp.pRS->Close();

	CString strtime1,strtime3,strtime4,stnames,strcan;
		strcan ="6,"+t.Format(_T("%Y-%m-%d,%H:%M:%S"))+","+t1.Format(_T("%Y-%m-%d,%H:%M:%S"));
		strtime = "��ʼ����:"+t.Format(_T("%Y-%m-%d %H:%M:%S")); 
		strtime1 = "��ֹ����:"+ t1.Format(_T("%Y-%m-%d %H:%M:%S")); 
		int m_hours = (t1.GetTime()-t.GetTime()+1)/3600;
		strtime2.Format("%d",m_hours); 
		strtime2 = "ʱ����:" +strtime2+"Сʱ";
		strtime3 = "��ӡʱ��:" + CTime::GetCurrentTime().Format(_T("%Y-%m-%d %H:%M:%S"));
		if(m_hours >20)
	     	strtime4 = t1.Format(_T("%Y-%m-%d"))+"�ձ���:";
		else
	     	strtime4 = t1.Format(_T("%Y-%m-%d"))+ "�౨��:";

		if(theApp.strargc == "OnEXCELDA")
		{
			if(m_hours >20)
				stnames = "�����������ձ���";
			else
				stnames = "�����������౨��";
		}
		else
				stnames = "������������¼��ѯ��ʾ";
		strtime += "    "+strtime1+"    "+strtime2;

    	strtime = "TRUNCATE TABLE reportdad";
    	try{
    		theApp.m_pConnection->Execute(_bstr_t(strtime),NULL,adCmdText);  }
    	catch(_com_error e){
    		AfxMessageBox(e.ErrorMessage()); }
	CString strDBr[16];
	CTime t = CTime::GetCurrentTime();
	int t_curse = t.GetTime();

	   size_t col = 0;
		int iItem = 3;
		for ( i = 1; i < MAX_FDS;i++)
		{
			for(int j = 1; j < 17;j++ )
			{
     			for(int k = 0; k < 300;k++ )
				{
    				if(m_ADRecord[i][j][k].duant == 6)
						break;
					{
                       	for(col=0; col<8; col++) {
							strtime="";
//                		BasicExcelCell* cell = sheet->Cell(iItem, col);
                		if(col==0)
							strtime =m_SlaveStation[i][j].WatchName+"|"+m_SlaveStation[i][j].strPN;
//                             m_Str2Data.GB2312ToUnicode(m_SlaveStation[i][j].WatchName,buf);
                		else if(col==1)
						{
	        				  int nstatus = m_ADRecord[i][j][k].duant;
			        		  if(nstatus == 0)
			        			  strtime= m_SlaveStation[i][j].ZeroState;
				         	  else if(nstatus == 1)
			         			  strtime= m_SlaveStation[i][j].OneState;
		        			  else if(nstatus == 2)
		        				  strtime= m_SlaveStation[i][j].TwoState;
//                             m_Str2Data.GB2312ToUnicode("1" ,buf);
						}
                		else if(col==2)
						{//�ۼƱ������ϵ�ʱ��(���ջ򱾰��ۼƱ������ϵ�ʱ��)
							COleDateTimeSpan t = m_ADRecord[i][j][299].tmid;
			            	strtime.Format("%d %d:%d:%d",t.GetDays(),t.GetHours(),t.GetMinutes(),t.GetSeconds()); 
//                            m_Str2Data.GB2312ToUnicode(strtime ,buf);
						}
                 		else if(col==3)
							//�������ϵ����(���ջ򱾰��ۼƱ������ϵ����)
				        	  strtime.Format("%d",m_ADRecord[i][j][0].m_ATotalnum);
//                          m_Str2Data.GB2312ToUnicode(m_ADRecord[i][j][k].strlocal,buf);
                 		else if(col==4)
						{//ÿ�α������ϵ�ʱ�̼����ʱ��  ÿ�α������ϵ�ʱ��
							COleDateTimeSpan t = m_ADRecord[i][j][k].tmid;
			            	strtime.Format("%d %d:%d:%d",t.GetDays(),t.GetHours(),t.GetMinutes(),t.GetSeconds()); 
		        		  strtime +="|" + m_ADRecord[i][j][k].BTime.Format(_T("%Y:%m:%d %H:%M:%S")) +"|"+ m_ADRecord[i][j][k].NTime.Format(_T("%Y:%m:%d %H:%M:%S")) ; 
//                          m_Str2Data.GB2312ToUnicode(strtime,buf);
						}
                		else if(col==5)//�ϵ�����
				        	  strtime.Format("%s",m_SlaveStation[i][j].strBS);
                 		else if(col==6)
						{//����״̬����ֹʱ�̡��ۼ�ʱ��
							strtime =m_ADRecord[i][j][k].strlocal;
							if(strtime !="")
							{
	    						COleDateTimeSpan t = m_ADRecord[i][j][k].tmid;
			            	strtime2.Format("%d %d:%d:%d",t.GetDays(),t.GetHours(),t.GetMinutes(),t.GetSeconds()); 
								strtime +="|"+strtime2;
    							int strl = strtime.GetLength();
			    				if(strl>799)
				    				strtime = strtime.Mid(0,799);
							}
//                          m_Str2Data.GB2312ToUnicode(strtime,buf);
						}
                 		else if(col==7)
							strtime =m_ADRecord[i][j][k].strsafetext;
//                          m_Str2Data.GB2312ToUnicode(m_ADRecord[i][j][k].strsafetext,buf);
//					rgMyRge.SetItem(_variant_t((long)iItem),_variant_t((long)(col+1)),_variant_t(strtime)); 
//						cell->Set(buf);
                        strDBr[col]=strtime;
						}
    	strtime.Format("INSERT INTO reportdad (R0,R1,R2,R3,R4,R5,R6,R7) VALUES('%s','%s','%s','%s','%s','%s','%s','%s')"
    		,strDBr[0],strDBr[1],strDBr[2],strDBr[3],strDBr[4],strDBr[5],strDBr[6],strDBr[7]);
     	theApp.m_pConnection->Execute(_bstr_t(strtime),NULL,adCmdText);
		            	iItem++;
					}//if
				}//k
	    	pFWnd->m_wndProgCtrl.StepIt();
			}//j
		}//i
	pFWnd->m_wndProgCtrl.SetPos (0);
	ShellExecute(0, "open", gstrTimeOut +"\\reportday.exe",m_Str2Data.CStringtocharp(strcan), 0, SW_NORMAL);
//	theApp.C_Ts.CreateP(gstrTimeOut +"\\reportday.exe", m_Str2Data.CStringtocharp(strcan),5,0x00000001);
}

void CMadeCertView::OnRECDABB() //�������ϵ�
{
}

void CMadeCertView::OnRECDFED() //�����������쳣
{
    CMainFrame* pFWnd=(CMainFrame*)AfxGetMainWnd();
	// initialize progress control.
	pFWnd->m_wndProgCtrl.SetRange (0, 3840);
	pFWnd->m_wndProgCtrl.SetPos (0);
	pFWnd->m_wndProgCtrl.SetStep (1);

		for(int i = 1; i < MAX_FDS;i++ )
			for(int j = 1; j < MAX_CHAN;j++ )
			{
				for(int h = 0; h < 300;h++)
				{
					m_ADRecord[i][j][h].m_ATotalnum = 0;
					m_ADRecord[i][j][h].ATotalV = 0;
					m_ADRecord[i][j][h].duant = 0;
					m_ADRecord[i][j][h].strlocal = "";
					m_ADRecord[i][j][h].havev = 0;
					m_ADRecord[i][j][h].tmid = 0;
					m_ADRecord[i][j][h].tmid1 = 0;
					m_ADRecord[i][j][h].AavV = 0;
					m_ADRecord[i][j][h].strsafetext = "";
					m_ADRecord[i][j][h].AMaxValue = 0;
					m_ADRecord[i][j][h].AMinValue = 666666;
				}
	    	pFWnd->m_wndProgCtrl.StepIt();
			}
	CString strtime,strtime2;
	if(b_twodb)
	{
		while ( !pRS1->EndOfFile)
		{
				int afds = pRS1->Fields->Item["ffds"]->Value.lVal;
				int achan = pRS1->Fields->Item["fchan"]->Value.lVal;
				COleDateTime dt(pRS1->Fields->Item["recdate"]->Value);
//				int afds = m_Realtimedata1.m_szffds;
//				int achan = m_Realtimedata1.m_szfchan;
	   		int dbp = mPoint[pRS1->Fields->Item["PID"]->Value.lVal];
//             if(dbp != 6666)
			 {
            	_bstr_t Explain =pRS1->Fields->Item["FeedStatus"]->Value;
				strtime.Format("%s",(char *)Explain);
    			strtime.TrimRight();
			if(strtime == "�쳣")
			{
				if(m_ADRecord[afds][achan][1].m_ATotalnum == 0)//��һ�������쳣ʱ��
					m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].BTime =dt;

               	 Explain =pRS1->Fields->Item["safemtext"]->Value;
				strtime.Format("%s",(char *)Explain);
					strtime.TrimRight();
					if(strtime != "")
					{//ÿ�δ�ʩ����ȡ��ʩʱ��
		        		  strtime2   =   dt.Format(_T("%Y-%m-%d %H:%M:%S")); 
	       	    		m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].strsafetext += strtime+"|"+strtime2+"|";
					}
				m_ADRecord[afds][achan][1].m_ATotalnum++;//n�������쳣��¼
			}
			else if(strtime == "����")
			{
				if(m_ADRecord[afds][achan][1].m_ATotalnum> 0)
				{//����ʱ�� ������1 �´γ�ʼ��  ÿ�������쳣ʱ��
	    			m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].NTime =dt;
					m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].tmid =dt-m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].BTime;
					//�ۼ������쳣ʱ��(���ջ򱾰��ۼ������쳣ʱ��)
//					m_ADRecord[afds][achan][299].tmid +=m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].tmid;
					//�����쳣����(���ջ򱾰��ۼ������쳣����)
	     			m_ADRecord[afds][achan][0].m_ATotalnum++;  //�������쳣����
	     			m_ADRecord[afds][achan][1].m_ATotalnum = 0;  //״̬ת��
				}
			}
			 }
            	m_ADRecord[afds][achan][0].ATime = dt;
			pRS1->MoveNext();
		}
	}
//	if(!m_Realtimedata._IsEmpty())
	{
		while ( !theApp.pRS->EndOfFile)
		{
				int afds = theApp.pRS->Fields->Item["ffds"]->Value.lVal;
				int achan = theApp.pRS->Fields->Item["fchan"]->Value.lVal;
			COleDateTime dt(theApp.pRS->Fields->Item["recdate"]->Value);
//				int afds = m_Realtimedata.m_szffds;
//				int achan = m_Realtimedata.m_szfchan;
	   		int dbp = mPoint[theApp.pRS->Fields->Item["PID"]->Value.lVal];
//             if(dbp != 6666)
			 {
            	_bstr_t Explain =theApp.pRS->Fields->Item["FeedStatus"]->Value;
				strtime.Format("%s",(char *)Explain);
    			strtime.TrimRight();
			if(strtime == "�쳣")
			{
				if(m_ADRecord[afds][achan][1].m_ATotalnum == 0)//��һ�������쳣ʱ��
					m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].BTime =dt;

                	 Explain =theApp.pRS->Fields->Item["safemtext"]->Value;
    				strtime.Format("%s",(char *)Explain);
					strtime.TrimRight();
					if(strtime != "")
					{//ÿ�δ�ʩ����ȡ��ʩʱ��
		        		  strtime2   =   dt.Format(_T("%Y-%m-%d %H:%M:%S")); 
	       	    		m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].strsafetext += strtime+"|"+strtime2+"|";
					}
				m_ADRecord[afds][achan][1].m_ATotalnum++;//n�������쳣��¼
			}
			else if(strtime == "����")
			{
				if(m_ADRecord[afds][achan][1].m_ATotalnum> 0)
				{//����ʱ�� ������1 �´γ�ʼ��  ÿ�������쳣ʱ��
	    			m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].NTime =dt;
					m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].tmid =dt-m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].BTime;
					//�ۼ������쳣ʱ��(���ջ򱾰��ۼ������쳣ʱ��)
//					m_ADRecord[afds][achan][299].tmid +=m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].tmid;
					//�����쳣����(���ջ򱾰��ۼ������쳣����)
	     			m_ADRecord[afds][achan][0].m_ATotalnum++;  //�������쳣����
	     			m_ADRecord[afds][achan][1].m_ATotalnum = 0;  //״̬ת��
				}
			}
			 }
            	m_ADRecord[afds][achan][0].ATime = dt;
			theApp.pRS->MoveNext();
		}
	}
		for( i = 1; i < MAX_FDS;i++ )
			for(int j = 1; j < MAX_CHAN;j++ )
			{
				if(m_ADRecord[i][j][1].m_ATotalnum> 0)//�������쳣
				{
	    			m_ADRecord[i][j][m_ADRecord[i][j][0].m_ATotalnum].NTime =m_ADRecord[i][j][0].ATime;
					m_ADRecord[i][j][m_ADRecord[i][j][0].m_ATotalnum].tmid =m_ADRecord[i][j][0].ATime-m_ADRecord[i][j][m_ADRecord[i][j][0].m_ATotalnum].BTime;
					//�ۼ������쳣ʱ��(���ջ򱾰��ۼ������쳣ʱ��)
//					m_ADRecord[i][j][299].tmid +=m_ADRecord[i][j][m_ADRecord[i][j][0].m_ATotalnum].tmid;
					//�����쳣����(���ջ򱾰��ۼ������쳣����)
	     			m_ADRecord[i][j][0].m_ATotalnum++;  //�������쳣����
	     			m_ADRecord[i][j][1].m_ATotalnum = 0;  //״̬ת��
				}
	    	pFWnd->m_wndProgCtrl.StepIt();
			}

		for ( i = 1; i < MAX_FDS;i++)
		{
			for(int j = 1; j < 17;j++ )
			{
         		int m_fen=0;
	   	    	int dbp = mPoint[m_SlaveStation[i][j].m_PID];
                if(dbp != 6666)
				{
                 	for(int h= 0 ;h<64 ; h++)
					{
            		     int cfds = m_ADCbreakE[i][j][h].bFSd;
            			 int cchan = m_ADCbreakE[i][j][h].bchanel;
            			 if(cfds == 0)
	            			 break;
            			 for(int m= 0 ;m<64 ; m++)
						 {
    	            	     int ffds = m_CFeed[cfds][cchan][m].bFSd;//������
	                		 int fchan = m_CFeed[cfds][cchan][m].bchanel;
		            		 if(ffds == 0)
	 	            			 break;
               	    		for(int k = 0; k < m_ADRecord[ffds][fchan][0].m_ATotalnum;k++ )
							{
								m_ADRecord[i][j][m_fen].ATime =m_ADRecord[ffds][fchan][k].BTime;
								m_ADRecord[i][j][m_fen].RTime =m_ADRecord[ffds][fchan][k].NTime;
								m_ADRecord[i][j][m_fen].tmid1 =m_ADRecord[ffds][fchan][k].tmid;
								m_ADRecord[i][j][m_fen].strlocal =m_ADRecord[ffds][fchan][k].strsafetext;
								m_ADRecord[i][j][299].tmid += m_ADRecord[ffds][fchan][k].tmid;
								m_fen++;
							}
							m_ADRecord[i][j][299].m_ATotalnum += m_ADRecord[ffds][fchan][0].m_ATotalnum;
						 }//for(int m= 0 ;m<64 ; m++)
					}//for(int h= 0 ;h<64 ; h++)
				}//if(dbp != 6666)
			}//for(int j = 1; j < 17;j++ )
		}//for ( i = 1; i < MAX_FDS;i++)
    if (b_twodb)
	{
		b_twodb = FALSE;
      	pRS1->Close();
	}
    theApp.pRS->Close();

	CString strtime1,strtime3,strtime4,stnames,strcan;
		strcan ="7,"+t.Format(_T("%Y-%m-%d,%H:%M:%S"))+","+t1.Format(_T("%Y-%m-%d,%H:%M:%S"));
		strtime = "��ʼ����:"+t.Format(_T("%Y-%m-%d %H:%M:%S")); 
		strtime1 = "��ֹ����:"+ t1.Format(_T("%Y-%m-%d %H:%M:%S")); 
		int m_hours = (t1.GetTime()-t.GetTime()+1)/3600;
		strtime2.Format("%d",m_hours); 
		strtime2 = "ʱ����:" +strtime2+"Сʱ";
		strtime3 = "��ӡʱ��:" + CTime::GetCurrentTime().Format(_T("%Y-%m-%d %H:%M:%S"));
		if(m_hours >20)
	     	strtime4 = t1.Format(_T("%Y-%m-%d"))+"�ձ���:";
		else
	     	strtime4 = t1.Format(_T("%Y-%m-%d"))+ "�౨��:";

		if(theApp.strargc == "OnEXCELDFE")
		{
			if(m_hours >20)
				stnames = "�����������쳣�ձ���";
			else
				stnames = "�����������쳣�౨��";
		}
		else
				stnames = "�����������쳣��¼��ѯ��ʾ";

		strtime += "    "+strtime1+"     "+strtime2;
    	strtime = "TRUNCATE TABLE reportdfd";
    	try{
    		theApp.m_pConnection->Execute(_bstr_t(strtime),NULL,adCmdText);  }
    	catch(_com_error e){
    		AfxMessageBox(e.ErrorMessage()); }
	CString strDBr[16];
	CTime t = CTime::GetCurrentTime();
	int t_curse = t.GetTime();

	size_t col = 0;
		int iItem = 3;
		for ( i = 1; i < MAX_FDS;i++)
		{
			for(int j = 1; j < 17;j++ )
			{
	   	    	int dbp = mPoint[m_SlaveStation[i][j].m_PID];
                if(dbp != 6666)
				{
				for(int k = 0; k < m_ADRecord[i][j][299].m_ATotalnum;k++ )
				{
					{
                       	for(col=0; col<6; col++) {
							strtime="";
//                		BasicExcelCell* cell = sheet->Cell(iItem, col);
                		if(col==0)
							strtime =m_SlaveStation[i][j].WatchName+"|"+m_SlaveStation[i][j].strPN;
//                             m_Str2Data.GB2312ToUnicode(m_SlaveStation[i][j].WatchName,buf);
                		else if(col==1)
				        	  strtime.Format("%s",m_SlaveStation[i][j].strBS);
                		else if(col==2)
							//�����쳣����(���ջ򱾰��ۼƶϵ����)
				        	  strtime.Format("%d",m_ADRecord[i][j][299].m_ATotalnum);
//                             m_Str2Data.GB2312ToUnicode("1" ,buf);
                		else if(col==3)
						{//�ۼ������쳣ʱ��(���ջ򱾰��ۼ������쳣ʱ��)
							COleDateTimeSpan t = m_ADRecord[i][j][299].tmid;
			            	strtime.Format("%d %d:%d:%d",t.GetDays(),t.GetHours(),t.GetMinutes(),t.GetSeconds()); 
//                            m_Str2Data.GB2312ToUnicode(strtime ,buf);
						}
                 		else if(col==4)//ÿ������״̬ÿ���ۼ�ʱ�估��ֹʱ��
						{
						  COleDateTimeSpan t = m_ADRecord[i][j][k].tmid1;
			            	strtime.Format("�쳣|%d %d:%d:%d",t.GetDays(),t.GetHours(),t.GetMinutes(),t.GetSeconds()); 
		        		  strtime +="|"+m_ADRecord[i][j][k].ATime.Format(_T("%Y:%m:%d %H:%M:%S")) +"|"+ m_ADRecord[i][j][k].RTime.Format(_T("%Y:%m:%d %H:%M:%S")) ; 
//                          m_Str2Data.GB2312ToUnicode(strtime,buf);
						}
                 		else if(col==5)
						{
							strtime =m_ADRecord[i][j][k].strlocal;
//                          m_Str2Data.GB2312ToUnicode(strtime,buf);
						}
//					rgMyRge.SetItem(_variant_t((long)iItem),_variant_t((long)(col+1)),_variant_t(strtime)); 
//						cell->Set(buf);
                        strDBr[col]=strtime;
						}
    	strtime.Format("INSERT INTO reportdfd (R0,R1,R2,R3,R4,R5) VALUES('%s','%s','%s','%s','%s','%s')"
    		,strDBr[0],strDBr[1],strDBr[2],strDBr[3],strDBr[4],strDBr[5]);
     	theApp.m_pConnection->Execute(_bstr_t(strtime),NULL,adCmdText);
		            	iItem++;
					}//if
				}//k
				}
	    	pFWnd->m_wndProgCtrl.StepIt();
			}//j
		}//i
	pFWnd->m_wndProgCtrl.SetPos (0);
	ShellExecute(0, "open", gstrTimeOut +"\\reportday.exe",m_Str2Data.CStringtocharp(strcan), 0, SW_NORMAL);
//	theApp.C_Ts.CreateP(gstrTimeOut +"\\reportday.exe", m_Str2Data.CStringtocharp(strcan),5,0x00000001);
}

void CMadeCertView::OnRECDSCD() //������״̬�䶯��¼
{
    CMainFrame* pFWnd=(CMainFrame*)AfxGetMainWnd();
	// initialize progress control.
	pFWnd->m_wndProgCtrl.SetRange (0, 3840);
	pFWnd->m_wndProgCtrl.SetPos (0);
	pFWnd->m_wndProgCtrl.SetStep (1);

		for(int i = 1; i < MAX_FDS;i++ )
			for(int j = 0; j < MAX_CHAN;j++ )
			{
				for(int h = 0; h < 300;h++)
				{
					m_ADRecord[i][j][h].m_ATotalnum = 0;
					m_ADRecord[i][j][h].ATotalV = 0;
					m_ADRecord[i][j][h].duant = 6;
					m_ADRecord[i][j][h].strlocal = "";
					m_ADRecord[i][j][h].havev = 0;
					m_ADRecord[i][j][h].tmid = 0;
					m_ADRecord[i][j][h].AavV = 0;
					m_ADRecord[i][j][h].strsafetext = "";
					m_ADRecord[i][j][h].AMaxValue = 0;
					m_ADRecord[i][j][h].AMinValue = 666666;
				}
	    	pFWnd->m_wndProgCtrl.StepIt();
			}
	if(b_twodb)
	{
		while ( !pRS1->EndOfFile)
		{
				int afds = pRS1->Fields->Item["fds"]->Value.lVal;
				int achan = pRS1->Fields->Item["chan"]->Value.lVal;
    			int nstatus = pRS1->Fields->Item["CDValue"]->Value.lVal;
				COleDateTime dt(pRS1->Fields->Item["recdate"]->Value);
	   		int dbp = mPoint[pRS1->Fields->Item["PID"]->Value.lVal];
             if(dbp != 6666)
			 {
    	    		if(nstatus == 1)
					{
     		    		if(m_ADRecord[afds][achan][1].m_ATotalnum == 0)//��һ��״̬�䶯ʱ��
				        	m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].BTime =dt;
				        m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].duant =nstatus;
        				m_ADRecord[afds][achan][1].m_ATotalnum++;//n��״̬�䶯
					}
	        		else if(nstatus != 1)
					{
	        			if(m_ADRecord[afds][achan][1].m_ATotalnum> 0)
						{//״̬�䶯ʱ�� ������1 �´γ�ʼ��  ÿ��״̬�䶯ʱ��
					//�ۼ�����ʱ��(���ջ򱾰��ۼ�����ʱ��)
					m_ADRecord[afds][achan][299].tmid +=dt-m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].BTime;
	     			m_ADRecord[afds][achan][0].m_ATotalnum ++;//��״̬�䶯����
					//״̬�䶯����(���ջ򱾰��ۼ�״̬�䶯����)
					//��n��״̬�䶯ʱ��
				    m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].BTime =dt;
				    m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].duant =nstatus;
	     			m_ADRecord[afds][achan][0].m_ATotalnum ++;//��״̬�䶯����
	     			m_ADRecord[afds][achan][1].m_ATotalnum = 0;  //״̬ת��
						}
					}
			 }
                 	m_ADRecord[afds][achan][0].ATime = dt;
			pRS1->MoveNext();
		}
	}
//	if(!m_Realtimedata._IsEmpty())
	{
		while ( !theApp.pRS->EndOfFile)
		{
				int afds = theApp.pRS->Fields->Item["fds"]->Value.lVal;
				int achan = theApp.pRS->Fields->Item["chan"]->Value.lVal;
    			int nstatus = theApp.pRS->Fields->Item["CDValue"]->Value.lVal;
			COleDateTime dt(theApp.pRS->Fields->Item["recdate"]->Value);
	   		int dbp = mPoint[theApp.pRS->Fields->Item["PID"]->Value.lVal];
             if(dbp != 6666)
			 {
                	if(nstatus == 1)
					{
     		        	if(m_ADRecord[afds][achan][1].m_ATotalnum == 0)//��һ��״̬�䶯ʱ��
						{
				        	m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].BTime =dt;
    				        m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].duant =nstatus;
            				m_ADRecord[afds][achan][1].m_ATotalnum++;//n��״̬�䶯
						}
					}
	        		else if(nstatus != 1)
					{
	        			if(m_ADRecord[afds][achan][1].m_ATotalnum> 0)
						{//״̬�䶯ʱ�� ������1 �´γ�ʼ��  ÿ��״̬�䶯ʱ��
					//�ۼ�����ʱ��(���ջ򱾰��ۼ�����ʱ��)
					m_ADRecord[afds][achan][299].tmid +=dt-m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].BTime;
	            	m_ADRecord[afds][achan][0].m_ATotalnum ++;//��״̬�䶯����
					//״̬�䶯����(���ջ򱾰��ۼ�״̬�䶯����)
					//��n��״̬�䶯ʱ��
				    m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].BTime =dt;
				    m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].duant =nstatus;
	     			m_ADRecord[afds][achan][0].m_ATotalnum ++;//��״̬�䶯����
	     			m_ADRecord[afds][achan][1].m_ATotalnum = 0;  //״̬ת��
						}
					}
			 }
                 	m_ADRecord[afds][achan][0].ATime = dt;
			theApp.pRS->MoveNext();
		}
	}
		for( i = 1; i < MAX_FDS;i++ )
			for(int j = 0; j < MAX_CHAN;j++ )
			{
				if(m_ADRecord[i][j][1].m_ATotalnum> 0)//��״̬ת��
					//�ۼ�����ʱ��(���ջ򱾰��ۼ�����ʱ��)
					m_ADRecord[i][j][299].tmid +=m_ADRecord[i][j][0].ATime-m_ADRecord[i][j][m_ADRecord[i][j][0].m_ATotalnum].BTime;
	    	pFWnd->m_wndProgCtrl.StepIt();
			}
    if (b_twodb)
	{
		b_twodb = FALSE;
      	pRS1->Close();
	}
    theApp.pRS->Close();

	CString strtime,strtime1,stnames;
	CString strtime2,strtime3,strtime4;
	CString strcan;
		strcan ="8,"+t.Format(_T("%Y-%m-%d,%H:%M:%S"))+","+t1.Format(_T("%Y-%m-%d,%H:%M:%S"));
		strtime = "��ʼ����:"+t.Format(_T("%Y-%m-%d %H:%M:%S")); 
		strtime1 = "��ֹ����:"+ t1.Format(_T("%Y-%m-%d %H:%M:%S")); 
		int m_hours = (t1.GetTime()-t.GetTime()+1)/3600;
		strtime2.Format("%d",m_hours); 
		strtime2 = "ʱ����:" +strtime2+"Сʱ";
		strtime3 = "��ӡʱ��:" + CTime::GetCurrentTime().Format(_T("%Y-%m-%d %H:%M:%S"));
		if(m_hours >20)
	     	strtime4 = t1.Format(_T("%Y-%m-%d"))+"�ձ���:";
		else
	     	strtime4 = t1.Format(_T("%Y-%m-%d"))+ "�౨��:";

//		BasicExcelCell* cell = sheet->Cell(0, 2);
		if(theApp.strargc == "OnEXCELDSCD")
		{
			if(m_hours >20)
				stnames = "������״̬�䶯�ձ���";
//             m_Str2Data.GB2312ToUnicode("������״̬�䶯�ձ���" ,buf);
			else
				stnames = "������״̬�䶯�౨��";
//             m_Str2Data.GB2312ToUnicode("������״̬�䶯�౨��" ,buf);
		}
		else
				stnames = "������״̬�䶯��¼��ѯ��ʾ";
//             m_Str2Data.GB2312ToUnicode("������״̬�䶯��¼��ѯ��ʾ" ,buf);
//		cell->Set(buf);
//		cell->SetFormat(fmt);

//        cell = sheet->Cell(1, 1);
		strtime += "    "+strtime1+"    "+strtime2;
//             m_Str2Data.GB2312ToUnicode(strtime ,buf);
//		cell->Set(buf);
//		cell->SetFormat(fmt_bold);
    	strtime = "TRUNCATE TABLE reportdsd";
    	try{
    		theApp.m_pConnection->Execute(_bstr_t(strtime),NULL,adCmdText);  }
    	catch(_com_error e){
    		AfxMessageBox(e.ErrorMessage()); }
	CString strDBr[16];
	CTime t = CTime::GetCurrentTime();
	int t_curse = t.GetTime();

	size_t col = 0;
		int iItem = 3;
		for ( i = 1; i < MAX_FDS;i++)
		{
			for(int j = 0; j < MAX_CHAN;j++ )
			{
				if(m_SlaveStation[i][j].ptype >3)
				{
     			for(int k = 0; k < 300;k++ )
				{
					if( m_ADRecord[i][j][k].duant == 6)
						break;

                	for(col=0; col<4; col++) {
						strtime ="";
//              		BasicExcelCell* cell = sheet->Cell(iItem, col);
         	      	if(col==0)
//					rgMyRge.SetItem(_variant_t((long)iItem),_variant_t((long)(col+1)),_variant_t(m_SlaveStation[i][j].WatchName)); 
//                      m_Str2Data.GB2312ToUnicode(m_SlaveStation[i][j].WatchName,buf);
							strtime =m_SlaveStation[i][j].WatchName+"|"+m_SlaveStation[i][j].strPN;
                 	else if(col==1)
					{
//					rgMyRge.SetItem(_variant_t((long)iItem),_variant_t((long)(col+1)),_variant_t("1")); 
							COleDateTimeSpan t = m_ADRecord[i][j][299].tmid;
			            	strtime.Format("%d %d:%d:%d",t.GetDays(),t.GetHours(),t.GetMinutes(),t.GetSeconds()); 
					}
//                      m_Str2Data.GB2312ToUnicode("1" ,buf);
         	      	else if(col==2)
					{
				        	strtime.Format("%d",m_ADRecord[i][j][0].m_ATotalnum+1);
//                      m_Str2Data.GB2312ToUnicode(strtime ,buf);
//					rgMyRge.SetItem(_variant_t((long)iItem),_variant_t((long)(col+1)),_variant_t(strtime)); 
					}
         	      	else if(col==3)
					{
					  int nstatus = m_ADRecord[i][j][k].duant;
					  if(nstatus == 0)
						  strtime= m_SlaveStation[i][j].ZeroState;
					  else if(nstatus == 1)
						  strtime= m_SlaveStation[i][j].OneState;
		        	  else if(nstatus == 2)
		        		  strtime= m_SlaveStation[i][j].TwoState;
			     	  COleDateTime oleDateTime=m_ADRecord[i][j][k].BTime;
			    	  strtime   +="|" + oleDateTime.Format(_T("%Y:%m:%d %H:%M:%S")); 
//                      m_Str2Data.GB2312ToUnicode(strtime,buf);
//					rgMyRge.SetItem(_variant_t((long)iItem),_variant_t((long)(col+1)),_variant_t(strtime)); 
					}
//                                m_Str2Data.GB2312ToUnicode(strtime ,buf);
//					rgMyRge.SetItem(_variant_t((long)(iItem-1)),_variant_t((long)(col+1)),_variant_t(strtime)); 
                        strDBr[col]=strtime;
					}//for(col=0; col<4; 
//            		cell->Set(buf);
    	strtime.Format("INSERT INTO reportdsd (R0,R1,R2,R3) VALUES('%s','%s','%s','%s')"
    		,strDBr[0],strDBr[1],strDBr[2],strDBr[3]);
     	theApp.m_pConnection->Execute(_bstr_t(strtime),NULL,adCmdText);
	           		iItem++;
				}//for(int k = 1; k < 300;k++
				}//if(m_SlaveStation[i][j].ptype >3)
	    	pFWnd->m_wndProgCtrl.StepIt();
			}
		}
	pFWnd->m_wndProgCtrl.SetPos (0);
//	}
	ShellExecute(0, "open", gstrTimeOut +"\\reportday.exe",m_Str2Data.CStringtocharp(strcan), 0, SW_NORMAL);
//	theApp.C_Ts.CreateP(gstrTimeOut +"\\reportday.exe", m_Str2Data.CStringtocharp(strcan),5,0x00000001);
}

void CMadeCertView::OnRECDRIVERE()   //�豸���ϼ�¼
{
    CMainFrame* pFWnd=(CMainFrame*)AfxGetMainWnd();
	// initialize progress control.
	pFWnd->m_wndProgCtrl.SetRange (0, 3840);
	pFWnd->m_wndProgCtrl.SetPos (0);
	pFWnd->m_wndProgCtrl.SetStep (1);

	for(int i = 1; i < MAX_FDS;i++ )
			for(int j = 0; j < MAX_CHAN;j++ )
			{
				for(int h = 0; h < 300;h++)
				{
					m_ADRecord[i][j][h].m_ATotalnum = 0;
					m_ADRecord[i][j][h].ATotalV = 0;
					m_ADRecord[i][j][h].duant = 0;
					m_ADRecord[i][j][h].strlocal = "";
					m_ADRecord[i][j][h].havev = 0;
					m_ADRecord[i][j][h].tmid = 0;
					m_ADRecord[i][j][h].AavV = 0;
					m_ADRecord[i][j][h].strsafetext = "";
					m_ADRecord[i][j][h].AMaxValue = 0;
					m_ADRecord[i][j][h].AMinValue = 666666;
				}
	    	pFWnd->m_wndProgCtrl.StepIt();
			}
	CString strtime,strtime2;
	if(b_twodb)
	{
		while ( !pRS1->EndOfFile)
		{
				int afds = pRS1->Fields->Item["fds"]->Value.lVal;
				int achan = pRS1->Fields->Item["chan"]->Value.lVal;
    			int m_alarm = pRS1->Fields->Item["ADStatus"]->Value.lVal;
				COleDateTime dt(pRS1->Fields->Item["recdate"]->Value);
	   		int dbp = mPoint[pRS1->Fields->Item["PID"]->Value.lVal];
             if(dbp != 6666)
			 {
			if(m_alarm > 47)
			{
				if(m_ADRecord[afds][achan][1].m_ATotalnum == 0)//��һ�ι���ʱ��
					m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].BTime =dt;

					//״̬
			    	m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].duant =dt;
                 	_bstr_t Explain =pRS1->Fields->Item["safemtext"]->Value;
	    			strtime.Format("%s",(char *)Explain);
					strtime.TrimRight();
					if(strtime != "")
					{//ÿ�δ�ʩ����ȡ��ʩʱ��
		        		  strtime2   =   dt.Format(_T("%Y-%m-%d %H:%M:%S")); 
	       	    		m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].strsafetext += strtime+"|"+strtime2+"|";
					}
		    		m_ADRecord[afds][achan][1].m_ATotalnum++;//n������ֵ
			}
			else if(m_alarm < 48)
			{
				if(m_ADRecord[afds][achan][1].m_ATotalnum> 0)
				{//����ʱ�� ������1 �´γ�ʼ��  ÿ�ι���ʱ��
	    			m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].NTime =dt;
					m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].tmid =dt-m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].BTime;
					//�ۼƹ���ʱ��(���ջ򱾰��ۼƹ���ʱ��)
					m_ADRecord[afds][achan][299].tmid +=m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].tmid;
					//���ϴ���(���ջ򱾰��ۼƹ��ϴ���)
	     			m_ADRecord[afds][achan][0].m_ATotalnum++;  //�ܹ��ϴ���
	     			m_ADRecord[afds][achan][1].m_ATotalnum = 0;  //״̬ת��
				}
			}
			 }
            	m_ADRecord[afds][achan][0].ATime = dt;
			pRS1->MoveNext();
		}
	}
//	if(!m_Realtimedata._IsEmpty())
	{
		while ( !theApp.pRS->EndOfFile)
		{
				int afds = theApp.pRS->Fields->Item["fds"]->Value.lVal;
				int achan = theApp.pRS->Fields->Item["chan"]->Value.lVal;
    			int m_alarm = theApp.pRS->Fields->Item["ADStatus"]->Value.lVal;
			COleDateTime dt(theApp.pRS->Fields->Item["recdate"]->Value);
	   		int dbp = mPoint[theApp.pRS->Fields->Item["PID"]->Value.lVal];
             if(dbp != 6666)
			 {
			if(m_alarm > 47)
			{
				if(m_ADRecord[afds][achan][1].m_ATotalnum == 0)//��һ�ι���ʱ��
					m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].BTime =dt;

					//״̬
			    	m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].duant =dt;
            	_bstr_t Explain =theApp.pRS->Fields->Item["safemtext"]->Value;
				strtime.Format("%s",(char *)Explain);
					strtime.TrimRight();
					if(strtime != "")
					{//ÿ�δ�ʩ����ȡ��ʩʱ��
		        		  strtime2   =   dt.Format(_T("%Y-%m-%d %H:%M:%S")); 
	       	    		m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].strsafetext += strtime+"|"+strtime2+"|";
					}
		    		m_ADRecord[afds][achan][1].m_ATotalnum++;//n������ֵ
			}
			else if(m_alarm < 48)
			{
				if(m_ADRecord[afds][achan][1].m_ATotalnum> 0)
				{//����ʱ�� ������1 �´γ�ʼ��  ÿ�ι���ʱ��
	    			m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].NTime =dt;
					m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].tmid =dt-m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].BTime;
					//�ۼƹ���ʱ��(���ջ򱾰��ۼƹ���ʱ��)
					m_ADRecord[afds][achan][299].tmid +=m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].tmid;
					//���ϴ���(���ջ򱾰��ۼƹ��ϴ���)
	     			m_ADRecord[afds][achan][0].m_ATotalnum++;  //�ܹ��ϴ���
	     			m_ADRecord[afds][achan][1].m_ATotalnum = 0;  //״̬ת��
				}
			}
			 }
            	m_ADRecord[afds][achan][0].ATime = dt;
			theApp.pRS->MoveNext();
		}
	}
		for( i = 1; i < MAX_FDS;i++ )
			for(int j = 0; j < MAX_CHAN;j++ )
			{
				if(m_ADRecord[i][j][1].m_ATotalnum> 0)//�й���
				{
	    			m_ADRecord[i][j][m_ADRecord[i][j][0].m_ATotalnum].NTime =m_ADRecord[i][j][0].ATime;
					m_ADRecord[i][j][m_ADRecord[i][j][0].m_ATotalnum].tmid =m_ADRecord[i][j][0].ATime-m_ADRecord[i][j][m_ADRecord[i][j][0].m_ATotalnum].BTime;
					//�ۼƹ���ʱ��(���ջ򱾰��ۼƹ���ʱ��)
					m_ADRecord[i][j][299].tmid +=m_ADRecord[i][j][m_ADRecord[i][j][0].m_ATotalnum].tmid;
					//���ϴ���(���ջ򱾰��ۼƹ��ϴ���)
	     			m_ADRecord[i][j][0].m_ATotalnum++;  //�ܹ��ϴ���
	     			m_ADRecord[i][j][1].m_ATotalnum = 0;  //״̬ת��
				}
	    	pFWnd->m_wndProgCtrl.StepIt();
			}
    if (b_twodb)
	{
		b_twodb = FALSE;
      	pRS1->Close();
	}
    theApp.pRS->Close();

	CString strtime1,strtime3,strtime4,stnames,strcan;
		strcan ="9,"+t.Format(_T("%Y-%m-%d,%H:%M:%S"))+","+t1.Format(_T("%Y-%m-%d,%H:%M:%S"));
		strtime = "��ʼ����:"+t.Format(_T("%Y-%m-%d %H:%M:%S")); 
		strtime1 = "��ֹ����:"+ t1.Format(_T("%Y-%m-%d %H:%M:%S")); 
		int m_hours = (t1.GetTime()-t.GetTime()+1)/3600;
		strtime2.Format("%d",m_hours); 
		strtime2 = "ʱ����:" +strtime2+"Сʱ";
		strtime3 = "��ӡʱ��:" + CTime::GetCurrentTime().Format(_T("%Y-%m-%d %H:%M:%S"));
		if(m_hours >20)
	     	strtime4 = t1.Format(_T("%Y-%m-%d"))+"�ձ���:";
		else
	     	strtime4 = t1.Format(_T("%Y-%m-%d"))+ "�౨��:";

//		BasicExcelCell* cell = sheet->Cell(0, 2);
		if(theApp.strargc == "OnEXCELDRIVERE")
		{
			if(m_hours >20)
				stnames = "����豸�����ձ���";
//             m_Str2Data.GB2312ToUnicode("����豸�����ձ���" ,buf);
			else
				stnames = "����豸���ϰ౨��";
//             m_Str2Data.GB2312ToUnicode("����豸���ϰ౨��" ,buf);
		}
		else
				stnames = "����豸���ϼ�¼��ѯ��ʾ";
//             m_Str2Data.GB2312ToUnicode("����豸���ϼ�¼��ѯ��ʾ" ,buf);
//		cell->Set(buf);
//		cell->SetFormat(fmt);

//        cell = sheet->Cell(1, 1);
		strtime += "    "+strtime1+"    "+strtime2;
//             m_Str2Data.GB2312ToUnicode(strtime ,buf);
//		cell->Set(buf);
//		cell->SetFormat(fmt_bold);
    	strtime = "TRUNCATE TABLE reported";
    	try{
    		theApp.m_pConnection->Execute(_bstr_t(strtime),NULL,adCmdText);  }
    	catch(_com_error e){
    		AfxMessageBox(e.ErrorMessage()); }
	CString strDBr[16];
	CTime t = CTime::GetCurrentTime();
	int t_curse = t.GetTime();

	size_t col = 0;
		int iItem = 3;
		for ( i = 1; i < MAX_FDS;i++)
		{
			for(int j = 0; j < MAX_CHAN;j++ )
			{
     			for(int k = 0; k < 300;k++ )
				{
    				if(m_ADRecord[i][j][k].duant == 0)
						break;

					    for(col=0; col<6; col++) {
							strtime="";
//                		BasicExcelCell* cell = sheet->Cell(iItem, col);
                		if(col==0)
							strtime =m_SlaveStation[i][j].WatchName+"|"+m_SlaveStation[i][j].strPN;
//                             m_Str2Data.GB2312ToUnicode(m_SlaveStation[i][j].WatchName,buf);
                		else if(col==1)//�ۼƴ���
				        	  strtime.Format("%d",m_ADRecord[i][j][0].m_ATotalnum);
//							strtime ="1" ;
//                             m_Str2Data.GB2312ToUnicode("1" ,buf);
                		else if(col==2)//�ۼ�ʱ��
						{
							COleDateTimeSpan t = m_ADRecord[i][j][299].tmid;
			            	strtime.Format("%d %d:%d:%d",t.GetDays(),t.GetHours(),t.GetMinutes(),t.GetSeconds()); 
//                            m_Str2Data.GB2312ToUnicode(strtime ,buf);
						}
                 		else if(col==3)//ÿ���ۼ�ʱ�估��ֹʱ��
						{
						  COleDateTimeSpan t = m_ADRecord[i][j][k].tmid;
			            	strtime.Format("%d %d:%d:%d",t.GetDays(),t.GetHours(),t.GetMinutes(),t.GetSeconds()); 
		        		  strtime +="|"+m_ADRecord[i][j][k].BTime.Format(_T("%Y:%m:%d %H:%M:%S")) +"|"+ m_ADRecord[i][j][k].NTime.Format(_T("%Y:%m:%d %H:%M:%S")) ; 
//                          m_Str2Data.GB2312ToUnicode(strtime,buf);
						}
                 		else if(col==4)//��ȫ��ʩ|ʱ��
						{
							strtime =m_ADRecord[i][j][k].strsafetext;
//                          m_Str2Data.GB2312ToUnicode(strtime,buf);
						}
                 		else if(col==5)//״̬
		        		  strtime   = theApp.m_RTDM.strstatus(m_ADRecord[i][j][k].duant); 
//                          m_Str2Data.GB2312ToUnicode(m_ADRecord[i][j][k].strsafetext,buf);
//					rgMyRge.SetItem(_variant_t((long)iItem),_variant_t((long)(col+1)),_variant_t(strtime)); 
//						cell->Set(buf);
                        strDBr[col]=strtime;
						}
    	strtime.Format("INSERT INTO reported (R0,R1,R2,R3,R4,R5) VALUES('%s','%s','%s','%s','%s','%s')"
    		,strDBr[0],strDBr[1],strDBr[2],strDBr[3],strDBr[4],strDBr[5]);
     	theApp.m_pConnection->Execute(_bstr_t(strtime),NULL,adCmdText);
		            	iItem++;
				}//k
	    	pFWnd->m_wndProgCtrl.StepIt();
			}//j
		}//i
	pFWnd->m_wndProgCtrl.SetPos (0);
//	ShellExecute(0, "open", gstrTimeOut +"\\report\\"+stnames + t1.Format(_T("%Y-%m-%d")) +".xls", NULL, NULL, SW_NORMAL);
	ShellExecute(0, "open", gstrTimeOut +"\\reportday.exe",m_Str2Data.CStringtocharp(strcan), 0, SW_NORMAL);
//	theApp.C_Ts.CreateP(gstrTimeOut +"\\reportday.exe", m_Str2Data.CStringtocharp(strcan),5,0x00000001);
}
//ģ������¼
void CMadeCertView::OnEXCELA() 
{
/*	int   nRange=2400;
	UINT nAvi[6] = { 0, IDC_DOWNLOAD_AVI, IDC_FIND_AVI, IDC_SYNC_AVI,
						IDC_UPDATE_AVI, IDC_WRITE_AVI };
	int nAviHeight[6] = { 0, 60, 50, 40, 40, 64 };
	CXProgressWnd wndProgress(this, _T("������������"), 
		(LPCTSTR)nAvi[4], nAviHeight[4]);
	BOOL	m_bModal = TRUE;
	if (m_bModal)
		wndProgress.GoModal(this);
	BOOL	m_bTimeLeft = FALSE;
	wndProgress.SetRange(0, nRange)
			   .EnableTimeLeft(TRUE)
			   .SetText(_T("This is a progress window...\n\n")
						_T("Try dragging it around, hitting Cancel or pressing ESC."));
*/
    CMainFrame* pFWnd=(CMainFrame*)AfxGetMainWnd();
	// initialize progress control.
	pFWnd->m_wndProgCtrl.SetRange (0, 2400);
	pFWnd->m_wndProgCtrl.SetPos (0);
	pFWnd->m_wndProgCtrl.SetStep (1);

		for(int i = 1; i < MAX_FDS;i++ )
			for(int j = 1; j < MAX_CHAN;j++ )
			{
				for(int h = 0; h < 300;h++)
				{
					m_ADRecord[i][j][h].m_ATotalnum = 0;
					m_ADRecord[i][j][h].ATotalV = 0;
					m_ADRecord[i][j][h].duant = 0;
					m_ADRecord[i][j][h].strlocal = "";
					m_ADRecord[i][j][h].havev = 0;
					m_ADRecord[i][j][h].tmid = 0;
					m_ADRecord[i][j][h].AavV = 0;
					m_ADRecord[i][j][h].strsafetext = "����";
				}
//			pFWnd->m_wndProgCtrl.SetText(_T("\n��ʼ������"));
	    	pFWnd->m_wndProgCtrl.StepIt();
			}
	CString strtime,strtime2;
	if(b_twodb)
	{
//		pRS1->MoveFirst();
		while ( !pRS1->EndOfFile)
		{
    	   		int dbp = mPoint[pRS1->Fields->Item["PID"]->Value.lVal];
             if(dbp != 6666)
			 {
				int afds = pRS1->Fields->Item["fds"]->Value.lVal;
				int achan = pRS1->Fields->Item["chan"]->Value.lVal;
				int ffds = pRS1->Fields->Item["ffds"]->Value.lVal;
				int fchan = pRS1->Fields->Item["fchan"]->Value.lVal;
    			int m_alarm = pRS1->Fields->Item["ADStatus"]->Value.lVal;
				COleDateTime dt(pRS1->Fields->Item["recdate"]->Value);
	    		if(m_alarm == 00 ||m_alarm == 16 ||m_alarm == 32)
				{//ƽ��ֵ0
			    	m_ADRecord[afds][achan][0].m_ATotalnum++;
			    	m_ADRecord[afds][achan][0].ATotalV +=pRS1->Fields->Item["AValue"]->Value.fltVal;
			    	if(m_ADRecord[afds][achan][1].ATotalV <pRS1->Fields->Item["AValue"]->Value.fltVal)
					{//���ֵ  ʱ��1
    			    	m_ADRecord[afds][achan][1].ATotalV = pRS1->Fields->Item["AValue"]->Value.fltVal;
		    	    	m_ADRecord[afds][achan][1].ATime = dt;
					}
				}
            	_bstr_t Explain =pRS1->Fields->Item["FeedStatus"]->Value;
				strtime.Format("%s",(char *)Explain);
				strtime.TrimRight();
				int ffdschan = (afds-1)*16 +achan;
    			strtime2 = m_ADRecord[ffds][fchan][ffdschan].strsafetext;//old�����쳣
				if(strtime2 != strtime)   
				{
					m_ADRecord[ffds][fchan][ffdschan].duant = 0;
			    	m_ADRecord[ffds][fchan][ffdschan].strsafetext = strtime;
	    			if(strtime == "�쳣") //�����쳣����3
					{
						m_ADRecord[ffds][fchan][ffdschan].m_ATotalnum++;
						if(m_ADRecord[afds][achan][3].m_ATotalnum<m_ADRecord[ffds][fchan][ffdschan].m_ATotalnum)
							m_ADRecord[afds][achan][3].m_ATotalnum = m_ADRecord[ffds][fchan][ffdschan].m_ATotalnum;
					}
				}
				if( "�쳣" == strtime)   //�����쳣���� �������ʱ��5
				{
						if(m_ADRecord[ffds][fchan][ffdschan].duant != 0)
    						m_ADRecord[ffds][fchan][ffdschan].tmid += dt -m_ADRecord[ffds][fchan][ffdschan].ATime;
						m_ADRecord[ffds][fchan][ffdschan].ATime = dt;
						if(m_ADRecord[afds][achan][5].tmid<m_ADRecord[ffds][fchan][ffdschan].tmid)
							m_ADRecord[afds][achan][5].tmid = m_ADRecord[ffds][fchan][ffdschan].tmid;
        				m_ADRecord[ffds][fchan][ffdschan].duant++;
				}

				int olds = m_ADRecord[afds][achan][1].duant; //��һ��״̬
     			if(m_alarm != olds)
				{
					m_ADRecord[afds][achan][1].duant =m_alarm;
					if(m_alarm ==16)//��������6
					{
						m_ADRecord[afds][achan][2].duant = 0;
						m_ADRecord[afds][achan][6].m_ATotalnum++;
//						m_ADRecord[afds][achan][2].ATime = m_Realtimedata1.m_szrecdate;
					}
//					if(olds == 16)//�������� �������ʱ��
//						m_ADRecord[afds][achan][3].tmid += m_Realtimedata1.m_szrecdate -m_ADRecord[afds][achan][2].ATime;
					if(m_alarm ==32 ||m_alarm ==64 ||m_alarm ==80 ||m_alarm ==96 ||m_alarm ==112 ||m_alarm ==128)//�ϵ����7
					{
						m_ADRecord[afds][achan][4].duant = 0;
						m_ADRecord[afds][achan][7].m_ATotalnum++;
//						m_ADRecord[afds][achan][4].ATime = m_Realtimedata1.m_szrecdate;
					}
//					if(olds == 32)//�ϵ���� �������ʱ��
//						m_ADRecord[afds][achan][5].tmid += m_Realtimedata1.m_szrecdate-m_ADRecord[afds][achan][4].ATime;
				}
					if(m_alarm ==16)//�����������ʱ��8
					{
						if(m_ADRecord[afds][achan][2].duant != 0)
    						m_ADRecord[afds][achan][8].tmid += dt -m_ADRecord[afds][achan][8].ATime;
						m_ADRecord[afds][achan][8].ATime = dt;
        				m_ADRecord[afds][achan][2].duant++;
					}
					if(m_alarm ==32 ||m_alarm ==64 ||m_alarm ==80 ||m_alarm ==96 ||m_alarm ==112 ||m_alarm ==128)//�ϵ�������ʱ��9
					{
						if(m_ADRecord[afds][achan][4].duant != 0)
    						m_ADRecord[afds][achan][9].tmid += dt-m_ADRecord[afds][achan][9].ATime;
						m_ADRecord[afds][achan][9].ATime = dt;
        				m_ADRecord[afds][achan][4].duant++;
					}

			 }//dbp != 6666
			pRS1->MoveNext();
		}
	}
//	if(!m_Realtimedata._IsEmpty())
//	if(theApp.pRS->GetEndOfFile() ==0)
	{
//		int xxx = theApp.pRS->GetRecordCount();
//		theApp.pRS->MoveFirst();
		while ( !theApp.pRS->EndOfFile)
		{
    	   	 int dbp = mPoint[theApp.pRS->Fields->Item["PID"]->Value.lVal];
             if(dbp != 6666)
			 {
				int afds = theApp.pRS->Fields->Item["fds"]->Value.lVal;
				int achan = theApp.pRS->Fields->Item["chan"]->Value.lVal;
				int ffds = theApp.pRS->Fields->Item["ffds"]->Value.lVal;
				int fchan = theApp.pRS->Fields->Item["fchan"]->Value.lVal;
    			int m_alarm = theApp.pRS->Fields->Item["ADStatus"]->Value.lVal;
				COleDateTime dt(theApp.pRS->Fields->Item["recdate"]->Value);
	    		if(m_alarm == 0 ||m_alarm == 16 ||m_alarm == 32)
				{//ƽ��ֵ10
			    	m_ADRecord[afds][achan][10].m_ATotalnum++;
			    	m_ADRecord[afds][achan][10].ATotalV +=theApp.pRS->Fields->Item["AValue"]->Value.fltVal;
			    	if(m_ADRecord[afds][achan][1].ATotalV <theApp.pRS->Fields->Item["AValue"]->Value.fltVal)
					{//���ֵ  ʱ��1
    			    	m_ADRecord[afds][achan][1].ATotalV = theApp.pRS->Fields->Item["AValue"]->Value.fltVal;
		    	    	m_ADRecord[afds][achan][1].ATime = dt;
					}
				}
            	_bstr_t Explain =theApp.pRS->Fields->Item["FeedStatus"]->Value;
				strtime.Format("%s",(char *)Explain);
				strtime.TrimRight();
				int ffdschan = (afds-1)*16 +achan;
    			strtime2 = m_ADRecord[ffds][fchan][ffdschan].strsafetext;//old�����쳣
				if(strtime2 != strtime)   
				{
					m_ADRecord[ffds][fchan][ffdschan].duant = 0;
			    		m_ADRecord[ffds][fchan][ffdschan].strsafetext = strtime;
	    			if(strtime == "�쳣") //�����쳣����12
					{
						m_ADRecord[ffds][fchan][ffdschan].m_ATotalnum++;
						if(m_ADRecord[afds][achan][12].m_ATotalnum<m_ADRecord[ffds][fchan][ffdschan].m_ATotalnum)
							m_ADRecord[afds][achan][12].m_ATotalnum = m_ADRecord[ffds][fchan][ffdschan].m_ATotalnum;
					}
				}
				if( "�쳣" == strtime)   //�����쳣���� �������ʱ��14
				{
						if(m_ADRecord[ffds][fchan][ffdschan].duant != 0)
    						m_ADRecord[ffds][fchan][ffdschan].tmid += dt -m_ADRecord[ffds][fchan][ffdschan].ATime;
						m_ADRecord[ffds][fchan][ffdschan].ATime = dt;
						if(m_ADRecord[afds][achan][14].tmid<m_ADRecord[ffds][fchan][ffdschan].tmid)
							m_ADRecord[afds][achan][14].tmid = m_ADRecord[ffds][fchan][ffdschan].tmid;
        				m_ADRecord[ffds][fchan][ffdschan].duant++;
				}

				int olds = m_ADRecord[afds][achan][7].duant; //��һ��״̬
     			if(m_alarm != olds)
				{
					m_ADRecord[afds][achan][7].duant =m_alarm;
					if(m_alarm ==16)//��������15
					{
	    				m_ADRecord[afds][achan][8].duant = 0;
						m_ADRecord[afds][achan][15].m_ATotalnum++;
					}
//					if(olds == 16)//�������� �������ʱ��
					if(m_alarm ==32 ||m_alarm ==64 ||m_alarm ==80 ||m_alarm ==96 ||m_alarm ==112 ||m_alarm ==128)//�ϵ����16
					{
    					m_ADRecord[afds][achan][9].duant = 0;
						m_ADRecord[afds][achan][16].m_ATotalnum++;
					}
//					if(olds == 32)//�ϵ���� �������ʱ��
//						m_ADRecord[afds][achan][5].tmid += m_Realtimedata.m_szrecdate-m_ADRecord[afds][achan][4].ATime;
				}
					if(m_alarm ==16)//�����������ʱ��17
					{
						if(m_ADRecord[afds][achan][8].duant != 0)
    						m_ADRecord[afds][achan][17].tmid += dt -m_ADRecord[afds][achan][17].ATime;
						m_ADRecord[afds][achan][17].ATime = dt;
        				m_ADRecord[afds][achan][8].duant++;
					}
					if(m_alarm ==32 ||m_alarm ==64 ||m_alarm ==80 ||m_alarm ==96 ||m_alarm ==112 ||m_alarm ==128)//�ϵ�������ʱ��18
					{
						if(m_ADRecord[afds][achan][9].duant != 0)
    						m_ADRecord[afds][achan][18].tmid += dt-m_ADRecord[afds][achan][18].ATime;
						m_ADRecord[afds][achan][18].ATime = dt;
        				m_ADRecord[afds][achan][9].duant++;
					}
			 }//dbp != 6666
			theApp.pRS->MoveNext();
		}
	}
//	int jjj1 = theApp.pRS->GetState();
    if (b_twodb)
	{
		b_twodb = FALSE;
      	pRS1->Close();
	}
    theApp.pRS->Close();

	CString strtime1,strtime3,strtime4,stnames,strcan;
		strcan ="1,"+t.Format(_T("%Y-%m-%d,%H:%M:%S"))+","+t1.Format(_T("%Y-%m-%d,%H:%M:%S"));
		strtime = "��ʼ����:"+t.Format(_T("%Y-%m-%d %H:%M:%S")); 
		strtime1 = "��ֹ����:"+ t1.Format(_T("%Y-%m-%d %H:%M:%S")); 
		int m_hours = (t1.GetTime()-t.GetTime()+1)/3600;
		if(theApp.strargc == "OnEXCELA")
		{
			if(m_hours >20)
				stnames = "ģ�����ձ���";
			else
				stnames = "ģ�����౨��";
		}
		else
				stnames = "ģ������¼��ѯ��ʾ";

//	BasicExcel xls;
//		USES_CONVERSION;
//		LPCTSTR lpName =A2W(stnames);
//	strtime2 =gstrTimeOut +"\\report\\" + stnames + ".xlt";
/*	const char* cxls=strtime2.GetBuffer(sizeof(strtime2));
	BasicExcel xls;//(cxls);
//	cls.Open(gstrTimeOut +"\\report\\" + stnames + ".xls");
    if (!xls.Load(cxls))
    {
        AfxMessageBox(_T("Program cannot open example.xls"));
    }
//	xls.Load(cxls);
//	xls.Load(gstrTimeOut +"\\report\\example.xls");
//	xls.New(1);
	BasicExcelWorksheet* sheet = xls.GetWorksheet((size_t)0);
	XLSFormatManager fmt_mgr(xls);

	 // Create a table containing an header row in bold and four rows below.
	ExcelFont font_bold;
	font_bold._weight = FW_BOLD; // 700
	CellFormat fmt_bold(fmt_mgr);
	fmt_bold.set_font(font_bold);

		ExcelFont font;
//		font.set_color_index(color);
		font.set_weight(500);
		font.set_height(500);
		font.set_font_name(L"Times New Roman");
		CellFormat fmt(fmt_mgr, font);*/
//    WCHAR * buf=new WCHAR[1000];

		strtime2.Format("%d",m_hours); 
		strtime2 = "ʱ����:" +strtime2+"Сʱ";
		strtime3 = "��ӡʱ��:" + CTime::GetCurrentTime().Format(_T("%Y-%m-%d %H:%M:%S"));
		if(m_hours >20)
	     	strtime4 = t1.Format(_T("%Y-%m-%d"))+"�ձ���:";
		else
	     	strtime4 = t1.Format(_T("%Y-%m-%d"))+ "�౨��:";

//		BasicExcelCell* cell = sheet->Cell(0, 2);
//        m_Str2Data.GB2312ToUnicode(stnames ,buf);
//		cell->Set(buf);
//		cell->SetFormat(fmt);

//        BasicExcelCell* cell = sheet->Cell(0, 1);
		strtime += "    "+strtime1+"     "+strtime2;
//             m_Str2Data.GB2312ToUnicode(strtime ,buf);
//		cell->Set(buf);
//		cell->SetFormat(fmt_bold);
		if(theApp.strargc == "OnEXCELA")
		{
//             cell = sheet->Cell(2, 0);
//       		strtime4 += "                                                  "+strtime3;
//             m_Str2Data.GB2312ToUnicode(strtime4 ,buf);
//       		cell->Set(buf);
		}

	size_t col = 0;
/*	for(col=0; col<10; col++) {
		BasicExcelCell* cell = sheet->Cell(3, col);
		if(col==0)
             m_Str2Data.GB2312ToUnicode("��װ�ص�|����",buf);
		else if(col==1)
             m_Str2Data.GB2312ToUnicode("ƽ��ֵ",buf);
		else if(col==2)
             m_Str2Data.GB2312ToUnicode("���ֵ",buf);
		else if(col==3)
             m_Str2Data.GB2312ToUnicode("���ֵʱ��",buf);
		else if(col==4)
             m_Str2Data.GB2312ToUnicode("��������",buf);
		else if(col==5)
             m_Str2Data.GB2312ToUnicode("�ۼƱ���ʱ��",buf);
		else if(col==6)
             m_Str2Data.GB2312ToUnicode("�ϵ����",buf);
		else if(col==7)
             m_Str2Data.GB2312ToUnicode("�ۼƶϵ�ʱ��",buf);
		else if(col==8)
             m_Str2Data.GB2312ToUnicode("�����쳣����",buf);
		else if(col==9)
             m_Str2Data.GB2312ToUnicode("�����쳣�ۼ�ʱ��",buf);
		cell->Set(buf);
		cell->SetFormat(fmt_bold);
	}*/

/*	_Application ExcelApp; 
	Workbooks wbsMyBooks; 
	_Workbook wbMyBook; 
	Worksheets wssMysheets; 
	_Worksheet wsMysheet; 
	Range rgMyRge; 
	//����Excel 2000������(����Excel) 
 	if (!ExcelApp.CreateDispatch("Excel.Application",NULL)) 
	{ 
		AfxMessageBox("����Excel����ʧ��!"); 
		return; 
	} 
	//����ģ���ļ��������ĵ� 
	wbsMyBooks.AttachDispatch(ExcelApp.GetWorkbooks(),true); 
	//CreateDirectory( str1, NULL );
//	if(!SetCurrentDirectory(str1))
//		AfxMessageBox("����template1.xlt�ļ���ʧ�� setcurrentdirectory");
	wbMyBook.AttachDispatch(wbsMyBooks.Add(_variant_t(gstrTimeOut +"\\report\\" + stnames + ".xlt"))); 
	//�õ�Worksheets 
	wssMysheets.AttachDispatch(wbMyBook.GetWorksheets(),true); 
	//�õ�sheet1 
	wsMysheet.AttachDispatch(wssMysheets.GetItem(_variant_t("sheet1")),true); 
	//�õ�ȫ��Cells����ʱ,rgMyRge��cells�ļ��� 
	rgMyRge.AttachDispatch(wsMysheet.GetCells(),true); 
	//����1��1�еĵ�Ԫ��ֵ 
	   rgMyRge.SetItem(_variant_t((long)1),_variant_t((long)2),_variant_t(strtime)); 
*/
    	strtime = "TRUNCATE TABLE reportad";
    	try{
    		theApp.m_pConnection->Execute(_bstr_t(strtime),NULL,adCmdText);  }
    	catch(_com_error e){
    		AfxMessageBox(e.ErrorMessage()); }
	CString strDBr[16];
	CTime t = CTime::GetCurrentTime();
	int t_curse = t.GetTime();

		int iItem = 3;//4
		for ( i = 1; i < MAX_FDS;i++)
		{
			for(int j = 1; j < 17;j++ )
			{
//     			for(int k = 0; k < 300;k++ )
				{
    				if(m_ADRecord[i][j][10].m_ATotalnum != 0)
					{
                    for(col=0; col<13; col++) 
					{
						strtime="";
//                		BasicExcelCell* cell = sheet->Cell(iItem, col);
                		if(col==0)
							strtime =m_SlaveStation[i][j].WatchName+"|"+m_SlaveStation[i][j].strPN;
//                             m_Str2Data.GB2312ToUnicode(m_SlaveStation[i][j].WatchName,buf);
                		else if(col==1)
							strtime =m_SlaveStation[i][j].m_Unit;
                		else if(col==2)
				        	  strtime.Format("%.2f",m_SlaveStation[i][j].AlarmValueH);
                		else if(col==3)
				        	  strtime.Format("%.2f",m_SlaveStation[i][j].Apbrk);
                		else if(col==4)
				        	  strtime.Format("%.2f",m_SlaveStation[i][j].Aprtn);
                		else if(col==5)
						{
							float m_fm = (m_ADRecord[i][j][0].ATotalV+m_ADRecord[i][j][10].ATotalV)/(m_ADRecord[i][j][0].m_ATotalnum+m_ADRecord[i][j][10].m_ATotalnum);
				        	  strtime.Format("%.2f",m_fm);
//                            m_Str2Data.GB2312ToUnicode(strtime ,buf);
						}
                		else if(col==6)
						{
				        	  strtime.Format("%.2f|",m_ADRecord[i][j][1].ATotalV);
							  strtime = strtime + m_ADRecord[i][j][1].ATime.Format(_T("%Y:%m:%d %H:%M:%S"));
//                            m_Str2Data.GB2312ToUnicode(strtime ,buf);
						}
//                 		else if(col==7)
//						{
//          				  COleDateTime oleDateTime=m_ADRecord[i][j][1].ATime;
//		        		  strtime   =   m_ADRecord[i][j][1].ATime.Format(_T("%Y:%m:%d %H:%M:%S")); 
//                          m_Str2Data.GB2312ToUnicode(strtime,buf);
//						}
                 		else if(col==7)
						{
				        	  strtime.Format("%d",m_ADRecord[i][j][6].m_ATotalnum+m_ADRecord[i][j][15].m_ATotalnum);
//                          m_Str2Data.GB2312ToUnicode(strtime,buf);
						}
                 		else if(col==8)
						{
          			    	  COleDateTimeSpan t =m_ADRecord[i][j][8].tmid +m_ADRecord[i][j][17].tmid;
			            	strtime.Format("%d %d:%d:%d",t.GetDays(),t.GetHours(),t.GetMinutes(),t.GetSeconds()); 
//                            m_Str2Data.GB2312ToUnicode(strtime,buf);
						}
                 		else if(col==9)
						{
				        	  strtime.Format("%d",m_ADRecord[i][j][7].m_ATotalnum+m_ADRecord[i][j][16].m_ATotalnum);
//                              m_Str2Data.GB2312ToUnicode(strtime,buf);
						}
                 		else if(col==10)
						{
          			    	  COleDateTimeSpan t =m_ADRecord[i][j][9].tmid +m_ADRecord[i][j][18].tmid;
			            	strtime.Format("%d %d:%d:%d",t.GetDays(),t.GetHours(),t.GetMinutes(),t.GetSeconds()); 
//                            m_Str2Data.GB2312ToUnicode(strtime,buf);
						}
						else if(col==11) 
						{
				        	  strtime.Format("%d",m_ADRecord[i][j][3].m_ATotalnum+m_ADRecord[i][j][12].m_ATotalnum);
//                          m_Str2Data.GB2312ToUnicode(strtime,buf);
						}
                 		else if(col==12)
						{
							COleDateTimeSpan t=0;
          			    	t =m_ADRecord[i][j][5].tmid +m_ADRecord[i][j][14].tmid;
			            	strtime.Format("%d %d:%d:%d",t.GetDays(),t.GetHours(),t.GetMinutes(),t.GetSeconds()); 
//                            m_Str2Data.GB2312ToUnicode(strtime,buf);
						}
//					rgMyRge.SetItem(_variant_t((long)iItem),_variant_t((long)(col+1)),_variant_t(strtime)); 
//						cell->Set(buf);
                        strDBr[col]=strtime;
					}
    	strtime.Format("INSERT INTO reportad (R0,R1,R2,R3,R4,R5,R6,R7,R8,R9,R10,R11,R12) VALUES('%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s')"
    		,strDBr[0],strDBr[1],strDBr[2],strDBr[3],strDBr[4],strDBr[5],strDBr[6],strDBr[7],strDBr[8],strDBr[9],strDBr[10],strDBr[11],strDBr[12]);
     	theApp.m_pConnection->Execute(_bstr_t(strtime),NULL,adCmdText);
	             	iItem++;
					}
				}//k
//			wndProgress.SetText(_T("\n�����ݿ�"));
	    	pFWnd->m_wndProgCtrl.StepIt();
			}//j
		}//i
	pFWnd->m_wndProgCtrl.SetPos (0);

/*		if(theApp.strargc == "OnEXCELA")
		{
            cell = sheet->Cell(iItem+1, 0);
    		strtime = m_CommonStr[1].strc[6]+ "      "+m_CommonStr[1].strc[7]+ "      "+m_CommonStr[1].strc[8]+ "      "+m_CommonStr[1].strc[9]+ "      "+m_CommonStr[1].strc[10]+ "      ";
             m_Str2Data.GB2312ToUnicode(strtime ,buf);
    		cell->Set(buf);
    		cell->SetFormat(fmt_bold);
		}*/

	//rgMyRge.SetItem(_variant_t((long)2),_variant_t((long)1),_variant_t("����ΰ")); 
	//rgMyRge.SetItem(_variant_t((long)20),_variant_t((long)3),_variant_t("ewerwr")); 
	//�õ����е��� 
/*	rgMyRge.AttachDispatch(wsMysheet.GetColumns(),true); 
	//�õ���һ�� 
	for(int iCollum=1;iCollum<=9;iCollum++)
	{
		int iWidth;
		if(iCollum==5)
			iWidth=20;
		else
			iWidth=10;
		rgMyRge.AttachDispatch(rgMyRge.GetItem(_variant_t((long)iCollum),vtMissing).pdispVal,true); 
		//�����п� 
		rgMyRge.SetColumnWidth(_variant_t((long)iWidth)); 
	}
*/
	/*
	//����ģ����Ԥ�ȴ�ŵĺ� 
	ExcelApp.Run(_variant_t("CopyRow"),_variant_t((long)10),vtMissing,vtMissing, 
	vtMissing,vtMissing,vtMissing,vtMissing,vtMissing,vtMissing,vtMissing, 
	vtMissing,vtMissing,vtMissing,vtMissing,vtMissing,vtMissing,vtMissing, 
	vtMissing,vtMissing,vtMissing,vtMissing,vtMissing,vtMissing,vtMissing, 
	vtMissing,vtMissing,vtMissing,vtMissing,vtMissing,vtMissing); 
	*/
	  //��ӡԤ�� 
//	wbMyBook.SetSaved(true); 
//	ExcelApp.SetVisible(true); 
	//wbMyBook.PrintPreview(_variant_t(false)); 
	//����Ϊ�ļ�
/*	ExcelApp.SetDisplayAlerts(FALSE);   //���ص����ĶԻ���
	wsMysheet.SaveAs(gstrTimeOut +"\\report\\" + stnames +t1.Format(_T("%Y-%m-%d"))+ ".xls",vtMissing,vtMissing,COleVariant("123"),vtMissing,
//	wsMysheet.SaveAs(gstrTimeOut +"\\report\\" + stnames +t1.Format(_T("%Y-%m-%d"))+ ".xls",vtMissing,vtMissing,vtMissing,vtMissing,
		vtMissing,vtMissing,vtMissing,vtMissing,vtMissing);   
    ExcelApp.Quit();
	//�ͷŶ��� 
	rgMyRge.ReleaseDispatch(); 
	wsMysheet.ReleaseDispatch(); 
	wssMysheets.ReleaseDispatch(); 
	wbMyBook.ReleaseDispatch(); 
	wbsMyBooks.ReleaseDispatch(); 
	ExcelApp.ReleaseDispatch(); 
	ShellExecute(0, "open", gstrTimeOut +"\\report\\"+stnames + t1.Format(_T("%Y-%m-%d")) +".xls",NULL, NULL, SW_NORMAL);
*/
	//book.AttachDispatch(books.Open(ExtPath, covOptional,covOptional, covOptional,
//COleVariant("123456"),covOptional, covOptional,covOptional, covOptional, 
//covOptional, covOptional, covOptional, covOptional, covOptional, covOptional));
//    delete [] buf;
//	xls.Save();
//	xls.SaveAs(gstrTimeOut +"\\report\\example.xls");
//	xls.SaveAs(gstrTimeOut +"\\report\\"+stnames+".xls");
//	xls.Close();
//	copy_sheet(gstrTimeOut +"\\report\\example.xls",gstrTimeOut +"\\report\\"+stnames+".xls");
//	ShellExecute(0, NULL, gstrTimeOut +"\\report\\sexample.xls", NULL, NULL, SW_NORMAL);
//	theApp.C_Ts.CreateP(gstrTimeOut +"\\reportday.exe", m_Str2Data.CStringtocharp(strcan),5,0x00000001);
	ShellExecute(0, "open", gstrTimeOut +"\\reportday.exe",m_Str2Data.CStringtocharp(strcan), 0, SW_NORMAL);

}

void CMadeCertView::copy_sheet(const char* from, const char* to)
{
	BasicExcel xls;
	xls.Load(from);
	xls.SaveAs(to);
}

void CMadeCertView::ACALRecord()
{
}

void CMadeCertView::OnButtonViewinfo() 
{
	// TODO: Add your control notification handler code here
	if(m_select==-1) return;
//	CViewInfoDlg dlg;
//	dlg.DoModal();

}

void CMadeCertView::OnClickListMade(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
/*	m_select=m_List.GetSelectionMark();
	if(m_select==-1) return;
	m_List.SetItemState(m_select,LVIS_SELECTED,LVIS_SELECTED);
	m_List.SetFocus();
	m_num=m_List.GetItemText(m_select,0);//�ڲ����*/

//	*pResult = 0;
}

void CMadeCertView::OnDestroy() 
{
//    if ( m_Realtimedata._IsOpen() )
//      m_Realtimedata.Close();
//    if ( m_Realtimedata1._IsOpen() )
//      m_Realtimedata1.Close();
//	if ( m_Rt5mdata._IsOpen() )
//	    m_Rt5mdata.Close();
    if ( m_CommonSet._IsOpen() )
         m_CommonSet.Close();

//	if(m_bExcelInit)
//		::CoUninitialize();  //EXCEL

	::CoUninitialize();
	m_Points.clear();
	CMainFrame* pFWnd=(CMainFrame*)AfxGetMainWnd();
   	pFWnd->m_MadeCert=NULL;
	CFormView::OnDestroy();
//	((CMainFrame*)AfxGetMainWnd())->m_pMade=NULL; // ��մ���ָ��
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

void CMadeCertView::OnBES() 
{
	BOOL bExist;
	int nItemCount=m_LCEXCEL1.GetItemCount();
    for(int nItem=0;nItem<nItemCount;nItem++)
	{
		if(m_LCEXCEL1.GetItemState(nItem,LVIS_SELECTED) & LVIS_SELECTED)
		{
			CString strP1=m_LCEXCEL1.GetItemText(nItem,0);
			CString strP2=m_LCEXCEL1.GetItemText(nItem,1);
			CString strPointNo=m_LCEXCEL1.GetItemText(nItem,2);
			int nItemCount1=m_LCEXCEL2.GetItemCount();
			bExist=FALSE;
			for(int j=0; j<nItemCount1; j++)
			{
				if(strPointNo==m_LCEXCEL2.GetItemText(j,2))
				{
					bExist=TRUE;
					break;
				}
			}
			if(!bExist)
			{
    			m_LCEXCEL1.DeleteItem(nItem);
				m_LCEXCEL2.InsertItem(nItemCount1, strP1);
				m_LCEXCEL2.SetItemText(nItemCount1, 1, strP2);
				m_LCEXCEL2.SetItemText(nItemCount1, 2, strPointNo);
			}
		}
	}
	L2upDB();
}

void CMadeCertView::OnBED() 
{
	int nItemCount1=m_LCEXCEL1.GetItemCount();
	int nItemCount=m_LCEXCEL2.GetItemCount();
    for(int nItem=nItemCount-1;nItem>=0;nItem--)
	{
		if(m_LCEXCEL2.GetItemState(nItem,LVIS_SELECTED) & LVIS_SELECTED)
		{
			CString strP1=m_LCEXCEL2.GetItemText(nItem,0);
			CString strP2=m_LCEXCEL2.GetItemText(nItem,1);
			CString strPointNo=m_LCEXCEL2.GetItemText(nItem,2);
				m_LCEXCEL1.InsertItem(nItemCount1, strP1);
				m_LCEXCEL1.SetItemText(nItemCount1, 1, strP2);
				m_LCEXCEL1.SetItemText(nItemCount1, 2, strPointNo);
			m_LCEXCEL2.DeleteItem(nItem);
		}
	}
	L2upDB();
}

void CMadeCertView::ADODBS(CString strTable,int n_dbl) 
{
    CString strDBLink = _T("Provider=SQLOLEDB.1;Persist Security Info=True;\
                          User ID=sa;Password=sunset;\
                          Data Source=") +strDBname+ _T(";Initial Catalog=BJygjl");
	try
	{
		if(n_dbl ==0)
		{
		theApp.pRS.CreateInstance(__uuidof(ADOCust::Recordset));
		theApp.pRS->Open(_bstr_t(strTable),_bstr_t(strDBLink), ADOCust::adOpenStatic ,ADOCust::adLockReadOnly , ADOCust::adCmdText );
		}
		else if(n_dbl ==1)
		{
			b_twodb =TRUE;
		pRS1.CreateInstance(__uuidof(ADOCust::Recordset));
		pRS1->Open(_bstr_t(strTable),_bstr_t(strDBLink), ADOCust::adOpenStatic ,ADOCust::adLockReadOnly , ADOCust::adCmdText );
		}
	}
	catch(_com_error &e)
	{
		AfxMessageBox(e.ErrorMessage());
	}
}

void CMadeCertView::L2upDB() 
{
       InitStr();
            	   	try
					{
    	int nItemCount=m_LCEXCEL2.GetItemCount();
         for(int nItem=0;nItem<nItemCount;nItem++)
		 {//һ��һ������
            if ( m_CommonSet._IsOpen() )
                 m_CommonSet.Close();
	      	CString strPointNo; 
     		strPointNo.Format(_T("SELECT * From commonset WHERE CommonID = %d"),nItem+1);
     		m_CommonSet.Open(strPointNo, &theApp.m_Cn);
	            				 m_CommonSet.m_szCommonID  = nItem+1;
	                    		 strPointNo=m_LCEXCEL2.GetItemText(nItem,2);
                if(theApp.strargc == "OnALARMS")
    		      			     m_CommonSet.m_szstrc2 = strPointNo;
              	else if(theApp.strargc == "OnBREAKES")
    		      			     m_CommonSet.m_szstrc3 = strPointNo;
            	else if(theApp.strargc == "OnFEEDES")
    		      			     m_CommonSet.m_szstrc4 = strPointNo;
            	else if(theApp.strargc == "OnSELECTS")
    		      			     m_CommonSet.m_szstrc5 = strPointNo;
               	else if(theApp.strargc == "OnRECAAD")
    		      			     m_CommonSet.m_szstrc6 = strPointNo;
            	else if(theApp.strargc == "OnRECABD")
    		      			     m_CommonSet.m_szstrc7 = strPointNo;
            	else if(theApp.strargc == "OnRECAFED")
    		      			     m_CommonSet.m_szstrc8 = strPointNo;
            	else if(theApp.strargc == "OnRECASR")
    		      			     m_CommonSet.m_szstrc9 = strPointNo;
            	else if(theApp.strargc == "OnRECDABD")
    		      			     m_CommonSet.m_szstrc10 = strPointNo;
            	else if(theApp.strargc == "OnRECDABB")
    		      			     m_CommonSet.m_szstrc11 = strPointNo;
            	else if(theApp.strargc == "OnRECDFED")
    		      			     m_CommonSet.m_szstrc12 = strPointNo;
            	else if(theApp.strargc == "OnRECDSCD")
    		      			     m_CommonSet.m_szstrc13 = strPointNo;
            	else if(theApp.strargc == "OnRECDRIVERE")
    		      			     m_CommonSet.m_szstrc14 = strPointNo;

            	else if(theApp.strargc == "OnEXCELA")
    		      			     m_CommonSet.m_szstrc15 = strPointNo;
               	else if(theApp.strargc == "OnEXCELAA")
    		      			     m_CommonSet.m_szstrc16 = strPointNo;
            	else if(theApp.strargc == "OnEXCELAB")
    		      			     m_CommonSet.m_szstrc17 = strPointNo;
            	else if(theApp.strargc == "OnEXCELAFE")
    		      			     m_CommonSet.m_szstrc18 = strPointNo;
            	else if(theApp.strargc == "OnEXCELASR")
    		      			     m_CommonSet.m_szstrc19 = strPointNo;
            	else if(theApp.strargc == "OnEXCELDA")
    		      			     m_CommonSet.m_szstrc20 = strPointNo;
            	else if(theApp.strargc == "OnEXCELDAB")
    		      			     m_CommonSet.m_szstrc21 = strPointNo;
            	else if(theApp.strargc == "OnEXCELDFE")
    		      			     m_CommonSet.m_szstrc22 = strPointNo;
            	else if(theApp.strargc == "OnEXCELDSCD")
    		      			     m_CommonSet.m_szstrc23 = strPointNo;
            	else if(theApp.strargc == "OnEXCELDRIVERE")
    		      			     m_CommonSet.m_szstrc24 = strPointNo;


				   	     m_CommonSet.Update();    //Update the recordset

				mPoint[m_Str2Data.String2Int(strPointNo)]=nItem;
		 }
		 if ( m_CommonSet._IsOpen() )
                 m_CommonSet.Close();
	      	CString strPointNo; 
     		strPointNo.Format(_T("SELECT * From commonset WHERE CommonID = %d"),nItemCount+1);
     		m_CommonSet.Open(strPointNo, &theApp.m_Cn);
	            				 m_CommonSet.m_szCommonID  = nItemCount+1;
                if(theApp.strargc == "OnALARMS")
    		      			     m_CommonSet.m_szstrc2 = "";
              	else if(theApp.strargc == "OnBREAKES")
    		      			     m_CommonSet.m_szstrc3 = "";
            	else if(theApp.strargc == "OnFEEDES")
    		      			     m_CommonSet.m_szstrc4 = "";
            	else if(theApp.strargc == "OnSELECTS")
    		      			     m_CommonSet.m_szstrc5 = "";
               	else if(theApp.strargc == "OnRECAAD")
    		      			     m_CommonSet.m_szstrc6 = "";
            	else if(theApp.strargc == "OnRECABD")
    		      			     m_CommonSet.m_szstrc7 = "";
            	else if(theApp.strargc == "OnRECAFED")
    		      			     m_CommonSet.m_szstrc8 = "";
            	else if(theApp.strargc == "OnRECASR")
    		      			     m_CommonSet.m_szstrc9 = "";
            	else if(theApp.strargc == "OnRECDABD")
    		      			     m_CommonSet.m_szstrc10 = "";
            	else if(theApp.strargc == "OnRECDABB")
    		      			     m_CommonSet.m_szstrc11 = "";
            	else if(theApp.strargc == "OnRECDFED")
    		      			     m_CommonSet.m_szstrc12 = "";
            	else if(theApp.strargc == "OnRECDSCD")
    		      			     m_CommonSet.m_szstrc13 = "";
            	else if(theApp.strargc == "OnRECDRIVERE")
    		      			     m_CommonSet.m_szstrc14 = "";

            	else if(theApp.strargc == "OnEXCELA")
    		      			     m_CommonSet.m_szstrc15 = "";
               	else if(theApp.strargc == "OnEXCELAA")
    		      			     m_CommonSet.m_szstrc16 = "";
            	else if(theApp.strargc == "OnEXCELAB")
    		      			     m_CommonSet.m_szstrc17 = "";
            	else if(theApp.strargc == "OnEXCELAFE")
    		      			     m_CommonSet.m_szstrc18 = "";
            	else if(theApp.strargc == "OnEXCELASR")
    		      			     m_CommonSet.m_szstrc19 = "";
            	else if(theApp.strargc == "OnEXCELDA")
    		      			     m_CommonSet.m_szstrc20 = "";
            	else if(theApp.strargc == "OnEXCELDAB")
    		      			     m_CommonSet.m_szstrc21 = "";
            	else if(theApp.strargc == "OnEXCELDFE")
    		      			     m_CommonSet.m_szstrc22 = "";
            	else if(theApp.strargc == "OnEXCELDSCD")
    		      			     m_CommonSet.m_szstrc23 = "";
            	else if(theApp.strargc == "OnEXCELDRIVERE")
    		      			     m_CommonSet.m_szstrc24 = "";

    					   	     m_CommonSet.Update();    //Update the recordset
					}
		     	    catch (CAxException *e)
					{
					        	AfxMessageBox(e->m_szErrorDesc, MB_OK);
				        		delete e;
					}
}

void CMadeCertView::ClearRDB() 
{


}

void CMadeCertView::InitStr() 
{
		m_Points.clear();
        for(int k = 0; k < 1000;k++ )
	          mPoint[k] =6666;
}

//bool CMadeCertView::SortList(int /*nCol*/, bool /*bAscending*/)
/*{
	CXTSortClass csc (&m_LCEXCEL2, m_nSortedCol);
    	csc.Sort (m_bAscending, xtSortInt);

//	if(m_Planting ==4)
//    	csc.Sort (m_bAscending, xtSortDateTime);
//	else
    	//csc.Sort (0, xtSortInt);          //max>> min
//    	csc.Sort (m_bAscending, xtSortString);
	return true;
}*/

void CMadeCertView::SortColumn(int iCol, bool bAsc)
{
	m_bAscending = bAsc;
	m_nSortedCol = iCol;

	// set sort image for header and sort column.
//	m_listCtrl.SetSortImage(m_nSortedCol, m_bAscending);

	CXTSortClass csc(&m_LCEXCEL2, m_nSortedCol);
	csc.Sort(m_bAscending, xtSortString);
}

BOOL CMadeCertView::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	HD_NOTIFY *pHDNotify = (HD_NOTIFY*)lParam;

	if (pHDNotify->hdr.code == HDN_ITEMCLICKA ||
		pHDNotify->hdr.code == HDN_ITEMCLICKW)
	{
		if (pHDNotify->iItem == m_nSortedCol)
			SortColumn(pHDNotify->iItem, !m_bAscending);
		else
			SortColumn(pHDNotify->iItem, BoolType(m_header.GetAscending()));
	}

	return CFormView::OnNotify(wParam, lParam, pResult);
}
