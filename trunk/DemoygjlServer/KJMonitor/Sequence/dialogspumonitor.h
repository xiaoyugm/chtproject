#if !defined(AFX_DIALOGSPUMONITOR_H__84D93D89_6824_498C_8FD1_8ABDBFEA78EE__INCLUDED_)
#define AFX_DIALOGSPUMONITOR_H__84D93D89_6824_498C_8FD1_8ABDBFEA78EE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// dialogspumonitor.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Cdialogspumonitor dialog

class Cdialogspumonitor : public CDialog
{
// Construction
public:
	Cdialogspumonitor(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(Cdialogspumonitor)
	enum { IDD = IDD_DIALOG3 };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Cdialogspumonitor)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
	private:
		int id_star,st_Seqnumber;
		char SeqText[32],S1Text[32];



protected:
	BOOL OnInitDialog();

	// Generated message map functions
	//{{AFX_MSG(Cdialogspumonitor)
	afx_msg void OnSaStart();
	afx_msg void OnSaAbort();
	afx_msg void OnOk1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOGSPUMONITOR_H__84D93D89_6824_498C_8FD1_8ABDBFEA78EE__INCLUDED_)
