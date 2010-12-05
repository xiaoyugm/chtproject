#pragma once

class AbstractCommand
{
public:
	AbstractCommand(void);
	AbstractCommand(UINT _nID);
	virtual ~AbstractCommand(void);

public:
	virtual void Execute();
	virtual void UnExecute();

protected:
	UINT		m_nID;
};
