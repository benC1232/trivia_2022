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
#include "GameRequestHandler.h"
#include "GameManager.h"
class LoginRequestHandler;
class MenuRequestHandler;
class RoomMemberRequestHandler;
class RoomAdminRequestHandler;
class GameRequestHandler;

class RequestHandlerFactory
{
public:
	RequestHandlerFactory() = default;
	RequestHandlerFactory(IDatabase* db);
	~RequestHandlerFactory();
	LoginRequestHandler* createLoginRequestHandler();
	LoginManager* getLoginManager() const;
	MenuRequestHandler* createMenuRequestHandler(LoggedUser user);
	RoomAdminRequestHandler* createRoomAdminRequestHandler(LoggedUser user, Room* room);
	RoomMemberRequestHandler* createRoomMemberRequestHandler(LoggedUser user, Room* room);
	GameRequestHandler* createGameRequestHandler(LoggedUser user, Game* game);

	StatisticsManager& getStatisticsManager() const;
	RoomManager& getRoomManager() const;
	GameManager& getGameManager() const;
	IDatabase& getDatabase() const;

private:
	LoginManager* m_loginManager;
	IDatabase* m_database;
	StatisticsManager* m_statisticsManager;
	RoomManager* m_roomManager;
	GameManager* m_gameManager;
};
