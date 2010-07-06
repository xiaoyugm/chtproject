#if !defined(AFX_BUTTONSETDLG_H__D75F1D7D_9B10_43F6_A448_04372DDF3BC3__INCLUDED_)
#define AFX_BUTTONSETDLG_H__D75F1D7D_9B10_43F6_A448_04372DDF3BC3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ButtonSetDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CButtonSetDlg dialog

class CButtonSetDlg : public CPropertyPage
{
	DECLARE_DYNCREATE(CButtonSetDlg)

// Construction
public:
	CButtonSetDlg();
	~CButtonSetDlg();

// Dialog Data
	//{{AFX_DATA(CButtonSetDlg)
	enum { IDD = IDD_DIALOG_BUTTON };
	CComboBox	m_ctlLinkView;
	CEdit	m_ctlPointNo;
	CEdit	m_ctlEnd;
	CEdit	m_ctlStart;
	CButton	m_PointNo;
	CButton	m_bCheck;
	CXTColorPicker	m_ctlFalseColor;
	CXTColorPicker	m_ctlTrueColor;
	CXTColorPicker	m_ctlErrorColor;
	CComboBox	m_ctlStyleCombo;
	CComboBox	m_ctlPostionCombo;
	CComboBox	m_ctlBorderCombo;
	CSpinButtonCtrl	m_ctlFontSize;
///	CSpinButtonCtrl	m_ctlTrans;
	CXTFontCombo	m_ctlFontCombo;
	CXTColorPicker	m_ctlTextColor;
	CString	m_strButton;
	BYTE	m_fontSize;
///	UINT	m_ntrans;
	UINT	m_nPointNo;
	BOOL	m_bIsRunShowValue;
	CString	m_strLinkViewName;
	//}}AFX_DATA
	CString				m_fontName;
	FontStyle           m_fontStyle;
	StringTrimming		m_trimmingSyle;
	StringFormatFlags   m_format;
	StringAlignment     m_fontAlignment;

	BOOL				m_bIsButton;
	COLORREF			m_color;
	COLORREF			m_FillColor;
	COLORREF			m_TrueColor;
	COLORREF			m_FalseColor;
	COLORREF			m_ErrorColor;

public:
	void InitSelectViewCombo();
// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CButtonSetDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CButtonSetDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelendokComboStyle();
	afx_msg void OnSelendokComboBorder();
	afx_msg void OnSelendokComboFont();
	afx_msg void OnSelendokComboPosition();
	afx_msg void OnDestroy();
	afx_msg void OnButtonPath();
	//}}AFX_MSG
	afx_msg void OnSelEndOkClr();
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BUTTONSETDLG_H__D75F1D7D_9B10_43F6_A448_04372DDF3BC3__INCLUDED_)
