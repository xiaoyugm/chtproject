// DrawWarn.cpp: implementation of the CDrawWarn class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "GUI_VisualStudio.h"
#include "DrawWarn.h"
#include "drawdoc.h"
#include "drawobj.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

extern CStrWarn m_CStrWarn[MAX_ROW];
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
IMPLEMENT_SERIAL(CDrawWarn, CDrawObj, 0)

CDrawWarn::CDrawWarn()
{
}

CDrawWarn::~CDrawWarn()
{
	if (m_nPercent != NULL)
		delete[] m_nPercent;
}

CDrawWarn::CDrawWarn(const CRect& position)
	: CDrawObj(position)
{
	ASSERT_VALID(this);
}

void CDrawWarn::Serialize(CArchive& ar)
{
	ASSERT_VALID(this);

	CDrawObj::Serialize(ar);
	if (ar.IsStoring())
	{
	}
	else
	{
		WORD wTemp;
		ar.Read(&m_ctlBackColor,sizeof(COLORREF));
		ar.Read(&m_ctlLineColor,sizeof(COLORREF));
		ar.Read(&m_ctlTextColor,sizeof(COLORREF));
		ar.Read(&m_ctlTitleColor,sizeof(COLORREF));
		ar >> m_nColCount;
		ar >> m_nRowCount;
		ar >> m_nCellWidth;
		ar >> m_nCellHeight;
		ar >> wTemp;		m_bIsAutoSize = (BOOL)wTemp;
		m_nPercent = new UINT[m_nRowCount];
		for(int i=0;i<m_nRowCount;i++)
			ar >> m_nPercent[i];

		m_fontStyle			= FontStyleRegular;
		m_fontSize			= 9;
		m_fontName			= "Arial";
		m_trimmingSyle		= StringTrimmingNone;
	}
}

void CDrawWarn::Draw(CDC* pDC)
{
	ASSERT_VALID(this);
	CRect rect = m_position;
	rect.NormalizeRect();

	if(rect.Width() < 10 || rect.Height()<10)
		return;

	Rect GdiRect (rect.TopLeft().x,rect.TopLeft().y,rect.Size().cx,rect.Size().cy); 

	Color crBackColor,crTitleColor,crLineColor,crTextColor ;
	crBackColor.SetFromCOLORREF(m_ctlBackColor);
	crTitleColor.SetFromCOLORREF(m_ctlTitleColor );
	crLineColor.SetFromCOLORREF(m_ctlLineColor);
	crTextColor.SetFromCOLORREF(m_ctlTextColor);

	Graphics graphics (pDC->m_hDC);
	graphics.SetSmoothingMode (SmoothingModeHighSpeed);
	Graphics Textgraphics (pDC->m_hDC);
	SolidBrush  solidBrush(crBackColor);
	SolidBrush  TitleBrush(crTitleColor);
	SolidBrush  TextBrush(crTextColor);
	Pen pen(crLineColor,1);
	
	graphics.FillRectangle(&solidBrush,GdiRect);

        		BSTR bstr = m_fontName.AllocSysString();
///	BSTR bstr = _com_util::ConvertStringToBSTR(m_fontName);
	FontFamily  fontFamily(bstr);
   	SysFreeString(bstr);
	Font font(&fontFamily, m_fontSize, m_fontStyle, UnitPoint);

	for(int j =1; j<= m_nColCount; j++)
	{
		m_nCellWidth = 0;
		for(int i=1; i<= m_nRowCount; i++)
		{
			CRect rc = rect;
			if(m_bIsAutoSize)
			{
				m_nCellWidth = rect.Width()/m_nRowCount;
				m_nCellHeight = rect.Height()/m_nColCount;
				rc.TopLeft().x += (i-1)*m_nCellWidth;
				rc.TopLeft().y += (j-1)*m_nCellHeight;
				m_CellRect = CRect(rc.TopLeft(),CSize(m_nCellWidth,m_nCellHeight));
				m_CellRect.NormalizeRect();
			}
			else
			{
				rc.TopLeft().x += m_nCellWidth;
				m_nCellWidth += rect.Width()*m_nPercent[i-1]/100;
				m_nCellHeight = rect.Height()/m_nColCount;
				rc.TopLeft().y += (j-1)*m_nCellHeight;	
				m_CellRect = CRect(rc.TopLeft(),CSize(rect.Width()*m_nPercent[i-1]/100,m_nCellHeight));
				m_CellRect.NormalizeRect();
			}

			Rect CellRect(m_CellRect.TopLeft().x,m_CellRect.TopLeft().y,m_CellRect.Size().cx,m_CellRect.Size().cy);

			graphics.DrawRectangle(&pen,CellRect);
			
			if(j == m_nColCount)	//画标题
			{
				StringFormat stringFormat;
				stringFormat.SetAlignment(StringAlignmentCenter);
				stringFormat.SetLineAlignment(StringAlignmentCenter);
				stringFormat.SetFormatFlags(StringFormatFlagsDirectionRightToLeft);
				stringFormat.SetTrimming(m_trimmingSyle);

				CString m_strButton;
				if(i == 1)
					m_strButton = "点号";
				if(i == 2)
					m_strButton = "数据";
				if(i == 3)
					m_strButton = "说明";
				if(i == 4)
					m_strButton = "报警原因";
				if(i == 5)
					m_strButton = "时间";

				m_strButton.TrimRight();
        		bstr = m_strButton.AllocSysString();
///				bstr = _com_util::ConvertStringToBSTR(m_strButton);
				RectF theRect (m_CellRect.TopLeft().x,m_CellRect.TopLeft().y,m_CellRect.Size().cx,m_CellRect.Size().cy);
				Matrix matrix(1,0,0,-1,0,0);
				Textgraphics.SetTransform(&matrix);
				
				theRect.Y *=-1;
				theRect.Height*=-1;
				Normallize (theRect);	
				Textgraphics.FillRectangle(&TitleBrush,theRect);
				Textgraphics.DrawString(bstr,-1,&font, theRect,&stringFormat, &TextBrush);
            	SysFreeString(bstr);
			}
			else 
			{					//画文字  m_CStrWarn      pStrWarn
				StringFormat stringFormat;
				stringFormat.SetAlignment(StringAlignmentNear);
				stringFormat.SetLineAlignment(StringAlignmentNear);

            	CString  strWarn;
/*				if(i == 1)
					strWarn = m_CStrWarn[j].strPoint;
				if(i == 2)
					strWarn = m_CStrWarn[j].strDate;
				if(i == 3)
					strWarn = m_CStrWarn[j].strTime;
				if(i == 4)
					strWarn = m_CStrWarn[j].strText;
				if(i == 5)
					strWarn = m_CStrWarn[j].strWarn;
*/
				strWarn.TrimRight();
        		bstr = strWarn.AllocSysString();
///				bstr = _com_util::ConvertStringToBSTR(strWarn);

				RectF theRect (m_CellRect.TopLeft().x,m_CellRect.TopLeft().y,m_CellRect.Size().cx,m_CellRect.Size().cy);
				Matrix matrix(1,0,0,-1,0,0);
				Textgraphics.SetTransform(&matrix);
				
				theRect.Y *=-1;
				theRect.Height*=-1;
				Normallize (theRect);	
				Textgraphics.DrawString(bstr,-1,&font, theRect,&stringFormat, &TextBrush);
             	SysFreeString(bstr);
			}			
		}
	}
	graphics.ReleaseHDC(pDC->m_hDC);
}

