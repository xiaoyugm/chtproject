// AnologInput.cpp : implementation file
//

#include "stdafx.h"
#include "kjmonitor.h"
#include "AnologInput.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAnologInput dialog


CAnologInput::CAnologInput(CWnd* pParent /*=NULL*/)
	: CDialog(CAnologInput::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAnologInput)
	m_unInput = 0;
	//}}AFX_DATA_INIT
}


void CAnologInput::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAnologInput)
	DDX_Text(pDX, IDC_EDIT_INPUT, m_unInput);
	DDV_MinMaxUInt(pDX, m_unInput, 0, 63);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAnologInput, CDialog)
	//{{AFX_MSG_MAP(CAnologInput)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAnologInput message handlers
