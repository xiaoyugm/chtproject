#include "stdafx.h"
#include "../resource.h"
#include "ToolbarBitmap.h"
#include "MenuItem.h"
#include "FileTools.h"

static const LONG ICON_WIDTH=	16;	//20;
static const LONG ICON_HEIGHT=	15; //19;

ToolbarBitmap::ToolbarBitmap()
:m_hBitmap(NULL),
m_nButtonCount(0),
m_pButtonIDs(NULL)
{}

ToolbarBitmap::ToolbarBitmap(UINT _nButtonCount)
:m_hBitmap(NULL),
m_nButtonCount(_nButtonCount),
m_pButtonIDs(NULL)
{}

ToolbarBitmap::~ToolbarBitmap()
{
	delete [] m_pButtonIDs;
}

/** @brief Return the handle on the internal bitmap
* @return HBITMAP m_hBitmap
*/
HBITMAP	ToolbarBitmap::GetHBitmap() const
{
	return m_hBitmap;
}

/** @brief Return the number of icons in the bitmap
* @return UINT m_nButtonCount
*/
UINT ToolbarBitmap::GetIconCount() const
{
	return m_nButtonCount;
}

/** @brief Return the array of IDs in the bitmap
* @remarks the array length is egal to m_nButtonCount
* @see GetIconCount
* @return UINT* m_pButtonIDs
*/
UINT* ToolbarBitmap::GetIconIDs()
{
	return m_pButtonIDs;
}

/** @brief Create the bitmap from the list of Menu Item
* @param _Items <BR>List of items
* @return bool always true
*/
bool ToolbarBitmap::Create(const std::list<MenuItem>& _Items)
{
	UINT xPos;
	UINT nOffset;
	BITMAPINFO bmpInfo;
	MenuItem	Item;
	HBITMAP		hBitmap;
	std::list<MenuItem>::const_iterator Iter;  

	HDC dc= CreateCompatibleDC(NULL);

	//first count the number of buttons and initialize the m_pButtonIDs array
	_InitializeButtonArray(_Items);

	ZeroMemory( &bmpInfo.bmiHeader, sizeof(BITMAPINFOHEADER) );
	bmpInfo.bmiHeader.biSize=			sizeof(BITMAPINFOHEADER);
	bmpInfo.bmiHeader.biWidth=			ICON_WIDTH*m_nButtonCount;		// Set size you need
	bmpInfo.bmiHeader.biHeight=			ICON_HEIGHT;					// Set size you need
	bmpInfo.bmiHeader.biPlanes=			1;
	bmpInfo.bmiHeader.biBitCount=		32; // Can be 8, 16, 32 bpp or other number
	bmpInfo.bmiHeader.biSizeImage=		0;
	bmpInfo.bmiHeader.biClrUsed=		0;
	bmpInfo.bmiHeader.biClrImportant=	0;
	VOID *pvBits;

	m_hBitmap= CreateDIBSection( dc, &bmpInfo, DIB_RGB_COLORS, &pvBits,	NULL, 0 );

	HDC dcBmp= CreateCompatibleDC(dc);
	HGDIOBJ tempObj= SelectObject(dcBmp, m_hBitmap);

	xPos=		0;
	nOffset=	0;

	for(Iter= _Items.begin(); Iter!=_Items.end(); ++Iter){
		Item= (*Iter);
		hBitmap= _LoadBitmap(Item.GetIconFileName());
		if(hBitmap){

			m_pButtonIDs[nOffset]= Item.GetCommandID();
			++nOffset;

			_AddButton(dcBmp, xPos, hBitmap);
			xPos+=ICON_WIDTH;
		}
	}

	SelectObject(dcBmp, tempObj);
	DeleteDC(dcBmp);
	return true;
}

/** @brief initialize the array for the button ids
* @remarks initialize both m_nButtonCount and m_pButtonIDs.<br>
* attention use an id only if you are pretty sure that the bitmap icon exist.<br>
* today we check the presence of hte file on the hard driver.<br>
* may be we could load it to be sure it is a valid bitmpa file ??
* @param _Items <BR>the list of Items to use.
*/
void ToolbarBitmap::_InitializeButtonArray(const std::list<MenuItem>& _Items)
{
	CString sIconFile;
	MenuItem	Item;
	std::list<MenuItem>::const_iterator Iter;  

	//First count the number of images available
	m_nButtonCount= 0;
	for(Iter= _Items.begin(); Iter!=_Items.end(); ++Iter){
		Item=		(*Iter);
		sIconFile=	Item.GetIconFileName();
		if(TRUE==CFileTools::DoesFileExist(sIconFile)){
			++m_nButtonCount;
		}
	}

	//Then create an array for bitmap ids
	m_pButtonIDs= new UINT[m_nButtonCount];
	ZeroMemory(m_pButtonIDs, m_nButtonCount*sizeof(UINT));
}


/** @brief Add a new bitmap in the given DC
* @remarks each bitmpa should be added after the previous one. <br>
* The y value is always set to 0 (toolbar)
* @param _dc <BR>the DC we are working with
* @param _xPos <BR>the x position where we want to draw the new bitmap
* @param _hBitmap <BR>the handle of the bitmap to draw
*/
void ToolbarBitmap::_AddButton(HDC _dc, UINT _xPos, HBITMAP _hBitmap)
{
	HDC dcTemp= CreateCompatibleDC(_dc);

	BITMAP bmpInfo;
	CBitmap oBitmap;
	oBitmap.Attach(_hBitmap);

	oBitmap.GetBitmap(&bmpInfo);

	HGDIOBJ oldGdiObj= SelectObject(dcTemp, oBitmap.m_hObject);
	::BitBlt(_dc, _xPos, 0, bmpInfo.bmWidth, bmpInfo.bmHeight, dcTemp, 0, 0, SRCCOPY);

	SelectObject(dcTemp, oldGdiObj);

	oBitmap.Detach();

	DeleteDC(dcTemp);

}

/** @brief load a bitmap from a file
* @param _sName <BR>the full file name.
* @return HBITMAP the handle on the bitmap
*/
HBITMAP ToolbarBitmap::_LoadBitmap(const CString& _sName)
{
	HBITMAP hBitmap= (HBITMAP)::LoadImage( NULL,
                _sName,
                IMAGE_BITMAP,
                0,
                0,
                LR_LOADFROMFILE | LR_LOADMAP3DCOLORS /*| LR_LOADTRANSPARENT |LR_CREATEDIBSECTION */
                );
	return hBitmap;
}
