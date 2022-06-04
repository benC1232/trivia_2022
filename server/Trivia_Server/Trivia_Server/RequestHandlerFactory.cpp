#include "RequestHandlerFactory.h"

RequestHandlerFactory::RequestHandlerFactory(IDatabase* db)
{
	m_database = db;
	m_loginManager = new LoginManager(this->m_database);
	m_statisticsManager = new StatisticsManager(this->m_database);
	m_roomManager = new RoomManager();
}

RequestHandlerFactory::~RequestHandlerFactory()
{
}

LoginRequestHandler* RequestHandlerFactory::createLoginRequestHandler()
{
	return new LoginRequestHandler(this);
}

LoginManager* RequestHandlerFactory::getLoginManager()
{
	return this->m_loginManager;
}

MenuRequestHandler* RequestHandlerFactory::createMenuRequestHandler(LoggedUser user)
{
	return new MenuRequestHandler(user, this->m_roomManager, this->m_statisticsManager, this);
}

RoomAdminRequestHandler* RequestHandlerFactory::createRoomAdminRequestHandler(LoggedUser user, Room* room)
{
	return new RoomAdminRequestHandler(room, user, this->m_roomManager, this);
}

RoomMemberRequestHandler* RequestHandlerFactory::createRoomMemberRequestHandler(LoggedUser user, Room* room)
{
	return new RoomMemberRequestHandler(room, user, this->m_roomManager, this);
}

StatisticsManager& RequestHandlerFactory::getStatisticsManager()
{
	return *this->m_statisticsManager;
}

RoomManager& RequestHandlerFactory::getRoomManager()
{
	return *this->m_roomManager;
}