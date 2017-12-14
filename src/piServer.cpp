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
#include "SystemSettings.h"
//#include <arpa/inet.h>

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
//		Cserver.PrintAliveMsg();
		sleep(1);
	}
}

void * piServer::DiscoveryServerTask(void *)
{
	DiscoveryServer Dserver;

	while(1){
		Dserver.WaitForDiscoveryPing();
		Dserver.DiscoveryServerResponse();
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
	/*Create UDP socket*/
	DserverSocketId = socket(PF_INET, SOCK_DGRAM, 0);

	/*Configure settings in address struct*/
	srvrAddr.sin_family = AF_INET;
	srvrAddr.sin_port = htons(D_SERVER_PORT);
	srvrAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	memset(srvrAddr.sin_zero, '\0', sizeof(srvrAddr.sin_zero));

	bind(DserverSocketId, (struct sockaddr*)&srvrAddr, sizeof(srvrAddr));
}

DiscoveryServer::~DiscoveryServer()
{

}

void DiscoveryServer::WaitForDiscoveryPing(void)
{
	unsigned int nBytes = 10;
	socklen_t nLen = sizeof(RecvAddr);

	recvfrom(DserverSocketId, (void*)buffer, nBytes, 0, (struct sockaddr *)&RecvAddr, &nLen);
}

void DiscoveryServer::DiscoveryServerResponse(void)
{
	struct sockaddr_in SendAddr;
	unsigned int nBytes = 10;

	SendAddr = RecvAddr;
	for(int c = 0; c < 5; c++){
		sendto(DserverSocketId, (void*)buffer, nBytes, 0, (struct sockaddr *)&SendAddr, sizeof(SendAddr));
		PrintAliveMsg();
		PrintReceivedMsg(buffer);
		sleep(1);
	}
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

void DiscoveryServer::PrintReceivedMsg(char * msg)
{
	std::cout << "B-Server received msg :" << msg << std::endl;
}

}
