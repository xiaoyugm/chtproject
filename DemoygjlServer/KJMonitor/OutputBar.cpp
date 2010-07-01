// OutputBar.cpp : implementation file
//
/////////////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "KJMonitor.h"
#include "OutputBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COutputBar

COutputBar::COutputBar()
{
	m_NowCount = 0 ;
	m_HistoryCount = 0 ;
}

COutputBar::~COutputBar()
{
	// TODO: add destruction code here.
}

IMPLEMENT_DYNAMIC(COutputBar, CXTDockWindow)

BEGIN_MESSAGE_MAP(COutputBar, CXTDockWindow)
	//{{AFX_MSG_MAP(COutputBar)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COutputBar message handlers

int COutputBar::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CXTDockWindow::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rectDummy(0, 0, 0, 0);

	// Create  the flat tab control.
	if (!m_flatTabCtrl.Create(WS_CHILD|WS_VISIBLE|FTS_XT_DEFAULT|FTS_XT_HSCROLL,
		CRect(0,0,0,0), this, IDC_FLATTABCTRL))
	{
		TRACE0( "Failed to create flattab control\n" );
		return -1;
	}

	// Define the default style for the output list boxes.
	DWORD dwStyle = WS_CHILD | WS_VSCROLL | WS_HSCROLL | WS_TABSTOP | LBS_NOINTEGRALHEIGHT | LBS_OWNERDRAWFIXED  | LBS_HASSTRINGS;

	// Create the sheet1 list box.          WS_HSCROLL     LBS_HASSTRINGS   | LBS_SORT
	if ( ::IsWindow( m_sheet1.m_hWnd ) )
	{
		m_sheet1.DestroyWindow();
	}
	if (!m_sheet1.Create( dwStyle, CRect(0,0,0,0), this, IDC_SHEET1 ))
	{
		TRACE0( "Failed to create sheet1.\n" );
		return -1;
	}
