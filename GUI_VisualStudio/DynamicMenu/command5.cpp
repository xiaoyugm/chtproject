#include "stdafx.h"
#include "Command5.h"

Command5::Command5()
:AbstractCommand()
{}

Command5::Command5(UINT _nID)
:AbstractCommand(_nID)
{}

Command5::~Command5()
{}

void Command5::Execute()
{
	AfxMessageBox(_T("Execution of Command 5"));
}


