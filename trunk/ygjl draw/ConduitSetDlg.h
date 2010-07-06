#if !defined(AFX_CONDUITSETDLG_H__96221199_CC46_4466_884B_A9B3DB1F71BF__INCLUDED_)
#define AFX_CONDUITSETDLG_H__96221199_CC46_4466_884B_A9B3DB1F71BF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ConduitSetDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CConduitSetDlg dialog

class CConduitSetDlg : public CDialog
{
// Construction
public:
	CConduitSetDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CConduitSetDlg)
	enum { IDD = IDD_DIALOG_CONDUIT };
	CXTColorPicker	m_Dot;
	CXTColorPicker	m_Conduit;
	UINT	m_nWidth;
///	UINT	m_nConduitTrans;
///	UINT	m_nDotTrans;
	BOOL	m_bIsAction;
///	BOOL	m_bIsShowMove;
///	UINT	m_nMax;
///	UINT	m_nMin;
	UINT	m_nPointNo;
	//}}AFX_DATA

	COLORREF	m_clrConduitColor;
	COLORREF	m_clrDotColor;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CConduitSetDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CConduitSetDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONDUITSETDLG_H__96221199_CC46_4466_884B_A9B3DB1F71BF__INCLUDED_)
