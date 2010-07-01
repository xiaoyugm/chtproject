#if !defined(AFX_DIALOGR_H__7131AA63_F0CD_4316_ADF5_753D7AFF9773__INCLUDED_)
#define AFX_DIALOGR_H__7131AA63_F0CD_4316_ADF5_753D7AFF9773__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// dialogR.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CdialogR dialog
#define unTimerId_R 3

class CdialogR : public CDialog
{
// Construction
public:
	CdialogR(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CdialogR)
	enum { IDD = IDD_DIALOG2 };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CdialogR)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);  
	afx_msg void OnTimer(UINT nIDEvent);// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	BOOL OnInitDialog();

	// Generated message map functions
	//{{AFX_MSG(CdialogR)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOGR_H__7131AA63_F0CD_4316_ADF5_753D7AFF9773__INCLUDED_)
