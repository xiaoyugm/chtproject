// DrawView.cpp : implementation of the CDrawView class
//

#include "stdafx.h"
#include "Draw.h"

#include "DrawDoc.h"
///#include "CntrItem.h"
#include "DrawView.h"
#include "MainFrm.h"

#include "drawobj.h"
///#include "cntritem.h"
#include "drawtool.h"
#include "DrawRect.h"
#include "LineProperty.h"
#include "EffectDlg.h"
#include "drawrect.h"
#include <math.h>
#include "SetActionDlg.h"
///#include "CarSetDlg.h"

///#include "inifile.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BOOL  bIsBold = FALSE;				//是否为
BOOL  bIsItalic = FALSE;
BOOL  bIsUnderline = FALSE;
/////////////////////////////////////////////////////////////////////////////
// CDrawView

// private clipboard format (list of Draw objects)
CLIPFORMAT CDrawView::m_cfDraw = (CLIPFORMAT)
	::RegisterClipboardFormat(_T("MFC Draw"));
CLIPFORMAT CDrawView::m_cfObjectDescriptor = NULL;

IMPLEMENT_DYNCREATE(CDrawView, CScrollView)

BEGIN_MESSAGE_MAP(CDrawView, CScrollView)
	//{{AFX_MSG_MAP(CDrawView)
	ON_COMMAND(ID_CANCEL_EDIT, OnCancelEdit)
	ON_WM_DESTROY()
	ON_WM_SETFOCUS()
	ON_WM_SIZE()
///	ON_COMMAND(ID_CANCEL_EDIT_CNTR, OnCancelEditCntr)
///	ON_COMMAND(ID_CANCEL_EDIT_SRVR, OnCancelEditSrvr)
	ON_WM_LBUTTONDBLCLK()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_OBJECT_LINECOLOR, OnObjectLineColor)
	ON_COMMAND(ID_OBJECT_FILLCOLOR, OnObjectFillColor)
	ON_COMMAND(ID_OBJECT_MOVEFORWARD, OnObjectMoveForward)
	ON_COMMAND(ID_OBJECT_MOVEBACK, OnObjectMoveBack)
	ON_UPDATE_COMMAND_UI(ID_OBJECT_MOVEBACK, OnUpdateSingleSelect)
	ON_COMMAND(ID_EDIT_SELECT_ALL, OnEditSelectAll)
	ON_COMMAND(ID_EDIT_CLEAR, OnEditClear)
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_COMMAND(ID_EDIT_CUT, OnEditCut)
	ON_COMMAND(ID_EDIT_PASTE, OnEditPaste)
	ON_UPDATE_COMMAND_UI(ID_EDIT_COPY, OnUpdateEditCopy)
	ON_UPDATE_COMMAND_UI(ID_EDIT_CUT, OnUpdateEditCut)
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE, OnUpdateEditPaste)
	ON_UPDATE_COMMAND_UI(ID_EDIT_SELECT_ALL, OnUpdateEditSelectAll)
	ON_UPDATE_COMMAND_UI(ID_EDIT_CLEAR, OnUpdateAnySelect)
	ON_COMMAND(ID_VIEW_GRID, OnViewGrid)
	ON_UPDATE_COMMAND_UI(ID_VIEW_GRID, OnUpdateViewGrid)
///	ON_COMMAND(ID_VIEW_SHOWOBJECTS, OnViewShowobjects)
///	ON_UPDATE_COMMAND_UI(ID_VIEW_SHOWOBJECTS, OnUpdateViewShowobjects)
	ON_COMMAND(ID_TOOLBOXARROW, OnDrawSelect)
	ON_COMMAND(ID_TOOLBOXSOLIDROUNDRECT, OnDrawRoundRect)
	ON_COMMAND(ID_TOOLBOXSOLIDRECT, OnDrawRect)
	ON_COMMAND(ID_TOOLBOXLINE, OnDrawLine)
	ON_COMMAND(ID_TOOLBOXSOLIDOVAL, OnDrawEllipse)
	ON_UPDATE_COMMAND_UI(ID_TOOLBOXSOLIDOVAL, OnUpdateDrawEllipse)
	ON_UPDATE_COMMAND_UI(ID_TOOLBOXLINE, OnUpdateDrawLine)
	ON_UPDATE_COMMAND_UI(ID_TOOLBOXSOLIDRECT, OnUpdateDrawRect)
	ON_UPDATE_COMMAND_UI(ID_TOOLBOXSOLIDROUNDRECT, OnUpdateDrawRoundRect)
	ON_UPDATE_COMMAND_UI(ID_TOOLBOXARROW, OnUpdateDrawSelect)
	ON_COMMAND(ID_TOOLBOXSOLIDPOLYGON, OnDrawPolygon)
	ON_UPDATE_COMMAND_UI(ID_TOOLBOXSOLIDPOLYGON, OnUpdateDrawPolygon)
	ON_COMMAND(ID_TOOLBOXRECTANGLE, OnToolboxrectangle)
	ON_UPDATE_COMMAND_UI(ID_TOOLBOXRECTANGLE, OnUpdateToolboxrectangle)
	ON_COMMAND(ID_TOOLBOXOVAL, OnToolboxoval)
	ON_UPDATE_COMMAND_UI(ID_TOOLBOXOVAL, OnUpdateToolboxoval)
	ON_COMMAND(ID_TOOLBOXPOLYGON, OnToolboxpolygon)
	ON_UPDATE_COMMAND_UI(ID_TOOLBOXPOLYGON, OnUpdateToolboxpolygon)
	ON_COMMAND(ID_TOOLBOXBITMAP, OnToolboxbitmap)
	ON_COMMAND(ID_TOOLBOXBUTTON, OnToolboxbutton)
	ON_UPDATE_COMMAND_UI(ID_TOOLBOXBUTTON, OnUpdateToolboxbutton)
	ON_COMMAND(ID_TOOLBOXTEXT, OnToolboxtext)
	ON_UPDATE_COMMAND_UI(ID_TOOLBOXTEXT, OnUpdateToolboxtext)
	ON_COMMAND(ID_TOOLBOXWARN, OnToolboxwarn)
	ON_COMMAND(ID_TOOLBOX_ROUNDRECT_NOFILL, OnToolboxRoundrectNofill)
	ON_UPDATE_COMMAND_UI(ID_TOOLBOX_ROUNDRECT_NOFILL, OnUpdateToolboxRoundrectNofill)
	ON_COMMAND(ID_TOOLBOX_ARROW, OnToolboxArrow)
	ON_UPDATE_COMMAND_UI(ID_TOOLBOX_ARROW, OnUpdateToolboxArrow)
	ON_COMMAND(ID_DRAW_CURVE, OnDrawCurve)
	ON_UPDATE_COMMAND_UI(ID_DRAW_CURVE, OnUpdateDrawCurve)
	ON_COMMAND(ID_TOOLBOXCHORD, OnToolboxchord)
	ON_UPDATE_COMMAND_UI(ID_TOOLBOXCHORD, OnUpdateToolboxchord)
	ON_COMMAND(ID_TOOLBOXPIE, OnToolboxpie)
	ON_UPDATE_COMMAND_UI(ID_TOOLBOXPIE, OnUpdateToolboxpie)
	ON_COMMAND(ID_TOOLBOX_CONDUIT, OnToolboxConduit)
	ON_UPDATE_COMMAND_UI(ID_TOOLBOX_CONDUIT, OnUpdateToolboxConduit)
	ON_COMMAND(ID_UNIT_SAVE, OnUnitSave)
	ON_UPDATE_COMMAND_UI(ID_UNIT_SAVE, OnUpdateUnitSave)
	ON_COMMAND(ID_OBJECT_LOADSUB, OnObjectLoadsub)
	ON_COMMAND(ID_FORMATTING_BOLD, OnFormattingBold)
	ON_COMMAND(ID_FORMATTING_ITALIC, OnFormattingItalic)
	ON_COMMAND(ID_FORMATTING_UNDERLINE, OnFormattingUnderline)
	ON_COMMAND(ID_TOOLBOXREPORT, OnToolboxreport)
	ON_UPDATE_COMMAND_UI(ID_TOOLBOXREPORT, OnUpdateToolboxreport)
	ON_COMMAND(ID_TOOLBOX_BEELINE, OnToolboxBeeline)
	ON_UPDATE_COMMAND_UI(ID_TOOLBOX_BEELINE, OnUpdateToolboxBeeline)
	ON_COMMAND(ID_TOOLBOX_QIE, OnToolboxQie)
	ON_UPDATE_COMMAND_UI(ID_TOOLBOX_QIE, OnUpdateToolboxQie)
	ON_COMMAND(ID_PUPUP_LOCK, OnPupupLock)
	ON_UPDATE_COMMAND_UI(ID_PUPUP_LOCK, OnUpdatePupupLock)
	ON_COMMAND(ID_TOOLBOX_TIME_CURVE, OnToolboxTimeCurve)
	ON_WM_CREATE()
	ON_COMMAND(ID_POPUP_ACTION, OnPopupAction)
	ON_UPDATE_COMMAND_UI(ID_POPUP_ACTION, OnUpdatePopupAction)
	ON_COMMAND(ID_TOOLBOXSTROKE, OnToolboxstroke)
	ON_COMMAND(ID_INSERT_CAR, OnInsertCar)
	ON_COMMAND(ID_INSERT_ROTARY, OnInsertRotary)
	ON_UPDATE_COMMAND_UI(ID_OBJECT_MOVEFORWARD, OnUpdateSingleSelect)
	ON_UPDATE_COMMAND_UI(ID_TOOLBOXBITMAP, OnUpdateToolboxbitmap)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CScrollView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDrawView construction/destruction

