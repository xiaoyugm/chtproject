#pragma once

#include "AbstractCommand.h"

class Command3: public AbstractCommand
{
protected:
	Command3();
public:
	Command3(UINT _nID);
	virtual ~Command3();

public:
	virtual void Execute();
};
