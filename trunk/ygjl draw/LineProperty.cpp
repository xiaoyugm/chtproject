// LineProperty.cpp : implementation file
//

#include "stdafx.h"
#include "Draw.h"
#include "LineProperty.h"
#include "EffectDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLineProperty property page

IMPLEMENT_DYNCREATE(CLineProperty, CPropertyPage)

CLineProperty::CLineProperty() : CPropertyPage(CLineProperty::IDD)
{
	//{{AFX_DATA_INIT(CLineProperty)

	//}}AFX_DATA_INIT

	m_bUpdata = FALSE;
}

CLineProperty::~CLineProperty()
{
}

void CLineProperty::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLineProperty)
	DDX_Control(pDX, IDC_COMBO_LINESTYLE, m_ctlLineStyle);
	DDX_Control(pDX, IDC_SPIN_LINESIZE, m_cltLineSize);
	DDX_Control(pDX, IDC_FILL_COLOR, m_ctlFillColor);
	DDX_Control(pDX, IDC_LINE_COLOR, m_ctlLineColor);
	DDX_Check(pDX, IDC_NoFill, m_bNoFill);
	DDX_Text(pDX, IDC_LINE_SIZE, m_nLineSize);
	DDV_MinMaxUInt(pDX, m_nLineSize, 1, 100);
	//}}AFX_DATA_MAP
	DDX_XTColorPicker(pDX, IDC_FILL_COLOR, m_clrFillColor);
	DDX_XTColorPicker(pDX, IDC_LINE_COLOR, m_clrLineColor);
}


BEGIN_MESSAGE_MAP(CLineProperty, CPropertyPage)
	//{{AFX_MSG_MAP(CLineProperty)
	ON_CBN_SELENDOK(IDC_COMBO_LINESTYLE, OnSelendokComboLinestyle)
	ON_EN_CHANGE(IDC_LINE_SIZE, OnChange)
	ON_BN_CLICKED(IDC_NoFill, OnNoFill)
	//}}AFX_MSG_MAP
	ON_CPN_XT_SELENDOK(IDC_FILL_COLOR, OnSelEndOkFillClr)
	ON_CPN_XT_SELENDOK(IDC_LINE_COLOR, OnSelEndOkLineClr)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLineProperty message handlers

BOOL CLineProperty::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();

	m_cltLineSize.SetRange(1,100);
	m_cltLineSize.SetPos(m_nLineSize);

	m_bUpdata = TRUE;

	switch(m_LineStyle)
	{
	case DashStyleSolid:
		m_ctlLineStyle.SetCurSel(0);
		break;
	case DashStyleDash:
		m_ctlLineStyle.SetCurSel(1);
		break;
	case DashStyleDot:
		m_ctlLineStyle.SetCurSel(2);
		break;
	case DashStyleDashDot :
		m_ctlLineStyle.SetCurSel(3);
		break;
	case DashStyleDashDotDot :
		m_ctlLineStyle.SetCurSel(4);
		break;
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CLineProperty::OnSelendokComboLinestyle() 
{
	
	int i = m_ctlLineStyle.GetCurSel();
	switch(i)
	{
	case 0:
		m_LineStyle = DashStyleSolid;
		break;
	case 1:
		m_LineStyle = DashStyleDash;
		break;
	case 2:
		m_LineStyle = DashStyleDot;
		break;
	case 3:
		m_LineStyle = DashStyleDashDot;
		break;
	case 4:
		m_LineStyle = DashStyleDashDotDot;
		break;
	}
}

void CLineProperty::OnSelEndOkFillClr()
{
	UpdateData();
	CEffectDlg *pDlg = (CEffectDlg *)(GetParent()->GetParent());
}

void CLineProperty::OnSelEndOkLineClr()
{
	UpdateData();
}

void CLineProperty::OnChange() 
{
	if(m_bUpdata)
		UpdateData();	
}

void CLineProperty::OnNoFill() 
{
	UpdateData();	
}
