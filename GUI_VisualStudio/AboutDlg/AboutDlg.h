// AboutDlg.h : header file
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

#if !defined(__ABOUTDLG_H__)
#define __ABOUTDLG_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#if (_MSC_VER > 1310) // VS2005
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_IA64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='ia64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif


/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog
#include "stdafx.h"
#include "Resource.h"

class CAboutDlg : public CDialog
{
// Construction
public:
	CAboutDlg(CWnd* pParent = NULL);
/*		: CDialog(IDD_ABOUTBOX, pParent)
	{
/*		NONCLIENTMETRICS ncm;
		::ZeroMemory(&ncm, sizeof(NONCLIENTMETRICS));
		ncm.cbSize = sizeof(NONCLIENTMETRICS);
		
		VERIFY(::SystemParametersInfo(SPI_GETNONCLIENTMETRICS,
			sizeof(NONCLIENTMETRICS), &ncm, 0));

		ncm.lfMenuFont.lfWeight = FW_BOLD;
		m_fontBold.CreateFontIndirect(&ncm.lfMenuFont);
    	BrushHol.CreateStockObject(HOLLOW_BRUSH);
	}
*/
// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	//enum { IDD = IDD_ABOUTBOX };
	CStatic m_txtPackageVersion;
	CStatic m_txtCopyrightInfo;
	CStatic m_txtAppName;
	CXTButton m_btnOk;
	CXTHyperLink m_txtURL;
	CXTHyperLink m_txtEmail;
	//}}AFX_DATA

	HICON m_hIcon;
	CBrush BrushHol;
	CFont m_fontBold;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
/*	{
		CDialog::DoDataExchange(pDX);
		//{{AFX_DATA_MAP(CAboutDlg)
		DDX_Control(pDX, IDC_TXT_TITLE, m_txtPackageVersion);
		DDX_Control(pDX, IDC_TXT_COPYRIGHT, m_txtCopyrightInfo);
		DDX_Control(pDX, IDC_TXT_APPNAME, m_txtAppName);
		DDX_Control(pDX, IDOK, m_btnOk);
		DDX_Control(pDX, IDC_TXT_URL, m_txtURL);
		DDX_Control(pDX, IDC_TXT_EMAIL, m_txtEmail);
		//}}AFX_DATA_MAP
	}*/
	// Generated message map functions
	//{{AFX_MSG(CSetTimeDlg)
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnDestroy();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	virtual BOOL OnInitDialog()
	{
		CDialog::OnInitDialog();

		// get a pointer to CWinApp.
		CWinApp* pApp = AfxGetApp( );
		ASSERT( pApp != NULL );

//	Invalidate(1);
		// set the sample title.
		CString csSampleTitle;
		csSampleTitle.Format(_T("%s 应用"), pApp->m_pszAppName);
		m_txtAppName.SetWindowText( csSampleTitle );

		// set the package version.
		CString csPackageVersion;
		csPackageVersion.Format( _T( "%s v%d.%d.%d" ),
			_XTP_PACKAGE_NAME, _XTPLIB_VERSION_MAJOR, _XTPLIB_VERSION_MINOR, _XTPLIB_VERSION_REVISION);
		m_txtPackageVersion.SetWindowText( "版本 2.0" );

		// set the about caption.
		CString csAboutCaption;
		csAboutCaption.Format( _T("关于 %s" ), pApp->m_pszAppName );
		SetWindowText( csAboutCaption );

		// set the copyright info.
		CString csCopyrightInfo;
		csCopyrightInfo.Format( _T( "(c) 2003-%d 阳光金力煤矿安全监控" ),
//		csCopyrightInfo.Format( _T( "(c)2003-%d 阳光金力, All Rights Reserved" ),
			COleDateTime::GetCurrentTime().GetYear( ) );
		m_txtCopyrightInfo.SetWindowText( csCopyrightInfo );

		// set the title text to bold font.
		m_txtPackageVersion.SetFont( &m_fontBold );

		// define the url for our hyperlinks.
		m_txtURL.SetURL( _T( "网址: http://www.xxx.com" ) );
		m_txtURL.SetUnderline( false );

		m_txtEmail.SetURL( _T( "邮箱:robustwellcao@gmail.com" ) );//mailto:
		m_txtEmail.SetUnderline( false );

		// set OK button style.
		m_btnOk.SetXButtonStyle( BS_XT_SEMIFLAT | BS_XT_HILITEPRESSED | BS_XT_WINXP_COMPAT );
        GetDlgItem(IDOK)->SetWindowText(_T("确定"));


		return TRUE;  // return TRUE unless you set the focus to a control
		              // EXCEPTION: OCX Property Pages should return FALSE
	}

};

CAboutDlg::CAboutDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_ABOUTBOX, pParent)
	{
/*		NONCLIENTMETRICS ncm;
		::ZeroMemory(&ncm, sizeof(NONCLIENTMETRICS));
		ncm.cbSize = sizeof(NONCLIENTMETRICS);
		
		VERIFY(::SystemParametersInfo(SPI_GETNONCLIENTMETRICS,
			sizeof(NONCLIENTMETRICS), &ncm, 0));

		ncm.lfMenuFont.lfWeight = FW_BOLD;
		m_fontBold.CreateFontIndirect(&ncm.lfMenuFont);*/
    	BrushHol.CreateStockObject(HOLLOW_BRUSH);
	}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
		CDialog::DoDataExchange(pDX);
		//{{AFX_DATA_MAP(CAboutDlg)
		DDX_Control(pDX, IDC_TXT_TITLE, m_txtPackageVersion);
		DDX_Control(pDX, IDC_TXT_COPYRIGHT, m_txtCopyrightInfo);
		DDX_Control(pDX, IDC_TXT_APPNAME, m_txtAppName);
		DDX_Control(pDX, IDOK, m_btnOk);
		DDX_Control(pDX, IDC_TXT_URL, m_txtURL);
		DDX_Control(pDX, IDC_TXT_EMAIL, m_txtEmail);
		//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CSetTimeDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_ERASEBKGND()
	ON_WM_DESTROY()
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CAboutDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CAboutDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


