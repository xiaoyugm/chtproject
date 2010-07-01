#if !defined(AFX_COLORLISTBOX_H__5529A6B1_584A_11D2_A41A_006097BD277B__INCLUDED_)
#define AFX_COLORLISTBOX_H__5529A6B1_584A_11D2_A41A_006097BD277B__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

//*************************************************************
// ColorListBox.h : header file
//
// MFC ListBox with optional color
// 
// Version: 1.0	01/10/1998 (c)Patrice Godard
//
//**************************************************************

/////////////////////////////////////////////////////////////////////////////
// CColorListBox window

class CColorListBox : public CXTListBox
{
// Construction
public:
	CColorListBox();

// Attributes
public:

// Operations
public:
	int AddString( LPCTSTR lpszItem);
	int AddString( LPCTSTR lpszItem, COLORREF rgb);
	int InsertString( int nIndex, LPCTSTR lpszItem, COLORREF rgb);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CColorListBox)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	//}}AFX_VIRTUAL

// Implementation
public:
	COLORREF getColor(int nIndex);
	int m_FontWidth;
	void SetFont(CString FontName,CString FontSize);
	virtual ~CColorListBox();

	// Generated message map functions
protected:
	//{{AFX_MSG(CColorListBox)
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
private:
	int m_FontSize;
	CString m_FontName;

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COLORLISTBOX_H__5529A6B1_584A_11D2_A41A_006097BD277B__INCLUDED_)
