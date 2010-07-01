#if !defined(AFX_USERPASSWDDLG_H__8687636A_EC27_47C4_ADFA_C6105E289927__INCLUDED_)
#define AFX_USERPASSWDDLG_H__8687636A_EC27_47C4_ADFA_C6105E289927__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// UserPasswdDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CUserPasswdDlg dialog
#include "Controls\\XPStyleButtonST.h"
#include "Controls\\ThemeHelperST.h"


class CUserPasswdDlg : public CDialog
{
// Construction
public:
	CUserPasswdDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CUserPasswdDlg)
	enum { IDD = IDD_DLG_USERPASSWD };
	CXPStyleButtonST 	m_btnADDUSER;
	CXPStyleButtonST 	m_btnVIEWRECORD;
	CXPStyleButtonST 	m_btnMODEFYPWD;
	CXPStyleButtonST m_btnOK;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUserPasswdDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CUserPasswdDlg)
	afx_msg void OnButtonModifypwd();
	afx_msg void OnButtonAdduser();
	afx_msg void OnButtonViewrecord();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	CThemeHelperST	m_ThemeHelper;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_USERPASSWDDLG_H__8687636A_EC27_47C4_ADFA_C6105E289927__INCLUDED_)
