/*
 * CommandParser.hpp
 *
 *  Created on: Dec 21, 2017
 *      Author: unni
 */

#ifndef COMMANDPARSER_HPP_
#define COMMANDPARSER_HPP_

#include <pthread.h>
#include <mqueue.h>

namespace Command_Parser
{
typedef struct
{
	int a;
}msgType_abc;

typedef struct
{
	int a;
}msgType_xyz;

typedef struct
{
	char CommandType;
	union
	{
		msgType_abc abc;
		msgType_xyz xyz;
	}msg;
}msgStruct;

class CommandParser
{
private:
	static pthread_t CommandParserThreadHandle;
	static mqd_t msgQ_ID;

	void ProcessInputMessage(msgStruct*);
	bool SendSignal();
	static void * CommandParserTask(void *);

public:
	CommandParser();
	~CommandParser();

	static bool SendMessage(char *, unsigned long int);
	static void TaskEntry();
	void Run();
};

}

#endif /* COMMANDPARSER_HPP_ */
