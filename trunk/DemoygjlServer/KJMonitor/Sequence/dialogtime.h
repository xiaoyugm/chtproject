#if !defined(AFX_DIALOGTIME_H__EA94AC21_A6F1_4959_A5A5_85CFFD24BECD__INCLUDED_)
#define AFX_DIALOGTIME_H__EA94AC21_A6F1_4959_A5A5_85CFFD24BECD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// dialogtime.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Cdialogtime dialog

class Cdialogtime : public CDialog
{
// Construction
public:
	Cdialogtime(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(Cdialogtime)
	enum { IDD = IDD_DIALOGDTIME };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Cdialogtime)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	private:
		int	TimePage;
// Implementation
protected:
	BOOL OnInitDialog();

	// Generated message map functions
	//{{AFX_MSG(Cdialogtime)
	virtual void OnOK();
	afx_msg void OnButtonshangye();
	afx_msg void OnButtonxiayiye();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOGTIME_H__EA94AC21_A6F1_4959_A5A5_85CFFD24BECD__INCLUDED_)
