#if !defined(AFX_WARNSETDIALOG_H__95846814_BDDB_4825_B8E4_2B1AFDAC475F__INCLUDED_)
#define AFX_WARNSETDIALOG_H__95846814_BDDB_4825_B8E4_2B1AFDAC475F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// WarnSetDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CWarnSetDialog dialog

class CWarnSetDialog : public CDialog
{
// Construction
public:
	CWarnSetDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CWarnSetDialog)
	enum { IDD = IDD_DIALOG_WARN };
	CSpinButtonCtrl	m_ctlWarn;
	CSpinButtonCtrl	m_ctlTime;
	CSpinButtonCtrl	m_ctlText;
	CSpinButtonCtrl	m_ctlPoint;
	CSpinButtonCtrl	m_ctlDate;
	CSpinButtonCtrl	m_ctlCol;
	CXTColorPicker	m_titleColor;
	CXTColorPicker	m_textColor;
	CXTColorPicker	m_lineColor;
	CXTColorPicker	m_backColor;
	UINT	m_nCol;
	BOOL	m_bIsAutoSize;
	UINT	m_nPoint;
	UINT	m_nDate;
	UINT	m_nTime;
	UINT	m_nText;
	UINT	m_nWarn;
	//}}AFX_DATA
	COLORREF   m_clrBackColor,
			   m_clrLineColor,
			   m_clrTextColor,
			   m_clrTitleColor;
	BOOL	m_bInitComplete;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWarnSetDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CWarnSetDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnChangePercent();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WARNSETDIALOG_H__95846814_BDDB_4825_B8E4_2B1AFDAC475F__INCLUDED_)
