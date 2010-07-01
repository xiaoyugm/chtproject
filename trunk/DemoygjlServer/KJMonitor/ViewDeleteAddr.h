#if !defined(AFX_VIEWDELETEADDR_H__96EE7F0D_7918_4557_B754_5EEFA7A3737E__INCLUDED_)
#define AFX_VIEWDELETEADDR_H__96EE7F0D_7918_4557_B754_5EEFA7A3737E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ViewDeleteAddr.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CViewDeleteAddr dialog
#include "Controls\\XPStyleButtonST.h"
#include "Controls\\ThemeHelperST.h"
#include "SQL\\sqldirect.h"

class CViewDeleteAddr : public CDialog
{
// Construction
public:
	void RebuildScanQue();

	BOOL m_bExcelInit;
	CString GetAppPath();
	void SetListReportTable();
	BOOL m_bSearchPoint;
	BOOL m_bUnusedAddr;
	void SetListCtrlTable(void);
	UINT m_unTrunkNo;
	CString GetConvName(UINT unConvID);  //1-13
	void GetDataFromDB(void);
	void ConnectDB(void);
	void SetButtonStyle(void);
	CViewDeleteAddr(CWnd* pParent = NULL);   // standard constructor

	CXTColorPicker	m_cpText;
	CXTColorPicker	m_cpBack;
	COLORREF m_clrRowText;
	COLORREF m_clrRowBack;

	int               m_nSortedCol;
	BOOL              m_bAscending;
	CXTFlatHeaderCtrl m_flatHeader;

	CSQLDirect m_SQLDirect;


	// Dialog Data
	//{{AFX_DATA(CViewDeleteAddr)
	enum { IDD = IDD_DLG_VIEWDELETEADDR };
	CXPStyleButtonST	m_ctrlBtnSequence;
	CXPStyleButtonST	m_ctrlBtnAlarm;
	CXPStyleButtonST	m_ctrlBtnDeselectAll;
	CXPStyleButtonST	m_ctrlBtnDeselect1;
	CXPStyleButtonST	m_ctrlBtnAddAll;
	CXPStyleButtonST	m_ctrlBtnAdd1;
	CXPStyleButtonST	m_ctrlBtnReport;
	CXPStyleButtonST	m_ctrlBtnAdd;
	CXTListCtrl	m_ctrlListReportTable;
	CComboBox	m_ctrlComboSelectTrunk;
	CXPStyleButtonST	m_ctrlBtnDeleteAddr;
	CXPStyleButtonST	m_ctrlBtnSearchPoint;
	CXPStyleButtonST	m_ctrlBtnDispUsedAddr;
	CXPStyleButtonST	m_ctrlBtnDeleteMultiConv;
	CXPStyleButtonST	m_ctrlBtnDispUnusedAddr;
	CXPStyleButtonST	m_btnOK;
	CXTListCtrl	m_ctrlList;
	UINT	m_unEditSearchPoint;
	UINT	m_unEditStartPoint;
	UINT	m_unEditEndPoint;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CViewDeleteAddr)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CViewDeleteAddr)
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void OnButtonDispusedaddr();
	afx_msg void OnButtonDispunusedaddr();
	afx_msg void OnButtonDeleteaddr();
	afx_msg void OnButtonDeletemulticonv();
	afx_msg void OnButtonSearchpoint();
	afx_msg void OnSelchangeComboSelecttrunk();
	afx_msg void OnButtonReport();
	afx_msg void OnButtonAdd();
	afx_msg void OnDblclkListAddr(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclkListReporttable(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnButtonAdd1();
	afx_msg void OnButtonAddall();
	afx_msg void OnButtonDeselect1();
	afx_msg void OnButtonDeselectall();
	afx_msg void OnButtonAlarm();
	afx_msg void OnButtonSequence();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	CThemeHelperST	m_ThemeHelper;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VIEWDELETEADDR_H__96EE7F0D_7918_4557_B754_5EEFA7A3737E__INCLUDED_)
