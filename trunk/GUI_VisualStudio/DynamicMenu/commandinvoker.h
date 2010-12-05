#pragma once

class AbstractCommand;

class CommandInvoker
{
protected:
	CommandInvoker();
	CommandInvoker(CommandInvoker&){};
public:
	virtual ~CommandInvoker();

public:
	static CommandInvoker& GetInstance();

public:
	void ExecuteCommand(AbstractCommand& _Command);


private:
	static CommandInvoker m_Invoker;
};
/*+- OmniWorks Replacement History - wtap_unitest`dart120`dart:commandinvoker.h;1 */
/*       1*[967020] 19-JUN-2007 15:57:12 (GMT) PAQUIER */
/*         "command invoker for dynamic commands (bypass MFC handlers)" */
/*+- OmniWorks Replacement History - wtap_unitest`dart120`dart:commandinvoker.h;1 */
