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
#include "Draw.h"

#include "drawdoc.h"
#include "drawview.h"
#include "drawobj.h"

///#include "cntritem.h"
#include "EffectDlg.h"
///#include "GroupProperty.h"

#include <math.h>

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
///	if(m_RectPath.GetSize() > 0)
///	{
///		m_RectPath.RemoveAll();
///	}
}

CDrawObj::CDrawObj(const CRect& position)
{
	m_position = position;
	m_pDocument = NULL;

	//初始化所有数据
	m_LineStyle			= DashStyleSolid;
	m_bNoFill			= FALSE;
	m_nLineSize			= 1;
	m_clrFillColor		= RGB(0x00,0x00,0x00);
	m_clrLineColor		= RGB(100,0x00,0x00);
	m_clrBackColor		= RGB(0x00,0x00,0xff);		
	m_bNoFill			= FALSE;
	m_bIsGroup			= FALSE;
	m_bIsUnit			= FALSE;
	m_strGroupName		= "";
	m_strUnitName		= "";

	m_nRoute			= 0;
	m_bLock				= FALSE;
	m_nPointNo			= 0;						//动作点号

	m_ActionStruct.stcLineChange.nPoint = 0 ;
	m_ActionStruct.stcLineChange.clrInLineColor = RGB(0,255,0);
	m_ActionStruct.stcLineChange.clrOutLineColor = RGB(255,0,0);
	m_ActionStruct.stcLineChange.clrCommErrorLineColor = RGB(255,255,0);

	m_ActionStruct.stcFillChange.nPoint = 0 ;
	m_ActionStruct.stcFillChange.clrInFillColor = RGB(0,255,0);
	m_ActionStruct.stcFillChange.clrOutFillColor = RGB(255,0,0);
	m_ActionStruct.stcFillChange.clrCommErrorFillColor = RGB(255,255,0);

	m_ActionStruct.stcPHChange.pufdata = 65538;
	m_ActionStruct.stcPHChange.clrFillColor = RGB(  0,   0, 255);
	m_ActionStruct.stcPVChange.pufdata = 65538;
	m_ActionStruct.stcPVChange.clrFillColor = RGB(  0,   0, 255);

	m_ActionStruct.stcRayChange.nMax = 65535;

	m_ActionStruct.bIsFillColorChange = FALSE;
	m_ActionStruct.bIsLineColorChange = FALSE;
	m_ActionStruct.bIsPencentFillH = FALSE;
	m_ActionStruct.bIsPencentFillV = FALSE;
	m_ActionStruct.bIsRayChange = FALSE;

}

void CDrawObj::Serialize(CArchive& ar)
{
	CObject::Serialize(ar);
	
	if (ar.IsStoring())
	{
		ar << m_position;							//坐标
		ar << (WORD)m_LineStyle;					//线条风格
		ar << (WORD)m_bNoFill;						//是否填充
		ar << m_nLineSize;							//线条尺寸
		ar.Write(&m_clrFillColor,sizeof(COLORREF));	//填充颜色
		ar.Write(&m_clrLineColor,sizeof(COLORREF));	//线条颜色
		ar.Write(&m_clrBackColor,sizeof(COLORREF));	//背景颜色
		ar << (WORD)m_bNoFill;
		ar << (WORD)m_bIsGroup;
		ar << m_strGroupName;
		ar << (WORD)m_bIsUnit;
		ar << m_strUnitName;

		ar << (WORD)m_bLock;
		ar << m_nPointNo;
		ar.Write(&m_ActionStruct,sizeof(ActionStruct));
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
	}
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
	if(m_bIsUnit)
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
	m_pDocument->UpdateAllViews(NULL, HINT_UPDATE_DRAWOBJ, this);
}

CDrawObj* CDrawObj::Clone(CDrawDoc* pDoc)
{
	ASSERT_VALID(this);

	CDrawObj* pClone = new CDrawObj(m_position);

	pClone->m_LineStyle			= m_LineStyle;				//线条风格
	pClone->m_clrFillColor		= m_clrFillColor;			//填充颜色
	pClone->m_clrLineColor		= m_clrLineColor;			//线条颜色
	pClone->m_bNoFill			= m_bNoFill;				//是否填充
	pClone->m_nLineSize			= m_nLineSize;				//线条尺寸
	pClone->m_clrBackColor		= m_clrBackColor;			//结束颜色
	pClone->m_bIsGroup			= m_bIsGroup;			
	pClone->m_nPointNo			= m_nPointNo;					//动作点号

	ASSERT_VALID(pClone);

	if (pDoc != NULL)
		pDoc->Add(pClone);

	return pClone;
}

void CDrawObj::OnEditProperties()
{
	ASSERT_VALID(this);
	{
		
		CEffectDlg dlg;
		//以下是数据交换
		dlg.m_LineStyle			= m_LineStyle;
		dlg.m_bNoFill			= m_bNoFill ;
		dlg.m_nLineSize			= m_nLineSize;
		dlg.m_clrFillColor		= m_clrFillColor;
		dlg.m_clrLineColor		= m_clrLineColor;
		
		if(dlg.DoModal() != IDOK)
			return;
		
		//以下是数据交换
		m_LineStyle			= dlg.m_LineStyle ;
		m_bNoFill			= dlg.m_bNoFill ;
		m_nLineSize			= dlg.m_nLineSize;
		m_clrFillColor		= dlg.m_clrFillColor;
		m_clrLineColor		= dlg.m_clrLineColor;
	}
	Invalidate();
	m_pDocument->SetModifiedFlag();
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
/*
void CDrawObj::AddCarRect(CRect rc)
{
	ASSERT_VALID(this);

	m_RectPath.Add(rc);
	m_pDocument->SetModifiedFlag();

}
*/

#ifdef _DEBUG
void CDrawObj::AssertValid()
{
	ASSERT(m_position.left <= m_position.right);
	ASSERT(m_position.bottom <= m_position.top);
}
#endif


///////////////////////////////////////////////////////////////////////////


