#if !defined(AFX_ANOLOGOUTDLG_H__F873AD8F_26DF_4505_9DB1_B14A075A17FC__INCLUDED_)
#define AFX_ANOLOGOUTDLG_H__F873AD8F_26DF_4505_9DB1_B14A075A17FC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AnologOutDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAnologOutDlg dialog
#include "FlatTab\\ColorListBox.h"
#include "Controls\\XPStyleButtonST.h"
#include "Controls\\ThemeHelperST.h"

#include "SQL\\sqldirect.h"

class CAnologOutDlg : public CDialog
{
// Construction
public:
	CAnologOutDlg(CWnd* pParent = NULL);   // standard constructor

	unsigned char m_ucCurrentValue;  
	unsigned short m_usCtrlPointNum;  //每次要控制的点数
	unsigned short m_usCtrlPointNumCount;  //已经发送命令的点数

// Dialog Data
	//{{AFX_DATA(CAnologOutDlg)
	enum { IDD = IDD_DLG_ANOLOGOUTPUT };
	CXPStyleButtonST	m_ctrlBtnOut;
	CXPStyleButtonST	m_ctrlBtnDelone;
	CXPStyleButtonST	m_ctrlBtnAddone;
	CColorListBox	m_ctrlListBoxCommInfo;
	CComboBox	m_ctrlComboTrunkNO;
	CXPStyleButtonST	m_ctrlBtnOK;
	CXTListCtrl	m_ctrlListSelectPoint;
	CXTListCtrl	m_ctrlListAllPoint;
	CXPStyleButtonST	m_ctrlBtnDeselectAll;
	CXPStyleButtonST	m_ctrlBtnDeSelect;
	CXPStyleButtonST	m_ctrlBtnSelectAll;
	CXPStyleButtonST	m_ctrlBtnSelect;
	UINT	m_unDelayTimerA;
	//}}AFX_DATA
     CSQLDirect m_SQLDirect;
	//CString2DataType m_String2DataType;

	CXTColorPicker	m_cpText;
	CXTColorPicker	m_cpBack;
	COLORREF m_clrRowText;
	COLORREF m_clrRowBack;
	int               m_nSortedCol;
	BOOL              m_bAscending;
	CXTFlatHeaderCtrl m_flatHeader;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAnologOutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	//}}AFX_VIRTUAL

// Implementation
protected:
     void ConnectDB();
	 void SetDBListHead();
	 void SetCtrlListHead();
	 void SetDBListContent();
	 void DispStatus();
	 void StopSendCtrlCmd(void);
	 void StartCmd(int m_usCtrlPointNumCount);
	BOOL BuildCtrlPointQue(void);
	// Generated message map functions
	//{{AFX_MSG(CAnologOutDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void OnSelchangeComboTrunkno();
	afx_msg void OnButtonSelect();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnButtonSelectall();
	afx_msg void OnButtonDeselect();
	afx_msg void OnButtonDeselectall();
	afx_msg void OnButtonOut();
	afx_msg void OnButtonAddone();
	afx_msg void OnButtonDelone();
	afx_msg void OnDblclkListAllpoint(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclkListSelectpoint(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	CThemeHelperST  m_ThemeHelper;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ANOLOGOUTDLG_H__F873AD8F_26DF_4505_9DB1_B14A075A17FC__INCLUDED_)
