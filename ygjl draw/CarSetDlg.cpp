// CarSetDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Draw.h"
#include "CarSetDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCarSetDlg dialog


CCarSetDlg::CCarSetDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCarSetDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCarSetDlg)
	m_nPointNo = 0;
	m_nSpeed = 0;
	m_strPath = _T("");
	//}}AFX_DATA_INIT
}


void CCarSetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCarSetDlg)
	DDX_Control(pDX, IDC_FILL_COLOR, m_ctlFillColor);
	DDX_Control(pDX, IDC_LINE_COLOR, m_ctlLineColor);
	DDX_Control(pDX, IDC_PIC_PATH, m_ctlPath);
	DDX_Text(pDX, IDC_EDIT_POINT_NO, m_nPointNo);
	DDX_Text(pDX, IDC_EDIT_SPEED, m_nSpeed);
	DDV_MinMaxUInt(pDX, m_nSpeed, 0, 1000);
	DDX_Text(pDX, IDC_EDIT_PIC_PATH, m_strPath);
	//}}AFX_DATA_MAP
	DDX_XTColorPicker(pDX, IDC_FILL_COLOR, m_clrFillColor);
	DDX_XTColorPicker(pDX, IDC_LINE_COLOR, m_clrLineColor);
}


BEGIN_MESSAGE_MAP(CCarSetDlg, CDialog)
	//{{AFX_MSG_MAP(CCarSetDlg)
	ON_BN_CLICKED(IDC_PIC_PATH, OnPicPath)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCarSetDlg message handlers

void CCarSetDlg::OnPicPath() 
{
	char filter[] = "图象文件(*.jpg,*.jpeg,*.gif,*.bmp,*.ico)|*.jpg;*.jpeg;*.gif;*.bmp;*.ico|JPEG文件(*.jpg,*.jpeg)|*.jpg;*.jpeg|GIF文件(*.gif)|*.gif|位图文件(*.bmp)|*.bmp|PNG文件(*.png)|*.png|图标文件(*.ico)|*.ico|所有文件(*.*)|*.*||";
	CFileDialog filedlg(TRUE,NULL,NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,filter,NULL);
	if(filedlg.DoModal() == IDOK)
	{
		m_strPath = filedlg.GetPathName();
		UpdateData(FALSE);
	}
}
