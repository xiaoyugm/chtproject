#if !defined(AFX_BUTTONSETDLG_H__D75F1D7D_9B10_43F6_A448_04372DDF3BC3__INCLUDED_)
#define AFX_BUTTONSETDLG_H__D75F1D7D_9B10_43F6_A448_04372DDF3BC3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ColorSetDlg.h : header file
//

#include "dbAx\AxContactCmd.hpp"
#include "dbAx\AxColorset.hpp"
#include "dbAx\CardFileEvents.hpp"
#include "dbAx\AccountSetEvents.hpp"
/////////////////////////////////////////////////////////////////////////////
// CColorSetDlg dialog

class CColorSetDlg : public CDialog
{
	DECLARE_DYNCREATE(CColorSetDlg)

// Construction
public:
	CColorSetDlg();
	~CColorSetDlg();

// Dialog Data
	//{{AFX_DATA(CButtonSetDlg)
	enum { IDD = IDD_COLORSET };
//	CComboBox	m_ctlLinkView;
//	CEdit	m_ctlPointNo;
//	CEdit	m_ctlEnd;
//	CEdit	m_ctlStart;
//	CButton	m_PointNo;
//	CButton	m_bCheck;
	CXTColorPicker	m_ctlFalseColor;
	CXTColorPicker	m_ctlTrueColor;
	CXTColorPicker	m_ctlErrorColor;
//	CComboBox	m_ctlStyleCombo;
//	CComboBox	m_ctlPostionCombo;
//	CComboBox	m_ctlBorderCombo;
//	CSpinButtonCtrl	m_ctlFontSize;
///	CSpinButtonCtrl	m_ctlTrans;
//	CXTFontCombo	m_ctlFontCombo;
	CXTColorPicker	m_ctlColor1;
	CXTColorPicker	m_ctlColor2;
	CXTColorPicker	m_ctlColor3;
	CXTColorPicker	m_ctlColor4;
	CXTColorPicker	m_ctlColor5;
	CXTColorPicker	m_ctlColor6;
	CXTColorPicker	m_ctlColor7;
	CXTColorPicker	m_ctlColor8;
	CXTColorPicker	m_ctlColor9;
//	CString	m_strButton;
//	BYTE	m_fontSize;
///	UINT	m_ntrans;
//	UINT	m_nPointNo;
//	BOOL	m_bIsRunShowValue;
//	CString	m_strLinkViewName;
	//}}AFX_DATA
//	CString				m_fontName;
//	FontStyle           m_fontStyle;
//	StringTrimming		m_trimmingSyle;
//	StringFormatFlags   m_format;
//	StringAlignment     m_fontAlignment;
  CAxConnection   m_Cn;
  CAxContactCmd   m_ContactCmd;
  CAxColorset     m_Colorset;
  CAxColorset     *m_ColorsetNew;

//	BOOL				m_bIsButton;
	COLORREF			m_color1;
	COLORREF			m_color2;
	COLORREF			m_color3;
	COLORREF			m_color4;
	COLORREF			m_color5;
	COLORREF			m_color6;
	COLORREF			m_color7;
	COLORREF			m_color8;
	COLORREF			m_color9;

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
	afx_msg void OnButSend();
	//}}AFX_MSG
	afx_msg void OnSelEndOkClr();
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BUTTONSETDLG_H__D75F1D7D_9B10_43F6_A448_04372DDF3BC3__INCLUDED_)
