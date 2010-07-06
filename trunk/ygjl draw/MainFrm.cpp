// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "Draw.h"

#include "MainFrm.h"
#include "NotifyCombo.h"

#include "DrawView.h"
#include "DrawDoc.h"
#include "DrawObj.h"
#include "DrawButton.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CXTMDIFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CXTMDIFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_COMMAND(ID_VIEW_FORMAT, OnViewFormat)
	ON_UPDATE_COMMAND_UI(ID_VIEW_FORMAT, OnUpdateViewFormat)
	ON_COMMAND(ID_VIEW_WORKSPACE, OnViewWorkspace)
	ON_UPDATE_COMMAND_UI(ID_VIEW_WORKSPACE, OnUpdateViewWorkspace)
	ON_COMMAND(ID_VIEW_TOOLBOX, OnViewToolbox)
	ON_UPDATE_COMMAND_UI(ID_VIEW_TOOLBOX, OnUpdateViewToolbox)
	ON_COMMAND(ID_FORMATTING_COLOR, OnFormattingColor)
	ON_COMMAND(ID_FORMATTING_BACK_COLOR, OnFormattingBackColor)
///	ON_COMMAND(ID_PUPOP_ACTIVE, OnPupopActive)
	ON_COMMAND(ID_POPUP_CLOSE, OnPopupClose)
	ON_COMMAND(ID_POPUP_MIN, OnPopupMin)
	ON_COMMAND(ID_POPUP_PROPERTY, OnPopupProperty)
	//}}AFX_MSG_MAP
	// Global help commands
