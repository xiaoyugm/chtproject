// drawobj.cpp - implementation for drawing objects
//
// This is a part of the Microsoft Foundation Classes C++ library.
// Copyright (c) Microsoft Corporation.  All rights reserved.
//
// This source code is only intended as a supplement to the
// Microsoft Foundation Classes Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding the
// Microsoft Foundation Classes product.


#include "stdafx.h"
#include "GUI_VisualStudio.h"

#include "drawdoc.h"
#include "drawview.h"
#include "drawobj.h"
#include <mmsystem.h>
///#include "cntritem.h"
#include <math.h>


extern "C"
void  CALLBACK  ActionProc(UINT id,UINT msg,DWORD dwUser,DWORD dw1,DWORD dw2)
{
	CDrawObj *	pObj = (CDrawObj *)dwUser;
	if(pObj->bIsStartRay)
	{
		if(pObj->m_ActionStruct.stcRayChange.bRayType)
		{
			if(pObj->bIsTranPlus)
			{
///				pObj->m_nTrans+=pObj->m_ActionStruct.stcRayChange.nRaySpeed;

///				if(pObj->m_nTrans > 250)
///					pObj->bIsTranPlus = !pObj->bIsTranPlus;
				pObj->Invalidate();
			}
			else
			{
///				pObj->m_nTrans-=pObj->m_ActionStruct.stcRayChange.nRaySpeed;
///				if(pObj->m_nTrans < 10)
///					pObj->bIsTranPlus = !pObj->bIsTranPlus;
				pObj->Invalidate();
			}
		}
		
		else
		{
			if(pObj->bIsTranPlus)
			{
				pObj->m_clrFillColor = pObj->m_ActionStruct.stcRayChange.clrRayStartColor;
				pObj->bIsTranPlus = !pObj->bIsTranPlus;
				pObj->Invalidate();
			}
			else
			{
				pObj->m_clrFillColor = pObj->m_ActionStruct.stcRayChange.clrRayEndColor;
				pObj->bIsTranPlus = !pObj->bIsTranPlus;
				pObj->Invalidate();
				
			}
			
		}
	}
	if(pObj->m_bIsSwitch)
	{
		pObj->m_nActionRoute += 10;
		pObj->Invalidate();
	}
}

void Normallize(Rect &rect){
//Ensure positive width and height
	if (rect.Width<0) {
		rect.X +=rect.Width;
		rect.Width = -rect.Width;
	}
	if (rect.Height<0) {
		rect.Y+=rect.Height;
		rect.Height = -rect.Height;
	}
}

void Normallize(RectF &rect){
//Ensure positive width and height
	if (rect.Width<0) {
		rect.X +=rect.Width;
		rect.Width = -rect.Width;
	}
	if (rect.Height<0) {
		rect.Y+=rect.Height;
		rect.Height = -rect.Height;
	}
}

IMPLEMENT_SERIAL(CDrawObj, CObject, 0)

CDrawObj::CDrawObj()
{
}

CDrawObj::~CDrawObj()
{
///	if(nTimerID)
///		timeKillEvent(nTimerID);
///	Remove();
}

CDrawObj::CDrawObj(const CRect& position)
{
	m_position = position;
	m_pDocument = NULL;

	//初始化所有数据
	m_LineStyle			= DashStyleSolid;
	m_bNoFill			= FALSE;
	m_nLineSize			= 2;
	m_clrFillColor		= RGB(0x00,0x00,0x00);
	m_clrLineColor		= RGB(100,0x00,0x00);

	m_clrBackColor		= RGB(0x00,0x00,0xff);		

	m_bNoFill = FALSE;

	m_bIsGroup = FALSE;
	m_strGroupName = "";

	m_nRoute = 0;
	m_bLock = FALSE;

	m_nPointNo = 0;					//动作点号

	m_nPercentFill = 100.0f;
}

