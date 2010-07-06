#if !defined(AFX_SETFILLACTIONDLG_H__2038CE4C_674C_497B_B261_BFC2DAEC4BB7__INCLUDED_)
#define AFX_SETFILLACTIONDLG_H__2038CE4C_674C_497B_B261_BFC2DAEC4BB7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetFillActionDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSetFillActionDlg dialog

class CSetFillActionDlg : public CDialog
{
// Construction
public:
	CSetFillActionDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSetFillActionDlg)
	enum { IDD = IDD_DIALOG_SET_FILL_ACTION };
	CXTColorPicker	m_outColor;
	CXTColorPicker	m_inStartColor;
	CXTColorPicker	m_inColor;
	UINT	m_nPointNo;
	//}}AFX_DATA
	COLORREF	m_clrInFillColor;
	COLORREF	m_clrOutFillColor;
	COLORREF    m_clrCommErrorFillColor;
	unsigned char	m_FillWarn_state;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSetFillActionDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSetFillActionDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETFILLACTIONDLG_H__2038CE4C_674C_497B_B261_BFC2DAEC4BB7__INCLUDED_)
