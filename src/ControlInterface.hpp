/*
 * ControlInterface.hpp
 *
 *  Created on: Jan 6, 2018
 *      Author: unni
 */

#ifndef CONTROLINTERFACE_HPP_
#define CONTROLINTERFACE_HPP_

namespace Control_Interface
{

class ControlInterface
{
private:
	static void * ControlInterfaceTask(void *);
	void ProcessInputMessage();

protected:

public:
	ControlInterface();
	~ControlInterface();

	static void StartTask();
	static bool SendMessage(char *, unsigned long int);
	void Run();
};

}

#endif /* CONTROLINTERFACE_HPP_ */
