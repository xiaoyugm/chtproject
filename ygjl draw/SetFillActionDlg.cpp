// SetFillActionDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Draw.h"
#include "SetFillActionDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSetFillActionDlg dialog


CSetFillActionDlg::CSetFillActionDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSetFillActionDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSetFillActionDlg)
	//}}AFX_DATA_INIT
}


void CSetFillActionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSetFillActionDlg)
	DDX_Control(pDX, IDC_OUT_COLOR, m_outColor);
	DDX_Control(pDX, IDC_IN_START_COLOR, m_inStartColor);
	DDX_Control(pDX, IDC_IN_COLOR, m_inColor);
	DDX_Text(pDX, IDC_EDIT_POINT_NO, m_nPointNo);
	//}}AFX_DATA_MAP
	DDX_XTColorPicker(pDX, IDC_IN_COLOR, m_clrInFillColor);
	DDX_XTColorPicker(pDX, IDC_OUT_COLOR, m_clrOutFillColor);
	DDX_XTColorPicker(pDX, IDC_IN_START_COLOR, m_clrCommErrorFillColor);
}


BEGIN_MESSAGE_MAP(CSetFillActionDlg, CDialog)
	//{{AFX_MSG_MAP(CSetFillActionDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSetFillActionDlg message handlers

BOOL CSetFillActionDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	m_outColor.ShowText(TRUE);
	m_inStartColor.ShowText(TRUE);
	m_inColor.ShowText(TRUE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
