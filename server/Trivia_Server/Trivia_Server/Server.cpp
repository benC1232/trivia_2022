#include "Server.h"

Server::Server()
{
	this->m_communicator = new Communicator();
}

Server::~Server()
{
	delete this->m_communicator;
}

void Server::run()
{
	std::thread t_connector(&Communicator::startHandleRequests, m_communicator);
	t_connector.detach();
}