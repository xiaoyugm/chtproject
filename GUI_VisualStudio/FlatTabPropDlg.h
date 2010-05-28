#if !defined(AFX_FLATTABPROPDLG_H__704EA15D_CD56_4018_B28F_E63CFFC02737__INCLUDED_)
#define AFX_FLATTABPROPDLG_H__704EA15D_CD56_4018_B28F_E63CFFC02737__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FlatTabPropDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFlatTabPropDlg dialog

class CSampleFormView;
class CFlatTabViewView;
class CFlatTabPropDlg : public CDialog
{
// Construction
public:
	CFlatTabPropDlg(CXTFlatTabCtrl* pFlatTabCtrl, CFlatTabViewView* pParent);   // standard constructor
	virtual ~CFlatTabPropDlg();

// Dialog Data
	//{{AFX_DATA(CFlatTabPropDlg)
	enum { IDD = IDD_FLATTAB_PROP };
	BOOL&	m_FTS_XT_BOTTOM;
	BOOL&	m_FTS_XT_HASARROWS;
	BOOL&	m_FTS_XT_HASHOMEEND;
	BOOL&	m_FTS_XT_HSCROLL;
	UINT	m_iTabNum;
	CString	m_sText;
	//}}AFX_DATA

	CFlatTabViewView*	 m_pParentWnd;
	CXTFlatTabCtrl*		 m_pFlatTabCtrl;
    int&				 m_dwTabStyle;
    CSampleFormView*		m_pSheet7;

    void UpdateDlgStatus();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFlatTabPropDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CFlatTabPropDlg)
	afx_msg void UpdateTabsStyle();
	afx_msg void OnManipulate();
	afx_msg void OnAddTab();
	afx_msg void OnDeleteAll();
	afx_msg void OnDeleteTab();
	afx_msg void OnModifyTab();
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FLATTABPROPDLG_H__704EA15D_CD56_4018_B28F_E63CFFC02737__INCLUDED_)
