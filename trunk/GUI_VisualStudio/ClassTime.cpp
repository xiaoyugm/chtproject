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
	m_ctrlDayH = 0;
	m_classnum = 0;
	//}}AFX_DATA_INIT
}


void CClassTime::DoDataExchange(CDataExchange* pDX)
{
	CXTResizeDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CClassTime)
	DDX_Text(pDX, IDC_EDIT_DAYREPORT, m_ctrlDayH);
	DDV_MinMaxUInt(pDX, m_ctrlDayH, 0, 23);
	DDX_Text(pDX, IDC_EDIT_CLASSNUM, m_classnum);
	DDV_MinMaxUInt(pDX, m_classnum, 0, 4);
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

		CString	 szFind;
		szFind.Format("%d",m_CommonSet.m_sznum1);
		GetDlgItem(IDC_EDIT_DAYREPORT)->SetWindowText(szFind);
		szFind.Format("%d",m_CommonSet.m_sznum2);
		GetDlgItem(IDC_EDIT_CLASSNUM)->SetWindowText(szFind);
	
	UpdateData(FALSE);
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
	UpdateData(FALSE);
}

void CClassTime::OnChaclass() 
{
	UpdateData(TRUE);
	UpdateData(FALSE);
}

void CClassTime::OnOK() 
{
            				try
							{
	         				 m_CommonSetNew->m_szCommonID  = 1;
		      			     m_CommonSetNew->m_sznum1 = m_ctrlDayH;
		    			     m_CommonSetNew->m_sznum2 = m_classnum;
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
    if ( m_CommonSet._IsOpen() )
      m_CommonSet.Close();
    m_Cn.Close();
    dbAx::Term();

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
