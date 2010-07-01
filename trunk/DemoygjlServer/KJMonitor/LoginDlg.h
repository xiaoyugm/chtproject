#if !defined(AFX_LOGINDLG_H__9CF3A640_2C8E_11D6_BA10_00A0C93CDD6C__INCLUDED_)
#define AFX_LOGINDLG_H__9CF3A640_2C8E_11D6_BA10_00A0C93CDD6C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LoginDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLoginDlg dialog
//#include "RdsUser.h"
#include "Controls\\XPStyleButtonST.h"
#include "Controls\\ThemeHelperST.h"

#include "SQL\\sqldirect.h"

class CLoginDlg : public CDialog
{
// Construction
public:
	void DispLatestUser(void);
	BOOL m_bLogInOut;   //0:in 1:out
	void ConnectDB(void);
	CLoginDlg(CWnd* pParent = NULL);   // standard constructor

	CSQLDirect m_SQLDirect;
    
// Dialog Data
	//{{AFX_DATA(CLoginDlg)
	enum { IDD = IDD_DLG_LOGIN };
	CButton	m_CheckManachine;
	CEdit	m_ctrlEditPWD;
	CXPStyleButtonST m_btnOK;
	CXPStyleButtonST m_btnCANCEL;
	CButton	m_ctrlIDOK;
	CString	m_strPasswd;
	CString	m_strUser;
	CString	m_strEditStatus;
	//}}AFX_DATA
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLoginDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
    
// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CLoginDlg)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	CThemeHelperST	m_ThemeHelper;
	
//	CXPStyleButtonST m_btnCANCEL;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LOGINDLG_H__9CF3A640_2C8E_11D6_BA10_00A0C93CDD6C__INCLUDED_)
