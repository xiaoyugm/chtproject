#include "stdafx.h"
#include "Command6.h"
#include "types.h" 

Command6::Command6()
:AbstractCommand()
{}

Command6::Command6(UINT _nID)
:AbstractCommand(_nID)
{}

Command6::~Command6()
{}

void Command6::Execute()
{
	AfxMessageBox(_T("Execution of Command 6"));
}


