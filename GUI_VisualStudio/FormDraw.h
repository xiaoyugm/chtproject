#if !defined(AFX_FORMDRAW_H__6AF7014F_888B_4EE5_9742_A48797B799E1__INCLUDED_)
#define AFX_FORMDRAW_H__6AF7014F_888B_4EE5_9742_A48797B799E1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FormDraw.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFormDraw dialog

class CFormDraw : public CDialog
{
// Construction
public:
	CFormDraw(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CFormDraw)
	enum { IDD = IDD_DFANSA };
	CXTListCtrl         m_LCFD;
	CXTListCtrl         m_LCFDA;
	CString    strsm;
	CXTFlatComboBox     m_ComDraw;
	//}}AFX_DATA
	CSearchDir m_sdir;
	CString m_result;
	CString2DataType    m_Str2Data;
	int   m_dorf;

	void L2upDB();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFormDraw)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CFormDraw)
	afx_msg void OnBES();
	afx_msg void OnBED();
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FORMDRAW_H__6AF7014F_888B_4EE5_9742_A48797B799E1__INCLUDED_)
