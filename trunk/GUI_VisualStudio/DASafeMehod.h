#if !defined(AFX_DASAFEMEHOD_H__5558166C_628C_427F_8559_C0F552449BE0__INCLUDED_)
#define AFX_DASAFEMEHOD_H__5558166C_628C_427F_8559_C0F552449BE0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DASafeMehod.h : header file
//

#include "dbAx\AxSControl.hpp"
#include "dbAx\AxAccountSet.hpp"
#include "dbAx\AxContactCmd.hpp"
#include "dbAx\AxContactSet.hpp"
#include "dbAx\CardFileEvents.hpp"
#include "dbAx\AccountSetEvents.hpp"
/////////////////////////////////////////////////////////////////////////////
// CDASafeMehod dialog

class CDASafeMehod : public CDialog
{
// Construction
public:
	CDASafeMehod(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDASafeMehod)
	enum { IDD = IDD_DLG_A_METHOD };
		// NOTE: the ClassWizard will add data members here
	CXTFlatComboBox     m_ComBoxSM;
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
	//{{AFX_VIRTUAL(CDASafeMehod)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDASafeMehod)
	afx_msg void OnchCB();
    afx_msg void OnBnOkSM();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DASAFEMEHOD_H__5558166C_628C_427F_8559_C0F552449BE0__INCLUDED_)
