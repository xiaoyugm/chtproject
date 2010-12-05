// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__C8428A7A_6E2A_4196_8377_7A28439C2A2F__INCLUDED_)
#define AFX_STDAFX_H__C8428A7A_6E2A_4196_8377_7A28439C2A2F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT
#include <afxcoll.h>
#include <afxtempl.h>
#include <afxsock.h>
#include <afxdb.h>

//#define AUTO_SUBCLASS       //added 
//#define MFCX_PROJ           //added 
//#include "XTToolkit.h"
#include <SqlDirect.h>
#pragma comment(lib,"CommonTools.lib")

#include <XTToolkitPro.h>   // Codejock Software Components
//#include <AboutDlg.h>       // Sample About Dialog

#include <GdiPlus.h>		//GDI+
#pragma comment(lib,"gdiplus.lib")
using namespace Gdiplus;


//#import "MSADO15.DLL" rename_namespace("ADOCust") rename("EOF","EndOfFile") 
//#define DEBUG_VER
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.
//#import "C:\Program Files\Common Files\System\ADO\MSADO15.DLL" rename_namespace("ADOCust") rename("EOF","EndOfFile") 
//using namespace ADOCust;

#endif // !defined(AFX_STDAFX_H__206B92CF_8EC7_412C_B52A_D254F5853948__INCLUDED_)