CDrawView::CDrawView()
{
///	m_pSelection = NULL;

	m_bGrid = TRUE;
	m_gridColor = RGB(0, 0, 128);
	m_bActive = FALSE;
// new
	if( m_cfObjectDescriptor == NULL )
		m_cfObjectDescriptor = (CLIPFORMAT)::RegisterClipboardFormat(_T("Object Descriptor") );
	m_prevDropEffect = DROPEFFECT_NONE;
// end new	
	bLock = FALSE;
	m_bIsDraw = FALSE;
}

CDrawView::~CDrawView()
{
}

// The following command handler provides the standard keyboard
//  user interface to cancel an in-place editing session.
void CDrawView::OnCancelEdit()
{
	// deactivate any in-place active item on this view!
	COleClientItem* pActiveItem = GetDocument()->GetInPlaceActiveItem(this);
	if (pActiveItem != NULL)
	{
		// if we found one, deactivate it
		pActiveItem->Close();
	}
	ASSERT(GetDocument()->GetInPlaceActiveItem(this) == NULL);

	// escape also brings us back into select mode
	ReleaseCapture();

	CDrawTool* pTool = CDrawTool::FindTool(CDrawTool::c_drawShape);
	if (pTool != NULL)
		pTool->OnCancel();

	CDrawTool::c_drawShape = selection;
	m_bIsDraw = FALSE;
}

BOOL CDrawView::PreCreateWindow(CREATESTRUCT& cs)
{
	if (!CScrollView::PreCreateWindow(cs))
		return FALSE;

	ASSERT(cs.style & WS_CHILD);
	if (cs.lpszClass == NULL)
		cs.lpszClass = AfxRegisterWndClass(CS_DBLCLKS);
	return TRUE;
}

void CDrawView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView) 
{
	CScrollView::OnActivateView(bActivate, pActivateView, pDeactiveView);
	// invalidate selections when active status changes
	if (m_bActive != bActivate)
	{
		if (bActivate)  // if becoming active update as if active
			m_bActive = bActivate;
		if (!m_selection.IsEmpty())
			OnUpdate(NULL, HINT_UPDATE_SELECTION, NULL);
		m_bActive = bActivate;
	}

}

/////////////////////////////////////////////////////////////////////////////
// CDrawView drawing
void CDrawView::InvalObj(CDrawObj* pObj)
{
	CRect rect = pObj->m_position;
	DocToClient(rect);
	if (m_bActive && IsSelected(pObj))
	{
		rect.left -= 18;
		rect.top -= 20;
		rect.right += 20;
		rect.bottom += 18;
	}
	rect.InflateRect(1, 1); // handles CDrawOleObj objects

	InvalidateRect(rect, FALSE);
}

void CDrawView::InvalRouteObj(CDrawObj* pObj)
{
	CRect rect = pObj->m_position;
	DocToClient(rect);
	rect.NormalizeRect();
	int nMax = max(rect.Height(),rect.Width())/2;
	int nMin = min(rect.Height(),rect.Width())/2;
	int nHypotenuse = sqrt(nMax * nMax + nMin * nMin);

		rect.left = rect.left-nHypotenuse+rect.Width()/2;
		rect.top = rect.top -nHypotenuse+rect.Height()/2 ;
		rect.right = rect.right + nHypotenuse+rect.Width()/2;
		rect.bottom += nHypotenuse+rect.Height()/2;

	rect.InflateRect(1, 1); // handles CDrawOleObj objects

	InvalidateRect(rect, FALSE);
}

void CDrawView::InvalMoveObj(CDrawObj* pObj)   //0413
{

}

void CDrawView::OnUpdate(CView* , LPARAM lHint, CObject* pHint)
{
	switch (lHint)
	{
	case HINT_UPDATE_WINDOW:    // redraw entire window
		Invalidate(FALSE);
		break;

	case HINT_UPDATE_DRAWOBJ:   // a single object has changed
		InvalObj((CDrawObj*)pHint);
		break;

	case HINT_UPDATE_ROUTE:
		InvalRouteObj((CDrawObj*)pHint);
		break;

	case HINT_UPDATE_SELECTION: // an entire selection has changed
		{
			CDrawObjList* pList = pHint != NULL ?
				(CDrawObjList*)pHint : &m_selection;
			POSITION pos = pList->GetHeadPosition();
			while (pos != NULL)
				InvalObj(pList->GetNext(pos));
		}
		break;

	case HINT_DELETE_SELECTION: // an entire selection has been removed
		if (pHint != &m_selection)
		{
			CDrawObjList* pList = (CDrawObjList*)pHint;
			POSITION pos = pList->GetHeadPosition();
			while (pos != NULL)
			{
				CDrawObj* pObj = pList->GetNext(pos);
				InvalObj(pObj);
				Remove(pObj);   // remove it from this view's selection
			}
		}
		break;

/*	case HINT_UPDATE_OLE_ITEMS:
		{
			CDrawDoc* pDoc = GetDocument();
			POSITION pos = pDoc->GetObjects()->GetHeadPosition();
			while (pos != NULL)
			{
				CDrawObj* pObj = pDoc->GetObjects()->GetNext(pos);
///				if (pObj->IsKindOf(RUNTIME_CLASS(CDrawOleObj)))
///					InvalObj(pObj);
			}
		}
		break;*/

	default:
		ASSERT(FALSE);
		break;
	}
}

void CDrawView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo) 
{
	CScrollView::OnPrepareDC(pDC, pInfo);

	pDC->SetMapMode(MM_ANISOTROPIC);
	pDC->SetViewportExt(pDC->GetDeviceCaps(LOGPIXELSX),
		pDC->GetDeviceCaps(LOGPIXELSY));
	pDC->SetWindowExt(100, -100);

	// set the origin of the coordinate system to the center of the page
	CPoint ptOrg;
	ptOrg.x = GetDocument()->GetSize().cx / 2;
	ptOrg.y = GetDocument()->GetSize().cy / 2;

	// ptOrg is in logical coordinates
	pDC->OffsetWindowOrg(-ptOrg.x,ptOrg.y);
}

