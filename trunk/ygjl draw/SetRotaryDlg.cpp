// SetRotaryDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Draw.h"
#include "SetRotaryDlg.h"
#include "ColourPicker.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSetRotaryDlg dialog


CSetRotaryDlg::CSetRotaryDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSetRotaryDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSetRotaryDlg)
	m_bIsContrarotate = FALSE;
	m_nMax = 0;
	m_nMin = 0;
	m_nPointNo = 0;
	m_nAngle = 0;
	//}}AFX_DATA_INIT
}


void CSetRotaryDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSetRotaryDlg)
	DDX_Control(pDX, IDC_LINE_COLOR, m_LineColor);
	DDX_Control(pDX, IDC_FORWARD_COLOR, m_ForWordColor);
	DDX_Control(pDX, IDC_BACK_COLOR, m_BackColor);
	DDX_Check(pDX, IDC_CHECK_CONTRAROTATE, m_bIsContrarotate);
///	DDX_Text(pDX, IDC_EDIT_MAX, m_nMax);
///	DDX_Text(pDX, IDC_EDIT_MIN, m_nMin);
	DDX_Text(pDX, IDC_EDIT_POINT_NO, m_nPointNo);
	DDX_Text(pDX, IDC_EDIT_SPEED, m_nAngle);
	//}}AFX_DATA_MAP
	DDX_XTColorPicker(pDX, IDC_LINE_COLOR, m_clrLineColor);
	DDX_XTColorPicker(pDX, IDC_FORWARD_COLOR, m_clrBackColor);
	DDX_XTColorPicker(pDX, IDC_BACK_COLOR, m_clrForwordColor);
//	DDX_ColourPicker(pDX, IDC_LINE_COLOR, m_clrLineColor);
//	DDX_ColourPicker(pDX, IDC_FORWARD_COLOR, m_clrBackColor);
//	DDX_ColourPicker(pDX, IDC_BACK_COLOR, m_clrForwordColor);
}


BEGIN_MESSAGE_MAP(CSetRotaryDlg, CDialog)
	//{{AFX_MSG_MAP(CSetRotaryDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSetRotaryDlg message handlers
