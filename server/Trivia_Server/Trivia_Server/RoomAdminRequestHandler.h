#pragma once
#include "LoggedUser.h"
#include "RequestHandlerFactory.h"
#include "Room.h"
#include "RoomManager.h"
class RequestHandlerFactory;
class RoomAdminRequestHandler :
	public IRequestHandler
{
public:
	RoomAdminRequestHandler(Room* room, LoggedUser user, RoomManager* roomManager, RequestHandlerFactory* requestHandlerFactory);
	bool isRequestRelevant(RequestInfo requestInfo)override;
	RequestResult handleRequest(RequestInfo requestInfo)override;
private:

	Room* m_room;
	LoggedUser m_user;
	RoomManager* m_roomManager;
	RequestHandlerFactory* m_requestHandlerFactory;
	RequestResult closeRoom(RequestInfo requestInfo);
	RequestResult startGame(RequestInfo requestInfo);
	RequestResult getRoomState(RequestInfo requestInfo);
};