BOOL CDrawView::OnScrollBy(CSize sizeScroll, BOOL bDoScroll) 
{
	if (!CScrollView::OnScrollBy(sizeScroll, bDoScroll))
		return FALSE;

	// update the position of any in-place active item
	if (bDoScroll)
	{
		UpdateActiveItem();
		UpdateWindow();
	}
	return TRUE;
}

void CDrawView::OnDraw(CDC* pDC)
{
	CDrawDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	CDC dc;
	CDC* pDrawDC = pDC;
	CBitmap bitmap;
	CBitmap* pOldBitmap = 0;

	// only paint the rect that needs repainting
	CRect client;
	pDC->GetClipBox(client);
	CRect rect = client;
	DocToClient(rect);

	if (!pDC->IsPrinting())
	{
		// draw to offscreen bitmap for fast looking repaints
		if (dc.CreateCompatibleDC(pDC))
		{
			if (bitmap.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height()))
			{
				OnPrepareDC(&dc, NULL);
				pDrawDC = &dc;

				// offset origin more because bitmap is just piece of the whole drawing
				dc.OffsetViewportOrg(-rect.left, -rect.top);
				pOldBitmap = dc.SelectObject(&bitmap);
				dc.SetBrushOrg(rect.left % 8, rect.top % 8);

				// might as well clip to the same rectangle
				dc.IntersectClipRect(client);
			}
		}
	}

	// paint background
	CBrush brush;
	if (!brush.CreateSolidBrush(pDoc->GetPaperColor()))
		return;

	brush.UnrealizeObject();
	pDrawDC->FillRect(client, &brush);

	if (!pDC->IsPrinting() && m_bGrid)
		DrawGrid(pDrawDC);

	pDoc->Draw(pDrawDC, this);

	if (pDrawDC != pDC)
	{
		pDC->SetViewportOrg(0, 0);
		pDC->SetWindowOrg(0,0);
		pDC->SetMapMode(MM_TEXT);
		dc.SetViewportOrg(0, 0);
		dc.SetWindowOrg(0,0);
		dc.SetMapMode(MM_TEXT);
		pDC->BitBlt(rect.left, rect.top, rect.Width(), rect.Height(),
			&dc, 0, 0, SRCCOPY);
		dc.SelectObject(pOldBitmap);
	}
}

void CDrawView::Remove(CDrawObj* pObj)
{
	POSITION pos = m_selection.Find(pObj);
	if (pos != NULL)
		m_selection.RemoveAt(pos);
}

void CDrawView::PasteNative(COleDataObject& dataObject)
{
	// get file refering to clipboard data
	CFile* pFile = dataObject.GetFileData(m_cfDraw);
	if (pFile == NULL)
		return;

	// connect the file to the archive
	CArchive ar(pFile, CArchive::load);
	TRY
	{
		ar.m_pDocument = GetDocument(); // set back-pointer in archive

		// read the selection
		m_selection.Serialize(ar);
	}
	CATCH_ALL(e)
	{
		ar.Close();
		delete pFile;
		THROW_LAST();
	}
	END_CATCH_ALL

	ar.Close();
	delete pFile;
}
/*
void CDrawView::PasteEmbedded(COleDataObject& dataObject, CPoint point )
{
	BeginWaitCursor();

	// paste embedded
	CDrawOleObj* pObj = new CDrawOleObj(GetInitialPosition());
	ASSERT_VALID(pObj);
	CDrawItem* pItem = new CDrawItem(GetDocument(), pObj);
	ASSERT_VALID(pItem);
	pObj->m_pClientItem = pItem;

	TRY
	{
		if (!pItem->CreateFromData(&dataObject) &&
			!pItem->CreateStaticFromData(&dataObject))
		{
			AfxThrowMemoryException();      // any exception will do
		}

		// add the object to the document
		GetDocument()->Add(pObj);
		m_selection.AddTail(pObj);
		ClientToDoc( point );
		pObj->MoveTo( CRect( point, pObj->m_extent ), this );

		// try to get initial presentation data
		pItem->UpdateLink();
		pItem->UpdateExtent();
	}
	CATCH_ALL(e)
	{
		// clean up item
		pItem->Delete();
		pObj->m_pClientItem = NULL;
		GetDocument()->Remove(pObj);
		pObj->Remove();

		AfxMessageBox(IDP_FAILED_TO_CREATE);
	}
	END_CATCH_ALL

	EndWaitCursor();
}
*/
void CDrawView::DrawGrid(CDC* pDC)
{
	CDrawDoc* pDoc = GetDocument();

	COLORREF oldBkColor = pDC->SetBkColor(pDoc->GetPaperColor());

	CRect rect;
	rect.left = -pDoc->GetSize().cx / 2 + 60;
	rect.top = -pDoc->GetSize().cy / 2 -60;
	rect.right = pDoc->GetSize().cx /2 + 60 ;
	rect.bottom = pDoc->GetSize().cy /2 -60 ;

	// Center lines
	CPen penDash;
	penDash.CreatePen(PS_DASH, 1, m_gridColor);
	CPen* pOldPen = pDC->SelectObject(&penDash);

	pDC->MoveTo(60, rect.top);
	pDC->LineTo(60, rect.bottom);
	pDC->MoveTo(rect.left, -60);
	pDC->LineTo(rect.right, -60);

	// Major unit lines
	CPen penDot;
//	penDot.CreatePen(PS_DOT, 1, m_gridColor);
	penDot.CreatePen(PS_DOT, 1, RGB(128,128,128));
	pDC->SelectObject(&penDot);

	for (int x = rect.left / 20 * 20; x < rect.right; x += 20)
	{
		if (x != 60)
		{
			pDC->MoveTo(x, rect.top);
			pDC->LineTo(x, rect.bottom);
		}
	}

	for (int y = rect.top / 20 * 20; y < rect.bottom; y += 20)
	{
		if (y != -60)
		{
			pDC->MoveTo(rect.left, y);
			pDC->LineTo(rect.right, y);
		}
	}

	// Outlines
	CPen penSolid;
	penSolid.CreatePen(PS_SOLID, 1, m_gridColor);
	pDC->SelectObject(&penSolid);
	pDC->MoveTo(rect.left, rect.top);
	pDC->LineTo(rect.right, rect.top);
	pDC->LineTo(rect.right, rect.bottom);
	pDC->LineTo(rect.left, rect.bottom);
	pDC->LineTo(rect.left, rect.top);

	pDC->SelectObject(pOldPen);
	pDC->SetBkColor(oldBkColor);
}

void CDrawView::OnInitialUpdate()
{
	CSize size = GetDocument()->GetSize();
	CClientDC dc(NULL);
	size.cx = MulDiv(size.cx, dc.GetDeviceCaps(LOGPIXELSX), 100);
	size.cy = MulDiv(size.cy, dc.GetDeviceCaps(LOGPIXELSY), 100);
	size.cx = size.cx + 100;
	size.cy = size.cy + 100;
	SetScrollSizes(MM_TEXT, size);
}

void CDrawView::SetPageSize(CSize size)
{
	CClientDC dc(NULL);
	size.cx = MulDiv(size.cx, dc.GetDeviceCaps(LOGPIXELSX), 100);
	size.cy = MulDiv(size.cy, dc.GetDeviceCaps(LOGPIXELSY), 100);
	size.cx = size.cx + 100;
	size.cy = size.cy + 100;
	SetScrollSizes(MM_TEXT, size);
	GetDocument()->UpdateAllViews(NULL, HINT_UPDATE_WINDOW, NULL);
}

/////////////////////////////////////////////////////////////////////////////
// CDrawView printing

void CDrawView::OnPrint(CDC* pDC, CPrintInfo* pInfo) 
{
///	if (pInfo->m_bPreview == FALSE)
///		((CDrawDoc*)GetDocument())->m_pSummInfo->RecordPrintDate();
	OnDraw(pDC);
}


