/*
 * input.cpp
 *
 *  Created on: Nov 29, 2017
 *      Author: unni
 */
#include "piServer.hpp"

#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include "SystemSettings.h"

using namespace std;

namespace piServerNs
{
pthread_t piServer::CserverThreadHandle;
pthread_t piServer::DserverThreadHandle;
int piServer::CserverSocketId;
int piServer::DserverSocketId;

piServer::piServer()
{
	// constructor
}

piServer::~piServer()
{

}

int piServer::StartTask()
{
	pthread_create(&CserverThreadHandle, NULL, CommunicationServerTask, NULL);
	pthread_create(&DserverThreadHandle, NULL, DiscoveryServerTask, NULL);
	return 0;
}

void * piServer::CommunicationServerTask(void *)
{
	CommunicationServer Cserver;
	while(1)
	{
		Cserver.PrintAliveMsg();
		sleep(1);
	}
}

void * piServer::DiscoveryServerTask(void *)
{
	DiscoveryServer Dserver;
	while(1)
	{
		//		Bserver.PrintAliveMsg();
		sleep(1);
	}
}

CommunicationServer::CommunicationServer()
{
	// open tcp server socket
}

CommunicationServer::~CommunicationServer()
{

}

DiscoveryServer::DiscoveryServer()
{
	int  nBytes;
	socklen_t nLen;
	char buffer[1024];
	struct sockaddr_in NetAddr;
	struct sockaddr_in RecvAddr;

	/*Create UDP socket*/
	DserverSocketId = socket(PF_INET, SOCK_DGRAM, 0);

	/*Configure settings in address struct*/
	NetAddr.sin_family = AF_INET;
	NetAddr.sin_port = htons(D_SERVER_PORT);
	NetAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	memset(NetAddr.sin_zero, '\0', sizeof(NetAddr.sin_zero));

	bind(DserverSocketId, (struct sockaddr*)&NetAddr, sizeof(NetAddr));
	nBytes = 10;

	nLen = sizeof(RecvAddr);
	while(1){
		recvfrom(DserverSocketId, (void*)buffer, nBytes, 0, (struct sockaddr *)&RecvAddr, &nLen);
		NetAddr.sin_addr.s_addr = RecvAddr.sin_addr.s_addr;
		for(int c = 0; c < 5; c++){
			sendto(DserverSocketId, (void*)buffer, nBytes, 0, (struct sockaddr *)&NetAddr, sizeof(NetAddr));
			PrintAliveMsg();
			sleep(1);
		}
	}
}

DiscoveryServer::~DiscoveryServer()
{

}

void CommunicationServer::SendMessage()
{

}

void CommunicationServer::SendSignal()
{

}

void DiscoveryServer::SendMessage()
{

}

void DiscoveryServer::SendSignal()
{

}

void CommunicationServer::PrintAliveMsg(void)
{
	std::cout << "C-Server alive" << std::endl;
}

void DiscoveryServer::PrintAliveMsg(void)
{
	std::cout << "B-Server alive" << std::endl;
}

}
