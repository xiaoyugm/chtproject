// SetRayActionDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Draw.h"
#include "SetRayActionDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSetRayActionDlg dialog


CSetRayActionDlg::CSetRayActionDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSetRayActionDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSetRayActionDlg)
	m_strSpeed = _T("");
	m_strType = _T("");
	m_nMax = 0;
	m_nMin = 0;
	m_nPointNo = 0;
	//}}AFX_DATA_INIT
}


void CSetRayActionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSetRayActionDlg)
	DDX_Control(pDX, IDC_START_COLOR, m_StartColor);
	DDX_Control(pDX, IDC_END_COLOR, m_EndColor);
	DDX_CBString(pDX, IDC_COMBO_RAY_SPEED, m_strSpeed);
	DDX_CBString(pDX, IDC_COMBO_RAY_TYPE, m_strType);
	DDX_Text(pDX, IDC_EDIT_MAX, m_nMax);
	DDX_Text(pDX, IDC_EDIT_MIN, m_nMin);
	DDX_Text(pDX, IDC_EDIT_POINT_NO, m_nPointNo);
	//}}AFX_DATA_MAP
	DDX_XTColorPicker(pDX, IDC_START_COLOR, m_clrStartColor);
	DDX_XTColorPicker(pDX, IDC_END_COLOR, m_clrEndColor);

}


BEGIN_MESSAGE_MAP(CSetRayActionDlg, CDialog)
	//{{AFX_MSG_MAP(CSetRayActionDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSetRayActionDlg message handlers

BOOL CSetRayActionDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	m_StartColor.ShowText(TRUE);
	m_EndColor.ShowText(TRUE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSetRayActionDlg::OnOK() 
{
	UpdateData();
	CDialog::OnOK();
}
