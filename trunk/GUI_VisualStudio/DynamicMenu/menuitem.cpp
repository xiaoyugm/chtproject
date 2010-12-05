#include "stdafx.h"
#include "MenuItem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

MenuItem::MenuItem()
:m_nCommandID(ID_SEPARATOR),
m_nActionCode(CmdNone)
{}

MenuItem::MenuItem(CmdMenuItem_t _nActionCode, const CString& _sDisplayName, const CString& _sIconFileName)
:m_nCommandID(ID_SEPARATOR),
m_sIconFileName(_sIconFileName),
m_sDisplayName(_sDisplayName),
m_nActionCode(_nActionCode)
{}

MenuItem::MenuItem(CmdMenuItem_t _nActionCode, const CString& _sDisplayName, const CString& _sTooltip, const CString& _sStatus, const CString& _sIconFileName)
:m_nCommandID(ID_SEPARATOR),
m_sIconFileName(_sIconFileName),
m_sDisplayName(_sDisplayName),
m_sTooltip(_sTooltip),
m_sStatus(_sStatus),
m_nActionCode(_nActionCode)
{}

MenuItem::MenuItem(CmdMenuItem_t _nActionCode, const CString& _sDisplayName)
:m_nCommandID(ID_SEPARATOR),
m_sDisplayName(_sDisplayName),
m_nActionCode(_nActionCode)
{}

MenuItem::~MenuItem()
{}

CString MenuItem::GetIconFileName() const
{
	return m_sIconFileName;
}

CString MenuItem::GetDisplayName() const
{
	return m_sDisplayName;
}

/** @brief the string to use for the tooltip associated with the menu
* @return CString the tooltip string
*/
CString MenuItem::GetTooltip() const
{
	if(m_sTooltip.IsEmpty()){
		return m_sDisplayName;
	}
	return m_sTooltip;
}

CString MenuItem::GetStatus() const
{
	if(m_sStatus.IsEmpty()){
		return m_sDisplayName;
	}
	return m_sStatus;
}

/** @brief Return the Command ID of the menu item
* @remarks A command id is unique in a CommandSet.<br>
* the command id is created at the object creation when it is inserted in the MenuItemList
* embded by the MenuCommandSet object.<br>
* ATTENTION: CommandIDs MUST NOT BE in conflict with MFC command ids used for WM_COMMAND()
* @return CString the tooltip string
*/
UINT MenuItem::GetCommandID() const
{
	return m_nCommandID;
}
	
/** @brief Return the command code associated with the MenuItem
* @remarks the command code is in general transmitted to the CommandInvoker for action.
* @return CmdMenuItem_t an avialble command
*/
CmdMenuItem_t MenuItem::GetActionCode() const
{
	return m_nActionCode;
}

/** @brief Tell if the current menu item is a Separator menu
* @remarks see ID_SEPARATOR or MF_SEPARATOR in MFC help for details 
* @return bool true if it is a separator
*/
bool MenuItem::IsSeparator() const
{
	return (bool)(ID_SEPARATOR==m_nCommandID);
}
