#pragma once
#include "Room.h"
#include "LoggedUser.h"
#include "RoomManager.h"
#include "RequestHandlerFactory.h"
class RequestHandlerFactory;
class RoomAdminRequestHandler
{
public:
	RoomAdminRequestHandler(Room* room, LoggedUser user, RoomManager* roomManager, RequestHandlerFactory* requestHandlerFactory);
	bool isRequestRelevant(RequestInfo requestInfo);
	RequestResult handleRequest(RequestInfo requestInfo);
private:

	Room* m_room;
	LoggedUser m_user;
	RoomManager* m_roomManager;
	RequestHandlerFactory* m_requestHandlerFactory;
	RequestResult closeRoom(RequestInfo requestInfo);
	RequestResult startGame(RequestInfo requestInfo);
	RequestResult getRoomState(RequestInfo requestInfo);
};
