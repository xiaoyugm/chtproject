// SetPercentFillDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Draw.h"
#include "SetPercentFillDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSetPercentFillDlg dialog


CSetPercentFillDlg::CSetPercentFillDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSetPercentFillDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSetPercentFillDlg)
	//}}AFX_DATA_INIT
}


void CSetPercentFillDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSetPercentFillDlg)
	DDX_Control(pDX, IDC_COMBO_REFERENCEPOINT, m_ctlReferencePoint);
	DDX_Control(pDX, IDC_FILL_COLOR, m_FillColor);
	DDX_Text(pDX, IDC_EDIT_POINT_NO, m_nPointNo);
	DDV_MinMaxUInt(pDX, m_nPointNo, 0, 15000);
	DDX_CBString(pDX, IDC_COMBO_REFERENCEPOINT, m_strReferencePoint);
	//}}AFX_DATA_MAP
	DDX_XTColorPicker(pDX, IDC_FILL_COLOR, m_clrFillColor);
}


BEGIN_MESSAGE_MAP(CSetPercentFillDlg, CDialog)
	//{{AFX_MSG_MAP(CSetPercentFillDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSetPercentFillDlg message handlers

BOOL CSetPercentFillDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
		
	if(m_bIsH)
	{
		m_ctlReferencePoint.AddString("左边");
		m_ctlReferencePoint.AddString("右边");
	}
	else
	{
		m_ctlReferencePoint.AddString("上面");
		m_ctlReferencePoint.AddString("下面");
	}
	UpdateData();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
