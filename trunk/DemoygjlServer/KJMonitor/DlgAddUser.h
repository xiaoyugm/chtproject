#if !defined(AFX_DLGADDUSER_H__14B0B2E6_3036_11D6_BA10_00A0C93CDD6C__INCLUDED_)
#define AFX_DLGADDUSER_H__14B0B2E6_3036_11D6_BA10_00A0C93CDD6C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgAddUser.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgAddUser dialog
//#include "RdsUser.h"

#include "Controls\\XPStyleButtonST.h"
#include "Controls\\ThemeHelperST.h"

#include "SQL\\sqldirect.h"
#include "SQL\\String2DataType.h"


class CDlgAddUser : public CDialog
{
// Construction
public:
	void ConnectDB(void);
	CDlgAddUser(CWnd* pParent = NULL);   // standard constructor

	CSQLDirect m_SQLDirect;
	CString2DataType m_String2DataType;


// Dialog Data
	//{{AFX_DATA(CDlgAddUser)
	enum { IDD = IDD_ADDUSER };
	CComboBox	m_ctrlComboAuthority;
	CXPStyleButtonST m_btnOK;
	CXPStyleButtonST m_btnCANCEL;
	CString	m_strCfmPWD;
	CString	m_strPWD;
	CString	m_strUser;
	CString	m_strDpt;
	CString	m_strAut;
	//}}AFX_DATA
//    CRdsUser rsUser;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgAddUser)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgAddUser)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()


private:
	CThemeHelperST	m_ThemeHelper;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGADDUSER_H__14B0B2E6_3036_11D6_BA10_00A0C93CDD6C__INCLUDED_)
