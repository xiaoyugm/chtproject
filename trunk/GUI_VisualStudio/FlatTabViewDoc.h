// FlatTabViewDoc.h : interface of the CFlatTabViewDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_FLATTABVIEWDOC_H__E6AC6F7A_AD3F_41F6_91A8_4FF679BD6F4E__INCLUDED_)
#define AFX_FLATTABVIEWDOC_H__E6AC6F7A_AD3F_41F6_91A8_4FF679BD6F4E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CRViewDoc : public CDocument
{
protected: // create from serialization only
	CRViewDoc();
	DECLARE_DYNCREATE(CRViewDoc)

// Attributes
public:
// Operations
public:
	void OnCloseD();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFlatTabViewDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual void OnCloseDocument();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CRViewDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CFlatTabViewDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


class CFlatTabViewDoc : public CDocument
{
protected: // create from serialization only
	CFlatTabViewDoc();
	DECLARE_DYNCREATE(CFlatTabViewDoc)

// Attributes
public:
	CString2DataType m_Str2Data;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFlatTabViewDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual void OnCloseDocument();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CFlatTabViewDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CFlatTabViewDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FLATTABVIEWDOC_H__E6AC6F7A_AD3F_41F6_91A8_4FF679BD6F4E__INCLUDED_)
