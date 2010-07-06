// FontPropertiesDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Draw.h"
#include "FontPropertiesDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFontPropertiesDlg property page

IMPLEMENT_DYNCREATE(CFontPropertiesDlg, CPropertyPage)

CFontPropertiesDlg::CFontPropertiesDlg() : CPropertyPage(CFontPropertiesDlg::IDD)
{
	//{{AFX_DATA_INIT(CFontPropertiesDlg)
	m_strButton = _T("");
	m_fontSize = 0;
///	m_ntrans = 0;
	m_nPointNo = 0;
	m_bIsRunShowValue = FALSE;
	m_blsDispTrue = FALSE;
	//}}AFX_DATA_INIT
	m_bIsButton = FALSE;
}

CFontPropertiesDlg::~CFontPropertiesDlg()
{
}

void CFontPropertiesDlg::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFontPropertiesDlg)
	DDX_Control(pDX, IDC_CHECK_POINT_VALUE2, m_bDispTrue);
	DDX_Control(pDX, IDC_EDIT_POINTNO, m_ctlPointNo);
	DDX_Control(pDX, IDC_CHECK_POINT_VALUE, m_bCheck);
	DDX_Control(pDX, IDC_BUTTON_FALSE_COLOR, m_ctlFalseColor);
	DDX_Control(pDX, IDC_BUTTON_TRUE_COLOR, m_ctlTrueColor);
	DDX_Control(pDX, IDC_BUTTON_ERROR_COLOR, m_ctlErrorColor);
	DDX_Control(pDX, IDC_COMBO_STYLE, m_ctlStyleCombo);
	DDX_Control(pDX, IDC_COMBO_POSITION, m_ctlPostionCombo);
	DDX_Control(pDX, IDC_SPIN_SIZE, m_ctlFontSize);
	DDX_Control(pDX, IDC_COMBO_FONT, m_ctlFontCombo);
	DDX_Control(pDX, IDC_TEXTCOLOR, m_ctlTextColor);
	DDX_Text(pDX, IDC_EDIT_TEXT, m_strButton);
	DDV_MaxChars(pDX, m_strButton, 300);
	DDX_Text(pDX, IDC_EDIT_FONTSIZE, m_fontSize);
	DDV_MinMaxByte(pDX, m_fontSize, 1, 72);
	DDX_Text(pDX, IDC_EDIT_POINTNO, m_nPointNo);
	DDV_MinMaxUInt(pDX, m_nPointNo, 0, 15000);
	DDX_Check(pDX, IDC_CHECK_POINT_VALUE, m_bIsRunShowValue);
	DDX_Check(pDX, IDC_CHECK_POINT_VALUE2, m_blsDispTrue);
	//}}AFX_DATA_MAP
	DDX_XTColorPicker(pDX, IDC_TEXTCOLOR, m_color);
	DDX_XTColorPicker(pDX, IDC_BUTTON_TRUE_COLOR, m_TrueColor);
	DDX_XTColorPicker(pDX, IDC_BUTTON_ERROR_COLOR, m_ErrorColor);
	DDX_XTColorPicker(pDX, IDC_BUTTON_FALSE_COLOR, m_FalseColor);

}


BEGIN_MESSAGE_MAP(CFontPropertiesDlg, CPropertyPage)
	//{{AFX_MSG_MAP(CFontPropertiesDlg)
	ON_CBN_SELENDOK(IDC_COMBO_STYLE, OnSelendokComboStyle)
	ON_CBN_SELENDOK(IDC_COMBO_BORDER, OnSelendokComboBorder)
	ON_CBN_SELENDOK(IDC_COMBO_FONT, OnSelendokComboFont)
	ON_CBN_SELENDOK(IDC_COMBO_POSITION, OnSelendokComboPosition)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
	ON_CPN_XT_SELENDOK(IDC_TEXTCOLOR, OnSelEndOkClr)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFontPropertiesDlg message handlers

BOOL CFontPropertiesDlg::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();

	if(m_bIsButton)
	{
		m_bCheck.EnableWindow(FALSE);
		m_bDispTrue.EnableWindow(FALSE);
		m_ctlStart.EnableWindow(FALSE);
		m_ctlEnd.EnableWindow(FALSE);
		m_ctlPointNo.EnableWindow(FALSE);
		m_ctlFalseColor.EnableWindow(FALSE);
		m_ctlTrueColor.EnableWindow(FALSE);
		m_ctlErrorColor.EnableWindow(FALSE);

	}
	
	//进行初始化
	m_ctlFontCombo.DisableFlatLook(TRUE);
	m_ctlFontCombo.InitControl( m_fontName, 120 );

///	m_ctlTrans.SetRange(0,255);
///	m_ctlTrans.SetPos(m_ntrans);

	m_ctlFontSize.SetRange(1,72);
	m_ctlFontSize.SetPos(m_fontSize);

//	FontStyle           m_fontStyle;
//	StringTrimming		m_trimmingSyle;
//	StringFormatFlags   m_format;
//	StringAlignment     m_fontAlignment;
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

void CFontPropertiesDlg::OnSelEndOkClr()
{
	UpdateData();	
}

void CFontPropertiesDlg::OnSelendokComboStyle() 
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

void CFontPropertiesDlg::OnSelendokComboBorder() 
{


}

void CFontPropertiesDlg::OnSelendokComboFont() 
{
	 m_ctlFontCombo.GetSelFont(m_fontName);
}

void CFontPropertiesDlg::OnSelendokComboPosition() 
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

void CFontPropertiesDlg::OnDestroy() 
{
	UpdateData();
	CPropertyPage::OnDestroy();	
}
