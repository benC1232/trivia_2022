#pragma once
#include "Communicator.h"
#include "IDatabase.h"
#include "RequestHandlerFactory.h"
#include "SqliteDataBase.h"

class RequestHandlerFactory;
class IDataBase;

class Server
{
public:
	Server();
	~Server();
	void run();
private:
	Communicator* m_communicator;
	RequestHandlerFactory *m_requestHandlerFactory;
	IDatabase* m_database;
};
