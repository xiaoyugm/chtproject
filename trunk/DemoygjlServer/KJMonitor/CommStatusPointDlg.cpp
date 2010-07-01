// CommStatusPointDlg.cpp : implementation file
//

#include "stdafx.h"
#include "kjmonitor.h"
#include "CommStatusPointDlg.h"
#include "MainFrm.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCommStatusPointDlg dialog


CCommStatusPointDlg::CCommStatusPointDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCommStatusPointDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCommStatusPointDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CCommStatusPointDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCommStatusPointDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCommStatusPointDlg, CDialog)
	//{{AFX_MSG_MAP(CCommStatusPointDlg)
	ON_BN_CLICKED(IIDC_BUTTON1, OnButton1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCommStatusPointDlg message handlers

BOOL CCommStatusPointDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CMainFrame* pFWnd=(CMainFrame*)AfxGetMainWnd();
	m_pCommStatusFM=pFWnd->m_pCommStatusFM;
	//pFWnd->m_pGLDoc=GetDocument();
	//pFWnd->>m_pGLView=this;
	//CWnd* pWnd;   //another way to define m_pCommStatusFM, also, m_pCommStatusFM should be define and redirect in appfile and CCommStatusFM first
	//pWnd=((CFrameWnd*)(AfxGetApp()->m_pMainWnd))->GetActiveWindow();//GetActiveView();
	//m_pCommStatusFM=pWnd->m_pCommStatusFM


	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CCommStatusPointDlg::OnButton1() 
{

	
}
