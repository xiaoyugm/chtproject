#if !defined(AFX_SETPERCENTFILLDLG_H__0B1C3F24_4D34_46AB_AEA8_7FB95F91D9DC__INCLUDED_)
#define AFX_SETPERCENTFILLDLG_H__0B1C3F24_4D34_46AB_AEA8_7FB95F91D9DC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetPercentFillDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSetPercentFillDlg dialog

class CSetPercentFillDlg : public CDialog
{
// Construction
public:
	CSetPercentFillDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSetPercentFillDlg)
	enum { IDD = IDD_DIALOG_SET_PERCENT_ACTION };
	CComboBox	m_ctlReferencePoint;
	CXTColorPicker	m_FillColor;
	UINT	m_nPointNo;
	UINT	m_pufdata;
	CString	m_strReferencePoint;
	//}}AFX_DATA
	BOOL	m_bIsH;
	COLORREF m_clrFillColor;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSetPercentFillDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSetPercentFillDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETPERCENTFILLDLG_H__0B1C3F24_4D34_46AB_AEA8_7FB95F91D9DC__INCLUDED_)