BOOL CDrawView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CDrawView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	CScrollView::OnBeginPrinting(pDC,pInfo);

	// check page size -- user could have gone into print setup
	// from print dialog and changed paper or orientation
	GetDocument()->ComputePageSize();
}

void CDrawView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CDrawView::OnDestroy()
{
	CScrollView::OnDestroy();

	// deactivate the inplace active item on this view
	COleClientItem* pActiveItem = GetDocument()->GetInPlaceActiveItem(this);
	if (pActiveItem != NULL && pActiveItem->GetActiveView() == this)
	{
		pActiveItem->Deactivate();
		ASSERT(GetDocument()->GetInPlaceActiveItem(this) == NULL);
	}
}


/////////////////////////////////////////////////////////////////////////////
// OLE Client support and commands

BOOL CDrawView::IsSelected(const CObject* pDocItem) const
{
	CDrawObj* pDrawObj = (CDrawObj*)pDocItem;
///	if (pDocItem->IsKindOf(RUNTIME_CLASS(CDrawItem)))
///		pDrawObj = ((CDrawItem*)pDocItem)->m_pDrawObj;
	return m_selection.Find(pDrawObj) != NULL;

	//return pDocItem == m_pSelection;
}
/*
// The following command handler provides the standard keyboard
//  user interface to cancel an in-place editing session.  Here,
//  the container (not the server) causes the deactivation.
void CDrawView::OnCancelEditCntr()
{
	// Close any in-place active item on this view.
	COleClientItem* pActiveItem = GetDocument()->GetInPlaceActiveItem(this);
	if (pActiveItem != NULL)
	{
		pActiveItem->Close();
	}
	ASSERT(GetDocument()->GetInPlaceActiveItem(this) == NULL);
}

// Special handling of OnSetFocus and OnSize are required for a container
//  when an object is being edited in-place.
void CDrawView::OnSetFocus(CWnd* pOldWnd)
{
	COleClientItem* pActiveItem = GetDocument()->GetInPlaceActiveItem(this);
	if (pActiveItem != NULL &&
		pActiveItem->GetItemState() == COleClientItem::activeUIState)
	{
		// need to set focus to this item if it is in the same view
		CWnd* pWnd = pActiveItem->GetInPlaceWindow();
		if (pWnd != NULL)
		{
			pWnd->SetFocus();   // don't call the base class
			return;
		}
	}

	CScrollView::OnSetFocus(pOldWnd);
}

void CDrawView::OnSize(UINT nType, int cx, int cy)
{
	CScrollView::OnSize(nType, cx, cy);
//	COleClientItem* pActiveItem = GetDocument()->GetInPlaceActiveItem(this);
//	if (pActiveItem != NULL)
//		pActiveItem->SetItemRects();
	UpdateActiveItem();
}

/////////////////////////////////////////////////////////////////////////////
// OLE Server support

// The following command handler provides the standard keyboard
//  user interface to cancel an in-place editing session.  Here,
//  the server (not the container) causes the deactivation.
void CDrawView::OnCancelEditSrvr()
{
	GetDocument()->OnDeactivateUI(FALSE);
}
*/
/////////////////////////////////////////////////////////////////////////////
// CDrawView diagnostics

#ifdef _DEBUG
void CDrawView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CDrawView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CDrawDoc* CDrawView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDrawDoc)));
	return (CDrawDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// 自定义函数
CRect CDrawView::GetInitialPosition()
{
	CRect rect(10, 10, 10, 10);
	ClientToDoc(rect);
	return rect;
}

void CDrawView::ClientToDoc(CPoint& point)
{
	CClientDC dc(this);
	OnPrepareDC(&dc, NULL);
	dc.DPtoLP(&point);
}

void CDrawView::ClientToDoc(CRect& rect)
{
	CClientDC dc(this);
	OnPrepareDC(&dc, NULL);
	dc.DPtoLP(rect);
	ASSERT(rect.left <= rect.right);
	ASSERT(rect.bottom <= rect.top);
}

void CDrawView::DocToClient(CPoint& point)
{
	CClientDC dc(this);
	OnPrepareDC(&dc, NULL);
	dc.LPtoDP(&point);
}

void CDrawView::DocToClient(CRect& rect)
{
	CClientDC dc(this);
	OnPrepareDC(&dc, NULL);
	dc.LPtoDP(rect);
	rect.NormalizeRect();
}

void CDrawView::Select(CDrawObj* pObj, BOOL bAdd)
{
	if (!bAdd)
	{
		OnUpdate(NULL, HINT_UPDATE_SELECTION, NULL);
		m_selection.RemoveAll();
	}

	if (pObj == NULL || IsSelected(pObj))
		return;

	if(pObj->m_strGroupName.GetLength() > 0 && !pObj->m_bIsGroup)
	{
		m_selection.AddHead(pObj);
	}
	else
	{
		if(pObj->m_strUnitName.GetLength() > 0 && !pObj->m_bIsUnit)
			m_selection.AddHead(pObj);
		else
			m_selection.AddTail(pObj);
	}


	InvalObj(pObj);
}

void CDrawView::SelectGroup(CDrawObj* pObj)
{
	if(pObj == NULL)
		return;
	m_selection.RemoveAll();

	//枚举所有的OBJECT
	CDrawObjList *ObjectAll = GetDocument()->GetObjects();
	POSITION pos = ObjectAll->GetHeadPosition();
	while(pos != NULL)
	{
		CDrawObj* Obj = ObjectAll->GetNext(pos);
//		if(Obj->m_bIsGroup)
			if(Obj->m_strGroupName == pObj->m_strGroupName)
				Select(Obj,TRUE);
	}
}

void CDrawView::SelectUnit(CDrawObj* pObj)
{
	if(pObj == NULL)
		return;
	m_selection.RemoveAll();

	//枚举所有的OBJECT
	CDrawObjList *ObjectAll = GetDocument()->GetObjects();
	POSITION pos = ObjectAll->GetHeadPosition();
	while(pos != NULL)
	{
		CDrawObj* Obj = ObjectAll->GetNext(pos);
//		if(Obj->m_bIsGroup)
			if(Obj->m_strUnitName  == pObj->m_strUnitName )
				Select(Obj,TRUE);
	}
}


// rect is in device coordinates
void CDrawView::SelectWithinRect(CRect rect, BOOL bAdd)
{
	if (!bAdd)
		Select(NULL);

	ClientToDoc(rect);

	CDrawObjList* pObList = GetDocument()->GetObjects();
	POSITION posObj = pObList->GetHeadPosition();
	while (posObj != NULL)
	{
		CDrawObj* pObj = pObList->GetNext(posObj);
		if (pObj->Intersects(rect))
		{
			Select(pObj, TRUE);
		}
	}
}

void CDrawView::Deselect(CDrawObj* pObj)
{
	POSITION pos = m_selection.Find(pObj);
	if (pos != NULL)
	{
		InvalObj(pObj);
		m_selection.RemoveAt(pos);
	}
}

void CDrawView::CloneSelection()
{
	POSITION pos = m_selection.GetHeadPosition();
	while (pos != NULL)
	{
		CDrawObj* pObj = m_selection.GetNext(pos);
		pObj->Clone(pObj->m_pDocument);
			// copies object and adds it to the document
	}
}

void CDrawView::UpdateActiveItem()
{
	COleClientItem* pActiveItem = GetDocument()->GetInPlaceActiveItem(this);
	if (pActiveItem != NULL &&
		pActiveItem->GetItemState() == COleClientItem::activeUIState)
	{
		// this will update the item rectangles by calling
		//  OnGetPosRect & OnGetClipRect.
		pActiveItem->SetItemRects();
	}
}

BOOL CDrawView::GetObjectInfo(COleDataObject* pDataObject,
	CSize* pSize, CSize* pOffset)
{
	ASSERT(pSize != NULL);

	// get object descriptor data
	HGLOBAL hObjDesc = pDataObject->GetGlobalData(m_cfObjectDescriptor);
	if (hObjDesc == NULL)
	{
		if (pOffset != NULL)
			*pOffset = CSize(0, 0); // fill in defaults instead
		*pSize = CSize(0, 0);
		return FALSE;
	}
	ASSERT(hObjDesc != NULL);

	// otherwise, got CF_OBJECTDESCRIPTOR ok.  Lock it down and extract size.
	LPOBJECTDESCRIPTOR pObjDesc = (LPOBJECTDESCRIPTOR)GlobalLock(hObjDesc);
	ASSERT(pObjDesc != NULL);
	pSize->cx = (int)pObjDesc->sizel.cx;
	pSize->cy = (int)pObjDesc->sizel.cy;
	if (pOffset != NULL)
	{
		pOffset->cx = (int)pObjDesc->pointl.x;
		pOffset->cy = (int)pObjDesc->pointl.y;
	}
	GlobalUnlock(hObjDesc);
	GlobalFree(hObjDesc);

	// successfully retrieved pSize & pOffset info
	return TRUE;
}

//设置组属性
void CDrawView::SetGroupProperty(CString strName, double Height, double Width, CRect oldRect)
{
	POSITION pos = m_selection.GetHeadPosition();
	oldRect.NormalizeRect();
	while (pos != NULL)
	{
		CDrawObj* pObj = m_selection.GetNext(pos);
		pObj->m_strGroupName = strName;
		CRect rect = pObj->m_position;
		rect.NormalizeRect();
		int nWidth = rect.Width();
		int nHeight = rect.Height();
		
		rect.top  = oldRect.top - (oldRect.top-rect.top)*Height;
		rect.left  = oldRect.left - (oldRect.left-rect.left)*Width;
		rect.right = rect.left+nWidth*Width;
		rect.bottom = rect.top +nHeight*Height;
		rect.NormalizeRect();
		pObj->m_position = rect;
	}
	GetDocument()->SetModifiedFlag();
	GetDocument()->UpdateAllViews(NULL);		
}

void CDrawView::SetUnitProperty(CString strName, double Height, double Width, CRect oldRect)
{
	POSITION pos = m_selection.GetHeadPosition();
	oldRect.NormalizeRect();
	while (pos != NULL)
	{
		CDrawObj* pObj = m_selection.GetNext(pos);
		pObj->m_strUnitName = strName;
		CRect rect = pObj->m_position;
		rect.NormalizeRect();
		int nWidth = rect.Width();
		int nHeight = rect.Height();
		
		rect.top  = oldRect.top - (oldRect.top-rect.top)*Height;
		rect.left  = oldRect.left - (oldRect.left-rect.left)*Width;
		rect.right = rect.left+nWidth*Width;
		rect.bottom = rect.top +nHeight*Height;
		rect.NormalizeRect();
		pObj->m_position = rect;
	}
	GetDocument()->SetModifiedFlag();
	GetDocument()->UpdateAllViews(NULL);		
}

/////////////////////////////////////////////////////////////////////////////
// CDrawView message handlers

void CDrawView::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (!m_bActive)
	{
		return;
	}		

	CDrawTool* pTool = CDrawTool::FindTool(CDrawTool::c_drawShape);
	if (pTool != NULL)
		pTool->OnLButtonDown(this, nFlags, point);
}

