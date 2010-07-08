#if !defined(AFX_DATETIME_H__2D045DF2_2937_41D4_940D_02AFA1CD613A__INCLUDED_)
#define AFX_DATETIME_H__2D045DF2_2937_41D4_940D_02AFA1CD613A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Datetime.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDatetime dialog

class CDatetime : public CDialog
{
// Construction
public:
	CDatetime(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDatetime)
	enum { IDD = IDD_DLG_DATETIME };
	CTime	m_time;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDatetime)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDatetime)
	afx_msg void OnSelectMonthcalendar(NMHDR* pNMHDR, LRESULT* pResult);
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DATETIME_H__2D045DF2_2937_41D4_940D_02AFA1CD613A__INCLUDED_)
