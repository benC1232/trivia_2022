#pragma once
#include "SqliteDataBase.h"
#include "IDatabase.h"
#include "LoginManager.h"
#include "LoginRequestHandler.h"
class RequestHandlerFactory
{
public:
	RequestHandlerFactory(IDatabase* db);
	~RequestHandlerFactory();
	LoginRequestHandler* createLoginRequestHandler();
	LoginManager* getLoginManager();
private:
	LoginManager* m_loginManager;
	IDatabase* m_database;
};
