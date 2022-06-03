#include "RoomMemberRequestHandler.h"
#define GET_ROOM_STATE_CODE 12
#define LEAVE_ROOM_CODE 13
bool RoomMemberRequestHandler::isRequestRelevant(RequestInfo requestInfo)
{
	return requestInfo.id == GET_ROOM_STATE_CODE || requestInfo.id == LEAVE_ROOM_CODE;
}

RequestResult RoomMemberRequestHandler::handleRequest(RequestInfo requestInfo)
{
	RequestResult result;
	if (requestInfo.id == GET_ROOM_STATE_CODE)
	{
		result = leaveRoom(requestInfo);
	}
	else if (requestInfo.id == LEAVE_ROOM_CODE)
	{
		result = getRoomState(requestInfo);
	}
	else
	{
		//throw error
	}
}

RequestResult RoomMemberRequestHandler::leaveRoom(RequestInfo requestInfo)
{
	RequestResult result;
	this->m_room.removeUser(this->m_user);
	LeaveRoomResponse response;
	response.status = LEAVE_ROOM_CODE;
	result.buffer = JsonResponsePacketSerializer::serializeLeaveRoomResponse(response);
	result.newHandler = this->m_requestHandlerFactory->createMenuRequestHandler(this->m_user);
	return result;
}

RequestResult RoomMemberRequestHandler::getRoomState(RequestInfo requestInfo)
{
	RequestResult result;
	GetRoomStateResponse getRoomStateResponse;
	getRoomStateResponse.status = GET_ROOM_STATE_CODE;
	getRoomStateResponse.hasGameBegun = this->m_room.getData().isActive;
	getRoomStateResponse.players = this->m_room.getAllUsers();
	getRoomStateResponse.questionCount = this->m_room.getData().numOfQuestionsInGame;
	result.buffer = JsonResponsePacketSerializer::serializeGetRoomStateResponse(getRoomStateResponse);
	//create a roomrequesthandler request here!!!
	return result;
}