#if !defined(AFX_FONTPROPERTIESDLG_H__967F101E_D5DE_41C1_8EBE_764942AEC059__INCLUDED_)
#define AFX_FONTPROPERTIESDLG_H__967F101E_D5DE_41C1_8EBE_764942AEC059__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FontPropertiesDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFontPropertiesDlg dialog

class CFontPropertiesDlg : public CPropertyPage
{
	DECLARE_DYNCREATE(CFontPropertiesDlg)

// Construction
public:
	CFontPropertiesDlg();
	~CFontPropertiesDlg();

// Dialog Data
	//{{AFX_DATA(CFontPropertiesDlg)
	enum { IDD = IDD_DIALOG_TEXT };
	CButton	m_bDispTrue;
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
	BOOL	m_blsDispTrue;
	//}}AFX_DATA
public:

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


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CFontPropertiesDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CFontPropertiesDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelendokComboStyle();
	afx_msg void OnSelendokComboBorder();
	afx_msg void OnSelendokComboFont();
	afx_msg void OnSelendokComboPosition();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	afx_msg void OnSelEndOkClr();
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FONTPROPERTIESDLG_H__967F101E_D5DE_41C1_8EBE_764942AEC059__INCLUDED_)
