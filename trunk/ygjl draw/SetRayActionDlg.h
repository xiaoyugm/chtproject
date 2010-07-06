#if !defined(AFX_SETRAYACTIONDLG_H__84180561_A522_4486_89CB_B2F22A8B0DBB__INCLUDED_)
#define AFX_SETRAYACTIONDLG_H__84180561_A522_4486_89CB_B2F22A8B0DBB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetRayActionDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSetRayActionDlg dialog

class CSetRayActionDlg : public CDialog
{
// Construction
public:
	CSetRayActionDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSetRayActionDlg)
	enum { IDD = IDD_DIALOG_SET_RAY_ACTION };
	CXTColorPicker	m_StartColor;
	CXTColorPicker	m_EndColor;
	CString	m_strSpeed;
	CString	m_strType;
	UINT	m_nMax;
	UINT	m_nMin;
	UINT	m_nPointNo;
	//}}AFX_DATA
	COLORREF     m_clrStartColor;
	COLORREF     m_clrEndColor;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSetRayActionDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSetRayActionDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETRAYACTIONDLG_H__84180561_A522_4486_89CB_B2F22A8B0DBB__INCLUDED_)
