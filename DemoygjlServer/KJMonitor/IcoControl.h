#if !defined(AFX_ICOCONTROL_H__FCC3AE30_60CD_4D2D_88B6_872AC42D0965__INCLUDED_)
#define AFX_ICOCONTROL_H__FCC3AE30_60CD_4D2D_88B6_872AC42D0965__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// IcoControl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CIcoControl dialog
#include "FlatTab\\ColorListBox.h"
#include "Controls\\XPStyleButtonST.h"
#include "Controls\\ThemeHelperST.h"

#include "SQL\\sqldirect.h"


class CIcoControl : public CDialog
{
// Construction
public:
	void StopSendCtrlCmd();
	CIcoControl(CWnd* pParent = NULL);   // standard constructor

	unsigned char m_ucCurrentState;  
	unsigned short m_usCtrlPointNum;  //每次要控制的点数
	unsigned short m_usCtrlPointNumCount;  //已经发送命令的点数
	void SetDBListContent(void);
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
	//{{AFX_DATA(CIcoControl)
	enum { IDD = IDD_DLG_ICO };
	CXPStyleButtonST	m_ctrlBtnHighWarn;
	CXPStyleButtonST	m_ctrlBtnHigh2Warn;
	CXPStyleButtonST	m_ctrlBtnDehighWarn;
	CXPStyleButtonST	m_ctrlBtnDehigh2Warn;
	CXPStyleButtonST	m_ctrlBtnOK;
	CXPStyleButtonST	m_ctrlBtnViewPort;
	CXTListCtrl	m_ctrlListSelectPoint;
	CColorListBox	m_ctrlListBoxCommInfo;
	CXTListCtrl	m_ctrlListAllPoint;
	CComboBox	m_ctrlComboTrunkNO;
	CXPStyleButtonST	m_ctrlBtnSelectAll;
	CXPStyleButtonST	m_ctrlBtnSelect;
	CXPStyleButtonST	m_ctrlBtnDeselectAll;
	CXPStyleButtonST	m_ctrlBtnDeselect;
	UINT	m_unDelayTimerICO;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIcoControl)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	//}}AFX_VIRTUAL

// Implementation
protected:
	void StartCmd(int m_usCtrlPointNumCount);
	void DispStatus();
	BOOL BuildCtrlPointQue(void);
	void SetCtrlListHead(void);
	void SetDBListHead(void);
	void ConnectDB();

	// Generated message map functions
	//{{AFX_MSG(CIcoControl)
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void OnButtonDehigh2warn();
	afx_msg void OnButtonDehignwarn();
	afx_msg void OnButtonDeselect();
	afx_msg void OnButtonDeselectall();
	afx_msg void OnButtonHign2warn();
	afx_msg void OnButtonHignwarn();
	afx_msg void OnButtonSelect();
	afx_msg void OnButtonSelectall();
	afx_msg void OnSelchangeComboTrunkno();
	afx_msg void OnDblclkListAllpoint(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclkListSelectpoint(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
		CThemeHelperST	m_ThemeHelper;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ICOCONTROL_H__FCC3AE30_60CD_4D2D_88B6_872AC42D0965__INCLUDED_)
