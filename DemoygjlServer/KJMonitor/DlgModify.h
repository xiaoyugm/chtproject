#if !defined(AFX_DLGMODIFY_H__8965BACA_2CFA_11D6_BA10_00A0C93CDD6C__INCLUDED_)
#define AFX_DLGMODIFY_H__8965BACA_2CFA_11D6_BA10_00A0C93CDD6C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgModify.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgModify dialog
//#include "RdsUser.h"
#include "Controls\\XPStyleButtonST.h"
#include "Controls\\ThemeHelperST.h"

#include "SQL\\sqldirect.h"

class CDlgModify : public CDialog
{
// Construction
public:
	void ConnectDB(void);
	CDlgModify(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgModify)
	enum { IDD = IDD_MODIFYPWD };
	CXPStyleButtonST m_btnOK;
	CXPStyleButtonST m_btnCANCEL;
	CString	m_strCfmpwd;
	CString	m_strNewPWD;
	//}}AFX_DATA
    //CDatabase m_dbUser;
    CSQLDirect m_SQLDirect;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgModify)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgModify)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	CThemeHelperST	m_ThemeHelper;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGMODIFY_H__8965BACA_2CFA_11D6_BA10_00A0C93CDD6C__INCLUDED_)