void CDrawView::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (!m_bActive)
		return;
	CDrawTool* pTool = CDrawTool::FindTool(CDrawTool::c_drawShape);
	if (pTool != NULL)
		pTool->OnLButtonUp(this, nFlags, point);
}

void CDrawView::OnMouseMove(UINT nFlags, CPoint point)
{
	CMainFrame* pMainFrame=(CMainFrame*)::AfxGetMainWnd();
	pMainFrame->SetMousePosText(point,point);

	if (!m_bActive)
		return;

	POSITION pos = m_selection.GetHeadPosition();            //判断对象是否锁定
	while(pos != NULL)
	{
		CDrawObj * pObj = m_selection.GetNext(pos);
		if(pObj->m_bLock)
			return;
	}	

	CDrawTool* pTool = CDrawTool::FindTool(CDrawTool::c_drawShape);
	if (pTool != NULL)
		pTool->OnMouseMove(this, nFlags, point);
}

void CDrawView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	if (!m_bActive)
		return;
	CDrawTool* pTool = CDrawTool::FindTool(CDrawTool::c_drawShape);
	if (pTool != NULL)
		pTool->OnLButtonDblClk(this, nFlags, point);

}

DROPEFFECT CDrawView::OnDragEnter(COleDataObject* pDataObject,
	DWORD grfKeyState, CPoint point)
{
	ASSERT(m_prevDropEffect == DROPEFFECT_NONE);
	m_bDragDataAcceptable = FALSE;
	if (!COleClientItem::CanCreateFromData(pDataObject))
		return DROPEFFECT_NONE;

	m_bDragDataAcceptable = TRUE;
	GetObjectInfo(pDataObject, &m_dragSize, &m_dragOffset);
	CClientDC dc(NULL);
	dc.HIMETRICtoDP(&m_dragSize);
	dc.HIMETRICtoDP(&m_dragOffset);

	return OnDragOver(pDataObject, grfKeyState, point);
}

DROPEFFECT CDrawView::OnDragOver(COleDataObject*,
	DWORD grfKeyState, CPoint point)
{
	if(m_bDragDataAcceptable == FALSE)
		return DROPEFFECT_NONE;

	point -= m_dragOffset;  // adjust target rect by original cursor offset

	// check for point outside logical area -- i.e. in hatched region
	// GetTotalSize() returns the size passed to SetScrollSizes
	CRect rectScroll(CPoint(0, 0), GetTotalSize());

	CRect rectItem(point,m_dragSize);
	rectItem.OffsetRect(GetDeviceScrollPosition());

	DROPEFFECT de = DROPEFFECT_NONE;
	CRect rectTemp;
	if (rectTemp.IntersectRect(rectScroll, rectItem))
	{
		// check for force link
		if ((grfKeyState & (MK_CONTROL|MK_SHIFT)) == (MK_CONTROL|MK_SHIFT))
			de = DROPEFFECT_NONE; // Draw isn't a linking container
		// check for force copy
		else if ((grfKeyState & MK_CONTROL) == MK_CONTROL)
			de = DROPEFFECT_COPY;
		// check for force move
		else if ((grfKeyState & MK_ALT) == MK_ALT)
			de = DROPEFFECT_MOVE;
		// default -- recommended action is move
		else
			de = DROPEFFECT_MOVE;
	}

	if (point == m_dragPoint)
		return de;

	// otherwise, cursor has moved -- need to update the drag feedback
	CClientDC dc(this);
	if (m_prevDropEffect != DROPEFFECT_NONE)
	{
		// erase previous focus rect
		dc.DrawFocusRect(CRect(m_dragPoint, m_dragSize));
	}
	m_prevDropEffect = de;
	if (m_prevDropEffect != DROPEFFECT_NONE)
	{
		m_dragPoint = point;
		dc.DrawFocusRect(CRect(point, m_dragSize));
	}
	return de;
}

BOOL CDrawView::OnDrop(COleDataObject* pDataObject,
	DROPEFFECT /*dropEffect*/, CPoint point)
{
	ASSERT_VALID(this);

	// clean up focus rect
	OnDragLeave();

	// offset point as appropriate for dragging
	GetObjectInfo(pDataObject, &m_dragSize, &m_dragOffset);
	CClientDC dc(NULL);
	dc.HIMETRICtoDP(&m_dragSize);
	dc.HIMETRICtoDP(&m_dragOffset);
	point -= m_dragOffset;

	// invalidate current selection since it will be deselected
	OnUpdate(NULL, HINT_UPDATE_SELECTION, NULL);
	m_selection.RemoveAll();
///	if (m_bDragDataAcceptable)
///		PasteEmbedded(*pDataObject, point);

	// update the document and views
	GetDocument()->SetModifiedFlag();
	GetDocument()->UpdateAllViews(NULL, 0, NULL);      // including this view

	return TRUE;
}

