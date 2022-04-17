#include "Server.h"

Server::~Server()
{
	delete this->m_communicator;
}

Server::Server()
{
	this->m_communicator = new Communicator();
}

void Server::run()
{
}