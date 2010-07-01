#if !defined(AFX_DIALOGFEG_H__CF682D1D_5260_43FD_BF92_3E05447BA427__INCLUDED_)
#define AFX_DIALOGFEG_H__CF682D1D_5260_43FD_BF92_3E05447BA427__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000



// DialogFeg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDialogFeg dialog

class CDialogFeg : public CDialog
{
// Construction
public:
	CDialogFeg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDialogFeg)
	enum { IDD = IDD_DIALOGFEG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialogFeg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	BOOL OnInitDialog();

	// Generated message map functions
	//{{AFX_MSG(CDialogFeg)
	afx_msg void OnPgdn();
	afx_msg void OnPgup();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
    int  	TrigPage;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOGFEG_H__CF682D1D_5260_43FD_BF92_3E05447BA427__INCLUDED_)
