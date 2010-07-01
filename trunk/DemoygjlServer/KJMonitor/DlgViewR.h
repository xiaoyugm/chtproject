//{{AFX_INCLUDES()
//#include "datagrid.h"
//}}AFX_INCLUDES
#if !defined(AFX_DLGVIEWR_H__40C48D97_310C_11D6_BA10_00A0C93CDD6C__INCLUDED_)
#define AFX_DLGVIEWR_H__40C48D97_310C_11D6_BA10_00A0C93CDD6C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgViewR.h : header file
//
/////////////////////////////////////////////////////////////////////////////
// CDlgViewR dialog
	
#include "SQL\\sqldirect.h"

#include "Controls\\XPStyleButtonST.h"
#include "Controls\\ThemeHelperST.h"



class CDlgViewR : public CDialog
{
// Construction
public:
	void GetDataFromDB(void);
	void ConnectDB();
	CDlgViewR(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgViewR)
	enum { IDD = IDD_VIEWRECORD };
	CXPStyleButtonST	m_btnOK;
	CXPStyleButtonST	m_ctrlBtnSortByUser;
	CXPStyleButtonST	m_ctrlBtnSortByAuth;
	CXPStyleButtonST	m_ctrlBtnDelete;
	CXTListCtrl	m_ctrlListTable;
	//}}AFX_DATA
	CXTColorPicker	m_cpText;
	CXTColorPicker	m_cpBack;
	COLORREF m_clrRowText;
	COLORREF m_clrRowBack;

	int               m_nSortedCol;
	BOOL              m_bAscending;
	CXTFlatHeaderCtrl m_flatHeader;

	CSQLDirect m_SQLDirect;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgViewR)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgViewR)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonSortbyuser();
	afx_msg void OnButtonSortbyauth();
	afx_msg void OnButtonDelete();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	CThemeHelperST	m_ThemeHelper;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGVIEWR_H__40C48D97_310C_11D6_BA10_00A0C93CDD6C__INCLUDED_)
