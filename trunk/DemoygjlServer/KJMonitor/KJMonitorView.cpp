// KJ86MonitorView.cpp : implementation of the CKJ86MonitorView class
//

#include "stdafx.h"
#include "KJMonitor.h"

#include "KJMonitorDoc.h"
#include "KJMonitorView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CKJ86MonitorView

IMPLEMENT_DYNCREATE(CKJMonitorView, CView)

BEGIN_MESSAGE_MAP(CKJMonitorView, CView)
	//{{AFX_MSG_MAP(CKJ86MonitorView)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CKJ86MonitorView construction/destruction

CKJMonitorView::CKJMonitorView()
{
	// TODO: add construction code here

}

CKJMonitorView::~CKJMonitorView()
{
}

BOOL CKJMonitorView::PreCreateWindow(CREATESTRUCT& cs)
{
	if (!CView::PreCreateWindow(cs))
		return FALSE;

	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CKJ86MonitorView drawing

void CKJMonitorView::OnDraw(CDC* pDC)
{
	CKJMonitorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CKJ86MonitorView printing

BOOL CKJMonitorView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CKJMonitorView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CKJMonitorView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CKJ86MonitorView diagnostics

#ifdef _DEBUG
void CKJMonitorView::AssertValid() const
{
	CView::AssertValid();
}

void CKJMonitorView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CKJMonitorDoc* CKJMonitorView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CKJMonitorDoc)));
	return (CKJMonitorDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CKJ86MonitorView message handlers