///	ON_COMMAND(ID_HELP_FINDER, CXTMDIFrameWnd::OnHelpFinder)
///	ON_COMMAND(ID_HELP, CXTMDIFrameWnd::OnHelp)
///	ON_COMMAND(ID_CONTEXT_HELP, CXTMDIFrameWnd::OnContextHelp)
///	ON_COMMAND(ID_DEFAULT_HELP, CXTMDIFrameWnd::OnHelpFinder)

	ON_CBN_SELENDOK(ID_FORMATTING_FONT, OnSelEndOk)
	ON_CBN_SELENDOK(ID_FORMATTING_SIZE, OnSelEndOk)
	ON_NOTIFY(NM_RETURN, ID_FORMATTING_FONT, OnReturn)
	ON_NOTIFY(NM_RETURN, ID_FORMATTING_SIZE, OnReturn)
	ON_MESSAGE(CPN_XT_SELENDOK, OnSelEndOKColor)

	ON_MESSAGE(CBRN_XT_DROPDOWN, OnToolbarDropDown)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
    ID_MOUSCAPTION,
	ID_MOUSPOINT,
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
    // Enable/Disable XP GUI Mode
    xtAfxData.bXPMode = TRUE;

    // Enable/Disable Menu Shadows
    xtAfxData.bMenuShadows = TRUE;

	// TODO: add member initialization code here
	m_uCmdID = ID_LINE_WIDTH;	
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CXTMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndMenuBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndMenuBar.LoadMenuBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create menubar\n");
		return -1;      // fail to create
	}
	
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	//工具箱
	if (!m_wndToolboxBar.Create(this, WS_CHILD | WS_VISIBLE | CBRS_RIGHT
		| CBRS_SIZE_FIXED | CBRS_TOOLTIPS | CBRS_FLYBY, IDW_TOOLBOX_BAR) ||
		!m_wndToolboxBar.LoadToolBar(IDR_TOOLBAR_BOX))
	{
		TRACE0("Failed to create palette bar\n");
		return -1;      // fail to create
	}

	m_wndToolboxBar.ModifyStyle(0, TBSTYLE_FLAT);
	m_wndToolboxBar.SetColumns(3);
	m_wndToolboxBar.SetWindowText(_T("工具箱"));

	//格式工具栏
	// create the format toolbar.
	if (!m_wndFormatBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC, CRect(0,0,0,0), 59500) ||
		!m_wndFormatBar.LoadToolBar(IDR_FORMATTING))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	// set the title for the formatting toolbar.
    m_wndFormatBar.SetWindowText( _T( "格式工具栏" ) );
 	// initialize the color picker dropdown for the toolbar.
    m_wndFormatBar.AddDropDownButton( ID_FORMATTING_COLOR,
		m_crCurrent, CLR_DEFAULT, CPS_XT_EXTENDED | CPS_XT_MORECOLORS ); 

    m_wndFormatBar.AddDropDownButton( ID_FORMATTING_BACK_COLOR,
		m_crFillColor, CLR_DEFAULT, CPS_XT_EXTENDED | CPS_XT_MORECOLORS ); 

	m_wndFormatBar.AddDropDownButton(ID_LINE_WIDTH);
	m_wndFormatBar.AddDropDownButton(ID_LINE_STYPE);
	m_wndFormatBar.AddDropDownButton(ID_LEFTARROW_STYLE);
	m_wndFormatBar.AddDropDownButton(ID_RIGHTARROW_STYLE);

	m_wndFormatBar.AutoSizeToolbar();
	// initialize the style, font and size combo boxes.
	if ( !InitComboFont ( ) ||
         !InitComboSize ( ) )
	{
		return -1;
	}

	// Create the workspace bar.
	if( !m_wndTabDockBar.Create(this, IDW_TABDOCKBAR, _T("导航器窗口"),
		CSize(200, 150), CBRS_LEFT))
	{
		TRACE0("Failed to create workspace dock window\n");
		return -1;		// fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndMenuBar.EnableDockingEx(CBRS_ALIGN_ANY, CBRS_XT_ALL_FLAT);
	m_wndToolBar.EnableDockingEx(CBRS_ALIGN_ANY, CBRS_XT_ALL_FLAT);
	m_wndTabDockBar.EnableDockingEx(CBRS_ALIGN_ANY, CBRS_XT_ALL_FLAT|CBRS_XT_GRIPPER_GRAD);
	m_wndToolboxBar.EnableDockingEx(CBRS_ALIGN_ANY, CBRS_XT_ALL_FLAT);
	m_wndFormatBar.EnableDockingEx(CBRS_ALIGN_ANY, CBRS_XT_ALL_FLAT);
	EnableDockingEx(CBRS_ALIGN_ANY, CBRS_XT_ALL_FLAT);
	DockControlBar(&m_wndMenuBar);
	DockControlBar(&m_wndToolBar);
	DockControlBar(&m_wndTabDockBar);
	DockControlBar(&m_wndToolboxBar);
	DockControlBar(&m_wndFormatBar);
	// Set the nubmer of columns for the m_wndToolboxBar bar.
	// Insert company name into the status bar.
	AddLogo();

	// TODO: Remove this line if you don't want cool menus.
	InstallCoolMenus(IDR_MAINFRAME);

// use multiple toolbars to initialize cool menus.
///UINT arToolbars[] = { IDR_MAINFRAME, IDR_TOOLBAR1 };
///InstallCoolMenus( arToolbars, _countof( arToolbars ) );

	XT_DROPDOWNBUTTON* pDDBtn = m_wndFormatBar.FindDropDownButton( ID_FORMATTING_COLOR );
	if ( pDDBtn != NULL ) {
		m_crCurrent = pDDBtn->clrColor;
	}

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CXTMDIFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	cs.style = WS_OVERLAPPED | WS_CAPTION | FWS_ADDTOTITLE
		| WS_THICKFRAME | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_MAXIMIZE;

	// Helps to reduce screen flicker.
	cs.lpszClass = AfxRegisterWndClass(0, NULL, NULL,
		AfxGetApp()->LoadIcon(IDR_MAINFRAME));

	return TRUE;
}

