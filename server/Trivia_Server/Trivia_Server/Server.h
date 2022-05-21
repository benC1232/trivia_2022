#pragma once
#include "Communicator.h"
#include "RequestHandlerFactory.h"
#include "IDatabase.h"
#include "SqliteDataBase.h"
#include <thread>

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
