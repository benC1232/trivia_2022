#pragma once
#include "Room.h"
#include "LoggedUser.h"
#include "RoomManager.h"
#include "RequestHandlerFactory.h"
class RoomMemberRequestHandler
{
public:
	bool isRequestRelevant(RequestInfo requestInfo);
	RequestResult handleRequest(RequestInfo requestInfo);
private:

	Room m_room;
	LoggedUser m_user;
	RoomManager* m_roomManager;
	RequestHandlerFactory* m_requestHandlerFactory;
	RequestResult leaveRoom(RequestInfo requestInfo);
	RequestResult getRoomState(RequestInfo requestInfo);
};
