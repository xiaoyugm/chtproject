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

extern SlaveStation             m_SlaveStation[MAX_FDS][MAX_CHAN];
extern SerialF               m_ClassTime[200];            //������
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
	m_ctrlStartH = m_ClassTime[1].ffds;
	m_ctrlEndH = m_ClassTime[1].ffds-1;
	m_endDateTime = CTime::GetCurrentTime();
	if(m_ctrlStartH == 0)
   	{
    	m_endDateTime = CTime::GetCurrentTime()-tpan;
		m_ctrlEndH =23;
	}

	m_startDateTime = CTime::GetCurrentTime()-tpan;
	m_tnum =0;
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

	CString strna[3];
	strna[0] = "��װ�ص�|����";
		strna[1] ="���";
		strna[2] ="PID";
		int m_widge[3];
		m_widge[0] =170;
		m_widge[1]=80;
		m_widge[2]=40;
	for(int i=0;i<3;i++)
	{
		m_LCEXCEL1.InsertColumn(i,strna[i],LVCFMT_LEFT,m_widge[i]);
		m_LCEXCEL2.InsertColumn(i,strna[i],LVCFMT_LEFT,m_widge[i]);
	}
	m_ctrlStartTime.SetTime(&m_startDateTime);
	m_ctrlEndTime.SetTime(&m_endDateTime);
	
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
  }
  catch ( dbAx::CAxException *e )
  {
		AfxMessageBox(e->m_szErrorDesc +  _T("BJygjl Message"));
//    MessageBox(e->m_szErrorDesc, _T("BJygjl Message"), MB_OK);
    delete e;
    return ;
  }

//	((CComboBox *)GetDlgItem(IDC_COMBO1))->SetCurSel(0);
	// TODO: Add your specialized code here and/or call the base class
//	m_List.SetWindowPos(NULL,0,0,1024,400,SWP_NOMOVE|SWP_NOZORDER | SWP_NOACTIVATE);
    	GetDlgItem(IDC_COMBMADE)->ShowWindow(SW_HIDE);;

		strna[0] ="Select * From pointdescription WHERE fdel=0";
	if(theApp.strargc == "OnALARMS")
//    	GetDlgItem(IDC_CHECK_ISALM)->ShowWindow(SW_SHOW);;
       	GetParentFrame()->SetWindowText("������¼��ѯ");
	else if(theApp.strargc == "OnBREAKES")
       	GetParentFrame()->SetWindowText("�ϵ��¼��ѯ");
	else if(theApp.strargc == "OnFEEDES")
       	GetParentFrame()->SetWindowText("�����쳣��¼��ѯ");
	else if(theApp.strargc == "OnSELECTS")
       	GetParentFrame()->SetWindowText("���ò�ѯ");
	else if(theApp.strargc == "OnRECAAD")
	{
		strna[0] ="Select * From pointdescription WHERE fdel=0 and ptype<3";
       	GetParentFrame()->SetWindowText("ģ����������¼��ѯ");
	}
	else if(theApp.strargc == "OnRECABD")
	{
		strna[0] ="Select * From pointdescription WHERE fdel=0 and ptype<3";
       	GetParentFrame()->SetWindowText("ģ�����ϵ��¼��ѯ");
	}
	else if(theApp.strargc == "OnRECAFED")
	{
		strna[0] ="Select * From pointdescription WHERE fdel=0 and ptype<3";
       	GetParentFrame()->SetWindowText("ģ���������쳣��¼��ѯ");
	}
	else if(theApp.strargc == "OnRECASR")
	{
		strna[0] ="Select * From pointdescription WHERE fdel=0 and ptype<3";
       	GetParentFrame()->SetWindowText("ģ����ͳ��ֵ��¼��ѯ");
	}
	else if(theApp.strargc == "OnRECDABD")
	{
		strna[0] ="Select * From pointdescription WHERE fdel=0 and ptype>3";
       	GetParentFrame()->SetWindowText("������������¼��ѯ");
	}
	else if(theApp.strargc == "OnRECDABB")
	{
		strna[0] ="Select * From pointdescription WHERE fdel=0 and ptype>3";
       	GetParentFrame()->SetWindowText("�������ϵ��¼��ѯ");
	}
	else if(theApp.strargc == "OnRECDFED")
	{
		strna[0] ="Select * From pointdescription WHERE fdel=0 and ptype>3";
       	GetParentFrame()->SetWindowText("�����������쳣��¼��ѯ");
	}
	else if(theApp.strargc == "OnRECDSCD")
	{
		strna[0] ="Select * From pointdescription WHERE fdel=0 and ptype>3";
       	GetParentFrame()->SetWindowText("������״̬�䶯��¼��ѯ");
	}
	else if(theApp.strargc == "OnRECDRIVERE")
	{
       	GetParentFrame()->SetWindowText("����豸���ϼ�¼��ѯ");
	}

	else if(theApp.strargc == "OnEXCELA")
	{
		strna[0] ="Select * From pointdescription WHERE fdel=0 and ptype<3";
       	GetParentFrame()->SetWindowText("ģ������(��)����");
	}
	else if(theApp.strargc == "OnEXCELAA")
	{
		strna[0] ="Select * From pointdescription WHERE fdel=0 and ptype<3";
       	GetParentFrame()->SetWindowText("ģ����������(��)����");
	}
	else if(theApp.strargc == "OnEXCELAB")
	{
		strna[0] ="Select * From pointdescription WHERE fdel=0 and ptype<3";
       	GetParentFrame()->SetWindowText("ģ�����ϵ���(��)����");
	}
	else if(theApp.strargc == "OnEXCELAFE")
	{
		strna[0] ="Select * From pointdescription WHERE fdel=0 and ptype<3";
       	GetParentFrame()->SetWindowText("ģ���������쳣��(��)����");
	}
	else if(theApp.strargc == "OnEXCELASR")
	{
		strna[0] ="Select * From pointdescription WHERE fdel=0 and ptype<3";
       	GetParentFrame()->SetWindowText("ģ����ͳ��ֵ��(��)����");
	}
	else if(theApp.strargc == "OnEXCELDA")
	{
		strna[0] ="Select * From pointdescription WHERE fdel=0 and ptype>3";
       	GetParentFrame()->SetWindowText("������������(��)����");
	}
	else if(theApp.strargc == "OnEXCELDAB")
	{
		strna[0] ="Select * From pointdescription WHERE fdel=0 and ptype>3";
       	GetParentFrame()->SetWindowText("�������ϵ���(��)����");
	}
	else if(theApp.strargc == "OnEXCELDFE")
	{
		strna[0] ="Select * From pointdescription WHERE fdel=0 and ptype>3";
       	GetParentFrame()->SetWindowText("�����������쳣��(��)����");
	}
	else if(theApp.strargc == "OnEXCELDSCD")
	{
		strna[0] ="Select * From pointdescription WHERE fdel=0 and ptype>3";
       	GetParentFrame()->SetWindowText("������״̬�䶯��(��)����");
	}
	else if(theApp.strargc == "OnEXCELDRIVERE")
	{
       	GetParentFrame()->SetWindowText("����豸������(��)����");
	}

  		m_PointDes.Create();
		m_PointDes.CursorType(adOpenDynamic);
		m_PointDes.CacheSize(50);
//		m_PointDes._SetRecordsetEvents(new CAccountSetEvents);
		m_PointDes.Open(strna[0] , &m_Cn);
		m_PointDes.MarshalOptions(adMarshalModifiedOnly);

       InitStr();
	CString strstartTime,strname,dddd;
    	int eYear;
		m_CommonSet.Create();
		m_CommonSet.CursorType(adOpenDynamic);
		m_CommonSet.CacheSize(50);
//		m_CommonSet._SetRecordsetEvents(new CAccountSetEvents);
		m_CommonSet.Open(_T("Select * From commonset"), &m_Cn);
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

         		m_PointDes.MoveFirst();
      	     	while ( !m_PointDes.IsEOF() )
				{
					int n_cp= m_PointDes.m_szPID;
					if(eYear == n_cp)
					{
						m_cba =100;
       					 break;
					}
	        		m_PointDes.MoveNext();
				}
				if(m_cba == 100)
				{
					mPoint[eYear]=iItem;
    	        	m_Points.push_back(eYear);
    		        iItem++;
					m_tnum = iItem;
				}
	    		m_CommonSet.MoveNext();
			}
		}
             for ( i = 0 ; i < m_Points.size() ; i++ )
        		m_LCEXCEL2.InsertItem(i, "ddd");

		 iItem = 0;
    	if(!m_PointDes._IsEmpty())
		{
    		m_PointDes.MoveFirst();
	     	while ( !m_PointDes.IsEOF() )
			{
				int m_cba =0;
	    		eYear = m_PointDes.m_szptype;
	    		if((eYear != 11))
				{
	    			strstartTime = m_PointDes.m_szpointnum;
    				strstartTime.TrimRight();
             		int nfds = m_PointDes.m_szfds;
              		int nchan = m_PointDes.m_szchan;
					eYear = m_PointDes.m_szPID;
    				dddd.Format("%d",eYear);
					int i=0;
             		for ( i = 0 ; i < m_Points.size() ; i++ )
					{
		      			if(eYear == m_Points[i])
						{
    						m_cba =100;
      						break;
						}
					}
					if(m_cba == 100)
					{
						strname =m_SlaveStation[nfds][nchan].WatchName;
//						if(strname != "")
						{
            				m_LCEXCEL2.SetItemText(i, 0, strname);
            				m_LCEXCEL2.SetItemText(i, 1, strstartTime);
        	    			m_LCEXCEL2.SetItemText(i, 2, dddd);
						}
					}
					else
					{
        				m_LCEXCEL1.InsertItem(iItem, m_SlaveStation[nfds][nchan].WatchName);
         				m_LCEXCEL1.SetItemText(iItem, 1, strstartTime);
        				m_LCEXCEL1.SetItemText(iItem, 2, dddd);
    	    	        iItem++;
					}
				}
	    		m_PointDes.MoveNext();
			}
		}

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
	CommonTools C_Ts;
	UpdateData(TRUE);
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
					theApp.socketClient.CalRtDB(t , starty , startm);
					theApp.socketClient.CalRtDB(t1 , endy , endm);
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
    					if(m_ClassTime[1].ffds >12)
						{
        					  strtime = t.Format(_T("%Y-%m-%d %H:%M:%S")); 
        					  sztime.Format("%d-%d-%d %d:59:59",starty,startm,C_Ts.GetDayM(starty,startm),m_ClassTime[1].ffds-1); 
            				  szConnect1 += strtime+"' and recdate<'" +sztime+"'";
        					  strtime.Format("%d-%d-%d %d:00:00",starty,startm,C_Ts.GetDayM(starty,startm),m_ClassTime[1].ffds); 
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

					if(endm != startm)   //������
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

 /*		((CRaChildFrame*)GetParentFrame( ))->Msg("��ʼ��ѯ���ݿ�");
		msg.Format("û�в�ѯ��������֤��,��ѯ����!");
	((CRaChildFrame*)GetParentFrame( ))->Msg(msg);*/
}

