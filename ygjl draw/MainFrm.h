// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__3883AFBA_52CE_46F2_AC21_5DC8AE8F4635__INCLUDED_)
#define AFX_MAINFRM_H__3883AFBA_52CE_46F2_AC21_5DC8AE8F4635__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "TabDockWnd.h"
#include "ToolBoxBar.h"
#include "NotifyCombo.h"

class CMainFrame : public CXTMDIFrameWnd
{
	DECLARE_DYNAMIC(CMainFrame)
public:
	CMainFrame();

// Attributes
public:
	CXTFontCombo& GetFontCombo() {
		return m_wndComboFont;
	}

	void GetSelFont( XT_LOGFONT& lf, COLORREF& cr );
	bool InitComboFont();
	bool InitComboSize();
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

public:  // control bar embedded members

	void AddLogo();
	void RemoveLogo();

	CXTLogoPane      m_wndLogoPane;
    CTabDockWnd		 m_wndTabDockBar;
	CXTStatusBar     m_wndStatusBar;
	CXTToolBar       m_wndToolBar;
	CToolBoxBar		 m_wndToolboxBar;
	CXTToolBar		 m_wndFormatBar;

	CNotifyCombo <CXTFontCombo>    m_wndComboFont;
	CNotifyCombo <CXTFlatComboBox> m_wndComboSize;

	CString  m_strFontSize;
	CString  m_strFontName;
	BOOL     m_bBold;
	BOOL     m_bItalic;
	BOOL     m_bUnderline;
	COLORREF m_crCurrent;
	COLORREF m_crFillColor;
	int      m_uCmdID;
// Generated message map functions
// Generated message map functions
protected:
	CXTWindowPos     m_wndPosition;

public:
	// Overrode CWnd implementation to restore saved window position.
	BOOL ShowWindowEx(int nCmdShow);
	void SetMousePosText(CPoint Logpoint,CPoint Devpoint);
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnViewFormat();
	afx_msg void OnUpdateViewFormat(CCmdUI* pCmdUI);
	afx_msg void OnViewWorkspace();
	afx_msg void OnUpdateViewWorkspace(CCmdUI* pCmdUI);
	afx_msg void OnViewToolbox();
	afx_msg void OnUpdateViewToolbox(CCmdUI* pCmdUI);
	afx_msg void OnFormattingColor();
	afx_msg void OnFormattingBackColor();
///	afx_msg void OnPupopActive();
	afx_msg void OnPopupClose();
	afx_msg void OnPopopMin();
	afx_msg void OnPopupMin();
	afx_msg void OnPopupProperty();
	//}}AFX_MSG
	afx_msg void OnSelEndOk();
	afx_msg void OnReturn(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg LRESULT OnSelEndOKColor(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnToolbarDropDown(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__3883AFBA_52CE_46F2_AC21_5DC8AE8F4635__INCLUDED_)
