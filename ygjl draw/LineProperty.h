#if !defined(AFX_LINEPROPERTY_H__2E21ACC9_AF91_4071_BD21_847A14B72B03__INCLUDED_)
#define AFX_LINEPROPERTY_H__2E21ACC9_AF91_4071_BD21_847A14B72B03__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LineProperty.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLineProperty dialog

class CLineProperty : public CPropertyPage
{
	DECLARE_DYNCREATE(CLineProperty)

// Construction
public:


	CLineProperty();
	~CLineProperty();

// Dialog Data
	//{{AFX_DATA(CLineProperty)
	enum { IDD = IDD_PROP_RECT };
	CXTComboBoxEx	m_ctlLineStyle;
	CSpinButtonCtrl	m_cltLineSize;
	CXTColorPicker	m_ctlFillColor;
	CXTColorPicker	m_ctlLineColor;
	BOOL	m_bNoFill;
	UINT	m_nLineSize;
	//}}AFX_DATA
	COLORREF	m_clrFillColor;		//填充颜色
	COLORREF	m_clrLineColor;		//线条颜色
	DashStyle   m_LineStyle;				//线条风格

	BOOL		m_bUpdata;

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CLineProperty)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CLineProperty)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelendokComboLinestyle();
	afx_msg void OnChange();
	afx_msg void OnNoFill();
	//}}AFX_MSG
	afx_msg void OnSelEndOkFillClr();
	afx_msg void OnSelEndOkLineClr();
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LINEPROPERTY_H__2E21ACC9_AF91_4071_BD21_847A14B72B03__INCLUDED_)
