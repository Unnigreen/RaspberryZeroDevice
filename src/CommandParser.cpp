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
#include <fcntl.h>
#include <sys/stat.h>

using namespace std;

namespace Command_Parser
{
pthread_t CommandParser::CommandParserThreadHandle;
mqd_t CommandParser::msgQ_ID;

CommandParser::CommandParser()
{
	struct mq_attr attr;

	attr.mq_flags = 0;
	attr.mq_maxmsg = 10;
	attr.mq_msgsize = sizeof(msgStruct);
	attr.mq_curmsgs = 0;

	msgQ_ID = mq_open("/MyMsgQ", O_CREAT | O_RDWR, 0777, &attr);
//	cout << "CommandParser msgQ_ID " << msgQ_ID << endl;
}

CommandParser::~CommandParser()
{

}

void CommandParser::TaskEntry()
{
	pthread_create(&CommandParserThreadHandle, NULL, CommandParserTask, NULL);
}

void CommandParser::Run()
{
	msgStruct msgRcvd;
	unsigned int msgPrio;
	ssize_t msgLen = 0;

//	cout << "CommandParser started" << endl;
	while(1)
	{
		msgLen = mq_receive(msgQ_ID, (char *)&msgRcvd, sizeof(msgStruct), &msgPrio);
		if(msgLen > 0)
		{
			ProcessInputMessage(&msgRcvd);
		}
	}
}

void * CommandParser::CommandParserTask(void *)
{
	CommandParser parser;
	parser.Run();

	return (void *)0;
}

void CommandParser::ProcessInputMessage(msgStruct* msgRcvd)
{
	char* msg = (char*)msgRcvd;
//	cout << "Msg received to process : " << msg << endl;

	switch(msgRcvd->CommandType)
	{
	case 'a':
		cout << "aaaaa" << endl;
		break;
	case 'b':
		cout << "bbbbb" << endl;
		break;
	case 'c':
		cout << "ccccc" << endl;
		break;
	default:
		cout << "DDDDD" << endl;
		break;
	}
}

bool CommandParser::SendMessage(char *msg, unsigned long int len)
{
	bool retVal = false;

	if(len <= sizeof(msgStruct))
	{
		if(mq_send(msgQ_ID, msg, len, 0) == 0)
		{
			retVal = true;
		}
	}
	return retVal;
}

bool CommandParser::SendSignal()
{
	bool retVal = false;

	return retVal;
}

}