void CMadeCertView::OnSABFE() 
{
	CString sztime,strtime,stnames;
	if(m_Realtimedata1._IsOpen())
	{
		m_Realtimedata1.MoveFirst();
		while ( !m_Realtimedata1.IsEOF() )
		{
	   		int dbp = mPoint[m_Realtimedata1.m_szPID];
             if(dbp != 6666)
			 {
				 if(m_ADP[dbp][m_ADP[dbp][0].m_ATotalnum].NTime != m_Realtimedata1.m_szrecdate)
				 {
        			m_ADP[dbp][0].m_ATotalnum++;
     				int afds = m_Realtimedata1.m_szfds;
	      			int achan = m_Realtimedata1.m_szchan;
	    			 m_ADP[dbp][m_ADP[dbp][0].m_ATotalnum].strsafetext = m_SlaveStation[afds][achan].WatchName;
	     			 m_ADP[dbp][m_ADP[dbp][0].m_ATotalnum].NTime = m_Realtimedata1.m_szrecdate;
	    			 m_ADP[dbp][m_ADP[dbp][0].m_ATotalnum].m_ATotalnum =m_Realtimedata1.m_szADStatus;
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
	    			  m_ADP[dbp][m_ADP[dbp][0].m_ATotalnum].strlocal =strtime;
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
	   		int dbp = mPoint[m_Realtimedata.m_szPID];
             if(dbp != 6666)
			 {
				 //debug error
				 if(m_ADP[dbp][m_ADP[dbp][0].m_ATotalnum].NTime != m_Realtimedata.m_szrecdate)
				 {
     			m_ADP[dbp][0].m_ATotalnum++;
				int afds = m_Realtimedata.m_szfds;
				int achan = m_Realtimedata.m_szchan;
				 m_ADP[dbp][m_ADP[dbp][0].m_ATotalnum].strsafetext = m_SlaveStation[afds][achan].WatchName;
				 m_ADP[dbp][m_ADP[dbp][0].m_ATotalnum].NTime = m_Realtimedata.m_szrecdate;
				 m_ADP[dbp][m_ADP[dbp][0].m_ATotalnum].m_ATotalnum =m_Realtimedata.m_szADStatus;
				  int nptype = m_SlaveStation[afds][achan].ptype;
				  if( nptype <3)
				    	  strtime.Format("%.2f",m_Realtimedata1.m_szAValue);
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
				  m_ADP[dbp][m_ADP[dbp][0].m_ATotalnum].strlocal =strtime;
				 }
			 }
			m_Realtimedata.MoveNext();
		}
	}

	if(theApp.strargc == "OnALARMS")
       	stnames= "������ѯ";
	else if(theApp.strargc == "OnBREAKES")
      	stnames= "�ϵ��ѯ";
	else if(theApp.strargc == "OnFEEDES")
       	stnames= "�����쳣��ѯ";
	else if(theApp.strargc == "OnSELECTS")
    	stnames= "���ò�ѯ";

	_Application ExcelApp; 
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
	size_t col = 0;
		int iItem = 3;
		for(int h = 0; h < m_tnum;h++)
		{
      		for(int i = 1; i < 1000;i++)
			{
				if(m_ADP[h][i].strsafetext =="")
					break;
			    for(col=0; col<4; col++) {
//         	     	BasicExcelCell* cell = sheet->Cell(iItem, col);
         	    	if(col==0)
							strtime =m_ADP[h][i].strsafetext;
//                      m_Str2Data.GB2312ToUnicode(m_ADP[h][i].strsafetext,buf);
        	     	else if(col==1)
							strtime =m_ADP[h][i].strlocal;
//                      m_Str2Data.GB2312ToUnicode(m_ADP[h][i].strlocal ,buf);
         	     	else if(col==2)
					{
				    	int nstatus = m_ADP[h][i].m_ATotalnum;
				    	strtime= theApp.socketClient.strstatus(nstatus);
//                        m_Str2Data.GB2312ToUnicode(strtime ,buf);
					}
         	     	else if(col==3)
					{
				  COleDateTime oleDateTime=m_ADP[h][i].NTime;
				  strtime   =   oleDateTime.Format(_T("%Y:%m:%d %H:%M:%S")); 
//                      m_Str2Data.GB2312ToUnicode(strtime,buf);
					}
					rgMyRge.SetItem(_variant_t((long)iItem),_variant_t((long)(col+1)),_variant_t(strtime)); 
				}
				iItem++;
			}
		}
	//����Ϊ�ļ�
	ExcelApp.SetDisplayAlerts(FALSE);   //���ص����ĶԻ���
	wsMysheet.SaveAs(gstrTimeOut +"\\report\\" + stnames +t1.Format(_T("%Y-%m-%d"))+ ".xls",vtMissing,vtMissing,COleVariant("123"),vtMissing,
		vtMissing,vtMissing,vtMissing,vtMissing,vtMissing);   
    ExcelApp.Quit();
	//�ͷŶ��� 
	rgMyRge.ReleaseDispatch(); 
	wsMysheet.ReleaseDispatch(); 
	wssMysheets.ReleaseDispatch(); 
	wbMyBook.ReleaseDispatch(); 
	wbsMyBooks.ReleaseDispatch(); 
	ExcelApp.ReleaseDispatch(); 
	ShellExecute(0, "open", gstrTimeOut +"\\report\\"+stnames + t1.Format(_T("%Y-%m-%d")) +".xls", NULL, NULL, SW_NORMAL);


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

void CMadeCertView::OnRECAAD() 
{
	CString strtime,strtime2;
	if(m_Realtimedata1._IsOpen())
	{
		m_Realtimedata1.MoveFirst();
		while ( !m_Realtimedata1.IsEOF() )
		{
				int afds = m_Realtimedata1.m_szfds;
				int achan = m_Realtimedata1.m_szchan;
	   		int dbp = mPoint[m_Realtimedata1.m_szPID];
             if(dbp != 6666)
			 {
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
				m_ADRecord[afds][achan][0].duant++;//n������ֵ
			}
			else if(m_alarm == 0)
			{
				if(m_ADRecord[afds][achan][0].duant> 0)
				{
	    			m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].BTime =m_Realtimedata1.m_szrecdate;
	     			m_ADRecord[afds][achan][0].m_ATotalnum++;  //�ܱ�������
	     			m_ADRecord[afds][achan][0].duant = 0;  //״̬ת��
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
	   		int dbp = mPoint[m_Realtimedata.m_szPID];
             if(dbp != 6666)
			 {
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
				m_ADRecord[afds][achan][0].duant++;//n������ֵ
			}
			else if(m_alarm == 0)
			{
				if(m_ADRecord[afds][achan][0].duant> 0)
				{
	    			m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].BTime =m_Realtimedata.m_szrecdate;
	     			m_ADRecord[afds][achan][0].m_ATotalnum++;  //�ܱ�������
	     			m_ADRecord[afds][achan][0].duant = 0;  //״̬ת��
				}
			}
			 }
			m_Realtimedata.MoveNext();
		}
	}
	CString strtime1,strtime3,strtime4,stnames;
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
	_Application ExcelApp; 
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

	size_t col = 0;
		int iItem = 3;
		for (int i = 1; i < MAX_FDS;i++)
		{
			for(int j = 1; j < 17;j++ )
			{
     			for(int k = 0; k < 300;k++ )
				{
    				if(m_ADRecord[i][j][k].strlocal!="ddd")
						break;
                       	for(col=0; col<8; col++) {
//                		BasicExcelCell* cell = sheet->Cell(iItem, col);
                		if(col==0)
							strtime =m_SlaveStation[i][j].WatchName;
//                             m_Str2Data.GB2312ToUnicode(m_SlaveStation[i][j].WatchName,buf);
                		else if(col==1)
//					  if((nstatus == 0x40)||(nstatus == 0x50)||(nstatus == 0x70))
//						  strtime= theApp.socketClient.strstatus(nstatus);
							strtime ="1";
//                             m_Str2Data.GB2312ToUnicode("1" ,buf);
                		else if(col==2)
						{
							COleDateTime o =m_ADRecord[i][j][k].NTime;
							COleDateTime o1 =m_ADRecord[i][j][k].BTime;
				         	COleDateTimeSpan t = o1-o;
			            	strtime.Format("%d %d:%d:%d",t.GetDays(),t.GetHours(),t.GetMinutes(),t.GetSeconds()); 
//                            m_Str2Data.GB2312ToUnicode(strtime ,buf);
						}
                 		else if(col==3)
						{
				    	  strtime.Format("%.2f",m_ADRecord[i][j][k].AMaxValue);
//                          m_Str2Data.GB2312ToUnicode(strtime,buf);
						}
                 		else if(col==4)
						{
          				  COleDateTime oleDateTime=m_ADRecord[i][j][k].AMaxTime;
		        		  strtime   =   oleDateTime.Format(_T("%Y:%m:%d %H:%M:%S")); 
//                          m_Str2Data.GB2312ToUnicode(strtime,buf);
						}
                 		else if(col==5)
						{
          				  COleDateTime oleDateTime=m_ADRecord[i][j][k].NTime;
		        		  strtime   =   oleDateTime.Format(_T("%Y:%m:%d %H:%M:%S")); 
//                          m_Str2Data.GB2312ToUnicode(strtime,buf);
						}
                 		else if(col==6)
						{
          				  COleDateTime oleDateTime=m_ADRecord[i][j][k].BTime;
		        		  strtime   =   oleDateTime.Format(_T("%Y:%m:%d %H:%M:%S")); 
//                          m_Str2Data.GB2312ToUnicode(strtime,buf);
						}
                 		else if(col==7)
							strtime =m_ADRecord[i][j][k].strsafetext;
//                          m_Str2Data.GB2312ToUnicode(m_ADRecord[i][j][k].strsafetext,buf);
					rgMyRge.SetItem(_variant_t((long)iItem),_variant_t((long)(col+1)),_variant_t(strtime)); 
						}
		            	iItem++;
				}//k
			}//j
		}//i
	//����Ϊ�ļ�
	ExcelApp.SetDisplayAlerts(FALSE);   //���ص����ĶԻ���
	wsMysheet.SaveAs(gstrTimeOut +"\\report\\" + stnames +t1.Format(_T("%Y-%m-%d"))+ ".xls",vtMissing,vtMissing,COleVariant("123"),vtMissing,
		vtMissing,vtMissing,vtMissing,vtMissing,vtMissing);   
    ExcelApp.Quit();
	//�ͷŶ��� 
	rgMyRge.ReleaseDispatch(); 
	wsMysheet.ReleaseDispatch(); 
	wssMysheets.ReleaseDispatch(); 
	wbMyBook.ReleaseDispatch(); 
	wbsMyBooks.ReleaseDispatch(); 
	ExcelApp.ReleaseDispatch(); 
	ShellExecute(0, "open", gstrTimeOut +"\\report\\"+stnames + t1.Format(_T("%Y-%m-%d")) +".xls", NULL, NULL, SW_NORMAL);
}

void CMadeCertView::OnRECABD() 
{
	CString strtime,strtime2;
	if(m_Realtimedata1._IsOpen())
	{
		m_Realtimedata1.MoveFirst();
		while ( !m_Realtimedata1.IsEOF() )
		{
				int afds = m_Realtimedata1.m_szfds;
				int achan = m_Realtimedata1.m_szchan;
   		int dbp = mPoint[m_Realtimedata1.m_szPID];
             if(dbp != 6666)
			 {
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
				m_ADRecord[afds][achan][0].duant++;//n���ϵ�ֵ
			}
			else if(m_alarm == 0)
			{
				if(m_ADRecord[afds][achan][0].duant> 0)
				{
	    			m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].BTime =m_Realtimedata1.m_szrecdate;
	     			m_ADRecord[afds][achan][0].m_ATotalnum++;  //�ܶϵ����
	     			m_ADRecord[afds][achan][0].duant = 0;  //״̬ת��
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
	   		int dbp = mPoint[m_Realtimedata.m_szPID];
             if(dbp != 6666)
			 {
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
				m_ADRecord[afds][achan][0].duant++;//n���ϵ�ֵ
			}
			else if(m_alarm == 0)
			{
				if(m_ADRecord[afds][achan][0].duant> 0)
				{
	    			m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].BTime =m_Realtimedata.m_szrecdate;
	     			m_ADRecord[afds][achan][0].m_ATotalnum++;  //�ܶϵ����
	     			m_ADRecord[afds][achan][0].duant = 0;  //״̬ת��
				}
			}
			 }
			m_Realtimedata.MoveNext();
		}
	}
	CString strtime1,strtime3,strtime4,stnames;
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
	_Application ExcelApp; 
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

	size_t col = 0;
		int iItem = 3;
		for (int i = 1; i < MAX_FDS;i++)
		{
			for(int j = 1; j < 17;j++ )
			{
     			for(int k = 0; k < 300;k++ )
				{
    				if(m_ADRecord[i][j][k].havev==0)
						break;
					{
                       	for(col=0; col<9; col++) {
//                		BasicExcelCell* cell = sheet->Cell(iItem, col);
                		if(col==0)
							strtime =m_SlaveStation[i][j].WatchName;
//                             m_Str2Data.GB2312ToUnicode(m_SlaveStation[i][j].WatchName,buf);
                		else if(col==1)
//					  if((nstatus == 0x40)||(nstatus == 0x50)||(nstatus == 0x70))
//						  strtime= theApp.socketClient.strstatus(nstatus);
//                             m_Str2Data.GB2312ToUnicode("1" ,buf);
							strtime ="1";
                		else if(col==2)
						{
							COleDateTime o =m_ADRecord[i][j][k].NTime;
							COleDateTime o1 =m_ADRecord[i][j][k].BTime;
				         	COleDateTimeSpan t = o1-o;
			            	strtime.Format("%d %d:%d:%d",t.GetDays(),t.GetHours(),t.GetMinutes(),t.GetSeconds()); 
//                            m_Str2Data.GB2312ToUnicode(strtime ,buf);
						}
                 		else if(col==3)
						{
				    	  strtime.Format("%.2f",m_ADRecord[i][j][k].AMaxValue);
//                          m_Str2Data.GB2312ToUnicode(strtime,buf);
						}
                 		else if(col==4)
						{
          				  COleDateTime oleDateTime=m_ADRecord[i][j][k].AMaxTime;
		        		  strtime   =   oleDateTime.Format(_T("%Y:%m:%d %H:%M:%S")); 
//                          m_Str2Data.GB2312ToUnicode(strtime,buf);
						}
                 		else if(col==5)
						{
          				  COleDateTime oleDateTime=m_ADRecord[i][j][k].NTime;
		        		  strtime   =   oleDateTime.Format(_T("%Y:%m:%d %H:%M:%S")); 
//                          m_Str2Data.GB2312ToUnicode(strtime,buf);
						}
                 		else if(col==6)
						{
          				  COleDateTime oleDateTime=m_ADRecord[i][j][k].BTime;
		        		  strtime   =   oleDateTime.Format(_T("%Y:%m:%d %H:%M:%S")); 
//                          m_Str2Data.GB2312ToUnicode(strtime,buf);
						}
                 		else if(col==7)
							strtime =m_ADRecord[i][j][k].strsafetext;
//                          m_Str2Data.GB2312ToUnicode(m_ADRecord[i][j][k].strsafetext,buf);
                 		else if(col==8)
							strtime =m_ADRecord[i][j][k].strlocal;
//                          m_Str2Data.GB2312ToUnicode(m_ADRecord[i][j][k].strlocal,buf);
					rgMyRge.SetItem(_variant_t((long)iItem),_variant_t((long)(col+1)),_variant_t(strtime)); 
//						cell->Set(buf);
						}
		            	iItem++;
					}//if
				}//k
			}//j
		}//i
	//����Ϊ�ļ�
	ExcelApp.SetDisplayAlerts(FALSE);   //���ص����ĶԻ���
	wsMysheet.SaveAs(gstrTimeOut +"\\report\\" + stnames +t1.Format(_T("%Y-%m-%d"))+ ".xls",vtMissing,vtMissing,COleVariant("123"),vtMissing,
		vtMissing,vtMissing,vtMissing,vtMissing,vtMissing);   
    ExcelApp.Quit();
	//�ͷŶ��� 
	rgMyRge.ReleaseDispatch(); 
	wsMysheet.ReleaseDispatch(); 
	wssMysheets.ReleaseDispatch(); 
	wbMyBook.ReleaseDispatch(); 
	wbsMyBooks.ReleaseDispatch(); 
	ExcelApp.ReleaseDispatch(); 
	ShellExecute(0, "open", gstrTimeOut +"\\report\\"+stnames + t1.Format(_T("%Y-%m-%d")) +".xls", NULL, NULL, SW_NORMAL);
}

void CMadeCertView::OnRECAFED() 
{
	CString strtime,strtime2;
	if(m_Realtimedata1._IsOpen())
	{
		m_Realtimedata1.MoveFirst();
		while ( !m_Realtimedata1.IsEOF() )
		{
				int afds = m_Realtimedata1.m_szfds;
				int achan = m_Realtimedata1.m_szchan;
	   		int dbp = mPoint[m_Realtimedata1.m_szPID];
             if(dbp != 6666)
			 {
			strtime = m_Realtimedata1.m_szFeedStatus;
			strtime.TrimRight();
			if(strtime == "�쳣")
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
				m_ADRecord[afds][achan][0].duant++;//n�������쳣��¼
			}
			else if(strtime == "����")
			{
				if(m_ADRecord[afds][achan][0].duant> 0)
				{
	    			m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].BTime =m_Realtimedata1.m_szrecdate;
	     			m_ADRecord[afds][achan][0].m_ATotalnum++;  //�������쳣��¼����
	     			m_ADRecord[afds][achan][0].duant = 0;  //״̬ת��
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
	   		int dbp = mPoint[m_Realtimedata.m_szPID];
             if(dbp != 6666)
			 {
			strtime = m_Realtimedata.m_szFeedStatus;
			strtime.TrimRight();
			if(strtime == "�쳣")
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
				m_ADRecord[afds][achan][0].duant++;//n�������쳣��¼ֵ
			}
			else if(strtime == "����")
			{
				if(m_ADRecord[afds][achan][0].duant> 0)
				{
	    			m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].BTime =m_Realtimedata.m_szrecdate;
	     			m_ADRecord[afds][achan][0].m_ATotalnum++;  //�������쳣��¼����
	     			m_ADRecord[afds][achan][0].duant = 0;  //״̬ת��
				}
			}
			 }
			m_Realtimedata.MoveNext();
		}
	}

	CString strtime1,strtime3,strtime4,stnames;
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

	_Application ExcelApp; 
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

	size_t col = 0;
		int iItem = 3;
		for (int i = 1; i < MAX_FDS;i++)
		{
			for(int j = 1; j < 17;j++ )
			{
     			for(int k = 0; k < 300;k++ )
				{
    				if(m_ADRecord[i][j][k].strlocal == "")
						break;
					{
                       	for(col=0; col<7; col++) {
//                		BasicExcelCell* cell = sheet->Cell(iItem, col);
                		if(col==0)
							strtime =m_SlaveStation[i][j].WatchName;
//                             m_Str2Data.GB2312ToUnicode(m_SlaveStation[i][j].WatchName,buf);
                		else if(col==1)
							strtime ="1";
//                             m_Str2Data.GB2312ToUnicode("1" ,buf);
                		else if(col==2)
						{
							COleDateTime o =m_ADRecord[i][j][k].NTime;
							COleDateTime o1 =m_ADRecord[i][j][k].BTime;
				         	COleDateTimeSpan t = o1-o;
			            	strtime.Format("%d %d:%d:%d",t.GetDays(),t.GetHours(),t.GetMinutes(),t.GetSeconds()); 
//                            m_Str2Data.GB2312ToUnicode(strtime ,buf);
						}
                 		else if(col==3)
						{
          				  COleDateTime oleDateTime=m_ADRecord[i][j][k].NTime;
		        		  strtime   =   oleDateTime.Format(_T("%Y:%m:%d %H:%M:%S")); 
//                          m_Str2Data.GB2312ToUnicode(strtime,buf);
						}
                 		else if(col==4)
						{
          				  COleDateTime oleDateTime=m_ADRecord[i][j][k].BTime;
		        		  strtime   =   oleDateTime.Format(_T("%Y:%m:%d %H:%M:%S")); 
//                          m_Str2Data.GB2312ToUnicode(strtime,buf);
						}
                 		else if(col==5)
							strtime =m_ADRecord[i][j][k].strsafetext;
//                          m_Str2Data.GB2312ToUnicode(m_ADRecord[i][j][k].strsafetext,buf);
                 		else if(col==6)
							strtime =m_ADRecord[i][j][k].strlocal;
//                          m_Str2Data.GB2312ToUnicode(m_ADRecord[i][j][k].strlocal,buf);
					rgMyRge.SetItem(_variant_t((long)iItem),_variant_t((long)(col+1)),_variant_t(strtime)); 
//						cell->Set(buf);
						}
		            	iItem++;
					}//if
				}//k
			}//j
		}//i
	//����Ϊ�ļ�
	ExcelApp.SetDisplayAlerts(FALSE);   //���ص����ĶԻ���
	wsMysheet.SaveAs(gstrTimeOut +"\\report\\" + stnames +t1.Format(_T("%Y-%m-%d"))+ ".xls",vtMissing,vtMissing,COleVariant("123"),vtMissing,
		vtMissing,vtMissing,vtMissing,vtMissing,vtMissing);   
    ExcelApp.Quit();
	//�ͷŶ��� 
	rgMyRge.ReleaseDispatch(); 
	wsMysheet.ReleaseDispatch(); 
	wssMysheets.ReleaseDispatch(); 
	wbMyBook.ReleaseDispatch(); 
	wbsMyBooks.ReleaseDispatch(); 
	ExcelApp.ReleaseDispatch(); 
	ShellExecute(0, "open", gstrTimeOut +"\\report\\"+stnames + t1.Format(_T("%Y-%m-%d")) +".xls", NULL, NULL, SW_NORMAL);
}

