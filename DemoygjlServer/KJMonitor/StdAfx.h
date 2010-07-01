// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__4EB381E9_2074_4710_A00F_1B91AD7B0359__INCLUDED_)
#define AFX_STDAFX_H__4EB381E9_2074_4710_A00F_1B91AD7B0359__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes
#if _MSC_VER >= 1200
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT                   NPORT(\\)
#include "afxdb.h"

#include <XTToolKit.h>      // Xtreme Toolkit MFC Extensions

#include <afxsock.h>		// 
#include "NPORT\\nport.h"
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.
#import "C:\Program Files\Common Files\System\ADO\MSADO15.DLL" rename_namespace("ADOCust") rename("EOF","EndOfFile") 
using namespace ADOCust;
#endif // !defined(AFX_STDAFX_H__4EB381E9_2074_4710_A00F_1B91AD7B0359__INCLUDED_)
