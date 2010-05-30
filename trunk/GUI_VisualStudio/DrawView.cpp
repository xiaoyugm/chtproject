// DrawView.cpp : implementation of the CDrawView class
//

#include "stdafx.h"
#include "GUI_VisualStudio.h"

#include "DrawDoc.h"
///#include "CntrItem.h"
#include "DrawView.h"
#include "MainFrm.h"

#include "drawobj.h"
///#include "cntritem.h"
///#include "drawtool.h"
#include "DrawRect.h"
#include "drawwarn.h"
#include "drawchart.h"
#include "drawbutton.h"
#include <math.h>
#include "SetTimeDlg.h"
#include "DrawRotary.h"
#include "DrawConduit.h"
#include "DrawCar.h"

#include "DrawPoly.h"

//#include <SqlDirect.h>
#include <String2DataType.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

enum
{
	CHART = 1,
	VIEW,
	DRAWTASK,
	ACTION
};

extern CStrWarn m_CStrWarn[MAX_ROW];
extern CPointInfo m_CPointInfo[MAX_POINT_NUMBER];
extern CWarnPoint m_CWarnPoint[MAX_POINT_NUMBER];
/////////////////////////////////////////////////////////////////////////////
// CDrawView             VIEW

// private clipboard format (list of Draw objects)
CLIPFORMAT CDrawView::m_cfDraw = (CLIPFORMAT)
	::RegisterClipboardFormat(_T("MFC Draw"));
CLIPFORMAT CDrawView::m_cfObjectDescriptor = NULL;

IMPLEMENT_DYNCREATE(CDrawView, CScrollView)

BEGIN_MESSAGE_MAP(CDrawView, CScrollView)
	//{{AFX_MSG_MAP(CDrawView)
	ON_WM_DESTROY()
	ON_WM_TIMER()
	ON_WM_LBUTTONDOWN()
//	ON_COMMAND(ID_TIME_VIEW, OnTimeView)
	ON_WM_SETFOCUS()
	ON_WM_SIZE()
	ON_WM_CREATE()
	ON_WM_MOUSEMOVE()               //0415
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

	m_bDragDataAcceptable = FALSE;
	m_Second =0 ;
    CountView = 0;
	BOOL m_bCount = FALSE;
	m_bGrid = FALSE;
	m_gridColor = RGB(0, 0, 128);
	m_bActive = FALSE;
// new
	if( m_cfObjectDescriptor == NULL )
		m_cfObjectDescriptor = (CLIPFORMAT)::RegisterClipboardFormat(_T("Object Descriptor") );
	m_prevDropEffect = DROPEFFECT_NONE;
// end new	

}

