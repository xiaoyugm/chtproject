#if !defined(AFX_EDIT12MODEDLG_H__D4614BE2_0F88_4C9D_B101_4B5B27749DCF__INCLUDED_)
#define AFX_EDIT12MODEDLG_H__D4614BE2_0F88_4C9D_B101_4B5B27749DCF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Edit12ModeDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CEdit12ModeDlg dialog
#include "Controls\\XPStyleButtonST.h"
#include "Controls\\ThemeHelperST.h"

#include "SQL\\sqldirect.h"
#include "SQL\\String2DataType.h"

class CEdit12ModeDlg : public CDialog
{
// Construction
public:
	void SetListTable();
	void SetListTableColumnName();
	CEdit12ModeDlg(CWnd* pParent = NULL);   // standard constructor

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
	//{{AFX_DATA(CEdit12ModeDlg)
	enum { IDD = IDD_DLG_EDIT12MODE };
	CXPStyleButtonST	m_ctrlBtnSavesetting;
	CXPStyleButtonST	m_ctrlBtnOK;
	CXTListCtrl	m_ctrlList;
	CXPStyleButtonST	m_ctrlBtnEdit;
	CString	m_strEditMode1;
	CString	m_strEditMode2;
	UINT	m_unEditNo;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEdit12ModeDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void ConnectDB(void);

	// Generated message map functions
	//{{AFX_MSG(CEdit12ModeDlg)
	afx_msg void OnButtonEdit();
	afx_msg void OnButtonSavesetting();
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	CThemeHelperST	m_ThemeHelper;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EDIT12MODEDLG_H__D4614BE2_0F88_4C9D_B101_4B5B27749DCF__INCLUDED_)
