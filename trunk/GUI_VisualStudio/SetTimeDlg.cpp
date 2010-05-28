// SetTimeDlg.cpp : implementation file
//

#include "stdafx.h"
#include "GUI_VisualStudio.h"
#include "SetTimeDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSetTimeDlg dialog


CSetTimeDlg::CSetTimeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSetTimeDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSetTimeDlg)
	m_nSecond = 0;
	//}}AFX_DATA_INIT
}


void CSetTimeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSetTimeDlg)
	DDX_Text(pDX, IDC_EDIT_SECOND, m_nSecond);
	DDV_MinMaxUInt(pDX, m_nSecond, 0, 255);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSetTimeDlg, CDialog)
	//{{AFX_MSG_MAP(CSetTimeDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSetTimeDlg message handlers

