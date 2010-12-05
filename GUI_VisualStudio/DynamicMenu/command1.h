#pragma once

#include "AbstractCommand.h"

class Command1: public AbstractCommand
{
protected:
	Command1();
public:
	Command1(UINT _nID);
	virtual ~Command1();

public:
	virtual void Execute();
};
