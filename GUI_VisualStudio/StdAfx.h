// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
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

#if !defined(AFX_STDAFX_H__5128F74D_6242_4586_A897_6F6EDDE36C3D__INCLUDED_)
#define AFX_STDAFX_H__5128F74D_6242_4586_A897_6F6EDDE36C3D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN        // Exclude rarely-used stuff from Windows headers

#if _MSC_VER > 1200

// Modify the following defines if you have to target a platform prior to the ones specified below.
// Refer to MSDN for the latest info on corresponding values for different platforms.
#ifndef WINVER              // Allow use of features specific to Windows 95 and Windows NT 4 or later.
#define WINVER 0x0400       // Change this to the appropriate value to target Windows 98 and Windows 2000 or later.
#endif

#ifndef _WIN32_WINNT        // Allow use of features specific to Windows NT 4 or later.
#if _MSC_VER > 1500
#define _WIN32_WINNT 0x0500
#else
#define _WIN32_WINNT 0x0400     // Change this to the appropriate value to target Windows 98 and Windows 2000 or later.
#endif
#endif

#ifndef _WIN32_WINDOWS      // Allow use of features specific to Windows 98 or later.
#define _WIN32_WINDOWS 0x0410 // Change this to the appropriate value to target Windows Me or later.
#endif

#ifndef _WIN32_IE           // Allow use of features specific to IE 4.0 or later.
#define _WIN32_IE 0x0500    // Change this to the appropriate value to target IE 5.0 or later.
#endif

#endif

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes
#if _MSC_VER >= 1200
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>         // MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT


// Lets help compiler to skip some headers
#define _XTP_EXCLUDE_CALENDAR
#define _XTP_EXCLUDE_REPORTCONTROL


#define ENABLE_MANIFESTEDITOR

#include <XTToolkitPro.h>   // Codejock Software Components
#include <AboutDlg.h>       // Sample About Dialog

#if _MSC_VER >= 1300
	#define WPD_CHARFORMAT CHARFORMAT2
	#define WPD_PARAFORMAT PARAFORMAT2
#else
	#define WPD_CHARFORMAT CHARFORMAT
	#define WPD_PARAFORMAT PARAFORMAT
#endif

#include <afxole.h>         // MFC OLE classes
#include <afxodlgs.h>       // MFC OLE dialog classes

#include "Enum.h"
#include "DataStructure.h"

#include "IniFile.h"

//#include   <afxsock.h> 
#include <NDKClient.h>
#pragma comment(lib,"NDK.lib")
#include <SqlDirect.h>

#include <GdiPlus.h>		//GDI+
#pragma comment(lib,"gdiplus.lib")
using namespace Gdiplus;

#pragma comment(lib,"SQL.lib")

#include <sqlite3.h>		//
#pragma comment(lib,"sqlite3.lib")
#include "dbAx\\CppSQLite3.h"

#include <atlbase.h>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

#include "CGridListCtrlEx\CGridColumnManagerProfile.h"
#include "CGridListCtrlEx\CGridColumnTraitEdit.h"
#include "CGridListCtrlEx\CGridColumnTraitCombo.h"
#include "CGridListCtrlEx\CGridRowTraitXP.h"
#include "CGridListCtrlEx\CGridListCtrlGroups.h"
#include "CListCtrl_DataModel.h"




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

typedef struct {
    COLORREF crColour;
    TCHAR    *szName;
} ColourTableEntry;
 

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__5128F74D_6242_4586_A897_6F6EDDE36C3D__INCLUDED_)
