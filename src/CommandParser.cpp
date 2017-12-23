/*
 * CommandParser.cpp
 *
 *  Created on: Dec 21, 2017
 *      Author: unni
 */

#include "CommandParser.hpp"
#include <iostream>
#include <unistd.h>
#include <sys/msg.h>
#include <sys/ipc.h>

using namespace std;

namespace Command_Parser
{

int CommandParser::msqid;
pthread_t CommandParser::CommandParserThreadHandle;

CommandParser::CommandParser()
{
	msqid = 0;

	msqid = msgget(1234, IPC_CREAT);

}

CommandParser::~CommandParser()
{

}

void CommandParser::TaskEntry()
{
	pthread_create(&CommandParserThreadHandle, NULL, CommandParserTask, NULL);
}

void * CommandParser::CommandParserTask(void *)
{
	CommandParser parser;
	CommandStruct cmdRcv;
	ssize_t len = 0;

	while(1)
	{
		len = msgrcv(msqid, (void *)&cmdRcv, sizeof(cmdRcv), 0, MSG_NOERROR);
//		cout << "Command parser msg : " << len << endl;
		printf("Command parser msg : %d, %d \n", len, cmdRcv.CommandType);
	}
}

void CommandParser::ProcessInputMessage()
{

}

bool CommandParser::SendMessage(CommandStruct *cmd)
{
	bool retVal = false;

	msgsnd(msqid, (void *)cmd, sizeof(cmd), IPC_NOWAIT);
	return retVal;
}

bool CommandParser::SendSignal()
{
	bool retVal = false;

	return retVal;
}

}
