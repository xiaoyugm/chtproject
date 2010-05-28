// DrawDoc.h : interface of the CDrawDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DRAWDOC_H__2C440487_C90D_4C41_B02C_2F89931CF85B__INCLUDED_)
#define AFX_DRAWDOC_H__2C440487_C90D_4C41_B02C_2F89931CF85B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "drawobj.h"

class CDrawSrvrItem;

class CDrawDoc : public COleServerDoc
{
protected: // create from serialization only
	CDrawDoc();
	DECLARE_DYNCREATE(CDrawDoc)
// Attributes
public:
	CDrawSrvrItem* GetEmbeddedItem()
		{ return (CDrawSrvrItem*)COleServerDoc::GetEmbeddedItem(); }

	CDrawObjList* GetObjects() { return &m_objects; }
	const CSize& GetSize() const { return m_size; }
	void ComputePageSize();
	int GetMapMode() const { return m_nMapMode; }
	COLORREF GetPaperColor() const { return m_paperColor; }

// Operations
public:
	CDrawObj* ObjectAt(const CPoint& point);
	void Draw(CDC* pDC, CDrawView* pView);
	void Add(CDrawObj* pObj);
	void Remove(CDrawObj* pObj);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDráwDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	virtual void OnCloseDocument();
	protected:
	virtual COleServerItem* OnGetEmbeddedItem();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDrawDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	CDrawObjList m_objects;
	CSize m_size;
	int m_nMapMode;
	COLORREF m_paperColor;
	CString  m_strDocName;
// Generated message map functions
public:
	//{{AFX_MSG(CDrawDoc)
	afx_msg void OnSettingPageColor();
	afx_msg void OnSettingPageSize();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CDrawDoc)
	afx_msg void OnViewPaperColor();
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DRAWDOC_H__2C440487_C90D_4C41_B02C_2F89931CF85B__INCLUDED_)
