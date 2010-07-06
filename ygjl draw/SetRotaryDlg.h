#if !defined(AFX_SETROTARYDLG_H__9CF1DD49_13E9_42BC_A872_FDEDAF80961F__INCLUDED_)
#define AFX_SETROTARYDLG_H__9CF1DD49_13E9_42BC_A872_FDEDAF80961F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetRotaryDlg.h : header file
//
#include <ColourPicker.h>
#pragma comment(lib,"Color.lib")

//////////////////////////////////////////////////////////////////////////
// CSetRotaryDlg dialog

class CSetRotaryDlg : public CDialog
{
// Construction
public:
	CSetRotaryDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSetRotaryDlg)
	enum { IDD = IDD_DIALOG_ROTARY };
	CXTColorPicker	m_LineColor;
	CXTColorPicker	m_ForWordColor;
	CXTColorPicker	m_BackColor;
//	CColourPicker	m_LineColor;
//	CColourPicker	m_ForWordColor;
//	CColourPicker	m_BackColor;
	BOOL	m_bIsContrarotate;
	UINT	m_nMax;
	UINT	m_nMin;
	UINT	m_nPointNo;
	UINT	m_nAngle;
	//}}AFX_DATA
	COLORREF       m_clrLineColor;
	COLORREF       m_clrBackColor;
	COLORREF       m_clrForwordColor;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSetRotaryDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSetRotaryDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETROTARYDLG_H__9CF1DD49_13E9_42BC_A872_FDEDAF80961F__INCLUDED_)
