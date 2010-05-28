// DrawRotary.cpp: implementation of the CDrawRotary class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "GUI_VisualStudio.h"
#include "DrawRotary.h"
#include "DrawDoc.h"
#include <math.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
IMPLEMENT_SERIAL(CDrawRotary, CDrawObj, 0)
CDrawRotary::CDrawRotary()
{
}

CDrawRotary::~CDrawRotary()
{
}

CDrawRotary::CDrawRotary(const CRect& position)
	: CDrawObj(position)
{
	ASSERT_VALID(this);
}

void CDrawRotary::Serialize(CArchive& ar)
{
	ASSERT_VALID(this);

	CDrawObj::Serialize(ar);
	if (ar.IsStoring())
	{
	}
	else
	{
		ar.Read(&m_RotaryStruct,sizeof(RotaryStruct));

		m_bIsAction = FALSE;
	}
}
/*
void CDrawRotary::Remove()
{
	delete this;
}
*/
void CDrawRotary::Draw(CDC* pDC)
{
	CRect rect = m_position;
	rect.NormalizeRect();
	int nWidth = rect.Width();
	int nHeight = rect.Height();
	int nMaxWidthHeight = max(nWidth, nHeight);
	rect.bottom = rect.top + nMaxWidthHeight;
	rect.right = rect.left + nMaxWidthHeight;
	m_position = rect;

	Rect GdiRect (rect.TopLeft().x,rect.TopLeft().y,rect.Size().cx,rect.Size().cy); 

	Color  clrLineColor,clrFillColor, clrRotaryColor;
	clrLineColor.SetFromCOLORREF(m_RotaryStruct.clrLineColor);
	clrFillColor.SetFromCOLORREF(m_RotaryStruct.clrFillColor );
	clrRotaryColor.SetFromCOLORREF(m_RotaryStruct.clrRotaryColor);
	
	Graphics graphics(pDC->m_hDC);
	Pen		pen(clrLineColor, 1);
	SolidBrush FillBrush(clrFillColor); 
	SolidBrush RotaryBrush(clrRotaryColor); 

	graphics.FillEllipse(&FillBrush,GdiRect);
	graphics.DrawEllipse(&pen,GdiRect);

		graphics.FillPie(&RotaryBrush, GdiRect, m_RotaryStruct.nAngle, 40);
		graphics.FillPie(&RotaryBrush, GdiRect, m_RotaryStruct.nAngle+90, 40);
		graphics.FillPie(&RotaryBrush, GdiRect, m_RotaryStruct.nAngle+180, 40);
		graphics.FillPie(&RotaryBrush, GdiRect, m_RotaryStruct.nAngle+270, 40);

	graphics.ReleaseHDC(pDC->m_hDC);
}
/*
int CDrawRotary::GetHandleCount()
{
	ASSERT_VALID(this);
	return CDrawObj::GetHandleCount();
}

// returns center of handle in logical coordinates
CPoint CDrawRotary::GetHandle(int nHandle)
{
	ASSERT_VALID(this);
	return CDrawObj::GetHandle(nHandle);
}

HCURSOR CDrawRotary::GetHandleCursor(int nHandle)
{
	ASSERT_VALID(this);
	return CDrawObj::GetHandleCursor(nHandle);
}

void CDrawRotary::MoveHandleTo(int nHandle, CPoint point, CDrawView* pView)
{
	ASSERT_VALID(this);
	CDrawObj::MoveHandleTo(nHandle, point, pView);
}

BOOL CDrawRotary::Intersects(const CRect& rect)
{
	ASSERT_VALID(this);

	CRect rectT = rect;
	rectT.NormalizeRect();

	CRect fixed = m_position;
	fixed.NormalizeRect();
	if ((rectT & fixed).IsRectEmpty())
		return FALSE;
	return TRUE;
}

CDrawObj* CDrawRotary::Clone(CDrawDoc* pDoc)
{
	ASSERT_VALID(this);

	CDrawRotary* pClone = new CDrawRotary(m_position);

	ASSERT_VALID(pClone);

	if (pDoc != NULL)
		pDoc->Add(pClone);

	ASSERT_VALID(pClone);
	return pClone;
}

void CDrawRotary::Invalidate()
{
	ASSERT_VALID(this);
	CDrawObj::Invalidate();
}

void CDrawRotary::OnEditProperties()
{
	ASSERT_VALID(this);
	Invalidate();
	m_pDocument->SetModifiedFlag();
}
*/
void CDrawRotary::StartAction()
{
	if(m_bIsAction)
	{
		if(m_RotaryStruct.bContrarotate)
			m_RotaryStruct.nAngle += m_RotaryStruct.nSpeed;   
		else
			m_RotaryStruct.nAngle +=  360 - m_RotaryStruct.nSpeed;  
		Invalidate();
	}
}