void CDrawView::OnDragLeave()
{
	CClientDC dc(this);
	if (m_prevDropEffect != DROPEFFECT_NONE)
	{
		dc.DrawFocusRect(CRect(m_dragPoint,m_dragSize)); // erase previous focus rect
		m_prevDropEffect = DROPEFFECT_NONE;
	}
}

void CDrawView::OnContextMenu(CWnd* pWnd, CPoint point) 
{
	// make sure window is active
	GetParentFrame()->ActivateFrame();

	CPoint local = point;
	ScreenToClient(&local);
	ClientToDoc(local);

	CDrawObj* pObj;
	pObj = GetDocument()->ObjectAt(local);
	if(pObj != NULL)
	{
		if(!IsSelected(pObj))
			Select( pObj, FALSE );          // reselect item if appropriate
		UpdateWindow();

		CMenu menu;
		if (menu.LoadMenu(ID_POPUP_MENU))
		{
			CMenu* pPopup = menu.GetSubMenu(0);
			ASSERT(pPopup != NULL);

			pPopup->TrackPopupMenu(TPM_RIGHTBUTTON | TPM_LEFTALIGN,
								   point.x, point.y,
								   AfxGetMainWnd()); // route commands through main window
		}
	}
}

void CDrawView::OnObjectFillColor()
{
	CColorDialog dlg;
	if (dlg.DoModal() != IDOK)
		return;

	COLORREF color = dlg.GetColor();

	POSITION pos = m_selection.GetHeadPosition();
	while (pos != NULL)
	{
		CDrawObj* pObj = m_selection.GetNext(pos);
		pObj->SetFillColor(color);
	}
}

void CDrawView::OnObjectLineColor()
{
	CColorDialog dlg;
	if (dlg.DoModal() != IDOK)
		return;

	COLORREF color = dlg.GetColor();

	POSITION pos = m_selection.GetHeadPosition();
	while (pos != NULL)
	{
		CDrawObj* pObj = m_selection.GetNext(pos);
		pObj->SetLineColor(color);
	}
}

//另存为子图
void CDrawView::OnUnitSave() 
{
	static char szFilter[] = "子图文件 (*.sub)|*.sub||";
	CFileDialog subdlg(FALSE,NULL,NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,szFilter,NULL);
	if(subdlg.DoModal() == IDOK)
	{
		CFile file;
		CString ext = subdlg.GetPathName();
		if(ext.Right(4).CompareNoCase(_T(".sub")) != 0)
			ext += ".sub";

		if(!file.Open(ext,CFile::modeCreate | CFile::modeWrite))
		{
			#ifdef _DEBUG
				afxDump << "Unable to open file" << "\n";
				exit( 1 );
			#endif
		}
		CArchive ar(&file, CArchive::store);
		
		// Serialize selected objects to the archive

		m_selection.Serialize(ar);
		if(ar.IsStoring())
			AfxMessageBox("子图存储完成!");
		ar.Close();
		file.Close();
	}
}

//加载子图
void CDrawView::OnObjectLoadsub() 
{
	static char szFilter[] = "子图文件 (*.sub)|*.sub||";
	CFileDialog subdlg(TRUE,NULL,NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,szFilter,NULL);
	if(subdlg.DoModal() == IDOK)
	{
		CFile file;
		if(!file.Open(subdlg.GetPathName(),CFile::modeRead))
		{
			#ifdef _DEBUG
				afxDump << "Unable to open file" << "\n";
				exit( 1 );
			#endif
		}
		CArchive ar(&file, CArchive::load);
		
		TRY
		{
			m_selection.RemoveAll();
			ar.m_pDocument = GetDocument(); // set back-pointer in archive
			m_selection.Serialize(ar);

			POSITION pos = m_selection.GetHeadPosition();
			while (pos != NULL)
				GetDocument()->Add(m_selection.GetNext(pos));
			GetDocument()->SetModifiedFlag();
			
			GetDocument()->UpdateAllViews(NULL, HINT_UPDATE_SELECTION, &m_selection);
		}
		CATCH_ALL(e)
		{
			ar.Close();
			file.Close();
			THROW_LAST();
		}
		END_CATCH_ALL
			
		ar.Close();
		file.Close();
	}	
}

void CDrawView::OnUpdateUnitSave(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_selection.GetCount() >= 1);
}

void CDrawView::OnEditSelectAll()
{
	CDrawObjList* pObList = GetDocument()->GetObjects();
	POSITION pos = pObList->GetHeadPosition();
	while (pos != NULL)
		Select(pObList->GetNext(pos), TRUE);
}

void CDrawView::OnUpdateEditSelectAll(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(GetDocument()->GetObjects()->GetCount() != 0);
}

void CDrawView::OnEditClear()
{
	// update all the views before the selection goes away
	GetDocument()->UpdateAllViews(NULL, HINT_DELETE_SELECTION, &m_selection);
	OnUpdate(NULL, HINT_UPDATE_SELECTION, NULL);

	// now remove the selection from the document
	POSITION pos = m_selection.GetHeadPosition();
	while (pos != NULL)
	{
		CDrawObj* pObj = m_selection.GetNext(pos);
		if(pObj->IsKindOf(RUNTIME_CLASS(CDrawRect)))
		{
			CDrawRect *pRect = (CDrawRect *)pObj;
			GetDocument()->Remove(pObj);
			pObj->Remove();
			continue;
		}
		GetDocument()->Remove(pObj);
		pObj->Remove();
	}
	m_selection.RemoveAll();
	GetDocument()->UpdateAllViews(NULL);
}

void CDrawView::OnUpdateAnySelect(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(!m_selection.IsEmpty());
}

void CDrawView::OnEditCopy()
{
	ASSERT_VALID(this);
	ASSERT(m_cfDraw != NULL);

	// Create a shared file and associate a CArchive with it
	CSharedFile file;
	CArchive ar(&file, CArchive::store);

	// Serialize selected objects to the archive
	m_selection.Serialize(ar);
	ar.Close();

	COleDataSource* pDataSource = NULL;
	TRY
	{
		pDataSource = new COleDataSource;
		// put on local format instead of or in addation to
		pDataSource->CacheGlobalData(m_cfDraw, file.Detach());

		// if only one item and it is a COleClientItem then also
		// paste in that format
		CDrawObj* pDrawObj = m_selection.GetHead();
/*		if (m_selection.GetCount() == 1 &&
			pDrawObj->IsKindOf(RUNTIME_CLASS(CDrawOleObj)))
		{
			CDrawOleObj* pDrawOle = (CDrawOleObj*)pDrawObj;
			pDrawOle->m_pClientItem->GetClipboardData(pDataSource, FALSE);
		}*/
		pDataSource->SetClipboard();
	}
	CATCH_ALL(e)
	{
		delete pDataSource;
		THROW_LAST();
	}
	END_CATCH_ALL
}

void CDrawView::OnUpdateEditCopy(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(!m_selection.IsEmpty());
}

void CDrawView::OnEditCut()
{
	OnEditCopy();
	OnEditClear();
}

void CDrawView::OnUpdateEditCut(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(!m_selection.IsEmpty());
}

void CDrawView::OnEditPaste()
{
	COleDataObject dataObject;
	dataObject.AttachClipboard();

	// invalidate current selection since it will be deselected
	OnUpdate(NULL, HINT_UPDATE_SELECTION, NULL);
	m_selection.RemoveAll();
	if (dataObject.IsDataAvailable(m_cfDraw))
	{
		PasteNative(dataObject);

		// now add all items in m_selection to document
		POSITION pos = m_selection.GetHeadPosition();
		while (pos != NULL)
			GetDocument()->Add(m_selection.GetNext(pos));
	}
///	else
///		PasteEmbedded(dataObject, GetInitialPosition().TopLeft() );

	GetDocument()->SetModifiedFlag();

	// invalidate new pasted stuff
	GetDocument()->UpdateAllViews(NULL, HINT_UPDATE_SELECTION, &m_selection);
}

