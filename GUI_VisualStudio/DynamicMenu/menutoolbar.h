#pragma once

#include "MenuItem.h"
#include <list>

class MenuToolbar
{
public:
	MenuToolbar();
	virtual ~MenuToolbar();

public:
	void Create(const CString& _sName, std::list<MenuItem>& _List);

	CString GetName() const;
	UINT GetIconCount() const;
	UINT* GetIconIDs() const;

private:
	CString m_sName;
	UINT	m_nCount;
	UINT*	m_pIDs;
};