///	m_sheet1.SetHorizontalExtent(1024);

	// set the tab control to have a static edge border.
	m_flatTabCtrl.ModifyStyleEx(NULL, WS_EX_STATICEDGE);

	// Create the sheet2 list box.
	if (!m_sheet2.Create( dwStyle, CRect(0,0,0,0), this, IDC_SHEET2 ))
	{
		TRACE0( "Failed to create sheet2.\n" );
		return -1;
	}

	// Create the sheet3 list box.
	if ( ::IsWindow( m_sheet3.m_hWnd ) )
	{
		m_sheet3.DestroyWindow();
	}
	if (!m_sheet3.Create(WS_CHILD |  
		LVS_REPORT | LVS_NOCOLUMNHEADER, rectDummy, this, IDC_SHEET3 ))
	{
		TRACE0( "Failed to create sheet3.\n" );
		return -1;
	}
	ListView_SetExtendedListViewStyleEx(m_sheet3.m_hWnd,
		LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT);

	// Create the sheet4 list box.
	if ( ::IsWindow( m_sheet4.m_hWnd ) )
	{
		m_sheet4.DestroyWindow();
	}
	if (!m_sheet4.Create( WS_CHILD | WS_TABSTOP | WS_CLIPCHILDREN |
		WS_HSCROLL | WS_VSCROLL | ES_MULTILINE, rectDummy, this, IDC_SHEET4 ))
	{
		TRACE0( "Failed to create sheet4.\n" );
		return -1;
	}
	m_sheet4.SetFont(m_sheet3.GetFont());

	// Create the sheet5 list box.
	if ( ::IsWindow( m_sheet5.m_hWnd ) )
	{
		m_sheet5.DestroyWindow();
	}
	if (!m_sheet5.Create( 
		WS_CHILD | TVS_HASBUTTONS | TVS_HASLINES | TVS_LINESATROOT | WS_VSCROLL, 
		rectDummy, this, IDC_SHEET5 ))
	{
		TRACE0( "Failed to create sheet5.\n" );
		return -1;
	}

	// Insert tabs into the flat tab control.
	m_flatTabCtrl.InsertItem(0, _T("当前报警信息"), &m_sheet1);
	m_flatTabCtrl.InsertItem(1, _T("历史报警信息"), &m_sheet2);
	m_flatTabCtrl.InsertItem(2, _T("Build"),        &m_sheet3);
	m_flatTabCtrl.InsertItem(3, _T("Debug"),        &m_sheet4);
	m_flatTabCtrl.InsertItem(4, _T("Find in Files 1"), &m_sheet5);

	// Insert text into the list box.
	m_sheet3.InsertColumn(0, _T("Column"), LVCFMT_LEFT, 1024);
	m_sheet3.InsertItem(0, _T("-------------------- Configuration: FlatTabCtrl - Win32 Debug--------------------"));
	m_sheet3.InsertItem(1, _T("Compiling resources..."));
	m_sheet3.InsertItem(2, _T("Compiling..."));
	m_sheet3.InsertItem(3, _T("StdAfx.cpp"));
	m_sheet3.InsertItem(5, _T("Compiling..."));
	m_sheet3.InsertItem(6, _T("AboutDlg.cpp"));
	m_sheet3.InsertItem(7, _T("FlatTabCtrl.cpp"));
	m_sheet3.InsertItem(8, _T("FlatTabCtrlDlg.cpp"));
	m_sheet3.InsertItem(9, _T("Generating Code..."));
	m_sheet3.InsertItem(10, _T("Linking..."));
	m_sheet3.InsertItem(11, _T(""));
	m_sheet3.InsertItem(12, _T("FlatTabCtrl.exe - 0 error(s), 0 warning(s)"));

	m_sheet4.SetWindowText( 
		_T("Loaded 'C:\\WINNT\\System32\\ntdll.dll', no matching symbolic information found.\r\n")
		_T("Loaded symbols for 'C:\\WINNT\\system32\\MFC42D.DLL'\r\n")
		_T("Loaded symbols for 'C:\\WINNT\\system32\\MSVCRTD.DLL'\r\n")
		_T("Loaded 'C:\\WINNT\\system32\\                                                                                                                                                                                    KERNEL32.DLL', no matching symbolic information found.\r\n")
		_T("Loaded 'C:\\WINNT\\system32\\GDI32.DLL', no matching symbolic information found.\r\n")
		_T("Loaded 'C:\\WINNT\\system32\\USER32.DLL', no matching symbolic information found.\r\n")
		_T("Loaded 'C:\\WINNT\\system32\\ADVAPI32.DLL', no matching symbolic information found.\r\n")
		_T("Loaded 'C:\\WINNT\\system32\\rpcrt4.dll', no matching symbolic information found.\r\n")
		_T("Loaded 'C:\\WINNT\\system32\\SHELL32.DLL', no matching symbolic information found.\r\n")
		_T("Loaded 'C:\\WINNT\\system32\\shlwapi.dll', no matching symbolic information found.\r\n")
		_T("Loaded 'C:\\WINNT\\system32\\comctl32.dll', no matching symbolic information found.\r\n")
		_T("Loaded symbols for 'C:\\WINNT\\system32\\MFCO42D.DLL'\r\n")
		_T("Loaded 'C:\\WINNT\\system32\\OLE32.DLL', no matching symbolic information found.\r\n")
		_T("Loaded 'C:\\WINNT\\system32\\OLEAUT32.DLL', no matching symbolic information found.\r\n")
		_T("Loaded 'C:\\WINNT\\system32\\lpk.dll', no matching symbolic information found.\r\n")
		_T("Loaded 'C:\\WINNT\\system32\\usp10.dll', no matching symbolic information found.\r\n")
		_T("XTTOOLKIT_DLL.DLL Initializing!\r\n")
		_T("Loaded 'C:\\WINNT\\system32\\indicdll.dll', no matching symbolic information found.\r\n")
		_T("Loaded 'C:\\WINNT\\system32\\imm32.dll', no matching symbolic information found.\r\n")
		_T("The program 'D:\\prj\\XT\\Toolkit\\Bin\\FlatTabCtrl.exe' has exited with code 0 (0x0).\r\n"));

	HTREEITEM file;
	file = m_sheet5.InsertItem(_T("D:\\Toolkit\\Samples\\FlatTabCtrl\\EditCtrlForFlatTab.cpp"));
	m_sheet5.InsertItem(_T("Line 92:            pSB->Create                                                                                                                                                           (WS_CHILD, CRect(0, 0, 0, 0), (CWnd *)this, 0)"), 0, 0, file);
	file = m_sheet5.InsertItem(_T("D:\\Toolkit\\Samples\\FlatTabCtrl\\FlatTabCtrl.rc"));
	m_sheet5.InsertItem(_T("Line 190:STYLE WS_CHILD"), 0, 0, file);
	file = m_sheet5.InsertItem(_T("D:\\Toolkit\\Samples\\FlatTabCtrl\\FlatTabCtrlDlg.cpp"));
	m_sheet5.InsertItem(_T("Line 92:            pSB->Create(WS_CHILD, CRect(0, 0, 0, 0), (CWnd *)this, 0)"), 0, 0, file);
	m_sheet5.InsertItem(_T("Line 265:	if (!m_pFlatTabCtrl->Create(WS_CHILD|WS_VISIBLE|m_dwTabStyle,"), 0, 0, file);
	m_sheet5.InsertItem(_T("Line 293:	if (!m_sheet1.Create(WS_CHILD |  "), 0, 0, file);
	m_sheet5.InsertItem(_T("Line 303:	if (!m_sheet2.Create( WS_CHILD | WS_TABSTOP | WS_CLIPCHILDREN |"), 0, 0, file);
	m_sheet5.InsertItem(_T("Line 312:	DWORD dwStyle = WS_CHILD | LBS_NOINTEGRALHEIGHT | WS_TABSTOP | WS_VSCROLL;"), 0, 0, file);
	m_sheet5.InsertItem(_T("Line 316:		WS_CHILD | TVS_HASBUTTONS | TVS_HASLINES | TVS_LINESATROOT | WS_VSCROLL, "), 0, 0, file);
	m_sheet5.InsertItem(_T("Line 348:        !((CWnd *)m_pSheet7)->Create(NULL, NULL, WS_CHILD, "), 0, 0, file);
	file = m_sheet5.InsertItem(_T("D:\\Toolkit\\Samples\\FlatTabCtrl\\SampleFormView.cpp"));
	m_sheet5.InsertItem(_T("Line 79:    m_ScrollBarH.Create(WS_CHILD, CRect(0, 0, 0, 0), this, 0);"), 0, 0, file);
	
	// Set the current tab.
	m_flatTabCtrl.SetCurSel(0);

	// Draw an edge around the control.
	SetXTBarStyle(CBRS_XT_DEFAULT|CBRS_XT_CLIENT_STATIC);

	// Associate the flat tab control with the docking window.
	SetChild(&m_flatTabCtrl);

	return 0;
}

