// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__5A7448CA_4FAB_4377_BC81_E6CE66F7DD8E__INCLUDED_)
#define AFX_STDAFX_H__5A7448CA_4FAB_4377_BC81_E6CE66F7DD8E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#if _MSC_VER >= 1300
	#define WPD_CHARFORMAT CHARFORMAT2
	#define WPD_PARAFORMAT PARAFORMAT2
#else
	#define WPD_CHARFORMAT CHARFORMAT
	#define WPD_PARAFORMAT PARAFORMAT
#endif

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxole.h>         // MFC OLE classes
#include <afxodlgs.h>       // MFC OLE dialog classes
#include <afxdisp.h>        // MFC Automation classes
#if _MSC_VER >= 1200
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <windows.h>
#include <Winuser.h>
#include <activscp.h>
#include <afxpriv.h>
#include <afxconv.h>
#include <objsafe.h>
#include <afxctl.h>
#include <afxtempl.h>
#include <comcat.h>
#include <shlwapi.h>
#pragma comment(lib,"shlwapi.lib")
#pragma message("Automatically linking with shlwapi.lib")

#include <XTToolKit.h>      // Xtreme Toolkit MFC Extensions

#include <GdiPlus.h>		//GDI+
#pragma comment(lib,"gdiplus.lib")
//#pragma message("Automatically linking with gdiplus.lib")
using namespace Gdiplus;

#import "Dll\\MSADO15.DLL" rename_namespace("ADOCust") rename("EOF","EndOfFile") 
using namespace ADOCust;

#pragma warning (disable : 4201)
	#include "mmsystem.h"
	#pragma comment(lib,"winmm.lib") 
	#pragma message("Automatically linking with winmm.lib")
#pragma warning (default : 4201)

struct CCharFormat : public WPD_CHARFORMAT
{
	CCharFormat() {cbSize = sizeof(WPD_CHARFORMAT);}
	BOOL operator==(CCharFormat& cf);
};
/*
typedef struct {
    COLORREF crColour;
    TCHAR    *szName;
} ColourTableEntry;
*/
#pragma warning (disable : 4244)
#pragma warning (disable : 4146)
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__5A7448CA_4FAB_4377_BC81_E6CE66F7DD8E__INCLUDED_)
