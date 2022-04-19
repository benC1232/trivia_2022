#include "Communicator.h"

Communicator::Communicator()
{
	//copied this code from week 13
	this->m_serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (this->m_serverSocket == INVALID_SOCKET)
		throw std::exception(__FUNCTION__ " - socket");
}

Communicator::~Communicator()
{
	//this code is also copied from week 13
	try
	{
		closesocket(this->m_serverSocket);
	}
	catch (...) {}
}

void Communicator::startHandleRequests()
{
	struct sockaddr_in sa = { 0 };

	sa.sin_port = htons(PORT); // port that server will listen for
	sa.sin_family = AF_INET;   // must be AF_INET
	sa.sin_addr.s_addr = INADDR_ANY;    // when there are few ip's for the machine. We will use always "INADDR_ANY"

	// Connects between the socket and the configuration (port and etc..)
	if (bind(this->m_serverSocket, (struct sockaddr*)&sa, sizeof(sa)) == SOCKET_ERROR)
		throw std::exception(__FUNCTION__ " - bind");

	// Start listening for incoming requests of clients
	if (listen(this->m_serverSocket, SOMAXCONN) == SOCKET_ERROR)
		throw std::exception(__FUNCTION__ " - listen");
	std::cout << "Listening on port " << PORT << std::endl;

	while (true)
	{
		// the main thread is only accepting clients
		// and add then to the list of handlers
		std::cout << "Waiting for client connection request" << std::endl;
		bindAndListen();
	}
}

void Communicator::bindAndListen()
{
	// this accepts the client and create a specific socket from server to this client
// the process will not continue until a client connects to the server
	SOCKET client_socket = accept(this->m_serverSocket, NULL, NULL);
	if (client_socket == INVALID_SOCKET)
		throw std::exception(__FUNCTION__);

	std::cout << "Client accepted. Server and client can speak" << std::endl;
	// the function that handle the conversation with the client
	std::thread tr(&Communicator::handleNewClient, this, client_socket);
	tr.detach();
}

void Communicator::handleNewClient(SOCKET clientSocket)
{
	LoginRequestHandler* handler;
	this->m_clients.insert({ clientSocket, handler });
	try
	{
		std::string s = "Hello";
		send(clientSocket, s.c_str(), s.size(), 0);  // last parameter: flag. for us will be 0.

		char m[6];
		recv(clientSocket, m, 5, 0);
		m[5] = 0;
		std::cout << "Client sent: " << m << std::endl;

		// Closing the socket (in the level of the TCP protocol)
		this->m_clients.erase(clientSocket);
		closesocket(clientSocket);
	}
	catch (...)
	{
		this->m_clients.erase(clientSocket);
		closesocket(clientSocket);
	}
}