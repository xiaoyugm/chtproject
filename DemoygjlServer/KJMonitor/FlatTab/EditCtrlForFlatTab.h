#if !defined(AFX_EDITCTRLFORFLATTAB_H__0A4C819E_A230_4050_87AB_2BC8DAA04377__INCLUDED_)
#define AFX_EDITCTRLFORFLATTAB_H__0A4C819E_A230_4050_87AB_2BC8DAA04377__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EditCtrlForFlatTab.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CEditCtrlForFlatTab window

class CEditCtrlForFlatTab : public CEdit
{
// Construction
public:
	CEditCtrlForFlatTab();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEditCtrlForFlatTab)
	public:
	virtual CScrollBar* GetScrollBarCtrl(int nBar) const;
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEditCtrlForFlatTab();

	// Generated message map functions
protected:
	//{{AFX_MSG(CEditCtrlForFlatTab)
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnUpdate();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

    CScrollBar m_ScrollBarH;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EDITCTRLFORFLATTAB_H__0A4C819E_A230_4050_87AB_2BC8DAA04377__INCLUDED_)
