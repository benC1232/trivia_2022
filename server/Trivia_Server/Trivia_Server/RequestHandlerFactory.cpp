#include "RequestHandlerFactory.h"

RequestHandlerFactory::RequestHandlerFactory(IDatabase* db)
{
	m_database = db;
	m_loginManager = new LoginManager(this->m_database);
	m_statisticsManager = new StatisticsManager(this->m_database);
	m_roomManager = new RoomManager();
	m_gameManager = new GameManager(this->m_database);
}

RequestHandlerFactory::~RequestHandlerFactory()
{
}
/*
* function creates a login request handler and returns it
* input: none
* output: LoginRequestHandler*
*/
LoginRequestHandler* RequestHandlerFactory::createLoginRequestHandler()
{
	return new LoginRequestHandler(this);
}
/*
* getter for login manager
* input: none
* output: LoginManager*
*/
LoginManager* RequestHandlerFactory::getLoginManager() const
{
	return this->m_loginManager;
}
/*
* function creates a menu request handler and returns it
* input: user
* output: MenuRequestHandler*
*/
MenuRequestHandler* RequestHandlerFactory::createMenuRequestHandler(LoggedUser user)
{
	return new MenuRequestHandler(user, this->m_roomManager, this->m_statisticsManager, this);
}
/*
* function creates a room admin request handler and returns it
* input: user, room
* output: RoomAdminRequestHandler*
*/
RoomAdminRequestHandler* RequestHandlerFactory::createRoomAdminRequestHandler(LoggedUser user, Room* room)
{
	return new RoomAdminRequestHandler(room, user, this->m_roomManager, this);
}
/*
* function creates a room member request handler and returns it
* input: user, room
* output: RoomMemberRequestHandler*
*/
RoomMemberRequestHandler* RequestHandlerFactory::createRoomMemberRequestHandler(LoggedUser user, Room* room)
{
	return new RoomMemberRequestHandler(room, user, this->m_roomManager, this);
}
/*
* function creates a game request handler and returns it
* input: user, game
* output: GameRequestHandler*
*/
GameRequestHandler* RequestHandlerFactory::createGameRequestHandler(LoggedUser user, Game* game)
{
	return new GameRequestHandler(this->m_gameManager, user, this, game);
}
/*
* getter function for the statistics manager
* input: none
* output: StatisticsManager*
*/
StatisticsManager& RequestHandlerFactory::getStatisticsManager() const
{
	return *this->m_statisticsManager;
}
/*
* getter function for the room manager
* input: none
* output: RoomManager*
*/
RoomManager& RequestHandlerFactory::getRoomManager() const
{
	return *this->m_roomManager;
}
/*
* getter function for the game manager
* input: none
* output: GameManager*
*/
GameManager& RequestHandlerFactory::getGameManager() const
{
	return *this->m_gameManager;
}
/*
* getter function for the database
* input: none
* output: IDatabase*
*/
IDatabase& RequestHandlerFactory::getDatabase() const
{
	return *this->m_database;
}