BOOL CMainFrame::ShowWindowEx(int nCmdShow)
{
	ASSERT_VALID(this);

	// Restore control bar postion.
	LoadBarState(_T("Control Bar State"));

	// Restore frame window size and position.
	m_wndPosition.LoadWindowPos(this);
	nCmdShow = m_wndPosition.showCmd;

	return ShowWindow(nCmdShow);
}


/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CXTMDIFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CXTMDIFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

void CMainFrame::AddLogo()
{
	if (!m_wndLogoPane.Create(_T("Robustech"), &m_wndStatusBar))
	{
		TRACE0("Failed to create logo control.\n");
		return;
	}

	int nWidth = m_wndLogoPane.GetTextSize().cx;

	// add the indicator to the status bar.
	m_wndStatusBar.AddIndicator(ID_INDICATOR_LOGO, 0);
	
	// Initialize the pane info and add the control.
	int nIndex = m_wndStatusBar.CommandToIndex(ID_INDICATOR_LOGO);
	ASSERT (nIndex != -1);
	
	m_wndStatusBar.SetPaneWidth(nIndex, nWidth);
	m_wndStatusBar.SetPaneStyle(nIndex, m_wndStatusBar.GetPaneStyle(nIndex) | SBPS_POPOUT);
	m_wndStatusBar.AddControl(&m_wndLogoPane, ID_INDICATOR_LOGO, FALSE);
}

void CMainFrame::RemoveLogo()
{
	m_wndStatusBar.RemoveIndicator(ID_INDICATOR_LOGO);
}

bool CMainFrame::InitComboFont()
{
	// create thefont combo box.
	if (!m_wndComboFont.Create( WS_CHILD|WS_VISIBLE|WS_VSCROLL|CBS_OWNERDRAWFIXED|CBS_DROPDOWN|CBS_SORT|CBS_HASSTRINGS|WS_CLIPCHILDREN,
		CRect(0,0,150,250), &m_wndFormatBar, ID_FORMATTING_FONT ))
	{
		TRACE0("Failed to create font combo.\n");
		return false;
	}

	// insert it into the formatting toolbar.
	m_wndFormatBar.InsertControl(&m_wndComboFont);

	m_strFontName = "Arial";
	// select the font and set the drop width for the combo.
	m_wndComboFont.InitControl( m_strFontName, 285 );

	// use a different character set.
	//CXTFontEnum::Get().Init( NULL, SYMBOL_CHARSET );
	//m_wndComboFont.InitControl( _T( "Wingdings" ) );

    return true;
}

bool CMainFrame::InitComboSize()
{
	// create the size combo box.
	if (!m_wndComboSize.Create( WS_CHILD|WS_VISIBLE|WS_VSCROLL|CBS_DROPDOWN|WS_CLIPCHILDREN,
		CRect(0,0,50,150), &m_wndFormatBar, ID_FORMATTING_SIZE ))
	{
		TRACE0("Failed to create size combo.\n");
		return false;
	}

	// insert it into the formatting toolbar.
	m_wndFormatBar.InsertControl(&m_wndComboSize);

	// insert strings into the size combo box.
	m_wndComboSize.AddString( _T( "8" ) );
	m_wndComboSize.AddString( _T( "10" ) );
	m_wndComboSize.AddString( _T( "12" ) );
	m_wndComboSize.AddString( _T( "14" ) );
	m_wndComboSize.AddString( _T( "18" ) );
	m_wndComboSize.AddString( _T( "24" ) );
	m_wndComboSize.AddString( _T( "36" ) );
	m_wndComboSize.AddString( _T( "72" ) );
	// set the selection.
	if ( m_wndComboSize.SelectString( -1, m_strFontSize ) == CB_ERR )
	{
		m_strFontSize = "12";
		m_wndComboSize.SetWindowText( m_strFontSize );
	}

	return true;
}

