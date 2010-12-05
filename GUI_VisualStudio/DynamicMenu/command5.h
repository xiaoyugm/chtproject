#pragma once

#include "AbstractCommand.h"

class Command5: public AbstractCommand
{
protected:
	Command5();
public:
	Command5(UINT _nID);
	virtual ~Command5();

public:
	virtual void Execute();
};
