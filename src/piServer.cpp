/*
 * input.cpp
 *
 *  Created on: Nov 29, 2017
 *      Author: unni
 */
#include "piServer.hpp"

#include <pthread.h>
#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include "SystemSettings.h"
#include "CommandParser.hpp"

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
		Cserver.WaitForCommunicationServerConnection();
		Cserver.PrintAliveMsg("Connected");
		Cserver.ClientService();
		Cserver.PrintAliveMsg("Disconnected");
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
	/*Create TCP socket*/
	CserverSocketId = socket(PF_INET, SOCK_STREAM, 0);
	ConnectionSocketId = 0;

	/*Configure settings in address struct*/
	srvrAddr.sin_family = AF_INET;
	srvrAddr.sin_port = htons(C_SERVER_PORT);
	srvrAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	memset(srvrAddr.sin_zero, '\0', sizeof(srvrAddr.sin_zero));

	bind(CserverSocketId, (struct sockaddr*)&srvrAddr, sizeof(srvrAddr));
	listen(CserverSocketId, 5);
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
	socklen_t AddrLen = sizeof(ClntAddr);

	memset(RxBuffer, 0, sizeof(RxBuffer));
	recvfrom(DserverSocketId, (void*)RxBuffer, nBytes, 0, (struct sockaddr *)&ClntAddr, &AddrLen);
}

void DiscoveryServer::DiscoveryServerResponse(void)
{
	struct sockaddr_in SendAddr;
	unsigned int TxLen = 10;

	SendAddr = ClntAddr;
	memset(TxBuffer, 0, sizeof(TxBuffer));
	strcpy(TxBuffer, RxBuffer);

//	Command_Parser::CommandStruct cmdTx;
//	cmdTx.CommandType = 7;
//	Command_Parser::CommandParser::SendMessage(&cmdTx);


	for(int c = 0; c < 5; c++){
		sendto(DserverSocketId, (void*)TxBuffer, TxLen, 0, (struct sockaddr *)&SendAddr, sizeof(SendAddr));
		PrintAliveMsg(RxBuffer);
		sleep(1);
	}
}

void CommunicationServer::WaitForCommunicationServerConnection(void)
{
	socklen_t AddrLen = sizeof(ClntAddr);

	ConnectionSocketId = accept(CserverSocketId, (struct sockaddr *)&ClntAddr, &AddrLen);
}

void CommunicationServer::ClientService(void)
{
	struct sockaddr_in SendAddr;

	strcpy(TxBuffer, "Unnikrishan");
	SendAddr = ClntAddr;
	while(1){
		memset(RxBuffer, 0, sizeof(RxBuffer));
		memset(TxBuffer, 0, sizeof(TxBuffer));
		if(recv(ConnectionSocketId, RxBuffer, C_SERVER_MAX_RX_BUFFER_SIZE, 0) == 0)
		{
			return;
		}
		send(ConnectionSocketId, TxBuffer, strlen(TxBuffer), 0);
		PrintAliveMsg(RxBuffer);
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

void CommunicationServer::PrintAliveMsg(char * msg)
{
	cout << "C-Server alive:" << msg << endl;
}

void DiscoveryServer::PrintAliveMsg(char * msg)
{
	cout << "B-Server alive:" << msg << endl;
}

}
