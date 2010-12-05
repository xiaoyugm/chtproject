#pragma once 


class AbstractCommand;
class CDataItem;

class CommandFactory
{
public:
	CommandFactory();
	virtual ~CommandFactory();

public:
	AbstractCommand* CreateCommand(UINT _nCommandCode);

private:
	AbstractCommand* _CommandCreation(UINT _nCommandCode);

};
