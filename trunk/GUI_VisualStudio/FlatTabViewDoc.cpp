// FlatTabViewDoc.cpp : implementation of the CFlatTabViewDoc class
//

#include "stdafx.h"
#include "GUI_VisualStudio.h"
#include "FlatTabViewDoc.h"
#include "SampleFormView.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRViewDoc

IMPLEMENT_DYNCREATE(CRViewDoc, CDocument)

BEGIN_MESSAGE_MAP(CRViewDoc, CDocument)
	//{{AFX_MSG_MAP(CFlatTabViewDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRViewDoc construction/destruction

CRViewDoc::CRViewDoc()
{
}

CRViewDoc::~CRViewDoc()
{
}

BOOL CRViewDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	return CDocument::OnOpenDocument(lpszPathName);
}

BOOL CRViewDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	return TRUE;
}

BOOL CRViewDoc::OnSaveDocument(LPCTSTR lpszPathName)
{
	return CDocument::OnSaveDocument(lpszPathName);
}


/////////////////////////////////////////////////////////////////////////////
// CRViewDoc serialization

void CRViewDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CRViewDoc diagnostics

#ifdef _DEBUG
void CRViewDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CRViewDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CRViewDoc commands
void CRViewDoc::OnCloseDocument() 
{
	CDocument::OnCloseDocument();
//	CMainFrame* pFWnd=(CMainFrame*)AfxGetMainWnd();
//    pFWnd->OnCloseR();
}

void CRViewDoc::OnCloseD()
{
	CDocument::OnCloseDocument();
}

/////////////////////////////////////////////////////////////////////////////
// CFlatTabViewDoc

IMPLEMENT_DYNCREATE(CFlatTabViewDoc, CDocument)

BEGIN_MESSAGE_MAP(CFlatTabViewDoc, CDocument)
	//{{AFX_MSG_MAP(CFlatTabViewDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFlatTabViewDoc construction/destruction

CFlatTabViewDoc::CFlatTabViewDoc()
{
	// TODO: add one-time construction code here

}

CFlatTabViewDoc::~CFlatTabViewDoc()
{
}

BOOL CFlatTabViewDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
//0415
	POSITION pos = GetFirstViewPosition();
	CSampleFormView *psView;
	while (pos != NULL)
		psView = (CSampleFormView*)GetNextView(pos);
	
	if(psView != NULL)
	{
		theApp.m_Sam.SetAt(lpszPathName,psView);
	}
	return CDocument::OnOpenDocument(lpszPathName);
}

BOOL CFlatTabViewDoc::OnNewDocument()
{

	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)
	return TRUE;
}

BOOL CFlatTabViewDoc::OnSaveDocument(LPCTSTR lpszPathName)
{
	return CDocument::OnSaveDocument(lpszPathName);
}


/////////////////////////////////////////////////////////////////////////////
// CFlatTabViewDoc serialization

void CFlatTabViewDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CFlatTabViewDoc diagnostics

#ifdef _DEBUG
void CFlatTabViewDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CFlatTabViewDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CFlatTabViewDoc commands
void CFlatTabViewDoc::OnCloseDocument() 
{
	CString pString,strpo,strSQL;
	pString = GetTitle();
       		int m_ishave = pString.GetLength();
    		strpo = pString.Mid(m_ishave-3,3);
	if(strpo != "rsf")
	    pString += ".rsf";
	CString strrsy ,strrsy1;
	strrsy = gstrTimeOut + "\\" + strMetrics+ "rsy\\";
	pString = strrsy+pString;
	theApp.m_Sam.RemoveKey(pString);

    		for(vector<CString>::iterator iter=theApp.m_addfilesy.begin(); iter!=theApp.m_addfilesy.end(); )
			{
	    		strpo = *iter;
				if(strpo == pString)
				{
	        		iter = theApp.m_addfilesy.erase(iter);
				}
		    	else
			    	iter++;
			}
	CDocument::OnCloseDocument();
}
