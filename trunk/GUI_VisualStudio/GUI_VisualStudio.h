// GUI_VisualStudio.h : main header file for the GUI_VISUALSTUDIO application
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

#if !defined(AFX_GUI_VISUALSTUDIO_H__43A4C0AC_0369_4063_BC19_7EBCB371EFD9__INCLUDED_)
#define AFX_GUI_VISUALSTUDIO_H__43A4C0AC_0369_4063_BC19_7EBCB371EFD9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

#include "MQServer.h"
#include "MQClient.h"
#include "drawview.h"
//#include <SqlDirect.h>
#include <String2DataType.h>
#include "dbAx\AxPointDescription.hpp"
#include "dbAx\AxAccountSet.hpp"
#include "dbAx\AxContactSet.hpp"
#include "dbAx\AxDisPoint.hpp"
#include "dbAx\CardFileEvents.hpp"

/////////////////////////////////////////////////////////////////////////////
// CGUI_VisualStudioApp:
// See GUI_VisualStudio.cpp for the implementation of this class
//

class CGUI_VisualStudioApp : public CWinApp
{
public:
	CGUI_VisualStudioApp();

	BOOL   ProcessShellCommand(CCommandLineInfo& rCmdInfo);
    CMQServer  SocketServer;
    CMQClient socketClient;
	BOOL   StartClient();
	void   SendMessage(CNDKMessage& message);     //211
	void   Sync(CNDKMessage& message);
	CNDKMessage m_sendmessage;

	CString GetAppPath();				//返回应用程序所在路径
	ULONG_PTR           gdiplusToken;
	CString2DataType m_Str2Data;

	BOOL   InitUIInfo();
	BOOL   InitData();
	
	void   OnCloseDB();
	BOOL   ConnectDB();
	BOOL   InitPointInfo();
	BOOL   InitDisplay();
    void   pushDIS(CString  str1,CString  str2,CString  str3);
	void   BuildDIS(CString  strItem);

    CCardFileEvents *pCnEvents;
    CAxConnection   m_Cn;
    CAxPointDescription  m_PointDes;
    CAxAccountSet   m_AccountSet;
    CAxContactSet   m_ContactSet;
    CAxDisPoint      m_DisPoint;
	//	CSQLDirect		m_sqlD;		//数据库
	CString2DataType m_String2DataType;
	int DocNum ,idis;
	CString curuser; //,IPPort

	bool m_senddata , m_sendcom;

///	CPointInfo      *pPointInfo;
	CMultiDocTemplate* pDocTemplate;
	CMultiDocTemplate* pNewDocTemplate;
	CMultiDocTemplate* pTabViewDocTemplate;

	CTypedPtrMap<CMapStringToOb,CString,CDrawView *> m_map;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGUI_VisualStudioApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

	COleTemplateServer m_server;
// Implementation
	//{{AFX_MSG(CGUI_VisualStudioApp)
	afx_msg void OnAppAbout();
	afx_msg void OnWindowCloseAll();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

extern CGUI_VisualStudioApp theApp;
extern CString gstrTimeOut;

AFX_INLINE BOOL CreateImageList(CImageList& il, UINT nID)
{
	if (!il.Create(16, 16, ILC_MASK|ILC_COLOR24, 0, 1))
		return FALSE;
	CBitmap bmp;
	VERIFY(bmp.LoadBitmap(nID));

	il.Add(&bmp, CXTPImageManager::GetBitmapMaskColor(bmp, CPoint(0, 0)));

	return TRUE;
}

class COfficeTreeCtrl : public CXTPOfficeBorder<CTreeCtrl>
{
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult)		
	{
		NMHDR* pNMHDR = (NMHDR*)lParam;
		
		switch (pNMHDR->code)
		{
		case TTN_SHOW:
			{
				// get a pointer to the tooltip control.
				HWND hWnd = TreeView_GetToolTips(m_hWnd);
				if (hWnd != NULL)
				{
					// make sure the tooltip is at the top of the "Z" order, otherwise
					// it will appear behind popup windows....
					::SetWindowPos(hWnd, HWND_TOP, 0, 0, 0, 0,
						SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
				}
			}
			break;
		}
		return CXTPOfficeBorder<CTreeCtrl>::OnNotify(wParam, lParam, pResult);
	}
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GUI_VISUALSTUDIO_H__43A4C0AC_0369_4063_BC19_7EBCB371EFD9__INCLUDED_)
