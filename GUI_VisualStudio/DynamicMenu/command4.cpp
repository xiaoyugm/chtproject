#include "stdafx.h"
#include "Command4.h"

Command4::Command4()
:AbstractCommand()
{}

Command4::Command4(UINT _nID)
:AbstractCommand(_nID)
{}

Command4::~Command4()
{}

void Command4::Execute()
{
	AfxMessageBox(_T("Execution of Command 4"));
}