void CMainFrame::GetSelFont( XT_LOGFONT& lf, COLORREF& cr )
{
	m_wndComboFont.GetSelFont( lf );

	int iSel = m_wndComboSize.GetCurSel( );
	if ( iSel != CB_ERR )
	{
		CString strText;
		m_wndComboSize.GetLBText( iSel, strText );
		lf.lfHeight = -( _ttoi( strText ) );
	}
	else
	{
		CString strText;
		m_wndComboSize.GetWindowText( strText );
		lf.lfHeight = -( _ttoi( strText ) );
	}

	lf.lfWeight    = m_bBold      ? FW_BOLD : FW_NORMAL;
	lf.lfItalic    = m_bItalic    ? 1 : 0;
	lf.lfUnderline = m_bUnderline ? 1 : 0;

	cr = m_crCurrent;
}

//字体或字号选择完成
void CMainFrame::OnSelEndOk()
{
	int iSel = m_wndComboSize.GetCurSel( );

	if ( iSel != CB_ERR ) {
		m_wndComboSize.GetLBText( iSel, m_strFontSize );
	}
	else {
		m_wndComboSize.GetWindowText( m_strFontSize );
	}

	//m_wndComboFont.GetWindowText(m_strFontName);
	m_wndComboFont.GetSelFont(m_strFontName);

	int nFontSize = atoi(m_strFontSize);

	CMDIFrameWnd *pFrame = (CMDIFrameWnd*)AfxGetApp()->m_pMainWnd;
	CMDIChildWnd *pChild = (CMDIChildWnd *) pFrame->GetActiveFrame();
	CDrawView *pView = (CDrawView*)pChild->GetActiveView();

	if(pView == NULL)
		return;
	
	if(pView->m_selection.GetCount() >= 1)
	{

		POSITION pos = pView->m_selection.GetHeadPosition();
		while(pos != NULL)
		{


			CDrawObj * pObj = pView->m_selection.GetNext(pos);
			if(pObj->IsKindOf(RUNTIME_CLASS(CDrawButton)))
			{
				CDrawButton *pButton = (CDrawButton *)pObj;
				if(m_strFontName.GetLength() > 0)
				{
					pButton->m_fontName = m_strFontName;
				}
				if( nFontSize > 0)
					pButton->m_fontSize = nFontSize;
				pButton->Invalidate();
			}
		}
	}
	pView->GetDocument()->SetModifiedFlag();
}

void CMainFrame::OnReturn(NMHDR* pNMHDR, LRESULT* pResult)
{
	UNREFERENCED_PARAMETER( pNMHDR );
	UNREFERENCED_PARAMETER( pResult );
	
	OnSelEndOk( );
}

//颜色选择完成
LRESULT CMainFrame::OnSelEndOKColor(WPARAM wParam, LPARAM lParam)
{
	UINT uiCmd = ( UINT )lParam;
	
	CMDIFrameWnd *pFrame = (CMDIFrameWnd*)AfxGetApp()->m_pMainWnd;
	CMDIChildWnd *pChild = (CMDIChildWnd *) pFrame->GetActiveFrame();
	CDrawView *pView = (CDrawView*)pChild->GetActiveView();	
	
	if(pView == NULL)
		return 0;
	
	if ( uiCmd == ID_FORMATTING_COLOR )
	{
		m_crCurrent = ( COLORREF )wParam;
		
		if(pView->m_selection.GetCount() >= 1)
		{
			
			POSITION pos = pView->m_selection.GetHeadPosition();
			while(pos != NULL)
			{
				CDrawObj * pObj = pView->m_selection.GetNext(pos);
				if(pObj->IsKindOf(RUNTIME_CLASS(CDrawButton)))
				{
					CDrawButton *pButton = (CDrawButton *)pObj;
					pButton->m_color = m_crCurrent;
					pButton->Invalidate();
				}
			}
		}
		pView->GetDocument()->SetModifiedFlag();
	}
	if( uiCmd == ID_FORMATTING_BACK_COLOR)
	{
		m_crFillColor = ( COLORREF )wParam;
		
		if(pView->m_selection.GetCount() >= 1)
		{
			
			POSITION pos = pView->m_selection.GetHeadPosition();
			while(pos != NULL)
			{
				CDrawObj * pObj = pView->m_selection.GetNext(pos);
				if(!pObj->IsKindOf(RUNTIME_CLASS(CDrawButton)))
				{
					pObj->m_clrFillColor = m_crFillColor;
					pObj->Invalidate();
				}
			}
		}
		pView->GetDocument()->SetModifiedFlag();

	}

	return 0;
}