void CDrawObj::Serialize(CArchive& ar)
{
	CObject::Serialize(ar);
	if (ar.IsStoring())
	{

	}
	else
	{
		// get the document back pointer from the archive
		m_pDocument = (CDrawDoc*)ar.m_pDocument;
		ASSERT_VALID(m_pDocument);
		ASSERT_KINDOF(CDrawDoc, m_pDocument);

		WORD wTemp;
		ar >> m_position;			
		ar >> wTemp;			m_LineStyle			= (DashStyle)wTemp;			
		ar >> wTemp;			m_bNoFill			= (BOOL)wTemp;		
		ar >> m_nLineSize;		
		ar.Read(&m_clrFillColor,sizeof(COLORREF));	
		ar.Read(&m_clrLineColor,sizeof(COLORREF));	
		ar.Read(&m_clrBackColor,sizeof(COLORREF));	
		ar >> wTemp;			m_bNoFill		= (BOOL)wTemp;
		ar >> wTemp;			m_bIsGroup		= (BOOL)wTemp;
		ar >> m_strGroupName;
		ar >> wTemp;			m_bIsUnit		= (BOOL)wTemp;
		ar >> m_strUnitName;
		ar >> wTemp;			m_bLock			= (BOOL)wTemp;
		ar >> m_nPointNo;
		ar.Read(&m_ActionStruct,sizeof(ActionStruct));

		Init();				//初始化
	}
}

void CDrawObj::Init()
{
	m_TempFillColor = m_clrFillColor;
	m_TempLineColor = m_clrLineColor;
//	nTimerID = timeSetEvent(200,1000,ActionProc,(DWORD)this,false ? TIME_ONESHOT : TIME_PERIODIC);
	bIsStartRay = FALSE;
	
	m_rectAction = m_position;
	m_nActionRoute = 0;
	m_bIsSwitch = FALSE;

}

void CDrawObj::Remove()
{
	delete this;
}

void CDrawObj::Draw(CDC*)
{
}

//
void CDrawObj::DrawTracker(CDC* pDC, TrackerState state)
{
	ASSERT_VALID(this);

	switch (state)
	{
	case normal:
		break;

	case selected:
	case active:
		{
			int nHandleCount = GetHandleCount();
			for (int nHandle = 1; nHandle <= nHandleCount; nHandle += 1)
			{
				CPoint handle = GetHandle(nHandle);
				CRect rect = m_position;
				rect.NormalizeRect();
				if(rect.Width() >5 || rect.Height()>5)
				{
					PatBlt(pDC->m_hDC,handle.x - 3, handle.y - 3, 7, 7, DSTINVERT);
				}
			}
		}
		break;
	}
}

// position is in logical
void CDrawObj::MoveTo(const CRect& position, CDrawView* pView)
{
	ASSERT_VALID(this);

	if (position == m_position)
		return;

	if (pView == NULL)
	{
		Invalidate();
		m_position = position;
		Invalidate();
	}
	else
	{
		pView->InvalObj(this);
		m_position = position;
		pView->InvalObj(this);
	}
	m_pDocument->SetModifiedFlag();
}

// Note: if bSelected, hit-codes start at one for the top-left
// and increment clockwise, 0 means no hit.
// If !bSelected, 0 = no hit, 1 = hit (anywhere)

// point is in logical coordinates
int CDrawObj::HitTest(CPoint point, CDrawView* pView, BOOL bSelected)
{
	ASSERT_VALID(this);
	ASSERT(pView != NULL);

	if (bSelected)
	{
		int nHandleCount = GetHandleCount();
		for (int nHandle = 1; nHandle <= nHandleCount; nHandle += 1)
		{
			// GetHandleRect returns in logical coords
			CRect rc = GetHandleRect(nHandle,pView);
			if (point.x >= rc.left && point.x < rc.right &&
				point.y <= rc.top && point.y > rc.bottom)
				return nHandle;
		}
	}
	else
	{
		if (point.x >= m_position.left && point.x < m_position.right &&
			point.y <= m_position.top && point.y > m_position.bottom)
			return 1;
	}
	return 0;
}

// rect must be in logical coordinates
BOOL CDrawObj::Intersects(const CRect& rect)
{
	ASSERT_VALID(this);

	CRect fixed = m_position;
	fixed.NormalizeRect();
	CRect rectT = rect;
	rectT.NormalizeRect();
	return !(rectT & fixed).IsRectEmpty();
}

int CDrawObj::GetHandleCount()
{
	ASSERT_VALID(this);
	//如果对象是组或单元对象则返回0
	if(m_bIsGroup)
		return 0;
	return 8;
}

