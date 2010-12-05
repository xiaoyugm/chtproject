#include "stdafx.h"
#include "MenuToolbar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

MenuToolbar::MenuToolbar()
:m_nCount(0),
m_pIDs(NULL)
{}

MenuToolbar::~MenuToolbar()
{
	delete [] m_pIDs;
}

CString MenuToolbar::GetName() const
{
	return m_sName;
}

UINT MenuToolbar::GetIconCount() const
{
	return m_nCount;
}

UINT* MenuToolbar::GetIconIDs() const
{
	return m_pIDs;
}

void MenuToolbar::Create(const CString& _sName, std::list<MenuItem>& _List)
{
	m_sName= _sName;
	std::list<MenuItem>::const_iterator Iter;

	m_nCount=	(UINT)_List.size();
	m_pIDs=		new UINT[m_nCount];

	UINT nIndex= 0;

	for(Iter= _List.begin(); Iter!= _List.end(); ++Iter){
		m_pIDs[nIndex]= (*Iter).GetCommandID();
		++nIndex;
	}
}

