#include "stdafx.h"
#include "CommandInvoker.h"
#include "AbstractCommand.h"

CommandInvoker CommandInvoker::m_Invoker;

CommandInvoker::CommandInvoker()
{}

CommandInvoker::~CommandInvoker()
{}

CommandInvoker& CommandInvoker::GetInstance()
{
	return m_Invoker;
}

void CommandInvoker::ExecuteCommand(AbstractCommand& _Command)
{
	_Command.Execute();
}
