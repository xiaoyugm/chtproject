// KJ86MonitorDoc.cpp : implementation of the CKJ86MonitorDoc class
//

#include "stdafx.h"
#include "KJMonitor.h"

#include "KJMonitorDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CKJ86MonitorDoc

IMPLEMENT_DYNCREATE(CKJMonitorDoc, CDocument)

BEGIN_MESSAGE_MAP(CKJMonitorDoc, CDocument)
	//{{AFX_MSG_MAP(CKJ86MonitorDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CKJ86MonitorDoc construction/destruction

CKJMonitorDoc::CKJMonitorDoc()
{
	// TODO: add one-time construction code here

}

CKJMonitorDoc::~CKJMonitorDoc()
{
}

BOOL CKJMonitorDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CKJ86MonitorDoc serialization

void CKJMonitorDoc::Serialize(CArchive& ar)
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
// CKJ86MonitorDoc diagnostics

#ifdef _DEBUG
void CKJMonitorDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CKJMonitorDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CKJ86MonitorDoc commands
