//*************************************************************
// ColorListBox.cpp : implementation file
//
// MFC ListBox with optional color
// 
// Version: 1.0	01/10/1998 (c)Patrice Godard
//
//**************************************************************

#include "stdafx.h"
#include "ColorListBox.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CColorListBox

CColorListBox::CColorListBox()
{
	m_FontName = "宋体";
	m_FontSize = 12;
	m_FontWidth = 5;
}

CColorListBox::~CColorListBox()
{
}


BEGIN_MESSAGE_MAP(CColorListBox, CXTListBox)
	//{{AFX_MSG_MAP(CColorListBox)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CColorListBox message handlers



void CColorListBox::DrawItem(LPDRAWITEMSTRUCT lpdis) 
{
	if (lpdis->itemID < 0)
		return; 

	COLORREF cvText;
	COLORREF cvBack;
	CString itemString;

	if ((lpdis->itemState & ODS_SELECTED) &&	// if item has been selected
		(lpdis->itemAction & (ODA_SELECT | ODA_DRAWENTIRE)))
			DrawFocusRect(lpdis->hDC, &lpdis->rcItem); 
	

	if (!(lpdis->itemState & ODS_SELECTED) &&	// if item has been deselected
		(lpdis->itemAction & ODA_SELECT))
			DrawFocusRect(lpdis->hDC, &lpdis->rcItem); 
	
	if(lpdis->itemData)		// if color information is present
			cvText = SetTextColor(lpdis->hDC, lpdis->itemData);
		else 	// if no color information, use default system colors
			cvText = SetTextColor(lpdis->hDC, GetSysColor((lpdis->itemState & ODS_SELECTED)
		? COLOR_HIGHLIGHTTEXT : COLOR_WINDOWTEXT)); 
	
	// always use system colors for background
	cvBack = SetBkColor(lpdis->hDC, GetSysColor((lpdis->itemState & ODS_SELECTED)
		? COLOR_HIGHLIGHT : COLOR_WINDOW)); 
	// get and display item text
	GetText(lpdis->itemID, itemString );

	/*//创建字体
	HFONT hfont = ::CreateFont(m_FontSize, m_FontWidth,0, 0,FW_DONTCARE, FALSE, FALSE, FALSE,
		DEFAULT_CHARSET, OUT_CHARACTER_PRECIS,CLIP_CHARACTER_PRECIS,DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE,
		m_FontName);
	HFONT pOldFont = (HFONT)SelectObject(lpdis->hDC, hfont);
	*/
	DrawText(lpdis->hDC, itemString, -1, &lpdis->rcItem, DT_LEFT | DT_SINGLELINE);
	// restore DC colors
	SetTextColor(lpdis->hDC, cvText); 
	//SelectObject(lpdis->hDC,pOldFont); 
	SetBkColor(lpdis->hDC, cvBack); 
}


//***********************************************
// original AddString() method
//
// purpose: Add a string to the listbox
//
// parameters: 
//		lpszItem: pointer to item text
//
// remarks:
//	    provided because CListBox::AddString is 
//		NOT virtual
//
// return:	item index
//***********************************************
int CColorListBox::AddString( LPCTSTR lpszItem)
{
	return ((CXTListBox*)this)->AddString(lpszItem);
}


//***********************************************
// new AddString() method
//
// purpose: Add a string to the listbox
//
// parameters: 
//		lpszItem: pointer to item text
//			 rgb: text color as a COLORREF
//
// return:	item index
//***********************************************
int CColorListBox::AddString( LPCTSTR lpszItem,COLORREF rgb )
{
	int item = AddString(lpszItem);
	if(item >=0)
		SetItemData(item,rgb);
	return item;
}


//***********************************************
// new InsertString() method
//
// purpose: Insert a string to the listbox
//
// parameters: 
//		  nIndex: index of inserted item
//		lpszItem: pointer to item text
//			 rgb: text color as a COLORREF
//
// return:	item index
//***********************************************
int CColorListBox::InsertString( int nIndex, LPCTSTR lpszItem, COLORREF rgb)
{
	int item = ((CXTListBox*)this)->InsertString(nIndex,lpszItem);
	if(item >=0)
		SetItemData(item,rgb);
	return item;

}



void CColorListBox::SetFont(CString FontName, CString FontSize)
{
	m_FontName = "宋体";
	m_FontSize = 9;
}

COLORREF CColorListBox::getColor(int nIndex)
{
	return (COLORREF)GetItemData(nIndex);
}
