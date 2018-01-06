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
	cout << "CommandParser msgQ_ID " << msgQ_ID << endl;
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

	cout << "CommandParser started" << endl;
	msgStruct msg;
	msg.CommandType = '2';
	msg.msg.abc.a = 22;
	SendMessage(&msg);
	while(1)
	{
		msgLen = mq_receive(msgQ_ID, (char *)&msgRcvd, sizeof(msgStruct), &msgPrio);
		cout << "msg rxed in CommandParser - type: " << msgRcvd.CommandType << " val: " << msgRcvd.msg.abc.a << " len: " << msgLen << endl;
	}
}

void * CommandParser::CommandParserTask(void *)
{
	CommandParser parser;
	parser.Run();

	return (void *)0;
}

void CommandParser::ProcessInputMessage()
{

}

bool CommandParser::SendMessage(msgStruct *msg)
{
	bool retVal = false;
	unsigned int msgSentStatus;

	msgSentStatus = mq_send(msgQ_ID, (char *)msg, sizeof(msgStruct), 0);
	return retVal;
}

bool CommandParser::SendSignal()
{
	bool retVal = false;

	return retVal;
}

}
