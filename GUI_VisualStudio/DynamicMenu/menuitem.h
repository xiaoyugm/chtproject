#pragma once

#include "types.h" 

class MenuItem
{
friend class MenuItemList;
public:
	MenuItem();
	MenuItem(CmdMenuItem_t _nActionCode, const CString& _sDisplayName, const CString& _sIconFileName);
	MenuItem(CmdMenuItem_t _nActionCode, const CString& _sDisplayName, const CString& _sTooltip, const CString& _sStatus, const CString& _sIconFileName);
	MenuItem(CmdMenuItem_t _nActionCode, const CString& _sDisplayName);
	virtual ~MenuItem();

	CString GetIconFileName() const;
	CString GetDisplayName() const;
	CString GetTooltip() const;
	CString GetStatus() const;
	UINT GetCommandID() const;
	CmdMenuItem_t GetActionCode() const;
	bool IsSeparator() const;

private:
	CString m_sDisplayName;
	CString m_sTooltip;
	CString m_sStatus;
	CString m_sIconFileName;
	UINT m_nCommandID;
	CmdMenuItem_t m_nActionCode;
};
/*+- OmniWorks Replacement History - wtap_unitest`dart120`dart:menuitem.h;3 */
/*       3*[973667] 04-JUL-2007 07:55:46 (GMT) PAQUIER */
/*         "read tooltip and status" */
/*       2*[969461] 22-JUN-2007 12:05:45 (GMT) PAQUIER */
/*         "add ID_SEPARATOR support for dynamic toolbar" */
/*       1*[967020] 19-JUN-2007 15:57:12 (GMT) PAQUIER */
/*         "simple menu item for dyanamic commands" */
/*+- OmniWorks Replacement History - wtap_unitest`dart120`dart:menuitem.h;3 */
