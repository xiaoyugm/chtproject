// DrawButton.cpp: implementation of the CDrawButton class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "GUI_VisualStudio.h"
#include "DrawButton.h"
#include "drawobj.h"
#include "drawdoc.h"
#include "drawview.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
IMPLEMENT_SERIAL(CDrawButton, CDrawObj, 0)

CDrawButton::CDrawButton()
{
}

CDrawButton::~CDrawButton()
{
}

CDrawButton::CDrawButton(const CRect& position)
	: CDrawObj(position)
{
	ASSERT_VALID(this);
}

void CDrawButton::Serialize(CArchive& ar)
{
	ASSERT_VALID(this);

	CDrawObj::Serialize(ar);
	if (ar.IsStoring())
	{
	}
	else
	{
		WORD wTemp;
		ar >> m_strButton;
		ar >> m_fontName;
		ar >> m_fontSize;
		ar >> wTemp;		m_fontAlignment  = (StringAlignment)wTemp;
		ar >> wTemp;		m_fontStyle  = (FontStyle)wTemp;
		ar >> wTemp;		m_trimmingSyle  = (StringTrimming)wTemp;
		ar >> wTemp;		m_format  = (StringFormatFlags)wTemp;
		ar.Read(&m_color,sizeof(COLORREF));
		ar >> wTemp;		m_nShape = (Shape)wTemp;
		ar >> m_nPointNo;
		ar >> wTemp;		m_bIsRunShowValue	= (BOOL)wTemp;
		ar >> wTemp;		m_blsDispTrue	= (BOOL)wTemp;
		ar.Read(&m_TrueColor, sizeof(COLORREF));
		ar.Read(&m_ErrorColor, sizeof(COLORREF));
		ar.Read(&m_FalseColor, sizeof(COLORREF));
		ar >> m_strLinkViewName;
		ar >> m_strPictureName;
		m_TempColor = m_color;
		m_bIsChangeHide = FALSE;       //0415
	}
}

void CDrawButton::Draw(CDC* pDC)
{
	ASSERT_VALID(this);
	CRect rect = m_position;
	CRect buttonRect = m_position;            //0415
	rect.NormalizeRect();

	CRect rc = rect;
	rc.NormalizeRect();
	if(rc.Width() < 10 || rc.Height()<10)
		return;

	RectF theRect (rect.TopLeft().x,rect.TopLeft().y,rect.Size().cx,rect.Size().cy); 
	Rect GdiRect (rect.TopLeft().x,rect.TopLeft().y,rect.Size().cx,rect.Size().cy); 

	COLORREF clrBackground = ::GetSysColor(COLOR_3DFACE);
	COLORREF m_clr3DShadow = ::GetSysColor(COLOR_3DSHADOW);
	COLORREF m_clr3DHilight = ::GetSysColor(COLOR_3DHILIGHT);

	Graphics graphics (pDC->m_hDC);

	switch (m_nShape)
	{
	case button:
		{
			pDC->FillSolidRect(rect, clrBackground);
			pDC->Draw3dRect(rect,m_clr3DShadow,m_clr3DHilight);
		}
	case text:		
		{
			//进行字符转换
			StringFormat stringFormat;
			stringFormat.SetAlignment(m_fontAlignment);
			stringFormat.SetLineAlignment(m_fontAlignment);
			stringFormat.SetFormatFlags(m_format);
			stringFormat.SetTrimming(m_trimmingSyle);

			CString strFontName = m_fontName;
			if(strFontName.Left(1) == "@")
			{
				strFontName.TrimLeft("@");
				stringFormat.SetFormatFlags(StringFormatFlagsDirectionVertical );
			}
    		BSTR bstr = strFontName.AllocSysString();
///			BSTR bstr = _com_util::ConvertStringToBSTR(strFontName);
///			WCHAR *fn = new unsigned short[m_fontName.GetLength()];;
				
			FontFamily  fontFamily(bstr);
	       	SysFreeString(bstr);

			Gdiplus::Font font(&fontFamily, m_fontSize, m_fontStyle, UnitPoint);
			
			SolidBrush  solidBrush(m_fontColor);
			
			//进行字符转换
			m_strButton.TrimRight();
///			int len = m_strButton.GetLength();
    		bstr = m_strButton.AllocSysString();
///			bstr = _com_util::ConvertStringToBSTR(m_strButton);
///			WCHAR *strButton = new unsigned short[len];
///			wcscpy(strButton,bstr);
			
			//must reverse Text, because in my system, y is small as it gose low
			Matrix matrix(1,0,0,-1,0,0);
			graphics.SetTransform(&matrix);
			
			theRect.Y *=-1;
			theRect.Height*=-1;
			Normallize (theRect);
			graphics.DrawString(bstr,-1,&font, theRect,&stringFormat, &solidBrush);
	       	SysFreeString(bstr);
		}
		break;
	case picture:
		{
       		if(!m_strPictureName.IsEmpty())
			{
        		BSTR strPicPath = m_strPictureName.AllocSysString();
///        		BSTR strPicPath = _com_util::ConvertStringToBSTR(m_strPictureName);
        		Image  m_pimage(strPicPath);
      	       	SysFreeString(strPicPath);
            	m_pimage.RotateFlip(Rotate180FlipX);
           		graphics.DrawImage(&m_pimage, GdiRect);
			}
		}
		break;	
	}
	graphics.ReleaseHDC(pDC->m_hDC);
}

void CDrawButton::StartAction()
{
	Invalidate();
}

void CDrawButton::Invalidate()
{
	ASSERT_VALID(this);
		m_pDocument->UpdateAllViews(NULL, HINT_UPDATE_DRAWOBJ, this);
}

/*
int CDrawButton::GetHandleCount()
{
	ASSERT_VALID(this);
	return CDrawObj::GetHandleCount();
}

// returns center of handle in logical coordinates
CPoint CDrawButton::GetHandle(int nHandle)
{
	ASSERT_VALID(this);

	return CDrawObj::GetHandle(nHandle);
}

HCURSOR CDrawButton::GetHandleCursor(int nHandle)
{
	ASSERT_VALID(this);

	return CDrawObj::GetHandleCursor(nHandle);
}

// point is in logical coordinates
void CDrawButton::MoveHandleTo(int nHandle, CPoint point, CDrawView* pView)
{
	ASSERT_VALID(this);
	CDrawObj::MoveHandleTo(nHandle, point, pView);
}

// rect must be in logical coordinates
BOOL CDrawButton::Intersects(const CRect& rect)
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

CDrawObj* CDrawButton::Clone(CDrawDoc* pDoc)
{
	ASSERT_VALID(this);

	CDrawButton* pClone = new CDrawButton(m_position);

	pClone->m_strButton		= m_strButton;
	pClone->m_fontAlignment = m_fontAlignment;
	pClone->m_fontColor		= m_fontColor;
	pClone->m_fontName		= m_fontName;
	pClone->m_fontSize		= m_fontSize;
	pClone->m_fontStyle		= m_fontStyle;
	pClone->m_format		= m_format;
	pClone->m_trimmingSyle	= m_trimmingSyle;
	pClone->m_nShape		= m_nShape;
	pClone->m_color			= m_color;
	pClone->m_trans			= m_trans;

	if (pDoc != NULL)
		pDoc->Add(pClone);

	ASSERT_VALID(pClone);
	return pClone;
}
/*
BOOL CDrawButton::SetState(ButtonState nState)
{
	m_nButtonState = nState;
//	Invalidate();
	return TRUE;
}

void CDrawButton::OnEditProperties()			//编辑属性
{

}*/