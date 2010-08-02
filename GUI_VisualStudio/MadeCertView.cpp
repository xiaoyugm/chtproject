// MadeCertView.cpp : implementation file
//

#include "stdafx.h"
#include "GUI_VisualStudio.h"
#include "MadeCertView.h"
#include "ChildFrm.h"
//#include "ViewInfoDlg.h"
#include "MainFrm.h"
//#include "MadeCertDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMadeCertView
//extern CString str[35];
IMPLEMENT_DYNCREATE(CMadeCertView, CFormView)

CMadeCertView::CMadeCertView()
	: CFormView(CMadeCertView::IDD)
{
	//{{AFX_DATA_INIT(CMadeCertView)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_select=-1;
//	m_bitMadeView.LoadBitmap(IDB_BITMAPVIEWMADE);
//	m_bitMadeViewUser.LoadBitmap(IDB_BITMAPVIEWUSER);
//	m_bitMadeCert.LoadBitmap(IDB_BITMAPMADECERT);

}

CMadeCertView::~CMadeCertView()
{
}

void CMadeCertView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMadeCertView)
//	DDX_Control(pDX, IDC_LIST_MADE, m_List);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMadeCertView, CFormView)
	//{{AFX_MSG_MAP(CMadeCertView)
//	ON_BN_CLICKED(IDC_BUTTON_LINEANDMADE, OnButtonLineandmade)
//	ON_BN_CLICKED(IDC_BUTTON_VIEWINFO, OnButtonViewinfo)
///	ON_BN_CLICKED(IDC_BUTTON_AUT_MADE, OnButtonAutMade)
//	ON_NOTIFY(NM_CLICK, IDC_LIST_MADE, OnClickListMade)
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
	GetParentFrame()->SetWindowPos(NULL,0,0,GetSystemMetrics(SM_CXSCREEN)-8,140,SWP_NOMOVE|SWP_NOZORDER | SWP_NOACTIVATE|SWP_SHOWWINDOW);

	

//	((CComboBox *)GetDlgItem(IDC_COMBO1))->SetCurSel(0);

	// TODO: Add your specialized code here and/or call the base class
//	m_List.SetWindowPos(NULL,0,0,1024,400,SWP_NOMOVE|SWP_NOZORDER | SWP_NOACTIVATE);
//	m_List.SetExtendedStyle(LVS_EX_FULLROWSELECT);

	CString strname[10];
	strname[0]="内部序列号";
	strname[1]="证书持有者ID";
	strname[2]="证书有效期";
	strname[3]="证书序列号";
	strname[4]="证书级别";
	strname[5]="证书有效起始日期";
	strname[6]="证书有效终止日期";
	strname[7]="密钥用途";
	strname[8]="证书状态";
	strname[9]="存储介质";
	for(int i=0;i<10;i++)
	{
//		m_List.InsertColumn(i,strname[i],LVCFMT_LEFT,120);
	}
	GetParentFrame()->SetWindowText("证书制作");
}

void CMadeCertView::OnButtonLineandmade() 
{
	// TODO: Add your control notification handler code here
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
	CFormView::OnDestroy();
	((CMainFrame*)AfxGetMainWnd())->m_pMade=NULL; // 清空窗口指针

	// TODO: Add your message handler code here
	
}
