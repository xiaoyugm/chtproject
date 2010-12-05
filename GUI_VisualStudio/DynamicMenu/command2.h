#pragma once

#include "AbstractCommand.h"

class Command2: public AbstractCommand
{
protected:
	Command2();
public:
	Command2(UINT _nID);
	virtual ~Command2();

public:
	virtual void Execute();
};