void CMadeCertView::OnRECASR() 
{
	CString strtime,strtime2,strname;
	int m_Atotal =0;
	int m_asr =0;
	float fmax,ATotalV;
	ATotalV=fmax =0;
	COleDateTime t2;
	if(!m_Rt5mdata._IsEmpty())
	{
		m_Rt5mdata.MoveFirst();
		while ( !m_Rt5mdata.IsEOF() )
		{
				int afds = m_Rt5mdata.m_szfds;
				int achan = m_Rt5mdata.m_szchan;
	   		int dbp = mPoint[m_Rt5mdata.m_szPID];
             if(dbp != 6666)
			 {
	     	    m_ADRecord[afds][achan][0].m_ATotalnum++;  //��ͳ�Ƽ�¼����
						float fcurmax =m_Rt5mdata.m_szAMaxValue;
						t2 = m_Rt5mdata.m_szrecdate;
						float fcurv =m_Rt5mdata.m_szAValue;

				m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].ATotalV =fcurv;
				m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].NTime =t2;
				m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].AMaxValue =fcurmax;
				if(fcurmax > m_ADRecord[afds][achan][0].AMaxValue)
				{
					m_ADRecord[afds][achan][0].NTime =t2;
					m_ADRecord[afds][achan][0].AMaxValue =fcurmax;
				}
				m_ADRecord[afds][achan][0].ATotalV +=fcurv;
			 }
			m_Rt5mdata.MoveNext();
		}
	}
	CString strtime1,strtime3,strtime4,stnames;
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

	_Application ExcelApp; 
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

	size_t col = 0;
		int iItem = 3;
		for (int i = 1; i < MAX_FDS;i++)
		{
			for(int j = 1; j < 17;j++ )
			{
     			for(int k = 0; k < 300;k++ )
				{
					if(m_ADRecord[i][j][k].ATotalV <= 0.0001)
						break;
                    for(col=0; col<5; col++) {
//             		BasicExcelCell* cell = sheet->Cell(iItem, col);
            	    if(col==0)
							strtime =m_SlaveStation[i][j].WatchName;
//                        m_Str2Data.GB2312ToUnicode(m_SlaveStation[i][j].WatchName,buf);
              		else if(col==1)
					{
			    		strtime.Format(_T("%.2f"), m_ADRecord[i][j][k].AMaxValue);
//                        m_Str2Data.GB2312ToUnicode(strtime1,buf);
					}
              		else if(col==2)
					{
						t2 =m_ADRecord[i][j][k].NTime;
						 strtime   =   t2.Format(_T("%Y:%m:%d %H:%M:%S")); 
//                         m_Str2Data.GB2312ToUnicode(strtime ,buf);
					}
               		else if(col==3)
					{
						if(k == 0)
    			    		strtime.Format(_T("%.2f"), m_ADRecord[i][j][0].ATotalV/(m_ADRecord[i][j][0].m_ATotalnum-1));
						else
    			    		strtime.Format(_T("%.2f"), m_ADRecord[i][j][k].ATotalV);
//                        m_Str2Data.GB2312ToUnicode(strtime1 ,buf);
					}
              		else if(col==4)
					{
						if(k == 0)
							strtime ="";
						else
						{
			    			t2 =m_ADRecord[i][j][k].NTime;
						 strtime   =   t2.Format(_T("%Y:%m:%d %H:%M:%S")); 
						}
//                         m_Str2Data.GB2312ToUnicode(strtime,buf);
					}
					rgMyRge.SetItem(_variant_t((long)iItem),_variant_t((long)(col+1)),_variant_t(strtime)); 
//					cell->Set(buf);
					}
		          iItem++;
				}
			}
		}
	//����Ϊ�ļ�
	ExcelApp.SetDisplayAlerts(FALSE);   //���ص����ĶԻ���
	wsMysheet.SaveAs(gstrTimeOut +"\\report\\" + stnames +t1.Format(_T("%Y-%m-%d"))+ ".xls",vtMissing,vtMissing,COleVariant("123"),vtMissing,
		vtMissing,vtMissing,vtMissing,vtMissing,vtMissing);   
    ExcelApp.Quit();
	//�ͷŶ��� 
	rgMyRge.ReleaseDispatch(); 
	wsMysheet.ReleaseDispatch(); 
	wssMysheets.ReleaseDispatch(); 
	wbMyBook.ReleaseDispatch(); 
	wbsMyBooks.ReleaseDispatch(); 
	ExcelApp.ReleaseDispatch(); 
	ShellExecute(0, "open", gstrTimeOut +"\\report\\"+stnames + t1.Format(_T("%Y-%m-%d")) +".xls", NULL, NULL, SW_NORMAL);
}

