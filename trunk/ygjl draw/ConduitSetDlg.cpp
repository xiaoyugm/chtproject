// ConduitSetDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Draw.h"
#include "ConduitSetDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CConduitSetDlg dialog


CConduitSetDlg::CConduitSetDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CConduitSetDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CConduitSetDlg)
	m_nWidth = 0;
///	m_nConduitTrans = 0;
///	m_nDotTrans = 0;
	m_bIsAction = FALSE;
///	m_bIsShowMove = FALSE;
///	m_nMax = 0;
///	m_nMin = 0;
	m_nPointNo = 0;
	//}}AFX_DATA_INIT
}


void CConduitSetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CConduitSetDlg)
	DDX_Control(pDX, IDC_BUTTON_DOT_COLOR, m_Dot);
	DDX_Control(pDX, IDC_BUTTON_CONDUIT_COLOR, m_Conduit);
	DDX_Text(pDX, IDC_EDIT_WIDTH, m_nWidth);
	DDV_MinMaxUInt(pDX, m_nWidth, 10, 50);
///	DDX_Text(pDX, IDC_EDIT_CONDUIT_TRANS, m_nConduitTrans);
///	DDV_MinMaxUInt(pDX, m_nConduitTrans, 0, 255);
///	DDX_Text(pDX, IDC_EDIT_DOT_TRANS, m_nDotTrans);
///	DDV_MinMaxUInt(pDX, m_nDotTrans, 0, 255);
///	DDX_Check(pDX, IDC_CHECK_SHOW_MOVE, m_bIsShowMove);
///	DDX_Text(pDX, IDC_EDIT_MAX_VALUE, m_nMax);
///	DDX_Text(pDX, IDC_EDIT_MIN_VALUE, m_nMin);
	DDX_Text(pDX, IDC_EDIT_POINT_NO, m_nPointNo);
	//}}AFX_DATA_MAP
	DDX_XTColorPicker(pDX, IDC_BUTTON_DOT_COLOR, m_clrDotColor);
	DDX_XTColorPicker(pDX, IDC_BUTTON_CONDUIT_COLOR, m_clrConduitColor);
}


BEGIN_MESSAGE_MAP(CConduitSetDlg, CDialog)
	//{{AFX_MSG_MAP(CConduitSetDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConduitSetDlg message handlers
