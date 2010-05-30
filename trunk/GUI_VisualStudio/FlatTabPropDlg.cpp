// FlatTabPropDlg.cpp : implementation file
//

#include "stdafx.h"
#include "GUI_VisualStudio.h"
#include "FlatTabPropDlg.h"
#include "FlatTabViewDoc.h"
#include "FlatTabViewView.h"
#include "SampleFormView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
/*
template <class T>
class CAutoDestructCtrl : public T
{
public:
    virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
    {
        LRESULT lRes = T::WindowProc(message, wParam, lParam);

        if (message == WM_DESTROY)
        {
            delete this;
        }

        return lRes;
    }
};
*/
/////////////////////////////////////////////////////////////////////////////
// CFlatTabPropDlg dialog


CFlatTabPropDlg::CFlatTabPropDlg(CXTFlatTabCtrl* pFlatTabCtrl, CFlatTabViewView* pParent /*=NULL*/)
	: CDialog(CFlatTabPropDlg::IDD, pParent),
	m_FTS_XT_BOTTOM(pParent->m_FTS_XT_BOTTOM),
	m_FTS_XT_HASARROWS(pParent->m_FTS_XT_HASARROWS),
	m_FTS_XT_HASHOMEEND(pParent->m_FTS_XT_HASHOMEEND),
	m_FTS_XT_HSCROLL(pParent->m_FTS_XT_HSCROLL),
	m_dwTabStyle(pParent->m_dwTabStyle)
{
	//{{AFX_DATA_INIT(CFlatTabPropDlg)
	m_iTabNum = 0;
	m_sText = _T("");
	//}}AFX_DATA_INIT

	m_pParentWnd = pParent;
	ASSERT_VALID(m_pParentWnd);

	m_pFlatTabCtrl = pFlatTabCtrl;
	ASSERT_VALID(m_pFlatTabCtrl);

}

CFlatTabPropDlg::~CFlatTabPropDlg()
{
}

void CFlatTabPropDlg::DoDataExchange(CDataExchange* pDX)
{
	const int nTabs = m_pFlatTabCtrl->GetItemCount() - 1;
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFlatTabPropDlg)
	DDX_Check(pDX, IDC_FTS_XT_BOTTOM, m_FTS_XT_BOTTOM);
	DDX_Check(pDX, IDC_FTS_XT_HASARROWS, m_FTS_XT_HASARROWS);
	DDX_Check(pDX, IDC_FTS_XT_HASHOMEEND, m_FTS_XT_HASHOMEEND);
	DDX_Check(pDX, IDC_FTS_XT_HSCROLL, m_FTS_XT_HSCROLL);
	DDX_Text(pDX, IDC_TAB_NUM, m_iTabNum);
	DDV_MinMaxUInt(pDX, m_iTabNum, 0, nTabs);
	DDX_Text(pDX, IDC_TEXT, m_sText);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CFlatTabPropDlg, CDialog)
	//{{AFX_MSG_MAP(CFlatTabPropDlg)
	ON_BN_CLICKED(IDC_FTS_XT_BOTTOM, UpdateTabsStyle)
	ON_BN_CLICKED(IDC_FTS_XT_HASARROWS, UpdateTabsStyle)
	ON_BN_CLICKED(IDC_FTS_XT_HASHOMEEND, UpdateTabsStyle)
	ON_BN_CLICKED(IDC_FTS_XT_HSCROLL, UpdateTabsStyle)
	ON_BN_CLICKED(IDC_MANIPULATE, OnManipulate)
	ON_BN_CLICKED(IDC_ADD_TAB, OnAddTab)
	ON_BN_CLICKED(IDC_DELETE_ALL, OnDeleteAll)
	ON_BN_CLICKED(IDC_DELETE_TAB, OnDeleteTab)
	ON_BN_CLICKED(IDC_MODIFY_TAB, OnModifyTab)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFlatTabPropDlg message handlers

BOOL CFlatTabPropDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	UpdateDlgStatus();	

	// Set control resizing.
//	SetResize(IDC_TEXT,       SZ_TOP_LEFT,     SZ_TOP_RIGHT);
//	SetResize(IDOK,           SZ_BOTTOM_RIGHT, SZ_BOTTOM_RIGHT);
//	SetResize(IDC_DELETE_TAB, SZ_TOP_LEFT,     SZ_TOP_RIGHT);
//	SetResize(IDC_MODIFY_TAB, SZ_TOP_LEFT,     SZ_TOP_RIGHT);
//	SetResize(IDC_ADD_TAB,    SZ_TOP_LEFT,     SZ_TOP_RIGHT);
//	SetResize(IDC_DELETE_ALL, SZ_TOP_LEFT,     SZ_TOP_RIGHT);
    
	// prevent vertical resizing.
