#include "stdafx.h"
#include "Command1.h"

Command1::Command1()
:AbstractCommand()
{}

Command1::Command1(UINT _nID)
:AbstractCommand(_nID)
{}

Command1::~Command1()
{}

void Command1::Execute()
{
	AfxMessageBox(_T("Execution of Command 1"));
}

