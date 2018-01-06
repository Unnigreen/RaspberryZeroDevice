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
#include "SystemSettings.h"

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
	virtual void PrintAliveMsg(char *) = 0;
};

class CommunicationServer : public piServer
{
private:
	struct sockaddr_in ClntAddr;
	struct sockaddr_in srvrAddr;
	int ConnectionSocketId;
	char RxBuffer[C_SERVER_MAX_RX_BUFFER_SIZE];
	char TxBuffer[C_SERVER_MAX_TX_BUFFER_SIZE];

public:
	CommunicationServer();
	virtual ~CommunicationServer();

	void WaitForCommunicationServerConnection();
	void ClientService();

	void SendMessage();
	void SendSignal();
	void PrintAliveMsg(char *);
};

class DiscoveryServer : public piServer
{
private:
	struct sockaddr_in ClntAddr;
	struct sockaddr_in srvrAddr;
	char RxBuffer[D_SERVER_MAX_RX_BUFFER_SIZE];
	char TxBuffer[D_SERVER_MAX_TX_BUFFER_SIZE];

public:
	DiscoveryServer();
	virtual ~DiscoveryServer();

	void SendMessage();
	void SendSignal();
	void PrintAliveMsg(char *);

	void WaitForDiscoveryPing();
	void DiscoveryServerResponse();
};

}

#endif /* PISERVER_HPP_ */
