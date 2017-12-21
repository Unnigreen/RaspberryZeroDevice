/*
 * CommandParser.cpp
 *
 *  Created on: Dec 21, 2017
 *      Author: unni
 */

#include "CommandParser.hpp"
#include <sys/msg.h>
#include <sys/ipc.h>

namespace Command_Parser
{

CommandParser::CommandParser()
{
	int msqid; /* return value from msgget() */

	msqid = msgget(1234, IPC_CREATE);

}

CommandParser::~CommandParser()
{

}

void CommandParser::ProcessInputMessage()
{

}

bool CommandParser::SendMessage(CommandStruct)
{
	bool retVal = false;

	return retVal;
}

bool CommandParser::SendSignal()
{
	bool retVal = false;

	return retVal;
}

}