void CDrawView::OnUpdateEditPaste(CCmdUI* pCmdUI)
{
	// determine if private or standard OLE formats are on the clipboard
	COleDataObject dataObject;
	BOOL bEnable = dataObject.AttachClipboard() &&
		(dataObject.IsDataAvailable(m_cfDraw) ||
		 COleClientItem::CanCreateFromData(&dataObject));

	// enable command based on availability
	pCmdUI->Enable(bEnable);
}

/*
void CDrawView::OnEditProperties()
{
	if (m_selection.GetCount() == 1 && CDrawTool::c_drawShape == selection)
	{
		CDrawTool* pTool = CDrawTool::FindTool(CDrawTool::c_drawShape);
		ASSERT(pTool != NULL);
		pTool->OnEditProperties(this);
	}
}

void CDrawView::OnUpdateEditProperties(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(m_selection.GetCount() == 1 &&
				   CDrawTool::c_drawShape == selection);
}
*/

void CDrawView::OnViewGrid()
{
	m_bGrid = !m_bGrid;
	Invalidate(FALSE);
}

void CDrawView::OnUpdateViewGrid(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_bGrid);
}
/*
void CDrawView::OnViewShowobjects() 
{
	CDrawOleObj::c_bShowItems = !CDrawOleObj::c_bShowItems;
	GetDocument()->UpdateAllViews(NULL, HINT_UPDATE_OLE_ITEMS, NULL);
}

void CDrawView::OnUpdateViewShowobjects(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(CDrawOleObj::c_bShowItems);
}
*/
//选择
void CDrawView::OnDrawSelect()
{
	CDrawTool::c_drawShape = selection;
}

void CDrawView::OnUpdateDrawSelect(CCmdUI* pCmdUI)
{
	pCmdUI->SetRadio(CDrawTool::c_drawShape == selection);
}

//画圆边矩形
void CDrawView::OnDrawRoundRect()
{
	CDrawTool::c_drawShape = roundRect;
}

void CDrawView::OnUpdateDrawRoundRect(CCmdUI* pCmdUI)
{
	pCmdUI->SetRadio(CDrawTool::c_drawShape == roundRect);
}

//画矩形
void CDrawView::OnDrawRect()
{
	CDrawTool::c_drawShape = rect;
}

void CDrawView::OnUpdateDrawRect(CCmdUI* pCmdUI)
{
	pCmdUI->SetRadio(CDrawTool::c_drawShape == rect);
}

//画线
void CDrawView::OnDrawLine()
{
	CDrawTool::c_drawShape = line;
}

void CDrawView::OnUpdateDrawLine(CCmdUI* pCmdUI)
{
	pCmdUI->SetRadio(CDrawTool::c_drawShape == line);
}

//画箭头
void CDrawView::OnToolboxArrow() 
{
	CDrawTool::c_drawShape = arrow;
}

void CDrawView::OnUpdateToolboxArrow(CCmdUI* pCmdUI) 
{
	pCmdUI->SetRadio(CDrawTool::c_drawShape == arrow);
}

//画直线
void CDrawView::OnToolboxBeeline() 
{
	CDrawTool::c_drawShape = beeline;
}

void CDrawView::OnUpdateToolboxBeeline(CCmdUI* pCmdUI) 
{
	pCmdUI->SetRadio(CDrawTool::c_drawShape == beeline);
}

//花圆
void CDrawView::OnDrawEllipse()
{
	CDrawTool::c_drawShape = ellipse;
}

void CDrawView::OnUpdateDrawEllipse(CCmdUI* pCmdUI)
{
	pCmdUI->SetRadio(CDrawTool::c_drawShape == ellipse);
}

//饼
void CDrawView::OnToolboxchord() 
{
	CDrawTool::c_drawShape = pie;
}

void CDrawView::OnUpdateToolboxchord(CCmdUI* pCmdUI) 
{
	pCmdUI->SetRadio(CDrawTool::c_drawShape == pie);
}

//45度饼
void CDrawView::OnToolboxpie() 
{
	CDrawTool::c_drawShape = pie45;
}

void CDrawView::OnUpdateToolboxpie(CCmdUI* pCmdUI) 
{
	pCmdUI->SetRadio(CDrawTool::c_drawShape == pie45);	
}

//切
void CDrawView::OnToolboxQie() 
{
	CDrawTool::c_drawShape = qie;
}

void CDrawView::OnUpdateToolboxQie(CCmdUI* pCmdUI) 
{
	pCmdUI->SetRadio(CDrawTool::c_drawShape == qie);	
}

//画线段
void CDrawView::OnDrawPolygon()
{
	CDrawTool::c_drawShape = poly;
}

void CDrawView::OnUpdateDrawPolygon(CCmdUI* pCmdUI)
{
	pCmdUI->SetRadio(CDrawTool::c_drawShape == poly);
}


//画空心矩形
void CDrawView::OnToolboxrectangle() 
{
	CDrawTool::c_drawShape = rectNoFill;
}

void CDrawView::OnUpdateToolboxrectangle(CCmdUI* pCmdUI) 
{
	pCmdUI->SetRadio(CDrawTool::c_drawShape == rectNoFill);
}

//画空心圆边矩形
void CDrawView::OnToolboxRoundrectNofill() 
{
	CDrawTool::c_drawShape = roundRectNoFill;
}

void CDrawView::OnUpdateToolboxRoundrectNofill(CCmdUI* pCmdUI) 
{
	pCmdUI->SetRadio(CDrawTool::c_drawShape == roundRectNoFill);
	
}

//画空心圆形
void CDrawView::OnToolboxoval() 
{
	CDrawTool::c_drawShape = ellipseNoFill;
}

void CDrawView::OnUpdateToolboxoval(CCmdUI* pCmdUI) 
{
	pCmdUI->SetRadio(CDrawTool::c_drawShape == ellipseNoFill);		
}

//画空心多边形
void CDrawView::OnToolboxpolygon() 
{
	CDrawTool::c_drawShape = polyNoFill;	
}

void CDrawView::OnUpdateToolboxpolygon(CCmdUI* pCmdUI) 
{
	pCmdUI->SetRadio(CDrawTool::c_drawShape == polyNoFill);	
}

//画曲线
void CDrawView::OnDrawCurve() 
{
	CDrawTool::c_drawShape = curve;
}

void CDrawView::OnUpdateDrawCurve(CCmdUI* pCmdUI) 
{
	pCmdUI->SetRadio(CDrawTool::c_drawShape == curve);	
}

//管道
void CDrawView::OnToolboxConduit() 
{
	CDrawTool::c_drawShape = conduit;
}

void CDrawView::OnUpdateToolboxConduit(CCmdUI* pCmdUI) 
{
	pCmdUI->SetRadio(CDrawTool::c_drawShape == conduit);		
}

//实时曲线
void CDrawView::OnToolboxTimeCurve() 
{
	CDrawTool::c_drawShape = chart;
	
}

//历史曲线
void CDrawView::OnToolboxstroke() 
{
///	CDrawTool::c_drawShape = history;	
}

//插入图片
void CDrawView::OnToolboxbitmap() 
{
	CDrawTool::c_drawShape = picture;
}

void CDrawView::OnUpdateToolboxbitmap(CCmdUI* pCmdUI) 
{
	pCmdUI->SetRadio(CDrawTool::c_drawShape == picture);		
}

//画按钮
void CDrawView::OnToolboxbutton() 
{
	CDrawTool::c_drawShape = button;	
}

