// ChildFrm.cpp : implementation of the CChildFrame class
//
// This file is a part of the XTREME TOOLKIT PRO MFC class library.
// (c)1998-2009 Codejock Software, All Rights Reserved.
//
// THIS SOURCE FILE IS THE PROPERTY OF CODEJOCK SOFTWARE AND IS NOT TO BE
// RE-DISTRIBUTED BY ANY MEANS WHATSOEVER WITHOUT THE EXPRESSED WRITTEN
// CONSENT OF CODEJOCK SOFTWARE.
//
// THIS SOURCE CODE CAN ONLY BE USED UNDER THE TERMS AND CONDITIONS OUTLINED
// IN THE XTREME TOOLKIT PRO LICENSE AGREEMENT. CODEJOCK SOFTWARE GRANTS TO
// YOU (ONE SOFTWARE DEVELOPER) THE LIMITED RIGHT TO USE THIS SOFTWARE ON A
// SINGLE COMPUTER.
//
// CONTACT INFORMATION:
// support@codejock.com
// http://www.codejock.com
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "GUI_VisualStudio.h"

#include "ChildFrm.h"
#include "FlatTabPropDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChildFrame

IMPLEMENT_DYNCREATE(CChildFrame, CMDIChildWnd)

BEGIN_MESSAGE_MAP(CChildFrame, CMDIChildWnd)
	//{{AFX_MSG_MAP(CChildFrame)
	ON_WM_CREATE()
	ON_COMMAND(ID_FLAT_TAB_PROP, OnFlatTabProp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChildFrame construction/destruction

CChildFrame::CChildFrame()
: m_pFlatTabCtrl(0)
, m_pFlatTabView(0)
{
	// TODO: add member initialization code here

}

CChildFrame::~CChildFrame()
{
}

BOOL CChildFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	if( !CMDIChildWnd::PreCreateWindow(cs) )
		return FALSE;

///	cs.style |= WS_CLIPCHILDREN;
	
///	cs.style = WS_CHILD | WS_VISIBLE | WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU
///		| FWS_ADDTOTITLE | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX 
///    ;

//	cs.style   &=~   (LONG)   FWS_PREFIXTITLE;
///	cs.style &= ~WS_MAXIMIZEBOX;
///	cs.style &= ~WS_THICKFRAME;
//   cs.style   &=~WS_VSCROLL;     FWS_ADDTOTITLE



	return TRUE;
}

/*
void CChildFrame::ActivateFrame(int nCmdShow)
{
	// TODO: Modify this function to change how the frame is activated.

	nCmdShow = SW_SHOWMAXIMIZED;

	CMDIChildWnd::ActivateFrame(nCmdShow);
}
*/

/////////////////////////////////////////////////////////////////////////////
// CChildFrame diagnostics

#ifdef _DEBUG
void CChildFrame::AssertValid() const
{
	CMDIChildWnd::AssertValid();
}

void CChildFrame::Dump(CDumpContext& dc) const
{
	CMDIChildWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CChildFrame message handlers

int CChildFrame::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CMDIChildWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	CMenu* pMenu = GetSystemMenu(FALSE);

	pMenu->RemoveMenu(SC_RESTORE, MF_BYCOMMAND);
	pMenu->RemoveMenu(SC_MINIMIZE, MF_BYCOMMAND);
	pMenu->RemoveMenu(SC_MAXIMIZE, MF_BYCOMMAND);
	pMenu->RemoveMenu(SC_MOVE, MF_BYCOMMAND);
	pMenu->RemoveMenu(SC_SIZE, MF_BYCOMMAND);
	
	return 0;
}

BOOL CChildFrame::OnCreateClient( LPCREATESTRUCT lpcs,
	CCreateContext* pContext)
{
	DragAcceptFiles();
/*
如何改变窗口标题  
     
  调用CWnd   :   :   SetWindowText可以改变任何窗口（包括控件）的标题。  
  //Set   title   for   application's   main   frame   window   .  
  AfxGetMainWnd   (   )   —>   SetWindowText   (_T("Application   title")   )  
  //Set   title   for   View's   MDI   child   frame   window   .  
  GetParentFrame   (   )   —>   SetWindowText   ("_T   ("MDI   Child   Frame   new   title")  
  )  
  //Set   title   for   dialog's   push   button   control.  
  GetDigitem   (IDC_BUTTON)   —>   SetWindowText   (_T   ("Button   new   title   ")   )   


#ifdef _XTP_INCLUDE_SYNTAXEDIT
	lpcs;
	return m_wndSplitter.Create( this,
		2, 2,                 // TODO: adjust the number of rows, columns
		CSize( 25, 25 ),      // TODO: adjust the minimum pane size
		pContext );
#else
	return CMDIChildWnd::OnCreateClient(lpcs, pContext);
#endif
*/
	return m_wndSplitter.Create( this,
		2, 2,                 // TODO: adjust the number of rows, columns  2, 2, 
		CSize( 10, 10 ),      // TODO: adjust the minimum pane size  10, 10
		pContext ,
        WS_CHILD | WS_VISIBLE | SPLS_DYNAMIC_SPLIT
			//		|WS_HSCROLL | WS_VSCROLL 
//		WS_CHILD | WS_VISIBLE | WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU 
//		| FWS_ADDTOTITLE | WS_MINIMIZEBOX | WS_MAXIMIZEBOX |WS_VSCROLL
		);
}

void CChildFrame::OnFlatTabProp() 
{
	if ( m_pFlatTabView && m_pFlatTabCtrl )
	{
		CFlatTabPropDlg	dlg(m_pFlatTabCtrl, m_pFlatTabView);
		dlg.DoModal();
	}
}
