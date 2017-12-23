//============================================================================
// Name        : Rasperri_zero.cpp
// Author      : Unni
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <unistd.h>
#include <pthread.h>

#include "piServer.hpp"
#include "CommandParser.hpp"

using namespace std;

//void *thread_main_1(void *x_void_ptr);
//void *thread_main_2(void *x_void_ptr);
//void *thread_main_3(void *x_void_ptr);

int main() {

	piServerNs::piServer::StartTask();
	Command_Parser::CommandParser::TaskEntry();

	cout << "MAIN RUNNING " << endl;
	while(1)
	{
		sleep(10);
	}
	return 0;
}

void *thread_main_1(void *x_void_ptr)
{
	while(1)
	{
		cout << "thread running 1 " << endl;
		sleep(1);
	}
}

void *thread_main_2(void *x_void_ptr)
{
	while(1)
	{
		cout << "thread running 2 " << endl;
		sleep(1);
	}
}

void *thread_main_3(void *x_void_ptr)
{
	while(1)
	{
		cout << "thread running 3 " << endl;
		sleep(1);
	}
}

