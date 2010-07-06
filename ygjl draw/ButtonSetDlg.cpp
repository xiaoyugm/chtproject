// ButtonSetDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Draw.h"
#include "ButtonSetDlg.h"
#include "MainFrm.h"
#include "DrawView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CButtonSetDlg property page

IMPLEMENT_DYNCREATE(CButtonSetDlg, CPropertyPage)

CButtonSetDlg::CButtonSetDlg() : CPropertyPage(CButtonSetDlg::IDD)
{
	//{{AFX_DATA_INIT(CButtonSetDlg)
	m_strButton = _T("");
	m_fontSize = 0;
	m_strLinkViewName = _T("");
	//}}AFX_DATA_INIT
}

CButtonSetDlg::~CButtonSetDlg()
{
}

void CButtonSetDlg::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CButtonSetDlg)
	DDX_Control(pDX, IDC_COMBO_VIEW, m_ctlLinkView);
	DDX_Control(pDX, IDC_COMBO_STYLE, m_ctlStyleCombo);
	DDX_Control(pDX, IDC_COMBO_POSITION, m_ctlPostionCombo);
	DDX_Control(pDX, IDC_SPIN_SIZE, m_ctlFontSize);
	DDX_Control(pDX, IDC_COMBO_FONT, m_ctlFontCombo);
	DDX_Control(pDX, IDC_TEXTCOLOR, m_ctlTextColor);
	DDX_Text(pDX, IDC_EDIT_TEXT, m_strButton);
	DDV_MaxChars(pDX, m_strButton, 100);
	DDX_Text(pDX, IDC_EDIT_FONTSIZE, m_fontSize);
	DDV_MinMaxByte(pDX, m_fontSize, 1, 72);
	DDX_Text(pDX, IDC_EDIT_LINK_VIEW, m_strLinkViewName);
	//}}AFX_DATA_MAP
	DDX_XTColorPicker(pDX, IDC_TEXTCOLOR, m_color);
}


BEGIN_MESSAGE_MAP(CButtonSetDlg, CPropertyPage)
	//{{AFX_MSG_MAP(CButtonSetDlg)
	ON_CBN_SELENDOK(IDC_COMBO_STYLE, OnSelendokComboStyle)
	ON_CBN_SELENDOK(IDC_COMBO_BORDER, OnSelendokComboBorder)
	ON_CBN_SELENDOK(IDC_COMBO_FONT, OnSelendokComboFont)
	ON_CBN_SELENDOK(IDC_COMBO_POSITION, OnSelendokComboPosition)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON_PATH, OnButtonPath)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CButtonSetDlg message handlers

BOOL CButtonSetDlg::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();

	//进行初始化
	InitSelectViewCombo();

	m_ctlFontCombo.DisableFlatLook(TRUE);
	m_ctlFontCombo.InitControl( m_fontName, 120 );


	m_ctlFontSize.SetRange(1,72);
	m_ctlFontSize.SetPos(m_fontSize);

	switch(m_fontStyle)
	{
	case FontStyleRegular:
		m_ctlStyleCombo.SetCurSel(0);
		break;
	case FontStyleBold:
		m_ctlStyleCombo.SetCurSel(1);
		break;
	case FontStyleItalic:
		m_ctlStyleCombo.SetCurSel(2);
		break;
	case FontStyleBoldItalic:
		m_ctlStyleCombo.SetCurSel(3);
		break;
	case FontStyleUnderline:
		m_ctlStyleCombo.SetCurSel(4);
		break;
	default:
		m_ctlStyleCombo.SetCurSel(0);
		break;
	}

	switch(m_fontAlignment)
	{
	case StringAlignmentNear:
		m_ctlPostionCombo.SetCurSel(1);
		break;
	case StringAlignmentCenter:
		m_ctlPostionCombo.SetCurSel(0);
		break;
	case StringAlignmentFar:
		m_ctlPostionCombo.SetCurSel(2);
		break;
	default:
		m_ctlPostionCombo.SetCurSel(0);
		break;
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE

}

void CButtonSetDlg::OnSelEndOkClr()
{
	UpdateData();	
}

void CButtonSetDlg::OnSelendokComboStyle() 
{
	switch(m_ctlStyleCombo.GetCurSel())
	{
	case 0:
		m_fontStyle = FontStyleRegular;
		break;
	case 1:
		m_fontStyle = FontStyleBold;
		break;
	case 2:
		m_fontStyle = FontStyleItalic;
		break;
	case 3:
		m_fontStyle = FontStyleBoldItalic;
		break;
	case 4:
		m_fontStyle = FontStyleUnderline;
		break;
	}
}

void CButtonSetDlg::OnSelendokComboBorder() 
{


}

void CButtonSetDlg::OnSelendokComboFont() 
{
	 m_ctlFontCombo.GetSelFont(m_fontName);
}

void CButtonSetDlg::OnSelendokComboPosition() 
{
	switch(	m_ctlPostionCombo.GetCurSel())
	{
	case 0:
		m_fontAlignment = StringAlignmentCenter;
		break;
	case 1:
		m_fontAlignment = StringAlignmentNear;
		break;
	case 2:
		m_fontAlignment = StringAlignmentFar;
		break;
	}	
}

void CButtonSetDlg::OnDestroy() 
{
	UpdateData();
	CPropertyPage::OnDestroy();	
}

void CButtonSetDlg::InitSelectViewCombo()
{
	CMainFrame *pMainFrame = (CMainFrame *)AfxGetApp()->m_pMainWnd;
	POSITION pos = pMainFrame->m_wndTabDockBar.m_wndTreeCtrl.m_map.GetStartPosition();
	while (pos != NULL)
	{	
		CDrawView *pView;
		CString strTemp;
		pMainFrame->m_wndTabDockBar.m_wndTreeCtrl.m_map.GetNextAssoc(pos,strTemp,pView);
		m_ctlLinkView.AddString(strTemp);
	}
}

void CButtonSetDlg::OnButtonPath() 
{
	char filter[] = "文件(*.rsy)|*.rsy||";
	CFileDialog filedlg(TRUE,NULL,NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,filter,NULL);
	if(filedlg.DoModal() == IDOK)
	{
		m_strLinkViewName = filedlg.GetPathName();
		UpdateData(FALSE);
	}
}
