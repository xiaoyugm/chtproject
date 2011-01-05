#if !defined(AFX_SAMPLEFORMVIEW_H__149EB79D_00E5_4190_A87C_FE96871C5BBA__INCLUDED_)
#define AFX_SAMPLEFORMVIEW_H__149EB79D_00E5_4190_A87C_FE96871C5BBA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SampleFormView.h : header file
//

#include "CListCtrl_DataModel.h"
/////////////////////////////////////////////////////////////////////////////
// CSampleFormView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CSampleFormView : public CFormView
{
protected:
	CSampleFormView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CSampleFormView)

// Form Data
public:
	//{{AFX_DATA(CSampleFormView)
	enum { IDD = IDD_FORMVIEW };
	CXTListCtrl	m_List1;
//	CGridListCtrlGroups	m_List2;
	CXTListCtrl	m_List2;
	CXTListCtrl	m_List3;
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA
	CListCtrl_DataModel m_DataModel;
	CImageList m_ImageList;
	POSITION	m_ViewPos;

	CString    strItem;
	int        m_Itemnum;
	int        nlistaj;
	int        ilistaj;
	int        n_cF;
	int                 m_iTheme;
	BOOL                m_bHotTracking,b_curdis;
	BOOL                m_bWinTheme;
	BOOL                m_bSortArrow;
	int             m_nSortedCol;
	bool            m_bAscending;
	int             m_nSortedCol2;
	bool            m_bAscending2;
	int             m_nSortedCol3;
	bool            m_bAscending3;
	HICON           m_hIcon;
//	int nlist;

	ListV m_strl1[100];
	vector<CString> m_vl1;
	vector<CString> m_vl2;
	vector<CString> m_vl3;
    SListstatus  m_ls[3][MAX_FDS][MAX_CHAN];

// Attributes
public:
//	CXTColorPicker	m_cpText;
//	CXTColorPicker	m_cpBack;
	COLORREF m_clrRowText;
	COLORREF m_clrRowBack;
//	CXTFlatHeaderCtrl m_flatHeader;
	CXTHeaderCtrl  m_flatHeader;
	CXTHeaderCtrl  m_flatHeader2;
	CXTHeaderCtrl  m_flatHeader3;
//	CXTHeaderCtrl   m_header;

	CString2DataType m_Str2Data;
	CImageList m_SampleFormImageList;
// Operations
public:
	void DisList123();
	void DisList(int nlist ,int ilist);
	void DisLEXT(int nlist ,int nfds,int nchan,int i);
	void BuildList(int nlist ,int ilist);
	void BuildLEXT(int nlist ,int nfds,int nchan,int i);
	void OpenAddDel();
	void Openadjust();
	void Deladjust();
    void AdjustAll() ;
    void DelAllAdjust() ;
	void OpenDayRT();
	void OpenRTChart();

	void SetInfo();
	void SetMonitorListHead(void);
	void SetLHeadEXT(int mlist);

	void EnableControls(BOOL bRedraw=TRUE);
	void SortColumn(int iCol, bool bAsc ,int mlist);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSampleFormView)
	public:
//	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
//	virtual bool SortList(int nCol, bool bAscending);
	virtual void OnInitialUpdate();
//	virtual CScrollBar* GetScrollBarCtrl(int nBar) const;
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CSampleFormView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CSampleFormView)
	afx_msg void OnFORMSLISTEXT();
	afx_msg void OnFORMPAGESO();
	afx_msg void OnFORMSCOLOR();
	afx_msg void OnDRAWS();
	afx_msg   void   OnColumnclickListstock(NMHDR*   pNMHDR,   LRESULT*   pResult); 
	afx_msg   void   OnColumnclickListstock2(NMHDR*   pNMHDR,   LRESULT*   pResult); 
	afx_msg   void   OnColumnclickListstock3(NMHDR*   pNMHDR,   LRESULT*   pResult); 
//	afx_msg void OpenAddDel(int ilist);
	afx_msg void OnSelendokComboThemes();
//	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
//	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
//	afx_msg void OnPaint();
	afx_msg void OnRclick1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnRclick2(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnRclick3(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

//    CScrollBar m_ScrollBarH;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SAMPLEFORMVIEW_H__149EB79D_00E5_4190_A87C_FE96871C5BBA__INCLUDED_)
