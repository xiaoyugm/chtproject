#if !defined(AFX_POINTEDITSWITCHIN_H__F6CD08C1_979D_4079_8590_F2392FD39CE2__INCLUDED_)
#define AFX_POINTEDITSWITCHIN_H__F6CD08C1_979D_4079_8590_F2392FD39CE2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PointEditSwitchIn.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPointEditSwitchIn dialog
#include "Controls\\XPStyleButtonST.h"
#include "Controls\\ThemeHelperST.h"

#include "SQL\\sqldirect.h"
#include "SQL\\String2DataType.h"


class CPointEditSwitchIn : public CDialog
{
// Construction
public:
	int GetChanelCount();
	void RebuildScanQue(void);
	void SetUpdateInfo(void);
	BOOL m_bGetChangePointInfo;
	void GetChnagePointInfo(void);
	void DispConvChannel(void);
	BOOL DisplayConvInfoInAddr(void);
	BOOL IsWarnMinMaxRight(void);
	BOOL FindPointInfo();
	BOOL FindAddrConvChanInfo(void);
	void ConnectDB();
	CPointEditSwitchIn(CWnd* pParent = NULL);   // standard constructor

protected:
	BOOL m_bPointEditChange;


	CSQLDirect m_SQLDirect;
	CString2DataType m_String2DataType;
	BOOL m_bSave,m_bSaveSuccess;
	UINT m_unConvID;
	int m_KeepDays, m_KeepHour,m_KeepMin; //保持时间：天/时/分

	CXTColorPicker	m_cpText;
	CXTColorPicker	m_cpBack;
	COLORREF m_clrRowText;
	COLORREF m_clrRowBack;

	int               m_nSortedCol;
	BOOL              m_bAscending;
	CXTFlatHeaderCtrl m_flatHeader;
// Dialog Data
	//{{AFX_DATA(CPointEditSwitchIn)
	enum { IDD = IDD_DLG_POINTEDIT_SWITCH_IN1 };
	CEdit	m_ctrlEditKeepTime;
	CComboBox	m_ctrlComboRecord;
	CXPStyleButtonST	m_ctrlBtnEdit12Mode;
	CComboBox	m_ctrlCombo21Mode;
	CComboBox	m_ctrlComboAPC;
	CEdit	m_ctrlEditChannel;
	CEdit	m_ctrlEditAddress;
	CButton	m_ctrlCheckChange;
	CXPStyleButtonST	m_ctrlBtnDelete;
	CXTListCtrl	m_ctrlList;
//	CComboBox	m_ctrlComboProcessType;
	CComboBox	m_ctrlComboScanFrequency;
	CComboBox	m_ctrlComboTrunkNo;
	CComboBox	m_ctrlComboWarnClass;
	CXPStyleButtonST	m_ctrlBtnBiewDeleteAddress;
	CButton	m_ctrlCheckMultiConv;
	CXPStyleButtonST	m_ctrlBtnViewPoint;
	CXPStyleButtonST	m_ctrlBtnViewAddr;
	CComboBox	m_ctrlComboBScan;
	CComboBox	m_ctrlComboSensorName;
	CXPStyleButtonST m_btnPOINTNOBACKWORD;
	CXPStyleButtonST m_btnPOINTNOFORWORD;
	CXPStyleButtonST m_btnOK;
	CXPStyleButtonST m_btnCANCEL;
	CXPStyleButtonST m_btnADDEDITANDGOON;
	UINT	m_unEditPoint;              //点号
	CEdit	m_ctrlEditPoint;          
	UINT	m_unEditAddress;
	UINT	m_unEditWarnDelay;
	CString	m_strEditOtherExplain;
	CString	m_strEditPointLabel;
	UINT	m_unEditChannel;
	CString	m_strEditKeepTime;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPointEditSwitchIn)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void SetListHead(void);

	// Generated message map functions
	//{{AFX_MSG(CPointEditSwitchIn)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonPointnobackword();
	afx_msg void OnButtonPointnoforword();
	afx_msg void OnSelchangeComboSensortype();
	afx_msg void OnSelchangeComboSensorname();
	afx_msg void OnDestroy();
	afx_msg void OnButtonAddeditandgoon();
	virtual void OnOK();
	afx_msg void OnButtonViewpoint();
	afx_msg void OnButtonViewaddr();
	afx_msg void OnButtonViewdeleteaddress();
	afx_msg void OnButtonDelete();
	afx_msg void OnDblclkListConv(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCheckChange();
	afx_msg void OnButtonEdit12mode();
	virtual void OnCancel();
	afx_msg void OnSelchangeComboRecord();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	BOOL CheckKeepTimeFormat();
	CThemeHelperST	m_ThemeHelper;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_POINTEDITSWITCHIN_H__F6CD08C1_979D_4079_8590_F2392FD39CE2__INCLUDED_)