CDrawView::~CDrawView()
{
//    KillTimer(CHART);
///    KillTimer(VIEW);
//    KillTimer(DRAWTASK);
//    KillTimer(ACTION);
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

void CDrawView::InvalRouteObj(CDrawObj* pObj)
{
	CRect rect = pObj->m_position;
	DocToClient(rect);
	rect.NormalizeRect();
	int nMax = max(rect.Height(),rect.Width())/2;   //2
	int nMin = min(rect.Height(),rect.Width())/2;
	int nHypotenuse = sqrt(nMax * nMax + nMin * nMin) ;

		rect.left = rect.left - nHypotenuse;///+rect.Width()/2;
		rect.top = rect.top - nHypotenuse;///+rect.Height()/2 ;
		rect.right = rect.right + nHypotenuse+rect.Width()/2;
		rect.bottom += nHypotenuse+rect.Height()/2;

	rect.InflateRect(1, 1); // handles CDrawOleObj objects

	InvalidateRect(rect, FALSE);
}

void CDrawView::InvalSizeObj(CDrawObj* pObj)
{
	CRect rect = pObj->m_rectAction;
	DocToClient(rect);
	rect.NormalizeRect();
/*	int nChangeH = pObj->m_ActionStruct.stcSizeChangeH.nMaxPercent;
	int nChangeW = pObj->m_ActionStruct.stcSizeChangeW.nMaxPercent;
	int nMax = max(nChangeH, nChangeW);

	int nWidth = rect.Width()*nMax/100;
	int nHeight = rect.Height()*nMax/100;

	rect.left -= nWidth;
	rect.right += nWidth;
	rect.top -= nHeight;
	rect.bottom += nHeight;
*/
	rect.InflateRect(1,1);

	InvalidateRect(rect, FALSE);

}

void CDrawView::InvalMoveObj(CDrawObj* pObj)
{
	CRect rect = pObj->m_rectAction;
	DocToClient(rect);
	rect.NormalizeRect();
	
	int nMoveH = 70;//pObj->m_ActionStruct.stcObjectMoveH.nPixMax;
	int nMoveV = 70;//pObj->m_ActionStruct.stcObjectMoveV.nPixMax;
	int nMax = max(nMoveH, nMoveV);

	rect.left -= nMax;
	rect.right += nMax;
	rect.top -= nMax;
	rect.bottom += nMax;
///	rect.InflateRect(1,1);      //0415
//0415
	nMax =  max(rect.Height(),rect.Width());
	int nMin =  min(rect.Height(),rect.Width());
	int nHypotenuse =  sqrt(nMax * nMax + nMin * nMin);

		rect.left = rect.left-nHypotenuse+rect.Width()/2;
		rect.top = rect.top -nHypotenuse+rect.Height()/2 ;
		rect.right = rect.right + nHypotenuse+rect.Width()/2;
		rect.bottom += nHypotenuse+rect.Height()/2;
	rect.InflateRect(1,1);

	InvalidateRect(rect, FALSE);
}

void CDrawView::InvalCarObj(CDrawObj* pObj)
{
	CRect rect = pObj->m_position;
	DocToClient(rect);

		rect.left -= 80 ;            //18;
		rect.top -=  90 ;             //20;
		rect.right +=  80 ;             //20;
		rect.bottom += 90 ;             //18

	rect.InflateRect(1, 1); // handles CDrawOleObj objects

	InvalidateRect(rect, FALSE);
}

/////////////////////////////////////////////////////////////////////////////
// CDrawView drawing
void CDrawView::InvalObj(CDrawObj* pObj)
{
	CRect rect = pObj->m_position;
	DocToClient(rect);
///	if (m_bActive && IsSelected(pObj))
///	{
		rect.left -= 18 ;            //18;
		rect.top -=  20 ;             //20;
		rect.right +=  20 ;             //20;
		rect.bottom += 18 ;             //18
///	}
	rect.InflateRect(1, 1); // handles CDrawOleObj objects

	InvalidateRect(rect, FALSE);
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

	case HINT_UPDATE_SIZE:
		InvalSizeObj((CDrawObj*)pHint);
		break;

	case HINT_UPDATE_MOVE:
		InvalMoveObj((CDrawObj*)pHint);
		break;

/*	case HINT_UPDATE_SELECTION: // an entire selection has changed
		{
			CDrawObjList* pList = pHint != NULL ?
				(CDrawObjList*)pHint : &m_selection;
			POSITION pos = pList->GetHeadPosition();
			while (pos != NULL)
				InvalObj(pList->GetNext(pos));
		}
		break;

/*	case HINT_DELETE_SELECTION: // an entire selection has been removed
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

	case HINT_UPDATE_OLE_ITEMS:
		{
			CDrawDoc* pDoc = GetDocument();
			POSITION pos = pDoc->GetObjects()->GetHeadPosition();
			while (pos != NULL)
			{
				CDrawObj* pObj = pDoc->GetObjects()->GetNext(pos);
				if (pObj->IsKindOf(RUNTIME_CLASS(CDrawOleObj)))
					InvalObj(pObj);
			}
		}
		break;*/

	case HINT_UPDATE_CAR:
		{
		InvalMoveObj((CDrawObj*)pHint);
		InvalCarObj((CDrawObj*)pHint);
		}
		break;

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
/*
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
*/
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

///	if (!pDC->IsPrinting() && m_bGrid)
///		DrawGrid(pDrawDC);

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

///	brush.DeleteObject();
///	DeleteObject(bitmap);
///	DeleteDC(dc);

}

void CDrawView::Remove(CDrawObj* pObj)
{
	POSITION pos = m_selection.Find(pObj);
	if (pos != NULL)
		m_selection.RemoveAt(pos);
}
/*
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

void CDrawView::DrawGrid(CDC* pDC)
{
	CDrawDoc* pDoc = GetDocument();

	COLORREF oldBkColor = pDC->SetBkColor(pDoc->GetPaperColor());
	pDC->SetBkColor(oldBkColor);
}
*/
void CDrawView::OnInitialUpdate()
{
	CSize size = GetDocument()->GetSize();
	CClientDC dc(NULL);
	size.cx = MulDiv(size.cx, dc.GetDeviceCaps(LOGPIXELSX), 100);
	size.cy = MulDiv(size.cy, dc.GetDeviceCaps(LOGPIXELSY), 100);
	size.cx = size.cx + 100;
	size.cy = size.cy + 100;
	SetScrollSizes(MM_TEXT, size);

	CString2DataType m_String2DataType;
							CString strtemp1,strtemp2,strtemp3,strtemp;
							CTime loginTime = CTime::GetCurrentTime();
							strtemp=loginTime.Format("%Y年%m月%d日%H时%M分%S秒");
							CString2DataType Str2Data;
							strtemp1=strtemp.Left(4);
							strtemp2=strtemp.Mid(6);
							strtemp3=strtemp2.Left(2);
							int nMonth=m_String2DataType.String2Int(strtemp3);
							int nYear=m_String2DataType.String2Int(strtemp1);

///							if((nMonth>=8)&&(nYear==2004))
							{
	SetTimer(CHART,1000,NULL);
///	SetTimer(VIEW,1317,NULL);
//	SetTimer(DRAWTASK,30,NULL);
	SetTimer(ACTION,30,NULL);
							}
///							else{
///								AfxMessageBox("对不起，请使用正版软件");
//								return;
//							}

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

// Special handling of OnSetFocus and OnSize are required for a container
//  when an object is being edited in-place.
void CDrawView::OnSetFocus(CWnd* pOldWnd)
{
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
*/
/////////////////////////////////////////////////////////////////////////////
// OLE Server support

// The following command handler provides the standard keyboard
//  user interface to cancel an in-place editing session.  Here,
//  the server (not the container) causes the deactivation.

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
/*
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
		m_selection.AddHead(pObj);
	else
		m_selection.AddTail(pObj);
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
*/
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
/*
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
}*/
/////////////////////////////////////////////////////////////////////////////
// CDrawView message handlers

//窗口交替显示
void CDrawView::OnTimeView() 
{
///    KillTimer(DRAW);
//	CSetTimeDlg dlg ;
//	dlg.m_nSecond = m_Second;

//	if(dlg.DoModal() == IDOK)
	{
//		m_Second = dlg.m_nSecond;
///    	SetTimer(DRAW,1123,NULL);
	}
	if(m_Second == 0)
	{
	}
	else
	{
	}
}

void CDrawView::OnTimer(UINT nIDEvent) 
{
    CMainFrame* pFWnd=(CMainFrame*)AfxGetMainWnd();
	
	double dfValue ; 
	unsigned short nPointNo,ufData,nPoint,OldwarnPoint ,pufdata;
	unsigned char Warn_state,OldWarn_state ,LineWarn_state ,FillWarn_state;
	switch(nIDEvent)
	{
    	case DRAWTASK:                                     
			{
			}
			break ;
    	case CHART: 
			{
		    	CDrawObjList *ObjectAll =GetDocument()->GetObjects();
		    	POSITION pos = ObjectAll->GetHeadPosition();
		    	while(pos != NULL)
				{
			    	CDrawObj* Obj = ObjectAll->GetNext(pos);
					if(Obj->IsKindOf(RUNTIME_CLASS(CDrawChart)))    //实时曲线
					{
				    	CDrawChart *pChart = (CDrawChart*)Obj;
                       	pChart->StartAction();
					}
					if(Obj->IsKindOf(RUNTIME_CLASS(CDrawWarn)))			//重画报警表
					{
                    	CDrawWarn *pWarn = (CDrawWarn*)Obj;
			    		nPointNo = m_CWarnPoint[0].warnPoint ;
				     	OldwarnPoint = m_CWarnPoint[0].OldwarnPoint ;
                        Warn_state = m_CPointInfo[nPointNo].lWarn_state ;
		    			OldWarn_state = m_CWarnPoint[0].OldWarn_state ;

				    	if((Warn_state != OldWarn_state) || (OldwarnPoint != nPointNo))
						{
	    					m_CWarnPoint[0].OldwarnPoint = nPointNo ;
		    				m_CWarnPoint[0].OldWarn_state = Warn_state ;
    						pWarn->StartAction();
						}
			 		}

//             	CMDIFrameWnd *pFrame = (CMDIFrameWnd*)AfxGetApp()->m_pMainWnd;
//              	CTaskListBar *pChild = (CTaskListBar *) pFrame->GetActiveFrame();
//	        	pChild->SetWarnInfo();

				}
///			}
///			break ;
///    	case DRAW:                                     //窗口交替显示
///			{
            	CMDIFrameWnd *pFrame = (CMDIFrameWnd*)AfxGetApp()->m_pMainWnd;
              	CMDIChildWnd *pChild = (CMDIChildWnd *) pFrame->GetActiveFrame();
//               	CDrawView *pView = (CDrawView*)pChild->GetActiveView();	
//            	if(pView == NULL)
//              		return;

/*		    	if(m_Second !=0 )                        //	窗口交替显示
				{                        
		         	CString strTemp;
		    		CountView ++ ;
			    	if(CountView == m_Second)
					{
    	        		if(m_ViewPos != NULL)
						{
			            	theApp.m_map.GetNextAssoc(m_ViewPos,strTemp,pView);
       		            	if(pView != NULL)
			            		pView->GetParentFrame()->ActivateFrame();
						}
		            	else 
						{
		    	        	m_ViewPos = theApp.m_map.GetStartPosition() ;     //0415
			            	theApp.m_map.GetNextAssoc(m_ViewPos,strTemp,pView);
       		            	if(pView != NULL)
			            		pView->GetParentFrame()->ActivateFrame();
						}
				    	CountView = 0 ;
					}
				}*/

				pFWnd->AddEdit();
			}
			break ;
    	case ACTION:                                     //连续动作
		{
//    if(pFWnd->m_ontime == 1)
//         		return;

        	CMDIFrameWnd *pFrame = (CMDIFrameWnd*)AfxGetApp()->m_pMainWnd;
         	CMDIChildWnd *pChild = (CMDIChildWnd *) pFrame->GetActiveFrame();
         	CDrawView *pView = (CDrawView*)pChild->GetActiveView();	

			if(!pView->IsKindOf(RUNTIME_CLASS(CDrawView)))
//        	if(pView == NULL)
           		return;

           	CDrawObjList *ObjectAll = pView->GetDocument()->GetObjects();
         	POSITION pos = ObjectAll->GetHeadPosition();
        	while(pos != NULL)
			{
				CDrawObj* Obj = ObjectAll->GetNext(pos);

        		if(Obj->IsKindOf(RUNTIME_CLASS(CDrawPoly)))
				{
           			CDrawPoly *pPoly = (CDrawPoly*)Obj;
                	if(Obj->m_ActionStruct.bIsLineColorChange)
					{
			     		nPoint = Obj->m_ActionStruct.stcLineChange.nPoint;
						if(nPoint != 0)
						{
	                	        Warn_state = m_CPointInfo[nPoint].lWarn_state ;
								LineWarn_state = Obj->m_ActionStruct.stcLineChange.LineWarn_state ;
		            		if(LineWarn_state != Warn_state)
							{
      	            	   		if((Warn_state & 0x30) == 0x00 )
								{
									Obj->m_ActionStruct.stcLineChange.LineWarn_state = Warn_state ;
		                    			pPoly->m_clrLineColor = Obj->m_ActionStruct.stcLineChange.clrInLineColor;
					        		if((Warn_state & 0x82) == 0x82)
		                      			pPoly->m_clrLineColor = Obj->m_ActionStruct.stcLineChange.clrInLineColor;
					          		else if((Warn_state & 0x82) == 0x02)
		                      			pPoly->m_clrLineColor = Obj->m_ActionStruct.stcLineChange.clrOutLineColor;
								}
								else if((Warn_state & 0x30) == 0x10 ){
									Obj->m_ActionStruct.stcLineChange.LineWarn_state = Warn_state ;
             			    		pPoly->m_clrLineColor = Obj->m_ActionStruct.stcLineChange.clrCommErrorLineColor;
								}
								else if((Warn_state & 0x30) == 0x20 ){
									Obj->m_ActionStruct.stcLineChange.LineWarn_state = Warn_state ;
            		       			pPoly->m_clrLineColor = Obj->m_ActionStruct.stcLineChange.clrOutLineColor;
								}
            					pPoly->Invalidate();    //0413
							}
						}
					}
                	if(Obj->m_ActionStruct.bIsFillColorChange)
					{
			     		nPoint = Obj->m_ActionStruct.stcFillChange.nPoint;
						if(nPoint != 0)
						{
	                	        Warn_state = m_CPointInfo[nPoint].lWarn_state ;
								FillWarn_state = Obj->m_ActionStruct.stcFillChange.FillWarn_state ;
		            		if(FillWarn_state != Warn_state)
							{
      	            	   		if((Warn_state & 0x30) == 0x00 )
								{
									Obj->m_ActionStruct.stcFillChange.FillWarn_state = Warn_state ;
		                    			pPoly->m_clrFillColor = Obj->m_ActionStruct.stcFillChange.clrInFillColor;
					        		if((Warn_state & 0x82) == 0x82)
		                      			pPoly->m_clrFillColor = Obj->m_ActionStruct.stcFillChange.clrInFillColor;
					          		else if((Warn_state & 0x82) == 0x02)
		                      			pPoly->m_clrFillColor = Obj->m_ActionStruct.stcFillChange.clrOutFillColor;
								}
								else if((Warn_state & 0x30) == 0x10 ){
									Obj->m_ActionStruct.stcFillChange.FillWarn_state = Warn_state ;
             			    		pPoly->m_clrFillColor = Obj->m_ActionStruct.stcFillChange.clrCommErrorFillColor;
								}
								else if((Warn_state & 0x30) == 0x20 ){
									Obj->m_ActionStruct.stcFillChange.FillWarn_state = Warn_state ;
            		       			pPoly->m_clrFillColor = Obj->m_ActionStruct.stcFillChange.clrOutFillColor;
								}
            					pPoly->Invalidate();    //0413
							}
						}
					}
///					pPoly->bIsStartAction = TRUE;
				}

        		if(Obj->IsKindOf(RUNTIME_CLASS(CDrawRect)))
				{
           			CDrawRect *pRect = (CDrawRect*)Obj;
                	if(Obj->m_ActionStruct.bIsLineColorChange)
					{
			     		nPoint = Obj->m_ActionStruct.stcLineChange.nPoint;
						if(nPoint != 0)
						{
	                	        Warn_state = m_CPointInfo[nPoint].lWarn_state ;
								LineWarn_state = Obj->m_ActionStruct.stcLineChange.LineWarn_state ;
		            		if(LineWarn_state != Warn_state)
							{
      	            	   		if((Warn_state & 0x30) == 0x00 )
								{
									Obj->m_ActionStruct.stcLineChange.LineWarn_state = Warn_state ;
		                    			pRect->m_clrLineColor = Obj->m_ActionStruct.stcLineChange.clrInLineColor;
					        		if((Warn_state & 0x82) == 0x82)
		                      			pRect->m_clrLineColor = Obj->m_ActionStruct.stcLineChange.clrInLineColor;
					          		else if((Warn_state & 0x82) == 0x02)
		                      			pRect->m_clrLineColor = Obj->m_ActionStruct.stcLineChange.clrOutLineColor;
								}
								else if((Warn_state & 0x30) == 0x10 ){
									Obj->m_ActionStruct.stcLineChange.LineWarn_state = Warn_state ;
             			    		pRect->m_clrLineColor = Obj->m_ActionStruct.stcLineChange.clrCommErrorLineColor;
								}
								else if((Warn_state & 0x30) == 0x20 ){
									Obj->m_ActionStruct.stcLineChange.LineWarn_state = Warn_state ;
            		       			pRect->m_clrLineColor = Obj->m_ActionStruct.stcLineChange.clrOutLineColor;
								}
            					pRect->Invalidate();    //0413
							}
						}
					}
                	if(Obj->m_ActionStruct.bIsFillColorChange)
					{
			     		nPoint = Obj->m_ActionStruct.stcFillChange.nPoint;
						if(nPoint != 0)
						{
	                	        Warn_state = m_CPointInfo[nPoint].lWarn_state ;
								FillWarn_state = Obj->m_ActionStruct.stcFillChange.FillWarn_state ;
		            		if(FillWarn_state != Warn_state)
							{
      	            	   		if((Warn_state & 0x30) == 0x00 )
								{
									Obj->m_ActionStruct.stcFillChange.FillWarn_state = Warn_state ;
		                    			pRect->m_clrFillColor = Obj->m_ActionStruct.stcFillChange.clrInFillColor;
					        		if((Warn_state & 0x82) == 0x82)
		                      			pRect->m_clrFillColor = Obj->m_ActionStruct.stcFillChange.clrInFillColor;
					          		else if((Warn_state & 0x82) == 0x02)
		                      			pRect->m_clrFillColor = Obj->m_ActionStruct.stcFillChange.clrOutFillColor;
								}
								else if((Warn_state & 0x30) == 0x10 ){
									Obj->m_ActionStruct.stcFillChange.FillWarn_state = Warn_state ;
             			    		pRect->m_clrFillColor = Obj->m_ActionStruct.stcFillChange.clrCommErrorFillColor;
								}
								else if((Warn_state & 0x30) == 0x20 ){
									Obj->m_ActionStruct.stcFillChange.FillWarn_state = Warn_state ;
            		       			pRect->m_clrFillColor = Obj->m_ActionStruct.stcFillChange.clrOutFillColor;
								}
            					pRect->Invalidate();    //0413
							}
						}
					}
                	if(Obj->m_ActionStruct.bIsPencentFillH)
					{
			     		nPoint = Obj->m_ActionStruct.stcPHChange.nPoint;
						if(nPoint != 0)
						{
	                	        ufData = m_CPointInfo[nPoint].lufdata ;
								pufdata = Obj->m_ActionStruct.stcPHChange.pufdata ;
		            		if(ufData != pufdata)
							{
				    			Obj->m_ActionStruct.stcPHChange.pufdata = ufData ;
	                    		pRect->m_clrFillColor = Obj->m_ActionStruct.stcPHChange.clrFillColor;
		                    	pRect->m_nPercentFill = m_CPointInfo[nPoint].pnValue *100;
		                    	pRect->m_RefPoint = Obj->m_ActionStruct.stcPHChange.ReferencePoint;
	                    		pRect->Invalidate();       
							}
						}
					}
                	if(Obj->m_ActionStruct.bIsPencentFillV)
					{
 			     		nPoint = Obj->m_ActionStruct.stcPVChange.nPoint;
						if(nPoint != 0)
						{
	                	        ufData = m_CPointInfo[nPoint].lufdata ;
								pufdata = Obj->m_ActionStruct.stcPVChange.pufdata ;
		            		if(ufData != pufdata)
							{
				    			Obj->m_ActionStruct.stcPVChange.pufdata = ufData ;
	                    		pRect->m_clrFillColor = Obj->m_ActionStruct.stcPVChange.clrFillColor;
		                    	pRect->m_nPercentFill = m_CPointInfo[nPoint].pnValue *100;
		                    	pRect->m_RefPoint = Obj->m_ActionStruct.stcPVChange.ReferencePoint;
	                    		pRect->Invalidate();       
							}
						}
					}


///					pRect->bIsStartAction = TRUE;
				}

         		if(Obj->IsKindOf(RUNTIME_CLASS(CDrawButton)))		//重画文本
				{
	           		CDrawButton *pText = (CDrawButton*)Obj;
        			if(pText->m_nShape == CDrawButton::text)
					{
		            	nPointNo = pText->m_nPointNo ;
						if(nPointNo != 0)
						{
	         	        Warn_state = m_CPointInfo[nPointNo].lWarn_state ;
                        dfValue = m_CPointInfo[nPointNo].ldfValue ;
            		    	if(pText->m_bIsRunShowValue)
							{
								if(nPointNo == 4)
								{
		            			ufData = m_CPointInfo[nPointNo].lufdata ;
                                CString str ,usUnit ;
                                usUnit  = m_CPointInfo[nPointNo].usUnit ;
                         		str.Format("%d%s", ufData , usUnit);		
                                pText ->m_strButton = str ;
								pText ->m_fontColor.SetFromCOLORREF(pText->m_TrueColor);
								}
								else
								{
                                CString str ,usUnit ;
                                usUnit  = m_CPointInfo[nPointNo].usUnit ;
                         		str.Format("%4.2f%s", dfValue,usUnit);		
                                pText ->m_strButton = str ;
				    	    	if((Warn_state & 0x30) == 0x00 )
									pText ->m_fontColor.SetFromCOLORREF(pText->m_TrueColor);
			                	else if((Warn_state & 0x30) == 0x10 )
									pText ->m_fontColor.SetFromCOLORREF(pText->m_ErrorColor);
			                	else   //if((Warn_state & 0x0c) == 0x08 )
									pText ->m_fontColor.SetFromCOLORREF(pText->m_FalseColor);
								}
							}
					    	else
							{
				        		if((Warn_state & 0x30) == 0x00 )
								{
//				    		    	if( pText ->m_blsDispTrue)
				    					pText ->m_fontColor.SetFromCOLORREF(pText->m_TrueColor);
//					    	    	else
//			    	    	    		pText ->m_fontColor = RGB(0,0,0);
								}
			                	else if((Warn_state & 0x30) == 0x10 )
									pText ->m_fontColor.SetFromCOLORREF(pText->m_ErrorColor);
			                	else   //if((Warn_state & 0x0c) == 0x08 )
								{
//					        		if( pText ->m_blsDispTrue)
//					     		    	pText ->m_fontColor = RGB(0,0,0);
//					    	    	else
		    							pText ->m_fontColor.SetFromCOLORREF(pText->m_FalseColor);
								}
							}
						}
						else
							pText ->m_fontColor.SetFromCOLORREF(pText->m_color);
	             		pText->StartAction();
///						pText->Invalidate();
					}
///        			if(pText->m_nShape == CDrawButton::button)
///						pText->Invalidate();
				}

		        if(Obj->IsKindOf(RUNTIME_CLASS(CDrawRotary)))
				{
	        		CDrawRotary* pRotary = (CDrawRotary*)Obj;
  	            	nPointNo = pRotary->m_RotaryStruct.nPoint ;
		        	Warn_state = m_CPointInfo[nPointNo].lufdata ;
		           	if(Warn_state  == 1 )
			        		pRotary->m_bIsAction = TRUE;
		       		else if(Warn_state == 0 )
		              		pRotary->m_bIsAction = FALSE;
	        		pRotary->StartAction();
///	        		continue;
				}

			    if(Obj->IsKindOf(RUNTIME_CLASS(CDrawConduit)))
				{
	         		CDrawConduit* pConduit = (CDrawConduit*)Obj;
  	            	nPointNo = pConduit->m_ConduitStruct.nPoint ;
		        	Warn_state = m_CPointInfo[nPointNo].lufdata ;
		           	if(Warn_state  == 1 )
			        		pConduit->m_bIsAction = TRUE;
		       		else if(Warn_state == 0 )
		              		pConduit->m_bIsAction = FALSE;
					pConduit->StartAction();
				}

				if(Obj->IsKindOf(RUNTIME_CLASS(CDrawCar)))
				{
					CDrawCar *pCar = (CDrawCar*)Obj;
  	            	nPointNo = pCar->m_CarStruct.nPoint ;
//		        	Warn_state = m_CPointInfo[nPointNo].lWarn_state ;
					Warn_state = m_CPointInfo[nPointNo].lufdata ;
					if(nPointNo > 4 )
					{
		            	if(Warn_state == 1 )
					    	pCar->DrawCarMove();
					}
//					else if((Warn_state & 0x02) == 0x00 )
//					{
///					    pCar->StartAction();
//					}
//						CRect rect = pCar->GetMoveRect();
//						InvalidateRect(rect, FALSE);
				}
		   }
		}
		break;
    }

	CScrollView::OnTimer(nIDEvent);
}


void CDrawView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CDrawObjList *ObjectAll =GetDocument()->GetObjects();
	POSITION pos = ObjectAll->GetHeadPosition();
	while(pos != NULL)
	{

		CDrawObj* Obj = ObjectAll->GetNext(pos);
		CRect rect = Obj->m_position;
		DocToClient(rect);
		rect.NormalizeRect();
		
		if(rect.PtInRect(point))
		{
			if(Obj->IsKindOf(RUNTIME_CLASS(CDrawButton)))			//链接区域事件
			{
				CDrawButton *pButton = (CDrawButton*)Obj;
				
       			if(pButton->m_nShape == CDrawButton::button)
				{
			    	CDrawView *pView;
		    		if(theApp.m_map.Lookup(pButton->m_strLinkViewName ,pView))
					{
			    		if(pView != NULL)
				    		pView->GetParentFrame()->ActivateFrame();
					}
			    	else
    					AfxMessageBox("该链接的窗口未被打开!");
				}
			}
		}
	}
	CScrollView::OnLButtonDown(nFlags, point);
}


/*
//画实时曲线
void CDrawView::DrawHistoryLine()
{
	CDrawObjList *ObjectAll =GetDocument()->GetObjects();
	POSITION pos = ObjectAll->GetHeadPosition();
	while(pos != NULL)
	{
		CDrawObj* Obj = ObjectAll->GetNext(pos);		
		if(Obj->IsKindOf(RUNTIME_CLASS(CDrawChart)))			//链接区域事件
		{
			CDrawChart *pChart = (CDrawChart*)Obj;
			if(!pChart->m_IsRealTime)
			{
				for(int j=0;j<100;j++)
				{
					int n = pChart->m_Graph.m_LineArray.GetSize();
					for(int i=0; i<n; i++)
					{
						pChart->m_Graph.AddYValue(i, 10);
					}
				}
			}
			
		}
	}
}

//0415
void CDrawView::OnMouseMove(UINT nFlags, CPoint point) 
{
	CDrawObjList * pObjList = GetDocument()->GetObjects();			//链接按钮响应鼠标移动消息
	POSITION Buttonpos = pObjList->GetHeadPosition();
	while(Buttonpos != NULL)
	{
		CDrawObj * pObj = pObjList->GetNext(Buttonpos);
		if(pObj->IsKindOf(RUNTIME_CLASS(CDrawButton)))
		{	
			CDrawButton* pButton = (CDrawButton*)pObj;
			CRect rect = pButton->m_position;
			rect.NormalizeRect();
			DocToClient(rect);
			if(rect.PtInRect(point))
			{	
				if(pButton->m_bIsHide)
				{
					pButton->m_bIsChangeHide = TRUE;
					pButton->m_bIsHide = FALSE;
				}
			}
			else
			{
				if(pButton->m_bIsChangeHide)
					pButton->m_bIsHide = TRUE;
			}
			pButton->Invalidate();
		}
	}	
	CScrollView::OnMouseMove(nFlags, point);
}
*/



