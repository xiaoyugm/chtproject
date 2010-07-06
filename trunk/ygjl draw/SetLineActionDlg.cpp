// SetLineActionDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Draw.h"
#include "SetLineActionDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSetLineActionDlg dialog


CSetLineActionDlg::CSetLineActionDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSetLineActionDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSetLineActionDlg)
	//}}AFX_DATA_INIT
}


void CSetLineActionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSetLineActionDlg)
	DDX_Control(pDX, IDC_BUTTON_CommError_COLOR, m_CommErrorColor);
	DDX_Control(pDX, IDC_BUTTON_IN_COLOR, m_OutColor);
	DDX_Control(pDX, IDC_BUTTON_OUT_COLOR, m_InColor);
	DDX_Text(pDX, IDC_EDIT_POINT_NO, m_nPointNo);
	DDV_MinMaxUInt(pDX, m_nPointNo, 0, 15000);
	//}}AFX_DATA_MAP
	DDX_XTColorPicker(pDX, IDC_BUTTON_CommError_COLOR, m_clrCommErrorLineColor);
	DDX_XTColorPicker(pDX, IDC_BUTTON_IN_COLOR, m_clrInLineColor);
	DDX_XTColorPicker(pDX, IDC_BUTTON_OUT_COLOR, m_clrOutLineColor);
}


BEGIN_MESSAGE_MAP(CSetLineActionDlg, CDialog)
	//{{AFX_MSG_MAP(CSetLineActionDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSetLineActionDlg message handlers

