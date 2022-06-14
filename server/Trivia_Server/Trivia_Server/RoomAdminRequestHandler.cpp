#include "RoomAdminRequestHandler.h"
#define CLOSE_ROOM_CODE 10
#define START_GAME_CODE 11
#define GET_ROOM_STATE_CODE 12

RoomAdminRequestHandler::RoomAdminRequestHandler(Room* room, LoggedUser user, RoomManager* roomManager,
	RequestHandlerFactory* requestHandlerFactory)
{
	this->m_room = room;
	this->m_user = user;
	this->m_roomManager = roomManager;
	this->m_requestHandlerFactory = requestHandlerFactory;
}

bool RoomAdminRequestHandler::isRequestRelevant(RequestInfo requestInfo)
{
	return requestInfo.id == CLOSE_ROOM_CODE || requestInfo.id == START_GAME_CODE || requestInfo.id ==
		GET_ROOM_STATE_CODE;
}
/*
* function handles the requests that this part of the state machine is responsible for
* input: request - the request that is being handled
* output: the response that is being sent to the client
*/
RequestResult RoomAdminRequestHandler::handleRequest(RequestInfo requestInfo)
{
	RequestResult result;
	if (requestInfo.id == CLOSE_ROOM_CODE)
	{
		result = closeRoom(requestInfo);
	}
	else if (requestInfo.id == START_GAME_CODE)
	{
		try
		{
			result = startGame(requestInfo);
		}
		catch (std::exception& e)
		{
			ErrorResponse num;
			num.message = e.what();
			result.buffer = JsonResponsePacketSerializer::serializeErrorResponse(num);
			result.newHandler = nullptr;
		}
	}
	else if (requestInfo.id == GET_ROOM_STATE_CODE)
	{
		result = getRoomState(requestInfo);
	}
	else
	{
		ErrorResponse num;
		num.message = "error while handling request [room admin request handler has received a wrong code]";
		result.buffer = JsonResponsePacketSerializer::serializeErrorResponse(num);
		result.newHandler = nullptr;
	}
	return result;
}
/*
* function closes the room
* input: request - the request that is being handled
* output: the response that is being sent to the client
*/
RequestResult RoomAdminRequestHandler::closeRoom(RequestInfo requestInfo) const
{
	this->m_requestHandlerFactory->getRoomManager().deleteRoom(this->m_room->getData().id);
	RequestResult result;
	CloseRoomResponse closeRoomResponse;
	closeRoomResponse.status = CLOSE_ROOM_CODE;
	result.buffer = JsonResponsePacketSerializer::serializeCloseRoomResponse(closeRoomResponse);
	result.newHandler = this->m_requestHandlerFactory->createMenuRequestHandler(this->m_user);
	return result;
}
/*
* function starts the game
* input: request - the request that is being handled
* output: the response that is being sent to the client
*/
RequestResult RoomAdminRequestHandler::startGame(RequestInfo requestInfo) const
{
	if (this->m_room->getAllUsers().size() == 1)
	{
		throw std::exception("cant start a game with one player");
	}
	this->m_requestHandlerFactory->getRoomManager().getRoom(this->m_room->getData().id)->setIsActive(true);
	RequestResult result;
	Game* game = this->m_requestHandlerFactory->getGameManager().createGame(*this->m_room);
	StartGameResponse startGameResponse;
	startGameResponse.status = START_GAME_CODE;
	result.buffer = JsonResponsePacketSerializer::serializeStartGameResponse(startGameResponse);
	result.newHandler = this->m_requestHandlerFactory->createGameRequestHandler(this->m_user, game);
	return result;
}
/*
* function gets the state of the room
* input: request - the request that is being handled
* output: the response that is being sent to the client
*/
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