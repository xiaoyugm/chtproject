//#if !defined(AFX_SAFEMETHOD_H__EB74F9C2_BD3E_4A43_B314_4A51111DD5DA__INCLUDED_)
//#define AFX_SAFEMETHOD_H__EB74F9C2_BD3E_4A43_B314_4A51111DD5DA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SafeMethod.h : header file
//

#include "dbAx\AxSControl.hpp"
#include "dbAx\AxAccountSet.hpp"
#include "dbAx\AxContactCmd.hpp"
#include "dbAx\AxContactSet.hpp"
#include "dbAx\CardFileEvents.hpp"
#include "dbAx\AccountSetEvents.hpp"
/////////////////////////////////////////////////////////////////////////////
// CSafeMethod dialog

class CSafeMethod : public CDialog
{
// Construction
public:
	CSafeMethod(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSafeMethod)
	enum { IDD = IDD_DIA_A_METHOD };
		// NOTE: the ClassWizard will add data members here
	CXTFlatComboBox     m_ComBoxSM;
	CXTFlatComboBox     m_ComBoxSM2;
	CXTListCtrl         m_LDCH;
	CXTHeaderCtrl   m_header;
    CString    strsm;
	//}}AFX_DATA
    CAxConnection   m_Cn;
    CAxContactCmd   m_ContactCmd;
    CAxPointDescription  m_PointDes;
	CRealtimedata   m_Realtimedata;
	CRealtimedata   *m_RealtimedataNew;

	CString2DataType    m_Str2Data;

	void OnClose();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSafeMethod)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    virtual BOOL OnInitDialog();
//	virtual BOOL DestroyWindow();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSafeMethod)
    afx_msg void OnBfds();
    afx_msg void OnBnOkSM();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

//#endif // !defined(AFX_SAFEMETHOD_H__EB74F9C2_BD3E_4A43_B314_4A51111DD5DA__INCLUDED_)
