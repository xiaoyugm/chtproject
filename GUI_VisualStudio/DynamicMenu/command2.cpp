#include "stdafx.h"
#include "Command2.h"

Command2::Command2()
:AbstractCommand()
{}

Command2::Command2(UINT _nID)
:AbstractCommand(_nID)
{}

Command2::~Command2()
{}

void Command2::Execute()
{
	AfxMessageBox(_T("Execution of Command 2"));
}

