// NewDocument.cpp : implementation file
//

#include "stdafx.h"
#include "Draw.h"
#include "NewDocument.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNewDocument dialog


CNewDocument::CNewDocument(CWnd* pParent /*=NULL*/)
	: CDialog(CNewDocument::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNewDocument)
	m_strDocName = _T("");
	m_lHeight = 941;
	m_bIsAutoSize = TRUE;
	m_clrColor = RGB(255,255,255);
	m_lWidth = 593;
	//}}AFX_DATA_INIT
	m_bInitIsOk = FALSE;
}


void CNewDocument::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNewDocument)
	DDX_Control(pDX, IDC_BACK_COLOR, m_color);
	DDX_Control(pDX, IDC_SPIN_WIDTH, m_ctlWidth);
	DDX_Control(pDX, IDC_SPIN_HEIGHT, m_ctlHeight);
	DDX_Text(pDX, IDC_EDIT_NAME, m_strDocName);
	DDV_MaxChars(pDX, m_strDocName, 32);
	DDX_Text(pDX, IDC_EDIT_HEIGHT, m_lHeight);
	DDV_MinMaxLong(pDX, m_lHeight, 0, 3200);
	DDX_Check(pDX, IDC_CHECK_AUTOSIZE, m_bIsAutoSize);
	DDX_Text(pDX, IDC_EDIT_WIDTH, m_lWidth);
	DDV_MinMaxLong(pDX, m_lWidth, 0, 3200);
	//}}AFX_DATA_MAP
	DDX_XTColorPicker(pDX, IDC_BACK_COLOR, m_clrColor);
}


BEGIN_MESSAGE_MAP(CNewDocument, CDialog)
	//{{AFX_MSG_MAP(CNewDocument)
	ON_WM_DESTROY()
	ON_EN_CHANGE(IDC_EDIT_HEIGHT, OnChangeEditHeight)
	ON_EN_CHANGE(IDC_EDIT_WIDTH, OnChangeEditWidth)
	ON_BN_CLICKED(IDC_CHECK_AUTOSIZE, OnCheckAutosize)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNewDocument message handlers

BOOL CNewDocument::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_ctlWidth.SetRange(1,3200);
	m_ctlWidth.SetPos(m_lWidth);

	m_ctlHeight.SetRange(1,3200);
	m_ctlHeight.SetPos(m_lHeight);

	m_bInitIsOk = TRUE;

	UpdateData();
	m_width = m_lWidth;
	m_height = m_lHeight;

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CNewDocument::OnDestroy() 
{
	UpdateData();
	CDialog::OnDestroy();	
}

void CNewDocument::OnChangeEditHeight() 
{
	if(!m_bInitIsOk)
		return;
	if(m_bIsAutoSize)
	{
		UpdateData();
		float i = m_lHeight/m_height;
		m_lWidth = m_width*i;
		UpdateData(FALSE);
	}

}

void CNewDocument::OnChangeEditWidth() 
{
	if(!m_bInitIsOk)
		return;
	if(m_bIsAutoSize)
	{
		UpdateData();
		float i = m_lWidth/m_width;
		m_lHeight = m_height*i;
		UpdateData(FALSE);
	}

	
}

void CNewDocument::OnCheckAutosize() 
{
	m_bIsAutoSize = !m_bIsAutoSize;
	UpdateData(FALSE);
	
}

void CNewDocument::OnOK() 
{
	//检查数据是否有效
	CDialog::OnOK();
}
