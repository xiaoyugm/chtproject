#include "stdafx.h"
#include "Command3.h"

Command3::Command3()
:AbstractCommand()
{}

Command3::Command3(UINT _nID)
:AbstractCommand(_nID)
{}

Command3::~Command3()
{}

void Command3::Execute()
{
	AfxMessageBox(_T("Execution of Command 3"));
}


