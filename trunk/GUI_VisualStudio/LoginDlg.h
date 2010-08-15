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
//#include "Controls\\XPStyleButtonST.h"
//#include "Controls\\ThemeHelperST.h"

//#include "SQL\\sqldirect.h"
#include "dbAx\AxLogin.hpp"
#include "dbAx\AccountSetEvents.hpp"

class CLoginDlg : public CXTResizeDialog
{
// Construction
public:
	int nrecord;
	BOOL m_bAddUser;   //0:del 1:add
	void ConnectDB(void);
	CLoginDlg(CWnd* pParent = NULL);   // standard constructor

    CCardFileEvents *pCnEvents;
    CAxConnection   m_Cn;
    CAxPointDescription  m_PointDes;
    CAxLogin        m_SLogin;
    CAxLogin        *m_SLoginNew;

	CSQLDirect m_SQLDirect;
 	CString2DataType    m_Str2Data;
   
// Dialog Data
	//{{AFX_DATA(CLoginDlg)
	enum { IDD = IDD_DLG_LOGIN };
	CButton	m_CheckManachine;
	CEdit	m_ctrlEditPWD;
	CButton m_btnOK;
	CXTFlatComboBox     m_ComBoxSM;
//	CXPStyleButtonST m_btnOK;
//	CButton m_btnCANCEL;
	CXTListCtrl         m_listUser;
	CButton	m_ctrlIDOK;
	CString	m_strPasswd;
	CString	m_strUser;
	CString	m_strdism;
//	CString	m_strEditStatus;
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
	afx_msg void OnchangeComboSM();
    afx_msg void OnItemChangedList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void DelUser();
	afx_msg void AddODUser();
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
//	CThemeHelperST	m_ThemeHelper;
	
//	CXPStyleButtonST m_btnCANCEL;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LOGINDLG_H__9CF3A640_2C8E_11D6_BA10_00A0C93CDD6C__INCLUDED_)