void CMadeCertView::OnRECDABD() 
{
	CString strtime,strtime2;
	if(m_Realtimedata1._IsOpen())
	{
		m_Realtimedata1.MoveFirst();
		while ( !m_Realtimedata1.IsEOF() )
		{
				int afds = m_Realtimedata1.m_szfds;
				int achan = m_Realtimedata1.m_szchan;
	   		int dbp = mPoint[m_Realtimedata1.m_szPID];
             if(dbp != 6666)
			 {
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
				m_ADRecord[afds][achan][0].duant++;//n������ֵ
			}
			else if(m_alarm == 0)
			{
				if(m_ADRecord[afds][achan][0].duant> 0)
				{
	    			m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].BTime =m_Realtimedata1.m_szrecdate;
	     			m_ADRecord[afds][achan][0].m_ATotalnum++;  //�ܱ�������
	     			m_ADRecord[afds][achan][0].duant = 0;  //״̬ת��
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
	   		int dbp = mPoint[m_Realtimedata.m_szPID];
             if(dbp != 6666)
			 {
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
				m_ADRecord[afds][achan][0].duant++;//n������ֵ
			}
			else if(m_alarm == 0)
			{
				if(m_ADRecord[afds][achan][0].duant> 0)
				{
	    			m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].BTime =m_Realtimedata.m_szrecdate;
	     			m_ADRecord[afds][achan][0].m_ATotalnum++;  //�ܱ�������
	     			m_ADRecord[afds][achan][0].duant = 0;  //״̬ת��
				}
			}
		  }
			 }
			m_Realtimedata.MoveNext();
		}
	}
	CString strtime1,strtime3,strtime4,stnames;
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

	_Application ExcelApp; 
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

	   size_t col = 0;
		int iItem = 3;
		for (int i = 1; i < MAX_FDS;i++)
		{
			for(int j = 1; j < 17;j++ )
			{
     			for(int k = 0; k < 300;k++ )
				{
    				if(m_ADRecord[i][j][k].strlocal == "")
						break;
					{
                       	for(col=0; col<7; col++) {
//                		BasicExcelCell* cell = sheet->Cell(iItem, col);
                		if(col==0)
							strtime =m_SlaveStation[i][j].WatchName;
//                             m_Str2Data.GB2312ToUnicode(m_SlaveStation[i][j].WatchName,buf);
                		else if(col==1)
							strtime = "1";
//                             m_Str2Data.GB2312ToUnicode("1" ,buf);
                		else if(col==2)
						{
							COleDateTime o =m_ADRecord[i][j][k].NTime;
							COleDateTime o1 =m_ADRecord[i][j][k].BTime;
				         	COleDateTimeSpan t = o1-o;
			            	strtime.Format("%d %d:%d:%d",t.GetDays(),t.GetHours(),t.GetMinutes(),t.GetSeconds()); 
//                            m_Str2Data.GB2312ToUnicode(strtime ,buf);
						}
                 		else if(col==3)
							strtime =m_ADRecord[i][j][k].strlocal;
//                          m_Str2Data.GB2312ToUnicode(m_ADRecord[i][j][k].strlocal,buf);
                 		else if(col==4)
						{
          				  COleDateTime oleDateTime=m_ADRecord[i][j][k].NTime;
		        		  strtime   =   oleDateTime.Format(_T("%Y:%m:%d %H:%M:%S")); 
//                          m_Str2Data.GB2312ToUnicode(strtime,buf);
						}
                 		else if(col==5)
						{
          				  COleDateTime oleDateTime=m_ADRecord[i][j][k].BTime;
		        		  strtime   =   oleDateTime.Format(_T("%Y:%m:%d %H:%M:%S")); 
//                          m_Str2Data.GB2312ToUnicode(strtime,buf);
						}
                 		else if(col==6)
							strtime =m_ADRecord[i][j][k].strsafetext;
//                          m_Str2Data.GB2312ToUnicode(m_ADRecord[i][j][k].strsafetext,buf);
					rgMyRge.SetItem(_variant_t((long)iItem),_variant_t((long)(col+1)),_variant_t(strtime)); 
//						cell->Set(buf);
						}
		            	iItem++;
					}//if
				}//k
			}//j
		}//i
	//����Ϊ�ļ�
	ExcelApp.SetDisplayAlerts(FALSE);   //���ص����ĶԻ���
	wsMysheet.SaveAs(gstrTimeOut +"\\report\\" + stnames +t1.Format(_T("%Y-%m-%d"))+ ".xls",vtMissing,vtMissing,COleVariant("123"),vtMissing,
		vtMissing,vtMissing,vtMissing,vtMissing,vtMissing);   
    ExcelApp.Quit();
	//�ͷŶ��� 
	rgMyRge.ReleaseDispatch(); 
	wsMysheet.ReleaseDispatch(); 
	wssMysheets.ReleaseDispatch(); 
	wbMyBook.ReleaseDispatch(); 
	wbsMyBooks.ReleaseDispatch(); 
	ExcelApp.ReleaseDispatch(); 
	ShellExecute(0, "open", gstrTimeOut +"\\report\\"+stnames + t1.Format(_T("%Y-%m-%d")) +".xls", NULL, NULL, SW_NORMAL);
}

