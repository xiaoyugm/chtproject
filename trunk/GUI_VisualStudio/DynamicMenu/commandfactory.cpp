#include "stdafx.h"
#include "CommandFactory.h"
#include "Command1.h"
#include "Command2.h"
#include "Command3.h"
#include "Command4.h"
#include "Command5.h"
#include "Command6.h"

#include "types.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CommandFactory::CommandFactory()
{}

CommandFactory::~CommandFactory()
{}

AbstractCommand* CommandFactory::CreateCommand(UINT _nCommandCode)
{
	return _CommandCreation(_nCommandCode);
}

AbstractCommand* CommandFactory::_CommandCreation(UINT _nCommandCode)
{
	AbstractCommand* pCommand= NULL;

	switch(_nCommandCode)
	{
		case CmdCommand1:
			pCommand= new Command1(_nCommandCode);
			break;
		case CmdCommand2:
			pCommand= new Command2(_nCommandCode);
			break;
		case CmdCommand3:
			pCommand= new Command3(_nCommandCode);
			break;
		case CmdCommand4:
			pCommand= new Command4(_nCommandCode);
			break;
		case CmdCommand5:
			pCommand= new Command5(_nCommandCode);
			break;			
		case CmdCommand6:
			pCommand= new Command6(_nCommandCode);
			break;			
	}
	return pCommand;
}



