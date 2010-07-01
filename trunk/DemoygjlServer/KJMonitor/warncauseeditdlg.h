#if !defined(AFX_WARNCAUSEEDITDLG_H__848013D6_4BEE_446A_9BD6_DA9E1EF1279C__INCLUDED_)
#define AFX_WARNCAUSEEDITDLG_H__848013D6_4BEE_446A_9BD6_DA9E1EF1279C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// WarnCauseEditDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CWarnCauseEditDlg dialog  
#include "Others\\soundbase.h"
#include "Controls\\XPStyleButtonST.h"
#include "Controls\\ThemeHelperST.h"
#include "Controls\\PictureEx.h"
#include "SQL\\sqldirect.h"


class CWarnCauseEditDlg : public CDialog
{
// Construction
public:
	CString GetAppPath();
	BOOL m_bPlaySound;
	CWarnCauseEditDlg(CWnd* pParent = NULL);   // standard constructor

	void SetListTable();
	void SetListTableColumnName();


public:
	BOOL m_bGifLoad;

	CSQLDirect m_SQLDirect;

	CXTColorPicker	m_cpText;
	CXTColorPicker	m_cpBack;
	COLORREF m_clrRowText;
	COLORREF m_clrRowBack;

	int               m_nSortedCol;
	BOOL              m_bAscending;
	CXTFlatHeaderCtrl m_flatHeader;


// Dialog Data
	//{{AFX_DATA(CWarnCauseEditDlg)
	enum { IDD = IDD_DLG_WARNCAUSEEDIT };
	CPictureEx	m_GifPic;
	CXPStyleButtonST	m_ctrlBtnAddEditAndGoOn;
	CXTListCtrl	m_ctrlList;
	CXPStyleButtonST	m_ctrlBtnTest;
	CXPStyleButtonST m_btnCANCEL;
	CString	m_strWarnCause;
	UINT	m_unEditWarnclassNO;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWarnCauseEditDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void ConnectDB(void);

	// Generated message map functions
	//{{AFX_MSG(CWarnCauseEditDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonTest();
	afx_msg void OnDestroy();
	afx_msg void OnButtonAddeditandgoon();
	afx_msg void OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	CThemeHelperST	m_ThemeHelper;



};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WARNCAUSEEDITDLG_H__848013D6_4BEE_446A_9BD6_DA9E1EF1279C__INCLUDED_)
