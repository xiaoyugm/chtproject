#include "stdafx.h"
#include "AbstractCommand.h"

AbstractCommand::AbstractCommand()
:m_nID(0)
{}

AbstractCommand::AbstractCommand(UINT _nID)
:m_nID(_nID)
{}

AbstractCommand::~AbstractCommand()
{}


void AbstractCommand::Execute()
{}

void AbstractCommand::UnExecute()
{}

