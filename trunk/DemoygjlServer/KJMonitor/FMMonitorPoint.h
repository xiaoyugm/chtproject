#if !defined(AFX_FMMONITORPOINT_H__1726F403_DBA2_4025_BD33_9884CBE6818C__INCLUDED_)
#define AFX_FMMONITORPOINT_H__1726F403_DBA2_4025_BD33_9884CBE6818C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FMMonitorPoint.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFMMonitorPoint form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

#include "Controls\\XPStyleButtonST.h"
#include "Controls\\ThemeHelperST.h"
#include "SQL\\sqldirect.h"

class CFMMonitorPoint : public CFormView
{
protected:
	CFMMonitorPoint();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CFMMonitorPoint)

// Form Data
public:
	//{{AFX_DATA(CFMMonitorPoint)
	enum { IDD = IDD_DLG_FMMONITORPOINT };
	CStatic	m_ctrlStaticCloseOpen9;
	CStatic	m_ctrlStaticCloseOpen8;
	CStatic	m_ctrlStaticCloseOpen15;
	CStatic	m_ctrlStaticCloseOpen14;
	CStatic	m_ctrlStaticCloseOpen13;
	CStatic	m_ctrlStaticCloseOpen12;
	CStatic	m_ctrlStaticCloseOpen11;
	CStatic	m_ctrlStaticCloseOpen10;
	CButton	m_ctrlCheckDispAsSamplePoint;
	CXPStyleButtonST	m_ctrlBtnDispMonitorNo;
	CStatic	m_ctrlStaticCloseOpen7;
	CStatic	m_ctrlStaticCloseOpen6;
	CStatic	m_ctrlStaticCloseOpen5;
	CStatic	m_ctrlStaticCloseOpen4;
	CStatic	m_ctrlStaticCloseOpen3;
	CStatic	m_ctrlStaticCloseOpen2;
	CStatic	m_ctrlStaticCloseOpen1;
	CStatic	m_ctrlStaticCloseOpen0;
	CXTListCtrl	m_ctrlListMonitor;
	short	m_snEditDispMonitorNo;
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
	BOOL bStartMonitor;
	int m_nPointNoForMonitorNo[MAX_POINT_NUMBER];
	unsigned short m_usDispStartMonitorNo,m_usDispStartPointNo;

// Operations
public:
	void UpdatePointsStatus();//更新监测点的状态
	void DrawMonitorStatus(unsigned short usMonitorNo);
	void SetDispMonitorNo(unsigned short sPointNo,unsigned char ucSetContent);

	void SetMointorStatus(UINT unMonitorPointNo);
	void SetSwitchStatus(unsigned char ucDispNo,unsigned short ucStatus);
	void SetBtnStyle(void);
	unsigned char m_ucOldTrunkNo;
	void SetMonitorListHead(void);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFMMonitorPoint)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnDraw(CDC* pDC);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CFMMonitorPoint();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CFMMonitorPoint)
	afx_msg void OnDestroy();
	afx_msg void OnButtonDispmonitorno();
	afx_msg void OnDblclkListMonitor(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	CThemeHelperST	m_ThemeHelper;

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FMMONITORPOINT_H__1726F403_DBA2_4025_BD33_9884CBE6818C__INCLUDED_)
