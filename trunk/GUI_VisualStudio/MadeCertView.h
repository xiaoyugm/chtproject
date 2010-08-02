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
protected:
	CMadeCertView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CMadeCertView)

// Form Data
public:
	//{{AFX_DATA(CMadeCertView)
	enum { IDD = IDD_FORMVIEW_MADE };
	CListCtrl	m_List;
	//}}AFX_DATA

// Attributes
public:
	int m_select;
	CString m_num;
	CBitmap m_bitMadeView,m_bitMadeViewUser,m_bitMadeCert;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMadeCertView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CMadeCertView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CMadeCertView)
	afx_msg void OnButtonLineandmade();
	afx_msg void OnButtonViewinfo();
	afx_msg void OnButtonAutMade();
	afx_msg void OnClickListMade(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MADECERTVIEW_H__2DC53940_CBBB_48C6_9455_F8244E91A324__INCLUDED_)
