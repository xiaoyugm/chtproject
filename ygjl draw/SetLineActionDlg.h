#if !defined(AFX_SETLINEACTIONDLG_H__87F3E6C5_9482_4F0D_A23F_967CF1C3371D__INCLUDED_)
#define AFX_SETLINEACTIONDLG_H__87F3E6C5_9482_4F0D_A23F_967CF1C3371D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetLineActionDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSetLineActionDlg dialog

class CSetLineActionDlg : public CDialog
{
// Construction
public:
	CSetLineActionDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSetLineActionDlg)
	enum { IDD = IDD_DIALOG_SET_LINE_ACTION };
	CXTColorPicker	m_CommErrorColor;
	CXTColorPicker	m_OutColor;
	CXTColorPicker	m_InColor;
	UINT	m_nPointNo;
	//}}AFX_DATA
	COLORREF     	m_clrInLineColor;
	COLORREF    	m_clrOutLineColor;
	COLORREF    	m_clrCommErrorLineColor;
	unsigned char	m_LineWarn_state;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSetLineActionDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSetLineActionDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETLINEACTIONDLG_H__87F3E6C5_9482_4F0D_A23F_967CF1C3371D__INCLUDED_)
