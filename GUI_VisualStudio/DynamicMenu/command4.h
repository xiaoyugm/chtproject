#pragma once

#include "AbstractCommand.h"

class Command4: public AbstractCommand
{
protected:
	Command4();
public:
	Command4(UINT _nID);
	virtual ~Command4();

public:
	virtual void Execute();
};
