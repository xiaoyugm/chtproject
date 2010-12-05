#include "..\stdafx.h"
#include "MenuCommandSetCfg.h"
#include "FileTools.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

MenuCommandSetCfg::MenuCommandSetCfg()
{}

MenuCommandSetCfg::~MenuCommandSetCfg()
{}

/** @brief Load and analyze the XML configuration file
* @remarks CoInitialize or CoInitializeEx must be called before (use MSXML)
* @param _sFileName the full path name of an existing file
*/
bool MenuCommandSetCfg::Load(const std::string& _sFileName)
{
	return _LoadFile(_sFileName);
}

std::string MenuCommandSetCfg::GetVersion()
{
	return m_sFileVersion;
}

/** @brief return the list of available Equipment modules
* @return std::list<std::string> only simple file names are returned
*/
std::list<MenuItem> MenuCommandSetCfg::GetMenuItems()
{
	return m_MenuItemList;
}

bool MenuCommandSetCfg::GetMenuList(MenuId_t _iMenuId, std::list<CmdMenuItem_t>& _List)
{
	_List.clear();
	map<MenuId_t, list<CmdMenuItem_t>>::const_iterator Iter= m_MenusMap.find(_iMenuId);
	if(Iter!=m_MenusMap.end()){
		_List= Iter->second;
		return true;
	}
	return false;
}


/** @brief Load all Application settings in one shot from the XML file.
* @remarks CoInitialize() or CoInitializeEx() must have been called before using this method.
* @param _sFileName the full path name of an existing file
*/
bool MenuCommandSetCfg::_LoadFile(const std::string& _sFileName)
{
	const _bstr_t XMLDOM_OBJECT= _T("Microsoft.XMLDOM");
	const _bstr_t NODE_DART(_T("uicfg"));
	const _bstr_t NODE_COMMANDS(_T("commands"));
	const _bstr_t NODE_VERSION(_T("version"));
	const _bstr_t NODE_COMMANDLIST(_T("commandlist"));
	const _bstr_t NODE_MENULIST(_T("menulist"));

	bool bResult= false;

	try
	{
		MSXML::IXMLDOMDocumentPtr XMLDom;
		HRESULT hResult = XMLDom.CreateInstance((LPCSTR)XMLDOM_OBJECT);
		if(S_OK==hResult)
		{
			_ClearLists();

			_bstr_t FileName(_sFileName.c_str());

			if(XMLDom->load(FileName))
			{
				MSXML::IXMLDOMNodePtr Root= XMLDom->selectSingleNode(NODE_DART);
				MSXML::IXMLDOMNodePtr XMLNode;
				MSXML::IXMLDOMNodePtr XMLNode2;
				if( Root != NULL )
				{
					//load the file version
					XMLNode = Root->selectSingleNode(NODE_VERSION);
					_LoadFileVersion(XMLNode);

					//load the list of menu items
					XMLNode = Root->selectSingleNode(NODE_COMMANDS);
					if(XMLNode){
						XMLNode2= XMLNode->selectSingleNode(NODE_COMMANDLIST);
						_LoadMenuItemList(XMLNode2);

						XMLNode2= XMLNode->selectSingleNode(NODE_MENULIST);
						_LoadMenuList(XMLNode2);
					}
					bResult= true;
				}
			}
		}
		else{
			TRACE(_T("Failed to load XMLDom (%x)\n"), hResult);
		}
	}
	catch(...){
		TRACE(_T("Exception while loading config file\n"));
	}
	return bResult;
}




