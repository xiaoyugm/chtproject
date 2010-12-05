#pragma once

#include "MenuItem.h"
#include <list>

class MenuItemList
{
public:
	MenuItemList(void);
	virtual ~MenuItemList(void);

	void AddItem(const MenuItem& _MenuItem);
	std::list<MenuItem> GetItems() const;
	UINT GetCount() const;
	void SetBaseCommandID(UINT _nBaseID);

private:
	UINT m_nCommandBaseID;
	std::list<MenuItem> m_Items;
	UINT _GetNextCommandID();
};
