#include "RequestHandlerFactory.h"

RequestHandlerFactory::RequestHandlerFactory(IDatabase* db)
{
	this->m_database = db;
	this->m_loginManager = new LoginManager(db);
}

RequestHandlerFactory::~RequestHandlerFactory()
{
	delete this->m_loginManager;
}

LoginRequestHandler* RequestHandlerFactory::createLoginRequestHandler()
{
	return new LoginRequestHandler();
}

LoginManager* RequestHandlerFactory::getLoginManager()
{
	return this->m_loginManager;
}