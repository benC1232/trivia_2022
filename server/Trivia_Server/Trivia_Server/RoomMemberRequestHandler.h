#pragma once
#include "Room.h"
#include "LoggedUser.h"
#include "RoomManager.h"
#include "RequestHandlerFactory.h"
class RequestHandlerFactory;
class RoomMemberRequestHandler :
	public IRequestHandler
{
public:
	RoomMemberRequestHandler(Room* room, LoggedUser user, RoomManager* roomManager, RequestHandlerFactory* requestHandlerFactory);
	bool isRequestRelevant(RequestInfo requestInfo)override;
	RequestResult handleRequest(RequestInfo requestInfo)override;
private:

	Room* m_room;
	LoggedUser m_user;
	RoomManager* m_roomManager;
	RequestHandlerFactory* m_requestHandlerFactory;
	RequestResult leaveRoom(RequestInfo requestInfo);
	RequestResult getRoomState(RequestInfo requestInfo);
};
