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

// test code start
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>
void *thread_main_1(void *x_void_ptr);
void *thread_main_2(void *x_void_ptr);
void *thread_main_3(void *x_void_ptr);
// test code end

int main() {

//	piServerNs::piServer::StartTask();
//	Command_Parser::CommandParser::TaskEntry();

	cout << "MAIN RUNNING " << endl;

	// test code start
	pthread_t ThreadHandle_1;
	pthread_t ThreadHandle_2;
	pthread_create(&ThreadHandle_1, NULL, thread_main_1, NULL);
	pthread_create(&ThreadHandle_2, NULL, thread_main_2, NULL);
	// test code end

	while(1)
	{
		sleep(10);
	}
	return 0;
}

typedef struct
{
	int a;
	int b;
	int c;
	int d;
}testMsg;

void *thread_main_1(void *x_void_ptr)
{
	struct mq_attr attr;
	mqd_t MsgQ_ID;
	testMsg msgRx;

	attr.mq_flags = 0;
	attr.mq_maxmsg = 10;
	attr.mq_msgsize = sizeof(testMsg);
	attr.mq_curmsgs = 0;

	MsgQ_ID = mq_open("/MyMsgQ", O_CREAT | O_RDWR, 0777, &attr);
	cout << "thread 1 MsgQ_ID " << MsgQ_ID << endl;
	msgRx.a = 11;
	msgRx.b = 22;
	msgRx.c = 33;
	msgRx.d = 44;
	while(1)
	{
		mq_send(MsgQ_ID, (char *)&msgRx, sizeof(msgRx), 0);
//		cout << "thread running 1 " << endl;
		cout << "thread 1 sent message" << endl;
		sleep(1);
	}
}

void *thread_main_2(void *x_void_ptr)
{
	struct mq_attr attr;
	mqd_t MsgQ_ID;
	testMsg msgRx;
	unsigned int msgPrio;

	attr.mq_flags = 0;
	attr.mq_maxmsg = 10;
	attr.mq_msgsize = sizeof(testMsg);
	attr.mq_curmsgs = 0;

	MsgQ_ID = mq_open("/MyMsgQ", O_CREAT | O_RDWR, 0777, &attr);
	cout << "thread 2 MsgQ_ID " << MsgQ_ID << endl;
	while(1)
	{

		mq_receive(MsgQ_ID, (char *)&msgRx, sizeof(msgRx), &msgPrio);
//		cout << "thread running 2 " << endl;
		cout << "Thread 2 rxed message: a-" << msgRx.a << " b-" << msgRx.b << " c-" << msgRx.c << " d-" << msgRx.d << endl;
//		sleep(1);
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
