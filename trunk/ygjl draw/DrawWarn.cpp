// DrawWarn.cpp: implementation of the CDrawWarn class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Draw.h"
#include "DrawWarn.h"
#include "drawdoc.h"
#include "drawobj.h"
#include "WarnSetDialog.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
IMPLEMENT_SERIAL(CDrawWarn, CDrawObj, 0)

CDrawWarn::CDrawWarn()
{
}

CDrawWarn::~CDrawWarn()
{
}

CDrawWarn::CDrawWarn(const CRect& position)
	: CDrawObj(position)
{
	ASSERT_VALID(this);
	m_ctlBackColor = RGB(255,255,255);			//背景颜色
	m_ctlLineColor = RGB(  0,  0,255);			//线条颜色
	m_ctlTextColor = RGB(255,  0,  0);			//字体颜色
	m_ctlTitleColor = RGB(0,0,200);

	m_bIsAutoSize =	TRUE;

	m_nCellWidth = 0;
	m_nCellHeight = 0;
	m_nRowCount = 5;
	m_nColCount = 11;

	m_fontStyle			= FontStyleRegular;
	m_fontSize			= 9;
	m_fontName			= "Arial";
	m_trimmingSyle		= StringTrimmingNone;

	m_nPercent = new UINT[m_nRowCount];

}

void CDrawWarn::Serialize(CArchive& ar)
{
	ASSERT_VALID(this);

	CDrawObj::Serialize(ar);
	if (ar.IsStoring())
	{
		ar.Write(&m_ctlBackColor,sizeof(COLORREF));
		ar.Write(&m_ctlLineColor,sizeof(COLORREF));
		ar.Write(&m_ctlTextColor,sizeof(COLORREF));
		ar.Write(&m_ctlTitleColor,sizeof(COLORREF));
		ar << m_nColCount;
		ar << m_nRowCount;
		ar << m_nCellWidth;
		ar << m_nCellHeight;
		ar << (WORD)m_bIsAutoSize;
		for(int i=0;i<m_nRowCount;i++)
			ar << m_nPercent[i];

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

	pStrWarn = new STRWARN[m_nColCount];
	AddWarn("1","2004/12/12","12:00","高报警","电压过低");
	AddWarn("2","2004/12/12","12:00","高报警","电压过低");
	AddWarn("3","2004/12/12","12:00","高报警","电压过低");
	AddWarn("4","2004/12/12","12:00","高报警","电压过低");
	AddWarn("5","2004/12/12","12:00","高报警","电压过低");
	AddWarn("6","2004/12/12","12:00","高报警","电压过低");
	AddWarn("7","2004/12/12","12:00","高报警","电压过低");
	AddWarn("8","2004/12/12","12:00","高报警","电压过低");
	AddWarn("9","2004/12/12","12:00","高报警","电压过低");
	AddWarn("10","2004/12/12","12:00","高报警","电压过低");
	AddWarn("11","2004/12/12","12:00","高报警","电压过低");
	AddWarn("12","2004/12/12","12:00","高报警","电压过低");

	Rect GdiRect (rect.TopLeft().x,rect.TopLeft().y,rect.Size().cx,rect.Size().cy); 

	Color crBackColor,crTitleColor,crLineColor,crTextColor ;
	crBackColor.SetFromCOLORREF(m_ctlBackColor);
	crTitleColor.SetFromCOLORREF(m_ctlTitleColor );
	crLineColor.SetFromCOLORREF(m_ctlLineColor);
	crTextColor.SetFromCOLORREF(m_ctlTextColor);

	Graphics graphics (pDC->m_hDC);
	Graphics Textgraphics (pDC->m_hDC);
	SolidBrush  solidBrush(crBackColor);
	SolidBrush  TitleBrush(crTitleColor);
	SolidBrush  TextBrush(crTextColor);
	Pen pen(crLineColor,1);
	
	graphics.FillRectangle(&solidBrush,GdiRect);

	BSTR bstr = _com_util::ConvertStringToBSTR(m_fontName);
///	WCHAR *fn = new unsigned short[m_fontName.GetLength()+1];;
///	wcscpy(fn,bstr);
				
	FontFamily  fontFamily(bstr);
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
///				int len = m_strButton.GetLength();
				bstr = _com_util::ConvertStringToBSTR(m_strButton);
///				WCHAR *strButton = new unsigned short[len];
///				wcscpy(strButton,bstr);
				RectF theRect (m_CellRect.TopLeft().x,m_CellRect.TopLeft().y,m_CellRect.Size().cx,m_CellRect.Size().cy);
				Matrix matrix(1,0,0,-1,0,0);
				Textgraphics.SetTransform(&matrix);
				
				theRect.Y *=-1;
				theRect.Height*=-1;
				Normallize (theRect);	
				Textgraphics.FillRectangle(&TitleBrush,theRect);
				Textgraphics.DrawString(bstr,-1,&font, theRect,&stringFormat, &TextBrush);
			}
			else					//画文字
			{
				StringFormat stringFormat;
				stringFormat.SetAlignment(StringAlignmentNear);
				stringFormat.SetLineAlignment(StringAlignmentNear);

				CString strWarn;
				if(i == 1)
					strWarn = pStrWarn[j].strPoint;
				if(i == 2)
					strWarn = pStrWarn[j].strDate;
				if(i == 3)
					strWarn = pStrWarn[j].strTime;
				if(i == 4)
					strWarn = pStrWarn[j].strText;
				if(i == 5)
					strWarn = pStrWarn[j].strWarn;

				strWarn.TrimRight();
///				int len = strWarn.GetLength();
				bstr = _com_util::ConvertStringToBSTR(strWarn);
///				WCHAR *strButton = new unsigned short[len];
///				wcscpy(strButton,bstr);
				RectF theRect (m_CellRect.TopLeft().x,m_CellRect.TopLeft().y,m_CellRect.Size().cx,m_CellRect.Size().cy);
				Matrix matrix(1,0,0,-1,0,0);
				Textgraphics.SetTransform(&matrix);
				
				theRect.Y *=-1;
				theRect.Height*=-1;
				Normallize (theRect);	
				Textgraphics.DrawString(bstr,-1,&font, theRect,&stringFormat, &TextBrush);
			}
		}
	}
	graphics.ReleaseHDC(pDC->m_hDC);
}