void CDrawView::OnUpdateToolboxbutton(CCmdUI* pCmdUI) 
{
	pCmdUI->SetRadio(CDrawTool::c_drawShape == button);		
}

void CDrawView::OnToolboxtext() 
{
	CDrawTool::c_drawShape = text;
}

void CDrawView::OnUpdateToolboxtext(CCmdUI* pCmdUI) 
{
	pCmdUI->SetRadio(CDrawTool::c_drawShape == text);		
}

//插入报警表
void CDrawView::OnToolboxwarn() 
{
	CDrawTool::c_drawShape = warn;	
}


/********************************************************************************
以下是格式工具栏中的按钮事件
********************************************************************************/
void CDrawView::OnUpdateSingleSelect(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(m_selection.GetCount() == 1);
}

void CDrawView::OnObjectMoveBack()
{
	CDrawDoc* pDoc = GetDocument();
	CDrawObj* pObj = m_selection.GetHead();
	CDrawObjList* pObjects = pDoc->GetObjects();
	POSITION pos = pObjects->Find(pObj);
	ASSERT(pos != NULL);
	if (pos != pObjects->GetHeadPosition())
	{
		POSITION posPrev = pos;
		pObjects->GetPrev(posPrev);
		pObjects->RemoveAt(pos);
		pObjects->InsertBefore(posPrev, pObj);
		InvalObj(pObj);
	}
}

void CDrawView::OnObjectMoveForward()
{
	CDrawDoc* pDoc = GetDocument();
	CDrawObj* pObj = m_selection.GetHead();
	CDrawObjList* pObjects = pDoc->GetObjects();
	POSITION pos = pObjects->Find(pObj);
	ASSERT(pos != NULL);
	if (pos != pObjects->GetTailPosition())
	{
		POSITION posNext = pos;
		pObjects->GetNext(posNext);
		pObjects->RemoveAt(pos);
		pObjects->InsertAfter(posNext, pObj);
		InvalObj(pObj);
	}
}

//黑体
void CDrawView::OnFormattingBold() 
{
	if(m_selection.GetCount() >= 1)
	{
		POSITION pos = m_selection.GetHeadPosition();
		while(pos != NULL)
		{
			CDrawObj * pObj = m_selection.GetNext(pos);
			if(pObj->IsKindOf(RUNTIME_CLASS(CDrawButton)))
			{
				CDrawButton *pButton = (CDrawButton *)pObj;
				if(!bIsBold)
				{
					pButton->m_fontStyle = FontStyleBold;
					bIsBold = TRUE;
				}
				else
				{
					pButton->m_fontStyle = FontStyleRegular;
					bIsBold = FALSE;
				}
				pButton->Invalidate();
			}
		}
	}
}

//斜体
void CDrawView::OnFormattingItalic() 
{
	if(m_selection.GetCount() >= 1)
	{
		POSITION pos = m_selection.GetHeadPosition();
		while(pos != NULL)
		{
			CDrawObj * pObj = m_selection.GetNext(pos);
			if(pObj->IsKindOf(RUNTIME_CLASS(CDrawButton)))
			{
				CDrawButton *pButton = (CDrawButton *)pObj;
				if(!bIsItalic)
				{
					pButton->m_fontStyle = FontStyleItalic;
					bIsItalic = TRUE;
				}
				else
				{
					pButton->m_fontStyle = FontStyleRegular;
					bIsItalic = FALSE;
				}
				pButton->Invalidate();
			}
		}
	}	
}

//下划线
void CDrawView::OnFormattingUnderline() 
{
	if(m_selection.GetCount() >= 1)
	{
		POSITION pos = m_selection.GetHeadPosition();
		while(pos != NULL)
		{
			CDrawObj * pObj = m_selection.GetNext(pos);
			if(pObj->IsKindOf(RUNTIME_CLASS(CDrawButton)))
			{
				CDrawButton *pButton = (CDrawButton *)pObj;
				if(!bIsUnderline)
				{
					pButton->m_fontStyle = FontStyleUnderline;
					bIsUnderline = TRUE;
				}					
				else
				{
					pButton->m_fontStyle = FontStyleRegular;
					bIsUnderline = FALSE;
				}
				pButton->Invalidate();
			}
		}
	}		
}

//测试报警表
void CDrawView::OnToolboxreport() 
{
	CDrawTool::c_drawShape = warning;
}

void CDrawView::OnUpdateToolboxreport(CCmdUI* pCmdUI) 
{
	pCmdUI->SetRadio(CDrawTool::c_drawShape == warning);
}

//锁定
void CDrawView::OnPupupLock() 
{
	POSITION pos = m_selection.GetHeadPosition();
	if(!bLock)
	{
		while(pos != NULL)
		{
			CDrawObj * pObj = m_selection.GetNext(pos);
			pObj->m_bLock = TRUE;
		}
	}
	else
	{
		while(pos != NULL)
		{
			CDrawObj * pObj = m_selection.GetNext(pos);
			pObj->m_bLock = FALSE;
		}
	}
}

void CDrawView::OnUpdatePupupLock(CCmdUI* pCmdUI) 
{
	POSITION pos = m_selection.GetHeadPosition();
	while(pos != NULL)
	{
		CDrawObj * pObj = m_selection.GetNext(pos);
		if(pObj->m_bLock)
		{
			bLock = TRUE;
		}
		else
		{
			bLock = FALSE;
		}
	}		
	pCmdUI->SetCheck(bLock);
}

int CDrawView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CScrollView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// register drop target
	if( m_dropTarget.Register( this ) )
		return 0;
	else
		return -1;
}


BOOL CDrawView::PreTranslateMessage(MSG* pMsg) 
{
	if(m_bIsDraw)
	{
		if ((pMsg->message  == WM_KEYDOWN || WM_SYSKEYDOWN == pMsg->message))
		{
			if(pMsg->wParam != VK_ESCAPE)
				return TRUE;
		}
	}
	return CScrollView::PreTranslateMessage(pMsg);
}

//弹出菜单“动作”
void CDrawView::OnPopupAction() 
{
//	if (m_selection.GetCount() == 1 ||
//		(m_selection.GetCount() > 0 && m_selection.GetHead()->m_strGroupName.GetLength() > 0))
	{
		CSetActionDlg dlg;
		
		POSITION pos = m_selection.GetHeadPosition();
		if(pos != NULL)
		{
			CDrawObj * pObj = m_selection.GetNext(pos);
			dlg.m_ActionStruct = pObj->m_ActionStruct;
		}

		if(dlg.DoModal() != IDOK)
			return;

		pos = m_selection.GetHeadPosition();
		while(pos != NULL)
		{
			CDrawObj * pObj = m_selection.GetNext(pos);
			pObj->m_ActionStruct = dlg.m_ActionStruct;
		}

	}
}

void CDrawView::OnUpdatePopupAction(CCmdUI* pCmdUI) 
{
	BOOL    bIsAction = FALSE;
	if(m_selection.GetCount() >0)
		bIsAction = TRUE;

	POSITION pos = m_selection.GetHeadPosition();
	while(pos != NULL)
	{
		CDrawObj * pObj = m_selection.GetNext(pos);
		if(pObj->IsKindOf(RUNTIME_CLASS(CDrawButton)))
			bIsAction = FALSE;
		if(pObj->IsKindOf(RUNTIME_CLASS(CDrawWarn)))
			bIsAction = FALSE;
		if(pObj->IsKindOf(RUNTIME_CLASS(CDrawChart)))
			bIsAction = FALSE;
		if(pObj->IsKindOf(RUNTIME_CLASS(CDrawConduit)))
			bIsAction = FALSE;
	}		
	pCmdUI->Enable(bIsAction);
}

//插入小车
void CDrawView::OnInsertCar() 
{
	CDrawTool::c_drawShape = car;
}

//插入转轮
void CDrawView::OnInsertRotary() 
{
	CDrawTool::c_drawShape = rotary;
}



