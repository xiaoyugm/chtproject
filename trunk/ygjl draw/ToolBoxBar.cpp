// ToolBoxBar.cpp: implementation of the CToolBoxBar class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Draw.h"
#include "ToolBoxBar.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CToolBoxBar::CToolBoxBar()
{
	m_nColumns		 = 2;
	m_cxLeftBorder	 = 5;
	m_cxRightBorder  = 5;
	m_cyTopBorder	 = 5;
	m_cyBottomBorder = 5;
}

CToolBoxBar::~CToolBoxBar()
{
	// TODO: add destruction code here.

}

IMPLEMENT_DYNAMIC(CToolBoxBar, CXTToolBar)

BEGIN_MESSAGE_MAP(CToolBoxBar, CXTToolBar)
	//{{AFX_MSG_MAP(CToolBoxBar)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CToolBoxBar message handlers

void CToolBoxBar::SetColumns(UINT nColumns)
{
	m_nColumns = nColumns;
	int nCount = GetToolBarCtrl().GetButtonCount();
	
	for(int i = 0; i < nCount; i++)
	{
		UINT nStyle = GetButtonStyle(i);
		BOOL bWrap = (((i + 1) % nColumns) == 0);
		
		if (bWrap) {
			nStyle |= TBBS_WRAPPED;
		}
		else {
			nStyle &= ~TBBS_WRAPPED;
		}
		
		SetButtonStyle(i, nStyle);
	}
}

UINT CToolBoxBar::GetColumns() const
{
	return m_nColumns;
}