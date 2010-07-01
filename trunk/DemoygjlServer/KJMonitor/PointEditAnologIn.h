#if !defined(AFX_POINTEDITANOLOGIN_H__5A603F00_4A38_11D7_9737_000795E47391__INCLUDED_)
#define AFX_POINTEDITANOLOGIN_H__5A603F00_4A38_11D7_9737_000795E47391__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PointEditAnologIn.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPointEditAnologIn dialog
#include "Controls\\XPStyleButtonST.h"
#include "Controls\\ThemeHelperST.h"

#include "SQL\\sqldirect.h"
#include "SQL\\String2DataType.h"


class CPointEditAnologIn : public CDialog
{
// Construction
public:
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
	CPointEditAnologIn(CWnd* pParent = NULL);   // standard constructor


protected:

	BOOL m_bPointEditChange;

	CSQLDirect m_SQLDirect;
	CString2DataType m_String2DataType;
	BOOL m_bSave,m_bSaveSuccess;
	UINT m_unConvID;

	CXTColorPicker	m_cpText;
	CXTColorPicker	m_cpBack;
	COLORREF m_clrRowText;
	COLORREF m_clrRowBack;

	int               m_nSortedCol;
	BOOL              m_bAscending;
	CXTFlatHeaderCtrl m_flatHeader;





// Dialog Data
	//{{AFX_DATA(CPointEditAnologIn)
	enum { IDD = IDD_DLG_POINTEDIT_ANOLOG_IN };
//	CComboBox	m_ctrlComboProcessType2;
	CEdit	m_ctrlEditChannel;
	CEdit	m_ctrlEditAddress;
	CButton	m_ctrlCheckChange;
	CXPStyleButtonST	m_ctrlBtnDelete;
	CXTListCtrl	m_ctrlList;
	CComboBox	m_ctrlComboPrecision;
	CComboBox	m_ctrlComboProcessType;
	CComboBox	m_ctrlComboScanFrequency;
	CComboBox	m_ctrlComboTrunkNo;
	CComboBox	m_ctrlComboWarnClass;
	CXPStyleButtonST	m_ctrlBtnBiewDeleteAddress;
	CButton	m_ctrlCheckMultiConv;
	CXPStyleButtonST	m_ctrlBtnViewPoint;
	CXPStyleButtonST	m_ctrlBtnViewAddr;
	CComboBox	m_ctrlComboBScan;
	CComboBox	m_ctrlComboSensorAccuracy;
	CComboBox	m_ctrlComboSensorName;
	CXPStyleButtonST m_btnPOINTNOBACKWORD;
	CXPStyleButtonST m_btnPOINTNOFORWORD;
	CXPStyleButtonST m_btnOK;
	CXPStyleButtonST m_btnCANCEL;
	CXPStyleButtonST m_btnADDEDITANDGOON;
	CComboBox	m_ctrlComboWarn;  //报警模式
//	CComboBox	m_ctrlComboPrintYN;
	CComboBox	m_ctrlComboSensorType;    //传感器类型
	UINT	m_unEditPoint;              //点号
	CEdit	m_ctrlEditPoint;          
	UINT	m_unEditAddress;
	double	m_dfEditMeaScopeMin;
	double	m_dfEditMeaScopeMax;
	CString	m_strEditUnit;
	UINT	m_unEditWarnDelay;
	CString	m_strEditOtherExplain;
	CString	m_strEditPointLabel;
	UINT	m_unEditChannel;
	double	m_unEditWarnMax;
	double	m_unEditWarnMin;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPointEditAnologIn)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void SetListHead(void);

	// Generated message map functions
	//{{AFX_MSG(CPointEditAnologIn)
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
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	CThemeHelperST	m_ThemeHelper;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_POINTEDITANOLOGIN_H__5A603F00_4A38_11D7_9737_000795E47391__INCLUDED_)