// returns logical coords of center of handle
CPoint CDrawObj::GetHandle(int nHandle)
{
	ASSERT_VALID(this);
	int x, y, xCenter, yCenter;

	// this gets the center regardless of left/right and top/bottom ordering
	xCenter = m_position.left + m_position.Width() / 2;
	yCenter = m_position.top + m_position.Height() / 2;

	switch (nHandle)
	{
	default:
		ASSERT(FALSE);

	case 1:
		x = m_position.left;
		y = m_position.top;
		break;

	case 2:
		x = xCenter;
		y = m_position.top;
		break;

	case 3:
		x = m_position.right;
		y = m_position.top;
		break;

	case 4:
		x = m_position.right;
		y = yCenter;
		break;

	case 5:
		x = m_position.right;
		y = m_position.bottom;
		break;

	case 6:
		x = xCenter;
		y = m_position.bottom;
		break;

	case 7:
		x = m_position.left;
		y = m_position.bottom;
		break;

	case 8:
		x = m_position.left;
		y = yCenter;
		break;
	}

	return CPoint(x, y);
}

// return rectange of handle in logical coords
CRect CDrawObj::GetHandleRect(int nHandleID, CDrawView* pView)
{
	ASSERT_VALID(this);
	ASSERT(pView != NULL);

	CRect rect;
	// get the center of the handle in logical coords
	CPoint point = GetHandle(nHandleID);
	// convert to client/device coords
	pView->DocToClient(point);
	// return CRect of handle in device coords
	rect.SetRect(point.x-3, point.y-3, point.x+3, point.y+3);
	pView->ClientToDoc(rect);

	return rect;
}

HCURSOR CDrawObj::GetHandleCursor(int nHandle)
{
	ASSERT_VALID(this);

	LPCTSTR id;
	switch (nHandle)
	{
	default:
		ASSERT(FALSE);

	case 1:
	case 5:
		id = IDC_SIZENWSE;
		break;

	case 2:
	case 6:
		id = IDC_SIZENS;
		break;

	case 3:
	case 7:
		id = IDC_SIZENESW;
		break;

	case 4:
	case 8:
		id = IDC_SIZEWE;
		break;
	}

	return AfxGetApp()->LoadStandardCursor(id);
}

// point must be in logical
void CDrawObj::MoveHandleTo(int nHandle, CPoint point, CDrawView* pView)
{
	ASSERT_VALID(this);

	CRect position = m_position;
	switch (nHandle)
	{
	default:
		ASSERT(FALSE);

	case 1:
		position.left = point.x;
		position.top = point.y;
		break;

	case 2:
		position.top = point.y;
		break;

	case 3:
		position.right = point.x;
		position.top = point.y;
		break;

	case 4:
		position.right = point.x;
		break;

	case 5:
		position.right = point.x;
		position.bottom = point.y;
		break;

	case 6:
		position.bottom = point.y;
		break;

	case 7:
		position.left = point.x;
		position.bottom = point.y;
		break;

	case 8:
		position.left = point.x;
		break;
	}

	MoveTo(position, pView);
}

void CDrawObj::Invalidate()
{
	ASSERT_VALID(this);
	if(m_nActionRoute ==0)
		m_pDocument->UpdateAllViews(NULL, HINT_UPDATE_DRAWOBJ, this);
	else
		m_pDocument->UpdateAllViews(NULL, HINT_UPDATE_ROUTE, this);
}

void CDrawObj::Invalidate(CRect rect)
{
	m_pDocument->UpdateAllViews(NULL, HINT_UPDATE_SIZE, this);
}

void CDrawObj::Invalidate(CPoint pt)
{
	m_pDocument->UpdateAllViews(NULL, HINT_UPDATE_MOVE, this);
}

CDrawObj* CDrawObj::Clone(CDrawDoc* pDoc)
{
	ASSERT_VALID(this);

	CDrawObj* pClone = new CDrawObj(m_position);

	ASSERT_VALID(pClone);

	if (pDoc != NULL)
		pDoc->Add(pClone);

	return pClone;
}

void CDrawObj::OnEditProperties()
{
	ASSERT_VALID(this);


	
}

void CDrawObj::OnOpen(CDrawView* /*pView*/ )
{
	OnEditProperties();
}

void CDrawObj::SetLineColor(COLORREF color)
{
	ASSERT_VALID(this);

	m_clrLineColor = color;
	Invalidate();
	m_pDocument->SetModifiedFlag();
}

void CDrawObj::SetFillColor(COLORREF color)
{
	ASSERT_VALID(this);

	m_clrFillColor = color;
	Invalidate();
	m_pDocument->SetModifiedFlag();
}

void CDrawObj::SetFillStyle(HatchStyle FillStyle,COLORREF fkColor,COLORREF bkColor)
{
	Invalidate();
	m_pDocument->SetModifiedFlag();

}



#ifdef _DEBUG
void CDrawObj::AssertValid()
{
	ASSERT(m_position.left <= m_position.right);
	ASSERT(m_position.bottom <= m_position.top);
}
#endif


