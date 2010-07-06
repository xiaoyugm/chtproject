#if !defined(AFX_REALTIMEDIALOG_H__6424E36F_D3CA_4EAD_A2EF_3C2CC6B2EA2F__INCLUDED_)
#define AFX_REALTIMEDIALOG_H__6424E36F_D3CA_4EAD_A2EF_3C2CC6B2EA2F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RealTimeDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRealTimeDialog dialog

class CRealTimeDialog : public CDialog
{
// Construction
public:
	CRealTimeDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CRealTimeDialog)
	enum { IDD = IDD_DIALOG_REAL_LINE };
	CXTColorPicker	m_line8;
	CXTColorPicker	m_line7;
	CXTColorPicker	m_line6;
	CXTColorPicker	m_line5;
	CXTColorPicker	m_line4;
	CXTColorPicker	m_line3;
	CXTColorPicker	m_line2;
	CXTColorPicker	m_line1;
	CXTColorPicker	m_backcolor;
	UINT	m_nXMin;
	UINT	m_nXMax;
	UINT	m_nYMax;
	UINT	m_nYMin;
	UINT	m_nPoint1;
	UINT	m_nPoint3;
	UINT	m_nPoint4;
	UINT	m_nPoint2;
	UINT	m_nTimeSpan;
	//}}AFX_DATA
public:
	COLORREF    m_clrBackColor;
	COLORREF    m_clrLine1;
	COLORREF    m_clrLine2;	
	COLORREF    m_clrLine3;
	COLORREF    m_clrLine4;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRealTimeDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CRealTimeDialog)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REALTIMEDIALOG_H__6424E36F_D3CA_4EAD_A2EF_3C2CC6B2EA2F__INCLUDED_)
