#pragma once
#define PORT 1618
#pragma comment(lib, "Ws2_32.lib")
#include <thread>
#include <WinSock2.h>
#include <map>
#include "IRequestHandler.h"
#include <iostream>
#include <exception>
#include "LoginRequestHandler.h"
class Communicator
{
public:
	Communicator();
	~Communicator();
	void startHandleRequests();
private:
	SOCKET m_serverSocket;
	std::map<SOCKET, IRequestHandler*> m_clients;
	void bindAndListen();
	void handleNewClient(SOCKET clientSocket);
};
