/*
 * ControlInterface.cpp
 *
 *  Created on: Jan 6, 2018
 *      Author: unni
 */

#include <iostream>
#include <unistd.h>
#include "ControlInterface.hpp"

using namespace std;

namespace Control_Interface
{

ControlInterface::ControlInterface()
{
	fptr = fopen("/dev/serial0", "a");
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
	ControlInterface serialControl;
	serialControl.Run();
}

bool ControlInterface::SendMessage(char *, unsigned long int)
{
	bool retVal = false;

	return retVal;
}

void ControlInterface::Run()
{
	while(1)
	{
//		cout << "Controller interface print" << endl;
		fprintf(fptr, "Hello ... !!!\n");
//		sleep(1);
	}
}

};
