#pragma once
#include "SqliteDataBase.h"
#include "IDatabase.h"
#include "LoginManager.h"
#include "LoginRequestHandler.h"
#include "RoomManager.h"
#include "StatisticsManager.h"
#include "MenuRequestHandler.h"
#include "RoomAdminRequestHandler.h"
#include "RoomMemberRequestHandler.h"
class LoginRequestHandler;
class MenuRequestHandler;
class RoomMemberRequestHandler;
class RoomAdminRequestHandler;

class RequestHandlerFactory
{
public:
	RequestHandlerFactory();
	RequestHandlerFactory(IDatabase* db);
	~RequestHandlerFactory();
	LoginRequestHandler* createLoginRequestHandler();
	LoginManager* getLoginManager();
	MenuRequestHandler* createMenuRequestHandler(LoggedUser user);
	RoomAdminRequestHandler* createRoomAdminRequestHandler(LoggedUser user, Room* room);
	RoomMemberRequestHandler* createRoomMemberRequestHandler(LoggedUser user, Room* room);

	StatisticsManager& getStatisticsManager();
	RoomManager& getRoomManager();

private:
	LoginManager* m_loginManager;
	IDatabase* m_database;
	StatisticsManager* m_statisticsManager;
	RoomManager* m_roomManager;
};