void CMadeCertView::OnRECDABB() //�������ϵ�
{
	CString strtime,strtime2;
	if(m_Realtimedata1._IsOpen())
	{
		m_Realtimedata1.MoveFirst();
		while ( !m_Realtimedata1.IsEOF() )
		{
				int afds = m_Realtimedata1.m_szfds;
				int achan = m_Realtimedata1.m_szchan;
	   		int dbp = mPoint[m_Realtimedata1.m_szPID];
             if(dbp != 6666)
			 {
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
				m_ADRecord[afds][achan][0].duant++;//n���ϵ�ֵ
			}
			else if(m_alarm == 0)
			{
				if(m_ADRecord[afds][achan][0].duant> 0)
				{
	    			m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].BTime =m_Realtimedata1.m_szrecdate;
	     			m_ADRecord[afds][achan][0].m_ATotalnum++;  //�ܶϵ����
	     			m_ADRecord[afds][achan][0].duant = 0;  //״̬ת��
				}
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
	   		int dbp = mPoint[m_Realtimedata.m_szPID];
             if(dbp != 6666)
			 {
			int m_alarm = m_Realtimedata.m_szADStatus;
			if(m_alarm == 32)
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
				m_ADRecord[afds][achan][0].duant++;//n���ϵ�ֵ
			}
			else if(m_alarm == 0)
			{
				if(m_ADRecord[afds][achan][0].duant> 0)
				{
	    			m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].BTime =m_Realtimedata.m_szrecdate;
	     			m_ADRecord[afds][achan][0].m_ATotalnum++;  //�ܶϵ����
	     			m_ADRecord[afds][achan][0].duant = 0;  //״̬ת��
				}
			}
			 }
			m_Realtimedata.MoveNext();
		}
	}
	CString strtime1,strtime3,strtime4,stnames;
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

		if(theApp.strargc == "OnEXCELDAB")
		{
			if(m_hours >20)
				stnames = "�������ϵ��ձ���";
			else
				stnames = "�������ϵ�౨��";
		}
		else
				stnames = "�������ϵ��¼��ѯ��ʾ";

		strtime += "    "+strtime1+"    "+strtime2;
	_Application ExcelApp; 
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

	size_t col = 0;
		int iItem = 3;
		for (int i = 1; i < MAX_FDS;i++)
		{
			for(int j = 1; j < 17;j++ )
			{
     			for(int k = 0; k < 300;k++ )
				{
    				if(m_ADRecord[i][j][k].strlocal == "")
						break;
					{
                       	for(col=0; col<7; col++) {
//                		BasicExcelCell* cell = sheet->Cell(iItem, col);
                		if(col==0)
		        		  strtime   =   m_SlaveStation[i][j].WatchName; 
//                             m_Str2Data.GB2312ToUnicode(m_SlaveStation[i][j].WatchName,buf);
                		else if(col==1)
		        		  strtime   =  "1"; 
//                             m_Str2Data.GB2312ToUnicode("1" ,buf);
                		else if(col==2)
						{
							COleDateTime o =m_ADRecord[i][j][k].NTime;
							COleDateTime o1 =m_ADRecord[i][j][k].BTime;
				         	COleDateTimeSpan t = o1-o;
			            	strtime.Format("%d %d:%d:%d",t.GetDays(),t.GetHours(),t.GetMinutes(),t.GetSeconds()); 
//                            m_Str2Data.GB2312ToUnicode(strtime ,buf);
						}
                 		else if(col==3)
		        		  strtime   =   m_ADRecord[i][j][k].strlocal; 
 //                         m_Str2Data.GB2312ToUnicode(m_ADRecord[i][j][k].strlocal,buf);
                 		else if(col==4)
						{
          				  COleDateTime oleDateTime=m_ADRecord[i][j][k].NTime;
		        		  strtime   =   oleDateTime.Format(_T("%Y:%m:%d %H:%M:%S")); 
//                          m_Str2Data.GB2312ToUnicode(strtime,buf);
						}
                 		else if(col==5)
						{
          				  COleDateTime oleDateTime=m_ADRecord[i][j][k].BTime;
		        		  strtime   =   oleDateTime.Format(_T("%Y:%m:%d %H:%M:%S")); 
//                          m_Str2Data.GB2312ToUnicode(strtime,buf);
						}
                 		else if(col==6)
		        		  strtime   =   m_ADRecord[i][j][k].strsafetext; 
//                          m_Str2Data.GB2312ToUnicode(m_ADRecord[i][j][k].strsafetext,buf);
					rgMyRge.SetItem(_variant_t((long)iItem),_variant_t((long)(col+1)),_variant_t(strtime)); 
//						cell->Set(buf);
						}
		            	iItem++;
					}//if
				}//k
			}//j
		}//i
	//����Ϊ�ļ�
	ExcelApp.SetDisplayAlerts(FALSE);   //���ص����ĶԻ���
	wsMysheet.SaveAs(gstrTimeOut +"\\report\\" + stnames +t1.Format(_T("%Y-%m-%d"))+ ".xls",vtMissing,vtMissing,COleVariant("123"),vtMissing,
		vtMissing,vtMissing,vtMissing,vtMissing,vtMissing);   
    ExcelApp.Quit();
	//�ͷŶ��� 
	rgMyRge.ReleaseDispatch(); 
	wsMysheet.ReleaseDispatch(); 
	wssMysheets.ReleaseDispatch(); 
	wbMyBook.ReleaseDispatch(); 
	wbsMyBooks.ReleaseDispatch(); 
	ExcelApp.ReleaseDispatch(); 
	ShellExecute(0, "open", gstrTimeOut +"\\report\\"+stnames + t1.Format(_T("%Y-%m-%d")) +".xls", NULL, NULL, SW_NORMAL);
}

