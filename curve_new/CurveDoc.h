// CurveDoc.h : interface of the CCurveDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CURVEDOC_H__0918A46C_5962_4CCE_8006_104338C8DE46__INCLUDED_)
#define AFX_CURVEDOC_H__0918A46C_5962_4CCE_8006_104338C8DE46__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
//#include "Graphic.h"
#include "CurveProp.h"

class CCurveDoc : public CDocument
{
public:

protected: // create from serialization only
	CCurveDoc();
	DECLARE_DYNCREATE(CCurveDoc)

// Attributes
public:
//	CTypedPtrList<CObList,CGraphic *> m_graphicList;
    CRtCurve *m_pRtCurve;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCurveDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual void DeleteContents();
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual void OnCloseDocument();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CCurveDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CCurveDoc)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CURVEDOC_H__0918A46C_5962_4CCE_8006_104338C8DE46__INCLUDED_)
