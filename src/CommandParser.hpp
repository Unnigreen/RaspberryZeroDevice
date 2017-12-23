/*
 * CommandParser.hpp
 *
 *  Created on: Dec 21, 2017
 *      Author: unni
 */

#ifndef COMMANDPARSER_HPP_
#define COMMANDPARSER_HPP_

#include <pthread.h>

namespace Command_Parser
{

typedef struct
{
	char CommandType;
	union
	{

	};
}CommandStruct;

class CommandParser
{
private:
	static int msqid;
	static pthread_t CommandParserThreadHandle;

	void ProcessInputMessage();
	bool SendSignal();

public:
	CommandParser();
	~CommandParser();

	static bool SendMessage(CommandStruct *);
	static void TaskEntry();
	static void * CommandParserTask(void *);
};

}

#endif /* COMMANDPARSER_HPP_ */
