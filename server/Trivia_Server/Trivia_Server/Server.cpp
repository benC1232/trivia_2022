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
	std::thread t_connector(&Communicator::startHandleRequests, m_communicator);
	t_connector.detach();
}