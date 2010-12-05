#pragma once

#include "MenuItem.h"
#include <list>

class MenuPopup
{
public:
	MenuPopup(void);
	virtual ~MenuPopup(void);

public:
	void Create(std::list<MenuItem>& _List);

	CMenu* GetPopup();
	void AddToMenu(CMenu* _pMenu);

private:
	std::list<MenuItem>	m_Items;

	void _FillMenu(CMenu* _pMenu);
	HBITMAP _LoadBitmap(const CString& _sName);
};
