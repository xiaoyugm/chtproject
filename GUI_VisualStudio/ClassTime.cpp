// ClassTime.cpp : implementation file
//

#include "stdafx.h"
#include "gui_visualstudio.h"
#include "ClassTime.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern  OthersSetting    m_OthersSetting;
/////////////////////////////////////////////////////////////////////////////
// CClassTime dialog


CClassTime::CClassTime(CWnd* pParent /*=NULL*/)
	: CXTResizeDialog(CClassTime::IDD, pParent)
{
	//{{AFX_DATA_INIT(CClassTime)
	m_cd = 0;
	m_cn = 1;
	//}}AFX_DATA_INIT
}


void CClassTime::DoDataExchange(CDataExchange* pDX)
{
	CXTResizeDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CClassTime)
	DDX_Text(pDX, IDC_EDIT_DAYREPORT, m_cd);
//	DDV_MaxChars(pDX, strcd, 2);
//	DDV_MinMaxUInt(pDX, m_cd, 0, 23);
	DDX_Text(pDX, IDC_EDIT_CLASSNUM, m_cn);
//	DDV_MinMaxUInt(pDX, m_cn, 0, 4);
//	DDV_MaxChars(pDX, strcd, 1);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CClassTime, CXTResizeDialog)
	//{{AFX_MSG_MAP(CClassTime)
	ON_EN_CHANGE(IDC_EDIT_DAYREPORT, OnChadayr)
	ON_EN_CHANGE(IDC_EDIT_CLASSNUM, OnChaclass)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CClassTime message handlersBOOL CLoginDlg::OnInitDialog() 
BOOL CClassTime::OnInitDialog() 
{
	CXTResizeDialog::OnInitDialog();
	
	int screenx=GetSystemMetrics (SM_CXSCREEN);
	int screeny=GetSystemMetrics (SM_CYSCREEN);
	ConnectDB();  //连接数据库
//	m_listUser.ModifyExtendedStyle(0, LVS_EX_FULLROWSELECT|LVS_SHOWSELALWAYS | LVS_EX_GRIDLINES);
//	SetResize(IDC_LIST_USER,         SZ_TOP_LEFT,    SZ_BOTTOM_RIGHT);

		m_CommonSet.MoveFirst();
		while ( !m_CommonSet.IsEOF() )
		{
			//班设置 1
        	CString  strc = m_CommonSet.m_szstrc1;
			strc.TrimRight();
			if(strc == "")
				break;
			int coxx = m_CommonSet.m_szCommonID;
			if(coxx == 1)
	     		GetDlgItem(IDC_EDIT_DAYREPORT)->SetWindowText(strc);   //班初始时间
            else
	       		GetDlgItem(IDC_EDIT_CLASSNUM)->SetWindowText(strc);  //班次
//	UpdateData(FALSE);
			m_CommonSet.MoveNext();
		}
//		szFind.Format("%d",m_CommonSet.m_sznum2);
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CClassTime::ConnectDB()
{
  CString szConnect = _T("Provider=SQLOLEDB.1;Persist Security Info=True;\
                          User ID=sa;Password=sunset;\
                          Data Source=") +m_OthersSetting.DBname+ _T(";Initial Catalog=BJygjl");
	try
	{
       dbAx::Init();
       m_Cn.Create();
//       m_Cn._SetConnectionEvents(new CCardFileEvents);
       m_Cn.CursorLocation(adUseClient);
       m_Cn.Open((LPCTSTR)szConnect);

		m_CommonSet.Create();
		m_CommonSet.CursorType(adOpenDynamic);
		m_CommonSet.CacheSize(50);
		m_CommonSet._SetRecordsetEvents(new CAccountSetEvents);
		m_CommonSet.Open(_T("Select * From commonset"), &m_Cn);
		m_CommonSet.MarshalOptions(adMarshalModifiedOnly);
     	m_CommonSetNew = &m_CommonSet;
	}
    catch ( dbAx::CAxException *e )
	{
    MessageBox(e->m_szErrorDesc, _T("BJygjl Message"), MB_OK);
    delete e;
    return ;
	}
}

void CClassTime::OnChadayr() 
{
	UpdateData(TRUE);
		CString cccc;
		GetDlgItem(IDC_EDIT_DAYREPORT)->GetWindowText(cccc);
		int nfds3 = m_Str2Data.String2Int(cccc);
		if(nfds3<0 || nfds3>23)
		{
          	AfxMessageBox("初始日报时间在0-23间选择！", MB_OK);
    		GetDlgItem(IDC_EDIT_DAYREPORT)->SetWindowText("22");
	    	  return;
		}
	UpdateData(FALSE);
}

void CClassTime::OnChaclass() 
{
	UpdateData(TRUE);
		CString cccc;
		GetDlgItem(IDC_EDIT_CLASSNUM)->GetWindowText(cccc);
		int nfds3 = m_Str2Data.String2Int(cccc);
		if(nfds3<1 || nfds3>3)
		{
          	AfxMessageBox("初始日报时间在1-3间选择！", MB_OK);
    		GetDlgItem(IDC_EDIT_CLASSNUM)->SetWindowText("3");
	    	  return;
		}
	UpdateData(FALSE);
}

void CClassTime::OnOK() 
{
	UpdateData(TRUE);
	for(int i=1 ; i< 3 ;i++)
	{
        if ( m_CommonSet._IsOpen() )
               m_CommonSet.Close();
		m_CommonSet.Create();
		m_CommonSet.CursorType(adOpenDynamic);
		m_CommonSet.CacheSize(50);
		m_CommonSet._SetRecordsetEvents(new CAccountSetEvents);
		CString strPointNo; 
		strPointNo.Format(_T("SELECT * From commonset WHERE CommonID = %d"),i);
		m_CommonSet.Open(strPointNo, &m_Cn);
		m_CommonSet.MarshalOptions(adMarshalModifiedOnly);
     	m_CommonSetNew = &m_CommonSet;
            				try
							{
	         				 m_CommonSetNew->m_szCommonID  = i;
							 if(i == 1)
    		      			     m_CommonSetNew->m_szstrc1 = theApp.m_Str2Data.Int2CString(m_cd);
							 else if(i == 2)
    		      			     m_CommonSetNew->m_szstrc1 = theApp.m_Str2Data.Int2CString(m_cn);
//		    			     m_CommonSetNew->m_sznum2 = m_classnum;
//      						m_CommonSetNew->AddNew();  //Add a new, blank record
					   	    m_CommonSetNew->Update();    //Update the recordset
							//If this is a new record, requery the database table
							//otherwise we may out-of-sync
//						    m_CommonSetNew->Requery();
							}
		     			    catch (CAxException *e)
							{
					        	AfxMessageBox(e->m_szErrorDesc, MB_OK);
				        		delete e;
							}
	}
    if ( m_CommonSet._IsOpen() )
      m_CommonSet.Close();
    m_Cn.Close();
    dbAx::Term();

	theApp.InitData();

	CDialog::OnOK();
}

void CClassTime::OnCancel() 
{
	// TODO: Add extra cleanup here
	
    if ( m_CommonSet._IsOpen() )
      m_CommonSet.Close();
    m_Cn.Close();
    dbAx::Term();
	CDialog::OnCancel();
}
