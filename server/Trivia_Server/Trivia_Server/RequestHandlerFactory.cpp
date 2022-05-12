#include "RequestHandlerFactory.h"

RequestHandlerFactory::RequestHandlerFactory(IDatabase* db)
{
	m_database = db;
	m_loginManager = new LoginManager();
}

RequestHandlerFactory::RequestHandlerFactory()
{
}

RequestHandlerFactory::~RequestHandlerFactory()
{
}

LoginRequestHandler* RequestHandlerFactory::createLoginRequestHandler()
{
	return new LoginRequestHandler();
}

LoginManager* RequestHandlerFactory::getLoginManager()
{
	return m_loginManager;
}