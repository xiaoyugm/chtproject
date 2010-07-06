// WarnSetDialog.cpp : implementation file
//

#include "stdafx.h"
#include "Draw.h"
#include "WarnSetDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWarnSetDialog dialog


CWarnSetDialog::CWarnSetDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CWarnSetDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CWarnSetDialog)
	//}}AFX_DATA_INIT
	m_bInitComplete = FALSE;
}


void CWarnSetDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWarnSetDialog)
	DDX_Control(pDX, IDC_SPIN_WARN, m_ctlWarn);
	DDX_Control(pDX, IDC_SPIN_TIME, m_ctlTime);
	DDX_Control(pDX, IDC_SPIN_TEXT, m_ctlText);
	DDX_Control(pDX, IDC_SPIN_POINT_PERCENT, m_ctlPoint);
	DDX_Control(pDX, IDC_SPIN_DATE, m_ctlDate);
	DDX_Control(pDX, IDC_SPIN_COL, m_ctlCol);
	DDX_Control(pDX, IDC_TITLECOLOR, m_titleColor);
	DDX_Control(pDX, IDC_TEXTCOLOR, m_textColor);
	DDX_Control(pDX, IDC_LINECOLOR, m_lineColor);
	DDX_Control(pDX, IDC_BACKCOLOR, m_backColor);
	DDX_Text(pDX, IDC_EDIT_COL_COUNT, m_nCol);
	DDV_MinMaxUInt(pDX, m_nCol, 1, 50);
	DDX_Check(pDX, IDC_CHECK_AUTOSIZE, m_bIsAutoSize);
	DDX_Text(pDX, IDC_EDIT_POINT, m_nPoint);
	DDV_MinMaxUInt(pDX, m_nPoint, 1, 100);
	DDX_Text(pDX, IDC_EDIT_DATE, m_nDate);
	DDV_MinMaxUInt(pDX, m_nDate, 1, 100);
	DDX_Text(pDX, IDC_EDIT_TIME, m_nTime);
	DDV_MinMaxUInt(pDX, m_nTime, 1, 100);
	DDX_Text(pDX, IDC_EDIT_TEXT, m_nText);
	DDV_MinMaxUInt(pDX, m_nText, 1, 100);
	DDX_Text(pDX, IDC_EDIT_WARN, m_nWarn);
	DDV_MinMaxUInt(pDX, m_nWarn, 1, 100);
	//}}AFX_DATA_MAP
	DDX_XTColorPicker(pDX, IDC_BACKCOLOR, m_clrBackColor);
	DDX_XTColorPicker(pDX, IDC_LINECOLOR, m_clrLineColor);
	DDX_XTColorPicker(pDX, IDC_TEXTCOLOR, m_clrTextColor);
	DDX_XTColorPicker(pDX, IDC_TITLECOLOR, m_clrTitleColor);

}


BEGIN_MESSAGE_MAP(CWarnSetDialog, CDialog)
	//{{AFX_MSG_MAP(CWarnSetDialog)
	ON_EN_CHANGE(IDC_EDIT_POINT, OnChangePercent)
	ON_EN_CHANGE(IDC_EDIT_DATE, OnChangePercent)
	ON_EN_CHANGE(IDC_EDIT_TIME, OnChangePercent)
	ON_EN_CHANGE(IDC_EDIT_TEXT, OnChangePercent)
	ON_EN_CHANGE(IDC_EDIT_WARN, OnChangePercent)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWarnSetDialog message handlers

BOOL CWarnSetDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();

	m_ctlWarn.SetRange(1,100);
	m_ctlTime.SetRange(1,100);
	m_ctlText.SetRange(1,100);
	m_ctlPoint.SetRange(1,100);
	m_ctlDate.SetRange(1,100);
	m_ctlCol.SetRange(1,50);
	

	m_bInitComplete = TRUE;
	if(m_bIsAutoSize)
	{
		m_nPoint = 5;
		m_nDate = 12;
		m_nTime = 30;
		m_nText = 40;
		m_nWarn = 13;
		UpdateData(FALSE);

	}
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CWarnSetDialog::OnChangePercent() 
{
	if(m_bInitComplete)
	{
		m_bIsAutoSize = FALSE;
	}

}

void CWarnSetDialog::OnOK() 
{
	UpdateData();
	int i = m_nPoint + m_nDate + m_nTime+ m_nText+m_nWarn;
	if(i != 100)
	{
		AfxMessageBox("所有的百分比相加必须为100%,请检查!");
		return;
	}
	UpdateData();
	CDialog::OnOK();
}
