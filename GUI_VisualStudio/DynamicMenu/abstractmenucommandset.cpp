#include "stdafx.h"
#include "AbstractMenuCommandSet.h"
#include "CommandInvoker.h"
#include "ToolbarBitmap.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


AbstactMenuCommandSet::AbstactMenuCommandSet()
:m_pToolbarBitmap(NULL)
{
	m_pToolbarBitmap= new ToolbarBitmap();
}

AbstactMenuCommandSet::~AbstactMenuCommandSet()
{
	delete m_pToolbarBitmap;
}

/** @brief return the internal toolbar bitmap object
* @return ToolbarBitmap& reference on m_pToolbarBitmap
*/
ToolbarBitmap& AbstactMenuCommandSet::GetToolbarBitmap() const
{
	return (ToolbarBitmap&)*m_pToolbarBitmap;
}

/** @brief Initialize the toolbar bitmap from a list of MenuItems
* @param _nBaseCmdID <BR>the command base id to use ( link with IDS in resource.h file).<br>
* you should reserve a range of ids in resource.h to avoid collision with other MFC command Ids.<br>
* see ID_CMDSET_RESERVED_xx values in resource.h
* @param _Items <BR>the list of MenuItems to use
*/
void AbstactMenuCommandSet::CreateToolbarBitmap(const std::list<MenuItem>& _Items)
{
	ASSERT(m_pToolbarBitmap);
	if(m_pToolbarBitmap){
		m_pToolbarBitmap->Create(_Items);
	}
}

/** @brief Give a MenuItem from its Button ID
* @remarks Button ID is the one use by MFC in message / command handlers
* @param _nBtnID <BR>the ID of the item we are looking for
* @param _MenuItem <BR>the found menu item. (update only if method return true) 
* @return bool true if found
*/
bool AbstactMenuCommandSet::GetMenuItem(UINT _nBtnID, MenuItem& _MenuItem) const
{
	std::list<MenuItem> Items= m_Menus.GetItems();
	std::list<MenuItem>::const_iterator Iter;

	for(Iter= Items.begin(); Iter!= Items.end(); ++Iter){
		if(_nBtnID==(*Iter).GetCommandID()){
			_MenuItem=(*Iter);
			return true;
		}
	}
	return false;
}

bool AbstactMenuCommandSet::GetMenuItemFromActionCode(CmdMenuItem_t _nActionCode, MenuItem& _MenuItem) const
{
	std::list<MenuItem> Items= m_Menus.GetItems();
	std::list<MenuItem>::const_iterator Iter;

	for(Iter= Items.begin(); Iter!= Items.end(); ++Iter){
		if(_nActionCode==(*Iter).GetActionCode()){
			_MenuItem=(*Iter);
			return true;
		}
	}
	return false;
}


/** @brief Check is a menu item ID is handled by the current MenuCommandSet
* @remarks an ID is in the range if it is in between [m_nBaseCommandID ... m_nBaseCommandID+ nd of MenuItems]
* @param _nID <BR>a given ID
* @return bool true if the menu Item ID is part of the one in the internal list
*/
bool AbstactMenuCommandSet::IsInRange(UINT _nID) const
{
	MenuItem oItem; 
	bool bInRange= false;
	
	if(true==GetMenuItem(_nID, oItem)){
		if( _nID==oItem.GetCommandID() ){
			bInRange= true;
		}
	}
	return bInRange;
}

MenuItemList& AbstactMenuCommandSet::GetMenuItemList()
{
	return m_Menus;
}


/*+- OmniWorks Replacement History - wtap_unitest`dart120`dart:abstractmenucommandset.cpp;2 */
/*       2*[969461] 22-JUN-2007 12:05:45 (GMT) PAQUIER */
/*         "change interface of :GetMenuItemFromActionCode" */
/*       1*[967020] 19-JUN-2007 15:57:12 (GMT) PAQUIER */
/*         "default set list of command objects" */
/*+- OmniWorks Replacement History - wtap_unitest`dart120`dart:abstractmenucommandset.cpp;2 */
