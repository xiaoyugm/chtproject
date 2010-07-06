// DrawDoc.cpp : implementation of the CDrawDoc class
//

#include "stdafx.h"
#include "Draw.h"

#include "DrawDoc.h"
///#include "CntrItem.h"
#include "SrvrItem.h"

#include "drawview.h"
#include "drawobj.h"
///#include "cntritem.h"
///#include "summpage.h"
///#include "statpage.h"

#include "NewDocument.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDrawDoc

IMPLEMENT_DYNCREATE(CDrawDoc, COleServerDoc)

BEGIN_MESSAGE_MAP(CDrawDoc, COleServerDoc)
	//{{AFX_MSG_MAP(CDrawDoc)
	ON_COMMAND(ID_SETTING_PAGE_COLOR, OnSettingPageColor)
	ON_COMMAND(ID_SETTING_PAGE_SIZE, OnSettingPageSize)
	ON_COMMAND(ID_VIEW_PAPERCOLOR, OnViewPaperColor)
	//}}AFX_MSG_MAP
	// Enable default OLE container implementation
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE, COleServerDoc::OnUpdatePasteMenu)
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE_LINK, COleServerDoc::OnUpdatePasteLinkMenu)
///	ON_UPDATE_COMMAND_UI(ID_OLE_EDIT_CONVERT, COleServerDoc::OnUpdateObjectVerbMenu)
	ON_COMMAND(ID_OLE_EDIT_CONVERT, COleServerDoc::OnEditConvert)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CDrawDoc, COleServerDoc)
	//{{AFX_DISPATCH_MAP(CDrawDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//      DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_IDraw to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {D32EE3DB-3C97-4E00-B82A-65A7AA5D067D}
static const IID IID_IDraw =
{ 0xd32ee3db, 0x3c97, 0x4e00, { 0xb8, 0x2a, 0x65, 0xa7, 0xaa, 0x5d, 0x6, 0x7d } };

BEGIN_INTERFACE_MAP(CDrawDoc, COleServerDoc)
	INTERFACE_PART(CDrawDoc, IID_IDraw, Dispatch)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDrawDoc construction/destruction

CDrawDoc::CDrawDoc()
{
	// Use OLE compound files
	EnableCompoundFile();

	// TODO: add one-time construction code here

	EnableAutomation();

	AfxOleLockApp();

	m_nMapMode = MM_ANISOTROPIC;
	m_paperColor = RGB(255, 255, 255);
	ComputePageSize();
	m_size.cx = 941;
	m_size.cy = 593;
	strDocName = "";
	bIsNoInit = FALSE;
	m_nObjID = 1;

}

CDrawDoc::~CDrawDoc()
{
	AfxOleUnlockApp();
	POSITION pos = m_objects.GetHeadPosition();
	while (pos != NULL)
		delete m_objects.GetNext(pos);
}

BOOL CDrawDoc::OnNewDocument()
{
	//设置纸张的大小
	CNewDocument  newdlg;

	strDocName.Format("窗口_%d",theApp.m_nView);
	newdlg.m_strDocName = strDocName;
	newdlg.m_lHeight = m_size.cy;
	newdlg.m_lWidth = m_size.cx;
	if(newdlg.DoModal() != IDOK)
		return FALSE;

	theApp.m_nView += 1;
	SetSize(newdlg.m_lWidth, newdlg.m_lHeight);
	strDocName = newdlg.m_strDocName;

	CMainFrame *pMainFrame = (CMainFrame *)AfxGetApp()->m_pMainWnd;
	if(pMainFrame->m_wndTabDockBar.m_wndTreeCtrl.IsSameName(strDocName))
	{
		AfxMessageBox("窗口名称重复，请检查!");
		bIsNoInit = TRUE;
		return FALSE;
	}


	POSITION pos = GetFirstViewPosition();
	CDrawView *pView;
	while (pos != NULL)
		pView = (CDrawView*)GetNextView(pos);

	if(pView != NULL)
		pMainFrame->m_wndTabDockBar.m_wndTreeCtrl.InsertViewName(strDocName, pView);

	SetTitle(strDocName);						//设置窗口标题
	m_paperColor = newdlg.m_clrColor;			//背景颜色

	if (!COleDocument::OnNewDocument())
		return FALSE;

	// Security defaults to 0
	return TRUE;
}


BOOL CDrawDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	strDocName.Format("窗口_%d",theApp.m_nView);
	theApp.m_nView += 1;
	SetTitle(strDocName);

	CMainFrame *pMainFrame = (CMainFrame *)AfxGetApp()->m_pMainWnd;
	POSITION pos = GetFirstViewPosition();
	CDrawView *pView;
	while (pos != NULL)
		pView = (CDrawView*)GetNextView(pos);

	pMainFrame->m_wndTabDockBar.m_wndTreeCtrl.InsertViewName(strDocName, pView);

	return COleDocument::OnOpenDocument(lpszPathName);
}

BOOL CDrawDoc::OnSaveDocument(LPCTSTR lpszPathName)
{
	m_strPathName = lpszPathName;
	return COleDocument::OnSaveDocument(lpszPathName);
}
/////////////////////////////////////////////////////////////////////////////
// CDrawDoc server implementation

