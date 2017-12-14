/*
 * input.hpp
 *
 *  Created on: Nov 29, 2017
 *      Author: unni
 */

#ifndef PISERVER_HPP_
#define PISERVER_HPP_

#include <pthread.h>
#include <arpa/inet.h>

namespace piServerNs
{

class piServer
{
private:

protected:
	static pthread_t CserverThreadHandle;
	static pthread_t DserverThreadHandle;
	static int CserverSocketId;
	static int DserverSocketId;

public:
	piServer();
	virtual ~piServer();
	static int StartTask();
	static void * CommunicationServerTask(void *);
	static void * DiscoveryServerTask(void *);

	virtual void SendMessage(void) = 0;
	virtual void SendSignal(void) = 0;
	virtual void PrintAliveMsg(void) = 0;
};

class CommunicationServer : public piServer
{
private:

public:
	CommunicationServer();
	virtual ~CommunicationServer();

	void SendMessage();
	void SendSignal();
	void PrintAliveMsg(void);
};

class DiscoveryServer : public piServer
{
private:
	struct sockaddr_in RecvAddr;
	struct sockaddr_in srvrAddr;
	char buffer[1024];

public:
	DiscoveryServer();
	virtual ~DiscoveryServer();

	void SendMessage();
	void SendSignal();
	void PrintAliveMsg(void);
	void PrintReceivedMsg(char *);

	void WaitForDiscoveryPing();
	void DiscoveryServerResponse();
};

}

#endif /* PISERVER_HPP_ */
