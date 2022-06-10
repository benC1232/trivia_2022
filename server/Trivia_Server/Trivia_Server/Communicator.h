#pragma once
#define PORT 9898
#pragma comment(lib, "Ws2_32.lib")
#include <thread>
#include <WinSock2.h>
#include <map>
#include "IRequestHandler.h"
#include "RequestHandlerFactory.h"
#include <iostream>
#include <exception>
#include "LoginRequestHandler.h"
#include "IDatabase.h"
class Communicator
{
public:
	Communicator(RequestHandlerFactory* factory);
	~Communicator();
	void startHandleRequests();
private:
	RequestHandlerFactory* m_handlerFactory;
	SOCKET m_serverSocket;
	std::map<SOCKET, IRequestHandler*> m_clients;
	void bindAndListen();
	void handleNewClient(SOCKET clientSocket);
	int getJsonSize(char buffer[]);
	std::vector<unsigned char> msgToBuffer(char msg[], int size);
	char* bufferToMsg(std::vector<unsigned char> buffer);
};