///////////////////////////////////////////////////////////////////////////
/*
IMPLEMENT_SERIAL(CDrawOleObj, CDrawObj, 0)

BOOL CDrawOleObj::c_bShowItems = TRUE;

CDrawOleObj::CDrawOleObj() : m_extent(0,0)
{
	m_pClientItem = NULL;
}

CDrawOleObj::CDrawOleObj(const CRect& position)
	: CDrawObj(position), m_extent(0, 0)
{
	m_pClientItem = NULL;
}

CDrawOleObj::~CDrawOleObj()
{
	if (m_pClientItem != NULL)
	{
		m_pClientItem->Release();
		m_pClientItem = NULL;
	}
}

void CDrawOleObj::Remove()
{
	if (m_pClientItem != NULL)
	{
		m_pClientItem->Delete();
		m_pClientItem = NULL;
	}
	CDrawObj::Remove();
}

void CDrawOleObj::Serialize( CArchive& ar )
{
	ASSERT_VALID(this);

	CDrawObj::Serialize(ar);

	if (ar.IsStoring())
	{
		ar << m_extent;
		ar << m_pClientItem;
	}
	else
	{
		ar >> m_extent;
		ar >> m_pClientItem;
		m_pClientItem->m_pDrawObj = this;
	}
}

CDrawObj* CDrawOleObj::Clone(CDrawDoc* pDoc)
{
	ASSERT_VALID(this);

	AfxGetApp()->BeginWaitCursor();

	CDrawOleObj* pClone = NULL;
	CDrawItem* pItem = NULL;
	TRY
	{
		// perform a "deep copy" -- need to copy CDrawOleObj and the CDrawItem
		//  that it points to.
		pClone = new CDrawOleObj(m_position);
		pItem = new CDrawItem(m_pDocument, pClone);
		if (!pItem->CreateCloneFrom(m_pClientItem))
			AfxThrowMemoryException();
		ASSERT_VALID(pClone);

		if (pDoc != NULL)
			pDoc->Add(pClone);
	}
	CATCH_ALL(e)
	{
		if(pItem)
			pItem->Delete();

		if(pClone)
		{
			pClone->m_pClientItem = NULL;
			pClone->Remove();
		}
		AfxGetApp()->EndWaitCursor();

		THROW_LAST();
	}
	END_CATCH_ALL

	AfxGetApp()->EndWaitCursor();
	return pClone;
}

void CDrawOleObj::Draw(CDC* pDC)
{
	ASSERT_VALID(this);

	CDrawItem* pItem = m_pClientItem;
	if (pItem != NULL)
	{
		// draw the OLE item itself
		pItem->Draw(pDC, m_position);

		// don't draw tracker in print preview or on printer
		if (!pDC->IsPrinting())
		{
			// use a CRectTracker to draw the standard effects
			CRectTracker tracker;
			tracker.m_rect = m_position;
			pDC->LPtoDP(tracker.m_rect);

			if (c_bShowItems)
			{
				// put correct border depending on item type
				if (pItem->GetType() == OT_LINK)
					tracker.m_nStyle |= CRectTracker::dottedLine;
				else
					tracker.m_nStyle |= CRectTracker::solidLine;
			}

			// put hatching over the item if it is currently open
			if (pItem->GetItemState() == COleClientItem::openState ||
				pItem->GetItemState() == COleClientItem::activeUIState)
			{
				tracker.m_nStyle |= CRectTracker::hatchInside;
			}
			tracker.Draw(pDC);
		}
	}
}

void CDrawOleObj::OnOpen(CDrawView* pView)
{
	AfxGetApp()->BeginWaitCursor();
	m_pClientItem->DoVerb(
		GetKeyState(VK_CONTROL) < 0 ? OLEIVERB_OPEN : OLEIVERB_PRIMARY,
		pView);
	AfxGetApp()->EndWaitCursor();
}

void CDrawOleObj::OnEditProperties()
{
	// using COlePropertiesDialog directly means no scaling
	COlePropertiesDialog dlg(m_pClientItem, 100, 100, NULL);

	dlg.DoModal();
}

// position is in logical
void CDrawOleObj::MoveTo(const CRect& position, CDrawView* pView)
{
	ASSERT_VALID(this);

	if (position == m_position)
		return;

	// call base class to update position
	CDrawObj::MoveTo(position, pView);

	// update position of in-place editing session on position change
	if (m_pClientItem->IsInPlaceActive())
		m_pClientItem->SetItemRects();
}
*/