BOOL COutputBar::CreateTabOutputWnd(COutputBarEdit& wndOutput, UINT nID)
{
	// Create the sheet1 list box.
	if (!wndOutput.Create(WS_CHILD, CRect(0,0,0,0), &m_flatTabCtrl, nID))
	{
		TRACE1( "Failed to create sheet id=%d.\n", nID );
		return FALSE;
	}

	wndOutput.SetFont(&m_sheetFont);

	return TRUE;
}

void COutputBar::AddDispWarnItem(int nWarnNormal, CString strItemText)
{
	m_NowCount ++ ;
	if(m_NowCount > 50)
	{
       	switch(nWarnNormal)
		{
        	case 0:  
         		m_sheet1.InsertString(0 , strItemText,RGB(0,255,0));
	        	break;
          	case 1: 
        		m_sheet1.InsertString(0, strItemText,RGB(255,128,0));
	         	break;
          	case 2: 
        		m_sheet1.InsertString(0, strItemText,RGB(255,0,0));
	         	break;
          	case 3: 
        		m_sheet1.InsertString(0, strItemText,RGB(255,255,0));
	         	break;
        	default:
          		break;
		}
    		char buf[256];
    		m_sheet1.GetText(50 ,buf);
    		CString strtemp = buf;

        	COLORREF rgb;
            int flag1 = GetFlag(50);
	    	if (flag1 == 0)
	    		rgb = RGB(0,255,0);
	     	else if(flag1 == 1)
	      		rgb = RGB(255, 128, 0);
	     	else if(flag1 == 2)
	      		rgb = RGB(255, 0, 0);
			else
	      		rgb = RGB(255, 255, 0);

    		m_sheet1.DeleteString(50);

    	m_HistoryCount ++ ;
		if(m_HistoryCount > 50 )
		{
         	m_sheet2.InsertString(0, strtemp , rgb);
    		m_sheet2.DeleteString(50);
		}
		else
         	m_sheet2.InsertString(0, strtemp , rgb);
	}
	else
	{
       	switch(nWarnNormal)
		{
        	case 0:  
         		m_sheet1.InsertString(0 , strItemText,RGB(0,255,0));
	        	break;
          	case 1: 
        		m_sheet1.InsertString(0, strItemText,RGB(255,128,0));
	         	break;
          	case 2: 
        		m_sheet1.InsertString(0, strItemText,RGB(255,0,0));
	         	break;
          	case 3: 
        		m_sheet1.InsertString(0, strItemText,RGB(255,255,0));
	         	break;
        	default:
          		break;
		}
	}
}

int COutputBar::GetFlag(int nIndex)
{
	COLORREF rgb;
		rgb = m_sheet1.getColor(nIndex);
	if (rgb == RGB(255,255,0))
		return 3;
	else if (rgb == RGB(255,0,0))
		return 2;
	else if (rgb == RGB(255,128,0))
		return 1;
	else 
		return 0;
}