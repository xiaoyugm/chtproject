// DrawButton.cpp: implementation of the CDrawButton class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Draw.h"
#include "DrawButton.h"
#include "drawobj.h"
#include "drawdoc.h"
#include "drawview.h"
#include "FontPropertiesDlg.h"
#include "ButtonSetDlg.h"     //0415

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
///	timeEndPeriod(1000);
}

CDrawButton::CDrawButton(const CRect& position)
	: CDrawObj(position)
{
	ASSERT_VALID(this);
	m_fontColor			= RGB(0,0,0);
	m_fontAlignment		= StringAlignmentCenter;
	m_fontStyle			= FontStyleBold ;
	m_fontSize			= 12;
	m_fontName			= "Arial";
	m_format			= StringFormatFlagsDirectionRightToLeft;
	m_trimmingSyle		= StringTrimmingNone;
	m_color				= RGB(0,0,0);
	m_strButton         = "Button";
	m_TrueColor			= RGB(0,255,0);			//正常时颜色
	m_FalseColor		= RGB(255,0,0);
	m_ErrorColor		= RGB(255,255,0);			//通讯失败时颜色
	m_nPointNo			= 0;					//对应点号
	m_bIsRunShowValue	= FALSE;				//是否在运行时显示点号的值
	m_blsDispTrue   	= FALSE;				//正常显示文本
	m_strLinkViewName   = "";					//连接的窗口名称
	m_bIsChangeHide		= FALSE;
	m_strPictureName    = "";					//图片路径
}

void CDrawButton::Serialize(CArchive& ar)
{
	ASSERT_VALID(this);

	CDrawObj::Serialize(ar);
	if (ar.IsStoring())
	{
		ar << m_strButton;
		ar << m_fontName;
		ar << m_fontSize;
		ar << (WORD)m_fontAlignment;
		ar << (WORD)m_fontStyle;
		ar << (WORD)m_format;
		ar << (WORD)m_trimmingSyle;
		ar.Write(&m_color,sizeof(COLORREF));
		ar << (WORD)m_nShape;
		ar << m_nPointNo;
		ar << (WORD)m_bIsRunShowValue;
		ar << (WORD)m_blsDispTrue;
		ar.Write(&m_TrueColor, sizeof(COLORREF));
		ar.Write(&m_ErrorColor, sizeof(COLORREF));
		ar.Write(&m_FalseColor, sizeof(COLORREF));
		ar << m_strLinkViewName;
		ar << m_strPictureName;
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
	}
}