/** @brief Load the list of MenuItems available in the xml cfg file
* @remarks Fill the internal m_MenuItemList list.
* @param _XMLNode The current node that should be opened on <commands><commandlist>
* @throw exception thrown by MSXML usage
*/
void MenuCommandSetCfg::_LoadMenuItemList(MSXML::IXMLDOMNodePtr _XMLNode)
{
	if(NULL==_XMLNode){
		return;
	}
	const _bstr_t ATTR_NAME(_T("name"));
	const _bstr_t ATTR_CMDID(_T("cmdid"));
	const _bstr_t ATTR_BITMAP(_T("bitmap"));
	const _bstr_t ATTR_TOOLTIP(_T("tooltip"));
	const _bstr_t ATTR_STATUS(_T("status"));

	std::string		sFolder= _GetBitmapFolder();
	std::string		sName;
	std::string		sBitmap;
	std::string		sTooltip;
	std::string		sStatus;
	std::string		sCmdId;
	CmdMenuItem_t	CmdId;

	MenuItem oItem;
	MSXML::IXMLDOMNodePtr XMLNode= _XMLNode->firstChild;
	MSXML::IXMLDOMNodePtr XMLAttribute;
	while(XMLNode)
	{
		CmdId= CmdNone;
		sName.empty();
		sCmdId.empty();
		sBitmap.empty();
		sTooltip.empty();
		sStatus.empty();

		XMLAttribute= XMLNode->attributes->getNamedItem(ATTR_CMDID);
		if(XMLAttribute){
			sCmdId= XMLAttribute->text;
			CmdId= (CmdMenuItem_t)atoi(sCmdId.c_str());
		}
		XMLAttribute= XMLNode->attributes->getNamedItem(ATTR_BITMAP);
		if(XMLAttribute){
			sBitmap= sFolder;
			sBitmap.append(XMLAttribute->text);
		}
		XMLAttribute= XMLNode->attributes->getNamedItem(ATTR_TOOLTIP);
		if(XMLAttribute){
			sTooltip= XMLAttribute->text;
		}
		XMLAttribute= XMLNode->attributes->getNamedItem(ATTR_STATUS);
		if(XMLAttribute){
			sStatus= XMLAttribute->text;
		}
		XMLAttribute= XMLNode->attributes->getNamedItem(ATTR_NAME);
		if(XMLAttribute){
			sName= XMLAttribute->text;
		}

		m_MenuItemList.push_back(MenuItem(CmdId, sName.c_str(), sTooltip.c_str(), sStatus.c_str(), sBitmap.c_str()));

		XMLNode = XMLNode->nextSibling;
	}
}

/** @brief Load the configuration for the dynamic toolbars and popups from the xml cfg file
* @remarks Fill the internal m_MenusMap map.
* @param _XMLNode The current node that should be opened on <commands><menulist>
* @throw exception thrown by MSXML usage
*/
void MenuCommandSetCfg::_LoadMenuList(MSXML::IXMLDOMNodePtr _XMLNode)
{
	if(NULL==_XMLNode){
		return;
	}

	const _bstr_t ATTR_ID(_T("id"));

	std::list<CmdMenuItem_t> IDs;
	MenuId_t iID;
	std::string sID;
	MSXML::IXMLDOMNodePtr XMLAttribute;
	MSXML::IXMLDOMNodePtr XMLNode= _XMLNode->firstChild;

	while(XMLNode)
	{
		iID= MenuIdUnkwon;
		sID.empty();

		XMLAttribute= XMLNode->attributes->getNamedItem(ATTR_ID);
		if(XMLAttribute){
			sID=	XMLAttribute->text;
			iID=	(MenuId_t)atoi(sID.c_str());
		}
		IDs= _LoadIDList(XMLNode);

		m_MenusMap.insert(make_pair(iID, IDs));

		XMLNode = XMLNode->nextSibling;
	}
}

std::list<CmdMenuItem_t> MenuCommandSetCfg::_LoadIDList(MSXML::IXMLDOMNodePtr _XMLNode)
{
	std::list<CmdMenuItem_t> List;

	if(NULL!=_XMLNode)
	{
		std::string sTemp;
		MSXML::IXMLDOMNodePtr XMLNode= _XMLNode->firstChild;
		while(XMLNode)
		{
			sTemp= XMLNode->text;
			List.push_back((CmdMenuItem_t)atoi(sTemp.c_str()));
			XMLNode = XMLNode->nextSibling;
		}
	}

	return List;
}

/** @brief Load the version of the XML file
* @remarks versio nis a string that should be formatted like 1.0
* @param _XMLNode The current node that should be opened on "modules"
* @throw exception thrown by MSXML usage
*/
void MenuCommandSetCfg::_LoadFileVersion(MSXML::IXMLDOMNodePtr _XMLNode)
{
	if(NULL==_XMLNode){
		return;
	}
	m_sFileVersion= _XMLNode->text;	
}


/** @brief reset state of the singleton
* @remarks clear current configuration. erase all information stored from the read of a job<br>
* method called from _LoadFile() before reading a file.
* @see _LoadFile
*/
void MenuCommandSetCfg::_ClearLists()
{
	m_sFileVersion.empty();
	m_MenuItemList.clear();
	m_MenusMap.clear();
}

std::string MenuCommandSetCfg::_GetBitmapFolder()
{
	std::string sFolder;
	CString sDir;
	CFileTools::GetExecutableDirectory(sDir);
	sDir.Append(_T("\\images\\"));

	sFolder= sDir;
	return sFolder;
}
