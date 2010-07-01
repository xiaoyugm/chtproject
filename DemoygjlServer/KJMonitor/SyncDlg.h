#if !defined(AFX_SYNCDLG_H__B1E3C68C_B063_4AD7_9F27_23D9BD87FA76__INCLUDED_)
#define AFX_SYNCDLG_H__B1E3C68C_B063_4AD7_9F27_23D9BD87FA76__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SyncDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSyncDlg dialog

class CSyncDlg : public CDialog
{
// Construction
public:
	CSyncDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSyncDlg)
	enum { IDD = IDD_DIALOG_SYNC };
	CString	m_strAnolog;
	CString	m_strData;
	CString	m_strPoint;
	CString	m_strRecord;
	CString	m_strSwitch;
	COleDateTime	m_DataStart;
	COleDateTime	m_DataEnd;
	COleDateTime	m_RecordStart;
	COleDateTime	m_RecordEnd;
	long	m_lAnologEnd;
	long	m_lAnologStart;
	long	m_lPointEnd;
	long	m_lPointStart;
	long	m_lSwitchEnd;
	long	m_lSwitchStart;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSyncDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void SyncData();
	void SyncRecord();
	void SyncSwitch();
	void SyncAnolog();
	void SyncPoint();


	// Generated message map functions
	//{{AFX_MSG(CSyncDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSync();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SYNCDLG_H__B1E3C68C_B063_4AD7_9F27_23D9BD87FA76__INCLUDED_)