COleServerItem* CDrawDoc::OnGetEmbeddedItem()
{
	// OnGetEmbeddedItem is called by the framework to get the COleServerItem
	//  that is associated with the document.  It is only called when necessary.

	CDrawSrvrItem* pItem = new CDrawSrvrItem(this);
	ASSERT_VALID(pItem);
	return pItem;
}

void CDrawDoc::Draw(CDC* pDC, CDrawView* pView)
{
	POSITION pos = m_objects.GetHeadPosition();
	while (pos != NULL)
	{
		CDrawObj* pObj = m_objects.GetNext(pos);
		pObj->Draw(pDC);
		if (pView->m_bActive && !pDC->IsPrinting() && pView->IsSelected(pObj))
			pObj->DrawTracker(pDC, CDrawObj::selected);
	}
}

void CDrawDoc::Add(CDrawObj* pObj)
{
	pObj->m_ID = m_nObjID;
	m_nObjID ++;
	m_objects.AddTail(pObj);
	pObj->m_pDocument = this;
	SetModifiedFlag();
}

void CDrawDoc::Remove(CDrawObj* pObj)
{
	// Find and remove from document
	POSITION pos = m_objects.Find(pObj);
	if (pos != NULL)
		m_objects.RemoveAt(pos);
	// set document modified flag
	SetModifiedFlag();

	// call remove for each view so that the view can remove from m_selection
	pos = GetFirstViewPosition();
	while (pos != NULL)
		((CDrawView*)GetNextView(pos))->Remove(pObj);
}

// point is in logical coordinates
CDrawObj* CDrawDoc::ObjectAt(const CPoint& point)
{
	CRect rect(point, CSize(1, 1));
	POSITION pos = m_objects.GetTailPosition();
	while (pos != NULL)
	{
		CDrawObj* pObj = m_objects.GetPrev(pos);

		if (pObj->Intersects(rect))
			return pObj;
	}

	return NULL;
}

void CDrawDoc::ComputePageSize()
{
//	CSize new_size(850, 1100);  // 8.5" x 11" default

	CSize new_size = m_size;
	CPrintDialog dlg(FALSE);
	if (AfxGetApp()->GetPrinterDeviceDefaults(&dlg.m_pd))
	{
		// GetPrinterDC returns a HDC so attach it
		CDC dc;
		HDC hDC= dlg.CreatePrinterDC();
		ASSERT(hDC != NULL);
		dc.Attach(hDC);

		// Get the size of the page in loenglish
		new_size.cx = MulDiv(dc.GetDeviceCaps(HORZSIZE), 1000, 254);
		new_size.cy = MulDiv(dc.GetDeviceCaps(VERTSIZE), 1000, 254);
	}

	// if size changed then iterate over views and reset
	if (new_size != m_size)
	{
		m_size = new_size;
		POSITION pos = GetFirstViewPosition();
		while (pos != NULL)
			((CDrawView*)GetNextView(pos))->SetPageSize(m_size);
	}
}

void CDrawDoc::OnViewPaperColor()
{
	CColorDialog dlg;
	if (dlg.DoModal() != IDOK)
		return;

	m_paperColor = dlg.GetColor();
	SetModifiedFlag();
	UpdateAllViews(NULL);
}

/////////////////////////////////////////////////////////////////////////////
// CDrawDoc serialization

void CDrawDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		ar << m_paperColor;
		m_objects.Serialize(ar);
		ar << m_size.cx;
		ar << m_size.cy;
		ar << m_strPathName;
	}
	else
	{
		ar >> m_paperColor;
		m_objects.Serialize(ar);
		ar >> m_size.cx;
		ar >> m_size.cy;
		ar >> m_strPathName;
	}

	// Calling the base class COleServerDoc enables serialization
	//  of the container document's COleClientItem objects.
	COleServerDoc::Serialize(ar);
}

/////////////////////////////////////////////////////////////////////////////
// CDrawDoc diagnostics

#ifdef _DEBUG
void CDrawDoc::AssertValid() const
{
	COleServerDoc::AssertValid();
}

void CDrawDoc::Dump(CDumpContext& dc) const
{
	COleServerDoc::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDrawDoc commands

void CDrawDoc::OnSettingPageColor() 
{
	CColorDialog dlg;
	if (dlg.DoModal() != IDOK)
		return;

	m_paperColor = dlg.GetColor();
//	SetModifiedFlag();
	UpdateAllViews(NULL);	
}

void CDrawDoc::SetSize(int x, int y)
{
	m_size = CSize(x,y);
	POSITION pos = GetFirstViewPosition();
	while (pos != NULL)
		((CDrawView*)GetNextView(pos))->SetPageSize(m_size);
}

//设置绘图区大小
void CDrawDoc::OnSettingPageSize() 
{
	CNewDocument  newdlg;
	newdlg.m_strDocName = strDocName;
	newdlg.m_lHeight = m_size.cy;
	newdlg.m_lWidth = m_size.cx;
	if(newdlg.DoModal() != IDOK)
		return;
	SetSize(newdlg.m_lWidth, newdlg.m_lHeight);	


}


void CDrawDoc::OnCloseDocument() 
{
	if(!bIsNoInit)
	{
		CMainFrame *pMainFrame = (CMainFrame *)AfxGetApp()->m_pMainWnd;
		pMainFrame->m_wndTabDockBar.m_wndTreeCtrl.DeleteViewName(strDocName);
	}	
	COleServerDoc::OnCloseDocument();
}