void CMadeCertView::OnRECDFED() //�����������쳣
{
	CString strtime,strtime2;
	if(m_Realtimedata1._IsOpen())
	{
		m_Realtimedata1.MoveFirst();
		while ( !m_Realtimedata1.IsEOF() )
		{
				int afds = m_Realtimedata1.m_szfds;
				int achan = m_Realtimedata1.m_szchan;
	   		int dbp = mPoint[m_Realtimedata1.m_szPID];
             if(dbp != 6666)
			 {
			strtime = m_Realtimedata1.m_szFeedStatus;
			strtime.TrimRight();
			if(strtime == "�쳣")
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
				m_ADRecord[afds][achan][0].duant++;//n�������쳣��¼
			}
			else if(strtime == "����")
			{
				if(m_ADRecord[afds][achan][0].duant> 0)
				{
	    			m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].BTime =m_Realtimedata1.m_szrecdate;
	     			m_ADRecord[afds][achan][0].m_ATotalnum++;  //�������쳣��¼����
	     			m_ADRecord[afds][achan][0].duant = 0;  //״̬ת��
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
	   		int dbp = mPoint[m_Realtimedata.m_szPID];
             if(dbp != 6666)
			 {
			strtime = m_Realtimedata.m_szFeedStatus;
			strtime.TrimRight();
			if(strtime == "�쳣")
			{
//				m_ADRecord[afds][achan][1].duant=100;
//				if()
				{
					m_ADRecord[afds][achan][2].duant =10;
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
			      	m_ADRecord[afds][achan][0].duant++;//n�������쳣��¼ֵ
				}
			}
			else if(strtime == "����")
			{
				if(m_ADRecord[afds][achan][0].duant> 0)
				{
	    			m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].BTime =m_Realtimedata.m_szrecdate;
	     			m_ADRecord[afds][achan][0].m_ATotalnum++;  //�������쳣��¼����
	     			m_ADRecord[afds][achan][0].duant = 0;  //״̬ת��
				}
			}
			 }
			m_Realtimedata.MoveNext();
		}
	}
	CString strtime1,strtime3,strtime4,stnames;
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
	_Application ExcelApp; 
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

	size_t col = 0;
		int iItem = 3;
		for (int i = 1; i < MAX_FDS;i++)
		{
			for(int j = 1; j < 17;j++ )
			{
     			for(int k = 0; k < 300;k++ )
				{
    				if(m_ADRecord[i][j][k].strlocal == "")
						break;
					{
                       	for(col=0; col<7; col++) {
//                		BasicExcelCell* cell = sheet->Cell(iItem, col);
                		if(col==0)
		        		  strtime   =  m_SlaveStation[i][j].WatchName; 
//                             m_Str2Data.GB2312ToUnicode(m_SlaveStation[i][j].WatchName,buf);
                		else if(col==1)
		        		  strtime   =   "1" ; 
//                             m_Str2Data.GB2312ToUnicode("1" ,buf);
                		else if(col==2)
						{
							COleDateTime o =m_ADRecord[i][j][k].NTime;
							COleDateTime o1 =m_ADRecord[i][j][k].BTime;
				         	COleDateTimeSpan t = o1-o;
			            	strtime.Format("%d %d:%d:%d",t.GetDays(),t.GetHours(),t.GetMinutes(),t.GetSeconds()); 
//                            m_Str2Data.GB2312ToUnicode(strtime ,buf);
						}
                 		else if(col==3)
						{
          				  COleDateTime oleDateTime=m_ADRecord[i][j][k].NTime;
		        		  strtime   =   oleDateTime.Format(_T("%Y:%m:%d %H:%M:%S")); 
//                          m_Str2Data.GB2312ToUnicode(strtime,buf);
						}
                 		else if(col==4)
						{
          				  COleDateTime oleDateTime=m_ADRecord[i][j][k].BTime;
		        		  strtime   =   oleDateTime.Format(_T("%Y:%m:%d %H:%M:%S")); 
//                          m_Str2Data.GB2312ToUnicode(strtime,buf);
						}
                 		else if(col==5)
		        		  strtime   =   m_ADRecord[i][j][k].strsafetext; 
//                          m_Str2Data.GB2312ToUnicode(m_ADRecord[i][j][k].strsafetext,buf);
                 		else if(col==6)
		        		  strtime   =   m_ADRecord[i][j][k].strlocal; 
//                          m_Str2Data.GB2312ToUnicode(m_ADRecord[i][j][k].strlocal,buf);

					rgMyRge.SetItem(_variant_t((long)iItem),_variant_t((long)(col+1)),_variant_t(strtime)); 
//						cell->Set(buf);
						}
		            	iItem++;
					}//if
				}//k
			}//j
		}//i
	//����Ϊ�ļ�
	ExcelApp.SetDisplayAlerts(FALSE);   //���ص����ĶԻ���
	wsMysheet.SaveAs(gstrTimeOut +"\\report\\" + stnames +t1.Format(_T("%Y-%m-%d"))+ ".xls",vtMissing,vtMissing,COleVariant("123"),vtMissing,
		vtMissing,vtMissing,vtMissing,vtMissing,vtMissing);   
    ExcelApp.Quit();
	//�ͷŶ��� 
	rgMyRge.ReleaseDispatch(); 
	wsMysheet.ReleaseDispatch(); 
	wssMysheets.ReleaseDispatch(); 
	wbMyBook.ReleaseDispatch(); 
	wbsMyBooks.ReleaseDispatch(); 
	ExcelApp.ReleaseDispatch(); 
	ShellExecute(0, "open", gstrTimeOut +"\\report\\"+stnames + t1.Format(_T("%Y-%m-%d")) +".xls", NULL, NULL, SW_NORMAL);
}

void CMadeCertView::OnRECDSCD() //������״̬�䶯��¼
{
	int m_s[MAX_FDS][MAX_CHAN];
	if(m_Realtimedata1._IsOpen())
	{
		m_Realtimedata1.MoveFirst();
		while ( !m_Realtimedata1.IsEOF() )
		{
				int afds = m_Realtimedata1.m_szfds;
				int achan = m_Realtimedata1.m_szchan;
	   		int dbp = mPoint[m_Realtimedata1.m_szPID];
             if(dbp != 6666)
			 {
	    			int nstatus = m_Realtimedata1.m_szCDValue;
    	    		if(nstatus != m_s[afds][achan])
					{
		         		m_s[afds][achan] = nstatus;
		        		m_ADRecord[afds][achan][0].m_ATotalnum++;
		        		m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].m_ATotalnum =nstatus;
		        		m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].NTime =m_Realtimedata1.m_szrecdate;
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
	   		int dbp = mPoint[m_Realtimedata.m_szPID];
             if(dbp != 6666)
			 {
        				int nstatus = m_Realtimedata.m_szCDValue;
            			if(nstatus != m_s[afds][achan])
						{
	              			m_s[afds][achan] = nstatus;
	            			m_ADRecord[afds][achan][0].m_ATotalnum++;
	             			m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].m_ATotalnum =nstatus;
		            		m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].NTime =m_Realtimedata.m_szrecdate;
						}
			 }
			m_Realtimedata.MoveNext();
		}
	}

	CString strtime,strtime1,stnames;
	CString strtime2,strtime3,strtime4;
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
	_Application ExcelApp; 
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

	size_t col = 0;
		int iItem = 3;
		for (int i = 1; i < MAX_FDS;i++)
		{
			for(int j = 1; j < 17;j++ )
			{
				if(m_SlaveStation[i][j].ptype >3)
				{
     			for(int k = 1; k < 300;k++ )
				{
					if( k> m_ADRecord[i][j][0].m_ATotalnum)
						break;

                	for(col=0; col<5; col++) {
//              		BasicExcelCell* cell = sheet->Cell(iItem, col);
         	      	if(col==0)
					rgMyRge.SetItem(_variant_t((long)iItem),_variant_t((long)(col+1)),_variant_t(m_SlaveStation[i][j].WatchName)); 
//                      m_Str2Data.GB2312ToUnicode(m_SlaveStation[i][j].WatchName,buf);
                 	else if(col==1)
					rgMyRge.SetItem(_variant_t((long)iItem),_variant_t((long)(col+1)),_variant_t("1")); 
//                      m_Str2Data.GB2312ToUnicode("1" ,buf);
         	      	else if(col==2)
					{
					  int nstatus = m_ADRecord[i][j][k].m_ATotalnum;
					  if(nstatus == 0)
						  strtime= m_SlaveStation[i][j].ZeroState;
					  else if(nstatus == 1)
						  strtime= m_SlaveStation[i][j].OneState;
					  else if(nstatus == 2)
						  strtime= m_SlaveStation[i][j].TwoState;
//                      m_Str2Data.GB2312ToUnicode(strtime ,buf);
					rgMyRge.SetItem(_variant_t((long)iItem),_variant_t((long)(col+1)),_variant_t(strtime)); 
					}
         	      	else if(col==3)
					{
			     	  COleDateTime oleDateTime=m_ADRecord[i][j][k].NTime;
			    	  strtime   =   oleDateTime.Format(_T("%Y:%m:%d %H:%M:%S")); 
//                      m_Str2Data.GB2312ToUnicode(strtime,buf);
					rgMyRge.SetItem(_variant_t((long)iItem),_variant_t((long)(col+1)),_variant_t(strtime)); 
					}
                		else if(col==4)
						{
			        		if(k > 1)
							{
//				    			cell = sheet->Cell(iItem-1, col);
				    			COleDateTime o =m_ADRecord[i][j][k-1].NTime;
					    		COleDateTime o1 =m_ADRecord[i][j][k].NTime;
				             	COleDateTimeSpan t = o1-o;
			                	strtime.Format("%d %d:%d:%d",t.GetDays(),t.GetHours(),t.GetMinutes(),t.GetSeconds()); 
//                                m_Str2Data.GB2312ToUnicode(strtime ,buf);
					rgMyRge.SetItem(_variant_t((long)(iItem-1)),_variant_t((long)(col+1)),_variant_t(strtime)); 
							}
						}
//            		cell->Set(buf);
					}
	           		iItem++;
				}
				}
			}
		}
	//����Ϊ�ļ�
	ExcelApp.SetDisplayAlerts(FALSE);   //���ص����ĶԻ���
	wsMysheet.SaveAs(gstrTimeOut +"\\report\\" + stnames +t1.Format(_T("%Y-%m-%d"))+ ".xls",vtMissing,vtMissing,COleVariant("123"),vtMissing,
		vtMissing,vtMissing,vtMissing,vtMissing,vtMissing);   
    ExcelApp.Quit();
	//�ͷŶ��� 
	rgMyRge.ReleaseDispatch(); 
	wsMysheet.ReleaseDispatch(); 
	wssMysheets.ReleaseDispatch(); 
	wbMyBook.ReleaseDispatch(); 
	wbsMyBooks.ReleaseDispatch(); 
	ExcelApp.ReleaseDispatch(); 
	ShellExecute(0, "open", gstrTimeOut +"\\report\\"+stnames + t1.Format(_T("%Y-%m-%d")) +".xls", NULL, NULL, SW_NORMAL);
}

