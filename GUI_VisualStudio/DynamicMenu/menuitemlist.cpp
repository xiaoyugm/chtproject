#include "stdafx.h"
#include "MenuItemList.h"

MenuItemList::MenuItemList()
:m_nCommandBaseID(0)
{}

MenuItemList::~MenuItemList()
{}

void MenuItemList::SetBaseCommandID(UINT _nBaseID)
{
	m_nCommandBaseID= _nBaseID;
}

void MenuItemList::AddItem(const MenuItem& _MenuItem)
{
	MenuItem oItem=		_MenuItem;
	oItem.m_nCommandID=	_GetNextCommandID();
	m_Items.push_back(oItem);
}

std::list<MenuItem> MenuItemList::GetItems() const
{
	return m_Items;
}

UINT MenuItemList::GetCount() const
{
	return (UINT)m_Items.size();
}

UINT MenuItemList::_GetNextCommandID()
{
	UINT nNextID= m_nCommandBaseID;
	UINT nID;
	std::list<MenuItem>::const_iterator Iter;

	for(Iter= m_Items.begin(); Iter!=m_Items.end(); ++Iter)
	{
		nID= (*Iter).GetCommandID();
		if(nID>=nNextID){
			nNextID= nID+1;
		}
	}
	return nNextID;
}