LRESULT CMainFrame::OnToolbarDropDown(WPARAM wParam, LPARAM lParam)
{
	NMTOOLBAR* pNMTB = ( NMTOOLBAR* )wParam;

	if ( pNMTB->iItem == m_uCmdID )
	{
		// construct a pointer to the calling toolbar.
		CXTToolBar* pToolBar = DYNAMIC_DOWNCAST( CXTToolBar, CWnd::FromHandle( pNMTB->hdr.hwndFrom ) );
		ASSERT_VALID( pToolBar );

		// create the border popup
		CXTToolBarPopupWnd* pwndPopup = new CXTToolBarPopupWnd( m_uCmdID );
		pwndPopup->Create( pToolBar, IDR_LINE_WIDTH, 2 );

		return 1; // handled.
	}

	return 0;
}

void CMainFrame::SetMousePosText(CPoint Logpoint,CPoint Devpoint)
{

	CString strText;
	strText.Format("逻辑坐标:(%d,%d)",Logpoint.x,-Logpoint.y);
	int nIndex=m_wndStatusBar.CommandToIndex(ID_MOUSPOINT);
	m_wndStatusBar.SetPaneText(nIndex,strText);
	
	CWindowDC dc(&m_wndStatusBar);
	CSize sizeText=dc.GetTextExtent(strText);
//	m_wndStatusBar.SetPaneInfo(nIndex,ID_MOUSPOINT,SBPS_NORMAL,sizeText.cx);

    strText.Format("屏幕坐标:(%d,%d)",Devpoint.x,Devpoint.y);
	nIndex=m_wndStatusBar.CommandToIndex(ID_MOUSCAPTION);
	m_wndStatusBar.SetPaneText(nIndex,strText);
	
    sizeText=dc.GetTextExtent(strText);
	m_wndStatusBar.SetPaneInfo(nIndex,ID_MOUSCAPTION,SBPS_NORMAL,sizeText.cx);
}

//格式工具栏
void CMainFrame::OnViewFormat() 
{
	ShowControlBar( &m_wndFormatBar,!m_wndFormatBar.IsWindowVisible( ), FALSE );
}

void CMainFrame::OnUpdateViewFormat(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck( m_wndFormatBar.IsWindowVisible( ) );	
}

//导航器
void CMainFrame::OnViewWorkspace() 
{
	ShowControlBar( &m_wndTabDockBar,!m_wndTabDockBar.IsWindowVisible( ), FALSE );	
}

void CMainFrame::OnUpdateViewWorkspace(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck( m_wndTabDockBar.IsWindowVisible( ) );	
}

//工具箱
void CMainFrame::OnViewToolbox() 
{
	ShowControlBar( &m_wndToolboxBar,!m_wndToolboxBar.IsWindowVisible( ), FALSE );	
}

void CMainFrame::OnUpdateViewToolbox(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck( m_wndToolboxBar.IsWindowVisible( ) );	
}


void CMainFrame::OnFormattingColor() 
{
}

void CMainFrame::OnFormattingBackColor() 
{
}


/*
void CMainFrame::OnPupopActive() 
{
///	m_wndTabDockBar.m_wndTreeCtrl.OnPupopActive();	
}
*/
void CMainFrame::OnPopupClose() 
{
///	m_wndTabDockBar.m_wndTreeCtrl.OnColse();
}

void CMainFrame::OnPopupMin() 
{
///	m_wndTabDockBar.m_wndTreeCtrl.OnMinsize();
}

void CMainFrame::OnPopupProperty() 
{
///	m_wndTabDockBar.m_wndTreeCtrl.OnProperty();
}
