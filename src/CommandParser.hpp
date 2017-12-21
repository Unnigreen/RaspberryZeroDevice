/*
 * CommandParser.hpp
 *
 *  Created on: Dec 21, 2017
 *      Author: unni
 */

#ifndef COMMANDPARSER_HPP_
#define COMMANDPARSER_HPP_

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
public:
	CommandParser();
	~CommandParser();

private:
	int msqid;

	void ProcessInputMessage();
	bool SendMessage(CommandStruct);
	bool SendSignal();
};

}

#endif /* COMMANDPARSER_HPP_ */