void CMadeCertView::OnRECDRIVERE()   //�豸���ϼ�¼
{
	CString strtime,strtime2;
	if(m_Realtimedata1._IsOpen())
	{
		m_Realtimedata1.MoveFirst();
		while ( !m_Realtimedata1.IsEOF() )
		{
				int afds = m_Realtimedata1.m_szfds;
				int achan = m_Realtimedata1.m_szchan;
	   		int dbp = mPoint[m_Realtimedata1.m_szPID];
             if(dbp != 6666)
			 {
			int m_alarm = m_Realtimedata1.m_szADStatus;
			if(m_alarm > 47)
			{
				if(m_ADRecord[afds][achan][0].duant == 0)
					m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].NTime =m_Realtimedata1.m_szrecdate;
				m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].BTime =m_Realtimedata1.m_szrecdate;
				m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].havev = m_Realtimedata1.m_szADStatus;

					strtime = m_Realtimedata1.m_szsafemtext;
					strtime.TrimRight();
					if(strtime != "")
					{
          				  COleDateTime t=m_Realtimedata1.m_szrecdate;
		        		  strtime2   =   t.Format(_T("%Y-%m-%d %H:%M:%S")); 
//	       	    		m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].RTime = m_Realtimedata1.m_szrecdate;
	       	    		m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].strsafetext += strtime+"|"+strtime2+"|";
					}
				m_ADRecord[afds][achan][0].duant++;//n���豸����ֵ
			}
			else if(m_alarm < 48)
			{
				if(m_ADRecord[afds][achan][0].duant> 0)
				{
	    			m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].BTime =m_Realtimedata1.m_szrecdate;
	     			m_ADRecord[afds][achan][0].m_ATotalnum++;  //���豸���ϴ���
	     			m_ADRecord[afds][achan][0].duant = 0;  //״̬ת��
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
	   		int dbp = mPoint[m_Realtimedata.m_szPID];
             if(dbp != 6666)
			 {
			int m_alarm = m_Realtimedata.m_szADStatus;
			if(m_alarm > 47)
			{
				if(m_ADRecord[afds][achan][0].duant == 0)
					m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].NTime =m_Realtimedata.m_szrecdate;
				m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].BTime =m_Realtimedata.m_szrecdate;
				m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].havev = m_Realtimedata.m_szADStatus;

				strtime = m_Realtimedata.m_szsafemtext;
					strtime.TrimRight();
					if(strtime != "")
					{
          				  COleDateTime t=m_Realtimedata.m_szrecdate;
		        		  strtime2   =   t.Format(_T("%Y-%m-%d %H:%M:%S")); 
	       	    		m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].strsafetext += strtime+"|"+strtime2+"|";
					}
				m_ADRecord[afds][achan][0].duant++;//n���豸����ֵ
			}
			else if(m_alarm < 48)
			{
				if(m_ADRecord[afds][achan][0].duant> 0)
				{
	    			m_ADRecord[afds][achan][m_ADRecord[afds][achan][0].m_ATotalnum].BTime =m_Realtimedata.m_szrecdate;
	     			m_ADRecord[afds][achan][0].m_ATotalnum++;  //���豸���ϴ���
	     			m_ADRecord[afds][achan][0].duant = 0;  //״̬ת��
				}
			}
			 }
			m_Realtimedata.MoveNext();
		}
	}
	CString strtime1,strtime3,strtime4,stnames;
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
	_Application ExcelApp; 
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

	size_t col = 0;
		int iItem = 3;
		for (int i = 1; i < MAX_FDS;i++)
		{
			for(int j = 1; j < MAX_CHAN;j++ )
			{
     			for(int k = 0; k < 300;k++ )
				{
    				if(m_ADRecord[i][j][k].havev == 0)
						break;

					    for(col=0; col<7; col++) {
//                		BasicExcelCell* cell = sheet->Cell(iItem, col);
                		if(col==0)
							strtime =m_SlaveStation[i][j].WatchName;
//                             m_Str2Data.GB2312ToUnicode(m_SlaveStation[i][j].WatchName,buf);
                		else if(col==1)
							strtime ="1" ;
//                             m_Str2Data.GB2312ToUnicode("1" ,buf);
                		else if(col==2)
						{
							COleDateTime o =m_ADRecord[i][j][k].NTime;
							COleDateTime o1 =m_ADRecord[i][j][k].BTime;
				         	COleDateTimeSpan t = o1-o;
			            	strtime.Format("%d %d:%d:%d",t.GetDays(),t.GetHours(),t.GetMinutes(),t.GetSeconds()); 
//                            m_Str2Data.GB2312ToUnicode(strtime ,buf);
						}
                 		else if(col==3)
						{
          				  COleDateTime oleDateTime=m_ADRecord[i][j][k].NTime;
		        		  strtime   =   oleDateTime.Format(_T("%Y:%m:%d %H:%M:%S")); 
//                          m_Str2Data.GB2312ToUnicode(strtime,buf);
						}
                 		else if(col==4)
						{
          				  COleDateTime oleDateTime=m_ADRecord[i][j][k].BTime;
		        		  strtime   =   oleDateTime.Format(_T("%Y:%m:%d %H:%M:%S")); 
//                          m_Str2Data.GB2312ToUnicode(strtime,buf);
						}
                 		else if(col==5)
		        		  strtime   =   m_ADRecord[i][j][k].strsafetext; 
//                          m_Str2Data.GB2312ToUnicode(m_ADRecord[i][j][k].strsafetext,buf);
                 		else if(col==6)
						{
							strtime= theApp.socketClient.strstatus(m_ADRecord[i][j][k].havev);
//                            m_Str2Data.GB2312ToUnicode(strtime,buf);
						}
					rgMyRge.SetItem(_variant_t((long)iItem),_variant_t((long)(col+1)),_variant_t(strtime)); 
//						cell->Set(buf);
						}
		            	iItem++;
				}//k
			}//j
		}//i
	//����Ϊ�ļ�
	ExcelApp.SetDisplayAlerts(FALSE);   //���ص����ĶԻ���
	wsMysheet.SaveAs(gstrTimeOut +"\\report\\" + stnames +t1.Format(_T("%Y-%m-%d"))+ ".xls",vtMissing,vtMissing,COleVariant("123"),vtMissing,
		vtMissing,vtMissing,vtMissing,vtMissing,vtMissing);   
    ExcelApp.Quit();
	//�ͷŶ��� 
	rgMyRge.ReleaseDispatch(); 
	wsMysheet.ReleaseDispatch(); 
	wssMysheets.ReleaseDispatch(); 
	wbMyBook.ReleaseDispatch(); 
	wbsMyBooks.ReleaseDispatch(); 
	ExcelApp.ReleaseDispatch(); 
	ShellExecute(0, "open", gstrTimeOut +"\\report\\"+stnames + t1.Format(_T("%Y-%m-%d")) +".xls", NULL, NULL, SW_NORMAL);
}

