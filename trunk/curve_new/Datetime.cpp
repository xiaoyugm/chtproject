// Datetime.cpp : implementation file
//

#include "stdafx.h"
#include "Curve.h"
#include "Datetime.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDatetime dialog


CDatetime::CDatetime(CWnd* pParent /*=NULL*/)
	: CDialog(CDatetime::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDatetime)
	m_time = 0;
	//}}AFX_DATA_INIT
}


void CDatetime::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDatetime)
	DDX_MonthCalCtrl(pDX, IDC_MONTHCALENDAR, m_time);
	//}}AFX_DATA_MAP
//	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDatetime, CDialog)
	//{{AFX_MSG_MAP(CDatetime)
	ON_NOTIFY(MCN_SELECT, IDC_MONTHCALENDAR, OnSelectMonthcalendar)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDatetime message handlers

void CDatetime::OnSelectMonthcalendar(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	int d = m_time.GetYear();
	d = m_time.GetMonth();
	d = m_time.GetDay();
	*pResult = 0;
}

BOOL CDatetime::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
//	SYSTEMTIME tm;
//	GetLocalTime(&tm);
//	CTime time(tm);
//	m_time = time;

//	CDialog::OnInitDialog();
//	m_time = 0;
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
