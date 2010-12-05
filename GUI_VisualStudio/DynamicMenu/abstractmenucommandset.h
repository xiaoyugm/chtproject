#pragma once

#include "MenuItemList.h"
#include "MenuToolbar.h"
#include "MenuPopup.h"
#include "ToolbarBitmap.h"
#include "types.h"

class AbstactMenuCommandSet
{
public:
	AbstactMenuCommandSet(void);
	virtual ~AbstactMenuCommandSet(void);

	virtual bool Create(const CString& _sCfgFileName, UINT _nBaseCmdID)= 0;
	virtual MenuToolbar* GetMenuToolbar(MenuId_t _nID) const= 0;
	virtual MenuPopup* GetMenuPopup(MenuId_t _nID) const= 0;
	virtual void DoUpdateMenu(UINT _nID, CCmdUI* _pCmdUI)= 0;
	virtual void DoCommandMenu(UINT _nID)= 0;

	bool IsInRange(UINT _nID) const;
	bool GetMenuItem(UINT _nBtnID, MenuItem& _MenuItem) const;
	ToolbarBitmap& GetToolbarBitmap() const;

private:
	MenuItemList		m_Menus;
	ToolbarBitmap*		m_pToolbarBitmap;

protected:
	void CreateToolbarBitmap(const std::list<MenuItem>& _Items);
	MenuItemList& GetMenuItemList();
	bool GetMenuItemFromActionCode(CmdMenuItem_t _nActionCode, MenuItem& _MenuItem) const;
};
