#if !defined(AFX_REPORT_H__97493D51_DA4D_4729_A386_9EA31CEA2A9A__INCLUDED_)
#define AFX_REPORT_H__97493D51_DA4D_4729_A386_9EA31CEA2A9A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Report.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CReport dialog
#include "XPStyleButtonST.h"
#include "ThemeHelperST.h"
#include "sqldirect.h"

class CReport : public CDialog
{
// Construction
public:
	void GetDateR(int &year,int &month,int &day,int &hour,int &minute,int &second,CString time);
	void GetDateR(int &year,int &month,int &day,CString time);
	void GetCollumHead();
	void SetListNowCollum();
	void SetListCollum();
	UINT m_unTrunkNo;
	BOOL m_bExcelInit;
	void SetListReportTable();
	void SetListCtrlTable();
	CString GetConvName(UINT unConvID);
	CString GetAppPath();
	void SetButtonStyle();
	void GetDataFromDB();
	void ConnectDB();
	CReport(CWnd* pParent = NULL);   // standard constructor

	CXTColorPicker	m_cpText;
	CXTColorPicker	m_cpBack;
	COLORREF m_clrRowText;
	COLORREF m_clrRowBack;

	CString m_strStartTime;
	CString m_strEndTime;
	UINT	m_ctrlStartSecond;
	UINT	m_ctrlEndSecond;

	int               m_nSortedCol;
	BOOL              m_bAscending;
	CXTFlatHeaderCtrl m_flatHeader;

	CSQLDirect m_SQLDirect;

// Dialog Data
	//{{AFX_DATA(CReport)
	enum { IDD = IDD_DLG_REPORT_EDIT };
	CXPStyleButtonST	m_ctrlBtnADDEDIT;
	CXPStyleButtonST	m_ctrlBtnDELCOLLUM;
	CXPStyleButtonST	m_ctrlBtnADDCOLLUM;
	CXTListCtrl	m_ctrlNowCollum;
	CXTListCtrl	m_ctrlCollum;
	CXPStyleButtonST	m_ctrlBtnReport;
	CXPStyleButtonST	m_ctrlBtnDeselectAll;
	CXPStyleButtonST	m_ctrlBtnDeselect1;
	CXPStyleButtonST	m_ctrlBtnAddAll;
	CXPStyleButtonST	m_ctrlBtnAdd1;
	CComboBox	m_ctrlComboSelectTrunk;
	CXTListCtrl	m_ctrlListReportTable;
	CXTListCtrl	m_ctrlList;
	CString	m_ctrlDefine;
	UINT	m_ctrlStartH;
	UINT	m_ctrlEndH;
	UINT	m_ctrlEndMin;
	UINT	m_ctrlStartMin;
	CDateTimeCtrl	m_ctrlStartTime;
	CDateTimeCtrl	m_ctrlEndTime;
	CTime m_endDateTime;
	CTime m_startDateTime;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CReport)
	public:
	virtual BOOL DestroyWindow();
	virtual void Serialize(CArchive& ar);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CReport)
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void OnButtonDeselectall();
	afx_msg void OnButtonDeselect1();
	afx_msg void OnButtonAddall();
	afx_msg void OnButtonAdd1();
	afx_msg void OnDblclkListAddr(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclkListReporttable(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelchangeComboSelecttrunk();
	afx_msg void OnButtonReport();
	afx_msg void OnDblclkListCollum(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclkListNowcollum(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnButAddedit();
	afx_msg void OnButAddCollum();
	afx_msg void OnButDelCollun();
	afx_msg void OnCloseupDatetimepickerstart(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCloseupDatetimepickerend(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnChangeEditStarth();
	afx_msg void OnChangeEditEndh();
	afx_msg void OnChangeEditStartmin();
	afx_msg void OnChangeEditEndmin();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	CThemeHelperST	m_ThemeHelper;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REPORT_H__97493D51_DA4D_4729_A386_9EA31CEA2A9A__INCLUDED_)
