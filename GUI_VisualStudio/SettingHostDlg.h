#if !defined(AFX_SETTINGHOSTDLG_H__92D4ACA8_B152_425C_BBA4_A10384483A86__INCLUDED_)
#define AFX_SETTINGHOSTDLG_H__92D4ACA8_B152_425C_BBA4_A10384483A86__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SettingHostDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSettingHostDlg dialog

class CSettingHostDlg : public CDialog
{
// Construction
public:
	CSettingHostDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSettingHostDlg)
	enum { IDD = IDD_DIALOG_HOST_SETTING };
	CString	m_strHostIP;
	CString	m_strPort;
	CString	m_strTimeOut;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSettingHostDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSettingHostDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETTINGHOSTDLG_H__92D4ACA8_B152_425C_BBA4_A10384483A86__INCLUDED_)
