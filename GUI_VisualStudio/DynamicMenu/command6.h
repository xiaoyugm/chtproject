#pragma once

#include "AbstractCommand.h"

class Command6: public AbstractCommand
{
protected:
	Command6();
public:
	Command6(UINT _nID);
	virtual ~Command6();

public:
	virtual void Execute();
};