void CDrawWarn::Invalidate()
{
	ASSERT_VALID(this);
	m_pDocument->UpdateAllViews(NULL, HINT_UPDATE_DRAWOBJ, this);
}

void CDrawWarn::StartAction()
{
		Invalidate();
}
/*
void CDrawWarn::DrawCell(CDC *pDC, Rect rect, int nCol, int nRow)
{

}

int CDrawWarn::GetHandleCount()
{
	ASSERT_VALID(this);
	return CDrawObj::GetHandleCount();
}

// returns center of handle in logical coordinates
CPoint CDrawWarn::GetHandle(int nHandle)
{
	ASSERT_VALID(this);

	return CDrawObj::GetHandle(nHandle);
}

HCURSOR CDrawWarn::GetHandleCursor(int nHandle)
{
	ASSERT_VALID(this);

	return CDrawObj::GetHandleCursor(nHandle);
}

// point is in logical coordinates
void CDrawWarn::MoveHandleTo(int nHandle, CPoint point, CDrawView* pView)
{
	ASSERT_VALID(this);
	CDrawObj::MoveHandleTo(nHandle, point, pView);
}

// rect must be in logical coordinates
BOOL CDrawWarn::Intersects(const CRect& rect)
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

CDrawObj* CDrawWarn::Clone(CDrawDoc* pDoc)
{
	ASSERT_VALID(this);

	CDrawWarn* pClone = new CDrawWarn(m_position);
	pClone->m_ctlBackColor = m_ctlBackColor;
	pClone->m_bIsAutoSize = m_bIsAutoSize;
	pClone->m_ctlLineColor = m_ctlLineColor;
	pClone->m_ctlTextColor = m_ctlTextColor;
	pClone->m_ctlTitleColor = m_ctlTitleColor;
	pClone->m_nColCount = m_nColCount;
	pClone->m_nCellWidth = m_nCellWidth;
	pClone->m_nCellHeight = m_nCellHeight;
	pClone->m_nRowCount = m_nRowCount;
	pClone->m_nColCount = m_nColCount;
	pClone->m_fontStyle = m_fontStyle;
	pClone->m_fontSize  = m_fontSize;
	pClone->m_fontName  = m_fontName;
	pClone->m_trimmingSyle = m_trimmingSyle;

	if (pDoc != NULL)
		pDoc->Add(pClone);

	ASSERT_VALID(pClone);
	return pClone;
}

void CDrawWarn::OnEditProperties()			//编辑属性
{

}
*/