#pragma once

#include "AbstractMenuCommandSet.h"
#include "MenuCommandSetCfg.h"


class MenuCommandSet: public AbstactMenuCommandSet
{
public:
	MenuCommandSet(void);
	virtual ~MenuCommandSet(void);

	virtual bool Create(const CString& _sCfgFileName, UINT _nBaseCmdID);

	virtual void DoUpdateMenu(UINT _nID, CCmdUI* _pCmdUI);
	virtual void DoCommandMenu(UINT _nID);

	virtual MenuToolbar* GetMenuToolbar(MenuId_t _nID) const;
	virtual MenuPopup* GetMenuPopup(MenuId_t _nID) const;

private:
	MenuCommandSetCfg m_Config;
	MenuToolbar m_ToolBar1;
	MenuPopup	m_PopupMenu1;
	MenuPopup	m_PopupMenu2;

private:
	void _InitializeToolBar1();
	void _InitializePopupMenu1();
	void _InitializePopupMenu2();

	void _InitializeToolbar(MenuToolbar& _Toolbar, const CString& _sName, const std::list<CmdMenuItem_t>& _List);
	void _InitializePopup(MenuPopup& _Popup, const std::list<CmdMenuItem_t>& _List);
};