#if !defined(AFX_EFFECTDLG_H__A7C69D1F_7907_4556_B289_7D19E77DC044__INCLUDED_)
#define AFX_EFFECTDLG_H__A7C69D1F_7907_4556_B289_7D19E77DC044__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EffectDlg.h : header file
//
#include "mytabctrl.h"
/////////////////////////////////////////////////////////////////////////////
// CEffectDlg dialog
#include "EffectDlg.h"
#include "enum.h"
#include "LineProperty.h"
///#include "FillPatternDlg.h"
///#include "FillGradientDlg.h"
///#include "ActionDlg.h"


class CEffectDlg : public CDialog
{
// Construction
public:
	CEffectDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CEffectDlg)
	enum { IDD = IDD_FILL_DLG };
	CMyTabCtrl	m_Tab;
	//}}AFX_DATA
	int				   m_effectpage;
	CLineProperty      *m_pLineProperty;

	//CLineProperty
	DashStyle   m_LineStyle;				//�������
	COLORREF	m_clrFillColor;				//�����ɫ
	COLORREF	m_clrLineColor;				//������ɫ
	BOOL		m_bNoFill;					//�Ƿ����
	UINT		m_nLineSize;				//�����ߴ�

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEffectDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CEffectDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EFFECTDLG_H__A7C69D1F_7907_4556_B289_7D19E77DC044__INCLUDED_)
