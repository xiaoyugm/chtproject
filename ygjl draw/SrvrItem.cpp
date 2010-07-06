// SrvrItem.cpp : implementation of the CDrawSrvrItem class
//

#include "stdafx.h"
#include "Draw.h"

#include "DrawDoc.h"
#include "SrvrItem.h"
///#include "CntrItem.h"

#include "DrawObj.h"
#include "DrawRect.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDrawSrvrItem implementation

IMPLEMENT_DYNAMIC(CDrawSrvrItem, COleServerItem)

CDrawSrvrItem::CDrawSrvrItem(CDrawDoc* pContainerDoc)
	: COleServerItem(pContainerDoc, TRUE)
{
	// Initialize GDI+.
	GdiplusStartupInput gdiplusStartupInput;
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
}

CDrawSrvrItem::~CDrawSrvrItem()
{
	GdiplusShutdown(gdiplusToken);	
}

void CDrawSrvrItem::Serialize(CArchive& ar)
{
	// CDrawSrvrItem::Serialize will be called by the framework if
	//  the item is copied to the clipboard.  This can happen automatically
	//  through the OLE callback OnGetClipboardData.  A good default for
	//  the embedded item is simply to delegate to the document's Serialize
	//  function.  If you support links, then you will want to serialize
	//  just a portion of the document.

	if (!IsLinkedItem())
	{
		CDrawDoc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		pDoc->Serialize(ar);
	}
}

BOOL CDrawSrvrItem::OnGetExtent(DVASPECT dwDrawAspect, CSize& rSize)
{
	// Most applications, like this one, only handle drawing the content
	//  aspect of the item.  If you wish to support other aspects, such
	//  as DVASPECT_THUMBNAIL (by overriding OnDrawEx), then this
	//  implementation of OnGetExtent should be modified to handle the
	//  additional aspect(s).

	if (dwDrawAspect != DVASPECT_CONTENT)
		return COleServerItem::OnGetExtent(dwDrawAspect, rSize);

	// CDrawSrvrItem::OnGetExtent is called to get the extent in
	//  HIMETRIC units of the entire item.  The default implementation
	//  here simply returns a hard-coded number of units.

	CDrawDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: replace this arbitrary size

	rSize = CSize(3000, 3000);   // 3000 x 3000 HIMETRIC units

	return TRUE;
}

BOOL CDrawSrvrItem::OnDraw(CDC* pDC, CSize& rSize)
{
	// Remove this if you use rSize
	UNREFERENCED_PARAMETER(rSize);

	CDrawDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: set mapping mode and extent
	//  (The extent is usually the same as the size returned from OnGetExtent)
	pDC->SetMapMode(MM_ANISOTROPIC);
	pDC->SetWindowOrg(0,0);
	pDC->SetWindowExt(3000, 3000);

	// TODO: add drawing code here.  Optionally, fill in the HIMETRIC extent.
	//  All drawing takes place in the metafile device context (pDC).

// The following code draws the first item at an arbitrary position.

	// TODO: remove this code when your real drawing code is complete

/*	POSITION pos = pDoc->GetStartPosition();
	CDrawItem* pItem = (CDrawItem*)pDoc->GetNextClientItem(pos);
	if (pItem != NULL)
		pItem->Draw(pDC, CRect(10, 10, 1010, 1010));*/
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CDrawSrvrItem diagnostics

#ifdef _DEBUG
void CDrawSrvrItem::AssertValid() const
{
	COleServerItem::AssertValid();
}

void CDrawSrvrItem::Dump(CDumpContext& dc) const
{
	COleServerItem::Dump(dc);
}
#endif

/////////////////////////////////////////////////////////////////////////////
