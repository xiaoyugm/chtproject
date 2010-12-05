#pragma once

#include "..\stdafx.h"
//#include <map>
//#include <list>
//#include <string>
//using namespace std;
#import "msxml.dll"

#include "MenuItem.h" 
#include "types.h" 

class MenuCommandSetCfg
{
public:
	MenuCommandSetCfg();
	virtual ~MenuCommandSetCfg();

public:
	bool Load(const std::string& _FileName);

	string GetVersion();

	list<MenuItem>			GetMenuItems();
	bool GetMenuList(MenuId_t _iMenuId, std::list<CmdMenuItem_t>& _List);


private:
	string										m_sFileVersion;
	list<MenuItem>								m_MenuItemList;
	//map<MenuId_t, std::list<CmdMenuItem_t>>	m_MenusMap;

private:
	bool _LoadFile(const std::string& _FileName);
	void _LoadFileVersion(MSXML::IXMLDOMNodePtr _XMLNode);
	void _LoadMenuItemList(MSXML::IXMLDOMNodePtr _XMLNode);
	void _LoadMenuList(MSXML::IXMLDOMNodePtr _XMLNode);
	list<CmdMenuItem_t> _LoadIDList(MSXML::IXMLDOMNodePtr _XMLNode);

	void _ClearLists();
	string _GetBitmapFolder();

};
/*+- OmniWorks Replacement History - wtap_unitest`dart120`dart:menucommandsetcfg.h;1 */
/*       1*[973377] 03-JUL-2007 14:21:23 (GMT) PAQUIER */
/*         "extract toolbar config from xml file" */
/*+- OmniWorks Replacement History - wtap_unitest`dart120`dart:menucommandsetcfg.h;1 */
