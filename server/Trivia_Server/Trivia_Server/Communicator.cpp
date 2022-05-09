#include "Communicator.h"
#define MESSAGE_SIZE 1024
#define JSON_OFFSET 5
Communicator::Communicator(RequestHandlerFactory* factory)
{
	//copied this code from week 13
	this->m_handlerFactory = factory;
	this->m_serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (this->m_serverSocket == INVALID_SOCKET)
		throw std::exception(__FUNCTION__ " - socket");
}

Communicator::~Communicator()
{
	//this code is also copied from week 13

	closesocket(this->m_serverSocket);
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
	LoginRequestHandler* handler = new LoginRequestHandler();
	this->m_clients.insert({ clientSocket, handler });
	try
	{
		char clientMessage[MESSAGE_SIZE];
		recv(clientSocket, clientMessage, MESSAGE_SIZE, 0);
		int jsonSize = getJsonSize(clientMessage);
		std::vector<unsigned char> buffer = msgToBuffer(clientMessage, jsonSize + JSON_OFFSET);
		RequestInfo request;
		request.id = int(buffer[0]);
		request.receivalTime = std::time(0);
		request.buffer = buffer;
		RequestResult result = handler->handleRequest(request);
		char* response = bufferToMsg(result.buffer);
		int responseSize = result.buffer.size();
		send(clientSocket, response, responseSize, 0);
		delete response;
		this->m_clients.erase(clientSocket);
		closesocket(clientSocket);
		std::cout << "socket closed successfully" << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		this->m_clients.erase(clientSocket);
		closesocket(clientSocket);
	}
}

int Communicator::getJsonSize(char buffer[])
{
	int size = (int)(buffer[1] << 24 | buffer[2] << 16 | buffer[3] << 8 | buffer[4]);
	return size;
}

std::vector<unsigned char> Communicator::msgToBuffer(char msg[], int size)
{
	std::vector<unsigned char> buffer;
	buffer.resize(size);
	for (int i = 0; i < size; i++)
	{
		buffer[i] = msg[i];
	}
	return buffer;
}

char* Communicator::bufferToMsg(std::vector<unsigned char> buffer)
{
	char* msg = new char[buffer.size()];
	for (int i = 0; i < buffer.size(); i++)
	{
		msg[i] = buffer[i];
	}
	return msg;
}