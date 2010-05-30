#if !defined(AFX_SETTINGHOSTDLG_H__92D4ACA8_B152_425C_BBA4_A10384483A86__INCLUDED_)
#define AFX_SETTINGHOSTDLG_H__92D4ACA8_B152_425C_BBA4_A10384483A86__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SettingHostDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSettingHostDlg dialog

class CSettingHostDlg : public CXTResizeDialog
{
// Construction
public:
	CSettingHostDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSettingHostDlg)
	enum { IDD = IDD_DIALOG_HOST_SETTING };
//	CString	m_strHostIP;
//	CString	m_strPort;
//	CString	m_strTimeOut;
	CXTListCtrl         m_listCtrl;
	BOOL                m_bSortColor;
	BOOL    m_bListColor;
	BOOL    m_bRowColor;
	//}}AFX_DATA
//	COLORREF            m_crSortText;
//	COLORREF            m_crSortBack;
//	COLORREF            m_crListText;
//	COLORREF            m_crListBack;
//	COLORREF            m_crRowText;
//	COLORREF            m_crRowBack;
//	CXTColorPicker      m_cpSortText;
	CXTColorPicker      m_cpSortBack;
//	CXTColorPicker      m_cpListText;
//	CXTColorPicker      m_cpListBack;
//	CXTColorPicker      m_cpRowText;
//	CXTColorPicker      m_cpRowBack;

	HICON           m_hIcon;
	int             m_nSortedCol;
	bool            m_bAscending;
	CXTHeaderCtrl   m_header;

	void SortColumn(int iCol, bool bAsc);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSettingHostDlg)
	protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSettingHostDlg)
	afx_msg void OnBtnADD();
	afx_msg void OnBtnDEL();
	afx_msg void OnBtnMOD();
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETTINGHOSTDLG_H__92D4ACA8_B152_425C_BBA4_A10384483A86__INCLUDED_)
