#include "RoomAdminRequestHandler.h"
#define CLOSE_ROOM_CODE 10
#define START_GAME_CODE 11
#define GET_ROOM_STATE_CODE 12
RoomAdminRequestHandler::RoomAdminRequestHandler(Room* room, LoggedUser user, RoomManager* roomManager, RequestHandlerFactory* requestHandlerFactory)
{
	this->m_room = room;
	this->m_user = user;
	this->m_roomManager = roomManager;
	this->m_requestHandlerFactory = requestHandlerFactory;
}
bool RoomAdminRequestHandler::isRequestRelevant(RequestInfo requestInfo)
{
	return requestInfo.id == CLOSE_ROOM_CODE || requestInfo.id == START_GAME_CODE || requestInfo.id == GET_ROOM_STATE_CODE;
}

RequestResult RoomAdminRequestHandler::handleRequest(RequestInfo requestInfo)
{
	RequestResult result;
	if (requestInfo.id == CLOSE_ROOM_CODE)
	{
		result = closeRoom(requestInfo);
	}
	else if (requestInfo.id == START_GAME_CODE)
	{
		result = startGame(requestInfo);
	}
	else if (requestInfo.id == GET_ROOM_STATE_CODE)
	{
		result = getRoomState(requestInfo);
	}
	else
	{
		ErrorResponse num;
		num.message = "error while handling request [room admin request handler has recived a wrong code]";
		result.buffer = JsonResponsePacketSerializer::serializeErrorResponse(num);
		result.newHandler = nullptr;
	}
	return result;
}

RequestResult RoomAdminRequestHandler::closeRoom(RequestInfo requestInfo)
{
	this->m_requestHandlerFactory->getRoomManager().deleteRoom(this->m_room->getData().id);
	RequestResult result;
	CloseRoomResponse closeRoomResponse;
	closeRoomResponse.status = CLOSE_ROOM_CODE;
	result.buffer = JsonResponsePacketSerializer::serializeCloseRoomResponse(closeRoomResponse);
	result.newHandler = this->m_requestHandlerFactory->createMenuRequestHandler(this->m_user);
	return result;
}

RequestResult RoomAdminRequestHandler::startGame(RequestInfo requestInfo)
{
	RequestResult result;
	Game* game = this->m_requestHandlerFactory->getGameManager().createGame(*this->m_room);
	StartGameResponse startGameResponse;
	startGameResponse.status = START_GAME_CODE;
	result.buffer = JsonResponsePacketSerializer::serializeStartGameResponse(startGameResponse);
	result.newHandler = this->m_requestHandlerFactory->createGameRequestHandler(this->m_user, game);
	return result;
}

RequestResult RoomAdminRequestHandler::getRoomState(RequestInfo requestInfo)
{
	RequestResult result;
	GetRoomStateResponse getRoomStateResponse;
	getRoomStateResponse.status = GET_ROOM_STATE_CODE;
	getRoomStateResponse.hasGameBegun = this->m_room->getData().isActive;
	getRoomStateResponse.players = this->m_room->getAllUsers();
	getRoomStateResponse.questionCount = this->m_room->getData().numOfQuestionsInGame;
	getRoomStateResponse.answerTimeOut = this->m_room->getData().timePerQuestion;
	result.buffer = JsonResponsePacketSerializer::serializeGetRoomStateResponse(getRoomStateResponse);
	result.newHandler = this;
	return result;
}