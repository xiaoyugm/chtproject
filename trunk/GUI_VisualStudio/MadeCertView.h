#if !defined(AFX_MADECERTVIEW_H__2DC53940_CBBB_48C6_9455_F8244E91A324__INCLUDED_)
#define AFX_MADECERTVIEW_H__2DC53940_CBBB_48C6_9455_F8244E91A324__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MadeCertView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMadeCertView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CMadeCertView : public CFormView
{
public:
	CMadeCertView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CMadeCertView)
	virtual ~CMadeCertView();

// Form Data
public:
	//{{AFX_DATA(CMadeCertView)
	enum { IDD = IDD_FORMVIEW_MADE };
	CListCtrl	m_List;
	UINT	m_ctrlStartH;
	UINT	m_ctrlEndH;
	CDateTimeCtrl	m_ctrlStartTime;
	CDateTimeCtrl	m_ctrlEndTime;
	CXTFlatComboBox     m_ComBoxSM;
	CXTListCtrl         m_LCEXCEL1;
	CXTListCtrl         m_LCEXCEL2;
	//}}AFX_DATA
	CTime m_endDateTime;
	CTime m_startDateTime;
	CTime t;
	CTime t1;

	ADOCust::_RecordsetPtr pRS1;
    CAxCommonSet        m_CommonSet;

	ADMainDis         m_ADRecord[MAX_FDS][MAX_CHAN][300];          //¼ÇÂ¼²éÑ¯
	CString2DataType    m_Str2Data;
	int mPoint[1000];
	vector<int> m_Points;
	vector<int>::iterator  iter;
	BOOL b_twodb;
// Attributes
public:
	int             m_nSortedCol;
	bool            m_bAscending;
	CXTHeaderCtrl   m_header;

	BOOL m_bExcelInit;
	int m_select;
	CString m_stragrv;
	CString m_num;
	CBitmap m_bitMadeView,m_bitMadeViewUser,m_bitMadeCert;

	void OnSABFE();

	void OnRECAAD();
	void OnRECABD();
	void OnRECAFED();
	void OnRECASR();
	void OnRECDABD();
	void OnRECDABB();
	void OnRECDFED();
	void OnRECDSCD();
	void OnRECDRIVERE();

	void OnEXCELA();

	void OnTAuto();
	void ACALRecord();
	void copy_sheet(const char* from, const char* to);
	void L2upDB();
	void InitStr();
	void ADODBS(CString strTable,int n_dbl);
	void ClearRDB();

	void SortColumn(int iCol, bool bAsc);
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMadeCertView)
	public:
	virtual void OnInitialUpdate();
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
//	virtual bool SortList(int nCol, bool bAscending);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CMadeCertView)
	afx_msg void OnBED();
	afx_msg void OnBES();
	afx_msg void OnchangeComboSM();
	afx_msg void OnChangeEditStarth();
	afx_msg void OnChangeEditEndh();
	afx_msg void OnDatetimestart(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDatetimeend(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBOKSEARCH();
	afx_msg void OnButtonViewinfo();
	afx_msg void OnClickListMade(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MADECERTVIEW_H__2DC53940_CBBB_48C6_9455_F8244E91A324__INCLUDED_)
