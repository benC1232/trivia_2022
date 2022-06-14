#include "Server.h"

#include <thread>

Server::Server()
{
	this->m_database = new SqliteDataBase();
	this->m_requestHandlerFactory = new RequestHandlerFactory(this->m_database);
	this->m_communicator = new Communicator(this->m_requestHandlerFactory);
}

Server::~Server()
{
	delete this->m_communicator;
	delete this->m_database;
	delete this->m_requestHandlerFactory;
}

//creates the t_connector and detaches it
void Server::run()
{
	std::thread t_connector(&Communicator::startHandleRequests, m_communicator);
	t_connector.detach();
}
