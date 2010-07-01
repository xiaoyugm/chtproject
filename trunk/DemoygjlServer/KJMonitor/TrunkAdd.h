#if !defined(AFX_TRUNKADD_H__18E80B02_BC69_48E5_98B0_D73B5DB36FAC__INCLUDED_)
#define AFX_TRUNKADD_H__18E80B02_BC69_48E5_98B0_D73B5DB36FAC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TrunkAdd.h : header file
//

#include "SQL\\sqldirect.h"

/////////////////////////////////////////////////////////////////////////////
// CTrunkAdd form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CTrunkAdd : public CFormView
{
protected:
	CTrunkAdd();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CTrunkAdd)

// Form Data
public:
	//{{AFX_DATA(CTrunkAdd)
	enum { IDD = IDD_DLG_TRUNKADD };
	CStatic	m_NoUse;
	CStatic	m_Use;
	CComboBox	m_ctrlboTrunk;
	CXTListCtrl	m_ListCtrl;
	//}}AFX_DATA

// Attributes
public:
	HICON m_hHalloween1;
	HICON m_hHalloween2;
	CSQLDirect m_SQLDirect;
	UINT Address ;
	UINT Dispicon ;

// Operations
public:
	void InsertItems();
	void InitImageList();
	void ConnectDB(void);
	void GetDataFromDBPoint(void);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTrunkAdd)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CTrunkAdd();
//	HICON m_hIcon;
	CImageList	m_cImageListNormal ;
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CTrunkAdd)
	afx_msg void OnDestroy();
	afx_msg void OnSelchangeBoTrunk();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TRUNKADD_H__18E80B02_BC69_48E5_98B0_D73B5DB36FAC__INCLUDED_)
