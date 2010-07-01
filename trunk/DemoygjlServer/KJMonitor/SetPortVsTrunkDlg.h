#if !defined(AFX_SETPORTVSTRUNKDLG_H__A6DB650C_B9D1_408E_89D6_1CC37E0464E7__INCLUDED_)
#define AFX_SETPORTVSTRUNKDLG_H__A6DB650C_B9D1_408E_89D6_1CC37E0464E7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetPortVsTrunkDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSetPortVsTrunkDlg dialog

#include "Controls\\XPStyleButtonST.h"
#include "Controls\\ThemeHelperST.h"

#include "SQL\\sqldirect.h"
#include "SQL\\String2DataType.h"

class CSetPortVsTrunkDlg : public CDialog
{
// Construction
public:

	void SetListTableColumnName(void);
	void SetListTable(void);
	CSetPortVsTrunkDlg(CWnd* pParent = NULL);   // standard constructor
	CSQLDirect m_SQLDirect;
	CString2DataType m_String2DataType;

	CXTColorPicker	m_cpText;
	CXTColorPicker	m_cpBack;
	COLORREF m_clrRowText;
	COLORREF m_clrRowBack;

	int               m_nSortedCol;
	BOOL              m_bAscending;
	CXTFlatHeaderCtrl m_flatHeader;

// Dialog Data
	//{{AFX_DATA(CSetPortVsTrunkDlg)
	enum { IDD = IDD_DLG_PORTVSTRUNKCOMFIRM };
	CXPStyleButtonST  m_ctrlBtnTestPort;
	CXPStyleButtonST  m_ctrlBtnEdit;
	CXPStyleButtonST  m_btnOK;
	CXPStyleButtonST  m_ctrlBtnSaveSetting;
	CXTListCtrl	m_ctrlList;
	CString	m_strEditStatus;
	UINT	m_unEditTrunkNo;
	UINT	m_unEditPortNo;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSetPortVsTrunkDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void ConnectDB(void);

	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CSetPortVsTrunkDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void OnButtonSavesetting();
	afx_msg void OnButtonEdit();
	afx_msg void OnButtonTestport();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	CThemeHelperST	m_ThemeHelper;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETPORTVSTRUNKDLG_H__A6DB650C_B9D1_408E_89D6_1CC37E0464E7__INCLUDED_)
