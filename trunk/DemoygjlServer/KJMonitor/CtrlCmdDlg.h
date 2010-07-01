#if !defined(AFX_CTRLCMDDLG_H__A0DC32A4_EC07_41C2_B497_09004D4B958A__INCLUDED_)
#define AFX_CTRLCMDDLG_H__A0DC32A4_EC07_41C2_B497_09004D4B958A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CtrlCmdDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCtrlCmdDlg dialog

#include "FlatTab\\ColorListBox.h"
#include "Controls\\XPStyleButtonST.h"
#include "Controls\\ThemeHelperST.h"

#include "SQL\\sqldirect.h"



class CCtrlCmdDlg : public CDialog
{

public:


// Construction
public:
	void StartCmd(int m_usCtrlPointNumCount);
	void DispStatus();
	unsigned char m_ucSendCtrlFlag;
	unsigned short m_usCtrlPointNum;  //每次要控制的点数
	unsigned short m_usCtrlPointNumCount;  //已经发送命令的点数
	void SetDBListContent(void);
	CCtrlCmdDlg(CWnd* pParent = NULL);   // standard constructor


	CSQLDirect m_SQLDirect;
	//CString2DataType m_String2DataType;

	CXTColorPicker	m_cpText;
	CXTColorPicker	m_cpBack;
	COLORREF m_clrRowText;
	COLORREF m_clrRowBack;

	int               m_nSortedCol;
	BOOL              m_bAscending;
	CXTFlatHeaderCtrl m_flatHeader;


// Dialog Data
	//{{AFX_DATA(CCtrlCmdDlg)
	enum { IDD = IDD_DLG_CTRLCMD };
	CXPStyleButtonST	m_ctrlBtnViewPort;
	CXPStyleButtonST	m_ctrlBtnOff;
	CXPStyleButtonST	m_ctrlBtnOpen;
	CXPStyleButtonST	m_ctrlBtnReverse;
	CComboBox	m_ctrlComboTrunkNO;
	CXPStyleButtonST	m_ctrlBtnOK;
	CXTListCtrl	m_ctrlListSelectPoint;
	CXTListCtrl	m_ctrlListAllPoint;
	CXPStyleButtonST	m_ctrlBtnSelectALL;
	CXPStyleButtonST	m_ctrlBtnSelect;
	CXPStyleButtonST	m_ctrlBtnDeselectAll;
	CXPStyleButtonST	m_ctrlBtnDeselect;
	CColorListBox		m_ctrlListBoxCommInfo;
	UINT	m_unDelayTimerD;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCtrlCmdDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	//}}AFX_VIRTUAL

// Implementation
protected:
	void StopSendCtrlCmd(void);
	BOOL BuildCtrlPointQue(void);
	void SetCtrlListHead(void);
	void SetDBListHead(void);
	void ConnectDB();

	CImageList		m_imageList;

	

	// Generated message map functions
	//{{AFX_MSG(CCtrlCmdDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonSelect();
	afx_msg void OnButtonDeselect();
	afx_msg void OnButtonSelectall();
	afx_msg void OnButtonDeselectall();
	afx_msg void OnSelchangeComboTrunkno();
	afx_msg void OnDestroy();
	afx_msg void OnDblclkListAllpoint(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclkListSelectpoint(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnButtonReverse();
	afx_msg void OnButtonOpen();
	afx_msg void OnButtonOff();
//	afx_msg void OnButtonViewport();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	CThemeHelperST	m_ThemeHelper;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CTRLCMDDLG_H__A0DC32A4_EC07_41C2_B497_09004D4B958A__INCLUDED_)