//	SetFlag(SZ_NOVERTICAL);

	// Load window placement
//	LoadPlacement(_T("CTabManipulationDlg"));

	return TRUE;
}

void CFlatTabPropDlg::UpdateTabsStyle() 
{
	int dwNewStyle = 0;
	UpdateData();
	if (m_FTS_XT_HASHOMEEND) 
	{
		dwNewStyle |= FTS_XT_HASHOMEEND;
		m_FTS_XT_HASARROWS = TRUE;
		UpdateData(FALSE);
	}
	GetDlgItem(IDC_FTS_XT_HASARROWS)->EnableWindow(!m_FTS_XT_HASHOMEEND);
	if (m_FTS_XT_BOTTOM)     dwNewStyle |= FTS_XT_BOTTOM;
	if (m_FTS_XT_HASARROWS)  dwNewStyle |= FTS_XT_HASARROWS;
	if (m_FTS_XT_HSCROLL)    dwNewStyle |= FTS_XT_HSCROLL;
	dwNewStyle |= FTS_XT_TOOLTIPS;
	if (dwNewStyle != m_dwTabStyle)
	{
		m_dwTabStyle = dwNewStyle;
		m_pParentWnd->CreateTabs();
	}
}

void CFlatTabPropDlg::OnManipulate() 
{

	
/*	if (m_pManipDlg == NULL)
	{
		m_pManipDlg = new CTabManipulationDlg(m_pFlatTabCtrl);
		m_pManipDlg->Create(CTabManipulationDlg::IDD, this);
	}
	m_pManipDlg->UpdateDlgStatus();
	m_pManipDlg->ShowWindow(SW_SHOW);
	m_pManipDlg->SetFocus();*/
}

void CFlatTabPropDlg::OnDestroy() 
{
	// Save window placement
//	SavePlacement(_T("CTabManipulationDlg"));

	CDialog::OnDestroy();
}

void CFlatTabPropDlg::OnAddTab() 
{
	if (UpdateData())
	{
		CRect rectDummy(0, 0, 0, 0);
	if ( m_pSheet7 && ::IsWindow( m_pSheet7->m_hWnd ) )
	{
		m_pSheet7->DestroyWindow();
	}
	CCreateContext cc;
	ZeroMemory(&cc, sizeof(cc));
	m_pSheet7 = (CSampleFormView*)RUNTIME_CLASS(CSampleFormView)->CreateObject();
	if (!m_pSheet7  || !((CWnd *)m_pSheet7)->Create(
		NULL, NULL, WS_CHILD, rectDummy, m_pFlatTabCtrl, IDC_SHEET7, &cc))
	{
		TRACE0( "Failed to create sheet7.\n" );
		return ;
	}
	
	
	/*		CAutoDestructCtrl<CEditCtrlForFlatTab> *pSheet = new 
            CAutoDestructCtrl<CEditCtrlForFlatTab>();
		pSheet->Create(WS_CHILD | WS_TABSTOP | WS_CLIPCHILDREN |
			WS_HSCROLL | WS_VSCROLL | ES_MULTILINE, rectDummy, 
			m_pFlatTabCtrl, 1000);
		pSheet->SetWindowText(m_sText);*/
		m_pFlatTabCtrl->InsertItem(m_iTabNum, m_sText, m_pSheet7);
		m_pSheet7->OnInitialUpdate();
	}
	UpdateDlgStatus();
}

void CFlatTabPropDlg::OnDeleteAll() 
{
	m_pFlatTabCtrl->DeleteAllItems();
	UpdateDlgStatus();
}

void CFlatTabPropDlg::OnDeleteTab() 
{
	if (m_pFlatTabCtrl->GetItemCount() > 0  &&  UpdateData())
	{
		m_pFlatTabCtrl->DeleteItem(m_iTabNum);
	}
	UpdateDlgStatus();
}

void CFlatTabPropDlg::OnModifyTab() 
{
	if (m_pFlatTabCtrl->GetItemCount() > 0  &&  UpdateData())
	{
		m_pFlatTabCtrl->SetItemText(m_iTabNum, m_sText);
	}
	UpdateDlgStatus();
}

void CFlatTabPropDlg::UpdateDlgStatus()
{
	const bool bHasTabs = (m_pFlatTabCtrl->GetItemCount() > 0);
	GetDlgItem(IDC_DELETE_ALL)->EnableWindow(bHasTabs);
	GetDlgItem(IDC_DELETE_TAB)->EnableWindow(bHasTabs);
	GetDlgItem(IDC_MODIFY_TAB)->EnableWindow(bHasTabs);
}
