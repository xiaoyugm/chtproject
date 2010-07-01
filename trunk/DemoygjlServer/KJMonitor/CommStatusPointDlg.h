#if !defined(AFX_COMMSTATUSPOINTDLG_H__B746F896_7A29_45DB_A4B2_BD5E2552AB7F__INCLUDED_)
#define AFX_COMMSTATUSPOINTDLG_H__B746F896_7A29_45DB_A4B2_BD5E2552AB7F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CommStatusPointDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCommStatusPointDlg dialog

#include "CommStatusFM.h"

class CCommStatusPointDlg : public CDialog
{
// Construction
public:
	CCommStatusFM* m_pCommStatusFM;
	CCommStatusPointDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCommStatusPointDlg)
	enum { IDD = IDD_DLG_COMMSTATUSPOINT };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCommStatusPointDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCommStatusPointDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnButton1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COMMSTATUSPOINTDLG_H__B746F896_7A29_45DB_A4B2_BD5E2552AB7F__INCLUDED_)
