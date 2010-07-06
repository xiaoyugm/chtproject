#if !defined(AFX_NEWDOCUMENT_H__736DC493_42C1_4E4E_8A95_AA3191C2F38A__INCLUDED_)
#define AFX_NEWDOCUMENT_H__736DC493_42C1_4E4E_8A95_AA3191C2F38A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NewDocument.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CNewDocument dialog

class CNewDocument : public CDialog
{
// Construction
public:
	CNewDocument(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CNewDocument)
	enum { IDD = IDD_DIALOG_NEW_DOC };
	CXTColorPicker	m_color;
	CSpinButtonCtrl	m_ctlWidth;
	CSpinButtonCtrl	m_ctlHeight;
	CString	m_strDocName;
	long	m_lHeight;
	BOOL	m_bIsAutoSize;
	long	m_lWidth;
	//}}AFX_DATA
	COLORREF        m_clrColor;
	BOOL    m_bInitIsOk;
	float    m_width, m_height;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNewDocument)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CNewDocument)
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void OnChangeEditHeight();
	afx_msg void OnChangeEditWidth();
	afx_msg void OnCheckAutosize();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NEWDOCUMENT_H__736DC493_42C1_4E4E_8A95_AA3191C2F38A__INCLUDED_)
