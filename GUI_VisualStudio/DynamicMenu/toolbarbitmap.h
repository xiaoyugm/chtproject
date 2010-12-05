#pragma once

class MenuItem;
#include <list>

class ToolbarBitmap
{
public:
	ToolbarBitmap();
	ToolbarBitmap(UINT _nButtonCount);
	virtual ~ToolbarBitmap();

	bool Create(const std::list<MenuItem>& _Items);

	HBITMAP	GetHBitmap() const;
	UINT GetIconCount() const;
	UINT* GetIconIDs();

private:
	HBITMAP	m_hBitmap;
	UINT	m_nButtonCount;
	UINT*	m_pButtonIDs;

private:
	HBITMAP _LoadBitmap(const CString& _sName);
	void _AddButton(HDC _dc, UINT _xPos, HBITMAP _hBitmap);
	void _InitializeButtonArray(const std::list<MenuItem>& _Items);
};
