// CurveDoc.cpp : implementation of the CCurveDoc class
//

#include "stdafx.h"
#include "Curve.h"
#include "CurveDoc.h"

//#include "CurveView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCurveDoc

IMPLEMENT_DYNCREATE(CCurveDoc, CDocument)

BEGIN_MESSAGE_MAP(CCurveDoc, CDocument)
	//{{AFX_MSG_MAP(CCurveDoc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCurveDoc construction/destruction

CCurveDoc::CCurveDoc()
{
	m_pRtCurve = NULL;     //0129
}

CCurveDoc::~CCurveDoc()
{

}

BOOL CCurveDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	if(m_pRtCurve)
		delete m_pRtCurve;
	m_pRtCurve = new CRtCurve();

	return TRUE;

}



/////////////////////////////////////////////////////////////////////////////
// CCurveDoc serialization

void CCurveDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
	}
	else
	{
	}
	m_pRtCurve->Serialize(ar);    //0129
}

/////////////////////////////////////////////////////////////////////////////
// CCurveDoc diagnostics

#ifdef _DEBUG
void CCurveDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CCurveDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCurveDoc commands




void CCurveDoc::DeleteContents() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CDocument::DeleteContents();
}

BOOL CCurveDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;
	// TODO: Add your specialized creation code here
	return TRUE;
}

void CCurveDoc::OnCloseDocument() 
{
	// TODO: Add your specialized code here and/or call the base class
	if(m_pRtCurve)
		delete m_pRtCurve;
	m_pRtCurve = NULL;	
	CDocument::OnCloseDocument();
}
