#if !defined(AFX_CARSETDLG_H__B675EE75_68E9_45FC_95BA_EA39E1074C55__INCLUDED_)
#define AFX_CARSETDLG_H__B675EE75_68E9_45FC_95BA_EA39E1074C55__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CarSetDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCarSetDlg dialog

class CCarSetDlg : public CDialog
{
// Construction
public:
	CCarSetDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCarSetDlg)
	enum { IDD = IDD_DIALOG_CAR };
	CXTColorPicker	m_ctlFillColor;
	CXTColorPicker	m_ctlLineColor;
	CButton	m_ctlPath;
	UINT	m_nPointNo;
	UINT	m_nSpeed;
	CString	m_strPath;
	//}}AFX_DATA
	COLORREF  m_clrLineColor;
	COLORREF  m_clrFillColor;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCarSetDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCarSetDlg)
	afx_msg void OnPicPath();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CARSETDLG_H__B675EE75_68E9_45FC_95BA_EA39E1074C55__INCLUDED_)
