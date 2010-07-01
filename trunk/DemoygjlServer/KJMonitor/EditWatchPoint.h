#if !defined(AFX_EDITWATCHPOINT_H__DAA5E6FA_793A_4953_82D2_D6481A133BA9__INCLUDED_)
#define AFX_EDITWATCHPOINT_H__DAA5E6FA_793A_4953_82D2_D6481A133BA9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EditWatchPoint.h : header file
//
#include "Controls\\XPStyleButtonST.h"
#include "Controls\\ThemeHelperST.h"
#include "SQL\\sqldirect.h"

/////////////////////////////////////////////////////////////////////////////
// CEditWatchPoint dialog

class CEditWatchPoint : public CDialog
{
// Construction
public:
	CEditWatchPoint(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CEditWatchPoint)
	enum { IDD = IDD_EDITPOINTWATCH };
	CXPStyleButtonST	m_ctrlBtnSeePoint;
	CXPStyleButtonST	m_ctrlBtnDeleteWatchNo;
	CXPStyleButtonST	m_ctrlBtnAddWatch;
	CXPStyleButtonST	m_ctrlBtnPoint;
	CComboBox	m_ctrlComboTrunk;
	CXTListCtrl	m_ctrlListPoint;
	CXTListCtrl	m_ctrlListWatch;
	UINT	m_unEditWatchNo;
	UINT	m_unEditPointNo;
	UINT	m_unEditSeePoint;
	//}}AFX_DATA

// Attributes
public:
	CXTColorPicker	m_cpText;
	CXTColorPicker	m_cpBack;
	COLORREF m_clrRowText;
	COLORREF m_clrRowBack;

	int               m_nSortedCol;
	BOOL              m_bAscending;
	CXTFlatHeaderCtrl m_flatHeader;

	CSQLDirect m_SQLDirect;
	BOOL m_bSearchPoint;

// Operations
public:
	void GetDataFromDBWatch(void);
	void SetBtnStyle(void);
//	unsigned char m_ucOldTrunkNo;
	void GetDataFromDBPoint(void);
	void ConnectDB(void);
	void SetWatchPointListHead(void);
	void SetPointListHead(void);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEditWatchPoint)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CEditWatchPoint)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeComboTrunk();
	afx_msg void OnButtonPoint();
	afx_msg void OnButtonAddwatch();
	afx_msg void OnButtonDeletewatchno();
	afx_msg void OnButtonSeepoint();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	CThemeHelperST	m_ThemeHelper;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EDITWATCHPOINT_H__DAA5E6FA_793A_4953_82D2_D6481A133BA9__INCLUDED_)