void CMadeCertView::OnEXCELA() 
{
		for(int i = 1; i < MAX_FDS;i++ )
			for(int j = 1; j < MAX_CHAN;j++ )
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
	CString strtime,strtime2;
	if(m_Realtimedata1._IsOpen())
	{
		m_Realtimedata1.MoveFirst();
		while ( !m_Realtimedata1.IsEOF() )
		{
    	   		int dbp = mPoint[m_Realtimedata1.m_szPID];
             if(dbp != 6666)
			 {
				int afds = m_Realtimedata1.m_szfds;
				int achan = m_Realtimedata1.m_szchan;
				int ffds = m_Realtimedata1.m_szffds;
				int fchan = m_Realtimedata1.m_szfchan;
    			int m_alarm = m_Realtimedata1.m_szADStatus;
	    		if(m_alarm == 00 ||m_alarm == 16 ||m_alarm == 32)
				{//ƽ��ֵ0
			    	m_ADRecord[afds][achan][0].m_ATotalnum++;
			    	m_ADRecord[afds][achan][0].ATotalV +=m_Realtimedata1.m_szAValue;
			    	if(m_ADRecord[afds][achan][1].ATotalV <m_Realtimedata1.m_szAValue)
					{//���ֵ  ʱ��1
    			    	m_ADRecord[afds][achan][1].ATotalV = m_Realtimedata1.m_szAValue;
		    	    	m_ADRecord[afds][achan][1].ATime = m_Realtimedata1.m_szrecdate;
					}
				}
				strtime = m_Realtimedata1.m_szFeedStatus;
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
    						m_ADRecord[ffds][fchan][ffdschan].tmid += m_Realtimedata1.m_szrecdate -m_ADRecord[ffds][fchan][ffdschan].ATime;
						m_ADRecord[ffds][fchan][ffdschan].ATime = m_Realtimedata1.m_szrecdate;
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
    						m_ADRecord[afds][achan][8].tmid += m_Realtimedata1.m_szrecdate -m_ADRecord[afds][achan][8].ATime;
						m_ADRecord[afds][achan][8].ATime = m_Realtimedata1.m_szrecdate;
        				m_ADRecord[afds][achan][2].duant++;
					}
					if(m_alarm ==32 ||m_alarm ==64 ||m_alarm ==80 ||m_alarm ==96 ||m_alarm ==112 ||m_alarm ==128)//�ϵ�������ʱ��9
					{
						if(m_ADRecord[afds][achan][4].duant != 0)
    						m_ADRecord[afds][achan][9].tmid += m_Realtimedata1.m_szrecdate-m_ADRecord[afds][achan][9].ATime;
						m_ADRecord[afds][achan][9].ATime = m_Realtimedata1.m_szrecdate;
        				m_ADRecord[afds][achan][4].duant++;
					}

			 }//dbp != 6666
			m_Realtimedata1.MoveNext();
		}
	}
	if(!m_Realtimedata._IsEmpty())
	{
		m_Realtimedata.MoveFirst();
		while ( !m_Realtimedata.IsEOF() )
		{
    	   		int dbp = mPoint[m_Realtimedata.m_szPID];
             if(dbp != 6666)
			 {
				int afds = m_Realtimedata.m_szfds;
				int achan = m_Realtimedata.m_szchan;
				int ffds = m_Realtimedata.m_szffds;
				int fchan = m_Realtimedata.m_szfchan;
    			int m_alarm = m_Realtimedata.m_szADStatus;
	    		if(m_alarm == 0 ||m_alarm == 16 ||m_alarm == 32)
				{//ƽ��ֵ10
			    	m_ADRecord[afds][achan][10].m_ATotalnum++;
			    	m_ADRecord[afds][achan][10].ATotalV +=m_Realtimedata.m_szAValue;
			    	if(m_ADRecord[afds][achan][1].ATotalV <m_Realtimedata.m_szAValue)
					{//���ֵ  ʱ��1
    			    	m_ADRecord[afds][achan][1].ATotalV = m_Realtimedata.m_szAValue;
		    	    	m_ADRecord[afds][achan][1].ATime = m_Realtimedata.m_szrecdate;
					}
				}
				strtime = m_Realtimedata.m_szFeedStatus;
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
    						m_ADRecord[ffds][fchan][ffdschan].tmid += m_Realtimedata.m_szrecdate -m_ADRecord[ffds][fchan][ffdschan].ATime;
						m_ADRecord[ffds][fchan][ffdschan].ATime = m_Realtimedata.m_szrecdate;
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
    						m_ADRecord[afds][achan][17].tmid += m_Realtimedata.m_szrecdate -m_ADRecord[afds][achan][17].ATime;
						m_ADRecord[afds][achan][17].ATime = m_Realtimedata.m_szrecdate;
        				m_ADRecord[afds][achan][8].duant++;
					}
					if(m_alarm ==32 ||m_alarm ==64 ||m_alarm ==80 ||m_alarm ==96 ||m_alarm ==112 ||m_alarm ==128)//�ϵ�������ʱ��18
					{
						if(m_ADRecord[afds][achan][9].duant != 0)
    						m_ADRecord[afds][achan][18].tmid += m_Realtimedata.m_szrecdate-m_ADRecord[afds][achan][18].ATime;
						m_ADRecord[afds][achan][18].ATime = m_Realtimedata.m_szrecdate;
        				m_ADRecord[afds][achan][9].duant++;
					}
			 }//dbp != 6666
			m_Realtimedata.MoveNext();
		}
	}

	CString stnames;
	CString strtime1,strtime3,strtime4;
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

	_Application ExcelApp; 
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

		int iItem = 3;//4
		for ( i = 1; i < MAX_FDS;i++)
		{
			for(int j = 1; j < 17;j++ )
			{
//     			for(int k = 0; k < 300;k++ )
				{
    				if(m_ADRecord[i][j][10].m_ATotalnum != 0)
					{
                    for(col=0; col<10; col++) 
					{
//                		BasicExcelCell* cell = sheet->Cell(iItem, col);
                		if(col==0)
							strtime =m_SlaveStation[i][j].WatchName;
//                             m_Str2Data.GB2312ToUnicode(m_SlaveStation[i][j].WatchName,buf);
                		else if(col==1)
						{
							float m_fm = (m_ADRecord[i][j][0].ATotalV+m_ADRecord[i][j][10].ATotalV)/(m_ADRecord[i][j][0].m_ATotalnum+m_ADRecord[i][j][10].m_ATotalnum);
				        	  strtime.Format("%.2f",m_fm);
//                            m_Str2Data.GB2312ToUnicode(strtime ,buf);
						}
                		else if(col==2)
						{
				        	  strtime.Format("%.2f",m_ADRecord[i][j][1].ATotalV);
//                            m_Str2Data.GB2312ToUnicode(strtime ,buf);
						}
                 		else if(col==3)
						{
//          				  COleDateTime oleDateTime=m_ADRecord[i][j][1].ATime;
		        		  strtime   =   m_ADRecord[i][j][1].ATime.Format(_T("%Y:%m:%d %H:%M:%S")); 
//                          m_Str2Data.GB2312ToUnicode(strtime,buf);
						}
                 		else if(col==4)
						{
				        	  strtime.Format("%d",m_ADRecord[i][j][6].m_ATotalnum+m_ADRecord[i][j][15].m_ATotalnum);
//                          m_Str2Data.GB2312ToUnicode(strtime,buf);
						}
                 		else if(col==5)
						{
          			    	  COleDateTimeSpan t =m_ADRecord[i][j][8].tmid +m_ADRecord[i][j][17].tmid;
			            	strtime.Format("%d %d:%d:%d",t.GetDays(),t.GetHours(),t.GetMinutes(),t.GetSeconds()); 
//                            m_Str2Data.GB2312ToUnicode(strtime,buf);
						}
                 		else if(col==6)
						{
				        	  strtime.Format("%d",m_ADRecord[i][j][7].m_ATotalnum+m_ADRecord[i][j][16].m_ATotalnum);
//                              m_Str2Data.GB2312ToUnicode(strtime,buf);
						}
                 		else if(col==7)
						{
          			    	  COleDateTimeSpan t =m_ADRecord[i][j][9].tmid +m_ADRecord[i][j][18].tmid;
			            	strtime.Format("%d %d:%d:%d",t.GetDays(),t.GetHours(),t.GetMinutes(),t.GetSeconds()); 
//                            m_Str2Data.GB2312ToUnicode(strtime,buf);
						}
						else if(col==8) 
						{
				        	  strtime.Format("%d",m_ADRecord[i][j][3].m_ATotalnum+m_ADRecord[i][j][12].m_ATotalnum);
//                          m_Str2Data.GB2312ToUnicode(strtime,buf);
						}
                 		else if(col==9)
						{
							COleDateTimeSpan t=0;
          			    	t =m_ADRecord[i][j][5].tmid +m_ADRecord[i][j][14].tmid;
			            	strtime.Format("%d %d:%d:%d",t.GetDays(),t.GetHours(),t.GetMinutes(),t.GetSeconds()); 
//                            m_Str2Data.GB2312ToUnicode(strtime,buf);
						}
					rgMyRge.SetItem(_variant_t((long)iItem),_variant_t((long)(col+1)),_variant_t(strtime)); 
//						cell->Set(buf);
					}
	             	iItem++;
					}
				}//k
			}//j
		}//i

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
	ExcelApp.SetDisplayAlerts(FALSE);   //���ص����ĶԻ���
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

	((CRaChildFrame*)GetParentFrame( ))->Msg("��ʼ֤������,��ȴ�");
	CMadeCertDlg dlg;
	dlg.DoModal();
	m_List.DeleteItem(m_select);
	((CRaChildFrame*)GetParentFrame( ))->Msg("֤�������ɹ�!");
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
	m_num=m_List.GetItemText(m_select,0);//�ڲ����*/

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
    if ( m_CommonSet._IsOpen() )
         m_CommonSet.Close();

    m_Cn.Close();
    //Cleanup the AxLib library
    dbAx::Term();
  }
  catch ( CAxException *e )
  {
    MessageBox(e->m_szErrorDesc, _T("BJygjl Message"), MB_OK);
    delete e;
  }
//	if(m_bExcelInit)
//		::CoUninitialize();  //EXCEL

	CFormView::OnDestroy();
	((CMainFrame*)AfxGetMainWnd())->m_pMade=NULL; // ��մ���ָ��
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
     		m_CommonSet.Open(strPointNo, &m_Cn);
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
					m_tnum = nItemCount;
		 if ( m_CommonSet._IsOpen() )
                 m_CommonSet.Close();
	      	CString strPointNo; 
     		strPointNo.Format(_T("SELECT * From commonset WHERE CommonID = %d"),nItemCount+1);
     		m_CommonSet.Open(strPointNo, &m_Cn);
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

void CMadeCertView::InitStr() 
{
		m_Points.clear();
          		for(int k = 0; k < 1000;k++ )
	             		mPoint[k] =6666;
		for(int i = 1; i < MAX_FDS;i++ )
			for(int j = 1; j < MAX_CHAN;j++ )
			{
				if(theApp.strargc == "OnEXCELA")
				{
	     			for(int h = 0; h < 300;h++)
					{
					m_ADRecord[i][j][h].m_ATotalnum = 0;
					m_ADRecord[i][j][h].ATotalV = 0;
					m_ADRecord[i][j][h].duant = 0;
					m_ADRecord[i][j][h].strlocal = "";
					m_ADRecord[i][j][h].tmid = 0;
					m_ADRecord[i][j][h].havev = 0;
					m_ADRecord[i][j][h].AavV = 0;
    					m_ADRecord[i][j][h].strsafetext = "����";
					}
				}
				else
				{
	     			for(int h = 0; h < 300;h++)
					{
					m_ADRecord[i][j][h].m_ATotalnum = 0;
					m_ADRecord[i][j][h].ATotalV = 0;
					m_ADRecord[i][j][h].duant = 0;
					m_ADRecord[i][j][h].strlocal = "";
					m_ADRecord[i][j][h].tmid = 0;
					m_ADRecord[i][j][h].havev = 0;
					m_ADRecord[i][j][h].AavV = 0;
					}
				}
			}
		for(int h = 0; h < m_tnum;h++)
		{
      		for(int i = 0; i < 500;i++)
			{
					m_ADP[h][i].m_ATotalnum = 0;
					m_ADP[h][i].ATotalV = 0;
					m_ADP[h][i].duant = 0;
					m_ADP[h][i].strlocal = "";
					m_ADP[h][i].strsafetext = "";
					m_ADP[h][i].havev = 0;
					m_ADP[h][i].AavV = 0;
			}
		}


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
