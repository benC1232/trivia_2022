#include "RoomMemberRequestHandler.h"
#define GET_ROOM_STATE_CODE 12
#define LEAVE_ROOM_CODE 13
RoomMemberRequestHandler::RoomMemberRequestHandler(Room* room, LoggedUser user, RoomManager* roomManager, RequestHandlerFactory* requestHandlerFactory)
{
	this->m_room = room;
	this->m_user = user;
	this->m_roomManager = roomManager;
	this->m_requestHandlerFactory = requestHandlerFactory;
}
bool RoomMemberRequestHandler::isRequestRelevant(RequestInfo requestInfo)
{
	return requestInfo.id == GET_ROOM_STATE_CODE || requestInfo.id == LEAVE_ROOM_CODE;
}

RequestResult RoomMemberRequestHandler::handleRequest(RequestInfo requestInfo)
{
	RequestResult result;
	if (requestInfo.id == GET_ROOM_STATE_CODE)
	{
		result = getRoomState(requestInfo);
	}
	else if (requestInfo.id == LEAVE_ROOM_CODE)
	{
		result = leaveRoom(requestInfo);
	}
	else
	{
		ErrorResponse num;
		num.message = "error while handling request [room member request handler has received a wrong code]";
		result.buffer = JsonResponsePacketSerializer::serializeErrorResponse(num);
		result.newHandler = nullptr;
	}
	return result;
}

RequestResult RoomMemberRequestHandler::leaveRoom(RequestInfo requestInfo)
{
	RequestResult result;
	this->m_room->removeUser(this->m_user);
	LeaveRoomResponse response;
	response.status = LEAVE_ROOM_CODE;
	result.buffer = JsonResponsePacketSerializer::serializeLeaveRoomResponse(response);
	result.newHandler = this->m_requestHandlerFactory->createMenuRequestHandler(this->m_user);
	return result;
}

RequestResult RoomMemberRequestHandler::getRoomState(RequestInfo requestInfo)
{
	RequestResult result;
	try
	{
		GetRoomStateResponse getRoomStateResponse;
		getRoomStateResponse.status = GET_ROOM_STATE_CODE;
		getRoomStateResponse.hasGameBegun = this->m_room->getData().isActive;
		getRoomStateResponse.players = this->m_room->getAllUsers();
		getRoomStateResponse.questionCount = this->m_room->getData().numOfQuestionsInGame;
		getRoomStateResponse.answerTimeOut = this->m_room->getData().timePerQuestion;
		result.buffer = JsonResponsePacketSerializer::serializeGetRoomStateResponse(getRoomStateResponse);
		if (this->m_room->getData().isActive)
		{
			Game* game = this->m_requestHandlerFactory->getGameManager().getGame(this->m_user);
			result.newHandler = this->m_requestHandlerFactory->createGameRequestHandler(this->m_user, game);
		}
		else
		{
			result.newHandler = this;
		}
		return result;
	}
	catch (std::bad_alloc e)
	{
		ErrorResponse num;
		num.message = "std::bad_alloc was thrown while handling request [room member request handler]";
		result.buffer = JsonResponsePacketSerializer::serializeErrorResponse(num);
		result.newHandler = this->m_requestHandlerFactory->createMenuRequestHandler(this->m_user);
		return result;
	}
}