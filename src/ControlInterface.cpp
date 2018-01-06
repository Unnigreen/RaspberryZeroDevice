/*
 * ControlInterface.cpp
 *
 *  Created on: Jan 6, 2018
 *      Author: unni
 */
#include "ControlInterface.hpp"

namespace Control_Interface
{

ControlInterface::ControlInterface()
{

}

ControlInterface::~ControlInterface()
{

}

void * ControlInterface::ControlInterfaceTask(void *)
{

	return (void *)0;
}
void ControlInterface::ProcessInputMessage()
{

}
void ControlInterface::StartTask()
{

}

bool ControlInterface::SendMessage(char *, unsigned long int)
{
	bool retVal = false;

	return retVal;
}

void ControlInterface::Run()
{

}

};