void CDrawButton::Draw(CDC* pDC)
{
	ASSERT_VALID(this);
	CRect rect = m_position;
	CRect buttonRect = m_position;    //0415
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

	m_fontColor.SetFromCOLORREF(m_color);
	
	if(m_nShape== text && m_strButton.CompareNoCase("button") == 0)
		m_strButton = "TEXT";
	
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
			BSTR bstr = _com_util::ConvertStringToBSTR(strFontName);
///			WCHAR *fn = new unsigned short[m_fontName.GetLength()];;
				
			FontFamily  fontFamily(bstr);

			Font font(&fontFamily, m_fontSize, m_fontStyle, UnitPoint);
			
			SolidBrush  solidBrush(m_fontColor);
			
			//进行字符转换
			m_strButton.TrimRight();
			int len = m_strButton.GetLength();
			bstr = _com_util::ConvertStringToBSTR(m_strButton);
///			WCHAR *strButton = new unsigned short[len];
///			wcscpy(strButton,bstr);   //strButton

			
			//must reverse Text, because in my system, y is small as it gose low
			Matrix matrix(1,0,0,-1,0,0);
			graphics.SetTransform(&matrix);
			
			theRect.Y *=-1;
			theRect.Height*=-1;
			Normallize (theRect);
			graphics.DrawString(bstr,-1,&font, theRect,&stringFormat, &solidBrush);
		}
		break;
	case picture:
		{
       		if(!m_strPictureName.IsEmpty())
			{
        		BSTR strPicPath = _com_util::ConvertStringToBSTR(m_strPictureName);
        		Image m_pimage(strPicPath);
            	m_pimage.RotateFlip(Rotate180FlipX);
           		graphics.DrawImage(&m_pimage, GdiRect);
			}
		}
		break;	
	}
	graphics.ReleaseHDC(pDC->m_hDC);
}

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
	pClone->m_TrueColor     = m_TrueColor;
	pClone->m_FalseColor	= m_FalseColor;
	pClone->m_ErrorColor	= m_ErrorColor;
	pClone->m_nPointNo		= m_nPointNo;
	pClone->m_bIsRunShowValue	= m_bIsRunShowValue;
	pClone->m_blsDispTrue	= m_blsDispTrue;
	pClone->m_strLinkViewName	= m_strLinkViewName;

	if (pDoc != NULL)
		pDoc->Add(pClone);

	ASSERT_VALID(pClone);
	return pClone;
}
/*
BOOL CDrawButton::SetState(ButtonState nState)       //0415
{
	m_nButtonState = nState;
	Invalidate();
	return TRUE;
}
*/
void CDrawButton::OnEditProperties()			//编辑属性
{
	CPropertySheet sheet( _T("属性") );
	if(m_nShape == button)
       {                                 //0415
		CButtonSetDlg	fontdlg;
		//进行数据交换
    	fontdlg.m_color			= m_color;
     	fontdlg.m_fontAlignment = m_fontAlignment;
    	fontdlg.m_fontName		= m_fontName;
    	fontdlg.m_fontSize		= m_fontSize;
        fontdlg.m_fontStyle		= m_fontStyle;
    	fontdlg.m_format		= m_format;
    	fontdlg.m_strButton		= m_strButton;
       	fontdlg.m_trimmingSyle  = m_trimmingSyle;
 		fontdlg.m_strLinkViewName = m_strLinkViewName;

    	sheet.AddPage(&fontdlg);
      	if (sheet.DoModal() != IDOK)
    		return;

    	m_color			=fontdlg.m_color;
    	m_fontAlignment = fontdlg.m_fontAlignment;
    	m_fontName		= fontdlg.m_fontName;
       	m_fontSize		= fontdlg.m_fontSize;
      	m_fontStyle		= fontdlg.m_fontStyle;
    	m_format		= fontdlg.m_format;
      	m_strButton		= fontdlg.m_strButton;
    	m_trimmingSyle	= fontdlg.m_trimmingSyle;
		m_strLinkViewName = fontdlg.m_strLinkViewName;
	}
	else if(m_nShape == text)
	{
		CFontPropertiesDlg fontdlg;
		//进行数据交换
		fontdlg.m_color			= m_color;
		fontdlg.m_fontAlignment = m_fontAlignment;
		fontdlg.m_fontName		= m_fontName;
		fontdlg.m_fontSize		= m_fontSize;
		fontdlg.m_fontStyle		= m_fontStyle;
		fontdlg.m_format		= m_format;
		fontdlg.m_strButton		= m_strButton;
		fontdlg.m_trimmingSyle  = m_trimmingSyle;
		fontdlg.m_bIsRunShowValue = m_bIsRunShowValue;
		fontdlg.m_blsDispTrue = m_blsDispTrue;
		fontdlg.m_ErrorColor  = m_ErrorColor;
		fontdlg.m_TrueColor   = m_TrueColor;
		fontdlg.m_nPointNo    = m_nPointNo;
		fontdlg.m_FalseColor	= m_FalseColor;

		sheet.AddPage(&fontdlg);
		if (sheet.DoModal() != IDOK)
			return;

		m_color			=fontdlg.m_color;
		m_fontAlignment = fontdlg.m_fontAlignment;
		m_fontName		= fontdlg.m_fontName;
		m_fontSize		= fontdlg.m_fontSize;
		m_fontStyle		= fontdlg.m_fontStyle;
		m_format		= fontdlg.m_format;
		m_strButton		= fontdlg.m_strButton;
		m_trimmingSyle	= fontdlg.m_trimmingSyle;
		m_bIsRunShowValue = fontdlg.m_bIsRunShowValue ;
		m_blsDispTrue = fontdlg.m_blsDispTrue ;
		m_ErrorColor	= fontdlg.m_ErrorColor;
		m_TrueColor		= fontdlg.m_TrueColor;
		m_nPointNo		= fontdlg.m_nPointNo ;
		m_FalseColor	= fontdlg.m_FalseColor;
	}
	else if(m_nShape == picture)
	{
    	char filter[] = "图象文件(*.jpg,*.jpeg,*.gif,*.bmp,*.ico)|*.jpg;*.jpeg;*.gif;*.bmp;*.ico|JPEG文件(*.jpg,*.jpeg)|*.jpg;*.jpeg|GIF文件(*.gif)|*.gif|位图文件(*.bmp)|*.bmp|图标文件(*.ico)|*.ico||";
    	CFileDialog filedlg(TRUE,NULL,NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,filter,NULL);
    	if(filedlg.DoModal() == IDOK)
		{
	      	m_strPictureName = filedlg.GetPathName();
		}
	}
	//进行数据交换
	Invalidate();
	m_pDocument->SetModifiedFlag();
}