// EffectDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Draw.h"
#include "EffectDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEffectDlg dialog
CEffectDlg::CEffectDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CEffectDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CEffectDlg)
	m_LineStyle = DashStyleSolid;
	m_bNoFill = FALSE;
	m_nLineSize = 1;
	m_clrFillColor = RGB(0xff,0xff,0xff);
	m_clrLineColor = RGB(0x00,0x00,0xff);

	//}}AFX_DATA_INIT
	m_pLineProperty = NULL;

}

void CEffectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEffectDlg)
	DDX_Control(pDX, IDC_TAB1, m_Tab);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CEffectDlg, CDialog)
	//{{AFX_MSG_MAP(CEffectDlg)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEffectDlg message handlers

BOOL CEffectDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

		m_pLineProperty = new CLineProperty;
		m_pLineProperty->m_LineStyle = m_LineStyle;
		m_pLineProperty->m_bNoFill = m_bNoFill;
		m_pLineProperty->m_nLineSize = m_nLineSize;
		m_pLineProperty->m_clrFillColor = m_clrFillColor;
		m_pLineProperty->m_clrLineColor = m_clrLineColor;
		m_pLineProperty->Create(IDD_PROP_RECT, &m_Tab);
		m_Tab.AddTab(m_pLineProperty,"ÉèÖÃ",0);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CEffectDlg::OnDestroy() 
{
	if(m_pLineProperty)
		delete m_pLineProperty;
	CDialog::OnDestroy();
}

void CEffectDlg::OnOK() 
{
	m_LineStyle = m_pLineProperty->m_LineStyle;
	m_bNoFill = m_pLineProperty->m_bNoFill;
	m_nLineSize = m_pLineProperty->m_nLineSize;
	m_clrFillColor = m_pLineProperty->m_clrFillColor;
	m_clrLineColor = m_pLineProperty->m_clrLineColor;

	CDialog::OnOK();
}