BOOL CAboutDlg::OnEraseBkgnd(CDC* pDC)
{
/*	CDC dcMemory;
	dcMemory.CreateCompatibleDC(pDC);
	CBitmap* pOldBitmap = dcMemory.SelectObject(&Background);
	CRect rcClient;
	GetClientRect(&rcClient);
	const CSize& sBitmap = BitmapSize;
	pDC->BitBlt(0,0,rcClient.Width(),rcClient.Height(),&dcMemory,0,0,SRCCOPY);
//	pDC->BitBlt(0,0,sBitmap.cx,sBitmap.cy,&dcMemory,0,0,SRCCOPY);
	dcMemory.SelectObject(pOldBitmap);
*/
	CommonTools C_Ts;
	CString strappPath ;
	strappPath = C_Ts.GetAppPath() ;
	strappPath += "\\Image\\BackGround.bmp";
	CRect rect;
	GetClientRect(&rect);
	Rect GdiRect (rect.TopLeft().x,rect.TopLeft().y,rect.Size().cx,rect.Size().cy); 

	Graphics graphics (pDC->m_hDC);
        		BSTR strPicPath = strappPath.AllocSysString();
///        		BSTR strPicPath = _com_util::ConvertStringToBSTR(m_strPictureName);
        		Image  m_pimage(strPicPath);
      	       	SysFreeString(strPicPath);
//            	m_pimage.RotateFlip(Rotate180FlipX);
           		graphics.DrawImage(&m_pimage, GdiRect);
	graphics.ReleaseHDC(pDC->m_hDC);

	return TRUE;
	//return CDialog::OnEraseBkgnd(pDC); Remove and return TRUE
}

void CAboutDlg::OnDestroy()
{
	CDialog::OnDestroy();

	BrushHol.DeleteObject();
}

HBRUSH CAboutDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
//	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	pDC->SetBkMode(TRANSPARENT);
	if( pWnd->GetDlgCtrlID() == IDC_STATIC)
	{
		pDC->SetTextColor(RGB(255, 0, 0));
	}
	// TODO:  Return a different brush if the default is not desired
	return BrushHol;
}




#ifdef ENABLE_MANIFESTEDITOR


#if !defined(_UNICODE) && (_MSC_VER < 1400)

#if _MSC_VER > 1200 //MFC 7.0
#include <..\src\mfc\afximpl.h> // MFC Global data
#else
#include <..\src\afximpl.h>     // MFC Global data
#endif

#endif

AFX_INLINE void EnableManifestEditor()
{
#if !defined(_UNICODE) && (_MSC_VER < 1400)
	OSVERSIONINFO ovi = {sizeof(OSVERSIONINFO)};
	::GetVersionEx(&ovi);

	if ((ovi.dwPlatformId >= VER_PLATFORM_WIN32_NT) && (ovi.dwMajorVersion >= 5))
	{
#if (_MSC_VER >= 1200)
		afxData.bWin95 = TRUE;
#else
		afxData.bWin32s = TRUE;
#endif
	}
#endif
}

#else

AFX_INLINE void EnableManifestEditor()
{
}

#endif


AFX_INLINE void ShowSampleHelpPopup(CWnd* pParentWnd, UINT nIDResource)
{
	CXTPPopupControl* pPopup = new CXTPPopupControl();
	pPopup->SetTransparency(200);
	pPopup->SetTheme(xtpPopupThemeOffice2003);
	pPopup->AllowMove(TRUE);
	pPopup->SetAnimateDelay(500);
	pPopup->SetPopupAnimation();
	pPopup->SetShowDelay(5000);
	pPopup->SetAutoDelete(TRUE);
	
	CXTPPopupItem* pItemText = (CXTPPopupItem*)pPopup->AddItem(new CXTPPopupItem(CRect(8, 12, 500, 130)));
	pItemText->SetRTFText(nIDResource);
	pItemText->FitToContent();
	CSize sz(pItemText->GetRect().Size());

	// close icon.
	CXTPPopupItem* pItemIcon = (CXTPPopupItem*)pPopup->AddItem(
		new CXTPPopupItem(CRect(sz.cx + 2, 10, sz.cx + 2 + 16, 10 + 16)));
	
	pPopup->GetImageManager()->SetIcon(IDI_POPUP_CLOSE, IDI_POPUP_CLOSE);
	pItemIcon->SetIconIndex(IDI_POPUP_CLOSE);

	pItemIcon->SetButton(TRUE);
	pItemIcon->SetID(XTP_ID_POPUP_CLOSE);

	pPopup->SetPopupSize(CSize(sz.cx + 20, sz.cy + 20));
	pPopup->Show(pParentWnd);
}


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(__ABOUTDLG_H__)
