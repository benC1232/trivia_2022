#include "Server.h"

Server::Server()
{
	this->m_database = new SqliteDataBase();
	RequestHandlerFactory* temp = new RequestHandlerFactory(this->m_database);
	this->m_requestHandlerFactory = *temp;
	this->m_communicator = new Communicator(temp);
}

Server::~Server()
{
	delete this->m_communicator;
	delete this->m_database;
}

//creates the t_connector and detaches it
void Server::run()
{
	std::thread t_connector(&Communicator::startHandleRequests, m_communicator);
	t_connector.detach();
}