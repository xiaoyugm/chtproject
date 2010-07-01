#if !defined(AFX_ADDRPOINTSCANSTATUSDLG_H__FFD049E9_9D90_42D3_952F_DD5FA0DEA6FA__INCLUDED_)
#define AFX_ADDRPOINTSCANSTATUSDLG_H__FFD049E9_9D90_42D3_952F_DD5FA0DEA6FA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AddrPointScanStatusDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAddrPointScanStatusDlg dialog

class CAddrPointScanStatusDlg : public CDialog
{
// Construction
public:
	void SetDispStaticContent(void);
	void SetListCtrlHead(void);
	unsigned char m_ucAddrNo;
	unsigned char m_ucTrunkNo;
	CAddrPointScanStatusDlg(CWnd* pParent = NULL);   // standard constructor

	CXTColorPicker	m_cpText;
	CXTColorPicker	m_cpBack;
	COLORREF m_clrRowText;
	COLORREF m_clrRowBack;

	int               m_nSortedCol;
	BOOL              m_bAscending;
	CXTFlatHeaderCtrl m_flatHeader;


// Dialog Data
	//{{AFX_DATA(CAddrPointScanStatusDlg)
	enum { IDD = IDD_DLG_SCANVIEWPOINTONADDR };
	CXTListCtrl	m_ctrlListPointStatus;
	CStatic	m_ctrlSaticTrunkAddr;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAddrPointScanStatusDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAddrPointScanStatusDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ADDRPOINTSCANSTATUSDLG_H__FFD049E9_9D90_42D3_952F_DD5FA0DEA6FA__INCLUDED_)
