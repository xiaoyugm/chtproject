#if !defined(AFX_BACKUPSETTINGDLG_H__36799B18_99ED_4356_8B2A_E27F05872C2D__INCLUDED_)
#define AFX_BACKUPSETTINGDLG_H__36799B18_99ED_4356_8B2A_E27F05872C2D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BackupSettingDlg.h : header file
//
#include "Others\\iniFile.h"
/////////////////////////////////////////////////////////////////////////////
// CBackupSettingDlg dialog

class CBackupSettingDlg : public CDialog
{
// Construction
public:
	CBackupSettingDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CBackupSettingDlg)
	enum { IDD = IDD_DIALOG_BACKUP };
	CString	m_BackupCOM1;
	CString	m_BackupCOM2;
	CString	m_BackupCOM3;
	CString	m_BackupCOM4;
	CString	m_BackupCOM5;
	CString	m_BackupCOM6;
	CString	m_BackupCOM7;
	CString	m_BackupCOM8;
	CString	m_BackupIP;
	CString	m_BackupPort;
	CString	m_BackupTimeout;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBackupSettingDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CIniFile m_ini;
	// Generated message map functions
	//{{AFX_MSG(CBackupSettingDlg)
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BACKUPSETTINGDLG_H__36799B18_99ED_4356_8B2A_E27F05872C2D__INCLUDED_)
