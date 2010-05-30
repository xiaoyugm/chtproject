// SrvrItem.h : interface of the CDrawSrvrItem class
//

#if !defined(AFX_SRVRITEM_H__3CB668A5_71B8_46D6_A91B_820E71C92457__INCLUDED_)
#define AFX_SRVRITEM_H__3CB668A5_71B8_46D6_A91B_820E71C92457__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CDrawSrvrItem : public COleServerItem
{
	DECLARE_DYNAMIC(CDrawSrvrItem)

// Constructors
public:
	CDrawSrvrItem(CDrawDoc* pContainerDoc);
	ULONG_PTR           gdiplusToken;
// Attributes
	CDrawDoc* GetDocument() const
		{ return (CDrawDoc*)COleServerItem::GetDocument(); }

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDrawSrvrItem)
	public:
	virtual BOOL OnDraw(CDC* pDC, CSize& rSize);
	virtual BOOL OnGetExtent(DVASPECT dwDrawAspect, CSize& rSize);
	//}}AFX_VIRTUAL

// Implementation
public:
	~CDrawSrvrItem();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SRVRITEM_H__3CB668A5_71B8_46D6_A91B_820E71C92457__INCLUDED_)
