#if !defined(AFX_SETTIMEDLG_H__F23E9803_41D7_40C1_B427_4AAA2CDD9ED2__INCLUDED_)
#define AFX_SETTIMEDLG_H__F23E9803_41D7_40C1_B427_4AAA2CDD9ED2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetTimeDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSetTimeDlg dialog

class CSetTimeDlg : public CDialog
{
// Construction
public:
	CSetTimeDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSetTimeDlg)
	enum { IDD = IDD_DIALOG_SET_TIMER };
	UINT	m_nSecond;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSetTimeDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSetTimeDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETTIMEDLG_H__F23E9803_41D7_40C1_B427_4AAA2CDD9ED2__INCLUDED_)
