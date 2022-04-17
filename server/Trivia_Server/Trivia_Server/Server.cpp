#include "Server.h"

Server::Server()
{
	this->m_communicator = new Communicator();
}

Server::~Server()
{
	delete this->m_communicator;
}

//creates the t_connector and detaches it
void Server::run()
{
	std::thread t_connector(&Communicator::startHandleRequests, m_communicator);
	t_connector.detach();
}