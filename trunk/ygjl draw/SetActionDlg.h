#if !defined(AFX_SETACTIONDLG_H__7F1F75B2_1B90_4C55_9D56_5253E92882DC__INCLUDED_)
#define AFX_SETACTIONDLG_H__7F1F75B2_1B90_4C55_9D56_5253E92882DC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetActionDlg.h : header file
//
#include "enum.h"
/////////////////////////////////////////////////////////////////////////////
// CSetActionDlg dialog

class CSetActionDlg : public CDialog
{
// Construction
public:
	CSetActionDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSetActionDlg)
	enum { IDD = IDD_DIALOG_SET_ACTION };
	BOOL	m_bIsFillAction;
	BOOL	m_bIsLineAction;
	BOOL	m_bIsPercentHAction;
	BOOL	m_bIsPercentVAction;
	BOOL	m_bIsRayAction;
	//}}AFX_DATA
public:
	ActionStruct	m_ActionStruct;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSetActionDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSetActionDlg)
	afx_msg void OnButtonLine();
	afx_msg void OnButtonFill();
	afx_msg void OnButtonRay();
	afx_msg void OnButtonPercentH();
	afx_msg void OnButtonPercentV();
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETACTIONDLG_H__7F1F75B2_1B90_4C55_9D56_5253E92882DC__INCLUDED_)
