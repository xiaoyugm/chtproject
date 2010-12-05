#include "stdafx.h"
#include "MenuCommandSet.h"
#include "AbstractCommand.h"
#include "CommandInvoker.h"
#include "CommandFactory.h" 
#include "ToolbarBitmap.h"
#include "types.h"


MenuCommandSet::MenuCommandSet()
:AbstactMenuCommandSet()
{}

MenuCommandSet::~MenuCommandSet()
{}

/** @brief Initialize the Menu Command Set from the xml file 
* @remarks load the xml file and build some dynamic menus 
* @param _sCfgFileName <BR>the full path name of the xml config file to use
* @param _nBaseCmdID <BR>the base resource id that will be used
* @return bool alway true
*/
bool MenuCommandSet::Create(const CString& _sCfgFileName, UINT _nBaseCmdID)
{
	GetMenuItemList().SetBaseCommandID(_nBaseCmdID);

	std::string sCfgFile= _sCfgFileName;	
	m_Config.Load(sCfgFile);

	std::list<MenuItem> List= m_Config.GetMenuItems();
	std::list<MenuItem>::const_iterator Iter;

	for(Iter= List.begin(); Iter!= List.end(); ++Iter)
	{
		GetMenuItemList().AddItem((*Iter));
	}
	//
	_InitializeToolBar1();
	//
	_InitializePopupMenu1();
	_InitializePopupMenu2();
	//create the bitmap toolbar 
	CreateToolbarBitmap(GetMenuItemList().GetItems());
	return true;
}

MenuToolbar* MenuCommandSet::GetMenuToolbar(MenuId_t _nID) const
{
	if(MenuIdToolbar1==_nID){
		return (MenuToolbar*)&m_ToolBar1;
	}
	return NULL;
}

MenuPopup* MenuCommandSet::GetMenuPopup(MenuId_t _nID) const
{
	if(MenuIdPopup1==_nID){
		return (MenuPopup*)&m_PopupMenu1;
	}
	if(MenuIdPopup2==_nID){
		return (MenuPopup*)&m_PopupMenu2;
	}
	return NULL;
}

void MenuCommandSet::DoUpdateMenu(UINT _nID, CCmdUI* _pCmdUI)
{
	if(_pCmdUI && IsInRange(_nID))
	{
		BOOL bEnable= FALSE;
		CWinApp* pApp= AfxGetApp();
		if(pApp)
		{
			CMDIFrameWnd * pMainFrame= (CMDIFrameWnd *)AfxGetApp()->m_pMainWnd;
			if(pMainFrame){
				CFrameWnd* pTemp= pMainFrame->GetActiveFrame();
				if(pMainFrame && (pTemp!=pMainFrame)){
					bEnable= TRUE;
				}
			}
		}
		_pCmdUI->Enable(bEnable);
	}
}//

void MenuCommandSet::DoCommandMenu(UINT _nID)
{
	if(IsInRange(_nID))
	{
		MenuItem oItem;
		if(GetMenuItem(_nID, oItem))
		{
			CommandFactory oFactory;
			std::auto_ptr<AbstractCommand> pCommand(oFactory.CreateCommand(oItem.GetActionCode()));
			if(pCommand.get()){
				CommandInvoker::GetInstance().ExecuteCommand(*pCommand.get());
			}
		}
	}
}


void MenuCommandSet::_InitializeToolBar1()
{
	std::list<CmdMenuItem_t> List;
	m_Config.GetMenuList(MenuIdToolbar1, List);
	_InitializeToolbar(m_ToolBar1, _T("Toolbar1"), List);
}




void MenuCommandSet::_InitializePopupMenu1()
{
	std::list<CmdMenuItem_t> List;
	m_Config.GetMenuList(MenuIdPopup1, List);
	_InitializePopup(m_PopupMenu1, List);
}

void MenuCommandSet::_InitializePopupMenu2()
{
	std::list<CmdMenuItem_t> List;
	m_Config.GetMenuList(MenuIdPopup2, List);
	_InitializePopup(m_PopupMenu2, List);
}

void MenuCommandSet::_InitializeToolbar(MenuToolbar& _Toolbar, const CString& _sName, const std::list<CmdMenuItem_t>& _List)
{
	std::list<CmdMenuItem_t>::const_iterator Iter;
	std::list<MenuItem> List;
	CmdMenuItem_t nMenuId;
	MenuItem oItem;

	for(Iter= _List.begin(); Iter!=_List.end(); ++Iter)
	{
		nMenuId= (*Iter);
		if(ID_SEPARATOR==nMenuId){
			List.push_back(MenuItem());
		}
		else if(GetMenuItemFromActionCode(nMenuId, oItem)){
			List.push_back(oItem);
		}
	}
	_Toolbar.Create(_sName, List);
}

void MenuCommandSet::_InitializePopup(MenuPopup& _Popup, const std::list<CmdMenuItem_t>& _List)
{
	std::list<CmdMenuItem_t>::const_iterator Iter;
	std::list<MenuItem> List;
	CmdMenuItem_t nMenuId;
	MenuItem oItem;

	for(Iter= _List.begin(); Iter!=_List.end(); ++Iter)
	{
		nMenuId= (*Iter);
		if(ID_SEPARATOR==nMenuId){
			List.push_back(MenuItem());
		}
		else if(GetMenuItemFromActionCode(nMenuId, oItem)){
			List.push_back(oItem);
		}
	}
	_Popup.Create(List);
}
