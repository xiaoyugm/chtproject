#if !defined(AFX_CLASSTIME_H__7DDB21DF_B0FF_4911_AF84_57652A49E823__INCLUDED_)
#define AFX_CLASSTIME_H__7DDB21DF_B0FF_4911_AF84_57652A49E823__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ClassTime.h : header file
//

#include "dbAx\AxLogin.hpp"
#include "dbAx\AccountSetEvents.hpp"
/////////////////////////////////////////////////////////////////////////////
// CClassTime dialog

class CClassTime : public CXTResizeDialog
{
// Construction
public:
	CClassTime(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CClassTime)
	enum { IDD = IDD_DIA_CLASS };
	UINT	m_ctrlDayH;
	UINT    m_classnum;
	//}}AFX_DATA
    CCardFileEvents *pCnEvents;
    CAxConnection   m_Cn;
    CAxCommonSet        m_CommonSet;
    CAxCommonSet        *m_CommonSetNew;

    void    ConnectDB();
	CString2DataType m_Str2Data;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClassTime)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CClassTime)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnChadayr();
	afx_msg void OnChaclass();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLASSTIME_H__7DDB21DF_B0FF_4911_AF84_57652A49E823__INCLUDED_)