void CDrawWarn::DrawCell(CDC *pDC, Rect rect, int nCol, int nRow)
{

}

void CDrawWarn::AddWarn(CString strPoint, CString strDate, CString strTime, CString strText, CString strWarn)
{
//	for(int i=0;i<m_nColCount;i++)
//	{
		pStrWarn[0].strPoint = strPoint;
		pStrWarn[0].strDate = strDate;
		pStrWarn[0].strTime = strTime;
		pStrWarn[0].strText = strText;
		pStrWarn[0].strWarn = strWarn;
//	}
	for(int i=m_nColCount-1;i>0;i--)
	{
		pStrWarn[i].strPoint = pStrWarn[i-1].strPoint;
		pStrWarn[i].strDate = pStrWarn[i-1].strDate;
		pStrWarn[i].strTime = pStrWarn[i-1].strTime;
		pStrWarn[i].strText = pStrWarn[i-1].strText;
		pStrWarn[i].strWarn = pStrWarn[i-1].strWarn;
	}
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
	CWarnSetDialog dlg;
	dlg.m_clrBackColor  = m_ctlBackColor;
	dlg.m_bIsAutoSize = m_bIsAutoSize;
	dlg.m_clrLineColor = m_ctlLineColor;
	dlg.m_clrTextColor = m_ctlTextColor;
	dlg.m_clrTitleColor = m_ctlTitleColor;
	dlg.m_nCol = m_nColCount;
	dlg.m_nPoint = m_nPercent[0];
	dlg.m_nDate = m_nPercent[1];
	dlg.m_nTime = m_nPercent[2];
	dlg.m_nText = m_nPercent[3];
	dlg.m_nWarn = m_nPercent[4];

	if(dlg.DoModal()!= IDOK)
		return;
	
	m_ctlBackColor = dlg.m_clrBackColor;
	m_bIsAutoSize  = dlg.m_bIsAutoSize;
	m_ctlLineColor = dlg.m_clrLineColor;
	m_ctlTextColor = dlg.m_clrTextColor;
	m_ctlTitleColor = dlg.m_clrTitleColor;
	m_nColCount = dlg.m_nCol;

	m_nPercent[0] = dlg.m_nPoint;
	m_nPercent[1] = dlg.m_nDate;
	m_nPercent[2] = dlg.m_nTime;
	m_nPercent[3] = dlg.m_nText;
	m_nPercent[4] = dlg.m_nWarn;

	//进行数据交换
	Invalidate();
	m_pDocument->SetModifiedFlag();
}